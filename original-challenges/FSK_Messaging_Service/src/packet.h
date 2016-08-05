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
#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdint.h>

#define MAX_PACKET_LENGTH		(48)
#define MAX_USERNAME_LENGTH		(8)

#define DEBUG_PACKET			(0)

typedef void (*fpPacketTypeHandler)( uint8_t *pPacketData, uint32_t dataLen );

typedef struct
{
	uint8_t packetType;
	fpPacketTypeHandler fpHandler;		
} tPacketTypeHandler;

typedef struct
{
	tPacketTypeHandler *pHandlers;
	uint8_t handlerCount;
} tPacketHandler;

typedef struct PACKET_INFO_STRUCT
{
	uint8_t packetData[MAX_PACKET_LENGTH];
	uint32_t dataLen;
	struct PACKET_INFO_STRUCT *pNextPacket;
	fpPacketTypeHandler fpHandler;		
	uint8_t packetType;
} tSinglePacketData;

typedef struct
{
	tSinglePacketData *pPacketList;
	uint32_t packetCount;
	uint32_t byteCount;
	uint32_t invalidPacketCount;
} tPacketData;

void init_packet_handler( void );
void receive_packet( uint8_t *pData, uint8_t dataLen, uint16_t packetCRC );
void add_new_packet( uint8_t packetType, fpPacketTypeHandler fpHandler, uint8_t *pData, uint8_t dataLen );
void destroy_packet_handler( void );

void display_packets( void );

void HandleBroadcastPacket( uint8_t *pData, uint32_t dataLen );
void HandleChannelPacket( uint8_t *pData, uint32_t dataLen );
void HandlePrivatePacket( uint8_t *pData, uint32_t dataLen );
void HandleConnectPacket( uint8_t *pData, uint32_t dataLen );
void HandleDisconnectPacket( uint8_t *pData, uint32_t dataLen );

#endif // __PACKET_H__
