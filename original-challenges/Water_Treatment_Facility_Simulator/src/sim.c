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
#include "stdio.h"
#include "plant.h"
#include "plant_system.h"
#include "menu.h"
#include "sim.h"

extern PlantSystem Influent;
extern PlantSystem Headworks;
extern PlantSystem HeadworksOutputValve;
extern uint8_t NumAsp;
extern PlantSystem Asp[5];
extern PlantSystem AspOutputValve;
extern uint8_t NumFilters;
extern PlantSystem Filter[5];
extern PlantSystem FilterOutputValve;
extern uint8_t NumDisinfection;
extern PlantSystem Disinfection[5];
extern PlantSystem DisinfectionOutputValve;
extern PlantSystem Effluent;

//
// Find the valve output that feeds the specified downstream system
//
int8_t FindValveOutput(pPlantSystem pValve, pPlantSystem pOutputSystem) {
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
void SimulateValve(pPlantSystem pValve) {
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
uint8_t CheckValveOutputs(void) {
	double OutputSum;
	uint8_t i;

	// HeadworksOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (HeadworksOutputValve.Output[i]) {
			OutputSum += HeadworksOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	// AspOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (AspOutputValve.Output[i]) {
			OutputSum += AspOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	// FilterOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (FilterOutputValve.Output[i]) {
			OutputSum += FilterOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	// DisinfectionOutputValve
	OutputSum = 0.0;
	for (i = 0; i < MAX_VALVE_INPUT; i++) {
		if (DisinfectionOutputValve.Output[i]) {
			OutputSum += DisinfectionOutputValve.PctOpen[i];
		}
	}
	if (OutputSum < 100.0)
		return(0);

	return(1);
}

//
// Simulate the Activated Sludge Process operation
//
void SimulateAsp(void) {
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
	for (i = 0; i < NumAsp; i++) {
		pInputSystem = Asp[i].Input[0];
		if (!pInputSystem) {
			return;
		}
	
		// This should be a valve because that's what the plant schematic says
		if (pInputSystem->Type != VALVE) {
			return;
		}
		
		// See how much we're getting from the upstream valve
		Asp[i].Flow = pInputSystem->Flow * GetValvePctFlow(pInputSystem, i);
		Asp[i].Cbod = pInputSystem->Cbod * GetValvePctFlow(pInputSystem, i);
		Asp[i].Tss = pInputSystem->Tss * GetValvePctFlow(pInputSystem, i);
		Asp[i].Tn = pInputSystem->Tn * GetValvePctFlow(pInputSystem, i);
		Asp[i].Tp = pInputSystem->Tp * GetValvePctFlow(pInputSystem, i);

		// Asp Reduces Tss by 90%
		Asp[i].Tss *= 0.1;

		// calculate the AOR provided
		// SOR = 0.188 * SCFM
		// AOR = 0.45 * SOR
		// AOR = 0.45 * 0.188 * (AerationPct * AerationMaxScfm)  in lbs/hr O2
		AorProvided = 0.45 * 0.188 * (Asp[i].AerationPct/100.0 * Asp[i].AerationMaxScfm);

		// calculate CBOD demand
		// Find the CBOD from the previous valve
		// Find the CBOD per hour
		// CBOD demand = 2 * CBOD/hr  in lbs/hr O2
		CbodDemand = 2.0 * Asp[i].Cbod / 24.0;

		if (AorProvided >= CbodDemand) {
			// able to remove all CBOD
			AorProvided -= CbodDemand;
			Asp[i].Cbod = 0.0;
		} else {
			// unable to remove all CBOD
			// remove what we can
			CbodDemand -= AorProvided;

			// the rest stays
			Asp[i].Cbod = CbodDemand / 2.0 * 24.0;

			// continue on to the next ASP
			continue;
		}
	
		// next see how much Tn is removed with the remaining AOR
		// Calculate TN demand per hour
		TnDemand = Asp[i].Tn / 24.0 * 4.6;

		// Calculate how much TN is removed
		TnRemoved = AorProvided / 4.6;

		if (AorProvided >= TnDemand) {
			Asp[i].Tn = 0;
		} else {
			Asp[i].Tn -= AorProvided * 24.0 / 4.6;
		}

		// Next see if the glycerin is able to handle the TnRemoved
		GlycerinProvided = 9.78 * Asp[i].GlycerinRate;
		GlycerinDemand = 6.5 * TnRemoved;
		if (GlycerinProvided >= GlycerinDemand) {
			// all of the nitrides are removed
			// but the excess becomes more CBOD
			Asp[i].Cbod += ((GlycerinProvided - GlycerinDemand)*24.0);
		} else {
			// not able to remove all of the nitrides
			Asp[i].Tn += (GlycerinDemand - GlycerinProvided);
		}

		// next see how much Tp is removed by the Alum feed
		// calculate how much Alum is being provided in lbs/hr
		AlumProvided = Asp[i].AlumRate * 0.49;

		// calculate the Alum demand for that amount of Tp
		AlumDemand = 0.9 * ( Asp[i].Tp / 24);

		if (AlumProvided >= AlumDemand) {
			// all Tp is removed
			Asp[i].Tp = 0;

			// count excess alum as increased CBOD
			Asp[i].Cbod += ((AlumProvided - AlumDemand) * 24.0);
		} else {
			// not all Tp is removed
			Asp[i].Tp = (AlumDemand - AlumProvided) / 0.9 * 24.0;
		}
	}

}

//
// Simulate the Filter operation
//
void SimulateFilter(void) {
	pPlantSystem pInputSystem;
	uint8_t i;
	double FlowGpm;
	double FilterSqft;
	double Loading;

	// Run the simulation for all of the Filters
	for (i = 0; i < NumFilters; i++) {
		pInputSystem = Filter[i].Input[0];
		if (!pInputSystem) {
			return;
		}
	
		// This should be a valve because that's what the plant schematic says
		if (pInputSystem->Type != VALVE) {
			return;
		}
		
		// See how much we're getting from the upstream valve
		Filter[i].Flow = pInputSystem->Flow * GetValvePctFlow(pInputSystem, i);
		Filter[i].Cbod = pInputSystem->Cbod * GetValvePctFlow(pInputSystem, i);
		Filter[i].Tss = pInputSystem->Tss * GetValvePctFlow(pInputSystem, i);
		Filter[i].Tn = pInputSystem->Tn * GetValvePctFlow(pInputSystem, i);
		Filter[i].Tp = pInputSystem->Tp * GetValvePctFlow(pInputSystem, i);

		// convert from MGD to GPM
		FlowGpm = Filter[i].Flow * 1000000.0 / 1440.0;

		// active filter sqft area (50 sqft per filter)
		FilterSqft = 50.0 * Filter[i].NumActiveFilters;

		// Calculate loading
		Loading = FlowGpm / FilterSqft;

		// Determine how much more Tss is removed
		if (Loading > 12.0) {
			// no Tss removal
		} else if (Loading >= 10.0) {
			Filter[i].Tss *= 0.4;
		} else if (Loading >= 9.0) {
			Filter[i].Tss *= 0.25;
		} else if (Loading >= 8.0) {
			Filter[i].Tss *= 0.2;
		} else if (Loading >= 7.0) {
			Filter[i].Tss *= 0.15;
		} else if (Loading >= 6.0) {
			Filter[i].Tss *= 0.1;
		} else if (Loading >= 3.0) {
			Filter[i].Tss *= 0.05;
		} else if (Loading >= 1.0) {
			Filter[i].Tss *= 0.01;
		} else {
			Filter[i].Tss = 0;
		}
	}

}

//
// Simulate the Disinfection operation
//
void SimulateDisinfection(void) {
	pPlantSystem pInputSystem;
	uint8_t i;
	double FlowGpm;
	double ContactTime;
	double ChlorineMass;
	double ChlorineConcentration;

	// Run the simulation for all of the ASP's
	for (i = 0; i < NumDisinfection; i++) {
		pInputSystem = Disinfection[i].Input[0];
		if (!pInputSystem) {
			return;
		}
	
		// This should be a valve because that's what the plant schematic says
		if (pInputSystem->Type != VALVE) {
			return;
		}
		
		// See how much we're getting from the upstream valve
		Disinfection[i].Flow = pInputSystem->Flow * GetValvePctFlow(pInputSystem, i);
		Disinfection[i].Cbod = pInputSystem->Cbod * GetValvePctFlow(pInputSystem, i);
		Disinfection[i].Tss = pInputSystem->Tss * GetValvePctFlow(pInputSystem, i);
		Disinfection[i].Tn = pInputSystem->Tn * GetValvePctFlow(pInputSystem, i);
		Disinfection[i].Tp = pInputSystem->Tp * GetValvePctFlow(pInputSystem, i);

		// First check Contact Time, given a 20,000 gallon disinfection tank
		FlowGpm = Disinfection[i].Flow * 1000000 / 1440;
		//ContactTime = FlowGpm / 20000;
		ContactTime = 20000.0 / FlowGpm;
		if (ContactTime < 20.0) {
			Disinfection[i].SuccessfulDisinfection = 0;
		} else {
			Disinfection[i].SuccessfulDisinfection = 1;
		}

		// Next check chlorine dosing
		ChlorineMass = 6.0 * Disinfection[i].ChlorineRate/100.0 * 76.1 * 0.12 * 24.0;

		// Use up any remaining Tn first
		// at a rate of 5 lb/day of chlorine for every 1 lb/day of Tn
		if (Disinfection[i].Tn > 0.0) {
			if (Disinfection[i].Tn * 5.0 >= ChlorineMass) {
				Disinfection[i].Tn -= ChlorineMass / 5.0;
				ChlorineMass = 0.0;
			} else {
				ChlorineMass -= Disinfection[i].Tn * 5.0;
				Disinfection[i].Tn = 0.0;
			}
		}

		// Disinfect what we can with the remaining chlorine
		ChlorineConcentration = ChlorineMass / (Disinfection[i].Flow * 8.34);
		if (ChlorineConcentration - 9.0 >= 0.0) {
			Disinfection[i].ChlorineResidual = ChlorineConcentration - 9.0;
		} else {
			Disinfection[i].ChlorineResidual = 0.0;
		}
		
		if (Disinfection[i].ChlorineResidual < 1.0 || Disinfection[i].ChlorineResidual > 8.0) {
			// disinfection failed
			Disinfection[i].SuccessfulDisinfection = 0;
		}

		// Convert the residual back to mass for easy merging in the next valve
		Disinfection[i].ChlorineResidual = Disinfection[i].ChlorineResidual * Disinfection[i].Flow * 8.34;
	}
}

#ifdef PATCHED_1
void SimulateEffluent(void) {
	pPlantSystem pInputSystem;

	pInputSystem = Effluent.Input[0];
	if (!pInputSystem) {
		return;
	}

	// This should be a valve because that's what the plant schematic says
	if (pInputSystem->Type != VALVE) {
		return;
	}
	
	Effluent.Flow = pInputSystem->Flow * GetValvePctFlow(pInputSystem, 0);
	Effluent.Cbod = pInputSystem->Cbod * GetValvePctFlow(pInputSystem, 0);
	Effluent.Tss = pInputSystem->Tss * GetValvePctFlow(pInputSystem, 0);
	Effluent.Tn = pInputSystem->Tn * GetValvePctFlow(pInputSystem, 0);
	Effluent.Tp = pInputSystem->Tp * GetValvePctFlow(pInputSystem, 0);
	Effluent.ChlorineResidual = pInputSystem->ChlorineResidual * GetValvePctFlow(pInputSystem, 0);
	Effluent.SuccessfulDisinfection = pInputSystem->SuccessfulDisinfection;

}
#else
void SimulateEffluent(void) {
	char buf[1024];
	pPlantSystem pEffluent;

	pEffluent = DisinfectionOutputValve.Output[0];
	if (pEffluent == NULL) {
		return;
	}

	pEffluent->Flow = DisinfectionOutputValve.Flow * GetValvePctFlow(&DisinfectionOutputValve, 0);
	pEffluent->Cbod = DisinfectionOutputValve.Cbod * GetValvePctFlow(&DisinfectionOutputValve, 0);
	pEffluent->Tss = DisinfectionOutputValve.Tss * GetValvePctFlow(&DisinfectionOutputValve, 0);
	pEffluent->Tn = DisinfectionOutputValve.Tn * GetValvePctFlow(&DisinfectionOutputValve, 0);
	pEffluent->Tp = DisinfectionOutputValve.Tp * GetValvePctFlow(&DisinfectionOutputValve, 0);
	pEffluent->ChlorineResidual = DisinfectionOutputValve.ChlorineResidual * GetValvePctFlow(&DisinfectionOutputValve, 0);
	pEffluent->SuccessfulDisinfection = DisinfectionOutputValve.SuccessfulDisinfection;

}
#endif

void SimulateHeadworks(void) {
	pPlantSystem pInputSystem;
	uint8_t i;

	pInputSystem = Headworks.Input[0];
	if (!pInputSystem) {
		return;
	}

	Headworks.Flow = pInputSystem->Flow;
	Headworks.Cbod = pInputSystem->Cbod;
	Headworks.Tss = pInputSystem->Tss * 0.7; // Headworks reduces Tss by 30%
	Headworks.Tn = pInputSystem->Tn;
	Headworks.Tp = pInputSystem->Tp;

}

uint8_t RunSimStep(void) {

	// Check the valves before we start
	if (!CheckValveOutputs()) {
		return(0);
	}

        // Simulate Headworks
        SimulateHeadworks();

        // Simulate valve between Headworks and Activated Sludge Process
        SimulateValve(&HeadworksOutputValve);

        // Simulate Activated Sludge Process
        SimulateAsp();

        // Simulate valve between Activated Sludge Process and Filters
        SimulateValve(&AspOutputValve);

        // Simulate Filters
        SimulateFilter();

        // Simulate valve between Filters and Disinfection
        SimulateValve(&FilterOutputValve);

        // Simulate Disinfection
        SimulateDisinfection();

        // Simulate valve to Discharge 
        SimulateValve(&DisinfectionOutputValve);

        // Simulate Effluent
        SimulateEffluent();

	return(1);
}
