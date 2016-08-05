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

#ifndef POSTAGE_H
#define POSTAGE_H 1

#define STAMP_SIZE 3

// struct for a stamp
typedef struct __attribute__((packed))  {
	char serial[STAMP_SIZE];
} stamp_t;


/**
 * Initialize the stamp roll.
 */
void init_stamp_roll(void);

/**
 * Create and return a new stamp.
 *
 * @return VA of new stamp or NULL on error.
 */
stamp_t *get_new_stamp(void);

/**
 * Use a stamp
 *
 * @param s 	A stamp to use
 * @return SUCCESS on success, else -1 if stamp is invalid
 */
int use_stamp(stamp_t *s);

#endif