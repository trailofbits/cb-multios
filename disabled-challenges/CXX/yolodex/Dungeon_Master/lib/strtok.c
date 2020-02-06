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
#include "libcgc.h"

/**
* Finds the first occurence of c in s
* 
* @param s the string to look in
* @param c the character to look for
*
* @return The first index in s where c occurs
*/
char *cgc_strchr(const char* s, int c) {

	int i;
	for(i=0; s[0] != (char) c; i++) {
		if(s[i+1] == '\0')
			return 0;
	}

	return (char *) &s[i];
}

/**
* Spans the initial part of a null-terminated string as long as s1 does 
* occur in s2.
* 
* @param s1 the string to look for in s2
* @param s2 the string to span
*
* @return The index in s2 after s1
*/
cgc_size_t cgc_strspn(const char *s1, const char *s2) {
	cgc_size_t result=0;

	for(int i=0; s1[i] != '\0' && cgc_strchr(s2, s1[i]); i++, result++);

	return result;
}

/**
* Spans the initial part of a null-terminated string as long as s1 does not 
* occur in s2.
* 
* @param s1 the string to look for in s2
* @param s2 the string to span
*
* @return The index in s2 which starts s1
*/
cgc_size_t cgc_strcspn(const char *s1, const char *s2) {
	cgc_size_t result=0;

	for(int i=0; s1[i] != '\0'; i++, result++) {
		if(cgc_strchr(s2, s1[i]))
			return result;
	}

	return result;
}

/**
* Remove sequential tokens from a null-terminated string
*
* NOTES: If string is > 0, the string is set and the first token is retuned.
*        If string is = 0, the next token of the set string is returned until NULL.
*
* 
* @param string The string to tokenize
* @param delim The delimeter that separates the tokens
*
* @return A null-terminated string containing the token
*/
char *cgc_strtok(char* string,const char *delim) {
	static char *ptr=0;
	int start, finish;

	if(string != NULL) {
		ptr = string;
	} else if( ptr == NULL) {
		return 0;
	}

	start = cgc_strspn(ptr, delim);
	string = &ptr[start];
	finish = cgc_strcspn(string, delim);
	ptr = &string[finish];

	if(ptr == string)
		return ptr=NULL;

	if(ptr[0] != '\0') {
		ptr[0] = '\0';
		ptr = &ptr[1];
	} else
		ptr = NULL;

	return string;
}


