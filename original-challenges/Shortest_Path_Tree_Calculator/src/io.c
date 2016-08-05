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
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "malloc.h"
#include "io.h"
#include "ll.h"
#include "graph.h"
#include "string.h"

extern uint32_t NumNodes;
extern uint32_t NumEdges;
const unsigned char *rand_page = (const unsigned char *)0x4347C000;

uint32_t ReadBytes(unsigned char *Buf, uint32_t TargetLen) {
	size_t rxbytes;
	uint32_t TotalLen = 0;

	while ((TotalLen < TargetLen) && (receive(STDIN, Buf+TotalLen, TargetLen-TotalLen, &rxbytes) == 0)) {
		if (rxbytes == 0) {
			return(0);
		}
		TotalLen += rxbytes;
	}
	if (TotalLen != TargetLen) {
		return(0);
	}

	return(TotalLen);
}

uint32_t ReadNull(uint32_t TargetLen) {
	size_t rxbytes;
	uint32_t TotalLen = 0;
	unsigned char *Buf;

	if (TargetLen == 0) {
		return(0);
	}

	if ((Buf = (unsigned char *)calloc(TargetLen)) == NULL) {
		_terminate(0);
	}

	while ((TotalLen < TargetLen) && (receive(STDIN, Buf+TotalLen, TargetLen-TotalLen, &rxbytes) == 0)) {
		if (rxbytes == 0) {
			free(Buf);
			return(0);
		}
		TotalLen += rxbytes;
	}
	if (TotalLen != TargetLen) {
		free(Buf);
		return(0);
	}

	free(Buf);
	return(TotalLen);
}

uint32_t SendBytes(unsigned char *Buf, uint32_t Len) {
	size_t txbytes;
	uint32_t TotalLen = 0;

	while (((transmit(STDOUT, Buf+TotalLen, Len-TotalLen, &txbytes)) == 0) && TotalLen < Len) {
		if (txbytes == 0) {
			return(0);
		}
		TotalLen += txbytes;
	}
	if (TotalLen != Len) {
		return(0);
	}

	return(TotalLen);
}

uint8_t SendResponse(uint8_t Code, uint8_t NumElements, uint32_t *Elements) {
	Response r;

	r.Code = Code;
	r.NumElements = NumElements;
	if (SendBytes((unsigned char *)&r, sizeof(Response)) != sizeof(Response)) {
		return(0);
	}
	
	// send the elements
	if (NumElements > 0) {
		if (SendBytes((unsigned char *)Elements, NumElements*sizeof(uint32_t))) {
			return(0);
		}
	}

	return(1);
}

uint8_t SendErrorResponse(uint8_t Code) {
	Response r;

	return(SendResponse(Code, 0, NULL));
}


// Read a command from the CRS
uint8_t ReadCmd(void) {
	Command Cmd;
	uint32_t *NewNodeNames;
	pEdgeArray NewEdges;
	uint32_t i;
	pNode NewNode;
	pEdge NewEdge;
	pEdge ExistingEdge;
	uint8_t NodeCount;
	uint32_t *SPT;

	// read in the basic command header
	if (ReadBytes((unsigned char *)&Cmd, sizeof(Command)) != sizeof(Command)) {
		return(0);
	}

	if (Cmd.Action == CMD_SEND_NODES) {
		// read in the indicated number of Nodes
#ifdef PATCHED_1
		if ((Cmd.NumElements + NumNodes) > MAX_NODES) {
#else
		if (Cmd.NumElements > MAX_NODES) {
#endif
			ReadNull(sizeof(uint32_t)*Cmd.NumElements);
			SendErrorResponse(RESP_ERROR_TOO_MANY_NODES);
			return(0);
		}
		if ((NewNodeNames = (uint32_t *)calloc(sizeof(uint32_t)*Cmd.NumElements)) == NULL) {
			DestroyNodes();
			DestroyEdges();
			_terminate(1);
		}
		if (ReadBytes((unsigned char *)NewNodeNames, sizeof(uint32_t)*Cmd.NumElements) != sizeof(uint32_t)*Cmd.NumElements) {
			free(NewNodeNames);
			return(0);
		}

		// make sure none of the new node names exist already
		for (i = 0; i < Cmd.NumElements; i++) {
			if (FindNode(NewNodeNames[i]) != NULL) {
				free(NewNodeNames);
				SendErrorResponse(RESP_ERROR_DUPLICATE_NODE);
				return(0);
			}
		}

		// Create the new nodes 
		for (i = 0; i < Cmd.NumElements; i++) {
			// create a new node
			if ((NewNode = (pNode)calloc(sizeof(Node))) == NULL) {
				free(NewNodeNames);
				DestroyNodes();
				DestroyEdges();
				_terminate(1);
			}
			NewNode->Name = NewNodeNames[i];
			NewNode->Distance = SIZE_MAX;
			// Add it to the graph
			if (!AddNode(NewNode)) {
				free(NewNodeNames);
				DestroyNodes();
				DestroyEdges();
				_terminate(1);
			}
		}

		// done creating new nodes
		free(NewNodeNames);

	} else if (Cmd.Action == CMD_SEND_EDGES) {
		// read in the indicated number of Edges
		if ((Cmd.NumElements + NumEdges) > MAX_EDGES) {
			ReadNull(sizeof(EdgeArray)*Cmd.NumElements);
			SendErrorResponse(RESP_ERROR_TOO_MANY_EDGES);
			return(0);
		}
		if ((NewEdges = (pEdgeArray)calloc(sizeof(EdgeArray)*Cmd.NumElements)) == NULL) {
			DestroyNodes();
			DestroyEdges();
			_terminate(1);
		}
		if (ReadBytes((unsigned char *)NewEdges, sizeof(EdgeArray)*Cmd.NumElements) != sizeof(EdgeArray)*Cmd.NumElements) {
			free(NewEdges);
			return(0);
		}
		
		// Create the new edges 
		for (i = 0; i < Cmd.NumElements; i++) {
			// create a new Edge
			if ((NewEdge = (pEdge)calloc(sizeof(Edge))) == NULL) {
				free(NewEdges);
				DestroyNodes();
				DestroyEdges();
				_terminate(1);
			}
			// make sure the starting and ending nodes exist
			if ((NewEdge->NodeA = FindNode(NewEdges[i].NodeA)) == NULL) {
				SendErrorResponse(RESP_ERROR_INVALID_NODE);
				free(NewEdge);
				free(NewEdges);
				DestroyNodes();
				DestroyEdges();
				_terminate(1);
			}
			if ((NewEdge->NodeZ = FindNode(NewEdges[i].NodeZ)) == NULL) {
				SendErrorResponse(RESP_ERROR_INVALID_NODE);
				free(NewEdge);
				free(NewEdges);
				DestroyNodes();
				DestroyEdges();
				_terminate(1);
			}
			// offset the weight by a fixed magic_page-based value
			NewEdge->Weight = NewEdges[i].Weight + rand_page[NumNodes];

			// see if one already exists
			if ((ExistingEdge = FindEdge(NewEdge->NodeA, NewEdge->NodeZ)) != NULL) {
				if (ExistingEdge->Weight > NewEdge->Weight) {
					ExistingEdge->Weight = NewEdge->Weight;
				}

				// keep the existing edge
				free(NewEdge);
				continue;
			}

			// Add it to the graph
			if (!AddEdge(NewEdge)) {
				free(NewEdge);
				free(NewEdges);
				DestroyNodes();
				DestroyEdges();
				_terminate(1);
			}
		}

	} else if (Cmd.Action == CMD_RUN_SPT) {
		if ((SPT = FindSpt(Cmd.StartingNode, Cmd.EndingNode, &NodeCount)) == NULL) {
			// unable to find SPT
			SendErrorResponse(RESP_ERROR_SPT_FAIL);
			return(0);
		}
		SendResponse(RESP_NODE_SET, NodeCount, SPT);
		free(SPT);

	} else {
		SendErrorResponse(RESP_ERROR_INVALID_CMD);
		return(0);
	}

	return(1);
}
