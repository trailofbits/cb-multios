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

#include "user.h"
#include "error.h"
#include "challenge.h"

typedef struct {
    team_t *team;
    chal_t *chal;
    char *flag;
    int valid;
    int idx;
    char *shout;
} flag_t;

typedef struct {
    size_t num_submit;
    size_t num_valid;
    size_t sz_submit;
    flag_t **submits;
    chal_t **chals;
    size_t *num_chals;
} flgmgr_t;

error_t flg_init(flgmgr_t *flg, chal_t **chals, size_t *num_chals);
error_t flg_add_submit(flgmgr_t *flg, team_t *team, const char* flag);
error_t flg_get_solves(flgmgr_t *flg, flag_t ***flags, chal_t *chal, size_t *n);
error_t flg_find_chal(flgmgr_t *flg, chal_t **chal, const char* flag);
int flg_team_did_solve(flgmgr_t *flg, team_t *team, chal_t *chal);

#endif
