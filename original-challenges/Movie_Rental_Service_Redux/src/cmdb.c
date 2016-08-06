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

void init_movies() {
    cmdb_entry_t initial_rows[] = {
      {"The Shawshank Redemption", "Two imprisoned men bond over a number of years, finding solace and eventual\n     redemption through acts of common decency.", 1994, 93, "Other", "R"},
      {"The Godfather", "The aging patriarch of an organized crime dynasty transfers control of his clandestine\n     empire to his reluctant son.", 1972, 92, "Other", "R"},
      {"The Dark Knight", "When Batman, Gordon have Harvey Dent launch an assault on the mob, they let the clown\n     out of the box, the Joker, bent on turning Gotham on itself and bringing any heroes\n     down to his level.", 2008, 90, "Action", "PG13"},
      {"Inception", "A thief who steals corporate secrets through use of dream-sharing technology is given the\n     inverse task of planting an idea into the mind of a CEO.", 2010, 88, "Action", "PG13"},
      {"The Matrix", "A computer hacker learns from mysterious rebels about the true nature of his reality and\n     his role in the war against its controllers.", 1999, 87, "Action", "R"},
      {"Modern Times", "The Tramp struggles to live in modern industrial society with the help of a young\n     homeless woman.", 1936, 86, "Comedy", "G"},
      {"About Time", "At the age of 21, Tim discovers he can travel in time and change what happens and has\n     happened in his own life. His decision to make his world a better place by getting\n     a girlfriend turns out not to be as easy as you might think.", 2013, 78, "Romance", "R"},
      {"Yes Man", "A guy challenges himself to say \"yes\" to everything for an entire year.", 2008, 69, "Comedy", "PG13"},
      {"The Conjuring", "Paranormal investigators Ed and Lorraine Warren work to help a family terrorized\n     by a dark presence in their farmhouse.", 2013, 75, "Horror", "R"},
      {"The Lion King", "Lion cub and future king Simba searches for his identity. His eagerness to please others\n     and penchant for testing his boundaries sometimes gets him into trouble.", 1994, 85, "Other", "G"},
    };

    int i;
    for (i = 0; i < sizeof(initial_rows)/sizeof(cmdb_entry_t); i++) {
        cmdb_entry_t *row = &initial_rows[i];
        add_movie(row->name, row->desc, row->year, row->score, row->type, row->mpaa);
    }
}

int rent_movie(int id)
{
    return rent_entry(id);
}

int return_movie(int id)
{
    return return_entry(id);
}

void list_all_movies()
{
    print_movies(ALL);
}

void list_owned_movies()
{
    print_movies(OWNED);
}

void list_rented_movies()
{
    print_movies(RENTED);
}

int get_num_owned_movies() {
    return get_list_length();
}

int get_num_rented_movies() {
    return get_num_rented();
}

