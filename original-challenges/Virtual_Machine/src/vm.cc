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
extern "C"
{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#include "clf.h"
#include "vm.h"

CVM::CVM( void *pMagicPage )
	: m_pMagicPage( pMagicPage ), m_oCPU( pMagicPage )
{

}

CVM::~CVM( )
{

}

bool CVM::Init( CCLF *pLoader )
{
	if ( !pLoader )
		return (false);

	if ( pLoader->m_sectionCount == 0 )
		return (false);

	if ( pLoader->m_pSections == NULL )
		return (false);

	// Begin loading
	for ( uint32_t i = 0; i < pLoader->m_sectionCount; i++ )
	{
		uint16_t sectionAddress = pLoader->m_pSections[i].sectionAddress;
		uint16_t sectionSize = pLoader->m_pSections[i].sectionSize;
		uint8_t *pSectionData = pLoader->m_pSections[i].pSectionData;
		uint8_t sectionType = pLoader->m_pSections[i].sectionType;

		uint8_t mmuFlags = 0;
		if ( sectionType == CCLF::SECTION_TYPE_EXECUTE )
			mmuFlags |= MMU_PAGE_READ | MMU_PAGE_EXEC;
		else if ( sectionType == CCLF::SECTION_TYPE_DATA )
			mmuFlags |= MMU_PAGE_READ | MMU_PAGE_WRITE;
		else if ( sectionType == CCLF::SECTION_TYPE_COMMENT )
			continue;

		if ( !m_oMMU.AddMemorySection( sectionAddress, pSectionData, sectionSize, mmuFlags ) )
			return (false);
	}

	// Initialize DMA
	m_oDMA.InitDMA();

	// Initialize CPU
	m_oCPU.Init( &m_oMMU, this, &m_oDMA, pLoader->m_entryAddress );

	CSendDevice *pSendDevice = new CSendDevice( 1 );
	CReadDevice *pReadDevice = new CReadDevice( 2 );

	m_oPeripheralList.AddLast( pSendDevice );
	m_oPeripheralList.AddLast( pReadDevice );

	// Add peripherals
	m_oDMA.AddPeripheral( 1, pSendDevice );
	m_oDMA.AddPeripheral( 2, pReadDevice );

	return (true);
}

bool CVM::Run( void )
{
	m_oCPU.Run();

	if ( m_oCPU.HasException() )
		printf( "Exception: $s\n", m_oCPU.GetExceptionText().c_str() );

	printf( "Registers:\n$s\nEnd Registers\n", m_oCPU.DumpRegisters().c_str() );

	return (true);
}
