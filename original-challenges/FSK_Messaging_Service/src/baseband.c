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
#include "baseband.h"
#include "packet.h"
#include "common.h"

#include <libcgc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void init_baseband( tBasebandState *pState )
{
	pState->cdrState.cdrState = CDR_STATE_NODATA;
	pState->cdrState.lastBitValue = 0;
	pState->cdrState.samplesPerClock = 0.0;
	pState->cdrState.sampleCounter = 0;
	pState->cdrState.preambleCounter = 0;

	pState->packetState.packetState = PACKET_STATE_NODATA;
	pState->packetState.syncBitPos = 0;
	pState->packetState.lastPreambleBit = 0;
	pState->packetState.packetDataLen = 0;
	pState->packetState.packetDataBytePos = 0;
	pState->packetState.packetDataBitPos = 0;
	pState->packetState.packetCRC = 0;
}

void process_sample( tBasebandState *pState, uint8_t in_sample )
{
	run_cdr( pState, in_sample );
}

void free_run_lock( tBasebandState *pState, uint8_t in_sample )
{
	// Calculate delta
	double delta = (double)pState->cdrState.sampleCounter / (pState->cdrState.samplesPerClock * (double)pState->cdrState.symbolsSinceLastTransition);

	// Maintain clock drift over time
	if ( delta < 1.0 )
		pState->cdrState.samplesPerClock -= 0.1;
	else if ( delta > 1.0 )
		pState->cdrState.samplesPerClock += 0.1;

#if DEBUG_BASEBAND
	printf( "DRIFT[$f,$f]\n", pState->cdrState.samplesPerClock, delta );
#endif
	// Reset transition counter	
	pState->cdrState.symbolsSinceLastTransition = 0;

	// Calculate clocks for next symbol (sample in the middle)
	pState->cdrState.clocksForNextSymbol = (pState->cdrState.samplesPerClock / 2.0);
}

void run_cdr( tBasebandState *pState, uint8_t in_sample )
{
	// Keep counting
	pState->cdrState.sampleCounter++;
	
	if ( pState->cdrState.lastBitValue != in_sample )
	{
		// Transition

		// Check mode
		if ( pState->cdrState.cdrState == CDR_STATE_NODATA )
		{
			pState->cdrState.cdrState = CDR_STATE_PREAMBLE;
			pState->cdrState.samplesPerClock = SAMPLES_PER_DATA;
			pState->cdrState.sampleCounter = 0;
		}
		else if ( pState->cdrState.cdrState == CDR_STATE_PREAMBLE )
		{
#if DEBUG_BASEBAND
			printf( "PA[$d,$d,$d,$f]\n", pState->cdrState.preambleCounter, pState->cdrState.sampleCounter, SAMPLES_PER_DATA, pState->cdrState.samplesPerClock );
#endif	
			
			// Check transition counter within 10% of data rate
			uint16_t sample_counter = pState->cdrState.sampleCounter;

			if ( sample_counter > (SAMPLES_PER_DATA + ((double)SAMPLES_PER_DATA * 0.12)) ||
			     sample_counter < (SAMPLES_PER_DATA - ((double)SAMPLES_PER_DATA * 0.12)) )
			{
				// Outside of 10% of data rate -- do not maintain lock
				pState->cdrState.cdrState = CDR_STATE_NODATA;

#if DEBUG_BASEBAND
				printf( "RESET[PR->NO]\n" );
#endif
			}
			else
			{
				uint16_t current_samples_per_clock = floor( pState->cdrState.samplesPerClock + 0.5 );

				if ( sample_counter < current_samples_per_clock )
					pState->cdrState.samplesPerClock -= 0.2;
				else if ( sample_counter > current_samples_per_clock )
					pState->cdrState.samplesPerClock += 0.2;	

				pState->cdrState.preambleCounter++;

				if ( pState->cdrState.preambleCounter >= PREAMBLE_LOCK_COUNT )
				{
					pState->packetState.packetState = PACKET_STATE_SYNCWORD;
					pState->packetState.syncBitPos = 0;
					pState->packetState.lastPreambleBit = pState->cdrState.lastBitValue;
					
					pState->cdrState.cdrState = CDR_STATE_LOCK;
					pState->cdrState.symbolsSinceLastTransition = 0;

					// Calculate clocks for next symbol (sample in the middle)
					pState->cdrState.clocksForNextSymbol = (pState->cdrState.samplesPerClock / 2.0);
				}
			}	
		}
		else if ( pState->cdrState.cdrState == CDR_STATE_LOCK )
		{
			// Reading data -- free run clock
			free_run_lock( pState, in_sample );
		}
		else
		{
			// Critical error -- unknown state
			_terminate(-3);
		}

		// Remember last bit value
		pState->cdrState.lastBitValue = in_sample;

		// Reset sample counter
		pState->cdrState.sampleCounter = 0;
	}
	else if ( pState->cdrState.cdrState == CDR_STATE_LOCK )
	{
		// Check for a sampling event...
		if ( pState->cdrState.sampleCounter == (uint32_t)round( pState->cdrState.clocksForNextSymbol ) )
		{
			pState->cdrState.clocksForNextSymbol += pState->cdrState.samplesPerClock;

			pState->cdrState.symbolsSinceLastTransition++;

			// Take a sample and process it
			do_sample( pState, in_sample );
		}	
	}
}

void reset_baseband_state( tBasebandState *pState )
{
#if DEBUG_BASEBAND
	printf( "[ERR]Resetting baseband state\n" );
#endif

	// Reset state machines
	pState->cdrState.cdrState = CDR_STATE_NODATA;
	pState->packetState.packetState = PACKET_STATE_NODATA;
	
	pState->cdrState.lastBitValue = 0;
	pState->cdrState.samplesPerClock = 0.0;
	pState->cdrState.sampleCounter = 0;
	pState->cdrState.preambleCounter = 0;

	pState->packetState.syncBitPos = 0;
	pState->packetState.lastPreambleBit = 0;
	pState->packetState.packetDataLen = 0;
	pState->packetState.packetDataBytePos = 0;
	pState->packetState.packetDataBitPos = 0;
	pState->packetState.packetCRC = 0;
}

void do_sample( tBasebandState *pState, uint8_t sample_in )
{
#if DEBUG_BASEBAND
	printf( "SAMPLE[$d]\n", sample_in );
#endif

	uint8_t packet_state = pState->packetState.packetState;

	if ( packet_state == PACKET_STATE_NODATA )
	{
		// Do nothing
	}
	else if ( packet_state == PACKET_STATE_SYNCWORD )
	{
		// Track sync word
		if ( pState->packetState.syncBitPos == 0 )
		{
			if ( sample_in == 1 )
				pState->packetState.syncBitPos = 1;
			else if ( sample_in == pState->packetState.lastPreambleBit )
			{
				// Error! two 0's likely in a row -- not preamble or sync word
				reset_baseband_state( pState );
			}
			else
			{
				// Still in preamble -- remember last preamble bit
				pState->packetState.lastPreambleBit = sample_in;
			}
		}
		else if ( pState->packetState.syncBitPos == 1 )
		{
			if ( sample_in == 0 )
			{
				pState->packetState.lastPreambleBit = 0;
				pState->packetState.syncBitPos = 0; // Still in preamble
			}
			else
				pState->packetState.syncBitPos = 2;
		}
		else
		{
			uint8_t syncBitPos = pState->packetState.syncBitPos;

			if ( pState->packetState.lastPreambleBit == 0 && pState->packetState.syncBitPos == 2 && sample_in == 1 )
			{
				// Got another 1... we were in the preamble one more 1 bit
				pState->packetState.lastPreambleBit = 1;
			}
			else
			{
				if ( sample_in != ((BIT_SYNC_WORD & (1<<(15-syncBitPos))) >> (15-syncBitPos)) )
					reset_baseband_state( pState );
				else
					pState->packetState.syncBitPos++;

				if ( pState->packetState.syncBitPos == 16 )
				{
#if DEBUG_BASEBAND
					printf( "\nSYNC WORD LOCK\n" );
#endif
					// Advance to reading header
					pState->packetState.packetState = PACKET_STATE_HEADER;

					pState->packetState.packetDataBitPos = 0;
					pState->packetState.packetDataBytePos = 0;
					pState->packetState.packetDataLen = 0;
				}
			}
		}
	}
	else if ( packet_state == PACKET_STATE_HEADER )
	{
		// Read in header (8-bits)
		pState->packetState.packetDataLen |= (sample_in & 0x1)<<(7-pState->packetState.packetDataBitPos);

		pState->packetState.packetDataBitPos++;

		if ( pState->packetState.packetDataBitPos == 8 )
		{
			if ( pState->packetState.packetDataLen == 0 )
				reset_baseband_state( pState );
			else
			{
#if DEBUG_BASEBAND
				printf( "PACKET DATA LEN[$d]\n", pState->packetState.packetDataLen );
#endif

				// Advance to data state
				pState->packetState.packetState = PACKET_STATE_DATA;
				pState->packetState.packetDataBitPos = 0;

				// Zero packet data
				memset( pState->packetState.packetData, 0, 255 );
			}
		}	
	}
	else if ( packet_state == PACKET_STATE_DATA )
	{
		// Read in data (up to data length)
		pState->packetState.packetData[pState->packetState.packetDataBytePos] |= ((sample_in & 0x1)<<(7-pState->packetState.packetDataBitPos));

		pState->packetState.packetDataBitPos++;

		if ( pState->packetState.packetDataBitPos == 8 )
		{
#if DEBUG_BASEBAND
			printf( "PACKET BYTE [$x][$d]\n", pState->packetState.packetData[pState->packetState.packetDataBytePos], pState->packetState.packetDataBytePos );
#endif

			pState->packetState.packetDataBitPos = 0;

			pState->packetState.packetDataBytePos++;

			if ( pState->packetState.packetDataBytePos == pState->packetState.packetDataLen )
			{
				// Advance to reading CRC
				pState->packetState.packetState = PACKET_STATE_CRC;

				pState->packetState.packetCRC = 0;
			}
		}
	}
	else if ( packet_state == PACKET_STATE_CRC )
	{
		pState->packetState.packetCRC |= ((sample_in & 0x1)<<(15-pState->packetState.packetDataBitPos));

		pState->packetState.packetDataBitPos++;

		if ( pState->packetState.packetDataBitPos == 16 )
		{
#if DEBUG_BASEBAND
			printf( "Packet RX[$d][$X]\n", pState->packetState.packetDataLen, pState->packetState.packetCRC );
#endif

			// Packet received! -- send to packet processing
			receive_packet( pState->packetState.packetData, pState->packetState.packetDataLen, pState->packetState.packetCRC );

			// Reset
			reset_baseband_state( pState );
		}
	}
}
