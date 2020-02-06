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

#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

#include "cgc_user.h"
#include "cgc_ctf.h"

unsigned int r;
unsigned int cgc_prng()
{
    r = ((((r >> 31) ^ (r >> 30) ^ (r >> 10) ^ (r >> 0)) & 1) << 31) | (r >> 1);
    return r;
}

void cgc_random_string(char *buf, cgc_size_t len)
{
    int i;
    int r;
    char str[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (i = 0; i < len; ++i)
    {
        r = cgc_prng();
        buf[i] = str[r % (sizeof(str) - 1)];
    }
}

void cgc_print_main_menu()
{
    cgc_printf("\n=== Menu ===================\n");
    cgc_printf("1. Register User\n");
    cgc_printf("2. Login User\n");
    cgc_printf("3. Quit\n");
    cgc_printf("> ");
}

int cgc_is_alphanum(const char *s)
{
    int i;
    for (i = 0; i < cgc_strlen(s) - 1; ++i)
    {
        if (!cgc_isalnum(s[i]))
            return 0;
    }
    return 1;
}

void cgc_handle_register_user(ctf_t *ctf)
{
    char shout[128], buf[256];
    user_t *user = NULL;
    team_t *team = NULL;
    int new_team = 0;
    error_t err;
    if ((err = cgc_user_new(&user)) != ERR_OK)
        goto fail;
    cgc_printf("\n=== User Creation ===================\n");
    cgc_printf("Nickname: ");
    err = ERR_INVALID_VALUE;
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) <= 0)
        goto fail;
    if (!cgc_is_alphanum(buf))
        goto fail;
    if ((err = cgc_user_set_nick(user, buf)) != ERR_OK)
        goto fail;
    cgc_printf("Password: ");
    err = ERR_INVALID_VALUE;
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) <= 0)
        goto fail;
    if (!cgc_is_alphanum(buf))
        goto fail;
    if ((err = cgc_user_set_pass(user, buf)) != ERR_OK)
        goto fail;
    cgc_printf("Team token: ");
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        goto fail;
    if (cgc_strcmp(buf, "") == 0)
    {
        if ((err = cgc_team_new(&team)) != ERR_OK)
            goto fail;
        cgc_printf("\n=== Team Creation ===================\n");
        cgc_printf("Team name: ");
        err = ERR_INVALID_VALUE;
        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) <= 0)
            goto fail;
        if ((err = cgc_team_change_name(team, buf)) != ERR_OK)
            goto fail;
        cgc_printf("Shoutout: ");
        err = ERR_INVALID_VALUE;
        cgc_fflush(cgc_stdout);
#ifdef PATCHED_1
        if (cgc_freaduntil(shout, sizeof(shout), '\n', cgc_stdin) <= 0)
#else
        if (cgc_freaduntil(shout, sizeof(buf), '\n', cgc_stdin) <= 0)
#endif
            goto fail;
        if ((err = cgc_team_set_shoutout(team, shout)) != ERR_OK)
            goto fail;
        cgc_random_string(team->code, sizeof(team->code) - 1);
        team->code[sizeof(team->code) - 1] = '\0';
        new_team = 1;
    }
    else
    {
        int i;
        for (i = 0; i < ctf->num_teams; ++i)
        {
            if (cgc_memcmp(ctf->teams[i]->code, buf, 32) == 0)
            {
                team = ctf->teams[i];
                break;
            }
        }
        if (i == ctf->num_teams)
        {
            err = ERR_NO_SUCH_TEAM;
            goto fail;
        }
    }
    if ((err = cgc_ctf_add_user(ctf, user)) != ERR_OK)
        goto fail;
    if (new_team && (err = cgc_ctf_add_team(ctf, team)) != ERR_OK)
        goto fail;
    if ((err = cgc_team_add_member(team, user)) != ERR_OK)
        goto fail;
    if ((err = cgc_user_set_team(user, team, NULL)) != ERR_OK)
        goto fail;
    cgc_printf("[INFO] Successfully registered.\n");
    if (new_team)
        cgc_printf("[INFO] Team code: ;s\n", team->code);
    return;

fail:
    cgc_printf("[ERROR] ;s\n", cgc_error_to_string(err));
    if (user)
        cgc_free(user);
    if (new_team && team)
        cgc_free(team);
    return;
}

void cgc_handle_login_user(ctf_t *ctf)
{
    error_t err;
    char nick[64], pass[64];
    cgc_printf("\n=== Login ===================\n");
    cgc_printf("Nick: ");
    err = ERR_INVALID_VALUE;
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(nick, sizeof(nick), '\n', cgc_stdin) <= 0)
        goto fail;
    if (!cgc_is_alphanum(nick))
        goto fail;
    cgc_printf("Password: ");
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(pass, sizeof(pass), '\n', cgc_stdin) <= 0)
        goto fail;
    if (!cgc_is_alphanum(pass))
        goto fail;
    if ((err = cgc_ctf_auth_user(ctf, &ctf->logged_in, nick, pass)) != ERR_OK)
        goto fail;
    cgc_printf("[INFO] Successfully logged in as ;s.\n", nick);
    return;

fail:
    cgc_printf("[ERROR] ;s\n", cgc_error_to_string(err));
}

void cgc_print_ctf_ticker(ctf_t *ctf)
{
    team_t *t = ctf->logged_in->team;
    cgc_size_t n = 1;
    team_t **tmp = NULL;
    cgc_ctf_get_ranks(ctf, &tmp, &n);
    cgc_free(tmp);
    cgc_printf("\n================================\n");
    cgc_printf("| [;s] - ;d\n", t->name, t->score);
    cgc_printf("================================\n");
    int i;
    flag_t **solves = NULL;
    n = 5;
    cgc_ctf_get_solves(ctf, &solves, &n);
    if (n == 0)
        cgc_printf("No solves yet.\n");
    for (i = 0; i < n; ++i)
        cgc_printf("| ;s solved ;s (;d pts)\n", solves[i]->team->name, solves[i]->chal->name, solves[i]->chal->points);
    if (solves)
        cgc_free(solves);
    cgc_printf("================================\n");
}

void cgc_print_ctf_menu(ctf_t *ctf)
{
    cgc_print_ctf_ticker(ctf);
    cgc_printf("\n=== CTF Menu ===================\n");
    cgc_printf("1. View challenge list\n");
    cgc_printf("2. View challenge detail\n");
    cgc_printf("3. View ranking\n");
    cgc_printf("4. View team profile\n");
    cgc_printf("5. Submit flag\n");
    cgc_printf("6. Logout\n");
    cgc_printf("> ");
}

void cgc_print_challenge(ctf_t *ctf, chal_t *chal, int detail)
{
    const char *cat = cgc_chal_cat_to_string(chal->cat);
    chal_stat_t stat = chal->status;
    if (cgc_flg_team_did_solve(&ctf->flg, ctf->logged_in->team, chal))
        stat = CSTAT_SOLVED_U;
    const char *status = cgc_chal_status_to_string(stat);
    if (!detail)
        cgc_printf("[;s] [;d pts] ;s - ;s\n", cat, chal->points, chal->name, status);
    else
    {
        cgc_printf("[;s] [;d pts] ;s - ;s\n", cat, chal->points, chal->name, status);
        if (chal->status == CSTAT_LOCKED)
            cgc_printf("Hidden.\n");
        else
            cgc_printf(";s\n", chal->desc);
        //cgc_printf("flag: ;s\n", chal->flag);
        flag_t **f = NULL;
        cgc_size_t n = 3;
        cgc_flg_get_solves(&ctf->flg, &f, chal, &n);
        if (n > 0)
        {
            cgc_printf("\nTop Solvers\n");
            cgc_printf("===========\n");
            int i;
            for(i = 0; i< n; ++i)
                cgc_printf(";d. ;s\n", i+1, f[i]->team->name);
            cgc_free(f);
        }
    }
}

void cgc_handle_view_challenge_list(ctf_t *ctf)
{
    int i;
    if (ctf->num_chals == 0)
    {
        cgc_printf("[INFO] No challenges are available.\n");
        return;
    }
    cgc_printf("\n=== Challenge list ===================\n");
    for (i = 0; i < ctf->num_chals; ++i)
    {
        cgc_printf(";d. ", i);
        cgc_print_challenge(ctf, ctf->chals[i], 0);
    }
}

void cgc_handle_view_challenge_detail(ctf_t *ctf)
{
    char buf[32];
    cgc_handle_view_challenge_list(ctf);
    if (ctf->num_chals == 0)
        return;
    cgc_printf("\nChoose idx: ");
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        goto fail;
    error_t err;
    chal_t *chal = NULL;
    if ((err = cgc_ctf_get_chal(ctf, &chal, cgc_strtoul(buf, NULL, 10))) != ERR_OK)
        goto fail;
    cgc_printf("\n=== Challenge detail ===================\n");
    cgc_print_challenge(ctf, chal, 1);
    return;

fail:
    cgc_printf("[ERROR] ;s\n", cgc_error_to_string(err));
}

void cgc_view_ranking_page(ctf_t *ctf, cgc_size_t page)
{
    int i;
    cgc_size_t n = (5 < ctf->num_teams - (page - 1) * 5) ? 5 : (ctf->num_teams - (page - 1) * 5);
    team_t **ranks = NULL;
    cgc_ctf_get_ranks(ctf, &ranks, &page);
    for (i = 0; i < n; ++i)
    {
        int rank = i + page * 5 + 1;
        cgc_printf(";d. ;s (;d pts)\n", rank, ranks[i]->name, ranks[i]->score);
    }
    cgc_free(ranks);
}

void cgc_handle_view_ranking(ctf_t *ctf)
{
    char buf[32];
    error_t err = ERR_INVALID_VALUE;
    cgc_printf("\n=== Ranking ===================\n");
    cgc_size_t page = 1;
    cgc_size_t num_pages = (ctf->num_teams / 5) + ((ctf->num_teams % 5) == 0 ? 0 : 1);
    cgc_view_ranking_page(ctf, 1);
    cgc_printf("\n=== 1 / ;d ===================\n", num_pages);
    while (1)
    {
        cgc_printf("\nPage: ");
        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
            goto fail;
        if (cgc_strcmp(buf, "q") == 0)
            return;
        page = cgc_strtoul(buf, NULL, 10);
        if (page < 1 || page > num_pages)
            goto fail;
        cgc_view_ranking_page(ctf, page);
        cgc_printf("\n=== ;d / ;d ===================\n", page, num_pages);
    }
    return;

fail:
    cgc_printf("[ERROR] ;s\n", cgc_error_to_string(err));
}

void cgc_handle_view_team_profile(ctf_t *ctf)
{
    char buf[64];
    error_t err = ERR_NO_SUCH_TEAM;
    cgc_printf("\nTeam name: ");
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) <= 0)
        goto fail;
    int i;
    team_t *t = NULL;
    for (i = 0; i < ctf->num_teams; ++i)
    {
        if (cgc_strcmp(ctf->teams[i]->name, buf) == 0)
        {
            t = ctf->teams[i];
            break;
        }
    }
    if (!t)
        goto fail;
    cgc_printf("\n=== Team profile ===================\n");
    cgc_printf(";s\n", t->name);
    cgc_printf("Leader: ;s\n", t->leader->nick);
    cgc_printf("Members (;d)\n - ", t->num_members);
    for (i = 0; i < t->num_members; ++i)
    {
        cgc_printf(";s", t->members[i]->nick);
        if (i != t->num_members - 1)
            cgc_printf(", ");
    }
    cgc_printf("\nShoutout: ;s\n", t->shout);
    return;

fail:
    cgc_printf("[ERROR] ;s\n", cgc_error_to_string(err));
}

void cgc_handle_submit_flag(ctf_t *ctf)
{
    char buf[512];
    error_t err = ERR_INVALID_FLAG;
    cgc_printf("\n=== Submit flag ===================\n");
    cgc_printf("Flag: ");
    cgc_fflush(cgc_stdout);
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) <= 0)
        goto fail;
    if ((err = cgc_ctf_submit_flag(ctf, ctf->logged_in->team, buf)) != ERR_OK)
        goto fail;
    chal_t *chal = NULL;
    cgc_flg_find_chal(&ctf->flg, &chal, buf);
    cgc_printf("[INFO] Congrats! You scored ;d points!\n", chal->points);
    return;
fail:
    cgc_printf("[ERROR] ;s\n", cgc_error_to_string(err));
}

void cgc_handle_logout_user(ctf_t *ctf)
{
    cgc_printf("[INFO] Successfully logged out.\n");
    ctf->logged_in = NULL;
}

void cgc_handle_quit()
{
    cgc_printf("Bye.\n");
    cgc_fflush(cgc_stdout);
    cgc_exit(0);
}

void cgc_do_random_action(ctf_t *ctf)
{
    ctf->status = CTF_STAT_LIVE;
    switch (cgc_prng() % 10)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            /* Create a random challenge */
            {
                chal_t *chal = (chal_t *) cgc_malloc(sizeof(chal_t));
                cgc_random_string(chal->name, 32);
                chal->name[32] = '\0';
                cgc_random_string(chal->desc, 64);
                chal->desc[64] = '\0';
                chal->points = cgc_prng() % 600;
                if (chal->points == 0)
                    chal->points = 1;
                chal->status = CSTAT_LOCKED;
                chal->cat = cgc_prng() % 7;
                chal->flag = cgc_malloc(64);
                cgc_random_string(chal->flag, 32);
                chal->flag[32] = '\0';
                cgc_ctf_add_chal(ctf, chal);
            }
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            /* Open a random challenge */
            {
                int i;
                for (i = 0; i < ctf->num_chals; ++i)
                {
                    chal_t *c = ctf->chals[i];
                    if (c->status == CSTAT_LOCKED)
                    {
                        if (cgc_prng() % 100 < 50)
                        {
                            cgc_ctf_open_chal(ctf, i);
                            break;
                        }
                    }
                }
            }
            break;
        case 8:
            /* Make CTF down */
            ctf->status = CTF_STAT_DOWN;
            break;
        case 9:
            break;
    }
}

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    void *secret_page = (void *)secret_page_i;
    char buf[256];

    r = *(unsigned int *)secret_page ^ *(unsigned int *)&secret_page[20];

    cgc_fbuffered(cgc_stdin, 1);
    cgc_fbuffered(cgc_stdout, 1);

    cgc_fxlat(cgc_stdin, "7943");
    cgc_fxlat(cgc_stdout, "7943");

    ctf_t ctf;
    cgc_ctf_init(&ctf);

    cgc_printf("Shout CTF CLI v0.1\n");
    cgc_printf("=================\n");
    cgc_fflush(cgc_stdout);
    while (1)
    {
        cgc_do_random_action(&ctf);
        if (!ctf.logged_in)
        {
            cgc_print_main_menu();
            cgc_fflush(cgc_stdout);
            if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
                break;
            if (ctf.status == CTF_STAT_DOWN)
            {
                cgc_printf("CTF server is down! Try again later :(\n");
                continue;
            }
            if (cgc_strcmp(buf, "1") == 0)
                cgc_handle_register_user(&ctf);
            else if (cgc_strcmp(buf, "2") == 0)
                cgc_handle_login_user(&ctf);
            else if (cgc_strcmp(buf, "3") == 0)
                cgc_handle_quit();
            else
                cgc_printf("Try again.\n");
        }
        else
        {
            cgc_print_ctf_menu(&ctf);
            cgc_fflush(cgc_stdout);
            if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
                break;
            if (ctf.status == CTF_STAT_DOWN)
            {
                cgc_printf("CTF server is down! Try again later :(\n");
                continue;
            }
            if (cgc_strcmp(buf, "1") == 0)
                cgc_handle_view_challenge_list(&ctf);
            else if (cgc_strcmp(buf, "2") == 0)
                cgc_handle_view_challenge_detail(&ctf);
            else if (cgc_strcmp(buf, "3") == 0)
                cgc_handle_view_ranking(&ctf);
            else if (cgc_strcmp(buf, "4") == 0)
                cgc_handle_view_team_profile(&ctf);
            else if (cgc_strcmp(buf, "5") == 0)
                cgc_handle_submit_flag(&ctf);
            else if (cgc_strcmp(buf, "6") == 0)
                cgc_handle_logout_user(&ctf);
            else
                cgc_printf("Try again.\n");
        }
    }

    cgc_fflush(cgc_stdout);
    return 0;
}
