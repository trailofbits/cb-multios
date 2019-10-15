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
#include "cgc_stdlib.h"
#include "cgc_ctype.h"
#include "cgc_stdint.h"


uint64_t randState[512];
uint32_t randIndex;
uint8_t a, b, c;
uint64_t mult;

void cgc_srand(void)
{
	cgc_memcpy((uint8_t *)&randState, (uint8_t *)0x4347c000, sizeof(randState));
	randIndex = 0;
	a = 12;
	b = 25;
	c = 27;
	mult = *(uint64_t *)0x4347c004;
}

uint32_t cgc_rand( void )
{	
	uint64_t r = randState[randIndex];
	r = r ^ (r >> a);
	r = r ^ (r << b);
	r = r ^ (r >> c);
	randState[randIndex++] = r;
	randIndex = randIndex % 512;
	uint64_t big = (uint64_t)r * mult;
	return ((r * mult) >> 32);
}

uint32_t cgc_random_in_range(uint32_t min, uint32_t max)
{
	if (min > max)
		return 0;
	if (min == max)
		return min;

	uint32_t value;
	uint32_t delta = max - min;

	uint32_t scale_divider = (0xffffffff) / delta;
	value = cgc_rand();
	return min + (value / scale_divider);
}


int cgc_atoi( const char *pStr )
{
	int value = 0;
	int negative = 0;

	while ( cgc_isspace( *pStr ) )
		pStr++;

	if ( *pStr == '\0' )
		return 0;

	if ( *pStr == '-' )
	{
		negative = 1;
		pStr++;
	}

	// Read in string
	while ( cgc_isdigit( *pStr ) )
		value = (value * 10) + (*pStr++ - '0');

	if ( negative )
		return (-value);
	else
		return value;	
}

double cgc_atof( char *pStr )
{
	double whole;
	double fraction = 0.0;
	char *pWhole = pStr;
	char *pFraction;
	
	// find the decimal point
	pFraction = pStr;
	while ( *pFraction != '\0' ) 
	{
		if (*pFraction == '.')
		{
			*pFraction = '\0';
			pFraction++;
			break;
		}
		pFraction++;
	}
	
	// convert the whole part
	whole = cgc_atoi(pWhole);

	// convert the fractional part
	if (*pFraction != '\0') {
		fraction = cgc_atoi(pFraction);
		while ( pFraction != '\0' && cgc_isdigit( *pFraction ) ) {
			fraction /= 10.0;
			pFraction++;
		}
	}

	return ( whole + fraction );
	
}
	

char *cgc_strcpy( char *pDest, const char *pSrc )
{
	char *pDestReturn = pDest;

	while ( *pSrc != '\0' )
		*pDest++ = *pSrc++;

	*pDest = '\0'; 

	return (pDestReturn);
}

char *cgc_strncpy( char *pDest, const char *pSrc, cgc_size_t maxlen )
{
	cgc_size_t n;

	for ( n = 0; n < maxlen; n++ )
	{
		if ( pSrc[n] == '\0' )
			break;

		pDest[n] = pSrc[n];
	}

	for ( ; n < maxlen; n++ )
		pDest[n] = '\0';

	return (pDest);
}

void *cgc_memcpy( void *pDest, const void *pSource, cgc_size_t nbytes )
{
	void *pDestReturn = pDest;

	while ( nbytes >= 4 )
	{
		*((uint32_t*)pDest) = *((uint32_t*)pSource);

		pDest += 4;
		pSource += 4;
		nbytes-=4;		
	}

	while ( nbytes > 0 )
	{
		*((uint8_t*)pDest) = *((uint8_t*)pSource);

		pDest++;
		pSource++;
		nbytes--;
	}

	return (pDestReturn);
}

void cgc_get_cgc_random( void *dest, int size) {
	cgc_random(dest, size, 0);
}
