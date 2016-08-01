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
#include <libc.h>
#include "list.h"
#include "challenges.h"


#define HUMANDETECTED "You call yourself a robot?"
#define NOTIMPLEMENTED "You want me to do *two* things?!"
#define INTERNALERR "If anyone asks, you're my debugger."
#define SUBMITOK "Oh, sure. Let the robot do all the work."
#define DELETEOK "Hopes: deleted."
#define WAYTOOBIG "Shut up, baby, I know it!"
#define LEHDR "PTTC"
#define BEHDR "CTTP"
#define MAX_PATH_SIZE 256
#define MAX_BODY_SIZE 1024*1024*2

#define LOGERR(req) if(dolog) logreq(req,ERR)
#define LOGWARN(req) if (dolog) logreq(req,WARN)
#define LOGINFO(req) if (dolog) logreq(req,INFO)
#define ISLE(resp) (memcmp(resp,LEHDR,4) == 0)
#define SWAP32(i) { i = (i<<24) | ((i<<8) & 0xff0000) | ((i>>8) & 0xff00) | ((i>>24)&0xff); }


typedef struct list list_t;
typedef struct list_node list_node_t;

enum LogCode {
    INFO = FLAG_PAGE,
    WARN,
    ERR
} typedef level_t;

enum Version {
    ONE = 0x10000000,
    TWO,
    THREE,
    FOUR
} typedef ver_t;

enum RequestType {
    RETRIEVE = 0x41414141,
    SUBMIT,
    CHECK,
    AUTH,
    DELETE,
    QUIT
} typedef rtype_t;

enum ResponseCode {
    OK = 0xbaaaaaaa,
    NOK,
    SOK,
    LOL
} typedef rcode_t;

struct cttpreq {
    char hdr[4];
    ver_t version;
    rtype_t type;
    size_t psize;
    size_t bodysize;
    char *path;
    char *body;
} typedef cttpreq_t;
    
struct cttpresp {
    char hdr[4];
    rcode_t code;
    size_t rsize;
    char *data;
} typedef cttpresp_t;

struct fileinfo {
    size_t psize;
    size_t bodysize;
    char *path;
    char *body;
} typedef fileinfo_t;

struct logmsg {
   level_t level;
   cttpreq_t *req;
} typedef logmsg_t;

static bool verified;
static bool dolog;
static list_t files;
static list_t loglist;

static cttpresp_t *internalerror();
bool do_challenge();

/**
 * Log a received requests
 *
 * @param req Original request
 * @param level Error level
 */
static void logreq(cttpreq_t *req, int level) {
    char *path, *body;
    list_node_t *node;
    logmsg_t *info;
    cttpreq_t *lreq = calloc(sizeof(cttpreq_t));

    if (!req) {
        debug("Passed null req\n");
        return;
    }
    
    if (!lreq) {
        debug("Failed to allocate log\n");
        return;
    }

    memcpy(lreq, req, sizeof(cttpreq_t));

    if (lreq->path && lreq->psize) {
        lreq->path = calloc(lreq->psize);

        if (!lreq->path) {
            debug("Failed to allocate path\n");
            return;
        }

        memcpy(lreq->path, req->path, lreq->psize);
    }

    if (lreq->body && lreq->bodysize) {
        lreq->body = calloc(lreq->bodysize);

        if (!lreq->body) {
            debug("Failed to allocate body\n");
            return;
        }
        
        memcpy(lreq->body, req->body, lreq->bodysize);
    }

    info = calloc(sizeof(logmsg_t));

    if (!info) {
        debug("Failed to allocate log entry\n");
        return;
    }

    info->req = lreq;
    info->level = level;

    node = calloc(sizeof(list_node_t));

    if (!node) {
        debug("Failed to allocate node\n");
        return;
    }

    node->data = info;

    list_push_back(&loglist, node);
}

/**
 * Get file from list
 *
 * @param path Requested path
 * @param psize Size of requested path
 * 
 * @return fileinfo_t struct of file
 */
static fileinfo_t *get_file(char *path, size_t psize) {
    list_node_t *cur, *n;
    fileinfo_t *f = NULL;

    if (!path)
        goto out;

    list_for_each_safe(&files, n, cur) {
        f = (fileinfo_t*)cur->data;
        if (!memcmp(path, f->path, psize < f->psize ? psize : f->psize)) {
            break;
        }
    }

    if (cur == NULL)
        return NULL;

out:
    return f;
}

/**
 * Add file to list
 *
 * @param file File to add
 * 
 * @return true on success, false on fail
 */
static bool add_file(fileinfo_t *file) {
    list_node_t *node = calloc(sizeof(list_node_t));

    if (!node) {
        return false;
    }

    if (get_file(file->path, file->psize)) {
        return false;
    }

    node->data = file;

    list_push_back(&files, node);

    return true;
}

/**
 * Delete file from list
 *
 * @param path Path to delete
 * @param psize Size of path
 * 
 * @return true on success, false on fail
 */
static bool delete_file(char *path, size_t psize) {
    list_node_t *cur, *n;
    fileinfo_t *f = NULL;

    if (!path) {
        return false;
    }

    list_for_each_safe(&files, n, cur) {
        f = (fileinfo_t*)cur->data;
        if (!memcmp(path, f->path, psize < f->psize ? psize : f->psize)) {
            break;
        }
    }

    if (cur) {
        list_remove(&files, cur);
        return true;
    } else {
        return false;
    }
}

/**
 * Construct a response message
 *
 * @param code Response code
 * @param msg Body of response
 * @param s Size of body
 * 
 * @return a response structure
 */
static cttpresp_t *genericmsg(rcode_t code, const char *msg, size_t s) {
    cttpresp_t  *resp = calloc(sizeof(cttpresp_t));

    if (!resp) {
        debug("Failed to allocate resp");
        return internalerror();
    }

    resp->data = calloc(s);
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        return internalerror();
    }

    strcpy(resp->data, msg);
    resp->rsize = strlen(resp->data)+1;
    resp->code = code;
    return resp;
}

/**
 * Construct an internal error response
 *
 * @return response struct
 */
static cttpresp_t *internalerror() {
    return genericmsg(NOK, INTERNALERR, sizeof(INTERNALERR));
}

/**
 * Construct a not implemented response
 *
 * @return response struct
 */
static cttpresp_t *notimplemented() {
    return genericmsg(LOL, NOTIMPLEMENTED, sizeof(NOTIMPLEMENTED));
}

/**
 * Handle a retrieve request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_retrieve(cttpreq_t *req) {
    cttpresp_t  *resp = calloc(sizeof(cttpresp_t));
    fileinfo_t *file; 

    if (!resp) {
        debug("Failed to allocate resp.\n");
        goto out;
    }

    if (!req) {
        debug("Passed null req\n");
        goto out_free;
    }

    file = get_file(req->path, req->psize);

    if (!file) {
        debug("Failed to find file.\n");
        goto out_free;
    }

    resp->data = calloc(file->bodysize);
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        goto out_free;
    }

    memcpy(resp->data, file->body, file->bodysize);
    resp->rsize = file->bodysize;
    resp->code = OK;

    LOGINFO(req);
    return resp;

out_free:
    free(resp);
out:
    if (req)
        LOGERR(req);
    return internalerror();
}

/**
 * Handle a submit request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_submit(cttpreq_t *req) {
    fileinfo_t *file; 

    if (!req) {
        debug("Passed null req\n");
        goto out;
    }

    file = calloc(sizeof(fileinfo_t));

    if (!file) {
        debug("Failed to alloc file.\n");
        goto out;
    }

    file->path = calloc(req->psize);

    if (!file->path) {
        debug("Failed too alloc path.\n");
        goto out_free_file;
    }

    file->body = calloc(req->bodysize);

    if (!file->body) {
        debug("Failed to alloc body.\n");
        goto out_free_path;
    }


    file->psize = req->psize;
    file->bodysize = req->bodysize;

    memcpy(file->path, req->path, req->psize);
    memcpy(file->body, req->body, req->bodysize);

    if (add_file(file)) {
        LOGINFO(req);
        return genericmsg(OK, SUBMITOK, sizeof(SUBMITOK));
    }

out_free_body:
    free(file->body);
out_free_path:
    free(file->path);
out_free_file:
    free(file);
out:
    if (req)
        LOGERR(req);
    return internalerror();
}

/**
 * Handle a check request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_check(cttpreq_t *req) {
    cttpresp_t  *resp = calloc(sizeof(cttpresp_t));
    fileinfo_t *file; 

    if (!resp) {
        debug("Failed to allocate resp.\n");
        goto out;
    }

    if (!req) {
        debug("Passed null req\n");
        goto out_free;
    }

    debug("in handle check\n");

    file = get_file(req->path, req->psize);

    if (!file) {
        debug("Failed to find file.\n");
        goto out_free;
    }

    resp->data = calloc(sizeof(size_t));
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        goto out_free;
    }

    debug("found file\n");
    memcpy(resp->data, &file->bodysize, sizeof(size_t));

    resp->rsize = sizeof(size_t);
    resp->code = OK;

    LOGINFO(req);
    return resp;

out_free:
    free(resp);
out:
    if (req)
        LOGERR(req);
    return internalerror();
}

/**
 * Handle a delete request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_delete(cttpreq_t *req) {
    fileinfo_t *file; 

    if (!req) {
        debug("Passed null req\n");
        goto out;
    }

    if (delete_file(req->path, req->psize)) { 
        LOGINFO(req);
        return genericmsg(OK, DELETEOK, sizeof(DELETEOK));
    }

out:
    if (req)
        LOGERR(req);
    return internalerror();
}

/**
 * Handle an auth request
 *
 * @param req Original request
 *
 * @return response struct
 */
STACKPROTECTINIT
static cttpresp_t *handle_auth(cttpreq_t *req) {
    STACKPROTECTADD
    size_t s;
#ifndef PATCHED_2
    char tmpbuf[4096];
#endif
    int i;
    char key;
    cttpresp_t  *resp = calloc(sizeof(cttpresp_t));
    fileinfo_t *file; 

    if (!do_challenge()) {
        debug("Failed to auth!\n");
        goto out;
    }

    if (!resp) {
        debug("Failed to allocate resp.\n");
        goto out;
    }

    if (!req) {
        debug("Passed null req\n");
        goto out_free;
    }

    file = get_file(req->path, req->psize);

    if (!file) {
        debug("Failed to find file.\n");
        goto out_free;
    }
    
    s = file->bodysize;
    resp->data = calloc(s);
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        goto out_free;
    }

#ifndef PATCHED_2
    memcpy(tmpbuf, file->body, s);
    key = randint();
    for (i=0; i < s; i++)
        *(resp->data+i) = tmpbuf[i] ^ key;
#else
    memcpy(resp->data, file->body, s);
    key = randint();
    for (i=0; i < s; i++)
        *(resp->data+i) ^= key;
#endif
    resp->rsize = s;
    resp->code = OK;

    LOGINFO(req);
    STACKPROTECTCHK
    return resp;

out_free:
    free(resp);
out:
    if (req)
        LOGERR(req);
    STACKPROTECTCHK
    return internalerror();
}

/**
 * Handle a v1 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_v1(cttpreq_t *req) {
    debug("Got v1 req\n");
    //just simple stuff
    if (!req) {
        debug("Passed null request\n");
        return internalerror();
    }
    switch (req->type) {
        case RETRIEVE:
            return handle_retrieve(req);
        case SUBMIT:
            return handle_submit(req);
        default:
            LOGERR(req);
            return notimplemented();
    }
}

/**
 * Handle a v2 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_v2(cttpreq_t *req) {
    debug("Got v2 req\n");
    //some new features!
    if (!req) {
        debug("Passed null request\n");
        return internalerror();
    }

    switch (req->type) {
        case RETRIEVE:
            return handle_retrieve(req);
        case SUBMIT:
            return handle_submit(req);
        case CHECK:
            return handle_check(req);
        case DELETE:
            return handle_delete(req);
        default: 
            LOGERR(req);
            return notimplemented();
    }
}

/**
 * Handle a v3 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_v3(cttpreq_t *req) {
    debug("Got v3 req\n");
    //we now support the robotic transport security protocol!
    if (!req) {
        debug("Passed null request\n");
        return internalerror();
    }

    switch (req->type) {
        case RETRIEVE:
            return handle_retrieve(req);
        case SUBMIT:
            return handle_submit(req);
        case CHECK:
            return handle_check(req);
        case DELETE:
            return handle_delete(req);
        case AUTH:
            return handle_auth(req);
        default:
            LOGERR(req);
            return notimplemented();
    }
}

/**
 * Handle a v4 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *handle_v4(cttpreq_t *req) {
    debug("Got v4 req\n");
    LOGERR(req);
    return notimplemented();
}

/**
 * Do silly captcha challenge. Randomly selected challenge, xor'd with
 * single byte key derived from flag page, along with a 4 byte token.
 *
 * @return true if a robot, false if a human
 */
bool do_challenge() {
    int i;
    size_t clen;
    char *encoded, *decoded;
    bool res;
    char *challenge = challenges[randint()%(sizeof(challenges)/sizeof(challenges[0]))];
    char key = (randint()^randint()) % 256;
    uint32_t token = randint();
    uint32_t etoken = token;
    uint32_t dtoken;

    clen = strlen(challenge);

    encoded = calloc(clen+1);

    decoded = calloc(clen+1);

    if (!encoded || !decoded) {
        debug("Failed to allocate encode/decode buffers.\n");
        return false;
    }

    for (i = 0; i < clen; i++) {
        encoded[i] = key ^ challenge[i];
    }

    for (i = 0; i < sizeof(token); i++) {
        *(((char *)&etoken)+i) ^= key;
    }

    SSEND(sizeof(key), (char*)&key);

    SSEND(sizeof(clen), (char*)&clen);

    SSEND(clen, encoded);

    SSEND(sizeof(etoken), (char*)&etoken);
    
    debug("grab decoded\n");
    RECV(clen, decoded);
    debug("grabbed,now dtok\n");

    RECV(sizeof(dtoken), (char*)&dtoken);
    debug("grabbed all\n");

    res = (memcmp(challenge, decoded, clen) == 0) && (token == (dtoken^0x127a1b76));

    free(encoded);
    free(decoded);

    return res;
}

/**
 * Handle an incoming request.
 *
 * @return true if processing should continue, false if it should stop
 */
bool handle_request() {
    cttpreq_t req = {0};
    cttpresp_t *resp;

    dolog = 1;

    if (READDATA(req)) {
        debug("Failed to recv request.\n");
        _terminate(3);
    }

#ifdef PATCHED_1
    //this patch is silly, but means protocol stays same between patched/unpatched
    req.path = NULL;
    req.body = NULL;
#endif

    if (!ISLE(&req)) {
        SWAP32(req.version);
        SWAP32(req.type);
        SWAP32(req.psize);
        SWAP32(req.bodysize);
    }

    if (req.type == QUIT) {
        SSEND(4, "done");
        return false;
    }

    if (req.psize > MAX_PATH_SIZE || req.bodysize > MAX_BODY_SIZE) {
        resp = calloc(sizeof(cttpresp_t));
        

        if (!resp) {
            debug("Failed to allocate resp.\n");
            _terminate(1);
        }

        resp->data = calloc(sizeof(WAYTOOBIG));
        
        if (!resp->data) {
            debug("Failed to allocate resp data.\n");
            _terminate(1);
        }

        strcpy(resp->data, WAYTOOBIG);
        resp->rsize = strlen(resp->data)+1;
        resp->code = NOK;

        LOGERR(&req);
    } else {
        //NO HUMANS ALLOWED
        if (!verified && !do_challenge()) {
            LOGERR(&req);
            return false;
        }

        verified = true;

        if (req.psize > 0) {
            int res = 0;
            req.path = calloc(req.psize);

            if (!req.path) {
                debug("Failed to allocate path.\n");
                _terminate(4);
            }

            RECV(req.psize, req.path);
        }

        if (req.bodysize > 0) {
            req.body = calloc(req.bodysize);

            if (!req.body) {
                debug("Failed to allocate body.\n");
                _terminate(5);
            }

            RECV(req.bodysize, req.body);
        }


        switch (req.version) {
            case ONE:
                resp = handle_v1(&req);
                break;
            case TWO:
                resp = handle_v2(&req);
                break;
            case THREE:
                resp = handle_v3(&req);
                break;
            case FOUR:
                resp = handle_v4(&req);
                break;
            default:
                LOGERR(&req);
                resp = notimplemented();
        }
    }

    if (resp) {
        size_t osize = resp->rsize;
        if(ISLE(&req)) {
            memcpy(resp->hdr, LEHDR, sizeof(resp->hdr));
        } else {
            memcpy(resp->hdr, BEHDR, sizeof(resp->hdr));
            SWAP32(resp->rsize);
            SWAP32(resp->code);
        }

        SSEND(sizeof(*resp)-sizeof(resp->data), (char*)resp);
        SSEND(osize, resp->data);
        
        if (req.path) {
            debug("freeing path\n");
            free(req.path);
        }

        if (req.body) {
            debug("freeing body\n");
            free(req.body);
        }

        if (resp->data) {
            debug("freeing resp data\n");
            free(resp->data);
        }

        debug("freeing resp\n");
        free(resp);
        

        return true;
    } else {
        return false;
    }
}

/**
 * Print out all our requests. All stats calculations are left up to the users,
 * who, as robots, enjoy that sort of thing.
 */
void print_stats() {
    list_node_t *cur, *n;
    logmsg_t* msg = NULL;

    list_for_each_safe(&loglist, n, cur) {
        msg = (logmsg_t*) cur->data;
        if (msg->req->path && msg->req->psize) {
            SSEND(sizeof(msg->level), (char*)&msg->level);
            SSEND(msg->req->psize, msg->req->path);
        }
    }
}
