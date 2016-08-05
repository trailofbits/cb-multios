/*

Author: James Nuttall <james@cromulence.com>

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
extern "C"
{
#include <stdio.h>
#include <stdlib.h>
}

#include "common.h"

#define INPUT_CAP 512

/*
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
}*/

char* ConvertToHexChars( uint8_t *pData, uint32_t dataLen )
{
	int len = dataLen * 2;
	char* str = new char[len];

	for ( uint32_t i = 0; i < dataLen; i++ )
	{
		sprintf( &str[ i * 2 ], "$x", (pData[i] >> 4) & 0xF );
		sprintf( &str[ ( i * 2 )+1 ], "$x", pData[i] & 0xF );
	}
	
	return str;
}

/*
uint8_t* ConvertBackHexChars( uint8_t *pData, uint32_t dataLen )
{
	int len = dataLen / 2;
	uint8_t* str = new uint8_t[len];

	int j = 0;

	for ( uint32_t i = 0; i < dataLen; )
	{
		uint16_t var = 0;
		uint8_t a,b;
		HexCharToInt( pData[i], a );
		HexCharToInt( pData[i+1], b );
		var = a << 4; // move to high nibble
		var += b;
		str[j++] = var;
		i += 2;
	}
	
	return str;
}*/
/*
void PrintHexBytes( uint8_t *pData, uint32_t dataLen )
{
	for ( uint32_t i = 0; i < dataLen; i++ )
		printf( "$x$x", (pData[i] >> 4) & 0xF, pData[i] & 0xF );
	
	printf( "\n" );
}*/

