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
#ifndef MALLOC_H
#define MALLOC_H 1

#include <libcgc.h> 

#define PAGE_SZ 4096

/**
 * A relatively simple malloc implementation.
 *
 * @param size Number of bytes of space desired
 * @return VA of allocated space, 
 *   or NULL if size is 0 or there is an error allocating more space.
 */
void *malloc(size_t size);

/**
 * A relatively simple calloc implementation.
 *
 * @param size Number of bytes of space desired
 * @return VA of allocated space, 
 *   or NULL if size is 0 or there is an error allocating more space.
 */
void *calloc(size_t size);


/**
 * Free allocated memory
 *
 * Calling free() in a NULL will segfault.
 *
 * @param VA of allocated memory.
 */
void free(void *ptr);

#endif
