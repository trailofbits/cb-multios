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
#include "service.h"

int main(void) {
	Stack programStack ={-1, 0, 0, NULL};

	while(1) {
		char buf[1024] ={0};
		int bytes_read =0;
		int arg_pos =0;

		bytes_read = recvline(STDIN, buf, sizeof(buf)-1);
		if (bytes_read <= 0)
			_terminate(1);

		if(programStack.numElements <= 0)
				initStack(&programStack, MAX_PROGRAM_STACK_SIZE, sizeof(Program *));

		if((arg_pos = parseCmd(NEW_PROGRAM_CMD_STR, buf))  > 0) {
			Program* program = NULL;

			initProgram(&program, STDIN);
			if(program != NULL)
				pushElement(&programStack, &program);
		} else if((arg_pos = parseCmd(EXECUTE_PROGRAM_CMD_STR, buf))  > 0) {
			int program_num;
			int ret;

			program_num = strn2int(buf+arg_pos, 10);
#ifdef PATCHED
		if(program_num > programStack.top || program_num < 0) {
#else		
			if(program_num > programStack.top) {
#endif
				ret = transmit_all(STDOUT, INVALID_PROGRAM_STR, sizeof(TOO_MANY_LINES_STR));
				if (ret != 0)
    				_terminate(13);
    		} else {

				Program **program_ptr;
				program_ptr = programStack.elements+(program_num*sizeof(Program *));
				executeProgram(*program_ptr);
			}
		}
	}

}