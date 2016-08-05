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
#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

#include <cutil_list.h>

class CPeripheral
{
public:
	CPeripheral( uint8_t peripheralID );
	virtual ~CPeripheral( );

	virtual bool Init( void ) = 0;
	virtual bool Read( uint8_t *pDest, uint16_t length ) = 0;
	virtual bool Write( uint8_t *pDest, uint16_t length ) = 0;

	uint8_t GetPeripheralID( void ) const { return m_peripheralID; };

private:
	uint8_t m_peripheralID;

public:
	CUtil::DLL_LINK( CPeripheral ) m_peripheralListLink;
};

class CSendDevice : public CPeripheral
{
public:
	CSendDevice( uint8_t peripheralID );
	~CSendDevice( );

	bool Init( void );
	bool Read( uint8_t *pDest, uint16_t length );
	bool Write( uint8_t *pDest, uint16_t length );

private:
};

class CReadDevice : public CPeripheral
{
public:
	CReadDevice( uint8_t peripheralID );
	~CReadDevice( );

	bool Init( void );
	bool Read( uint8_t *pDest, uint16_t length );
	bool Write( uint8_t *pDest, uint16_t length );

private:
};

#endif // __PERIPHERAL_H__
