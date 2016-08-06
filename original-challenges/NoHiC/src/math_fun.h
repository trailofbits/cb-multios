/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef MATH_FUN_H
#define MATH_FUN_H
#include "libc.h"

void do_int_mean(list_t * num_list);
void do_int_median(list_t * num_list);
void do_int_mode(list_t * num_list);
void do_int_range(list_t * num_list);
void do_int_sum(list_t * num_list);
void do_int_product(list_t * num_list);
void do_int_min(list_t * num_list);
void do_int_max(list_t * num_list);
void do_int_sort(list_t * num_list);
void do_int_rsort(list_t * num_list);
void do_int_odds(list_t * num_list);
void do_int_evens(list_t * num_list);

void do_dbl_mean(list_t * num_list);
void do_dbl_median(list_t * num_list);
void do_dbl_mode(list_t * num_list);
void do_dbl_range(list_t * num_list);
void do_dbl_sum(list_t * num_list);
void do_dbl_product(list_t * num_list);
void do_dbl_min(list_t * num_list);
void do_dbl_max(list_t * num_list);
void do_dbl_sort(list_t * num_list);
void do_dbl_rsort(list_t * num_list);
void do_dbl_odds(list_t * num_list);
void do_dbl_evens(list_t * num_list);

#endif