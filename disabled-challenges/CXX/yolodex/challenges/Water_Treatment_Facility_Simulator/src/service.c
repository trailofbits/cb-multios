/*

Author: Joe Rogers <joe@cromulence.com>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_plant.h"
#include "cgc_plant_system.h"
#include "cgc_menu.h"
#include "cgc_sim.h"
#include "cgc_stdio.h"
#include "cgc_prng.h"

extern PlantSystem cgc_Effluent;
uint8_t cgc_SimStepCount = 0;

const char *rand_page = (const char *)0x4347C000;

int main(int cgc_argc, char *cgc_argv[]) {
	char buf[32];

	// init the PRNG
	cgc_seed_prng(*(unsigned int *)rand_page);

	// init the simulation
	cgc_InitPlant();

	// Run a simulation step to prime the system
	cgc_RunSimStep();

	// Print the plant schematic
	cgc_PrintPlantSchematic(); 

	// Print the current plant status
	cgc_PrintPlantStatus();

	// Print inital banner
	cgc_PrintSystemBanner();

	// Run the simulation loop
	while (cgc_SimStepCount < 254) {

		// Allow the operator to adjust plant parameters
		if (!cgc_PrintMenu()) {
			break;
		}

		// Run a simulation step
		if (!cgc_RunSimStep()) {
			cgc_cromu_puts("A valve's output percentages don't total to at least 100%.  Can't run the simulation.");
			continue;
		}
		cgc_SimStepCount++;

		// Enforce water quality standards
		cgc_CheckEffluentQuality();

		// Adjust Influent 
		cgc_RandomInfluent();

	}

	// see if the sim ran for at least 24 hours
	if (cgc_SimStepCount >= 24) {
		if (cgc_Effluent.QualityFailures > 5) {
			cgc_cromu_printf("There were $d hours with sub-standard water quality levels. You Failed!\n", cgc_Effluent.QualityFailures);
		} else {
			cgc_SimulateEffluent();
			cgc_cromu_puts("Congratulations!  You've successfully operated the plant for 24 hours.  You Win!");
		}
	} else {
		cgc_cromu_puts("Ending simulation at less than 24 hours.");
	}
	
	return(0);

}
