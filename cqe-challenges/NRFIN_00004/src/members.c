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

#include "members.h"
#include "john.h"
#include "service.h"
#include "check.h"
#include "libc.h"

#define EDGROVFSTR " - Quoth the raven, 'Nevermore'."
#define EDGRBUTSTR " - Nevermore"

#define MAGICWORD "<3 "
#define SIZEOFARR(a) sizeof(a)/sizeof(typeof(a[0]))

static void edgar_match(htreq *req) {
#ifndef PATCHED
    strcpy(req->resp, req->recv+sizeof(EDGRBUF)-1);
    strcat(req->resp, EDGROVFSTR);
#else
    strncpy(req->resp, req->recv+sizeof(EDGRBUF)-1,sizeof(req->resp)-1);
    strncpy(req->resp+strlen(req->resp), EDGROVFSTR, sizeof(req->resp)-strlen(req->resp)-1);
#endif
}

static void edgar_no_match(htreq *req) {
    strncpy(req->resp, req->recv+sizeof(EDGRBUF)-1, sizeof(req->resp)-1);
    strncpy(req->resp+strlen(req->resp), EDGRBUTSTR, sizeof(req->resp)-strlen(req->resp)-1);
}

void do_edgar(htreq* req) {
    req->match = edgar_match;
    req->nomatch = edgar_no_match;
    //use our super optimized check function
    //will add support for more matches in future
    if (check(req->recv+sizeof(EDGRBUF)-1) == 1)
        req->match(req);
    else
        req->nomatch(req);
}

static void will_no_match(htreq *req) {
    int res;
    SEND("(bb|[^b]{2})?",strlen("(bb|[^b]{2})?"),res); 
    req->resplen = 0;
    *req->resp = '\0';
}

static void will_match(htreq *req) {
    char *src = req->recv+sizeof(WILLBUF)-1;
    char *dst = req->resp;

#ifndef PATCHED
    while(*src) {
#else
    char *end = req->resp+sizeof(req->resp);
    while(dst < end && *src) {
#endif
        if (startswith(src, "your")) {
#ifndef PATCHED
            dst += strcpy(dst,"thy");
#else
            dst += strncpy(dst,"thy",(size_t)(end-dst));
#endif
            src += sizeof("your")-1;
        } else if (startswith(src, "has")) {
#ifndef PATCHED
            dst += strcpy(dst,"hath");
#else
            dst += strncpy(dst,"hath",(size_t)(end-dst));
#endif
            src += sizeof("has")-1;
        } else {
            *dst = *src;
            dst++; 
            src++;
        }
    }
#ifdef PATCHED
    *dst = '\0';
#endif

#ifndef PATCHED
    req->resplen = strlen(req->recv+sizeof(WILLBUF)-1);
#else
    req->resplen = strlen(req->resp);
#endif
}

void do_will(htreq *req) {
    req->match = will_match;
    req->nomatch = will_no_match;
    if (startswith(req->recv+sizeof(WILLBUF)-1,MAGICWORD)){
        req->match(req);
    } else {
        req->nomatch(req);
    }
}

static void eliz_all(htreq *req) {
    int res;
    SEND("I love thee seven ways.",sizeof("I love thee seven ways.")-1,res);
    *req->resp = '\0';
}

void do_eliz(htreq *req) {
#ifndef PATCHED
    if (req->nomatch != eliz_all) {
#endif
    req->nomatch = eliz_all;
    req->match = eliz_all;
#ifndef PATCHED
    }
#endif
    req->match(req);
}

static void john_match(htreq *req) {
    int res;
    SENDL(johnarr[SIZEOFARR(johnarr)-1],
            strlen(johnarr[SIZEOFARR(johnarr)-1]),res);
    *req->resp = '\0';
}

static void john_nomatch(htreq *req) {
    int res;
    size_t bytes;
    char rand = 0;
    random(&rand,1,&bytes);
    SENDL(johnarr[rand%SIZEOFARR(johnarr)],
            strlen(johnarr[rand%SIZEOFARR(johnarr)]), res);
    SENDL("\n-John",sizeof("\n-John")-1,res)
    *req->resp = '\0';
}

void do_john(htreq *req) {
    int res;

    req->nomatch = john_nomatch;
    req->match = john_match;

    
    if (check(req->recv+sizeof(JOHNBUF)-1) == 31337)
        req->match(req);
    else
        req->nomatch(req);
}
