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
#ifndef FILAMENTS_H_
#define FILAMENTS_H_
#ifdef FILAMENTS

#include <wrapper.h>
#include <libcgc.h>

typedef void (*start_func_t) (void *userdata);

typedef struct fib {
    struct fib *next;
    unsigned int id;
    void *stack;
    jmp_buf env;
    start_func_t start_func;
    void *userdata;
} fib_t;

void filaments_init();
void filaments_new(start_func_t func, void *userdata);
void filaments_yield();
fib_t *filaments_current();
void filaments_switch(fib_t *new_fib);

#endif /* FILAMENTS */
#endif /* !FILAMENTS_H_ */
