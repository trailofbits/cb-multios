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
#include <string.h>
#include <prng.h>
#include <fs.h>
}

#include <cutil_list.h>
#include <cutil_string.h>

#include "databasefs.h"

CDBNode::CDBNode( const CUtil::String &sName, const CUtil::String &sOwner, uint8_t modeBits )
	: m_modeBits( modeBits ), m_sName( sName ), m_sOwner( sOwner )
{

}

CDBNode::CDBNode( const char *pszName, const char *pszOwner, uint8_t modeBits )
	: m_modeBits( modeBits ), m_sName( pszName ), m_sOwner( pszOwner )
{

}

CDBNode::~CDBNode( )
{

}

CDBFile::CDBFile( const CUtil::String &sName, const CUtil::String &sOwner, uint8_t modeBits )
	: CDBNode( sName, sOwner, modeBits ), m_fileSize( 0 )
{
	bzero( m_pChunks, sizeof(tFileChunk *)*FILE_MAX_CHUNKS );
}

CDBFile::CDBFile( const char *pszName, const char *pszOwner, uint8_t modeBits )
	: CDBNode( pszName, pszOwner, modeBits ), m_fileSize( 0 )
{
	bzero( m_pChunks, sizeof(tFileChunk *)*FILE_MAX_CHUNKS );
}

CDBFile::~CDBFile( )
{
	if ( m_fileSize > 0 )
	{
		uint32_t topChunk = (m_fileSize / FILE_CHUNK_SIZE)+1;
		if ( topChunk > FILE_MAX_CHUNKS )
			topChunk = FILE_MAX_CHUNKS;

		for ( uint32_t curChunk = 0; curChunk < topChunk; curChunk++ )
		{
			if ( m_pChunks[curChunk] )
			{
				delete m_pChunks[curChunk];
				m_pChunks[curChunk] = NULL;
			}
		}
	}

	m_fileSize = 0;
}

uint8_t CDBFile::WriteData( int32_t writePos, uint8_t *pData, uint32_t writeLength, uint32_t &writeActual )
{
	if ( !pData )
		return FILE_WRITE_ERROR;

	uint32_t writeAmount = writeLength;
	if ( writePos + writeLength > MAX_FILE_SIZE )
	{
		return FILE_WRITE_ERROR_MAX_FILESIZE;
	}

	if ( writePos > m_fileSize )
	{
		return FILE_WRITE_PAST_EOF;
	}

	// Begin writing
	uint32_t fromPos = 0;
	while ( writeAmount > 0 )
	{
		uint32_t chunkPos = (writePos / FILE_CHUNK_SIZE);
		uint32_t chunkOffset = (writePos % FILE_CHUNK_SIZE);

		uint32_t chunkToWrite = writeAmount;
		if ( chunkToWrite > (FILE_CHUNK_SIZE - chunkOffset) )
			chunkToWrite = (FILE_CHUNK_SIZE - chunkOffset);

		if ( !m_pChunks[chunkPos] )
		{
			m_pChunks[chunkPos] = new tFileChunk;
			bzero( m_pChunks[chunkPos]->chunkData, FILE_CHUNK_SIZE );
		}

		memcpy( m_pChunks[chunkPos]->chunkData+chunkOffset, pData+fromPos, chunkToWrite );
		
		writeAmount -= chunkToWrite;
		fromPos += chunkToWrite;
		writePos += chunkToWrite;	 	
	}

	if ( writePos > m_fileSize )
		m_fileSize = writePos;

	writeActual = fromPos;

	return (FILE_WRITE_OK);	
}

uint8_t CDBFile::ReadData( int32_t readPos, uint8_t *pData, uint32_t readLength, uint32_t &readActual )
{
	if ( readPos > m_fileSize )
		return (FILE_READ_ERROR);

	if ( readLength == 0 )
		return (FILE_READ_OK);

	if ( !pData )
		return (FILE_READ_EOF);

	uint32_t readAmount = readLength;
	if ( readPos+readAmount > m_fileSize )
		readAmount = (m_fileSize - readPos);

	if ( readAmount > readLength )
		readAmount = readLength;

	uint32_t fromPos = 0;
	while ( readAmount > 0 )
	{
		uint32_t chunkPos = (readPos / FILE_CHUNK_SIZE);
		uint32_t chunkOffset = (readPos % FILE_CHUNK_SIZE);

		uint32_t chunkToRead = readAmount;
		if ( chunkToRead > (FILE_CHUNK_SIZE - chunkOffset) )
			chunkToRead = (FILE_CHUNK_SIZE - chunkOffset);

		if ( !m_pChunks[chunkPos] )
		{
			// Critical error
			return (FILE_READ_ERROR);
		}

		memcpy( pData+fromPos, m_pChunks[chunkPos]->chunkData+chunkOffset, chunkToRead );

		readAmount -= chunkToRead;
		fromPos += chunkToRead;
		readPos += chunkToRead;	 	
	}
	
	readActual = fromPos;

	return (FILE_READ_OK);	
}

CDBFSUser::CDBFSUser( const CUtil::String &sUsername, const CUtil::String &sPassword )
	: m_sUsername( sUsername ), m_sPassword( sPassword )
{

}

CDBFSUser::CDBFSUser( const char *pszUsername, const char *pszPassword )
	: m_sUsername( pszUsername ), m_sPassword( pszPassword )
{

}

CDBFSUser::~CDBFSUser( )
{

}

CDBFSOpenFile::CDBFSOpenFile( CDBFile *pFile, uint8_t openMode )
	: m_pFile( pFile ), m_curFilePos( 0 ), m_openMode( openMode )
{

}

CDBFSOpenFile::~CDBFSOpenFile( )
{

}

CDBFS::CDBFS( CTimeGen *pTimeGen )
	: m_bLastError( false ), m_pTimeGen( pTimeGen ), m_sLastError( "" ), m_pCurUser( NULL ), m_curFiles( 0 ), m_maxFiles( 8 )
{

}

CDBFS::~CDBFS( )
{

}

bool CDBFS::Init( CUtil::String sRootPassword, uint32_t maxFiles )
{
	ClearError();

	m_maxFiles = maxFiles;
	m_curFiles = 0;

	m_nodeList.DeleteAll();
	m_userList.DeleteAll();
	m_openFileList.DeleteAll();

	m_userList.AddFirst( new CDBFSUser( "root", sRootPassword ) );

	m_pCurUser = NULL;

	return (true);
}

bool CDBFS::AddFileAsRoot( CUtil::String sFilename, uint8_t *pData, uint32_t dataLen )
{
	if ( FindFileByName( sFilename ) )
	{
		SetError( "File already exists" );

		// Failed to add
		return (false);
	}

	if ( IsMaxFilesReached() )
	{
		SetError( "Max files created" );
		return (false);
	}

	// Create new file
	CDBFile *pFile = CreateFile( sFilename, "root", FS_MODE_OWNER_READ|FS_MODE_OWNER_WRITE );
	m_curFiles++;	

	uint32_t fileWriteActual;
	uint32_t fileWriteAmount = dataLen;

	uint8_t writeStatus;
	if ( (writeStatus = pFile->WriteData( 0, pData, fileWriteAmount, fileWriteActual)) != FILE_WRITE_OK )
	{
		SetError( "Write error" );
		return (false);
	}

	// Write success
	ClearError();

	return (true);	
}

CDBFSUser *CDBFS::FindUser( CUtil::String sUsername )
{
	CDBFSUser *pCur;
	
	for ( pCur = m_userList.GetFirst(); pCur; pCur = m_userList.GetNext( pCur ) )
	{
		if ( pCur->GetUsername() == sUsername )
			return (pCur);
	}

	return (NULL);
}

bool CDBFS::SetUser( CUtil::String sUsername, CUtil::String sPassword )
{
	CDBFSUser *pUser;

	if ( !(pUser = FindUser( sUsername )) )
	{
		SetError( "Invalid username" );

		return (false);
	}

	if ( pUser->GetPassword() != sPassword )
	{
		SetError( "Invalid password" );

		return (false);
	}

	ClearError();
	
	m_pCurUser = pUser;

	return (true);
}

bool CDBFS::AddUser( CUtil::String sUsername, CUtil::String sPassword )
{
	if ( m_pCurUser == NULL )
	{
		SetError( "Must be root" );

		return (false);
	}

	if ( m_pCurUser->GetUsername() != "root" )
	{
		SetError( "Must be root" );

		return (false);
	}

	if ( FindUser( sUsername ) )
	{
		SetError( "User already exists" );

		return (false);
	}

	ClearError();
	
	m_userList.AddLast( new CDBFSUser( sUsername, sPassword ) );

	return (true);
}

bool CDBFS::DeleteUser( CUtil::String sUsername )
{
	if ( m_pCurUser == NULL )
	{
		SetError( "Must be root" );

		return (false);
	}

	if ( m_pCurUser->GetUsername() != "root" )
	{
		SetError( "Must be root" );

		return (false);
	}

	CDBFSUser *pUser;
	if ( !(pUser = FindUser( sUsername )) )
	{
		SetError( "User not found" );

		return (false);
	}

	if ( pUser->GetUsername() == "root" )
	{
		SetError( "Can't delete root user" );
		
		return (false);
	}

	ClearError();

	delete pUser;

	return (true);
}

bool CDBFS::RenameFile( CUtil::String sOldFilename, CUtil::String sNewFilename )
{
	// Quick check if they are logged in
	if ( m_pCurUser == NULL )
	{
		SetError( "Permission denied" );
		return (false);
	}
	
	// Rename file anywhere on the file system to a new location (can be a move as well)
	CDBFile *pFile = FindFileByName( sOldFilename );

	if ( !pFile )
	{
		SetError( "Source file not found" );
		return (false);
	}

	// Check permissions
	if ( !IsUserRoot() && !(pFile->GetOwner() == m_pCurUser->GetUsername()) )
	{
		SetError( "Permission denied" );
		return (false);
	}

	// Check destination
	if ( FindFileByName( sNewFilename ) )
	{
		SetError( "File already exists" );
		return (false);
	}

	// Remove
	pFile->m_dbLink.Unlink();

	// Change name
	pFile->SetName( sNewFilename.c_str() );

	// Re-add
	m_nodeList.AddLast( pFile );

	// Clear file system errors	
	ClearError();

	return (true);
}

bool CDBFS::DeleteFile( CUtil::String sFilename )
{
	// Quick check if they are logged in
	if ( m_pCurUser == NULL )
	{
		SetError( "Must login first" );
		return (false);
	}
	
	// Rename file anywhere on the file system to a new location (can be a move as well)
	CDBFile *pFile = FindFileByName( sFilename );

	if ( !pFile )
	{
		SetError( "Invalid filename" );
		return (false);
	}

	// Check permissions
	if ( !IsUserRoot() && !(pFile->GetOwner() == m_pCurUser->GetUsername()) )
	{
		SetError( "Permission denied" );
		return (false);
	}

	if ( IsFileOpen( pFile ) )
	{
		// Close all open handles
		if ( pFile )
		{
			CDBFSOpenFile *pNext;
			for ( CDBFSOpenFile *pCurOpenFile = m_openFileList.GetFirst(); pCurOpenFile; pCurOpenFile = pNext )
			{
				pNext = m_openFileList.GetNext( pCurOpenFile );
				if ( pCurOpenFile->GetFile() == pFile )
				{
					delete pCurOpenFile;
				}
			}
		}
	}

	// Delete file
	delete pFile;

	// Free up file
	m_curFiles--;

	// Clear file system errors
	ClearError();

	return (true);
}

CDBFSOpenFile *CDBFS::OpenFile( CUtil::String sFilename, const char *pszMode )
{
	// Check mode
	if ( pszMode == NULL )
	{
		SetError( "Invalid filename or mode" );
		return (NULL);
	}

	if ( strlen(pszMode) != 1 )
	{
		SetError( "Invalid mode" );
		return (NULL);
	}

	if ( pszMode[0] != 'r' && pszMode[0] != 'w' && pszMode[0] != 'a' )
	{
		SetError( "Invalid mode" );
		return (NULL);
	}

	if ( !m_pCurUser )
	{
		SetError( "Must login first" );
		return (NULL);
	}

	// Find file
	CDBFile *pFile = FindFileByName( sFilename );

	if ( (!pFile && pszMode[0] == 'r') || (!pFile && pszMode[0] == 'a') )
	{
		// Open for reading and file does not exist
		SetError( "Unable to locate file" );
		return (NULL);
	}

	// If we are creating a file (write mode)
	if ( !pFile )
	{
		// Creating file
		if ( !IsUserRoot() )
		{
			SetError( "Permission denied" );
			return (NULL);
		}

		if ( IsMaxFilesReached() )
		{
			SetError( "Max files created" );
			return (NULL);
		}

		// Create new file
		pFile = CreateFile( sFilename, m_pCurUser->GetUsername(), FS_MODE_OWNER_READ|FS_MODE_OWNER_WRITE );
		m_curFiles++;	
	}	

	// Create open file data structure
	uint8_t openMode = 0;
	if ( pszMode[0] == 'r' )
		openMode = FILE_OPEN_READ;
	else
		openMode = FILE_OPEN_WRITE;

	CDBFSOpenFile *pOpenFileData = new CDBFSOpenFile( pFile, openMode );

	m_openFileList.AddLast( pOpenFileData ); 

	// If opened in append mode!
	if ( pszMode[0] == 'a' )
		pOpenFileData->SetFilePositionEnd();

	ClearError();
	return (pOpenFileData);
}

bool CDBFS::CloseFile( CDBFSOpenFile *pFile )
{
	if ( !pFile )
	{
		SetError( "Invalid file pointer" );
		return (false);
	}

	// Check for file pointer
	bool bFound = false;	
	for ( CDBFSOpenFile *pOpenFileCur = m_openFileList.GetFirst(); pOpenFileCur; pOpenFileCur = m_openFileList.GetNext( pOpenFileCur ) )
	{
		if ( pOpenFileCur == pFile )
		{
			bFound = true;
			break;
		}
	}

	if ( !bFound )
	{
		SetError( "Invalid file pointer" );
		return (false);	
	}

	delete pFile;

	// Clear error
	ClearError();
	return (true);
}

bool CDBFS::IsFileOpen( CDBFile *pFile )
{
	if ( !pFile )
		return (false);

	for ( CDBFSOpenFile *pOpenFileCur = m_openFileList.GetFirst(); pOpenFileCur; pOpenFileCur = m_openFileList.GetNext( pOpenFileCur ) )
	{
		if ( pOpenFileCur->GetFile() == pFile )
			return (true);
	}

	return (false);
}

CDBFile *CDBFS::FindFileByName( const CUtil::String &sFilename )
{
	// Scan for file name
	for ( CDBNode *pNode = m_nodeList.GetFirst(); pNode; pNode = m_nodeList.GetNext( pNode ) )
	{
		if ( pNode->GetType() == FS_NODE_FILE )
		{
			if ( pNode->GetName() == sFilename )
				return (CDBFile *)pNode;
		}
	}

	// File not found
	return NULL;
}

uint32_t CDBFS::FileRead( uint8_t *pBuf, uint32_t size, uint32_t nitems, CDBFSOpenFile *pFP )
{
	if ( !pBuf )
	{
		SetError( "Invalid buffer" );
		return (0);
	}

	if ( !pFP )
	{
		SetError( "Invalid file pointer" );
		return (0);
	}

	// Check for file pointer
	bool bFound = false;	
	for ( CDBFSOpenFile *pOpenFileCur = m_openFileList.GetFirst(); pOpenFileCur; pOpenFileCur = m_openFileList.GetNext( pOpenFileCur ) )
	{
		if ( pOpenFileCur == pFP )
		{
			bFound = true;
			break;
		}
	}
	
	if ( !bFound )
	{
		SetError( "Invalid file pointer" );
		return (0);
	}
	

	int32_t filePos = pFP->GetFilePosition();
	CDBFile *pDBFile = pFP->GetFile();

	if ( !pDBFile )
	{
		SetError( "Invalid file pointer" );
		return (0);
	}	

	uint32_t fileReadAmount = (size*nitems);
	uint32_t fileReadActual = 0;

	uint8_t readStatus;

	if ( (readStatus = pDBFile->ReadData( filePos, pBuf, fileReadAmount, fileReadActual )) != FILE_READ_OK )
	{
		SetError( "Read error" );
		return (fileReadActual);
	}

	// Clear error
	ClearError();

	return (fileReadActual);
}

uint32_t CDBFS::FileWrite( uint8_t *pBuf, uint32_t size, uint32_t nitems, CDBFSOpenFile *pFP )
{
	if ( !pBuf )
	{
		SetError( "Invalid buffer" );
		return (0);
	}

	if ( !pFP )
	{
		SetError( "Invalid file pointer" );
		return (0);
	}

	// Check for file pointer
	bool bFound = false;	
	for ( CDBFSOpenFile *pOpenFileCur = m_openFileList.GetFirst(); pOpenFileCur; pOpenFileCur = m_openFileList.GetNext( pOpenFileCur ) )
	{
		if ( pOpenFileCur == pFP )
		{
			bFound = true;
			break;
		}
	}
	
	if ( !bFound )
	{
		SetError( "Invalid file pointer" );
		return (0);
	}
	
	// Check to make sure file is opened writeable
	if ( pFP->GetMode() != FILE_OPEN_WRITE )
	{
		SetError( "File opened read only" );
		return (0);
	}

	int32_t filePos = pFP->GetFilePosition();
	CDBFile *pDBFile = pFP->GetFile();

	if ( !pDBFile )
	{
		SetError( "Invalid file pointer" );
		return (0);
	}

	uint32_t fileWriteAmount = (size*nitems);
	uint32_t fileWriteActual = 0;

	uint8_t writeStatus;
	if ( (writeStatus = pDBFile->WriteData( filePos, pBuf, fileWriteAmount, fileWriteActual)) != FILE_WRITE_OK )
	{
		SetError( "Write error" );
		return (fileWriteActual);
	}

	// Clear error
	ClearError();

	return (fileWriteActual);
}

uint32_t CDBFS::FileSeek( CDBFSOpenFile *pFP, int32_t offset, int8_t origin )
{
	if ( !pFP )
	{
		SetError( "Invalid file pointer" );
		return (-1);
	}

	// Check for file pointer
	bool bFound = false;	
	for ( CDBFSOpenFile *pOpenFileCur = m_openFileList.GetFirst(); pOpenFileCur; pOpenFileCur = m_openFileList.GetNext( pOpenFileCur ) )
	{
		if ( pOpenFileCur == pFP )
		{
			bFound = true;
			break;
		}
	}
	
	if ( !bFound )
	{
		SetError( "Invalid file pointer" );
		return (-1);
	}
	
	int32_t filePos = pFP->GetFilePosition();
	CDBFile *pFile = pFP->GetFile();

	if ( !pFile )
	{
		SetError( "Invalid file pointer" );
		return (-1);
	}

	int32_t newPos = 0;
	if ( origin == SEEK_SET )
		newPos = offset;
	else if ( origin == SEEK_CUR )
		newPos = ((int32_t)filePos) + offset;
	else if ( origin == SEEK_END )
		newPos = ((int32_t)pFile->GetFileSize()) + offset;

#ifdef PATCHED_1
	if ( newPos < 0 || newPos > pFile->GetFileSize() )
#else
	if ( newPos > pFile->GetFileSize() )
#endif
	{
		SetError( "Out of range" );
		return (-1);
	} 

	if ( !pFP->SetFilePosition( newPos ) )
	{
		SetError( "Out of range" );
		return (-1);
	}

	// Clear errors
	ClearError();

	return (0);
}
