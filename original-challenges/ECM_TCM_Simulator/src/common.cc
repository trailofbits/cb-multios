/*

Author: Jason Williams <jdw@cromulence.com>

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
extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#include "common.h"

#if 0
CUtil::String ReadLine( void )
{
	char pszLine[512];
	char c;
	size_t num_bytes;
	size_t pos;

	for ( pos = 0; pos < 511; pos++ )
	{
		if ( receive( STDIN, &c, 1, &num_bytes ) != 0 )
			_terminate( -1 );

		if ( num_bytes == 0 )
			_terminate( -1 );

		if ( c == '\n' )
			break;

		pszLine[pos] = c;
	}

	pszLine[pos] = '\0';

	return CUtil::String(pszLine);
}
#else
char g_szLineBuffer[4096+1];
uint32_t g_lineLength = 0;

CUtil::String ReadLine( void )
{
        uint32_t maxLen = 4096;

        char *pszLine = new char[maxLen+1];

        bool bLineFound = false;
        uint32_t lastScanPos = 0;
        while ( 1 )
        {
                uint32_t pos;
                for ( pos = lastScanPos; pos < g_lineLength; pos++ )
                {
                        if ( g_szLineBuffer[pos] == '\n' )
                        {
                                bLineFound = true;
                                break;
                        }
                }

                if ( bLineFound )
                {
                        // Include newline
                        lastScanPos = pos;
                        break;
                }

		if ( pos == g_lineLength && g_lineLength == maxLen )
                {
                        // Exceeded max length!
                        lastScanPos = pos;
                        break;
                }

                lastScanPos = pos;

                size_t num_bytes;
                uint32_t readRemaining = (maxLen - pos);

                if ( receive( STDIN, g_szLineBuffer+pos, readRemaining, &num_bytes ) != 0 )
                        _terminate( -1 );

                if ( num_bytes == 0 )
                        _terminate( -1 );

                g_lineLength += num_bytes;
        }

        memcpy( pszLine, g_szLineBuffer, lastScanPos );
        pszLine[lastScanPos] = '\0';

        CUtil::String sLine = pszLine;

        delete pszLine;

        uint32_t copyToPos = 0;
        uint32_t copyFromPos = lastScanPos+1;

        if ( bLineFound )
        {
                for ( uint32_t copyAmount = 0; copyAmount < (g_lineLength-(lastScanPos+1)); copyAmount++ )
                        g_szLineBuffer[copyToPos++] = g_szLineBuffer[copyFromPos++];

                g_lineLength -= (lastScanPos+1);
        }
        else
        {
                for ( uint32_t copyAmount = 0; copyAmount < (g_lineLength-lastScanPos); copyAmount++ )
                        g_szLineBuffer[copyToPos++] = g_szLineBuffer[copyFromPos++];

                g_lineLength -= (lastScanPos);
        }

        return (sLine);
}
#endif

bool HexCharToInt( char c, uint8_t &outValue )
{
	if ( c >= 'A' && c <= 'F' )
		outValue = (10 + (c - 'A'));
	else if ( c >= 'a' && c <= 'f' )
		outValue = (10 + (c -'a'));
	else if ( c >= '0' && c <= '9' )
		outValue = (c - '0');
	else
		return (false);

	return (true);
}

void PrintHexBytes( uint8_t *pData, uint32_t dataLen )
{
	for ( uint32_t i = 0; i < dataLen; i++ )
		printf( "$x$x", (pData[i] >> 4) & 0xF, pData[i] & 0xF );
	
	printf( "\n" );
}
