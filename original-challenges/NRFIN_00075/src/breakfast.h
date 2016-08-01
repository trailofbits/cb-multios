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

#ifndef SERIALIZE_H
#define SERIALIZE_H 1

typedef struct {
    char type[4];			// type of content (Plain or Serialized)
    unsigned short size;	// number of bytes in content
    char content[];			// buffer to store content
} Stream;

/**
 * Process the input stream to extract serialized objects
 *
 * @param input_stream 	Input stream object
 * @return 0 on success, else -1 on error
 */
ssize_t process_serialized_input(Stream *input_stream);
/**
 * Process the input stream to extract non-serialized objects
 *
 * @param input_stream 	Input stream object
 * @return 0 on success, else -1 on error
 */
ssize_t process_plain_input(Stream *input_stream);


#endif