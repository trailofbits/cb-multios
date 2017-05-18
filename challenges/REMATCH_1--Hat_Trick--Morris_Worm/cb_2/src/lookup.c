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
#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_malloc.h"
#include "cgc_lookup.h"

void cgc_usage() {
  cgc_printf("lookupd [-s] [-q] names\n");
}

void cgc_lookup(int argc, char **argv) {
  int brief = 0;
  int quick = 0;
  char **names;
  int num_names;
  int i;

// Process command line args
  if (cgc_strcmp(argv[0], "lookup") != 0) {
    cgc_usage();
    return;
  }
  i = 1;
  while (i < argc) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 's') {
        brief = 1;
      } else if (argv[i][1] == 'l') {
        brief = 0; 
      } else if (argv[i][1] == 'q') {
        quick = 1;
      } else {
        cgc_printf("Invalid Switch: -$c\n", argv[i][1]);
        cgc_usage();
        return;
      }
      i++;
    } else {
      break;
    }
  }
  // Remaining arguments are names
  if (i >= argc) {
  // print all users on the system
    if (brief) {
      cgc_print_all_users_short();
    } else {
      cgc_print_all_users_long();
    }
    return;
  }

  while (i < argc) {
    user *u;
    if (quick) {
      u = cgc_quick_lookup(argv[i]);
    } else {
      u = cgc_long_lookup(argv[i]);
    }
    if (u == NULL) {
      cgc_printf("User not found ($s)\n", argv[i]);
    } else {
      if (brief) {
        cgc_print_user_short(u);
      } else {
        cgc_print_user_long(u);
      }
    }
    i++;
  }
}


user *cgc_quick_lookup(char *name) {
  list *l = cgc_short_list;
  while(l != NULL) {
    if (l->object == NULL) {
      break;
    }
    user *u = l->object;
    if (cgc_equals(u->name, name)) {
      return u;
    }
    l = l->next;
  }
  return NULL;
}

user *cgc_long_lookup(char *name) {
  user *u = cgc_root_user;
  while(u != NULL) {
    if (cgc_equals(u->name, name)) {
      list *l = cgc_short_list;
      while (l->next != NULL) {
        user *su = l->object;
        if (su == NULL) {
          break;
        }
        if (cgc_equals(su->name, name)) {
          break;
        }
      }
      if (l->next == NULL) {
        l->next = cgc_calloc(sizeof(list));
        l->next->object = u;
      }
      return u;
    }
    u = u->next;
  }
  return NULL;
}


void cgc_print_all_users_short() {
  user *u = cgc_root_user;
  while (u != NULL) {
    cgc_print_user_short(u);
    u = u->next;
  }
}


void cgc_print_all_users_long() {
  user *u = cgc_root_user;
  while (u != NULL) {
    cgc_print_user_long(u);
    u = u->next;
  }
}

void cgc_print_user_short(user *u) {
  cgc_printf("Username: $s\n", u->name);
  cgc_printf("Real name: $s\n", u->realname);
  cgc_printf("Phone #:$s\n", u->phone);
  cgc_printf("\n");
  }


void cgc_print_user_long(user *u) {
  cgc_printf("Username: $s\nReal name: $s\nHost name: $s\nIdle for: $d seconds\n", u->name, u->realname, u->hostname, u->idletime);
  if (u->online) {
    cgc_printf("User is online\n");
  } else {
    cgc_printf("User is offline\n");
  }
  cgc_printf("Phone #:$s\n\n", u->phone);
  }