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
#ifndef __NETWORK_FS_H__
#define __NETWORK_FS_H__

#include <cutil_list.h>

#include "databasefs.h"
#include "timegen.h"

class CNetworkComm;
class CDBFS;

class CNetworkFS
{
public:
	static const uint32_t DEFAULT_MAX_FILES = 10;

public:
	CNetworkFS( CTimeGen *pTimeGen );
	~CNetworkFS( );

	bool Init( CNetworkComm *pComms, uint32_t maxFiles );

	bool Run( void );

	void SetError( const char *pszError );

	bool HasError( void ) const { return m_bError; };
	const CUtil::String &GetError( void ) const { return m_sErrorText; };

protected:
	void HandleCFSLogin( void );
	void HandleCFSDir( void );
	void HandleCFSRead( void );
	void HandleCFSWrite( void );
	void HandleCFSWriteAppend( void );
	void HandleCFSDel( void );
	void HandleCFSRename( void );

	
protected:
	typedef enum
	{
		REQUEST_CFS_LOGIN	= 0,
		REQUEST_CFS_DIR		= 1,
		REQUEST_CFS_READ	= 2,
		REQUEST_CFS_WRITE	= 3,
		REQUEST_CFS_WRITE_APPEND = 4,
		REQUEST_CFS_DEL		= 5,
		REQUEST_CFS_RENAME	= 6
	} eRequestType;

	typedef enum
	{
		RESPONSE_SUCCESS	= 0,
		RESPONSE_LOGIN_FAILED 	= 1,
		RESPONSE_SYSTEM_FAILURE	= 2,
		RESPONSE_INVALID_FILE	= 3,
		RESPONSE_DELETE_FAILED	= 4,
		RESPONSE_RENAME_FAILED 	= 5,
		RESPONSE_TOO_MANY_OPEN_FILES = 6	
	} eResponseType;

	typedef struct REQUEST_HEADER
	{
		uint8_t requestType;
	} __attribute__((packed)) tRequestHeader;

	typedef struct RESPONSE_HEADER
	{
		uint8_t responseType;
		uint8_t responseCode;
		uint16_t responseLength;
	} __attribute__((packed)) tResponseHeader;

	void SendResponse( eRequestType, eResponseType, uint8_t *pData, uint16_t dataLen );

private:
	class CTempFileList
	{
	public:
		CTempFileList( CDBFile *pFile )
			: m_pFile( pFile )	
		{

		}

		CDBFile *m_pFile;
		CUtil::DLL_LINK( CTempFileList ) m_oLink;
	};

private:
	CTimeGen *m_pTimeGen;
	CDBFS *m_pFS;
	CNetworkComm *m_pComms;

	uint32_t m_maxFiles;

	bool m_bError;
	CUtil::String m_sErrorText;
};

#endif // __NETWORK_FS_H__
