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

#include <libcgc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"

void quit();
void print_movie_detail(int, movie_t *);

movie_t default_movies[] = {
  {"The Shawshank Redemption", "Two imprisoned men bond over a number of years, finding solace and eventual\n     redemption through acts of common decency.", 1994, 93, G_OTHER, R_R, NULL},
  {"The Godfather", "The aging patriarch of an organized crime dynasty transfers control of his clandestine\n     empire to his reluctant son.", 1972, 92, G_OTHER, R_R, NULL},
  {"The Dark Knight", "When Batman, Gordon have Harvey Dent launch an assault on the mob, they let the clown\n     out of the box, the Joker, bent on turning Gotham on itself and bringing any heroes\n     down to his level.", 2008, 90, G_ACTION, R_PG13, NULL},
  {"Inception", "A thief who steals corporate secrets through use of dream-sharing technology is given the\n     inverse task of planting an idea into the mind of a CEO.", 2010, 88, G_ACTION, R_PG13, NULL},
  {"The Matrix", "A computer hacker learns from mysterious rebels about the true nature of his reality and\n     his role in the war against its controllers.", 1999, 87, G_ACTION, R_R, NULL},
  {"Modern Times", "The Tramp struggles to live in modern industrial society with the help of a young\n     homeless woman.", 1936, 86, G_COMEDY, R_G, NULL},
  {"About Time", "At the age of 21, Tim discovers he can travel in time and change what happens and has\n     happened in his own life. His decision to make his world a better place by getting\n     a girlfriend turns out not to be as easy as you might think.", 2013, 78, G_ROMANCE, R_R, NULL},
  {"Yes Man", "A guy challenges himself to say \"yes\" to everything for an entire year.", 2008, 69, G_COMEDY, R_PG13, NULL},
  {"The Conjuring", "Paranormal investigators Ed and Lorraine Warren work to help a family terrorized\n     by a dark presence in their farmhouse.", 2013, 75, G_HORROR, R_R, NULL},
  {"The Lion King", "Lion cub and future king Simba searches for his identity. His eagerness to please others\n     and penchant for testing his boundaries sometimes gets him into trouble.", 1994, 85, G_OTHER, R_G, NULL},
};

char g_password[21];
unsigned int g_num_movies = 0;
movie_list_t movies_full;
movie_list_t movies_rented;

void initialize()
{
  unsigned int i, rand;
  char c;
  movie_t *movie;
  printf("\n   . . . Initializing the inventory . . .\n         (movie info from IMDb.com)\n");

  for (i = 0; i <= sizeof(g_password)/sizeof(g_password[0]); ++i)
  {
    random(&c, sizeof(c), NULL);
    random(&rand, sizeof(rand), NULL);
    if (c & 1)
      g_password[i] = 'A' + (rand % 26);
    else
      g_password[i] = 'a' + (rand % 26);
  }
  g_password[i] = '\0';

  for (i = 0; i < sizeof(default_movies)/sizeof(default_movies[0]); ++i)
  {
    movie = (movie_t *) malloc(sizeof(movie_t));
    if (movie == NULL)
      goto fail;
    memset(movie, '\0', sizeof(movie_t));
    movie->title = (char *) malloc(strlen(default_movies[i].title) + 1);
    movie->desc = (char *) malloc(strlen(default_movies[i].desc) + 1);
    if (movie->title == NULL || movie->desc == NULL)
      goto fail;
    strcpy(movie->title, default_movies[i].title);
    strcpy(movie->desc, default_movies[i].desc);
    movie->year = default_movies[i].year;
    movie->score = default_movies[i].score;
    movie->genre = default_movies[i].genre;
    movie->rating = default_movies[i].rating;
    movie->print_info = &print_movie_detail;
    movie_add(&movies_full, movie);
  }
  return;

fail:
  printf("[ERROR] Initialization failed. Exit.\n");
  quit();
}

int readuntil(int fd, char *buf, size_t len, char delim)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    size_t rx;
    if (receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
        if (*(c++) == delim)
            break;
    }
    *(c-1) = '\0';
    return c - buf;
}

void print_movie_detail(int id, movie_t *movie)
{
  char *rating_str, *genre_str;
  char format[] = "[%d] %s (%d, %s) - %s [%d/100]\n  => %s\n";

  if (movie)
  {
    switch (movie->rating)
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

    switch (movie->genre)
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

    printf(format, id, movie->title, movie->year,
                             rating_str, genre_str, movie->score, movie->desc);
  }
}

void list_movies()
{
  int num_movies = 0;
  movie_node_t *node;

  /* Movie list (full) */
  printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  printf("--------------\n%d movie(s)\n", num_movies);

  /* Movie list (rented) */
  num_movies = 0;
  printf("\nMovies (Rented)\n--------------\n");
  for (node = movies_rented; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  printf("--------------\n%d movie(s)\n", num_movies);
}

void rent_movie()
{
  movie_node_t *node;
  unsigned int movie_id, num_movies = 0;
  char buf[256];

  /* Present the full movie list with index */
  printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    /* Shouldn't really happen with successful init */
    printf("[ERROR] Movie list is empty. Please try again later.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    printf("Enter movie id: ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = strtoul(buf, NULL, 10);
    if (movie_id >=1 && movie_id <= num_movies)
      break;
    printf("[ERROR] Invalid movie id. Try again.\n");
  }

  /* Check if the movie isn't rented already */
  movie_node_t *tmp = movie_find_by_id(movies_full, movie_id);
  movie_t *movie = tmp->movie;
  tmp = movie_find(movies_rented, movie->title);
  if (tmp)
  {
    printf("Sorry, [%s] is already rented at this time. Please try again later.\n", tmp->movie->title);
    return;
  }

  /* If not in rental list, insert it into rental list */
  tmp = movie_find_by_id(movies_full, movie_id);
  if (movie_add(&movies_rented, tmp->movie) != 0)
    printf("[ERROR] Failed to rent. Please try again later.\n");
  else
    printf("Successfully rented [%s]! Enjoy!\n", tmp->movie->title);
}

void return_movie()
{
  char buf[256];
  unsigned int movie_id, num_movies = 0;
  movie_node_t *node;

  /* Present the list of rented movies with index */
  printf("\nMovies (Rented)\n--------------\n");
  for (node = movies_rented; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    printf("[ERROR] All the movies are in our inventory.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    printf("Enter movie id: ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = strtoul(buf, NULL, 10);
    //if (movie_id >= 1 && movie_id <= g_num_movies)
    //  break;
    if (movie_id >= 1 && movie_id <= num_movies)
      break;
    printf("[ERROR] Invalid movie id. Try again.\n");
  }

  /* Remove the movie entry in rental list */
  movie_node_t *tmp = movie_find_by_id(movies_rented, movie_id);
  if (tmp == NULL)
  {
    /* Shouldn't happen */
    printf("Sorry, we have some issues here. Please try again later.\n");
    return;
  }

  if (movie_delete(&movies_rented, movie_id) != 0)
  {
    /* Shouldn't happen */
    printf("[ERROR] Failed to return the movie. Please try again.\n");
    return;
  }

  printf("Successfully returned [%s]! Thank you!\n", tmp->movie->title);
}

int login()
{
  int admin = 0;
  char buf[64];
  char username[] = "admin";

  printf("username: ");
  readuntil(STDIN, buf, sizeof(buf), '\n');
  if (strcmp(username, buf) != 0)
  {
    printf("[ERROR] Permission Denied: Wrong credentials\n");
    return admin;
  }

  printf("password: ");
#if PATCHED
  readuntil(STDIN, buf, sizeof(buf), '\n');
#else
  readuntil(STDIN, buf, sizeof(buf) + 4, '\n');
#endif
  if (strcmp(g_password, buf) != 0)
  {
    printf("[ERROR] Permission Denied: Wrong credentials\n");
    return admin;
  }

  printf("\nWelcome, admin!\n");
  admin = 1;

  return admin;
}

void add_movie()
{
  char buf[1024];
  movie_t *movie;

  movie = (movie_t *) malloc(sizeof(movie_t));
  if (!movie)
    return;
  printf("Add a movie\n--------------\n");
  printf("Enter Title: ");
  if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  movie->title = (char *) malloc(strlen(buf) + 1);
  if (movie->title == NULL)
    goto fail;
  strcpy(movie->title, buf);

  printf("Enter Description: ");
  if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  movie->desc = (char *) malloc(strlen(buf) + 1);
  if (movie->desc == NULL)
    goto fail;
  strcpy(movie->desc, buf);

  while (1)
  {
    printf("Enter Year (1800-2015): ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    movie->year = strtoul(buf, NULL, 10);
    if (movie->year >= 1800 && movie->year <= 2015)
      break;
    printf("[ERROR] Invalid year. Try again.\n");
  }

  while (1)
  {
    printf("Enter Review score (0-100): ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    movie->score = strtoul(buf, NULL, 10);
    if (movie->score >= 0 && movie->score <= 100)
      break;
    printf("[ERROR] Invalid rating. Try again.\n");
  }

  int finish = 0;
  while (!finish)
  {
    printf("Select a genre\n 1. Action\n 2. Romance\n 3. Comeda\n 4. Horror\n 5. Other\nChoice: ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    unsigned int genre = strtoul(buf, NULL, 10);
    finish = 1;
    switch (genre)
    {
      case 1:
        movie->genre = G_ACTION; break;
      case 2:
        movie->genre = G_ROMANCE; break;
      case 3:
        movie->genre = G_COMEDY; break;
      case 4:
        movie->genre = G_HORROR; break;
      case 5:
        movie->genre = G_OTHER; break;
      default:
        finish = 0;
        printf("[ERROR] Invalid genre. Try again.\n");
        break;
    }
  }

  finish = 0;
  while (!finish)
  {
    printf("Select a film rating\n 1. G\n 2. PG\n 3. PG-13\n 4. R\n 5. Unknown\nChoice: ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    unsigned int rating = strtoul(buf, NULL, 10);
    finish = 1;
    switch (rating)
    {
      case 1:
        movie->rating = R_G; break;
      case 2:
        movie->rating = R_PG; break;
      case 3:
        movie->rating = R_PG13; break;
      case 4:
        movie->rating = R_R; break;
      case 5:
        movie->rating = R_UNKNOWN; break;
      default:
        finish = 0;
        printf("[ERROR] Invalid film rating. Try again.\n");
        break;
    }
  }

  //movie->id = ++g_num_movies;
  movie->print_info = &print_movie_detail;
  if (movie_add(&movies_full, movie) != 0)
  {
    printf("[ERROR] Failed to add a movie.\n");
    goto fail;
  }
  return;

fail:
  if (movie)
  {
    if (movie->desc)
      free(movie->desc);
    if (movie->title)
      free(movie->title);
    free(movie);
  }
  return;
}

void remove_movie()
{
  char buf[256];
  unsigned int num_movies = 0, movie_id;
  movie_node_t *node;

  /* Movie list (full) */
  printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    printf("[ERROR] Movie list is empty.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    printf("Enter movie id: ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = strtoul(buf, NULL, 10);
    if (movie_id >= 1 && movie_id <= num_movies)
      break;
    printf("[ERROR] Invalid movie id. Try again.\n");
  }

  node = movie_find_by_id(movies_full, movie_id);
  movie_t *movie = node->movie;

#if PATCHED
  if (movie_delete(&movies_full, movie_id) != 0 || movie_delete(&movies_rented, movie_id) != 0)
#else
  if (movie_delete(&movies_full, movie_id) != 0)
#endif
    printf("[ERROR] Failed to remove.\n");
  else
  {
    g_num_movies--;
    free_movie(movie);
    printf("Successfully removed the movie!\n");
  }
}

void update_movie()
{
  unsigned int movie_id, num_movies = 0;
  char *new_title, *new_desc;
  char buf[1024];
  movie_node_t *node;
  movie_t *movie;

  /* Present the full list with index */
  printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    printf("[ERROR] Nothing to update.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    printf("Enter movie id: ");
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = strtoul(buf, NULL, 10);
    if (movie_id >= 1 && movie_id <= num_movies)
      break;
    printf("[ERROR] Invalid movie id. Try again.\n");
  }

  node = movie_find_by_id(movies_full, movie_id);
  movie = node->movie;

  printf("\nUpdate a movie\n--------------\nJust leave it empty to keep the old value.\n");
  printf("Enter new title (current: [%s]): ", movie->title);
  if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    return;
  if (strlen(buf) != 0)
  {
    new_title = (char *) malloc(strlen(buf) + 1);
    if (new_title == NULL)
      goto fail;
    strcpy(new_title, buf);
    free(movie->title);
    movie->title = new_title;
  }
  printf("Enter new description (current: [%s]): ", movie->desc);
  if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    return;
  if (strlen(buf) != 0)
  {
    new_desc = (char *) malloc(strlen(buf) + 1);
    if (new_desc == NULL)
      goto fail;
    strcpy(new_desc, buf);
    free(movie->desc);
    movie->desc = new_desc;
  }
  while (1)
  {
    printf("Enter new year (1800-2015) (current: [%d]): ", movie->year);
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (strlen(buf) != 0)
    {
      int new_year = strtoul(buf, NULL, 10);
      if (new_year >= 1800 && new_year <= 2015)
      {
        movie->year = new_year;
        break;
      }
      printf("[ERROR] Invalid year. Try again.\n");
    }
    else
      break;
  }

  while (1)
  {
    printf("Enter new review score (0-100) (current: [%d/100]: ", movie->score);
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (strlen(buf) != 0)
    {
      int new_score = strtoul(buf, NULL, 10);
      if (new_score >= 0 && new_score <= 100)
      {
        movie->score = new_score;
        break;
      }
      printf("[ERROR] Invalid rating. Try again.\n");
    }
    else
      break;
  }

  int finish = 0;
  while (!finish)
  {
    printf("Select a genre (current: [%s])\n 1. Action\n 2. Romance\n 3. Comeda\n 4. Horror\n 5. Other\nChoice: ", movie_g2s(movie->genre));
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (strlen(buf) != 0)
    {
      unsigned int genre = strtoul(buf, NULL, 10);
      finish = 1;
      switch (genre)
      {
        case 1:
          movie->genre = G_ACTION; break;
        case 2:
          movie->genre = G_ROMANCE; break;
        case 3:
          movie->genre = G_COMEDY; break;
        case 4:
          movie->genre = G_HORROR; break;
        case 5:
          movie->genre = G_OTHER; break;
        default:
          finish = 0;
          printf("[ERROR] Invalid genre. Try again.\n");
          break;
      }
    }
    else
      break;
  }

  finish = 0;
  while (!finish)
  {
    printf("Select a film rating (current: [%s]\n 1. G\n 2. PG\n 3. PG-13\n 4. R\n 5. Unknown\nChoice: ", movie_r2s(movie->rating));
    if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (strlen(buf) != 0)
    {
      unsigned int rating = strtoul(buf, NULL, 10);
      finish = 1;
      switch (rating)
      {
        case 1:
          movie->rating = R_G; break;
        case 2:
          movie->rating = R_PG; break;
        case 3:
          movie->rating = R_PG13; break;
        case 4:
          movie->rating = R_R; break;
        case 5:
          movie->rating = R_UNKNOWN; break;
        default:
          finish = 0;
          printf("[ERROR] Invalid film rating. Try again.\n");
          break;
      }
    }
    else
      break;
  }

  printf("Successfully updated the movie information!\n");
  return;

fail:
  if (new_title)
    free(new_title);
  if (new_desc)
    free(new_desc);
  if (movie)
    free(movie);
}

void quit()
{
  printf("Bye!\n");
  exit(0);
}

int main()
{
  int admin_mode = 0;
  char buf[4096];
  char welcome[] = "========= Movie Rental Service v0.1 =========";
  char menu[] = "\n1. List movies\n2. Rent movie\n3. Return movie\n4. Admin mode\n5. Exit\n\nChoice: ";
  char admin_menu[] = "\n1. Add movie\n2. Remove movie\n3. Update movie\n4. Quit admin mode\n\nChoice: ";

  printf(welcome);
  initialize();
  printf("=============================================");

  while (1)
  {
    if (admin_mode)
    {
      printf(admin_menu);
      if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
        quit();
      switch (buf[0])
      {
        case '1':
          add_movie();
          break;
        case '2':
          remove_movie();
          break;
        case '3':
          update_movie();
          break;
        case '4':
          admin_mode = 0;
          break;
        default:
          printf("[ERROR] Invalid menu. Please select again.\n");
          break;
      }
    }
    else
    {
      printf(menu);
      if (readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
        quit();
      switch (buf[0])
      {
        case '1':
          list_movies();
          break;
        case '2':
          rent_movie();
          break;
        case '3':
          return_movie();
          break;
        case '4':
          admin_mode = login();
          break;
        case '5':
          quit();
          break;
        default:
          printf("[ERROR] Invalid menu. Please select again.\n");
          break;
      }
    }
  }

  return 0;
}
