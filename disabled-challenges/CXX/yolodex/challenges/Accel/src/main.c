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
#include "cgc_ctype.h"

#include "cgc_accel.h"
#include "cgc_accelio.h"
#include "cgc_convert.h"

#define ASSIGN "ASSIGN"
#define CLEAR "CLEAR "
#define REPR "REPR "
#define SHOW "SHOW "
#define TABLE "TABLE"
#define EXIT "EXIT"

#define BAD_CLEAR_CMD -8
#define BAD_ASSIGN_CMD -4
#define BAD_SHOW_CMD -2
#define BAD_INPUT -1
#define CMD_SUCCESS 0
#define EXIT_CODE 1

#define LINE_SIZE 512

static void cgc_print_table() {
   cgc_print_assigned_cells();
}

static int cgc_readline(int fd, char *line, cgc_size_t line_size)
{
    cgc_size_t i;
    cgc_size_t rx;

    for (i = 0; i < line_size; i++) {
        if (cgc_receive(fd, line, 1, &rx) != 0 || rx == 0)
            cgc_exit(0);
        if (*line == '\n')
            break;
        line++;
    }

    if (i == line_size && *line != '\n')
        return -1;
    else if (*line != '\n')
        return 1;
    else
        *line = '\0';

    return 0;
}

static int cgc_parse_line(char *line)
{
    int is_repr = 0;
    cgc_size_t i;
    char tmp[32];
    char *tok;
    char val_str[LINE_SIZE];
    char *cell_str;

    if (cgc_strtrim(line, LINE_SIZE, TRIM_FRONT) == -1)
        return BAD_INPUT;

    cgc_memcpy(tmp, line, cgc_strlen(SHOW));
    for (i = 0; i < cgc_strlen(SHOW); i++)
        tmp[i] = cgc_toupper(tmp[i]);

    if (cgc_memcmp(tmp, SHOW, cgc_strlen(SHOW)) == 0)
        goto show_cmd;

    cgc_memcpy(tmp, line, cgc_strlen(REPR));
    for (i = 0; i < cgc_strlen(REPR); i++)
        tmp[i] = cgc_toupper(tmp[i]);

    if (cgc_memcmp(tmp, REPR, cgc_strlen(REPR)) == 0) {
        is_repr = 1;
        goto show_cmd;
    }

    cgc_memcpy(tmp, line, cgc_strlen(CLEAR));
    for (i = 0; i < cgc_strlen(CLEAR); i++)
        tmp[i] = cgc_toupper(tmp[i]);

    if (cgc_memcmp(tmp, CLEAR, cgc_strlen(CLEAR)) == 0)
        goto clear_cmd;

    // Use sizeof to include null terminator (vs cgc_strlen)
    cgc_memcpy(tmp, line, sizeof(EXIT));
    for (i = 0; i < sizeof(EXIT); i++)
        tmp[i] = cgc_toupper(tmp[i]);

    if (cgc_memcmp(tmp, EXIT, sizeof(EXIT)) == 0)
        goto exit_cmd;

    goto assign_cmd;

show_cmd:
    cgc_strtrim(line, LINE_SIZE, TRIM_BACK);
    cgc_memcpy(tmp, &line[cgc_strlen(SHOW)], sizeof(TABLE));
    for (i = 0; i < sizeof(TABLE); i++)
        tmp[i] = cgc_toupper(tmp[i]);

    // Use sizeof to include null terminator (vs cgc_strlen)
    if (cgc_memcmp(tmp, TABLE, sizeof(TABLE)) == 0) {
        cgc_print_table();
        return CMD_SUCCESS;
    } else if (cgc_valid_cell_id(&line[cgc_strlen(SHOW)]) != -1) {
        cell_str = cgc_show_cell(&line[cgc_strlen(SHOW)], is_repr, val_str, LINE_SIZE);
        if (is_repr)
            cgc_printf("Cell Repr: %s\n", cell_str);
        else
            cgc_printf("Cell Value: %s\n", cell_str);
        return CMD_SUCCESS;
    } else {
        return BAD_SHOW_CMD;
    }

clear_cmd:
    if (cgc_clear_cell(&line[cgc_strlen(CLEAR)]) != 0)
        return BAD_CLEAR_CMD;

    return CMD_SUCCESS;

assign_cmd:
    tok = cgc_strsep(&line, "=");
    if (tok == NULL || line == NULL)
        return BAD_INPUT;

    if (cgc_set_cell(tok, line, LINE_SIZE) != 0)
        return BAD_ASSIGN_CMD;

    return CMD_SUCCESS;

exit_cmd:
    return EXIT_CODE;
}

int main(int cgc_argc, char *cgc_argv[]) {
    char line[LINE_SIZE];
    cgc_init_sheet();
    int cgc_exit = 0;
    int line_status;

    do {
        cgc_printf("Accel:-$ ");
        line_status = cgc_readline(STDIN, line, LINE_SIZE);
        if(line_status != 0) {
            cgc_printf("\n");
            continue;
        }

        switch (cgc_parse_line(line)) {
            case BAD_CLEAR_CMD:
                cgc_printf("Error clearing cell\n");
                break;
            case BAD_ASSIGN_CMD:
                cgc_printf("Error assigning cell. Valid Cells: A0-ZZ99\n");
                break;
            case BAD_SHOW_CMD:
                cgc_printf("Error showing data. Try SHOW TABLE or SHOW [A0-ZZ99]\n");
                break;
            case BAD_INPUT:
                cgc_printf("Bad input\n");
                break;
            case CMD_SUCCESS:
                cgc_printf("Success.\n");
                break;
            case EXIT_CODE:
                cgc_exit = 1;
                cgc_printf("Exiting...\n");
                return 0;
            default:
                cgc_printf("Unknown Input\n");
                break;
        }
    } while (!cgc_exit);

    cgc_printf("Unsupported signal. Exiting...\n");
    return 0;
}

