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


#ifndef SIXER_H
#define SIXER_H 1


struct sixer {
	unsigned int bits_used;
	const char *p_idx;
	const char *ais_msg;
};

/**
 * Get a byte mask with the high bits zerod.
 *
 * @param num_high_bits_zerod The number of high bits zerod in the mask
 * @return byte mask
 */
char get_byte_mask(unsigned char num_high_bits_zerod);

/**
 * Initialized the sixer struct.
 *
 * @param s Pointer to sixer struct.
 * @param ais_msg Pointer to 6bit ASCII encoded ais msg
 */
void init_sixer(struct sixer *s, const char *ais_msg);

/**
 * Count number of bits left in the ais msg.
 *
 * @param s Pointer to sixer struct.
 * @return Number of bits
 */
unsigned int sixer_strlen(struct sixer *s);

/**
 * Get the type value of the ais message.
 *
 * @param ais_msg Pointer to 6bit ASCII encoded ais msg.
 * @return msg type number or ERR_INVALID_MESSAGE on error
 */
char get_msg_type(const char *ais_msg);

/**
 * Get the next num_bits bits from the 6bit ASCII encoded ais msg.
 *
 * @param s Pointer to sixer struct.
 * @param num_bits Number of bits to extract from ais message.
 * @return extracted bits or ERR_INVALID_MESSAGE on error.
 */
int get_bits_from_sixer(struct sixer *s, int num_bits);

/**
 * Convert two's compliment int to signed int.
 *
 * @param two_int Two's compliment int.
 * @param sign_bit A single 1 shifted to align with the sign bit.
 * @return signed int
 */
int sixer_bits_twos_to_sint(int twos_int, int sign_bit);

/**
 * Convert sixer bits to ASCII char used in AIS message content.
 *
 * @param sixer_bits Bits to convert to ASCII char
 * @return ASCII char, or -1 if sixer_bits is > 63.
 */
char sixer_bits_to_ASCII_str_char(unsigned char sixer_bits);

/**
 * Convert ASCII armored char to unarmored 6bit char.
 *
 * @param armored_char ASCII armored char
 * @return 6bit char, or -1 if armored_char > 63
 */
char unarmor_ASCII_char(unsigned char armored_char);


#endif

