/*

Author: Jason Williams

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
#ifndef __WORKER_PRNG_H__
#define __WORKER_PRNG_H__

// Needlessly complex PRNG that does unnecessary work (memory allocations/transformations/etc.)
#define PRNG_MATRIX_MAX_SIZE	(4096)
#define DEFAULT_MATRIX_SIZE	(512)

#define MAGIC_PAGE_MASK		(0xA5C1B301)

#define MAGIC_PAGE_SIZE_DWORD	(1024)

class CPRNG
{
public:
	CPRNG( uint32_t *pMagicPage, uint32_t magicPageByteSize );
	~CPRNG( );

	uint32_t GetRandomU32( void );
	uint16_t GetRandomU16( void );
	uint8_t GetRandomU8( void );
	
	uint32_t GetRandomRange( uint32_t start, uint32_t end );

private:
	uint32_t GetRandomInternal( void );

	void GenerateMatrix( void );	

private:
	uint32_t m_matrixPosition;
	uint32_t m_matrixSize;
	uint32_t *m_pGeneratorMatrix;
	
	uint32_t m_magicPagePosition;
	uint32_t m_magicPageSize;	
	uint32_t *m_pMagicPage;
};

#endif // __WORKER_PRNG_H__
