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
#include <stdint.h>
#include "libc.h"
#include "prng.h"
#include "malloc.h"
#include "fs.h"

#define ROAMTIMEOUT 2
#define VERSION 0xc0ff33

/**
 * Read in data from stdin with a timeout
 *
 * @param s struct to read into
 * @return 1 on success, 0 on failure
 */
#define READDATATIMEOUT(s) (sizeof(s) == readall_timeout(stdin,(char *)&s,sizeof(s)) ? 1 : 0)

/**
 * Read in data from stdin and decrypt
 *
 * @param s struct to read into
 * @return 1 on success, 0 on failure
 */
#define EREADDATA(s) (sizeof(s) == ereadall(stdin,(char *)&s,sizeof(s)) ? 1 : 0)

/**
 * Encrypt data and send to stdout
 *
 * @param s struct to write
 * @return 1 on success, 0 on failure
 */
#define ESENDDATA(s) (sizeof(s) == esendall(stdout,(char *)&s,sizeof(s)) ? 1 : 0)


enum Status {OK, EXIT, DISCON, ERR} typedef status_t; 

enum MsgType {MKDIR, LIST, PUT, GET, RM, RMDIR,
    QUIT} typedef msgtype_t;

enum RespType {MKDIR_OK, MKDIR_FAIL, LIST_OK,
    LIST_FAIL, PUT_OK, PUT_FAIL, GET_OK, GET_FAIL,
    RM_OK, RM_FAIL, RMDIR_OK, RMDIR_FAIL, QUIT_OK} typedef resptype_t;

struct msg {
    msgtype_t type;
    char buf[1024];
} typedef msg_t;

struct resp {
    resptype_t type;
    char buf[1024];
} typedef resp_t;

struct config {
    uint32_t max_ver;
    uint32_t min_ver;
    uint32_t encrypt;
    uint32_t allow_reconnect;
    size_t buf_size;
} typedef config_t;

static config_t conf;
static char *last;

/**
 * Attempt to read a fixed number of bytes, timeout after 2 seconds
 *
 * @param fd File descriptor to read from.
 * @param buf Buffer to write read bytes to.
 * @param s Maximum number of bytes to read
 * @return Number of bytes read 
 */
static size_t readall_timeout(int fd, char *buf, size_t s) {
    fd_set readfds;
    int numready = 0;
    struct timeval timeout = {ROAMTIMEOUT, 0};
    size_t i, res, recvd = 0;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    for (i=0; i < s; i+=recvd) {
        res = fdwait(fd+1, &readfds, NULL, &timeout, &numready);
        if (!res && numready) {
            if (receive(fd, buf+i, s-i, &recvd) || recvd == 0)
                DIE(READFAIL);
        } else {
            break;
        }
    }

    return i;
}

/**
 * Attempt to read a fixed number of bytes and decrypt
 *
 * @param fd File descriptor to read from.
 * @param buf Buffer to write read bytes to.
 * @param s Maximum number of bytes to read
 * @return Number of bytes read 
 */
static size_t ereadall(int fd, char *buf, size_t s) {
    size_t i = 0;
    uint32_t *buf32 = (uint32_t*)buf;

    if ((s % 4) != 0) {
        debug("Encrypted recv must be 4 byte aligned!\n");
        DIE(READFAIL);
    }

    if (s != (i = readall_timeout(fd, buf, s))) {
        debug("readall failed, returns @h\n", i);
        return i;
    }

    for (i = 0; i < s/4; i++) {
        uint32_t tmp;
        tmp = getshifty();
        buf32[i] ^= tmp;
    }
    return s;
}

/**
 * Attempt to encrypt then send a fixed number of bytes
 *
 * @param fd File descriptor to write to
 * @param buf Buffer to read bytes from
 * @param s Number of bytes to send
 * @return Number of bytes sent.
 */
static size_t esendall(int fd, char *buf, size_t s) {
    int i;
    uint32_t *buf32 = (uint32_t*)buf;
    size_t res;

    if ((s % sizeof(uint32_t)) != 0) {
        debug("Encrypted sends must be 4 byte aligned!\n");
        DIE(WRITEFAIL);
    }

    for (i = 0; i < s/sizeof(uint32_t); i++)
        buf32[i] ^= getshifty();

    res = sendall(fd, buf, s);

    if (s != res)
        DIE(WRITEFAIL);
    
    return s;
}

/**
 * Handle a mkdir request
 *
 * @param msg client message data
 * @return Response data, NULL on allocation error
 */
resp_t *do_mkdir(msg_t *msg) {
    resp_t *resp = calloc(sizeof(resp_t));

    if (!resp) {
        debug("Failed to allocate response.\n");
        return NULL;
    }

    if (!add_dir(msg->buf)) {
        resp->type = MKDIR_OK;
        memset(resp->buf, 0, sizeof(resp->buf));
    } else {
        debug("Adding directory failed.\n");
        resp->type = MKDIR_FAIL;
    }

    return resp;
}

/**
 * Handle a list request
 *
 * @param msg client message data
 * @return Response data, NULL on allocation error
 */
resp_t *do_list(msg_t *msg) {
    char *dirlist;
    resp_t *resp = calloc(sizeof(resp_t));

    debug("Attempting to list directory...\n");

    if (!resp) {
        debug("Failed to allocate response.\n");
        return NULL;
    }

    dirlist = ls_dir(msg->buf);

    if (!dirlist) {
        debug("Listing directory failed.\n");
        resp->type = LIST_FAIL;
        return resp;
    }

    //truncate if too long
    if (strlen(dirlist) > MAX_FILE_SIZE)
        *(dirlist+MAX_FILE_SIZE) = '\0'; 
    strcpy(resp->buf, dirlist);

    resp->type = LIST_OK;

    free(dirlist);

    return resp;
}

/**
 * Handle a put request
 *
 * @param msg client message data
 * @return Response data, NULL on allocation error
 */
resp_t *do_put(msg_t *msg) {
    char *fn;
    char *data;
    size_t fnlen, datalen;

    debug("Attempting put...\n");

    resp_t *resp = calloc(sizeof(resp_t));

    if (!resp) {
        debug("Failed to allocate response.\n");
        return NULL;
    }

    fnlen = strlen(msg->buf);

    if (fnlen > MAX_FILENAME_SIZE) {
        debug("Filename too large.\n");
        resp->type = PUT_FAIL;
        return resp;
    }

    fn = malloc(fnlen+1);
    strcpy(fn, msg->buf);

    datalen = strlen(msg->buf+fnlen+1);
    
    if (datalen > MAX_FILE_SIZE) {
        debug("File data too large.\n");
        resp->type = PUT_FAIL;
        free(fn);
        return resp;
    }

    data = malloc(datalen+1);
    strcpy(data, msg->buf+fnlen+1);

    if (!add_file(fn, data)) {
        resp->type = PUT_OK;
    } else {
        debug("Put failed.\n");
        resp->type = PUT_FAIL;
    }

    free(fn);
    free(data);

    return resp;
}

/**
 * Handle a get request
 *
 * @param msg client message data
 * @return Response data, NULL on allocation error
 */
resp_t *do_get(msg_t *msg) {
    char *data;

    debug("Attempting to get file...\n");

    resp_t *resp = calloc(sizeof(resp_t));

    if (!resp) {
        debug("Failed to allocate response.\n");
        return NULL;
    }

    if (!(data = readfile(msg->buf))) {
        debug("Failed to read file.\n");
        resp->type = GET_FAIL;
        return resp;
    }

    resp->type = GET_OK;
    memcpy(resp->buf, data, sizeof(resp->buf));
    return resp;
}

/**
 * Handle a rm request
 *
 * @param msg client message data
 * @return Response data, NULL on allocation error
 */
resp_t *do_rm(msg_t *msg) {
    resp_t *resp = calloc(sizeof(resp_t));

    debug("Attempting to remove file...\n");

    if (!resp) {
        debug("Failed to allocate response.\n");
        return NULL;
    }

    if (!rm_file(msg->buf)) {
        resp->type = RM_OK;
        return resp;
    } else {
        debug("Failed to rm file.\n");
        resp->type = RM_FAIL;
        return resp;
    }

    memcpy(resp, msg, sizeof(resp_t));
    return resp;
}

/**
 * Handle a rmdir request
 *
 * @param msg client message data
 * @return Response data, NULL on allocation error
 */
resp_t *do_rmdir(msg_t *msg) {
    resp_t *resp = calloc(sizeof(resp_t));

    debug("Attempting to remove dir...\n");

    if (!resp) {
        debug("Failed to allocate response.\n");
        return NULL;
    }

    if (!rm_dir(msg->buf)) {
        resp->type = RMDIR_OK;
        return resp;
    } else {
        debug("Failed to rm dir.\n");
        resp->type = RMDIR_FAIL;
        return resp;
    }

    memcpy(resp, msg, sizeof(resp_t));
    return resp;
}

/**
 * Process the next incoming request
 *
 * @return status response
 */
status_t process_req() {
    msg_t *msg = malloc(sizeof(msg_t));
    resp_t *resp = NULL;

    if (!EREADDATA(*msg)) {
        debug("Disconnected!\n");
        return DISCON; 
    }

    msg->buf[sizeof(msg->buf)-1] = '\0';

    switch (msg->type) {
        case MKDIR:
            resp = do_mkdir(msg);
            break;
        case LIST:
            resp = do_list(msg);
            break;
        case PUT:
            resp = do_put(msg);
            break;
        case GET:
            resp = do_get(msg);
            break;
        case RM:
            resp = do_rm(msg);
            break;
        case RMDIR:
            resp = do_rmdir(msg);
            break;
        case QUIT:
            return EXIT;
        default:
            return ERR;
    }

    if (!resp)
        return ERR;

    ESENDDATA(*resp);

    if (last)
        free(last);

    last = (char *)resp;

    return OK;
}

/**
 * Main request handling loop
 *
 * @return 0 on success, err code on failure
 */
int go(void) {
    int i;
    int res;
    uint32_t tmp = 0;  
    uint32_t *seed;
    char *resend;
    size_t tosend;
    size_t offset;
    uint32_t *f;

    init_fs();
    debug("fs init complete\n");

    if (!READDATATIMEOUT(conf)) {
        debug("failed to recv conf\n");
        res = 0;
        SENDDATA(res); 
        return 3;
    }

    if (conf.min_ver > VERSION || conf.max_ver < VERSION) {
        debug("version mismatch\n");
        res = 0;
        SENDDATA(res); 
        return 5;
    }
    //send success ack
    res = 1;
    SENDDATA(res);

    //seed our PRNG
    //because of how it works, seeding with 0's == no encryption
    seed = (uint32_t*)(FLAG_PAGE + (8*sizeof(uint32_t)));

    f = malloc(8*sizeof(uint32_t));

    if (!f)
        return 1;

    memcpy(f, seed, 8*sizeof(uint32_t));

    if (!conf.encrypt)
        seed = calloc(8*sizeof(uint32_t));

    srand(seed);

    //inform client of seed
    for (i = 0; i < 8; i+=2) {
        if (conf.encrypt)
            tmp = f[i]^f[i+1];
        SENDDATA(tmp);
    }

    #ifdef PATCHED_1
    memset(f, '\0', 8*sizeof(uint32_t));
    #endif
    debug("flag data: @h\n",f);

    free(f);


    while (1) {
        res = process_req();
        if (res == ERR || res == EXIT) {
             break;
        } else if (res == DISCON && conf.allow_reconnect && last) {
            debug("disconnected, retrying\n");
            if (!READDATATIMEOUT(conf)) {
                debug("failed to recv conf\n");
                return 3;
            }

            if (!last)
                continue;

            debug("Allocating resend buffer of @h bytes.\n",conf.buf_size+sizeof(resp_t));
            #ifdef PATCHED_1
            resend = calloc(conf.buf_size+sizeof(resp_t));
            #else
            resend = malloc(conf.buf_size+sizeof(resp_t));
            #endif
            debug("resend data: @h\n",resend);

            if (!READDATA(offset)) {
                debug("failed to recv offset\n");
                return 4;
            }

            tosend = sizeof(resp_t)-offset;
            tosend = tosend > sizeof(resp_t) ? sizeof(resp_t) : tosend;

            if (offset > conf.buf_size || offset > sizeof(resp_t)
            #ifdef PATCHED_1
                    || tosend > (conf.buf_size+sizeof(resp_t))
            #endif
            ){
                debug("failed to validate offset.\n");
                return 1;
            } else {
                debug("copying last out\n");
                memcpy(resend, last+offset, sizeof(resp_t)-offset);
            }

            #ifdef PATCHED_1
            if (tosend != esendall(stdout, resend, tosend))
            #else
            if (tosend != esendall(stdout, resend, sizeof(resp_t)))
            #endif
                return 4;
            debug("Resent all, should be back!\n");

            free(resend);
            free(last);
            last = NULL;
        }
    }
    return 0;
}

/**
 * Calculate checksum of .text
 *
 * @return csum of the .text section
 */
uint32_t get_text_checksum() {
#if !(defined(PATCHED_1) || defined(DEBUG))
    char *cur = (char *) go; 
    uint32_t csum = 0; 

    //ensure our functions are still happy
    if (!((void*)go < (void*)longjmp))
        _terminate(2);

    //now lets calculate our checksum
    do {
        csum ^= *(uint32_t*)cur;
        cur += sizeof(uint32_t);
        //close enough :)
    } while (cur < (char *)longjmp);

    return csum;
#else
    uint32_t *flag = (uint32_t*)FLAG_PAGE;
    return 0x1337b33f ^ flag[0] ^ flag[1];
#endif
}

bool verify_integrity() {
/* Ensure our client is running a valid binary!
 * Send to server for validation! */

    uint32_t res = 0;

    #if !(defined(PATCHED_1) || defined(DEBUG))
    res = getshifty();
    #endif
    res ^= get_text_checksum();

    //verify that this is correct
    //in practice, the poll just refuses to respond if wrong
    printf("@h",res);
    if(!READDATA(res))
        return 0;
    return res;
}

int main() {
    if (verify_integrity())
        return go();
    else
        return 2;
}
