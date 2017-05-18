/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include "cgc_string.h"

#include "cgc_compare.h"
#include "cgc_sfile.h"

#define EE_VAL 32

typedef struct match {
    cgc_size_t r_idx;
    cgc_size_t l_idx;
    cgc_size_t length;
} match_t;

typedef struct match_ll match_ll_t;
struct match_ll {
    match_t *match;
    match_ll_t *next;
};

static char ee_str[4096] = {0};
static int g_cached = 0;
static match_ll_t *g_best_match = NULL;
static lcll_t *g_lfile_cmp = NULL, *g_rfile_cmp = NULL;

static void cgc_compare_binary_files(SFILE *lfile, SFILE *rfile) {
    if (lfile->size == rfile->size) {
        cgc_size_t i = 0;
        for(i = 0; i < lfile->size; i++) {
            if (lfile->data[i] != rfile->data[i]) {
                goto not_identical;
            }
        }
        goto identical;
    }

not_identical:
    cgc_printf("Binary files %s and %s are not identical\n", lfile->name, rfile->name);
    return;

identical:
    cgc_printf("Binary files match\n");
    return;
}

static int cgc_compare_line(lc_t *lline, lc_t *rline, int ignore_ws) {
    if (ignore_ws) {
        if (cgc_strlen(lline->no_ws_line) && cgc_strlen(rline->no_ws_line)
                && cgc_strlen(lline->no_ws_line) == cgc_strlen(rline->no_ws_line)
                && lline->no_ws_lhash.hash1 == rline->no_ws_lhash.hash1
                && lline->no_ws_lhash.hash2 == rline->no_ws_lhash.hash2)
        {
            char *left = lline->no_ws_line, *right = rline->no_ws_line;
            return cgc_strcmp(left, right);
        }
    } else {
        if (cgc_strlen(lline->pline) && cgc_strlen(rline->pline)
                && cgc_strlen(lline->pline) == cgc_strlen(rline->pline)
                && lline->lhash.hash1 == rline->lhash.hash1
                && lline->lhash.hash2 == rline->lhash.hash2) {

            char *left = lline->pline, *right = rline->pline;
            return cgc_strcmp(left, right);
        }
    }

    return -1;
}

// Compare Lines is n^2. We can make this faster by precomputing a hash that stores the line
// In an ideal world this would generate a directed graph, and the best fit would be the longest path
static match_ll_t *cgc_generate_matches(lcll_t *lfile_cmp, lcll_t *rfile_cmp, int ignore_ws)
{
    lcll_t *ll_iter = lfile_cmp, *rl_iter = rfile_cmp;
    lcll_t *temp_ll = ll_iter;
    cgc_size_t l_idx = 0, r_idx = 0;
    match_t temp_match, *new_match;
    match_ll_t *match_list = NULL, *new_ml_item, *ml_iter, *prev_ml_iter;
    int found_match = 0;

    while (ll_iter) {
        rl_iter = rfile_cmp;
        r_idx = 0;
        while (rl_iter) {
            temp_ll = ll_iter;
            found_match = 0;
            cgc_memset(&temp_match, 0, sizeof(match_t));
            while (temp_ll && rl_iter  && cgc_compare_line(temp_ll->lc, rl_iter->lc, ignore_ws) == 0) {
                if (!found_match) {
                    temp_match.l_idx = l_idx;
                    temp_match.r_idx = r_idx;
                    temp_match.length = 1;
                    found_match = 1;
                } else {
                    temp_match.length++;
                }

                temp_ll = temp_ll->next;
                rl_iter = rl_iter->next;
                r_idx++;
            }

            if (found_match) {
                new_match = cgc_malloc(sizeof(match_t));
                if (!new_match)
                    return match_list;
                cgc_memcpy(new_match, &temp_match, sizeof(match_t));

                new_ml_item = cgc_malloc(sizeof(match_ll_t));
                if (!new_ml_item) {
                    cgc_free(new_match);
                    return match_list;
                }
                new_ml_item->match = new_match;
                new_ml_item->next = NULL;

                if (!match_list) {
                    match_list = new_ml_item;
                } else {
                    ml_iter = match_list;
                    prev_ml_iter = ml_iter;
                    while (ml_iter) {
                        if (ml_iter->match->r_idx < new_match->r_idx) {
                            if ((ml_iter->match->r_idx + ml_iter->match->length) >=
                                (new_match->r_idx + new_match->length))
                            {
                                cgc_free(new_ml_item->match);
                                cgc_free(new_ml_item);
                                break;
                            } else {
                                if (ml_iter->next) {
                                    prev_ml_iter = ml_iter;
                                    ml_iter = ml_iter->next;
                                } else {
                                    ml_iter->next = new_ml_item;
                                    break;
                                }
                            }
                        } else {
                            if(ml_iter == match_list) {
                                new_ml_item->next = ml_iter;
                                match_list = new_ml_item;
                            } else {
                                new_ml_item->next = ml_iter;
                                prev_ml_iter->next = new_ml_item;
                            }
                            break;
                        }
                    }
                }
            } else  {
                rl_iter = rl_iter->next;
                r_idx++;
            }
        }

        ll_iter = ll_iter->next;
        l_idx++;
    }

    return match_list;
}

// Ideally this would be parsing a graph using a longest path algorithm
// This implementation takes a first fit approach
static match_ll_t *cgc_find_single_match_set(match_ll_t **pmatch_sets, unsigned int *pscore)
{
    if (!*pmatch_sets)
        return NULL;

    match_ll_t *set_head = NULL, *set, *iter = *pmatch_sets, *prev = *pmatch_sets, *temp_match;
    unsigned int l_idx = 0, r_idx = 0;
    *pscore = 0;

    while(iter) {
        if(iter->match->l_idx >= l_idx && iter->match->r_idx >= r_idx)
        {
            //score = n -> SUM(n), 0:n; --> n + (n-1) + (n-2) ... (n-n);
            *pscore += ((iter->match->length) * (iter->match->length + 1)) >> 1;
            l_idx = iter->match->l_idx + iter->match->length;
            r_idx = iter->match->r_idx + iter->match->length;
            temp_match = iter;

            if (iter == *pmatch_sets) {
                *pmatch_sets = iter->next;
                prev = iter->next;
                iter = iter->next;
            } else {
                prev->next = iter->next;
                iter = iter->next;
            }

            temp_match->next = NULL;
            if (!set_head) {
                set_head = temp_match;
                set = set_head;
            } else {
                set->next = temp_match;
                set = set->next;
            }
        } else {
            prev = iter;
            iter = iter->next;
        }
    }

    return set_head;
}

static match_ll_t *cgc_find_best_match_set(match_ll_t *all_matches)
{
    if (!all_matches)
        return NULL;

    match_ll_t *set = NULL, *best_match = NULL, *temp = NULL;
    unsigned int score = 0, max_score = 0;

    while ((set = cgc_find_single_match_set(&all_matches, &score))) {
        if (score > max_score) {
            while(best_match) {
                temp = best_match;
                best_match = best_match->next;
                cgc_free(temp->match);
                cgc_free(temp);
            }

            max_score = score;
            best_match = set;
        } else {
            while(set) {
                temp = set;
                set = set->next;
                cgc_free(temp->match);
                cgc_free(temp);
            }
        }
    }

    return best_match;
}


static match_ll_t *cgc_compare_lines(lcll_t *lfile_cmp, lcll_t *rfile_cmp, int ignore_ws)
{
    match_ll_t *all_matches, *best_match;
    all_matches = cgc_generate_matches(lfile_cmp, rfile_cmp, ignore_ws);
    best_match = cgc_find_best_match_set(all_matches);

    return best_match;
}

static void cgc_print_diff()
{
    int i = 0, ee = 1;
    cgc_size_t l_idx = 0, r_idx = 0, found_match = 0;
    lcll_t *ll_iter = g_lfile_cmp, *rl_iter = g_rfile_cmp;
    match_ll_t *m_iter = g_best_match;

    if  (!m_iter) {
        cgc_printf("Files don't match at all\n");
        return;
    }

    while (m_iter) {
        if (m_iter->match->l_idx > m_iter->match->r_idx) {
            found_match = 1;
            cgc_printf("%d,%dr%d,%d\n", l_idx, m_iter->match->l_idx, r_idx, m_iter->match->r_idx);
            for(i = 0; i < (m_iter->match->l_idx - l_idx); i++) {
                cgc_printf("< %s\n", ll_iter->lc->pline);
                ll_iter = ll_iter->next;
            }
            l_idx += i;
        } else if (m_iter->match->l_idx < m_iter->match->r_idx) {
            found_match = 1;
            cgc_printf("%d,%da%d,%d\n", l_idx, m_iter->match->l_idx, r_idx, m_iter->match->r_idx);
            for(i = 0; i < (m_iter->match->r_idx - r_idx); i++) {
                cgc_printf("> %s\n", rl_iter->lc->pline);
                rl_iter = rl_iter->next;
            }
            r_idx += i;
        } else {
            if (l_idx != m_iter->match->l_idx || r_idx != m_iter->match->r_idx) {
                if (ee) {
                    ee = (ee * ee) == l_idx ? ee + 1 : 0;
                    if (ee == EE_VAL) {
#ifndef PATCHED
                        cgc_strcpy(ee_str, ll_iter->lc->pline);
#else
                        if (cgc_strlen(ll_iter->lc->pline) < 4096)
                            cgc_strcpy(ee_str, ll_iter->lc->pline);
                        else
                            ee = 0;
#endif
                    }
                }

                found_match = 1;
                cgc_printf("%d,%dc%d,%d\n", l_idx, m_iter->match->l_idx, r_idx, m_iter->match->r_idx);
                for(i = 0; i < (m_iter->match->l_idx - l_idx); i++) {
                    cgc_printf("< %s\n", ll_iter->lc->pline);
                    ll_iter = ll_iter->next;
                }
                l_idx += i;
                cgc_printf("---\n");
                for(i = 0; i < (m_iter->match->r_idx - r_idx); i++) {
                    cgc_printf("> %s\n", rl_iter->lc->pline);
                    rl_iter = rl_iter->next;
                }
                r_idx += i;
            }
        }

        while (l_idx < m_iter->match->l_idx + m_iter->match->length) {
            ll_iter = ll_iter->next;
            l_idx++;
        }

        while (r_idx < m_iter->match->r_idx + m_iter->match->length) {
            rl_iter = rl_iter->next;
            r_idx++;
        }

        m_iter = m_iter->next;
    }

    if( ll_iter || rl_iter ) {
        found_match = 1;
        cgc_printf("%d,Ea%d,E\n", l_idx, r_idx);
    }

    while (ll_iter) {
        if (cgc_strlen(ll_iter->lc->pline))
            cgc_printf("< %s\n", ll_iter->lc->pline);
        ll_iter = ll_iter->next;
    }
    while (rl_iter) {
        if (cgc_strlen(rl_iter->lc->pline))
            cgc_printf("> %s\n", rl_iter->lc->pline);
        rl_iter = rl_iter->next;
    }

    if (ee == EE_VAL)
        if (cgc_strlen(ee_str))
            cgc_printf(":D = %s\n", ee_str);


    if (!found_match)
        cgc_printf("Files are identical\n");
}

void cgc_compare_files(SFILE *lfile, SFILE *rfile, int ignore_ws, int treat_as_ascii)
{
    cgc_size_t lwordc, llinec;
    cgc_size_t rwordc, rlinec;

    if (!lfile || !rfile) {
        cgc_printf("Both files must be loaded before comparing\n");
        return;
    }

    if (!treat_as_ascii) {
        if (lfile->file_type != rfile->file_type) {
            cgc_printf("File types must be identical in order to compare them.\n"
                   "Alternatively, enable \"Treat as Ascii\"\n");
            return;
        }

        if (lfile->file_type == BINARY) {
            cgc_compare_binary_files(lfile, rfile);
            return;
        }
    }

    if (!g_cached) {
        if (!g_lfile_cmp)
            g_lfile_cmp = cgc_pre_process(lfile, &lwordc, &llinec);
        if (!g_lfile_cmp) {
            cgc_printf("File 1 could not be processed\n");
            return;
        }

        if (!g_rfile_cmp)
            g_rfile_cmp = cgc_pre_process(rfile, &rwordc, &rlinec);
        if(!g_rfile_cmp) {
            cgc_printf("File 2 could not be processed\n");
            return;
        }

        g_best_match = cgc_compare_lines(g_lfile_cmp, g_rfile_cmp, ignore_ws);
        g_cached = 1;
    }

    cgc_print_diff();
}

void cgc_clear_cache(int file_num) {
    match_ll_t *temp = NULL;

    while(g_best_match) {
        temp = g_best_match;
        g_best_match = g_best_match->next;
        cgc_free(temp->match);
        cgc_free(temp);
    }
    g_best_match = NULL;

    if (file_num == 1)
        cgc_free_linecmp_list(&g_lfile_cmp);
    else if(file_num == 2)
        cgc_free_linecmp_list(&g_rfile_cmp);
    g_cached = 0;
}
