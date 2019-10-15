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
#ifndef DEBUG_BRC_H_
#define DEBUG_BRC_H_

#define SERVER
//#define DEBUG

#define FOUT stderr

#ifdef DEBUG
#define _PRINTF(...) fprintf(FOUT, __VA_ARGS__)
#define PRINTF(...) \
    do { \
        fprintf(FOUT, "SERVER: "); \
        fprintf(FOUT, __VA_ARGS__); \
    } while(0)
#else
#define _PRINTF(...) \
    do { \
    } while(0)

#define PRINTF(...) \
    do { \
    } while(0)
#endif

void print_byte_array(const char *bytes, const unsigned short length);

#endif /*DEBUG_BRC_H_*/
