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
#include <libcgc.h>
#include "service.h"
#include "stdlib.h"
#include "malloc.h"
#include "dates.h"


int download_dive(logbook_type *Info)  {

	dive_log_type *next_dive;
	char buffer[1024];
	char buffer2[1024];
	size_t count;
	int ret_code;
	time_t sample_time;
	time_t first_sample;
	int sample_depth;
	struct dive_data *temp_ptr;
	datetime_struct_type tm;
	int max_depth=0;
	int sum_depth=0;
	int count_samples=0;
	time_t delta_time;
	int *bins;
	int bin_number;
	int i; 

	// receive the first samples outside of the loop to start the linked list
	ret_code=receive_bytes ((unsigned char *)&first_sample, sizeof(first_sample));

	if (ret_code < 0 ) {

		printf("received error code \n");
		return -1;
	}

	
	ret_code=receive_bytes((unsigned char *)&sample_depth, sizeof(sample_depth));

	if (ret_code < 0) {
		printf("received error code or zero sample \n");
		return -1;
	}


	// ok we got a valid sample, so allocate the data for the new dive 

	// if its the first dive in the log
	if (Info->dives == 0)  {
		Info->dives=calloc(1, sizeof(dive_log_type));

		if (Info->dives==0)
			_terminate(-1);

		next_dive = Info->dives;
	}
	// otherwise, add it to the end of the log
	else  {

		next_dive = Info->dives;
		while (next_dive->next != 0)
			next_dive = next_dive->next;

		next_dive->next = calloc(1, sizeof(dive_log_type));

		if (next_dive->next==0)
			_terminate(-1);

		next_dive = next_dive->next;
	}

	// now allocate memory for the first data point in the dive
	next_dive->data=calloc(1, sizeof(struct dive_data));

	if (next_dive->data==0)
		_terminate(-1);

	temp_ptr=next_dive->data;

	temp_ptr->timestamp=first_sample;
	temp_ptr->depth=sample_depth;

	// if (sample_depth > max_depth)
	// 	max_depth=sample_depth;

	// sum_depth+=sample_depth;
	// count_samples++;

	// convert the timestamp value into a broken out structure of the date/time
	// this will be used to fill out part of the meta data about the dive
	time_t2datetime(first_sample, &tm);


	// now loops and get more data samples
	while(1) {

		ret_code=receive_bytes((unsigned char *)&sample_time, sizeof(sample_time));

		if (ret_code < 0) {
			printf("received error code or zero timestamp \n");
			return -1;
		}

		// input is terminated by a zero timestamp value 
		if (sample_time == 0)  {
			break;

		}

		ret_code=receive_bytes((unsigned char *)&sample_depth, sizeof(sample_depth));

		if (ret_code < 0) {
			printf("received error code or zero sample \n");
			return -1;
		}

		temp_ptr->next=calloc(1, sizeof(dive_data_type));

		if (temp_ptr->next == 0)
			_terminate(-1);

		temp_ptr=temp_ptr->next;

		temp_ptr->timestamp=sample_time;
		temp_ptr->depth=sample_depth;

	}

	temp_ptr->next=0;

	// calculate the start to finish duration of the dive in seconds
	delta_time = temp_ptr->timestamp - first_sample;

	// set the dive time to the first sample
	next_dive->timestamp = first_sample;
	to_date_str(&tm, next_dive->dive_date);
	to_time_str(&tm, next_dive->dive_time);

	//timestamps are in seconds, convert the delta to minutes for the dive log
	next_dive->dive_length = delta_time/60;

	//setup bins per minute of the dive
	bins=calloc(next_dive->dive_length+1, sizeof(int));

	 if (bins==0)
	 	_terminate(-1);


	// now run through the samples to collect meta data for the dive log

	max_depth = 0;
	sum_depth = 0;
	count_samples = 0;

	temp_ptr=next_dive->data;

	while (temp_ptr != 0) {

		if (temp_ptr->depth > max_depth)
			max_depth=temp_ptr->depth;

		sum_depth+=temp_ptr->depth;
		count_samples++;

		bin_number = (temp_ptr->timestamp - first_sample)/60;
#ifdef PATCHED
		if (bin_number >= 0 && bin_number < next_dive->dive_length+1)
#endif
			bins[bin_number]++;

		temp_ptr=temp_ptr->next;

	}

	next_dive->bincount=0;

	for (i=0;i< next_dive->dive_length+1; ++i)
		next_dive->bincount+=bins[i];


	free(bins);

	next_dive->max_depth= max_depth;

	if (count_samples > 0)
		next_dive->avg_depth= sum_depth/count_samples;
	else
		next_dive->avg_depth=0;

	// now prompt for the remaining entries, but also allow editing of stuff from the data
	printf("Dive Site");

	if (next_dive->dive_site_name[0]!= 0)
		printf(" (@s)", next_dive->dive_site_name);

	printf(": ");

	count=getline(buffer, sizeof(next_dive->dive_site_name));

	if (count > 0)
		strncpy(next_dive->dive_site_name, buffer, sizeof(next_dive->dive_site_name));


	printf("Date");

	if (next_dive->dive_date[0]!= 0)
		printf(" (@s)", next_dive->dive_date);

	printf(": ");

	count=getline(buffer, sizeof(next_dive->dive_date));

	if (count > 0)
		strncpy(next_dive->dive_date, buffer, count);


	printf("Time");

	if (next_dive->dive_time[0]!= 0)
		printf(" (@s)", next_dive->dive_time);

	printf(": ");

	count=getline(buffer2, sizeof(next_dive->dive_time));

	if (count > 0)
		strncpy(next_dive->dive_time, buffer2, count);

	printf("Location (area/city)");

	if (next_dive->location[0]!= 0)
		printf(" (@s)", next_dive->location);

	printf(": ");

	count=getline(buffer, sizeof(next_dive->location));

	if (count > 0)
		strncpy(next_dive->location, buffer, count);

		printf("Max Depth in ft");

	if (next_dive->max_depth!= 0)
		printf(" (@d)", next_dive->max_depth);

	printf(": ");

	count=getline(buffer, sizeof(buffer));

	if (count > 0)
		next_dive->max_depth= atoi(buffer);

		printf("Avg Depth in ft");

	if (next_dive->avg_depth!= 0)
		printf(" (@d)", next_dive->avg_depth);

	printf(": ");

	count=getline(buffer, sizeof(buffer));

	if (count > 0)
		next_dive->avg_depth=atoi(buffer);

	printf("Dive Duration (mins)");

	if (next_dive->dive_length!= 0)
		printf(" (@d)", next_dive->dive_length);

	printf(": ");

	count=getline(buffer, 13);

	if (count > 0)
		next_dive->dive_length = atoi(buffer);

	printf("O2 Percentage");

	if (next_dive->O2_percent!= 0)
		printf(" (@d)", next_dive->O2_percent);

	printf(": ");

	count=getline(buffer, 11);

	if (count > 0)
		next_dive->O2_percent=atoi(buffer);

	
	printf("Pressure In (psi)");

	if (next_dive->pressure_in!= 0)
		printf(" (@d)", next_dive->pressure_in);

	printf(": ");

	count=getline(buffer, 20);

	if (count > 0)
		next_dive->pressure_in=atoi(buffer);

	printf("Pressure Out (psi)");

	if (next_dive->pressure_out!= 0)
		printf(" (@d)", next_dive->pressure_out);

	printf(": ");

	count=getline(buffer, 11);

	if (count > 0)
		next_dive->pressure_out=atoi(buffer);

	next_dive->next=0;

return 0;
}

