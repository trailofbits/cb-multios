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
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_prng.h"
#include "cgc_plant.h"
#include "cgc_plant_system.h"

// plant structures
PlantSystem cgc_Influent;
PlantSystem cgc_Headworks;
PlantSystem cgc_HeadworksOutputValve;
uint8_t cgc_NumAsp = 3;
PlantSystem cgc_Asp[5];
PlantSystem cgc_AspOutputValve;
uint8_t cgc_NumFilters = 3;
PlantSystem cgc_Filter[5];
PlantSystem cgc_FilterOutputValve;
uint8_t cgc_NumDisinfection = 3;
PlantSystem cgc_Disinfection[5];
PlantSystem cgc_DisinfectionOutputValve;
PlantSystem cgc_Effluent;

char StatusBuf[8192];

//
// Calculate the random influent each round
//
void cgc_RandomInfluent(void) {
	cgc_Influent.Flow = cgc_random_in_range(9, 30) / 10.0;
	cgc_Influent.Cbod = cgc_random_in_range(1900, 4000);
	cgc_Influent.Tss = cgc_random_in_range(2000, 5000);
	cgc_Influent.Tn = cgc_random_in_range(490, 750);
	cgc_Influent.Tp = cgc_random_in_range(75, 150);
}

//
// Initialize the Influent system
//
void cgc_InitInfluent(void) {
	cgc_bzero(&cgc_Influent, sizeof(PlantSystem));

	cgc_Influent.Type = INFLUENT;
	cgc_strncpy(cgc_Influent.Name, "Influent", 31);
	cgc_Influent.Flow = 1.6;
	cgc_Influent.Cbod = 2680.0;
	cgc_Influent.Tss = 3300.0;
	cgc_Influent.Tn = 540.0;
	cgc_Influent.Tp = 94.0;
	cgc_Influent.Output[0] = &cgc_Headworks;
}

//
// Calculate the percent flow through a specified valve output
//
double cgc_GetValvePctFlow(pPlantSystem pValve, uint8_t Output) {
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
void cgc_SetValveOutput(pPlantSystem pValve, uint8_t Output, double PctOpen) {

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
void cgc_SetSystemName(pPlantSystem pSystem, char *NewName) {

	if (!pSystem) {
		return;
	}

	cgc_strncpy(pSystem->Name, NewName, 31);

}

//
// Change the ASP system aeration percentage
//
void cgc_ChangeAerationPercent(pPlantSystem pAsp, double NewPct) {

	if (!cgc_Asp || cgc_Asp->Type != ASP || NewPct < 0.0 || NewPct > 100.0) {
		return;
	}

	pAsp->AerationPct = NewPct;

}

//
// Change the ASP system glycerin rate
//
void cgc_ChangeGlycerinRate(pPlantSystem pAsp, double NewRate) {

	if (!cgc_Asp || cgc_Asp->Type != ASP || NewRate < 0.0 || NewRate > 100.0) {
		return;
	}

	pAsp->GlycerinRate = NewRate;

}

//
// Change the ASP system alum rate
//
void cgc_ChangeAlumRate(pPlantSystem pAsp, double NewRate) {

	if (!cgc_Asp || cgc_Asp->Type != ASP || NewRate < 0.0 || NewRate > 100.0) {
		return;
	}

	pAsp->AlumRate = NewRate;

}

//
// Change the Disinfection system chlorine rate
//
void cgc_ChangeChlorineRate(pPlantSystem pDisinfection, double NewChlorineRate) {

	if (!pDisinfection || pDisinfection->Type != DISINFECTION || NewChlorineRate < 0.0 || NewChlorineRate > 100.0) {
		return;
	}

	pDisinfection->ChlorineRate = NewChlorineRate;

}

//
// Change the number of active filters
//
void cgc_ChangeNumActiveFilters(pPlantSystem pFilter, uint8_t NumFilters) {

	if (!pFilter || pFilter->Type != FILTER || NumFilters < 0 || NumFilters > pFilter->MaxFilters) {
		return;
	}

	pFilter->NumActiveFilters = NumFilters;

}

//
// Change the Headworks system
//
void cgc_InitHeadworks(void) {
	cgc_bzero(&cgc_Headworks, sizeof(PlantSystem));

	cgc_Headworks.Type = HEADWORKS;
	cgc_strncpy(cgc_Headworks.Name, "Headworks", 31);
	cgc_Headworks.Input[0] = &cgc_Influent;
	cgc_Headworks.Output[0] = &cgc_HeadworksOutputValve;
	cgc_Headworks.TssReductionPct = 30.0;
}

//
// Initialize the Headworks system
//
void cgc_InitHeadworksOutputValve(void) {
	uint8_t i;

	cgc_bzero(&cgc_HeadworksOutputValve, sizeof(PlantSystem));

	cgc_HeadworksOutputValve.Type = VALVE;
	cgc_strncpy(cgc_HeadworksOutputValve.Name, "V1", 31);

	// inputs
	cgc_HeadworksOutputValve.Input[0] = &cgc_Headworks;

	// outputs and valve positions
	for (i = 0; i < cgc_NumAsp; i++) {
		cgc_HeadworksOutputValve.Output[i] = &cgc_Asp[i];
		cgc_HeadworksOutputValve.PctOpen[i] = 100.0/cgc_NumAsp;
	}
}

//
// Initialize the Active Sludge Process system
//
void cgc_InitAsp(void) {
	uint8_t i;

	cgc_bzero(&cgc_Asp, sizeof(cgc_Asp));

	for (i = 0; i < cgc_NumAsp; i++) {
		cgc_Asp[i].Type = ASP;
		cgc_cromu_sprintf(cgc_Asp[i].Name, "Asp$d", i);

		cgc_Asp[i].Input[0] = &cgc_HeadworksOutputValve;
		cgc_Asp[i].Output[0] = &cgc_AspOutputValve;

		cgc_Asp[i].AerationPct = 50.0;
		cgc_Asp[i].AerationMaxScfm = 4800.0;
		cgc_Asp[i].GlycerinRate = 4.0;
		cgc_Asp[i].AlumRate = 20.0;
	}
}

//
// Initialize the ASP Output Valve
//
void cgc_InitAspOutputValve(void) {
	uint8_t i;

	cgc_bzero(&cgc_AspOutputValve, sizeof(PlantSystem));

	cgc_AspOutputValve.Type = VALVE;
	cgc_strncpy(cgc_AspOutputValve.Name, "V2", 31);

	// inputs
	for (i = 0; i < cgc_NumAsp; i++) {
		cgc_AspOutputValve.Input[i] = &cgc_Asp[i];
	}

	// outputs to Filters
	for (i = 0; i < cgc_NumFilters; i++) {
		cgc_AspOutputValve.Output[i] = &cgc_Filter[i];
		cgc_AspOutputValve.PctOpen[i] = 100.0/cgc_NumFilters;
	}

}

//
// Initialize the Filter system
//
void cgc_InitFilters(void) {
	uint8_t i;
	double Gpm;

	cgc_bzero(&cgc_Filter, sizeof(cgc_Filter));

	for (i = 0; i < cgc_NumFilters; i++) {
		cgc_Filter[i].Type = FILTER;
		cgc_cromu_sprintf(cgc_Filter[i].Name, "Filter$d", i);
		cgc_Filter[i].Input[0] = &cgc_AspOutputValve;
		cgc_Filter[i].Output[0] = &cgc_FilterOutputValve;
	}

	// set the active and max filters
	cgc_Filter[0].MaxFilters = 2;
	cgc_Filter[0].NumActiveFilters = 1;
	cgc_Filter[1].MaxFilters = 4;
	cgc_Filter[1].NumActiveFilters = 2;
	cgc_Filter[2].MaxFilters = 4;
	cgc_Filter[2].NumActiveFilters = 2;

}

//
// Initialize the Filter Output valve
//
void cgc_InitFilterOutputValve(void) {
	uint8_t i;

	cgc_bzero(&cgc_FilterOutputValve, sizeof(PlantSystem));

	cgc_FilterOutputValve.Type = VALVE;
	cgc_strncpy(cgc_FilterOutputValve.Name, "V3", 31);

	// inputs
	for (i = 0; i < cgc_NumFilters; i++) {
		cgc_FilterOutputValve.Input[i] = &cgc_Filter[i];
	}

	// outputs
	for (i = 0; i < cgc_NumDisinfection; i++) {
		cgc_FilterOutputValve.Output[i] = &cgc_Disinfection[i];
		cgc_FilterOutputValve.PctOpen[i] = 100.0 / cgc_NumDisinfection;
	}

}

//
// Initialize the Disinfection system
//
void cgc_InitDisinfection(void) {
	uint8_t i;

	cgc_bzero(&cgc_Disinfection, sizeof(cgc_Disinfection));

	for (i = 0; i < cgc_NumDisinfection; i++) {
		cgc_Disinfection[i].Type = DISINFECTION;
		cgc_cromu_sprintf(cgc_Disinfection[i].Name, "Disinfection$d", i);
		cgc_Disinfection[i].Input[0] = &cgc_FilterOutputValve;
		cgc_Disinfection[i].Output[0] = &cgc_DisinfectionOutputValve;
		cgc_Disinfection[i].ChlorineRate = 1.0;
	}

}

//
// Initialize the Disinfection output valve
//
void cgc_InitDisinfectionOutputValve(void) {
	uint8_t i;

	cgc_bzero(&cgc_DisinfectionOutputValve, sizeof(PlantSystem));

	cgc_DisinfectionOutputValve.Type = VALVE;
	cgc_strncpy(cgc_DisinfectionOutputValve.Name, "V4", 31);

	// inputs from the disinfection systems
	for (i = 0; i < cgc_NumDisinfection; i++) {
		cgc_DisinfectionOutputValve.Input[i] = &cgc_Disinfection[i];
	}

	// output to effluent
	cgc_DisinfectionOutputValve.Output[0] = &cgc_Effluent;
	cgc_DisinfectionOutputValve.PctOpen[0] = 100.0;

}

//
// Initialize the Effluent system
//
void cgc_InitEffluent(void) {
	cgc_bzero(&cgc_Effluent, sizeof(PlantSystem));

	cgc_Effluent.Type = EFFLUENT;
	cgc_strncpy(cgc_Effluent.Name, "Effluent", 31);
	cgc_Effluent.Input[0] = &cgc_DisinfectionOutputValve;
}

//
// See if the effluent meets the water quality standards
//
void cgc_CheckEffluentQuality(void) {
	double Cbod_mgl;
	double Tss_mgl;
	double Tn_mgl;
	double Tp_mgl;

	// convert to mg/L
	Cbod_mgl = cgc_Effluent.Cbod / (cgc_Effluent.Flow * 8.34);
	Tss_mgl = cgc_Effluent.Tss / (cgc_Effluent.Flow * 8.34);
	Tn_mgl = cgc_Effluent.Tn / (cgc_Effluent.Flow * 8.34);
	Tp_mgl = cgc_Effluent.Tp / (cgc_Effluent.Flow * 8.34);

	if (Cbod_mgl > 5.0 || Tss_mgl > 5.0 || Tn_mgl > 3.0 || Tp_mgl > 1.0 || cgc_Effluent.SuccessfulDisinfection == 0) {
		// quality failed standards
		cgc_Effluent.QualityFailures++;
	}
	return;
}

void cgc_PrintPlantSchematic(void) {

	cgc_cromu_puts("Plant Schematic");
	cgc_cromu_puts("#####################################################################################################################################");
	cgc_cromu_puts("                                         --------                -----------               -----------------                         ");
	cgc_cromu_puts("                                -------> | ASP1 | ------  -----> | Filter1 | -----  -----> | Disinfection1 | -----                   ");
	cgc_cromu_puts("                                |        --------      |  |      -----------     |  |      -----------------     |                   ");
	cgc_cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cgc_cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cgc_cromu_puts("                                0                      v  0                      v  0                            v                   ");
	cgc_cromu_puts("            -------------     ------     --------     ------     -----------    ------     -----------------    ------               ");
	cgc_cromu_puts("Influent -> | Headworks | --> | V1 | 1-> | ASP2 | --> | V2 | 1-> | Filter2 | -> | V3 | 1-> | Disinfection2 | -> | V4 | 0-> Effluent  ");
	cgc_cromu_puts("            -------------     ------     --------     ------     -----------    ------     -----------------    ------               ");
	cgc_cromu_puts("                                2                      ^  2                      ^  2                            ^                   ");
	cgc_cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cgc_cromu_puts("                                |                      |  |                      |  |                            |                   ");
	cgc_cromu_puts("                                |        --------      |  |      -----------     |  |      -----------------     |                   ");
	cgc_cromu_puts("                                -------> | ASP3 | ------  -----> | Filter3 | -----  -----> | Disinfection3 | -----                   ");
	cgc_cromu_puts("                                         --------                -----------               -----------------                         ");
	cgc_cromu_puts("#####################################################################################################################################");


}

//
// Print the plant status
//
void cgc_PrintPlantStatus(void) {
	char *buf = cgc_PrintPlantStatusBuf();
	cgc_cromu_puts(buf);
}

//
// Print the plant status to the StatusBuf buffer
//
char *cgc_PrintPlantStatusBuf(void) {
	uint32_t pos = 0;

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Plant Status\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "#####################################################################################################################################\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Units\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Flow - MGD\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "CBOD, TSS, TN, TP - lbs/day\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Aeration, Glycerin_Rate, Alum_rate, OutputPct - percent\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Influent       |      Flow       CBOD        TSS         TN         TP\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f\n", cgc_Influent.Name, cgc_Influent.Flow, cgc_Influent.Cbod, cgc_Influent.Tss, cgc_Influent.Tn, cgc_Influent.Tp);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Headworks      |      Flow       CBOD        TSS         TN         TP\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f\n", cgc_Headworks.Name, cgc_Headworks.Flow, cgc_Headworks.Cbod, cgc_Headworks.Tss, cgc_Headworks.Tn, cgc_Headworks.Tp);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "ASPs           |      Flow       CBOD        TSS         TN         TP     Aeration     Glycerin_Rate    Alum_Rate\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|--------------------------------------------------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f     $8.2f          $8.2f     $8.2f\n", cgc_Asp[0].Name, cgc_Asp[0].Flow, cgc_Asp[0].Cbod, cgc_Asp[0].Tss, cgc_Asp[0].Tn, cgc_Asp[0].Tp, cgc_Asp[0].AerationPct, cgc_Asp[0].GlycerinRate, cgc_Asp[0].AlumRate);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f     $8.2f          $8.2f     $8.2f\n", cgc_Asp[1].Name, cgc_Asp[1].Flow, cgc_Asp[1].Cbod, cgc_Asp[1].Tss, cgc_Asp[1].Tn, cgc_Asp[1].Tp, cgc_Asp[1].AerationPct, cgc_Asp[1].GlycerinRate, cgc_Asp[1].AlumRate);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f     $8.2f          $8.2f     $8.2f\n", cgc_Asp[2].Name, cgc_Asp[2].Flow, cgc_Asp[2].Cbod, cgc_Asp[2].Tss, cgc_Asp[2].Tn, cgc_Asp[2].Tp, cgc_Asp[2].AerationPct, cgc_Asp[2].GlycerinRate, cgc_Asp[2].AlumRate);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Filters        |      Flow       CBOD        TSS         TN         TP     Num_Active_Filters\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|-----------------------------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f               $8d\n", cgc_Filter[0].Name, cgc_Filter[0].Flow, cgc_Filter[0].Cbod, cgc_Filter[0].Tss, cgc_Filter[0].Tn, cgc_Filter[0].Tp, cgc_Filter[0].NumActiveFilters);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f               $8d\n", cgc_Filter[1].Name, cgc_Filter[1].Flow, cgc_Filter[1].Cbod, cgc_Filter[1].Tss, cgc_Filter[1].Tn, cgc_Filter[1].Tp, cgc_Filter[1].NumActiveFilters);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f               $8d\n", cgc_Filter[2].Name, cgc_Filter[2].Flow, cgc_Filter[2].Cbod, cgc_Filter[2].Tss, cgc_Filter[2].Tn, cgc_Filter[2].Tp, cgc_Filter[2].NumActiveFilters);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Disinfection   |      Flow       CBOD        TSS         TN         TP     Chlorine_Rate\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|------------------------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f          $8.2f\n", cgc_Disinfection[0].Name, cgc_Disinfection[0].Flow, cgc_Disinfection[0].Cbod, cgc_Disinfection[0].Tss, cgc_Disinfection[0].Tn, cgc_Disinfection[0].Tp, cgc_Disinfection[0].ChlorineRate);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f          $8.2f\n", cgc_Disinfection[1].Name, cgc_Disinfection[1].Flow, cgc_Disinfection[1].Cbod, cgc_Disinfection[1].Tss, cgc_Disinfection[1].Tn, cgc_Disinfection[1].Tp, cgc_Disinfection[1].ChlorineRate);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f          $8.2f\n", cgc_Disinfection[2].Name, cgc_Disinfection[2].Flow, cgc_Disinfection[2].Cbod, cgc_Disinfection[2].Tss, cgc_Disinfection[2].Tn, cgc_Disinfection[2].Tp, cgc_Disinfection[2].ChlorineRate);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Effluent       |      Flow       CBOD        TSS         TN         TP          Quality_Failures\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|--------------------------------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |  $8.2f   $8.2f   $8.2f   $8.2f   $8.2f                        $2d\n", cgc_Effluent.Name, cgc_Effluent.Flow, cgc_Effluent.Cbod, cgc_Effluent.Tss, cgc_Effluent.Tn, cgc_Effluent.Tp, cgc_Effluent.QualityFailures);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	pos += cgc_cromu_sprintf(StatusBuf+pos,  "Valves         |    OutputPct[0]    OutputPct[1]    OutputPct[2]    OutputPct[3]    OutputPct[4]\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "---------------|--------------------------------------------------------------------------------\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n",
		cgc_HeadworksOutputValve.Name, cgc_HeadworksOutputValve.PctOpen[0],cgc_HeadworksOutputValve.PctOpen[1],cgc_HeadworksOutputValve.PctOpen[2],
		cgc_HeadworksOutputValve.PctOpen[3],cgc_HeadworksOutputValve.PctOpen[4]);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n",
		cgc_AspOutputValve.Name, cgc_AspOutputValve.PctOpen[0],cgc_AspOutputValve.PctOpen[1],cgc_AspOutputValve.PctOpen[2],cgc_AspOutputValve.PctOpen[3],
		cgc_AspOutputValve.PctOpen[4]);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n",
		cgc_FilterOutputValve.Name, cgc_FilterOutputValve.PctOpen[0],cgc_FilterOutputValve.PctOpen[1],cgc_FilterOutputValve.PctOpen[2],
		cgc_FilterOutputValve.PctOpen[3],cgc_FilterOutputValve.PctOpen[4]);
	pos += cgc_cromu_sprintf(StatusBuf+pos,"$-14s |        $8.2f        $8.2f        $8.2f        $8.2f        $8.2f\n",
		cgc_DisinfectionOutputValve.Name, cgc_DisinfectionOutputValve.PctOpen[0],cgc_DisinfectionOutputValve.PctOpen[1],
		cgc_DisinfectionOutputValve.PctOpen[2],cgc_DisinfectionOutputValve.PctOpen[3],cgc_DisinfectionOutputValve.PctOpen[4]);
	pos += cgc_cromu_sprintf(StatusBuf+pos,  "#####################################################################################################################################\n");
	pos += cgc_cromu_sprintf(StatusBuf+pos,"\n");

	return(StatusBuf);
}

void cgc_InitPlant(void) {

	// Init Influent
	cgc_InitInfluent();

	// Init Headworks
	cgc_InitHeadworks();

	// Init valve between Headworks and Activated Sludge Process
	cgc_InitHeadworksOutputValve();

	// Init Activated Sludge Process
	cgc_InitAsp();

	// Init valve between Activated Sludge Process and Filters
	cgc_InitAspOutputValve();

	// Init Filters
	cgc_InitFilters();

	// Init valve between Filters and Disinfection
	cgc_InitFilterOutputValve();

	// Init Disinfection
	cgc_InitDisinfection();

	// Init valve to Discharge and Reject Storage
	cgc_InitDisinfectionOutputValve();

	// Init Effluent
	cgc_InitEffluent();

}
