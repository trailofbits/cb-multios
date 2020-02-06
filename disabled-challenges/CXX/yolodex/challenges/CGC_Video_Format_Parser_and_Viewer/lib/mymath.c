/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

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
#include "libcgc.h"
#include "cgc_mymath.h"
#include "cgc_stdint.h"

int cgc_expi( int base, int exponent)
{
	int result = 1;

	while( exponent ) {
		result *= base;
		exponent--;
	}

	return result;
}

double cgc_floor( double val )
{
    if ( val > 0.0 )
        return cgc_rint( val + 0.5 ) - 1.0;
    else if ( val < 0.0 )
        return cgc_rint( val - 0.5 ) + 1.0;
    else
        return 0.0;
}

double cgc_round_away_from_zero( double val )
{
    if ( val > 0.0 )
        return cgc_rint( val + 0.5 );
    else if ( val < 0.0 )
        return cgc_rint( val - 0.5 );
    else
        return 0.0;
}

double cgc_round( double val, double n )
{
    // Round to n digits
    n = cgc_rint( n );

    double high_pow10 = cgc_pow( 10, n );
    double low_pow10 = cgc_pow( 10, -n );

    return (cgc_round_away_from_zero( val * high_pow10 ) * low_pow10);
}
