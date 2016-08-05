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
#include "screen.h"

// global shell environment
environment ENV;

void PrintPrompt(void) {
	printf("$s@CB> ", ENV.User);
}

int32_t ParseCli(char *buf, Command *pCmd) {
	char *tok;
	uint8_t FoundQuote = 0;

	if (!buf || !pCmd) {
		return(0);
	}

	pCmd->argc = 0;
	while ((tok = strtok(buf, " ")) && pCmd->argc <= MAX_ARGS) {
		buf = NULL;
		if (FoundQuote) {
			if (tok[strlen(tok)-1] == '"') {
				// found the close quote at the end of tok
				// copy this token onto the argv and move on
				tok[strlen(tok)-1] = '\0';
				if (strlen(pCmd->argv[pCmd->argc]) + strlen(tok) + 1 > MAX_ARGLEN) {
					// parse error
					return(1);
				}
				strcat(pCmd->argv[pCmd->argc], " ");
				strcat(pCmd->argv[pCmd->argc++], tok);
				FoundQuote = 0;
				continue;
			}

			if (tok[0] == '"' && tok[1] == '\0') {
				// quote is the only thing in tok, so done with this argv
				pCmd->argc++;
				FoundQuote = 0;
				continue;
			}

			if (strchr(tok, '"') == NULL) {
				// add this tok to the argv
				if (strlen(pCmd->argv[pCmd->argc]) + strlen(tok) + 1 > MAX_ARGLEN) {
					// parse error
					return(1);
				}
				strcat(pCmd->argv[pCmd->argc], " ");
				strcat(pCmd->argv[pCmd->argc], tok);
				continue;
			} else {
				// found the close quote in the middle of the tok
				// parse error
				return(1);
			}

		}
		if (tok[0] == '\"') {
			// found an open quote
			if (tok[strlen(tok)-1] == '"') {
				// found the end quote
				tok[strlen(tok)-1] = '\0';
				// copy everything between the quotes into the argv
				strncpy(pCmd->argv[pCmd->argc++], tok+1, MAX_ARGLEN);
			} else {
				// this token doesn't end with a quote, so check that there are no mid-token quotes
				if (strchr(tok+1, '"') != NULL) {
					// parse error
					return(1);
				}

				// make note that we're in a quoted argument
				FoundQuote = 1;

				// but copy what we have into the first part of the argv
				strncpy(pCmd->argv[pCmd->argc], tok+1, MAX_ARGLEN);
			}
			continue;
		}

		// no quotes, just copy to an argv
		strncpy(pCmd->argv[pCmd->argc++], tok, MAX_ARGLEN);
	}

	return(2);
}

int32_t HandleListFiles(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 1) {
		puts("Invalid arguments");
		return(0);
	}

	ListFiles();
	return(1);
}	

int32_t HandleExit(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 1) {
		puts("Invalid arguments");
		return(0);
	}

	puts("logout");

	_terminate(0);

}

int32_t HandleHelp(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc == 1) {
		puts("Available commands:");
		puts("chuser");
		puts("chpw");
		puts("exit");
		puts("id");
		puts("help");
		puts("?");
		puts("newuser");
		puts("deluser");
		puts("dump");
		puts("print");
	} else if (pCmd->argc == 2) {
		if (!strcmp(pCmd->argv[1], "chuser")) {
			puts("Usage: chuser <username>");
		} else if (!strcmp(pCmd->argv[1], "passwd")) {
			if (!strcmp(ENV.User, "root")) {
				puts("Usage: passwd <username>");
			} else {
				puts("Usage: passwd");
			}
		} else if (!strcmp(pCmd->argv[1], "exit")) {
			puts("Usage: exit");
		} else if (!strcmp(pCmd->argv[1], "id")) {
			puts("Usage: id");
		} else if (!strcmp(pCmd->argv[1], "help")) {
			puts("Usage: help <command>");
		} else if (!strcmp(pCmd->argv[1], "?")) {
			puts("Usage: ? <command>");
		} else if (!strcmp(pCmd->argv[1], "newuser")) {
			puts("Usage: newuser <username> <group>");
		} else if (!strcmp(pCmd->argv[1], "deluser")) {
			puts("Usage: deluser <username>");
		} else if (!strcmp(pCmd->argv[1], "cat")) {
			puts("Usage: dump <filename>");
		} else if (!strcmp(pCmd->argv[1], "echo")) {
			puts("Usage: print <text> [> file]");
		} else {
			printf("Unknown command: $s\n", pCmd->argv[1]);
		}
	}

	return(1);
	
}

uint8_t HandleDump(Command *pCmd) {
	FILE *stream;

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 2) {
		puts("Input error");
		puts("Usage: dump <filename>");
		return(0);
	}

	return(Dump(pCmd->argv[1]));

}	

uint8_t HandlePrint(Command *pCmd) {
	FILE *stream;
	char *RedirectFile = NULL;
	uint32_t i;

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc < 2) {
		puts("Input error");
		puts("Usage: print \"<text>\" [> file]");
		return(0);
	}

	// run through the args to see if we have a file redirect
	for (i = 2; i < pCmd->argc; i++) {
		if (pCmd->argv[i][0] == '>' && pCmd->argv[i][1] == '\0') {
			// found a file redirect...and there should only be one more arg
			if (i+1 != pCmd->argc-1)  {
				puts("Input error");
				puts("Usage: print \"<text>\" [> file]");
				return(0);
			}
			RedirectFile = pCmd->argv[i+1];
			break;
		} 
	}

	if (RedirectFile) {
		if ((stream = fopen(RedirectFile, "w", 0)) == NULL) {
			printf("Unable to open file '$s'\n\r", RedirectFile);
			return(0);
		}
		if (fwrite(pCmd->argv[1], strlen(pCmd->argv[1]), 1, stream) != strlen(pCmd->argv[1])) {
			fclose(stream);
			return(0);
		}
		fclose(stream);
	} else {
		// output to stdout
		printf("$s", pCmd->argv[1]);
		for (i = 2; i < pCmd->argc; i++) {
			printf(" $s", pCmd->argv[i]);
		}
		puts("");
	}

	return(1);

}

void PrependCommandHistory(char *buf) {
	uint8_t i;

	ENV.NumCommandHistory = 0;
#ifdef PATCHED_2
	for (i = MAX_CMD_HISTORY-1; i > 0; i--) {
#else
	for (i = MAX_CMD_HISTORY; i > 0; i--) {
#endif
		if (ENV.CommandHistory[i-1][0] != '\0') {
			strcpy(ENV.CommandHistory[i], ENV.CommandHistory[i-1]);
			if (ENV.NumCommandHistory == 0) {
				ENV.NumCommandHistory = i;
			}
		}
	}
	strcpy(ENV.CommandHistory[0], buf);
	ENV.NumCommandHistory++;
}
