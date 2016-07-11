/*
 Copyright (c) 2014 Cromulence LLC
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 */

#ifndef __FILE_H__
#define __FILE_H__

#include <libcgc.h>
#include <stdlib.h>
#include <malloc.h>

#define FILE 0
#define DIR 1

typedef struct file {
	char name[256];
	unsigned int type;
	unsigned int length;
	char *data;
} file, *pfile;

/// Allocates the file structure and zeros the buffer
pfile init_file( void );

/// Sets the files name to that specified by name
int set_name( pfile pf, char *name);

/// Sets the type of file as indicated by type only FILE or DIR are valid
int set_type( pfile pf, int type);

/// Allocates a new copy of the data buffer and inserts it into the structure
int set_data( pfile pf, int length, char *data );

/// Frees the file structure and associated data
void free_file( pfile pf );

/// Adds a file to the root node
int add_file( pfile nf );

/// Retrieves the file specified by name
pfile get_file( char *name );

/// Reallocates the pfile list to allow an additional file
int fixup_dir_length( pfile d );

/// Utility function to search for the next '/' in a string
int find_next_slash( char *str, int start, int max );

/// Retrieves the pfile beneath a given directory if it exists
pfile retrieve_sub( pfile pf, char *name );

/// Frees the file structure associated with name
int delete_file( char *name );

/// Returns 0 if file is not a sub 1 if it is
int does_sub_file_exist( pfile pf, char *name);

/// Bubble sort the files of a directory
int bubble_sort( pfile parent );

#endif
