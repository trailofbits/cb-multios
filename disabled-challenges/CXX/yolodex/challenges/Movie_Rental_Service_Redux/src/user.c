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
#include "cgc_readline.h"

#define LINE_SIZE 1024

enum {DEBUG = 0, ADMIN = 1, USER = 2};

static char *admin_username = "root";
static char *admin_password = NULL; //jlCLrhQ

static unsigned int a=123848, b=12384812, c=84813, d=9837149;
static unsigned int cgc_rng()
{
    unsigned int temp = a ^  (a << 7);
    a = b; b = c; c = d;
    return d = (d ^ (d >> 8)) ^ (temp ^ (temp >> 19));
}

static char *cgc_random_password()
{
    char *pw = cgc_malloc(8);
    if (!pw) {
        pw = admin_username;
        return pw;
    }
    pw[7] = '\0';
    int i = 0;
    for (i = 0; i < 7; i++) {
        if(cgc_rng() % 5) {
            if (cgc_rng()  % 2)
                pw[i] = cgc_rng() % 26 + 'A';
            else
                pw[i] = cgc_rng() % 26 + 'a';
        } else {
            pw[i] = cgc_rng() % 17 + '0';
        }
    }

    return pw;
}

static void cgc_list_movies()
{
    cgc_list_all_movies();
}

static void cgc_user_rent_movie()
{
    cgc_size_t id = 0, num_movies = cgc_get_num_owned_movies();
    char line[LINE_SIZE];
    cgc_list_owned_movies();

    if (num_movies == 0) {
        cgc_printf("[ERROR] Movie list is empty. Please try again later.\n");
        return;
    }

    while(id == 0 || id > num_movies) {
        cgc_printf("Enter movie id: ");
        cgc_readline(STDIN, line, LINE_SIZE);
        id = cgc_strtol(line, NULL, 10);
        if (id == 0 || id > num_movies)
            cgc_printf("[ERROR] Invalid movie id. Try again.\n");
    }

    cgc_rent_movie(id);
}

static void cgc_user_return_movie()
{
    cgc_size_t id = 0, num_rented = cgc_get_num_rented_movies();
    char line[LINE_SIZE];
    cgc_list_rented_movies();

    if (num_rented == 0) {
        cgc_printf("[ERROR] All the movies are in our inventory.\n");
        return;
    }

    while(id == 0 || id > num_rented) {
        cgc_printf("Enter movie id: ");
        cgc_readline(STDIN, line, LINE_SIZE);
        id = cgc_strtol(line, NULL, 10);
        if (id == 0 || id > num_rented)
            cgc_printf("[ERROR] Invalid movie id. Try again.\n");
    }

    cgc_return_movie(id);
}

static int cgc_admin_login()
{
    char line[LINE_SIZE];
    cgc_printf("username: ");
    cgc_readline(STDIN, line, LINE_SIZE);
    if (cgc_strcmp(line, admin_username) != 0) {
        cgc_printf("[ERROR] Permission Denied: Wrong credentials\n");
        return -1;
    }

    cgc_printf("password: ");
    cgc_readline(STDIN, line, LINE_SIZE);
    if (cgc_strcmp(line, admin_password) != 0) {
        cgc_printf("[ERROR] Permission Denied: Wrong credentials\n");
        return -1;
    }

    return 0;
}

int cgc_run_user_mode(int *user)
{
    if (admin_password == NULL)
        admin_password = cgc_random_password();

    char line[LINE_SIZE];
    int choice;

    cgc_printf("1. List movies\n");
    cgc_printf("2. Rent movie\n");
    cgc_printf("3. Return movie\n");
    cgc_printf("4. Admin mode\n");
    cgc_printf("5. Exit\n\n");
    cgc_printf("Choice: ");

    cgc_readline(STDIN, line, LINE_SIZE);
    choice = cgc_strtol(line, NULL, 10);

    switch(choice) {
    case 1:
        cgc_list_movies();
        break;
    case 2:
        cgc_user_rent_movie();
        break;
    case 3:
        cgc_user_return_movie();
        break;
    case 4:
        if (cgc_admin_login() == 0)
            *user = ADMIN;
        break;
    case 5:
        return 1;
        break;
    default:
        cgc_printf("[ERROR] Invalid menu. Please select again.\n");
    }

    return 0;
}
