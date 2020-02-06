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
#include "libcgc.h"
#include "cgc_jlib.h"

void cgc_zero(char *buf, unsigned int len) {
	unsigned int i;

	if (!buf) {
		return;
	}

	for (i = 0; i < len; i++) {
		buf[i] = '\0';
	}

	return;
}

cgc_size_t cgc_strlen(char *buf) {
	cgc_size_t i = 0;

	if (!buf) {
		return(0);
	}

	while (buf[i]) {
		i++;
	}

	return(i);
}

void cgc_print(char *buf) {
	cgc_size_t len;
	cgc_size_t total_sent = 0;
	cgc_size_t tx_bytes;

	if (!buf) {
		return;
	}

	len = cgc_strlen(buf);
	while (total_sent < len) {
		if (cgc_transmit(STDOUT, buf+total_sent, len-total_sent, &tx_bytes) != 0) {
			cgc__terminate(-1);
		}
		total_sent += tx_bytes;
	}
}

int cgc_read_until(char *buf, char delim, cgc_size_t max_len) {
	cgc_size_t total_received = 0;
	char c;
	cgc_size_t rx_bytes;

	if (!buf) {
		return(-1);
	}

	while (total_received < max_len-1) {
		if (cgc_receive(STDIN, &c, 1, &rx_bytes) != 0) {
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

int cgc_strmatch(char *buf1, char *buf2) {
	cgc_size_t len1;	
	int i;

	if (!buf1 || !buf2) {
		return(0);
	}

	len1 = cgc_strlen(buf1);
	if (len1 != cgc_strlen(buf2)) {
		return(0);
	}

	for (i = 0; i < len1; i++) {
		if (buf1[i] != buf2[i]) {
			return(0);
		}
	}

	return(1);
}

void cgc_strcopy(char *dst, char *src) {
	int i;

	if (!dst || !src) {
		return;
	}

	for (i = 0; i < cgc_strlen(src); i++) {
		dst[i] = src[i];
	}

	return;
}

void cgc_memcopy(char *dst, char *src, unsigned int len) {
	int i;

	if (!dst || !src) {
		return;
	}

	for (i = 0; i < len; i++) {
		dst[i] = src[i];
	}

	return;
}

int cgc_isdigits(char *buf) {
	int i;

	if (!buf) {
		return(0);
	}

	for (i = 0; i < cgc_strlen(buf); i++) {
		if (buf[i] < '0' || buf[i] > '9') {
			return(0);
		}
	}
	return(1);
}

int cgc_atoi(char *buf) {
	int i;
	int val = 0;
	int m = 1;

	if (!buf) {
		return(0);
	}

	i = cgc_strlen(buf);
	if (!i) {
		return(0);
	}
	
	for (i = i-1; i >= 0; i--) {
		val += ((buf[i] - '0') * m);
		m *= 10;
	}	

	return(val);
}

void cgc_print_uint(unsigned int val) {
	char buf[100];
	char buf2[100];
	int i = 0;
	int j = 0;

	if (val == 0) {
		cgc_print("0");
		return;
	}

	while (val) {
		buf[i++] = (val % 10) + '0';
		val /= 10;
	}
	buf[i] = '\0';

	for (i = cgc_strlen(buf)-1; i >= 0; i--) {
		buf2[j++] = buf[i];
	}
	buf2[j] = '\0';

	cgc_print(buf2);

	return;

}

