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

#include "mmu.h"

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

CMMU::CMMU( )
{
	for ( uint16_t i = 0; i < MMU_PAGE_COUNT; i++ )
	{
		m_mmuPages[i].pageData = NULL;
		m_mmuPages[i].mmuFlags = MMU_PAGE_NOT_ALLOC;
	}
}

CMMU::~CMMU( )
{
	for ( uint16_t i = 0; i < MMU_PAGE_COUNT; i++ )
	{
		if ( m_mmuPages[i].pageData )
			delete [] m_mmuPages[i].pageData;

		m_mmuPages[i].pageData = NULL;
		m_mmuPages[i].mmuFlags = MMU_PAGE_NOT_ALLOC;
	}
}

bool CMMU::AddMemorySection( uint16_t address, uint8_t *pData, uint16_t dataLen, uint8_t mmuFlags )
{
	address &= 0xFFFE;

	if ( !pData )
		return (false);

	if ( dataLen % MMU_PAGE_SIZE != 0 )
		return (false);

	uint16_t copyRemaining = dataLen;
	uint16_t copyFromPos = 0;

	// Define new section
	while ( copyRemaining > 0 )
	{
		uint16_t mmuPage = ((address+copyFromPos) / MMU_PAGE_SIZE);
		uint16_t pageOffset = ((address+copyFromPos) % MMU_PAGE_SIZE);
		uint16_t copyAmount = copyRemaining;

		if ( copyRemaining > (MMU_PAGE_SIZE - pageOffset) )
			copyAmount = MMU_PAGE_SIZE - pageOffset;

		if ( !m_mmuPages[mmuPage].pageData )
		{
			m_mmuPages[mmuPage].pageData = new uint8_t[MMU_PAGE_SIZE];
	
			bzero( m_mmuPages[mmuPage].pageData, MMU_PAGE_SIZE );	
		}

		m_mmuPages[mmuPage].mmuFlags |= mmuFlags;
	
		// Copy in the data
		memcpy( m_mmuPages[mmuPage].pageData+pageOffset, pData+copyFromPos, copyAmount );

		// Update copy positions
		copyFromPos += copyAmount;
		copyRemaining -= copyAmount;
	}

	return (true);
}

bool CMMU::Fetch16( uint16_t address, uint16_t &value )
{
	address &= 0xFFFE;

	uint16_t mmuPage = (address / MMU_PAGE_SIZE);
	uint16_t pageOffset = (address % MMU_PAGE_SIZE);

	// No need to worry about straddling a page -- just make the lookup
	if ( !(m_mmuPages[mmuPage].mmuFlags & MMU_PAGE_EXEC) )
		return (false);	// Cannot exec!

	value = *(uint16_t*)&(m_mmuPages[mmuPage].pageData[pageOffset]);

	return (true);
}

bool CMMU::Read16( uint16_t address, uint16_t &value )
{
	address &= 0xFFFE;

	uint16_t mmuPage = (address / MMU_PAGE_SIZE);
	uint16_t pageOffset = (address % MMU_PAGE_SIZE);

	// No need to worry about straddling a page -- just make the lookup
	if ( !(m_mmuPages[mmuPage].mmuFlags & MMU_PAGE_READ) )
		return (false);	// Cannot exec!
	
	value = *(uint16_t*)&(m_mmuPages[mmuPage].pageData[pageOffset]);

	return (true);
}

bool CMMU::Write16( uint16_t address, uint16_t value )
{
	address &= 0xFFFE;

	uint16_t mmuPage = (address / MMU_PAGE_SIZE);
	uint16_t pageOffset = (address % MMU_PAGE_SIZE);

	// No need to worry about straddling a page -- just make the lookup
	if ( !(m_mmuPages[mmuPage].mmuFlags & MMU_PAGE_WRITE) )
		return (false);	// Cannot exec!

	*(uint16_t*)&(m_mmuPages[mmuPage].pageData[pageOffset]) = value;

	return (true);
}

bool CMMU::ReadDMA( uint16_t address, uint8_t *pData, uint16_t amount )
{
	uint16_t offset = 0;

	while ( amount > 0 )
	{
		uint16_t mmuPage = ((address+offset) / MMU_PAGE_SIZE);
		uint16_t pageOffset = ((address+offset) % MMU_PAGE_SIZE);

		// No need to worry about straddling a page -- just make the lookup
		if ( !(m_mmuPages[mmuPage].mmuFlags & MMU_PAGE_READ) )
			return (false);	// Cannot exec!

		uint16_t amountToRead = amount;
		if ( pageOffset+amountToRead > MMU_PAGE_SIZE )
			amountToRead = (MMU_PAGE_SIZE - (pageOffset+amountToRead));

		memcpy( pData+offset, m_mmuPages[mmuPage].pageData+pageOffset, amountToRead );

		offset += amountToRead;
		amount -= amountToRead;
	}

	return (true);
}

bool CMMU::WriteDMA( uint16_t address, uint8_t *pData, uint16_t amount )
{
	uint16_t offset = 0;

	while ( amount > 0 )
	{
		uint16_t mmuPage = ((address+offset) / MMU_PAGE_SIZE);
		uint16_t pageOffset = ((address+offset) % MMU_PAGE_SIZE);
		
		// No need to worry about straddling a page -- just make the lookup
		if ( !(m_mmuPages[mmuPage].mmuFlags & MMU_PAGE_WRITE) )
			return (false);	// Cannot exec!

		uint16_t amountToWrite = amount;
		if ( pageOffset+amountToWrite > MMU_PAGE_SIZE )
			amountToWrite = (MMU_PAGE_SIZE - (pageOffset+amountToWrite));

		memcpy( m_mmuPages[mmuPage].pageData+pageOffset, (pData+offset), amountToWrite );

		offset += amountToWrite;
		amount -= amountToWrite;
	}

	return (true);
}
