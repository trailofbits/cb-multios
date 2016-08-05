/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include <libcgc.h>

typedef struct __attribute__((__packed__)) _L4Hdr {
	unsigned char Dst;
	unsigned char Src;
	uint8_t Len;
} L4Hdr, *pL4Hdr;

#define MAX_HANDLERS (16)
typedef struct _Handlers {
	uint8_t L4Addr;
	uint8_t (*Handler)(unsigned char *Data, uint8_t DataLen, unsigned char *Response, uint8_t *ResponseLen);
} Handlers, *pHandlers;

typedef struct _L4Connection {
	uint32_t PeerL3Addr;
	uint32_t LocalL3Addr;
	unsigned char PeerL4Addr;
	unsigned char LocalL4Addr;
	void *Handler;
} L4Connection, *pL4Connection;

uint8_t L4_RegisterHandler(uint8_t NewL4Addr, void *NewHandler);
