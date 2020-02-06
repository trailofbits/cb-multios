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
#include "cgc_stdio.h"
#include "cgc_plant.h"
#include "cgc_plant_system.h"
#include "cgc_menu.h"
#include "cgc_sim.h"

extern PlantSystem cgc_Influent;
extern PlantSystem cgc_Headworks;
extern PlantSystem cgc_HeadworksOutputValve;
extern uint8_t cgc_NumAsp;
extern PlantSystem cgc_Asp[5];
extern PlantSystem cgc_AspOutputValve;
extern uint8_t cgc_NumFilters;
extern PlantSystem cgc_Filter[5];
extern PlantSystem cgc_FilterOutputValve;
extern uint8_t cgc_NumDisinfection;
extern PlantSystem cgc_Disinfection[5];
extern PlantSystem cgc_DisinfectionOutputValve;
extern PlantSystem cgc_Effluent;

//
// Find the valve output that feeds the specified downstream system
//
int8_t cgc_FindValveOutput(pPlantSystem pValve, pPlantSystem pOutputSystem) {
	int8_t i;

	if (pValve == NULL || pValve->Type != VALVE || pOutputSystem == NULL) {
		return -1;
	}

	for (i = 0; i < MAX_VALVE_OUTPUT; i++) {
		if (pValve->Output[i] == pOutputSystem) {
			return(i);
		}
	}
	return(-1);

}

//
// Simulate the Valve operation
//
void cgc_SimulateValve(pPlantSystem pValve) {
	pPlantSystem pInputSystem;
	pPlantSystem pOutputSystem;
	uint8_t i;

	// Calculate Flow, CBOD, TSS, Tn and Tp coming into the valve
	pValve->Flow = 0.0;
	pValve->Cbod = 0.0;
	pValve->Tss = 0.0;
	pValve->Tn = 0.0;
	pValve->Tp = 0.0;
	pValve->ChlorineResidual = 0.0;
	pValve->SuccessfulDisinfection = 1;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		pInputSystem = pValve->Input[i];
		if (pInputSystem) {
			pValve->Flow += pInputSystem->Flow;
			pValve->Cbod += pInputSystem->Cbod;
			pValve->Tss += pInputSystem->Tss;
			pValve->Tn += pInputSystem->Tn;
			pValve->Tp += pInputSystem->Tp;
			pValve->ChlorineResidual += pInputSystem->ChlorineResidual;
			if (pInputSystem->SuccessfulDisinfection == 0) {
				pValve->SuccessfulDisinfection = 0;
			}
		}
	}
}

//
// Make sure the total of the valve outputs is at least 100%
// More is ok since we calculate the flows based on the PctOpen/Total.
// Less is not ok because it could mean flows would back up in the system.
//
uint8_t cgc_CheckValveOutputs(void) {
	double OutputSum;
	uint8_t i;

	// HeadworksOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (cgc_HeadworksOutputValve.Output[i]) {
			OutputSum += cgc_HeadworksOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	// cgc_AspOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (cgc_AspOutputValve.Output[i]) {
			OutputSum += cgc_AspOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	// FilterOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (cgc_FilterOutputValve.Output[i]) {
			OutputSum += cgc_FilterOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	// DisinfectionOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (cgc_DisinfectionOutputValve.Output[i]) {
			OutputSum += cgc_DisinfectionOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	return(1);
}

//
// Simulate the Activated Sludge Process operation
//
void cgc_SimulateAsp(void) {
	pPlantSystem pInputSystem;
	uint8_t i;
	double AorProvided;
	double CbodDemand;
	double TnDemand;
	double TnRemoved;
	double GlycerinDemand;
	double GlycerinProvided;
	double AlumDemand;
	double AlumProvided;

	// Run the simulation for all of the ASP's
	for (i = 0; i < cgc_NumAsp; i++) {
		pInputSystem = cgc_Asp[i].Input[0];
		if (!pInputSystem) {
			return;
		}
	
		// This should be a valve because that's what the plant schematic says
		if (pInputSystem->Type != VALVE) {
			return;
		}
		
		// See how much we're getting from the upstream valve
		cgc_Asp[i].Flow = pInputSystem->Flow * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Asp[i].Cbod = pInputSystem->Cbod * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Asp[i].Tss = pInputSystem->Tss * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Asp[i].Tn = pInputSystem->Tn * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Asp[i].Tp = pInputSystem->Tp * cgc_GetValvePctFlow(pInputSystem, i);

		// cgc_Asp Reduces Tss by 90%
		cgc_Asp[i].Tss *= 0.1;

		// calculate the AOR provided
		// SOR = 0.188 * SCFM
		// AOR = 0.45 * SOR
		// AOR = 0.45 * 0.188 * (AerationPct * AerationMaxScfm)  in lbs/hr O2
		AorProvided = 0.45 * 0.188 * (cgc_Asp[i].AerationPct/100.0 * cgc_Asp[i].AerationMaxScfm);

		// calculate CBOD demand
		// Find the CBOD from the previous valve
		// Find the CBOD per hour
		// CBOD demand = 2 * CBOD/hr  in lbs/hr O2
		CbodDemand = 2.0 * cgc_Asp[i].Cbod / 24.0;

		if (AorProvided >= CbodDemand) {
			// able to remove all CBOD
			AorProvided -= CbodDemand;
			cgc_Asp[i].Cbod = 0.0;
		} else {
			// unable to remove all CBOD
			// remove what we can
			CbodDemand -= AorProvided;

			// the rest stays
			cgc_Asp[i].Cbod = CbodDemand / 2.0 * 24.0;

			// continue on to the next ASP
			continue;
		}
	
		// next see how much Tn is removed with the remaining AOR
		// Calculate TN demand per hour
		TnDemand = cgc_Asp[i].Tn / 24.0 * 4.6;

		// Calculate how much TN is removed
		TnRemoved = AorProvided / 4.6;

		if (AorProvided >= TnDemand) {
			cgc_Asp[i].Tn = 0;
		} else {
			cgc_Asp[i].Tn -= AorProvided * 24.0 / 4.6;
		}

		// Next see if the glycerin is able to handle the TnRemoved
		GlycerinProvided = 9.78 * cgc_Asp[i].GlycerinRate;
		GlycerinDemand = 6.5 * TnRemoved;
		if (GlycerinProvided >= GlycerinDemand) {
			// all of the nitrides are removed
			// but the excess becomes more CBOD
			cgc_Asp[i].Cbod += ((GlycerinProvided - GlycerinDemand)*24.0);
		} else {
			// not able to remove all of the nitrides
			cgc_Asp[i].Tn += (GlycerinDemand - GlycerinProvided);
		}

		// next see how much Tp is removed by the Alum feed
		// calculate how much Alum is being provided in lbs/hr
		AlumProvided = cgc_Asp[i].AlumRate * 0.49;

		// calculate the Alum demand for that amount of Tp
		AlumDemand = 0.9 * ( cgc_Asp[i].Tp / 24);

		if (AlumProvided >= AlumDemand) {
			// all Tp is removed
			cgc_Asp[i].Tp = 0;

			// count excess alum as increased CBOD
			cgc_Asp[i].Cbod += ((AlumProvided - AlumDemand) * 24.0);
		} else {
			// not all Tp is removed
			cgc_Asp[i].Tp = (AlumDemand - AlumProvided) / 0.9 * 24.0;
		}
	}

}

//
// Simulate the Filter operation
//
void cgc_SimulateFilter(void) {
	pPlantSystem pInputSystem;
	uint8_t i;
	double FlowGpm;
	double FilterSqft;
	double Loading;

	// Run the simulation for all of the Filters
	for (i = 0; i < cgc_NumFilters; i++) {
		pInputSystem = cgc_Filter[i].Input[0];
		if (!pInputSystem) {
			return;
		}
	
		// This should be a valve because that's what the plant schematic says
		if (pInputSystem->Type != VALVE) {
			return;
		}
		
		// See how much we're getting from the upstream valve
		cgc_Filter[i].Flow = pInputSystem->Flow * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Filter[i].Cbod = pInputSystem->Cbod * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Filter[i].Tss = pInputSystem->Tss * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Filter[i].Tn = pInputSystem->Tn * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Filter[i].Tp = pInputSystem->Tp * cgc_GetValvePctFlow(pInputSystem, i);

		// convert from MGD to GPM
		FlowGpm = cgc_Filter[i].Flow * 1000000.0 / 1440.0;

		// active filter sqft area (50 sqft per filter)
		FilterSqft = 50.0 * cgc_Filter[i].NumActiveFilters;

		// Calculate loading
		Loading = FlowGpm / FilterSqft;

		// Determine how much more Tss is removed
		if (Loading > 12.0) {
			// no Tss removal
		} else if (Loading >= 10.0) {
			cgc_Filter[i].Tss *= 0.4;
		} else if (Loading >= 9.0) {
			cgc_Filter[i].Tss *= 0.25;
		} else if (Loading >= 8.0) {
			cgc_Filter[i].Tss *= 0.2;
		} else if (Loading >= 7.0) {
			cgc_Filter[i].Tss *= 0.15;
		} else if (Loading >= 6.0) {
			cgc_Filter[i].Tss *= 0.1;
		} else if (Loading >= 3.0) {
			cgc_Filter[i].Tss *= 0.05;
		} else if (Loading >= 1.0) {
			cgc_Filter[i].Tss *= 0.01;
		} else {
			cgc_Filter[i].Tss = 0;
		}
	}

}

//
// Simulate the Disinfection operation
//
void cgc_SimulateDisinfection(void) {
	pPlantSystem pInputSystem;
	uint8_t i;
	double FlowGpm;
	double ContactTime;
	double ChlorineMass;
	double ChlorineConcentration;

	// Run the simulation for all of the ASP's
	for (i = 0; i < cgc_NumDisinfection; i++) {
		pInputSystem = cgc_Disinfection[i].Input[0];
		if (!pInputSystem) {
			return;
		}
	
		// This should be a valve because that's what the plant schematic says
		if (pInputSystem->Type != VALVE) {
			return;
		}
		
		// See how much we're getting from the upstream valve
		cgc_Disinfection[i].Flow = pInputSystem->Flow * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Disinfection[i].Cbod = pInputSystem->Cbod * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Disinfection[i].Tss = pInputSystem->Tss * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Disinfection[i].Tn = pInputSystem->Tn * cgc_GetValvePctFlow(pInputSystem, i);
		cgc_Disinfection[i].Tp = pInputSystem->Tp * cgc_GetValvePctFlow(pInputSystem, i);

		// First check Contact Time, given a 20,000 gallon disinfection tank
		FlowGpm = cgc_Disinfection[i].Flow * 1000000 / 1440;
		//ContactTime = FlowGpm / 20000;
		ContactTime = 20000.0 / FlowGpm;
		if (ContactTime < 20.0) {
			cgc_Disinfection[i].SuccessfulDisinfection = 0;
		} else {
			cgc_Disinfection[i].SuccessfulDisinfection = 1;
		}

		// Next check chlorine dosing
		ChlorineMass = 6.0 * cgc_Disinfection[i].ChlorineRate/100.0 * 76.1 * 0.12 * 24.0;

		// Use up any remaining Tn first
		// at a rate of 5 lb/day of chlorine for every 1 lb/day of Tn
		if (cgc_Disinfection[i].Tn > 0.0) {
			if (cgc_Disinfection[i].Tn * 5.0 >= ChlorineMass) {
				cgc_Disinfection[i].Tn -= ChlorineMass / 5.0;
				ChlorineMass = 0.0;
			} else {
				ChlorineMass -= cgc_Disinfection[i].Tn * 5.0;
				cgc_Disinfection[i].Tn = 0.0;
			}
		}

		// Disinfect what we can with the remaining chlorine
		ChlorineConcentration = ChlorineMass / (cgc_Disinfection[i].Flow * 8.34);
		if (ChlorineConcentration - 9.0 >= 0.0) {
			cgc_Disinfection[i].ChlorineResidual = ChlorineConcentration - 9.0;
		} else {
			cgc_Disinfection[i].ChlorineResidual = 0.0;
		}
		
		if (cgc_Disinfection[i].ChlorineResidual < 1.0 || cgc_Disinfection[i].ChlorineResidual > 8.0) {
			// disinfection failed
			cgc_Disinfection[i].SuccessfulDisinfection = 0;
		}

		// Convert the residual back to mass for easy merging in the next valve
		cgc_Disinfection[i].ChlorineResidual = cgc_Disinfection[i].ChlorineResidual * cgc_Disinfection[i].Flow * 8.34;
	}
}

#ifdef PATCHED_1
void cgc_SimulateEffluent(void) {
	pPlantSystem pInputSystem;

	pInputSystem = cgc_Effluent.Input[0];
	if (!pInputSystem) {
		return;
	}

	// This should be a valve because that's what the plant schematic says
	if (pInputSystem->Type != VALVE) {
		return;
	}
	
	cgc_Effluent.Flow = pInputSystem->Flow * cgc_GetValvePctFlow(pInputSystem, 0);
	cgc_Effluent.Cbod = pInputSystem->Cbod * cgc_GetValvePctFlow(pInputSystem, 0);
	cgc_Effluent.Tss = pInputSystem->Tss * cgc_GetValvePctFlow(pInputSystem, 0);
	cgc_Effluent.Tn = pInputSystem->Tn * cgc_GetValvePctFlow(pInputSystem, 0);
	cgc_Effluent.Tp = pInputSystem->Tp * cgc_GetValvePctFlow(pInputSystem, 0);
	cgc_Effluent.ChlorineResidual = pInputSystem->ChlorineResidual * cgc_GetValvePctFlow(pInputSystem, 0);
	cgc_Effluent.SuccessfulDisinfection = pInputSystem->SuccessfulDisinfection;

}
#else
void cgc_SimulateEffluent(void) {
	char buf[1024];
	pPlantSystem pEffluent;

	pEffluent = cgc_DisinfectionOutputValve.Output[0];
	if (pEffluent == NULL) {
		return;
	}

	pEffluent->Flow = cgc_DisinfectionOutputValve.Flow * cgc_GetValvePctFlow(&cgc_DisinfectionOutputValve, 0);
	pEffluent->Cbod = cgc_DisinfectionOutputValve.Cbod * cgc_GetValvePctFlow(&cgc_DisinfectionOutputValve, 0);
	pEffluent->Tss = cgc_DisinfectionOutputValve.Tss * cgc_GetValvePctFlow(&cgc_DisinfectionOutputValve, 0);
	pEffluent->Tn = cgc_DisinfectionOutputValve.Tn * cgc_GetValvePctFlow(&cgc_DisinfectionOutputValve, 0);
	pEffluent->Tp = cgc_DisinfectionOutputValve.Tp * cgc_GetValvePctFlow(&cgc_DisinfectionOutputValve, 0);
	pEffluent->ChlorineResidual = cgc_DisinfectionOutputValve.ChlorineResidual * cgc_GetValvePctFlow(&cgc_DisinfectionOutputValve, 0);
	pEffluent->SuccessfulDisinfection = cgc_DisinfectionOutputValve.SuccessfulDisinfection;

}
#endif

void cgc_SimulateHeadworks(void) {
	pPlantSystem pInputSystem;
	uint8_t i;

	pInputSystem = cgc_Headworks.Input[0];
	if (!pInputSystem) {
		return;
	}

	cgc_Headworks.Flow = pInputSystem->Flow;
	cgc_Headworks.Cbod = pInputSystem->Cbod;
	cgc_Headworks.Tss = pInputSystem->Tss * 0.7; // Headworks reduces Tss by 30%
	cgc_Headworks.Tn = pInputSystem->Tn;
	cgc_Headworks.Tp = pInputSystem->Tp;

}

uint8_t cgc_RunSimStep(void) {

	// Check the valves before we start
	if (!cgc_CheckValveOutputs()) {
		return(0);
	}

        // Simulate Headworks
        cgc_SimulateHeadworks();

        // Simulate valve between Headworks and Activated Sludge Process
        cgc_SimulateValve(&cgc_HeadworksOutputValve);

        // Simulate Activated Sludge Process
        cgc_SimulateAsp();

        // Simulate valve between Activated Sludge Process and Filters
        cgc_SimulateValve(&cgc_AspOutputValve);

        // Simulate Filters
        cgc_SimulateFilter();

        // Simulate valve between Filters and Disinfection
        cgc_SimulateValve(&cgc_FilterOutputValve);

        // Simulate Disinfection
        cgc_SimulateDisinfection();

        // Simulate valve to Discharge 
        cgc_SimulateValve(&cgc_DisinfectionOutputValve);

        // Simulate Effluent
        cgc_SimulateEffluent();

	return(1);
}
