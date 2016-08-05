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
#include <libcgc.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "shell.h"
#include "fs.h"
#include "user.h"
#include "io.h"
#include "prng.h"

extern environment ENV;

int main(void) {
	Command Cmd;
	char buf[MAX_CMD_LEN];
	int32_t i;
	uint8_t ParseResult;
	const char *rand_page = (const char *)0x4347C000;

	// init the prng
        seed_prng(*(unsigned int *)rand_page);
	
	// init the file system
	InitFilesystem();

	// zero out the command history
	bzero(ENV.CommandHistory, sizeof(ENV.CommandHistory));
	ENV.NumCommandHistory = 0;

	// log in the default 'crs' user
	Login();

	while (1) {
		PrintPrompt();

		if (ReadShellPrompt(STDIN, buf, MAX_CMD_LEN-1) == 0) {
			printf("\b\b  \b\b\n\r");
			continue;
		}
		printf("\b\b  \b\b\n\r");

		PrependCommandHistory(buf);

		ParseResult = ParseCli(buf, &Cmd);
		if (ParseResult == 0) {
			break;
		} else if (ParseResult == 1) {
			puts("Invalid input");
			continue;
		}

		// Command handler
		if (!strcmp(Cmd.argv[0], "list")) {
			HandleListFiles(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "chuser")) {
			ChUser(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "chpw")) {
			ChPw(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "exit")) {
			HandleExit(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "id")) {
			ID(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "?")) {
			HandleHelp(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "help")) {
			HandleHelp(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "newuser")) {
			NewUser(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "deluser")) {
			DelUser(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "dump")) {
			HandleDump(&Cmd);
		} else if (!strcmp(Cmd.argv[0], "print")) {
			HandlePrint(&Cmd);
		} else {
			printf("Invalid command: $s\n\r", buf);
		}

	}

	return(0);
}
