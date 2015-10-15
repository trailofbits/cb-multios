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

#ifndef SERVICE_H
#define SERVICE_H

#include "dates.h"

typedef unsigned long datetime_type;

typedef struct {

    char last_name[21];
    char first_name[21];
    char phone[16];
    char street[30];
    char city[20];
    char state[3];
    char zip[11];
    char padi_number[20];
    char cert_date[11];

} diver_info_type;

typedef struct dive_data {

    datetime_type timestamp;
    unsigned int depth;
    struct dive_data *next;

} dive_data_type;

typedef struct dive_log {

    char dive_site_name[26];
    char dive_date[11];
    char dive_time[9];
    time_t timestamp;
    unsigned int max_depth;  // in feet
    unsigned int avg_depth;  // in feet
    unsigned int dive_length;  // in minutes
    unsigned int pressure_in; // psi
    unsigned int pressure_out; // psi
    unsigned int O2_percent; // integer percentage of O2
    char water_type[6];  // fresh or salt
    unsigned int water_temp; // Celsius
    unsigned int bincount;
    char location[26];
    dive_data_type *data;  // linked list of time/depth
    struct dive_log *next;


} dive_log_type;

typedef struct {

    diver_info_type diver;
    dive_log_type *dives;

} logbook_type;


int edit_diver(logbook_type *);
int log_dives(logbook_type *);
int print_dives(logbook_type *);
int list_dives(logbook_type *);
int download_dive(logbook_type *);
int dive_statistics(logbook_type *);
int exit_app(int retcode);
int print_diver_info(logbook_type *Info);
int edit_dives(logbook_type *Info);
int remove_dives(logbook_type *Info);
int update_dive(dive_log_type *);


#endif
