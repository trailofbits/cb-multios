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
#include "libcgc.h"
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_prng.h"
#include "cgc_fs.h"
}

#include "cgc_cutil_string.h"

#include "cgc_timegen.h"
#include "cgc_comms.h"
#include "cgc_networkfs.h"

#define PAGE_SIZE	(4096)

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

	CTimeGen *pTimeGen;

	pTimeGen = new CTimeGen( (uint32_t *)secret_page_i, (PAGE_SIZE / sizeof(uint32_t)) );	

	CNetworkComm oComms( STDIN, STDOUT );

	CNetworkFS oNFS( pTimeGen );

	if ( !oNFS.Init( &oComms, 10 ) )
	{
		cgc_printf( "Failed to initialize!\n" );

		delete pTimeGen;
		return (-1);
	}

	if ( !oNFS.Run( ) )
	{
		if ( oNFS.HasError() )
		{
			cgc_printf( "Network File System error: %s\n", oNFS.GetError().c_str() );
		
			delete pTimeGen;
			return (-1);
		}
	}

	delete pTimeGen;
	return 0;
}
