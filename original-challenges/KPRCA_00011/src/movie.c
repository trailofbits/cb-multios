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

#include <stdlib.h>
#include <string.h>

#include "movie.h"

const char* movie_g2s(enum genre_t genre)
{
 const char *genre_str = NULL;
  switch (genre)
  {
    case G_ACTION:
      genre_str = "Action"; break;
    case G_ROMANCE:
      genre_str = "Romance"; break;
    case G_COMEDY:
      genre_str = "Comedy"; break;
    case G_HORROR:
      genre_str = "Horror"; break;
    default:
      genre_str = "Other"; break;
  }
  return genre_str;
}

const char* movie_r2s(enum rating_t rating)
{
  const char *rating_str = NULL;
  switch (rating)
  {
    case R_G:
      rating_str = "G"; break;
    case R_PG:
      rating_str = "PG"; break;
    case R_PG13:
      rating_str = "PG13"; break;
    case R_R:
      rating_str = "R"; break;
    default:
      rating_str = "Unknown"; break;
  }
  return rating_str;
}

int movie_add(movie_list_t *list, movie_t *movie)
{
  if (list)
  {
    movie_node_t *node = (movie_node_t *) malloc(sizeof(movie_node_t));
    if (node == NULL)
      return -1;

    if (*list == NULL)
    {
      node->movie = movie;
      node->next = NULL;
      *list = node;
      return 0;
    }

    movie_node_t *tmp = movie_find(*list, movie->title);
    if (tmp)
    {
      if (node) free(node);
      return -1;
    }

    tmp = *list;
    while (1)
    {
      if (tmp->next == NULL) break;
      tmp = tmp->next;
    }

    node->movie = movie;
    node->next = NULL;
    tmp->next = node;
    return 0;
  }
  return -1;
}

void free_movie(movie_t *movie)
{
  if (movie)
  {
    if (movie->title)
      free(movie->title);
    if (movie->desc)
      free(movie->desc);
    free(movie);
  }
}

int movie_delete(movie_list_t *list, int id)
{
  if (list)
  {
    movie_node_t *prev = NULL;
    movie_node_t *tmp = *list;

    int n = 1;
    if (tmp && id == 1)
    {
      *list = tmp->next;
      free(tmp);
      return 0;
    }

    prev = *list;
    tmp = prev->next;

    while (tmp != NULL)
    {
      n++;
      if (id == n)
      {
        prev->next = tmp->next;
        free(tmp);
        break;
      }
      prev = tmp;
      tmp = tmp->next;
    }
    return 0;
  }
  return -1;
}

int movie_update(movie_t *movie)
{
  
  return 0;
}

movie_node_t* movie_find(movie_list_t list, char *title)
{
  if (list)
  {
    movie_node_t *cur = list;
    while (cur != NULL)
    {
      if (strcmp(cur->movie->title, title) == 0)
        return cur;
      cur = cur->next;
    }
  }
  return NULL;
}

movie_node_t* movie_find_by_id(movie_list_t list, int id)
{
  if (list)
  {
    int n = 0;
    movie_node_t *cur = list;
    while (cur != NULL)
    {
      n++;
      if (id == n)
        return cur;
      cur = cur->next;
    }
  }
  return NULL;
}
