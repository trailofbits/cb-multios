/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SERVICE_H
#define SERVICE_H

#include <libcgc.h>
#include "libc.h"
#include "verbs.h"

#if DEBUG_ENABLE
#define DEBUG(msg) transmit(STDERR, msg, sizeof(msg), 0)
#else
#define DEBUG(msg) do {} while (0)
#endif

#define FATAL(msg, errno) DEBUG(msg); transmit(STDOUT, msg, sizeof(msg), 0); _terminate(errno);

// Thing we may want to change.
#define DELIM_URI ' '
#define DELIM_EOF "\r" // this is sent at the end of each response
#define CLOG_DELAY 3 // in microseconds

// Things we probably don't want to change.
#define RECV_BUF_SZ 1024
#define URI_BUF_SZ 16
#define RND_BUF_SZ 32
#define FILE_BUF_SZ 16

#define ERRNO_RANDOM 1000+BASE_ID+4
#define ERRNO_INVALID_VERB 1000+BASE_ID+5
#define ERRNO_INSUFFICIENT_FUNDS 1000+BASE_ID+6
#define ERRNO_FILE_NOT_FOUND 1000+BASE_ID+7
#define ERRNO_INVALID_REQ 1000+BASE_ID+8
#define ERRNO_UNK 1000+BASE_ID+1337

#define ERR_RANDOM "wrong # of random bytes\n"
#define ERR_INVALID_VERB "invalid verb\n"
#define ERR_INVALID_REQ "invalid request\n"
#define ERR_INSUFFICIENT_FUNDS "you're too poor to use this verb :(\n"
#define ERR_FILE_NOT_FOUND "requested file not found\n"


int dump_file(char *name);
int head_file(char *name);
int list_files(void);
int main(void);

// stupid-simple files that have 16-character names and 16-character contents
typedef struct fileentry {
    char name[FILE_BUF_SZ];
    char contents[FILE_BUF_SZ];   
} fileentry;

UINT8 num_files;
fileentry *files;
char buf_recv[RECV_BUF_SZ];
char *ptr_uri_tip;
char *ptr_uri_gimme;
char *ptr_uri_smore;
char *ptr_uri_mooch;
char *ptr_uri_auth;


#endif





