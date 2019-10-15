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
#ifndef __MMU_H__
#define __MMU_H__

#define MMU_PAGE_NOT_ALLOC	(0)
#define MMU_PAGE_READ		(1)
#define MMU_PAGE_WRITE		(2)
#define MMU_PAGE_EXEC		(4)

#define MMU_PAGE_SIZE		(512)
#define MMU_PAGE_COUNT		((0x10000)/MMU_PAGE_SIZE)

class CMMU
{
public:
	CMMU( );
	~CMMU( );

	bool AddMemorySection( uint16_t address, uint8_t *pData, uint16_t dataLen, uint8_t mmuFlags );

	bool Fetch16( uint16_t address, uint16_t &value );
	bool Read16( uint16_t address, uint16_t &value );
	bool Write16( uint16_t address, uint16_t value );

	bool ReadDMA( uint16_t address, uint8_t *pData, uint16_t amount );
	bool WriteDMA( uint16_t address, uint8_t *pData, uint16_t amount );

private:
	typedef struct MMU_PAGE
	{
		uint8_t *pageData;
		uint8_t mmuFlags;		
	} tMMUPage;

	tMMUPage m_mmuPages[MMU_PAGE_COUNT];
};

#endif // __MMU_H__
