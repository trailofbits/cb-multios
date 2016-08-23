/*

Copyright (c) 2015 Cromulence LLC

Authors: Cromulence <cgc@cromulence.com>

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
// This is an implementation of the WELL RNG 1024a random number generator
#include <prng.h>
#include <stdint.h>
#include <string.h>

#define R	32
#define M1	3
#define M2	24
#define M3	10

uint32_t state[R];
uint32_t state_n;

void seed_prng_array( uint32_t *pSeedArray, uint32_t arrayLen )
{
	uint32_t i;

	// CLear initial state
	bzero( (void *)state, R*sizeof(uint32_t) );

	state_n = 0;

	// Only use a maximum of 32 uint32_t's to seed state
	if ( arrayLen > 32 )
		arrayLen = 32;

	for ( i = 0; i < arrayLen; i++ )
		state[i] = pSeedArray[i];

	for ( i = arrayLen; i < R; i++ )
	{
		uint32_t state_value = state[(i-1)&0x1f];

		// Mix in some of the previous state, the current iteration, and multiply by a mersenne prime		
		state[i] = (uint32_t)((state_value ^ (state_value >> 30) + i) * 524287);
	}
}

void seed_prng( uint32_t seedValue )
{
	seed_prng_array( &seedValue, 1 );
}

uint32_t prng( void )
{
	// Get new random
	uint32_t v0 = state[ state_n ];
	uint32_t vM1 = state[ (state_n + M1) & 0x1f ];
	uint32_t vM2 = state[ (state_n + M2) & 0x1f ];
	uint32_t vM3 = state[ (state_n + M3) & 0x1f ];
		
	uint32_t z0 = state[ (state_n+31) & 0x1f ];
	uint32_t z1 = v0 ^ (vM1 ^ (vM1 >> 8));
	uint32_t z2 = (vM2 ^ (vM2 << 19)) ^ (vM3 ^ (vM3 << 14));
	
	uint32_t newV1 = z1 ^ z2;
	uint32_t newV0 = (z0 ^ (z0 << 11)) ^ (z1 ^ (z1 << 7)) ^ (z2 ^ (z2 << 13));

	state[ state_n ] = newV1;
	state[ (state_n+31) & 0x1f ] = newV0;

	state_n = (state_n + 31) & 0x1f;

	return newV0;	
}

// Random [min,max] (note that is inclusive)
uint32_t random_in_range( uint32_t min, uint32_t max )
{
	if ( min > max )
		return 0;

	if ( min == max )
		return min;

	uint32_t random_value;
	uint32_t delta = max - min + 1;

	// Check for [0, 0xffffffff]
	if ( delta == 0 )
		return prng();

	uint32_t scale_divider = (0xffffffff) / delta;
	
	do
	{
		random_value = prng();

		// Pick values until they fall into one of the buckets
	} while ( random_value >= scale_divider * delta);

	// Scale value back down add min and return	
	return min + (random_value / scale_divider);
}
