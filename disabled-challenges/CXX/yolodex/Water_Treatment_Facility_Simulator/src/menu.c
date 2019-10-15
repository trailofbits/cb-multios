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
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_plant.h"
#include "cgc_string.h"

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

extern uint8_t cgc_SimStepCount;

int32_t cgc_read_until(char *buf, char delimiter, cgc_size_t max) {
	cgc_size_t total_len = 0;
	char c;
	cgc_size_t num_bytes;

	if (buf == NULL) {
		return(-1);
	}

	while (total_len < max-1) {
		if (cgc_receive(STDIN, &c, 1, &num_bytes) != 0) {
			return(-1);
		}
		if (num_bytes == 0) {
			return(-1);
		}
		if (c == delimiter) {
			break;
		}
		buf[total_len++] = c;
	}
	buf[total_len] = '\0';

	return(total_len);
}

void cgc_PrintAspMenu(void) {
	char buf[9];
	int32_t len;
	uint8_t Num;
	double NewPct;
	double NewRate;

	while (1) {
		// Print the ASP control menu
		cgc_cromu_puts("1. Change aeration rate");
		cgc_cromu_puts("2. Change glycerin rate");
		cgc_cromu_puts("3. Change alum rate");
		cgc_cromu_puts("4. Return to previous menu");
		cgc_cromu_printf("Selection: ");
	
		if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
			cgc__terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cgc_cromu_printf("Which ASP 0-$d: ", cgc_NumAsp-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}

				cgc_cromu_printf("New aeration percent: ");
				if ((len = cgc_read_until(buf, '\n', 8)) == -1) {
					cgc__terminate(-1);
				}
				NewPct = cgc_cromu_atof(buf);
				if (NewPct < 0 || NewPct > 100.0) {
					continue;
				}

				cgc_ChangeAerationPercent(&cgc_Asp[Num], NewPct);

				break;
			case '2':
				cgc_cromu_printf("Which ASP 0-$d: ", cgc_NumAsp-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}

				cgc_cromu_printf("New glycerin rate (0-100 gallons/hr): ");
				if ((len = cgc_read_until(buf, '\n', 8)) == -1) {
					cgc__terminate(-1);
				}
				NewRate = cgc_cromu_atof(buf);
				if (NewRate < 0 || NewRate > 100.0) {
					continue;
				}

				cgc_ChangeGlycerinRate(&cgc_Asp[Num], NewRate);

				break;
			case '3':
				cgc_cromu_printf("Which ASP 0-$d: ", cgc_NumAsp-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}

				cgc_cromu_printf("New alum rate (0-100 gallons/hr): ");
				if ((len = cgc_read_until(buf, '\n', 8)) == -1) {
					cgc__terminate(-1);
				}
				NewRate = cgc_cromu_atof(buf);
				if (NewRate < 0 || NewRate > 100.0) {
					continue;
				}

				cgc_ChangeAlumRate(&cgc_Asp[Num], NewRate);

				break;
			case '4':
				return;

		}
	}
}

void cgc_PrintFilterMenu(void) {
	char buf[4];
	int32_t len;
	uint8_t Num;
	uint8_t NumActiveFilters;

	while (1) {
		// Print the ASP control menu
		cgc_cromu_puts("1. Change active filter count");
		cgc_cromu_puts("2. Return to previous menu");
		cgc_cromu_printf("Selection: ");
	
		if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
			cgc__terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cgc_cromu_printf("Which Filter 0-$d: ", cgc_NumFilters-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}

				cgc_cromu_printf("How many filters (0-$d): ", cgc_Filter[Num].MaxFilters);
				if ((len = cgc_read_until(buf, '\n', 7)) == -1) {
					cgc__terminate(-1);
				}
				NumActiveFilters = cgc_cromu_atoi(buf);
				if (NumActiveFilters < 0 || NumActiveFilters > cgc_Filter[Num].MaxFilters) {
					continue;
				}

				cgc_ChangeNumActiveFilters(&cgc_Filter[Num], NumActiveFilters);

				break;
			case '2':
				return;

		}
	}

}


void cgc_PrintDisinfectionMenu(void) {
	char buf[9];
	int32_t len;
	uint8_t Num;
	double NewChlorineRate;

	while (1) {
		// Print the ASP control menu
		cgc_cromu_puts("1. Change chlorine rate");
		cgc_cromu_puts("2. Return to previous menu");
		cgc_cromu_printf("Selection: ");
	
		if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
			cgc__terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cgc_cromu_printf("Which Disinfection system 0-$d: ", cgc_NumDisinfection-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumDisinfection-1) {
					continue;
				}

				cgc_cromu_printf("New chlorine rate (0-100): ");
				if ((len = cgc_read_until(buf, '\n', 8)) == -1) {
					cgc__terminate(-1);
				}
				NewChlorineRate = cgc_cromu_atof(buf);
				if (NewChlorineRate < 0.0 || NewChlorineRate > 100.0) {
					continue;
				}

				cgc_ChangeChlorineRate(&cgc_Disinfection[Num], NewChlorineRate);

				break;
			case '2':
				return;

		}
	}
}

void cgc_PrintRenameMenu(void) {
	char buf[256];
	int8_t len;
	char System;
	uint8_t Num;

	while (1) {
		// print the list of systems
		cgc_cromu_puts("1. Influent");
		cgc_cromu_puts("2. Headworks");
		cgc_cromu_puts("3. ASPs");
		cgc_cromu_puts("4. Filters");
		cgc_cromu_puts("5. Disinfections");
		cgc_cromu_puts("6. Effluent");
		cgc_cromu_puts("7. Valves");
		cgc_cromu_puts("8. Return to previous menu");
		cgc_cromu_printf("Selection: ");

		if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
			cgc__terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cgc_cromu_printf("New Influent name: ");
				if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
					cgc__terminate(-1);
				}
				cgc_strncpy(cgc_Influent.Name, buf, len+1);
				break;
			case '2':
				cgc_cromu_printf("New Headworks name: ");
				if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
					cgc__terminate(-1);
				}
				cgc_strncpy(cgc_Headworks.Name, buf, len+1);
				break;
			case '3':
				cgc_cromu_printf("Which ASP 0-$d: ", cgc_NumAsp-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}
				cgc_cromu_printf("New ASP$d name: ", Num);
				if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
					cgc__terminate(-1);
				}
				cgc_strncpy(cgc_Asp[Num].Name, buf, len+1);
				break;
			case '4':
				cgc_cromu_printf("Which Filter 0-$d: ", cgc_NumFilters-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}
				cgc_cromu_printf("New Filter$d name: ", Num);
				if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
					cgc__terminate(-1);
				}
				cgc_strncpy(cgc_Filter[Num].Name, buf, len+1);
				break;
			case '5':
				cgc_cromu_printf("Which Disinfection system 0-$d: ", cgc_NumAsp-1);
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num > cgc_NumAsp-1) {
					continue;
				}
				cgc_cromu_printf("New Disinfection$d name: ", Num);
				if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
					cgc__terminate(-1);
				}
				cgc_strncpy(cgc_Disinfection[Num].Name, buf, len+1);
				break;
			case '6':
				cgc_cromu_printf("New Effluent name: ");
				if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
					cgc__terminate(-1);
				}
				cgc_strncpy(cgc_Effluent.Name, buf, len+1);
				break;
			case '7':
				cgc_cromu_puts("1. V1");
				cgc_cromu_puts("2. V2");
				cgc_cromu_puts("3. V3");
				cgc_cromu_puts("4. V4");
				cgc_cromu_printf("Which valve: ");
				if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
					cgc__terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cgc_cromu_atoi(buf);
				if (Num == 1) {
					cgc_cromu_printf("New V1 name: ");
					if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
						cgc__terminate(-1);
					}
					cgc_strncpy(cgc_HeadworksOutputValve.Name, buf, len+1);
				} else if (Num == 2) {
					cgc_cromu_printf("New V2 name: ");
					if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
						cgc__terminate(-1);
					}
					cgc_strncpy(cgc_AspOutputValve.Name, buf, len+1);
				} else if (Num == 3) {
					cgc_cromu_printf("New V3 name: ");
					if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
						cgc__terminate(-1);
					}
					cgc_strncpy(cgc_FilterOutputValve.Name, buf, len+1);
				} else if (Num == 4) {
					cgc_cromu_printf("New V4 name: ");
#ifdef PATCHED_1
					if ((len = cgc_read_until(buf, '\n', 31)) == -1) {
						cgc__terminate(-1);
					}
					cgc_strncpy(cgc_DisinfectionOutputValve.Name, buf, len+1);

#else
					if (cgc_read_until(buf, '\n', 255) == -1) {
						cgc__terminate(-1);
					}
					len = cgc_strlen(buf);
					if (len < 31) {
						cgc_strcpy(cgc_DisinfectionOutputValve.Name, buf);
					}
#endif
				} else {
					continue;
				}
				break;
			case '8':
				return;
				break;
		}
	}
}
void cgc_PrintValveMenu(void) {
	char buf[10];
	int32_t len;
	uint8_t Output;
	double PctOpen;
	char Valve;

	while (1) {
		// Print the Valve control menu
		cgc_cromu_puts("1. Change valve V1 output percentage");
		cgc_cromu_puts("2. Change valve V2 output percentage");
		cgc_cromu_puts("3. Change valve V3 output percentage");
		cgc_cromu_puts("4. Change valve V4 output percentage");
		cgc_cromu_puts("5. Return to previous menu");
		cgc_cromu_printf("Selection: ");
	
		if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
			cgc__terminate(-1);
		}

		if (len != 1) {
			continue;
		}
		Valve = buf[0];
		if (Valve == '5') {
			return;
		}

		// which valve output?
		cgc_cromu_printf("Valve Output: ");
		if ((len = cgc_read_until(buf, '\n', 3)) == -1) {
			cgc__terminate(-1);
		}
		if (len != 1) {
			continue;
		}
		Output = buf[0]-0x30;

		// what percent open?
		cgc_cromu_printf("Percent Open (0.00-100.00): ");
		if ((len = cgc_read_until(buf, '\n', 8)) == -1) {
			cgc__terminate(-1);
		}
		if (len > 6) {
			continue;
		}
		PctOpen = cgc_cromu_atof(buf);

		switch (Valve) {
			case '1':
				cgc_SetValveOutput(&cgc_HeadworksOutputValve, Output, PctOpen);
				break;
			case '2':
				cgc_SetValveOutput(&cgc_AspOutputValve, Output, PctOpen);
				break;
			case '3':
				cgc_SetValveOutput(&cgc_FilterOutputValve, Output, PctOpen);
				break;
			case '4':
				cgc_SetValveOutput(&cgc_DisinfectionOutputValve, Output, PctOpen);
				break;
		}
	}
}

void cgc_PrintSystemBanner(void) {

	cgc_cromu_puts("Welcome to the Wastewater Treatement Plant Simulator");
	cgc_cromu_puts("###################################################");
	cgc_cromu_puts("Your job is to take the plant described in the schematic above and make potable water.");
	cgc_cromu_puts("The simulation starts with a random plant status.");
	cgc_cromu_puts("");

}

uint8_t cgc_PrintMenu(void) {
	char buf[4];
	int32_t len;

	while (1) {
		// Print the top level menu
		cgc_cromu_puts("Wastewater Treatment Plant Simulation");
		cgc_cromu_printf("Simulation Hour $d\n", cgc_SimStepCount);
		cgc_cromu_puts("1. Print plant schematic");
		cgc_cromu_puts("2. Print plant status");
		cgc_cromu_puts("3. Control Activated Sludge Process (ASP)");
		cgc_cromu_puts("4. Control Filters");
		cgc_cromu_puts("5. Control Disinfection");
		cgc_cromu_puts("6. Control Valves");
		cgc_cromu_puts("7. Rename System");
		cgc_cromu_puts("8. Run Simulation Step");
		cgc_cromu_puts("9. Exit");
		cgc_cromu_printf("Selection: ");
	
		if ((len = cgc_read_until(buf, '\n', 4)) == -1) {
			cgc__terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cgc_PrintPlantSchematic();
				break;
			case '2':
				cgc_PrintPlantStatus();
				break;
			case '3':
				cgc_PrintAspMenu();
				break;
			case '4':
				cgc_PrintFilterMenu();
				break;
			case '5':
				cgc_PrintDisinfectionMenu();
				break;
			case '6':
				cgc_PrintValveMenu();
				break;
			case '7':
				cgc_PrintRenameMenu();
				break;
			case '8':
				return(1);
				break;
			case '9':
				return(0);
				break;
			default:
				break;
		}
	}
}

