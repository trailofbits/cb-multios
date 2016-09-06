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
#define ENABLE_BUFFERED_PRINTF

extern "C"
{
#include <libcgc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <prng.h>
}

#include <cutil_list.h>
#include <cutil_string.h>
#include "simulation.h"
#include "ecm.h"
#include "tcm.h"
#include "common.h"

void RunSimulation( uint8_t *pSecretPage )
{
	CSimulation oSim;

	uint64_t ecmEquipmentID = *((uint64_t*)(pSecretPage));
	uint64_t tcmEquipmentID = *((uint64_t*)(pSecretPage+8));

#if 0 
	printf( "Equipment ID ECM: " );
	PrintHexBytes( pSecretPage, 8 );
	printf( "Equipment ID TCM: " );
	PrintHexBytes( pSecretPage+8, 8 );
#endif

	oSim.AddSimulationComponent( new CECM( oSim.GetLanBus(), ecmEquipmentID ) );
	oSim.AddSimulationComponent( new CTCM( oSim.GetLanBus(), tcmEquipmentID ) );

	oSim.SetupSimulation();

	// Run simulation
	oSim.RunSimulation();	
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) 
{
	void *secret_page = (void *)secret_page_i;

	uint32_t *pPageArray = (uint32_t*)secret_page;
	uint32_t ts = pPageArray[0] + pPageArray[1] + pPageArray[2] + pPageArray[3];
	uint32_t idx = 0;

	ts &= 0x7FFFF;

	printf( "START::TS=$d\n", ts+1452975600 );
	
	bool bDone = false;
	do
	{
		RunSimulation( (uint8_t*)secret_page );

		for (;;)
		{
			if ( idx >= 1024 )
				idx = 0;

			ts += pPageArray[idx];
			
			ts &= 0x7FFFF;

			idx++;

			printf( "Run another simulation (TS=$d) (y/n)? ", ts+1452975600 );
			CUtil::String sLine;

			sLine = ReadLine();

			if ( sLine[0] == 'n' )
			{
				bDone = true;
				break;
			}
			else if ( sLine[0] == 'y' )
			{
				bDone = false;
				break;
			}
		}	
	} while ( !bDone );

	return 0;
}
