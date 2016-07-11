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

#include <libcgc.h>
#include "service.h"
#include "members.h"

#define GREET "Hello, welcome to the alpha version of our latest HeartThrob(TM) service!\n\n"\
 "   _      _\n"\
 "  /  \\  /  \\\n"\
 "  \\   \\/   /\n"\
 "   \\      /\n"\
 "    \\    /\n"\
 "     \\  /\n"\
 "      \\/\n\n"\
 "If you experience any problems, please contact your nearest HeartThrob technician!\n\n"\
 "Your choices are:\n"\
 "Elizabeth\n"\
 "Edgar\n"\
 "John\n"\
 "William\n\n"\
 "To interact with our virtual members, address them as follows:\n"\
 "Edgar: What doth the raven say?\n\n"\
 "Our authors provide various services, please give them a try...\n"

int prompt(char *pmpt, char *buf, size_t size) {
    int ret;

    SEND(pmpt, strlen(pmpt), ret);

    RECV(buf, size, ret);

    return ret;
 }

int main(void) {
    int ret;
    htreq *req;

    ALLOC(sizeof(htreq),0,(void**)&req,ret);

    //make sure our CB will crash on out of bounds read/write
    req = (htreq *)(((char *)req)+4096-sizeof(htreq));

    SENDL(GREET, sizeof(GREET)-1, ret);

    while (1) {
        ret = prompt("> ", req->recv, sizeof(req->recv));
        if (startswith(req->recv,EDGRBUF)) {
            do_edgar(req);
            req->resplen = strlen(req->resp);
        } else if (startswith(req->recv,WILLBUF)) {
            do_will(req);
        } else if (startswith(req->recv,ELIZBUF)) {
            do_eliz(req);
            req->resplen = strlen(req->resp);
        } else if (startswith(req->recv,JOHNBUF)) {
            do_john(req);
            req->resplen = strlen(req->resp);
        } else if (streq(req->recv,"quit")) {
            _terminate(0);
        } else if (streq(req->recv,"")) {
	        continue;
        } else {
	        strcpy(req->resp,"Error");
            req->resplen = strlen(req->resp);
	    }

        SENDL(req->resp, req->resplen, ret); 
    }
    return 0;
}
