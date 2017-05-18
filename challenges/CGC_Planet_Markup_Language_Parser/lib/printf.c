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
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_mymath.h"

// 5 digits of precision
#define F32_PRECISION       0.00001

int cgc_putc( int c )
{
    cgc_size_t tx_count;

    if ( cgc_transmit( STDOUT, &c, 1, &tx_count ) != 0 )
        cgc__terminate(2);

    return c;
}

void cgc_int_to_str( int val, char *buf )
{
    char temp_buf[32];
    char *c = temp_buf;
    int count = 0;

    if ( buf == NULL )
        return;

    if ( val < 0 )
    {
        *buf = '-';
        buf++;

        val *= -1;
    }

    do
    {
        *c = (val % 10) + '0';
        val /= 10;

        c++;
        count++;
    } while ( val != 0 );

    while ( count-- > 0 )
    {
        c--;
        *buf = *c;
        buf++;
    }

    *buf = '\0';
}

#ifdef PATCHED
void cgc_float_to_str( double val, char *buf, unsigned int max )
{
    char *end = buf + max;

    if ( buf == NULL )
        return;

    if ( cgc_isnan( val ) )
    {
        strncpy( buf, "nan", max );
    }
    else if ( cgc_isinf( val ) )
    {
        strncpy( buf, "inf", max );
    }
    else if ( val == 0.0 )
    {
        strncpy( buf, "0.00000", max );
    }
    else
    {
        int digit;
        int m;
        int m1;
        int fraction_digit;
        int in_fraction;
        int neg = 0;
        char *c = buf;

        if ( val > 0.0 )
            val = val + (F32_PRECISION * 0.5);
        else
            val = val - (F32_PRECISION * 0.5);

        // Negative numbers
        if ( val < 0.0 )
        {
            neg = 1;
            *(c++) = '-';
            val = -val;
            if ( c == end ) {
              return;
	    } 
        }

        // Calculate magnitude
        m = cgc_log10( val );

        if ( m < 1.0 )
            m = 0;

        fraction_digit = 0;
        in_fraction = 0;
        while ( val > F32_PRECISION || m >= 0 )
        {
            double weight = cgc_pow( 10.0, m );
            if ( weight > 0 && !cgc_isinf(weight) )
            {
                digit = cgc_floor( val / weight );
                val -= (digit * weight);

                *(c++) = '0' + digit;

                if ( in_fraction )
                    fraction_digit++;
		if ( c == end ) {
			return;
		}
            }

            if ( m == 0 && val > 0.0 )
            {
                *(c++) = '.';
                in_fraction = 1;
                fraction_digit = 0;
		if ( c == end) {
			return;
		}
            }

            m--;
        }

        while ( in_fraction && fraction_digit < 5 )
        {
            *(c++) = '0';
            fraction_digit++;
		if ( c == end ) {
			return;
		}
        }

        *c = '\0';
    }
}
#else
void cgc_float_to_str( double val, char *buf )
{
    if ( buf == NULL )
        return;

    if ( cgc_isnan( val ) )
    {
        cgc_strcpy( buf, "nan" );
    }
    else if ( cgc_isinf( val ) )
    {
        cgc_strcpy( buf, "inf" );
    }
    else if ( val == 0.0 )
    {
        cgc_strcpy( buf, "0.00000" );
    }
    else
    {
        int digit;
        int m;
        int m1;
        int fraction_digit;
        int in_fraction;
        int neg = 0;
        char *c = buf;

        if ( val > 0.0 )
            val = val + (F32_PRECISION * 0.5);
        else
            val = val - (F32_PRECISION * 0.5);

        // Negative numbers
        if ( val < 0.0 )
        {
            neg = 1;
            *(c++) = '-';
            val = -val;
        }

        // Calculate magnitude
        m = cgc_log10( val );

        if ( m < 1.0 )
            m = 0;

        fraction_digit = 0;
        in_fraction = 0;
        while ( val > F32_PRECISION || m >= 0 )
        {
            double weight = cgc_pow( 10.0, m );
            if ( weight > 0 && !cgc_isinf(weight) )
            {
                digit = cgc_floor( val / weight );
                val -= (digit * weight);

                *(c++) = '0' + digit;

                if ( in_fraction )
                    fraction_digit++;
            }

            if ( m == 0 && val > 0.0 )
            {
                *(c++) = '.';
                in_fraction = 1;
                fraction_digit = 0;
            }

            m--;
        }

        while ( in_fraction && fraction_digit < 5 )
        {
            *(c++) = '0';
            fraction_digit++;
        }

        *c = '\0';
    }
}
#endif

int cgc_vprintf( const char *fmt, va_list arg )
{
    int character_count = 0;
    char temp_buf[64];

    if ( fmt == NULL )
        return -1;

    while ( *fmt )
    {
        if ( *fmt == '@' )
        {
            fmt++;

            // We don't handle any special formatting
            switch ( *fmt )
            {
            case '@':
                cgc_putc( '@' );
                break;

            case 'd':
                // Integer
                {
                    int int_arg = va_arg( arg, int );
                    char *c;

                    cgc_int_to_str( int_arg, temp_buf );

                    c = temp_buf;
                    while ( *c )
                    {
                        cgc_putc( *c );
                        character_count++;
                        c++;
                    }
                }
                break;

            case 'f':
                // Float
                {
                    double float_arg = va_arg( arg, double );
                    char *c;
#ifdef PATCHED
                    cgc_float_to_str( float_arg, temp_buf, 64 );
#else
                    cgc_float_to_str( float_arg, temp_buf );
#endif

                    c = temp_buf;
                    while ( *c )
                    {
                        cgc_putc( *c );
                        character_count++;
                        c++;
                    }
                }
                break;
            case 's':
               // string
               {
                    char *string_arg = va_arg( arg, char *);
                    while (*string_arg)
                    {
                        cgc_putc( *string_arg );
                        character_count++;
                        string_arg++;
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
            cgc_putc( *fmt );
            fmt++;

            character_count++;
        }
    }

    return (character_count);
}

int cgc_printf( const char *fmt, ... )
{
    va_list arg;
    int done;

    va_start( arg, fmt );
    done = cgc_vprintf( fmt, arg );
    va_end( arg );

    return done;
}
