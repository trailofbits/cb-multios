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

#ifndef BITSET_H_
#define BITSET_H_

#include <libcgc.h>

struct bitset {
    size_t size;
    unsigned char data[0];
};

/**
 * Initialize a empty bitset. Struct must be large enough to contain size + size bits.
 *
 * @param bitset The bitset to initialize
 * @param size The size of the bitset
 */
void bitset_init(struct bitset *bitset, size_t size);

/**
 * Clear a bitset.
 *
 * @param bitset The bitset to clear
 */
void bitset_clear(struct bitset *bitset);

/**
 * Set a bit in a bitset
 *
 * @param bitset The bitset to update
 * @param bit The bit to set
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int bitset_set_bit(struct bitset *bitset, unsigned int bit);

/**
 * Clear a bit in a bitset
 *
 * @param bitset The bitset to update
 * @param bit The bit to set
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int bitset_clear_bit(struct bitset *bitset, unsigned int bit);

/**
 * Get a bit from a bitset
 *
 * @param bitset The bitset to access
 * @param bit The bit to get
 * @return value of bit on success, EXIT_FAILURE on failure
 */
int bitset_get_bit(struct bitset *bitset, unsigned int bit);

/**
 * Find the first bit in a bitset matching set
 *
 * @param bitset The bitset to access
 * @param set Look for a set or unset bit
 * @return The index of the first matching bit, or EXIT_FAILURE if none found
 */
int bitset_find_first(struct bitset *bitset, int set);

#endif /* BITSET_H_ */

