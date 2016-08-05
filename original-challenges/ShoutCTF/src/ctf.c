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

#include <string.h>

#include "ctf.h"

error_t ctf_init(ctf_t *ctf)
{
    ctf->status = CTF_STAT_DOWN;
    ctf->num_chals = 0;
    ctf->num_teams = 0;
    ctf->num_users = 0;
    ctf->chals = (chal_t **) malloc(8 * sizeof(chal_t *));
    ctf->sz_chals = 8;
    ctf->teams = (team_t **) malloc(16 * sizeof(team_t *));
    ctf->sz_teams = 16;
    ctf->users = (user_t **) malloc(32 * sizeof(user_t *));
    ctf->sz_users = 32;
    ctf->logged_in = NULL;
    flg_init(&ctf->flg, ctf->chals, &ctf->num_chals);
    return ERR_OK;
}

error_t ctf_submit_flag(ctf_t *ctf, team_t *team, const char *flag)
{
    error_t err;
    flgmgr_t *flg = &ctf->flg;
    if ((err = flg_add_submit(flg, team, flag)) != ERR_OK)
        return err;
    return ERR_OK;
}

error_t ctf_add_user(ctf_t *ctf, user_t *user)
{
    if (!ctf || !user)
        return ERR_INTERNAL;
    int i;
    for (i = 0; i < ctf->num_users; ++i)
    {
        if (strcmp(ctf->users[i]->nick, user->nick) == 0)
            return ERR_USER_EXISTS;
    }
    if (ctf->num_users == ctf->sz_users)
    {
        ctf->users = (user_t **) realloc(ctf->users, 2 * ctf->sz_users * sizeof(user_t *));
        ctf->sz_users *= 2;
    }
    ctf->users[ctf->num_users++] = user;
    return ERR_OK;
}

error_t ctf_auth_user(ctf_t *ctf, user_t **user, const char *nick, const char *pass)
{
    if (!ctf || !user || !nick || !pass)
        return ERR_INTERNAL;
    int i;
    for (i = 0; i < ctf->num_users; ++i)
    {
        user_t *u = ctf->users[i];
        if (strcmp(u->nick, nick) == 0)
        {
            if (strcmp(u->pass, pass) == 0)
            {
                *user = u;
                return ERR_OK;
            }
            return ERR_WRONG_PASS;
        }
    }
    return ERR_NO_SUCH_USER;
}

error_t ctf_add_team(ctf_t *ctf, team_t *team)
{
    if (!ctf || !team)
        return ERR_INTERNAL;
    int i;
    for (i = 0; i < ctf->num_teams; ++i)
    {
        if (strcmp(ctf->teams[i]->name, team->name) == 0)
            return ERR_TEAM_EXISTS;
    }
    if (ctf->num_teams == ctf->sz_teams)
    {
        ctf->teams = (team_t **) realloc(ctf->teams, 2 * ctf->sz_teams * sizeof(team_t *));
        ctf->sz_teams *= 2;
    }
    ctf->teams[ctf->num_teams++] = team;
    return ERR_OK;
}

error_t ctf_add_chal(ctf_t *ctf, chal_t *chal)
{
    if (!ctf || !chal)
        return ERR_INTERNAL;
    int i;
    for (i = 0; i < ctf->num_chals; ++i)
    {
        if (strcmp(ctf->chals[i]->name, chal->name) == 0 ||
            strcmp(ctf->chals[i]->flag, chal->flag) == 0)
            return ERR_CHAL_EXISTS;
    }
    if (ctf->num_chals == ctf->sz_chals)
    {
        ctf->chals = (chal_t **) realloc(ctf->chals, 2 * ctf->sz_chals * sizeof(chal_t *));
        ctf->flg.chals = ctf->chals;
        ctf->sz_chals *= 2;
    }
    ctf->chals[ctf->num_chals++] = chal;
    return ERR_OK;
}

error_t ctf_open_chal(ctf_t *ctf, size_t cid)
{
    if (!ctf)
        return ERR_INTERNAL;
    if (cid >= ctf->num_chals)
        return ERR_NO_SUCH_CHAL;
    chal_t *chal = ctf->chals[cid];
    if (chal->status != CSTAT_LOCKED)
        return ERR_CHAL_ALREADY_OPEN;
    chal->status = CSTAT_OPEN;
    return ERR_OK;
}

error_t ctf_get_solves(ctf_t *ctf, flag_t ***solves, size_t *n)
{
    if (!ctf || !solves || !n)
        return ERR_INTERNAL;
    error_t err;
    if ((err = flg_get_solves(&ctf->flg, solves, NULL, n)) != ERR_OK)
        return err;
    return ERR_OK;
}

team_t* ctf_select_nth(team_t **arr, size_t len, int n)
{
    int i, j;
    team_t *tmp;
    for (i = j = 0; i < len - 1; ++i)
    {
        if (arr[i]->score < arr[len-1]->score) continue;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        j++;
    }
    tmp = arr[len-1];
    arr[len-1] = arr[j];
    arr[j] = tmp;
    if (n == j)
        return arr[j];
    if (j > n)
        return ctf_select_nth(arr, j, n);
    return ctf_select_nth(&arr[j], len - j, n - j);
}

error_t ctf_get_ranks(ctf_t *ctf, team_t ***ranks, size_t *page)
{
    if (!ctf || !ranks || !page)
        return ERR_INTERNAL;
    error_t err;
    int i, j;
    for (i = 0; i < ctf->num_teams; ++i)
        ctf->teams[i]->score = 0;
    for (i = 0; i < ctf->num_chals; ++i)
    {
        chal_t *c = ctf->chals[i];
        if (c->status != CSTAT_LOCKED)
        {
            for (j = 0; j < ctf->num_teams; ++j)
            {
                team_t *t = ctf->teams[j];
                if (flg_team_did_solve(&ctf->flg, t, c))
                    t->score += c->points;
            }
        }
    }
    size_t n = (5 < ctf->num_teams) ? 5 : ctf->num_teams;
    size_t p = *page;
    *ranks = NULL;
    *page = 0;
    if (n == 0)
        return ERR_OK;
    if ((p - 1) * 5 >= ctf->num_teams)
        p = 0;
    else
        p = (p - 1) * 5;
    *page = p;
    *ranks = (team_t **) malloc(n * sizeof(team_t *));
    team_t **temp = (team_t **) malloc(ctf->num_teams * sizeof(team_t *));
    memcpy(temp, ctf->teams, ctf->num_teams * sizeof(team_t *));
    for (i = p, j = 0; i < ctf->num_teams && j < n; ++i, ++j)
        (*ranks)[j] = ctf_select_nth(temp, ctf->num_teams, i);
    free(temp);
    return ERR_OK;
}

error_t ctf_get_team(ctf_t *ctf, team_t **team, size_t tid)
{
    if (!ctf || !team)
        return ERR_INTERNAL;
    if (tid >= ctf->num_teams)
        return ERR_NO_SUCH_TEAM;
    *team = ctf->teams[tid];
    return ERR_OK;
}

error_t ctf_get_chal(ctf_t *ctf, chal_t **chal, size_t cid)
{
    if (!ctf || !chal)
        return ERR_INTERNAL;
    if (cid >= ctf->num_chals)
        return ERR_NO_SUCH_CHAL;
    *chal = ctf->chals[cid];
    return ERR_OK;
}

