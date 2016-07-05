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
#include "sentence.h"
#include "sixer.h"



int parse_sentence(const char *buf, struct sentence_struct *ss) {

	const char *p_buf = NULL;
	const char *start = "!AAAAA";
	const char *end = NULL;
	unsigned int frag_num = 0;
	unsigned int frag_total = 0;
	unsigned int session_id = 0;
	unsigned char msg_type = 0;
	int ret = 0;

	FAILBAIL(get_sentence_start(buf, &p_buf));
	if (SUCCESS != strncmp(start, p_buf, 6)) {
		return ERR_INVALID_SENTENCE;
	}

	if (TRUE != is_checksum_correct(p_buf)) {
		return ERR_INVALID_SENTENCE;
	}

	p_buf = get_next_field(p_buf);
	if (NULL == p_buf) {
		return ERR_INVALID_SENTENCE;
	} else {
		FAILBAIL(field_to_uint(p_buf, &frag_num));
	}

	p_buf = get_next_field(p_buf);
	if (NULL == p_buf) {
		return ERR_INVALID_SENTENCE;
	} else {
		FAILBAIL(field_to_uint(p_buf, &frag_total));
	}

	p_buf = get_next_field(p_buf);
	if (NULL == p_buf) {
		return ERR_INVALID_SENTENCE;
	} else {
		FAILBAIL(field_to_uint(p_buf, &session_id));
	}

	if (EMPTY == ss->msg_status) {
		if ((1 != frag_num) || (frag_num > frag_total)) {
			return ERR_INVALID_SENTENCE;
		} else {
			ss->frag_total = frag_total;
			ss->frag_num = frag_num;
			ss->session_id = session_id;
		}
	} else if (PARTIAL == ss->msg_status) {
		if ((1 + ss->frag_num != frag_num) || 
			(ss->frag_total != frag_total) || 
			(ss->session_id != session_id) ||
			(frag_num > frag_total)) {
			return ERR_INVALID_SENTENCE;
		} else {
			ss->frag_num++;
		}
	} else {
		return ERR_INVALID_SENTENCE;
	}

	p_buf = get_next_field(p_buf); // start of ascii encoded AIS msg payload
	end = get_next_field(p_buf) - 1;

#if PATCHED
	if (MAX_SENTENCE_LEN < (end-p_buf+strlen(ss->ais_msg))) {
		return ERR_INVALID_SENTENCE;
	}
#endif
	ss->p_ais_msg_idx = fieldncpy(p_buf, ss->p_ais_msg_idx, end-p_buf);
	if (EMPTY == ss->msg_status) {
		ss->msg_type = get_msg_type(p_buf);
		if ((1 != ss->msg_type) && (4 != ss->msg_type) && (5 != ss->msg_type)) {
			return ERR_INVALID_SENTENCE;
		}
	}

	if (ss->frag_total == ss->frag_num) {
		ss->msg_status = DONE;
	} else {
		ss->msg_status = PARTIAL;
	}

	return SUCCESS;
}

void reset_sentence_struct(struct sentence_struct *ss) {
 	ss->frag_num = 0;
 	ss->frag_total = 0;
 	ss->session_id = 0;
	ss->msg_status = EMPTY;
	ss->msg_type = 0;
	memset((void *)ss->ais_msg, 0, MAX_SENTENCE_LEN);
 	ss->p_ais_msg_idx = ss->ais_msg;
 }

int get_sentence_start(const char *str, const char **start) {

	if (NULL == str) {
		return ERR_NULL_PARAM;
	}
	if (NULL == start) {
		return ERR_NULL_PARAM;
	}

	while ('!' != *str && 0 != *str) {
		str++;
	}

	if ('!' == *str) {
		*start = str;
		return SUCCESS;
	} else {
		*start = NULL;
		return ERR_INVALID_SENTENCE;
	}
}


int is_checksum_correct(const char *str) {

	const char *ptr = NULL;
	int ret = 0;
	unsigned char calcsum = 0;

	// calculate checksum
	if (SUCCESS != get_sentence_start(str, &ptr)) {
		return ERR_INVALID_SENTENCE;
	}
	ptr++; // advance past the '!'

	while ((0 != *ptr) && ('*' != *ptr)) {
		calcsum ^= *ptr;
		ptr++;
	}

	if ('*' != *ptr) {
		return ERR_INVALID_SENTENCE;
	}

	if ((FALSE == is_hex_digit(*(ptr+1))) || (FALSE == is_hex_digit(*(ptr+2)))) {
		return ERR_INVALID_SENTENCE;
	}

	if (calcsum == ((ascii_hex_to_bin(*(ptr+1)) << 4) + ascii_hex_to_bin(*(ptr+2)))) {
		return TRUE;
	}

	return FALSE;
}

int field_to_uint(const char *str, unsigned int *int_val) {

	int tmp = 0;
	*int_val = 0;

	while ( (NULL != str) && (0 != *str) && ('*' != *str) && (',' != *str)) {
		*int_val *= 10;

		if (0 > (tmp = ascii_hex_to_bin(*str))) {
			return tmp;
		}
		*int_val += tmp;
		str++;
	}

	return SUCCESS;
}

const char *get_next_field(const char *str) {

	while ( (NULL != str) && (0 != *str) && ('*' != *str) && (',' != *str)) {
		str++;
	}

	if ( (NULL != str) && (0 != *str)) {
		return str + 1;
	}

	return NULL;
}

char *fieldncpy(const char *str, char *buf, int n) {

	while ( (0 != n) 
			&& (NULL != str) && (NULL != buf) && (0 != *str) 
			&& ('*' != *str) && (',' != *str)) {
		*buf = *str;
		str++;
		buf++;
		n--;
	}

	if (NULL != buf) {
		*buf = 0;
	}

	return buf;
}

