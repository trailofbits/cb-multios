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
#include "menu.h"
#include "stdlib.h"

int edit_dives(logbook_type *Info)  {

	char buf[1024];
	int rcv_cnt;

	dive_log_type *next_dive;
	next_dive = Info->dives;

	int dive_count = 1;
	int dive_number_to_edit = 0;

	if (next_dive == 0) {

		printf("\n");
		printf("Dive Log is empty\n");
		return 0;
	}

	list_dives(Info);

	printf("\n");
	printf("Enter Dive # to edit: ");

	rcv_cnt=getline(buf, sizeof(buf));
		
	if (rcv_cnt==0)
		return 0;

	dive_number_to_edit=atoi(buf);

	next_dive = Info->dives;
	dive_count = 1;

	while (dive_count < dive_number_to_edit && next_dive!= 0) {
		++dive_count;
		next_dive=next_dive->next;

	}

	if (dive_count==dive_number_to_edit && next_dive != 0) {
		printf("Editing dive number @d\n", dive_number_to_edit);

		// now display and allow for updating of the data
		update_dive(next_dive);
	}
	else {

		printf("Invalid dive number entered\n");

	}
	
	return 0;
}


int update_dive(dive_log_type *dive) {


char buffer[1024];
char buf2[1024];
size_t count;

	printf("Dive Site");

	if (dive->dive_site_name[0]!= 0)
		printf(" (@s)", dive->dive_site_name);

	printf(": ");

	count=getline(buffer, sizeof(dive->dive_site_name));

	if (count > 0) {
		strncpy(dive->dive_site_name, buffer, sizeof(dive->dive_site_name));
	}

	printf("Date");

	if (dive->dive_date[0]!= 0)
		printf(" (@s)", dive->dive_date);

	printf(": ");

	count=getline(buffer, sizeof(dive->dive_date));

	if (count > 0)
		strncpy(dive->dive_date, buffer, sizeof(dive->dive_date));

	printf("Time");

	if (dive->dive_time[0]!= 0)
		printf(" (@s)", dive->dive_time);

	printf(": ");

	count=getline(buf2, sizeof(dive->dive_time));

	if (count > 0)
		strncpy(dive->dive_time, buf2, sizeof(dive->dive_time));

	strncat(buffer, " ", 1);
	strncat(buffer, buf2, strlen(buf2));

	datetime_struct_type tm;
	dive->timestamp =  str2datetime(buffer, &tm);

	printf("Location (area/city)");

	if (dive->location[0]!= 0)
		printf(" (@s)", dive->location);

	printf(": ");

#ifdef PATCHED
    count=getline(buffer, sizeof(dive->location));
#else
	count=getline(buffer, sizeof(buffer));
#endif

	if (count > 0)
		strncpy(dive->location, buffer, count);

	printf("Max Depth in ft");

	if (dive->max_depth!= 0)
		printf(" (@d)", dive->max_depth);

	printf(": ");

	count=getline(buffer, sizeof(buffer));

	if (count > 0)
		dive->max_depth= atoi(buffer);

	printf("Avg Depth in ft");

	if (dive->avg_depth!= 0)
		printf(" (@d)", dive->avg_depth);

	printf(": ");

	count=getline(buffer, sizeof(buffer));

	if (count > 0)
		dive->avg_depth=atoi(buffer);

	printf("Dive Duration (mins)");

	if (dive->dive_length!= 0)
		printf(" (@d)", dive->dive_length);

	printf(": ");

	count=getline(buffer, 13);

	if (count > 0)
		dive->dive_length = atoi(buffer);

	printf("O2 Percentage");

	if (dive->O2_percent!= 0)
		printf(" (@d)", dive->O2_percent);

	printf(": ");

	count=getline(buffer, 11);

	if (count > 0)
		dive->O2_percent=atoi(buffer);
	
	printf("Pressure In (psi)");

	if (dive->pressure_in!= 0)
		printf(" (@d)", dive->pressure_in);

	printf(": ");

	count=getline(buffer, 20);

	if (count > 0)
		dive->pressure_in=atoi(buffer);

	printf("Pressure Out (psi)");

	if (dive->pressure_out!= 0)
		printf(" (@d)", dive->pressure_out);

	printf(": ");

	count=getline(buffer, 11);

	if (count > 0)
		dive->pressure_out=atoi(buffer);

	return 0;

}