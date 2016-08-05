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

#ifndef CHAL_H
#define CHAL_H

typedef enum {
    CAT_CRYPTO,
    CAT_PWNABLE,
    CAT_FORENSICS,
    CAT_WEB,
    CAT_NETWORK,
    CAT_REVERSING,
    CAT_MISC,
} category_t;

typedef enum {
    CSTAT_LOCKED,
    CSTAT_SOLVED,
    CSTAT_SOLVED_U,
    CSTAT_OPEN,
} chal_stat_t;

typedef struct {
    char name[128];
    char desc[256];
    unsigned int points;
    chal_stat_t status;
    category_t cat;
    char *flag;
} chal_t;

const char* chal_cat_to_string(category_t cat);
const char* chal_status_to_string(chal_stat_t stat);

#endif
