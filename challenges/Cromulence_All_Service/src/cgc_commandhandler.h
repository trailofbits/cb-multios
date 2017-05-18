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
#ifndef __COMMANDHANDLER_H__
#define __COMMANDHANDLER_H__

#define MAX_COMMAND_ENTRIES     (20)
#define MAX_COMMAND_LENGTH      (128)
#define MAX_DESCRIPTION_LENGTH  (512)

typedef void (*tCmdFunction)( char *pszArgString );

typedef struct COMMAND_TABLE_ENTRY
{
    char            szCommand[128];
    char            szDescription[512];
    tCmdFunction    pCmdFunc;
} tCommandTableEntry;

class CCommandHandler
{
public:
    CCommandHandler();
    ~CCommandHandler();

    bool RegisterCommand( const char *pszCommand, const char *pszDescription, tCmdFunction funcPtr );

    tCmdFunction GetCommandFunction( const char *pszCommand );

    void Run( void );

    void ListCommands( void );

private:
    tCommandTableEntry m_cmdTable[MAX_COMMAND_ENTRIES];
    uint32_t m_cmdCount;
};

#endif // __COMMANDHANDLER_H___
