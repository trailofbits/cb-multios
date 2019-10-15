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
#include "cgc_input.h"
#include "cgc_malloc.h"
#include "cgc_tvis.h"
#include "cgc_room.h"

double SIM_TIME;

extern double *cgc_TGrid;
extern double *cgc_HGrid;
extern uint32_t cgc_X;
extern uint32_t cgc_Y;
extern uint32_t cgc_Z;
double TimeStep;
extern double cgc_TC[8];
extern double cgc_HC[8];

// defined as a actual function here because of gcc double alignment bug
double *cgc_pGRID(double *grid, uint32_t x, uint32_t y, uint32_t z) {
	return (grid + x + y*cgc_X + z*cgc_X*cgc_Y);
}

int32_t cgc_GetSimLength(void) {
	char buf[100];
		
	SIM_TIME = 0.0;
        while (SIM_TIME <= 0.0) {
                cgc_printf("For how long would you like to run the simulation? (s): ");
                if (cgc_read_until(buf, "\n", 99) == -1) {
                        // failed to cgc_read the input
                        return(-1);
                }
		SIM_TIME = cgc_cgcatof(buf);
	}

	return(0);
}

// lookup thermal conductivity for a cell given its temperature
double cgc_L(uint32_t x, uint32_t y, uint32_t z) {
	double temp;
	double Lxyz;
	int index;

	// error handling
	if (x >= cgc_X || y >= cgc_Y || z >= cgc_Z) {
		return(-1);
	}

	// get the temperature of the requested cell
	temp = *cgc_pGRID(cgc_TGrid,x,y,z);

	// calculate the thermal conductivity for that temperature	
	index = temp/80.77;
	Lxyz = cgc_TC[(int)(temp/80.77)];
	
	return(Lxyz);

}

// lookup heat capacity for a cell given its temperature
double cgc_C(uint32_t x, uint32_t y, uint32_t z) {
	double temp;
	double Cxyz;
	int index;

	// error handling
	if (x >= cgc_X || y >= cgc_Y || z >= cgc_Z) {
		return(-1);
	}

	// get the temperature of the requested cell
	temp = *cgc_pGRID(cgc_TGrid,x,y,z);

	// calculate the thermal conductivity for that temperature	
	index = temp/80.77;
	Cxyz = cgc_HC[(int)(temp/80.77)];
	
	return(Cxyz);

}

// calculate conductance between cell x,y,z and cell x+dx,y+dy,z+dz
double cgc_K(uint32_t x, uint32_t y, uint32_t z, int32_t dx, int32_t dy, int32_t dz) {
	double Kxyz;

	// Conductance between cells Kxyz and Kxyz+1
	// Kxyz+1/2 = (deltax*deltay)/(deltaz/(2*Lxyz) + deltaz+1/(2*Lxyz+1))
	// in this simulation deltax, deltay, and deltaz are all 1 meter

	// see if we're on a boundary
	if ( (dx == -1 && x == 0) || (dx == 1 && x == cgc_X-1) || 
	     (dy == -1 && y == 0) || (dy == 1 && y == cgc_Y-1) || 
	     (dz == -1 && z == 0) || (dz == 1 && z == cgc_Z-1)) {
		Kxyz = 1 / ( (1/(2*cgc_L(x,y,z))) );
	} else {
		Kxyz = 1 / ( (1/(2*cgc_L(x,y,z))) + (1/(2*cgc_L(x+dx,y+dy,z+dz))) );
	}

	return(Kxyz);

}

// calculate heat flow for cell x,y,z
double cgc_H(uint32_t x, uint32_t y, uint32_t z) {
	double Hxyz = 0.0;
	double Kval;
	double Tadj;
	double Txyz;

	// current cell's temperature
	Txyz = *cgc_pGRID(cgc_TGrid,x,y,z);

	// Heat Flow
	// Hxyz = sum of flows from each adjacent cell
	// each flow (example z-1 direction) is Kxyz-1 * (Txyz-1 - Txyz)

	// x-1 cell
	if (x != 0) {
		// only valid if we're not on a boundary cell
		Kval = cgc_K(x,y,z,-1,0,0);
		Tadj = *cgc_pGRID(cgc_TGrid,x-1,y,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// x+1 cell
	if (x != cgc_X-1) {
		// only valid if we're not on a boundary cell
		Kval = cgc_K(x,y,z,1,0,0);
		Tadj = *cgc_pGRID(cgc_TGrid,x+1,y,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// y-1 cell
	if (y != 0) {
		// only valid if we're not on a boundary cell
		Kval = cgc_K(x,y,z,0,-1,0);
		Tadj = *cgc_pGRID(cgc_TGrid,x,y-1,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// y+1 cell
	if (y != cgc_Y-1) {
		// only valid if we're not on a boundary cell
		Kval = cgc_K(x,y,z,0,1,0);
		Tadj = *cgc_pGRID(cgc_TGrid,x,y+1,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// z-1 cell
	if (z != 0) {
		// only valid if we're not on a boundary cell
		Kval = cgc_K(x,y,z,0,0,-1);
		Tadj = *cgc_pGRID(cgc_TGrid,x,y,z-1);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// z+1 cell
	if (z != cgc_Z-1) {
		// only valid if we're not on a boundary cell
		Kval = cgc_K(x,y,z,0,0,1);
		Tadj = *cgc_pGRID(cgc_TGrid,x,y,z+1);
		Hxyz += Kval*(Tadj - Txyz);
	}

	return(Hxyz);

}

// calculate new temperature for cell x,y,z
double cgc_Tnew(uint32_t x, uint32_t y, uint32_t z) {
	double NewTemp;

	if (cgc_HGrid == NULL || *cgc_pGRID(cgc_HGrid,x,y,z) <= NO_HEAT+273.15) {
		// Calculate the New Temperature
		// TxyzNew = Txyz + (deltaTime/(Cxyz * deltax,deltay,deltaz))*Hxyz
		// where:
		//  deltaTime is the time step
		//  Cxyz = Volumetric Heat Capacity of cell x,y,z
		//     average of 1200 J/m^3*K for air
		//  deltax,deltay,deltaz = size of grid cell  = 1m x 1m x 1m
		//  Hxyz = Heat Flow for cell x,y,z
		NewTemp = *cgc_pGRID(cgc_TGrid,x,y,z) + (TimeStep/cgc_C(x,y,z))*cgc_H(x,y,z);
	} else {
		// This grid location has a constant heat source.
		// So, there's no point in calculating any changes.
		// It will always have the supplied temperature
		NewTemp = *cgc_pGRID(cgc_HGrid,x,y,z);
	}

	return(NewTemp);

}

void cgc_CalcTimeStep(void) {
	uint32_t x, y, z;
	double MinTimeStep = 10.0;
	double TSxyz;
	double Ksum;

	// minimum, stable timestamp is calculated using
	// deltaTime < (Cxyz*deltax*deltay*deltaz)/(Sum surrounding cell K's)
	//  Cxyz = Volumetric Heat Capacity of cell x,y,z
	//  in this simulation deltax, deltay, and deltaz are all 1 meter
	for (z = 0; z < cgc_Z; z++) {
		for (y = 0; y < cgc_Y; y++) {
			for (x = 0; x < cgc_X; x++) {
				Ksum = 0.0;
				Ksum += cgc_K(x,y,z,-1,0,0);
				Ksum += cgc_K(x,y,z,1,0,0);
				Ksum += cgc_K(x,y,z,0,-1,0);
				Ksum += cgc_K(x,y,z,0,1,0);
				Ksum += cgc_K(x,y,z,0,0,-1);
				Ksum += cgc_K(x,y,z,0,0,1);
				TSxyz = cgc_C(x,y,z)/Ksum;

				if (MinTimeStep == -1.0) {
					MinTimeStep = TSxyz;
				}
				if (TSxyz < MinTimeStep && TSxyz > 0.0) {
					MinTimeStep = TSxyz;
				}
			}
		}
	}

	// use the minimum we found
	TimeStep = MinTimeStep;

}

int32_t cgc_SimStep(void) {
	uint32_t x, y, z;
	cgc_size_t malloc_size;
	double *TGridNew;

	// allocate a new TGrid to hold updated temperatures
	malloc_size = cgc_X*cgc_Y*cgc_Z*sizeof(double);
	if ((TGridNew = cgc_calloc(malloc_size, 1)) == NULL) {
		return(-1);
	}

	// run through the grid and calcuate the new temperatures
	for (z = 0; z < cgc_Z; z++) {
		for (y = 0; y < cgc_Y; y++) {
			for (x = 0; x < cgc_X; x++) {
				*cgc_pGRID(TGridNew,x,y,z) = cgc_Tnew(x,y,z);
			}
		}
	}

	// free and replace the old TGrid
	cgc_free(cgc_TGrid);
	cgc_TGrid = TGridNew;

	return(0);
}

// increment the CurrTime by TimeStep
void cgc_IncrementTimestep(double *CurrTime) {
	// increment the simulation time
	*CurrTime += TimeStep;
}

int32_t cgc_RunSim(void) {
	double CurrTime = 0.0;

	// find a stable timestamp for the given input data
	cgc_CalcTimeStep();

	while (CurrTime < SIM_TIME) {
		if (cgc_SimStep()) {
			return(-1);
		}

		// increment the simulation time
		cgc_IncrementTimestep(&CurrTime);

		// output the current grid
		cgc_GraphTemps(cgc_TGrid);
		cgc_printf("At @f seconds\n", CurrTime);
		cgc_kbhit();

	}

	return(0);
}
