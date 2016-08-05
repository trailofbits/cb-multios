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
#ifndef CGCRPC_H
#define CGCRPC_H


#define CGCRPC_SUCCESS          0
#define CGCRPC_FAILURE          -1

#define CGCRPC_ERROR_FORMAT     2
#define CGCRPC_ERROR_COMMAND    4
#define CGCRPC_ERROR_NOT_FOUND  8
#define CGCRPC_ERROR_VERSION    10

#define MAX_CGCRPC_CONNECTIONS  10
#define MAX_CGCRPC_ENDPOINTS    10

#define MAX_CGCRPC_RESPONSE_SIZE 2048

// CGCRPC Commands

/*  Generic Command Format
  uint16_t command
  ...command specific options

  Generic Response Format
  uint16_t command
  ...command specific options
*/
#define CGCRPC_BIND             0xa0
/*
  uint16_t nameLength
  uint8_t name[nameLength]
  uint16_t version
*/
#define CGCRPC_BIND_RESPONSE    0x0a
/*
  uint8_t responseCode
  uint32_t  bindID
*/
#define CGCRPC_WRITE_TO_PIPE    0xa1
/*
  uint32_t bindID 
  uint16_t opCode
  uint16_t requestLength
  uint8_t *requestData
*/
#define CGCRPC_WRITE_TO_PIPE_RESPONSE 0x1a
/*
  uint32_t bindID
  uint16_t responseLength
  uint8_t *responseBytes
*/

typedef struct CGCRPC_Endpoint_s {
  char      name[64];
  uint16_t  version;
  void      (*handler)(uint16_t, uint8_t *, uint32_t, uint8_t **, uint16_t *);
} CGCRPC_Endpoint;

typedef struct CGCRPC_Connection_s {
  uint32_t bindID;
  CGCRPC_Endpoint *endpoint;
} CGCRPC_Connection;

extern CGCRPC_Endpoint endpoints[MAX_CGCRPC_ENDPOINTS];
extern CGCRPC_Connection connections[MAX_CGCRPC_CONNECTIONS];

uint32_t HandleCGCRPCMessage(void *data, uint32_t dataLength, void **output, uint32_t *outputLength);
void InitializeCGCRPC();

#endif