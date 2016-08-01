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
#include "readline.h"

#define LINE_SIZE 1024

enum {DEBUG = 0, ADMIN = 1, USER = 2};

static char *admin_username = "root";
static char *admin_password = NULL; //jlCLrhQ

static unsigned int a=123848, b=12384812, c=84813, d=9837149;
static unsigned int rng()
{
    unsigned int temp = a ^  (a << 7);
    a = b; b = c; c = d;
    return d = (d ^ (d >> 8)) ^ (temp ^ (temp >> 19));
}

static char *random_password()
{
    char *pw = malloc(8);
    if (!pw) {
        pw = admin_username;
        return pw;
    }
    pw[7] = '\0';
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(rng() % 5) {
            if (rng()  % 2)
                pw[i] = rng() % 26 + 'A';
            else
                pw[i] = rng() % 26 + 'a';
        } else {
            pw[i] = rng() % 17 + '0';
        }
    }

    return pw;
}

static void list_movies()
{
    list_all_movies();
}

static void user_rent_movie()
{
    size_t id = 0, num_movies = get_num_owned_movies();
    char line[LINE_SIZE];
    list_owned_movies();

    if (num_movies == 0) {
        printf("[ERROR] Movie list is empty. Please try again later.\n");
        return;
    }

    while(id == 0 || id > num_movies) {
        printf("Enter movie id: ");
        readline(STDIN, line, LINE_SIZE);
        id = strtol(line, NULL, 10);
        if (id == 0 || id > num_movies)
            printf("[ERROR] Invalid movie id. Try again.\n");
    }

    rent_movie(id);
}

static void user_return_movie()
{
    size_t id = 0, num_rented = get_num_rented_movies();
    char line[LINE_SIZE];
    list_rented_movies();

    if (num_rented == 0) {
        printf("[ERROR] All the movies are in our inventory.\n");
        return;
    }

    while(id == 0 || id > num_rented) {
        printf("Enter movie id: ");
        readline(STDIN, line, LINE_SIZE);
        id = strtol(line, NULL, 10);
        if (id == 0 || id > num_rented)
            printf("[ERROR] Invalid movie id. Try again.\n");
    }

    return_movie(id);
}

static int admin_login()
{
    char line[LINE_SIZE];
    printf("username: ");
    readline(STDIN, line, LINE_SIZE);
    if (strcmp(line, admin_username) != 0) {
        printf("[ERROR] Permission Denied: Wrong credentials\n");
        return -1;
    }

    printf("password: ");
    readline(STDIN, line, LINE_SIZE);
    if (strcmp(line, admin_password) != 0) {
        printf("[ERROR] Permission Denied: Wrong credentials\n");
        return -1;
    }

    return 0;
}

int run_user_mode(int *user)
{
    if (admin_password == NULL)
        admin_password = random_password();

    char line[LINE_SIZE];
    int choice;

    printf("1. List movies\n");
    printf("2. Rent movie\n");
    printf("3. Return movie\n");
    printf("4. Admin mode\n");
    printf("5. Exit\n\n");
    printf("Choice: ");

    readline(STDIN, line, LINE_SIZE);
    choice = strtol(line, NULL, 10);

    switch(choice) {
    case 1:
        list_movies();
        break;
    case 2:
        user_rent_movie();
        break;
    case 3:
        user_return_movie();
        break;
    case 4:
        if (admin_login() == 0)
            *user = ADMIN;
        break;
    case 5:
        return 1;
        break;
    default:
        printf("[ERROR] Invalid menu. Please select again.\n");
    }

    return 0;
}
