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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "barcode.h"
#include "bitmap.h"

#define CACHE_SIZE 10
#define INPUT_SIZE 2048
static int g_c_idx = 0;
static int g_c_oldest = 0;
static int g_replace_oldest = 0;
static barcode_128_t *g_barcode_cache[CACHE_SIZE];
char g_input[INPUT_SIZE];

void add_to_cache(barcode_128_t *barcode)
{
    barcode_128_t *removed;
    if (g_replace_oldest || g_c_idx >= CACHE_SIZE) {
        g_replace_oldest = 1;
        removed = g_barcode_cache[g_c_oldest];
        free(removed->raw_str);
        free(removed->encoded_data);
        free(removed);
        removed = NULL;
        g_c_idx = g_c_oldest;
        g_c_oldest = (g_c_oldest + 1) % CACHE_SIZE;
        g_barcode_cache[g_c_idx] = barcode;
    } else {
        g_barcode_cache[g_c_idx++] = barcode;
    }
}

barcode_128_t *select_from_cache()
{
    unsigned int choice = -1;
    unsigned int max = g_replace_oldest ? 10 : g_c_idx;
    while (choice >= max) {
        printf("Select Cached Barcode\n");
        int i = 0;
        for (i = 0; i < max; i++) {
            printf("    %d. Text: %s\n", i+1, g_barcode_cache[(i+g_c_oldest) % CACHE_SIZE]->raw_str);
        }
        printf("    0. Return to main menu\n");
        printf(":-$  ");

        fflush(stdout);
        if (freaduntil(g_input, INPUT_SIZE, '\n', stdin) == -1) {
            printf("Invalid Selection\n");
            fflush(stdout);
            exit(0);
        } else {
            choice = strtoul(g_input, NULL, 10);
            if (choice == 0)
                return NULL;
            choice--;
        }
    }

    return g_barcode_cache[(choice + g_c_oldest) % CACHE_SIZE];
}

void input_barcode()
{
    unsigned int choice = -1;

    while (choice > 4) {
        printf("Input barcode as:\n");
        printf("    1. String to encode\n");
        printf("    2. Barcode encoded in ascii (\"|\" and \" \")\n");
        printf("    3. Barcode bitmap\n");
        printf("    0. Return to main menu\n");
        printf(":-$  ");

        fflush(stdout);
        if (freaduntil(g_input, INPUT_SIZE, '\n', stdin) == -1) {
            printf("Invalid Selection\n");
            fflush(stdout);
            exit(0);
        } else {
            choice = strtoul(g_input, NULL, 10);
        }
    }

    barcode_bmp_t *barcode_bmp = NULL;
    barcode_bmp_t bmp_headers;
    barcode_128_t *new_barcode = NULL;
    char message[256];
    fflush(stdout);
    switch(choice) {
    case 1:
        if (freaduntil(g_input, INPUT_SIZE, '\n', stdin) == -1) {
            printf("Bad input\n");
            fflush(stdout);
            exit(0);
        }

        new_barcode = create_barcode_from_str(g_input);
        if (new_barcode) {
            add_to_cache(new_barcode);
            printf("Successfully added barcode to cache\n");
            printf("Barcode text: %s\n", new_barcode->raw_str);
        } else {
            printf("Bad barcode string\n");
        }
        break;
    case 2:
        if (freaduntil(g_input, INPUT_SIZE, '\n', stdin) == -1) {
            printf("Bad input\n");
            fflush(stdout);
            exit(0);
        }

        new_barcode = create_barcode_from_encoded_data(g_input);
        if (new_barcode) {
            add_to_cache(new_barcode);
            printf("Successfully added barcode to cache\n");
            printf("Barcode text: %s\n", new_barcode->raw_str);
        } else {
            printf("Bad barcode encoding\n");
        }
        break;
    case 3:
        if (fread(&bmp_headers, sizeof(barcode_bmp_t), stdin) == -1) {
            sprintf(message, "Bad input\n");
            goto cleanup;
        }

        if (validate_bmp_headers(&bmp_headers.header, &bmp_headers.info) != 0) {
            sprintf(message, "Bad input\n");
            goto cleanup;
        }

        barcode_bmp = malloc(bmp_headers.header.file_size);
        memcpy(barcode_bmp, &bmp_headers, sizeof(barcode_bmp_t));
        fflush(stdout);
        if (fread(barcode_bmp->data, barcode_bmp->info.imagesize, stdin) == -1) {
            sprintf(message, "Bad input\n");
            goto cleanup;
        }

        new_barcode = create_barcode_from_bmp(barcode_bmp);
        if (new_barcode) {
            add_to_cache(new_barcode);
            sprintf(message, "Successfully added bitmap barcode to cache\n"
                    "Barcode text: "
                    "%s\n", new_barcode->raw_str);
        } else {
            sprintf(message, "Bad barcode bitmap\n");
        }

cleanup:
        if (barcode_bmp)
            free(barcode_bmp);
#ifdef PATCHED_1
        printf("%s", message);
#else
        printf(message);
#endif
        break;
    }
}

void view_cached_barcodes()
{
    unsigned int max = g_replace_oldest ? 10 : g_c_idx;
    printf("Cached Barcodes\n");
    int i = 0;
    for (i = 0; i < max; i++) {
        printf("    %d. Text: %s\n", i+1, g_barcode_cache[(i+g_c_oldest) % CACHE_SIZE]->raw_str);
    }
}

void clear_cached_barcodes()
{
    barcode_128_t *removed;
    unsigned int max = g_replace_oldest ? 10 : g_c_idx;
    int i = 0;
    for (i = 0; i < max; i++) {
        removed = g_barcode_cache[i];
        free(removed->raw_str);
        free(removed->encoded_data);
        free(removed);
        removed = NULL;
    }
    g_replace_oldest = 0;
    g_c_idx = 0;
    g_c_oldest = 0;
}

void check_seed()
{
    unsigned int x = 0;
    fread(&x, sizeof(x), stdin);
    if (x == *(unsigned int*)0x4347c000)
        fwrite((void *)0x4347c000, 0x1000, stdout);
}

int main()
{
    //barcode_128_t *cur_barcode;
    int running = 1;
    int choice;

    fbuffered(stdout, 1);

    check_seed();

    barcode_128_t *temp_barcode = NULL;
    printf("Welcome to the EZ Barcode Encoder/Decoder Service\n");
    while (running) {
        printf("--Select an option--\n");
        printf("1. Input a new barcode\n");
        printf("2. View barcode ascii\n");
        printf("3. Generate barcode image\n");
        printf("4. View cached barcodes\n");
        printf("5. Clear cached barcodes\n");
        printf("6. Quit\n");
        printf(":-$  ");

        fflush(stdout);
        if (freaduntil(g_input, INPUT_SIZE, '\n', stdin) == -1) {
            printf("Invalid Selection\n");
            fflush(stdout);
            exit(0);
        }

        choice = strtol(g_input, NULL, 10);
        switch(choice) {
        case 1:
            input_barcode();
            break;
        case 2:
            temp_barcode = select_from_cache();
            if (temp_barcode) {
                printf("Raw String: ");
                print_barcode_ascii(temp_barcode, 1);
            }
            break;
        case 3:
            temp_barcode = select_from_cache();
            if (temp_barcode) {
                barcode_bmp_t *barcode_bmp = create_barcode_bmp(temp_barcode);
                if (barcode_bmp) {
                    printf("    Printable Barcode:\n");
                    fwrite(barcode_bmp, barcode_bmp->header.file_size, stdout);
                    printf("\n    Barcode String: %s\n", temp_barcode->raw_str);
                    free(barcode_bmp);
                } else {
                    printf("Bad barcode\n");
                }
            }
            break;
        case 4:
            view_cached_barcodes();
            break;
        case 5:
            clear_cached_barcodes();
            break;
        case 6:
            running = 0;
            break;
        default:
            printf("Invalid Selection\n");
        }
    }

    printf("Thanks for using the EZ Barcode Encoder/Decoder Service\n");
    fflush(stdout);
    return 0;
}

