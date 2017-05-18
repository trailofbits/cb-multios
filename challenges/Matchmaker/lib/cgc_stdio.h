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

#ifndef STDIO_H_
#define STDIO_H_

#include "libcgc.h"

#include "cgc_stdlib.h"

typedef struct FILE FILE;
extern FILE *cgc_stdin, *cgc_stdout, *cgc_stderr;

/** Is this file in cgc_read or cgc_write mode, mutually exclusive */
enum mode {
    /** Read mode */
    READ,
    /** Write mode */
    WRITE
};

/**
 * Read exactly size bytes from fd into ptr.
 *
 * @param fd The file descriptor to cgc_read from
 * @param ptr The output buffer
 * @param size The size to cgc_read
 * @return size on success, else EXIT_FAILURE
 */
cgc_ssize_t cgc_read_all(int fd, void *ptr, cgc_size_t size);

/**
 * Read at most size bytes from fd into ptr, stopping on delim.
 *
 * @param fd The file descriptor to cgc_read from
 * @param ptr The output buffer
 * @param delim The byte to stop on
 * @param size The size to cgc_read
 * @return size on success, else EXIT_FAILURE
 */
cgc_ssize_t cgc_read_until(int fd, void *ptr, unsigned char delim, cgc_size_t size);

/**
 * Write exactly size bytes from ptr to fd.
 *
 * @param fd The file descriptor to cgc_write to
 * @param ptr The input buffer
 * @param size The size to cgc_write
 * @return size on success, else EXIT_FAILURE
 */
cgc_ssize_t cgc_write_all(int fd, const void *ptr, cgc_size_t size);

/**
 * Open a FILE given a file descriptor and a mode.
 *
 * @param fd The file descriptor to open
 * @param mode The mode of the FILE
 * @return A pointer to a FILE or NULL on failure
 */
FILE *cgc_fdopen(int fd, enum mode mode);

/**
 * Close a FILE opened with fdopen.
 *
 * @param stream The FILE to close
 */
void cgc_fclose(FILE *stream);

/**
 * Flush buffer from FILE pointer to its fd.
 *
 * @param stream The FILE to flush
 * @return EXIT_SUCCESS on success, else EXIT_FAILURE
 */
int cgc_fflush(FILE *stream);

/**
 * Read exactly size bytes from FILE pointer into ptr, buffered.
 *
 * @param ptr The output buffer
 * @param size The size to cgc_read
 * @param stream The FILE pointer to cgc_read from
 * @return size on success, else EXIT_FAILURE
 */
cgc_ssize_t cgc_fread(void *ptr, cgc_size_t size, FILE *stream);

/**
 * Read at most size bytes from FILE pointer into ptr, stopping on delim, buffered.
 *
 * @param ptr The output buffer
 * @param delim The byte to stop on
 * @param size The size to cgc_read
 * @param stream The FILE pointer to cgc_read from
 * @return size on success, else EXIT_FAILURE
 */
cgc_ssize_t cgc_fread_until(void *ptr, unsigned char delim, cgc_size_t size, FILE *stream);

/**
 * Write size bytes from ptr into FILE pointer, buffered.
 *
 * @param ptr The input buffer
 * @param size The size to cgc_write
 * @param stream The FILE pointer to cgc_write to
 * @return size on success, else EXIT_FAILURE
 */
cgc_ssize_t cgc_fwrite(const void *ptr, cgc_size_t size, FILE *stream);

/**
 * Get a character from FILE pointer, buffered.
 *
 * @param stream The FILE pointer to cgc_read from
 * @return The value of the character cgc_read, or EXIT_FAILURE
 */
int cgc_fgetc(FILE *stream);

/**
 * Write a character to FILE pointer, buffered.
 *
 * @param stream The FILE pointer to cgc_write to
 * @return EXIT_SUCCESS on success, else EXIT_FAILURE
 */
int cgc_fputc(int character, FILE *stream);

/**
 * Get a character from cgc_stdin, buffered.
 *
 * @return The value of the character cgc_read, or EXIT_FAILURE
 */
#define getc() fgetc(cgc_stdin)

/**
 * Write a character to cgc_stdout, buffered.
 *
 * @return EXIT_SUCCESS on success, else EXIT_FAILURE
 */
#define putc(character) fputc(character, cgc_stdout)

/**
 * Print a formatted string to cgc_stdout, taking parameters from a va_list,
 *      buffered.
 *
 * @param format The format string to use
 * @param arg The va_list to retrieve values from
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_vprintf(const char *format, va_list arg);

/**
 * Print a formatted string to a FILE pointer, taking parameters from a va_list,
 *      buffered.
 *
 * @param stream The FILE pointer to cgc_write to
 * @param format The format string to use
 * @param arg The va_list to retrieve values from
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_vfprintf(FILE *stream, const char *format, va_list arg);

/**
 * Write a formatted string to a buffer, taking parameters from a va_list.
 *
 * @param s The buffer to cgc_write to
 * @param format The format string to use
 * @param arg The va_list to retrieve values from
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_vsprintf(char *s, const char *format, va_list arg);

/**
 * Write a formatted string to a buffer, writing at most num bytes, taking
 *      parameters from a va_list.
 *
 * @param s The buffer to cgc_write to
 * @param num The maximum number of bytes to cgc_write
 * @param format The format string to use
 * @param arg The va_list to retrieve values from
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_vsnprintf(char *s, cgc_size_t num, const char *format, va_list arg);

/**
 * Read formatted input from cgc_stdin, taking parameters from a va_list,
 *      buffered.
 *
 * UNIMPLEMENTED
 *
 * @param format The format string to use
 * @param arg The va_list to cgc_write values to
 * @return The number of bytes cgc_read on success, else EXIT_FAILURE
 */
int vscanf(const char *format, va_list arg);

/**
 * Read formatted input from a FILE pointer, taking parameters from a va_list,
 *      buffered.
 *
 * UNIMPLEMENTED
 *
 * @param stream The file pointer to cgc_read from
 * @param format The format string to use
 * @param arg The va_list to cgc_write values to
 * @return The number of bytes cgc_read on success, else EXIT_FAILURE
 */
int vfscanf(FILE *stream, const char *format, va_list arg);

/**
 * Read formatted input from a string, taking parameters from a va_list.
 *
 * UNIMPLEMENTED
 *
 * @param s The string to cgc_read from
 * @param format The format string to use
 * @param arg The va_list to cgc_write values to
 * @return The number of bytes cgc_read on success, else EXIT_FAILURE
 */
int vsscanf(char *s, const char *format, va_list arg);

/**
 * Print a formatted string to cgc_stdout, buffered.
 *
 * @param format The format string to use
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_printf(const char *format, ...);

/**
 * Print a formatted string to a FILE pointer, buffered.
 *
 * @param stream The FILE pointer to cgc_write to
 * @param format The format string to use
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_fprintf(FILE *stream, const char *format, ...);

/**
 * Write a formatted string to a buffer.
 *
 * @param s The buffer to cgc_write to
 * @param format The format string to use
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_sprintf(char *s, const char *format, ...);

/**
 * Write a formatted string to a buffer, writing at most num bytes.
 *
 * @param s The buffer to cgc_write to
 * @param num The maximum number of bytes to cgc_write
 * @param format The format string to use
 * @return The number of bytes written on success, else EXIT_FAILURE
 */
int cgc_snprintf(char *s, cgc_size_t num, const char *format, ...);

/**
 * Read formatted input from cgc_stdin, buffered.
 *
 * UNIMPLEMENTED
 *
 * @param format The format string to use
 * @return The number of bytes cgc_read on success, else EXIT_FAILURE
 */
int scanf(const char *format, ...);

/**
 * Read formatted input from a FILE pointer, buffered.
 *
 * UNIMPLEMENTED
 *
 * @param stream The FILE pointer to cgc_read from
 * @param format The format string to use
 * @return The number of bytes cgc_read on success, else EXIT_FAILURE
 */
int fscanf(const char *format, ...);

/**
 * Read formatted input from a string.
 *
 * UNIMPLEMENTED
 *
 * @param s The string to cgc_read from
 * @param format The format string to use
 * @return The number of bytes cgc_read on success, else EXIT_FAILURE
 */
int sscanf(char *s, const char *format, ...);

#endif /* STDIO_H_ */

