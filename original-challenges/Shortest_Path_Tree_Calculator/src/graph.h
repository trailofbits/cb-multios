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
#ifndef GRAPH_H
#define GRAPH_H
#include <libcgc.h>
#include <stdint.h>

#define MAX_NODES (255)
typedef struct _node {
	uint32_t InSPT;
	struct _node *PrevSPT;
	struct _node *Next;
	uint32_t Name;
	uint32_t Distance;
} Node, *pNode;

#define MAX_EDGES (2000)
typedef struct _edge {
	struct _edge *Next;
	struct _edge *Prev;
	pNode NodeA;
	pNode NodeZ;
	uint32_t Weight;
} Edge, *pEdge;

//uint32_t *FindSpt(uint32_t StartingNodeName, uint32_t EndingNodeName, uint32_t *NodeCount);
uint32_t *FindSpt(uint32_t StartingNodeName, uint32_t EndingNodeName, uint8_t *NodeCount);


#endif // #ifndef GRAPH_H
