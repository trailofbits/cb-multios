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
#include "libcgc.h"
#include "cgc_service.h"
#include "cgc_stdlib.h"
#include "cgc_malloc.h"
#include "cgc_dates.h"


int cgc_log_dives(logbook_type *Info)  {

	dive_log_type *next_dive;
	char buffer[1024];
	char buffer2[1024];
	cgc_size_t count;

	// if this is the first entry, assign it to the head of the list
	if (Info->dives == 0)  {
		Info->dives=cgc_calloc(1, sizeof(dive_log_type));

		if (Info->dives==0)
			cgc__terminate(-1);

		next_dive = Info->dives;
	}
	// if its not the first, append to the end
	else  {

		next_dive = Info->dives;
		while (next_dive->next != 0)
			next_dive = next_dive->next;

		next_dive->next = cgc_calloc(1, sizeof(dive_log_type));

		if (next_dive->next==0)
			cgc__terminate(-1);

		next_dive = next_dive->next;
	}


	// now gather all the dive meta data

	cgc_printf("Dive Site");

	if (next_dive->dive_site_name[0]!= 0)
		cgc_printf(" (@s)", next_dive->dive_site_name);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(next_dive->dive_site_name));

	if (count > 0)
		cgc_strncpy(next_dive->dive_site_name, buffer, sizeof(next_dive->dive_site_name));


	cgc_printf("Date");

	if (next_dive->dive_date[0]!= 0)
		cgc_printf(" (@s)", next_dive->dive_date);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(next_dive->dive_date));

	if (count > 0)
		cgc_strncpy(next_dive->dive_date, buffer, count);


	cgc_printf("Time");

	if (next_dive->dive_time[0]!= 0)
		cgc_printf(" (@s)", next_dive->dive_time);

	cgc_printf(": ");

	count=cgc_getline(buffer2, sizeof(next_dive->dive_time));

	if (count > 0)
		cgc_strncpy(next_dive->dive_time, buffer2, count);

	cgc_strncat(buffer, " ", 1);
	cgc_strncat(buffer, buffer2, cgc_strlen(buffer2));

	datetime_struct_type tm;
	next_dive->timestamp =  cgc_str2datetime(buffer, &tm);

	cgc_printf("Location (area/city)");

	if (next_dive->location[0]!= 0)
		cgc_printf(" (@s)", next_dive->location);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(next_dive->location));

	if (count > 0)
		cgc_strncpy(next_dive->location, buffer, count);

		cgc_printf("Max Depth in ft");

	if (next_dive->max_depth!= 0)
		cgc_printf(" (@d)", next_dive->max_depth);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(buffer));

	if (count > 0)
		next_dive->max_depth= cgc_atoi(buffer);

		cgc_printf("Avg Depth in ft");

	if (next_dive->avg_depth!= 0)
		cgc_printf(" (@d)", next_dive->avg_depth);

	cgc_printf(": ");

	count=cgc_getline(buffer, sizeof(buffer));

	if (count > 0)
		next_dive->avg_depth=cgc_atoi(buffer);

	cgc_printf("Dive Duration (mins)");

	if (next_dive->dive_length!= 0)
		cgc_printf(" (@d)", next_dive->dive_length);

	cgc_printf(": ");

	count=cgc_getline(buffer, 13);

	if (count > 0)
		next_dive->dive_length = cgc_atoi(buffer);


	cgc_printf("O2 Percentage");

	if (next_dive->O2_percent!= 0)
		cgc_printf(" (@d)", next_dive->O2_percent);

	cgc_printf(": ");

	count=cgc_getline(buffer, 11);

	if (count > 0)
		next_dive->O2_percent=cgc_atoi(buffer);

	
	cgc_printf("Pressure In (psi)");

	if (next_dive->pressure_in!= 0)
		cgc_printf(" (@d)", next_dive->pressure_in);

	cgc_printf(": ");

	count=cgc_getline(buffer, 20);

	if (count > 0)
		next_dive->pressure_in=cgc_atoi(buffer);

	cgc_printf("Pressure Out (psi)");

	if (next_dive->pressure_out!= 0)
		cgc_printf(" (@d)", next_dive->pressure_out);

	cgc_printf(": ");

	count=cgc_getline(buffer, 11);

	if (count > 0)
		next_dive->pressure_out=cgc_atoi(buffer);

	next_dive->next=0;

	return 0;
}


