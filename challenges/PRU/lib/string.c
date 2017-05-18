/*

Copyright (c) 2015 Cromulence LLC

Authors: Cromulence <cgc@cromulence.com>

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
#include "cgc_string.h"
#include "cgc_stdint.h"

cgc_size_t cgc_strlen( const char *str )
{
	cgc_size_t len = 0;
	while ( *str++ != '\0' )
		len++;

	return len;
}

void cgc_bzero(void *s, cgc_size_t n) {
        while (n) {
                ((char *)s)[--n] = '\0';
        }
        ((char *)s)[n] = '\0';
}

void *cgc_memset( void *ptr, int value, cgc_size_t num )
{
	void *ptr_temp = ptr;
	uint8_t set_value_byte = (uint8_t)value;
	uint32_t set_value_dword = (set_value_byte << 24) | (set_value_byte << 16) | (set_value_byte << 8) | set_value_byte;

	while ( num >= 4 )
	{
		*((uint32_t*)ptr++) = set_value_dword;	
		num-=4;	
	}

	while ( num > 0 )
	{
		*((uint8_t*)ptr++) = set_value_byte;	
		num--;
	}

	return (ptr_temp);
}

char *cgc_strchr(char *s, int c) {
	uint32_t i;

	if (!s) {
		return(NULL);
	}
	for (i = 0; i < cgc_strlen(s); i++) {
		if (s[i] == c) {
			return(s+i);
		}
	}

	return(NULL);

}

char *cgc_StrtokNext = NULL;
char *cgc_strtok(char *str, char *sep) {
	uint32_t i, j;
	uint32_t str_len;
	char *tok;

	if (!sep) {
		return(NULL);
	}

	if (!str) {
		if (!cgc_StrtokNext) {
			return(NULL);
		} else {
			str = cgc_StrtokNext;
		}
	}

	// deal with any leading sep chars
	while (cgc_strchr(sep, *str) && *str != '\0') {
		str++;
	}
	if (*str == '\0') {
		cgc_StrtokNext = NULL;
		return(NULL);
	}

	str_len = cgc_strlen(str);
	for (i = 0; i < str_len; i++) {
		if (cgc_strchr(sep, str[i])) {
			// found a sep character
			str[i] = '\0';
			// see if there are any subsequent tokens
			for (j = i+1; j < str_len; j++) {
				if (cgc_strchr(sep, str[j])) {
					// found one
					str[j] = '\0';
				} else {
					// no more tokens
					cgc_StrtokNext = str+j;
					return(str);
				}
			}
			if (j == str_len) {
				cgc_StrtokNext = NULL;
			}
			return(str);
		}
	}

	// made it to the end of the string without any new tokens
	cgc_StrtokNext = NULL;
	return(str);
}
