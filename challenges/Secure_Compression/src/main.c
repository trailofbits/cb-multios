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

#include "libcgc.h"
#include "cgc_stdio.h"
#include "cgc_string.h"

#include "cgc_sc.h"

const char *secret = (const char*) 0x4347C000;

void cgc_print_menu()
{
    cgc_printf("1. Compress\n");
    cgc_printf("2. Decompress\n");
    cgc_printf("3. Quit\n");
}

void cgc_handle_compress()
{
    int i;
    unsigned char buf[95], *out = NULL;
    unsigned char data[MAX_DATA_SIZE];
    cgc_size_t outlen = 0;
    sc_obj_t *sc = NULL;

    cgc_printf("Key?\n");
    if (cgc_fread(buf, sizeof(buf), cgc_stdin) != sizeof(buf))
        goto fail;

    cgc_memset(data, 0, sizeof(data));
    for (i = 0; i < sizeof(buf); ++i)
    {
        if (buf[i] < 32 || buf[i] > 126)
            goto fail;
        if (data[buf[i]]++ > 0)
            goto fail;
    }

    cgc_printf("Data?\n");
    cgc_memset(data, 0, sizeof(data));
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil((char *) data, sizeof(data), '\0', cgc_stdin) < 0)
        goto fail;

    sc = cgc_sc_new(buf);
    sc->data = data;
    sc->data_len = cgc_strlen((char *)data);
    if (cgc_sc_scompress(sc, &out, &outlen) < 0)
        goto fail;
    cgc_printf("Original Size: %d\n", sc->data_len);
    cgc_printf("Compressed Size: %d (%d%%)\n", outlen, ((int) ((outlen / (sc->data_len * 1.0)) * 100)));
    cgc_printf("Compressed Data: ");
    for (i = 0; i < outlen && i < 32; ++i)
        cgc_printf("%02X", out[i]);
    cgc_printf("\n");

    goto done;

fail:
    cgc_printf("error.\n");
done:
    if (sc)
        cgc_free(sc);
    if (out)
        cgc_free(out);
}

void cgc_handle_decompress()
{
    int i;
    unsigned char buf[95], *out = NULL;
    unsigned char data[MAX_DATA_SIZE];
    cgc_size_t outlen = 0, len = 0;
    sc_obj_t *sc = NULL;

    cgc_printf("Key?\n");
    if (cgc_fread(buf, sizeof(buf), cgc_stdin) != sizeof(buf))
        goto fail;

    cgc_memset(data, 0, sizeof(data));
    for (i = 0; i < sizeof(buf); ++i)
    {
        if (buf[i] < 32 || buf[i] > 126)
            goto fail;
        if (data[buf[i]]++ > 0)
            goto fail;
    }

    cgc_printf("Length?\n");
    cgc_memset(data, 0, sizeof(data));
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil((char *) data, sizeof(data), '\n', cgc_stdin) < 0)
        goto fail;
    len = cgc_strtoul((char *) data, NULL, 10);
    if (len > MAX_DATA_SIZE)
        goto fail;

    cgc_printf("Data?\n");
    cgc_memset(data, 0, sizeof(data));
    if (cgc_fread((char *) data, len, cgc_stdin) < 0)
        goto fail;

    sc = cgc_sc_new(buf);
    sc->data = data;
    sc->data_len = len;
    if (cgc_sc_sdecompress(sc, &out, &outlen) < 0)
        goto fail;
    cgc_printf("Compressed Size: %d\n", sc->data_len);
    cgc_printf("Original Size: %d\n", cgc_strlen((char *) out));
    cgc_printf("Original Data: ");
    cgc_fwrite(out, outlen, cgc_stdout);
    cgc_fwrite("\n", 1, cgc_stdout);
    goto done;

fail:
    cgc_printf("error.\n");
done:
    if (sc)
        cgc_free(sc);
    if (out)
        cgc_free(out);
}

int main(int cgc_argc, char *cgc_argv[])
{
    char buf[8];
    int i;
    cgc_fbuffered(cgc_stdin, 1);
    for (i = 0; i < 8; i += 2)
        cgc_printf("%02X", secret[i] & 0xFF);
    cgc_printf("\n");
    while(1)
    {
        cgc_print_menu();
        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
            return -1;
        switch(cgc_strtoul(buf, NULL, 10))
        {
            case 1:
                cgc_handle_compress();
                break;
            case 2:
                cgc_handle_decompress();
                break;
            case 3:
                cgc_printf("Bye.\n");
                cgc_fflush(cgc_stdout);
                cgc_exit(0);
                break;
            default:
                cgc_printf("Invalid menu.\n");
                break;
        }
    }
    return 0;
}
