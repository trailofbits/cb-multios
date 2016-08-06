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


#ifndef OPERATION_H
#define OPERATION_H 1

#define ALLOC(sz,p) if (SUCCESS != allocate(sz, 0, (void **)p)) {_terminate(ERRNO_ALLOC);}
#define RECV(v,s) if(s != recv_all((char *)v, s)) {_terminate(ERR_RECV_FAILED);}
#define SENDSI(v) send((char *)&v, sizeof(int32_t));

// 4096 syllables bytes, assuming 2 bytes per syllable is 2048 syllables
// this assumption is wrong because one syllable is 3 bytes.
#define MAX_SYLLABLES_BYTES 4096
// 2048 notes bytes, assyming 1 byte per note is 2048 notes
// this assumption is correct. However, when the notes
// get converted to syllables, if any note relates to the one
// 3 byte syllable, then the total syllable bytes will exceed 4096 bytes.
#define MAX_NOTES_BYTES 2048
#define BUFFER_LEN 4096

// notes
enum {
	C = 1,
	D = 2,
	E = 3,
	F = 4,
	G = 5,
	A = 6,
	B = 7,
};

// syllables
enum {
	Ut = 1,
	Re = 2,
	Mi = 3,
	Fa = 4,
	Sol = 5,
	La = 6,
	Si = 7,
};

enum {
	ERR_RECV_FAILED = -900,
	ERR_INVALID_CMD = -901,
	ERR_INVALID_NOTE = -902,
	ERR_INVALID_SYLLABLE = -903,
	ERR_TOO_MANY_NOTES = -904,
	ERR_TOO_MANY_SYLLABLES = -905,
	ERR_NO_NOTES = -906,
	ERR_NO_SYLLABLES = -907,
};

extern int to_syllables(char *syllables_buf, char *notes_buf);
extern int to_notes(char *syllables_buf, char *notes_buf);

#endif