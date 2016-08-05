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
#ifndef IO_H
#define IO_H
#include <libcgc.h>

// command 
#define CMD_SEND_NODES (1)
#define CMD_SEND_EDGES (2)
#define CMD_RUN_SPT (3)
typedef struct __attribute__((__packed__)) _command {
	uint8_t Action;
	uint32_t NumElements;
	uint32_t StartingNode;
	uint32_t EndingNode;
} Command, *pCommand;

#define RESP_ERROR_DUPLICATE_NODE (1)
#define RESP_ERROR_TOO_MANY_NODES (2)
#define RESP_ERROR_TOO_MANY_EDGES (3)
#define RESP_ERROR_INVALID_NODE (4)
#define RESP_ERROR_INVALID_CMD (5)
#define RESP_NODE_SET (6)
#define RESP_ERROR_SPT_FAIL (7)
typedef struct __attribute__((__packed__)) _response {
	uint8_t Code;
	uint8_t NumElements;
} Response, *pResponse;

typedef struct _edgearray {
	uint32_t NodeA;
	uint32_t NodeZ;
	uint32_t Weight;
} EdgeArray, *pEdgeArray;

uint8_t ReadCmd(void);

#endif // #ifndef IO_H
