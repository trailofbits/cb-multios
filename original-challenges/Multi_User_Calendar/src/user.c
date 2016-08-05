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
#include "user.h"
#include "read.h"

size_t g_user_id = 0;

user_t *create_user(char *username, char *about)
{
    if (!username || !strlen(username) || !about || !strlen(about))
        return NULL;

    user_t *user = calloc(1, sizeof(user_t));
    user->id = g_user_id++;
    strcpy(user->username, username);
    strcpy(user->about, about);
    user->calendar.num_events = 0;
    user->calendar.events = NULL;

    return user;
}

bool delete_user(user_t **user)
{
    if (!*user)
        return false;
    free(*user);
    *user = NULL;
    return true;
}

int compare_users(void *_user1, void *_user2)
{
    user_t *user1 = (user_t *)_user1;
    user_t *user2 = (user_t *)_user2;

    if (!user1 || !user2)
        return -1;

    return strcmp(user1->username, user2->username);
}

void print_user(void *_user)
{
    user_t *user = (user_t *)_user;
    printf("User id = %d\n", user->id);
    printf("Username is \"%s\"\n", user->username);
    printf("About %s: %s\n", user->username, user->about);
    printf("---------------------\n");
}

void print_simple(void *_user)
{
    user_t *user = (user_t *)_user;
    printf("Id=%d, username=%s\n", user->id, user->username);
}


void clear_list(user_list_t **users)
{
    user_t *user = (user_t *)popfront((list_t **) users);
    while (user) {
        free(user);
        user = (user_t *)popfront((list_t **) users);
    }
}

user_t *find_user_from_list(char *buf, size_t buflen, int *recv_status, user_list_t *list, int list_size)
{
    if (!buf || buflen < 2)
        return NULL;

    user_t temp_user;
    user_list_t *users = list;
    char *username = NULL;
    int tries = 0;

    //Read username
#ifdef PATCHED_1
    username = q_and_a("Enter username: ", MAX_USERNAME, buf, buflen, recv_status, true);
#else
    username = q_and_a("Enter username: ", buflen, buf, buflen, recv_status, true);
#endif
    if (!username)
        return NULL;

    if (*recv_status != SUCCESS) {
        free(username);
        return NULL;
    }

    if (list_size <= 100) {
        user_list_t *iter = list;
        int i;
        for (i = 0; i < list_size; i++, iter = iter->next) {
            if (strcmp(username, iter->user->username) == 0) {
                free(username);
                return iter->user;
            }
        }
        free(username);
        return NULL;
    } else {
        strcpy(temp_user.username, username);
        free(username);
        username = NULL;
        return find((list_t *)users, &temp_user, &compare_users);
    }
}

bool add_user_to_list(char *buf, size_t buflen, int *recv_status, user_list_t *all_users, user_list_t **list)
{
    *recv_status = FAIL;
    int num_tries = 0;
    char *username = NULL;
    char *about = NULL;
    user_t *found_user = NULL;

    //Read username
    while(*recv_status != SUCCESS) {
        found_user = find_user_from_list(buf, buflen, recv_status, all_users, 1000);

        switch (*recv_status) {
        case ERROR:
            return false;
        case SUCCESS:
            if (found_user) {
                if (!insert_in_order((list_t **)list, found_user, &compare_users))
                    *recv_status = FAIL;
                return true;
            }
        case FAIL:
        default:
            printf("Try again\n");
        }
        if (++num_tries == MAX_TRIES)
            break;
    }

    return false;
}

void print_user_list(char *msg, user_list_t *list)
{
    printf("%s", msg);
    print((list_t *)list, &print_user);
}
