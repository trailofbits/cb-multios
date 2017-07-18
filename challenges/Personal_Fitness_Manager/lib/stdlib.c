/*

Copyright (c) 2016 Cromulence LLC

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
#include "cgc_stdint.h"
#include "cgc_ctype.h"

#include "cgc_prng.h"

int cgc_rand( void )
{
	return (cgc_random_in_range( 0, RAND_MAX-1 ));
}

void cgc_srand( unsigned int seed )
{
	cgc_seed_prng( seed );
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

cgc_size_t cgc_receive_bytes (unsigned char *buffer, cgc_size_t count) 
{
	cgc_size_t TotalBytes = 0;
	cgc_size_t rx_bytes;
	
	if (!buffer) {
		return(0);
	}

	while (TotalBytes < count) {
		if (cgc_receive(STDIN, buffer+TotalBytes, count-TotalBytes, &rx_bytes) != 0) 
		{
			cgc__terminate(0);
		}
		if (rx_bytes == 0) 
		{
			cgc__terminate(0);
		}
		TotalBytes += rx_bytes;
	}

	return(TotalBytes);
}

int cgc_write( void *buffer, cgc_size_t count )
{
	cgc_size_t written;
    int total_written;
    int retval;

    written = 0;
    total_written = 0;

    while (total_written < count) {
	   retval=cgc_transmit(STDOUT, buffer+total_written, count-total_written, &written);

       if (retval != 0)
            return(-1);

       total_written+=written;
    }


	return(count);

}