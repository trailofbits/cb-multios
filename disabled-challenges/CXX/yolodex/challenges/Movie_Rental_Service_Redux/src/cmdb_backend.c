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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_cmdb_backend.h"

//Genres
static char g_genre_action[] = "Action";
static char g_genre_romance[] = "Romance";
static char g_genre_comedy[] = "Comedy";
static char g_genre_horror[]  = "Horror";
static char g_genre_other[] = "Other";

static cgc_size_t g_num_genres = 5;
static char *g_all_genres[10] = {
    g_genre_action, g_genre_romance, g_genre_comedy,
    g_genre_horror, g_genre_other
};

//MPAA Rating
static char g_mpaa_g[] = "G";
static char g_mpaa_pg[] = "PG";
static char g_mpaa_pg13[] = "PG13";
static char g_mpaa_r[] = "R";
static char g_mpaa_unknown[] = "Unknown";

static cgc_size_t g_num_mpaa_ratings = 5;
static char *g_all_mpaa_ratings[10] = {
    g_mpaa_g, g_mpaa_pg, g_mpaa_pg13, g_mpaa_r, g_mpaa_unknown
};

static cgc_size_t g_list_size = 0;
static cgc_size_t g_list_length = 0;
static cgc_size_t g_num_rented = 0;

static cmdb_entry_t *g_cmdb = NULL;

static char *cgc_check_genre(char *genre)
{
    cgc_size_t i = 0;
    for (i = 0; i < g_num_genres; i++) {
        if(cgc_strcmp(genre, g_all_genres[i]) == 0)
            return g_all_genres[i];
    }

    return NULL;
}

static char *cgc_check_rating(char *rating)
{
    cgc_size_t i = 0;
    for (i = 0; i < g_num_mpaa_ratings; i++) {
        if(cgc_strcmp(rating, g_all_mpaa_ratings[i]) == 0)
            return g_all_mpaa_ratings[i];
    }

    return NULL;
}

char *cgc_get_genre(int id)
{
    if(id < 1 || id > g_num_genres)
        return NULL;

    return g_all_genres[id-1];
}

char *cgc_get_rating(int id)
{
    if(id < 1 || id > g_num_mpaa_ratings)
        return NULL;

    return g_all_mpaa_ratings[id-1];
}

cgc_size_t cgc_get_list_length()
{
    return g_list_length;
}

cgc_size_t cgc_get_num_rented()
{
    return g_num_rented;
}

int cgc_add_movie(char *name, char *desc, short year, char score, char *type, char *mpaa) {
    char *genre = cgc_check_genre(type), *rating = cgc_check_rating(mpaa);
    if (!genre || !rating)
        return -1;
    if (year < 1800 || year > 2015)
        return -1;
    if (score < 0 || score > 100)
        return -1;

    cmdb_entry_t *row = cgc_malloc(sizeof(cmdb_entry_t));
    if (!row)
        return -1;

    row->name = cgc_strdup(name);
    row->desc = cgc_strdup(desc);
    row->year = year;
    row->score = score;
    row->type = genre;
    row->mpaa = rating;
    row->is_checked_out = 0;

    if (cgc_add_entry(row) != 0) {
        cgc_free(row);
        return -1;
    }

    return 0;
}

int cgc_add_entry(cmdb_entry_t *entry)
{
    if (g_list_size == 0) {
        g_cmdb = cgc_malloc(sizeof(cmdb_entry_t) * 16);
        if (!g_cmdb) {
            return -1;
        }
        g_list_size = 16;
    } else if(g_list_size == g_list_length) {
        cgc_size_t i;
        cmdb_entry_t *temp_db = g_cmdb;
        g_cmdb = cgc_malloc(sizeof(cmdb_entry_t) * g_list_size<<1);
        if (!g_cmdb) {
            g_cmdb = temp_db;
            return -1;
        }
        cgc_memcpy(g_cmdb, temp_db, (sizeof(cmdb_entry_t) * g_list_size));

        g_list_size <<= 1;
        cgc_free(temp_db);
    }

    cgc_memcpy(&g_cmdb[g_list_length++], entry, sizeof(cmdb_entry_t));
    return 0;
}

int cgc_delete_entry(int id)
{
    if (!g_list_length)
        return 1;

    if (id < 1 || id > g_list_length)
        return -1;
    id--;

    cgc_free(g_cmdb[id].name);
    cgc_free(g_cmdb[id].desc);

    if (id+1 < g_list_length)
        cgc_memcpy(&g_cmdb[id], &g_cmdb[id+1], sizeof(cmdb_entry_t) * (g_list_length - (id+1)));

    g_list_length--;
    cgc_printf("Successfully removed the movie!\n");
    return 0;
}

int cgc_rent_entry(int id)
{
    if (id < 1 || id > g_list_length)
        return -1;
    id--;

    if (g_cmdb[id].is_checked_out) {
        cgc_printf("Sorry, [%s] is already rented at this time. Please try again later.\n", g_cmdb[id].name);
        return 1;
    }

    g_cmdb[id].is_checked_out = 1;
    g_num_rented++;

    cgc_printf("Successfully rented [%s]! Enjoy!\n", g_cmdb[id].name);
    return 0;
}

int cgc_return_entry(int id)
{
    if (id < 1 || id > g_num_rented)
        return -1;

    int i = 0, j = 0;
    for (i = 0; i < g_list_length; i++) {
        if (g_cmdb[i].is_checked_out)
            j++;
        else
            continue;

        if (j == id) {
            g_cmdb[i].is_checked_out = 0;
            g_num_rented--;
            cgc_printf("Successfully returned [%s]! Thank you!\n", g_cmdb[i].name);
            return 0;
        }
    }

    return -1;
}

cmdb_entry_t *cgc_find_entry(char *name)
{
    int i;
    for (i = 0; i < g_list_length; i++) {
        if (cgc_strcmp(g_cmdb[i].name, name) == 0)
            return &g_cmdb[i];
    }

    return NULL;
}

cmdb_entry_t *cgc_get_entry(int id)
{
    if (id < 1 || id > g_list_length)
        return NULL;

    return &g_cmdb[--id];
}

void cgc_print_entry(cmdb_entry_t *entry)
{
    cgc_printf("%s (%d, %s) - %s [%d/100]\n", entry->name, entry->year, entry->mpaa, entry->type, entry->score);
    cgc_printf("  => %s\n", entry->desc);
}

void cgc_print_movies(filter_e filter)
{
    int i;

    if (filter == ALL || filter == OWNED) {
        cgc_printf("\nMovies (Full)\n");
        cgc_printf("--------------\n");

        for (i = 0; i < g_list_length; i++) {
            cgc_printf("[%d] ", i+1);
            cgc_print_entry(&g_cmdb[i]);
        }

        cgc_printf("--------------\n");
        cgc_printf("%d movie(s)\n", g_list_length);
    }
    if (filter == ALL || filter == RENTED) {
        int j = 0;
        cgc_printf("\nMovies (Rented)\n");
        cgc_printf("--------------\n");

        for (i = 0; (i < g_list_length) && g_num_rented; i++) {
            if (g_cmdb[i].is_checked_out) {
                cgc_printf("[%d] ", ++j);
                cgc_print_entry(&g_cmdb[i]);
            }
        }

        cgc_printf("--------------\n");
        cgc_printf("%d movie(s)\n", g_num_rented);
    }
}

void cgc_print_genres()
{
    int i;
    for (i = 0; i < g_num_genres; i++) {
#ifndef PATCHED
        cgc_printf("\n %d. ", i+1);
        cgc_printf(g_all_genres[i]);
#else
        cgc_printf("\n %d. %s", i+1, g_all_genres[i]);
#endif
    }
    cgc_printf("\n");
}

void cgc_print_ratings()
{
    int i;
    for (i = 0; i < g_num_mpaa_ratings; i++)
        cgc_printf("\n %d. %s", i+1, g_all_mpaa_ratings[i]);
    cgc_printf("\n");
}

//Debug add genre
void cgc_dag(char *new_genre)
{
    if (!new_genre)
        return;

    if (g_num_genres < 10)
        g_all_genres[g_num_genres++] = cgc_strdup(new_genre);
}

//Debug add rating
void cgc_dar(char *new_rating)
{
    if (!new_rating)
        return;

    if (g_num_mpaa_ratings < 10)
        g_all_mpaa_ratings[g_num_mpaa_ratings++] = cgc_strdup(new_rating);
}

