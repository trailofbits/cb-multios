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
#include "operation.h"

/*
 * Convert the note to the associated syllable and save the
 * syllable into syllable_buf.
 *
 * Returns:
 *  Success: 2 or 3 (number of letters written to syllable_buf)
 *  Failure: ERR_INVALID_NOTE
 */
int get_syllable_for_note_id(int note_id, char *syllable_buf) {

	switch(note_id) {
	case C:
		syllable_buf[0] = 'U';
		syllable_buf[1] = 't';
		return 2;
	case D:
		syllable_buf[0] = 'R';
		syllable_buf[1] = 'e';
		return 2;
	case E:
		syllable_buf[0] = 'M';
		syllable_buf[1] = 'i';
		return 2;
	case F:
		syllable_buf[0] = 'F';
		syllable_buf[1] = 'a';
		return 2;
	case G:
		syllable_buf[0] = 'S';
		syllable_buf[1] = 'o';
		syllable_buf[2] = 'l';
		return 3;
	case A:
		syllable_buf[0] = 'L';
		syllable_buf[1] = 'a';
		return 2;
	case B:
		syllable_buf[0] = 'S';
		syllable_buf[1] = 'i';
		return 2;
	default:
		return ERR_INVALID_NOTE;
	}
}

/*
 * Convert the syllable to the associated note and save the
 * note into note_buf.
 *
 * If syllable is invalid, note_buf is undefined.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_SYLLABLE
 */
int get_note_for_syllable_id(int syllable_id, char *note_buf) {

	switch(syllable_id) {
	case Ut:
		note_buf[0] = 'C';
		return SUCCESS;
	case Re:
		note_buf[0] = 'D';
		return SUCCESS;
	case Mi:
		note_buf[0] = 'E';
		return SUCCESS;
	case Fa:
		note_buf[0] = 'F';
		return SUCCESS;
	case Sol:
		note_buf[0] = 'G';
		return SUCCESS;
	case La:
		note_buf[0] = 'A';
		return SUCCESS;
	case Si:
		note_buf[0] = 'B';
		return SUCCESS;
	default:
		return ERR_INVALID_SYLLABLE;
	}
}

/*
 * Read the string and return the id of the first note.
 *
 * str is not expected to be null terminated.
 *
 * Returns:
 *  Success: 1 thru 7 from notes enum
 *  Failure: ERR_INVALID_NOTE
 */
int get_next_note_id(const char *str) {

	switch(str[0]) {
	case 'C':
		return C;
	case 'D':
		return D;
	case 'E':
		return E;
	case 'F':
		return F;
	case 'G':
		return G;
	case 'A':
		return A;
	case 'B':
		return B;
	default:
		return ERR_INVALID_NOTE;
	}
}

/*
 * Read the string and return the id of the 
 * syllable at the beginning of the string.
 *
 * bytes_read is a 1 byte char buffer.
 * str is not expected to be null terminated.
 *
 * If an invaild syllable is encountered, bytes_read is undefined.
 *  And the syllables in the remainder of the string are undefined.
 *
 * Returns:
 *  Success: 1 thru 7 in syllables enum
 *  Failure: ERR_INVALID_SYLLABLE
 */
int get_next_syllable_id(const char *str, char *bytes_read) {

	char s0 = str[0];
	char s1 = str[1];
	char s2 = str[2];
	if ('U' == s0 && 't' == s1) {
		bytes_read[0] = 2;
		return Ut;
	} else 	if ('R' == s0 && 'e' == s1) {
		bytes_read[0] = 2;
		return Re;
	} else 	if ('M' == s0 && 'i' == s1) {
		bytes_read[0] = 2;
		return Mi;
	} else 	if ('F' == s0 && 'a' == s1) {
		bytes_read[0] = 2;
		return Fa;
	} else 	if ('S' == s0 && 'o' == s1 && 'l' == s2) {
		bytes_read[0] = 3;
		return Sol;
	} else 	if ('L' == s0 && 'a' == s1) {
		bytes_read[0] = 2;
		return La;
	} else 	if ('S' == s0 && 'i' == s1) {
		bytes_read[0] = 2;
		return Si;
	} else {
		return ERR_INVALID_SYLLABLE;
	}
}

/*
 * Write the note matching syllable_id into notes_buf.
 *
 * Returns:
 *  Success: 1 (number of bytes written)
 *  Failure: ERR_INVALID_SYLLABLE
 */
int write_note_to_buf(int syllable_id, char *notes_buf) {

	int ret = 1;
	char note = 0;

	ret = get_note_for_syllable_id(syllable_id, &note);
	if (SUCCESS == ret) {
		notes_buf[0] = note;
		ret = 1;
	}
	return ret;
}

/*
 * Write the syllable matching note_id into syllable_buf.
 *
 * Returns:
 *  Success: 2 or 3 (number of bytes written)
 *  Failure: ERR_INVALID_NOTE
 */
int write_syllable_to_buf(int note_id, char *syllable_buf) {

	int ret = 2;
	char syllable[3] = {0};

	ret = get_syllable_for_note_id(note_id, syllable);
	if (0 < ret) {
		syllable_buf[0] = syllable[0];
		syllable_buf[1] = syllable[1];
	}
	if (3 == ret) {
		syllable_buf[2] = syllable[2];
	}
	return ret;
}

/*
 * Loop through syllables in syllables_buf, convert them to notes and
 *  write them to notes_buf.
 *
 * Processing will stop when either an invalid syllable is found,
 * or bytes_count syllables have been processed.
 *
 * Returns:
 *  Success: total bytes written to notes_buf (> 0)
 *  Failure: ERR_INVALID_SYLLABLE
 */
int process_syllables(uint32_t bytes_count, char *syllables_buf, char *notes_buf) {

	int ret = 1;
	char *s_buf_ptr = syllables_buf;
	char *n_buf_ptr = notes_buf;
	int syllable_id = 0;
	char bytes_read[1] = {0};
	int total_bytes_written = 0;

	while ((0 < ret) && (0 < bytes_count)) {
		syllable_id = get_next_syllable_id(s_buf_ptr, bytes_read);
		if (0 < syllable_id) {
			s_buf_ptr += bytes_read[0];
			bytes_count -= bytes_read[0];

			ret = write_note_to_buf(syllable_id, n_buf_ptr);
			if (1 == ret) {
				n_buf_ptr += ret;
				total_bytes_written += ret;
			}
		} else {
			ret = syllable_id;
		}

	}

	// ret == 0 not possible.
	if (0 < ret) {
		ret = total_bytes_written;
	}

	return ret;
}

/*
 * Loop through notes in notes_buf, convert them to syllables and
 *  write them to syllables_buf.
 *
 * Processing will stop when either an invalid note is found,
 * or bytes_count notes have been processed.
 *
 * Returns:
 *  Success: total bytes written to syllables_buf (> 0)
 *  Failure: ERR_INVALID_NOTE, ERR_TOO_MANY_NOTES
 */
int process_notes(uint32_t bytes_count, char *syllables_buf, char *notes_buf) {

	int ret = 1;
	char *s_buf_ptr = syllables_buf;
	char *n_buf_ptr = notes_buf;
	int note_id = 0;
	int total_bytes_written = 0;

#if PATCHED
	while ((0 < ret) && ((MAX_SYLLABLES_BYTES - 2) > total_bytes_written) && (0 < bytes_count)) {
#else
	while ((0 < ret) && (MAX_SYLLABLES_BYTES > total_bytes_written) && (0 < bytes_count)) {
#endif
		note_id = get_next_note_id(n_buf_ptr);
		if (0 < note_id) {
			n_buf_ptr++;
			bytes_count--;

			ret = write_syllable_to_buf(note_id, s_buf_ptr);
			if ((2 == ret) || (3 == ret)) {
				s_buf_ptr += ret;
				total_bytes_written += ret;
			}
		} else {
			ret = note_id;
		}
	}

	// ret == 0 not possible.
	if (0 < ret) {
		ret = total_bytes_written;
	}

	return ret;
}

/*
 * Send resultant syllables to client.
 */
void send_syllables(uint32_t bytes_count, char *syllable_buf) {
	send(syllable_buf, bytes_count * sizeof(char));
}

/*
 * Send resultant notes to client.
 */
void send_notes(uint32_t bytes_count, char *notes_buf) {
	send(notes_buf, bytes_count * sizeof(char));	
}

/*
 * Receive the token count.
 *
 * Returns:
 *  Token count >= 0
 */
uint32_t recv_bytes_count() {
    uint32_t count[1] = {0};
    RECV(count, sizeof(uint32_t));
	return count[0];
}

/*
 * Control operation to convert received notes into syllables
 * and send resulting syllables back to client.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_NOTE, ERR_TOO_MANY_NOTES,
 * 			 ERR_NO_NOTES, ERR_NO_SYLLABLES
 */
int to_syllables(char *syllables_buf, char *notes_buf) {

	int ret = 0;
	int total_bytes_written = 0;

	uint32_t bytes_count = recv_bytes_count();

	if (0 >= bytes_count) {
		return ERR_NO_NOTES;
	}

	if (MAX_NOTES_BYTES < bytes_count) {
		return ERR_TOO_MANY_NOTES;
	}

	RECV(notes_buf, bytes_count);

	total_bytes_written = process_notes(bytes_count, syllables_buf, notes_buf);

	if (0 < total_bytes_written) {
		send_syllables(total_bytes_written, syllables_buf);
		ret = SUCCESS;
	} else if (0 == total_bytes_written) {
		ret = ERR_NO_SYLLABLES;
	} else {
		ret = total_bytes_written;
	}

	return ret;
}

/*
 * Control operation to convert received syllables into notes
 * and send resulting notes back to client.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_SYLLABLE, ERR_TOO_MANY_SYLLABLES, 
 *			 ERR_NO_SYLLABLES, ERR_NO_NOTES
 */
int to_notes(char *syllables_buf, char *notes_buf) {

	int ret = 0;
	int total_bytes_written = 0;

	uint32_t bytes_count = recv_bytes_count();

	if (0 >= bytes_count) {
		return ERR_NO_SYLLABLES;
	}

	if (MAX_SYLLABLES_BYTES < bytes_count) {
		return ERR_TOO_MANY_SYLLABLES;
	}

	RECV(syllables_buf, bytes_count);

	total_bytes_written = process_syllables(bytes_count, syllables_buf, notes_buf);

	if (0 < total_bytes_written) {
		send_notes(total_bytes_written, notes_buf);
		ret = SUCCESS;
	} else if (0 == total_bytes_written) {
		ret = ERR_NO_NOTES;
	} else {
		ret = total_bytes_written;
	}

	return ret;
}