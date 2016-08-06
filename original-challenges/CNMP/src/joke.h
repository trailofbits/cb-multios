/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <libcgc.h>
#include "libc.h"

#ifndef JOKES_H
#define JOKES_H

#define MAX_JOKES 256
#define MAX_JOKE_STRING_LEN 512


// define a joke_struct that has a joke_id, and joke_string
typedef struct joke_struct {
	uint32_t joke_id;
	char joke_string[MAX_JOKE_STRING_LEN];
} joke_struct;

// jokedb_struct is our array of jokes, and a count of the jokes in the array
typedef struct jokedb_struct {
	int count;
	joke_struct jokes[MAX_JOKES];
} jokedb_struct;

// define function interfaces
int insert_joke(jokedb_struct *jokedb, const char *joke_str);
void load_default_jokes(jokedb_struct *jokedb);
int joke_count(jokedb_struct *jokedb);

#endif

