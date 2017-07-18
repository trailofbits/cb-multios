/*

Author: Steve Wood <swood@cromulence.co>

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
#include "cgc_service.h"
#include "cgc_stdlib.h"

int cgc_list_dives(logbook_type *Info) {
	dive_log_type *next_dive;
	int dive_count = 1;

	next_dive = Info->dives;

	cgc_printf("\n");

	if (next_dive == 0) {

		cgc_printf("Dive Log is empty\n");
		return -1;
	}

	cgc_printf("Dive# @-10s @-8s @-25s @-25s\n","Date","Time","Dive Site","Location");

	while (next_dive != 0) {

		cgc_printf("@4d: @-10s @-8s @-25s @-25s\n", dive_count, next_dive->dive_date, next_dive->dive_time, next_dive->dive_site_name,
									next_dive->location);

		next_dive = next_dive->next;
		++dive_count;

	}

	return 0;

}

int cgc_print_dives(logbook_type *Info)  {
	dive_log_type *next_dive;
	int dive_count;
	int dive_number_to_display;
	int rcv_cnt;
	char buf[100];

	if (cgc_list_dives(Info) == -1)
		return -1;

	cgc_printf("\n");
	cgc_printf("Enter Dive # to display: ");

	rcv_cnt=cgc_getline(buf, sizeof(buf));
		
	if (rcv_cnt==0)
		return 0;

	dive_number_to_display=cgc_atoi(buf);

	next_dive = Info->dives;
	dive_count = 1;

	while (dive_count < dive_number_to_display && next_dive!= 0) {
		++dive_count;
		next_dive=next_dive->next;

	}

	if (dive_count==dive_number_to_display && next_dive != 0) {

		cgc_printf("\n");

		cgc_printf("          Date: @s\n", next_dive->dive_date);
		cgc_printf("          Time: @s\n", next_dive->dive_time);
		cgc_printf("     Dive Site: @s\n", next_dive->dive_site_name);
		cgc_printf("      Location: @s\n", next_dive->location);
		cgc_printf("     Max Depth: @d\n", next_dive->max_depth);
		cgc_printf("     Avg Depth: @d\n", next_dive->avg_depth);
		cgc_printf("      Duration: @d\n", next_dive->dive_length);
		cgc_printf("    O2 Percent: @d\n", next_dive->O2_percent);
		cgc_printf("Start Pressure: @d\n", next_dive->pressure_in);
		cgc_printf("  End Pressure: @d\n", next_dive->pressure_out);
		cgc_printf("     Bin Count: @d\n", next_dive->bincount);
		cgc_printf("\n");

	}
	else {

		cgc_printf("Invalid dive number entered\n");

	}

return 0;

}

