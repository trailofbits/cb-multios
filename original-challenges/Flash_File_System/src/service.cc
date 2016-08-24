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

#include "nor_flash.h"
#include "flash_fs.h"
#include "comms.h"

#define PAGE_SIZE	(4096)

void TestFS( CNORFlash *pNORFlash )
{
	CFlashFS oFS;

	oFS.Init( pNORFlash );

	int32_t test1FD = oFS.OpenFile( "test.txt", OPEN_MODE_WRITE );
	int32_t test2FD = oFS.OpenFile( "test2.txt", OPEN_MODE_WRITE );
	int32_t test3FD = oFS.OpenFile( "test3.txt", OPEN_MODE_WRITE );

	printf( "Test1 FD is: $d\n", test1FD );
	printf( "Test2 FD is: $d\n", test2FD );
	printf( "Test3 FD is: $d\n", test3FD );

	int32_t retValue = oFS.WriteFile( test1FD, (uint8_t*)"blah", 4 );

	printf( "Ret value is: $d\n", retValue );

	uint8_t testData[2048];
	uint8_t testData2[2048];
	
	retValue = oFS.WriteFile( test1FD, testData, 1792 );

	printf( "Ret value is: $d\n", retValue );

	retValue = oFS.CloseFile( test1FD );

	printf( "Close ret: $d\n", retValue );

	test1FD = oFS.OpenFile( "test.txt", OPEN_MODE_READ );

	printf( "Open read FD is: $d\n", test1FD );

	uint8_t readBlahBuffer[6];
	retValue = oFS.ReadFile( test1FD, readBlahBuffer, 4 );

	printf( "Read return is: $d\n", retValue );
	readBlahBuffer[5] = '\0';
	printf( "Read blah buffer is: $s\n", readBlahBuffer );

	retValue = oFS.DeleteFile( "test.txt" );

	printf( "Delete test.txt ret: $d\n", retValue );

	retValue = oFS.ReadFile( test1FD, readBlahBuffer, 4 );
		
	printf( "Read from FD=1 is: $d\n", retValue );
}
	
typedef struct TEST_COMMAND_RESPONSE
{
	int32_t retValue;
	uint32_t responseLen;
} tTestCommandResponse;

bool SendCommandResponse( tTestCommandResponse *pResponse, uint8_t *pData, uint32_t dataLen )
{
	pResponse->responseLen = dataLen;

	if ( SendData( STDOUT, (uint8_t*)pResponse, sizeof(tTestCommandResponse) ) != sizeof(tTestCommandResponse) )
	{
		// Comm error
		return (false);
	}

	if ( dataLen > 0 )
	{
		if ( SendData( STDOUT, pData, dataLen ) != dataLen )
		{
			// Commm error
			return (false);
		}
	}

	return (true);
}

#define MAX_TEMP_TEST_LEN	4096

bool OpenFileCommand( CFlashFS *pFS )
{
	typedef struct OPEN_FILE_COMMAND
	{
		uint8_t fileNameLen;
		uint8_t openMode;
	} tOpenFileCommand;

	uint8_t openFileName[257];
	tTestCommandResponse oResponse;
	tOpenFileCommand oCommandData;

	if ( RecvData( STDIN, (uint8_t*)&oCommandData, sizeof(oCommandData) ) != sizeof(oCommandData) )
	{
		// Bad command
		return true;
	}

	if ( RecvData( STDIN, openFileName, oCommandData.fileNameLen ) != oCommandData.fileNameLen )
	{
		// Bad command
		return true;
	}

	openFileName[oCommandData.fileNameLen] = '\0';

	int32_t retValue = pFS->OpenFile( (const char *)openFileName, oCommandData.openMode );

	// Set return value
	oResponse.retValue = retValue;

	// Send response!
	SendCommandResponse( &oResponse, (uint8_t*)NULL, 0 );

	return false;
}

bool CloseFileCommand( CFlashFS *pFS )
{
	typedef struct CLOSE_FILE_COMMAND
	{
		int32_t fd;
	} tCloseFileCommand;

	tTestCommandResponse oResponse;
	tCloseFileCommand oCommandData;

	if ( RecvData( STDIN, (uint8_t*)&oCommandData, sizeof(oCommandData) ) != sizeof(oCommandData) )
	{
		// Bad command
		return true;
	}

	int32_t retValue = pFS->CloseFile( oCommandData.fd );

	// Set return value
	oResponse.retValue = retValue;

	// Send response!
	SendCommandResponse( &oResponse, (uint8_t*)NULL, 0 );

	return false;
}

bool ReadFileCommand( CFlashFS *pFS, uint8_t *tempData )
{
	typedef struct READ_FILE_COMMAND
	{
		int32_t fd;
		uint32_t dataLen;
	} tReadFileCommand;

	tTestCommandResponse oResponse;
	tReadFileCommand oCommandData;

	if ( RecvData( STDIN, (uint8_t*)&oCommandData, sizeof(oCommandData) ) != sizeof(oCommandData) )
	{
		// Bad command
		return true;
	}

	if ( oCommandData.dataLen > MAX_TEMP_TEST_LEN )
		oCommandData.dataLen = MAX_TEMP_TEST_LEN;

	int32_t retValue = pFS->ReadFile( oCommandData.fd, tempData, oCommandData.dataLen );

	// Set return value
	oResponse.retValue = retValue;

	// Send response!
	if ( oResponse.retValue <= 0 )
		SendCommandResponse( &oResponse, (uint8_t*)NULL, 0 );
	else
		SendCommandResponse( &oResponse, tempData, oCommandData.dataLen );

	return false;
}

bool WriteFileCommand( CFlashFS *pFS, uint8_t *tempData )
{
	typedef struct WRITE_FILE_COMMAND
	{
		int32_t fd;
		uint32_t dataLen;
	} tWriteFileCommand;

	tTestCommandResponse oResponse;
	tWriteFileCommand oCommandData;

	if ( RecvData( STDIN, (uint8_t*)&oCommandData, sizeof(oCommandData) ) != sizeof(oCommandData) )
	{
		// Bad command
		return true;
	}

	if ( oCommandData.dataLen > MAX_TEMP_TEST_LEN )
		oCommandData.dataLen = MAX_TEMP_TEST_LEN;

	if ( RecvData( STDIN, tempData, oCommandData.dataLen ) != oCommandData.dataLen )
	{
		// Bad command
		return true;
	}

	int32_t retValue = pFS->WriteFile( oCommandData.fd, tempData, oCommandData.dataLen );

	// Set return value
	oResponse.retValue = retValue;

	// Send response!
	SendCommandResponse( &oResponse, (uint8_t*)NULL, 0 );

	return false;
}	

bool DeleteFileCommand( CFlashFS *pFS )
{
	typedef struct DELETE_FILE_COMMAND
	{
		uint8_t fileNameLen;
	} tDeleteFileCommand;

	uint8_t deleteFileName[257];
	tTestCommandResponse oResponse;
	tDeleteFileCommand oCommandData;

	if ( RecvData( STDIN, (uint8_t*)&oCommandData, sizeof(oCommandData) ) != sizeof(oCommandData) )
	{
		// Bad command
		return true;
	}

	if ( RecvData( STDIN, deleteFileName, oCommandData.fileNameLen ) != oCommandData.fileNameLen )
	{
		// Bad command
		return true;
	}

	deleteFileName[oCommandData.fileNameLen] = '\0';

	int32_t retValue = pFS->DeleteFile( (const char *)deleteFileName );

	// Set return value
	oResponse.retValue = retValue;

	// Send response!
	SendCommandResponse( &oResponse, (uint8_t*)NULL, 0 );

	return false;
}	

void SetupDevice( int secret_page_i, CFlashFS *pFS, CNORFlash *pNORFlash )
{
	uint8_t *pMagicPage = (uint8_t*)secret_page_i;

	CNORFlash oFlash;
	CFlashFS oFS;

	// Use magic page data to init device
	uint32_t blockSize, blocksPerSector, sectorCount;
	
	if ( pMagicPage[0] < 0x80 )
		blockSize = 256;
	else
		blockSize = 512;

	blocksPerSector = ((pMagicPage[1] % 3)+2) * 4; // 8, 12, 16

	sectorCount = ((pMagicPage[2] % 32)+128) * 4; // 128 -> 252 sectors
 
	pNORFlash->Init( blockSize, blocksPerSector, sectorCount );

	pFS->Init( pNORFlash );

	printf( "Starting test for device ($d, $d, $d):\n", blockSize, blocksPerSector, sectorCount );
}

void RunTestSystem( CFlashFS *pFS )
{
	uint8_t tempData[MAX_TEMP_TEST_LEN];

	bool bDone = false;
	do
	{
		uint8_t commandNum;
	
		if ( RecvData( STDIN, &commandNum, sizeof(commandNum) ) != sizeof(commandNum) )
			break;

		switch ( commandNum )
		{
		case 0:	// OpenFile
			bDone = OpenFileCommand( pFS );
			break;

		case 1:	// CloseFile
			bDone = CloseFileCommand( pFS );
			break;

		case 2:	// WriteFile
			bDone = WriteFileCommand( pFS, tempData );
			break;

		case 3:	// ReadFile
			bDone = ReadFileCommand( pFS, tempData );
			break;

		case 4:	// DeleteFile
			bDone = DeleteFileCommand( pFS );
			break;

		case 5:
			printf("Stop simulation\n" );
			bDone = true;
			break;

		default:
			printf( "Invalid command\n" );
			bDone = true;
			// Invalid command
			break;
		}
	} while ( !bDone );
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) 
{
	CNORFlash oFlash;
	CFlashFS oFS;

	SetupDevice( secret_page_i, &oFS, &oFlash );
	RunTestSystem( &oFS );
}

#if 0
	CNORFlash oFlash;

	oFlash.Init( 512, 16, 128 );

	printf( "$08X\n", secret_page_i );

	TestFS( &oFlash );

	return (0);
}
#endif
