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
#ifndef SENTENCE_H
#define SENTENCE_H 1

// sentences are a comma separated list of fields.

#define MAX_SENTENCE_LEN 65 // longest sentence is 64 + 1 for NULL

enum msg_status {
	EMPTY = 1,
	PARTIAL = 2,
	DONE = 3,
};

struct sentence_struct {
	unsigned int frag_num;
	unsigned int frag_total;
	unsigned int session_id;
	char *p_ais_msg_idx;			// ptr to idx after last byte received in ais_msg
	unsigned char msg_status;		// ais message receive status (EMPTY, PARTIAL, DONE)
	unsigned char msg_type;			// ais message type
	char *ais_msg; // ASCII encoded ais message content
};


/**
 * Parse the receied sentence and store the data in the sentence_struct.
 *
 * @param buf Pointer to buffer containing received sentence.
 * @param ss Pointer to sentence struct.
 * @return SUCCESS if sucessful parse, else ERR_INVALID_SENTENCE on error.
 */
int parse_sentence(const char *buf, struct sentence_struct *ss);

/**
 * Set the sentence_struct to all 0's.
 *
 * @param sentence_struct Pointer to sentence struct.
 */
void reset_sentence_struct(struct sentence_struct *ss);

/**
 * Find the start of the sentence in the string str.
 *
 * @param str Pointer to char string
 * @param start Store a pointer to the start of the sentence.
 * @return SUCCESS if start is found, else ERR_INVALID_SENTENCE
 */
int get_sentence_start(const char *str, const char **start);

/**
 * Calculate the checksum and compare with the value provided at the 
 * end of the sentence.
 *
 * @param str Pointer to char string
 * @return TRUE if checksum is correct, FALSE if incorrect,
 *	or ERR_INVALID_SENTENCE on error
 */
int is_checksum_correct(const char *str);

/**
 * Convert a field in the sentence to a uint.
 *
 * @param str Pointer to start of field within a sentence.
 * @param int_val Pointer to uint to hold result
 * @return SUCCESS if conversion succeeded, else -1 if it failed. int_val
 *	content is undefined on failure.
 */
int field_to_uint(const char *str, unsigned int *int_val);

/**
 * Get a pointer to the start of the next field.
 *
 * @param str Pointer to anywhere within a sentence.
 * @return address of first char of next field, NULL if at end of str.
 */
const char * get_next_field(const char *str);

/**
 * Copy count bytes of field from the sentence into a buffer.
 *
 * @ param str Pointer to start of a field in a sentence. (src)
 * @ param buf Pointer to buffer to store the field. (dest)
 * @ param n Number of bytes to copy.
 * @return VA of last char written to buf (usually '\0')
 */
char *fieldncpy(const char *str, char *buf, int n);


#endif