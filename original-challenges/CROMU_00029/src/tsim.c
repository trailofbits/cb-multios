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
#include "input.h"
#include "malloc.h"
#include "tvis.h"
#include "room.h"

double SIM_TIME;

extern double *TGrid;
extern double *HGrid;
extern uint32_t X;
extern uint32_t Y;
extern uint32_t Z;
double TimeStep;
extern double TC[8];
extern double HC[8];

// defined as a actual function here because of gcc double alignment bug
double *pGRID(double *grid, uint32_t x, uint32_t y, uint32_t z) {
	return (grid + x + y*X + z*X*Y);
}

int32_t GetSimLength(void) {
	char buf[100];
		
	SIM_TIME = 0.0;
        while (SIM_TIME <= 0.0) {
                printf("For how long would you like to run the simulation? (s): ");
                if (read_until(buf, "\n", 99) == -1) {
                        // failed to read the input
                        return(-1);
                }
		SIM_TIME = cgcatof(buf);
	}

	return(0);
}

// lookup thermal conductivity for a cell given its temperature
double L(uint32_t x, uint32_t y, uint32_t z) {
	double temp;
	double Lxyz;
	int index;

	// error handling
	if (x >= X || y >= Y || z >= Z) {
		return(-1);
	}

	// get the temperature of the requested cell
	temp = *pGRID(TGrid,x,y,z);

	// calculate the thermal conductivity for that temperature	
	index = temp/80.77;
	Lxyz = TC[(int)(temp/80.77)];
	
	return(Lxyz);

}

// lookup heat capacity for a cell given its temperature
double C(uint32_t x, uint32_t y, uint32_t z) {
	double temp;
	double Cxyz;
	int index;

	// error handling
	if (x >= X || y >= Y || z >= Z) {
		return(-1);
	}

	// get the temperature of the requested cell
	temp = *pGRID(TGrid,x,y,z);

	// calculate the thermal conductivity for that temperature	
	index = temp/80.77;
	Cxyz = HC[(int)(temp/80.77)];
	
	return(Cxyz);

}

// calculate conductance between cell x,y,z and cell x+dx,y+dy,z+dz
double K(uint32_t x, uint32_t y, uint32_t z, int32_t dx, int32_t dy, int32_t dz) {
	double Kxyz;

	// Conductance between cells Kxyz and Kxyz+1
	// Kxyz+1/2 = (deltax*deltay)/(deltaz/(2*Lxyz) + deltaz+1/(2*Lxyz+1))
	// in this simulation deltax, deltay, and deltaz are all 1 meter

	// see if we're on a boundary
	if ( (dx == -1 && x == 0) || (dx == 1 && x == X-1) || 
	     (dy == -1 && y == 0) || (dy == 1 && y == Y-1) || 
	     (dz == -1 && z == 0) || (dz == 1 && z == Z-1)) {
		Kxyz = 1 / ( (1/(2*L(x,y,z))) );
	} else {
		Kxyz = 1 / ( (1/(2*L(x,y,z))) + (1/(2*L(x+dx,y+dy,z+dz))) );
	}

	return(Kxyz);

}

// calculate heat flow for cell x,y,z
double H(uint32_t x, uint32_t y, uint32_t z) {
	double Hxyz = 0.0;
	double Kval;
	double Tadj;
	double Txyz;

	// current cell's temperature
	Txyz = *pGRID(TGrid,x,y,z);

	// Heat Flow
	// Hxyz = sum of flows from each adjacent cell
	// each flow (example z-1 direction) is Kxyz-1 * (Txyz-1 - Txyz)

	// x-1 cell
	if (x != 0) {
		// only valid if we're not on a boundary cell
		Kval = K(x,y,z,-1,0,0);
		Tadj = *pGRID(TGrid,x-1,y,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// x+1 cell
	if (x != X-1) {
		// only valid if we're not on a boundary cell
		Kval = K(x,y,z,1,0,0);
		Tadj = *pGRID(TGrid,x+1,y,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// y-1 cell
	if (y != 0) {
		// only valid if we're not on a boundary cell
		Kval = K(x,y,z,0,-1,0);
		Tadj = *pGRID(TGrid,x,y-1,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// y+1 cell
	if (y != Y-1) {
		// only valid if we're not on a boundary cell
		Kval = K(x,y,z,0,1,0);
		Tadj = *pGRID(TGrid,x,y+1,z);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// z-1 cell
	if (z != 0) {
		// only valid if we're not on a boundary cell
		Kval = K(x,y,z,0,0,-1);
		Tadj = *pGRID(TGrid,x,y,z-1);
		Hxyz += Kval*(Tadj - Txyz);
	}

	// z+1 cell
	if (z != Z-1) {
		// only valid if we're not on a boundary cell
		Kval = K(x,y,z,0,0,1);
		Tadj = *pGRID(TGrid,x,y,z+1);
		Hxyz += Kval*(Tadj - Txyz);
	}

	return(Hxyz);

}

// calculate new temperature for cell x,y,z
double Tnew(uint32_t x, uint32_t y, uint32_t z) {
	double NewTemp;

	if (HGrid == NULL || *pGRID(HGrid,x,y,z) <= NO_HEAT+273.15) {
		// Calculate the New Temperature
		// TxyzNew = Txyz + (deltaTime/(Cxyz * deltax,deltay,deltaz))*Hxyz
		// where:
		//  deltaTime is the time step
		//  Cxyz = Volumetric Heat Capacity of cell x,y,z
		//     average of 1200 J/m^3*K for air
		//  deltax,deltay,deltaz = size of grid cell  = 1m x 1m x 1m
		//  Hxyz = Heat Flow for cell x,y,z
		NewTemp = *pGRID(TGrid,x,y,z) + (TimeStep/C(x,y,z))*H(x,y,z);
	} else {
		// This grid location has a constant heat source.
		// So, there's no point in calculating any changes.
		// It will always have the supplied temperature
		NewTemp = *pGRID(HGrid,x,y,z);
	}

	return(NewTemp);

}

void CalcTimeStep(void) {
	uint32_t x, y, z;
	double MinTimeStep = 10.0;
	double TSxyz;
	double Ksum;

	// minimum, stable timestamp is calculated using
	// deltaTime < (Cxyz*deltax*deltay*deltaz)/(Sum surrounding cell K's)
	//  Cxyz = Volumetric Heat Capacity of cell x,y,z
	//  in this simulation deltax, deltay, and deltaz are all 1 meter
	for (z = 0; z < Z; z++) {
		for (y = 0; y < Y; y++) {
			for (x = 0; x < X; x++) {
				Ksum = 0.0;
				Ksum += K(x,y,z,-1,0,0);
				Ksum += K(x,y,z,1,0,0);
				Ksum += K(x,y,z,0,-1,0);
				Ksum += K(x,y,z,0,1,0);
				Ksum += K(x,y,z,0,0,-1);
				Ksum += K(x,y,z,0,0,1);
				TSxyz = C(x,y,z)/Ksum;

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

int32_t SimStep(void) {
	uint32_t x, y, z;
	size_t malloc_size;
	double *TGridNew;

	// allocate a new TGrid to hold updated temperatures
	malloc_size = X*Y*Z*sizeof(double);
	if ((TGridNew = calloc(malloc_size, 1)) == NULL) {
		return(-1);
	}

	// run through the grid and calcuate the new temperatures
	for (z = 0; z < Z; z++) {
		for (y = 0; y < Y; y++) {
			for (x = 0; x < X; x++) {
				*pGRID(TGridNew,x,y,z) = Tnew(x,y,z);
			}
		}
	}

	// free and replace the old TGrid
	free(TGrid);
	TGrid = TGridNew;

	return(0);
}

// increment the CurrTime by TimeStep
void IncrementTimestep(double *CurrTime) {
	// increment the simulation time
	*CurrTime += TimeStep;
}

int32_t RunSim(void) {
	double CurrTime = 0.0;

	// find a stable timestamp for the given input data
	CalcTimeStep();

	while (CurrTime < SIM_TIME) {
		if (SimStep()) {
			return(-1);
		}

		// increment the simulation time
		IncrementTimestep(&CurrTime);

		// output the current grid
		GraphTemps(TGrid);
		printf("At @f seconds\n", CurrTime);
		kbhit();

	}

	return(0);
}
