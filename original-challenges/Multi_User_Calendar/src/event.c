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
#include <stdio.h>
#include <string.h>
#include "event.h"
#include "read.h"
#include "datetime.h"

int g_event_id = 0;

event_t *create_event(struct user *owner, char *name, char *desc, duration_t *duration, bool is_all_day)
{
    if (!owner || !name || !strlen(name) || !desc || !strlen(desc) || !duration)
        return NULL;

    event_t *event = malloc(sizeof(event_t));
    event->id = g_event_id++;
    event->owner = owner;
    strcpy(event->name, name);
    strcpy(event->desc, desc);
    event->duration = *duration;
    event->is_all_day = is_all_day;

    return event;
}


bool delete_event(event_t **event)
{
    if (!*event)
        return false;
    free(*event);
    *event = NULL;
    return true;
}

int compare_events(void *_event1, void *_event2)
{
    event_t *event1 = (event_t *)_event1;
    event_t *event2 = (event_t *)_event2;

    if (!event1 || !event2)
        return -1;

    if (event1->id < event2->id)
        return -1;
    else if (event1->id == event2->id)
        return 0;
    else
        return 1;
}

int compare_event_dates(void *_event1, void *_event2)
{
    event_t *event1 = (event_t *)_event1;
    event_t *event2 = (event_t *)_event2;

    if (!event1 || !event2)
        return -1;

    return compare_date(&event1->duration.start.date, &event2->duration.start.date);
}

event_t *find_event_from_list(char *buf, size_t buflen, int *recv_status, event_list_t *list)
{
    if (!buf || buflen < 2)
        return NULL;

    char *event_id = NULL;;
    event_t temp_event;
    int tries = 0;

    event_id = q_and_a("Enter eventid: ", 10, buf, buflen, recv_status, true);
    if (!event_id)
        return NULL;

    if (*recv_status != SUCCESS) {
        free(event_id);
        return NULL;
    } else {
        temp_event.id = strtol(event_id, NULL, 10);
        free(event_id);
        return find((list_t *)list, &temp_event, &compare_events);
    }
}

void print_event(event_t *event)
{
    char date_str[16];
    char time_str[8];

    printf("Event ID: %d - %s\n", event->id, event->name);
    printf("About the event: %s\n", event->desc);
    if (event->is_all_day) {
        get_date_str(date_str, &event->duration.start.date);
        printf("Starts %s\n", date_str);
        get_date_str(date_str, &event->duration.end.date);
        printf("Ends %s\n", date_str);
    } else {
        get_date_str(date_str, &event->duration.start.date);
        get_time_str(time_str, &event->duration.start.time);
        printf("Starts %s @ %s\n", date_str, time_str);
        get_date_str(date_str, &event->duration.end.date);
        get_time_str(time_str, &event->duration.end.time);
        printf("Ends %s @ %s\n", date_str, time_str);
    }
}

