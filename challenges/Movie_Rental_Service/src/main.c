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

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_movie.h"

void cgc_quit();
void cgc_print_movie_detail(int, movie_t *);

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
unsigned int cgc_g_num_movies = 0;
movie_list_t movies_full;
movie_list_t movies_rented;

void cgc_initialize()
{
  unsigned int i, rand;
  char c;
  movie_t *movie;
  cgc_printf("\n   . . . Initializing the inventory . . .\n         (movie info from IMDb.com)\n");

  for (i = 0; i <= sizeof(g_password)/sizeof(g_password[0]); ++i)
  {
    cgc_random(&c, sizeof(c), NULL);
    cgc_random(&rand, sizeof(rand), NULL);
    if (c & 1)
      g_password[i] = 'A' + (rand % 26);
    else
      g_password[i] = 'a' + (rand % 26);
  }
  g_password[i] = '\0';

  for (i = 0; i < sizeof(default_movies)/sizeof(default_movies[0]); ++i)
  {
    movie = (movie_t *) cgc_malloc(sizeof(movie_t));
    if (movie == NULL)
      goto fail;
    cgc_memset(movie, '\0', sizeof(movie_t));
    movie->title = (char *) cgc_malloc(cgc_strlen(default_movies[i].title) + 1);
    movie->desc = (char *) cgc_malloc(cgc_strlen(default_movies[i].desc) + 1);
    if (movie->title == NULL || movie->desc == NULL)
      goto fail;
    cgc_strcpy(movie->title, default_movies[i].title);
    cgc_strcpy(movie->desc, default_movies[i].desc);
    movie->year = default_movies[i].year;
    movie->score = default_movies[i].score;
    movie->genre = default_movies[i].genre;
    movie->rating = default_movies[i].rating;
    movie->print_info = &cgc_print_movie_detail;
    cgc_movie_add(&movies_full, movie);
  }
  return;

fail:
  cgc_printf("[ERROR] Initialization failed. Exit.\n");
  cgc_quit();
}

int cgc_readuntil(int fd, char *buf, cgc_size_t len, char delim)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    cgc_size_t rx;
    if (cgc_receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
        if (*(c++) == delim)
            break;
    }
    *(c-1) = '\0';
    return c - buf;
}

void cgc_print_movie_detail(int id, movie_t *movie)
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

    cgc_printf(format, id, movie->title, movie->year,
                             rating_str, genre_str, movie->score, movie->desc);
  }
}

void cgc_list_movies()
{
  int num_movies = 0;
  movie_node_t *node;

  /* Movie list (full) */
  cgc_printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  cgc_printf("--------------\n%d movie(s)\n", num_movies);

  /* Movie list (rented) */
  num_movies = 0;
  cgc_printf("\nMovies (Rented)\n--------------\n");
  for (node = movies_rented; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  cgc_printf("--------------\n%d movie(s)\n", num_movies);
}

void cgc_rent_movie()
{
  movie_node_t *node;
  unsigned int movie_id, num_movies = 0;
  char buf[256];

  /* Present the full movie list with index */
  cgc_printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  cgc_printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    /* Shouldn't really happen with successful init */
    cgc_printf("[ERROR] Movie list is empty. Please try again later.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    cgc_printf("Enter movie id: ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = cgc_strtoul(buf, NULL, 10);
    if (movie_id >=1 && movie_id <= num_movies)
      break;
    cgc_printf("[ERROR] Invalid movie id. Try again.\n");
  }

  /* Check if the movie isn't rented already */
  movie_node_t *tmp = cgc_movie_find_by_id(movies_full, movie_id);
  movie_t *movie = tmp->movie;
  tmp = cgc_movie_find(movies_rented, movie->title);
  if (tmp)
  {
    cgc_printf("Sorry, [%s] is already rented at this time. Please try again later.\n", tmp->movie->title);
    return;
  }

  /* If not in rental list, insert it into rental list */
  tmp = cgc_movie_find_by_id(movies_full, movie_id);
  if (cgc_movie_add(&movies_rented, tmp->movie) != 0)
    cgc_printf("[ERROR] Failed to rent. Please try again later.\n");
  else
    cgc_printf("Successfully rented [%s]! Enjoy!\n", tmp->movie->title);
}

void cgc_return_movie()
{
  char buf[256];
  unsigned int movie_id, num_movies = 0;
  movie_node_t *node;

  /* Present the list of rented movies with index */
  cgc_printf("\nMovies (Rented)\n--------------\n");
  for (node = movies_rented; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  cgc_printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    cgc_printf("[ERROR] All the movies are in our inventory.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    cgc_printf("Enter movie id: ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = cgc_strtoul(buf, NULL, 10);
    //if (movie_id >= 1 && movie_id <= g_num_movies)
    //  break;
    if (movie_id >= 1 && movie_id <= num_movies)
      break;
    cgc_printf("[ERROR] Invalid movie id. Try again.\n");
  }

  /* Remove the movie entry in rental list */
  movie_node_t *tmp = cgc_movie_find_by_id(movies_rented, movie_id);
  if (tmp == NULL)
  {
    /* Shouldn't happen */
    cgc_printf("Sorry, we have some issues here. Please try again later.\n");
    return;
  }

  if (cgc_movie_delete(&movies_rented, movie_id) != 0)
  {
    /* Shouldn't happen */
    cgc_printf("[ERROR] Failed to return the movie. Please try again.\n");
    return;
  }

  cgc_printf("Successfully returned [%s]! Thank you!\n", tmp->movie->title);
}

int cgc_login()
{
  int admin = 0;
  char buf[64];
  char username[] = "admin";

  cgc_printf("username: ");
  cgc_readuntil(STDIN, buf, sizeof(buf), '\n');
  if (cgc_strcmp(username, buf) != 0)
  {
    cgc_printf("[ERROR] Permission Denied: Wrong credentials\n");
    return admin;
  }

  cgc_printf("password: ");
#if PATCHED
  cgc_readuntil(STDIN, buf, sizeof(buf), '\n');
#else
  cgc_readuntil(STDIN, buf, sizeof(buf) + 4, '\n');
#endif
  if (cgc_strcmp(g_password, buf) != 0)
  {
    cgc_printf("[ERROR] Permission Denied: Wrong credentials\n");
    return admin;
  }

  cgc_printf("\nWelcome, admin!\n");
  admin = 1;

  return admin;
}

void cgc_add_movie()
{
  char buf[1024];
  movie_t *movie;

  movie = (movie_t *) cgc_malloc(sizeof(movie_t));
  if (!movie)
    return;
  cgc_printf("Add a movie\n--------------\n");
  cgc_printf("Enter Title: ");
  if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  movie->title = (char *) cgc_malloc(cgc_strlen(buf) + 1);
  if (movie->title == NULL)
    goto fail;
  cgc_strcpy(movie->title, buf);

  cgc_printf("Enter Description: ");
  if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  movie->desc = (char *) cgc_malloc(cgc_strlen(buf) + 1);
  if (movie->desc == NULL)
    goto fail;
  cgc_strcpy(movie->desc, buf);

  while (1)
  {
    cgc_printf("Enter Year (1800-2015): ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    movie->year = cgc_strtoul(buf, NULL, 10);
    if (movie->year >= 1800 && movie->year <= 2015)
      break;
    cgc_printf("[ERROR] Invalid year. Try again.\n");
  }

  while (1)
  {
    cgc_printf("Enter Review score (0-100): ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    movie->score = cgc_strtoul(buf, NULL, 10);
    if (movie->score >= 0 && movie->score <= 100)
      break;
    cgc_printf("[ERROR] Invalid rating. Try again.\n");
  }

  int finish = 0;
  while (!finish)
  {
    cgc_printf("Select a genre\n 1. Action\n 2. Romance\n 3. Comeda\n 4. Horror\n 5. Other\nChoice: ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    unsigned int genre = cgc_strtoul(buf, NULL, 10);
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
        cgc_printf("[ERROR] Invalid genre. Try again.\n");
        break;
    }
  }

  finish = 0;
  while (!finish)
  {
    cgc_printf("Select a film rating\n 1. G\n 2. PG\n 3. PG-13\n 4. R\n 5. Unknown\nChoice: ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    unsigned int rating = cgc_strtoul(buf, NULL, 10);
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
        cgc_printf("[ERROR] Invalid film rating. Try again.\n");
        break;
    }
  }

  //movie->id = ++g_num_movies;
  movie->print_info = &cgc_print_movie_detail;
  if (cgc_movie_add(&movies_full, movie) != 0)
  {
    cgc_printf("[ERROR] Failed to add a movie.\n");
    goto fail;
  }
  return;

fail:
  if (movie)
  {
    if (movie->desc)
      cgc_free(movie->desc);
    if (movie->title)
      cgc_free(movie->title);
    cgc_free(movie);
  }
  return;
}

void cgc_remove_movie()
{
  char buf[256];
  unsigned int num_movies = 0, movie_id;
  movie_node_t *node;

  /* Movie list (full) */
  cgc_printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  cgc_printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    cgc_printf("[ERROR] Movie list is empty.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    cgc_printf("Enter movie id: ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = cgc_strtoul(buf, NULL, 10);
    if (movie_id >= 1 && movie_id <= num_movies)
      break;
    cgc_printf("[ERROR] Invalid movie id. Try again.\n");
  }

  node = cgc_movie_find_by_id(movies_full, movie_id);
  movie_t *movie = node->movie;

#if PATCHED
  if (cgc_movie_delete(&movies_full, movie_id) != 0 || cgc_movie_delete(&movies_rented, movie_id) != 0)
#else
  if (cgc_movie_delete(&movies_full, movie_id) != 0)
#endif
    cgc_printf("[ERROR] Failed to remove.\n");
  else
  {
    cgc_g_num_movies--;
    cgc_free_movie(movie);
    cgc_printf("Successfully removed the movie!\n");
  }
}

void cgc_update_movie()
{
  unsigned int movie_id, num_movies = 0;
  char *new_title, *new_desc;
  char buf[1024];
  movie_node_t *node;
  movie_t *movie;

  /* Present the full list with index */
  cgc_printf("\nMovies (Full)\n--------------\n");
  for (node = movies_full; node != NULL; node = node->next)
  {
    num_movies++;
    node->movie->print_info(num_movies, node->movie);
  }
  cgc_printf("--------------\n%d movie(s)\n", num_movies);
  if (num_movies == 0)
  {
    cgc_printf("[ERROR] Nothing to update.\n");
    return;
  }

  /* Get and validate the index */
  while (1)
  {
    cgc_printf("Enter movie id: ");
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      return;
    movie_id = cgc_strtoul(buf, NULL, 10);
    if (movie_id >= 1 && movie_id <= num_movies)
      break;
    cgc_printf("[ERROR] Invalid movie id. Try again.\n");
  }

  node = cgc_movie_find_by_id(movies_full, movie_id);
  movie = node->movie;

  cgc_printf("\nUpdate a movie\n--------------\nJust leave it empty to keep the old value.\n");
  cgc_printf("Enter new title (current: [%s]): ", movie->title);
  if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    return;
  if (cgc_strlen(buf) != 0)
  {
    new_title = (char *) cgc_malloc(cgc_strlen(buf) + 1);
    if (new_title == NULL)
      goto fail;
    cgc_strcpy(new_title, buf);
    cgc_free(movie->title);
    movie->title = new_title;
  }
  cgc_printf("Enter new description (current: [%s]): ", movie->desc);
  if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
    return;
  if (cgc_strlen(buf) != 0)
  {
    new_desc = (char *) cgc_malloc(cgc_strlen(buf) + 1);
    if (new_desc == NULL)
      goto fail;
    cgc_strcpy(new_desc, buf);
    cgc_free(movie->desc);
    movie->desc = new_desc;
  }
  while (1)
  {
    cgc_printf("Enter new year (1800-2015) (current: [%d]): ", movie->year);
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (cgc_strlen(buf) != 0)
    {
      int new_year = cgc_strtoul(buf, NULL, 10);
      if (new_year >= 1800 && new_year <= 2015)
      {
        movie->year = new_year;
        break;
      }
      cgc_printf("[ERROR] Invalid year. Try again.\n");
    }
    else
      break;
  }

  while (1)
  {
    cgc_printf("Enter new review score (0-100) (current: [%d/100]: ", movie->score);
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (cgc_strlen(buf) != 0)
    {
      int new_score = cgc_strtoul(buf, NULL, 10);
      if (new_score >= 0 && new_score <= 100)
      {
        movie->score = new_score;
        break;
      }
      cgc_printf("[ERROR] Invalid rating. Try again.\n");
    }
    else
      break;
  }

  int finish = 0;
  while (!finish)
  {
    cgc_printf("Select a genre (current: [%s])\n 1. Action\n 2. Romance\n 3. Comeda\n 4. Horror\n 5. Other\nChoice: ", cgc_movie_g2s(movie->genre));
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (cgc_strlen(buf) != 0)
    {
      unsigned int genre = cgc_strtoul(buf, NULL, 10);
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
          cgc_printf("[ERROR] Invalid genre. Try again.\n");
          break;
      }
    }
    else
      break;
  }

  finish = 0;
  while (!finish)
  {
    cgc_printf("Select a film rating (current: [%s]\n 1. G\n 2. PG\n 3. PG-13\n 4. R\n 5. Unknown\nChoice: ", cgc_movie_r2s(movie->rating));
    if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
      goto fail;
    if (cgc_strlen(buf) != 0)
    {
      unsigned int rating = cgc_strtoul(buf, NULL, 10);
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
          cgc_printf("[ERROR] Invalid film rating. Try again.\n");
          break;
      }
    }
    else
      break;
  }

  cgc_printf("Successfully updated the movie information!\n");
  return;

fail:
  if (new_title)
    cgc_free(new_title);
  if (new_desc)
    cgc_free(new_desc);
  if (movie)
    cgc_free(movie);
}

void cgc_quit()
{
  cgc_printf("Bye!\n");
  cgc_exit(0);
}

int main(int cgc_argc, char *cgc_argv[])
{
  int admin_mode = 0;
  char buf[4096];
  char welcome[] = "========= Movie Rental Service v0.1 =========";
  char menu[] = "\n1. List movies\n2. Rent movie\n3. Return movie\n4. Admin mode\n5. Exit\n\nChoice: ";
  char admin_menu[] = "\n1. Add movie\n2. Remove movie\n3. Update movie\n4. Quit admin mode\n\nChoice: ";

  cgc_printf(welcome);
  cgc_initialize();
  cgc_printf("=============================================");

  while (1)
  {
    if (admin_mode)
    {
      cgc_printf(admin_menu);
      if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
        cgc_quit();
      switch (buf[0])
      {
        case '1':
          cgc_add_movie();
          break;
        case '2':
          cgc_remove_movie();
          break;
        case '3':
          cgc_update_movie();
          break;
        case '4':
          admin_mode = 0;
          break;
        default:
          cgc_printf("[ERROR] Invalid menu. Please select again.\n");
          break;
      }
    }
    else
    {
      cgc_printf(menu);
      if (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') < 0)
        cgc_quit();
      switch (buf[0])
      {
        case '1':
          cgc_list_movies();
          break;
        case '2':
          cgc_rent_movie();
          break;
        case '3':
          cgc_return_movie();
          break;
        case '4':
          admin_mode = cgc_login();
          break;
        case '5':
          cgc_quit();
          break;
        default:
          cgc_printf("[ERROR] Invalid menu. Please select again.\n");
          break;
      }
    }
  }

  return 0;
}
