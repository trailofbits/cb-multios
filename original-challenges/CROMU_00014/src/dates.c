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

#include "dates.h"
#include "stdlib.h"


time_t datetime2time_t(datetime_struct_type *tm)  {

int i;
time_t result=0;

    // the epoch starts at 1/1/1970
    if (tm->year < 1970)
        return 0;

    // add up the number of days in the years since the epoch
    for (i=1970; i < tm->year; ++i)
        result+= 365 + leap_year(i);


    // now add the days from this year--correcting for the numbering starting at 1 not 0
    result+= tm->doy -1;


    // now convert to seconds
    result*= 86400;

    result+= tm->hour*3600;

    result+= tm->min*60;

    result+= tm->sec;

    return (result);

}


int time_t2datetime(time_t epoch, datetime_struct_type *tm)  {

unsigned int day_seconds;
unsigned int num_days_since_epoch;
unsigned int cum_days_since_epoch;
unsigned int day_of_year;
int i;

int cumulative_days_by_month[]= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

// first do the hour, mins, seconds because they are really easy
    day_seconds = epoch % 86400;

    tm->sec= day_seconds % 60;
    tm->min= day_seconds / 60 % 60;
    tm->hour= day_seconds / 3600;


// now work on the date part

    // how many days since the epoch date 1-Jan-1970
    num_days_since_epoch = epoch / 86400;
    cum_days_since_epoch=0;

    // count up the elapsed days by year until we exceed the target date
    for (i=1970; cum_days_since_epoch <= num_days_since_epoch; ++i)  {
        cum_days_since_epoch+= (365+ leap_year(i));

    }

    // one less is the year of this date
    tm->year = i-1;

    // now that we have the year, we can do leap_year calcs

    // find the number of days to 1 Jan of our year
    cum_days_since_epoch -= (365 + leap_year(tm->year));


    // now calculate the day of the year
    day_of_year = num_days_since_epoch - cum_days_since_epoch + 1;


    tm->doy = day_of_year;

    // based on the day of year, figure out the month
    for (i=0; (cumulative_days_by_month[i]+ ((i>1)*leap_year(tm->year))) < day_of_year; ++i)  {

      
    }

    // unlike the Unix standard, these months are 1-12, not 0-11
    tm->month= i;

    // now figure out the day of the month
    tm->day = day_of_year - cumulative_days_by_month[tm->month-1]  - ((tm->month > 2) * leap_year(tm->year));

    return 0;
}


time_t str2datetime(char *buff, datetime_struct_type *tm) {


unsigned mon, mday, year;
unsigned hours, mins, secs;

int cumulative_days[]= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

char *tmp;

//parse string in the from of "MM/DD/YYYY HH:MM:SS" into the structure elements

    while (isspace(*buff))
        ++buff;

    tmp=buff;
    
    mon=atoi(tmp);
    
    if (mon < 1 || mon > 12)
        return(-2);

    while (*tmp!='/' && *tmp!=0)
        ++tmp;
        
    ++tmp;
    
    mday=atoi(tmp);
    
    if (mday < 1)
        return (-2);

    if ((mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) && mday > 31)
        return (-2);
    
    if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && mday > 30)
        return (-2);
    
    while (*tmp!='/' && *tmp!=0)
        ++tmp;
        
    ++tmp;
    
    year=atoi(tmp);
    
    // constrain the year so that other calculations are valid
    if (year < 1970 || year > 2050)
        return (-2);

    // now that we have the year and if its a leap year, validate the Feb dates
    if (mon == 2 && mday > 28+ leap_year(year))
        return (-2);
    
    tm->year = year;
    tm->day = mday;
    tm->month = mon;

    while (!isspace(*tmp))
        ++tmp;

    while (isspace(*tmp))
        ++tmp;

    hours = atoi(tmp);


    while (*tmp!=':' && *tmp!=0)
        ++tmp;

    ++tmp;

    mins = atoi(tmp);


    while (*tmp!=':' && *tmp!=0)
    ++tmp;

    ++tmp;
    
    secs = atoi(tmp);

    tm->hour = hours;
    tm->min = mins;
    tm->sec = secs;

    tm->doy = doy(tm->year, tm->month, tm->day);

    return (datetime2time_t(tm));

}


void print_time_t (time_t date) {
    
    datetime_struct_type tm;

    time_t2datetime(date, &tm);

    printf("@d/@d/@d @02d:@02d:@02d", tm.month, tm.day, tm.year,
                tm.hour, tm.min, tm.sec);
    
}

void print_datetime(datetime_struct_type *tm)  {

    printf("@d/@d/@d @02d:@02d:@02d", tm->month, tm->day, tm->year,
                tm->hour, tm->min, tm->sec);

}

int to_date_str(datetime_struct_type *tm, char *buffer) {

    sprintf(buffer, "@d/@d/@d", tm->month, tm->day, tm->year);
    return 0;

}

int to_time_str(datetime_struct_type *tm, char *buffer) {

    sprintf(buffer, "@02d:@02d:@02d", tm->hour, tm->min, tm->sec);
    return 0;
    
}


int diff_between_dates(time_t start, time_t end) {

// unimplemented right now
return 0;

}

// classic leap year calculation
unsigned int leap_year(unsigned int year) {
    
    if ((year%400==0 || year%100!=0) && (year%4==0))
        return 1;
    else
        return 0;

}

// for accounting reasons it might be handy to have the day of the year number
unsigned int doy(unsigned year, unsigned month, unsigned day) {

unsigned int doy;
int cumulative_days[]= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

    doy=cumulative_days[month-1] + day;
    
    if (month > 2)
        doy+=leap_year(year);
        
    return (doy);

}



