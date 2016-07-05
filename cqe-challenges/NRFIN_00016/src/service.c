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
#include "libc.h"
#include "service.h"
#include "csum.h"


#define SUCCESS "Valve successfully modified."
#define INVALIDCSUM "Invalid checksum."
#define REDACTED "This is not the function you're looking for."

uint32_t valvepos; 
char resp[11] = {0};

static char *getv(reqpkt_t *req) {
    /*
     * Get the position of the valve.
     * Doesn't matter if anyone knows this
     */

    uint2str(resp,sizeof(resp),valvepos);
    return resp;
}

static char *setv(reqpkt_t *req) {
    /*
     * Set the position of the valve.
     * Since we're the only ones who know how to make these packets, should be safe.
     */

    valvepos = str2uint((char *)req->data.data);
    return SUCCESS;
}

static char *gett(reqpkt_t *req) {
    /*
     * Get the temperature of the widget.
     * Currently, we can't do this, so we just guess. Should be fine.
     */

    uint32_t temp = 0;
    RAND(&temp, sizeof(temp), NULL);
    uint2str(resp,sizeof(resp),temp);
    return resp;
}

static char *redacted(reqpkt_t *req) {
    /*
     * This is one of the replacements for our remote management system.
     * Should be pretty much impossible for researchers to find them all.
     */
    #ifndef PATCHED
    memcpy(&valvepos,req->data.data+4,*(uint32_t*)(req->data.data));
    #endif
    return REDACTED;

}

static char *admin_add_login(reqpkt_t *req) {
    /*
     * This is one of the replacements for our remote management system.
     * Should be pretty much impossible for researchers to find them all.
     */
    char idx = req->data.data[0];
    char buf[128] = {0};
    #ifndef PATCHED
    if (idx > 127)
    #else
    if (idx < 0)
    #endif
        return REDACTED;
    memcpy(buf,req->data.data,idx);
    return REDACTED;
}
    
static char *admin_addxoradd_login(reqpkt_t *req) {
    /*
     * This is one of the replacements for our remote management system.
     * Should be pretty much impossible for  researchers to find them all.
     */
    #ifndef PATCHED
    //for your protection
    char buf[5] = {0};
    if (startswith((char *)req->data.data,"robots only")) {
        strcpy(buf,(char *)req->data.data);
    }
    #endif
    return REDACTED;
}

static char *admin_crc_login(reqpkt_t *req) {
    /*
     * This is one of the replacements for our remote management system.
     * Should be pretty much impossible for  researchers to find them all.
     */
    #ifndef PATCHED
    char buf[64] = {0};
    uint8_t len = req->data.data[0];
    uint8_t i;
    if (len > 64)
        return REDACTED;
    len = len-4;
    for (i=0; i < len; i++)
        buf[i] = req->data.data[i];
    #endif
    return REDACTED;
}

static char *admin_fp_login(reqpkt_t *req) {
    /*
     * This is one of the replacements for our remote management system.
     * Should be pretty much impossible for  researchers to find them all.
     */
    #ifndef PATCHED
    double storage[10];
    int j = 0;
    double i,max;

    max = *((double*)(req->data.data+8));
    if (max > 1.10001)
        return REDACTED;
    for (i = 0.0; i < max; i+=0.1, j++)
        storage[j] = *(((double*)(req->data.data))+j);
    #endif
    return REDACTED;
}

static char *admin_md5_login(reqpkt_t *req) {
    /*
     * This is one of the replacements for our remote management system.
     * Should be pretty much impossible for  researchers to find them all.
     */
    #ifndef PATCHED
    uint8_t i;
    uint32_t buf[32];
    for (i = 0; i < req->data.data[5]; i++)
        buf[i] = *(((uint32_t*)(req->data.data+6))+i);
    #endif
    return REDACTED;
}

static char *process_pkt(reqpkt_t *req) {
    /* Here we process the control packet and return an appropriate response.
     *
     * There are three types of packets:
     *  - Get valve position
     *  - Set valve position
     *  - Get temperature
     *  - <redacted>
     *
     * All packets contain 5 different checksums to ensure packet integrity:
     *  - Simple additive checksum
     *  - A more complex addition+xor+addition checksum
     *  - A checksum based on floating point addition
     *  - A modified CRC32
     *  - An MD5 hash
     *
     * Because of recent pushback against our remote assistance technology,
     * we have replaced our device accounts with less obvious access methods.
     * Hopefully this will help us avoid further embarrassment.
     *
     */
    uint32_t lresult;
    uint64_t llresult;
    double fpresult;
    uint32_t md5res[4];

    //md5 hash of the string "admin"/
    uint32_t md5secret[] = {0x292f2321, 0xa7a5577a, 0x0e4a8943, 0xc31f804a};

    llresult = additive(req->data.data, REQ_SIZE);

    if (llresult == 0x4242424242424242)
        return admin_add_login(req);

    if (req->additive != llresult)
        return INVALIDCSUM;

    llresult = addxoradd(req->data.data, REQ_SIZE);

    if (llresult ==  3141592653589793238)
        return admin_addxoradd_login(req);

    if (req->addxoradd != llresult)
        return INVALIDCSUM;

    lresult = crc32(req->data.data, REQ_SIZE);

    if (lresult == 0x6F4E3700)
        return admin_crc_login(req);

    if (req->crc32 != lresult)
        return INVALIDCSUM;

    fpresult = fpadditive(req->data.data, REQ_SIZE);

    if (fpresult == 2.71828182845)
        return admin_fp_login(req);

    //NaNaNaNaNaNaNaNaNaN...
    if (req->fp == req->fp && req->fp != fpresult)
        return INVALIDCSUM;

    md5(req->data.data, 5, md5res);

    if (!memcmp(md5res,md5secret,sizeof(md5res)))
        return admin_md5_login(req);

    md5(req->data.data, REQ_SIZE, md5res);

    if (memcmp(md5res, req->md5, sizeof(md5res)))
        return INVALIDCSUM;

    //phew! our packet is verified!
    //let's do this!

    switch(req->data.code) {
        case GETV:
            return getv(req);
        case SETV:
            return setv(req);
        case GETT:
            return gett(req);
        case NOTHERE:
            //let's give ourselves one more chance to remote in
            //need to make sure we can always help our customers
            return redacted(req);
        default:
            return "NaNaNaNaNaNaNaNaNaNaNaNaNaN watman!"; 
    }
}


int main(void) {
    int res = 0;
    reqpkt_t req = {0};
    char *r;

    RAND(&valvepos,sizeof(valvepos),NULL);
    
    RECV(sizeof(reqpkt_t),(char *)&req);

    r = process_pkt(&req);

    SSENDL(strlen(r),r);

    return 0;
}
