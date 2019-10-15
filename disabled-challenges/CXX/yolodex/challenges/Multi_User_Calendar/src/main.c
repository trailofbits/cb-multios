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
#include "cgc_string.h"
#include "cgc_stdio.h"

#include "cgc_read.h"
#include "cgc_user.h"
#include "cgc_calendar.h"

#define LINE_SIZE 2048
char line[LINE_SIZE];

int cgc_g_num_users = 0;
user_list_t *cgc_g_all_users = NULL;
user_t *cgc_g_cur_user = NULL;
date_t g_cur_date = { 2016, 8, 4 };
date_t g_view_date = { 2016, 8, 4 };

bool cgc_add_user()
{
    int recv_status = FAIL;
    int num_tries = 0;
    char *username = NULL;
    char *about = NULL;
    user_t *found_user = NULL;

    while(recv_status != SUCCESS) {
        found_user = cgc_find_user_from_list(line, LINE_SIZE, &recv_status, cgc_g_all_users, cgc_g_num_users);

        switch (recv_status) {
        case ERROR:
            goto cleanup;
        case SUCCESS:
            if (found_user || !cgc_strlen(line) || cgc_strlen(line) > MAX_USERNAME) {
                recv_status = FAIL;
            } else {
                username = cgc_strdup(line);
                break;
            }
        case FAIL:
        default:
            cgc_printf("Try again\n");
        }
        if (++num_tries == MAX_TRIES)
            goto cleanup;
    }

    about = cgc_q_and_a("Enter a short \"about me\" section.: ", MAX_ABOUT, line, LINE_SIZE, &recv_status, false);
    if (recv_status != SUCCESS)
        goto cleanup;

    user_t* user = cgc_create_user(username, about);
    if (!cgc_insert_in_order((list_t **)&cgc_g_all_users, user, &cgc_compare_users)) {
        if (user)
            cgc_delete_user(&user);
        cgc_printf("Cannot add user at this time\n");
    } else {
        cgc_printf("Successfully added user\n");
        cgc_g_num_users++;
    }
cleanup:
    if (username)
        cgc_free(username);
    if (about)
        cgc_free(about);
    return (recv_status != ERROR);
}

bool cgc_remove_user()
{
    int recv_status = FAIL;
    user_t *user = cgc_find_user_from_list(line, LINE_SIZE, &recv_status, cgc_g_all_users, cgc_g_num_users);
    if (recv_status == ERROR)
        return false;

    if (!user) {
        cgc_printf("User not found\n");
        return true;
    }

    user = cgc_pop((list_t **)&cgc_g_all_users, user, &cgc_compare_users);
    if (cgc_compare_users(user, cgc_g_cur_user) == 0)
        cgc_g_cur_user = NULL;
    if(cgc_delete_user(&user)) {
        cgc_printf("Suceessfully deleted user\n");
        cgc_g_num_users--;
    }

    return true;
}

bool cgc_set_current_user()
{
    int recv_status = FAIL;
    user_t *user = NULL;
    cgc_print_user_list("------All Users------\n", cgc_g_all_users);
    cgc_printf("Entering a username will set it as the current user\n");
    user = cgc_find_user_from_list(line, LINE_SIZE, &recv_status, cgc_g_all_users, cgc_g_num_users);
    if (recv_status == ERROR)
        return false;

    if (!user) {
        cgc_printf("User not set\n");
    } else {
        cgc_g_cur_user = user;
    }

    return true;
}

bool cgc_change_cur_date()
{
    int recv_status = FAIL;
    char *new_date_str = NULL;
    new_date_str = cgc_q_and_a("Enter new date (MM-DD-YYYY): ", MAX_DATE, line, LINE_SIZE, &recv_status, true);
    if (recv_status == ERROR)
        return false;
    if (new_date_str) {
        if (cgc_strtodate(new_date_str, &g_cur_date)) {
            cgc_printf("Date successfully changed\n");
            g_view_date = g_cur_date;
        } else {
            cgc_printf("Date not changed\n");
        }
        cgc_free(new_date_str);
    } else {
        cgc_printf("Try again\n");
    }

    return true;
}

bool cgc_change_view_date()
{
    int recv_status = FAIL;
    char *new_date_str = NULL;
    new_date_str = cgc_q_and_a("Enter date to view (MM-DD-YYYY): ", MAX_DATE, line, LINE_SIZE, &recv_status, true);
    if (recv_status == ERROR)
        return false;
    if (new_date_str) {
        if (cgc_strtodate(new_date_str, &g_view_date))
            cgc_printf("Successfully changed calendar view date\n");
        else
            cgc_printf("Date not changed\n");
        cgc_free(new_date_str);
    } else {
        cgc_printf("Try again\n");
    }

    return true;
}

bool cgc_add_user_event(user_t *user)
{
    if (user == NULL) {
        cgc_printf("Must set a user first\n");
        return true;
    }

    event_t *event;
    int recv_status = FAIL;
    char *event_name = NULL;
    char *event_desc = NULL;
    char *start_date_str;
    char *date_str = NULL;
    date_t start_date;
    date_t end_date;
    char *is_all_day_str = NULL;
    bool is_all_day = false;
    char *time_str = NULL;
    time_t start_time;
    time_t end_time;
    duration_t event_duration;

    while (!event_name) {
        event_name = cgc_q_and_a("Event Name: ", MAX_EVENT_NAME, line, LINE_SIZE, &recv_status, false);
        if (recv_status == ERROR)
            return false;
    }
    while (!event_desc) {
        event_desc = cgc_q_and_a("Event Description: ", MAX_EVENT_DESC, line, LINE_SIZE, &recv_status, false);
        if (recv_status == ERROR)
            return false;
    }

    while (!date_str) {
        date_str = cgc_q_and_a("Start Date (MM-DD-YYYY): ", MAX_DATE, line, LINE_SIZE, &recv_status, false);
        if (recv_status == ERROR)
            return false;

        start_date_str = cgc_strdup(date_str);
        if (!cgc_strtodate(date_str, &start_date)) {
            if(date_str) {
                cgc_free(start_date_str);
                start_date_str = NULL;
                cgc_free(date_str);
                date_str = NULL;
            }
            cgc_printf("Try again\n");
        }
    }
    cgc_free(date_str);
    date_str = NULL;

    while (!date_str) {
        char question[32];
        cgc_sprintf(question, "End Date (MM-DD-YYYY) [%s]: ", start_date_str);
        date_str = cgc_q_and_a(question, MAX_DATE, line, LINE_SIZE, &recv_status, true);
        if (recv_status == ERROR)
            return false;

        if (date_str && !cgc_strlen(date_str)) {
            end_date = start_date;
        }
        else if (!cgc_strtodate(date_str, &end_date) || cgc_compare_date(&end_date, &start_date) < 0 ) {
            if(date_str) {
                cgc_free(date_str);
                date_str = NULL;
            }
            cgc_printf("Try again\n");
        }
    }
    cgc_free(start_date_str);
    start_date_str = NULL;
    cgc_free(date_str);
    date_str = NULL;

    while (!is_all_day_str) {
        is_all_day_str = cgc_q_and_a("All day event? (y/n) [n]: ", LINE_SIZE, line, LINE_SIZE, &recv_status, true);
        if (recv_status == ERROR)
            return false;

        if (is_all_day_str && !cgc_strlen(is_all_day_str)) {
            is_all_day = false;
        }
        else if (is_all_day_str) {
            if (recv_status != SUCCESS) {
                cgc_free(is_all_day_str);
                is_all_day_str = NULL;
                continue;
            }
            if (is_all_day_str[0] == 'y' || is_all_day_str[0] == 'Y')
                is_all_day = true;
        }
    }
    cgc_free(is_all_day_str);
    is_all_day_str = NULL;

    if (!is_all_day) {
        while (!time_str) {
            time_str = cgc_q_and_a("Start Time (HH:MM): ", MAX_TIME, line, LINE_SIZE, &recv_status, false);
            if (recv_status == ERROR)
                return false;

            if (!cgc_strtotime(time_str, &start_time)) {
                if(time_str) {
                    cgc_free(time_str);
                    time_str = NULL;
                }
                cgc_printf("Try again\n");
            }
        }
        cgc_free(time_str);
        time_str = NULL;

        while (!time_str) {
            char question[32];
            cgc_sprintf(question, "End time (HH:MM): ", time_str);
            time_str = cgc_q_and_a(question, MAX_TIME, line, LINE_SIZE, &recv_status, false);
            if (recv_status == ERROR)
                return false;

            if (!cgc_strtotime(time_str, &end_time) || (cgc_compare_date(&start_date, &end_date) == 0 &&
                                                        cgc_compare_time(&end_time, &start_time) <= 0 )) {
                if(time_str) {
                    cgc_free(time_str);
                    time_str = NULL;
                }
                cgc_printf("Try again\n");
            }
        }
        cgc_free(time_str);
        time_str = NULL;
    } else {
        cgc_set_time(&start_time, 0, 0);
        cgc_set_time(&end_time, 23, 59);
    }

    event_duration.start.date = start_date;
    event_duration.start.time = start_time;
    event_duration.end.date = end_date;
    event_duration.end.time = end_time;

    event = cgc_create_event(user, event_name, event_desc, &event_duration, is_all_day);
    if(!cgc_add_calendar_event(&user->calendar, event)) {
        if (event) {
            cgc_free(event);
            event = NULL;
        }
        cgc_printf("Could not add event\n");
    }
    else {
        cgc_print_event(event);
    }

    return true;
}

bool cgc_remove_user_event(user_t *user)
{
    int recv_status = FAIL;
    event_t *event = cgc_find_event_from_list(line, LINE_SIZE, &recv_status, cgc_g_cur_user->calendar.events);
    if (recv_status == ERROR)
        return false;

    if (!event) {
        cgc_printf("Event not found\n");
        return true;
    }

    if (!cgc_remove_calendar_event(&user->calendar, event))
        cgc_printf("Could not remove event\n");
    else
        cgc_printf("Successfully removed event\n");
    return true;
}

bool cgc_user_menu(bool *edit_calendar)
{
    int choice = 0;
    char *cur_user;
    if (!cgc_g_cur_user || !cgc_strlen(cgc_g_cur_user->username))
        cur_user = "None";
    else
        cur_user = cgc_g_cur_user->username;

    cgc_printf("Options:\n");
    cgc_printf("1. View users\n");
    cgc_printf("2. Add user\n");
    cgc_printf("3. Remove user\n");
    cgc_printf("4. Set user\n");
    cgc_printf("5. View Calendar\n");
    cgc_printf("6. Change Date\n");
    cgc_printf("7. Exit\n");
    cgc_printf("---Current User is *%s*---\n", cur_user);
    cgc_printf("---Today's date is ");
    cgc_print_date(&g_cur_date);
    cgc_printf("---\n");

    cgc_printf("Selection: ");
    if (cgc_readnum(line, LINE_SIZE, &choice) == ERROR)
        return false;

    switch(choice) {
    case 1:
        cgc_print_user_list("------All Users------\n", cgc_g_all_users);
        return true;
    case 2:
        return cgc_add_user();
    case 3:
        return cgc_remove_user();
    case 4:
        return cgc_set_current_user();
    case 5:
        *edit_calendar = true;
        return true;
    case 6:
        return cgc_change_cur_date();
    case 7:
        return false;
    default:
        cgc_printf("Try again\n");
        return true;
    }
}

bool cgc_calendar_menu(bool *edit_calendar)
{
    int choice = 0;
    char *cur_user;
    date_t old_date;
    bool is_running;

    if (!cgc_g_cur_user || !cgc_strlen(cgc_g_cur_user->username)) {
        cgc_printf("Must select a user before viewing a calendar\n");
        *edit_calendar = false;
        return true;
    } else {
        cur_user = cgc_g_cur_user->username;
    }

    cgc_printf("Options:\n");
    cgc_printf("1. View Day\n");
    cgc_printf("2. View Month\n");
    cgc_printf("3. View Agenda\n");
    cgc_printf("4. Change Date\n");
    cgc_printf("5. Change View Date\n");
    cgc_printf("6. Add Calendar Event\n");
    cgc_printf("7. Remove Calendar Event\n");
    cgc_printf("8. Return to User Selection\n");
    cgc_printf("---Current User is *%s*---\n", cur_user);
    cgc_printf("---Today's date is ");
    cgc_print_date(&g_cur_date);
    cgc_printf("---\n");
    cgc_printf("---Calendar view date is ");
    cgc_print_date(&g_view_date);
    cgc_printf("---\n");

    cgc_printf("Selection: ");
    if (cgc_readnum(line, LINE_SIZE, &choice) == ERROR)
        return false;

    switch(choice) {
    case 1:
        cgc_view_day(&cgc_g_cur_user->calendar, g_view_date);
        return true;
    case 2:
        cgc_view_month(&cgc_g_cur_user->calendar, g_view_date);
        return true;
    case 3:
        cgc_view_agenda(&cgc_g_cur_user->calendar, g_view_date);
        return true;
    case 4:
        return cgc_change_cur_date();
    case 5:
        return cgc_change_view_date();
    case 6:
        return cgc_add_user_event(cgc_g_cur_user);
    case 7:
        return cgc_remove_user_event(cgc_g_cur_user);
    case 8:
        *edit_calendar = false;
        return true;
    default:
        cgc_printf("Try again\n");
        return true;
    }
}

void cgc_check_seed()
{
    unsigned int x = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    if (x == *(unsigned int*)0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
}

int main(int cgc_argc, char *cgc_argv[])
{

    int i  = 0;
    int choice = 1;
    bool edit_calendar = false;
    bool running = true;

    cgc_check_seed();

    while (running) {
        if (edit_calendar)
            running = cgc_calendar_menu(&edit_calendar);
        else
            running = cgc_user_menu(&edit_calendar);
    }

    return 0;
}

