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

#define READ_ERROR 1
#define TRANSMIT_ERROR 2
#define BUFFER_ERROR 3
#define SIZE_ERROR 4
#define RECEIVE_ERROR 5
#define NO_DATA 6

#define FILE_BUFFER_SIZE 4096

typedef struct {
	size_t fd;
	size_t index;
	size_t num;
	unsigned char buffer[FILE_BUFFER_SIZE];
} File;

/**
* Read from the socket until either a delimeter is ditected or n bytes are read
* 
* @param socket The file descripter to read from
* @param buffer The buffer to store the read bytes in
* @param delim The delimiter to detect 
* @param size The maximum number of bytes to read
* @param read The number of total bytes read
* @return 0 if successful, -1 if the receive call returns an error, -2 if the receive call does not read a byte
*/
int read_until_delim_or_n(unsigned int socket, char* buffer, char delim, size_t size, size_t* read);

/**
* Read exactly n bytes from the socket
* 
* @param socket The file descripter to read from
* @param buffer The buffer to store the read bytes in
* @param size The maximum number of bytes to read
* @param read The number of total bytes read
* @return 0 if successful, -1 if the receive call returns an error, -2 if the receive call does not read a byte
*/
int read_n_bytes(unsigned int socket, char* buffer, size_t size, size_t* read);

/**
* Send size bytes to the socket
* 
* @param socket The file descripter to send to
* @param buffer The buffer to store the read bytes in
* @param size The maximum number of bytes to send
* @return 0 if successful, -1 if the transmit call returns an error
*/
int transmit_all(int fd, const void *buf, const size_t size);