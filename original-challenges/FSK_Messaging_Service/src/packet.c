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
#include "common.h"
#include "packet.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

tPacketHandler g_packetHandlers = { NULL, 0 };
tPacketData g_packetData = { NULL, 0, 0, 0 };

void init_packet_handler( void )
{
	g_packetHandlers.pHandlers = (tPacketTypeHandler *)malloc( sizeof(tPacketTypeHandler) * 5 );

	g_packetHandlers.handlerCount = 5;

	tPacketTypeHandler *pTypeHandlers = g_packetHandlers.pHandlers;

	pTypeHandlers[0].packetType = 0;
	pTypeHandlers[0].fpHandler = &HandleBroadcastPacket;

	pTypeHandlers[1].packetType = 1;
	pTypeHandlers[1].fpHandler = &HandleChannelPacket;

	pTypeHandlers[2].packetType = 2;
	pTypeHandlers[2].fpHandler = &HandlePrivatePacket;

	pTypeHandlers[3].packetType = 3;
	pTypeHandlers[3].fpHandler = &HandleConnectPacket;

	pTypeHandlers[4].packetType = 4;
	pTypeHandlers[4].fpHandler = &HandleDisconnectPacket;
}

void destroy_packet_handler( void )
{
	// Free data
	if ( g_packetHandlers.pHandlers )
		free( g_packetHandlers.pHandlers );

	g_packetHandlers.pHandlers = NULL;

	tSinglePacketData *pCur;
	tSinglePacketData *pNext;

	for ( pCur = g_packetData.pPacketList; pCur; pCur = pNext )
	{
		pNext = pCur->pNextPacket;

		free( pCur );
	}

	g_packetData.pPacketList = NULL;
}

uint16_t simple_checksum16( uint8_t *pData, uint16_t dataLen )
{
	// A CRC-16 algorithm with non-standard initial value and polynomial
	uint16_t checksum = 0xbfad;

	while ( dataLen-- > 0 )
	{
		checksum += *pData++;
	}

	return checksum;
}

void receive_packet( uint8_t *pData, uint8_t dataLen, uint16_t packetCRC )
{
	if ( pData == NULL )
		return;

	if ( dataLen == 0 )
		return;

	// Perform Checksum check
	uint16_t check_checksum = simple_checksum16( pData, dataLen );

	// Validate Checksum
	if ( packetCRC != check_checksum )
		return;

#ifdef PATCHED_1
	if ( dataLen > MAX_PACKET_LENGTH+1 )
		return;
#endif

	// Process and receive packet
#if DEBUG_PACKET	
	printf( "Packet received %d!\n", pData[0] );
#endif

	// Handle packet type
	uint8_t packetType = pData[0];
	uint8_t found = 0;
	for ( uint32_t i = 0; i < g_packetHandlers.handlerCount; i++ )
	{
		if ( g_packetHandlers.pHandlers[i].packetType == packetType )
		{
			found = 1;

			add_new_packet( packetType, g_packetHandlers.pHandlers[i].fpHandler, pData+1, dataLen-1 );

			// Record packet statistics
			g_packetData.packetCount++;
			g_packetData.byteCount += (dataLen);
		}
	}

	if ( !found )
	{
		// Error no handler found for this packet type
		g_packetData.invalidPacketCount++;
	}
}

void add_new_packet( uint8_t packetType, fpPacketTypeHandler fpHandler, uint8_t *pData, uint8_t dataLen )
{
	tSinglePacketData *pNewPacket = (tSinglePacketData *)malloc( sizeof(tSinglePacketData) );


	pNewPacket->packetType = packetType;
	pNewPacket->fpHandler = fpHandler;

	pNewPacket->pNextPacket = NULL;
	
	pNewPacket->dataLen = dataLen;
	
	// Copy in the data	
	memcpy( pNewPacket->packetData, pData, dataLen );

	// Add packet to receive list
	if ( g_packetData.pPacketList == NULL )
		g_packetData.pPacketList = pNewPacket;	
	else
	{
		pNewPacket->pNextPacket = g_packetData.pPacketList;
		g_packetData.pPacketList = pNewPacket;
	}
}

void display_packets( void )
{
	tSinglePacketData *pCur = NULL;

	printf( "Total $d bytes received and $d invalid packets.\n", g_packetData.byteCount, g_packetData.invalidPacketCount );
	printf( "Displaying $d received packets:\n", g_packetData.packetCount );

	uint32_t packetNum = 0;
	for ( pCur = g_packetData.pPacketList; pCur; pCur = pCur->pNextPacket )
	{
		// Print display information
		printf( "Displaying packet $d type $d:\n", packetNum, pCur->packetType );

		// Display packet data
		(*pCur->fpHandler)( pCur->packetData, pCur->dataLen );
	
		packetNum++;	
	}
}

void HandleBroadcastPacket( uint8_t *pData, uint32_t dataLen )
{
	if ( pData == NULL )
	{
		printf( "[BROADCAST]No data\n" );
		return;
	}

	if ( dataLen < 1 )
	{
		printf( "[BROADCAST]Missing length\n" );
		return;
	}

	uint8_t fromUserNameLen = pData[0];

	if ( dataLen < fromUserNameLen+2 )
	{
		printf( "[BROADCAST]Invalid message length\n" );
		return;
	}

	if ( fromUserNameLen > MAX_USERNAME_LENGTH )
	{
		printf( "[BROADCAST]Username length was too large\n" );
		return;
	}

	uint8_t broadcastMessageLen = pData[fromUserNameLen+1];

	if ( dataLen != (fromUserNameLen+broadcastMessageLen+2) )
	{
		printf( "[BROADCAST]Message length did not match packet length\n" );
		return;
	}

	// Display message
	char szTemp[256];
	char szUsername[MAX_USERNAME_LENGTH+1];

	memcpy( szUsername, pData+1, fromUserNameLen );
	szUsername[fromUserNameLen] = '\0';

	memcpy( szTemp, pData+fromUserNameLen+2, broadcastMessageLen );
	szTemp[broadcastMessageLen] = '\0';

	printf( "[BROADCAST]From $s::$s\n", szUsername, szTemp );
}

void HandleChannelPacket( uint8_t *pData, uint32_t dataLen )
{
	if ( pData == NULL )
	{
		printf( "[CHANNEL]No data\n" );
		return;
	}

	if ( dataLen < 2 )
	{
		printf( "[CHANNEL]Invalid length\n" );
		return;
	}

	uint8_t fromUserNameLen = pData[0];

	if ( dataLen < fromUserNameLen+3 )
	{
		printf( "[CHANNEL]Invalid message length\n" );
		return;
	}

	if ( fromUserNameLen > MAX_USERNAME_LENGTH )
	{
		printf( "[CHANNEL]Username length was too large\n" );
		return;
	}

	uint8_t channelNumber = pData[fromUserNameLen+1];
	uint8_t channelMessageLen = pData[fromUserNameLen+2];

	if ( dataLen != (fromUserNameLen+channelMessageLen+3) )
	{
		printf( "[CHANNEL]Message length did not match packet length\n" );
		return;
	}

	// Display message
	char szFromUsername[MAX_USERNAME_LENGTH+1];
	char szTemp[256];

	memcpy( szFromUsername, pData+1, fromUserNameLen );
	szFromUsername[fromUserNameLen] = '\0';

	memcpy( szTemp, pData+fromUserNameLen+3, channelMessageLen );
	szTemp[channelMessageLen] = '\0';

	printf( "[CHANNEL $d]Message from $s::$s\n", channelNumber, szFromUsername, szTemp );
}

void HandlePrivatePacket( uint8_t *pData, uint32_t dataLen )
{
	if ( pData == NULL )
	{
		printf( "[PRIVATE MESSAGE]No data\n" );
		return;
	}

	if ( dataLen < 2 )
	{
		printf( "[PRIVATE MESSAGE]Invalid length\n" );
		return;
	}

	uint8_t toUserNameLen = pData[0];

	if ( dataLen < (toUserNameLen+3) )
	{
		printf( "[PRIVATE MESSAGE]Message length did not match packet length\n" );
		return;
	}

	if ( toUserNameLen > MAX_USERNAME_LENGTH )
	{
		printf( "[PRIVATE MESSAGE]Username length was too large\n" );
		return;
	}

	uint8_t fromUserNameLen = pData[toUserNameLen+1];

	if ( dataLen < (toUserNameLen+fromUserNameLen+3) )
	{
		printf( "[PRIVATE MESSAGE]Message length did not match packet length\n" );
		return;
	}

	if ( fromUserNameLen > MAX_USERNAME_LENGTH )
	{
		printf( "[PRIVATE MESSAGE]Username length was too large\n" );
		return;
	}

	uint8_t privateMessageLen = pData[toUserNameLen+fromUserNameLen+2];

	if ( dataLen != (toUserNameLen+fromUserNameLen+privateMessageLen+3) )
	{
		printf( "[PRIVATE MESSAGE]Message length did not match packet length\n" );
		return;
	}

	// Display message
	char szTemp[256];

	char szFromUsername[MAX_USERNAME_LENGTH+1];
	char szToUsername[MAX_USERNAME_LENGTH+1];

	memcpy( szToUsername, pData+1, toUserNameLen );
	szToUsername[toUserNameLen] = '\0';

	memcpy( szFromUsername, pData+toUserNameLen+2, fromUserNameLen );
	szFromUsername[fromUserNameLen] = '\0';

	memcpy( szTemp, pData+toUserNameLen+fromUserNameLen+3, privateMessageLen );
	szTemp[privateMessageLen] = '\0';

	printf( "[PRIVATE MESSAGE]$s to $s::$s\n", szToUsername, szFromUsername, szTemp );
}

void HandleConnectPacket( uint8_t *pData, uint32_t dataLen )
{
	if ( pData == NULL )
	{
		printf( "[CONNECT MESSAGE]No data\n" );
		return;
	}

	if ( dataLen < 1 )
	{
		printf( "[CONNECT MESSAGE]Invalid length\n" );
		return;
	}

	uint8_t connectUserNameLen = pData[0];

	if ( dataLen != (connectUserNameLen+1) )
	{
		printf( "[CONNECT MESSAGE]Message length did not match packet length\n" );
		return;
	}

	if ( connectUserNameLen >= MAX_USERNAME_LENGTH )
	{
		printf( "[CONNECT MESSAGE]Username length was too large\n" );
		return;	
	}

	// Display message
	char szUsername[MAX_USERNAME_LENGTH];

	memcpy( szUsername, pData+1, connectUserNameLen );
	szUsername[connectUserNameLen] = '\0';

	printf( "[CONNECT MESSAGE]$s connected\n", szUsername );	
}

void HandleDisconnectPacket( uint8_t *pData, uint32_t dataLen )
{
	if ( pData == NULL )
	{
		printf( "[DISCONNECT MESSAGE]No data\n" );
		return;
	}

	if ( dataLen < 1 )
	{
		printf( "[DISCONNECT MESSAGE]Invalid length\n" );
		return;
	}

	uint8_t disconnectUserNameLen = pData[0];

	if ( dataLen != (disconnectUserNameLen+1) )
	{
		printf( "[DISCONNECT MESSAGE]Message length did not match packet length\n" );
		return;
	}

	if ( disconnectUserNameLen >= MAX_USERNAME_LENGTH )
	{
		printf( "[DISCONNECT MESSAGE]Username length was too large\n" );
		return;	
	}

	// Display message
	char szUsername[MAX_USERNAME_LENGTH];

	memcpy( szUsername, pData+1, disconnectUserNameLen );
	szUsername[disconnectUserNameLen] = '\0';

	printf( "[DISCONNECT MESSAGE]$s disconnected\n", szUsername );	
}
