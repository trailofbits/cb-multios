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
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include <prng.h>

int rand( void )
{
	return (random_in_range( 0, RAND_MAX-1 ));
}

void srand( unsigned int seed )
{
	seed_prng( seed );
}

int cromu_atoi( const char *pStr )
{
	int value = 0;
	int negative = 0;

	while ( isspace( *pStr ) )
		pStr++;

	if ( *pStr == '\0' )
		return 0;

	if ( *pStr == '-' )
	{
		negative = 1;
		pStr++;
	}

	// Read in string
	while ( isdigit( *pStr ) )
		value = (value * 10) + (*pStr++ - '0');

	if ( negative )
		return (-value);
	else
		return value;	
}

double cromu_atof( char *pStr )
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
	whole = cromu_atoi(pWhole);

	// convert the fractional part
	if (*pFraction != '\0') {
		fraction = cromu_atoi(pFraction);
		while ( pFraction != '\0' && isdigit( *pFraction ) ) {
			fraction /= 10.0;
			pFraction++;
		}
	}

	return ( whole + fraction );
	
}
	

char *strcpy( char *pDest, const char *pSrc )
{
	char *pDestReturn = pDest;

	while ( *pSrc != '\0' )
		*pDest++ = *pSrc++;

	*pDest = '\0'; 

	return (pDestReturn);
}

char *strncpy( char *pDest, const char *pSrc, size_t maxlen )
{
	size_t n;

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

void *memcpy( void *pDest, const void *pSource, size_t nbytes )
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
