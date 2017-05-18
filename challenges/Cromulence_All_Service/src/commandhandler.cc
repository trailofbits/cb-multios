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
#include "cgc_common.h"

CCommandHandler::CCommandHandler()
    : m_cmdCount( 0 )
{
    cgc_memset( m_cmdTable, 0, sizeof(tCommandTableEntry) * MAX_COMMAND_ENTRIES );
}

CCommandHandler::~CCommandHandler()
{

}

bool CCommandHandler::RegisterCommand( const char *pszCommand, const char *pszDescription, tCmdFunction pFunc )
{
    if ( m_cmdCount == MAX_COMMAND_ENTRIES )
        return (false);

    if ( !pszCommand )
        return (false);

    if ( !pFunc )
        return (false);

    cgc_strncpy( m_cmdTable[m_cmdCount].szCommand, pszCommand, MAX_COMMAND_LENGTH );
    cgc_strncpy( m_cmdTable[m_cmdCount].szDescription, pszDescription, MAX_DESCRIPTION_LENGTH );

    m_cmdTable[m_cmdCount].pCmdFunc = pFunc;

    // Update command table count
    m_cmdCount++;

    return (true);
}

tCmdFunction CCommandHandler::GetCommandFunction( const char *pszCommand )
{
    for ( uint32_t i = 0; i < m_cmdCount; i++ )
    {
        if ( cgc_stricmp( m_cmdTable[i].szCommand, pszCommand ) == 0 )
            return (m_cmdTable[i].pCmdFunc);
    }

    return (NULL);
}

void CCommandHandler::Run( void )
{
    char szLine[1024];

    for (;;)
    {
        // Prompt
        cgc_printf( ": " );

        // Get command line
        cgc_getline( szLine, 1024 );

        char *szToken = cgc_strtok( szLine, " " );

        if ( szToken == NULL )
        {
            cgc_printf( "Unknown command.\n" );
            continue;
        }

        if ( cgc_stricmp( szToken, "exit" ) == 0 )
            break;

        if ( cgc_stricmp( szToken, "?" ) == 0 )
        {
            ListCommands();
            continue;
        }

        // Search for appropriate command
        tCmdFunction pCmdFunc = GetCommandFunction( szToken );

        if ( pCmdFunc == NULL )
        {
            cgc_printf( "Unknown command.\n" );
            continue;
        }

        (*pCmdFunc)( cgc_strtok( NULL, "" ) );
    }
}

void CCommandHandler::ListCommands( void )
{
    cgc_printf( "Available commands:\n" );
    for ( uint32_t i = 0; i < m_cmdCount; i++ )
    {
        cgc_printf( "@s - @s\n", m_cmdTable[i].szCommand, m_cmdTable[i].szDescription );
    }
}
