/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

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
#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <stdint.h>

#define MAX_COMMAND_LENGTH      (32)
#define MAX_USER_NAME           (8)
#define MAX_PASSWORD            (8)

#define CMD_FLAG_NOAUTH         (0)
#define CMD_FLAG_AUTH           (1)
#define CMD_FLAG_EXIT           (2)

#define USER_STATE_NOAUTH       (0)
#define USER_STATE_AUTH         (1)


typedef struct _USER_STATE_STRUCT
{
    uint32_t    state;
} tUserState;

// Command Function Pointer type
typedef int8_t (*fpCommandHandler)( uint8_t *pszCommandString, tUserState *pState );


typedef struct _COMMAND_HANDLER_TABLE
{
    uint8_t szCommand[MAX_COMMAND_LENGTH+1];
    fpCommandHandler pCmdHandler;
    uint8_t flags;
} tCommandHandlerTable;


// User handlers
void init_user( tUserState *pState );

// Parses a command string
int8_t parse_command( uint8_t *pszCommandLine, tUserState *pState );

// Command Handlers
int8_t command_insert( uint8_t *pszCommandString, tUserState *pState );
int8_t command_remove( uint8_t *pszCommandString, tUserState *pState );
int8_t command_update( uint8_t *pszCommandString, tUserState *pState );
int8_t command_print( uint8_t *pszCommandString, tUserState *pState );
int8_t command_find( uint8_t *pszCommandString, tUserState *pState );
int8_t command_login( uint8_t *pszCommandString, tUserState *pState );
int8_t command_logout( uint8_t *pszCommandString, tUserState *pState );
int8_t command_exit( uint8_t *pszCommandString, tUserState *pState );

#endif // __COMMAND_HANDLER_H__
