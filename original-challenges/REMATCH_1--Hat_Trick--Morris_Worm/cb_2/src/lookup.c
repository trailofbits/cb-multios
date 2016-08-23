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
#include <libcgc.h>
#include "libc.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "lookup.h"

void usage() {
  printf("lookupd [-s] [-q] names\n");
}

void lookup(int argc, char **argv) {
  int brief = 0;
  int quick = 0;
  char **names;
  int num_names;
  int i;

// Process command line args
  if (strcmp(argv[0], "lookup") != 0) {
    usage();
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
        printf("Invalid Switch: -$c\n", argv[i][1]);
        usage();
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
      print_all_users_short();
    } else {
      print_all_users_long();
    }
    return;
  }

  while (i < argc) {
    user *u;
    if (quick) {
      u = quick_lookup(argv[i]);
    } else {
      u = long_lookup(argv[i]);
    }
    if (u == NULL) {
      printf("User not found ($s)\n", argv[i]);
    } else {
      if (brief) {
        print_user_short(u);
      } else {
        print_user_long(u);
      }
    }
    i++;
  }
}


user *quick_lookup(char *name) {
  list *l = short_list;
  while(l != NULL) {
    if (l->object == NULL) {
      break;
    }
    user *u = l->object;
    if (equals(u->name, name)) {
      return u;
    }
    l = l->next;
  }
  return NULL;
}

user *long_lookup(char *name) {
  user *u = root_user;
  while(u != NULL) {
    if (equals(u->name, name)) {
      list *l = short_list;
      while (l->next != NULL) {
        user *su = l->object;
        if (su == NULL) {
          break;
        }
        if (equals(su->name, name)) {
          break;
        }
      }
      if (l->next == NULL) {
        l->next = calloc(sizeof(list));
        l->next->object = u;
      }
      return u;
    }
    u = u->next;
  }
  return NULL;
}


void print_all_users_short() {
  user *u = root_user;
  while (u != NULL) {
    print_user_short(u);
    u = u->next;
  }
}


void print_all_users_long() {
  user *u = root_user;
  while (u != NULL) {
    print_user_long(u);
    u = u->next;
  }
}

void print_user_short(user *u) {
  printf("Username: $s\n", u->name);
  printf("Real name: $s\n", u->realname);
  printf("Phone #:$s\n", u->phone);
  printf("\n");
  }


void print_user_long(user *u) {
  printf("Username: $s\nReal name: $s\nHost name: $s\nIdle for: $d seconds\n", u->name, u->realname, u->hostname, u->idletime);
  if (u->online) {
    printf("User is online\n");
  } else {
    printf("User is offline\n");
  }
  printf("Phone #:$s\n\n", u->phone);
  }