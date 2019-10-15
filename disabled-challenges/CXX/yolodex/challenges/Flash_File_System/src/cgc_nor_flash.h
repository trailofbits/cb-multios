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
#ifndef __NOR_FLASH_H__
#define __NOR_FLASH_H__

#define MAX_BLOCK_SIZE	(512)
#define MAX_BLOCKS_PER_SECTOR	(16)
#define MAX_SECTOR_COUNT	(256)

#define FLASH_SUCCESS	(0)
#define FLASH_INVALID_BLOCK	(-1)
#define FLASH_INVALID_SECTOR	(-2)
#define FLASH_NO_MEMORY		(-3)
#define FLASH_INVALID_ADDRESS	(-4)

// Class to simulate the behavior of NOR Flash
class CNORFlash
{
public:
	CNORFlash( );
	~CNORFlash( );

	void Init( uint32_t blockSize, uint32_t blocksPerSector, uint32_t sectorCount );

	int32_t WriteData( uint32_t address, uint8_t *pData, uint32_t dataLen );
	int32_t ReadData( uint32_t address, uint8_t *pData, uint32_t dataLen );	

	int32_t DeviceErase( void );
	int32_t SectorErase( uint32_t sectorNum );
	int32_t BlockErase( uint32_t blockNum );

	uint32_t GetBlockSize( void ) const { return m_blockSize; };
	uint32_t GetBlocksPerSector( void ) const { return m_blocksPerSector; };
	uint32_t GetSectorCount( void ) const { return m_sectorCount; };

private:
	uint8_t *m_pFlashMemory;
	uint32_t m_blockSize;
	uint32_t m_blocksPerSector;
	uint32_t m_sectorCount;
};

#endif // __NOR_FLASH_H__
