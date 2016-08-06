#ifndef __STRING_H__
#define __STRING_H__

#include <stdint.h>

class String
{
public:
    String();
    String( const char *instr );
    String( const String &instr );
    ~String();

    String& operator+=( const String &rhs );
    const String operator+( const String &rhs ) const;
    const char *c_str( void ) const;

    bool operator==( const String &rhs ) const;
    bool operator!=( const String &rhs ) const;
    void operator=( const String &rhs );
    void SetString( const char *pszBuffer );

    String upper( void ) const;
    String lower( void ) const;

    String Trim( size_t length );
    String SubString( size_t startPos, size_t endPos ) const;
    String StripSpaces( void ) const;

    bool ToInteger( int32_t &intValue );

    size_t length( void );
    bool empty( void );

public:
    const static size_t STRING_END_POS = 0xFFFFFFFF;

private:
    size_t m_length;
    char *m_pData;
};

#endif // __STRING_H__
