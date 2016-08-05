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
#include "stdio.h"
#include "malloc.h"
#include "libc.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "lookup.h"


int gets(char *buf) {
    size_t bytes_received = 0;
    int bytes_total = 0;
    int ret;
    while (1) {
        ret = receive(STDIN, buf, 1, &bytes_received);
        if ((ret != 0) || (bytes_received == 0)) {
            return bytes_total;
        }
        bytes_total++;
        if (*buf == '\n') {
            *buf = '\0';
            return bytes_total;
        }
        buf++;
    } 
}

void lookupd() {

    char input[512];
    int bytes_received = 0;

#ifdef PATCHED_1
    bytes_received = receive_until(input, sizeof(input), '\n');
    bytes_received = force_newline(input, sizeof(input), bytes_received);
#else
    bytes_received = gets(input);
#endif
    char *args[20];
    int i = 0;
    // parse input
    char *p = input;

    while (i < 19) {
        while(isspace(*p)) p++;
        if (!*p)
            break;
        if (*p == '/' && (p[1] == 'W' || p[1] == 'w')) {
            p += 2;
            args[i++] = "-l";
        }
        if (*p && !isspace(*p)) {
            args[i++] = p;
            while (*p && !isspace(*p)) p++;
            *p++ = '\0';
        }
    }
    // Null terminate argument list
    args[i] = 0;

    lookup(i, args);
}

user *root_user;
int num_users;
list *short_list;

char *gen_random_str(int min, int max) {
    int length = random_in_range(min, max);
    char *s = calloc(length);
    for(int i=0; i<length - 2; i++) {
        s[i] = random_in_range(0x30, 0x7e);
    }
    return s;
}

user *gen_random_user() {
    user *new_user = calloc(sizeof(user));
    new_user->name = gen_random_str(5, 32);
    char *hn = gen_random_str(5, 32);
    strcpy(new_user->hostname, hn);
    free(hn);
    new_user->idletime = rand() & 0xffffff;
    new_user->realname = gen_random_str(5, 64);
    new_user->phone = gen_random_str(9,9);
    new_user->online = random_in_range(0,1);

    return new_user;
}
  

int main(void) {
    char *sp;
    char input[512];
    int bytes_received = 0;
    fd_set fds;
    int ready_fds;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int ret;

    // Initialize user list
    srand();
    root_user = gen_random_user();
    num_users++;
    user *u = root_user;
    short_list = calloc(sizeof(short_list));
    short_list->object = root_user;
    for(int i=0; i<10; i++) {
        u->next = gen_random_user();
        u = u->next;
        num_users++;
    }

    // read input
    while (1) {
        FD_ZERO(&fds);
        FD_SET(FD_FROM_MAIN, &fds);
        ret = fdwait(FD_FROM_MAIN + 1, &fds, NULL, &timeout, &ready_fds);
        bytes_received = receive_until_fd(FD_FROM_MAIN, input, sizeof(input), '\n');
        bytes_received = force_newline(input, sizeof(input), bytes_received);
        if (equals(input, "terminate\n")) {
            goto EXIT;
        }
        if (bytes_received > 0) {
            lookupd();
            // Tell main program lookupd is done
            send_all_fd(FD_TO_MAIN, "\0\n", 2);       
        }
    } 

    EXIT:
    // exit
    return 0;
}
