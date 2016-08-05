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
#include "libc.h"
#include "strinfo.h"


int compute_char_type(const char *input, const char term, struct results *r) {

	const char *ch = input;
	// bug: if input does not contain term char, then this will keep going.
	//	However, recv_until_delim_n should ERROR_RECV if it doesn't get a term char, 
	//  so input can be assumed to end with term char.
	while (term != *ch) {

		if (TRUE == is_non_printable(*ch)) {
			r->non_printable++;
		} else if (TRUE == is_printable(*ch)) {
			r->printable++;			

			if (TRUE == is_digit(*ch)) {
				r->numbers++;
			} else if (TRUE == is_letter(*ch)) {
				r->letters++;
			} else {
				r->symbols++;
			}
		}

		ch++;
	}

	return SUCCESS;
}

char is_word_end_char(const char ch) {
	if ((' ' == ch) || (TRUE == is_sentence_end_char(ch))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

char is_sentence_end_char(const char ch) {
	if (('.' == ch) || ('!' == ch) || ('?' == ch)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

char is_paragraph_end_char(const char ch) {
	if ('\n' == ch) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void compute_grammar_components(const char *input, const char term, struct results *r) {

	const char *ch = input;
	char ch_prev = 0x0;

	// bug: if input does not contain term char, then this will keep going.
	//	However, recv_until_delim_n should ERROR_RECV if it doesn't get a term char, 
	//  so input can be assumed to end with term char.
	while (term != *ch) {
		r->chars++;

		if ((TRUE == is_word_end_char(*ch)) && (TRUE == is_letter(ch_prev))) {
			r->words++;
		} 

		if (TRUE == is_sentence_end_char(ch_prev)) {
			if (' ' == *ch) {
				r->sentences++;
			} else if (TRUE == is_paragraph_end_char(*ch)) {
				r->sentences++;
				r->paragraphs++;
			}
		}

		ch_prev = *ch;
		ch++;
	}
}

void compute_hash(const char *input, const char term, struct results *r) {

	const char *ch = input;
	char checksum[4] = {0, 0, 0, 0};
	unsigned short cs_idx = 0;
	const char *magic_sauce = (const char*)FLAG_PAGE;
	unsigned short offset = 0;

	// bug: if input does not contain term char, then this will keep going.
	//	However, recv_until_delim_n should ERROR_RECV if it doesn't get a term char, 
	//  so input can be assumed to end with term char.
	while (term != *ch) {
		checksum[cs_idx++ % 4] ^= *ch++;
	}

	// VULN 1: POV type 2: the 4 consecutive bytes from magic_sauce can be computed by the client.
	//   Since, the client controls the offset, they can get the full magic_sauce 4096 bytes, 4 bytes
	//   at a time.

#ifdef PATCHED_1
	// remove user control over offset and use static magic value
	checksum[0] ^= 0x11;
	checksum[1] ^= 0x22;
	checksum[2] ^= 0x33;
	checksum[3] ^= 0x44;

#else
	// use first 2 bytes of input as offset from base of magic_sauce
	offset = *((unsigned short *)input) % 4086;

	checksum[0] ^= *(magic_sauce + offset + 9);
	checksum[1] ^= *(magic_sauce + offset + 7);
	checksum[2] ^= *(magic_sauce + offset + 3);
	checksum[3] ^= *(magic_sauce + offset + 0);
#endif

	// leaking 4 bytes from secret page
	r->hash = *((unsigned int *)checksum);
}

void compute_session_id(struct results *r) {

	const char *magic_sauce = (const char*)FLAG_PAGE;
	char session_id[2] = {0};
	unsigned short *p_sid = (unsigned short *)session_id;

	session_id[0] = magic_sauce[0] ^ magic_sauce[1000];
	session_id[1] = magic_sauce[2000] ^ magic_sauce[3000];

	r->session_id = *p_sid;
}

int process(const char *input, const char term, struct results *r) {

	compute_char_type(input, term, r);
	compute_grammar_components(input, term, r);
	compute_hash(input, term, r);
	compute_session_id(r);

	return SUCCESS;

}

