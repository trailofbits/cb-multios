/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef CTF_H
#define CTF_H

#include "cgc_user.h"
#include "cgc_challenge.h"
#include "cgc_flgmgr.h"

#define CTF_STAT_DOWN   0
#define CTF_STAT_LIVE   1

typedef struct {
    int status;
    cgc_size_t num_chals;
    cgc_size_t num_teams;
    cgc_size_t num_users;
    cgc_size_t sz_chals;
    cgc_size_t sz_teams;
    cgc_size_t sz_users;
    chal_t **chals;
    team_t **teams;
    user_t **users;
    flgmgr_t flg;
    user_t *logged_in;
} ctf_t;

error_t cgc_ctf_init(ctf_t *ctf);

/* Feature */
error_t cgc_ctf_submit_flag(ctf_t *ctf, team_t *team, const char *flag);
error_t cgc_ctf_add_user(ctf_t *ctf, user_t *user);
error_t cgc_ctf_auth_user(ctf_t *ctf, user_t **user, const char *nick, const char *pass);
error_t cgc_ctf_add_team(ctf_t *ctf, team_t *team);
error_t cgc_ctf_add_chal(ctf_t *ctf, chal_t *chal);
error_t cgc_ctf_open_chal(ctf_t *ctf, cgc_size_t cid);

/* Ticker & Info */
error_t cgc_ctf_get_solves(ctf_t *ctf, flag_t ***solves, cgc_size_t *n);
error_t cgc_ctf_get_ranks(ctf_t *ctf, team_t ***ranks, cgc_size_t *page);
error_t cgc_ctf_get_team(ctf_t *ctf, team_t **team, cgc_size_t tid);
error_t cgc_ctf_get_chal(ctf_t *ctf, chal_t **chal, cgc_size_t cid);

#endif
