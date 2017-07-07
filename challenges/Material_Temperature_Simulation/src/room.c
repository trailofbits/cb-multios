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
#include "cgc_input.h"
#include "cgc_malloc.h"

#define pGRID(grid,x,y,z) (grid + x + y*cgc_X + z*cgc_X*cgc_Y)

// room dimensions
uint32_t cgc_X;
uint32_t cgc_Y;
uint32_t cgc_Z;

// temperature grid
double *cgc_TGrid;

// heat source grid
double *cgc_HGrid;

// Thermal conductivities
double cgc_TC[8];

// Heat capacities
double cgc_HC[8];

int cgc_ValidStr(char *buf, char *AllowedChars) {

	for (; *buf; buf++) {
		if (!cgc_strchr(AllowedChars, *buf)) {
			return(0);
		}
	}

	return(1);
}

int cgc_ParseDimensions(char *buf) {
	char DimensionChars[] = "0123456789,. ";
	char *x = buf;
	char *y;
	char *z;

	// make sure we got a valid string
	if (!cgc_ValidStr(buf, DimensionChars)) {
		cgc_puts("Invalid characters in dimensions");
		return(-1);
	}

	// cgc_read the cgc_X dimension
	if ((x = cgc_strtok(buf, ",")) == NULL) {
		cgc_puts("Invalid X dimension\n");
		return(-1);
	}
	cgc_X = cgc_atoi(x);

	// cgc_read the cgc_Y dimension
	if ((y = cgc_strtok(NULL, ",")) == NULL) {
		cgc_puts("Invalid Y dimension\n");
		return(-1);
	}
	cgc_Y = cgc_atoi(y);

	// cgc_read the cgc_Z dimension
	if ((z = cgc_strtok(NULL, ",")) == NULL) {
		cgc_puts("Invalid Z dimension\n");
		return(-1);
	}
	cgc_Z = cgc_atoi(z);

	return(0);
}

void cgc_InitAir(void) {

	cgc_TC[0] = .0000; // 0 K
	cgc_TC[1] = .0072; // 80 K
	cgc_TC[2] = .0160; // 161 K
	cgc_TC[3] = .0243; // 242 K
	cgc_TC[4] = .0271; // 323 K
	cgc_TC[5] = .0330; // 403 K
	cgc_TC[6] = .0390; // 484 K
	cgc_TC[7] = .0454; // 565 K

	// density (kg/m^3) * specific heat (J/(Kg*K))
	cgc_HC[0] = 3819;
	cgc_HC[1] = 2865;
	cgc_HC[2] = 1.980*1009.0;
	cgc_HC[3] = 1.379*1004.8;
	cgc_HC[4] = 1.098*1006.2;
	cgc_HC[5] = 0.895*1013.2;
	cgc_HC[6] = 0.740*1025.8;
	cgc_HC[7] = 0.612*1038.1;

	return;
}

void cgc_InitAluminum(void) {

	cgc_TC[0] = 4110; // 0 K
	cgc_TC[1] = 432.0; // 80 K
	cgc_TC[2] = 248.0; // 161 K
	cgc_TC[3] = 235.0; // 242 K
	cgc_TC[4] = 238.0; // 323 K
	cgc_TC[5] = 240.0; // 403 K
	cgc_TC[6] = 236.0; // 484 K
	cgc_TC[7] = 234.0; // 565 K

	// density (kg/m^3) * specific heat (J/(Kg*K))
	cgc_HC[0] = 2712.0*0.050;
	cgc_HC[1] = 2712.0*400.0;
	cgc_HC[2] = 2712.0*700.0;
	cgc_HC[3] = 2712.0*857.4;
	cgc_HC[4] = 2712.0*920.6;
	cgc_HC[5] = 2712.0*955.5;
	cgc_HC[6] = 2712.0*984.8;
	cgc_HC[7] = 2712.0*1024.0;

	return;
}

void cgc_InitCopper(void) {

	cgc_TC[0] = 24900.0; // 9 K
	cgc_TC[1] = 557.0; // 80 K
	cgc_TC[2] = 428.0; // 161 K
	cgc_TC[3] = 406.0; // 242 K
	cgc_TC[4] = 399.0; // 323 K
	cgc_TC[5] = 393.0; // 403 K
	cgc_TC[6] = 388.0; // 484 K
	cgc_TC[7] = 382.0; // 565 K

	// density (kg/m^3) * specific heat (J/(Kg*K))
	cgc_HC[0] = 134.1; // 8940.0*0.015;
	cgc_HC[1] = 2503200.0; // 8940.0*280.0;
	cgc_HC[2] = 3129000.0; // 8940.0*350.0;
	cgc_HC[3] = 3344454.0; // 8940.0*374.1;
	cgc_HC[4] = 3491964.0; // 8940.0*390.6;
	cgc_HC[5] = 3563484.0; // 8940.0*398.6;
	cgc_HC[6] = 3609078.0; // 8940.0*403.7;
	cgc_HC[7] = 3689538.0; // 8940.0*412.7;

	return;
}

// set a custom Thermal Conductivity for the given temperature
void cgc_SetTC(uint32_t i, char *buf) {
	double val;

	val = cgc_cgcatof(buf);
	cgc_TC[i] = val;
}

// set a custom Heat Capacity for the given temperature
void cgc_SetHC(uint32_t i, char *buf) {
	double val;

	val = cgc_cgcatof(buf);
	cgc_HC[i] = val;
}

// define a custom material
#define RELATIVE_PCT (.25)
void cgc_InitCustom(void) {
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

	cgc_puts("Enter the thermal conductivities in W/(m*K) for your material at the following temperatures (Celcius):");
	for (i = 0; i < 8; i++) {
		valid = 0;
		while (!valid) {
			valid = 1;
			cgc_printf("@s: ", temps[i]);
			if (cgc_read_until(buf, "\n", 99) == -1) {
				cgc__terminate(-1);
			}

			val = cgc_cgcatof(buf);
#ifdef PATCHED
			if (val < 0) {
				cgc_puts("Invalid value...must be greater than zero");
				valid = 0;
                return;
			}
#endif
			// make sure the new value is within 25% of the previous value
			if (i > 0) {
				if (cgc_TC[i-1] > 0) {
					if (val > cgc_TC[i-1]) {
						if (val > cgc_TC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					} else if (val < cgc_TC[i-1]) {
						if (val < cgc_TC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					}
				} else if (cgc_TC[i-1] < 0) {
					if (val > cgc_TC[i-1]) {
						if (val > cgc_TC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					} else if (val < cgc_TC[i-1]) {
						if (val < cgc_TC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					}
				}

				if (!valid) {
					cgc_printf("Invalid value...must be within @d% of the previous value\n", (int)(RELATIVE_PCT*100.0));
				}
			}
		}

		// Set the Thermal Conductivity
		cgc_SetTC(i, buf);
	}

	cgc_puts("Enter the heat capacity in J/(m^3*K) for your material when it is at the following temperatures (Celcius):");
	for (i = 0; i < 8; i++) {
		valid = 0;
		while (!valid) {
			valid = 1;
			cgc_printf("@s: ", temps[i]);
			if (cgc_read_until(buf, "\n", 99) == -1) {
				cgc__terminate(-1);
			}

			val = cgc_cgcatof(buf);

#ifdef PATCHED
			if (val < 0) {
				cgc_puts("Invalid value...must be greater than zero");
				valid = 0;
                return;
			}
#endif

			// make sure the new value is within 5% of the previous value
			if (i > 0) {
				if (cgc_HC[i-1] > 0) {
					if (val > cgc_HC[i-1]) {
						if (val > cgc_HC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					} else if (val < cgc_HC[i-1]) {
						if (val < cgc_HC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					}
				} else if (cgc_HC[i-1] < 0) {
					if (val > cgc_HC[i-1]) {
						if (val > cgc_HC[i-1]*(1-RELATIVE_PCT))
							valid = 0;
					} else if (val < cgc_HC[i-1]) {
						if (val < cgc_HC[i-1]*(1+RELATIVE_PCT))
							valid = 0;
					}
				}

				if (!valid) {
					cgc_printf("Invalid value...must be within @d% of the previous value\n", (int)(RELATIVE_PCT*100.0));
				}
			}
		}

		// Set the Heat Capacity
		cgc_SetHC(i, buf);
	}

	return;
}

// allocate an array large enough to hold a temperature grid for the particular material size
int32_t cgc_AllocateGrid(double **grid, uint32_t x, uint32_t y, uint32_t z) {
	cgc_size_t malloc_size = x*y*z*sizeof(double);

	if ((*grid = cgc_calloc(malloc_size, 1)) == NULL) {
		return(-1);
	}

	return(0);

}

int cgc_InitMaterial(void) {
	char buf[100];
	uint32_t x,y,z;
	int8_t isothermic;
	int8_t heat;
	double temperature;
	cgc_size_t malloc_size;
	int8_t material;

	material = 0;
	cgc_puts("For what material would you like to run this simulation?");
	cgc_puts("  1. Air");
	cgc_puts("  2. Aluminum");
	cgc_puts("  3. Copper");
	cgc_puts("  4. Custom");
	while (material < 1 || material > 4) {
		cgc_printf("Selection: ");
		if (cgc_read_until(buf, "\n", 99) == -1) {
			// failed to cgc_read the input
			return(-1);
		}

		material = cgc_atoi(buf);
	}

	// set up the thermal conductivity and heat capacities
	switch(material) {
		case 1:
			cgc_InitAir();
			break;
		case 2:
			cgc_InitAluminum();
			break;
		case 3:
			cgc_InitCopper();
			break;
		case 4:
			cgc_InitCustom();
			break;
		default:
			return(-1);
	}

	// flush any remaining chars from cgc_stdin
	cgc_flush_stdin();

	// Determine the dimensions
	malloc_size = cgc_X*cgc_Y*cgc_Z*sizeof(double);
	while (cgc_X == 0 || cgc_Y == 0 || cgc_Z == 0 || malloc_size > MAX_MALLOC) {
		cgc_printf("How large is the material (X,Y,Z meters): ");
		if (cgc_read_until(buf, "\n", 99) == -1) {
			// failed to cgc_read the input
			return(-1);
		}
		if (cgc_ParseDimensions(buf)) {
			return(-1);
		}

		malloc_size = cgc_X*cgc_Y*cgc_Z*sizeof(double);
	}

	// flush any remaining chars from cgc_stdin
	cgc_flush_stdin();

#ifdef PATCHED
	// one last check to make sure we didn't overflow cgc_size_t
	if ( (cgc_pow(2, 8*sizeof(cgc_size_t)) / ((sizeof(double) * cgc_X * cgc_Y)) <= cgc_Z) ||
		(cgc_pow(2, 8*sizeof(cgc_size_t)) / ((sizeof(double) * cgc_Y * cgc_Z)) <= cgc_X) ||
		(cgc_pow(2, 8*sizeof(cgc_size_t)) / ((sizeof(double) * cgc_X * cgc_Z)) <= cgc_Y) ) {
		cgc_puts("Invalid room dimensions");
		return(-1);
	}
#endif

	// Allocate space for the temperature grid
	if (cgc_AllocateGrid(&cgc_TGrid, cgc_X,cgc_Y,cgc_Z)) {
		return(-1);
	}

	// See if they want to start with an isothermic temperature
	isothermic = -1;
	while (isothermic < 0) {
		cgc_printf("Should the material be isothermic? (y,n): ");
		if (cgc_read_until(buf, "\n", 3) == -1) {
			// failed to cgc_read the input
			cgc_free(cgc_TGrid);
			return(-1);
		}
		if (buf[0] == 'y' || buf[0] == 'cgc_Y') {
			isothermic = 1;
		} else if (buf[0] == 'n' || buf[0] == 'N') {
			isothermic = 0;
		}
	}

	// flush any remaining chars from cgc_stdin
	cgc_flush_stdin();

	if (isothermic) {
		// isothermic, so what temperature value?
		temperature = -274.0;
		while (temperature < MIN_TEMP || temperature > MAX_TEMP) {
			cgc_printf("  What temperature? (@f - @f degrees C): ", MIN_TEMP, MAX_TEMP);
			if (cgc_read_until(buf, "\n", 99) == -1) {
				// failed to cgc_read the input
				cgc_free(cgc_TGrid);
				return(-1);
			}
			temperature = cgc_cgcatof(buf);
		}

		// flush any remaining chars from cgc_stdin
		cgc_flush_stdin();

		// set the room up with that temperature
		for (x = 0; x < cgc_X; x++) {
			for (y = 0; y < cgc_Y; y++) {
				for (z = 0; z < cgc_Z; z++) {
					// temperature converted to Kelvin
					*pGRID(cgc_TGrid,x,y,z) = temperature + 273.15;
				}
			}
		}

	} else {
		// Otherwise, cgc_read in a blob of data and use it to populate
		// the cgc_TGrid
		cgc_printf("  Send the grid temperatures as a comma separated list of Celcius decimal values.\n");
		cgc_printf("  The program will populate the X, then Y, then Z dimensions of the room.\n");
		if (cgc_read_temps(cgc_TGrid)) {
			cgc_free(cgc_TGrid);
			return(-1);
		}
	}

	// Are there any constant engergy/heat sources in the room?
	heat = -1;
	while (heat < 0) {
		cgc_printf("Are there any constant energy sources in the room? (y,n): ");
		if (cgc_read_until(buf, "\n", 3) == -1) {
			// failed to cgc_read the input
			cgc_free(cgc_TGrid);
			return(-1);
		}
		if (buf[0] == 'y' || buf[0] == 'cgc_Y') {
			heat = 1;
		} else if (buf[0] == 'n' || buf[0] == 'N') {
			heat = 0;
		}
	}

	// flush any remaining chars from cgc_stdin
	cgc_flush_stdin();

	if (heat) {
		// allocate a grid to hold the heat source data
		if (cgc_AllocateGrid(&cgc_HGrid,cgc_X,cgc_Y,cgc_Z)) {
			cgc_free(cgc_TGrid);
			return(-1);
		}

		// cgc_read in the data
		cgc_printf("  Send the heat sources as temperatures in a comma separated list of Celcius decimal values.\n");
		cgc_printf("  The program will populate the X, then Y, then Z dimensions of the room.\n");
		cgc_printf("  Send @f for any grid location which doesn't have a heat source.\n", NO_HEAT);
		if (cgc_read_temps(cgc_HGrid)) {
			cgc_free(cgc_TGrid);
			cgc_free(cgc_HGrid);
			return(-1);
		}
	}

	return(0);

}
