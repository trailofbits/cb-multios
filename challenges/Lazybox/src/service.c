/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_stdint.h"
#include "cgc_shell.h"
#include "cgc_fs.h"
#include "cgc_user.h"
#include "cgc_io.h"
#include "cgc_prng.h"

extern environment cgc_ENV;

int main(int cgc_argc, char *cgc_argv[]) {
	Command Cmd;
	char buf[MAX_CMD_LEN];
	int32_t i;
	uint8_t ParseResult;
	const char *rand_page = (const char *)0x4347C000;

	// init the prng
        cgc_seed_prng(*(unsigned int *)rand_page);
	
	// init the file system
	cgc_InitFilesystem();

	// zero out the command history
	cgc_bzero(cgc_ENV.CommandHistory, sizeof(cgc_ENV.CommandHistory));
	cgc_ENV.NumCommandHistory = 0;

	// log in the default 'crs' user
	cgc_Login();

	while (1) {
		cgc_PrintPrompt();

		if (cgc_ReadShellPrompt(STDIN, buf, MAX_CMD_LEN-1) == 0) {
			cgc_printf("\b\b  \b\b\n\r");
			continue;
		}
		cgc_printf("\b\b  \b\b\n\r");

		cgc_PrependCommandHistory(buf);

		ParseResult = cgc_ParseCli(buf, &Cmd);
		if (ParseResult == 0) {
			break;
		} else if (ParseResult == 1) {
			cgc_puts("Invalid input");
			continue;
		}

		// Command handler
		if (!cgc_strcmp(Cmd.argv[0], "list")) {
			cgc_HandleListFiles(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "chuser")) {
			cgc_ChUser(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "chpw")) {
			cgc_ChPw(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "exit")) {
			cgc_HandleExit(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "id")) {
			cgc_ID(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "?")) {
			cgc_HandleHelp(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "help")) {
			cgc_HandleHelp(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "newuser")) {
			cgc_NewUser(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "deluser")) {
			cgc_DelUser(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "dump")) {
			cgc_HandleDump(&Cmd);
		} else if (!cgc_strcmp(Cmd.argv[0], "print")) {
			cgc_HandlePrint(&Cmd);
		} else {
			cgc_printf("Invalid command: $s\n\r", buf);
		}

	}

	return(0);
}
