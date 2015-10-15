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


int dive_statistics(logbook_type *Info)  {

	char buf[1024];
	int rcv_cnt;
	int dive_count = 0;
	int sum_max_depths = 0;
	int max_depth_count = 0;
	int sum_dive_lengths = 0;
	int dive_lengths_count = 0;
	dive_log_type *next_dive;

	printf("\n");

	if (Info->dives == 0) {

		printf("No dives are logged\n");
		return -1;

	}

	next_dive = Info->dives;


	while (next_dive != 0) {

		++dive_count;

		if (next_dive->max_depth > 0) {

			sum_max_depths+= next_dive->max_depth;
			++max_depth_count;
		}
				
		if (next_dive->dive_length > 0) {

			sum_dive_lengths+= next_dive->dive_length;
			++dive_lengths_count;
		}

		next_dive = next_dive->next;
	} // while 

	printf("Dives logged: @d\n", dive_count);

	if (max_depth_count > 0) 
		printf("Average Max Depth: @d\n", sum_max_depths/max_depth_count);
	else
		printf("Average Max Depth: 0\n");

	if (dive_lengths_count > 0)
		printf("Average Dive Length: @d\n", sum_dive_lengths/dive_lengths_count);
	else
		printf("Average Dive Length: 0\n");



	return 0;
}