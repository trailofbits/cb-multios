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

#include "cgc_string.h"

#include "cgc_user.h"

error_t cgc_user_new(user_t **user)
{
    if (!user)
        return ERR_INTERNAL;
    *user = (user_t *) cgc_malloc(sizeof(user_t));
    cgc_memset(*user, 0, sizeof(user_t));
    return ERR_OK;
}

error_t cgc_user_set_nick(user_t *user, const char *nick)
{
    if (!user || !nick)
        return ERR_INTERNAL;
    if (cgc_strlen(nick) >= sizeof(user->nick))
        return ERR_NICK_LONG;
    cgc_memset(user->nick, 0, sizeof(user->nick));
    cgc_strcpy(user->nick, nick);
    return ERR_OK;
}

error_t cgc_user_set_pass(user_t *user, const char *pass)
{
    if (!user || !pass)
        return ERR_INTERNAL;
    if (cgc_strlen(pass) >= sizeof(user->pass))
        return ERR_PASS_LONG;
    cgc_memset(user->pass, 0, sizeof(user->pass));
    cgc_strcpy(user->pass, pass);
    return ERR_OK;
}

error_t cgc_user_set_team(user_t *user, team_t *team, team_t **old)
{
    if (!user || !team)
        return ERR_INTERNAL;
    if (old)
        *old = user->team;
    user->team = team;
    return ERR_OK;
}

error_t cgc_team_new(team_t **team)
{
    if (!team)
        return ERR_INTERNAL;
    *team = (team_t *) cgc_malloc(sizeof(team_t));
    cgc_memset(*team, 0, sizeof(team_t));
    (*team)->members = (user_t **) cgc_malloc(sizeof(user_t *) * 8);
    (*team)->sz_members = 8;
    cgc_memset((*team)->members, 0, (*team)->sz_members * sizeof(user_t *));
    return ERR_OK;
}
error_t cgc_team_add_member(team_t *team, user_t *user)
{
    if (!team || !user)
        return ERR_INTERNAL;
    if (team->num_members == team->sz_members)
    {
        cgc_size_t nsz = team->sz_members * 2 * sizeof(user_t *);
        team->members = (user_t **) cgc_realloc(team->members, nsz);
        team->sz_members *= 2;
    }
    if (team->num_members == 0)
        team->leader = user;
    team->members[team->num_members++] = user;
    return ERR_OK;
}

error_t cgc_team_remove_member(team_t *team, const char *nick)
{
    int i;
    cgc_size_t n;
    if (!team || !nick)
        return ERR_INTERNAL;
    for (i = 0; i < team->num_members; ++i)
    {
        if (cgc_strcmp(team->members[i]->nick, nick) == 0)
            break;
    }
    if (i == team->num_members)
        return ERR_NO_SUCH_USER;
    n = (team->num_members - i - 1) * sizeof(user_t *);
    cgc_memmove(&team->members[i], &team->members[i+1], n);
    team->num_members--;
    return ERR_OK;
}

error_t cgc_team_change_name(team_t *team, const char *name)
{
    if (!team || !name)
        return ERR_INTERNAL;
    if (cgc_strlen(name) >= sizeof(team->name))
        return ERR_NAME_LONG;
    cgc_memset(team->name, 0, sizeof(team->name));
    cgc_strcpy(team->name, name);
    return ERR_OK;
}

error_t cgc_team_set_shoutout(team_t *team, const char *shout)
{
    if (!team || !shout)
        return ERR_INTERNAL;
    if (team->shout)
        cgc_free(team->shout);
    team->shout = cgc_strdup(shout);
    return ERR_OK;
}
