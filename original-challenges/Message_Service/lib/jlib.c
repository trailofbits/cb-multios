/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

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
#include <libcgc.h>
#include "jlib.h"

void zero(char *buf, unsigned int len) {
	unsigned int i;

	if (!buf) {
		return;
	}

	for (i = 0; i < len; i++) {
		buf[i] = '\0';
	}

	return;
}

size_t strlen(char *buf) {
	size_t i = 0;

	if (!buf) {
		return(0);
	}

	while (buf[i]) {
		i++;
	}

	return(i);
}

void print(char *buf) {
	size_t len;
	size_t total_sent = 0;
	size_t tx_bytes;

	if (!buf) {
		return;
	}

	len = strlen(buf);
	while (total_sent < len) {
		if (transmit(STDOUT, buf+total_sent, len-total_sent, &tx_bytes) != 0) {
			_terminate(-1);
		}
		total_sent += tx_bytes;
	}
}

int read_until(char *buf, char delim, size_t max_len) {
	size_t total_received = 0;
	char c;
	size_t rx_bytes;

	if (!buf) {
		return(-1);
	}

	while (total_received < max_len-1) {
		if (receive(STDIN, &c, 1, &rx_bytes) != 0) {
			return(-1);
		}
		if (rx_bytes == 0) {
			return(-1);
		}
		if (c == delim) {
			break;
		}
		buf[total_received++] = c;
	}
	buf[total_received] = '\0';

	return(0);
}

int strmatch(char *buf1, char *buf2) {
	size_t len1;	
	int i;

	if (!buf1 || !buf2) {
		return(0);
	}

	len1 = strlen(buf1);
	if (len1 != strlen(buf2)) {
		return(0);
	}

	for (i = 0; i < len1; i++) {
		if (buf1[i] != buf2[i]) {
			return(0);
		}
	}

	return(1);
}

void strcopy(char *dst, char *src) {
	int i;

	if (!dst || !src) {
		return;
	}

	for (i = 0; i < strlen(src); i++) {
		dst[i] = src[i];
	}

	return;
}

void memcopy(char *dst, char *src, unsigned int len) {
	int i;

	if (!dst || !src) {
		return;
	}

	for (i = 0; i < len; i++) {
		dst[i] = src[i];
	}

	return;
}

int isdigits(char *buf) {
	int i;

	if (!buf) {
		return(0);
	}

	for (i = 0; i < strlen(buf); i++) {
		if (buf[i] < '0' || buf[i] > '9') {
			return(0);
		}
	}
	return(1);
}

int atoi(char *buf) {
	int i;
	int val = 0;
	int m = 1;

	if (!buf) {
		return(0);
	}

	i = strlen(buf);
	if (!i) {
		return(0);
	}
	
	for (i = i-1; i >= 0; i--) {
		val += ((buf[i] - '0') * m);
		m *= 10;
	}	

	return(val);
}

void print_uint(unsigned int val) {
	char buf[100];
	char buf2[100];
	int i = 0;
	int j = 0;

	if (val == 0) {
		print("0");
		return;
	}

	while (val) {
		buf[i++] = (val % 10) + '0';
		val /= 10;
	}
	buf[i] = '\0';

	for (i = strlen(buf)-1; i >= 0; i--) {
		buf2[j++] = buf[i];
	}
	buf2[j] = '\0';

	print(buf2);

	return;

}

