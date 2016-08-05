/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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
#ifndef SERVICE_H
#define SERVICE_H

#include <libcgc.h>
#include "linkedlist.h"
#include "stdint.h"

#define QUERY_ALL     0x01
#define QUERY_SERVER  0x02
#define QUERY_ONE     0x03
#define QUERY_ADMIN   0x04

#define RESPONSE      0x05

#define LIST_SERVER   0x01
#define LIST_INSTANCE 0x02

typedef struct query_s {
  uint8_t type;
  uint16_t length;
  uint8_t *data;
} query;

typedef struct response_s {
  uint16_t size;
  uint8_t *data;
} response;

typedef struct serverInfo_s {
  char *name;
  linkedList *instances;
} serverInfo;

typedef struct instanceInfo_s {
  char *name;
  serverInfo *server;
  int   port;
  int   adminPortOffset;
  int   isClustered;
  char  *versionString;
  char  *optionString;
} instanceInfo;

extern linkedList *serverList;

void InitializeSimulation();

query *DestroyQuery(query *pQuery);
query *ParseQuery(char *inputBuffer);

response *DestroyResponse(response *pResponse);
response *GenerateBlankResponse();
int AddToResponse(response *pResponse, char *pString);
int SendResponse(response *pResponse);
int DumpResponse(response *pResponse);

#endif