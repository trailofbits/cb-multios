/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef LOOKUP_H
#define LOOKUP_H

#define FD_TO_MAIN 5
#define FD_FROM_MAIN 4

#define HMAX 32

#define MAX_USERS 32

typedef struct user_s {
  char *name;
  char hostname[HMAX+1];
  unsigned long idletime;
  char *realname;
  char *phone;
  char online;
  struct user_s *next;
} user;

typedef struct list_s {
  void *object;
  struct list_s *next;
} list;

extern user *root_user;
extern int num_users;
extern list *short_list;

void lookup(int argc, char **argv);
user *quick_lookup(char *name);
user *long_lookup(char *name);
void print_all_users_short();
void print_all_users_long();
void print_user_short(user *u);
void print_user_long(user *u);
#endif