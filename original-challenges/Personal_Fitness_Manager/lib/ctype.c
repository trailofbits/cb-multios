/*

Copyright (c) 2016 Cromulence LLC

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
#include <ctype.h>

#define		DEL	0x7f
#define		SPC	0x20

#define		TAB	0x09
#define		LF	0x0a
#define		VT	0x0b
#define 	FF	0x0c
#define		CR	0x0d

int isdigit( int c )
{
	if ( c >= '0' && c <= '9' )
		return 1;
	else
		return 0;
}

int isupper( int c )
{
	if ( c >= 'A' && c <= 'Z' )
		return 1;
	else
		return 0;
}

int islower( int c )
{
	if ( c >= 'a' && c <= 'z' )
		return 1;
	else
		return 0;
}

int isalpha( int c )
{
	if ( isupper( c ) || islower( c ) )
		return 1;
	else
		return 0;
}

int isalnum( int c )
{
	if ( isalpha( c ) || isdigit( c ) )
		return 1;
	else
		return 0;
}

int isprint( int c )
{
	if ( c >= SPC && c != DEL )
		return 1;
	else
		return 0;
}

int toupper( int c )
{
	if ( islower( c ) )
		return (c - 'a') + 'A';
	else
		return c;
}

int tolower( int c )
{
	if ( isupper( c ) )
	       return (c - 'A') + 'a';
	else
		return c;	
}

int isspace( int c )
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
