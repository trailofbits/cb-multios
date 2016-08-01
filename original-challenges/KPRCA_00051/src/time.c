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
#include "time.h"
#include <string.h>

time_t time(char hour, char minute)
{
    time_t t;
    t.hour = hour;
    t.minute = minute;
    return t;
}

int timecmp(time_t t1, time_t t2)
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

int days_intersect(days_t d1, days_t d2)
{
    if (d1 == H && d2 == H)
        return 0;

    return (d1 & d2);
}

void daystostr(days_t days, char *output)
{
    if (!output)
        return;

    memset(output, 0, 9);
    if(days & M)
        strcat(output, "M");
    if(days & T)
        strcat(output, "T");
    if(days & W)
        strcat(output, "W");
    if(days & R)
        strcat(output, "R");
    if(days & F)
        strcat(output, "F");
    if(days & S)
        strcat(output, "S");
    if(days & U)
        strcat(output, "U");
    if(days & H)
        strcat(output, "H");
}

