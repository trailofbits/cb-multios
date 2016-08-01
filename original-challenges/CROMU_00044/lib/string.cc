
extern "C"
{
#include <libcgc.h>
#include <stdlib.h>
}

#include "string.h"

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

String::String()
{
    m_length = 0;
    m_pData = NULL;
}

String::String( const char *instr )
{
    size_t alloc_length = strlen( instr ) + 1;
    m_pData = new char[alloc_length];

    memcpy( (void *)m_pData, (void *)instr, alloc_length-1 );
    m_pData[alloc_length-1] = '\0';

    m_length = alloc_length-1;
}

String::String( const String &instr )
{
    size_t alloc_length = instr.m_length+1;
    m_pData = new char[ alloc_length ];

    memcpy( m_pData, instr.m_pData, instr.m_length );

    m_pData[alloc_length-1] = '\0';
    m_length = instr.m_length;
}

String::~String()
{
    if ( m_pData )
        delete [] m_pData;
}

String& String::operator+=( const String &rhs )
{
    size_t alloc_length = m_length + rhs.m_length + 1;
    char *pNewData = new char[alloc_length];

    memcpy( pNewData, m_pData, m_length );
    memcpy( pNewData+m_length, rhs.m_pData, rhs.m_length );

    if ( m_pData )
        delete [] m_pData;

    m_pData = pNewData;
    m_length = alloc_length-1;

    return *this;
}

const String String::operator+( const String &rhs ) const
{
    return String(*this) += rhs;
}

const char *String::c_str( void ) const
{
    return (m_pData);
}

size_t String::length( void )
{
    return (m_length);
}

bool String::empty( void )
{
    return (m_length == 0);
}

String String::upper( void ) const
{
    String upperStr = *this;

    for ( size_t i = 0; i < upperStr.m_length; i++ )
        upperStr.m_pData[i] = toupper( upperStr.m_pData[i] );

    return (upperStr);
}

String String::lower( void ) const
{
    String lowerStr = *this;

    for ( size_t i = 0; i < lowerStr.m_length; i++ )
        lowerStr.m_pData[i] = tolower( lowerStr.m_pData[i] );

    return (lowerStr);
}

String String::StripSpaces( void ) const
{
    // Very inefficient method of stripping spaces
    size_t i;
    for ( i = 0; i < m_length; i++ )
    {
        if ( m_pData[i] != ' ' )
            break;
    }

    return (SubString( i, String::STRING_END_POS ));
}

String String::Trim( size_t length )
{
    *this = SubString( 0, length );

    return (*this);
}

String String::SubString( size_t startPos, size_t endPos ) const
{
    if ( startPos >= m_length )
        return String("");

    if ( endPos > m_length )
        endPos = m_length;

    if ( startPos >= endPos )
        return String("");

    size_t new_length = endPos - startPos;
    char *pszNewStr = new char[new_length+1];

    // Copy in string
    size_t copyPos = 0;
    for ( size_t curPos = startPos; curPos < endPos; curPos++ )
        pszNewStr[copyPos++] = m_pData[curPos];

    pszNewStr[copyPos] = '\0';

    return String(pszNewStr);
}

bool String::operator==( const String &rhs ) const
{
    if ( m_length != rhs.m_length )
        return (false);

    for ( size_t i = 0; i < m_length; i++ )
        if ( m_pData[i] != rhs.m_pData[i] )
            return (false);

    return (true);
}

bool String::operator!=( const String &rhs ) const
{
    return !(*this == rhs);
}

void String::operator=( const String &rhs )
{
    if ( m_pData )
        delete [] m_pData;

    size_t alloc_length = rhs.m_length+1;
    m_pData = new char[ alloc_length ];

    memcpy( m_pData, rhs.m_pData, rhs.m_length );

    m_pData[alloc_length-1] = '\0';
    m_length = rhs.m_length;
}

void String::SetString( const char *pszBuffer )
{
    if ( m_pData )
        delete [] m_pData;

    size_t alloc_length = strlen( pszBuffer ) + 1;
    m_pData = new char[alloc_length];

    memcpy( (void *)m_pData, (void *)pszBuffer, alloc_length-1 );
    m_pData[alloc_length-1] = '\0';

    m_length = alloc_length-1;
}

bool String::ToInteger( int32_t &intValue )
{
    if ( m_pData )
    {
        intValue = atoi( m_pData );
        return (true);
    }
    else
        return (false);     // Conversion failed
}
