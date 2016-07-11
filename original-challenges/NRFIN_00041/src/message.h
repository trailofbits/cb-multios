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
#include "sentence.h"

#ifndef MESSAGE_H
#define MESSAGE_H 1

#define MAX_ENGLISH_LEN 140 // max msg len: msg 1 = 137, msg 4 = 91, msg 5 = 124


/**
 * Determine AIS message type and dispatch message-type-specific parser.
 *
 * @param english Pointer to char buffer to store english translation.
 * @param ss Sentence struct holding ais message to translate.
 * @return SUCCESS if fully translated, PARTIAL if only have partial message,
 *	or ERR_INVALID_MESSAGE on error.
 */
int to_english(char *english, struct sentence_struct *ss);

/**
 * Parser for AIS message type 1.
 *
 * @param english Pointer to char buffer to store english translation.
 * @param ais_msg ASCII 6-bit armored AIS payload.
 * @return SUCCESS if successful, or ERR_INVALID_MESSAGE on error.
 */
int parse_msg_type_1(char *english, const char *ais_msg);

/**
 * Parser for AIS message type 4.
 *
 * @param english Pointer to char buffer to store english translation.
 * @param ais_msg ASCII 6-bit armored AIS payload.
 * @return SUCCESS if successful, or ERR_INVALID_MESSAGE on error.
 */
int parse_msg_type_4(char *english, const char *ais_msg);

/**
 * Parser for AIS message type 5.
 *
 * @param english Pointer to char buffer to store english translation.
 * @param ais_msg ASCII 6-bit armored AIS payload.
 * @return SUCCESS if successful, or ERR_INVALID_MESSAGE on error.
 */
int parse_msg_type_5(char *english, const char *ais_msg);




#endif