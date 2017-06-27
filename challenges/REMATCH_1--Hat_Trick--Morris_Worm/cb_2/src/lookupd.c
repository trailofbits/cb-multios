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
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_libc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"
#include "cgc_lookup.h"


int cgc_gets(char *buf) {
    cgc_size_t bytes_received = 0;
    int bytes_total = 0;
    int ret;
    while (1) {
        ret = cgc_receive(STDIN, buf, 1, &bytes_received);
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

void cgc_lookupd() {

    char input[512];
    int bytes_received = 0;

#ifdef PATCHED_1
    bytes_received = cgc_receive_until(input, sizeof(input), '\n');
    bytes_received = cgc_force_newline(input, sizeof(input), bytes_received);
#else
    bytes_received = cgc_gets(input);
#endif
    char *args[20];
    int i = 0;
    // parse input
    char *p = input;

    while (i < 19) {
        while(cgc_isspace(*p)) p++;
        if (!*p)
            break;
        if (*p == '/' && (p[1] == 'W' || p[1] == 'w')) {
            p += 2;
            args[i++] = "-l";
        }
        if (*p && !cgc_isspace(*p)) {
            args[i++] = p;
            while (*p && !cgc_isspace(*p)) p++;
            *p++ = '\0';
        }
    }
    // Null terminate argument list
    args[i] = 0;

    cgc_lookup(i, args);
}

user *cgc_root_user;
int num_users;
list *cgc_short_list;

char *cgc_gen_random_str(int min, int max) {
    int length = cgc_random_in_range(min, max);
    char *s = cgc_calloc(length);
    for(int i=0; i<length - 2; i++) {
        s[i] = cgc_random_in_range(0x30, 0x7e);
    }
    return s;
}

user *cgc_gen_random_user() {
    user *new_user = cgc_calloc(sizeof(user));
    new_user->name = cgc_gen_random_str(5, 32);
    char *hn = cgc_gen_random_str(5, 32);
    cgc_strcpy(new_user->hostname, hn);
    cgc_free(hn);
    new_user->idletime = cgc_rand() & 0xffffff;
    new_user->realname = cgc_gen_random_str(5, 64);
    new_user->phone = cgc_gen_random_str(9,9);
    new_user->online = cgc_random_in_range(0,1);

    return new_user;
}
  

int main(int cgc_argc, char *cgc_argv[]) {
    char *sp;
    char input[512];
    int bytes_received = 0;
    cgc_fd_set fds;
    int ready_fds;
    struct cgc_timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int ret;

    // Initialize user list
    cgc_srand();
    cgc_root_user = cgc_gen_random_user();
    num_users++;
    user *u = cgc_root_user;
    cgc_short_list = cgc_calloc(sizeof(cgc_short_list));
    cgc_short_list->object = cgc_root_user;
    for(int i=0; i<10; i++) {
        u->next = cgc_gen_random_user();
        u = u->next;
        num_users++;
    }

    // cgc_read input
    while (1) {
        FD_ZERO(&fds);
        FD_SET(FD_FROM_MAIN, &fds);
        ret = cgc_fdwait(FD_FROM_MAIN + 1, &fds, NULL, &timeout, &ready_fds);
        bytes_received = cgc_receive_until_fd(FD_FROM_MAIN, input, sizeof(input), '\n');
        bytes_received = cgc_force_newline(input, sizeof(input), bytes_received);
        if (cgc_equals(input, "terminate\n")) {
            goto EXIT;
        }
        if (bytes_received > 0) {
            cgc_lookupd();
            // Tell main program lookupd is done
            cgc_send_all_fd(FD_TO_MAIN, "\0\n", 2);       
        }
    } 

    EXIT:
    // cgc_exit
    return 0;
}
