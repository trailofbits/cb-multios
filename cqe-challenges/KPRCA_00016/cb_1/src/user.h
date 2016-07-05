/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#define MAX_NUM_USERS 999
#define MAX_USERNAME_LEN 64
#define MAX_PASSWORD_LEN 64

typedef struct user {
  unsigned short user_id;
  unsigned int auth_code;
  char username[MAX_USERNAME_LEN];
  char password[MAX_PASSWORD_LEN];
  struct user *next;
} user_t;

typedef user_t* user_list_t;

int add_user(user_list_t *, user_t *);
user_t* find_user(user_list_t, char *);
user_t* find_user_by_id(user_list_t, unsigned short);
user_t* get_user(user_list_t, unsigned short, unsigned int);

#endif
