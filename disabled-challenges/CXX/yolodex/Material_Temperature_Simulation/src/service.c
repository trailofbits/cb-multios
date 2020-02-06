/*

Author: Joe Rogers <joe@cromulence.co>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_room.h"
#include "cgc_tsim.h"
#include "cgc_tvis.h"
#include "cgc_input.h"

extern double *cgc_TGrid;
extern double *cgc_HGrid;
extern uint32_t cgc_X;
extern uint32_t cgc_Y;
extern uint32_t cgc_Z;

int main(int cgc_argc, char *cgc_argv[]) {

	// Init global vars
	cgc_TGrid = NULL;
	cgc_HGrid = NULL;
	cgc_X = 0;
	cgc_Y = 0;
	cgc_Z = 0;

	// Init Material
	if (cgc_InitMaterial()) {
		cgc__terminate(-1);
	}

	// Determine length of simulation
	if (cgc_GetSimLength()) {
		cgc__terminate(-1);
	}

	// Print Starting Temps
	cgc_GraphTemps(cgc_TGrid);
	cgc_printf("At 0.00000 seconds\n");
	cgc_kbhit();

	// Run the simulation
	cgc_RunSim();

	// Output the results
	cgc_GraphTemps(cgc_TGrid);

	return(0);
}
