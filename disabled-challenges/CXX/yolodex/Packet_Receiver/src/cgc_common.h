/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef __COMMON_H__
#define __COMMON_H__

extern "C" {
#include "cgc_stdlib.h"
#include "libcgc.h"
#include "cgc_stdint.h"
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

// Turn this on to aid in debugging
// #define DEBUG_MESSAGES      1

// Maximum number of bytes that will can be received
#define MAX_BYTES_RECEIVED      (64000)

// Size of the list for past fragments during reassembly of fragmented messages
#define MESSAGE_FRAGMENT_LIST_MAX  (64)

// Maximum possible message fragments
#define MAX_MESSAGE_FRAGMENTS   (16)

#include "cgc_datastream.h"
#include "cgc_messagepacket.h"
#include "cgc_doublelist.h"
#include "cgc_messagehandler.h"
#include "cgc_messagerenderer.h"


#endif // __COMMON_H___
