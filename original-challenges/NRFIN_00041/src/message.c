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
#include "message.h"
#include "sixer.h"

const char *STATUS[] = {"underway using engine",
						  "at anchor",
						  "not under command",
						  "restricted maneuverability",
						  "constrained by draught",
						  "moored",
						  "aground",
						  "fishing",
						  "underway using sail"};

const char *MANEUEVER[] = {"maneuver not available",
							"no special maneuver",
							"special maneuver"};

const char *EPFD[9] = {"undefined",
					  "GPS",
					  "GLONASS",
					  "Combined GPS/GLONASS",
					  "Loran-C",
					  "Chayka",
					  "Integrated navigation system",
					  "Surveyed",
					  "Galileo"};

int to_english(char *english, struct sentence_struct *ss) {

	unsigned char msg_type = 0;

	if (DONE != ss->msg_status) {
		return ERR_INVALID_MESSAGE;
	}

	msg_type = get_msg_type(ss->ais_msg);
	if (msg_type != ss->msg_type) {
		return ERR_INVALID_MESSAGE;
	}

	switch(msg_type) {
		case 1:
			return parse_msg_type_1(english, ss->ais_msg);
		case 4:
			return parse_msg_type_4(english, ss->ais_msg);
		case 5:
			return parse_msg_type_5(english, ss->ais_msg);
		default:
			return ERR_INVALID_MESSAGE;
	}
}


int parse_msg_type_1(char *english, const char *ais_msg) {
	struct sixer s;
	init_sixer(&s, ais_msg);
	char *p_eng = english;
	int val = 0;
	int ret = 0;

	if (144 != sixer_strlen(&s)) {
		return ERR_INVALID_MESSAGE;
	}

	// type 3 bits (1)
	if (1 != (val = get_bits_from_sixer(&s, 3))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 8, "~c,", "type 1");
	p_eng += ret;

	// mmsi 30 bits (9 digits)
	if (0 > (val = get_bits_from_sixer(&s, 30))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 11, "~n,", val);
	p_eng += ret;

	// status 4 bits (0-8)
	val = get_bits_from_sixer(&s, 4);
	if ((0 > val) || (8 < val)) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 28, "~c,", STATUS[val]);
	p_eng += ret;

	// turn 8 bits (-127 - 128) (twos)
	val = get_bits_from_sixer(&s, 8);
	if (128 < val) { // is negative
		val = sixer_bits_twos_to_sint(val, 0x80);
	}
	if (0 == val) {
		ret = snprintf(p_eng, 13, "~c,", "not turning");
	} else if (0 > val) {
		ret = snprintf(p_eng, 18, "~c ~n,", "turning left", -val);
	} else {
		ret = snprintf(p_eng, 19, "~c ~n,", "turning right", val);
	}
	p_eng += ret;

	// speed 10 bits (0 to 1023)
	val = get_bits_from_sixer(&s, 10);
	if (1023 == val) {
		ret = snprintf(p_eng, 11, "~c,", "speed unk");
	} else if (1020 < val) {
		ret = snprintf(p_eng, 9, "~c,", ">102kts");
	} else {
		ret = snprintf(p_eng, 8, "~nkts,", val/10);
	}
	p_eng += ret;

	// accuracy 1 bit (0 or 1)
	get_bits_from_sixer(&s, 1);

	// lat 27 bits (60k * (-90 to 91)) (twos)
	val = get_bits_from_sixer(&s, 27);
	if ((91*60000) < val) { // is negative
		val = sixer_bits_twos_to_sint(val, 0x800000);
	}

	if ((91*60000) == val) {
		ret = snprintf(p_eng, 9, "~c,", "lat unk");
	} else if (0 == val) {
		ret = snprintf(p_eng, 3, "~n,", val);
	} else if (0 < val) {
		ret = snprintf(p_eng, 10, "~nN,", val);
	} else {
		ret = snprintf(p_eng, 10, "~nS,", -val);
	}
	p_eng += ret;

	// long 28 bits (60k * (-180 to 181)) (twos)
	val = get_bits_from_sixer(&s, 28);
	if ((181*60000) < val) { // is negative
		val = sixer_bits_twos_to_sint(val, 0x1000000);
	}

	if ((181*60000) == val) {
		ret = snprintf(p_eng, 9, "~c,", "lon unk");
	} else if (0 == val) {
		ret = snprintf(p_eng, 3, "~n,", val);
	} else if (0 < val) {
		ret = snprintf(p_eng, 11, "~nE,", val);
	} else {
		ret = snprintf(p_eng, 11, "~nW,", -val);
	}
	p_eng += ret;

	// course 12 bits (0 - 3600)
	val = get_bits_from_sixer(&s, 12);
	if (3600 == val) {
		ret = snprintf(p_eng, 12, "~c,", "course unk");
	} else if (3590 < val) {
		return ERR_INVALID_MESSAGE;
	} else {
		ret = snprintf(p_eng, 8, "c:~n,", val/10);
	}
	p_eng += ret;

	// heading 9 bits (0 - 511)
	val = get_bits_from_sixer(&s, 9);
	if (511 == val) {
		ret = snprintf(p_eng, 13, "~c,", "heading unk");
	} else if (359 < val) {
		return ERR_INVALID_MESSAGE;
	} else {
		ret = snprintf(p_eng, 10, "h:~n TN,", val);
	}
	p_eng += ret;

	// seconds 6 bits (0 - 59)
	get_bits_from_sixer(&s, 6);

	// maneuver 2 bits (0 - 2)
	val = get_bits_from_sixer(&s, 2);
	if (3 == val) {
		return ERR_INVALID_MESSAGE;
	} else {
		ret = snprintf(p_eng, 24, "~c.", MANEUEVER[val]);
	}
	p_eng += ret;

	return SUCCESS;
}

int parse_msg_type_4(char *english, const char *ais_msg) {
	struct sixer s;
	init_sixer(&s, ais_msg);
	char *p_eng = english;
	int val = 0;
	int ret = 0;

	if (138 != sixer_strlen(&s)) { // 136 + 2 padding from the ASCII encoding.
		return ERR_INVALID_MESSAGE;
	}

	// type 3 bits (4)
	if (4 != (val = get_bits_from_sixer(&s, 3))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 8, "~c,", "type 4");
	p_eng += ret;

	// mmsi 30 bits (9 digits)
	if (0 > (val = get_bits_from_sixer(&s, 30))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 11, "~n,", val);
	p_eng += ret;

	// year 14 bits (0-9999)
	val = get_bits_from_sixer(&s, 14);
	if (0 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 6, "~n,", val);
	}
	p_eng += ret;

	// month 4 bits (0-12)
	val = get_bits_from_sixer(&s, 4);
	if (12 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (0 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// day 5 bits (0-31)
	val = get_bits_from_sixer(&s, 5);
	if (31 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (0 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// hour 5 bits (0-24)
	val = get_bits_from_sixer(&s, 5);
	if (24 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (24 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// minutes 6 bits (0-60)
	val = get_bits_from_sixer(&s, 6);
	if (60 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (60 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// seconds 6 bits (0-60)
	val = get_bits_from_sixer(&s, 6);
	if (60 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (60 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// accuracy 1bit (0 or 1) -- NOT IN STR
	val = get_bits_from_sixer(&s, 1);

	// lat 27 bits (60k * (-90 to 91)) (twos)
	val = get_bits_from_sixer(&s, 27);
	if ((91*60000) < val) { // is negative
		val = sixer_bits_twos_to_sint(val, 0x800000);
	}

	if ((91*60000) == val) {
		ret = snprintf(p_eng, 9, "~c,", "lat unk");
	} else if (0 == val) {
		ret = snprintf(p_eng, 3, "~n,", val);
	} else if (0 < val) {
		ret = snprintf(p_eng, 10, "~nN,", val);
	} else {
		ret = snprintf(p_eng, 10, "~nS,", -val);
	}
	p_eng += ret;

	// long 28 bits (60k * (-180 to 181)) (twos)
	val = get_bits_from_sixer(&s, 28);
	if ((181*60000) < val) { // is negative
		val = sixer_bits_twos_to_sint(val, 0x1000000);
	}

	if ((181*60000) == val) {
		ret = snprintf(p_eng, 9, "~c,", "lon unk");
	} else if (0 == val) {
		ret = snprintf(p_eng, 3, "~n,", val);
	} else if (0 < val) {
		ret = snprintf(p_eng, 11, "~nE,", val);
	} else {
		ret = snprintf(p_eng, 11, "~nW,", -val);
	}
	p_eng += ret;

	// epfd 4 bits (0-8)
	val = get_bits_from_sixer(&s, 4);
	if (8 < val) {
		return ERR_INVALID_MESSAGE;
	} else {
		ret = snprintf(p_eng, 30, "~c.", EPFD[val]);
	}
	return SUCCESS;
}

int parse_msg_type_5(char *english, const char *ais_msg) {
	struct sixer s;
	init_sixer(&s, ais_msg);
	char *p_eng = english;
	int val = 0;
	int ret = 0;
	int byte = 0;
	int skip = FALSE;

	if (384 != sixer_strlen(&s)) {
		return ERR_INVALID_MESSAGE;
	}

	// type 3 bits (5)
	if (5 != (val = get_bits_from_sixer(&s, 3))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 8, "~c,", "type 5");
	p_eng += ret;

	// mmsi 30 bits (9 digits)
	if (0 > (val = get_bits_from_sixer(&s, 30))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 11, "~n,", val);
	p_eng += ret;

	// imo 30 bits (9 digits)
	if (0 > (val = get_bits_from_sixer(&s, 30))) {return ERR_INVALID_MESSAGE;}
	ret = snprintf(p_eng, 11, "~n,", val);
	p_eng += ret;

	// callsign 42 bits (7 six-bit chars)
	skip = FALSE;
	for (int idx = 0; idx < 7; idx++) {
		if (0 > (val = get_bits_from_sixer(&s, 6))) {return ERR_INVALID_MESSAGE;}
		byte = sixer_bits_to_ASCII_str_char(val);
		if (('@' == byte) || (TRUE == skip)) {
			skip = TRUE;
		} else {
			*p_eng = byte;
			p_eng++;
		}
	}
	*p_eng = ',';
	p_eng++;

	skip = FALSE;
	for (int idx = 0; idx < 20; idx++) {
		if (0 > (val = get_bits_from_sixer(&s, 6))) {return ERR_INVALID_MESSAGE;}
		byte = sixer_bits_to_ASCII_str_char(val);
		if (('@' == byte) || (TRUE == skip)) {
			skip = TRUE;
		} else {
			*p_eng = byte;
			p_eng++;
		}
	}
	*p_eng = ',';
	p_eng++;

	// epfd 4 bits (0-8)
	val = get_bits_from_sixer(&s, 4);
	if (8 < val) {
		return ERR_INVALID_MESSAGE;
	} else {
		ret = snprintf(p_eng, 30, "~c,", EPFD[val]);
	}
	p_eng += ret;

	// month 4 bits (0-12)
	val = get_bits_from_sixer(&s, 4);
	if (12 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (0 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// day 5 bits (0-31)
	val = get_bits_from_sixer(&s, 5);
	if (31 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (0 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// hour 5 bits (0-24)
	val = get_bits_from_sixer(&s, 5);
	if (24 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (24 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// minutes 6 bits (0-60)
	val = get_bits_from_sixer(&s, 6);
	if (60 < val) {
		return ERR_INVALID_MESSAGE;
	} else if (60 == val) {
		ret = snprintf(p_eng, 5, "~c,", "N/A");
	} else {
		ret = snprintf(p_eng, 4, "~n,", val);
	}
	p_eng += ret;

	// draught 8 bits (0-255)
	val = get_bits_from_sixer(&s, 8);
	ret = snprintf(p_eng, 5, "~n,", val);
	p_eng += ret;

	// dest 120 bits (20 six-bit chars)
	skip = FALSE;
	for (int idx = 0; idx < 20; idx++) {
		if (0 > (val = get_bits_from_sixer(&s, 6))) {return ERR_INVALID_MESSAGE;}
		byte = sixer_bits_to_ASCII_str_char(val);
		if (('@' == byte) || (TRUE == skip)) {
			skip = TRUE;
		} else {
			*p_eng = byte;
			p_eng++;
		}
	}
	*p_eng = '.';
	p_eng++;

	return SUCCESS;
}
