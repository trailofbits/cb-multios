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
#include <libcgc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
}

#include "nor_flash.h"

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

CNORFlash::CNORFlash( )
	: m_pFlashMemory( NULL ), m_blockSize( 0 ), m_blocksPerSector( 0 ), m_sectorCount( 0 )
{

}

CNORFlash::~CNORFlash( )
{
	if ( m_pFlashMemory )
	{
		uint32_t memorySize = (m_blockSize * m_blocksPerSector * m_sectorCount);

		if ( deallocate( m_pFlashMemory, memorySize ) != 0 )
			_terminate( -1 );
	}
}

void CNORFlash::Init( uint32_t blockSize, uint32_t blocksPerSector, uint32_t sectorCount )
{
	if ( blockSize % 64 != 0 )
		m_blockSize = ((blockSize / 64)+1) * 64;
	else
		m_blockSize = blockSize;

	if ( m_blockSize > MAX_BLOCK_SIZE )
		m_blockSize = MAX_BLOCK_SIZE;

	if ( blocksPerSector > MAX_BLOCKS_PER_SECTOR )
		m_blocksPerSector = MAX_BLOCKS_PER_SECTOR;
	else
		m_blocksPerSector = blocksPerSector;

	if ( sectorCount > MAX_SECTOR_COUNT )
		m_sectorCount = MAX_SECTOR_COUNT;
	else
		m_sectorCount = sectorCount;		

	uint32_t memorySize = (m_blockSize * m_blocksPerSector * m_sectorCount);

	// Allocate
	if ( allocate( memorySize, 0, (void **)&m_pFlashMemory ) != 0 )
		_terminate( -1 );	// Allocate failed

	// Flash memory -- erase to all 1's
	memset( m_pFlashMemory, 0xFF, memorySize );
}

int32_t CNORFlash::WriteData( uint32_t address, uint8_t *pData, uint32_t dataLen )
{
	if ( m_pFlashMemory == NULL )
		return (FLASH_NO_MEMORY);

	uint32_t memorySize = (m_blockSize * m_blocksPerSector * m_sectorCount);

	if ( (address+dataLen) > memorySize )
		return (FLASH_INVALID_ADDRESS);

	// Simulate a write to flash -- IE: we can only set bits to 0 -- they cannot be reset to 1
	uint32_t curPos = 0;	
	while ( dataLen > 0 )
	{
		m_pFlashMemory[address] &= pData[curPos];

		address++;
		curPos++;
		dataLen--;
	}	

	return (curPos);	
}

int32_t CNORFlash::ReadData( uint32_t address, uint8_t *pData, uint32_t dataLen )
{
	if ( m_pFlashMemory == NULL )
		return (FLASH_NO_MEMORY);

	uint32_t memorySize = (m_blockSize * m_blocksPerSector * m_sectorCount);

	if ( (address+dataLen) > memorySize )
		return (FLASH_INVALID_ADDRESS);

	// Simulate a write to flash -- IE: we can only set bits to 0 -- they cannot be reset to 1
	uint32_t curPos = 0;	
	while ( dataLen > 0 )
	{
		pData[curPos] = m_pFlashMemory[address];

		address++;
		curPos++;
		dataLen--;
	}	

	return (curPos);	
}

int32_t CNORFlash::DeviceErase( void )
{
	uint32_t memorySize = (m_blockSize * m_blocksPerSector * m_sectorCount);

	// Flash memory -- erase to all 1's
	memset( m_pFlashMemory, 0xFF, memorySize );

	return (FLASH_SUCCESS);
}

int32_t CNORFlash::SectorErase( uint32_t sectorNum )
{
	if ( sectorNum >= m_sectorCount )
		return (FLASH_INVALID_SECTOR);

	// Get sector address
	uint32_t sectorSize = (m_blockSize * m_blocksPerSector);

	uint32_t sectorAddress = (sectorSize * sectorNum);

	// Erase sector (All 1's)
	memset( (m_pFlashMemory+sectorAddress), 0xFF, sectorSize );	

	return (FLASH_SUCCESS);
}

int32_t CNORFlash::BlockErase( uint32_t blockNum )
{
	uint32_t blocksTotal = (m_blocksPerSector * m_sectorCount);

	if ( blockNum >= blocksTotal )
		return (FLASH_INVALID_BLOCK);

	// Erase block (All 1's)
	memset( (m_pFlashMemory+(m_blockSize*blockNum)), 0xFF, m_blockSize );

	return (FLASH_SUCCESS);
}
