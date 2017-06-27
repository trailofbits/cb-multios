/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "libcgc.h"
#include "cgc_ctype.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_thompson.h"
#include "cgc_trex.h"

#define TEXT_END_SEQ "\n\n\n"
#define MAX_TEXT_SIZE 500000
#define MAX_SEARCH_STR_SIZE 500

//Put the bug here -- Get it so there is a case where resizing the buffer doesn't set it to null
static int resize_buf(void **buf, cgc_size_t old_size)
{
    if (MAX_TEXT_SIZE / 2 < old_size)
        return 0;

    int new_size = old_size * 2;
    char *new_buf = cgc_malloc(new_size);
    if (*buf) {
        cgc_memcpy(new_buf, *buf, old_size);
        cgc_free(*buf);
    }
    *buf = new_buf;
    return new_size;
}

static unsigned char readopt(int fd) {
    unsigned char c = 0, d = 0;
    cgc_size_t rx;

    if ((cgc_receive(fd, &c, 1, &rx) != 0 || rx == 0) || (cgc_receive(fd, &d, 1, &rx) != 0 || rx == 0))
        return -1;

    if (d != '\n') {
        while(d != '\n')
            if (cgc_receive(fd, &d, 1, &rx) != 0 || rx == 0)
                return -1;
        return -1;
    }

    return c;
}

static int readtrex(int fd, unsigned char *trex, cgc_size_t size)
{
    cgc_size_t i, rx;
    unsigned char d = 0;

    for (i = 0; i < size; i++) {
        if (cgc_receive(fd, trex, 1, &rx) != 0 || rx == 0)
            return -1;
        if (*trex == '\n')
            break;
        trex++;
    }

    if (*trex != '\n') {
        while(d != '\n')
            if (cgc_receive(fd, &d, 1, &rx) != 0 || rx == 0)
                return -1;
        return -1;
    } else {
        *trex = '\0';
    }

    return i;
}

static int create_text(int fd, unsigned char **text)
{
    cgc_size_t len = 0, buf_size = 16, rx;
    unsigned char *pend_seq = TEXT_END_SEQ;
    unsigned char *buf;

    buf_size = resize_buf(text, buf_size);
    while(buf_size) {
        buf = *text;
        if (cgc_receive(fd, &buf[len], 1, &rx) != 0 || rx == 0)
            goto bad_text;
        if (buf[len] == *pend_seq) {
            if (*++pend_seq == '\0')
                break;
        } else {
            pend_seq = TEXT_END_SEQ;
        }
        if (++len == buf_size)
            buf_size = resize_buf(text, buf_size);
    }
    if(len < 3 || !buf_size)
        goto bad_text;

    (*text)[len - 2] = '\0';
    return len - 2;
bad_text:
    if (buf_size)
        cgc_free(*text);
    *text = NULL;
    return 0;
}

void cgc_print_menu(match_type_e match_type, unsigned char *text, unsigned char *trex)
{
    unsigned char temp;
    cgc_printf("Text Searcher: Main Menu\n");
    cgc_printf("1. Enter Text\n");
    cgc_printf("2. Enter Search String\n");
    cgc_printf("3. Line Search - Partial Matches\n");
    cgc_printf("4. Line Search - Exact Matches\n");
    cgc_printf("5. Print Text\n");
    cgc_printf("6. Print Search String\n");
    cgc_printf("7. Search Text\n");
    cgc_printf("8. Quit\n\n");
    if (text) {
        if (cgc_strlen(text) > 15) {
            temp = text[15];
            text[15] = '\0';
            cgc_printf("[Text=%s...]\n", text);
            text[15] = temp;
        } else {
            cgc_printf("[Text=%s]\n", text);
        }
    }
    if (cgc_strlen(trex)) {
        if (cgc_strlen(trex) > 15) {
            temp = trex[15];
            trex[15] = '\0';
            cgc_printf("[SearchString=%s...]\n", trex);
            trex[15] = temp;
        } else {
            cgc_printf("[SearchString=%s]\n", trex);
        }
    }

    if (match_type == PARTIAL)
        cgc_printf("[LineMatching=Partial]\n");
    if (match_type == ALL)
        cgc_printf("[LineMatching=Exact]\n");
    cgc_printf("Select: ");
}

static void test()
{
    state_t *nfa;
    unsigned char *rpn = NULL;
    unsigned char *test_string = "aaaaaaaa";
    unsigned char *trex = "a";
    int retcode = cgc_retorpn(trex, cgc_strlen(trex) + 1, &rpn);
    retcode = cgc_retorpn(trex, cgc_strlen(trex) + 1, &rpn);
    if (retcode >= 0)
        nfa = cgc_evalrpn(rpn);
    else
        cgc_printf("Invalid search string\n");
    if (nfa == NULL)
        cgc_printf("Bad rpn\n");
    debug_state(nfa);
    cgc_printf("trex = %s\n", trex);
    cgc_printf("rpn = %s\n", rpn);
    cgc_printf("Test string = %s\n", test_string);

    cgc_printf("Partial Matching:\n");
    cgc_match(nfa, test_string, PARTIAL);
    cgc_printf("Full Line Matching:\n");
    cgc_match(nfa, test_string, ALL);

    cgc_exit(0);
}

int main(int cgc_argc, char *cgc_argv[])
{
    int quit = FALSE;
    unsigned char *text = NULL, *rpn = NULL;
    unsigned char trex[MAX_SEARCH_STR_SIZE] = {'\0'};
    unsigned char selection = 0;
    int match_len = 0, text_len = 0, trex_len = 0, retcode;
    match_type_e match_type = PARTIAL;
    state_t *nfa = NULL;
    cgc_init_trex();

    do {
        cgc_printf("\n");
        cgc_print_menu(match_type, text, trex);
        selection = readopt(STDIN);
        //fdprintf(2, "Selection = %c\n", selection);
        switch(selection) {
            case '1':
                cgc_printf("Enter text to search\n");
                if(text) {
                    cgc_free(text);
                    text = NULL;
                }
                text_len = create_text(STDIN, &text);
                break;
            case '2':
                cgc_printf("Enter search string\n");
                trex_len = readtrex(STDIN, trex, MAX_SEARCH_STR_SIZE);
                if (trex_len < 0)
                {
                    trex_len = 0;
                    *trex = 0;
                }
                break;
            case '3':
                match_type = PARTIAL;
                break;
            case '4':
                match_type = ALL;
                break;
            case '5':
                if (text)
                    cgc_printf("--Text--\n%s\n", text);
                else
                    cgc_printf("--Text--\n\n", text);
                break;
            case '6':
                if (cgc_strlen(trex))
                    cgc_printf("--Search String--\n%s\n", trex);
                else
                    cgc_printf("--Search String--\n\n", trex);
                break;
            case '7':
                if (!text_len) {
                    cgc_printf("Input text has not been received\n");
                    break;
                } else if(!trex_len) {
                    cgc_printf("Search text has not been received\n");
                    break;
                }
                retcode = cgc_retorpn(trex, cgc_strlen(trex) + 1, &rpn);
                if (retcode >= 0) {
                    nfa = cgc_evalrpn(rpn);
                } else {
                    cgc_printf("Invalid search string\n");
                    break;
                }
                if (nfa == NULL) {
                    cgc_printf("Bad rpn\n");
                    break;
                }
                cgc_match(nfa, text, match_type);
                break;
            case '8':
                break;
            default:
                cgc_printf("Bad Selection\n");
        }
    } while (selection != '8');

    cgc_printf("Exiting...\n");
    return 0;
}
