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
#ifndef CGCMB_H
#define CGCMB_H

#include "fs.h"

#define CGCMB_MAGIC 0xC47C4D42

// Message Types
#define CGCMB_NEGOTIATE                   0x01
#define CGCMB_NEGOTIATE_RESPONSE          0xf1
#define CGCMB_SESSION_SETUP               0x02
#define CGCMB_SESSION_SETUP_RESPONSE      0xf2
#define CGCMB_TREE_CONNECT                0x03
#define CGCMB_TREE_CONNECT_RESPONSE       0xf3
#define CGCMB_TREE_DISCONNECT             0x04
#define CGCMB_TREE_DISCONNECT_RESPONSE    0xf4
#define CGCMB_FILE_CREATE                 0x05
#define CGCMB_FILE_CREATE_RESPONSE        0xf5
#define CGCMB_FILE_CLOSE                  0x06
#define CGCMB_FILE_CLOSE_RESPONSE         0xf6
#define CGCMB_FILE_READ                   0x07
#define CGCMB_FILE_READ_RESPONSE          0xf7
#define CGCMB_FILE_WRITE                  0x08
#define CGCMB_FILE_WRITE_RESPONSE         0xf8
#define CGCMB_FILE_CANCEL                 0x09
#define CGCMB_FILE_CANCEL_RESPONSE        0xf9
#define CGCMB_TRANSACTION                 0x0a
#define CGCMB_TRANSACTION_RESPONSE        0xfa
#define CGCMB_ECHO                        0x0b
#define CGCMB_ECHO_RESPONSE               0xfb
#define CGCMB_END_SESSION                 0x0c
#define CGCMB_END_SESSION_RESPONSE        0xfc
#define CGCMB_ERROR_RESPONSE              0xff

// Error codes
#define CGCMB_ERROR_FORMAT        0xe1
#define CGCMB_ERROR_LENGTH        0xe2
#define CGCMB_ERROR_STATE         0xe3
#define CGCMB_ERROR_ACCESS        0xe4 
#define CGCMB_ERROR_SESSION       0xe5
#define CGCMB_ERROR_MSG           0xe6
#define CGCMB_ERROR_USER          0xe7
#define CGCMB_ERROR_FULL          0xe8
#define CGCMB_ERROR_NOT_FOUND     0xe9
#define CGCMB_ERROR_FILE          0xea
#define CGCMB_ERROR_TRANSACTION   0xeb


// Supported Dialects
#define CGCMB_DIALECT_1   0x313e
#define CGCMB_DIALECT_2   0x4155
#define CGCMB_DIALECT_3   0x2671

typedef enum {INITIAL, NEGOTIATE, SESSION, CLOSED} CGCMBServerStates_t;
typedef enum {CONNECTION_OPEN, CONNECTION_CLOSED} CGCMBConnectionStates_t;

#define MAX_CONNECTIONS 32
#define MAX_OPEN_FILES 16

#define MAX_READ_SIZE   2048
#define MAX_WRITE_SIZE  2048

typedef struct CGCMB_Connection_s {
  uint32_t connectionID;
  CGCMBConnectionStates_t state;
  fs_tree *openTree;
  fs_file *openFiles[MAX_OPEN_FILES];
} CGCMB_Connection;

typedef struct CGCMB_ServerState_s {
  CGCMBServerStates_t state;
  uint16_t dialect;
  uint32_t sessionKey;
  uint16_t userID;
  CGCMB_Connection *connections[MAX_CONNECTIONS];
} CGCMB_ServerState;

extern CGCMB_ServerState *mbServerState;

typedef struct CGCMB_Header_s {
  uint32_t protocol;
  uint8_t command;
  uint8_t status;
  uint8_t flags;
  uint8_t security[8];
} CGCMB_Header;

typedef struct CGCMB_Data_s {
  uint16_t count;
  uint8_t *data;
  uint16_t currentOffset;
} CGCMB_Data;

typedef struct CGCMB_Message_s {
  CGCMB_Header *header;
  CGCMB_Data *parameters;
  CGCMB_Data *data;
  void *parsed;
} CGCMB_Message;

typedef struct CGCMB_NEGOTIATE_s {
  uint32_t numDialects;
  uint16_t  *dialects;
} CGCMB_NEGOTIATE_Message;

typedef struct CGCMB_SESSION_SETUP_s {
  uint32_t sessionKey;
  uint32_t reserved;
  uint8_t *password;
  uint8_t *accountName;
} CGCMB_SESSION_SETUP_Message;

typedef struct CGCMB_TREE_CONNECT_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint8_t *password;
  uint8_t *path;
  uint8_t *service;
} CGCMB_TREE_CONNECT_Message;

typedef struct CGCMB_TREE_DISCONNECT_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint32_t connectionID;
} CGCMB_TREE_DISCONNECT_Message;

typedef struct CGCMB_FILE_CREATE_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint32_t connectionID;
  uint32_t mode;
  uint8_t *filename;
} CGCMB_FILE_CREATE_Message;

typedef struct CGCMB_FILE_CLOSE_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint32_t connectionID;
  uint16_t fileID;
} CGCMB_FILE_CLOSE_Message;

typedef struct CGCMB_FILE_READ_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint32_t connectionID;
  uint16_t fileID;
  uint16_t bytesToRead;
  uint32_t readOffset;
} CGCMB_FILE_READ_Message;

typedef struct CGCMB_FILE_WRITE_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint32_t connectionID;
  uint16_t fileID;
  uint8_t  mode;
  uint16_t bytesToWrite;
  uint32_t writeOffset;
  uint8_t *bytes;
} CGCMB_FILE_WRITE_Message;

typedef struct CGCMB_TRANSACTION_s {
  uint32_t sessionKey;
  uint16_t userID;
  uint32_t connectionID;
  uint16_t fileID;
} CGCMB_TRANSACTION_Message;

int ReceiveCGCMBMessage(TransportMessage *tpMessage, CGCMB_Message **pmbMessage);
void DestroyCGCMBMessage(CGCMB_Message **pmbMessage);
int ParseCGCMBMessage(CGCMB_Message *mbMessage);
int HandleCGCMBMessage(CGCMB_Message *mbMessage);
void TransmitCGCMBMessage(CGCMB_Message *mbMessage);
CGCMB_Message *CreateBlankCGCMBMessage();
int VerifyCGCMBMessage(CGCMB_Message *mbMessage);
int ReadFromData(uint8_t *dest, CGCMB_Data *source, uint32_t length);
void SendErrorResponse(uint32_t errorCode);
#endif