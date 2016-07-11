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
#include "input.h"
#include "malloc.h"

#define pGRID(grid,x,y,z) (grid + x + y*X + z*X*Y)

// room dimensions
uint32_t X;
uint32_t Y;
uint32_t Z;

// temperature grid
double *TGrid;

// heat source grid
double *HGrid;

// Thermal conductivities
double TC[8];

// Heat capacities
double HC[8];

int ValidStr(char *buf, char *AllowedChars) {

	for (; *buf; buf++) {
		if (!strchr(AllowedChars, *buf)) {
			return(0);
		}
	}

	return(1);
}

int ParseDimensions(char *buf) {
	char DimensionChars[] = "0123456789,. ";
	char *x = buf;
	char *y;
	char *z;

	// make sure we got a valid string
	if (!ValidStr(buf, DimensionChars)) {
		puts("Invalid characters in dimensions");
		return(-1);
	}

	// read the X dimension
	if ((x = strtok(buf, ",")) == NULL) {
		puts("Invalid X dimension\n");
		return(-1);
	}
	X = atoi(x);

	// read the Y dimension
	if ((y = strtok(NULL, ",")) == NULL) {
		puts("Invalid Y dimension\n");
		return(-1);
	}
	Y = atoi(y);

	// read the Z dimension
	if ((z = strtok(NULL, ",")) == NULL) {
		puts("Invalid Z dimension\n");
		return(-1);
	}
	Z = atoi(z);
	
	return(0);
}

void InitAir(void) {

	TC[0] = .0000; // 0 K
	TC[1] = .0072; // 80 K
	TC[2] = .0160; // 161 K
	TC[3] = .0243; // 242 K
	TC[4] = .0271; // 323 K
	TC[5] = .0330; // 403 K
	TC[6] = .0390; // 484 K
	TC[7] = .0454; // 565 K

	// density (kg/m^3) * specific heat (J/(Kg*K))
	HC[0] = 3819;
	HC[1] = 2865;
	HC[2] = 1.980*1009.0;
	HC[3] = 1.379*1004.8;
	HC[4] = 1.098*1006.2;
	HC[5] = 0.895*1013.2;
	HC[6] = 0.740*1025.8;
	HC[7] = 0.612*1038.1;

	return;
}

void InitAluminum(void) {

	TC[0] = 4110; // 0 K
	TC[1] = 432.0; // 80 K
	TC[2] = 248.0; // 161 K
	TC[3] = 235.0; // 242 K
	TC[4] = 238.0; // 323 K
	TC[5] = 240.0; // 403 K
	TC[6] = 236.0; // 484 K
	TC[7] = 234.0; // 565 K

	// density (kg/m^3) * specific heat (J/(Kg*K))
	HC[0] = 2712.0*0.050;
	HC[1] = 2712.0*400.0;
	HC[2] = 2712.0*700.0;
	HC[3] = 2712.0*857.4;
	HC[4] = 2712.0*920.6;
	HC[5] = 2712.0*955.5;
	HC[6] = 2712.0*984.8;
	HC[7] = 2712.0*1024.0;

	return;
}

void InitCopper(void) {

	TC[0] = 24900.0; // 9 K
	TC[1] = 557.0; // 80 K
	TC[2] = 428.0; // 161 K
	TC[3] = 406.0; // 242 K
	TC[4] = 399.0; // 323 K
	TC[5] = 393.0; // 403 K
	TC[6] = 388.0; // 484 K
	TC[7] = 382.0; // 565 K

	// density (kg/m^3) * specific heat (J/(Kg*K))
	HC[0] = 134.1; // 8940.0*0.015;
	HC[1] = 2503200.0; // 8940.0*280.0;
	HC[2] = 3129000.0; // 8940.0*350.0;
	HC[3] = 3344454.0; // 8940.0*374.1;
	HC[4] = 3491964.0; // 8940.0*390.6;
	HC[5] = 3563484.0; // 8940.0*398.6;
	HC[6] = 3609078.0; // 8940.0*403.7;
	HC[7] = 3689538.0; // 8940.0*412.7;

	return;
}

// set a custom Thermal Conductivity for the given temperature
void SetTC(uint32_t i, char *buf) {
	double val;

	val = cgcatof(buf);
	TC[i] = val;
}

// set a custom Heat Capacity for the given temperature
void SetHC(uint32_t i, char *buf) {
	double val;

	val = cgcatof(buf);
	HC[i] = val;
}

// define a custom material
#define RELATIVE_PCT (.25)
void InitCustom(void) {
	uint32_t i;
	char *temps[] = { 
		"-264.15", 
		"-193.15", 
		"-112.15", 
		" -31.15", 
		"  49.85", 
		" 129.85", 
		" 210.85", 
		" 291.85" };
	char buf[100];
	double val;
	int valid;

	puts("Enter the thermal conductivities in W/(m*K) for your material at the following temperatures (Celcius):");
	for (i = 0; i < 8; i++) {
		valid = 0;
		while (!valid) {
			valid = 1;
			printf("@s: ", temps[i]);
			if (read_until(buf, "\n", 99) == -1) {
				_terminate(-1);
			}

			val = cgcatof(buf);
#ifdef PATCHED
			if (val < 0) {
				puts("Invalid value...must be greater than zero");
				valid = 0;
                return;
			}
#endif
			// make sure the new value is within 25% of the previous value
			if (i > 0) {
				if (TC[i-1] > 0) {
					if (val > TC[i-1]) {
						if (val > TC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					} else if (val < TC[i-1]) {
						if (val < TC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					}
				} else if (TC[i-1] < 0) {
					if (val > TC[i-1]) {
						if (val > TC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					} else if (val < TC[i-1]) {
						if (val < TC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					}
				}

				if (!valid) {
					printf("Invalid value...must be within @d% of the previous value\n", (int)(RELATIVE_PCT*100.0));
				}
			}
		}

		// Set the Thermal Conductivity
		SetTC(i, buf);
	}

	puts("Enter the heat capacity in J/(m^3*K) for your material when it is at the following temperatures (Celcius):");
	for (i = 0; i < 8; i++) {
		valid = 0;
		while (!valid) {
			valid = 1;
			printf("@s: ", temps[i]);
			if (read_until(buf, "\n", 99) == -1) {
				_terminate(-1);
			}
	
			val = cgcatof(buf);

#ifdef PATCHED
			if (val < 0) {
				puts("Invalid value...must be greater than zero");
				valid = 0;
                return;
			}
#endif

			// make sure the new value is within 5% of the previous value
			if (i > 0) {
				if (HC[i-1] > 0) {
					if (val > HC[i-1]) {
						if (val > HC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					} else if (val < HC[i-1]) {
						if (val < HC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					}
				} else if (HC[i-1] < 0) {
					if (val > HC[i-1]) {
						if (val > HC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					} else if (val < HC[i-1]) {
						if (val < HC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					}
				}

				if (!valid) {
					printf("Invalid value...must be within @d% of the previous value\n", (int)(RELATIVE_PCT*100.0));
				}
			}
		}

		// Set the Heat Capacity
		SetHC(i, buf);
	}

	return;
}

// allocate an array large enough to hold a temperature grid for the particular material size
int32_t AllocateGrid(double **grid, uint32_t x, uint32_t y, uint32_t z) {
	size_t malloc_size = x*y*z*sizeof(double);

	if ((*grid = calloc(malloc_size, 1)) == NULL) {
		return(-1);
	}

	return(0);

}

int InitMaterial(void) {
	char buf[100];
	uint32_t x,y,z;
	int8_t isothermic;
	int8_t heat;
	double temperature;
	size_t malloc_size;
	int8_t material;

	material = 0;
	puts("For what material would you like to run this simulation?");
	puts("  1. Air");
	puts("  2. Aluminum");
	puts("  3. Copper");
	puts("  4. Custom");
	while (material < 1 || material > 4) {
		printf("Selection: ");
		if (read_until(buf, "\n", 99) == -1) {
			// failed to read the input
			return(-1);
		}

		material = atoi(buf);
	}

	// set up the thermal conductivity and heat capacities 
	switch(material) {
		case 1:
			InitAir();
			break;
		case 2:
			InitAluminum();
			break;
		case 3:
			InitCopper();
			break;
		case 4:
			InitCustom();
			break;
		default:
			return(-1);
	}

	// flush any remaining chars from stdin
	flush_stdin();

	// Determine the dimensions
	malloc_size = X*Y*Z*sizeof(double);
	while (X == 0 || Y == 0 || Z == 0 || malloc_size > MAX_MALLOC) {
		printf("How large is the material (X,Y,Z meters): ");
		if (read_until(buf, "\n", 99) == -1) {
			// failed to read the input
			return(-1);
		}
		if (ParseDimensions(buf)) {
			return(-1);
		}

		malloc_size = X*Y*Z*sizeof(double);
	}

	// flush any remaining chars from stdin
	flush_stdin();

#ifdef PATCHED
	// one last check to make sure we didn't overflow size_t
	if ( (pow(2, 8*sizeof(size_t)) / ((sizeof(double) * X * Y)) <= Z) ||
		(pow(2, 8*sizeof(size_t)) / ((sizeof(double) * Y * Z)) <= X) ||
		(pow(2, 8*sizeof(size_t)) / ((sizeof(double) * X * Z)) <= Y) ) {
		puts("Invalid room dimensions");
		return(-1);
	}
#endif

	// Allocate space for the temperature grid
	if (AllocateGrid(&TGrid, X,Y,Z)) {
		return(-1);
	}

	// See if they want to start with an isothermic temperature
	isothermic = -1;
	while (isothermic < 0) {
		printf("Should the material be isothermic? (y,n): ");
		if (read_until(buf, "\n", 3) == -1) {
			// failed to read the input
			free(TGrid);
			return(-1);
		}
		if (buf[0] == 'y' || buf[0] == 'Y') {
			isothermic = 1;
		} else if (buf[0] == 'n' || buf[0] == 'N') {
			isothermic = 0;
		}
	}

	// flush any remaining chars from stdin
	flush_stdin();

	if (isothermic) {	
		// isothermic, so what temperature value?
		temperature = -274.0;
		while (temperature < MIN_TEMP || temperature > MAX_TEMP) {
			printf("  What temperature? (@f - @f degrees C): ", MIN_TEMP, MAX_TEMP);
			if (read_until(buf, "\n", 99) == -1) {
				// failed to read the input
				free(TGrid);
				return(-1);
			}
			temperature = cgcatof(buf);
		}

		// flush any remaining chars from stdin
		flush_stdin();

		// set the room up with that temperature
		for (x = 0; x < X; x++) {
			for (y = 0; y < Y; y++) {
				for (z = 0; z < Z; z++) {
					// temperature converted to Kelvin
					*pGRID(TGrid,x,y,z) = temperature + 273.15;
				}
			}
		}

	} else {
		// Otherwise, read in a blob of data and use it to populate
		// the TGrid
		printf("  Send the grid temperatures as a comma separated list of Celcius decimal values.\n");
		printf("  The program will populate the X, then Y, then Z dimensions of the room.\n");
		if (read_temps(TGrid)) {
			free(TGrid);
			return(-1);
		}
	}

	// Are there any constant engergy/heat sources in the room?
	heat = -1;
	while (heat < 0) {
		printf("Are there any constant energy sources in the room? (y,n): ");
		if (read_until(buf, "\n", 3) == -1) {
			// failed to read the input
			free(TGrid);
			return(-1);
		}
		if (buf[0] == 'y' || buf[0] == 'Y') {
			heat = 1;
		} else if (buf[0] == 'n' || buf[0] == 'N') {
			heat = 0;
		}
	}

	// flush any remaining chars from stdin
	flush_stdin();

	if (heat) {
		// allocate a grid to hold the heat source data
		if (AllocateGrid(&HGrid,X,Y,Z)) {
			free(TGrid);
			return(-1);
		}

		// read in the data
		printf("  Send the heat sources as temperatures in a comma separated list of Celcius decimal values.\n");
		printf("  The program will populate the X, then Y, then Z dimensions of the room.\n");
		printf("  Send @f for any grid location which doesn't have a heat source.\n", NO_HEAT);
		if (read_temps(HGrid)) {
			free(TGrid);
			free(HGrid);
			return(-1);
		}
	}

	return(0);

}
