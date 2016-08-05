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

#include "read.h"
#include "user.h"
#include "calendar.h"

#define LINE_SIZE 2048
char line[LINE_SIZE];

int g_num_users = 0;
user_list_t *g_all_users = NULL;
user_t *g_cur_user = NULL;
date_t g_cur_date = { 2016, 8, 4 };
date_t g_view_date = { 2016, 8, 4 };

bool add_user()
{
    int recv_status = FAIL;
    int num_tries = 0;
    char *username = NULL;
    char *about = NULL;
    user_t *found_user = NULL;

    while(recv_status != SUCCESS) {
        found_user = find_user_from_list(line, LINE_SIZE, &recv_status, g_all_users, g_num_users);

        switch (recv_status) {
        case ERROR:
            goto cleanup;
        case SUCCESS:
            if (found_user || !strlen(line) || strlen(line) > MAX_USERNAME) {
                recv_status = FAIL;
            } else {
                username = strdup(line);
                break;
            }
        case FAIL:
        default:
            printf("Try again\n");
        }
        if (++num_tries == MAX_TRIES)
            goto cleanup;
    }

    about = q_and_a("Enter a short \"about me\" section.: ", MAX_ABOUT, line, LINE_SIZE, &recv_status, false);
    if (recv_status != SUCCESS)
        goto cleanup;

    user_t* user = create_user(username, about);
    if (!insert_in_order((list_t **)&g_all_users, user, &compare_users)) {
        if (user)
            delete_user(&user);
        printf("Cannot add user at this time\n");
    } else {
        printf("Successfully added user\n");
        g_num_users++;
    }
cleanup:
    if (username)
        free(username);
    if (about)
        free(about);
    return (recv_status != ERROR);
}

bool remove_user()
{
    int recv_status = FAIL;
    user_t *user = find_user_from_list(line, LINE_SIZE, &recv_status, g_all_users, g_num_users);
    if (recv_status == ERROR)
        return false;

    if (!user) {
        printf("User not found\n");
        return true;
    }

    user = pop((list_t **)&g_all_users, user, &compare_users);
    if (compare_users(user, g_cur_user) == 0)
        g_cur_user = NULL;
    if(delete_user(&user)) {
        printf("Suceessfully deleted user\n");
        g_num_users--;
    }

    return true;
}

bool set_current_user()
{
    int recv_status = FAIL;
    user_t *user = NULL;
    print_user_list("------All Users------\n", g_all_users);
    printf("Entering a username will set it as the current user\n");
    user = find_user_from_list(line, LINE_SIZE, &recv_status, g_all_users, g_num_users);
    if (recv_status == ERROR)
        return false;

    if (!user) {
        printf("User not set\n");
    } else {
        g_cur_user = user;
    }

    return true;
}

bool change_cur_date()
{
    int recv_status = FAIL;
    char *new_date_str = NULL;
    new_date_str = q_and_a("Enter new date (MM-DD-YYYY): ", MAX_DATE, line, LINE_SIZE, &recv_status, true);
    if (recv_status == ERROR)
        return false;
    if (new_date_str) {
        if (strtodate(new_date_str, &g_cur_date)) {
            printf("Date successfully changed\n");
            g_view_date = g_cur_date;
        } else {
            printf("Date not changed\n");
        }
        free(new_date_str);
    } else {
        printf("Try again\n");
    }

    return true;
}

bool change_view_date()
{
    int recv_status = FAIL;
    char *new_date_str = NULL;
    new_date_str = q_and_a("Enter date to view (MM-DD-YYYY): ", MAX_DATE, line, LINE_SIZE, &recv_status, true);
    if (recv_status == ERROR)
        return false;
    if (new_date_str) {
        if (strtodate(new_date_str, &g_view_date))
            printf("Successfully changed calendar view date\n");
        else
            printf("Date not changed\n");
        free(new_date_str);
    } else {
        printf("Try again\n");
    }

    return true;
}

bool add_user_event(user_t *user)
{
    if (user == NULL) {
        printf("Must set a user first\n");
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
        event_name = q_and_a("Event Name: ", MAX_EVENT_NAME, line, LINE_SIZE, &recv_status, false);
        if (recv_status == ERROR)
            return false;
    }
    while (!event_desc) {
        event_desc = q_and_a("Event Description: ", MAX_EVENT_DESC, line, LINE_SIZE, &recv_status, false);
        if (recv_status == ERROR)
            return false;
    }

    while (!date_str) {
        date_str = q_and_a("Start Date (MM-DD-YYYY): ", MAX_DATE, line, LINE_SIZE, &recv_status, false);
        if (recv_status == ERROR)
            return false;

        start_date_str = strdup(date_str);
        if (!strtodate(date_str, &start_date)) {
            if(date_str) {
                free(start_date_str);
                start_date_str = NULL;
                free(date_str);
                date_str = NULL;
            }
            printf("Try again\n");
        }
    }
    free(date_str);
    date_str = NULL;

    while (!date_str) {
        char question[32];
        sprintf(question, "End Date (MM-DD-YYYY) [%s]: ", start_date_str);
        date_str = q_and_a(question, MAX_DATE, line, LINE_SIZE, &recv_status, true);
        if (recv_status == ERROR)
            return false;

        if (date_str && !strlen(date_str)) {
            end_date = start_date;
        }
        else if (!strtodate(date_str, &end_date) || compare_date(&end_date, &start_date) < 0 ) {
            if(date_str) {
                free(date_str);
                date_str = NULL;
            }
            printf("Try again\n");
        }
    }
    free(start_date_str);
    start_date_str = NULL;
    free(date_str);
    date_str = NULL;

    while (!is_all_day_str) {
        is_all_day_str = q_and_a("All day event? (y/n) [n]: ", LINE_SIZE, line, LINE_SIZE, &recv_status, true);
        if (recv_status == ERROR)
            return false;

        if (is_all_day_str && !strlen(is_all_day_str)) {
            is_all_day = false;
        }
        else if (is_all_day_str) {
            if (recv_status != SUCCESS) {
                free(is_all_day_str);
                is_all_day_str = NULL;
                continue;
            }
            if (is_all_day_str[0] == 'y' || is_all_day_str[0] == 'Y')
                is_all_day = true;
        }
    }
    free(is_all_day_str);
    is_all_day_str = NULL;

    if (!is_all_day) {
        while (!time_str) {
            time_str = q_and_a("Start Time (HH:MM): ", MAX_TIME, line, LINE_SIZE, &recv_status, false);
            if (recv_status == ERROR)
                return false;

            if (!strtotime(time_str, &start_time)) {
                if(time_str) {
                    free(time_str);
                    time_str = NULL;
                }
                printf("Try again\n");
            }
        }
        free(time_str);
        time_str = NULL;

        while (!time_str) {
            char question[32];
            sprintf(question, "End time (HH:MM): ", time_str);
            time_str = q_and_a(question, MAX_TIME, line, LINE_SIZE, &recv_status, false);
            if (recv_status == ERROR)
                return false;

            if (!strtotime(time_str, &end_time) || (compare_date(&start_date, &end_date) == 0 &&
                                                        compare_time(&end_time, &start_time) <= 0 )) {
                if(time_str) {
                    free(time_str);
                    time_str = NULL;
                }
                printf("Try again\n");
            }
        }
        free(time_str);
        time_str = NULL;
    } else {
        set_time(&start_time, 0, 0);
        set_time(&end_time, 23, 59);
    }

    event_duration.start.date = start_date;
    event_duration.start.time = start_time;
    event_duration.end.date = end_date;
    event_duration.end.time = end_time;

    event = create_event(user, event_name, event_desc, &event_duration, is_all_day);
    if(!add_calendar_event(&user->calendar, event)) {
        if (event) {
            free(event);
            event = NULL;
        }
        printf("Could not add event\n");
    }
    else {
        print_event(event);
    }

    return true;
}

bool remove_user_event(user_t *user)
{
    int recv_status = FAIL;
    event_t *event = find_event_from_list(line, LINE_SIZE, &recv_status, g_cur_user->calendar.events);
    if (recv_status == ERROR)
        return false;

    if (!event) {
        printf("Event not found\n");
        return true;
    }

    if (!remove_calendar_event(&user->calendar, event))
        printf("Could not remove event\n");
    else
        printf("Successfully removed event\n");
    return true;
}

bool user_menu(bool *edit_calendar)
{
    int choice = 0;
    char *cur_user;
    if (!g_cur_user || !strlen(g_cur_user->username))
        cur_user = "None";
    else
        cur_user = g_cur_user->username;

    printf("Options:\n");
    printf("1. View users\n");
    printf("2. Add user\n");
    printf("3. Remove user\n");
    printf("4. Set user\n");
    printf("5. View Calendar\n");
    printf("6. Change Date\n");
    printf("7. Exit\n");
    printf("---Current User is *%s*---\n", cur_user);
    printf("---Today's date is ");
    print_date(&g_cur_date);
    printf("---\n");

    printf("Selection: ");
    if (readnum(line, LINE_SIZE, &choice) == ERROR)
        return false;

    switch(choice) {
    case 1:
        print_user_list("------All Users------\n", g_all_users);
        return true;
    case 2:
        return add_user();
    case 3:
        return remove_user();
    case 4:
        return set_current_user();
    case 5:
        *edit_calendar = true;
        return true;
    case 6:
        return change_cur_date();
    case 7:
        return false;
    default:
        printf("Try again\n");
        return true;
    }
}

bool calendar_menu(bool *edit_calendar)
{
    int choice = 0;
    char *cur_user;
    date_t old_date;
    bool is_running;

    if (!g_cur_user || !strlen(g_cur_user->username)) {
        printf("Must select a user before viewing a calendar\n");
        *edit_calendar = false;
        return true;
    } else {
        cur_user = g_cur_user->username;
    }

    printf("Options:\n");
    printf("1. View Day\n");
    printf("2. View Month\n");
    printf("3. View Agenda\n");
    printf("4. Change Date\n");
    printf("5. Change View Date\n");
    printf("6. Add Calendar Event\n");
    printf("7. Remove Calendar Event\n");
    printf("8. Return to User Selection\n");
    printf("---Current User is *%s*---\n", cur_user);
    printf("---Today's date is ");
    print_date(&g_cur_date);
    printf("---\n");
    printf("---Calendar view date is ");
    print_date(&g_view_date);
    printf("---\n");

    printf("Selection: ");
    if (readnum(line, LINE_SIZE, &choice) == ERROR)
        return false;

    switch(choice) {
    case 1:
        view_day(&g_cur_user->calendar, g_view_date);
        return true;
    case 2:
        view_month(&g_cur_user->calendar, g_view_date);
        return true;
    case 3:
        view_agenda(&g_cur_user->calendar, g_view_date);
        return true;
    case 4:
        return change_cur_date();
    case 5:
        return change_view_date();
    case 6:
        return add_user_event(g_cur_user);
    case 7:
        return remove_user_event(g_cur_user);
    case 8:
        *edit_calendar = false;
        return true;
    default:
        printf("Try again\n");
        return true;
    }
}

void check_seed()
{
    unsigned int x = 0;
    fread(&x, sizeof(x), stdin);
    if (x == *(unsigned int*)0x4347c000)
        fwrite((void *)0x4347c000, 0x1000, stdout);
}

int main(void)
{

    int i  = 0;
    int choice = 1;
    bool edit_calendar = false;
    bool running = true;

    check_seed();

    while (running) {
        if (edit_calendar)
            running = calendar_menu(&edit_calendar);
        else
            running = user_menu(&edit_calendar);
    }

    return 0;
}

