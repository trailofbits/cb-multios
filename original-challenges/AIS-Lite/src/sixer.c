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
#include "libc.h"
#include "common.h"
#include "sixer.h"

char get_byte_mask(unsigned char num_high_bits_zerod) {
	switch(num_high_bits_zerod) {
		case 0: return 0x3F; // 63
		case 1: return 0x1F; // 31
		case 2: return 0x0F; // 15
		case 3: return 0x07; // 7
		case 4: return 0x03; // 3
		case 5: return 0x01; // 1
	}
	return 0;
}

void init_sixer(struct sixer *s, const char *ais_msg) {
	s->bits_used = 0;
	s->ais_msg = ais_msg;
	s->p_idx = s->ais_msg;
}

unsigned int sixer_strlen(struct sixer *s) {
	// ais_msg is 6bit ASCII encoded, so each byte/char has 6 bits of data encoded in it.
	return (6 * strlen(s->p_idx)) - s->bits_used;
}

char get_msg_type(const char *ais_msg) {

	struct sixer s;
	init_sixer(&s, ais_msg);

	return (char)get_bits_from_sixer(&s, 3);
}

int get_bits_from_sixer(struct sixer *s, int num_bits) {

	unsigned int accumulator = 0;
	unsigned char byte = 0;
	unsigned char used_now = 0;
	unsigned char shift_num = 0;

	while (0 < num_bits) {
		byte = unarmor_ASCII_char((unsigned char)*(s->p_idx));
		if (0 > byte) {
			return ERR_INVALID_MESSAGE;
		}

		if (6 <= num_bits) {
			s->p_idx++;
			if (0 == s->bits_used) {
				accumulator = (accumulator << 6) + byte;
				num_bits -= 6;
			} else {
				accumulator = (accumulator << (6 - s->bits_used)) | (byte & get_byte_mask(s->bits_used));
				num_bits -= 6 - s->bits_used;
				s->bits_used = 0;
			}
		} else {
			if (num_bits > (6 - s->bits_used)) {
				used_now = 6 - s->bits_used;
			} else {
				used_now = num_bits;
			}

			shift_num = 6 - s->bits_used - used_now;
			accumulator = (accumulator << used_now) | ((byte & get_byte_mask(s->bits_used)) >> shift_num);

			if (6 == (s->bits_used + used_now)) {
				s->p_idx++;
				s->bits_used = 0;
			} else {
				s->bits_used += used_now;
			}
			num_bits -= used_now;
		}
	}

	return accumulator;
}

int sixer_bits_twos_to_sint(int twos_int, int sign_bit) {

	int accumulator = 0;
	if (0 < (twos_int & sign_bit)) {
		accumulator = -1 * ((~twos_int + 1) & (sign_bit - 1));
	} else {
		accumulator = twos_int;
	}
	return accumulator;
}

char sixer_bits_to_ASCII_str_char(unsigned char sixer_bits) {
	if (63 < sixer_bits) {
		return -1;
	} else if (32 > sixer_bits) {
		return sixer_bits + 64;
	} else {
		return sixer_bits;
	}
}

char unarmor_ASCII_char(unsigned char armored_char) {
	if ((119 < armored_char) || ((87 < armored_char) && 96 > armored_char)) {
		return -1;
	} else {
		armored_char -= 48;
	}

	if (40 <= armored_char) {
		armored_char -= 8;
	}
	return armored_char;
}
