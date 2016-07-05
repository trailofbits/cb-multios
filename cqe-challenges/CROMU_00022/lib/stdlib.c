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
#include <stdarg.h>
#include <mymath.h>


#define F32_PRECISION       0.00001


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

    unsigned long long int integer_part = 0;
    int sign = 1;
    int part;
    int digit_count = 0;
    int retval;

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

                if ( digit_count == 10 )
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
    if ( integer_part <= 2147483647 ){
        retval = (signed long int)integer_part;
        retval = sign * retval;
    return retval;
    }else {
    return 0;
    }
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

char *strncpy( char *dest, const char *src, size_t n )
{
    size_t i;

    for ( i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
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

void *memset(void *s, int c, size_t n)
{
    unsigned char *t = (unsigned char *)s;
    while (--n)
        t[n] = (unsigned char)c;
    t[n] = (unsigned char)c;
    return(s);
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

size_t receive_until_flush( char *dst, char delim, size_t max )
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
    //consume any extra input to delim
    while ( receive( STDIN, &c, 1, &rx ) == 0 ){
        if ( c == delim ){
            goto end;
        }
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
    transmit(STDOUT, "\n", 1, &size);
}

char *strchr(const char *s, int c) {
	while (*s != '\0') {
		if (*s == c) {
			return((char *)s);
		}
		s++;
	}
	if (*s == c) {
		return((char *)s);
	}
	return(NULL);
}

char *token = NULL;
char *prev_str = NULL;
unsigned int prev_str_len = 0;
char *prev_str_ptr = NULL;
char *strtok(char *str, const char *delim) {
	char *start;
	char *end;
	char *t;
	int i;

	// invalid input
	if (delim == NULL) {
		return(NULL);
	}
	
	// called on existing string
	if (str == NULL) {
		if (prev_str == NULL) {
			return(NULL);
		}
		// already parsed through end of original str
		if (prev_str_ptr >= prev_str+prev_str_len) {
			return(NULL);
		}
	} else {
		// called with new string, so free the old one
		if (prev_str) {
			deallocate(prev_str, prev_str_len);
			prev_str = NULL;
			prev_str_len = 0;
			prev_str_ptr = NULL;
		}
	}

	// not been called before, so make a copy of the string
	if (prev_str == NULL) {
		if (strlen(str) > 4096) {
			// too big
			return(NULL);
		} 
		prev_str_len = strlen(str);
		if (allocate(prev_str_len, 0, (void *)&prev_str)) {
			return(NULL);
		}
		strcpy(prev_str, str);
		prev_str_ptr = prev_str;
	}

	str = prev_str_ptr;

	// make sure the string isn't starting with a delimeter
	while (strchr(delim, str[0]) && str < prev_str+prev_str_len) {
		str++;
	}
	if (str >= prev_str+prev_str_len) {
		return(NULL);
	}

	// find the earliest next delimiter
	start = str;
	end = str+strlen(str);
	for (i = 0; i < strlen((char *)delim); i++) {
		if ((t = strchr(start, delim[i]))) {
			if (t != NULL && t < end) {
				end = t;
			}
		}
	}
	
	// populate the new token
	token = start;
	*end = '\0';

	prev_str_ptr = end+1;

	return(token);
}

ssize_t write( const void *buf, size_t count )
{
	size_t size;

	transmit(STDOUT, buf, count, &size);

	if (count != size)
		return(-1);

	return(size);

}

char *strdup(char *s) 
{
        char *retval;

        if (!s) {
                return(NULL);
        }

        if (allocate(strlen(s)+1, 0, (void *)&retval)) {
                return(NULL);
        }

        bzero(retval, strlen(s)+1);
        strcpy(retval, s);

        return(retval);
}

int putc( int c )
{
    size_t tx_count;

    if ( transmit( STDOUT, &c, 1, &tx_count ) != 0 )
        _terminate(2);

    return c;
}

void int_to_str( int val, char *buf )
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

void int_to_hex( unsigned int val, char *buf )
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

void float_to_str( double val, char *buf, int precision )
{
    if ( buf == NULL )
        return;

    if ( isnan( val ) )
    {
        strcpy( buf, "nan" );
    }
    else if ( isinf( val ) )
    {
        strcpy( buf, "inf" );
    }
    else if ( val == 0.0 )
    {
        strcpy( buf, "0.00000" );
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
        m = log10( val );

        if ( m < 1.0 )
            m = 0;

        fraction_digit = 0;
        in_fraction = 0;
        while ( val > F32_PRECISION || m >= 0 )
        {
            double weight = pow( 10.0, m );
            if ( weight > 0 && !isinf(weight) )
            {
                digit = floor( val / weight );
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

int vprintf( const char *fmt, va_list arg )
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

                putc('@');
                fmt++;
                character_count++;
                continue;
            }

            if (*fmt == '-') {

                left_justification=1;
                ++fmt;
            }

            if (isdigit(*fmt)) {

                if (*fmt == '0') {

                    zero_padding = 1;
                    fmt++;
                }

                if (isdigit(*fmt)) {

                    width = atoi(fmt);

                    // skip past the width specification
                    while (isdigit(*fmt))
                        fmt++;
                }
            }

            if (*fmt == '.') {

                // skip over the '.'
                fmt++;

                precision=atoi(fmt);

                // now skip past the integer precision value
                while (isdigit(*fmt))
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
                            putc('0');
                        else
                            putc(' ');

                        character_count++;
                    }
                }

                // output the char itself
                putc(c);
                character_count++;

                // justify to the left
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        putc(' ');
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

                int_to_str( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - strlen(temp_buf);

                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            putc('0');
                        else
                            putc(' ');

                        character_count++;
                    }
                }

                // now output the integer value
                c = temp_buf;
                while ( *c )
                {
                    putc( *c );
                    character_count++;
                    c++;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        putc(' ');
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

                int_to_hex( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - strlen(temp_buf);

                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            putc('0');
                        else
                            putc(' ');

                        character_count++;
                    }
                }

                // now output the hex string
                c = temp_buf;
                while ( *c )
                {
                    putc( *c );
                    character_count++;
                    c++;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        putc(' ');
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

                float_to_str( float_arg, temp_buf, precision);

                // is the output string shorter than the desired width?
                pad_len = width - strlen(temp_buf);

                // pad the output with spaces or zeros
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            putc('0');
                        else
                            putc(' ');

                        character_count++;
                    }
                }

                // now output the float value
                c = temp_buf;
                while ( *c )
                {
                    putc( *c );
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

                if (precision > 0 && precision < strlen(string_arg))

                    output_strlen = precision;
                else
                    output_strlen = strlen(string_arg);


                pad_len = width - output_strlen;

                // pad the output with spaces or zeros
                // right justification
                if (!left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        if (zero_padding)
                            putc('0');
                        else
                            putc(' ');

                        character_count++;
                    }
                }

                while ( *string_arg && output_strlen > 0 )
                {
                    putc( *string_arg );
                    character_count++;
                    string_arg++;
                    --output_strlen;
                }

                // left justification
                if (left_justification) {
                    for (i=0; i< pad_len; ++i) {

                        // the option to pad with 0 is ignored when left justified
                        putc(' ');
                        character_count++;
                    }
                }

                fmt++;
                continue;

            }

        }
        else
        {
            putc( *fmt );
            fmt++;

            character_count++;
        }
    }

    return (character_count);
}




int vsprintf( char *str, const char *fmt, va_list arg )
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

            if (isdigit(*fmt)) {

                if (*fmt == '0') {

                    zero_padding = 1;
                    fmt++;
                }

                if (isdigit(*fmt)) {

                    width = atoi(fmt);

                    while (isdigit(*fmt))
                        fmt++;
                }
            }

            if (*fmt == '.') {

                // skip over the '.'
                fmt++;

                precision=atoi(fmt);

                // now skip past the integer precision value
                while (isdigit(*fmt))
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

                int_to_str( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - strlen(temp_buf);

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

                int_to_hex( int_arg, temp_buf );

                // is the output string shorter than the desired width?
                pad_len = width - strlen(temp_buf);

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

                float_to_str( float_arg, temp_buf, precision);

                // is the output string shorter than the desired width?
                pad_len = width - strlen(temp_buf);

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

                if (precision > 0 && precision < strlen(string_arg))

                    output_strlen = precision;
                else
                    output_strlen = strlen(string_arg);


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

int printf( const char *fmt, ... )
{
    va_list arg;
    int done;
    char large_buff[4096];
    size_t tx_count;

    va_start( arg, fmt );

   // done = vsprintf(large_buff, fmt, arg);
   // transmit( STDOUT, large_buff, done, &tx_count );
    
    done = vprintf( fmt, arg );
    va_end( arg );

    return done;
}

int sprintf( char *str, const char *fmt, ... )
{
    va_list arg;
    int done;

    va_start( arg, fmt );
    done = vsprintf( str, fmt, arg );
    va_end( arg );

    return done;
}


/*
heap_metadata *heap_manager = NULL;


void *calloc(size_t count, size_t size) {
    void *ret;
    ret = malloc(size * count);
    memset(ret, 0, size * count);
    return ret;
}

void free(void *ptr) {
    heap_header *chunkHeader;
    heap_block_header *blockHead;

    chunkHeader = (heap_header*)(((char*)ptr)-sizeof(heap_header));
    chunkHeader->flags = FREE_FLAG;
    blockHead = (heap_block_header *)((int)&ptr & 0xfffff000);
    blockHead->remaining_size+=chunkHeader->size;
    return;
}

void *malloc(size_t size) {
    heap_block_header *blockHead;
    if (heap_manager == NULL) {
        void *mallocPtr;
        //this is our first allocation.
        allocate(4096, 0, &mallocPtr);
        heap_manager = mallocPtr;
        heap_manager->mem_commit = 4096;
        heap_manager->mem_inuse = sizeof(heap_manager);
        heap_manager->mem_free = 4096-heap_manager->mem_inuse;
        allocate(4096, 0, (void *)&heap_manager->blocks);
        memset(heap_manager->blocks, 0, 4096);
        blockHead = (heap_block_header *)heap_manager->blocks;
        blockHead->remaining_size = 4096-sizeof(heap_block_header);
        blockHead->next = NULL;
    }
    blockHead = (heap_block_header *)heap_manager->blocks;
    if(size > blockHead->remaining_size) {
        allocate(4096, 0, (void *)&blockHead->next);
        if(blockHead->next == NULL) {
            puts("Not enough space available to allocate more heap.  Failure.");
            _terminate(-1);
        }
        blockHead = blockHead->next;
        blockHead->remaining_size = 4096-sizeof(heap_block_header);
    } else {
        heap_header *chunkHeader;
        blockHead->remaining_size-=size;
        chunkHeader = (heap_header *)blockHead->data;

        while((chunkHeader->flags & INUSE_FLAG) && (chunkHeader->size < size+sizeof(heap_header)))
            chunkHeader = (heap_header *)(((void *)(chunkHeader)+sizeof(heap_header)) + chunkHeader->size);
        chunkHeader->size = size;
        chunkHeader->flags = INUSE_FLAG;
        return (char *)chunkHeader+sizeof(heap_header);
    }
    return 0;
}

*/
