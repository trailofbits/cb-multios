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
#ifndef __DIVE_H__
#define __DIVE_H__

#include <string.h>

#define DIVE_BIN_COUNT      (128)

class DiveBin
{
public:
    DiveBin() { };
    ~DiveBin() { };

    void SetTimeVal( uint32_t timeval ) { m_timeval = timeval; };
    void SetDepth( uint32_t depth ) { m_depth = depth; };

    uint32_t GetTimeVal( void ) const { return m_timeval; };
    uint32_t GetDepth( void ) const { return m_depth; };

private:
    uint32_t m_timeval;
    uint32_t m_depth;
};

class Dive : public DLItem
{
public:
    Dive() : DLItem(), m_diveBinCount( 0 ) { };
    ~Dive() { };

    void SetDiveSite( const String &sDiveSite ) { m_diveSite = sDiveSite; };
    void SetDate( const Date &oDate ) { m_date = oDate; };
    void SetTime( const Time &oTime  ) { m_time = oTime; };
    void SetLocation( const String &sLocation ) { m_location = sLocation; };
    void SetMaxDepth( uint32_t maxDepth ) { m_maxDepth = maxDepth; };
    void SetAvgDepth( uint32_t avgDepth ) { m_avgDepth = avgDepth; };
    void SetDuration( uint32_t diveDuration ) { m_diveDuration = diveDuration; };
    void SetO2Percentage( uint32_t o2Percentage ) { m_o2Percentage = o2Percentage; };
    void SetStartPressure( uint32_t startPressure ) { m_startPressure = startPressure; };
    void SetEndPressure( uint32_t endPressure ) { m_endPressure = endPressure; };

    const String& GetDiveSite( void ) const { return m_diveSite; };
    const Date& GetDate( void ) const { return m_date; };
    const Time& GetTime( void ) const { return m_time; };
    const String& GetLocation( void ) const { return m_location; };
    uint32_t GetMaxDepth( void ) const { return m_maxDepth; };
    uint32_t GetAvgDepth( void ) const { return m_avgDepth; };
    uint32_t GetDuration( void ) const { return m_diveDuration; };
    uint32_t GetO2Percentage( void ) const { return m_o2Percentage; };
    uint32_t GetStartPressure( void ) const { return m_startPressure; };
    uint32_t GetEndPressure( void ) const { return m_endPressure; };

    uint32_t GetBinCount( void ) const { return m_diveBinCount; };
    uint32_t AddDiveBin( uint32_t timeval, uint32_t depth );
    const DiveBin& GetDiveBin( uint32_t index ) const { return m_diveBins[index]; };

private:
    DiveBin m_diveBins[DIVE_BIN_COUNT];
    uint32_t m_diveBinCount;

    String m_diveSite;
    Date m_date;
    Time m_time;
    String m_location;
    uint32_t m_maxDepth;
    uint32_t m_avgDepth;
    uint32_t m_diveDuration;
    uint32_t m_o2Percentage;
    uint32_t m_startPressure;
    uint32_t m_endPressure;
};

#endif // __DIVE_H___
