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
#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "fs.h"
#include "cmd.h"

ShellCmds cmds[] = {
	{ "show",       LsHandler,     "List files in a directory" },
	{ "dump",       CatHandler,    "Dump the contents of a file" },
	{ "delete",     RmHandler,     "Delete a file" },
	{ "mkfolder",   MkdirHandler,  "Make a new directory" },
	{ "delfolder",  RmdirHandler,  "Delete a directory" },
	{ "bye",        ExitHandler,   "Exit the program" },
	{ "echo",       EchoHandler,   "Echo a string to the screen or into a file" },
	{ "fsinfo",     DfHandler,     "Provides usage information about filesystem" },
	{ "help",       HelpHandler,   "Help listing" },
	{ "?",          HelpHandler,   "Help listing" },
	{ NULL,		NULL,		NULL},
};

extern char *ARGV[];
extern uint32_t ARGC;
extern char CWD[];

/*
   read input until the specified delim char is seen or 
   we reach the max length
 */
int readUntil(char *buf, int max, char delim) {
	unsigned char c[1];
	size_t size;
	uint32_t i = 0;

	while (i < max) {
		if (receive(STDIN, c, 1, &size) != 0) {
			return(-1);
		}
		if (size != 1) {
			return(-1);
		}
		if (c[0] == delim) {
			break;
		}
		*buf++ = c[0];
		i++;
	}
	*buf++ = '\0';
	return(i);
}

/*
   Bye command
 */
int ExitHandler() {

	puts("bye");
	_terminate(0);

}

/* 
   mkfolder command 
 */
int MkdirHandler() {
	char pathname[MAX_CMD];

	if (ARGC != 2) {
		puts("usage: mkfolder <directory>");
		return(0);
	}

	if (ARGV[1][0] == '/') {
		// we have a full path
		return(mkdir(ARGV[1]));
	} else {
		// we need to prepend the CWD
		bzero(pathname, MAX_CMD);
		if ((strlen(CWD)+strlen(ARGV[1]) + 1) > MAX_CMD-1) {
			puts("command too long");
			return(0);
		}
		strcpy(pathname, CWD);
		strcat(pathname, ARGV[1]);
		return(mkdir(pathname));
	}

	return(0);
}

/*
   delfolder command
 */ 
int RmdirHandler() {
	char pathname[MAX_CMD];

	if (ARGC != 2) {
		puts("usage: delfolder <directory>");
		return(0);
	}

	if (ARGV[1][0] == '/') {
		// we have a full path
		return(rmdir(ARGV[1]));
	} else {
		// we need to prepend the CWD
		bzero(pathname, MAX_CMD);
		if ((strlen(CWD)+strlen(ARGV[1]) + 1) > MAX_CMD-1) {
			puts("command too long");
			return(0);
		}
		strcpy(pathname, CWD);
		strcat(pathname, ARGV[1]);
		return(rmdir(pathname));
	}

	return(0);
}

/* 
   show command
 */
int LsHandler() {
	char pathname[MAX_CMD];

	if (ARGC == 1) {
		// no path given, assume CWD
		return(ls(CWD));
	}
	if (ARGC != 2) {
		puts("usage: show <directory>");
		return(0);
	}

	if (ARGV[1][0] == '/') {
		// we have a full path
		return(ls(ARGV[1]));
	} else {
		// we need to prepend the CWD
		bzero(pathname, MAX_CMD);
		if ((strlen(CWD)+strlen(ARGV[1]) + 1) > MAX_CMD-1) {
			puts("command too long");
			return(0);
		}
		strcpy(pathname, CWD);
		strcat(pathname, ARGV[1]);
		return(ls(pathname));
	}

	return(0);

}

/* 
   delete command
 */
int RmHandler() {
	char pathname[MAX_CMD];

	if (ARGC != 2) {
		puts("usage: delete <file>");
		return(0);
	}

	if (ARGV[1][0] == '/') {
		// no path given, assume CWD
		return(unlink(ARGV[1]));
	} else {
		// we need to prepend the CWD
		bzero(pathname, MAX_CMD);
		if ((strlen(CWD)+strlen(ARGV[1]) + 1) > MAX_CMD-1) {
			puts("command too long");
			return(0);
		}
		strcpy(pathname, CWD);
		strcat(pathname, ARGV[1]);
		return(unlink(pathname));
	}

	return(0);

}

/* 
   echo command
 */
int EchoHandler() {
	char pathname[MAX_CMD];
	char outstr[MAX_CMD];
	FILE *out;
	int len;

	if (ARGC < 2 || ARGC == 3) {
		puts("usage: echo <text> [>|>>] [file]");
		return(0);
	}

	if (ARGC == 2) {
		// handle case of 'echo <text>'
		bzero(outstr, MAX_CMD);
		strncpy(outstr, ARGV[1], MAX_CMD-1);
		if ((len = Unescape(outstr)) == -1) {
			puts("unable to write to file");
			return(-1);
		}
		write(outstr, len);
		return(0);
	}

	if (ARGC == 4) {
		// redirecting to a file
		bzero(pathname, MAX_CMD);
		if (ARGV[3][0] == '/') {
			if (strlen(ARGV[3]) > MAX_CMD-1) {
				puts("invalid file name");
				return(-1);
			}
			strcpy(pathname, ARGV[3]);
		} else {
			if ((strlen(CWD)+strlen(ARGV[3]) + 1) > MAX_CMD-1) {
				puts("command too long");
				return(0);
			}
			strcpy(pathname, CWD);
			strcat(pathname, ARGV[3]);
		}
			
		if (!strcmp(ARGV[2], ">")) {
			// write to file
			if ((out = fopen(pathname, "w")) == NULL) {
				puts("unable to write to file");
				return(-1);
			}
			bzero(outstr, MAX_CMD);
			strncpy(outstr, ARGV[1], MAX_CMD-1);
			if ((len = Unescape(outstr)) == -1) {
				puts("unable to write to file");
				fclose(out);
				return(-1);
			}
			fwrite(outstr, len, 1, out);
			fclose(out);
		} else if (!strcmp(ARGV[2], ">>")) {
			// append to file
			if ((out = fopen(pathname, "a")) == NULL) {
				puts("unable to write to file");
				return(-1);
			}
			bzero(outstr, MAX_CMD);
			strncpy(outstr, ARGV[1], MAX_CMD-1);
			if ((len = Unescape(outstr)) == -1) {
				fclose(out);
				puts("unable to write to file");
				return(-1);
			}
			fwrite(outstr, len, 1, out);
			fclose(out);
		} else {
			puts("usage: echo <text> [>|>>] [file]");
			return(0);
		}
	}

	return(0);

}

/*
   show command
 */
int CatHandler() {
	char pathname[MAX_CMD];

	if (ARGC != 2) {
		puts("usage: dump <file>");
		return(0);
	}

	if (ARGV[1][0] == '/') {
		// no path given, assume CWD
		return(ReadFile(ARGV[1]));
	} else {
		// we need to prepend the CWD
		bzero(pathname, MAX_CMD);
		if ((strlen(CWD)+strlen(ARGV[1]) + 1) > MAX_CMD-1) {
			puts("command too long");
			return(0);
		}
		strcpy(pathname, CWD);
		strcat(pathname, ARGV[1]);
		return(ReadFile(pathname));
	}

	return(0);

}

/* 
   help command
 */
int HelpHandler() {
	ShellCmds *c;
	int len;

	c = cmds;
	while (c->command) {
		printf("@s", c->command);
		len = 20-strlen(c->command);
		while (len-- > 0) {
			printf(" ");
		}
		printf("@s\n", c->help);
		c++;
	}

	return(0);
}

/* 
   fsinfo command
 */
int DfHandler() {

	if (ARGC != 1) {
		puts("usage: fsinfo");
		return(0);
	}

	StatusFS();

	return(0);
}

/*
   check if a given character is a valid hex digit
 */
int IsHex(char c) {

	if (c >= '0' && c <= '9') {
		return(1);
	}
	if (c >= 'a' && c <= 'f') {
		return(1);
	}
	if (c >= 'A' && c <= 'F') {
		return(1);
	}

	return(0);
}

/* 
   Convert a 1-byte hex value string to a char
 */
char Hex2Char(char *c) {
	char val = 0;

	if (*c >= '0' && *c <= '9') {
		val += (*c-48)*16;
	}
	if (*c >= 'a' && *c <= 'f') {
		val += (*c-97+10)*16;
	}
	if (*c >= 'A' && *c <= 'F') {
		val += (*c-65+10)*16;
	}

	if (*(c+1) >= '0' && *(c+1) <= '9') {
		val += (*(c+1)-48);
	}
	if (*(c+1) >= 'a' && *(c+1) <= 'f') {
		val += (*(c+1)-97+10);
	}
	if (*(c+1) >= 'A' && *(c+1) <= 'F') {
		val += (*(c+1)-65+10);
	}

	return(val);
}


/*
   Take a string of hex values in the form of \xAA\xBB and 
   convert them to their char equivalents
 */
int Unescape(char *buf) {
	char *c = buf;
	char val;
	char *t;

	if (!buf) {
		return(-1);
	}

	while (*c) {
		// if the next 4 char's match our escape pattern \x##
		if (*c == '\\' && *(c+1) == 'x' &&
			IsHex(*(c+2)) && IsHex(*(c+3))) {
	
			// convert the hex value to char
			*c = Hex2Char(c+2);

			// shift the rest of the string back
			t = c+1;
			while (*t && *(t+3)) {
				*t = *(t+3);
				t++;
			}
			*t = '\0';
		}
		c++;
	}

	return(c-buf);
}
