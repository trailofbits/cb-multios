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

int g_currentWriteFD;
int g_currentReadFD;

void setup_io( int readFD, int writeFD )
{
    // Store the FD for I/O operations
    g_currentReadFD = readFD;
    g_currentWriteFD = writeFD;
}

uint8_t read_u8( void )
{
    int retvalue;
    uint8_t temp;
    size_t rx_count = 1;

    if ( (retvalue = receive( g_currentReadFD, &temp, sizeof(temp), &rx_count )) != 0 )
        _terminate( IO_ERROR_TERMINATE );

    return (temp);
}

uint16_t read_u16( void )
{
    int retvalue;
    uint16_t temp;
    size_t rx_count = 1;

    if ( (retvalue = receive( g_currentReadFD, &temp, sizeof(temp), &rx_count )) != 0 )
        _terminate( IO_ERROR_TERMINATE );

    return (temp);
}

uint32_t read_u32( void )
{
    int retvalue;
    uint32_t temp;
    size_t rx_count = 1;

    if ( (retvalue = receive( g_currentReadFD, &temp, sizeof(temp), &rx_count )) != 0 )
        _terminate( IO_ERROR_TERMINATE );

    return (temp);
}

void write_u8( uint8_t value )
{
    int retvalue;
    size_t tx_bytes = 1;

    if ( (retvalue = transmit( g_currentWriteFD, &value, sizeof(value), &tx_bytes )) != 0 )
        _terminate( IO_ERROR_TERMINATE );
}

void write_u16( uint16_t value )
{
    int retvalue;

    if ( (retvalue = transmit( g_currentWriteFD, &value, sizeof(value), NULL )) != 0 )
        _terminate( IO_ERROR_TERMINATE );
}

void write_u32( uint32_t value )
{
    int retvalue;

    if ( (retvalue = transmit( g_currentWriteFD, &value, sizeof(value), NULL )) != 0 )
        _terminate( IO_ERROR_TERMINATE );
}
