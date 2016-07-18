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

#ifndef EDITOR_H_
#define EDITOR_H_

#include "list.h"

/** Maximum line count we will hold. */
#define MAX_LINE_COUNT 256
/** Maximum size per line in characters. */
#define MAX_LINE_SIZE 256
/** Maximum command size. */
#define MAX_COMMAND_SIZE 256

/** Special mark indicating the last addressed command. */
#define DOT_MARK -27
/** Special mark indicating the end of the file. */
#define DOLLAR_MARK -28

/** A command to be run by the editor. */
struct command {
    char command;           /**< The command's letter */
    int start;              /**< The start of the operating region */
    int end;                /**< The end of the operating region */
    size_t size;            /**< The size of the command's data */
    char buf[0];            /**< The command's data */
} __attribute__((packed));

/** Holds the results of a command when output is produced. */
struct result {
    int result;             /**< The integer return code from the command */
    size_t size;            /**< The size of the output */
    unsigned int csum;      /**< A checksum, set by the caller */
    char buf[0];            /**< The output of the command */
} __attribute__((packed));

/**
 * Run a command specified by the command structure and return either an integer
 * return code or a result structure containing output. Result is allocated on
 * the heap and it is the caller's responsibility to free.
 *
 * @param command The command to execute
 * @param result A pointer to hold the allocated result
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int run_command(struct command *command, struct result **result);

#endif /* EDITOR_H_ */

