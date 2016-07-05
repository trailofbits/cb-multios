/*
 * Author: Brian Pak <brian.pak@kapricasecurity.com>
 * 
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
#include <ctype.h>
#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#define CODE_SZ 4000
#define STACK_SZ 1000

#define ERR_OK  0
#define ERR_INV 1
#define ERR_OVF 2
#define ERR_UNF 3

#define OP_UNARY  1
#define OP_BINARY 2

#define BYTE1(x) (x & 0xff)
#define BYTE2(x) ((x >> 8) & 0xff)
#define BYTE3(x) ((x >> 16) & 0xff)
#define BYTE4(x) ((x >> 24) & 0xff)

#define EMIT_BYTE(b) (*(jit->code_ptr++) = b)

#define ASSERT_UNF(opns) \
    if (jit->count < opns) { \
        return ERR_UNF; \
    }

#if PATCHED
#define ASSERT_OVF(sz) \
    if (jit->stack_ptr < jit->stack || \
            jit->code_ptr + (sz) >= jit->code + CODE_SZ) { \
        return ERR_OVF; \
    }
#else
#define ASSERT_OVF(sz)
#endif

typedef struct jit {
    char code[CODE_SZ];
    int stack[STACK_SZ/sizeof(int)];
    char *code_ptr;
    int *stack_ptr;
    int count;
} jit_t;

#define JITStackEnd (jit->stack + STACK_SZ/sizeof(int))

#define MAX_OUTPUT (64*1024)
static char *g_output_buf = NULL;
static size_t g_output_len = 0;

int readuntil(int fd, char *buf, size_t len, char delim)
{
    size_t i;
    char *c = buf;
    for (i = 0; i < len; ++i)
    {
        size_t rx;
        if (receive(fd, c, 1, &rx) != 0 || rx == 0)
            break;
        if (*(c++) == delim)
            break;
    }
    *(c-1) = '\0';
    return c - buf;
}

int jit_int(jit_t *jit, int n)
{
    /* Push the old value and pull in a new value.
     *
     * mov  $stack_ptr, %ecx
     * mov  %edi, [%ecx]
     * xchg %edi, %eax
     * mov  $n, %eax
     */
    int sp = (int) (jit->stack_ptr - 1);
    char code[] = { 0xb9, BYTE1(sp), BYTE2(sp), BYTE3(sp), BYTE4(sp), 0x89,
                    0x39, 0x97, 0xb8, BYTE1(n), BYTE2(n), BYTE3(n), BYTE4(n) };

    ASSERT_OVF(sizeof(code));
    memcpy(jit->code_ptr, code, sizeof(code));
    jit->code_ptr += sizeof(code);
    jit->stack_ptr--;
    jit->count++;

    return ERR_OK;
}

int jit_op(jit_t *jit, char op)
{
    int sp = (int) (jit->stack_ptr);

    switch (op)
    {
        case '+':           /* add */
            ASSERT_OVF(9);
            ASSERT_UNF(OP_BINARY);
            EMIT_BYTE(0x01); EMIT_BYTE(0xf8);
            EMIT_BYTE(0xb9);
            EMIT_BYTE(BYTE1(sp)); EMIT_BYTE(BYTE2(sp)); EMIT_BYTE(BYTE3(sp)); EMIT_BYTE(BYTE4(sp));
            EMIT_BYTE(0x8b); EMIT_BYTE(0x39);
            jit->stack_ptr += 1;
            jit->count -= 1;
            break;

        case '-':           /* sub */
            ASSERT_OVF(9);
            ASSERT_UNF(OP_BINARY);
            EMIT_BYTE(0x29); EMIT_BYTE(0xf8);
            EMIT_BYTE(0xb9);
            EMIT_BYTE(BYTE1(sp)); EMIT_BYTE(BYTE2(sp)); EMIT_BYTE(BYTE3(sp)); EMIT_BYTE(BYTE4(sp));
            EMIT_BYTE(0x8b); EMIT_BYTE(0x39);
            jit->stack_ptr += 1;
            jit->count -= 1;
            break;

        case '*':           /* mul */
            ASSERT_OVF(10);
            ASSERT_UNF(OP_BINARY);
            EMIT_BYTE(0x0f); EMIT_BYTE(0xaf); EMIT_BYTE(0xc7);
            EMIT_BYTE(0xb9);
            EMIT_BYTE(BYTE1(sp)); EMIT_BYTE(BYTE2(sp)); EMIT_BYTE(BYTE3(sp)); EMIT_BYTE(BYTE4(sp));
            EMIT_BYTE(0x8b); EMIT_BYTE(0x39);
            jit->stack_ptr += 1;
            jit->count -= 1;
            break;

        case '/':           /* div */
            ASSERT_OVF(22);
            ASSERT_UNF(OP_BINARY);
            EMIT_BYTE(0x83); EMIT_BYTE(0xff); EMIT_BYTE(0x00);
            EMIT_BYTE(0x75); EMIT_BYTE(0x07); EMIT_BYTE(0x31);
            EMIT_BYTE(0xc0); EMIT_BYTE(0x40); EMIT_BYTE(0x89);
            EMIT_BYTE(0xc3); EMIT_BYTE(0xcd); EMIT_BYTE(0x80);
            EMIT_BYTE(0x99); EMIT_BYTE(0xf7); EMIT_BYTE(0xff);
            EMIT_BYTE(0xb9);
            EMIT_BYTE(BYTE1(sp)); EMIT_BYTE(BYTE2(sp)); EMIT_BYTE(BYTE3(sp)); EMIT_BYTE(BYTE4(sp));
            EMIT_BYTE(0x8b); EMIT_BYTE(0x39);
            jit->stack_ptr += 1;
            jit->count -= 1;
            break;

        case '^':           /* pow */
            ASSERT_OVF(29);
            ASSERT_UNF(OP_BINARY);
            EMIT_BYTE(0x57); EMIT_BYTE(0x31); EMIT_BYTE(0xc9);
            EMIT_BYTE(0x41); EMIT_BYTE(0x83); EMIT_BYTE(0xff);
            EMIT_BYTE(0x00); EMIT_BYTE(0x7c); EMIT_BYTE(0x0a);
            EMIT_BYTE(0x85); EMIT_BYTE(0xff); EMIT_BYTE(0x74);
            EMIT_BYTE(0x07); EMIT_BYTE(0x0f); EMIT_BYTE(0xaf);
            EMIT_BYTE(0xc8); EMIT_BYTE(0x4f); EMIT_BYTE(0xeb);
            EMIT_BYTE(0xf6); EMIT_BYTE(0x49); EMIT_BYTE(0x5f);
            EMIT_BYTE(0x91);
            EMIT_BYTE(0xb9);
            EMIT_BYTE(BYTE1(sp)); EMIT_BYTE(BYTE2(sp)); EMIT_BYTE(BYTE3(sp)); EMIT_BYTE(BYTE4(sp));
            EMIT_BYTE(0x8b); EMIT_BYTE(0x39);
            jit->stack_ptr += 1;
            jit->count -= 1;
            break;

        case '|':           /* abs */
            ASSERT_OVF(14);
            ASSERT_UNF(OP_UNARY);
            EMIT_BYTE(0x52); EMIT_BYTE(0x89); EMIT_BYTE(0xc1);
            EMIT_BYTE(0xc1); EMIT_BYTE(0xf9); EMIT_BYTE(0x1f);
            EMIT_BYTE(0x89); EMIT_BYTE(0xca); EMIT_BYTE(0x31);
            EMIT_BYTE(0xc2); EMIT_BYTE(0x29); EMIT_BYTE(0xca);
            EMIT_BYTE(0x92); EMIT_BYTE(0x5a);
            break;

        case '~':           /* neg */
            ASSERT_OVF(2);
            ASSERT_UNF(OP_UNARY);
            EMIT_BYTE(0xf7); EMIT_BYTE(0xd8);
            break;

        case '!':           /* not */
            ASSERT_OVF(2);
            ASSERT_UNF(OP_UNARY);
            EMIT_BYTE(0xf7); EMIT_BYTE(0xd0);
            break;

        default:            /* nop */
            EMIT_BYTE(0x90); break;
    }

    return 0;
}

int main()
{
    char buf[8192];
    g_output_buf = malloc(MAX_OUTPUT);
    if (g_output_buf == NULL)
    {
        fdprintf(STDOUT, "Failed to allocate output buffer.\n");
        return -1;
    }

    /* Allocate JIT struct */
    jit_t *jit;
    if (allocate(sizeof(jit_t), 1, (void **)&jit) != 0)
    {
        fdprintf(STDOUT, "Failed to allocate JIT struct.\n");
        return -1;
    }

    fdprintf(STDOUT, "> ");
    /* Main RPN loop */
    while (readuntil(STDIN, buf, sizeof(buf), '\n') > 0)
    {
        int val = 0;
        int error = ERR_OK;

        if (strcmp(buf, "quit") == 0)
        {
            fdprintf(STDOUT, "QUIT\n");
            return 0;
        }

        if (strlen(buf) > 0)
        {
            jit->code_ptr = jit->code;
            jit->stack_ptr = JITStackEnd;
            jit->count = 0;

            char prologue[] = { 0x55, 0x8b, 0xec, 0x81, 0xec, 0xff, 0x00, 0x00, 0x00, 0x51, 0x31, 0xc0, 0x89, 0xc2 };
            memcpy(jit->code_ptr, prologue, sizeof(prologue));
            jit->code_ptr += sizeof(prologue);

            char *tok, *input = buf;
            while (*input && input < buf + strlen(buf))
            {
                if (isspace(*input))
                {
                    input++;
                    continue;
                }

                int n = strtol(input, &tok, 0);
                if (input == tok)
                {
                    /* Operator */
                    char c = *(input + 1);
                    if (!isspace(c) && c != '\0')
                    {
                        error = ERR_INV;
                        break;
                    }
                    error = jit_op(jit, *input);
                    input++;
                }
                else
                {
                    /* Number */
                    error = jit_int(jit, n);
                    input = tok;
                }
            }

            char epilogue[] = { 0x59, 0x8b, 0xe5, 0x5d, 0xc3 };
            if (jit->code_ptr + sizeof(epilogue) >= jit->code + CODE_SZ) {
                error = ERR_OVF;
            }
            else
            {
                memcpy(jit->code_ptr, epilogue, sizeof(epilogue));
                jit->code_ptr += sizeof(epilogue);

                /* Execute JIT'd code */
                val = ((int (*)(void)) jit->code)();
            }
        }

        if (error != ERR_OK)
            fdprintf(STDOUT, "Error!\n");
        else
            fdprintf(STDOUT, "%d (0x%08x)\n", val, val);
        fdprintf(STDOUT, "> ");
    }

    return 0;
}
