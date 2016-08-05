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
#include <cstdlib.h>

#define __hidden __attribute__((__visibility__("hidden")))
typedef struct
{
    void (*fn) (void *arg);
    void *arg;
} atexit_fn_t;
static atexit_fn_t atexit_handlers[256];
static int atexit_idx = 0;

extern "C"
{
    extern void (*__init_array_start[])(int, char **, char **) __hidden;
    extern void (*__init_array_end[])(int, char **, char **) __hidden;
    void *__dso_handle;
};

void ctors()
{
    size_t i;
    for (i = 0; i < __init_array_end - __init_array_start; i++)
    {
        void (*fn) (int, char **, char **) = __init_array_start[i];
        if (fn != NULL && (unsigned int)fn != 1)
            fn(0, NULL, NULL);
    }
}

extern "C" int __cxa_atexit(void (*func)(void *), void *arg, void *dso)
{
    if (atexit_idx == 256) return -1;

    atexit_fn_t *fn = &atexit_handlers[atexit_idx++];
    fn->fn = func;
    fn->arg = arg;
    return 0;
}

void dtors()
{
    size_t i;
    for (i = 0; i < atexit_idx; i++)
        atexit_handlers[i].fn(atexit_handlers[i].arg);
}

#ifdef CPLUSPLUS
#undef main

extern "C" int __attribute__((fastcall)) _main(int secret_page_i, char *unused[]);
extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    ctors();
    _main(secret_page_i, unused);
    dtors();
}

#endif
