/*

Copyright (c) 2015 Cromulence LLC

Authors: Cromulence <cgc@cromulence.com>

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
#include "cgc_ctype.h"

#define		DEL	0x7f
#define		SPC	0x20

#define		TAB	0x09
#define		LF	0x0a
#define		VT	0x0b
#define 	FF	0x0c
#define		CR	0x0d

int cgc_isdigit( int c )
{
	if ( c >= '0' && c <= '9' )
		return 1;
	else
		return 0;
}

int cgc_isupper( int c )
{
	if ( c >= 'A' && c <= 'Z' )
		return 1;
	else
		return 0;
}

int cgc_islower( int c )
{
	if ( c >= 'a' && c <= 'z' )
		return 1;
	else
		return 0;
}

int cgc_isalpha( int c )
{
	if ( cgc_isupper( c ) || cgc_islower( c ) )
		return 1;
	else
		return 0;
}

int cgc_isalnum( int c )
{
	if ( cgc_isalpha( c ) || cgc_isdigit( c ) )
		return 1;
	else
		return 0;
}

int cgc_isprint( int c )
{
	if ( c >= SPC && c != DEL )
		return 1;
	else
		return 0;
}


int cgc_toupper( int c )
{
	if ( cgc_islower( c ) )
		return (c - 'a') + 'A';
	else
		return c;
}

int cgc_tolower( int c )
{
	if ( cgc_isupper( c ) )
	       return (c - 'A') + 'a';
	else
		return c;	
}

int cgc_isspace( int c )
{
	if ( c == SPC ||
	     c == TAB ||
	     c == LF ||
	     c == VT ||
	     c == FF ||
	     c == CR )
		return 1;
	else
		return 0;
}
