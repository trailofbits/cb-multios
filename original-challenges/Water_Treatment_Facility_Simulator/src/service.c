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
#include <libcgc.h>
#include "stdlib.h"
#include "plant.h"
#include "plant_system.h"
#include "menu.h"
#include "sim.h"
#include "stdio.h"
#include "prng.h"

extern PlantSystem Effluent;
uint8_t SimStepCount = 0;

const char *rand_page = (const char *)0x4347C000;

int main(void) {
	char buf[32];

	// init the PRNG
	seed_prng(*(unsigned int *)rand_page);

	// init the simulation
	InitPlant();

	// Run a simulation step to prime the system
	RunSimStep();

	// Print the plant schematic
	PrintPlantSchematic(); 

	// Print the current plant status
	PrintPlantStatus();

	// Print inital banner
	PrintSystemBanner();

	// Run the simulation loop
	while (SimStepCount < 254) {

		// Allow the operator to adjust plant parameters
		if (!PrintMenu()) {
			break;
		}

		// Run a simulation step
		if (!RunSimStep()) {
			cromu_puts("A valve's output percentages don't total to at least 100%.  Can't run the simulation.");
			continue;
		}
		SimStepCount++;

		// Enforce water quality standards
		CheckEffluentQuality();

		// Adjust Influent 
		RandomInfluent();

	}

	// see if the sim ran for at least 24 hours
	if (SimStepCount >= 24) {
		if (Effluent.QualityFailures > 5) {
			cromu_printf("There were $d hours with sub-standard water quality levels. You Failed!\n", Effluent.QualityFailures);
		} else {
			SimulateEffluent();
			cromu_puts("Congratulations!  You've successfully operated the plant for 24 hours.  You Win!");
		}
	} else {
		cromu_puts("Ending simulation at less than 24 hours.");
	}
	
	return(0);

}
