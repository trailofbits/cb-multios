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

#ifndef STDLIB_H_
#define STDLIB_H_

/** Integer value representing failure */
#define EXIT_FAILURE (-1)
/** Integer value representing success */
#define EXIT_SUCCESS (0)

/** Round up x to the nearest multiple of a, a being a power or two */
#define ALIGN(x, a) (((x) + (a - 1)) & ~(a - 1))

/** Round ptr down to its page's base address */
#define ROUND_TO_PAGE(ptr) ((void *)((unsigned long)(ptr) & (PAGE_SIZE - 1)))

/**
 * Return the max of a and b.
 *
 * @param a The first argument
 * @param b The second argument
 * @return a if a > b else b
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * Return the min of a and b.
 *
 * @param a The first argument
 * @param b The second argument
 * @return a if a < b else b
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/** The flag page, always mapped in at a constant address */
#define FLAG_PAGE ((void *)0x4347C000)
/** The page size for this architecture, uses 4K pages */
#define PAGE_SIZE (1 << 12)

#ifndef va_start
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif

/**
 * Seed the random number generator.
 *
 * @param seed The value to seed the RNG with
 */
void srand(unsigned int seed);

/**
 * Get a "random" integer.
 *
 * Uses an LCG, not meant to be secure.
 *
 * @return A "random"-ish integer from 0 to UINT_MAX
 */
unsigned int rand(void);

#endif /* STDLIB_H_ */

