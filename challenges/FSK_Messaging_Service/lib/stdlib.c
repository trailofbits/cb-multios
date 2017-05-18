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
#include "cgc_stdint.h"
#include "cgc_ctype.h"

#include "cgc_prng.h"

#define LONG_MIN (0x80000000L)
#define LONG_MAX (0x7FFFFFFFL)

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

long int cgc_strtol( const char *str, char **endptr, int base )
{
	long int value = 0;
	int neg = 0;

	if ( str == NULL )
		return (0);

	if ( base >= 16 )
		base = 16;

	// Skip whitespace	
	while ( cgc_isspace( *str ) )
		str++;

	if ( *str == '-' )
	{
		neg = 1;
		str++;
	}
	else if ( *str == '+' )
		str++;

	if ( (base == 16 || base == 0) && *str == '0' && (*(str+1) == 'x' || *(str+1) == 'X') )
	{
		str+=2;
		base = 16;
	}
	else if ( (base == 0 || base == 2 ) && *str == '0' && (*(str+1) == 'b' || *(str+1) == 'B') )
	{
		str+=2;
		base = 2;
	}

	if ( base == 0 )
	{
		if ( *str == '0' )
		{
			base = 8;
		}
		else
			base = 10;
	}

	unsigned long cutoff_value = 0;
	if ( neg )
		cutoff_value = -(unsigned long)LONG_MIN;
	else
		cutoff_value = (unsigned long)LONG_MAX;
	long int cutlim_value = cutoff_value % (unsigned long)base;
	
	cutoff_value /= base;

	while ( *str != '\0' )
	{
		int c = *str;

		if ( cgc_isdigit( c ) )
			c -= '0';
		else if ( cgc_isalpha(c) )
		{
			if ( cgc_isupper(c) )
				c -= ('A' - 10);
			else
				c -= ('a' - 10);
		}
		else
			break;
	
		if ( c >= base )
			break;

		if ( value > cutoff_value || (value == cutoff_value && c > cutlim_value) )
			break;
		else
		{
			value *= base;
			value += c;
		}

		str++;	
	}

	// Check if we should set endptr
	if ( endptr )
		*endptr = (char *)str;

	if ( neg )
		return -value;
	else
		return value;	
}
