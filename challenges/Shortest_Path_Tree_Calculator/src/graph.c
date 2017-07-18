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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_graph.h"
#include "cgc_ll.h"
#include "cgc_io.h"

extern pNode cgc_Nodes;
extern pEdge cgc_Edges;

uint32_t cgc_NumNodes = 0;
uint32_t cgc_NumEdges = 0;

// find the node with the minimum distance
// not already in the SPT
pNode cgc_FindMinDistanceNode(void) {
	pNode n;
	pNode MinDistanceNode = NULL;
	uint32_t MinDistance = SIZE_MAX;

	n = cgc_Nodes;
	while (n) {
		if (n->Distance < MinDistance && !(n->InSPT)) {
			MinDistance = n->Distance;
			MinDistanceNode = n;
		}
		n = n->Next;
	}

	return(MinDistanceNode);
}

//uint32_t *FindSpt(uint32_t StartingNodeName, uint32_t EndingNodeName, uint32_t *NodeCount) {
uint32_t *cgc_FindSpt(uint32_t StartingNodeName, uint32_t EndingNodeName, uint8_t *NodeCount) {
	pNode StartingNode;
	pNode EndingNode;
	int32_t i;
	pNode MinDistanceNode;
	pNode n;
	pEdge e;
	pNode AdjacentNode;
	uint32_t *Response;

	if (cgc_Nodes == NULL || NodeCount == NULL) {
		return(NULL);
	}

	// Set all node distances to max and init the tracking variables
	n = cgc_Nodes;
	while (n) {
		n->Distance = SIZE_MAX;
		n->InSPT = 0;
		n->PrevSPT = NULL;
		n = n->Next;
	}

	// find the ending node
	if ((EndingNode = cgc_FindNode(EndingNodeName)) == NULL) {
		return(NULL);
	}
	
	// find the starting node and set its distance to 0
	if ((StartingNode = cgc_FindNode(StartingNodeName)) == NULL) {
		return(NULL);
	}
	StartingNode->Distance = 0;

	for (i = 0; i < cgc_NumNodes; i++) {
		// find the node with the minimum distance
		if ((MinDistanceNode = cgc_FindMinDistanceNode()) == NULL) {
			// unable to find the next node in the SPT
			// due to disconnected graph
			return(NULL);
		}

		// add it to the SPT
		MinDistanceNode->InSPT = 1;

		// see if we've found the end node
		if (MinDistanceNode == EndingNode) {
			// found the end
			break;
		}

		// find edges from this node to others
		e = cgc_Edges;
		while (e) {
			if (e->NodeA == MinDistanceNode) {
				// if the cost via this edge is lower, update it
				if (MinDistanceNode->Distance + e->Weight < e->NodeZ->Distance) {
					e->NodeZ->Distance = MinDistanceNode->Distance + e->Weight;
					e->NodeZ->PrevSPT = MinDistanceNode;
				}
			}
			if (e->NodeZ == MinDistanceNode) {
				// if the cost via this edge is lower, update it
				if (MinDistanceNode->Distance + e->Weight < e->NodeA->Distance) {
					e->NodeA->Distance = MinDistanceNode->Distance + e->Weight;
					e->NodeA->PrevSPT = MinDistanceNode;
				}
			}
			e = e->Next;
		}
	}

	// count how many nodes there are in the SPT
	*NodeCount = 1;
	n = EndingNode;
	while (n != StartingNode) {
		if (!(n->PrevSPT)) {
			return(NULL);
		}
		(*NodeCount)++;
		n = n->PrevSPT;
	}
	// allocate space for the uint32_t array
	if ((Response = (uint32_t *)cgc_calloc(sizeof(uint32_t)*(*NodeCount))) == NULL) {
		cgc__terminate(-1);
	}
	
	// starting at the end node, work our way back
	// along the SPT creating the response we'll send
	// back to the client
	n = EndingNode;
	i = *NodeCount;
	while (n != StartingNode) {
		Response[--i] = n->Name;

		if (!(n->PrevSPT)) {
			return(NULL);
		}

		n = n->PrevSPT;
	}
	Response[--i] = n->Name;

	// Free the graph data
	cgc_DestroyNodes();
	cgc_DestroyEdges();
	cgc_NumNodes = 0;
	cgc_NumEdges = 0;

	return(Response);
}
