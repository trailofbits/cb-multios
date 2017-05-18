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

#include "cgc_members.h"
#include "cgc_john.h"
#include "cgc_service.h"
#include "cgc_check.h"
#include "cgc_libc.h"

#define EDGROVFSTR " - Quoth the raven, 'Nevermore'."
#define EDGRBUTSTR " - Nevermore"

#define MAGICWORD "<3 "
#define SIZEOFARR(a) sizeof(a)/sizeof(typeof(a[0]))

static void cgc_edgar_match(htreq *req) {
#ifndef PATCHED
    cgc_strcpy(req->resp, req->recv+sizeof(EDGRBUF)-1);
    cgc_strcat(req->resp, EDGROVFSTR);
#else
    cgc_strncpy(req->resp, req->recv+sizeof(EDGRBUF)-1,sizeof(req->resp)-1);
    cgc_strncpy(req->resp+cgc_strlen(req->resp), EDGROVFSTR, sizeof(req->resp)-cgc_strlen(req->resp)-1);
#endif
}

static void cgc_edgar_no_match(htreq *req) {
    cgc_strncpy(req->resp, req->recv+sizeof(EDGRBUF)-1, sizeof(req->resp)-1);
    cgc_strncpy(req->resp+cgc_strlen(req->resp), EDGRBUTSTR, sizeof(req->resp)-cgc_strlen(req->resp)-1);
}

void cgc_do_edgar(htreq* req) {
    req->match = cgc_edgar_match;
    req->nomatch = cgc_edgar_no_match;
    //use our super optimized check function
    //will add support for more matches in future
    if (cgc_check(req->recv+sizeof(EDGRBUF)-1) == 1)
        req->match(req);
    else
        req->nomatch(req);
}

static void cgc_will_no_match(htreq *req) {
    int res;
    SEND("(bb|[^b]{2})?",cgc_strlen("(bb|[^b]{2})?"),res); 
    req->resplen = 0;
    *req->resp = '\0';
}

static void cgc_will_match(htreq *req) {
    char *src = req->recv+sizeof(WILLBUF)-1;
    char *dst = req->resp;

#ifndef PATCHED
    while(*src) {
#else
    char *end = req->resp+sizeof(req->resp);
    while(dst < end && *src) {
#endif
        if (cgc_startswith(src, "your")) {
#ifndef PATCHED
            dst += cgc_strcpy(dst,"thy");
#else
            dst += cgc_strncpy(dst,"thy",(cgc_size_t)(end-dst));
#endif
            src += sizeof("your")-1;
        } else if (cgc_startswith(src, "has")) {
#ifndef PATCHED
            dst += cgc_strcpy(dst,"hath");
#else
            dst += cgc_strncpy(dst,"hath",(cgc_size_t)(end-dst));
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
    req->resplen = cgc_strlen(req->recv+sizeof(WILLBUF)-1);
#else
    req->resplen = cgc_strlen(req->resp);
#endif
}

void cgc_do_will(htreq *req) {
    req->match = cgc_will_match;
    req->nomatch = cgc_will_no_match;
    if (cgc_startswith(req->recv+sizeof(WILLBUF)-1,MAGICWORD)){
        req->match(req);
    } else {
        req->nomatch(req);
    }
}

static void cgc_eliz_all(htreq *req) {
    int res;
    SEND("I love thee seven ways.",sizeof("I love thee seven ways.")-1,res);
    *req->resp = '\0';
}

void cgc_do_eliz(htreq *req) {
#ifndef PATCHED
    if (req->nomatch != cgc_eliz_all) {
#endif
    req->nomatch = cgc_eliz_all;
    req->match = cgc_eliz_all;
#ifndef PATCHED
    }
#endif
    req->match(req);
}

static void cgc_john_match(htreq *req) {
    int res;
    SENDL(johnarr[SIZEOFARR(johnarr)-1],
            cgc_strlen(johnarr[SIZEOFARR(johnarr)-1]),res);
    *req->resp = '\0';
}

static void cgc_john_nomatch(htreq *req) {
    int res;
    cgc_size_t bytes;
    char rand = 0;
    cgc_random(&rand,1,&bytes);
    SENDL(johnarr[rand%SIZEOFARR(johnarr)],
            cgc_strlen(johnarr[rand%SIZEOFARR(johnarr)]), res);
    SENDL("\n-John",sizeof("\n-John")-1,res)
    *req->resp = '\0';
}

void cgc_do_john(htreq *req) {
    int res;

    req->nomatch = cgc_john_nomatch;
    req->match = cgc_john_match;

    
    if (cgc_check(req->recv+sizeof(JOHNBUF)-1) == 31337)
        req->match(req);
    else
        req->nomatch(req);
}
