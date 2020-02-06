/*

Author: Jason Williams <jdw@cromulence.co>

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

void cgc_int_to_hex( unsigned int val, char *buf )
{
    char temp_buf[32];
    char *c = temp_buf;
    int count = 0;

    if ( buf == NULL )
        return;

    do
    {
        *c = (val % 16) + '0';
	if (*c > '9') {
		*c += 7;
	}
        val /= 16;

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

void cgc_float_to_str( double val, char *buf, int precision )
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

        while ( in_fraction && fraction_digit < precision )
        {
            *(c++) = '0';
            fraction_digit++;
        }

        *c = '\0';
    }
}

int cgc_vprintf( const char *fmt, va_list arg )
{
    int character_count = 0;
    char temp_buf[64];
    int width, precision, zero_padding, left_justification;
    int i;
    int pad_len;

    if ( fmt == NULL )
        return -1;

    while ( *fmt )
    {
        if ( *fmt == '@' )
        {
            fmt++;

            width=0;
            precision=0;
            zero_padding=0;
            left_justification=0;
            pad_len=0;

            // We handle width, precision, and justification (but not for floats yet)
            if (*fmt == '@') {

                cgc_putc('@');
                fmt++;
                character_count++;
                continue;
            }

            if (*fmt == '-') {

                left_justification=1;
                ++fmt;
            }

            if (cgc_isdigit(*fmt)) {

                if (*fmt == '0') {

                    zero_padding = 1;
                    fmt++;
                }

                if (cgc_isdigit(*fmt)) {

                    width = cgc_atoi(fmt);

                    // skip past the width specification
                    while (cgc_isdigit(*fmt))
                        fmt++;
                }
            }

            if (*fmt == '.') {

                // skip over the '.'
                fmt++;

                precision=cgc_atoi(fmt);

                // now skip past the integer precision value
                while (cgc_isdigit(*fmt))
                    fmt++;

            }

                // single char
            if (*fmt == 'c') {
                
                char c = (char )va_arg(arg, int);

                pad_len = width - 1;

                // justify right 
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            cgc_putc('0');
                        else
                            cgc_putc(' ');

                        character_count++;
                    }
                }

                // output the char itself
                cgc_putc(c);
                character_count++;

                // justify to the left
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        cgc_putc(' ');
                        character_count++;
                    }
                }

                fmt++;
                continue;
            }

                 // Integer 
            if (*fmt == 'd')  {

                int int_arg = va_arg( arg, int );
                char *c;

                cgc_int_to_str( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - cgc_strlen(temp_buf);

                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            cgc_putc('0');
                        else
                            cgc_putc(' ');

                        character_count++;
                    }
                }

                // now output the integer value
                c = temp_buf;
                while ( *c )
                {
                    cgc_putc( *c );
                    character_count++;
                    c++;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        cgc_putc(' ');
                        character_count++;
                    }
                }

                fmt++;
                continue;

            }

                // hex
            if ( *fmt == 'x')  {
            
                unsigned int int_arg = va_arg( arg, unsigned int );
                char *c;

                cgc_int_to_hex( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - cgc_strlen(temp_buf);

                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            cgc_putc('0');
                        else
                            cgc_putc(' ');

                        character_count++;
                    }
                }

                // now output the hex string
                c = temp_buf;
                while ( *c )
                {
                    cgc_putc( *c );
                    character_count++;
                    c++;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        cgc_putc(' ');
                        character_count++;
                    }
                }

                fmt++;
                continue;
            }

                // Float
            if (*fmt =='f' ) {

                    // currently does not support precision specification for float type
                    // need the float_to_str() updated to support the rounding necessary

                double float_arg = va_arg( arg, double );
                char *c;

                cgc_float_to_str( float_arg, temp_buf, precision);

                // is the output string shorter than the desired width?
                pad_len = width - cgc_strlen(temp_buf);

                // pad the output with spaces or zeros
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            cgc_putc('0');
                        else
                            cgc_putc(' ');

                        character_count++;
                    }
                }

                // now output the float value
                c = temp_buf;
                while ( *c )
                {
                    cgc_putc( *c );
                    character_count++;
                    c++;
                }
                fmt++;
                continue;
            }

            if (*fmt== 's' )  {
                // String
                char *string_arg = va_arg( arg, char * );
                int output_strlen;

                if (precision > 0 && precision < cgc_strlen(string_arg))

                    output_strlen = precision;
                else
                    output_strlen = cgc_strlen(string_arg);


                pad_len = width - output_strlen;

                // pad the output with spaces or zeros
                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            cgc_putc('0');
                        else
                            cgc_putc(' ');

                        character_count++;
                    }
                }

                while ( *string_arg && output_strlen > 0 )
                {
                    cgc_putc( *string_arg );
                    character_count++;
                    string_arg++;
                    --output_strlen;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        cgc_putc(' ');
                        character_count++;
                    }
                }

                fmt++;
                continue;

            }

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




int cgc_vsprintf( char *str, const char *fmt, va_list arg )
{
    int character_count = 0;
    char temp_buf[64];
    int width, precision, zero_padding, left_justification;
    int i;
    int pad_len;

    if ( fmt == NULL )
        return -1;

    while ( *fmt )
    {
        if ( *fmt == '@' )
        {
            fmt++;

            width=0;
            precision=0;
            zero_padding=0;
            left_justification=0;
            pad_len=0;

            
            if (*fmt == '@') {

                str[character_count]='@';
                fmt++;
                character_count++;
                continue;
            }

            if (*fmt == '-') {

                left_justification=1;
                ++fmt;
            }

            if (cgc_isdigit(*fmt)) {

                if (*fmt == '0') {

                    zero_padding = 1;
                    fmt++;
                }

                if (cgc_isdigit(*fmt)) {

                    width = cgc_atoi(fmt);

                    while (cgc_isdigit(*fmt))
                        fmt++;
                }
            }

            if (*fmt == '.') {

                // skip over the '.'
                fmt++;

                precision=cgc_atoi(fmt);

                // now skip past the integer precision value
                while (cgc_isdigit(*fmt))
                    fmt++;

            }

                // single char
            if (*fmt == 'c') {
                
                char c = (char )va_arg(arg, int);

                pad_len = width - 1;

                // justify right 
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            str[character_count]='0';
                        else
                            str[character_count]=' ';

                        character_count++;
                    }
                }

                str[character_count]=c;
                character_count++;

                // justify to the left
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        str[character_count]=' ';
                        character_count++;
                    }
                }

                fmt++;
                continue;
            }

                 // Integer 
            if (*fmt == 'd')  {

                int int_arg = va_arg( arg, int );
                char *c;

                cgc_int_to_str( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - cgc_strlen(temp_buf);

                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            str[character_count]='0';
                        else
                            str[character_count]=' ';

                        character_count++;
                    }
                }

                // now output the integer value
                c = temp_buf;
                while ( *c )
                {
                    str[character_count]=*c;
                    character_count++;
                    c++;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        str[character_count]= ' ';
                        character_count++;
                    }
                }

                fmt++;
                continue;

            }

                // hex
            if ( *fmt == 'x')  {
            
                unsigned int int_arg = va_arg( arg, unsigned int );
                char *c;

                cgc_int_to_hex( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - cgc_strlen(temp_buf);

                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            str[character_count] = '0';
                        else
                            str[character_count] = ' ';

                        character_count++;
                    }
                }

                // now output the hex string
                c = temp_buf;
                while ( *c )
                {
                    str[character_count]=*c;
                    character_count++;
                    c++;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        str[character_count]=' ';
                        character_count++;
                    }
                }

                fmt++;
                continue;
            }

                // Float
            if (*fmt =='f' ) {


                double float_arg = va_arg( arg, double );
                char *c;

                cgc_float_to_str( float_arg, temp_buf, precision);

                // is the output string shorter than the desired width?
                pad_len = width - cgc_strlen(temp_buf);

                // pad the output with spaces or zeros
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            str[character_count]='0';
                        else
                            str[character_count]=' ';

                        character_count++;
                    }
                }

                // now output the float value
                c = temp_buf;
                while ( *c )
                {
                    str[character_count]= *c;
                    character_count++;
                    c++;
                }
                fmt++;
                continue;
            }

            if (*fmt== 's' )  {
                // String
                char *string_arg = va_arg( arg, char * );
                int output_strlen;

                if (precision > 0 && precision < cgc_strlen(string_arg))

                    output_strlen = precision;
                else
                    output_strlen = cgc_strlen(string_arg);


                pad_len = width - output_strlen;

                // pad the output with spaces or zeros
                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            str[character_count]='0';
                        else
                            str[character_count]=' ';
                        character_count++;
                    }
                }

                while ( *string_arg && output_strlen > 0 )
                {
                    str[character_count]= *string_arg;
                    character_count++;
                    string_arg++;
                    --output_strlen;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        str[character_count]=' ';
                        character_count++;
                    }
                }

                fmt++;
                continue;

            }

        }
        else
        {
            str[character_count]= *fmt;
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
    char large_buff[4096];
    cgc_size_t tx_count;

    va_start( arg, fmt );

   // done = vsprintf(large_buff, fmt, arg);
   // transmit( STDOUT, large_buff, done, &tx_count );
    
    done = cgc_vprintf( fmt, arg );
    va_end( arg );

    return done;
}

int cgc_sprintf( char *str, const char *fmt, ... )
{
    va_list arg;
    int done;

    va_start( arg, fmt );
    done = cgc_vsprintf( str, fmt, arg );
    va_end( arg );

    return done;
}
