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
#include "cgc_screen.h"

// global shell environment
environment cgc_ENV;

void cgc_PrintPrompt(void) {
	cgc_printf("$s@CB> ", cgc_ENV.User);
}

int32_t cgc_ParseCli(char *buf, Command *pCmd) {
	char *tok;
	uint8_t FoundQuote = 0;

	if (!buf || !pCmd) {
		return(0);
	}

	pCmd->argc = 0;
	while ((tok = cgc_strtok(buf, " ")) && pCmd->argc <= MAX_ARGS) {
		buf = NULL;
		if (FoundQuote) {
			if (tok[cgc_strlen(tok)-1] == '"') {
				// found the close quote at the end of tok
				// copy this token onto the argv and move on
				tok[cgc_strlen(tok)-1] = '\0';
				if (cgc_strlen(pCmd->argv[pCmd->argc]) + cgc_strlen(tok) + 1 > MAX_ARGLEN) {
					// parse error
					return(1);
				}
				cgc_strcat(pCmd->argv[pCmd->argc], " ");
				cgc_strcat(pCmd->argv[pCmd->argc++], tok);
				FoundQuote = 0;
				continue;
			}

			if (tok[0] == '"' && tok[1] == '\0') {
				// quote is the only thing in tok, so done with this argv
				pCmd->argc++;
				FoundQuote = 0;
				continue;
			}

			if (cgc_strchr(tok, '"') == NULL) {
				// add this tok to the argv
				if (cgc_strlen(pCmd->argv[pCmd->argc]) + cgc_strlen(tok) + 1 > MAX_ARGLEN) {
					// parse error
					return(1);
				}
				cgc_strcat(pCmd->argv[pCmd->argc], " ");
				cgc_strcat(pCmd->argv[pCmd->argc], tok);
				continue;
			} else {
				// found the close quote in the middle of the tok
				// parse error
				return(1);
			}

		}
		if (tok[0] == '\"') {
			// found an open quote
			if (tok[cgc_strlen(tok)-1] == '"') {
				// found the end quote
				tok[cgc_strlen(tok)-1] = '\0';
				// copy everything between the quotes into the argv
				cgc_strncpy(pCmd->argv[pCmd->argc++], tok+1, MAX_ARGLEN);
			} else {
				// this token doesn't end with a quote, so check that there are no mid-token quotes
				if (cgc_strchr(tok+1, '"') != NULL) {
					// parse error
					return(1);
				}

				// make note that we're in a quoted argument
				FoundQuote = 1;

				// but copy what we have into the first part of the argv
				cgc_strncpy(pCmd->argv[pCmd->argc], tok+1, MAX_ARGLEN);
			}
			continue;
		}

		// no quotes, just copy to an argv
		cgc_strncpy(pCmd->argv[pCmd->argc++], tok, MAX_ARGLEN);
	}

	return(2);
}

int32_t cgc_HandleListFiles(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 1) {
		cgc_puts("Invalid arguments");
		return(0);
	}

	cgc_ListFiles();
	return(1);
}	

int32_t cgc_HandleExit(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 1) {
		cgc_puts("Invalid arguments");
		return(0);
	}

	cgc_puts("logout");

	cgc__terminate(0);

}

int32_t cgc_HandleHelp(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc == 1) {
		cgc_puts("Available commands:");
		cgc_puts("chuser");
		cgc_puts("chpw");
		cgc_puts("exit");
		cgc_puts("id");
		cgc_puts("help");
		cgc_puts("?");
		cgc_puts("newuser");
		cgc_puts("deluser");
		cgc_puts("dump");
		cgc_puts("print");
	} else if (pCmd->argc == 2) {
		if (!cgc_strcmp(pCmd->argv[1], "chuser")) {
			cgc_puts("Usage: chuser <username>");
		} else if (!cgc_strcmp(pCmd->argv[1], "passwd")) {
			if (!cgc_strcmp(cgc_ENV.User, "root")) {
				cgc_puts("Usage: passwd <username>");
			} else {
				cgc_puts("Usage: passwd");
			}
		} else if (!cgc_strcmp(pCmd->argv[1], "exit")) {
			cgc_puts("Usage: exit");
		} else if (!cgc_strcmp(pCmd->argv[1], "id")) {
			cgc_puts("Usage: id");
		} else if (!cgc_strcmp(pCmd->argv[1], "help")) {
			cgc_puts("Usage: help <command>");
		} else if (!cgc_strcmp(pCmd->argv[1], "?")) {
			cgc_puts("Usage: ? <command>");
		} else if (!cgc_strcmp(pCmd->argv[1], "newuser")) {
			cgc_puts("Usage: newuser <username> <group>");
		} else if (!cgc_strcmp(pCmd->argv[1], "deluser")) {
			cgc_puts("Usage: deluser <username>");
		} else if (!cgc_strcmp(pCmd->argv[1], "cat")) {
			cgc_puts("Usage: dump <filename>");
		} else if (!cgc_strcmp(pCmd->argv[1], "echo")) {
			cgc_puts("Usage: print <text> [> file]");
		} else {
			cgc_printf("Unknown command: $s\n", pCmd->argv[1]);
		}
	}

	return(1);
	
}

uint8_t cgc_HandleDump(Command *pCmd) {
	FILE *stream;

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 2) {
		cgc_puts("Input error");
		cgc_puts("Usage: dump <filename>");
		return(0);
	}

	return(cgc_Dump(pCmd->argv[1]));

}	

uint8_t cgc_HandlePrint(Command *pCmd) {
	FILE *stream;
	char *RedirectFile = NULL;
	uint32_t i;

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc < 2) {
		cgc_puts("Input error");
		cgc_puts("Usage: print \"<text>\" [> file]");
		return(0);
	}

	// run through the args to see if we have a file redirect
	for (i = 2; i < pCmd->argc; i++) {
		if (pCmd->argv[i][0] == '>' && pCmd->argv[i][1] == '\0') {
			// found a file redirect...and there should only be one more arg
			if (i+1 != pCmd->argc-1)  {
				cgc_puts("Input error");
				cgc_puts("Usage: print \"<text>\" [> file]");
				return(0);
			}
			RedirectFile = pCmd->argv[i+1];
			break;
		} 
	}

	if (RedirectFile) {
		if ((stream = cgc_fopen(RedirectFile, "w", 0)) == NULL) {
			cgc_printf("Unable to open file '$s'\n\r", RedirectFile);
			return(0);
		}
		if (cgc_fwrite(pCmd->argv[1], cgc_strlen(pCmd->argv[1]), 1, stream) != cgc_strlen(pCmd->argv[1])) {
			cgc_fclose(stream);
			return(0);
		}
		cgc_fclose(stream);
	} else {
		// output to cgc_stdout
		cgc_printf("$s", pCmd->argv[1]);
		for (i = 2; i < pCmd->argc; i++) {
			cgc_printf(" $s", pCmd->argv[i]);
		}
		cgc_puts("");
	}

	return(1);

}

void cgc_PrependCommandHistory(char *buf) {
	uint8_t i;

	cgc_ENV.NumCommandHistory = 0;
#ifdef PATCHED_2
	for (i = MAX_CMD_HISTORY-1; i > 0; i--) {
#else
	for (i = MAX_CMD_HISTORY; i > 0; i--) {
#endif
		if (cgc_ENV.CommandHistory[i-1][0] != '\0') {
			cgc_strcpy(cgc_ENV.CommandHistory[i], cgc_ENV.CommandHistory[i-1]);
			if (cgc_ENV.NumCommandHistory == 0) {
				cgc_ENV.NumCommandHistory = i;
			}
		}
	}
	cgc_strcpy(cgc_ENV.CommandHistory[0], buf);
	cgc_ENV.NumCommandHistory++;
}
