/*

Copyright (c) 2015 Cromulence LLC

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
#include <cutil_string.h>

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
}

using namespace CUtil;


String::String( )
{
	m_pData = new char[1];
	m_pData[0] = '\0';

	m_length = 0;
}

String::String( const String &str )
	: m_pData( NULL ), m_length( 0 )
{
	SetInternal( str );
}

String::String( const char *pszStr )
	: m_pData( NULL ), m_length( 0 )
{
	SetInternal( pszStr );
}

String::~String( )
{
	if ( m_pData )
		delete [] m_pData;

	m_length = 0;
}
	
// Operators
bool String::operator==( const String &rhs ) const
{
	if ( m_length != rhs.m_length )
		return (false);

	return memcmp( m_pData, rhs.m_pData, m_length ) == 0;
}

bool String::operator!=( const String &rhs ) const
{
	return !(*this == rhs);
}

void String::operator=( const String &rhs )
{
	SetInternal( rhs );
}

void String::operator=( const char *rhs )
{
	SetInternal( rhs );
}

const String& String::operator+( const String &rhs ) const
{
	return String(*this) += rhs;
}

String& String::operator+=( const String &rhs )
{
	// Make a new string of this string + rhs
	size_t new_stringlen = m_length + rhs.m_length;

	char *pNewData = new char[new_stringlen+1];

	memcpy( pNewData, m_pData, m_length );
	memcpy( pNewData+m_length, rhs.m_pData, rhs.m_length );

	// Keep a null terminator at the end for easy return of c_str
	pNewData[m_length+rhs.m_length] = '\0';

	if ( m_pData )
		delete [] m_pData;

	m_pData = pNewData;
	m_length = new_stringlen;

	return *this;
}
		
// Conversion
const char* String::c_str( void ) const
{
	return (m_pData);
}

String String::Upper( void ) const
{
	String sUpper = *this;

	for ( size_t i = 0; i < m_length; i++ )
	{
		if ( islower( sUpper.m_pData[i] ) )
			sUpper.m_pData[i] = toupper( sUpper.m_pData[i] );
	}

	return (sUpper);
}

String String::Lower( void ) const
{
	String sLower = *this;

	for ( size_t i = 0; i < m_length; i++ )
	{
		if ( isupper( sLower.m_pData[i] ) )
			sLower.m_pData[i] = tolower( sLower.m_pData[i] );
	}

	return (sLower);
}

char String::operator[]( const size_t &loc ) const
{
	if ( IsEmpty() )
		return '\0';

	if ( loc >= m_length )
		return '\0';

	return m_pData[loc];
}

String String::Trim( size_t length ) const
{
	return (SubString( 0, length ));
}

String String::SubString( size_t startPos, size_t endPos ) const
{
	if ( endPos > m_length )
		endPos = m_length;

	if ( startPos >= m_length || startPos >= endPos )
	       return String("");

	size_t new_length = endPos - startPos;
	char *pszNewStr = new char[new_length+1];

	size_t destPos = 0;
	for ( size_t srcPos = startPos; srcPos < endPos; srcPos++ )
		pszNewStr[destPos++] = m_pData[srcPos];

	pszNewStr[destPos] = '\0';
	
	return String(pszNewStr);	
}

String String::TrimSpaces( void ) const
{
	size_t pos = 0;
	for ( ; pos < m_length; pos++ )
	{
		if ( m_pData[pos] != ' ' )
			break;
	}

	return (SubString( pos, npos ));
}

bool String::ToInt( uint32_t &value )
{
	if ( !IsEmpty() )
	{
		value = atoi( m_pData );
		return (true);
	}
	else
		return (false);
}

size_t String::GetLength( void ) const
{
	return (m_length);
}

bool String::IsEmpty( void ) const
{
	return (m_length == 0);
}

void String::SetInternal( const char *pszStr )
{
	if ( m_pData )
		delete [] m_pData;

	if ( pszStr == NULL )
	{
		m_pData = new char[1];
		m_pData[0] = '\0';

		m_length = 0;
		return;
	}

	m_length = strlen( pszStr );

	m_pData = new char[m_length+1];

	memcpy( m_pData, pszStr, m_length );
	m_pData[m_length] = '\0';
}

void String::SetInternal( const String& str )
{
	if ( m_pData )
		delete [] m_pData;

	m_length = str.m_length;

	m_pData = new char[m_length+1];

	memcpy( m_pData, str.m_pData, m_length );
	m_pData[m_length] = '\0';
}
