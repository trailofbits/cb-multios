/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_insn.h"

#define MAX_PKT_LEN 0x10000
#define MAGIC 0x12ab34cd
#define MAJOR 3
#define MINOR 10

typedef struct {
    unsigned int ts;
    unsigned int ts_usec;
    unsigned int length;
    unsigned int orig_length;
    unsigned char data[];
} pkt_hdr_t;

typedef struct {
    unsigned int magic;
    unsigned short major;
    unsigned short minor;
    unsigned int maxlen;
    unsigned int type;
    pkt_hdr_t pkt[];
} file_hdr_t;

void cgc_check_seed()
{
    unsigned int x = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    if (x == *(unsigned int*)0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
}

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    file_hdr_t *file;
    filter_t *filter;
    pkt_hdr_t *pkt;
    unsigned int length, value, i;
    void *secret_page = (void *)secret_page_i;

    (void) secret_page;

    cgc_fbuffered(cgc_stdout, 1);
    cgc_check_seed();

    if (cgc_fread(&length, sizeof(length), cgc_stdin) < 0)
        return 0;

    filter = filter_alloc(length);
    if (filter == NULL)
        return 0;

    for (i = 0; i < length; i++)
    {
        if (cgc_fread(&filter->insn[i], sizeof(filter->insn[0]), cgc_stdin) < 0)
            return 0;
    }

    if (!cgc_filter_validate(filter))
    {
invalid:
        cgc_fwrite("\x00", 1, cgc_stdout);
        cgc_fflush(cgc_stdout);
        return 0;
    }

    cgc_fwrite("\x01", 1, cgc_stdout);
    cgc_fflush(cgc_stdout);

    if (cgc_fread(&length, sizeof(length), cgc_stdin) < 0)
        return 0;

    if (length >= INT_MAX)
        return 0;

    file = cgc_malloc(length);
    if (cgc_fread(file, length, cgc_stdin) < 0)
        return 0;

    if (file->magic != MAGIC || file->major != MAJOR || file->minor < MINOR)
        goto invalid;

    cgc_fwrite("\x01", 1, cgc_stdout);

    pkt = &file->pkt[0];
    for (i = 0; (uintptr_t)pkt < (uintptr_t)file + length; i++)
    {
        if (pkt->length >= MAX_PKT_LEN)
            break;

        value = cgc_filter_execute(filter, (unsigned char *)pkt, sizeof(pkt_hdr_t) + pkt->length);
        cgc_fwrite(&value, sizeof(value), cgc_stdout);
        cgc_fprintf(cgc_stderr, "Packet %d: returned %08X\n", i, value);

        pkt = (pkt_hdr_t *)&pkt->data[pkt->length];
    }

    cgc_fflush(cgc_stdout);

    cgc_free(file);
    cgc_free(filter);
    return 0;
}
