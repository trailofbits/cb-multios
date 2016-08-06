/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 * 
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
#include <libcgc.h>

static struct {
    unsigned char i, j;
    unsigned char S[256];
} g_state;

unsigned char parcour_byte()
{
    int i = ++g_state.i;
    int j = g_state.j = g_state.j + g_state.S[i];
    unsigned char tmp = g_state.S[i];
    g_state.S[i] = g_state.S[j];
    g_state.S[j] = tmp;
    return g_state.S[(g_state.S[i] + g_state.S[j]) % 256];
}

void parcour_init(const char *key, size_t size)
{
    int i, j;
    for (i = 0; i < 256; i++)
        g_state.S[i] = i;
    for (i = 0, j = 0; i < 256; i++)
    {
        j = (256 + j - g_state.S[i] + key[i % size]) % 256;
        unsigned char tmp = g_state.S[i];
        g_state.S[i] = g_state.S[j];
        g_state.S[j] = tmp;
    }
    g_state.i = 0;
    g_state.j = 0;

    for (i = 0; i < 5000; i++)
        parcour_byte();
}

