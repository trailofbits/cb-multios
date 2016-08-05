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

#include <libcgc.h>
#include <stdio.h>
#include <string.h>

#include "sc.h"

const char *secret = (const char*) 0x4347C000;

void print_menu()
{
    printf("1. Compress\n");
    printf("2. Decompress\n");
    printf("3. Quit\n");
}

void handle_compress()
{
    int i;
    unsigned char buf[95], *out = NULL;
    unsigned char data[MAX_DATA_SIZE];
    size_t outlen = 0;
    sc_obj_t *sc = NULL;

    printf("Key?\n");
    if (fread(buf, sizeof(buf), stdin) != sizeof(buf))
        goto fail;

    memset(data, 0, sizeof(data));
    for (i = 0; i < sizeof(buf); ++i)
    {
        if (buf[i] < 32 || buf[i] > 126)
            goto fail;
        if (data[buf[i]]++ > 0)
            goto fail;
    }

    printf("Data?\n");
    memset(data, 0, sizeof(data));
    fflush(stdout);
    if (freaduntil((char *) data, sizeof(data), '\0', stdin) < 0)
        goto fail;

    sc = sc_new(buf);
    sc->data = data;
    sc->data_len = strlen((char *)data);
    if (sc_scompress(sc, &out, &outlen) < 0)
        goto fail;
    printf("Original Size: %d\n", sc->data_len);
    printf("Compressed Size: %d (%d%%)\n", outlen, ((int) ((outlen / (sc->data_len * 1.0)) * 100)));
    printf("Compressed Data: ");
    for (i = 0; i < outlen && i < 32; ++i)
        printf("%02X", out[i]);
    printf("\n");

    goto done;

fail:
    printf("error.\n");
done:
    if (sc)
        free(sc);
    if (out)
        free(out);
}

void handle_decompress()
{
    int i;
    unsigned char buf[95], *out = NULL;
    unsigned char data[MAX_DATA_SIZE];
    size_t outlen = 0, len = 0;
    sc_obj_t *sc = NULL;

    printf("Key?\n");
    if (fread(buf, sizeof(buf), stdin) != sizeof(buf))
        goto fail;

    memset(data, 0, sizeof(data));
    for (i = 0; i < sizeof(buf); ++i)
    {
        if (buf[i] < 32 || buf[i] > 126)
            goto fail;
        if (data[buf[i]]++ > 0)
            goto fail;
    }

    printf("Length?\n");
    memset(data, 0, sizeof(data));
    fflush(stdout);
    if (freaduntil((char *) data, sizeof(data), '\n', stdin) < 0)
        goto fail;
    len = strtoul((char *) data, NULL, 10);
    if (len > MAX_DATA_SIZE)
        goto fail;

    printf("Data?\n");
    memset(data, 0, sizeof(data));
    if (fread((char *) data, len, stdin) < 0)
        goto fail;

    sc = sc_new(buf);
    sc->data = data;
    sc->data_len = len;
    if (sc_sdecompress(sc, &out, &outlen) < 0)
        goto fail;
    printf("Compressed Size: %d\n", sc->data_len);
    printf("Original Size: %d\n", strlen((char *) out));
    printf("Original Data: ");
    fwrite(out, outlen, stdout);
    fwrite("\n", 1, stdout);
    goto done;

fail:
    printf("error.\n");
done:
    if (sc)
        free(sc);
    if (out)
        free(out);
}

int main()
{
    char buf[8];
    int i;
    fbuffered(stdin, 1);
    for (i = 0; i < 8; i += 2)
        printf("%02X", secret[i] & 0xFF);
    printf("\n");
    while(1)
    {
        print_menu();
        fflush(stdout);
        if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
            return -1;
        switch(strtoul(buf, NULL, 10))
        {
            case 1:
                handle_compress();
                break;
            case 2:
                handle_decompress();
                break;
            case 3:
                printf("Bye.\n");
                fflush(stdout);
                exit(0);
                break;
            default:
                printf("Invalid menu.\n");
                break;
        }
    }
    return 0;
}
