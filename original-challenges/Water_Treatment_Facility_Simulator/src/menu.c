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
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "plant.h"
#include "string.h"

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

extern uint8_t SimStepCount;

int32_t read_until(char *buf, char delimiter, size_t max) {
	size_t total_len = 0;
	char c;
	size_t num_bytes;

	if (buf == NULL) {
		return(-1);
	}

	while (total_len < max-1) {
		if (receive(STDIN, &c, 1, &num_bytes) != 0) {
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

void PrintAspMenu(void) {
	char buf[9];
	int32_t len;
	uint8_t Num;
	double NewPct;
	double NewRate;

	while (1) {
		// Print the ASP control menu
		cromu_puts("1. Change aeration rate");
		cromu_puts("2. Change glycerin rate");
		cromu_puts("3. Change alum rate");
		cromu_puts("4. Return to previous menu");
		cromu_printf("Selection: ");
	
		if ((len = read_until(buf, '\n', 3)) == -1) {
			_terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cromu_printf("Which ASP 0-$d: ", NumAsp-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}

				cromu_printf("New aeration percent: ");
				if ((len = read_until(buf, '\n', 8)) == -1) {
					_terminate(-1);
				}
				NewPct = cromu_atof(buf);
				if (NewPct < 0 || NewPct > 100.0) {
					continue;
				}

				ChangeAerationPercent(&Asp[Num], NewPct);

				break;
			case '2':
				cromu_printf("Which ASP 0-$d: ", NumAsp-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}

				cromu_printf("New glycerin rate (0-100 gallons/hr): ");
				if ((len = read_until(buf, '\n', 8)) == -1) {
					_terminate(-1);
				}
				NewRate = cromu_atof(buf);
				if (NewRate < 0 || NewRate > 100.0) {
					continue;
				}

				ChangeGlycerinRate(&Asp[Num], NewRate);

				break;
			case '3':
				cromu_printf("Which ASP 0-$d: ", NumAsp-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}

				cromu_printf("New alum rate (0-100 gallons/hr): ");
				if ((len = read_until(buf, '\n', 8)) == -1) {
					_terminate(-1);
				}
				NewRate = cromu_atof(buf);
				if (NewRate < 0 || NewRate > 100.0) {
					continue;
				}

				ChangeAlumRate(&Asp[Num], NewRate);

				break;
			case '4':
				return;

		}
	}
}

void PrintFilterMenu(void) {
	char buf[4];
	int32_t len;
	uint8_t Num;
	uint8_t NumActiveFilters;

	while (1) {
		// Print the ASP control menu
		cromu_puts("1. Change active filter count");
		cromu_puts("2. Return to previous menu");
		cromu_printf("Selection: ");
	
		if ((len = read_until(buf, '\n', 3)) == -1) {
			_terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cromu_printf("Which Filter 0-$d: ", NumFilters-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}

				cromu_printf("How many filters (0-$d): ", Filter[Num].MaxFilters);
				if ((len = read_until(buf, '\n', 7)) == -1) {
					_terminate(-1);
				}
				NumActiveFilters = cromu_atoi(buf);
				if (NumActiveFilters < 0 || NumActiveFilters > Filter[Num].MaxFilters) {
					continue;
				}

				ChangeNumActiveFilters(&Filter[Num], NumActiveFilters);

				break;
			case '2':
				return;

		}
	}

}


void PrintDisinfectionMenu(void) {
	char buf[9];
	int32_t len;
	uint8_t Num;
	double NewChlorineRate;

	while (1) {
		// Print the ASP control menu
		cromu_puts("1. Change chlorine rate");
		cromu_puts("2. Return to previous menu");
		cromu_printf("Selection: ");
	
		if ((len = read_until(buf, '\n', 3)) == -1) {
			_terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cromu_printf("Which Disinfection system 0-$d: ", NumDisinfection-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
		
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumDisinfection-1) {
					continue;
				}

				cromu_printf("New chlorine rate (0-100): ");
				if ((len = read_until(buf, '\n', 8)) == -1) {
					_terminate(-1);
				}
				NewChlorineRate = cromu_atof(buf);
				if (NewChlorineRate < 0.0 || NewChlorineRate > 100.0) {
					continue;
				}

				ChangeChlorineRate(&Disinfection[Num], NewChlorineRate);

				break;
			case '2':
				return;

		}
	}
}

void PrintRenameMenu(void) {
	char buf[256];
	int8_t len;
	char System;
	uint8_t Num;

	while (1) {
		// print the list of systems
		cromu_puts("1. Influent");
		cromu_puts("2. Headworks");
		cromu_puts("3. ASPs");
		cromu_puts("4. Filters");
		cromu_puts("5. Disinfections");
		cromu_puts("6. Effluent");
		cromu_puts("7. Valves");
		cromu_puts("8. Return to previous menu");
		cromu_printf("Selection: ");

		if ((len = read_until(buf, '\n', 3)) == -1) {
			_terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				cromu_printf("New Influent name: ");
				if ((len = read_until(buf, '\n', 31)) == -1) {
					_terminate(-1);
				}
				strncpy(Influent.Name, buf, len+1);
				break;
			case '2':
				cromu_printf("New Headworks name: ");
				if ((len = read_until(buf, '\n', 31)) == -1) {
					_terminate(-1);
				}
				strncpy(Headworks.Name, buf, len+1);
				break;
			case '3':
				cromu_printf("Which ASP 0-$d: ", NumAsp-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}
				cromu_printf("New ASP$d name: ", Num);
				if ((len = read_until(buf, '\n', 31)) == -1) {
					_terminate(-1);
				}
				strncpy(Asp[Num].Name, buf, len+1);
				break;
			case '4':
				cromu_printf("Which Filter 0-$d: ", NumFilters-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}
				cromu_printf("New Filter$d name: ", Num);
				if ((len = read_until(buf, '\n', 31)) == -1) {
					_terminate(-1);
				}
				strncpy(Filter[Num].Name, buf, len+1);
				break;
			case '5':
				cromu_printf("Which Disinfection system 0-$d: ", NumAsp-1);
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num > NumAsp-1) {
					continue;
				}
				cromu_printf("New Disinfection$d name: ", Num);
				if ((len = read_until(buf, '\n', 31)) == -1) {
					_terminate(-1);
				}
				strncpy(Disinfection[Num].Name, buf, len+1);
				break;
			case '6':
				cromu_printf("New Effluent name: ");
				if ((len = read_until(buf, '\n', 31)) == -1) {
					_terminate(-1);
				}
				strncpy(Effluent.Name, buf, len+1);
				break;
			case '7':
				cromu_puts("1. V1");
				cromu_puts("2. V2");
				cromu_puts("3. V3");
				cromu_puts("4. V4");
				cromu_printf("Which valve: ");
				if ((len = read_until(buf, '\n', 3)) == -1) {
					_terminate(-1);
				}
				if (len != 1) {
					continue;
				}
				Num = cromu_atoi(buf);
				if (Num == 1) {
					cromu_printf("New V1 name: ");
					if ((len = read_until(buf, '\n', 31)) == -1) {
						_terminate(-1);
					}
					strncpy(HeadworksOutputValve.Name, buf, len+1);
				} else if (Num == 2) {
					cromu_printf("New V2 name: ");
					if ((len = read_until(buf, '\n', 31)) == -1) {
						_terminate(-1);
					}
					strncpy(AspOutputValve.Name, buf, len+1);
				} else if (Num == 3) {
					cromu_printf("New V3 name: ");
					if ((len = read_until(buf, '\n', 31)) == -1) {
						_terminate(-1);
					}
					strncpy(FilterOutputValve.Name, buf, len+1);
				} else if (Num == 4) {
					cromu_printf("New V4 name: ");
#ifdef PATCHED_1
					if ((len = read_until(buf, '\n', 31)) == -1) {
						_terminate(-1);
					}
					strncpy(DisinfectionOutputValve.Name, buf, len+1);

#else
					if (read_until(buf, '\n', 255) == -1) {
						_terminate(-1);
					}
					len = strlen(buf);
					if (len < 31) {
						strcpy(DisinfectionOutputValve.Name, buf);
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
void PrintValveMenu(void) {
	char buf[10];
	int32_t len;
	uint8_t Output;
	double PctOpen;
	char Valve;

	while (1) {
		// Print the Valve control menu
		cromu_puts("1. Change valve V1 output percentage");
		cromu_puts("2. Change valve V2 output percentage");
		cromu_puts("3. Change valve V3 output percentage");
		cromu_puts("4. Change valve V4 output percentage");
		cromu_puts("5. Return to previous menu");
		cromu_printf("Selection: ");
	
		if ((len = read_until(buf, '\n', 3)) == -1) {
			_terminate(-1);
		}

		if (len != 1) {
			continue;
		}
		Valve = buf[0];
		if (Valve == '5') {
			return;
		}

		// which valve output?
		cromu_printf("Valve Output: ");
		if ((len = read_until(buf, '\n', 3)) == -1) {
			_terminate(-1);
		}
		if (len != 1) {
			continue;
		}
		Output = buf[0]-0x30;

		// what percent open?
		cromu_printf("Percent Open (0.00-100.00): ");
		if ((len = read_until(buf, '\n', 8)) == -1) {
			_terminate(-1);
		}
		if (len > 6) {
			continue;
		}
		PctOpen = cromu_atof(buf);

		switch (Valve) {
			case '1':
				SetValveOutput(&HeadworksOutputValve, Output, PctOpen);
				break;
			case '2':
				SetValveOutput(&AspOutputValve, Output, PctOpen);
				break;
			case '3':
				SetValveOutput(&FilterOutputValve, Output, PctOpen);
				break;
			case '4':
				SetValveOutput(&DisinfectionOutputValve, Output, PctOpen);
				break;
		}
	}
}

void PrintSystemBanner(void) {

	cromu_puts("Welcome to the Wastewater Treatement Plant Simulator");
	cromu_puts("###################################################");
	cromu_puts("Your job is to take the plant described in the schematic above and make potable water.");
	cromu_puts("The simulation starts with a random plant status.");
	cromu_puts("");

}

uint8_t PrintMenu(void) {
	char buf[4];
	int32_t len;

	while (1) {
		// Print the top level menu
		cromu_puts("Wastewater Treatment Plant Simulation");
		cromu_printf("Simulation Hour $d\n", SimStepCount);
		cromu_puts("1. Print plant schematic");
		cromu_puts("2. Print plant status");
		cromu_puts("3. Control Activated Sludge Process (ASP)");
		cromu_puts("4. Control Filters");
		cromu_puts("5. Control Disinfection");
		cromu_puts("6. Control Valves");
		cromu_puts("7. Rename System");
		cromu_puts("8. Run Simulation Step");
		cromu_puts("9. Exit");
		cromu_printf("Selection: ");
	
		if ((len = read_until(buf, '\n', 4)) == -1) {
			_terminate(-1);
		}

		if (len != 1) {
			continue;
		}

		switch (buf[0]) {
			case '1':
				PrintPlantSchematic();
				break;
			case '2':
				PrintPlantStatus();
				break;
			case '3':
				PrintAspMenu();
				break;
			case '4':
				PrintFilterMenu();
				break;
			case '5':
				PrintDisinfectionMenu();
				break;
			case '6':
				PrintValveMenu();
				break;
			case '7':
				PrintRenameMenu();
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

