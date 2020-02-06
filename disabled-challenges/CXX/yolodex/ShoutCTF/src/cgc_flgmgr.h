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

#ifndef FLAG_H
#define FLAG_H

#include "cgc_user.h"
#include "cgc_error.h"
#include "cgc_challenge.h"

typedef struct {
    team_t *team;
    chal_t *chal;
    char *flag;
    int valid;
    int idx;
    char *shout;
} flag_t;

typedef struct {
    cgc_size_t num_submit;
    cgc_size_t num_valid;
    cgc_size_t sz_submit;
    flag_t **submits;
    chal_t **chals;
    cgc_size_t *num_chals;
} flgmgr_t;

error_t cgc_flg_init(flgmgr_t *flg, chal_t **chals, cgc_size_t *num_chals);
error_t cgc_flg_add_submit(flgmgr_t *flg, team_t *team, const char* flag);
error_t cgc_flg_get_solves(flgmgr_t *flg, flag_t ***flags, chal_t *chal, cgc_size_t *n);
error_t cgc_flg_find_chal(flgmgr_t *flg, chal_t **chal, const char* flag);
int cgc_flg_team_did_solve(flgmgr_t *flg, team_t *team, chal_t *chal);

#endif
