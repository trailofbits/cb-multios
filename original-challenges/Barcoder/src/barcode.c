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
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "barcode.h"
#include "bitmap.h"
#include "codes.h"

//Overhead - Quiet Zone
//Overhead - Start Character
//Encoded Data
//Overhead - Check Character
//Overhead - Stop Character
//Overhead - Quiet Zone
#define BARCODE_OVERHEAD_LENGTH 5

barcode_128_lut_t g_barcode_lut[] = {
	{ ' ', "00", "|| ||  ||  ", 212222},
	{ '!', "01", "||  || ||  ", 222122},
	{ '"', "02", "||  ||  || ", 222221},
	{ '#', "03", "|  |  ||   ", 121223},
	{ '$', "04", "|  |   ||  ", 121322},
	{ '%', "05", "|   |  ||  ", 131222},
	{ '&', "06", "|  ||  |   ", 122213},
	{ '\'', "07", "|  ||   |  ", 122312},
	{ '(', "08", "|   ||  |  ", 132212},
	{ ')', "09", "||  |  |   ", 221213},
	{ '*', "10", "||  |   |  ", 221312},
	{ '+', "11", "||   |  |  ", 231212},
	{ ',', "12", "| ||  |||  ", 112232},
	{ '-', "13", "|  || |||  ", 122132},
	{ '.', "14", "|  ||  ||| ", 122231},
	{ '/', "15", "| |||  ||  ", 113222},
	{ '0', "16", "|  ||| ||  ", 123122},
	{ '1', "17", "|  |||  || ", 123221},
	{ '2', "18", "||  |||  | ", 223211},
	{ '3', "19", "||  | |||  ", 221132},
	{ '4', "20", "||  |  ||| ", 221231},
	{ '5', "21", "|| |||  |  ", 213212},
	{ '6', "22", "||  ||| |  ", 223112},
	{ '7', "23", "||| || ||| ", 312131},
	{ '8', "24", "||| |  ||  ", 311222},
	{ '9', "25", "|||  | ||  ", 321122},
	{ ':', "26", "|||  |  || ", 321221},
	{ ';', "27", "||| ||  |  ", 312212},
	{ '<', "28", "|||  || |  ", 322112},
	{ '=', "29", "|||  ||  | ", 322211},
	{ '>', "30", "|| || ||   ", 212123},
	{ '?', "31", "|| ||   || ", 212321},
	{ '@', "32", "||   || || ", 232121},
	{ 'A', "33", "| |   ||   ", 111323},
	{ 'B', "34", "|   | ||   ", 131123},
	{ 'C', "35", "|   |   || ", 131321},
	{ 'D', "36", "| ||   |   ", 112313},
	{ 'E', "37", "|   || |   ", 132113},
	{ 'F', "38", "|   ||   | ", 132311},
	{ 'G', "39", "|| |   |   ", 211313},
	{ 'H', "40", "||   | |   ", 231113},
	{ 'I', "41", "||   |   | ", 231311},
	{ 'J', "42", "| || |||   ", 112133},
	{ 'K', "43", "| ||   ||| ", 112331},
	{ 'L', "44", "|   || ||| ", 132131},
	{ 'M', "45", "| ||| ||   ", 113123},
	{ 'N', "46", "| |||   || ", 113321},
	{ 'O', "47", "|   ||| || ", 133121},
	{ 'P', "48", "||| ||| || ", 313121},
	{ 'Q', "49", "|| |   ||| ", 211331},
	{ 'R', "50", "||   | ||| ", 231131},
	{ 'S', "51", "|| ||| |   ", 213113},
	{ 'T', "52", "|| |||   | ", 213311},
	{ 'U', "53", "|| ||| ||| ", 213131},
	{ 'V', "54", "||| | ||   ", 311123},
	{ 'W', "55", "||| |   || ", 311321},
	{ 'X', "56", "|||   | || ", 331121},
	{ 'Y', "57", "||| || |   ", 312113},
	{ 'Z', "58", "||| ||   | ", 312311},
	{ '[', "59", "|||   || | ", 332111},
	{ '\\', "60", "||| |||| | ", 314111},
	{ ']', "61", "||  |    | ", 221411},
	{ '^', "62", "||||   | | ", 431111},
	{ '_', "63", "| |  ||    ", 111224},
	{ '`', "64", "| |    ||  ", 111422},
	{ 'a', "65", "|  | ||    ", 121124},
	{ 'b', "66", "|  |    || ", 121421},
	{ 'c', "67", "|    | ||  ", 141122},
	{ 'd', "68", "|    |  || ", 141221},
	{ 'e', "69", "| ||  |    ", 112214},
	{ 'f', "70", "| ||    |  ", 112412},
	{ 'g', "71", "|  || |    ", 122114},
	{ 'h', "72", "|  ||    | ", 122411},
	{ 'i', "73", "|    || |  ", 142112},
	{ 'j', "74", "|    ||  | ", 142211},
	{ 'k', "75", "||    |  | ", 241211},
	{ 'l', "76", "||  | |    ", 221114},
	{ 'm', "77", "|||| ||| | ", 413111},
	{ 'n', "78", "||    | |  ", 241112},
	{ 'o', "79", "|   |||| | ", 134111},
	{ 'p', "80", "| |  ||||  ", 111242},
	{ 'q', "81", "|  | ||||  ", 121142},
	{ 'r', "82", "|  |  |||| ", 121241},
	{ 's', "83", "| ||||  |  ", 114212},
	{ 't', "84", "|  |||| |  ", 124112},
	{ 'u', "85", "|  ||||  | ", 124211},
	{ 'v', "86", "|||| |  |  ", 411212},
	{ 'w', "87", "||||  | |  ", 421112},
	{ 'x', "88", "||||  |  | ", 421211},
	{ 'y', "89", "|| || |||| ", 212141},
	{ 'z', "90", "|| |||| || ", 214121},
	{ '{', "91", "|||| || || ", 412121},
	{ '|', "92", "| | ||||   ", 111143},
	{ '}', "93", "| |   |||| ", 111341},
	{ '~', "94", "|   | |||| ", 131141},
	{ 127, "95", "| |||| |   ", 114113},
	{ 128, "96", "| ||||   | ", 114311},
	{ 129, "97", "|||| | |   ", 411113},
	{ 130, "98", "|||| |   | ", 411311},
	{ 131, "99", "| ||| |||| ", 113141},
	{ '\t', "M1", "| |||| ||| ", 114131},
	{ '\xC0', "M2", "||| | |||| ", 311141},
	{ '\x00', "M3", "|||| | ||| ", 411131},
	{ '\x00', "SA", "|| |    |  ", 211412},
	{ '\x00', "SB", "|| |  |    ", 211214},
	{ '\x00', "SC", "|| |  |||  ", 211232},
	{ '\x00', "SP", "||   ||| | ||", 2331112},
	{ '\x00', "QT", "           ", 0xB},
};

barcode_128_lut_t *g_blut_startb = &g_barcode_lut[104];
barcode_128_lut_t *g_blut_startc = &g_barcode_lut[105];
barcode_128_lut_t *g_blut_stop = &g_barcode_lut[106];
barcode_128_lut_t *g_blut_quiet = &g_barcode_lut[107];

barcode_128_lut_t *find_entry_by_bin_rep(char *bin_rep)
{
    int i = 0;
    for (i = 0; i < (sizeof(g_barcode_lut) / sizeof(barcode_128_lut_t)); i++) {
        if (strcmp((const char *)g_barcode_lut[i].binary_rep, bin_rep) == 0)
            return &g_barcode_lut[i];
    }
    return NULL;
}

barcode_128_t *create_barcode_from_str(char *barcode_str)
{
    if (!barcode_str || !strlen(barcode_str) || strlen(barcode_str) > MAX_BARCODE_LENGTH)
        return NULL;

    barcode_128_t *new_barcode = malloc(sizeof(barcode_128_t));

    int i = 0;
    int is_type_c = 1;
    char *type_c_str = NULL;
    char digits[3] = { '\0', '\0', '\0' };
    for (i = 0; i < strlen(barcode_str); i++) {
        if (!isdigit(barcode_str[i])) {
            is_type_c = 0;
        }
        if ((barcode_str[i] < ' ' || barcode_str[i] > '~') && barcode_str[i] != '\t' && barcode_str[i] != '\xC0') {
            free(new_barcode);
            return NULL;
        }
    }
    printf("but the q isdid i make it here?\n");

    int idx = 0;
    if (is_type_c) {
        int type_c_idx = 0;
        new_barcode->encoding_type = TYPE_C;
        if (strlen(barcode_str) % 2 != 0) {
            type_c_str = malloc(strlen(barcode_str) + 2);
            type_c_str[0] = '0';
            memcpy(&type_c_str[1], barcode_str, strlen(barcode_str) + 1);
            barcode_str = type_c_str;
            new_barcode->raw_str = type_c_str;
        } else {
            new_barcode->raw_str = strdup(barcode_str);
        }

        new_barcode->checksum = 105;
        new_barcode->length = (BARCODE_OVERHEAD_LENGTH + strlen(barcode_str)/2);
        new_barcode->encoded_data = malloc(sizeof(barcode_128_lut_t *) * new_barcode->length);
        new_barcode->encoded_data[idx++] = g_blut_quiet;
        new_barcode->encoded_data[idx++] = g_blut_startc;
        for (i = 0; i < strlen(barcode_str); i+=2) {
            digits[0] = barcode_str[i];
            digits[1] = barcode_str[i+1];
            type_c_idx = strtoul(digits, NULL, 10);
            if (type_c_idx >= 100)
                type_c_idx = 0;

            new_barcode->encoded_data[idx++] = &g_barcode_lut[type_c_idx];
            new_barcode->checksum += type_c_idx * ((i+2)/2);
        }
    } else {
        int type_b_idx = 0;
        new_barcode->encoding_type = TYPE_B;
        new_barcode->raw_str = strdup(barcode_str);

        new_barcode->checksum = 104;
        new_barcode->length = (BARCODE_OVERHEAD_LENGTH + strlen(barcode_str));
        new_barcode->encoded_data = malloc(sizeof(barcode_128_lut_t *) * new_barcode->length);
        new_barcode->encoded_data[idx++] = g_blut_quiet;
        new_barcode->encoded_data[idx++] = g_blut_startb;
        for (i = 0; i < strlen(barcode_str); i++) {
            if (barcode_str[i] == '\t')
                type_b_idx = 100;
            else if (barcode_str[i] == '\xC0')
                type_b_idx = 101;
            else
                type_b_idx = barcode_str[i] - 32;

            new_barcode->encoded_data[idx++] = &g_barcode_lut[type_b_idx];
            new_barcode->checksum += type_b_idx * (i+1);
        }
    }

    new_barcode->checksum %= 103;
    new_barcode->encoded_data[idx++] = &g_barcode_lut[new_barcode->checksum];
    new_barcode->encoded_data[idx++] = g_blut_stop;
    new_barcode->encoded_data[idx++] = g_blut_quiet;

    if (idx != new_barcode->length) {
        printf("Bad barcode processing\n");
        new_barcode->length = idx;
    }

    return new_barcode;
}

char * find_stop_code(char *encoded_data)
{
    char *stop = (char *)g_blut_stop->binary_rep;

    int i = strlen(stop) - 1;
    int j = strlen(encoded_data) - 1;

    while(j >= 0 && encoded_data[j] == ' ')
        j--;

    while (i >= 0 && j >= 0) {
        if(stop[i--] != encoded_data[j--])
            return NULL;
    }

    return &encoded_data[j+1];
}

barcode_128_t *create_barcode_from_encoded_data(char *encoded_data)
{
    char *barcode_end = find_stop_code(encoded_data);
    if (!barcode_end)
        return NULL;

    int checksum_idx = barcode_end - encoded_data - 11;
    int i = 0;
    while (encoded_data[i] && encoded_data[i] != '|')
        i++;

    if (i >= checksum_idx || !encoded_data[i])
        return NULL;

    char find_encode[12];
    int str_idx = 0;
    int idx = 0;
    barcode_128_lut_t *entry = NULL;
    barcode_128_t *new_barcode = malloc(sizeof(barcode_128_t));
    new_barcode->checksum = 0;
    new_barcode->length = (BARCODE_OVERHEAD_LENGTH - 1 + ((checksum_idx - i) / 11));
    new_barcode->encoded_data = malloc(sizeof(barcode_128_lut_t *) * new_barcode->length);
    new_barcode->encoded_data[idx++] = g_blut_quiet;
    new_barcode->encoding_type = 0;

    find_encode[11] = '\0';
    memcpy(find_encode, &encoded_data[i], 11);
    entry = find_entry_by_bin_rep(find_encode);
    if (!entry)
        goto error;

    new_barcode->encoded_data[idx++] = entry;
    if (entry == g_blut_startb){
        new_barcode->encoding_type = TYPE_B;
        new_barcode->checksum += 104;
    }
    else if (entry == g_blut_startc){
        new_barcode->encoding_type = TYPE_C;
        new_barcode->checksum += 105;
    } else {
        goto error;
    }

    i += 11;
    while (i < checksum_idx) {
        memcpy(find_encode, &encoded_data[i], 11);
        entry = find_entry_by_bin_rep(find_encode);
        if (!entry)
            goto error;

        new_barcode->encoded_data[idx++] = entry;
        if (entry->code_b == '\t')
            new_barcode->checksum = new_barcode->checksum + (100 * ++str_idx);
        else if (entry->code_b == (unsigned char)'\xC0')
            new_barcode->checksum = new_barcode->checksum + (101 * ++str_idx);
        else
            new_barcode->checksum = new_barcode->checksum + ((entry->code_b - 32) * ++str_idx);
        i += 11;
    }

    find_encode[11] = '\0';
    memcpy(find_encode, &encoded_data[i], 11);
    entry = find_entry_by_bin_rep(find_encode);
    new_barcode->checksum %= 103;
    if (!entry || entry != &g_barcode_lut[new_barcode->checksum])
        goto error;

    new_barcode->encoded_data[idx++] = entry;
    new_barcode->encoded_data[idx++] = g_blut_stop;
    new_barcode->encoded_data[idx++] = g_blut_quiet;

    if (idx != new_barcode->length) {
        printf("Bad barcode processing\n");
        new_barcode->length = idx;
    }

    int str_size = 0;
    if (new_barcode->encoding_type == TYPE_B) {
        str_size = new_barcode->length - 5 + 1;
    } else if (new_barcode->encoding_type == TYPE_C) {
        str_size = ((new_barcode->length - 5) * 2) + 1;
    }
    new_barcode->raw_str = malloc(str_size);
    new_barcode->raw_str[str_size - 1] = '\0';
    for (i = 2; i < new_barcode->length-3; i++) {
        if (new_barcode->encoding_type == TYPE_B) {
            new_barcode->raw_str[i-2] = new_barcode->encoded_data[i]->code_b;
        }
        if (new_barcode->encoding_type == TYPE_C) {
            new_barcode->raw_str[(i-2) * 2] = new_barcode->encoded_data[i]->code_c[0];
            new_barcode->raw_str[((i-2) * 2)+ 1] = new_barcode->encoded_data[i]->code_c[1];
        }
    }

    return new_barcode;
error:
    free(new_barcode->encoded_data);
    free(new_barcode);
    return NULL;
}

char *create_barcode_ascii(barcode_128_t *barcode)
{
    int i = 0;
    int str_len = ((barcode->length - 1) * 11) + 14;
    char *barcode_enc_str = calloc(1, str_len);
    char *dst = barcode_enc_str;
    for (i = 0; i < barcode->length; i++) {
        char *p = (char *)barcode->encoded_data[i]->binary_rep;
        while (*p)
            *dst++ = *p++;
    }
    return barcode_enc_str;
}
void print_barcode_ascii(barcode_128_t *barcode, int include_str)
{
    int i = 0;
    if (include_str) {
        for (i = 2; i < barcode->length-3; i++) {
            if (barcode->encoding_type == TYPE_B) {
                printf("%c", barcode->encoded_data[i]->code_b);
            }
            if (barcode->encoding_type == TYPE_C) {
                printf("%s", barcode->encoded_data[i]->code_c);
            }
        }
        printf("\n");
    }

    for (i = 1; i < barcode->length-1; i++) {
        printf("%s", barcode->encoded_data[i]->binary_rep);
    }
    printf("\n");
}

