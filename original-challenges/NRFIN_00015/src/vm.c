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
#include "vm.h"
#include "stack.h"

void invalid_command() {
	int ret;

	ret = transmit_all(STDOUT, INVALID_CMD_STR, sizeof(INVALID_CMD_STR));
    if (ret != 0)
        _terminate(3);
}

int parseCmd(char* command, char* buffer) {

	int command_size; 

	command_size = strnlen(command, MAX_LINE_SIZE);

	if(strncmp(buffer, command, command_size) == 0) {
		return command_size;
	} else
		return 0;
}

int receiveProgramSize(socket) {
	char buf[1024] ={0};
	int bytes_read;
	int arg_pos;
	int size;

	bytes_read = recvline(socket, buf, sizeof(buf)-1);
	if (bytes_read <= 0)
		_terminate(4);

	arg_pos = parseCmd(PRGM_SIZE_CMD, buf);
	if (!arg_pos) {
		invalid_command();
		_terminate(5);
	}

	size = strn2int(buf+arg_pos, MAX_ARG_SIZE);

	return size;

}

void initProgram(Program **program_ptr, int socket) {

	char buf[MAX_LINE_SIZE] ={0};
	int size;
	int ret;
	int bytes_read;

	size = receiveProgramSize(socket);

	if(size <= 0) {
		return;
	}

	if(size > MAX_PROGRAM_SIZE)
		return;

	ret = allocate(sizeof(Program) + MAX_LINE_SIZE*size, 0, (void**) program_ptr);
	if (ret != 0)
		_terminate(6);

	Program *program;
	program = *program_ptr;
	program->lineNumber = -1;
	program->size = size;

	int i;
	for (i = 0; i < size; i++) {
		bytes_read = recvline(socket, buf, MAX_LINE_SIZE);
		if (bytes_read <= 0)
			_terminate(7);

		addLine(program, buf);
	}

	program->lineNumber = 0;

	return;
	
}

int isProgramFull(Program *program) {
	return program->lineNumber >= program->size - 1;
}

void addLine(Program *program, char* buf) {
	int ret;

	if(isProgramFull(program)) {
		ret = transmit_all(STDOUT, TOO_MANY_LINES_STR, sizeof(TOO_MANY_LINES_STR));
    	if (ret != 0)
        	_terminate(10);
        return;
	}

    program->lineNumber++;
	memcpy(&program->lines[program->lineNumber*MAX_LINE_SIZE], buf, MAX_LINE_SIZE);

}

void executeProgram(Program* program) {

	Stack stack;
	int arg_pos;

	initStack(&stack, program->size * 16, MAX_ARG_SIZE);
	if(stack.elements == NULL)
		return;

	program->lineNumber = 0;

	while(program->lineNumber < program->size) {
		char* line;
		
		line = &program->lines[program->lineNumber*MAX_LINE_SIZE];

		if((arg_pos = parseCmd(PUSH_CMD, line)) > 0) {
			pushElement(&stack, line+arg_pos);
			program->lineNumber++;
		}
		else if((arg_pos = parseCmd(POP_CMD, line)) > 0)	{
			char* element;
			int len;

			element = (char *) popElement(&stack);

			len = strnlen(element, MAX_ARG_SIZE);
			memset(element, 0, len);

			program->lineNumber++;
		}
		else if((arg_pos = parseCmd(ADD_CMD, line)) > 0) {
			int a, b, ret;
			char *a_str;
			char *a_element;
			char *b_element;
			int len;

			a_element = popElement(&stack);
			b_element = popElement(&stack);

			a = strn2int(a_element, MAX_ARG_SIZE);
			b = strn2int(b_element, MAX_ARG_SIZE);
			a += b;
			a_str = itoaB10(a); 

			len = strnlen(a_element, MAX_ARG_SIZE);
			memset(a_element, 0, len);

			len = strnlen(b_element, MAX_ARG_SIZE);
			memset(b_element, 0, len);

			len = strlen(a_str);
			pushElement(&stack, a_str);
			
			ret = deallocate(a_str, len); 
			if (ret != 0)
				_terminate(11);

			program->lineNumber++;
		}
		else if((arg_pos = parseCmd(PRINT_CMD, line)) > 0) {
			int ret, len;
			char *element;

			element = (char *) popElement(&stack);
			ret = transmit_all(STDOUT, element, strnlen(element, MAX_ARG_SIZE));
			if (ret != 0)
				_terminate(14);			
			ret = transmit_all(STDOUT, NEWLINE, strnlen(NEWLINE, MAX_ARG_SIZE));
			if (ret != 0)
				_terminate(15);	

			len = strnlen(element, MAX_ARG_SIZE);
			memset(element, 0, len);

			program->lineNumber++;
		}
		else if((arg_pos = parseCmd(COPY_CMD, line)) > 0) {
			int copy_num;
			int ret, i;

			copy_num = strn2int(line+arg_pos, MAX_ARG_SIZE);
			if(copy_num < 1) {
				program->lineNumber++;
				continue;
			}

			char *element;
			element = popElement(&stack);

			for(i=0; i<copy_num; i++) {
				pushElement(&stack, element);
			}

			program->lineNumber++;
		} else
			program->lineNumber++;

	}

	destroyStack(&stack);

}
