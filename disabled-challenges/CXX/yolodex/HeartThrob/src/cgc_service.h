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

#include "libcgc.h"
#include "cgc_libc.h"

#define DEBUG 0
#if DEBUG
#define LOG(a) cgc_transmit(STDERR, a, sizeof(a), 0)
#endif

#ifndef SERVICE_H
#define SERVICE_H


#define EDGRBUF "Edgar: "
#define WILLBUF "William: "
#define ELIZBUF "Elizabeth: "
#define JOHNBUF "John: "
#define EBUF "ERROR: input too large"
#define SEND(b,s,o) o=cgc_sendall(STDOUT,b,s); if (o<=0) cgc__terminate(1);
#define SENDL(b,s,o) o=cgc_sendline(STDOUT,b,s); if (o<=0) cgc__terminate(1);
#define RECV(b,s,o) o=cgc_recvline(STDIN,b,s); if(o<0){SENDL(EBUF,sizeof(EBUF)-1,o);  cgc__terminate(2);}
#define ALLOC(s,x,a,o) o=cgc_allocate(s,x,a); if(o!=0) cgc__terminate(3);

typedef struct htreq {
    cgc_size_t resplen;
    char recv[1044];
    char resp[1024];
    void (*match)(struct htreq*);
    void (*nomatch)(struct htreq*);
        
} htreq;

int cgc_prompt(char *pmpt, char *buf, cgc_size_t size);
int main(int cgc_argc, char *cgc_argv[]);

#endif
