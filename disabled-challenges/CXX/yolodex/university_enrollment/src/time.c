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
#include "cgc_time.h"
#include "cgc_string.h"

time_t cgc_time(char hour, char minute)
{
    time_t t;
    t.hour = hour;
    t.minute = minute;
    return t;
}

int cgc_timecmp(time_t t1, time_t t2)
{
    if (t1.hour < t2.hour)
        return -1;
    if (t1.hour > t2.hour)
        return 1;
    if (t1.minute < t2.minute)
        return -1;
    if (t1.minute > t2.minute)
        return 1;

    return 0;
}

int cgc_days_intersect(days_t d1, days_t d2)
{
    if (d1 == H && d2 == H)
        return 0;

    return (d1 & d2);
}

void cgc_daystostr(days_t days, char *output)
{
    if (!output)
        return;

    cgc_memset(output, 0, 9);
    if(days & M)
        cgc_strcat(output, "M");
    if(days & T)
        cgc_strcat(output, "T");
    if(days & W)
        cgc_strcat(output, "W");
    if(days & R)
        cgc_strcat(output, "R");
    if(days & F)
        cgc_strcat(output, "F");
    if(days & S)
        cgc_strcat(output, "S");
    if(days & U)
        cgc_strcat(output, "U");
    if(days & H)
        cgc_strcat(output, "H");
}

