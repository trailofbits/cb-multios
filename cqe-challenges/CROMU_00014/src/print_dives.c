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
#include "service.h"
#include "stdlib.h"

int list_dives(logbook_type *Info) {
	dive_log_type *next_dive;
	int dive_count = 1;

	next_dive = Info->dives;

	printf("\n");

	if (next_dive == 0) {

		printf("Dive Log is empty\n");
		return -1;
	}

	printf("Dive# @-10s @-8s @-25s @-25s\n","Date","Time","Dive Site","Location");

	while (next_dive != 0) {

		printf("@4d: @-10s @-8s @-25s @-25s\n", dive_count, next_dive->dive_date, next_dive->dive_time, next_dive->dive_site_name,
									next_dive->location);

		next_dive = next_dive->next;
		++dive_count;

	}

	return 0;

}

int print_dives(logbook_type *Info)  {
	dive_log_type *next_dive;
	int dive_count;
	int dive_number_to_display;
	int rcv_cnt;
	char buf[100];

	if (list_dives(Info) == -1)
		return -1;

	printf("\n");
	printf("Enter Dive # to display: ");

	rcv_cnt=getline(buf, sizeof(buf));
		
	if (rcv_cnt==0)
		return 0;

	dive_number_to_display=atoi(buf);

	next_dive = Info->dives;
	dive_count = 1;

	while (dive_count < dive_number_to_display && next_dive!= 0) {
		++dive_count;
		next_dive=next_dive->next;

	}

	if (dive_count==dive_number_to_display && next_dive != 0) {

		printf("\n");

		printf("          Date: @s\n", next_dive->dive_date);
		printf("          Time: @s\n", next_dive->dive_time);
		printf("     Dive Site: @s\n", next_dive->dive_site_name);
		printf("      Location: @s\n", next_dive->location);
		printf("     Max Depth: @d\n", next_dive->max_depth);
		printf("     Avg Depth: @d\n", next_dive->avg_depth);
		printf("      Duration: @d\n", next_dive->dive_length);
		printf("    O2 Percent: @d\n", next_dive->O2_percent);
		printf("Start Pressure: @d\n", next_dive->pressure_in);
		printf("  End Pressure: @d\n", next_dive->pressure_out);
		printf("     Bin Count: @d\n", next_dive->bincount);
		printf("\n");

	}
	else {

		printf("Invalid dive number entered\n");

	}

return 0;

}

