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

extern "C"
{
#include <libcgc.h>
#include <stdint.h>
#include <stdlib.h>
}

#include "workerprng.h"
#include "gps.h"
#include "packagetracker.h"

#define SKIP_ID_SIZE	(32)
#define MAGIC_PAGE_SIZE	(4096)

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) 
{
	void *secret_page = (void *)secret_page_i;

	// Use magic page to run random number generator
	CPRNG oRNG( (uint32_t *)((uint8_t*)secret_page+SKIP_ID_SIZE), (MAGIC_PAGE_SIZE-SKIP_ID_SIZE) );

	// Pass secret page for debug access for poller
	CPackageTracker oTracker( secret_page );

	// Seed the simulation with RNG data
	oTracker.SeedSimulation( &oRNG );

	// Run GPS Tracker
	oTracker.Run();

	return 0;
}
