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
#ifndef PLANT_H
#define PLANT_H

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_plant_system.h"

void cgc_RandomInfluent(void);
void cgc_InitPlant(void);
void cgc_PrintPlantSchematic(void);
void cgc_PrintPlantStatus(void);
char *cgc_PrintPlantStatusBuf(void);
void cgc_SetValveOutput(pPlantSystem pValve, uint8_t Output, double PctOpen);
double cgc_GetValvePctFlow(pPlantSystem pValve, uint8_t Output);
void cgc_ChangeAerationPercent(pPlantSystem pAsp, double NewPct);
void cgc_ChangeGlycerinRate(pPlantSystem pAsp, double NewRate);
void cgc_ChangeAlumRate(pPlantSystem pAsp, double NewRate);
void cgc_ChangeNumActiveFilters(pPlantSystem pFilter, uint8_t cgc_NumFilters);
void cgc_ChangeChlorineRate(pPlantSystem pDisinfection, double NewChlorineRate);
void cgc_SetSystemName(pPlantSystem pSystem, char *NewName);
void cgc_CheckEffluentQuality(void);

#endif
