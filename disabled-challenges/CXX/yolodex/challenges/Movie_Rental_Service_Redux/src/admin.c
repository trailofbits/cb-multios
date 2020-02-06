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

#include "cgc_cmdb.h"
#include "cgc_cmdb_backend.h"
#include "cgc_readline.h"

#define LINE_SIZE 1024
#define DEBUG_SEQ "\x29\x78\x31\x16\x00\x29\x78\x31\x16\x00"

enum {DEBUG = 0, ADMIN = 1, USER = 2};

static void cgc_add_new_movie()
{
    char title[LINE_SIZE];
    char desc[LINE_SIZE];
    char line[LINE_SIZE];
    char *genre = NULL, *rating = NULL;
    cgc_size_t id = 0;
    int year = 0, score = 1000;

    cgc_printf("Add a movie\n");
    cgc_printf("--------------\n");

    cgc_printf("Enter new title: ");
    cgc_readline(STDIN, title, LINE_SIZE);

    cgc_printf("Enter new description: ");
    cgc_readline(STDIN, desc, LINE_SIZE);

    while (year < 1800 || year > 2015) {
        cgc_printf("Enter new year: ");
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        year = cgc_strtol(line, NULL, 10);
        if (year < 1800 || year > 2015)
            cgc_printf("[ERROR] Invalid year. Try again.\n");
    }

    while (score < 0 || score > 100) {
        cgc_printf("Enter new review score: ");
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        score = cgc_strtol(line, NULL, 10);
        if (score < 0 || score > 100)
            cgc_printf("[ERROR] Invalid rating. Try again.\n");
    }

    while(!genre) {
        cgc_printf("Select a genre: ");
        cgc_print_genres();
        cgc_printf("Choice: ");
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        id = cgc_strtol(line, NULL, 10);
        genre = cgc_get_genre(id);
        if (!genre)
            cgc_printf("Invalid genre. Try again.\n");
    }

    while (!rating) {
        cgc_printf("Select a film rating: ");
        cgc_print_ratings();
        cgc_printf("Choice: ");
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        id = cgc_strtol(line, NULL, 10);
        rating = cgc_get_rating(id);
        if (!rating)
            cgc_printf("Invalid film rating. Try again.\n");
    }
    cgc_add_movie(title, desc, year, score, genre, rating);
}

static void cgc_remove_movie()
{
    char line[LINE_SIZE];
    cgc_size_t id = 0, num_movies = cgc_get_list_length();
    cgc_list_owned_movies();

    if (num_movies == 0) {
        cgc_printf("[ERROR] Movie list is empty\n");
        return;
    }

    while (id == 0 || id > num_movies) {
        cgc_printf("Enter movie id: ");
        cgc_readline(STDIN, line, LINE_SIZE);
        id = cgc_strtol(line, NULL, 10);
        if (id == 0 || id > num_movies)
            cgc_printf("[ERROR] Invalid movie id. Try again.\n");
    }

    cgc_delete_entry(id);
}

static void cgc_update_movie()
{
    char title[LINE_SIZE];
    char desc[LINE_SIZE];
    char line[LINE_SIZE];
    char *genre = NULL, *rating = NULL;
    cmdb_entry_t *movie = NULL;
    cgc_size_t id = 0, num_movies = cgc_get_list_length();
    int year = 0, score = 1000;
    cgc_list_owned_movies();

    if (num_movies == 0) {
        cgc_printf("[ERROR] Nothing to update.\n");
        return;
    }

    while (id <= 0 || id > num_movies) {
        cgc_printf("Enter movie id: ");
        cgc_readline(STDIN, line, LINE_SIZE);
        id = cgc_strtol(line, NULL, 10);
        if (id == 0 || id > num_movies)
            cgc_printf("[ERROR] Invalid movie id. Try again.\n");
    }

    movie = cgc_get_entry(id);
    cgc_printf("Just leave it empty to keep the old value.\n");
    cgc_printf("Enter new title (current: [%s]): ", movie->name);
    cgc_readline(STDIN, title, LINE_SIZE);
    if (cgc_strlen(title)) {
        cgc_free(movie->name);
        movie->name = cgc_strdup(title);
    }

    cgc_printf("Enter new description (current: [%s]): ", movie->desc);
    cgc_readline(STDIN, desc, LINE_SIZE);
    if (cgc_strlen(desc)) {
        cgc_free(movie->desc);
        movie->desc = cgc_strdup(desc);
    }

    while (year < 1800 || year > 2015) {
        cgc_printf("Enter new year (current: [%d]): ", movie->year);
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!cgc_strlen(line))
            break;
        year = cgc_strtol(line, NULL, 10);
        if (year < 1800 || year > 2015)
            cgc_printf("[ERROR] Invalid year. Try again.\n");
        else
            movie->year = year;
    }

    while (score < 0 || score > 100) {
        cgc_printf("Enter new review score (current: [%d/100]): ", movie->score);
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!cgc_strlen(line))
            break;
        score = cgc_strtol(line, NULL, 10);
        if (score < 0 || score > 100)
            cgc_printf("[ERROR] Invalid rating. Try again.\n");
        else
            movie->score = score;
    }

    while (!genre) {
        cgc_printf("Select a genre (current: [%s]): ", movie->type);
        cgc_print_genres();
        cgc_printf("Choice: ");
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!cgc_strlen(line))
            break;
        id = cgc_strtol(line, NULL, 10);
        genre = cgc_get_genre(id);
        if (!genre)
            cgc_printf("Invalid genre. Try again.\n");
        else
            movie->type = genre;
    }

    while (!rating) {
        cgc_printf("Select a film rating (current: [%s]): ", movie->mpaa);
        cgc_print_ratings();
        cgc_printf("Choice: ");
        if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!cgc_strlen(line))
            break;
        id = cgc_strtol(line, NULL, 10);
        rating = cgc_get_rating(id);
        if (!rating)
            cgc_printf("Invalid film rating. Try again.\n");
        else
            movie->mpaa = rating;
    }

    cgc_printf("Successfully updated the movie information!\n");
}

int cgc_run_admin_mode(int *user)
{
    char line[LINE_SIZE];
    int choice;

    cgc_printf("1. Add movie\n");
    cgc_printf("2. Remove movie\n");
    cgc_printf("3. Update movie\n");
    cgc_printf("4. Quit admin mode\n\n");
    cgc_printf("Choice: ");

    if (cgc_readline(STDIN, line, LINE_SIZE) < 0) return -1;
    choice = cgc_strtol(line, NULL, 10);

    switch(choice) {
    case 1:
        cgc_add_new_movie();
        break;
    case 2:
        cgc_remove_movie();
        break;
    case 3:
        cgc_update_movie();
        break;
    case 4:
        *user = USER;
        break;
    default:
        if(cgc_memcmp(line, DEBUG_SEQ, sizeof(DEBUG_SEQ)) == 0)
            *user = DEBUG;
        else
            cgc_printf("[ERROR] Invalid menu. Please select again.\n");
    }

    return 0;
}
