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
 
#include "verbs.h"

#define BANNER_TIP "Just the Tip!\n" \
                   "-------------\n"
int do_tip(char *uri) {
    
    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_TIP, sizeof(BANNER_TIP), bytes_sent);
    if (sizeof(BANNER_TIP) != bytes_sent) { return ERRNO_SEND; }

    if ((ret = head_file(uri)) != SUCCESS) { return ret; }

    return ret;
}

#define BANNER_STATUS "FASTLANE fully operational!\n" \
                      "Thank you for asking kind sir/madam!\n"
int do_status() {

    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_STATUS, sizeof(BANNER_STATUS), ret);

    return ret;
}

#define BANNER_GIMME "Your FASTLANE file contents; we appreciate your business!\n" \
                     "---------------------------------------------------------\n"
int do_gimme(char *uri) {

    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_GIMME, sizeof(BANNER_GIMME), bytes_sent);
    if (sizeof(BANNER_GIMME) != bytes_sent) { return ERRNO_SEND; }

    if ((ret = dump_file(uri)) != SUCCESS) { return ret; }

    return ret;
}

#define BANNER_LIST "Your files, kind sir/madam!\n" \
                    "---------------------------\n"
int do_list() {

    int ret = SUCCESS;
    int bytes_sent = 0;
    size_t i;

    SENDNULLTRUNC(BANNER_LIST, sizeof(BANNER_LIST), bytes_sent);
    if (sizeof(BANNER_LIST) != bytes_sent) { return ERRNO_SEND; }

    if ((ret = list_files()) != SUCCESS) { return ret; }

    return ret;
}

#define BANNER_SMORE "here's a lil' bit\n" \
                     "-----------------\n"
int do_smore(char *uri) {

    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_SMORE, sizeof(BANNER_SMORE), bytes_sent);
    if (sizeof(BANNER_SMORE) != bytes_sent) { return ERRNO_SEND; }

    if ((ret = head_file(uri)) != SUCCESS) { return ret; }

    return ret;
}

#define BANNER_YOUUP "Yep, i'm up, but all our basic lines are \"clogged\"\n" \
                        "Upgrade to FASTLANE today!\n"
int do_youup() {

    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_YOUUP, sizeof(BANNER_YOUUP), ret);

    return ret;
}

#define BANNER_MOOCH "the tubes are \"clogged\" right now...\n" \
                      "------------------------------------\n"
int do_mooch(char *uri) {

    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_MOOCH, sizeof(BANNER_MOOCH), bytes_sent);
    if (sizeof(BANNER_MOOCH) != bytes_sent) { return ERRNO_SEND; }

#ifndef DEBUG_ENABLE
    pause(CLOG_DELAY);
#endif

    if ((ret = dump_file(uri)) != SUCCESS) { return ret; }

    return ret;
}

#define BANNER_SUP "here're your files, plebian:\n" \
                   "----------------------------\n"
int do_sup() {

    int ret = SUCCESS;
    int bytes_sent = 0;
    size_t i;

    SENDNULLTRUNC(BANNER_SUP, sizeof(BANNER_SUP), bytes_sent);
    if (sizeof(BANNER_SUP) != bytes_sent) { return ERRNO_SEND; }

    if ((ret = list_files()) != SUCCESS) { return ret; }

    return ret;
}

#define BANNER_AUTH "Adding FASTLANE credits...\n" \
                    "--------------------------\n"
#define AUTH_SUCCESS "Authentication successful!\n"
#define AUTH_FAILURE "Sorry, failed to add credits.\n"
int do_auth(char *uri) {

    int ret = SUCCESS;
    int bytes_sent = 0;

    SENDNULLTRUNC(BANNER_AUTH, sizeof(BANNER_AUTH), ret);

    // interpret the URI as a hex-encoded UINT32 value
    UINT32 attempt = hex2UINT32(uri);

    // We're sometimes expiring a timer installed by the make infrastructure 
    // when attempt is too large and pow() recurses too many times.
    // We scope the range of the solution to something that will not trigger 
    // the alarm signal.  Obviously this has a direct impact on the difficulty
    // of the crypto problem.
    attempt &= AUTH_KEY_SPACE;

    if (0xFFFFFFFF == attempt || 
        AUTH_PRODUCT != my_pow(AUTH_GENERATOR, attempt) % AUTH_ORDER) { 
        SENDNULLTRUNC(AUTH_FAILURE, sizeof(AUTH_FAILURE), ret);
    } else {
        SENDNULLTRUNC(AUTH_SUCCESS, sizeof(AUTH_SUCCESS), ret);
        *ptr_credits = *ptr_credits + 3;
    }

    return ret;
}



