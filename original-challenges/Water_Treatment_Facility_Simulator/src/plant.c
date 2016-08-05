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
#include "stdint.h"
#include "string.h"
#include "prng.h"
#include "plant.h"
#include "plant_system.h"

// plant structures
PlantSystem Influent;
PlantSystem Headworks;
PlantSystem HeadworksOutputValve;
uint8_t NumAsp = 3;
PlantSystem Asp[5];
PlantSystem AspOutputValve;
uint8_t NumFilters = 3;
PlantSystem Filter[5];
PlantSystem FilterOutputValve;
uint8_t NumDisinfection = 3;
PlantSystem Disinfection[5];
PlantSystem DisinfectionOutputValve;
PlantSystem Effluent;

char StatusBuf[8192];

//
// Calculate the random influent each round
//
void RandomInfluent(void) {
	Influent.Flow = random_in_range(9, 30) / 10.0;
	Influent.Cbod = random_in_range(1900, 4000);
	Influent.Tss = random_in_range(2000, 5000);
	Influent.Tn = random_in_range(490, 750);
	Influent.Tp = random_in_range(75, 150);
}

//
// Initialize the Influent system
//
void InitInfluent(void) {
	bzero(&Influent, sizeof(PlantSystem));

	Influent.Type = INFLUENT;
	strncpy(Influent.Name, "Influent", 31);
	Influent.Flow = 1.6;
	Influent.Cbod = 2680.0;
	Influent.Tss = 3300.0;
	Influent.Tn = 540.0;
	Influent.Tp = 94.0;
	Influent.Output[0] = &Headworks;
}

//
// Calculate the percent flow through a specified valve output
//
double GetValvePctFlow(pPlantSystem pValve, uint8_t Output) {
	uint8_t i;
	double sum;

	// make sure we got valid values
	if (!pValve || Output > MAX_VALVE_OUTPUT) {
		return(0);
	}

	// make sure the valve and specified output are valid
	if (pValve->Type != VALVE || pValve->Output[Output] == NULL) {
		return(0);
	}

	// run through the valid valve outcromu_puts and get the sum of the output percentages
	sum = 0.0;
	for (i = 0; i < MAX_VALVE_OUTPUT; i++) {
		if (pValve->Output[i] == NULL) {
			continue;
		}
		sum += pValve->PctOpen[i];
	}

	// return the percent of the total flow the Output valve would get
	if (sum == 0.0) {
		return(0.0);
	} else {
		return(pValve->PctOpen[Output] / sum);
	}


}

//
// Set the percent open for a given valve output
//
void SetValveOutput(pPlantSystem pValve, uint8_t Output, double PctOpen) {

	// make sure we got valid values
	if (!pValve || Output > MAX_VALVE_OUTPUT || PctOpen > 100.0) {
		return;
	}

	// make sure the valve and specified output are valid
	if (pValve->Type != VALVE || pValve->Output[Output] == NULL) {
		return;
	}

	// set the output percent as requested
	pValve->PctOpen[Output] = PctOpen;

}

//
// Rename a specified system
//
void SetSystemName(pPlantSystem pSystem, char *NewName) {

	if (!pSystem) {
		return;
	}

	strncpy(pSystem->Name, NewName, 31);

}

//
// Change the ASP system aeration percentage
//
void ChangeAerationPercent(pPlantSystem pAsp, double NewPct) {

	if (!Asp || Asp->Type != ASP || NewPct < 0.0 || NewPct > 100.0) {
		return;
	}

	pAsp->AerationPct = NewPct;

}

//
// Change the ASP system glycerin rate
//
void ChangeGlycerinRate(pPlantSystem pAsp, double NewRate) {

	if (!Asp || Asp->Type != ASP || NewRate < 0.0 || NewRate > 100.0) {
		return;
	}

	pAsp->GlycerinRate = NewRate;

}

//
// Change the ASP system alum rate
//
void ChangeAlumRate(pPlantSystem pAsp, double NewRate) {

	if (!Asp || Asp->Type != ASP || NewRate < 0.0 || NewRate > 100.0) {
		return;
	}

	pAsp->AlumRate = NewRate;

}

//
// Change the Disinfection system chlorine rate
//
void ChangeChlorineRate(pPlantSystem pDisinfection, double NewChlorineRate) {

	if (!pDisinfection || pDisinfection->Type != DISINFECTION || NewChlorineRate < 0.0 || NewChlorineRate > 100.0) {
		return;
	}

	pDisinfection->ChlorineRate = NewChlorineRate;

}

//
// Change the number of active filters
//
void ChangeNumActiveFilters(pPlantSystem pFilter, uint8_t NumFilters) {

	if (!pFilter || pFilter->Type != FILTER || NumFilters < 0 || NumFilters > pFilter->MaxFilters) {
		return;
	}

	pFilter->NumActiveFilters = NumFilters;

}

//
// Change the Headworks system
//
void InitHeadworks(void) {
	bzero(&Headworks, sizeof(PlantSystem));

	Headworks.Type = HEADWORKS;
	strncpy(Headworks.Name, "Headworks", 31);
	Headworks.Input[0] = &Influent;
	Headworks.Output[0] = &HeadworksOutputValve;
	Headworks.TssReductionPct = 30.0;
}

//
// Initialize the Headworks system
//
void InitHeadworksOutputValve(void) {
	uint8_t i;

	bzero(&HeadworksOutputValve, sizeof(PlantSystem));

	HeadworksOutputValve.Type = VALVE;
	strncpy(HeadworksOutputValve.Name, "V1", 31);

	// inputs
	HeadworksOutputValve.Input[0] = &Headworks;

	// outputs and valve positions
	for (i = 0; i < NumAsp; i++) {
		HeadworksOutputValve.Output[i] = &Asp[i];
		HeadworksOutputValve.PctOpen[i] = 100.0/NumAsp;
	}	
}

//
// Initialize the Active Sludge Process system
//
void InitAsp(void) {
	uint8_t i;

	bzero(&Asp, sizeof(Asp));

	for (i = 0; i < NumAsp; i++) {
		Asp[i].Type = ASP;
		cromu_sprintf(Asp[i].Name, "Asp$d", i);

		Asp[i].Input[0] = &HeadworksOutputValve;
		Asp[i].Output[0] = &AspOutputValve;

		Asp[i].AerationPct = 50.0;
		Asp[i].AerationMaxScfm = 4800.0;
		Asp[i].GlycerinRate = 4.0;
		Asp[i].AlumRate = 20.0;
	}
}

//
// Initialize the ASP Output Valve
//
void InitAspOutputValve(void) {
	uint8_t i;

	bzero(&AspOutputValve, sizeof(PlantSystem));

	AspOutputValve.Type = VALVE;
	strncpy(AspOutputValve.Name, "V2", 31);

	// inputs
	for (i = 0; i < NumAsp; i++) {
		AspOutputValve.Input[i] = &Asp[i];
	}

	// outputs to Filters
	for (i = 0; i < NumFilters; i++) {
		AspOutputValve.Output[i] = &Filter[i];
		AspOutputValve.PctOpen[i] = 100.0/NumFilters;
	}

}

//
// Initialize the Filter system
//
void InitFilters(void) {
	uint8_t i;
	double Gpm;

	bzero(&Filter, sizeof(Filter));

	for (i = 0; i < NumFilters; i++) {
		Filter[i].Type = FILTER;
		cromu_sprintf(Filter[i].Name, "Filter$d", i);
		Filter[i].Input[0] = &AspOutputValve;
		Filter[i].Output[0] = &FilterOutputValve;
	}

	// set the active and max filters
	Filter[0].MaxFilters = 2;
	Filter[0].NumActiveFilters = 1;
	Filter[1].MaxFilters = 4;
	Filter[1].NumActiveFilters = 2;
	Filter[2].MaxFilters = 4;
	Filter[2].NumActiveFilters = 2;

}

//
// Initialize the Filter Output valve
//
void InitFilterOutputValve(void) {
	uint8_t i;

	bzero(&FilterOutputValve, sizeof(PlantSystem));

	FilterOutputValve.Type = VALVE;
	strncpy(FilterOutputValve.Name, "V3", 31);

	// inputs
	for (i = 0; i < NumFilters; i++) {
		FilterOutputValve.Input[i] = &Filter[i];
	}

	// outputs
	for (i = 0; i < NumDisinfection; i++) {
		FilterOutputValve.Output[i] = &Disinfection[i];
		FilterOutputValve.PctOpen[i] = 100.0 / NumDisinfection;
	}
		
}

//
// Initialize the Disinfection system
//
void InitDisinfection(void) {
	uint8_t i;

	bzero(&Disinfection, sizeof(Disinfection));

	for (i = 0; i < NumDisinfection; i++) {
		Disinfection[i].Type = DISINFECTION;
		cromu_sprintf(Disinfection[i].Name, "Disinfection$d", i);
		Disinfection[i].Input[0] = &FilterOutputValve;
		Disinfection[i].Output[0] = &DisinfectionOutputValve;
		Disinfection[i].ChlorineRate = 1.0;
	}

}

//
// Initialize the Disinfection output valve
//
void InitDisinfectionOutputValve(void) {
	uint8_t i;

	bzero(&DisinfectionOutputValve, sizeof(PlantSystem));

	DisinfectionOutputValve.Type = VALVE;
	strncpy(DisinfectionOutputValve.Name, "V4", 31);

	// inputs from the disinfection systems
	for (i = 0; i < NumDisinfection; i++) {
		DisinfectionOutputValve.Input[i] = &Disinfection[i];
	}

	// output to effluent
	DisinfectionOutputValve.Output[0] = &Effluent;
	DisinfectionOutputValve.PctOpen[0] = 100.0;

}

//
// Initialize the Effluent system
//
void InitEffluent(void) {
	bzero(&Effluent, sizeof(PlantSystem));

	Effluent.Type = EFFLUENT;
	strncpy(Effluent.Name, "Effluent", 31);
	Effluent.Input[0] = &DisinfectionOutputValve;
}

//
// See if the effluent meets the water quality standards
//
void CheckEffluentQuality(void) {
	double Cbod_mgl;
	double Tss_mgl;
	double Tn_mgl;
	double Tp_mgl;

	// convert to mg/L 
	Cbod_mgl = Effluent.Cbod / (Effluent.Flow * 8.34);
	Tss_mgl = Effluent.Tss / (Effluent.Flow * 8.34);
	Tn_mgl = Effluent.Tn / (Effluent.Flow * 8.34);
	Tp_mgl = Effluent.Tp / (Effluent.Flow * 8.34);

	if (Cbod_mgl > 5.0 || Tss_mgl > 5.0 || Tn_mgl > 3.0 || Tp_mgl > 1.0 || Effluent.SuccessfulDisinfection == 0) {
		// quality failed standards
		Effluent.QualityFailures++;
	}
	return;
}

void PrintPlantSchematic(void) {

	cromu_puts("Plant Schematic");
	cromu_puts("#####################################################################################################################################");
	cromu_puts("                                         --------                -----------               -----------------                         ");
	cromu_puts("                                -------> | ASP1 | ------  -----> | Filter1 | -----  -----> | Disinfection1 | -----                   ");
	cromu_puts("                                |        --------      |  |      -----------     |  |      -----------------     |                   ");
	cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cromu_puts("                                0                      v  0                      v  0                            v                   ");
	cromu_puts("            -------------     ------     --------     ------     -----------    ------     -----------------    ------               ");
	cromu_puts("Influent -> | Headworks | --> | V1 | 1-> | ASP2 | --> | V2 | 1-> | Filter2 | -> | V3 | 1-> | Disinfection2 | -> | V4 | 0-> Effluent  ");
	cromu_puts("            -------------     ------     --------     ------     -----------    ------     -----------------    ------               ");
	cromu_puts("                                2                      ^  2                      ^  2                            ^                   ");
	cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cromu_puts("                                |        --------      |  |      -----------     |  |      -----------------     |                   ");
	cromu_puts("                                -------> | ASP3 | ------  -----> | Filter3 | -----  -----> | Disinfection3 | -----                   ");
	cromu_puts("                                         --------                -----------               -----------------                         ");
	cromu_puts("#####################################################################################################################################");


}

//
// Print the plant status
//
void PrintPlantStatus(void) {
	char *buf = PrintPlantStatusBuf();
	cromu_puts(buf);
}

//
// Print the plant status to the StatusBuf buffer
//
char *PrintPlantStatusBuf(void) {
	uint32_t pos = 0;

	pos += cromu_sprintf(StatusBuf+pos,  "Plant Status\n");
	pos += cromu_sprintf(StatusBuf+pos,  "#####################################################################################################################################\n");
	pos += cromu_sprintf(StatusBuf+pos,  "Units\n");
	pos += cromu_sprintf(StatusBuf+pos,  "Flow - MGD\n");
	pos += cromu_sprintf(StatusBuf+pos,  "CBOD, TSS, TN, TP - lbs/day\n");
	pos += cromu_sprintf(StatusBuf+pos,  "Aeration, Glycerin_Rate, Alum_rate, OutputPct - percent\n");
	pos += cromu_sprintf(StatusBuf+pos,  "\n");

	pos += cromu_sprintf(StatusBuf+pos,  "Influent       |      Flow       CBOD        TSS         TN         TP\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f\n", Influent.Name, Influent.Flow, Influent.Cbod, Influent.Tss, Influent.Tn, Influent.Tp);
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	pos += cromu_sprintf(StatusBuf+pos,  "Headworks      |      Flow       CBOD        TSS         TN         TP\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f\n", Headworks.Name, Headworks.Flow, Headworks.Cbod, Headworks.Tss, Headworks.Tn, Headworks.Tp);
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	pos += cromu_sprintf(StatusBuf+pos,  "ASPs           |      Flow       CBOD        TSS         TN         TP     Aeration     Glycerin_Rate    Alum_Rate\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|--------------------------------------------------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f     $8.2f          $8.2f     $8.2f\n", Asp[0].Name, Asp[0].Flow, Asp[0].Cbod, Asp[0].Tss, Asp[0].Tn, Asp[0].Tp, Asp[0].AerationPct, Asp[0].GlycerinRate, Asp[0].AlumRate);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f     $8.2f          $8.2f     $8.2f\n", Asp[1].Name, Asp[1].Flow, Asp[1].Cbod, Asp[1].Tss, Asp[1].Tn, Asp[1].Tp, Asp[1].AerationPct, Asp[1].GlycerinRate, Asp[1].AlumRate);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f     $8.2f          $8.2f     $8.2f\n", Asp[2].Name, Asp[2].Flow, Asp[2].Cbod, Asp[2].Tss, Asp[2].Tn, Asp[2].Tp, Asp[2].AerationPct, Asp[2].GlycerinRate, Asp[2].AlumRate);
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	pos += cromu_sprintf(StatusBuf+pos,  "Filters        |      Flow       CBOD        TSS         TN         TP     Num_Active_Filters\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|-----------------------------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f               $8d\n", Filter[0].Name, Filter[0].Flow, Filter[0].Cbod, Filter[0].Tss, Filter[0].Tn, Filter[0].Tp, Filter[0].NumActiveFilters);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f               $8d\n", Filter[1].Name, Filter[1].Flow, Filter[1].Cbod, Filter[1].Tss, Filter[1].Tn, Filter[1].Tp, Filter[1].NumActiveFilters);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f               $8d\n", Filter[2].Name, Filter[2].Flow, Filter[2].Cbod, Filter[2].Tss, Filter[2].Tn, Filter[2].Tp, Filter[2].NumActiveFilters);
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	pos += cromu_sprintf(StatusBuf+pos,  "Disinfection   |      Flow       CBOD        TSS         TN         TP     Chlorine_Rate\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|------------------------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f          $8.2f\n", Disinfection[0].Name, Disinfection[0].Flow, Disinfection[0].Cbod, Disinfection[0].Tss, Disinfection[0].Tn, Disinfection[0].Tp, Disinfection[0].ChlorineRate);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f          $8.2f\n", Disinfection[1].Name, Disinfection[1].Flow, Disinfection[1].Cbod, Disinfection[1].Tss, Disinfection[1].Tn, Disinfection[1].Tp, Disinfection[1].ChlorineRate);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f          $8.2f\n", Disinfection[2].Name, Disinfection[2].Flow, Disinfection[2].Cbod, Disinfection[2].Tss, Disinfection[2].Tn, Disinfection[2].Tp, Disinfection[2].ChlorineRate);
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	pos += cromu_sprintf(StatusBuf+pos,  "Effluent       |      Flow       CBOD        TSS         TN         TP          Quality_Failures\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|--------------------------------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f                        $2d\n", Effluent.Name, Effluent.Flow, Effluent.Cbod, Effluent.Tss, Effluent.Tn, Effluent.Tp, Effluent.QualityFailures);
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	pos += cromu_sprintf(StatusBuf+pos,  "Valves         |    OutputPct[0]    OutputPct[1]    OutputPct[2]    OutputPct[3]    OutputPct[4]\n");
	pos += cromu_sprintf(StatusBuf+pos,  "---------------|--------------------------------------------------------------------------------\n");
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n", 
		HeadworksOutputValve.Name, HeadworksOutputValve.PctOpen[0],HeadworksOutputValve.PctOpen[1],HeadworksOutputValve.PctOpen[2],
		HeadworksOutputValve.PctOpen[3],HeadworksOutputValve.PctOpen[4]);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n", 
		AspOutputValve.Name, AspOutputValve.PctOpen[0],AspOutputValve.PctOpen[1],AspOutputValve.PctOpen[2],AspOutputValve.PctOpen[3],
		AspOutputValve.PctOpen[4]);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n", 
		FilterOutputValve.Name, FilterOutputValve.PctOpen[0],FilterOutputValve.PctOpen[1],FilterOutputValve.PctOpen[2],
		FilterOutputValve.PctOpen[3],FilterOutputValve.PctOpen[4]);
	pos += cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n", 
		DisinfectionOutputValve.Name, DisinfectionOutputValve.PctOpen[0],DisinfectionOutputValve.PctOpen[1],
		DisinfectionOutputValve.PctOpen[2],DisinfectionOutputValve.PctOpen[3],DisinfectionOutputValve.PctOpen[4]);
	pos += cromu_sprintf(StatusBuf+pos,  "#####################################################################################################################################\n");
	pos += cromu_sprintf(StatusBuf+pos,"\n");

	return(StatusBuf);
}

void InitPlant(void) {

	// Init Influent
	InitInfluent();

	// Init Headworks
	InitHeadworks();

	// Init valve between Headworks and Activated Sludge Process
	InitHeadworksOutputValve();

	// Init Activated Sludge Process
	InitAsp();

	// Init valve between Activated Sludge Process and Filters
	InitAspOutputValve();

	// Init Filters
	InitFilters();

	// Init valve between Filters and Disinfection
	InitFilterOutputValve();

	// Init Disinfection
	InitDisinfection();

	// Init valve to Discharge and Reject Storage
	InitDisinfectionOutputValve();

	// Init Effluent
	InitEffluent();

}

