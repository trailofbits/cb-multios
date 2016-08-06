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
#include <libcgc.h>
#include <mymath.h>
#include <stdint.h>

double floor( double val )
{
    if ( val > 0.0 )
        return rint( val + 0.5 ) - 1.0;
    else if ( val < 0.0 )
        return rint( val - 0.5 ) + 1.0;
    else
        return 0.0;
}

double round_away_from_zero( double val )
{
    if ( val > 0.0 )
        return rint( val + 0.5 );
    else if ( val < 0.0 )
        return rint( val - 0.5 );
    else
        return 0.0;
}

double round( double val, double n )
{
    // Round to n digits
    n = rint( n );

    double high_pow10 = pow( 10, n );
    double low_pow10 = pow( 10, -n );

    return (round_away_from_zero( val * high_pow10 ) * low_pow10);
}

int abs(int num)
{
    if (num > 0)
        return num;
    return (num *= -1);
}
