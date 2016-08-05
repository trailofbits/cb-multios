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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
}

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

// #define FLASH_DEBUG_MODE	(1)

#include "flash_fs.h"
	
CFlashFS::CFlashFS( )
	: m_pFlash( NULL ), m_fileTableAddress( 0 )
{

}

CFlashFS::~CFlashFS( )
{

}

bool CFlashFS::Init( CNORFlash *pFlash )
{
	bool bFlashErased = false;

	if ( !pFlash )
		return (false);

	if ( pFlash->GetSectorCount() < 16 )
		return (false);

	m_pFlash = pFlash;

	for ( uint32_t i = 0; i < MAX_FILE_DESCRIPTORS; i++ )
	{
		m_fileDescriptorTable[i].filePos = 0;
		m_fileDescriptorTable[i].hdrID = OBJ_ID_UNUSED_FD;
	}

	// Reset file descriptor count
	m_fileDescriptorCount = 0;

	// Read in file system header
	tFlashFSHdr oFSHdr;

	if ( m_pFlash->ReadData( 0, (uint8_t*)&oFSHdr, sizeof(oFSHdr) ) != sizeof(oFSHdr) )
		return (false);

	// Check version
	if ( oFSHdr.version == 0xFF )
	{
		// Erased device
		oFSHdr.version = FLASH_FS_VERSION;
		oFSHdr.fileTableBlockIdx = 0;	// Default position
		oFSHdr.fileTableBlockOffset = sizeof(oFSHdr);

		// Write it to flash
		if ( m_pFlash->WriteData( 0, (uint8_t*)&oFSHdr, sizeof(oFSHdr) ) != sizeof(oFSHdr) )
		{
			// Write error
			return (false);
		}

		bFlashErased = true;
	}
	
	memcpy( (void *)&m_fsHdr, (void *)&oFSHdr, sizeof(oFSHdr) );

	// Get the file table address
	m_fileTableAddress = (oFSHdr.fileTableBlockIdx * m_pFlash->GetBlockSize()) + oFSHdr.fileTableBlockOffset;

	// Sector 1 -- file table
	// Sector 2, 3, and 4 -- object table
	// Sector 5 -> (end-4) -- file data
	// Sector end-4 -> end -- scratch area

	// Find maximum file table size and header table size
	m_fileTableIDMax = ((m_pFlash->GetBlockSize() * m_pFlash->GetBlocksPerSector()) - m_fileTableAddress) / sizeof(tFlashFileTableObj);

	// Find maximum object header ID
	m_objHeaderIDMax = ((m_pFlash->GetBlockSize() * m_pFlash->GetBlocksPerSector() * 3) / sizeof(tFlashFileHdr));

	// Scratch sector setup -- the last 4 sectors are used for scratch
	m_scratchSectorCur = m_pFlash->GetSectorCount() - 4;

	// Calculate the maximum block ID for data blocks
	m_maxDataBlockID = (m_pFlash->GetBlocksPerSector() * (m_pFlash->GetSectorCount() - 4));

	// Clear scratch
	m_pFlash->SectorErase( m_scratchSectorCur );

	// Load files from file table
	m_fileTableCount = 0;
	m_fileTableIDNext = 0;

	// Remember last object header ID
	m_objHeaderIDNext = 0;

	// Clean file table
	for ( uint32_t i = 0; i < MAX_FILES; i++ )
	{
		m_fileTable[i].fileTableID = 0xFFFF;
		m_fileTable[i].hdrID = 0xFFFF;
	}

	uint32_t curAddress = m_fileTableAddress;	
	while ( true )
	{
		// Read first entry in file table
		tFlashFileTableObj oFileTableObj;

		if ( m_pFlash->ReadData( curAddress, (uint8_t*)&oFileTableObj, sizeof(oFileTableObj) ) != sizeof(oFileTableObj) )
		{
			// Read error
			return (false);
		}	

		if ( oFileTableObj.objBits == OBJ_NOT_INIT )
			break;

		if ( oFileTableObj.objBits == OBJ_ERASE )
			;	// Ignore
		else if ( oFileTableObj.objBits == OBJ_INUSE )
		{
			m_fileTable[m_fileTableCount].hdrID = oFileTableObj.objID;
			m_fileTable[m_fileTableCount].fileTableID = m_fileTableIDNext;

			m_fileTableCount++;

			if ( oFileTableObj.objID > m_objHeaderIDNext )
				m_objHeaderIDNext = oFileTableObj.objID;

			if ( m_fileTableCount >= MAX_FILES )
				return (false);
		}
		else
			return (false); // Unknown

		m_fileTableIDNext++;
	}

	if ( bFlashErased )
		m_lastDataBlockID = 0;
	else
	{
		// Find a new data block ID
		uint16_t dataBlockID = 0;
		do
		{
			// Check for overrun
			if ( dataBlockID >= m_maxDataBlockID )
			{
				// No free data blocks! FLASH FULL
				return (false);
			}		
				
			uint32_t address = GetAddressForDataID( dataBlockID );

			// Read data block
			uint8_t readBits;
		
			if ( m_pFlash->ReadData( address, (uint8_t*)&readBits, 1 ) != 1 )
			{
				// Read error
				return (false);
			}

			if ( readBits == OBJ_NOT_INIT )
				break;

			dataBlockID++;
		} while ( true );

		// Remember last data block ID
		m_lastDataBlockID = dataBlockID;
	}

	// Move to the next object
	m_objHeaderIDNext++;
	
	return (true);
}
	
int32_t CFlashFS::WriteFile( int32_t fd, uint8_t *pData, uint32_t dataLen )
{
	// Find file descriptor
	tFileDescriptorTable oFDData;

	if ( !FindFileDescriptorData( fd, &oFDData ) )
	{
		// FD not found
		return (FD_NOT_FOUND);
	}

	// Write to file
	uint16_t hdrID = oFDData.hdrID;

	tFlashFileHdr oHdrData;

	uint32_t hdrAddress = GetAddressForHeaderID( hdrID );

	if ( m_pFlash->ReadData( hdrAddress, (uint8_t*)&oHdrData, sizeof(oHdrData) ) != sizeof(oHdrData) )
	{
		// Read failure
		return (-1);
	}

	// Find proper position to write to
	uint16_t dataID = oHdrData.dataID;

	uint32_t filePos = oFDData.filePos;

	if ( filePos > oHdrData.objSize )
	{
		// Error
#if FLASH_DEBUG_MODE
		printf( "FS ERR: File position past file size\n" );
#endif
		filePos = oHdrData.objSize;
	}

	// Remember file size
	uint32_t fileSize = oHdrData.objSize;

	// Find block to write to and offset of block to write to (starting)
	uint32_t movePos = 0;
	uint32_t baseBlockSize = (m_pFlash->GetBlockSize() - sizeof(tFlashDataHdr));

	uint16_t prevBlockID = 0xFFFF;
	uint16_t startBlockID = dataID;
	uint16_t curBlockID = dataID;
	uint16_t curBlockOffset = 0;

	while ( movePos < filePos )
	{
		uint32_t moveRemaining = (filePos - movePos);

		uint32_t maxMove = 0;
		curBlockOffset = (sizeof(tFlashDataHdr));
		if ( movePos == 0 )
		{
			curBlockOffset += oHdrData.fileNameLen;
			maxMove = (baseBlockSize - oHdrData.fileNameLen);
		}
		else
		{
			//curBlockOffset = (sizeof(tFlashDataHdr));
			maxMove = baseBlockSize;
		}

		if ( maxMove > moveRemaining )
		{
			// Record starting offset
			curBlockOffset += (moveRemaining);
			break;
		} 
	
		// Move to next block
		tFlashDataHdr oDataHdr;

		uint32_t dataAddress = GetAddressForDataID( curBlockID ); 
		if ( m_pFlash->ReadData( dataAddress, (uint8_t*)&oDataHdr, sizeof(oDataHdr) ) != sizeof(oDataHdr) )
		{
			// Errror
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Read error\n" );
#endif
			return -1;
		}

		if ( oDataHdr.objBits != OBJ_INUSE )
		{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Data block should be in use\n" );
#endif
			return -1;
		}

		prevBlockID = curBlockID;
		curBlockID = oDataHdr.nextDataID;	
		curBlockOffset = (sizeof(tFlashDataHdr));

		movePos += maxMove;
	}

	// Did not move -- so set block offset
	if ( filePos == 0 )
		curBlockOffset = (sizeof(tFlashDataHdr) + oHdrData.fileNameLen);

	// Begin writing to file
	uint32_t dataToWrite = dataLen;	
	uint32_t dataPos = 0;
	
	while ( dataToWrite > 0 )
	{	
		uint32_t dataWritten = 0;
		uint32_t dataToWriteInBlock = dataToWrite;
		uint16_t nextBlockID = 0xFFFF;

		if ( curBlockOffset+dataToWriteInBlock > m_pFlash->GetBlockSize() )
			dataToWriteInBlock = (m_pFlash->GetBlockSize()-curBlockOffset);

		// Do we need to overwrite this data block???
		if ( filePos < fileSize )
		{
			// Use a slow block erase for overwrites to preserve linked list indexes
			uint32_t blockSize = m_pFlash->GetBlockSize();

			uint32_t blockAddress = GetAddressForDataID( curBlockID );

			tFlashDataHdr oPrevDataHdr;
			tFlashDataHdr oNewDataHdr;

			if ( m_pFlash->ReadData( blockAddress, (uint8_t*)&oPrevDataHdr, sizeof(oPrevDataHdr) ) != sizeof(oPrevDataHdr) )
			{
				// Read error
				return (-1);
			}

			// Remember next block ID
			nextBlockID = oPrevDataHdr.nextDataID;

			oNewDataHdr.objBits = OBJ_INUSE;
			oNewDataHdr.prevDataID = oPrevDataHdr.prevDataID;
			oNewDataHdr.nextDataID = oPrevDataHdr.nextDataID;

			// Read in temp data (up to where we start overwriting it)
			if ( m_pFlash->ReadData( (blockAddress+sizeof(oPrevDataHdr)), m_tempBlock, curBlockOffset-sizeof(oPrevDataHdr)) != (curBlockOffset-sizeof(oPrevDataHdr)) )
			{
				// Read error
				return (-1);
			}

			// Add in new data to write
			memcpy( m_tempBlock+(curBlockOffset-sizeof(oPrevDataHdr)), pData+dataPos, dataToWriteInBlock );

			// Is there any data remaining in the block that wasn't written
			if ( (curBlockOffset+dataToWriteInBlock) < blockSize )
			{
				if ( m_pFlash->ReadData( blockAddress+curBlockOffset+dataToWriteInBlock, m_tempBlock+(curBlockOffset-sizeof(oPrevDataHdr))+dataToWriteInBlock, blockSize-(curBlockOffset+dataToWriteInBlock) ) != (blockSize - (curBlockOffset+dataToWriteInBlock)) )
				{
					// Read error
					return (-1);
				}
			}

			uint32_t blockToEraseID = (m_pFlash->GetBlocksPerSector() * 4) + curBlockID;
			m_pFlash->BlockErase( blockToEraseID ); 
			
			// Write new block
			if ( m_pFlash->WriteData( blockAddress, (uint8_t*)&oNewDataHdr, sizeof(oNewDataHdr) ) != sizeof(oNewDataHdr) )
			{
				// Write error
				return (-1);
			}

			if ( m_pFlash->WriteData( (blockAddress+sizeof(oNewDataHdr)), m_tempBlock, blockSize-sizeof(oNewDataHdr) ) != (blockSize-sizeof(oNewDataHdr)) )
			{
				// Write error
				return (-1);
			}
		}
		else
		{
			// Currently appending new data -- allocate block as necessary
			if ( curBlockID == 0xFFFF )
			{
				// Allocate
				curBlockID = GetNextDataBlockID();	

				tFlashDataHdr oNewBlockHdr;
				oNewBlockHdr.objBits = OBJ_INUSE;
				oNewBlockHdr.nextDataID = 0xFFFF;
				oNewBlockHdr.prevDataID = prevBlockID;

				// Remember next ID
				nextBlockID = 0xFFFF;

				uint32_t newBlockAddress = GetAddressForDataID( curBlockID );

				if ( m_pFlash->WriteData( newBlockAddress, (uint8_t*)&oNewBlockHdr, sizeof(oNewBlockHdr) ) != sizeof(oNewBlockHdr) )
				{
					// Read error
					return (-1);
				}

				// Write old
				tFlashDataHdr oPrevBlockHdr;
				
				uint32_t prevBlockAddress = GetAddressForDataID( prevBlockID );
				
				if ( m_pFlash->ReadData( prevBlockAddress, (uint8_t*)&oPrevBlockHdr, sizeof(oPrevBlockHdr) ) != sizeof(oPrevBlockHdr) )
				{
					// Read error
					return (-1);
				}

				if ( oPrevBlockHdr.nextDataID != 0xFFFF )
				{
#if FLASH_DEBUG_MODE
					printf( "FS ERR: Previous data block ID should be 0xFFFF\n" );
#endif
					return (-1);
				}

				oPrevBlockHdr.nextDataID = curBlockID;
	
				if ( m_pFlash->WriteData( prevBlockAddress, (uint8_t*)&oPrevBlockHdr, sizeof(oPrevBlockHdr) ) != sizeof(oPrevBlockHdr) )
				{
					// Write error
					return (-1);
				}		
			}
			else
			{
				uint32_t curBlockAddress = GetAddressForDataID( curBlockID );

				tFlashDataHdr oCurBlockHdr;
				if ( m_pFlash->ReadData( curBlockAddress, (uint8_t*)&oCurBlockHdr, sizeof(oCurBlockHdr) ) != sizeof(oCurBlockHdr) )
				{
					// Read error
					return (-1);
				}

				// Remember next block ID
				nextBlockID = oCurBlockHdr.nextDataID;
			}
		
			// Write data
			uint32_t curBlockAddress = GetAddressForDataID( curBlockID );

			if ( m_pFlash->WriteData( curBlockAddress+curBlockOffset, pData+dataPos, dataToWriteInBlock ) != dataToWriteInBlock )
			{
				// Write error
				return (-1);
			}			
		}

		prevBlockID = curBlockID;

		curBlockID = nextBlockID;

		curBlockOffset = sizeof(tFlashDataHdr);

		// Update file position
		filePos += dataToWriteInBlock;

		// Update data position
		dataPos += dataToWriteInBlock;

		// Reduce amount of data left to write
		dataToWrite -= dataToWriteInBlock;	
	}

	// Check if file size changed
	if ( filePos > fileSize )
	{
		// Update file header
		tFlashFileHdr oNewFileHdr;

		// Create new header -- updating file size
		oNewFileHdr.objBits = OBJ_INUSE;
		oNewFileHdr.dataID = oHdrData.dataID;
		oNewFileHdr.objSize = filePos;
		oNewFileHdr.fileNameLen = oHdrData.fileNameLen;
	
		// Write old header -- as erased
		oHdrData.objBits = OBJ_ERASE;
		
		if ( m_pFlash->WriteData( hdrAddress, (uint8_t*)&oHdrData, sizeof(oHdrData) ) != sizeof(oHdrData) )
		{
			// Write failure
			return (-1);
		}

		// Allocate new header
		uint16_t newHdrID = GetNewObjHeaderID();

		// Update file table
		uint32_t i;
		for ( i = 0; i < MAX_FILES; i++ )
		{
			if ( m_fileTable[i].hdrID == hdrID )
			{
				// Update file table entry to point to new header
				uint16_t newFileTableID = GetNewFileTableID();

				uint32_t oldFileTableAddress = GetAddressForFileTableID( m_fileTable[i].fileTableID );
				
				uint8_t tempByte = OBJ_ERASE;	
				if ( m_pFlash->WriteData( oldFileTableAddress, &tempByte, sizeof(tempByte) ) != sizeof(tempByte) )
				{
					// Write error
					return (-1);
				}

				m_fileTable[i].hdrID = newHdrID; 
				m_fileTable[i].fileTableID = newFileTableID;
				break;
			}
		}

		if ( i == MAX_FILES )
		{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: File table entry not found when attempting update on file table\n" );
#endif
			return (-1);
		}

		// Now update the FD table (multiple FDs might be pointing to this file)
		for ( i = 0; i < MAX_FILE_DESCRIPTORS; i++ )
		{
			if ( m_fileDescriptorTable[i].hdrID == hdrID )
				m_fileDescriptorTable[i].hdrID = newHdrID;
		}

		// Lastly write the new file table block
		uint32_t newHdrAddress = GetAddressForHeaderID( newHdrID );

		if ( m_pFlash->WriteData( newHdrAddress, (uint8_t*)&oNewFileHdr, sizeof(oNewFileHdr) ) != sizeof(oNewFileHdr) )
		{
			// Write error
			return (-1);
		}
	}

	// Update file descriptor's file position
	m_fileDescriptorTable[fd].filePos = filePos;

	// Return amount written
	return (dataPos);
}

int32_t CFlashFS::ReadFile( int32_t fd, uint8_t *pData, uint32_t dataLen )
{
	// Find file descriptor
	tFileDescriptorTable oFDData;

	if ( !FindFileDescriptorData( fd, &oFDData ) )
	{
		// FD not found
		return (FD_NOT_FOUND);
	}

	// Write to file
	uint16_t hdrID = oFDData.hdrID;

	tFlashFileHdr oHdrData;

	uint32_t hdrAddress = GetAddressForHeaderID( hdrID );

	if ( m_pFlash->ReadData( hdrAddress, (uint8_t*)&oHdrData, sizeof(oHdrData) ) != sizeof(oHdrData) )
	{
		// Read failure
		return (-1);
	}

	// Find proper position to write to
	uint16_t dataID = oHdrData.dataID;

	uint32_t filePos = oFDData.filePos;

	if ( filePos > oHdrData.objSize )
	{
		// Error
#if FLASH_DEBUG_MODE
		printf( "FS ERR: File position past file size\n" );
#endif
		filePos = oHdrData.objSize;

		return (-1);
	}

	// Only read the amount remaining
	if ( filePos+dataLen > oHdrData.objSize )
		dataLen = oHdrData.objSize - filePos;

	// IF we don't have anything to read -- just return 0
	if ( dataLen == 0 )
		return (0);

	// Remember file size
	uint32_t fileSize = oHdrData.objSize;

	// Find block to write to and offset of block to write to (starting)
	uint32_t movePos = 0;
	uint32_t baseBlockSize = (m_pFlash->GetBlockSize() - sizeof(tFlashDataHdr));

	uint16_t prevBlockID = 0xFFFF;
	uint16_t startBlockID = dataID;
	uint16_t curBlockID = dataID;
	uint16_t curBlockOffset = 0;

	while ( movePos < filePos )
	{
		uint32_t moveRemaining = (filePos - movePos);

		uint32_t maxMove = 0;
		curBlockOffset = sizeof(tFlashDataHdr);
		if ( movePos == 0 )
		{
			curBlockOffset += oHdrData.fileNameLen;
			maxMove = (baseBlockSize - oHdrData.fileNameLen);
		}
		else
		{
			maxMove = baseBlockSize;
		}

		if ( maxMove > moveRemaining )
		{
			// Record starting offset
			curBlockOffset += (moveRemaining);
			break;
		} 
	
		// Move to next block
		tFlashDataHdr oDataHdr;

		uint32_t dataAddress = GetAddressForDataID( curBlockID ); 
		if ( m_pFlash->ReadData( dataAddress, (uint8_t*)&oDataHdr, sizeof(oDataHdr) ) != sizeof(oDataHdr) )
		{
			// Errror
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Read error\n" );
#endif
			return -1;
		}

		if ( oDataHdr.objBits != OBJ_INUSE )
		{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Data block should be in use\n" );
#endif
			return -1;
		}

		curBlockOffset = (sizeof(tFlashDataHdr));
		
		prevBlockID = curBlockID;
		curBlockID = oDataHdr.nextDataID;	

		movePos += maxMove;
	}

	// Did not move -- so set block offset
	if ( filePos == 0 )
		curBlockOffset = (sizeof(tFlashDataHdr) + oHdrData.fileNameLen);

	// Begin reading from file
	uint32_t dataToRead = dataLen;	
	uint32_t dataPos = 0;
	
	while ( dataToRead > 0 )
	{	
		uint32_t dataToReadInBlock = dataToRead;

		if ( curBlockOffset+dataToReadInBlock > m_pFlash->GetBlockSize() )
			dataToReadInBlock = (m_pFlash->GetBlockSize()-curBlockOffset);

		if ( curBlockID == 0xFFFF )
		{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Read past inuse blocks\n" );
#endif
			return -1;
		}

		uint32_t blockAddress = GetAddressForDataID( curBlockID );

		tFlashDataHdr oDataHdr;

		// Read block
		if ( m_pFlash->ReadData( blockAddress, (uint8_t*)&oDataHdr, sizeof(oDataHdr) ) != sizeof(oDataHdr) )
		{
			// Read error
			return (-1);
		}

		// Validate
		if ( oDataHdr.objBits != OBJ_INUSE )
		{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Read block should be in use\n" );
#endif
			return -1;
		}

		// Read
		if ( m_pFlash->ReadData( blockAddress+curBlockOffset, pData+dataPos, dataToReadInBlock ) != dataToReadInBlock )
		{
			// Read errror
			return (-1);
		}
		
		curBlockID = oDataHdr.nextDataID;
	
		curBlockOffset = sizeof(tFlashDataHdr);
	
		dataToRead -= dataToReadInBlock;
		dataPos += dataToReadInBlock;

		// Update file position
		filePos += dataToReadInBlock;
	}

	// Read doesn't change any data in flash
	m_fileDescriptorTable[fd].filePos = filePos;

	return (dataPos);
}

int32_t CFlashFS::DeleteFile( const char *pszFilename )
{
	uint16_t hdrID;
	uint32_t objSize;

	// Not in recent file list -- try looking in file table
	if ( !FindFileInFlashTable( pszFilename, &hdrID, &objSize ) )
	{
		return (-1);
	}

	tFlashFileHdr oHdrData;

	uint32_t hdrAddress = GetAddressForHeaderID( hdrID );

	if ( m_pFlash->ReadData( hdrAddress, (uint8_t*)&oHdrData, sizeof(oHdrData) ) != sizeof(oHdrData) )
	{
		// Read failure
		return (-1);
	}

	uint16_t curBlockID = oHdrData.dataID;
	uint16_t nextBlockID = 0xFFFF;

	do
	{
		// Move to next block
		tFlashDataHdr oDataHdr;

		uint32_t dataAddress = GetAddressForDataID( curBlockID ); 
		if ( m_pFlash->ReadData( dataAddress, (uint8_t*)&oDataHdr, sizeof(oDataHdr) ) != sizeof(oDataHdr) )
		{
			// Errror
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Delete error\n" );
#endif
			return -1;
		}

		if ( oDataHdr.objBits != OBJ_INUSE )
		{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: Data block should be in use, while deleting file\n" );
#endif
			return -1;
		}

		// Mark it erased
		oDataHdr.objBits = OBJ_ERASE;

		// Write
		if ( m_pFlash->WriteData( dataAddress, (uint8_t*)&oDataHdr, sizeof(oDataHdr) ) != sizeof(oDataHdr) )
		{
			// Write error
			return (-1);
		}

		curBlockID = oDataHdr.nextDataID;	

		// Check for last block
		if ( curBlockID == 0xFFFF )
			break;

	} while ( true );

	// Delete file header
	oHdrData.objBits = OBJ_ERASE;

	// Write header
	if ( m_pFlash->WriteData( hdrAddress, (uint8_t*)&oHdrData, sizeof(oHdrData) ) != sizeof(oHdrData) )
	{
		// Write error
		return (-1);
	}

	// Delete file table entry
	uint16_t fileTableID = 0xFFFF;
	for ( uint32_t i = 0; i < MAX_FILES; i++ )
	{
		if ( m_fileTable[i].hdrID == hdrID )
		{
			m_fileTable[i].hdrID = 0xFFFF;
			fileTableID = m_fileTable[i].fileTableID;

			m_fileTable[i].fileTableID = 0xFFFF;

			m_fileTableCount--;
			break;
		}
	}

	if ( fileTableID == 0xFFFF )
	{
#if FLASH_DEBUG_MODE
			printf( "FS ERR: File table entry not found, while deleting file\n" );
#endif
			return -1;
	}

	// Write file table entry
	uint32_t fileTableAddress = GetAddressForFileTableID( fileTableID );

	uint8_t tempByte = OBJ_ERASE;
	if ( m_pFlash->WriteData( fileTableAddress, &tempByte, sizeof(tempByte) ) != sizeof(tempByte) )
	{
		// Write error
		return (-1);
	}

	// Lastly remove all file descriptors
	for ( uint32_t i = 0; i < MAX_FILE_DESCRIPTORS; i++ )
	{
		if ( m_fileDescriptorTable[i].hdrID == hdrID )
		{
			m_fileDescriptorTable[i].hdrID = OBJ_ID_UNUSED_FD;
			m_fileDescriptorTable[i].filePos = 0;

			m_fileDescriptorCount--;
		}
	}

	return (0);
}

int32_t CFlashFS::OpenFile( const char *pszFilename, uint8_t openAttributes )
{
	bool bFileFound = false;

	uint16_t objID;
	uint32_t objSize;

	if ( m_fileDescriptorCount >= MAX_FILE_DESCRIPTORS )
	{
		// Max FDs
		return (OPEN_FILE_MAX_FD);
	}

	// Not in recent file list -- try looking in file table
	if ( !FindFileInFlashTable( pszFilename, &objID, &objSize ) )
	{
		// No file at all
		if ( openAttributes != OPEN_MODE_WRITE )
		{
			// Fail -- not opened writeable
			return (OPEN_FILE_NOT_FOUND);
		}

		// No file present -- create it
		if ( !CreateNewFile( pszFilename, &objID, &objSize ) )
		{
			// Fail -- out of free blocks
			return (OPEN_FILE_OUT_OF_SPACE);
		}
	}
	
	int32_t newFD = GetNewFileDescriptor();

	if ( newFD == -1 )
	{
		// File already opened
		return (OPEN_FILE_ALREADY_OPEN);
	}

	// File found or file created for write mode
	m_fileDescriptorTable[newFD].hdrID = objID;

	if ( openAttributes == OPEN_MODE_APPEND )
		m_fileDescriptorTable[newFD].filePos = objSize;
	else
		m_fileDescriptorTable[newFD].filePos = 0;

	return (newFD);
}

int32_t CFlashFS::CloseFile( int32_t fd )
{
	// Bug here
#if PATCHED_1
	if ( fd < 0 )
		return (CLOSE_BAD_FD);
#endif

	if ( fd >= MAX_FILE_DESCRIPTORS )
		return (CLOSE_BAD_FD);

	if ( m_fileDescriptorTable[fd].hdrID == OBJ_ID_UNUSED_FD )
		return (CLOSE_BAD_FD);

	m_fileDescriptorTable[fd].hdrID = OBJ_ID_UNUSED_FD;
	m_fileDescriptorTable[fd].filePos = 0;

	m_fileDescriptorCount--;

	return (fd);
}

bool CFlashFS::FindFileDescriptorData( int16_t fd, tFileDescriptorTable *pFDData )
{
	if ( fd < 0 || fd >= MAX_FILE_DESCRIPTORS )
		return (false);

	if ( m_fileDescriptorTable[fd].hdrID == OBJ_ID_UNUSED_FD )
		return (false);

	pFDData->hdrID = m_fileDescriptorTable[fd].hdrID;
	pFDData->filePos = m_fileDescriptorTable[fd].filePos;

	return (true);
}

bool CFlashFS::FindFileInFlashTable( const char *pszFilename, uint16_t *pObjID, uint32_t *pObjSize )
{
	char szFilenameTemp[256];
	
	uint8_t testFileLen = strlen( pszFilename );

	// Read first file in file table
	// Loop through file descriptor table
	uint32_t fileTableHitCount = 0;
	for ( uint32_t i = 0; i < MAX_FILES; i++ )	
	{
		if ( fileTableHitCount >= m_fileTableCount )
			break; // Exit early if we need to
		
		if ( m_fileTable[i].hdrID == 0xFFFF )
			continue;

		fileTableHitCount++;		

		uint32_t fileHeaderAddr = GetAddressForHeaderID( m_fileTable[i].hdrID );

		tFlashFileHdr oFileHdr;
		if ( m_pFlash->ReadData( fileHeaderAddr, (uint8_t*)&oFileHdr, sizeof(oFileHdr) ) != sizeof(oFileHdr) )
			return (false);

		if ( testFileLen != oFileHdr.fileNameLen )
			continue;
 
		// Read file name
		uint32_t fileNameAddress = GetAddressForDataID( oFileHdr.dataID ) + sizeof(tFlashDataHdr);

		if ( m_pFlash->ReadData( fileNameAddress, (uint8_t*)szFilenameTemp, oFileHdr.fileNameLen ) != oFileHdr.fileNameLen )
			return (false);

		szFilenameTemp[oFileHdr.fileNameLen] = '\0';

		if ( strcmp( pszFilename, szFilenameTemp ) == 0 )
		{
			(*pObjID) = m_fileTable[i].hdrID;
			(*pObjSize) = oFileHdr.objSize;

			return (true);
		}

	}

	return (false);	
}

uint32_t CFlashFS::GetFileTableAddress( void )
{
	return (m_fileTableAddress);
}

bool CFlashFS::CreateNewFile( const char *pszFilename, uint16_t *pObjID, uint32_t *pObjSize )
{
	if ( m_fileTableCount >= MAX_FILES )
		return (false);

	uint16_t objHeaderID = GetNewObjHeaderID();

	if ( objHeaderID == 0xFFFF )
	{
		// Clean object header table
		CleanObjHeaderTable();
	
		objHeaderID = GetNewObjHeaderID();
	}

	if ( objHeaderID == 0xFFFF )
		return (false);	// Critical error

	// Get a new file table header
	uint16_t fileTableID = GetNewFileTableID( );

	if ( fileTableID == 0xFFFF )
	{
		// Clean file table
		CleanFileTable();
	
		fileTableID = GetNewFileTableID( );
	}	

	if ( fileTableID == 0xFFFF )
		return (false);	// Critical error -- out of file table indexes

	if ( !CreateNewObject( pszFilename, fileTableID, objHeaderID ) )
		return (false); // Critical error -- out of space?

	(*pObjID) = objHeaderID;
	(*pObjSize) = 0;			

	return (true);
}

uint32_t CFlashFS::GetAddressForHeaderID( uint16_t objID )
{
	return ((m_pFlash->GetBlockSize() * m_pFlash->GetBlocksPerSector()) + (sizeof(tFlashFileHdr) * objID));	
}

uint32_t CFlashFS::GetAddressForFileTableID( uint16_t objID )
{
	return (m_fileTableAddress + (sizeof(tFlashFileTableObj) * objID));
}

uint32_t CFlashFS::GetAddressForDataID( uint16_t objID )
{
	return ((GetAddressForSector( 4 )) + (m_pFlash->GetBlockSize() * objID));
}

uint32_t CFlashFS::GetAddressForSector( uint16_t sectorNum )
{
	return (m_pFlash->GetBlockSize() * m_pFlash->GetBlocksPerSector() * sectorNum);
}

uint16_t CFlashFS::GetNewFileTableID( void )
{
	if ( m_fileTableCount >= MAX_FILES )
		return (0xFFFF);
	
	uint16_t newFileTableID = m_fileTableIDNext;
	do
	{
		if ( newFileTableID >= MAX_FILES )
			newFileTableID = 0;

		if ( m_fileTable[newFileTableID].hdrID == 0xFFFF )
			break;

		newFileTableID++;
	} while ( true );

	if ( m_fileTableIDNext < MAX_FILES )
		m_fileTableIDNext++;

	return (newFileTableID);
}

uint16_t CFlashFS::GetNewObjHeaderID( void )
{
	if ( m_objHeaderIDNext >= m_objHeaderIDMax )	
		return (0xFFFF);

	uint16_t newObjHeaderID = m_objHeaderIDNext++;

	return (newObjHeaderID);
}

bool CFlashFS::CleanFileTable( void )
{
	// Easy cleanup -- just rewrite the file table after erasing sector 1
	m_pFlash->SectorErase( 0 );
	
	// Rewrite
	tFlashFSHdr oFSHdr;
	
	oFSHdr.version = FLASH_FS_VERSION;
	oFSHdr.fileTableBlockIdx = 0;	// Default position
	oFSHdr.fileTableBlockOffset = sizeof(oFSHdr);

	// Write it to flash
	if ( m_pFlash->WriteData( 0, (uint8_t*)&oFSHdr, sizeof(oFSHdr) ) != sizeof(oFSHdr) )
	{
		// Write error
		return (false);
	}

	uint32_t curAddress = GetFileTableAddress();
	uint16_t tableIDCur = 0;
	for ( uint32_t i = 0; i < m_fileTableCount; i++ )
	{
		do
		{
			if ( tableIDCur >= MAX_FILES )
			{
				// Error
				return (false);
			}

			if ( m_fileTable[tableIDCur].hdrID != 0xFFFF )
			{
				m_fileTable[i].hdrID = m_fileTable[tableIDCur].hdrID;
				m_fileTable[i].fileTableID = i;
				break;
			}
			
			tableIDCur++;

		} while ( true );

		tFlashFileTableObj oFileTableObj;

		oFileTableObj.objBits = OBJ_INUSE;
		oFileTableObj.objID = m_fileTable[tableIDCur].hdrID;

		if ( m_pFlash->WriteData( curAddress, (uint8_t*)&oFileTableObj, sizeof(oFileTableObj) ) != sizeof(oFileTableObj) )
		{
			// Write error
			return (false);
		}

		curAddress += sizeof(oFileTableObj);
	}

	// Reset file table
	m_fileTableIDNext = m_fileTableCount;

	for ( tableIDCur = m_fileTableIDNext; tableIDCur < MAX_FILES; tableIDCur++ )
	{
		m_fileTable[tableIDCur].hdrID = 0xFFFF;
		m_fileTable[tableIDCur].fileTableID = 0xFFFF;
	}

	return (true);
}

bool CFlashFS::CleanObjHeaderTable( void )
{
	// Object header table is in sectors 1-3, there can be up to MAX_FILES object headers
	// Copy into the scratch sector	

	bool bDone = false;
	uint32_t fileTablePos = 0;

	uint32_t scratchStartSector = 0;
	uint32_t scratchEndSector = 0;
	uint32_t fileHeaderCount = 0;
	do
	{
		uint32_t scratchCurAddress = GetAddressForSector( m_scratchSectorCur );
		uint32_t scratchEndAddress = GetAddressForSector( m_scratchSectorCur+1 );

		uint32_t i = 0;

		if ( scratchStartSector == 0 )
			scratchStartSector = m_scratchSectorCur;

		scratchEndSector = m_scratchSectorCur+1;

		// Go through the file table and move it to the scratch sector
		for ( i = fileTablePos; fileHeaderCount < m_fileTableCount; i++ )
		{
			if ( m_fileTable[i].hdrID == 0xFFFF )
				continue;

			if ( i >= MAX_FILES )
			{
#if FLASH_DEBUG_MODE
				printf( "FS ERR: Cleaning object header table -- wrap-around (should not happen)\n" );
#endif
				return (false);
			}

			// Copy data
			tFlashFileHdr oTemp;

			if ( scratchCurAddress+sizeof(oTemp) > scratchEndAddress )
				break;

			uint32_t fileTableHeaderAddr = GetAddressForFileTableID( m_fileTable[i].hdrID );

			if ( m_pFlash->ReadData( fileTableHeaderAddr, (uint8_t*)&oTemp, sizeof(oTemp) ) != sizeof(oTemp) )
			{
				// Read error
				return (false);
			}

			// Write to scratch
			if ( m_pFlash->WriteData( scratchCurAddress, (uint8_t*)&oTemp, sizeof(oTemp) ) != sizeof(oTemp) )
			{
				// Write error
				return (false);
			}

			scratchCurAddress += sizeof(oTemp);
	
			fileHeaderCount++;
		}
		
		if ( fileHeaderCount == m_fileTableCount )
			bDone = true;

		fileTablePos = i;

		m_scratchSectorCur = GetNextScratchSector();
	}	
	while ( !bDone );

	// Erase file header sectors
	m_pFlash->SectorErase( 1 );
	m_pFlash->SectorErase( 2 );
	m_pFlash->SectorErase( 3 );

	// Copy back
	uint32_t headerCurAddress = GetAddressForHeaderID( 0 );

	uint32_t copyPerSector = ((m_pFlash->GetBlockSize() * m_pFlash->GetBlocksPerSector()) / sizeof(tFlashFileHdr)) * sizeof(tFlashFileHdr);

	fileTablePos = 0;
	fileHeaderCount = 0;
	
	do
	{
		// Copy as much as possible
		uint32_t copyFromPos = GetAddressForSector( scratchStartSector );
		uint32_t copyFromEndPos = copyFromPos + copyPerSector;

		scratchStartSector++;

		// Copy
		uint32_t i = 0;
		for ( i = fileTablePos; fileHeaderCount < m_fileTableCount; i++ )
		{
			if ( m_fileTable[i].hdrID == 0xFFFF )
				continue;

			if ( i >= MAX_FILES )
			{
#if FLASH_DEBUG_MODE
				printf( "FS ERR: Cleaning object header table -- wrap-around (should not happen)\n" );
#endif
				return (false);
			}

			tFlashFileHdr oTemp;

			if ( copyFromPos+sizeof(oTemp) > copyFromEndPos )
				break;

			// From scratch to new position in header table
			if ( m_pFlash->ReadData( copyFromPos, (uint8_t*)&oTemp, sizeof(oTemp) ) != sizeof(oTemp) )
			{
				// Read error
				return (false);
			}

			// Write to scratch
			if ( m_pFlash->WriteData( headerCurAddress, (uint8_t*)&oTemp, sizeof(oTemp) ) != sizeof(oTemp) )
			{
				// Write error
				return (false);
			}

			// Reset file table
			m_fileTable[i].hdrID = fileHeaderCount;

			fileHeaderCount++;

			copyFromPos += sizeof(oTemp);
			headerCurAddress += sizeof(oTemp);
		}

		fileTablePos = i;
	
		if ( fileHeaderCount == m_fileTableCount )
			break;	

		// Wrap around scratch sector
		if ( scratchStartSector >= m_pFlash->GetSectorCount() )
			scratchStartSector = m_pFlash->GetSectorCount() - 4;

	} while ( true );

	// Always clean file table after rewriting object header table
	CleanFileTable();

	return (true);
}

bool CFlashFS::CleanDataBlocks( void )
{
	// Clean up some sectors to use -- normally this would be done
	// progressively over the life of the device (for speed reasons)

	// Find first emtpy 
	uint32_t curDataID = 0;
	for ( curDataID = 0; curDataID < m_maxDataBlockID; curDataID++ )
	{
		uint32_t curBlockAddress = GetAddressForDataID( curDataID );
	}

	CleanObjHeaderTable();

	// Out of memory	
	return (false);
}

uint16_t CFlashFS::GetNextScratchSector( void )
{
	m_scratchSectorCur++;

	if ( m_scratchSectorCur >= m_pFlash->GetSectorCount() )
		m_scratchSectorCur = m_pFlash->GetSectorCount() - 4;

	m_pFlash->SectorErase( m_scratchSectorCur );

	return (m_scratchSectorCur);
}

bool CFlashFS::CreateNewObject( const char *pszObjectName, uint16_t fileTableID, uint16_t hdrID )
{
	uint8_t objNameLen = strlen(pszObjectName);

	// Find new spot for object
	for ( uint32_t i = 0; i < MAX_FILES; i++ )
	{
		if ( m_fileTable[i].hdrID == 0xFFFF )
		{
			m_fileTable[i].hdrID = hdrID;
			m_fileTable[i].fileTableID = fileTableID;
	
			m_fileTableCount++;
			break;
		}
	}

	// Get a data block
	uint16_t dataBlockID = GetNextDataBlockID();

	// Claim block -- but not used yet
	tFlashDataHdr oDataHdr;

	oDataHdr.objBits = OBJ_INUSE;
	oDataHdr.prevDataID = 0x0;	// First in block list
	oDataHdr.nextDataID = 0xFFFF;	// Not init'ed yet

	uint32_t dataAddress = GetAddressForDataID( dataBlockID );

	if ( m_pFlash->WriteData( dataAddress, (uint8_t*)&oDataHdr, sizeof(oDataHdr) ) != sizeof(oDataHdr) )
	{
		// Fail to write data
		return (false);
	}

	// Write name
	if ( m_pFlash->WriteData( (dataAddress+sizeof(oDataHdr)), (uint8_t*)pszObjectName, objNameLen ) != objNameLen )
	{
		// Fail to write data
		return (false);
	}
	
	// Write header data
	tFlashFileHdr oFileHdr;

	oFileHdr.objBits = OBJ_INUSE;
	oFileHdr.dataID = dataBlockID;
	oFileHdr.objSize = 0;
	oFileHdr.fileNameLen = objNameLen;

	// Write header
	uint32_t hdrAddress = GetAddressForHeaderID( hdrID );

	if ( m_pFlash->WriteData( hdrAddress, (uint8_t*)&oFileHdr, sizeof(oFileHdr) ) != sizeof(oFileHdr) )
	{
		// Fail to write header
		return (false);
	}
	
	return (true);
}

int32_t CFlashFS::GetNewFileDescriptor( void )
{
	if ( m_fileDescriptorCount >= MAX_FILE_DESCRIPTORS )
		return (-1);

	for ( uint32_t i = 0; i < MAX_FILE_DESCRIPTORS; i++ )
	{
		if ( m_fileDescriptorTable[i].hdrID == OBJ_ID_UNUSED_FD )
		{
			m_fileDescriptorCount++;
			return (i);
		}
	}

	return (-1);
}

uint16_t CFlashFS::GetNextDataBlockID( void )
{
	// Get a new data block
	uint16_t nextDataBlockID = m_lastDataBlockID++;

	if ( nextDataBlockID >= m_maxDataBlockID )
	{
		// Clean
		CleanDataBlocks( );
	}
	
	nextDataBlockID = m_lastDataBlockID++;

	return (nextDataBlockID);
}
