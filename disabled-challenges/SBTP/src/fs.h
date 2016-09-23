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

#ifndef FS_H
#define FS_H

#include "list.h"

#define MAX_FILENAME_SIZE 127
#define MAX_FILE_SIZE 1023

struct dirtree {
    char name[MAX_FILENAME_SIZE+1];
    struct list directories;
    struct list files;
} typedef dirtree_t;

struct file {
    char name[MAX_FILENAME_SIZE+1];
    char data[MAX_FILE_SIZE+1];
} typedef file_t;


/**
 * Make a new directory
 *
 * @param path New path
 * @return 0 on success, err code on failure
 */
int add_dir(char *path);

/**
 * Remove a directory
 *
 * @param path Path to remove
 * @return 0 on success, err code on failure
 */
int rm_dir(char *path);

/**
 * Add a new file
 *
 * @param path Path to file
 * @param data File data
 * @return 0 on success, err code on failure
 */
int add_file(char *path, char *data);

/**
 * Remove a file
 *
 * @param path Path to file
 * @return 0 on success, err code on failure
 */
int rm_file(char *path);

/**
 * Read a file
 *
 * @param path Path to file
 * @return File data on success, NULL on err
 */
char *readfile(char *path);

/**
 * List a directory
 *
 * @param path to list
 * @return Path data on success, NULL on err
 */
char *ls_dir(char *path);

/**
 * Initialize the filesystem
 */
void init_fs();

#endif
