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
#ifndef __DATETIME_H__
#define __DATETIME_H__

#include <stdint.h>
#include <string.h>

// Forward declarations
class Date;
class Time;

class Date
{
public:
    Date() : m_day( 1 ), m_month( 1 ), m_year( 1900 ) { };
    ~Date() { };

    void SetDate( uint8_t day, uint8_t month, uint16_t year )
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }

    bool SetDate( const char* pszInStr );
    bool SetDate( const String& instr );
    void FromUnixTimeval( uint32_t timeval );

    String GetString( void ) const;

private:
    uint8_t     m_day;
    uint8_t     m_month;
    uint16_t    m_year;
};

class Time
{
public:
    Time() : m_hour( 0 ), m_minute( 0 ), m_second( 0 ) { };
    Time( uint8_t hour, uint8_t minute, uint8_t second ) : m_hour( hour ), m_minute( minute ), m_second( second ) { };
    ~Time() { };

    void SetTime( uint8_t hour, uint8_t minute, uint8_t second )
    {
        m_hour = hour;
        m_minute = minute;
        m_second = second;
    }

    bool SetTime( const char *pszInStr );
    bool SetTime( const String& inStr );

    void FromUnixTimeval( uint32_t timeval );

    String GetString( void ) const;

private:
    uint8_t     m_hour;
    uint8_t     m_minute;
    uint8_t     m_second;
};

#endif // __DATETIME_H__
