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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_event.h"
#include "cgc_read.h"
#include "cgc_datetime.h"

int cgc_g_event_id = 0;

event_t *cgc_create_event(struct user *owner, char *name, char *desc, duration_t *duration, bool is_all_day)
{
    if (!owner || !name || !cgc_strlen(name) || !desc || !cgc_strlen(desc) || !duration)
        return NULL;

    event_t *event = cgc_malloc(sizeof(event_t));
    event->id = cgc_g_event_id++;
    event->owner = owner;
    cgc_strcpy(event->name, name);
    cgc_strcpy(event->desc, desc);
    event->duration = *duration;
    event->is_all_day = is_all_day;

    return event;
}


bool cgc_delete_event(event_t **event)
{
    if (!*event)
        return false;
    cgc_free(*event);
    *event = NULL;
    return true;
}

int cgc_compare_events(void *_event1, void *_event2)
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

int cgc_compare_event_dates(void *_event1, void *_event2)
{
    event_t *event1 = (event_t *)_event1;
    event_t *event2 = (event_t *)_event2;

    if (!event1 || !event2)
        return -1;

    return cgc_compare_date(&event1->duration.start.date, &event2->duration.start.date);
}

event_t *cgc_find_event_from_list(char *buf, cgc_size_t buflen, int *recv_status, event_list_t *list)
{
    if (!buf || buflen < 2)
        return NULL;

    char *event_id = NULL;;
    event_t temp_event;
    int tries = 0;

    event_id = cgc_q_and_a("Enter eventid: ", 10, buf, buflen, recv_status, true);
    if (!event_id)
        return NULL;

    if (*recv_status != SUCCESS) {
        cgc_free(event_id);
        return NULL;
    } else {
        temp_event.id = cgc_strtol(event_id, NULL, 10);
        cgc_free(event_id);
        return cgc_find((list_t *)list, &temp_event, &cgc_compare_events);
    }
}

void cgc_print_event(event_t *event)
{
    char date_str[16];
    char time_str[8];

    cgc_printf("Event ID: %d - %s\n", event->id, event->name);
    cgc_printf("About the event: %s\n", event->desc);
    if (event->is_all_day) {
        cgc_get_date_str(date_str, &event->duration.start.date);
        cgc_printf("Starts %s\n", date_str);
        cgc_get_date_str(date_str, &event->duration.end.date);
        cgc_printf("Ends %s\n", date_str);
    } else {
        cgc_get_date_str(date_str, &event->duration.start.date);
        cgc_get_time_str(time_str, &event->duration.start.time);
        cgc_printf("Starts %s @ %s\n", date_str, time_str);
        cgc_get_date_str(date_str, &event->duration.end.date);
        cgc_get_time_str(time_str, &event->duration.end.time);
        cgc_printf("Ends %s @ %s\n", date_str, time_str);
    }
}

