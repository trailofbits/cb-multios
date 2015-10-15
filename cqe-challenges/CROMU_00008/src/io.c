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
#include <stdlib.h>
#include <libcgc.h>
#include "io.h"

int g_lasterror = 0;

int readLine( int fd, char *buffer, size_t maxlen )
{
    size_t pos;
    char temp_buffer[2];
    int retvalue;
    size_t rx_count;

    for ( pos = 1; pos < maxlen; pos++ )
    {
        if ( (retvalue = receive( fd, (void *)temp_buffer, 1, &rx_count)) != 0 )
        {
            g_lasterror = retvalue;
            return (-1);
        }
        else
        {
            if ( temp_buffer[0] == '\n' )
                break;

            buffer[0] = temp_buffer[0];
            buffer++;
        }
    }

    buffer[0] = '\0';
    return pos;
}

char *sanitize_string( char *str )
{
    char *str_start = str;
    char c;

    while ( (c = *str) )
    {
        if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
             (c >= '0' && c <= '9') )
            ;
        else
            *str = '_';

        str++;
    }

    return str_start;
}
