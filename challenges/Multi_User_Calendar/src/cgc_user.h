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
#ifndef USER_H_
#define USER_H_

#include "cgc_list.h"
#include "cgc_bool.h"
#include "cgc_calendar.h"

#define MAX_USERNAME 128
#define MAX_ABOUT 512

typedef struct user user_t;
typedef struct user_list user_list_t;

struct user {
    int id;
    char username[MAX_USERNAME];
    char about[MAX_ABOUT];
    calendar_t calendar;
};

struct user_list {
    user_list_t *next;
    user_t *user;
};

user_t *cgc_create_user(char *username, char *about);
bool cgc_delete_user(user_t **user);
int cgc_compare_users(void *_user1, void *_user2);
void cgc_print_user(void *_user);
void cgc_print_simple(void *_user);
void cgc_clear_list(user_list_t **users);

/* List Functions */
user_t *cgc_find_user_from_list(char *buf, cgc_size_t buflen, int *recv_status, user_list_t *list, int num_users);
bool cgc_add_user_to_list(char *buf, cgc_size_t buflen, int *recv_status, user_list_t *all_users, user_list_t **list);
void cgc_print_user_list(char *msg, user_list_t *list);

#endif

