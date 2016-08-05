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
#ifndef __BASEBAND_H__
#define __BASEBAND_H__

#include <stdint.h>

#define DEBUG_BASEBAND			(0)

// CDR stands for Clock Data Recovery
#define CDR_STATE_NODATA		(0)
#define CDR_STATE_PREAMBLE		(1)
#define CDR_STATE_LOCK			(2)

#define PACKET_STATE_NODATA		(0)
#define PACKET_STATE_SYNCWORD		(1)
#define PACKET_STATE_HEADER		(2)
#define PACKET_STATE_DATA		(3)
#define PACKET_STATE_CRC		(4)

// Number of preamble bits to receive before locking on the preamble (should start CDR)
#define PREAMBLE_LOCK_COUNT		(15)

#define BIT_SYNC_WORD			0xCFA3

typedef struct
{
	uint8_t cdrState;	// Clock Data Recovery state

	uint8_t lastBitValue;	// The last bit value received (0 or 1)

	double samplesPerClock;	// Number of samples per clock
	double clocksForNextSymbol;	// Number of clock cycles until sampling next symbol	
	uint32_t symbolsSinceLastTransition;	// Number of samples since last transition	
	uint32_t sampleCounter;	// Number of samples recorded between different symbols
	uint32_t preambleCounter;	// Number of preamble bits received
} tCDRState;

typedef struct
{
	uint8_t packetState;	// Packet receiver state machine

	uint8_t lastPreambleBit;// Last bit received for preamble before sync word
	uint8_t syncBitPos;	// Position in the sync word	
	
	uint8_t packetDataLen; 		// Length of the packet data
	uint8_t packetDataBytePos;	// Current position in the receiving packet data
	uint8_t packetDataBitPos;	// Current bit position in the receiving packet data
	uint8_t packetData[256];	// Packet data as being received

	uint16_t packetCRC;		// Received packet CRC
} tPacketState;

typedef struct
{
	tCDRState cdrState;
	tPacketState packetState;
} tBasebandState;

void init_baseband( tBasebandState *pState );
void reset_baseband_state( tBasebandState *pState );

void run_cdr( tBasebandState *pState, uint8_t sample_in );
void process_sample( tBasebandState *pCurState, uint8_t symbol_in ); 
void do_sample( tBasebandState *pState, uint8_t symbol_in );

#endif // __BASEBAND_H__
