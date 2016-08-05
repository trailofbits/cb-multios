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

struct results {
    unsigned int hash;

    unsigned short chars;
    unsigned short words;
    unsigned short sentences;
    unsigned short paragraphs;

    unsigned short printable;
    unsigned short non_printable;

    unsigned short letters;
    unsigned short numbers;
    unsigned short symbols;

    unsigned short session_id;
};

/**
 * Process input and store results in r.
 *
 * @param input Input character string.
 * @param term Input termination char
 * @param r Results struct
 * @return SUCCESS if success, else -1
 */
int process(const char *input, const char term, struct results *r);


int compute_char_type(const char *input, const char term, struct results *r);

void compute_grammar_components(const char *input, const char term, struct results *r);

void compute_hash(const char *input, const char term, struct results *r);

char is_word_end_char(const char ch);

char is_sentence_end_char(const char ch);

char is_paragraph_end_char(const char ch);