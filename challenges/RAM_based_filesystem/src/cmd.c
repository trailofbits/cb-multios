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
#include "cgc_stdint.h"
#include "cgc_fs.h"
#include "cgc_cmd.h"

ShellCmds cgc_cmds[] = {
	{ "show",       cgc_LsHandler,     "List files in a directory" },
	{ "dump",       cgc_CatHandler,    "Dump the contents of a file" },
	{ "delete",     cgc_RmHandler,     "Delete a file" },
	{ "mkfolder",   cgc_MkdirHandler,  "Make a new directory" },
	{ "delfolder",  cgc_RmdirHandler,  "Delete a directory" },
	{ "bye",        cgc_ExitHandler,   "Exit the program" },
	{ "echo",       cgc_EchoHandler,   "Echo a string to the screen or into a file" },
	{ "fsinfo",     cgc_DfHandler,     "Provides usage information about filesystem" },
	{ "help",       cgc_HelpHandler,   "Help listing" },
	{ "?",          cgc_HelpHandler,   "Help listing" },
	{ NULL,		NULL,		NULL},
};

extern char *cgc_ARGV[];
extern uint32_t cgc_ARGC;
extern char cgc_CWD[];

/*
   cgc_read input until the specified delim char is seen or 
   we reach the max length
 */
int cgc_readUntil(char *buf, int max, char delim) {
	unsigned char c[1];
	cgc_size_t size;
	uint32_t i = 0;

	while (i < max) {
		if (cgc_receive(STDIN, c, 1, &size) != 0) {
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
int cgc_ExitHandler() {

	cgc_puts("bye");
	cgc__terminate(0);

}

/* 
   mkfolder command 
 */
int cgc_MkdirHandler() {
	char pathname[MAX_CMD];

	if (cgc_ARGC != 2) {
		cgc_puts("usage: mkfolder <directory>");
		return(0);
	}

	if (cgc_ARGV[1][0] == '/') {
		// we have a full path
		return(cgc_mkdir(cgc_ARGV[1]));
	} else {
		// we need to prepend the cgc_CWD
		cgc_bzero(pathname, MAX_CMD);
		if ((cgc_strlen(cgc_CWD)+cgc_strlen(cgc_ARGV[1]) + 1) > MAX_CMD-1) {
			cgc_puts("command too long");
			return(0);
		}
		cgc_strcpy(pathname, cgc_CWD);
		cgc_strcat(pathname, cgc_ARGV[1]);
		return(cgc_mkdir(pathname));
	}

	return(0);
}

/*
   delfolder command
 */ 
int cgc_RmdirHandler() {
	char pathname[MAX_CMD];

	if (cgc_ARGC != 2) {
		cgc_puts("usage: delfolder <directory>");
		return(0);
	}

	if (cgc_ARGV[1][0] == '/') {
		// we have a full path
		return(cgc_rmdir(cgc_ARGV[1]));
	} else {
		// we need to prepend the cgc_CWD
		cgc_bzero(pathname, MAX_CMD);
		if ((cgc_strlen(cgc_CWD)+cgc_strlen(cgc_ARGV[1]) + 1) > MAX_CMD-1) {
			cgc_puts("command too long");
			return(0);
		}
		cgc_strcpy(pathname, cgc_CWD);
		cgc_strcat(pathname, cgc_ARGV[1]);
		return(cgc_rmdir(pathname));
	}

	return(0);
}

/* 
   show command
 */
int cgc_LsHandler() {
	char pathname[MAX_CMD];

	if (cgc_ARGC == 1) {
		// no path given, assume cgc_CWD
		return(cgc_ls(cgc_CWD));
	}
	if (cgc_ARGC != 2) {
		cgc_puts("usage: show <directory>");
		return(0);
	}

	if (cgc_ARGV[1][0] == '/') {
		// we have a full path
		return(cgc_ls(cgc_ARGV[1]));
	} else {
		// we need to prepend the cgc_CWD
		cgc_bzero(pathname, MAX_CMD);
		if ((cgc_strlen(cgc_CWD)+cgc_strlen(cgc_ARGV[1]) + 1) > MAX_CMD-1) {
			cgc_puts("command too long");
			return(0);
		}
		cgc_strcpy(pathname, cgc_CWD);
		cgc_strcat(pathname, cgc_ARGV[1]);
		return(cgc_ls(pathname));
	}

	return(0);

}

/* 
   delete command
 */
int cgc_RmHandler() {
	char pathname[MAX_CMD];

	if (cgc_ARGC != 2) {
		cgc_puts("usage: delete <file>");
		return(0);
	}

	if (cgc_ARGV[1][0] == '/') {
		// no path given, assume cgc_CWD
		return(cgc_unlink(cgc_ARGV[1]));
	} else {
		// we need to prepend the cgc_CWD
		cgc_bzero(pathname, MAX_CMD);
		if ((cgc_strlen(cgc_CWD)+cgc_strlen(cgc_ARGV[1]) + 1) > MAX_CMD-1) {
			cgc_puts("command too long");
			return(0);
		}
		cgc_strcpy(pathname, cgc_CWD);
		cgc_strcat(pathname, cgc_ARGV[1]);
		return(cgc_unlink(pathname));
	}

	return(0);

}

/* 
   echo command
 */
int cgc_EchoHandler() {
	char pathname[MAX_CMD];
	char outstr[MAX_CMD];
	FILE *out;
	int len;

	if (cgc_ARGC < 2 || cgc_ARGC == 3) {
		cgc_puts("usage: echo <text> [>|>>] [file]");
		return(0);
	}

	if (cgc_ARGC == 2) {
		// handle case of 'echo <text>'
		cgc_bzero(outstr, MAX_CMD);
		cgc_strncpy(outstr, cgc_ARGV[1], MAX_CMD-1);
		if ((len = cgc_Unescape(outstr)) == -1) {
			cgc_puts("unable to write to file");
			return(-1);
		}
		cgc_write(outstr, len);
		return(0);
	}

	if (cgc_ARGC == 4) {
		// redirecting to a file
		cgc_bzero(pathname, MAX_CMD);
		if (cgc_ARGV[3][0] == '/') {
			if (cgc_strlen(cgc_ARGV[3]) > MAX_CMD-1) {
				cgc_puts("invalid file name");
				return(-1);
			}
			cgc_strcpy(pathname, cgc_ARGV[3]);
		} else {
			if ((cgc_strlen(cgc_CWD)+cgc_strlen(cgc_ARGV[3]) + 1) > MAX_CMD-1) {
				cgc_puts("command too long");
				return(0);
			}
			cgc_strcpy(pathname, cgc_CWD);
			cgc_strcat(pathname, cgc_ARGV[3]);
		}
			
		if (!cgc_strcmp(cgc_ARGV[2], ">")) {
			// cgc_write to file
			if ((out = cgc_fopen(pathname, "w")) == NULL) {
				cgc_puts("unable to write to file");
				return(-1);
			}
			cgc_bzero(outstr, MAX_CMD);
			cgc_strncpy(outstr, cgc_ARGV[1], MAX_CMD-1);
			if ((len = cgc_Unescape(outstr)) == -1) {
				cgc_puts("unable to write to file");
				cgc_fclose(out);
				return(-1);
			}
			cgc_fwrite(outstr, len, 1, out);
			cgc_fclose(out);
		} else if (!cgc_strcmp(cgc_ARGV[2], ">>")) {
			// append to file
			if ((out = cgc_fopen(pathname, "a")) == NULL) {
				cgc_puts("unable to write to file");
				return(-1);
			}
			cgc_bzero(outstr, MAX_CMD);
			cgc_strncpy(outstr, cgc_ARGV[1], MAX_CMD-1);
			if ((len = cgc_Unescape(outstr)) == -1) {
				cgc_fclose(out);
				cgc_puts("unable to write to file");
				return(-1);
			}
			cgc_fwrite(outstr, len, 1, out);
			cgc_fclose(out);
		} else {
			cgc_puts("usage: echo <text> [>|>>] [file]");
			return(0);
		}
	}

	return(0);

}

/*
   show command
 */
int cgc_CatHandler() {
	char pathname[MAX_CMD];

	if (cgc_ARGC != 2) {
		cgc_puts("usage: dump <file>");
		return(0);
	}

	if (cgc_ARGV[1][0] == '/') {
		// no path given, assume cgc_CWD
		return(cgc_ReadFile(cgc_ARGV[1]));
	} else {
		// we need to prepend the cgc_CWD
		cgc_bzero(pathname, MAX_CMD);
		if ((cgc_strlen(cgc_CWD)+cgc_strlen(cgc_ARGV[1]) + 1) > MAX_CMD-1) {
			cgc_puts("command too long");
			return(0);
		}
		cgc_strcpy(pathname, cgc_CWD);
		cgc_strcat(pathname, cgc_ARGV[1]);
		return(cgc_ReadFile(pathname));
	}

	return(0);

}

/* 
   help command
 */
int cgc_HelpHandler() {
	ShellCmds *c;
	int len;

	c = cgc_cmds;
	while (c->command) {
		cgc_printf("@s", c->command);
		len = 20-cgc_strlen(c->command);
		while (len-- > 0) {
			cgc_printf(" ");
		}
		cgc_printf("@s\n", c->help);
		c++;
	}

	return(0);
}

/* 
   fsinfo command
 */
int cgc_DfHandler() {

	if (cgc_ARGC != 1) {
		cgc_puts("usage: fsinfo");
		return(0);
	}

	cgc_StatusFS();

	return(0);
}

/*
   check if a given character is a valid hex digit
 */
int cgc_IsHex(char c) {

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
char cgc_Hex2Char(char *c) {
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
int cgc_Unescape(char *buf) {
	char *c = buf;
	char val;
	char *t;

	if (!buf) {
		return(-1);
	}

	while (*c) {
		// if the next 4 char's match our escape pattern \x##
		if (*c == '\\' && *(c+1) == 'x' &&
			cgc_IsHex(*(c+2)) && cgc_IsHex(*(c+3))) {
	
			// convert the hex value to char
			*c = cgc_Hex2Char(c+2);

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
