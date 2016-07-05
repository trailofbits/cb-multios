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
#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "cmdb_backend.h"

//Genres
static char g_genre_action[] = "Action";
static char g_genre_romance[] = "Romance";
static char g_genre_comedy[] = "Comedy";
static char g_genre_horror[]  = "Horror";
static char g_genre_other[] = "Other";

static size_t g_num_genres = 5;
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

static size_t g_num_mpaa_ratings = 5;
static char *g_all_mpaa_ratings[10] = {
    g_mpaa_g, g_mpaa_pg, g_mpaa_pg13, g_mpaa_r, g_mpaa_unknown
};

static size_t g_list_size = 0;
static size_t g_list_length = 0;
static size_t g_num_rented = 0;

static cmdb_entry_t *g_cmdb = NULL;

static char *check_genre(char *genre)
{
    size_t i = 0;
    for (i = 0; i < g_num_genres; i++) {
        if(strcmp(genre, g_all_genres[i]) == 0)
            return g_all_genres[i];
    }

    return NULL;
}

static char *check_rating(char *rating)
{
    size_t i = 0;
    for (i = 0; i < g_num_mpaa_ratings; i++) {
        if(strcmp(rating, g_all_mpaa_ratings[i]) == 0)
            return g_all_mpaa_ratings[i];
    }

    return NULL;
}

char *get_genre(int id)
{
    if(id < 1 || id > g_num_genres)
        return NULL;

    return g_all_genres[id-1];
}

char *get_rating(int id)
{
    if(id < 1 || id > g_num_mpaa_ratings)
        return NULL;

    return g_all_mpaa_ratings[id-1];
}

size_t get_list_length()
{
    return g_list_length;
}

size_t get_num_rented()
{
    return g_num_rented;
}

int add_movie(char *name, char *desc, short year, char score, char *type, char *mpaa) {
    char *genre = check_genre(type), *rating = check_rating(mpaa);
    if (!genre || !rating)
        return -1;
    if (year < 1800 || year > 2015)
        return -1;
    if (score < 0 || score > 100)
        return -1;

    cmdb_entry_t *row = malloc(sizeof(cmdb_entry_t));
    if (!row)
        return -1;

    row->name = strdup(name);
    row->desc = strdup(desc);
    row->year = year;
    row->score = score;
    row->type = genre;
    row->mpaa = rating;
    row->is_checked_out = 0;

    if (add_entry(row) != 0) {
        free(row);
        return -1;
    }

    return 0;
}

int add_entry(cmdb_entry_t *entry)
{
    if (g_list_size == 0) {
        g_cmdb = malloc(sizeof(cmdb_entry_t) * 16);
        if (!g_cmdb) {
            return -1;
        }
        g_list_size = 16;
    } else if(g_list_size == g_list_length) {
        size_t i;
        cmdb_entry_t *temp_db = g_cmdb;
        g_cmdb = malloc(sizeof(cmdb_entry_t) * g_list_size<<1);
        if (!g_cmdb) {
            g_cmdb = temp_db;
            return -1;
        }
        memcpy(g_cmdb, temp_db, (sizeof(cmdb_entry_t) * g_list_size));

        g_list_size <<= 1;
        free(temp_db);
    }

    memcpy(&g_cmdb[g_list_length++], entry, sizeof(cmdb_entry_t));
    return 0;
}

int delete_entry(int id)
{
    if (!g_list_length)
        return 1;

    if (id < 1 || id > g_list_length)
        return -1;
    id--;

    free(g_cmdb[id].name);
    free(g_cmdb[id].desc);

    if (id+1 < g_list_length)
        memcpy(&g_cmdb[id], &g_cmdb[id+1], sizeof(cmdb_entry_t) * (g_list_length - (id+1)));

    g_list_length--;
    printf("Successfully removed the movie!\n");
    return 0;
}

int rent_entry(int id)
{
    if (id < 1 || id > g_list_length)
        return -1;
    id--;

    if (g_cmdb[id].is_checked_out) {
        printf("Sorry, [%s] is already rented at this time. Please try again later.\n", g_cmdb[id].name);
        return 1;
    }

    g_cmdb[id].is_checked_out = 1;
    g_num_rented++;

    printf("Successfully rented [%s]! Enjoy!\n", g_cmdb[id].name);
    return 0;
}

int return_entry(int id)
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
            printf("Successfully returned [%s]! Thank you!\n", g_cmdb[i].name);
            return 0;
        }
    }

    return -1;
}

cmdb_entry_t *find_entry(char *name)
{
    int i;
    for (i = 0; i < g_list_length; i++) {
        if (strcmp(g_cmdb[i].name, name) == 0)
            return &g_cmdb[i];
    }

    return NULL;
}

cmdb_entry_t *get_entry(int id)
{
    if (id < 1 || id > g_list_length)
        return NULL;

    return &g_cmdb[--id];
}

void print_entry(cmdb_entry_t *entry)
{
    printf("%s (%d, %s) - %s [%d/100]\n", entry->name, entry->year, entry->mpaa, entry->type, entry->score);
    printf("  => %s\n", entry->desc);
}

void print_movies(filter_e filter)
{
    int i;

    if (filter == ALL || filter == OWNED) {
        printf("\nMovies (Full)\n");
        printf("--------------\n");

        for (i = 0; i < g_list_length; i++) {
            printf("[%d] ", i+1);
            print_entry(&g_cmdb[i]);
        }

        printf("--------------\n");
        printf("%d movie(s)\n", g_list_length);
    }
    if (filter == ALL || filter == RENTED) {
        int j = 0;
        printf("\nMovies (Rented)\n");
        printf("--------------\n");

        for (i = 0; (i < g_list_length) && g_num_rented; i++) {
            if (g_cmdb[i].is_checked_out) {
                printf("[%d] ", ++j);
                print_entry(&g_cmdb[i]);
            }
        }

        printf("--------------\n");
        printf("%d movie(s)\n", g_num_rented);
    }
}

void print_genres()
{
    int i;
    for (i = 0; i < g_num_genres; i++) {
#ifndef PATCHED
        printf("\n %d. ", i+1);
        printf(g_all_genres[i]);
#else
        printf("\n %d. %s", i+1, g_all_genres[i]);
#endif
    }
    printf("\n");
}

void print_ratings()
{
    int i;
    for (i = 0; i < g_num_mpaa_ratings; i++)
        printf("\n %d. %s", i+1, g_all_mpaa_ratings[i]);
    printf("\n");
}

//Debug add genre
void dag(char *new_genre)
{
    if (!new_genre)
        return;

    if (g_num_genres < 10)
        g_all_genres[g_num_genres++] = strdup(new_genre);
}

//Debug add rating
void dar(char *new_rating)
{
    if (!new_rating)
        return;

    if (g_num_mpaa_ratings < 10)
        g_all_mpaa_ratings[g_num_mpaa_ratings++] = strdup(new_rating);
}

