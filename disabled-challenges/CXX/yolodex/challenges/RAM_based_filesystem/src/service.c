/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2014 Cromulence LLC

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
#include "cgc_fs.h"
#include "cgc_cmd.h"

char *cgc_ARGV[MAX_ARGS];
uint32_t cgc_ARGC;
extern ShellCmds cgc_cmds[];
char cgc_CWD[MAX_CMD];

int cgc_FreeArgs() {
	int i = 0;

	while (cgc_ARGV[i]) {
		cgc_deallocate(cgc_ARGV[i], cgc_strlen(cgc_ARGV[i]));
		cgc_ARGV[i] = NULL;
		i++;
	}

	return(0);
}

int cgc_ParseArgs(char *cmd) {
	char *tok;
	char *t;
	int new_len;
	int open_quote = 0;

	// start with a clean slate
	cgc_bzero(cgc_ARGV, MAX_ARGS*sizeof(char*));
	cgc_ARGC = 0;

	// look for spaces
	if ((tok = cgc_strtok(cmd, " ")) == NULL) {
		cgc_ARGC = 0;
		return(0);
	}
	cgc_ARGV[cgc_ARGC++] = cgc_strdup(tok);

	while ((tok = cgc_strtok(NULL, " ")) != NULL && cgc_ARGC < MAX_ARGS-1) {
		// handle closing quote made up of multiple " "-separated tokens
		if (open_quote && tok[cgc_strlen(tok)-1] == '"') {
			new_len = cgc_strlen(cgc_ARGV[cgc_ARGC]) + cgc_strlen(tok) + 1;
			if (cgc_allocate(new_len, 0, (void *)&t)) {
				cgc_FreeArgs();
				cgc_ARGC = 0;
				return(0);
			}
			cgc_strcpy(t, cgc_ARGV[cgc_ARGC]+1);
			cgc_strcat(t, " ");
			tok[cgc_strlen(tok)-1] = '\0';
			cgc_strcat(t, tok);
			cgc_deallocate(cgc_ARGV[cgc_ARGC], cgc_strlen(cgc_ARGV[cgc_ARGC]));
			cgc_ARGV[cgc_ARGC++] = t;
			open_quote = 0;

		// handle middle tokens for quoted string
		} else if (open_quote) {
			new_len = cgc_strlen(cgc_ARGV[cgc_ARGC]) + cgc_strlen(tok) + 2;
			if (cgc_allocate(new_len, 0, (void *)&t)) {
				cgc_FreeArgs();
				cgc_ARGC = 0;
				return(0);
			}
			cgc_strcpy(t, cgc_ARGV[cgc_ARGC]);
			cgc_strcat(t, " ");
			cgc_strcat(t, tok);
			cgc_deallocate(cgc_ARGV[cgc_ARGC], cgc_strlen(cgc_ARGV[cgc_ARGC]));
			cgc_ARGV[cgc_ARGC] = t;

		// handle token delimited by quotes
		} else if (tok[0] == '"' & tok[cgc_strlen(tok)-1] == '"') {
			tok[cgc_strlen(tok)-1] = '\0';
			cgc_ARGV[cgc_ARGC++] = cgc_strdup(tok+1);

		// handle starting quote 
		} else if (tok[0] == '"') {
			open_quote = 1;
			cgc_ARGV[cgc_ARGC] = cgc_strdup(tok);

		// not a quoted token
		} else {
			cgc_ARGV[cgc_ARGC++] = cgc_strdup(tok);
		}
	}

	// found a starting, but no ending quote, abort processing
	if (open_quote) {
		cgc_puts("missing quote");
		cgc_FreeArgs();
		cgc_ARGC = 0;
		return(0);
	}

	// too many args, abort processing
	if (cgc_ARGC == MAX_ARGS-1) {
		cgc_puts("too many args");
		cgc_FreeArgs();
		cgc_ARGC = 0;
		return(0);
	}

	return(cgc_ARGC);

}

int main(int cgc_argc, char *cgc_argv[]) {
	char cmd[MAX_CMD];
	ShellCmds *c;

	cgc_bzero(cgc_CWD, MAX_CMD);
	cgc_strcpy(cgc_CWD, "/");

	if (cgc_InitFS(512*1024)) {
		cgc_puts("Failed to initialize the RAM file system\n");
		return(-1);
	}

	cgc_puts("Welcome to the cgcfs shell!");
	cgc_puts("Type help for a list of available commands.");
	cgc_printf("% ");
	cgc_bzero(cmd, MAX_CMD);
	while (cgc_readUntil(cmd, MAX_CMD-1, '\n') != -1) {
		cgc_ParseArgs(cmd);

		// parse failure
		if (cgc_ARGC == 0) {
			cgc_FreeArgs();
			cgc_bzero(cmd, MAX_CMD);
			cgc_printf("% ");
			continue;
		}

		// find the command being requested
		if (cgc_ARGV[0] != NULL) {
			c = cgc_cmds;
			while (c->command != NULL) {
				if (!cgc_strcmp(c->command, cgc_ARGV[0])) {
					// run the command
					c->handler();

					break;
				}
				c++;
			}
		}
		if (c == NULL) {
			cgc_puts("Invalid command");
		}
		if (c->command == NULL) {
			cgc_puts("Invalid command");
		}

		cgc_FreeArgs();
		cgc_bzero(cmd, MAX_CMD);
		cgc_printf("% ");
	}

	if (cgc_DestroyFS()) {
		cgc_puts("Failed to destroy the RAM file system\n");
		return(-1); 
	}

	return(0);

}
