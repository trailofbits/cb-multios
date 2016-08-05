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
#ifndef PLANT_SYSTEM_H
#define PLANT_SYSTEM_H

#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"

#define MAX_VALVE_INPUT (5)
#define MAX_VALVE_OUTPUT (5)
#define MAX_FILTERS (10)
#define SQFT_PER_FILTER (100)
#define MINUTES_PER_DAY (60*24)

#define INFLUENT (0)
#define HEADWORKS (1)
#define ASP (2)
#define FILTER (3)
#define DISINFECTION (4)
#define VALVE (5)
#define EFFLUENT (6)

typedef struct _plantsystem {
	// System Type
	uint8_t Type;

	// system name
	char Name[32];

	// Headworks values
	double TssReductionPct; 

	// Actived Sludge Process values
	double AerationPct;
	double AerationMaxScfm;
	double GlycerinRate;
	double AlumRate;

	// Filter values
	double GpmPerSqft;
	uint8_t NumActiveFilters;
	uint8_t MaxFilters;

	// Disinfection values
	uint8_t SuccessfulDisinfection;
	double ChlorineRate;
	double ChlorineResidual;

	// Effluent
	uint8_t QualityFailures;

	// valve values
	// pointer to structs that are outputs from the valve
	struct _plantsystem *Output[MAX_VALVE_OUTPUT];

	// common values for most plant systems
	double Flow;     // MGD
	double Cbod;	 // lbs/day
	double Tss;      // lbs/day
	double Tn;       // lbs/day
	double Tp;       // lbs/day

	// pointer to structs that are inputs to the valve
	struct _plantsystem *Input[MAX_VALVE_INPUT];

	// percent open for each valve output
	double PctOpen[MAX_VALVE_OUTPUT];
	
} PlantSystem, *pPlantSystem;

#endif
