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
#include "cgc_string.h"
#include "cgc_barcode.h"
#include "cgc_bitmap.h"

#define CACHE_SIZE 10
#define INPUT_SIZE 2048
static int g_c_idx = 0;
static int g_c_oldest = 0;
static int g_replace_oldest = 0;
static barcode_128_t *g_barcode_cache[CACHE_SIZE];
char g_input[INPUT_SIZE];

void cgc_add_to_cache(barcode_128_t *barcode)
{
    barcode_128_t *removed;
    if (g_replace_oldest || g_c_idx >= CACHE_SIZE) {
        g_replace_oldest = 1;
        removed = g_barcode_cache[g_c_oldest];
        cgc_free(removed->raw_str);
        cgc_free(removed->encoded_data);
        cgc_free(removed);
        removed = NULL;
        g_c_idx = g_c_oldest;
        g_c_oldest = (g_c_oldest + 1) % CACHE_SIZE;
        g_barcode_cache[g_c_idx] = barcode;
    } else {
        g_barcode_cache[g_c_idx++] = barcode;
    }
}

barcode_128_t *cgc_select_from_cache()
{
    unsigned int choice = -1;
    unsigned int max = g_replace_oldest ? 10 : g_c_idx;
    while (choice >= max) {
        cgc_printf("Select Cached Barcode\n");
        int i = 0;
        for (i = 0; i < max; i++) {
            cgc_printf("    %d. Text: %s\n", i+1, g_barcode_cache[(i+g_c_oldest) % CACHE_SIZE]->raw_str);
        }
        cgc_printf("    0. Return to main menu\n");
        cgc_printf(":-$  ");

        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(g_input, INPUT_SIZE, '\n', cgc_stdin) == -1) {
            cgc_printf("Invalid Selection\n");
            cgc_fflush(cgc_stdout);
            cgc_exit(0);
        } else {
            choice = cgc_strtoul(g_input, NULL, 10);
            if (choice == 0)
                return NULL;
            choice--;
        }
    }

    return g_barcode_cache[(choice + g_c_oldest) % CACHE_SIZE];
}

void cgc_input_barcode()
{
    unsigned int choice = -1;

    while (choice > 4) {
        cgc_printf("Input barcode as:\n");
        cgc_printf("    1. String to encode\n");
        cgc_printf("    2. Barcode encoded in ascii (\"|\" and \" \")\n");
        cgc_printf("    3. Barcode bitmap\n");
        cgc_printf("    0. Return to main menu\n");
        cgc_printf(":-$  ");

        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(g_input, INPUT_SIZE, '\n', cgc_stdin) == -1) {
            cgc_printf("Invalid Selection\n");
            cgc_fflush(cgc_stdout);
            cgc_exit(0);
        } else {
            choice = cgc_strtoul(g_input, NULL, 10);
        }
    }

    barcode_bmp_t *barcode_bmp = NULL;
    barcode_bmp_t bmp_headers;
    barcode_128_t *new_barcode = NULL;
    char message[256];
    cgc_fflush(cgc_stdout);
    switch(choice) {
    case 1:
        if (cgc_freaduntil(g_input, INPUT_SIZE, '\n', cgc_stdin) == -1) {
            cgc_printf("Bad input\n");
            cgc_fflush(cgc_stdout);
            cgc_exit(0);
        }

        new_barcode = cgc_create_barcode_from_str(g_input);
        if (new_barcode) {
            cgc_add_to_cache(new_barcode);
            cgc_printf("Successfully added barcode to cache\n");
            cgc_printf("Barcode text: %s\n", new_barcode->raw_str);
        } else {
            cgc_printf("Bad barcode string\n");
        }
        break;
    case 2:
        if (cgc_freaduntil(g_input, INPUT_SIZE, '\n', cgc_stdin) == -1) {
            cgc_printf("Bad input\n");
            cgc_fflush(cgc_stdout);
            cgc_exit(0);
        }

        new_barcode = cgc_create_barcode_from_encoded_data(g_input);
        if (new_barcode) {
            cgc_add_to_cache(new_barcode);
            cgc_printf("Successfully added barcode to cache\n");
            cgc_printf("Barcode text: %s\n", new_barcode->raw_str);
        } else {
            cgc_printf("Bad barcode encoding\n");
        }
        break;
    case 3:
        if (cgc_fread(&bmp_headers, sizeof(barcode_bmp_t), cgc_stdin) == -1) {
            cgc_sprintf(message, "Bad input\n");
            goto cleanup;
        }

        if (cgc_validate_bmp_headers(&bmp_headers.header, &bmp_headers.info) != 0) {
            cgc_sprintf(message, "Bad input\n");
            goto cleanup;
        }

        barcode_bmp = cgc_malloc(bmp_headers.header.file_size);
        cgc_memcpy(barcode_bmp, &bmp_headers, sizeof(barcode_bmp_t));
        cgc_fflush(cgc_stdout);
        if (cgc_fread(barcode_bmp->data, barcode_bmp->info.imagesize, cgc_stdin) == -1) {
            cgc_sprintf(message, "Bad input\n");
            goto cleanup;
        }

        new_barcode = cgc_create_barcode_from_bmp(barcode_bmp);
        if (new_barcode) {
            cgc_add_to_cache(new_barcode);
            cgc_sprintf(message, "Successfully added bitmap barcode to cache\n"
                    "Barcode text: "
                    "%s\n", new_barcode->raw_str);
        } else {
            cgc_sprintf(message, "Bad barcode bitmap\n");
        }

cleanup:
        if (barcode_bmp)
            cgc_free(barcode_bmp);
#ifdef PATCHED_1
        cgc_printf("%s", message);
#else
        cgc_printf(message);
#endif
        break;
    }
}

void cgc_view_cached_barcodes()
{
    unsigned int max = g_replace_oldest ? 10 : g_c_idx;
    cgc_printf("Cached Barcodes\n");
    int i = 0;
    for (i = 0; i < max; i++) {
        cgc_printf("    %d. Text: %s\n", i+1, g_barcode_cache[(i+g_c_oldest) % CACHE_SIZE]->raw_str);
    }
}

void cgc_clear_cached_barcodes()
{
    barcode_128_t *removed;
    unsigned int max = g_replace_oldest ? 10 : g_c_idx;
    int i = 0;
    for (i = 0; i < max; i++) {
        removed = g_barcode_cache[i];
        cgc_free(removed->raw_str);
        cgc_free(removed->encoded_data);
        cgc_free(removed);
        removed = NULL;
    }
    g_replace_oldest = 0;
    g_c_idx = 0;
    g_c_oldest = 0;
}

void cgc_check_seed()
{
    unsigned int x = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    if (x == *(unsigned int*)0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
}

int main(int cgc_argc, char *cgc_argv[])
{
    //barcode_128_t *cur_barcode;
    int running = 1;
    int choice;

    cgc_fbuffered(cgc_stdout, 1);

    cgc_check_seed();

    barcode_128_t *temp_barcode = NULL;
    cgc_printf("Welcome to the EZ Barcode Encoder/Decoder Service\n");
    while (running) {
        cgc_printf("--Select an option--\n");
        cgc_printf("1. Input a new barcode\n");
        cgc_printf("2. View barcode ascii\n");
        cgc_printf("3. Generate barcode image\n");
        cgc_printf("4. View cached barcodes\n");
        cgc_printf("5. Clear cached barcodes\n");
        cgc_printf("6. Quit\n");
        cgc_printf(":-$  ");

        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(g_input, INPUT_SIZE, '\n', cgc_stdin) == -1) {
            cgc_printf("Invalid Selection\n");
            cgc_fflush(cgc_stdout);
            cgc_exit(0);
        }

        choice = cgc_strtol(g_input, NULL, 10);
        switch(choice) {
        case 1:
            cgc_input_barcode();
            break;
        case 2:
            temp_barcode = cgc_select_from_cache();
            if (temp_barcode) {
                cgc_printf("Raw String: ");
                cgc_print_barcode_ascii(temp_barcode, 1);
            }
            break;
        case 3:
            temp_barcode = cgc_select_from_cache();
            if (temp_barcode) {
                barcode_bmp_t *barcode_bmp = cgc_create_barcode_bmp(temp_barcode);
                if (barcode_bmp) {
                    cgc_printf("    Printable Barcode:\n");
                    cgc_fwrite(barcode_bmp, barcode_bmp->header.file_size, cgc_stdout);
                    cgc_printf("\n    Barcode String: %s\n", temp_barcode->raw_str);
                    cgc_free(barcode_bmp);
                } else {
                    cgc_printf("Bad barcode\n");
                }
            }
            break;
        case 4:
            cgc_view_cached_barcodes();
            break;
        case 5:
            cgc_clear_cached_barcodes();
            break;
        case 6:
            running = 0;
            break;
        default:
            cgc_printf("Invalid Selection\n");
        }
    }

    cgc_printf("Thanks for using the EZ Barcode Encoder/Decoder Service\n");
    cgc_fflush(cgc_stdout);
    return 0;
}

