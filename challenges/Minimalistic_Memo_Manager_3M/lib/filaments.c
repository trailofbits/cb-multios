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
#ifdef FILAMENTS

#undef FILAMENTS
#include "cgc_wrapper.h"
#define FILAMENTS

#include "libcgc.h"


#include "cgc_filaments.h"
#include "cgc_string.h"

static unsigned int g_next_id = 1;
static fib_t *g_fib;
static fib_t *g_active_fibs;

void cgc_filaments_init()
{
    fib_t *fib;
    if (cgc_allocate(0x1000, 0, (void **)&fib) != 0) cgc__terminate(-1);

    fib->id = 0;
    fib->stack = 0;
    fib->next = NULL;
    g_fib = fib;
    g_active_fibs = fib;
}

void cgc_filaments_switch(fib_t *new_fib)
{
    if (new_fib == g_fib)
        return;

    if (cgc_setjmp(g_fib->env) == 0)
    {
        // switch to new_fib
        g_fib = new_fib;
        cgc_longjmp(g_fib->env, 1);
    }
    else
    {
        // just regained control
        return;
    }
}

void cgc_filaments_yield()
{
    fib_t *next = g_fib->next;
    if (next == NULL)
        next = g_active_fibs;

    cgc_filaments_switch(next);
}

void cgc___filaments_new()
{
    g_fib->start_func(g_fib->userdata);

    // TODO destroy the filament
    while (1)
        cgc_filaments_yield();
}

void cgc_filaments_new(start_func_t func, void *userdata)
{
    fib_t *fib;
    if (cgc_allocate(0x1000, 0, (void **)&fib) != 0) cgc__terminate(-1);

    fib->id = g_next_id++;
    if (cgc_allocate(0x8000, 0, &fib->stack) != 0) cgc__terminate(-1);

    fib->start_func = func;
    fib->userdata = userdata;
    cgc_memset(fib->env, 0, sizeof(fib->env));
    fib->env->_b[0] = (long)cgc___filaments_new;
    fib->env->_b[2] = (long)fib->stack + 0x7ffc;

    fib->next = g_active_fibs;
    g_active_fibs = fib;
}

fib_t *cgc_filaments_current()
{
    return g_fib;
}

int cgc___filaments_transmit(int fd, const void *buf, cgc_size_t count, cgc_size_t *tx_bytes)
{
    cgc_filaments_yield();
    int retval = cgc_transmit(fd, buf, count, tx_bytes);
    return retval;
}

int cgc___filaments_receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes)
{
    while (1)
    {
        struct cgc_timeval tv;
        cgc_fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        if (cgc_fdwait(fd + 1, &rfds, NULL, &tv, NULL) != 0)
            break;

        if (FD_ISSET(fd, &rfds))
            break;

        cgc_filaments_yield();
    }

    int retval = cgc_receive(fd, buf, count, rx_bytes);
    return retval;
}

int cgc___filaments_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
	   const struct cgc_timeval *timeout, int *readyfds)
{
    cgc_filaments_yield();
    int retval = cgc_fdwait(nfds, readfds, writefds, timeout, readyfds);
    return retval;
}

int cgc___filaments_allocate(cgc_size_t length, int is_X, void **addr)
{
    cgc_filaments_yield();
    int retval = cgc_allocate(length, is_X, addr);
    return retval;
}

int cgc___filaments_deallocate(void *addr, cgc_size_t length)
{
    cgc_filaments_yield();
    int retval = cgc_deallocate(addr, length);
    return retval;
}

int cgc___filaments_random(void *buf, cgc_size_t count, cgc_size_t *rnd_bytes)
{
    cgc_filaments_yield();
    int retval = cgc_random(buf, count, rnd_bytes);
    return retval;
}

#endif
