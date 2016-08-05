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

#ifndef USER_H
#define USER_H

#include "error.h"

struct team_t;
typedef struct user_t {
    char nick[16];
    char pass[32];
    struct team_t *team;
} user_t;

typedef struct team_t {
    char code[33];
    char name[32];
    struct user_t** members;
    struct user_t *leader;
    size_t num_members;
    size_t sz_members;
    char *shout;
    unsigned int score;
} team_t;

/* User */
error_t user_new(user_t **user);
error_t user_set_nick(user_t *user, const char *nick);
error_t user_set_pass(user_t *user, const char *pass);
error_t user_set_team(user_t *user, team_t *team, team_t **old);

/* Team */
error_t team_new(team_t **team);
error_t team_add_member(team_t *team, user_t *user);
error_t team_remove_member(team_t *team, const char *nick);
error_t team_change_name(team_t *team, const char *name);
error_t team_set_shoutout(team_t *team, const char *shout);

#endif
