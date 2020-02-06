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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"

int cgc_islower( int c )
{
	if ( c >= 'a' && c <= 'z') {
		return 1;
	}

	return 0;
}

int cgc_isupper( int c )
{
	if ( c >= 'A' && c <= 'Z') {
		return 1;
	}

	return 0;
}

int cgc_isascii( int c )
{
	if ( 0x20 <= c && c <= 0x7e ) {
		return 1;
	}

	return 0;
}

int cgc_isalpha( int c )
{
	if ( cgc_islower(c) || cgc_isupper(c) ) {
		return 1;
	}

	return 0;
}

int cgc_isspace( int c )
{
    if ( c == ' ' ||
         c == '\t' ||
         c == '\n' ||
         c == '\v' ||
         c == '\f' ||
         c == '\r' )
        return 1;
    else
        return 0;
}

int cgc_isdigit( int c )
{
    if ( c >= '0' && c <= '9' )
        return 1;
    else
        return 0;
}

int cgc_isnan( double val )
{
    return __builtin_isnan( val );
}

int cgc_isinf( double val )
{
    return __builtin_isinf( val );
}

int cgc_tolower( int c )
{
    if ( c >= 'A' && c <= 'Z' )
        return (c - 'A') + 'a';
    else
        return c;
}

int cgc_toupper( int c )
{
    if ( c >= 'a' && c <= 'z' )
        return (c - 'a') + 'A';
    else
        return c;
}

int cgc_strcmp( char *str1, char *str2 )
{
    cgc_size_t i;

    for ( i = 0; ; i++ )
    {
        if ( str1[i] == '\0' && str2[i] == '\0' )
            break;

        if ( str1[i] == '\0' )
            return -1;

        if ( str2[i] == '\0' )
            return 1;

        if ( str1[i] < str2[i] )
            return -1;

        if ( str1[i] > str2[i] )
            return 1;
    }

    return 0;
}

char *cgc_strncat( char *dest, char *src, cgc_size_t n )
{
	cgc_size_t i = cgc_strlen(dest);
	cgc_size_t j;

	for (j = 0; i < n; i++, j++ )
	{
		if (src[j] == '\0')
			break;

		dest[i] = src[j];
	}

	return (dest);
}

char *cgc_strcat( char *dest, char *src )
{
	cgc_size_t i = cgc_strlen(dest);
	cgc_size_t j;

	for (j = 0; ; i++, j++ )
	{
		if (src[j] == '\0')
			break;

		dest[i] = src[j];
	}

	return (dest);
}

char *cgc_strchr( char *src, char c )
{
	char *result = NULL;

	while ( src[0] != '\0' ) {
		if ( src[0] == c ) {
			result = src;
			break;
		}
		src++;
	}

	return result;
}

char *cgc_strcpy( char *dest, char *src )
{
    cgc_size_t i;

    for ( i = 0; ; i++ )
    {
        if ( src[i] == '\0' )
            break;

        dest[i] = src[i];
    }
    dest[i] = '\0';

    return (dest);
}

char *cgc_strncpy( char *dest, const char *src, cgc_size_t num )
{
    cgc_size_t i;

    for ( i = 0; i < num; i++ )
    {
        if ( src[i] == '\0' )
            break;

        dest[i] = src[i];
    }
    dest[i] = '\0';

    return (dest);
}

void *cgc_memcpy( void *dest, void *src, cgc_size_t numbytes )
{
    cgc_size_t bytes_copied = 0;
    if ( numbytes >= 4 )
    {
        for ( ; bytes_copied+3 < numbytes; bytes_copied += 4 )
            *((uint32_t*)(dest+bytes_copied)) = *((uint32_t*)(src+bytes_copied));
    }

    for ( ; bytes_copied < numbytes; bytes_copied++ )
        *((uint8_t*)(dest+bytes_copied)) = *((uint8_t*)(src+bytes_copied));

    return dest;
}

void *cgc_memset( void *dest, int value, cgc_size_t numbytes )
{
    cgc_size_t bytes_copied = 0;
    uint8_t byte_set_value = (uint8_t)value;

    if ( numbytes >= 4 )
    {
        uint32_t dword_set_value = (byte_set_value << 24) | (byte_set_value << 16) | (byte_set_value << 8) | byte_set_value;

        for ( ; bytes_copied+3 < numbytes; bytes_copied += 4 )
            *((uint32_t*)(dest+bytes_copied)) = dword_set_value;
    }

    for ( ; bytes_copied < numbytes; bytes_copied++ )
        *((uint8_t*)(dest+bytes_copied)) = byte_set_value;

    return dest;
}

int cgc_atoi(const char* str)
{
    if ( str == NULL )
        return 0;

    int integer_part = 0;
    int sign = 1;
    int part;
    int digit_count = 0;

    // Skip whitespace
    while ( cgc_isspace( str[0] ) )
        str++;

    part = 0; // First part (+/-/number is acceptable)

    while( str[0] != '\0' )
    {
        if ( str[0] == '-' )
        {
            if ( part != 0 )
                return 0;

            sign = -1;
            part++;
        }
        else if ( str[0] == '+' )
        {
            if ( part != 0 )
                return 0;

            part++;
        }
        else if ( cgc_isdigit( *str ) )
        {
            if ( part == 0 || part == 1 )
            {
                // In integer part
                part = 1;
                integer_part = (integer_part * 10) + (*str - '0');

                digit_count++;

                if ( digit_count == 9 )
                    break;
            }
            else
            {
                // part invalid
                return 0;
            }
        }
        else
            break;

        str++;
    }

    return (sign * integer_part);
}

cgc_size_t cgc_strlen( const char *str )
{
    cgc_size_t length = 0;

    while ( str[length] != '\0' )
        length++;

    return length;
}

int cgc_abs( int val )
{
    if ( val < 0 )
        return -val;
    else
        return val;
}
