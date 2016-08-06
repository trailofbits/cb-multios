/*
 * Author: Brian Pak <brian.pak@kapricasecurity.com>
 *
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#ifndef MOVIE_H
#define MOVIE_H

enum genre_t {
  G_ACTION = 1,
  G_ROMANCE,
  G_COMEDY,
  G_HORROR,
  G_OTHER
};

enum rating_t {
  R_G = 1,
  R_PG,
  R_PG13,
  R_R,
  R_UNKNOWN
};

typedef struct movie {
  char *title;
  char *desc;
  int year;
  int score;
  enum genre_t genre;
  enum rating_t rating;
  void (*print_info)(int, struct movie *);
} movie_t;

typedef struct movie_node {
  movie_t *movie;
  struct movie_node *next;
} movie_node_t;

typedef movie_node_t * movie_list_t;

const char* movie_g2s(enum genre_t);
const char* movie_r2s(enum rating_t);

int movie_add(movie_list_t *, movie_t *);
int movie_delete(movie_list_t *, int);
int movie_update(movie_t *);
movie_node_t* movie_find(movie_list_t, char *);
movie_node_t* movie_find_by_id(movie_list_t, int);
void free_movie(movie_t *);

#endif
