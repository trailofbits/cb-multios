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
#include "cgc_graph.h"
#include "cgc_malloc.h"
#include "cgc_io.h"

extern pNode cgc_Nodes;
extern pEdge cgc_Edges;
extern uint32_t cgc_NumNodes;
extern uint32_t cgc_NumEdges;

// add a node to a list
pNode cgc_AddNode(pNode Element) {

	if (!Element) {
		return(NULL);
	}

	if (!cgc_Nodes) {
		cgc_Nodes = Element;
		Element->Next = NULL;
		cgc_NumNodes++;
		return(Element);
	}
	
	Element->Next = cgc_Nodes;
	cgc_Nodes = Element;
	cgc_NumNodes++;

	return(Element);

}

// add an edge to a list
pEdge cgc_AddEdge(pEdge Element) {

	if (!Element) {
		return(NULL);
	}
	
	if (!cgc_Edges) {
		cgc_Edges = Element;
		cgc_NumEdges++;
		return(Element);
	}

	Element->Next = cgc_Edges;
	cgc_Edges = Element;
	cgc_NumEdges++;

	return(Element);

}

// remove a node from a list by pointer
pNode cgc_RemoveNode(pNode Element) {
	pNode n;
	pNode prev;

	if (!cgc_Nodes || !Element) {
		return(NULL);
	}

	if (Element == cgc_Nodes) {
		cgc_Nodes = Element->Next;
		Element->Next = NULL;
		return(cgc_Nodes);
	}

	prev = cgc_Nodes;
	n = cgc_Nodes->Next;
	while (n) {
		if (n == Element) {
			prev->Next = n->Next;
			Element->Next = NULL;
			return(cgc_Nodes);
		}
		n = n->Next;
	}

	return(NULL);
	
}

// remove an edge from a list by pointer
pEdge cgc_RemoveEdge(pEdge Element) {
	pEdge e;
	pEdge prev;

	if (!cgc_Edges || !Element) {
		return(NULL);
	}

	if (Element == cgc_Edges) {
		cgc_Edges = Element->Next;
		Element->Next = NULL;
		return(cgc_Edges);
	}

	prev = cgc_Edges;
	e = cgc_Edges->Next;
	while (e) {
		if (e == Element) {
			prev->Next = e->Next;
			Element->Next = NULL;
			return(cgc_Edges);
		}
		e = e->Next;
	}

	return(NULL);
	
}

// find a node in a list by its Name
pNode cgc_FindNode(uint32_t TargetName) {
	pNode Curr = cgc_Nodes;

	if (!cgc_Nodes) {
		return(NULL);
	}

	while (Curr) {
		if (Curr->Name == TargetName) {
			return(Curr);
		}
		Curr = Curr->Next;
	}

	return(NULL);

}

// find an edge in a list by its starting and ending node
pEdge cgc_FindEdge(pNode NodeA, pNode NodeZ) {
	pEdge Curr = cgc_Edges;

	if (!cgc_Edges) {
		return(NULL);
	}

	while (Curr) {
		if ((Curr->NodeA == NodeA) && (Curr->NodeZ == NodeZ)) {
			return(Curr);
		}
		if ((Curr->NodeA == NodeZ) && (Curr->NodeZ == NodeA)) {
			return(Curr);
		}
		Curr = Curr->Next;
	}

	return(NULL);

}

// Destroy a nodes list
uint8_t cgc_DestroyNodes(void) {
	pNode Curr = cgc_Nodes;
	pNode Next;

	if (!cgc_Nodes) {
		return(0);
	}

	while (Curr) {
		Next = Curr->Next;
		cgc_free(Curr);
		Curr = Next;
	}

	cgc_Nodes = NULL;

	return(1);
}

// Destroy a edges list
uint8_t cgc_DestroyEdges(void) {
	pEdge Curr = cgc_Edges;
	pEdge Next;

	if (!cgc_Edges) {
		return(0);
	}

	while (Curr) {
		Next = Curr->Next;
		cgc_free(Curr);
		Curr = Next;
	}

	cgc_Edges = NULL;

	return(1);
}
