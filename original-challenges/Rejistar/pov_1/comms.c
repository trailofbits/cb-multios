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
#include "comms.h"

static File std_input = { .fd = STDIN, .index = 0};

int fill_buffer() {
	std_input.index = 0;
	std_input.num = 0;

	if(receive(std_input.fd, std_input.buffer, FILE_BUFFER_SIZE, &std_input.num))
		return -1;

	if (std_input.num == 0)
		return -2;

	return 0;
}

int get_char(char *ch) {
	int result;

	if (std_input.num == 0 || std_input.num <= std_input.index) {
		if((result = fill_buffer()))
			return result;
	}

	*ch = std_input.buffer[std_input.index];
	std_input.index++;

	return 0;

}

int read_until_delim_or_n(unsigned int socket, char* buffer, char delim, size_t size, size_t* read) {

	size_t tmp=0;
	*read = 0;
	char tmp_char;
	int result=0;

	if(!buffer)
		return BUFFER_ERROR;

	if(!size)
		return SIZE_ERROR;

	for (unsigned int i = 0; i < size; i++) {
		if((result = get_char(&tmp_char)))
			return result;

		if (delim != 0 && tmp_char == delim)
			return 0;

		buffer[i] = tmp_char;
		*read += 1;
	}

	return 0;
}

int read_n_bytes(unsigned int socket, char* buffer, size_t size, size_t* read) {
	return read_until_delim_or_n(socket, buffer, 0, size, read);
}


