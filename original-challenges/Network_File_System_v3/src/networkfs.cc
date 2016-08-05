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

#include <cutil_string.h>
#include <cutil_vector.h>

#include "comms.h"
#include "databasefs.h"
#include "networkfs.h"

int strcmp_unsigned( const unsigned char *s1, const unsigned char *s2 )
{
	if (s1 && !s2) {
                return(1);
        }
        if (!s1 && s2) {
                return(-1);
        }
        if (!s1 && !s2) {
                return(0);
        }

        while (*s1 != '\0' && *s2 != '\0') {
                if (*s1 > *s2) {
                        return(1);
                }
                if (*s1 < *s2) {
                        return(-1);
                }
                s1++;
                s2++;
        }
        if (*s1 != '\0' && *s2 == '\0') {
                return(1);
        }
        if (*s1 == '\0' && *s2 != '\0') {
                return(-1);
        }
        return(0);	
}

CNetworkFS::CNetworkFS( CTimeGen *pTimeGen )
	: m_pFS( NULL ), m_pComms( NULL ), m_pTimeGen( pTimeGen ), m_maxFiles( DEFAULT_MAX_FILES )
{

}

CNetworkFS::~CNetworkFS( )
{
	if ( m_pFS )
		delete m_pFS;

	m_pFS = NULL;
}

bool CNetworkFS::Init( CNetworkComm *pComms, uint32_t maxFiles )
{
	if ( pComms == NULL )
		return (false);

	if ( m_pFS )
	{
		delete m_pFS;
		m_pFS = NULL;	
	}

	// Setup comms and access password
	m_pComms = pComms;

	m_maxFiles = maxFiles;

	m_pFS = new CDBFS( m_pTimeGen );

	m_pFS->Init( "rootpasswd", maxFiles );
	m_pFS->AddFileAsRoot( "passwd", (uint8_t*)"root:rootpasswd", 15 );

	return (true);
}

bool CNetworkFS::Run( void )
{
	bool bDone = false;

	if ( !m_pComms )
	{
		SetError( "No comms available!" );
		return (false);
	}

	while ( !bDone )
	{
		// Receive Loop
		
		// Read request
		tRequestHeader oRequestHdr;

		if ( m_pComms->RecvData( (uint8_t*)&oRequestHdr, sizeof(oRequestHdr) ) != sizeof(oRequestHdr) )
		{
			// Exit if no data received
			return (true);
		}

		switch( oRequestHdr.requestType )
		{
		case REQUEST_CFS_LOGIN:
			HandleCFSLogin();
			break;

		case REQUEST_CFS_DIR:
			HandleCFSDir();
			break;
	
		case REQUEST_CFS_READ:
			HandleCFSRead();
			break;
	
		case REQUEST_CFS_WRITE:
			HandleCFSWrite();
			break;

		case REQUEST_CFS_WRITE_APPEND:
			HandleCFSWriteAppend();
			break;

		case REQUEST_CFS_DEL:
			HandleCFSDel();
			break;

		case REQUEST_CFS_RENAME:
			HandleCFSRename();
			break;

		default:
			SetError( "Unknown request type!" );
			break;
		}

		if ( HasError() )
			return (false);
	}

	return (false);
}

void CNetworkFS::SetError( const char *pszError )
{
	m_sErrorText = pszError;
	m_bError = true;
}

void CNetworkFS::HandleCFSLogin( void )
{
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	typedef struct REQUEST_CFS_LOGIN_STRUCT
	{
		uint8_t usernameLen;
		uint8_t passwordLen;
	} __attribute__((packed)) tRequestCFSLogin;

	tRequestCFSLogin oLoginHdr;

	if ( m_pComms->RecvData( (uint8_t*)&oLoginHdr, sizeof(oLoginHdr) ) != sizeof(oLoginHdr) )
	{
		SetError( "Login read error" );
		return;
	}

	// Read in username and password
	char *pszUsername = new char[oLoginHdr.usernameLen+1];
	char *pszPassword = new char[oLoginHdr.passwordLen+1];

	if ( m_pComms->RecvData( (uint8_t*)pszUsername, oLoginHdr.usernameLen ) != oLoginHdr.usernameLen )
	{
		delete pszUsername;
		delete pszPassword;

		SetError( "Login read error" );
		return;
	}

	pszUsername[oLoginHdr.usernameLen] = '\0';

	if ( m_pComms->RecvData( (uint8_t*)pszPassword, oLoginHdr.passwordLen ) != oLoginHdr.passwordLen )
	{
		delete pszUsername;
		delete pszPassword;

		SetError( "Login read error" );
		return;
	}

	pszPassword[oLoginHdr.passwordLen] = '\0';

	CUtil::String sUsername = pszUsername;
	CUtil::String sPassword = pszPassword;

	delete pszUsername;
	delete pszPassword;
	
	// Validate login!
	bool bLoginValid = m_pFS->SetUser( sUsername, sPassword );

	if ( !bLoginValid )
	{
		// Login invalid!!
		SendResponse( REQUEST_CFS_LOGIN, RESPONSE_LOGIN_FAILED, NULL, 0 );
		
		return;
	}

	// Login succeeded
	SendResponse( REQUEST_CFS_LOGIN, RESPONSE_SUCCESS, NULL, 0 );
}

void CNetworkFS::HandleCFSDir( void )
{
	// Directory listing	
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	uint32_t dataSize = 512;

	CUtil::DLL_LIST( CTempFileList, m_oLink ) oSortedList;

	CDBFile *pFile;
	for ( pFile = m_pFS->ListFileFirst( ); pFile; pFile = m_pFS->ListFileNext( pFile ) )
	{
		if ( pFile->GetName().GetLength() > 32 )
			dataSize += pFile->GetName().GetLength();
		else
			dataSize += 32;

		if ( pFile->GetOwner().GetLength() > 32 )
			dataSize += pFile->GetOwner().GetLength();	
		else
			dataSize += 32;

		// Create sorted list
		if ( oSortedList.IsEmpty() )
			oSortedList.AddLast( new CTempFileList( pFile ) );
		else
		{
			// Find the right location
			CTempFileList *pPrevFile = NULL;
			CTempFileList *pCurFile = NULL;
			for ( pCurFile = oSortedList.GetFirst(); pCurFile; pCurFile = oSortedList.GetNext( pCurFile ) )
			{
				if ( strcmp_unsigned( (unsigned char *)pFile->GetName().c_str(), (unsigned char *)pCurFile->m_pFile->GetName().c_str() ) < 0 )
					break;

				pPrevFile = pCurFile;
			}
	
			if ( pPrevFile == NULL )
				oSortedList.AddFirst( new CTempFileList( pFile ) );
			else if ( pPrevFile == pCurFile )
				oSortedList.AddLast( new CTempFileList( pFile ) );
			else
				oSortedList.AddAfter( pPrevFile, new CTempFileList( pFile ) );
		}	

		dataSize += 8;	// Size
		dataSize += 4;  // Mode
		dataSize += 10;  // Timestamp
		dataSize += 5;  // Spaces and newline
	}

	char *pszFileList = new char[dataSize];
	uint32_t pos = 0;

	pos += sprintf( pszFileList, "$-32s $-32s $-8s $-4s $-10s\n", "Filename", "Owner", "Size", "Mode", "Timestamp" );

	uint32_t sendSize = 0;	
	
	CTempFileList *pFileList;	
	for ( pFileList = oSortedList.GetFirst(); pFileList; pFileList = oSortedList.GetNext( pFileList ) )	
	{
		pFile = pFileList->m_pFile;

		char modeStr[6] = "----";

		uint8_t modeBits = pFile->GetModeBits();

		if ( modeBits & FS_MODE_OWNER_READ )
			modeStr[0] = 'r';

		if ( modeBits & FS_MODE_OWNER_WRITE )
			modeStr[1] = 'w';
	
		if ( modeBits & FS_MODE_OTHER_READ )
			modeStr[2] = 'r';
		
		if ( modeBits & FS_MODE_OTHER_WRITE )
			modeStr[3] = 'w';

		pos += sprintf( pszFileList+pos, "$-32s $-32s $-8d $-4s $-10d\n", pFile->GetName().c_str(), pFile->GetOwner().c_str(), pFile->GetFileSize(), modeStr, pFile->GetAccessTime() );
	}

	// Delete all the temporary storage holders
	oSortedList.DeleteAll();

	// Send pos worth of data for response
	SendResponse( REQUEST_CFS_DIR, RESPONSE_SUCCESS, (uint8_t*)pszFileList, pos );

	delete pszFileList;
}

void CNetworkFS::HandleCFSRead( void )
{
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	typedef struct REQUEST_CFS_READ_STRUCT
	{
		uint32_t fileOffset;
		uint16_t readLength;
		uint8_t fileNameLength;
	} __attribute__((packed)) tRequestCFSRead;

	tRequestCFSRead oReadHdr;

	if ( m_pComms->RecvData( (uint8_t*)&oReadHdr, sizeof(oReadHdr) ) != sizeof(oReadHdr) )
	{
		SetError( "Read read error" );
		return;
	}

	char *pszFilename = new char[oReadHdr.fileNameLength+1];

	// Read in filename
	if ( m_pComms->RecvData( (uint8_t*)pszFilename, oReadHdr.fileNameLength ) != oReadHdr.fileNameLength )
	{
		delete pszFilename;

		SetError( "Read read error" );
		return;
	}

	pszFilename[oReadHdr.fileNameLength] = '\0';

	CUtil::String sFilename = pszFilename;
	delete pszFilename;

	// Open file
	CDBFSOpenFile *pFP = m_pFS->OpenFile( sFilename, "r" );

	if ( !pFP )
	{
		SendResponse( REQUEST_CFS_READ, RESPONSE_INVALID_FILE, NULL, 0 );

		return;
	}

	// Seek
	if ( m_pFS->FileSeek( pFP, oReadHdr.fileOffset, SEEK_SET ) != 0 )
	{
		SendResponse( REQUEST_CFS_READ, RESPONSE_SYSTEM_FAILURE, NULL, 0 );

		return;
	}

	// Read
	// Allocate send buffer
	uint8_t *pReadData = new uint8_t[ oReadHdr.readLength ];

	if ( m_pFS->FileRead( pReadData, oReadHdr.readLength, 1, pFP ) == 0 )
	{
		// Read failure
		delete pReadData;

		SendResponse( REQUEST_CFS_READ, RESPONSE_SYSTEM_FAILURE, NULL, 0 );

		return;
	}

	// Close file
	m_pFS->CloseFile( pFP );
	pFP = NULL;

	SendResponse( REQUEST_CFS_READ, RESPONSE_SUCCESS, pReadData, oReadHdr.readLength );

	return;
}

void CNetworkFS::HandleCFSWrite( void )
{
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	typedef struct REQUEST_CFS_WRITE_STRUCT
	{
		uint16_t writeLength;
		uint8_t fileNameLength;
	} __attribute__((packed)) tRequestCFSWrite;

	tRequestCFSWrite oWriteHdr;

	if ( m_pComms->RecvData( (uint8_t*)&oWriteHdr, sizeof(oWriteHdr) ) != sizeof(oWriteHdr) )
	{
		SetError( "Write read error" );
		return;
	}

	char *pszFilename = new char[oWriteHdr.fileNameLength+1];
	uint8_t *pData = new uint8_t[oWriteHdr.writeLength];

	// Read in filename
	if ( m_pComms->RecvData( (uint8_t*)pszFilename, oWriteHdr.fileNameLength ) != oWriteHdr.fileNameLength )
	{
		delete pszFilename;
		delete pData;

		SetError( "Write read error" );
		return;
	}

	pszFilename[oWriteHdr.fileNameLength] = '\0';

	if ( m_pComms->RecvData( pData, oWriteHdr.writeLength ) != oWriteHdr.writeLength )
	{
		delete pszFilename;
		delete pData;

		SetError( "Write read error" );
		return;
	}

	CUtil::String sFilename = pszFilename;
	delete pszFilename;

	// Open file
	CDBFSOpenFile *pFP = m_pFS->OpenFile( sFilename, "w" );

	if ( !pFP )
	{
		delete pData;

		SendResponse( REQUEST_CFS_WRITE, RESPONSE_INVALID_FILE, NULL, 0 );

		return;
	}

	// Seek
	if ( m_pFS->FileSeek( pFP, 0, SEEK_SET ) != 0 )
	{
		delete pData;

		SendResponse( REQUEST_CFS_WRITE, RESPONSE_SYSTEM_FAILURE, NULL, 0 );

		return;
	}

	// Write
	// Send buffer
	if ( m_pFS->FileWrite( pData, oWriteHdr.writeLength, 1, pFP ) == 0 )
	{
		// Write failure
		delete pData;

		SendResponse( REQUEST_CFS_WRITE, RESPONSE_SYSTEM_FAILURE, NULL, 0 );

		return;
	}

	// Free buffer
	delete pData;

	// Close file
	m_pFS->CloseFile( pFP );
	pFP = NULL;

	SendResponse( REQUEST_CFS_WRITE, RESPONSE_SUCCESS, NULL, 0 );

	return;
}

void CNetworkFS::HandleCFSWriteAppend( void )
{
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	typedef struct REQUEST_CFS_WRITE_APPEND_STRUCT
	{
		uint16_t dataLen;
		uint8_t fileNameLength;
	} __attribute__((packed)) tRequestCFSWriteAppend;

	tRequestCFSWriteAppend oWriteAppendHdr;

	if ( m_pComms->RecvData( (uint8_t*)&oWriteAppendHdr, sizeof(oWriteAppendHdr) ) != sizeof(oWriteAppendHdr) )
	{
		SetError( "Write append read error" );
		return;
	}

	uint8_t *pData = new uint8_t[oWriteAppendHdr.dataLen];
	char *pszFilename = new char[oWriteAppendHdr.fileNameLength+1];

	// Read in filename
	if ( m_pComms->RecvData( (uint8_t*)pszFilename, oWriteAppendHdr.fileNameLength ) != oWriteAppendHdr.fileNameLength )
	{
		delete pData;
		delete pszFilename;

		SetError( "Write append read error" );
		return;
	}

	pszFilename[oWriteAppendHdr.fileNameLength] = '\0';

	// Read data
	if ( m_pComms->RecvData( pData, oWriteAppendHdr.dataLen ) != oWriteAppendHdr.dataLen )
	{
		delete pData;
		delete pszFilename;

		SetError( "Write append read error" );
		return;
	}

	CUtil::String sFilename = pszFilename;
	delete pszFilename;

	// Open file (in append mode)
	CDBFSOpenFile *pFP = m_pFS->OpenFile( sFilename, "a" );

	if ( !pFP )
	{
		delete pData;

		SendResponse( REQUEST_CFS_WRITE_APPEND, RESPONSE_INVALID_FILE, NULL, 0 );

		return;
	}

	// Write
	if ( m_pFS->FileWrite( pData, oWriteAppendHdr.dataLen, 1, pFP ) == 0 )
	{
		// Write failure
		delete pData;

		SendResponse( REQUEST_CFS_WRITE_APPEND, RESPONSE_SYSTEM_FAILURE, NULL, 0 );

		return;
	}
	
	// Free buffer
	delete pData;

	// Close file
	m_pFS->CloseFile( pFP );
	pFP = NULL;

	SendResponse( REQUEST_CFS_WRITE_APPEND, RESPONSE_SUCCESS, NULL, 0 );
}

void CNetworkFS::HandleCFSDel( void )
{
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	typedef struct REQUEST_CFS_DELETE_STRUCT
	{
		uint8_t fileNameLength;
	} __attribute__((packed)) tRequestCFSDelete;

	tRequestCFSDelete oDeleteHdr;

	if ( m_pComms->RecvData( (uint8_t*)&oDeleteHdr, sizeof(oDeleteHdr) ) != sizeof(oDeleteHdr) )
	{
		SetError( "Delete read error" );
		return;
	}

	char *pszFilename = new char[oDeleteHdr.fileNameLength+1];

	// Read in filename
	if ( m_pComms->RecvData( (uint8_t*)pszFilename, oDeleteHdr.fileNameLength ) != oDeleteHdr.fileNameLength )
	{
		delete pszFilename;

		SetError( "Delete read error" );
		return;
	}

	pszFilename[oDeleteHdr.fileNameLength] = '\0';

	CUtil::String sFilename = pszFilename;
	delete pszFilename;

	if ( !m_pFS->DeleteFile( sFilename ) )
	{
		SendResponse( REQUEST_CFS_DEL, RESPONSE_DELETE_FAILED, NULL, 0 );

		return;
	}
	
	SendResponse( REQUEST_CFS_DEL, RESPONSE_SUCCESS, NULL, 0 );
}

void CNetworkFS::HandleCFSRename( void )
{
	if ( !m_pFS )
	{
		SetError( "No file system" );
		return;
	}

	typedef struct REQUEST_CFS_RENAME_STRUCT
	{
		uint8_t origFileNameLength;
		uint8_t newFileNameLength;
	} __attribute__((packed)) tRequestCFSRename;

	tRequestCFSRename oRenameHdr;

	if ( m_pComms->RecvData( (uint8_t*)&oRenameHdr, sizeof(oRenameHdr) ) != sizeof(oRenameHdr) )
	{
		SetError( "Rename read error" );
		return;
	}

	char *pszOrigFilename = new char[oRenameHdr.origFileNameLength+1];
	char *pszNewFilename = new char [oRenameHdr.newFileNameLength+1];

	// Read in filename
	if ( m_pComms->RecvData( (uint8_t*)pszOrigFilename, oRenameHdr.origFileNameLength ) != oRenameHdr.origFileNameLength )
	{
		delete pszOrigFilename;
		delete pszNewFilename;

		SetError( "Rename read error" );
		return;
	}

	pszOrigFilename[oRenameHdr.origFileNameLength] = '\0';

	if ( m_pComms->RecvData( (uint8_t*)pszNewFilename, oRenameHdr.newFileNameLength ) != oRenameHdr.newFileNameLength )
	{
		delete pszOrigFilename;
		delete pszNewFilename;

		SetError( "Rename read error" );
		return;
	}

	pszNewFilename[oRenameHdr.newFileNameLength] = '\0';

	CUtil::String sOrigFilename = pszOrigFilename;
	CUtil::String sNewFilename = pszNewFilename;

	delete pszOrigFilename;
	delete pszNewFilename;

	if ( !m_pFS->RenameFile( sOrigFilename, sNewFilename ) )
	{
		SendResponse( REQUEST_CFS_RENAME, RESPONSE_RENAME_FAILED, NULL, 0 );

		return;
	}
	
	SendResponse( REQUEST_CFS_RENAME, RESPONSE_SUCCESS, NULL, 0 );
}

void CNetworkFS::SendResponse( eRequestType requestType, eResponseType responseType, uint8_t *pResponseData, uint16_t responseLength )
{
	tResponseHeader oResponseHdr;

	oResponseHdr.responseType = requestType;
	oResponseHdr.responseCode = responseType;
	oResponseHdr.responseLength = responseLength;

	// Create and send a resopnse -- include header and response data
	m_pComms->SendData( (uint8_t*)&oResponseHdr, sizeof(oResponseHdr) );

	if ( responseLength == 0 )
		return;

	m_pComms->SendData( (uint8_t*)pResponseData, responseLength );
}
