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
#include "cgc_list.h"
#include "cgc_challenges.h"


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

#define LOGERR(req) if(dolog) cgc_logreq(req,ERR)
#define LOGWARN(req) if (dolog) logreq(req,WARN)
#define LOGINFO(req) if (dolog) cgc_logreq(req,INFO)
#define ISLE(resp) (cgc_memcmp(resp,LEHDR,4) == 0)
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
    cgc_size_t psize;
    cgc_size_t bodysize;
    char *path;
    char *body;
} typedef cttpreq_t;
    
struct cttpresp {
    char hdr[4];
    rcode_t code;
    cgc_size_t rsize;
    char *data;
} typedef cttpresp_t;

struct fileinfo {
    cgc_size_t psize;
    cgc_size_t bodysize;
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

static cttpresp_t *cgc_internalerror();
bool cgc_do_challenge();

/**
 * Log a received requests
 *
 * @param req Original request
 * @param level Error level
 */
static void cgc_logreq(cttpreq_t *req, int level) {
    char *path, *body;
    list_node_t *node;
    logmsg_t *info;
    cttpreq_t *lreq = cgc_calloc(sizeof(cttpreq_t));

    if (!req) {
        debug("Passed null req\n");
        return;
    }
    
    if (!lreq) {
        debug("Failed to allocate log\n");
        return;
    }

    cgc_memcpy(lreq, req, sizeof(cttpreq_t));

    if (lreq->path && lreq->psize) {
        lreq->path = cgc_calloc(lreq->psize);

        if (!lreq->path) {
            debug("Failed to allocate path\n");
            return;
        }

        cgc_memcpy(lreq->path, req->path, lreq->psize);
    }

    if (lreq->body && lreq->bodysize) {
        lreq->body = cgc_calloc(lreq->bodysize);

        if (!lreq->body) {
            debug("Failed to allocate body\n");
            return;
        }
        
        cgc_memcpy(lreq->body, req->body, lreq->bodysize);
    }

    info = cgc_calloc(sizeof(logmsg_t));

    if (!info) {
        debug("Failed to allocate log entry\n");
        return;
    }

    info->req = lreq;
    info->level = level;

    node = cgc_calloc(sizeof(list_node_t));

    if (!node) {
        debug("Failed to allocate node\n");
        return;
    }

    node->data = info;

    cgc_list_push_back(&loglist, node);
}

/**
 * Get file from list
 *
 * @param path Requested path
 * @param psize Size of requested path
 * 
 * @return fileinfo_t struct of file
 */
static fileinfo_t *cgc_get_file(char *path, cgc_size_t psize) {
    list_node_t *cur, *n;
    fileinfo_t *f = NULL;

    if (!path)
        goto out;

    list_for_each_safe(&files, n, cur) {
        f = (fileinfo_t*)cur->data;
        if (!cgc_memcmp(path, f->path, psize < f->psize ? psize : f->psize)) {
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
static bool cgc_add_file(fileinfo_t *file) {
    list_node_t *node = cgc_calloc(sizeof(list_node_t));

    if (!node) {
        return false;
    }

    if (cgc_get_file(file->path, file->psize)) {
        return false;
    }

    node->data = file;

    cgc_list_push_back(&files, node);

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
static bool cgc_delete_file(char *path, cgc_size_t psize) {
    list_node_t *cur, *n;
    fileinfo_t *f = NULL;

    if (!path) {
        return false;
    }

    list_for_each_safe(&files, n, cur) {
        f = (fileinfo_t*)cur->data;
        if (!cgc_memcmp(path, f->path, psize < f->psize ? psize : f->psize)) {
            break;
        }
    }

    if (cur) {
        cgc_list_remove(&files, cur);
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
static cttpresp_t *cgc_genericmsg(rcode_t code, const char *msg, cgc_size_t s) {
    cttpresp_t  *resp = cgc_calloc(sizeof(cttpresp_t));

    if (!resp) {
        debug("Failed to allocate resp");
        return cgc_internalerror();
    }

    resp->data = cgc_calloc(s);
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        return cgc_internalerror();
    }

    cgc_strcpy(resp->data, msg);
    resp->rsize = cgc_strlen(resp->data)+1;
    resp->code = code;
    return resp;
}

/**
 * Construct an internal error response
 *
 * @return response struct
 */
static cttpresp_t *cgc_internalerror() {
    return cgc_genericmsg(NOK, INTERNALERR, sizeof(INTERNALERR));
}

/**
 * Construct a not implemented response
 *
 * @return response struct
 */
static cttpresp_t *cgc_notimplemented() {
    return cgc_genericmsg(LOL, NOTIMPLEMENTED, sizeof(NOTIMPLEMENTED));
}

/**
 * Handle a retrieve request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_retrieve(cttpreq_t *req) {
    cttpresp_t  *resp = cgc_calloc(sizeof(cttpresp_t));
    fileinfo_t *file; 

    if (!resp) {
        debug("Failed to allocate resp.\n");
        goto out;
    }

    if (!req) {
        debug("Passed null req\n");
        goto out_free;
    }

    file = cgc_get_file(req->path, req->psize);

    if (!file) {
        debug("Failed to find file.\n");
        goto out_free;
    }

    resp->data = cgc_calloc(file->bodysize);
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        goto out_free;
    }

    cgc_memcpy(resp->data, file->body, file->bodysize);
    resp->rsize = file->bodysize;
    resp->code = OK;

    LOGINFO(req);
    return resp;

out_free:
    cgc_free(resp);
out:
    if (req)
        LOGERR(req);
    return cgc_internalerror();
}

/**
 * Handle a submit request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_submit(cttpreq_t *req) {
    fileinfo_t *file; 

    if (!req) {
        debug("Passed null req\n");
        goto out;
    }

    file = cgc_calloc(sizeof(fileinfo_t));

    if (!file) {
        debug("Failed to alloc file.\n");
        goto out;
    }

    file->path = cgc_calloc(req->psize);

    if (!file->path) {
        debug("Failed too alloc path.\n");
        goto out_free_file;
    }

    file->body = cgc_calloc(req->bodysize);

    if (!file->body) {
        debug("Failed to alloc body.\n");
        goto out_free_path;
    }


    file->psize = req->psize;
    file->bodysize = req->bodysize;

    cgc_memcpy(file->path, req->path, req->psize);
    cgc_memcpy(file->body, req->body, req->bodysize);

    if (cgc_add_file(file)) {
        LOGINFO(req);
        return cgc_genericmsg(OK, SUBMITOK, sizeof(SUBMITOK));
    }

out_free_body:
    cgc_free(file->body);
out_free_path:
    cgc_free(file->path);
out_free_file:
    cgc_free(file);
out:
    if (req)
        LOGERR(req);
    return cgc_internalerror();
}

/**
 * Handle a check request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_check(cttpreq_t *req) {
    cttpresp_t  *resp = cgc_calloc(sizeof(cttpresp_t));
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

    file = cgc_get_file(req->path, req->psize);

    if (!file) {
        debug("Failed to find file.\n");
        goto out_free;
    }

    resp->data = cgc_calloc(sizeof(cgc_size_t));
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        goto out_free;
    }

    debug("found file\n");
    cgc_memcpy(resp->data, &file->bodysize, sizeof(cgc_size_t));

    resp->rsize = sizeof(cgc_size_t);
    resp->code = OK;

    LOGINFO(req);
    return resp;

out_free:
    cgc_free(resp);
out:
    if (req)
        LOGERR(req);
    return cgc_internalerror();
}

/**
 * Handle a delete request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_delete(cttpreq_t *req) {
    fileinfo_t *file; 

    if (!req) {
        debug("Passed null req\n");
        goto out;
    }

    if (cgc_delete_file(req->path, req->psize)) { 
        LOGINFO(req);
        return cgc_genericmsg(OK, DELETEOK, sizeof(DELETEOK));
    }

out:
    if (req)
        LOGERR(req);
    return cgc_internalerror();
}

/**
 * Handle an auth request
 *
 * @param req Original request
 *
 * @return response struct
 */
STACKPROTECTINIT
static cttpresp_t *cgc_handle_auth(cttpreq_t *req) {
    STACKPROTECTADD
    cgc_size_t s;
#ifndef PATCHED_2
    char tmpbuf[4096];
#endif
    int i;
    char key;
    cttpresp_t  *resp = cgc_calloc(sizeof(cttpresp_t));
    fileinfo_t *file; 

    if (!cgc_do_challenge()) {
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

    file = cgc_get_file(req->path, req->psize);

    if (!file) {
        debug("Failed to find file.\n");
        goto out_free;
    }
    
    s = file->bodysize;
    resp->data = cgc_calloc(s);
    
    if (!resp->data) {
        debug("Failed to allocate resp data");
        goto out_free;
    }

#ifndef PATCHED_2
    cgc_memcpy(tmpbuf, file->body, s);
    key = cgc_randint();
    for (i=0; i < s; i++)
        *(resp->data+i) = tmpbuf[i] ^ key;
#else
    cgc_memcpy(resp->data, file->body, s);
    key = cgc_randint();
    for (i=0; i < s; i++)
        *(resp->data+i) ^= key;
#endif
    resp->rsize = s;
    resp->code = OK;

    LOGINFO(req);
    STACKPROTECTCHK
    return resp;

out_free:
    cgc_free(resp);
out:
    if (req)
        LOGERR(req);
    STACKPROTECTCHK
    return cgc_internalerror();
}

/**
 * Handle a v1 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_v1(cttpreq_t *req) {
    debug("Got v1 req\n");
    //just simple stuff
    if (!req) {
        debug("Passed null request\n");
        return cgc_internalerror();
    }
    switch (req->type) {
        case RETRIEVE:
            return cgc_handle_retrieve(req);
        case SUBMIT:
            return cgc_handle_submit(req);
        default:
            LOGERR(req);
            return cgc_notimplemented();
    }
}

/**
 * Handle a v2 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_v2(cttpreq_t *req) {
    debug("Got v2 req\n");
    //some new features!
    if (!req) {
        debug("Passed null request\n");
        return cgc_internalerror();
    }

    switch (req->type) {
        case RETRIEVE:
            return cgc_handle_retrieve(req);
        case SUBMIT:
            return cgc_handle_submit(req);
        case CHECK:
            return cgc_handle_check(req);
        case DELETE:
            return cgc_handle_delete(req);
        default: 
            LOGERR(req);
            return cgc_notimplemented();
    }
}

/**
 * Handle a v3 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_v3(cttpreq_t *req) {
    debug("Got v3 req\n");
    //we now support the robotic transport security protocol!
    if (!req) {
        debug("Passed null request\n");
        return cgc_internalerror();
    }

    switch (req->type) {
        case RETRIEVE:
            return cgc_handle_retrieve(req);
        case SUBMIT:
            return cgc_handle_submit(req);
        case CHECK:
            return cgc_handle_check(req);
        case DELETE:
            return cgc_handle_delete(req);
        case AUTH:
            return cgc_handle_auth(req);
        default:
            LOGERR(req);
            return cgc_notimplemented();
    }
}

/**
 * Handle a v4 request
 *
 * @param req Original request
 *
 * @return response struct
 */
static cttpresp_t *cgc_handle_v4(cttpreq_t *req) {
    debug("Got v4 req\n");
    LOGERR(req);
    return cgc_notimplemented();
}

/**
 * Do silly captcha challenge. Randomly selected challenge, xor'd with
 * single byte key derived from flag page, along with a 4 byte token.
 *
 * @return true if a robot, false if a human
 */
bool cgc_do_challenge() {
    int i;
    cgc_size_t clen;
    char *encoded, *decoded;
    bool res;
    char *challenge = challenges[cgc_randint()%(sizeof(challenges)/sizeof(challenges[0]))];
    char key = (cgc_randint()^cgc_randint()) % 256;
    uint32_t token = cgc_randint();
    uint32_t etoken = token;
    uint32_t dtoken;

    clen = cgc_strlen(challenge);

    encoded = cgc_calloc(clen+1);

    decoded = cgc_calloc(clen+1);

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

    res = (cgc_memcmp(challenge, decoded, clen) == 0) && (token == (dtoken^0x127a1b76));

    cgc_free(encoded);
    cgc_free(decoded);

    return res;
}

/**
 * Handle an incoming request.
 *
 * @return true if processing should continue, false if it should stop
 */
bool cgc_handle_request() {
    cttpreq_t req = {0};
    cttpresp_t *resp;

    dolog = 1;

    if (READDATA(req)) {
        debug("Failed to recv request.\n");
        cgc__terminate(3);
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
        resp = cgc_calloc(sizeof(cttpresp_t));
        

        if (!resp) {
            debug("Failed to allocate resp.\n");
            cgc__terminate(1);
        }

        resp->data = cgc_calloc(sizeof(WAYTOOBIG));
        
        if (!resp->data) {
            debug("Failed to allocate resp data.\n");
            cgc__terminate(1);
        }

        cgc_strcpy(resp->data, WAYTOOBIG);
        resp->rsize = cgc_strlen(resp->data)+1;
        resp->code = NOK;

        LOGERR(&req);
    } else {
        //NO HUMANS ALLOWED
        if (!verified && !cgc_do_challenge()) {
            LOGERR(&req);
            return false;
        }

        verified = true;

        if (req.psize > 0) {
            int res = 0;
            req.path = cgc_calloc(req.psize);

            if (!req.path) {
                debug("Failed to allocate path.\n");
                cgc__terminate(4);
            }

            RECV(req.psize, req.path);
        }

        if (req.bodysize > 0) {
            req.body = cgc_calloc(req.bodysize);

            if (!req.body) {
                debug("Failed to allocate body.\n");
                cgc__terminate(5);
            }

            RECV(req.bodysize, req.body);
        }


        switch (req.version) {
            case ONE:
                resp = cgc_handle_v1(&req);
                break;
            case TWO:
                resp = cgc_handle_v2(&req);
                break;
            case THREE:
                resp = cgc_handle_v3(&req);
                break;
            case FOUR:
                resp = cgc_handle_v4(&req);
                break;
            default:
                LOGERR(&req);
                resp = cgc_notimplemented();
        }
    }

    if (resp) {
        cgc_size_t osize = resp->rsize;
        if(ISLE(&req)) {
            cgc_memcpy(resp->hdr, LEHDR, sizeof(resp->hdr));
        } else {
            cgc_memcpy(resp->hdr, BEHDR, sizeof(resp->hdr));
            SWAP32(resp->rsize);
            SWAP32(resp->code);
        }

        SSEND(sizeof(*resp)-sizeof(resp->data), (char*)resp);
        SSEND(osize, resp->data);
        
        if (req.path) {
            debug("freeing path\n");
            cgc_free(req.path);
        }

        if (req.body) {
            debug("freeing body\n");
            cgc_free(req.body);
        }

        if (resp->data) {
            debug("freeing resp data\n");
            cgc_free(resp->data);
        }

        debug("freeing resp\n");
        cgc_free(resp);
        

        return true;
    } else {
        return false;
    }
}

/**
 * Print out all our requests. All stats calculations are left up to the users,
 * who, as robots, enjoy that sort of thing.
 */
void cgc_print_stats() {
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
