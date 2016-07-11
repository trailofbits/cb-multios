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
#include "stack.h"

#define PUSH_CMD "push"
#define POP_CMD "pop"
#define ADD_CMD "add"
#define PRINT_CMD "print"
#define COPY_CMD "copy"
#define PRGM_SIZE_CMD "size"
#define INVALID_CMD_STR "Invalid command!\n"
#define MAX_PROGRAM_SIZE 9999
#define MAX_LINE_SIZE 16
#define MAX_ARG_SIZE 8
#define TOO_MANY_LINES_STR "Too many lines in program!\n"
#define INVALID_ADDRESS_STR "Invalid address\n"
#define NEWLINE "\n"

typedef char ProgramLine[8];

typedef struct {
	long long size;
	int lineNumber;
	ProgramLine lines;
} Program;

void initProgram(Program **program, int socket);
void addLine(Program *program, ProgramLine line);
int isProgramFull(Program *program);
void executeProgram(Program *program);
int parseCmd(char* command, char* buffer);


