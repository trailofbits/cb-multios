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

#include "timegen.h"

CTimeGen::CTimeGen( uint32_t *pGeneratorSource, uint32_t generatorSize )
	: m_lastTimestamp( START_UNIX_TIMESTAMP ), m_lastMix( 0 ), m_pGeneratorSource( pGeneratorSource ), m_generatorSize( generatorSize ), m_lastPos( 0 )
{
	m_pGeneratorSource = new uint32_t[generatorSize];

	memcpy( m_pGeneratorSource, pGeneratorSource, sizeof(uint32_t)*generatorSize );
}

CTimeGen::~CTimeGen( )
{
	if ( m_pGeneratorSource )
		delete m_pGeneratorSource;
}

uint32_t CTimeGen::GetUnixTimestamp( void )
{
	uint32_t newDelta = (GetGeneratorMix());

	newDelta = (newDelta % 120);	// Up to 2 minutes max deltas
	
	m_lastTimestamp = (m_lastTimestamp + newDelta);

	return (m_lastTimestamp);	
}

uint32_t CTimeGen::GetGeneratorMix( void )
{
	uint32_t a = m_lastMix;
	uint32_t b = 0;
	uint32_t c = 0;

	// Do some random math
	uint32_t pos = m_lastPos;
	for ( uint32_t i = 0; i < GENERATOR_ROUNDS; i++ )
	{
		if ( pos >= m_generatorSize )
			pos = 0;

		c = (a * 3);
		b = (c << 7) ^ b;
		a = b + (m_pGeneratorSource[pos++] & 0xAA11AA11) % 731;			
	}

	m_lastPos = pos;

	m_lastMix = ((a >> 13 | (b << 13)) ^ c);

	return (m_lastMix);
}
