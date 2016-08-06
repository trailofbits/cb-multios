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
#include "common.h"

bool IsLeapYear( uint16_t year )
{
    if ( (year % 400 == 0 || year % 100 != 0) &&
         (year % 4 == 0) )
        return (true);
    else
        return (false);
}

uint8_t DaysInMonth( uint8_t month, uint16_t year )
{
    if ( month == 2 )
    {
        if ( IsLeapYear( year ) )
            return (29);
        else
            return (28);
    }
    else if ( month == 1 || month == 3 || month == 5 ||
              month == 7 || month == 8 || month == 10 ||
              month == 12 )
    {
        return (31);
    }
    else if ( month == 4 || month == 6 || month == 9 ||
              month == 11 )
    {
        return (30);
    }
    else
        return (0); // Error?
}

