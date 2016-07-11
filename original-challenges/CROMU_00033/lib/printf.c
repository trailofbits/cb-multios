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
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#define INT_BUF_MAX         (32)

int putc( int c )
{
    size_t tx_count;

    if ( transmit( STDOUT, &c, 1, &tx_count ) != 0 )
        _terminate(2);

    return c;
}

int vprintf( const char *fmt, va_list arg )
{
    int i = 0;

    if ( fmt == NULL )
        return -1;

    for ( ; ; )
    {
        if ( *fmt == '\0' )
            break;

        if ( *fmt == '$' )
        {
            fmt++;

            switch ( *fmt )
            {
            case '$':
                putc( '$' );
                break;

            case 's':
                {
                    char *str1 = va_arg( arg, char * );

                    while ( *str1 )
                    {
                        putc( *str1 );
                        i++;

                        str1++;
                        if ( str1 == '\0' )
                            break;
                    }
                }
                break;
	    case 'c':
		{
			int ch = va_arg( arg, int );
			char c = (char)ch;
			putc( c );
		}
		break;
            case 'd':
                {
                    char temp[INT_BUF_MAX];
                    int char_count;
                    int int_arg = va_arg( arg, int );

                    char_count = 0;
                    if ( int_arg < 0 )
                    {
                        int_arg = -int_arg;
                        putc( '-' );
                        i++;
                    }
                    else if ( int_arg == 0 )
                    {
                        char_count = 1;
                        temp[0] = '0';
                    }

                    while ( int_arg != 0 )
                    {
                        temp[char_count++] = (int_arg % 10) + '0';
                        int_arg /= 10;

                        if ( char_count >= INT_BUF_MAX )
                            break;
                    }

                    while ( char_count-- > 0 )
                    {
                        putc( temp[char_count] );
                        i++;
                    }
                }
                break;

            case 'x':
            case 'X':
                {
                    char temp[INT_BUF_MAX];
                    int char_count;
                    unsigned int int_arg = va_arg( arg, unsigned int );

                    char_count = 0;
                    while ( int_arg != 0 )
                    {
                        unsigned int val = (int_arg & 0xF);
                        int_arg = int_arg >> 4;

                        if ( val >= 10 )
                        {
                            if ( *fmt == 'x' )
                                temp[char_count++] = (val - 10) + 'a';
                            else
                                temp[char_count++] = (val - 10) + 'A';
                        }
                        else
                            temp[char_count++] = val + '0';

                        if ( char_count >= INT_BUF_MAX )
                            break;
                    }

                    while ( char_count-- > 0 )
                    {
                        putc( temp[char_count] );
                        i++;
                    }
                }
                break;

            case '\0':
                return -1;

            default:
                // Unknown
                return -1;
            }

            fmt++;
        }
        else
        {
            putc( *fmt );
            fmt++;

            i++;
        }
    }

    return (i);
}

int printf( const char *fmt, ... )
{
    va_list arg;
    int done;

    va_start( arg, fmt );
    done = vprintf( fmt, arg );
    va_end( arg );

    return done;
}
