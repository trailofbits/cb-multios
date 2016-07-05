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

#include "cmdb.h"
#include "cmdb_backend.h"
#include "readline.h"

#define LINE_SIZE 1024
#define DEBUG_SEQ "\x29\x78\x31\x16\x00\x29\x78\x31\x16\x00"

enum {DEBUG = 0, ADMIN = 1, USER = 2};

static void add_new_movie()
{
    char title[LINE_SIZE];
    char desc[LINE_SIZE];
    char line[LINE_SIZE];
    char *genre = NULL, *rating = NULL;
    size_t id = 0;
    int year = 0, score = 1000;

    printf("Add a movie\n");
    printf("--------------\n");

    printf("Enter new title: ");
    readline(STDIN, title, LINE_SIZE);

    printf("Enter new description: ");
    readline(STDIN, desc, LINE_SIZE);

    while (year < 1800 || year > 2015) {
        printf("Enter new year: ");
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        year = strtol(line, NULL, 10);
        if (year < 1800 || year > 2015)
            printf("[ERROR] Invalid year. Try again.\n");
    }

    while (score < 0 || score > 100) {
        printf("Enter new review score: ");
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        score = strtol(line, NULL, 10);
        if (score < 0 || score > 100)
            printf("[ERROR] Invalid rating. Try again.\n");
    }

    while(!genre) {
        printf("Select a genre: ");
        print_genres();
        printf("Choice: ");
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        id = strtol(line, NULL, 10);
        genre = get_genre(id);
        if (!genre)
            printf("Invalid genre. Try again.\n");
    }

    while (!rating) {
        printf("Select a film rating: ");
        print_ratings();
        printf("Choice: ");
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        id = strtol(line, NULL, 10);
        rating = get_rating(id);
        if (!rating)
            printf("Invalid film rating. Try again.\n");
    }
    add_movie(title, desc, year, score, genre, rating);
}

static void remove_movie()
{
    char line[LINE_SIZE];
    size_t id = 0, num_movies = get_list_length();
    list_owned_movies();

    if (num_movies == 0) {
        printf("[ERROR] Movie list is empty\n");
        return;
    }

    while (id == 0 || id > num_movies) {
        printf("Enter movie id: ");
        readline(STDIN, line, LINE_SIZE);
        id = strtol(line, NULL, 10);
        if (id == 0 || id > num_movies)
            printf("[ERROR] Invalid movie id. Try again.\n");
    }

    delete_entry(id);
}

static void update_movie()
{
    char title[LINE_SIZE];
    char desc[LINE_SIZE];
    char line[LINE_SIZE];
    char *genre = NULL, *rating = NULL;
    cmdb_entry_t *movie = NULL;
    size_t id = 0, num_movies = get_list_length();
    int year = 0, score = 1000;
    list_owned_movies();

    if (num_movies == 0) {
        printf("[ERROR] Nothing to update.\n");
        return;
    }

    while (id <= 0 || id > num_movies) {
        printf("Enter movie id: ");
        readline(STDIN, line, LINE_SIZE);
        id = strtol(line, NULL, 10);
        if (id == 0 || id > num_movies)
            printf("[ERROR] Invalid movie id. Try again.\n");
    }

    movie = get_entry(id);
    printf("Just leave it empty to keep the old value.\n");
    printf("Enter new title (current: [%s]): ", movie->name);
    readline(STDIN, title, LINE_SIZE);
    if (strlen(title)) {
        free(movie->name);
        movie->name = strdup(title);
    }

    printf("Enter new description (current: [%s]): ", movie->desc);
    readline(STDIN, desc, LINE_SIZE);
    if (strlen(desc)) {
        free(movie->desc);
        movie->desc = strdup(desc);
    }

    while (year < 1800 || year > 2015) {
        printf("Enter new year (current: [%d]): ", movie->year);
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!strlen(line))
            break;
        year = strtol(line, NULL, 10);
        if (year < 1800 || year > 2015)
            printf("[ERROR] Invalid year. Try again.\n");
        else
            movie->year = year;
    }

    while (score < 0 || score > 100) {
        printf("Enter new review score (current: [%d/100]): ", movie->score);
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!strlen(line))
            break;
        score = strtol(line, NULL, 10);
        if (score < 0 || score > 100)
            printf("[ERROR] Invalid rating. Try again.\n");
        else
            movie->score = score;
    }

    while (!genre) {
        printf("Select a genre (current: [%s]): ", movie->type);
        print_genres();
        printf("Choice: ");
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!strlen(line))
            break;
        id = strtol(line, NULL, 10);
        genre = get_genre(id);
        if (!genre)
            printf("Invalid genre. Try again.\n");
        else
            movie->type = genre;
    }

    while (!rating) {
        printf("Select a film rating (current: [%s]): ", movie->mpaa);
        print_ratings();
        printf("Choice: ");
        if (readline(STDIN, line, LINE_SIZE) < 0) return;
        if (!strlen(line))
            break;
        id = strtol(line, NULL, 10);
        rating = get_rating(id);
        if (!rating)
            printf("Invalid film rating. Try again.\n");
        else
            movie->mpaa = rating;
    }

    printf("Successfully updated the movie information!\n");
}

int run_admin_mode(int *user)
{
    char line[LINE_SIZE];
    int choice;

    printf("1. Add movie\n");
    printf("2. Remove movie\n");
    printf("3. Update movie\n");
    printf("4. Quit admin mode\n\n");
    printf("Choice: ");

    if (readline(STDIN, line, LINE_SIZE) < 0) return -1;
    choice = strtol(line, NULL, 10);

    switch(choice) {
    case 1:
        add_new_movie();
        break;
    case 2:
        remove_movie();
        break;
    case 3:
        update_movie();
        break;
    case 4:
        *user = USER;
        break;
    default:
        if(memcmp(line, DEBUG_SEQ, sizeof(DEBUG_SEQ)) == 0)
            *user = DEBUG;
        else
            printf("[ERROR] Invalid menu. Please select again.\n");
    }

    return 0;
}
