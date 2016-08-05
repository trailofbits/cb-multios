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

#include <libcgc.h>
#include "stdlib.h"
#include "plant_system.h"

void RandomInfluent(void);
void InitPlant(void);
void PrintPlantSchematic(void);
void PrintPlantStatus(void);
char *PrintPlantStatusBuf(void);
void SetValveOutput(pPlantSystem pValve, uint8_t Output, double PctOpen);
double GetValvePctFlow(pPlantSystem pValve, uint8_t Output);
void ChangeAerationPercent(pPlantSystem pAsp, double NewPct);
void ChangeGlycerinRate(pPlantSystem pAsp, double NewRate);
void ChangeAlumRate(pPlantSystem pAsp, double NewRate);
void ChangeNumActiveFilters(pPlantSystem pFilter, uint8_t NumFilters);
void ChangeChlorineRate(pPlantSystem pDisinfection, double NewChlorineRate);
void SetSystemName(pPlantSystem pSystem, char *NewName);
void CheckEffluentQuality(void);

#endif
