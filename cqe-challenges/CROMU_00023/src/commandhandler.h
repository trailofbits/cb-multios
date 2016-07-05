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

#include <stdint.h>
#include <string.h>

// Forward declarations
class CommandHandler
{
public:
    CommandHandler();
    ~CommandHandler();

    void ParserLoop( void );

private:
    bool CmdChangeDiverInfo( void );
    bool CmdLogNewDive( void );
    bool CmdDownloadDiveData( void );
    bool CmdEditDives( void );
    bool CmdPrintDiveLogs( void );
    bool CmdRemoveDives( void );
    bool CmdDiverStatistics( void );
    bool CmdExitApplication( void );

    void PrintDiverInfo( void );

private:
    typedef bool (CommandHandler::*pCmdFptr)( void );

    typedef struct COMMAND_FUNCTION
    {
        char szCommand[128];
        char szDescription[128];
        pCmdFptr pCmdFunc;
    } tCommandFunction;

    DLQueue m_diveQueue;
    DiverInfo m_oDiver;
    bool m_bDiverInitialized;

private:
    void PrintCommandTable( tCommandFunction * );
    void PrintDiveList( void );
};

#endif // __COMMANDHANDLER_H__
