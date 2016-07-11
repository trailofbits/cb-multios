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

bool Date::SetDate( const char* pszInStr )
{
    uint8_t tempMonth, tempDay;
    uint16_t tempYear;

    if ( pszInStr == NULL )
        return (false);

    while ( isspace( *pszInStr ) )
        pszInStr++;

    tempMonth = 0;
    tempDay = 0;
    tempYear = 0;

    if ( isdigit( *pszInStr ) )
        tempMonth = (*pszInStr - '0');
    else
        return (false);

    pszInStr++;

    if ( isdigit( *pszInStr ) )
    {
        tempMonth *= 10;
        tempMonth += (*pszInStr - '0');
        pszInStr++;
    }

    if ( *pszInStr != '/' )
        return (false);

    if ( tempMonth == 0 || tempMonth > 12 )
        return (false);

    // Advance
    pszInStr++;

    // Parse day format
    if ( isdigit( *pszInStr ) )
        tempDay = (*pszInStr - '0');
    else
        return (false);

    pszInStr++;

    if ( isdigit( *pszInStr ) )
    {
        tempDay *= 10;
        tempDay += (*pszInStr - '0');

        pszInStr++;
    }

    if ( *pszInStr != '/' )
        return (false);

    if ( tempDay == 0 || tempDay > 31 )
        return (false);

    // Advance
    pszInStr++;

    // Parse year
    if ( isdigit( *pszInStr ) )
        tempYear = (*pszInStr - '0');
    else
        return (false);

    pszInStr++;

    if ( isdigit( *pszInStr ) )
    {
        tempYear *= 10;
        tempYear += (*pszInStr - '0');

        pszInStr++;
    }
    else
        return (false);

    if ( isdigit( *pszInStr ) )
    {
        tempYear *= 10;
        tempYear += (*pszInStr - '0');

        pszInStr++;
    }
    else
    {
        // End parsing (2 character date)
        if ( tempYear < 31 )
            tempYear += 2000;
        else
            tempYear += 1900;

        m_month = tempMonth;
        m_day = tempDay;
        m_year = tempYear;
        return (true);
    }

    // 4 Character date
    if ( isdigit( *pszInStr ) )
    {
        tempYear *= 10;
        tempYear += (*pszInStr - '0');

        m_month = tempMonth;
        m_day = tempDay;
        m_year = tempYear;

        return (true);
    }
    else
        return (false);

    return (true);
}

bool Date::SetDate( const String& inStr )
{
    return SetDate( inStr.c_str() );
}

String Date::GetString( void ) const
{
    char tempStr[512];

    sprintf( tempStr, "@d/@d/@d", m_month, m_day, m_year );

    return String( tempStr );
}

void Date::FromUnixTimeval( uint32_t timeval )
{
    // Get days
    uint32_t daysFromEpoch = (timeval / 86400);

    // Calculate year...
    uint32_t last_year = 1970, last_year_days = 0;
    uint32_t cur_year, day_counter;
    for ( cur_year = 1970, day_counter = 0; day_counter <= daysFromEpoch; cur_year++ )
    {
        last_year = cur_year;
        last_year_days = day_counter;

        // Add days based on year
        day_counter += 365;

        if ( IsLeapYear( cur_year ) )
            day_counter++;
    }

    m_year = last_year;

    uint32_t day_in_year = (daysFromEpoch - last_year_days);

    // Now calculate month
    uint32_t last_month = 1, last_month_days = 0;
    uint32_t cur_month;
    for ( cur_month = 1, day_counter = 0; day_counter <= day_in_year; cur_month++ )
    {
        last_month = cur_month;
        last_month_days = day_counter;

        day_counter += DaysInMonth( cur_month, m_year );
    }

    m_month = last_month;

    // Now find day -- this is just the days remaining
    m_day = (day_in_year - last_month_days)+1;
}

bool Time::SetTime( const char *pszInStr )
{
    uint8_t tempHour, tempMinute, tempSecond;

    tempHour = 0;
    tempMinute = 0;
    tempSecond = 0;

    if ( pszInStr == NULL )
        return (false);

    while ( isspace( *pszInStr ) )
        pszInStr++;

    if ( isdigit( *pszInStr ) )
        tempHour = (*pszInStr - '0');
    else
        return (false);

    pszInStr++;

    if ( isdigit( *pszInStr ) )
    {
        tempHour *= 10;
        tempHour += (*pszInStr - '0');
        pszInStr++;
    }

    if ( *pszInStr != ':' )
        return (false);

    pszInStr++;

    if ( tempHour >= 24 )
        return (false);

    if ( isdigit( *pszInStr ) )
        tempMinute = (*pszInStr - '0');
    else
        return (false);

    pszInStr++;

    if ( isdigit( *pszInStr ) )
    {
        tempMinute *= 10;
        tempMinute += (*pszInStr - '0');
        pszInStr++;
    }

    if ( *pszInStr != ':' )
        return (false);

    pszInStr++;

    if ( tempMinute >= 60 )
        return (false);

    if ( isdigit( *pszInStr ) )
        tempSecond = (*pszInStr - '0');
    else
        return (false);

    pszInStr++;

    if ( isdigit( *pszInStr ) )
    {
        tempSecond *= 10;
        tempSecond += (*pszInStr - '0');
        pszInStr++;
    }

    if ( tempSecond >= 60 )
        return (false);

    m_hour = tempHour;
    m_minute = tempMinute;
    m_second = tempSecond;

    return (true);
}

bool Time::SetTime( const String &inStr )
{
    return SetTime( inStr.c_str() );
}

String Time::GetString( void ) const
{
    char tempStr[512];

    sprintf( tempStr, "@02d:@02d:@02d", m_hour, m_minute, m_second );

    return String( tempStr );
}

void Time::FromUnixTimeval( uint32_t timeval )
{
    uint32_t dayRemainder = timeval % 86400;

    uint32_t hour = (dayRemainder / 3600);
    uint32_t second = (dayRemainder % 60);
    uint32_t minute = ((dayRemainder / 60) % 60);

    m_hour = hour;
    m_minute = minute;
    m_second = second;
}
