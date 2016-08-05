/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
extern "C"
{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#include "peripheral.h"

CPeripheral::CPeripheral( uint8_t peripheralID )
	: m_peripheralID( peripheralID )
{

}

CPeripheral::~CPeripheral( )
{

}

CSendDevice::CSendDevice( uint8_t peripheralID )
	: CPeripheral( peripheralID )
{

}

CSendDevice::~CSendDevice( )
{

}

bool CSendDevice::Init( void )
{

	return (true);
}

bool CSendDevice::Read( uint8_t *pDest, uint16_t length )
{
	// Does nothing
	return (true);
}

bool CSendDevice::Write( uint8_t *pDest, uint16_t length )
{
	if ( !pDest )
		return (false);

	uint32_t writePos = 0;
	while ( writePos < length )
	{
		size_t tx_bytes;
		uint32_t writeRemaining = (length - writePos);

		if ( transmit( STDOUT, (const void *)(pDest + writePos), writeRemaining, &tx_bytes ) != 0 )
		      _terminate( -1 );

		if ( tx_bytes == 0 )
			_terminate( -1 );

		writePos += tx_bytes;		
	}

	return (true);
}

CReadDevice::CReadDevice( uint8_t deviceID )
	: CPeripheral( deviceID )
{

}

CReadDevice::~CReadDevice( )
{

}

bool CReadDevice::Init( void )
{

	return (true);
}

bool CReadDevice::Read( uint8_t *pDest, uint16_t length )
{
	if ( !pDest )
		return (false);

	uint32_t readPos = 0;
	while ( readPos < length )
	{
		size_t rx_bytes;
		uint32_t readRemaining = (length - readPos);

		if ( receive( STDIN, (void *)(pDest + readPos), readRemaining, &rx_bytes ) != 0 )
		      _terminate( -1 );

		if ( rx_bytes == 0 )
			_terminate( -1 );

		readPos += rx_bytes;		
	}

	return (true);
}

bool CReadDevice::Write( uint8_t *pDest, uint16_t length )
{
	// Does nothing
	return (true);
}
