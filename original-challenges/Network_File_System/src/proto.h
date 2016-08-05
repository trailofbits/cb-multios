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
#ifndef SERVICE_H
#define SERVICE_H
#include <libcgc.h>

// Request
typedef struct _request {
	uint8_t Type;
	char *Username;
	char *Password;
	char *Filename;
	char *Filename2;
	uint8_t DataLen;
	char *Data;
	uint32_t Offset;
	uint8_t ReadWriteLength;
} Request, *pRequest;

// Responses
#define RESP_SUCCESS (0)
#define RESP_LOGIN_FAILED (1)
#define RESP_SYSTEM_FAILURE (2)
#define RESP_INVALID_FILE (3)
#define RESP_DELETE_FAILED (4)
#define RESP_RENAME_FAILED (5)

// packet formats
#define RESPONSE_HEADER_LEN (4)
typedef struct __attribute__((__packed__)) _response {
	uint8_t Type;
	uint8_t Code;
	uint16_t DataLen;
	char *Data;
} Response, *pResponse;

#define REQUEST_HEADER_LEN (1)
typedef struct _request_header {
	uint8_t Type;
} RequestHeader, *pRequestHeader;

// login type
#define CFS_LOGIN (0)
typedef struct _login_header {
	uint8_t UsernameLen;
	uint8_t PasswordLen;
	// char Username[UsernameLen];
	// char Password[UsernameLen];
} LoginHeader, *pLoginHeader;

// Request Directory Listing
#define CFS_DIR (1)

// Read from file
#define CFS_READ (2)
typedef struct __attribute__((__packed__)) _read_header {
	uint32_t Offset;	
	uint8_t Length;
	uint8_t FilenameLen;
	// char Filename[FilenameLen]
} ReadHeader, *pReadHeader;

// Write to file
#define CFS_WRITE (3)
#define CFS_WRITE_APPEND (4)
typedef struct __attribute__((__packed__)) _write_header {
	uint8_t Length;
	uint8_t FilenameLen;
	// char Filename[FilenameLen]
	// char Data[Length]
} WriteHeader, *pWriteHeader;

// Remove file
#define CFS_DEL (5)
typedef struct __attribute__((__packed__)) _del_header {
	uint8_t FilenameLen;
	// char Filename[FilenameLen]
} DelHeader, *pDelHeader;

// Rename file
#define CFS_RENAME (6)
typedef struct __attribute__((__packed__)) _rename_header {
	uint8_t OldFilenameLen;
	uint8_t NewFilenameLen;
	// char OldFilename[FilenameLen]
	// char newFilename[FilenameLen]
} RenameHeader, *pRenameHeader;

pRequest ReceiveRequest(void);
pResponse HandleRequest(pRequest pReq);
uint8_t SendResponse(pResponse pResp);
uint8_t FreeRequest(pRequest pReq);
uint8_t FreeResponse(pResponse pResp);

#endif
