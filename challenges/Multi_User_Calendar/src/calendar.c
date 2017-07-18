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
#include "cgc_calendar.h"

#define MAX_AGENDA_EVENTS 8
#define AGENDA_LOOKAHEAD 3

void cgc_view_day(calendar_t * cal, date_t date)
{
    char date_str[16];
    cgc_get_date_str(date_str, &date);

    event_list_t *iter = cal->events;
    int datecmp = 0;
    cgc_printf("Viewing Calendar Appointments for %s\n", date_str);
    while(iter) {
        datecmp = cgc_compare_date(&iter->event->duration.start.date, &date);
        if (datecmp > 0)
            break;

        if (cgc_date_within(iter->event->duration, date)) {
            cgc_printf("------------------------\n");
            cgc_print_event(iter->event);
        }
        iter = iter->next;
    }
    cgc_printf("------------------------\n");
}

void cgc_view_month(calendar_t * cal, date_t date)
{
    char date_str[16];
    cgc_get_date_str(date_str, &date);

    event_list_t *iter = cal->events;
    int datecmp = 0;
    char *month = cgc_get_month(&date);
    cgc_printf("Viewing Monthly Calendar for %s %d\n", month, date.year);
    while(iter) {
        if (iter->event->duration.start.date.month >= date.month &&
            iter->event->duration.end.date.month <= date.month) {
            cgc_printf("------------------------\n");
            cgc_print_event(iter->event);
        }
        iter = iter->next;
    }
    cgc_printf("------------------------\n");
}

date_t cgc_calc_agenda_lookahead(date_t date)
{
    date_t lookahead = date;
    lookahead.year += AGENDA_LOOKAHEAD / 12;
    if (AGENDA_LOOKAHEAD % 12 == 0)
        return lookahead;

    lookahead.month = (date.month + AGENDA_LOOKAHEAD);
    if (lookahead.month > 12) {
        lookahead.year++;
        lookahead.month %= 12;
    }

    return lookahead;
}

void cgc_view_agenda(calendar_t *cal, date_t date)
{
    int i = 0, printed_events = 0;
    char date_str[16];
    cgc_get_date_str(date_str, &date);
    date_t lookahead = cgc_calc_agenda_lookahead(date);

    event_list_t *iter = cal->events;
    int datecmp = 0;
    char *month = cgc_get_month(&date);
    cgc_printf("Agenda View\n");
    while(i++ < cal->num_events && printed_events < MAX_AGENDA_EVENTS) {
        datecmp = cgc_compare_date(&iter->event->duration.start.date, &date);
        if (datecmp < 0) {
            iter = iter->next;
            continue;
        }

        if (cgc_compare_date(&iter->event->duration.start.date, &lookahead) <= 0) {
            cgc_printf("------------------------\n");
            cgc_print_event(iter->event);
            printed_events++;
        } else {
            break;
        }
        iter = iter->next;
    }
    cgc_printf("------------------------\n");
}

bool cgc_add_calendar_event(calendar_t *cal, event_t *event)
{
    if (cgc_insert_in_order((list_t **)&cal->events, event, &cgc_compare_event_dates)) {
        cal->num_events++;
        return true;
    }

    return false;
}

bool cgc_remove_calendar_event(calendar_t *cal, event_t *event)
{
    event = cgc_pop((list_t **)&cal->events, event, &cgc_compare_events);
    if (cgc_delete_event(&event)) {
        cal->num_events--;
        return true;
    }

    return false;
}
