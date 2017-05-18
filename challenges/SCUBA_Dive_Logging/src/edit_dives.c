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
#include "cgc_menu.h"
#include "cgc_stdlib.h"

int cgc_edit_dives(logbook_type *Info)  {

	char buf[1024];
	int rcv_cnt;

	dive_log_type *next_dive;
	next_dive = Info->dives;

	int dive_count = 1;
	int dive_number_to_edit = 0;

	if (next_dive == 0) {

		cgc_printf("\n");
		cgc_printf("Dive Log is empty\n");
		return 0;
	}

	cgc_list_dives(Info);

	cgc_printf("\n");
	cgc_printf("Enter Dive # to edit: ");

	rcv_cnt=cgc_getline(buf, sizeof(buf));
		
	if (rcv_cnt==0)
		return 0;

	dive_number_to_edit=cgc_atoi(buf);

	next_dive = Info->dives;
	dive_count = 1;

	while (dive_count < dive_number_to_edit && next_dive!= 0) {
		++dive_count;
		next_dive=next_dive->next;

	}

	if (dive_count==dive_number_to_edit && next_dive != 0) {
		cgc_printf("Editing dive number @d\n", dive_number_to_edit);

		// now display and allow for updating of the data
		cgc_update_dive(next_dive);
	}
	else {

		cgc_printf("Invalid dive number entered\n");

	}
	
	return 0;
}


int cgc_update_dive(dive_log_type *dive) {


char buffer[1024];
char buf2[1024];
cgc_size_t count;

	cgc_printf("Dive Site");

	if (dive->dive_site_name[0]!= 0)
		cgc_printf(" (@s)", dive->dive_site_name);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(dive->dive_site_name));

	if (count > 0) {
		cgc_strncpy(dive->dive_site_name, buffer, sizeof(dive->dive_site_name));
	}

	cgc_printf("Date");

	if (dive->dive_date[0]!= 0)
		cgc_printf(" (@s)", dive->dive_date);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(dive->dive_date));

	if (count > 0)
		cgc_strncpy(dive->dive_date, buffer, sizeof(dive->dive_date));

	cgc_printf("Time");

	if (dive->dive_time[0]!= 0)
		cgc_printf(" (@s)", dive->dive_time);

	cgc_printf(": ");

	count=cgc_getline(buf2, sizeof(dive->dive_time));

	if (count > 0)
		cgc_strncpy(dive->dive_time, buf2, sizeof(dive->dive_time));

	cgc_strncat(buffer, " ", 1);
	cgc_strncat(buffer, buf2, cgc_strlen(buf2));

	datetime_struct_type tm;
	dive->timestamp =  cgc_str2datetime(buffer, &tm);

	cgc_printf("Location (area/city)");

	if (dive->location[0]!= 0)
		cgc_printf(" (@s)", dive->location);

	cgc_printf(": ");

#ifdef PATCHED
    count=cgc_getline(buffer, sizeof(dive->location));
#else
	count=cgc_getline(buffer, sizeof(buffer));
#endif

	if (count > 0)
		cgc_strncpy(dive->location, buffer, count);

	cgc_printf("Max Depth in ft");

	if (dive->max_depth!= 0)
		cgc_printf(" (@d)", dive->max_depth);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(buffer));

	if (count > 0)
		dive->max_depth= cgc_atoi(buffer);

	cgc_printf("Avg Depth in ft");

	if (dive->avg_depth!= 0)
		cgc_printf(" (@d)", dive->avg_depth);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(buffer));

	if (count > 0)
		dive->avg_depth=cgc_atoi(buffer);

	cgc_printf("Dive Duration (mins)");

	if (dive->dive_length!= 0)
		cgc_printf(" (@d)", dive->dive_length);

	cgc_printf(": ");

	count=cgc_getline(buffer, 13);

	if (count > 0)
		dive->dive_length = cgc_atoi(buffer);

	cgc_printf("O2 Percentage");

	if (dive->O2_percent!= 0)
		cgc_printf(" (@d)", dive->O2_percent);

	cgc_printf(": ");

	count=cgc_getline(buffer, 11);

	if (count > 0)
		dive->O2_percent=cgc_atoi(buffer);
	
	cgc_printf("Pressure In (psi)");

	if (dive->pressure_in!= 0)
		cgc_printf(" (@d)", dive->pressure_in);

	cgc_printf(": ");

	count=cgc_getline(buffer, 20);

	if (count > 0)
		dive->pressure_in=cgc_atoi(buffer);

	cgc_printf("Pressure Out (psi)");

	if (dive->pressure_out!= 0)
		cgc_printf(" (@d)", dive->pressure_out);

	cgc_printf(": ");

	count=cgc_getline(buffer, 11);

	if (count > 0)
		dive->pressure_out=cgc_atoi(buffer);

	return 0;

}