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
#ifndef __DBFS_H__
#define __DBFS_H__

#include <cutil_list.h>
#include <cutil_string.h>

#include "timegen.h"

#define SEEK_SET		(1)
#define SEEK_CUR		(0)
#define SEEK_END		(2)

#define FS_NODE_FILE		(1)
#define FS_NODE_DIRECTORY	(2)

#define FS_MODE_OWNER_READ	(1)
#define FS_MODE_OWNER_WRITE	(2)
#define FS_MODE_OTHER_READ	(4)
#define FS_MODE_OTHER_WRITE	(8)

// Open modes
#define FILE_OPEN_READ		(1)
#define FILE_OPEN_WRITE		(2)

class CDBNode 
{
public:
	CDBNode( const CUtil::String &sName, const CUtil::String &sOwner, uint8_t modeBits );
	CDBNode( const char *pszName, const char *pszOwner, uint8_t modeBits );
	virtual ~CDBNode( );
	
	const CUtil::String &GetName( void ) const { return m_sName; };
	const CUtil::String &GetOwner( void ) const { return m_sOwner; };
	uint8_t GetModeBits( void ) const { return m_modeBits; };

	virtual uint8_t GetType( void ) const = 0;

	void SetName( const char *pszName ) { m_sName = pszName; };
	void SetOwner( const char *pszOwner ) { m_sOwner = pszOwner; };

	uint32_t GetAccessTime( void ) const { return m_accessTime; };
	void SetAccessTime( uint32_t accessTime ) { m_accessTime = accessTime; };

protected:
	CUtil::String m_sName;
	CUtil::String m_sOwner;
	uint8_t m_modeBits;
	uint32_t m_accessTime;

public:	
	CUtil::DLL_LINK( CDBNode ) m_dbLink;	
};

// 1 MB max file size
#define FILE_CHUNK_SIZE		(4096)
#define FILE_MAX_CHUNKS		(256)
#define MAX_FILE_SIZE		(FILE_CHUNK_SIZE * FILE_MAX_CHUNKS)

#define FILE_WRITE_OK			(0)
#define FILE_WRITE_ERROR_MAX_FILESIZE	(1)
#define FILE_WRITE_PAST_EOF		(2)
#define FILE_WRITE_ERROR		(3)

#define FILE_READ_OK			(0)
#define FILE_READ_EOF			(1)
#define FILE_READ_ERROR			(2)

class CDBFile : public CDBNode
{
public:
	CDBFile( const CUtil::String &sName, const CUtil::String &sOwner, uint8_t modeBits );
	CDBFile( const char *pszName, const char *pszOwner, uint8_t modeBits );
	~CDBFile( );

	uint8_t GetType( void ) const { return (FS_NODE_FILE); };

	int32_t GetFileSize( void ) const { return m_fileSize; };

	uint8_t WriteData( int32_t writePos, uint8_t *pData, uint32_t writeLength, uint32_t &writeActual );
	uint8_t ReadData( int32_t readPos, uint8_t *pData, uint32_t readLength, uint32_t &readActual );

protected:
	typedef struct FILE_CHUNK
	{
		uint8_t chunkData[FILE_CHUNK_SIZE];
	} tFileChunk;

	int32_t m_fileSize;

	tFileChunk *m_pChunks[FILE_MAX_CHUNKS];
};

class CDBFSUser
{
public:
	CDBFSUser( const CUtil::String &sUsername, const CUtil::String &sPassword );
	CDBFSUser( const char *pszUsername, const char *pszPassword );
	~CDBFSUser( );

	const CUtil::String &GetUsername( void ) const { return m_sUsername; };
	const CUtil::String &GetPassword( void ) const { return m_sPassword; };

private:
	CUtil::String m_sUsername;
	CUtil::String m_sPassword;

public:
	CUtil::DLL_LINK( CDBFSUser ) m_fsUserLink;
};

class CDBFSOpenFile
{
public:
	CDBFSOpenFile( CDBFile *pFile, uint8_t openMode );
	~CDBFSOpenFile( );

	CDBFile *GetFile( void ) { return m_pFile; };
	
	int32_t GetFilePosition( void ) const { return m_curFilePos; };
	bool SetFilePosition( int32_t filePosition )
	{
		if ( !m_pFile )
			return (false);

		if ( filePosition > m_pFile->GetFileSize() )
			filePosition = m_pFile->GetFileSize();

		m_curFilePos = filePosition;

		return (true);
	}

	bool SetFilePositionEnd( void )
	{
		if ( !m_pFile )
			return (false);

		m_curFilePos = m_pFile->GetFileSize();

		return (true);	
	}

	uint8_t GetMode( void ) const { return m_openMode; };

private:
	uint8_t m_openMode;
	int32_t m_curFilePos;
	CDBFile *m_pFile;

public:
	CUtil::DLL_LINK( CDBFSOpenFile ) m_openFileLink;
};

// Database File System 
class CDBFS
{
public:
	CDBFS( CTimeGen *pTimeGen );
	~CDBFS( );

	bool Init( CUtil::String sRootPassword, uint32_t maxFiles );

	bool AddFileAsRoot( CUtil::String sFilename, uint8_t *pFileData, uint32_t dataLen );

	CDBFSUser *FindUser( CUtil::String sUsername );

	bool SetUser( CUtil::String sUsername, CUtil::String sPassword );

	bool AddUser( CUtil::String sUsername, CUtil::String sPassword );

	bool DeleteUser( CUtil::String sUsername );

	// Accessor
	bool HasLastError( void ) const { return m_bLastError; };
	const CUtil::String &GetLastError( void ) const { return m_sLastError; };
	
	// FS functions
	bool RenameFile( CUtil::String sOldFilename, CUtil::String sNewFilename );
	bool DeleteFile( CUtil::String sFilename );

	CDBFSOpenFile *OpenFile( CUtil::String sFilename, const char *pszMode );
	bool CloseFile( CDBFSOpenFile *pFile );

	CDBFile *ListFileFirst( void ) { return (CDBFile *)m_nodeList.GetFirst(); };
	CDBFile *ListFileNext( CDBFile *pCur ) { return (CDBFile *)m_nodeList.GetNext( pCur ); };

	uint32_t FileRead( uint8_t *pBuf, uint32_t size, uint32_t nitems, CDBFSOpenFile *pFP );
	uint32_t FileWrite( uint8_t *pBuf, uint32_t size, uint32_t nitems, CDBFSOpenFile *pFP );
	uint32_t FileSeek( CDBFSOpenFile *pFP, int32_t offset, int8_t origin );

private:
	bool IsUserRoot( void )
	{
		if ( m_pCurUser && m_pCurUser->GetUsername() == "root" )
			return (true);
		else
			return (false);
	}

	void SetError( const char *pszError ) { m_bLastError = true; m_sLastError = pszError; };
	void ClearError( void ) { m_bLastError = false; m_sLastError = ""; };

	CDBFile *FindFileByName( const CUtil::String &sFilename );

	bool IsFileOpen( CDBFile *pFile );

	bool IsMaxFilesReached( void ) 
	{
		return (m_curFiles >= m_maxFiles);
	}

	CDBFile *CreateFile( const CUtil::String &sFilename, const CUtil::String &sOwner, uint8_t modeBits )
	{
		CDBFile *pFile = new CDBFile( sFilename, sOwner, modeBits );

		// If access time is available set it	
		if ( m_pTimeGen )
			pFile->SetAccessTime( m_pTimeGen->GetUnixTimestamp() );
	
		m_nodeList.AddLast( pFile );

		return (pFile);
	}

private:
	uint32_t m_maxFiles;
	uint32_t m_curFiles;

	bool m_bLastError;
	CUtil::String m_sLastError;

	CTimeGen *m_pTimeGen;

	CDBFSUser *m_pCurUser;

	// Starting nodes (root of file system tree)
	CUtil::DLL_LIST( CDBNode, m_dbLink )	m_nodeList;	

	// List of users that can access file system
	CUtil::DLL_LIST( CDBFSUser, m_fsUserLink ) m_userList;

	// List of open files for file system
	CUtil::DLL_LIST( CDBFSOpenFile, m_openFileLink ) m_openFileList;
};

#endif // __DBFS_H__
