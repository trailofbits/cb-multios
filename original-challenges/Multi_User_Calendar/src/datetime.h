/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef DATETIME_H_
#define DATETIME_H_

#include "bool.h"

#define MAX_DATE 10
#define MAX_TIME 5

typedef struct {
    short year;
    char month;
    char day;
} date_t;

typedef struct {
    char hour;
    char minute;
} time_t;

typedef struct {
    date_t date;
    time_t time;
} datetime_t;

typedef struct {
    datetime_t start;
    datetime_t end;
} duration_t;

bool set_date(date_t *date, char month, char day, short year);
bool set_time(time_t *time, char hour, char minute);
bool set_datetime(datetime_t *dt, date_t date, time_t time);
bool set_duration(duration_t *d, datetime_t dt1, datetime_t dt2);
int compare_date(void *_date1, void *_date2);
int compare_time(void *_time1, void *_time2);
int compare_datetime(void *_dt1, void *_dt2);
bool durations_overlap(duration_t d1, duration_t d2);
bool date_within(duration_t d, date_t date);
bool datetime_within(duration_t d, datetime_t dt);
bool strtodate(char *datestr, date_t *date);
bool strtotime(char *timestr, time_t *time);
void print_date(date_t *date);
void print_time(time_t *time);
char *get_month(date_t *date);
void get_time_str(char *time_str, time_t *time);
void get_date_str(char *date_str, date_t *date);

#endif
