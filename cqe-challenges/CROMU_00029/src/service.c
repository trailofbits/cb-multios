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
#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "room.h"
#include "tsim.h"
#include "tvis.h"
#include "input.h"

extern double *TGrid;
extern double *HGrid;
extern uint32_t X;
extern uint32_t Y;
extern uint32_t Z;

int main(void) {

	// Init global vars
	TGrid = NULL;
	HGrid = NULL;
	X = 0;
	Y = 0;
	Z = 0;

	// Init Material
	if (InitMaterial()) {
		_terminate(-1);
	}

	// Determine length of simulation
	if (GetSimLength()) {
		_terminate(-1);
	}

	// Print Starting Temps
	GraphTemps(TGrid);
	printf("At 0.00000 seconds\n");
	kbhit();

	// Run the simulation
	RunSim();

	// Output the results
	GraphTemps(TGrid);

	return(0);
}
