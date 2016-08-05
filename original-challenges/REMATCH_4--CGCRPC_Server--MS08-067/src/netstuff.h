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
#ifndef NETSTUFF_H
#define NETSTUFF_H


#define NETSTUFF_PATH_CHAR  0xd0  // Used like a forward slash /
#define NETSTUFF_DIR_CHAR   0xd1  // Used like a dot .
#define NETSTUFF_SERVICE_CHAR 0xd2  // Used like double slash //
#define NETSTUFF_PATH_CHAR2 0xd3  // Used like back slash \



#define NETSTUFF_FILE_ENUM              0xb0  // List all files
#define NETSTUFF_PATH_ENUM              0xb1  // List all trees
#define NETSTUFF_SERVICE_ENUM           0xb2  // List all services
/*
  Request:
  Response:
    uint16_t numServices;
    uint8_t *services; // each null terminated
*/
#define NETSTUFF_FIND_TREE              0xb3  // Find which tree a file is in
#define NETSTUFF_FIND_FILE              0xb4  // Find a filename by FileID
#define NETSTUFF_FILE_STAT              0xb5  // Info on file
/*
  Request:
  uint8_t   *path;

  Response:
  uint16_t fileID;
  uint16_t numBytes;
  uint8_t isOpen;
  uint16_t errorCode;
*/
#define NETSTUFF_FILE_CLOSE             0xb6  // Force close a file/resource
#define NETSTUFF_SESSION_ENUM           0xb7   // Info on established sessions
#define NETSTUFF_SESSION_DEL            0xb8  // Force close a session
#define NETSTUFF_CONNECTION_ENUM        0xb9  // List all open connections
#define NETSTUFF_CONNECTION_DEL         0xba  // Force close a connection
#define NETSTUFF_NAME_CANONICALIZE      0xbb  // Convert filename to canonical format

#define NETSTUFF_NET_PATH_CANONICALIZE  0xbc  // Convert path name to canonical format
/*
  Request
  uint8_t  path[];

  Response:
  uint8_t path[] (canonicalized)
  uint16_t errorCode;
*/
  
#define NETSTUFF_PATH_COMPARE           0xbd  // comparison of paths
#define NETSTUFF_NAME_COMPARE           0xbe  // Implementation specific comparison of two names of certain type


#define NETSTUFF_SUCCESS          0xe0
#define NETSTUFF_ERROR_COMMAND    0xe1
#define NETSTUFF_ERROR_FORMAT     0xe2
#define NETSTUFF_ERROR_NOT_FOUND  0xe3
#define NETSTUFF_ERROR_PATH       0xe4
#define NETSTUFF_ERROR_PATH_TYPE  0xe5
#define NETSTUFF_ERROR_PATH_CANON 0xe6


typedef struct DataSet_s {
  uint8_t *data;
  uint16_t length;
  uint16_t offset;
} DataSet;

void AddData(DataSet *ds, uint8_t *newData, uint16_t length);
int ReadData(DataSet *ds, uint8_t *dest, uint16_t length);
uint8_t *BufCat(uint8_t *dest, uint8_t *src);
uint8_t *BufCpy(uint8_t *dest, uint8_t *source);
uint32_t BufCmp(uint8_t *s1, uint8_t *s2);
uint32_t Length(uint8_t *b);


void NETSTUFF_Handler(uint16_t opCode, uint8_t *data, uint32_t requestLength, uint8_t **endpointData, uint16_t *endpointDataLength);
uint8_t ServiceEnum(uint8_t *data, uint16_t length, DataSet *outputds);
uint8_t FileStat(uint8_t *data, uint16_t length, DataSet *outputds);
uint8_t NetPathCanonicalize(uint8_t *path, uint16_t length, DataSet *outputds);
uint8_t *FindChar(uint8_t *s, uint16_t length, uint8_t c);
uint8_t CanonicalizePathName(uint8_t *path, uint16_t length, uint8_t *output, uint16_t *outputLength);
uint8_t ConvertPathMacros(uint8_t *buffer);
uint8_t NetPathType(uint8_t *path, uint16_t length);
#endif


