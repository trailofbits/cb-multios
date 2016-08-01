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
#include <libcgc.h>
#include <stdlib.h>
#include <stdint.h>

int memcpy( void *dest, void *src, size_t n )
{
	size_t index = 0;

	while ( index < n ) {
		((char*)dest)[index] = ((char*)src)[index];
		index++;
	}

	return index;
}

int islower( int c )
{
	if ( c >= 0x61 && c <= 0x7a )
		return 1;
	else
		return 0;
}

int isupper( int c )
{
	if ( c >= 0x41 && c <= 0x5a )
		return 1;
	else
		return 0;
}

int isalpha( int c )
{
	return islower( c ) | isupper( c );
}

int isalnum( int c )
{
	return isalpha( c ) | isdigit( c );
}

int isspace( int c )
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

int isdigit( int c )
{
    if ( c >= '0' && c <= '9' )
        return 1;
    else
        return 0;
}

int isnan( double val )
{
    return __builtin_isnan( val );
}

int isinf( double val )
{
    return __builtin_isinf( val );
}

double atof(const char* str)
{
    if ( str == NULL )
        return 0.0;

    double val = 0.0;
    double scale = 0.1;
    int sign = 1;
    int part;

    // Skip whitespace
    while ( isspace( str[0] ) )
        str++;

    part = 0; // First part (+/-/./number is acceptable)

    while( str[0] != '\0' )
    {
        if ( str[0] == '-' )
        {
            if ( part != 0 )
                return 0.0;

            sign = -1;
            part++;
        }
        else if ( str[0] == '+' )
        {
            if ( part != 0 )
                return 0.0;

            part++;
        }
        else if ( str[0] == '.' )
        {
            if ( part == 0 || part == 1 )
                part = 2;
            else
                return 0.0;
        }
        else if ( isdigit( *str ) )
        {
            if ( part == 0 || part == 1 )
            {
                // In integer part
                part = 1;
                val = (val * 10.0) + (*str - '0');
            }
            else if ( part == 2 )
            {
                val += ((*str - '0') * scale);
                scale /= 10.0;
            }
            else
            {
                // part invalid
                return 0.0;
            }
        }
        else
            break;

        str++;
    }

    return (sign * val);
}


int atoi(const char* str)
{
    if ( str == NULL )
        return 0;

    int integer_part = 0;
    int sign = 1;
    int part;
    int digit_count = 0;

    // Skip whitespace
    while ( isspace( str[0] ) )
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
        else if ( isdigit( *str ) )
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

char *strncpy( char *dest, char *src, size_t n )
{
    size_t i;

    for ( i = 0; i < n ; i++ )
    {
        if ( src[i] == '\0' )
            break;

        dest[i] = src[i];
    }
    dest[i] = '\0';

    return (dest);
}

char *strcpy( char *dest, char *src )
{
    size_t i;

    for ( i = 0; ; i++ )
    {
        if ( src[i] == '\0' )
            break;

        dest[i] = src[i];
    }
    dest[i] = '\0';

    return (dest);
}

void bzero( void *buff, size_t len )
{
    size_t index = 0;
    unsigned char *c = buff;

    if ( buff == NULL ) {
        goto end;
    }

    if ( len == 0 ) {
        goto end;
    }

    for ( index = 0; index < len; index++ ) {
        c[index] = 0x00;
    }

end:
    return;
}

int memcmp( void *s1, void *s2, size_t n ) 
{
    char *c1 = (char*)s1;
    char *c2 = (char*)s2;

    if ( n == 0 ) {
        return 0;
    }

    while ( *c1 && (*c1 == *c2) && n )
    {
      c1++,c2++;
      n--;
    }

    c1--,c2--;

    return (*(const unsigned char *)c1 - *(const unsigned char *)c2);
}

int strcmp( const char *s1, const char *s2 ) 
{
    while ( *s1 && (*s1 == *s2) ) 
    {
      s1++,s2++;
    }
    return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

char *strncat ( char *dest, const char *src, size_t n ) 
{
    size_t dest_len = strlen(dest);
    size_t i;

    if (dest == NULL || src == NULL) 
    {
      return(dest);
    }
    for (i = 0; i < n && src[i] != '\0'; i++) 
    {
      dest[dest_len+i] = src[i];
    }
    dest[dest_len+i] = '\0';

    return(dest);
}

size_t receive_until( char *dst, char delim, size_t max )
{
    size_t len = 0;
    size_t rx = 0;
    char c = 0;

    while( len < max ) {
        dst[len] = 0x00;

        if ( receive( STDIN, &c, 1, &rx ) != 0 ) {
            len = 0;
            goto end;
        }

        if ( c == delim ) {
            goto end;
        }
   
        dst[len] = c;
        len++;
    }
end:
    return len;
}

size_t strcat( char *dest, char*src )
{
    size_t length = 0;
    size_t start = 0;

    if ( dest == NULL || src == NULL) {
        goto end;
    }

    start = strlen( dest );

    for ( ; src[length] != 0x00 ; start++, length++ ) {
        dest[start] = src[length];
    }

    length = start;
end:
    return length;
}

size_t strlen( char * str )
{
    size_t length = 0;

    if ( str == NULL ) {
        goto end;
    }

    while ( str[length] ) { length++; }

end:
    return length;
}

size_t itoa( char *out, size_t val, size_t max )
{
    size_t length = 0;
    size_t end = 0;
    size_t temp = 0;

    if ( out == NULL ) {
        goto end;
    }

    // Calculate the needed length
    temp = val;
    do {
        end++;
        temp /= 10;
    } while ( temp );

    // ensure we have enough room
    if ( end >= max ) {
        goto end;
    }

    length = end;

    // Subtract one to skip the null
    end--;

    do {
        out[end] = (val % 10) + 0x30;
        val /= 10;
        end--;
    } while ( val );

    out[length] = 0x00;
end:
    return length;
}

void puts( char *t )
{
    size_t size;
    transmit(STDOUT, t, strlen(t), &size);
}
