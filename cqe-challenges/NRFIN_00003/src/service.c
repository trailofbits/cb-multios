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

#include "service.h"

// Copy the URI from the recv buffer into a verb-specific buffer.
// Vulnerability resides here.
int copy_uri(char *buf_verb) {

    int ret = SUCCESS;
    int bytes_sent = -1;
    size_t pos_uri = -1;

    // Find our delimeter
    pos_uri = findchar(buf_recv, DELIM_URI);
    if (-1 == pos_uri || pos_uri > RECV_BUF_SZ-URI_BUF_SZ) { 
        SENDNULLTRUNC(ERR_INVALID_REQ, sizeof(ERR_INVALID_REQ), bytes_sent);
        return ERRNO_INVALID_REQ; 
    }

    // Pull out the URI
#ifndef PATCHED
    memcpy(
        (unsigned char *)buf_verb, 
        (unsigned char *)buf_recv+pos_uri+1, 
        URI_BUF_SZ+1); // VULN: off-by-one
#else
    memcpy(
        (unsigned char *)buf_verb, 
        (unsigned char *)(buf_recv+pos_uri+1), 
        URI_BUF_SZ);
#endif

    return ret;
}

// Check whether the user has any remaining credits.
int check_plebian(void) {

    if (*ptr_credits) { 
        *ptr_credits = *ptr_credits - 1;
        return SUCCESS; 
    }
    return ERRNO_INSUFFICIENT_FUNDS;
}

// Provided a filename, return a pointer to the file's contents.
char * get_file_contents(char *name) {

    int ret = SUCCESS;
    int bytes_sent = -1;
    size_t i = 0;

    for (i=0; i<num_files; i++) {
        if (!memcmp(name, files[i].name, FILE_BUF_SZ)) {
            return files[i].contents;
        }
    }

    // we didn't find the file
    SENDNULLTRUNC(ERR_FILE_NOT_FOUND, sizeof(ERR_FILE_NOT_FOUND), bytes_sent);
    return NULL;
}

// Provided a filename, send the file contents to the user.
int dump_file(char *name) {

    int ret = SUCCESS;
    int bytes_sent = -1;
    char *file_contents = NULL;

    if (NULL == (file_contents = get_file_contents(name))) {
        return ERRNO_FILE_NOT_FOUND;
    }

    SEND(file_contents, FILE_BUF_SZ, bytes_sent);
    return ret;
}

// Provided a filename, send the first HEAD_SZ bytes of contents to the user.
#define HEAD_SZ 4
int head_file(char *name) {

    int ret = SUCCESS;
    int bytes_sent = -1;
    char *file_contents = NULL;

    if (NULL == (file_contents = get_file_contents(name))) {
        return ERRNO_FILE_NOT_FOUND;
    }

    SEND(file_contents, HEAD_SZ, bytes_sent);
    return ret;
}

int list_files(void) {

    int ret = SUCCESS;
    size_t i = 0;
    int bytes_sent = -1;

    for (i=0; i<num_files; i++) {
        SEND(files[i].name, FILE_BUF_SZ, bytes_sent);
        SEND("\n", 1, bytes_sent);
    }

    return ret;
}

int dispatch_verb(void) {

    int ret = SUCCESS;
    int bytes_sent = -1;

    if (!memcmp(buf_recv, "TIP", sizeof("TIP"))) {

        if (SUCCESS != (ret = check_plebian())) { return ret; }
        if (SUCCESS != (ret = copy_uri(ptr_uri_tip))) { return ret; }
        if (SUCCESS != (ret = do_tip(ptr_uri_tip))) { return ret; }

    } else if (!memcmp(buf_recv, "STATUS", sizeof("STATUS"))) {

        if (SUCCESS != (ret = check_plebian())) { return ret; }
        if (SUCCESS != (ret = do_status())) { return ret; }

    } else if (!memcmp(buf_recv, "GIMME", sizeof("GIMME"))) {

        if (SUCCESS != (ret = check_plebian())) { return ret; }
        if (SUCCESS != (ret = copy_uri(ptr_uri_gimme))) { return ret; }
        if (SUCCESS != (ret = do_gimme(ptr_uri_gimme))) { return ret; }

    } else if (!memcmp(buf_recv, "LIST", sizeof("LIST"))) {

        if (SUCCESS != (ret = check_plebian())) { return ret; }
        if (SUCCESS != (ret = do_list())) { return ret; }

    } else if (!memcmp(buf_recv, "SMORE", sizeof("SMORE"))) {

        if (SUCCESS != (ret = copy_uri(ptr_uri_smore))) { return ret; }
        if (SUCCESS != (ret = do_smore(ptr_uri_smore))) { return ret; }

    } else if (!memcmp(buf_recv, "YOUUP", sizeof("YOUUP"))) {

        if (SUCCESS != (ret = do_youup())) { return ret; }

    } else if (!memcmp(buf_recv, "MOOCH", sizeof("MOOCH"))) {

        if (SUCCESS != (ret = copy_uri(ptr_uri_mooch))) { return ret; }
        if (SUCCESS != (ret = do_mooch(ptr_uri_mooch))) { return ret; }

    } else if (!memcmp(buf_recv, "SUP", sizeof("SUP"))) {

        if (SUCCESS != (ret = do_sup())) { return ret; }

    } else if (!memcmp(buf_recv, "AUTH", sizeof("AUTH"))) {

        if (SUCCESS != (ret = copy_uri(ptr_uri_auth))) { return ret; }
        if (SUCCESS != (ret = do_auth(ptr_uri_auth))) { return ret; }

    } else if (!memcmp(buf_recv, "QUIT", sizeof("QUIT"))) {

        QUIT();

    } else {

        SENDNULLTRUNC(ERR_INVALID_VERB, sizeof(ERR_INVALID_VERB), bytes_sent);
        ret = ERRNO_INVALID_VERB;

    }

    return ret;
}

// make fake files (names, contents) for querying
#define NUM_CHARS_ALPHA 26
#define NUM_CHARS_NUMERIC 10
int init_content() {

    int ret = SUCCESS;
    UINT8 rnd[RND_BUF_SZ];
    size_t rnd_bytes = 0;
    size_t i = 0;
    size_t j = 0;

    // determine number of files in the directory; range: [1, 255]
    while ((0 != random(rnd, 1, &rnd_bytes)) && (1 != rnd_bytes)) {}
    num_files = rnd[0];
    if (0 == num_files) { num_files = 1; } // yeah, this biases

    // allocate NX space for the fileentries
    ALLOC(sizeof(fileentry) * num_files, 0, (void **)&files, ret);
    if (SUCCESS != ret) { return ret; }

    // for each file, determine a 16-character (no NULL) ASCII name & contents
    for (i=0; i<num_files; i++) {
        while ((0 != random(rnd, FILE_BUF_SZ*2, &rnd_bytes)) && (FILE_BUF_SZ*2 != rnd_bytes)) {}

        // filename, limited to lowercase ASCII characters
        for (j=0; j < FILE_BUF_SZ; j++) {
            files[i].name[j] = (rnd[j] % NUM_CHARS_ALPHA) + 'a';
        }

        // file contents, limited to numbers
        for (j=0; j < FILE_BUF_SZ; j++) {
            files[i].contents[j] = 
                (rnd[j+FILE_BUF_SZ] % NUM_CHARS_NUMERIC) + '0';
        }
    }

    return ret;
}


int main(void) {

    int ret = SUCCESS;
    int bytes_sent = -1;
    UINT32 crash;

    // We emulate an end-of-stack / SIGSEGV by putting a pointer directly above
    // the TIP buffer.  Overflowing the TIP buffer with the correct value
    // should cause SIGSEGV.
    UINT32 *ptr_crash = &crash;

    // These are the (stack) buffers we intend to overflow
    // high addrs  /-----------------------------------\   end of stack
    //             |   *ptr_crash                      |
    //             |   FASTLANE TIP URI buff           |
    //             |   FASTLANE GIMME URI buff         |
    //             |   3 dummy bytes                   |
    //             |   # of FASTLANE credits (1 byte)  |
    //             |   SLOWLANE SMORE URI buff         |
    //             |   SLOWLANE MOOCH URI buff         |
    //             |   SLOWLANE AUTH buff              |
    // low addrs   \-----------------------------------/
    char uri_tip[URI_BUF_SZ] = {0};
    char uri_gimme[URI_BUF_SZ] = {0};
    UINT8 dummy[3] = {0};
    UINT8 credits = 0;
    char uri_smore[URI_BUF_SZ] = {0};
    char uri_mooch[URI_BUF_SZ] = {0};
    char uri_auth[URI_BUF_SZ] = {0};

    // easier referencing in child functions
    ptr_uri_tip = uri_tip;
    ptr_uri_gimme = uri_gimme;
    ptr_credits = &credits; 
    ptr_uri_smore = uri_smore;
    ptr_uri_mooch = uri_mooch;
    ptr_uri_auth = uri_auth;

    // set up the files
    if ((ret = init_content()) != SUCCESS) { 
        FATAL("fatal error during init_content()\n", ERRNO_UNK);
        return ret; 
    }

    while(1) {

        RECV(buf_recv, RECV_BUF_SZ, ret);

        if (ERRNO_INSUFFICIENT_FUNDS == (ret = dispatch_verb())) {
            SENDNULLTRUNC(
                ERR_INSUFFICIENT_FUNDS, 
                sizeof(ERR_INSUFFICIENT_FUNDS), 
                bytes_sent);
        }

        SENDNULLTRUNC(DELIM_EOF, sizeof(DELIM_EOF), bytes_sent);

        // This is where a crash _may_ occur.
        // Specifically, if TIP is overflown with \xfd, \xfe or \xff, this
        // write will go off the end of the stack (@ 0xbaaaafff).
        // This limited choice increases CRS difficulty.
        *ptr_crash = 0xdeadbeef;
    }
    
    // We should never get here.
    return ret;
}  

