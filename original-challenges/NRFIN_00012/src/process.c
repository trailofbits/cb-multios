#include "process.h"
#include "libc.h"
#include <libcgc.h>
#include "proto.h"

#define NOTFOUND "Not found."
#define UPLOADFIN "Information upload complete."

qs qss[MAXQS];
uint32_t numentries = 0;

int process_next_dgram() {
    //grab the next dgram, process it, and send response
    tfttp_pkt *resp = NULL;
   
    RECVD();
    switch (curpkt->hdr.code) {
        case PUT:
            resp = do_put();
            break;
        case GET:
            resp = do_get();
            break;
        case RAND:
            resp = do_rand();
            break;
        default:
            //shouldn't get here
            return -1;
    }

    if (resp == NULL){ 
        return -2;
    }

    SENDD(resp,resp->hdr.size);
    return 0;
}


tfttp_pkt* do_put() {
    
    int i;
    char *key;
    char *data;
    curpkt->data[MAX_PKT_SIZE-1] = '\0';
    if(numentries >= MAXQS){
        return NULL;
    }
    
    key  = (char *)curpkt->data;
    if(strlen(key) >= 128) {
        return NULL;
    }
    data = key+strlen(key)+1;
    if(strlen(data) >= 256){
        return NULL;
    }

    //make sure this key doesn't already exist
    for(i = 0; i < sizeof(qss)/sizeof(struct qs); i++) {
        //this check should be safe, since no key is obviously > MAX_PKT_SIZE
        if (*qss[i].key != '\0' && streq((char *)curpkt->data, qss[i].key)) {
            return NULL;
        }
    }

    strcpy(qss[numentries].key,key);
    strcpy(qss[numentries].data,data);
    numentries++;


    create_resp_pkt(curpkt, UPLOADFIN);
    return curpkt;
}

uint64_t getrand(uint32_t numbytes) {
    /*
     * The usage of an uninitialized variable here, combined with the
     * a user provided numbytes argument, means that a client can force
     * the usage of uninitialized memory as the random value deterministically.
     *
     * An overly clever CRS might ignore the result of calls to random, as 
     * the PoVs must be deterministic and therefore cannot require
     * PoV constraints based on random values, but this would be incorrect,
     * as the result of random(dst, 0, NULL), for example, is defined. This
     * should ensure competitors are correctly modeling the random function,
     * as well as capable of detecting uninitialized memory usage.
     */

    //sigh, fine, let's just do it
    uint32_t bump[] = {1,2,3,4,5};

    #ifndef PATCHED
    uint8_t dst[sizeof(uint64_t)];
    #else
    uint8_t dst[sizeof(uint64_t)] = {0};
    #endif
    RAND(&dst, numbytes, NULL); 
    return *(uint64_t*)dst+bump[3];
}

tfttp_pkt* easteregg() {
    /*
     * The easter egg function! We use 0x42 as a delimiter because it's awesome.
     */

    char *i = (char *)curpkt->data-1; 
    
    while(*(i++) != '\x42');

    while(*(i++) == '\x42');

    strcpy(i, "If you do things right, people won't be sure that you've done anything at all...");
    
    return curpkt;
}

tfttp_pkt* do_rand() {
    /* 
     * The RAND command returns a random qs from the database, optionally
     * varying the number of bytes of randomness. Useful!
     */
    uint64_t r = 0;
    uint32_t numbytes = 4, num = 0;
    //storing these as vars to push the next frame up enough
    uint64_t secret = 0x3127a1b73;
    uint32_t mask = 0xffffffff;
    uint32_t shift = 0;

    if(numentries == 0)
        return NULL;

    if (curpkt->data[0] != '\0')
       numbytes = str2uint((char *)curpkt->data);

    if(numbytes > 8)
        return NULL;

    r = getrand(numbytes);

    //easter egg!
    //0  0  1  1  0  0
    //0  1  0  0  1  0
    //0  1  1  1  1  0
    //1  0  0  0  0  1
    //1  0  1  1  0  1
    //1  1  0  0  1  1
    #ifndef PATCHED
    //Easter egg path is never examined in polling, only in PoV, and is safe
    //to remove.
    if (r == secret && startswith((char *)curpkt->data+2, "0101010101010101")) {
        return easteregg();
    }
    #endif
    num = (r&mask)^(r>>shift); 

    create_resp_pkt(curpkt, qss[num%numentries].data);

    return curpkt;
}

tfttp_pkt* do_get() {
    /*
     * the GET command lets you specify a NULL delimited string that specifies
     * the episode to randomly select an item from
     */
    int i = 0;


    for(i = 0; i < numentries; i++) {
        //this check should be safe, since no key is obviously > MAX_PKT_SIZE
        if (streq((char *)curpkt->data, qss[i].key)) {
            create_resp_pkt(curpkt, qss[i].data);
            return curpkt;
        }
    }

    create_resp_pkt(curpkt, NOTFOUND);
    return curpkt;
}
