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
#include "common.h"

CDataStream::CDataStream()
    : m_bitpos( 0 ), m_bytesRxCount( 0 )
{

}

CDataStream::~CDataStream()
{

}

void CDataStream::Setup( int32_t socketNumber )
{
    m_socketNumber = socketNumber;
    m_bitpos = 0;
    m_buffer = 0;
}

uint8_t CDataStream::ReadBit( void )
{
    uint8_t value = 0;

    if ( m_bitpos >= 8 )
        RefillBuffer();

    value = (m_buffer & (1<<(7-m_bitpos))) >> (7-m_bitpos);

    m_bitpos++;

    return (value);
}

uint8_t CDataStream::ReadByte( void )
{
    uint8_t value = 0;
    uint8_t idx;

    for ( idx = 0; idx < 8; idx++ )
        value |= (ReadBit() << (7-idx));

    return (value);
}

void CDataStream::RefillBuffer( void )
{
    int32_t retvalue;
    uint8_t value;
    size_t rx_count = 1;

    if ( m_bytesRxCount >= MAX_BYTES_RECEIVED )
        _terminate( 0 );

    if  ( (retvalue = receive( m_socketNumber, &value, 1, &rx_count )) != 0 )
        _terminate( -1 );

    if ( rx_count != 1 )
        _terminate( -1 );

    m_bytesRxCount++;

    m_buffer = value;
    m_bitpos = 0;
}
