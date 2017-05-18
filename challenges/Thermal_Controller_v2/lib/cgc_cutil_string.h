/*

Copyright (c) 2016 Cromulence LLC

Authors: Jason Williams <jdw@cromulence.com>

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
#ifndef __CUTIL_STRING_H__
#define __CUTIL_STRING_H__

extern "C"
{
#include "cgc_stdint.h"
#include "libcgc.h"
#include "cgc_stddef.h"
}

#ifdef NULL
#undef NULL
#define NULL 0
#endif

#include "cgc_stdint.h"

// Cromulence Utilities Library
// String class

namespace CUtil
{
	class String
	{
	public:
		// End position marker
		const static cgc_size_t npos = 0xffffffff;

	public:
		String( );
		String( const String &str );
		String( const char *pszStr );

		~String( );

		// Operators
		bool operator==( const String &rhs ) const;
		bool operator!=( const String &rhs ) const;
		void operator=( const String &rhs );
		void operator=( const char *rhs );

		const String& operator+( const String &rhs ) const;
		String& operator+=( const String &rhs );

		// Conversion
		const char* c_str( void ) const;
		String Upper( void ) const;
		String Lower( void ) const;

		// Trim to a specific length
		String Trim( cgc_size_t length ) const;

		// Accessor method
		char operator[]( const cgc_size_t &loc ) const;

		// Get string within string from start to end positions
		String SubString( cgc_size_t startPos, cgc_size_t endPos ) const;
		
		// Trim leading spaces (TrimSpaces)	
		String TrimSpaces( void ) const;

		bool ToInt( uint32_t &value );

		cgc_size_t GetLength( void ) const;
		bool IsEmpty( void ) const;

	protected:
		void SetInternal( const String &str );
		void SetInternal( const char *pszStr );
	
	protected:
		char 	*m_pData;
		cgc_size_t	m_length;	
	};
}

#endif // __CUTIL_STRING_H__
