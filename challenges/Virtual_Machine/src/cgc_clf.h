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
#ifndef __CLF_H__
#define __CLF_H__

class CCLF
{
public:
	friend class CVM;

public:
	CCLF();
	~CCLF();

	bool LoadFile( uint8_t *pFileData, uint32_t fileSize );

public:
	static const uint32_t MAX_LOADER_FILE_SIZE = 64000;

	static const uint32_t CLF_HEADER_MAGIC = 0xc3585c51;	// push ecx, pop esp, pop eax, ret

	static const uint32_t CLF_MAX_SECTION_COUNT = 10;

private:
	enum 
	{
		SECTION_TYPE_EXECUTE = 0,
		SECTION_TYPE_DATA = 1,
		SECTION_TYPE_COMMENT = 2
	} eSectionType;

	// Section file header
	typedef struct SECTION_FILE_HEADER
	{
		uint8_t sectionType;
		uint16_t sectionSize;
		uint16_t sectionAddress;
		uint32_t fileOffset;
	} __attribute__((packed))  tSectionFileHeader;

	// Section headers define loadable sections, such as execute, data, and comment
	typedef struct SECTION_DATA
	{
		uint8_t sectionType;
		uint16_t sectionSize;
		uint16_t sectionAddress;
		uint8_t *pSectionData;	
	} tSectionData;

	tSectionData *m_pSections;
	uint8_t m_sectionCount;
	uint16_t m_entryAddress;
};

#endif // __CLF_H__
