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

#ifndef DATES_H
#define DATES_H

typedef unsigned long time_t;

typedef struct {

	unsigned int month;  // 1-12
	unsigned int day;    // 1-31
	unsigned int year;   // 1970 - X
	unsigned int hour;   // 0-23
	unsigned int min;    // 0-59
	unsigned int sec;    // 0-59
	unsigned int doy;    // 0-366

}  datetime_struct_type;


// from a string formatted MM/DD/YYYY HH:MM:SS in buff, fill out the datetime_struct and return a time_t value
time_t str2datetime(char *buff, datetime_struct_type *);

time_t datetime2time_t(datetime_struct_type *);

int time_t2datetime(time_t, datetime_struct_type *);

void print_time_t (time_t);

void print_datetime(datetime_struct_type *tm);

int diff_between_dates(time_t start, time_t end);

int to_date_str(datetime_struct_type *tm, char *buffer);
int to_time_str(datetime_struct_type *tm, char *buffer);

// returns 1 if year is a leap year, 0 otherwise
unsigned int leap_year(unsigned int year);

// returns the day of the year.  1-366 ( 365 for non leap years)
unsigned int doy(unsigned year, unsigned month, unsigned day);

int print_date (time_t);





#endif
