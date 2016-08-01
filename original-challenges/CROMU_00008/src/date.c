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
#include <stdlib.h>
#include "date.h"

int32_t date_compare( tDateTime date1, tDateTime date2 )
{
    // IF date1 is later than date2 return 1
    // IF date1 is earlier than date2 return -1
    // IF date1 is equal to date2 return 0

    if ( date1.year < date2.year )
        return -1;

    if ( date1.year > date2.year )
        return 1;

    if ( date1.month < date2.month )
        return -1;

    if ( date1.month > date2.month )
        return 1;

    if ( date1.day < date2.day )
        return -1;

    if ( date1.day > date2.day )
        return 1;

    if ( date1.hour < date2.hour )
        return -1;

    if ( date1.hour > date2.hour )
        return 1;

    if ( date1.minute < date2.minute )
        return -1;

    if ( date1.minute > date2.minute )
        return 1;

    if ( date1.second < date2.second )
        return -1;

    if ( date1.second > date2.second )
        return 1;

    // 0 == dates equal
    return 0;
}

int32_t parse_date( const char *str, tDateTime *pDate )
{
    const char *start = str;
    tDateTime tTempDate;

    if ( str == NULL )
        return 0;

    // Consume beginning whitespace
    while ( isspace( *str ) )
        str++;

    // Parse format (mm/dd/yy hh:mi:ss) (24 hour date time format)

    // --------------------
    // Parse month
    if ( isdigit( *str ) )
        tTempDate.month = (*str - '0');
    else
        return 0;

    str++;

    if ( isdigit( *str ) )
    {
        tTempDate.month *= 10;
        tTempDate.month += (*str - '0');
        str++;

        if ( *str != '/' )
            return 0;
    }
    else if ( *str != '/' )
        return 0;

    // Check month
    if ( tTempDate.month == 0 || tTempDate.month > 12 )
        return 0;

    str++;

    // --------------------
    // Parse day
    if ( isdigit( *str ) )
        tTempDate.day = (*str - '0');
    else
        return 0;

    str++;

    if ( isdigit( *str ) )
    {
        tTempDate.day *= 10;
        tTempDate.day += (*str - '0');
        str++;

        if ( *str != '/' )
            return 0;
    }
    else if ( *str != '/' )
        return 0;

    if ( tTempDate.day == 0 || tTempDate.day > 31 )
        return 0;

    str++;

    // --------------------
    // Parse year
    if ( isdigit( *str ) )
        tTempDate.year = (*str - '0');
    else
        return 0;

    str++;

    if ( isdigit( *str ) )
    {
        tTempDate.year *= 10;
        tTempDate.year += (*str - '0');
        str++;
    }
    else if ( !isspace( *str ) )
        return 0;   // Parse error, expecting a space character

    // Normalize the year so that dates less than 28 are for the year 2000 and greater
    if ( tTempDate.year < 28 )
        tTempDate.year += 100;

    while ( isspace( *str ) )
        str++;

    // --------------------
    // Parse hour
    if ( isdigit( *str ) )
        tTempDate.hour = (*str - '0');
    else
        return 0;

    str++;

    if ( isdigit( *str ) )
    {
        tTempDate.hour *= 10;
        tTempDate.hour += (*str - '0');
        str++;

        if ( *str != ':' )
            return 0;
    }
    else if ( *str != ':' )
        return 0;

    // Verify 24-hour format
    if ( tTempDate.hour >= 24 )
        return 0;

    // Advance
    str++;

    // --------------------
    // Parse minute
    if ( isdigit( *str ) )
        tTempDate.minute = (*str - '0');
    else
        return 0;

    str++;

    if ( isdigit( *str ) )
    {
        tTempDate.minute *= 10;
        tTempDate.minute += (*str - '0');
        str++;

        if ( *str != ':' )
            return 0;
    }
    else if ( *str != ':' )
        return 0;

    // Verify minutes are less than 60
    if ( tTempDate.minute >= 60 )
        return 0;

    // Advance
    str++;

    // --------------------
    // Parse second
    if ( isdigit( *str ) )
        tTempDate.second = (*str - '0');
    else
        return 0;

    str++;

    if ( isdigit( *str ) )
    {
        tTempDate.second *= 10;
        tTempDate.second += (*str - '0');
        str++;
    }

    if ( tTempDate.second >= 60 )
        return 0;

    // Copy the parsed temporary date into the passed in argument
    memcpy( (void *)pDate, &tTempDate, sizeof(tDateTime) );

    // Success
    return (str - start);
}

