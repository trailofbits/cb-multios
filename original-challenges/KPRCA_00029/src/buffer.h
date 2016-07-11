/*
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
#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t read_idx;
    uint64_t write_idx;
    uint8_t *buffer;
    size_t length;
} buffer_t;

// read functions
int buffer_read_bit(buffer_t *);
unsigned int buffer_read_bits(buffer_t *, unsigned int count);
void buffer_read_bytes(buffer_t *, uint8_t *, size_t);

// write functions
void buffer_write_bit(buffer_t *, int value);
void buffer_write_bits(buffer_t *, unsigned int value, unsigned int count);
void buffer_write_bytes(buffer_t *, uint8_t *, size_t);

// misc functions
void buffer_init(buffer_t *, uint8_t *, size_t);
uint64_t buffer_read_remaining(buffer_t *);
uint64_t buffer_read_tell(buffer_t *);
void buffer_read_seek(buffer_t *, uint64_t);
uint64_t buffer_write_tell(buffer_t *);
void buffer_write_seek(buffer_t *, uint64_t);

#endif /* !BUFFER_H_ */
