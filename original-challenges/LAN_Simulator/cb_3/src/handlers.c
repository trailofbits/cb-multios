/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "stdlib.h"
#include "stdio.h"
#include "prng.h"
#include "common.h"
#include "L4.h"
#include "string.h"

extern Handlers Listeners[MAX_HANDLERS];

uint8_t Echo(unsigned char *Data, uint8_t DataLen, unsigned char *Response, uint8_t *ResponseLen) {

        memcpy(Response, Data, DataLen);
        *ResponseLen = DataLen;

        return(1);
}

uint8_t Chargen(unsigned char *Data, uint8_t DataLen, unsigned char *Response, uint8_t *ResponseLen) {
	uint8_t NumBytes;
	uint8_t i;

	NumBytes = prng() % 127;
	for (i = 0; i < NumBytes; i++) {
		Response[i] = prng() % 256;
	}
	*ResponseLen = NumBytes;

	return(1);
}

const char *Words[] = {
        "aa", "ab", "ac", "ad", "ae", "af", "ag", "ah", "ai", "aj", "ak", "al", "am", "an", "ao", "ap", "aq", "ar", "as", "at", "au", "av", "aw", "ax", "ay", "az",
        "ba", "bb", "bc", "bd", "be", "bf", "bg", "bh", "bi", "bj", "bk", "bl", "bm", "bn", "bo", "bp", "bq", "br", "bs", "bt", "bu", "bv", "bw", "bx", "by", "bz",
        "ca", "cb", "cc", "cd", "ce", "cf", "cg", "ch", "ci", "cj", "ck", "cl", "cm", "cn", "co", "cp", "cq", "cr", "cs", "ct", "cu", "cv", "cw", "cx", "cy", "cz",
        "da", "db", "dc", "dd", "de", "df", "dg", "dh", "di", "dj", "dk", "dl", "dm", "dn", "do", "dp", "dq", "dr", "ds", "dt", "du", "dv", "dw", "dx", "dy", "dz",
        "ea", "eb", "ec", "ed", "ee", "ef", "eg", "eh", "ei", "ej", "ek", "el", "em", "en", "eo", "ep", "eq", "er", "es", "et", "eu", "ev", "ew", "ex", "ey", "ez",
        "fa", "fb", "fc", "fd", "fe", "ff", "fg", "fh", "fi", "fj", "fk", "fl", "fm", "fn", "fo", "fp", "fq", "fr", "fs", "ft", "fu", "fv", "fw", "fx", "fy", "fz",
        "ga", "gb", "gc", "gd", "ge", "gf", "gg", "gh", "gi", "gj", "gk", "gl", "gm", "gn", "go", "gp", "gq", "gr", "gs", "gt", "gu", "gv", "gw", "gx", "gy", "gz",
        "ha", "hb", "hc", "hd", "he", "hf", "hg", "hh", "hi", "hj", "hk", "hl", "hm", "hn", "ho", "hp", "hq", "hr", "hs", "ht", "hu", "hv", "hw", "hx", "hy", "hz",
        "ia", "ib", "ic", "id", "ie", "if", "ig", "ih", "ii", "ij", "ik", "il", "im", "in", "io", "ip", "iq", "ir", "is", "it", "iu", "iv", "iw", "ix", "iy", "iz",
        "ja", "jb", "jc", "jd", "je", "jf", "jg", "jh", "ji", "jj", "jk", "jl", "jm", "jn", "jo", "jp", "jq", "jr", "js", "jt", "ju", "jv"
};
uint8_t Pwdgen_Offset;
uint8_t Pwdgen(unsigned char *Data, uint8_t DataLen, unsigned char *Response, uint8_t *ResponseLen) {
	uint8_t NumPasswords;
	uint8_t Syllables;
	char Password[22];
	const char *rand_bytes = (const char *)0x4347C000;
	
	Response[0] = '\0';
	for (NumPasswords = 0; NumPasswords < 6; NumPasswords++) {
		Password[0] = '\0';
		for (Syllables = 0; Syllables < 10; Syllables++) {
			sprintf(Password, "$s$s", Password, Words[(uint8_t)(*rand_bytes)]);
			rand_bytes += Pwdgen_Offset;
		}
		sprintf((char *)Response, "$s$s\n", Response, Password);
	}

	*ResponseLen = strlen((char *)Response);

	return(1);
}

uint8_t RegisterHandlers(void) {
	L4_RegisterHandler(7, Echo);
	L4_RegisterHandler(19, Chargen);
	L4_RegisterHandler(129, Pwdgen);
	return(1);
}

