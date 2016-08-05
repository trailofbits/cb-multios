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

#ifndef STRING_H_
#define STRING_H_

#include <libcgc.h>

/**
 * Copies num bytes from source to destination.
 *
 * @param destination The destination pointer
 * @param source The source pointer
 * @param num The number of bytes to copy
 * @return The destination pointer
 */
void *memcpy(void *destination, const void *source, size_t num);

/**
 * Moves num bytes from source to destination, allowing buffers to overlap.
 *
 * @param destination The destination pointer
 * @param source The source pointer
 * @param num The number of bytes to move
 * @return The destination pointer
 */
void *memmove(void *destination, const void *source, size_t num);

/**
 * Sets num bytes in ptr to value.
 *
 * @param ptr The destination pointer
 * @param value The value to set, interpreted as an unsigned char
 * @param num The number of bytes to set
 * @return The destination pointer
 */
void *memset(void *ptr, int value, size_t num);

/**
 * Returns the length of str.
 *
 * @param str The string to measure
 * @return The length of str
 */
size_t strlen(const char *str);

/**
 * Returns the length of str, examining at most num bytes.
 *
 * @param str The string to measure
 * @param num The number of bytes to examine
 * @return The length of str, or num if longer than num
 */
size_t strnlen(const char *str, size_t num);

/**
 * Copies a string from source to destination.
 *
 * @param destination The destination string
 * @param source The source string
 * @return destination
 */
char *strcpy(char *destination, const char *source);

/**
 * Copies at most num bytes of a string from source to destination.
 *
 * Not guaranteed to NULL terminate, will pad with NULL bytes if source has
 * fewer than num bytes
 *
 * @param destination The destination string
 * @param source The source string
 * @param num The maximum number of bytes to copy
 * @return destination
 */
char *strncpy(char *destination, const char *source, size_t num);

/**
 * Appends a string from source to destination.
 *
 * @param destination The destination string
 * @param source The source string
 * @return destination
 */
char *strcat(char *destination, const char *source);

/**
 * Appends at most num bytes from source to destination.
 *
 * @param destination The destination string
 * @param source The source string
 * @param num The maximum number of bytes to append
 * @return destination
 */
char *strncat(char *destination, const char *source, size_t num);

/**
 * Compares num bytes between ptr1 and ptr2.
 *
 * @param ptr1 The first buffer to compare
 * @param ptr2 The second buffer to compare
 * @param num The maximum number of bytes to compare
 * @return 0 if ptr1 == ptr2, <0 if ptr1 < ptr2, >0 if ptr1 > ptr2
 */
int memcmp(const void *ptr1, const void *ptr2, size_t num);

/**
 * Compares str1 to str2.
 *
 * @param str1 The first string to compare
 * @param str2 The second string to compare
 * @return 0 if str1 == str2, <0 if str1 < str2, >0 if str1 > str2
 */
int strcmp(const char *str1, const char *str2);

/**
 * Compares at most num bytes between str1 and str2.
 *
 * @param str1 The first string to compare
 * @param str2 The second string to compare
 * @param num The number of bytes to compare
 * @return 0 if str1 == str2, <0 if str1 < str2, >0 if str1 > str2
 */
int strncmp(const char *str1, const char *str2, size_t num);

/**
 * Find the first instance of value in the first num bytes of ptr.
 *
 * @param ptr The buffer to search
 * @param value The byte to search for, interpretted as an unsigned char
 * @param num The number of bytes to search
 * @return A pointer to the first instance of value in ptr, or NULL if not found
 */
void *memchr(void *ptr, int value, size_t num);

/**
 * Find the first instance of character in str.
 *
 * @param str The string to search
 * @param character The character to search for, interpretted as a char
 * @return A pointer to the first instance of character in str, or NULL if not
 *      found
 */
char *strchr(char *str, int character);

/**
 * Find the first instance of any of the characters in str2 in str1.
 *
 * @param str1 The string to search
 * @param str2 A string containing the characters to search for
 * @return A pointer to the first instance in str1, or NULL if not found
 */
char *strpbrk(char *str1, const char *str2);

/**
 * Find the last instance of character in str.
 *
 * @param str The string to search
 * @param character The character to search for, interpretted as a char
 * @return A pointer to the first instance of character in str, or NULL if not
 *      found
 */
char *strrchr(char *str, int character);

/**
 * Find the last instance of substring str2 in str1.
 *
 * @param str1 The string to search
 * @param str2 The substring to search for
 * @return A pointer to the first instance of str2 in str1, or NULL if not found
 */
char *strstr(char *str1, const char *str2);

/**
 * Return the number of characters in str1 before any of the characters in str2
 * occur.
 *
 * @param str1 The string to search
 * @param str2 A string containing the characters to search for
 * @return The number of characters in str1 before any of the characters in str2
 *      occur, or strlen(str1) if none found
 */
size_t strcspn(const char *str1, const char *str2);

/**
 * Return the number of characters at the start of str1 that consist of only
 * characters found in str2.
 *
 * @param str1 The string to search
 * @param str2 A string containing the characters to search for
 * @return The number of characters at the start of str1 that consist of only
 *      characters found in str2
 */
size_t strspn(const char *str1, const char *str2);

/**
 * Split a string into tokens separated by the characters in delimiter.
 *
 * Begin tokenizing a string by passing it as the first parameter, then call
 * with NULL as the first parameter until strtok returns NULL.
 *
 * @param str The string to search, or NULL to continue previous search
 * @param delimeters A string containing the delimiters to split on
 * @return Tokens of str separated by characters in delimiter, or NULL if no
 *      more tokens available.
 */
char *strtok(char *str, const char *delimiters);

#endif /* STRING_H_ */

