/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#ifndef __TIMEGEN_H__
#define __TIMEGEN_H__

#define START_UNIX_TIMESTAMP	(1452975638)
#define GENERATOR_ROUNDS	(20)

// Unix Timestamp generator, utilizes magic page data
class CTimeGen
{
public:
	CTimeGen( uint32_t *pGeneratorSource, uint32_t generatorSize );
	~CTimeGen( );

	uint32_t GetUnixTimestamp( void );

private:
	uint32_t GetGeneratorMix( void );

private:
	uint32_t *m_pGeneratorSource;
	uint32_t m_generatorSize;

	uint32_t m_lastPos;

	uint32_t m_lastTimestamp;
	uint32_t m_lastMix;
};

#endif // __TIME_GEN_H__
