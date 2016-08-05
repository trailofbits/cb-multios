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
#include <string.h>
#include <stdio.h>
#include "datetime.h"

#define JAN "January"
#define FEB "Februrary"
#define MAR "March"
#define APR "April"
#define MAY "May"
#define JUN "June"
#define JUL "July"
#define AUG "August"
#define SEP "Septempber"
#define OCT "October"
#define NOV "November"
#define DEC "December"
#define BAD_MONTH "Undefined Month"

bool is_valid_date(date_t *date)
{
    if (!date || date->year < 2015 || date->year > 2025 || date->month < 1 || date->month > 12 || date->day < 1)
        return false;

    switch (date->month)  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (date->day > 31)
            return false;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (date->day > 30)
            return false;
        break;
    case 2:
        if (date->year % 400 != 0 && date->year % 4 == 0) {
            if (date->day > 29)
                return false;
            else if (date->day > 28)
                return false;
        }
        break;
    default:
        return false;
    }
    return true;
}

bool is_valid_time(time_t *time)
{
    return (time && time->hour >= 0 && time->hour <= 23 && time->minute >= 0 && time->minute <= 59);
}

bool set_date(date_t *date, char month, char day, short year)
{
    if (!date)
        return false;

    date_t temp;
    temp.year = year;
    temp.month = month;
    temp.day = day;
    if(!is_valid_date(&temp))
        return false;

    *date = temp;
    return true;
}

bool set_time(time_t *time, char hour, char minute)
{
    if (!time || hour < 0 || hour > 23 || minute < 0 || minute > 59)
        return false;

    time->hour = hour;
    time->minute = minute;
    return true;
}

bool set_datetime(datetime_t *dt, date_t date, time_t time)
{
    if (!dt || !is_valid_date(&date) || !is_valid_time(&time))
        return false;

    dt->date = date;
    dt->time = time;
    return true;
}

bool set_duration(duration_t *d, datetime_t dt1, datetime_t dt2)
{
    if (!d)
        return false;

    if (compare_date(&dt1, &dt2) >= 0)
        return false;

    if (!set_datetime(&d->start, dt1.date, dt1.time))
        return false;
    if (!set_datetime(&d->end, dt2.date, dt2.time))
        return false;

    return true;
}

int compare_date(void *_date1, void *_date2)
{
    date_t *date1 = (date_t *)_date1;
    date_t *date2 = (date_t *)_date2;

    if (!date1 || !date2)
        return -1;

    if (date1->year < date2->year)
        return -1;
    if (date1->year > date2->year)
        return 1;
    if (date1->month < date2->month)
        return -1;
    if (date1->month > date2->month)
        return 1;
    if (date1->day < date2->day)
        return -1;
    if (date1->day > date2->day)
        return 1;

    return 0;
}

int compare_time(void *_time1, void *_time2)
{
    time_t *time1 = (time_t *)_time1;
    time_t *time2 = (time_t *)_time2;

    if (!time1 || !time2)
        return -1;

    if (time1->hour < time2->hour)
        return -1;
    if (time1->hour > time2->hour)
        return 1;
    if (time1->minute < time2->minute)
        return -1;
    if (time1->minute > time2->minute)
        return 1;

    return 0;
}

int compare_datetime(void *_dt1, void *_dt2)
{
    int comp_val = 0;
    datetime_t *dt1 = (datetime_t *)_dt1;
    datetime_t *dt2 = (datetime_t *)_dt2;

    comp_val = compare_date(&dt1->date, &dt2->date);
    if (comp_val != 0)
        return comp_val;

    return compare_time(&dt1->time, &dt2->time);
}

bool durations_overlap(duration_t d1, duration_t d2)
{
    int comp1, comp2;
    comp1 = compare_datetime(&d1.start, &d2.end);
    comp2 = compare_datetime(&d1.end, &d2.start);
    if (comp1 == -1 && comp2 == 1)
        return true;

    comp1 = compare_datetime(&d2.start, &d1.end);
    comp2 = compare_datetime(&d2.end, &d1.start);
    if (comp1 == -1 && comp2 == 1)
        return true;

    return false;
}

bool date_within(duration_t d, date_t date)
{
    int comp1, comp2;
    comp1 = compare_date(&d.start.date, &date);
    comp2 = compare_date(&d.end.date, &date);
    if (comp1 <= 0 && comp2 >= 0)
        return true;

    return false;
}

bool datetime_within(duration_t d, datetime_t dt)
{
    int comp1, comp2;
    comp1 = compare_datetime(&d.start, &dt);
    comp2 = compare_datetime(&d.end, &dt);
    if (comp1 == -1 && comp2 == 1)
        return true;

    return false;
}

bool strtodate(char *datestr, date_t *date)
{
    if (!datestr || !date || strlen(datestr) < 8)
        return false;

    date_t temp;
    memset(&temp, 0, sizeof(date_t));
    char *year, *month, *day;
    if ((month = strsep(&datestr, "-")) == NULL)
        return false;
    if ((day = strsep(&datestr, "-")) == NULL)
        return false;
    if ((year = strsep(&datestr, "-")) == NULL)
        return false;

    temp.year = strtol(year, NULL, 10);
    temp.month = strtol(month, NULL, 10);
    temp.day = strtol(day, NULL, 10);

    if (is_valid_date(&temp)) {
        *date = temp;
        return true;
    } else {
        return false;
    }
}

bool strtotime(char *timestr, time_t *time)
{
    if (!timestr || !time || strlen(timestr) < 4)
        return false;

    time_t temp;
    char *hour, *minute;
    if ((hour = strsep(&timestr, ":")) == NULL)
        return false;
    if ((minute = strsep(&timestr, "-")) == NULL)
        return false;

    temp.hour = strtol(hour, NULL, 10);
    temp.minute = strtol(minute, NULL, 10);

    if (temp.hour == 0) {
        int i;
        for (i = 0; i < strlen(hour); i++) {
            if (hour[i] != '0')
                return false;
        }
    }

    if (temp.minute == 0) {
        int i;
        for (i = 0; i < strlen(minute); i++) {
            if (minute[i] != '0')
                return false;
        }
    }

    if (is_valid_time(&temp)) {
        *time = temp;
        return true;
    } else {
        return false;
    }
}

void print_date(date_t *date)
{
    printf("%d-%d-%d", date->month, date->day, date->year);
}

void get_date_str(char *date_str, date_t *date)
{
    sprintf(date_str, "%d-%d-%d", date->month, date->day, date->year);
}

char *get_month(date_t *date)
{
    if (!date)
        return BAD_MONTH;

    switch(date->month) {
    case 1:
        return JAN;
    case 2:
        return FEB;
    case 3:
        return MAR;
    case 4:
        return APR;
    case 5:
        return MAY;
    case 6:
        return JUN;
    case 7:
        return JUL;
    case 8:
        return AUG;
    case 9:
        return SEP;
    case 10:
        return OCT;
    case 11:
        return NOV;
    case 12:
        return DEC;
    default:
        return BAD_MONTH;
    }
}

void print_time(time_t *time)
{
    char *zero = "0";
    char *emptystr = "";
    char *min_pad;
    if(time->minute < 10)
        min_pad = zero;
    else
        min_pad = emptystr;

    printf("%d:%s%d", time->hour, min_pad, time->minute);
}

void get_time_str(char *time_str, time_t *time)
{
    char *zero = "0";
    char *emptystr = "";
    char *min_pad;
    if(time->minute < 10)
        min_pad = zero;
    else
        min_pad = emptystr;

    sprintf(time_str, "%d:%s%d", time->hour, min_pad, time->minute);
}

