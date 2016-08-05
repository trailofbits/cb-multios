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
#ifndef __FLASH_FS_H__
#define __FLASH_FS_H__

#include "nor_flash.h"

#define RECENT_FILE_TABLE_SIZE		(8)

// Adjust this value to change the maximum number of open file descriptors
#define MAX_FILE_DESCRIPTORS		(16)
#define MAX_FILES			(128)

#define OBJ_ID_UNUSED_FD		(0xFFFF)

#define FD_NOT_FOUND		(-1)

#define OPEN_MODE_READ		(1)
#define OPEN_MODE_WRITE		(2)
#define OPEN_MODE_APPEND	(4)

#define OPEN_FILE_NOT_FOUND	(-1)
#define OPEN_FILE_OUT_OF_SPACE	(-2)
#define OPEN_FILE_MAX_FD	(-3)
#define OPEN_FILE_ALREADY_OPEN	(-4)

#define CLOSE_BAD_FD		(-1)

#define FLASH_FS_VERSION	(0xC1)

#define OBJ_NOT_INIT	(0xFF)
#define OBJ_CLAIM	(0x04)
#define OBJ_ERASE	(0x01)
#define OBJ_INUSE	(0x02)

// A flash file system
class CFlashFS
{
public:
	CFlashFS( );
	~CFlashFS( );

	bool Init( CNORFlash *pFlash );

	int32_t WriteFile( int32_t fd, uint8_t *pData, uint32_t dataLen );
	int32_t ReadFile( int32_t fd, uint8_t *pData, uint32_t dataLen );

	int32_t DeleteFile( const char *pszFilename );

	int32_t OpenFile( const char *pszFilename, uint8_t openAttributes );
	int32_t CloseFile( int32_t fd );
	

protected:
	// Header for the entire flash FS
	typedef struct FLASH_FS_HEADER
	{
		uint8_t version;
		uint16_t fileTableBlockIdx;
		uint16_t fileTableBlockOffset;
	} __attribute__((packed)) tFlashFSHdr;

	typedef struct FLASH_FILE_TABLE_OBJ
	{
		uint8_t objBits;	// Current state (INUSE, ERASE, UNINIT)
		uint16_t objID;		// ID for header block
	} __attribute__((packed)) tFlashFileTableObj;

	typedef struct FLASH_FILE_HEADER
	{
		uint8_t objBits;	// Current state (INUSE, ERASE, UNINIT)
		uint16_t dataID;	// Same as the block index -- every file is a block on the device
		uint32_t objSize;	// The size of the object (file size)
		uint8_t fileNameLen;
	} __attribute__((packed)) tFlashFileHdr;

	typedef struct FLASH_DATA_HEADER
	{
		uint8_t objBits;	// Current state (INUSE, ERASE, UNINIT)
		uint16_t prevDataID;	// Prev ID for data object
		uint16_t nextDataID;	// Next ID for data object
	} __attribute__((packed)) tFlashDataHdr;

	typedef struct FLASH_SECTOR_HEADER
	{
		uint16_t sectorMask;	
	} __attribute__((packed)) tFlashSectorHeader;

	typedef struct FILE_DESCRIPTOR_TABLE
	{
		uint16_t hdrID;		// Same as a block index -- every file is a block on the device
		uint32_t filePos;
	} tFileDescriptorTable;

	typedef struct FILE_TABLE_STRUCT
	{
		uint16_t fileTableID;
		uint16_t hdrID;
	} tFileTableData;

protected:
	bool FindFileDescriptorData( int16_t fd, tFileDescriptorTable *pFDData );

	bool FindFileInFlashTable( const char *pszFilename, uint16_t *pObjID, uint32_t *pObjSize );

	uint32_t GetFileTableAddress( void );

	bool CreateNewFile( const char *pszFilename, uint16_t *pObjID, uint32_t *pObjSize );

	uint32_t GetAddressForHeaderID( uint16_t objID );
	uint32_t GetAddressForFileTableID( uint16_t objID );
	uint32_t GetAddressForDataID( uint16_t objID );
	uint32_t GetAddressForSector( uint16_t sectorNum );

	uint16_t GetNewFileTableID( void );
	uint16_t GetNewObjHeaderID( void );

	uint16_t GetNextDataBlockID( void );

	bool CleanFileTable( void );
	bool CleanObjHeaderTable( void );
	bool CleanDataBlocks( void );

	uint16_t GetNextScratchSector( void );

	bool CreateNewObject( const char *pszObjectName, uint16_t fileTableID, uint16_t hdrID );

	int32_t GetNewFileDescriptor( void );

private:
	uint8_t m_tempBlock[512];

	CNORFlash *m_pFlash;

	// Max file descriptors available
	tFileDescriptorTable m_fileDescriptorTable[MAX_FILE_DESCRIPTORS];

	uint16_t m_fileDescriptorCount;

	tFlashFSHdr m_fsHdr;
	uint32_t m_fileTableAddress;

	tFileTableData m_fileTable[MAX_FILES];
	uint16_t m_fileTableCount;
	uint16_t m_fileTableIDNext;

	uint16_t m_fileTableIDMax;
	uint16_t m_objHeaderIDMax;

	uint16_t m_objHeaderIDNext;
	uint16_t m_scratchSectorCur;	// Current scratch sector

	uint16_t m_lastDataBlockID;
	uint16_t m_maxDataBlockID;	// Max data block ID
};

#endif // __FLASH_FS_H__
