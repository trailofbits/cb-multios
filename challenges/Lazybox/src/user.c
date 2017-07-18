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
#include "cgc_io.h"

extern environment cgc_ENV;

void cgc_Login(void) {
	cgc_strcpy(cgc_ENV.User, "crs");
	cgc_strcpy(cgc_ENV.Group, "crs");
}

uint8_t cgc_ChUser(Command *pCmd) {
	pFILE PasswdFile;
	char buf[128];
	char password_buf[32];
	char *user;
	char *group;
	char *password;

	if (!pCmd) {
		return(0);
	}
	if (pCmd->argc != 2) {
		cgc_puts("Input error");
		cgc_puts("Usage: chuser <username>");
		return(0);
	}

	if ((PasswdFile = cgc_fopen("passwd", "r", 1)) == NULL) {
		cgc_puts("Unable to open passwd file");
		return(0);
	}

	while (cgc_fgets(buf, 128, PasswdFile)) {
		if ((password = cgc_strtok(buf, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			return(0);
		}
		if ((user = cgc_strtok(NULL, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			return(0);
		}
		if (!cgc_strcmp(user, pCmd->argv[1])) {
			if ((group = cgc_strtok(NULL, ":")) == NULL) {
				cgc_fclose(PasswdFile);
				cgc_puts("Passwd file is corrupted");
				return(0);
			}
			// root always has su rights
			if (!cgc_strcmp(cgc_ENV.User, "root")) {
				cgc_strcpy(cgc_ENV.User, user);
				cgc_strcpy(cgc_ENV.Group, group);
				cgc_printf("Authentication success for user '$s'\n\r",cgc_ENV.User);
				cgc_fclose(PasswdFile);
				return(1);
			}
				
			cgc_printf("Password: ");
			if (cgc_ReadUntilNewline(STDIN, password_buf, 32) == 0) {
				cgc_fclose(PasswdFile);
				return(0);
			}
			cgc_printf("\b\b  \b\b\n\r");
			
			if (!cgc_strcmp(password, password_buf)) {
				// passwords match
				cgc_strcpy(cgc_ENV.User, user);
				cgc_strcpy(cgc_ENV.Group, group);
				cgc_printf("Authentication success for user '$s'\n\r",cgc_ENV.User);
				cgc_fclose(PasswdFile);
				return(1);
			} else {
				cgc_puts("Authentication failure");
				return(0);
			}
		}
	}
	cgc_printf("No passwd entry for user '$s'\n\r", pCmd->argv[1]);
	cgc_fclose(PasswdFile);
	return(0);
}

uint8_t cgc_ChPw(Command *pCmd) {
	pFILE PasswdFile;
	char buf[128];
	char password_buf[32];
	char *user;
	char *group;
	char *password;
	char TargetUser[32];
	char OutputBuf[MAX_FILE_SIZE];
	char NewPasswdLine[128];

	if (!pCmd) {
		return(0);
	}
	if (!cgc_strcmp(cgc_ENV.User, "root")) {
		if (pCmd->argc != 2) {
			cgc_puts("Input error");
			cgc_puts("Usage: chpw <username>");
			return(0);
		}
		cgc_strcpy(TargetUser, pCmd->argv[1]);
	} else {
		if (pCmd->argc != 1) {
			cgc_puts("Input error");
			cgc_puts("Usage: chpw");
			return(0);
		}
		cgc_strcpy(TargetUser, cgc_ENV.User);
	}

	if ((PasswdFile = cgc_fopen("passwd", "r", 1)) == NULL) {
		cgc_puts("Unable to open passwd file");
		return(0);
	}

	cgc_bzero(OutputBuf, MAX_FILE_SIZE);

	while (cgc_fgets(buf, 128, PasswdFile)) {
		if (buf[0] == '\0') {
			// empty line
			continue;
		}
		if ((password = cgc_strtok(buf, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			cgc_fclose(PasswdFile);
			return(0);
		}
		if ((user = cgc_strtok(NULL, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			cgc_fclose(PasswdFile);
			return(0);
		}
		if (!cgc_strcmp(user, TargetUser)) {
			// found the target user
			if ((group = cgc_strtok(NULL, ":")) == NULL) {
				cgc_fclose(PasswdFile);
				cgc_puts("Passwd file is corrupted");
				return(0);
			}

			cgc_printf("New password: ");
			if (cgc_ReadUntilNewline(STDIN, password_buf, 32) == 0) {
				cgc_fclose(PasswdFile);
	                	cgc_printf("\b\b  \b\b\n\r");
				cgc_puts("Password not changed");
				return(0);
			}
	                cgc_printf("\b\b  \b\b\n\r");
#ifdef PATCHED_1
			if (strchr(password_buf, ':')) {
				cgc_puts("Passwords may not contain ':' characters");
				cgc_fclose(PasswdFile);
				return(0);
			}
#endif

			// add the new passwd file line to the buffer we'll 
			// eventually cgc_write back to the passwd file
			// output_buffer += "user:group:password_buf"
			cgc_sprintf(NewPasswdLine, "$s:$s:$s\n", password_buf, user, group);
			if (cgc_strlen(OutputBuf) + cgc_strlen(NewPasswdLine) > MAX_FILE_SIZE) {
				cgc_puts("Password file is too large");
				cgc_fclose(PasswdFile);
				return(0);
			}
			cgc_strcat(OutputBuf, NewPasswdLine);
			
		} else {
			// this is not the user you're looking for
			// add it to the buffer we'll eventually
			// cgc_write back to the passwd file
			// but first put back the ':' delimiter the strtok removed
			password[cgc_strlen(password)] = ':';
			user[cgc_strlen(user)] = ':';
			cgc_strcat(OutputBuf, buf);
			cgc_strcat(OutputBuf, "\n");
		}
	}
	cgc_fclose(PasswdFile);

	if (cgc_strlen(OutputBuf) > 0) {
		if ((PasswdFile = cgc_fopen("passwd", "w", 1)) == NULL) {
			cgc_puts("Unable to open passwd file");
			return(0);
		}
		// cgc_write the new password buf
		if (cgc_fwrite(OutputBuf, cgc_strlen(OutputBuf)+1, 1, PasswdFile) != cgc_strlen(OutputBuf)+1) {
			cgc_puts("Password file update failed\n\r");
			cgc_fclose(PasswdFile);
			return(0);
		}

		cgc_fclose(PasswdFile);
	}

	return(1);

}

uint8_t cgc_ID(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 1) {
		cgc_puts("Input error");
		cgc_puts("Usage: id");
		return(0);
	}

	cgc_printf("uid=$s gid=$s\n\r", cgc_ENV.User, cgc_ENV.Group);

	return(1);
}

uint8_t cgc_NewUser(Command *pCmd) {
	pFILE PasswdFile;
	char buf[128];
	char password_buf[32];
	char *user;
	char *passwd;
	char OutputBuf[MAX_FILE_SIZE];
	char NewPasswdLine[128];

	if (!pCmd) {
		return(0);
	}

	if (cgc_strcmp(cgc_ENV.User, "root")) {
		cgc_puts("Must be root");
		return(0);
	}

	if (pCmd->argc != 3) {
		cgc_puts("Input error");
		cgc_puts("Usage: newuser <username> <group>");
		return(0);
	}

	// see if the new user already exists
	if ((PasswdFile = cgc_fopen("passwd", "r", 1)) == NULL) {
		cgc_puts("Unable to open passwd file");
		return(0);
	}
	cgc_bzero(OutputBuf, MAX_FILE_SIZE);

	while (cgc_fgets(buf, 128, PasswdFile)) {
		if (buf[0] == '\0') {
			// empty line
			continue;
		}
		if ((passwd = cgc_strtok(buf, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			cgc_fclose(PasswdFile);
			return(0);
		}
		if ((user = cgc_strtok(NULL, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			cgc_fclose(PasswdFile);
			return(0);
		}
		if (!cgc_strcmp(user, pCmd->argv[1])) {
			cgc_printf("User '$s' already exists\n\r", pCmd->argv[1]);
			cgc_fclose(PasswdFile);
			return(0);
		}

		// add this line to the output buffer
		passwd[cgc_strlen(passwd)] = ':';
		user[cgc_strlen(user)] = ':';
		cgc_strcat(OutputBuf, buf);
		cgc_strcat(OutputBuf, "\n");
	}
	cgc_fclose(PasswdFile);

	// got to the end of the file and didn't find the user, so
	// get a password for the new user
	cgc_printf("New user password: ");
	if (cgc_ReadUntilNewline(STDIN, password_buf, 32) == 0) {
		cgc_fclose(PasswdFile);
		return(0);
	}
	cgc_printf("\b\b  \b\b\n\r");

	// add the new user to the passwd file
	cgc_sprintf(NewPasswdLine, "$s:$s:$s\n", password_buf, pCmd->argv[1], pCmd->argv[2]);
	if (cgc_strlen(OutputBuf) + cgc_strlen(NewPasswdLine) > MAX_FILE_SIZE) {
		cgc_puts("Password file is too large");
		cgc_fclose(PasswdFile);
		return(0);
	}
	cgc_strcat(OutputBuf, NewPasswdLine);

	if (cgc_strlen(OutputBuf) > 0) {
		if ((PasswdFile = cgc_fopen("passwd", "w", 1)) == NULL) {
			cgc_puts("Unable to open passwd file");
			return(0);
		}
		// cgc_write the new password buf
		if (cgc_fwrite(OutputBuf, cgc_strlen(OutputBuf)+1, 1, PasswdFile) != cgc_strlen(OutputBuf)+1) {
			cgc_puts("Password file update failed\n\r");
			cgc_fclose(PasswdFile);
			return(0);
		}

		cgc_fclose(PasswdFile);
	}

	cgc_printf("User '$s' added\n\r", pCmd->argv[1]);
	return(1);
}

uint8_t cgc_DelUser(Command *pCmd) {
	pFILE PasswdFile;
	char buf[128];
	char *user;
	char *passwd;
	char OutputBuf[MAX_FILE_SIZE];
	uint8_t Found = 0;

	if (!pCmd) {
		return(0);
	}

	if (cgc_strcmp(cgc_ENV.User, "root")) {
		cgc_puts("Must be root");
		return(0);
	}

	if (pCmd->argc != 2) {
		cgc_puts("Input error");
		cgc_puts("Usage: deluser <username>");
		return(0);
	}

	// see if the user exists
	if ((PasswdFile = cgc_fopen("passwd", "r", 1)) == NULL) {
		cgc_puts("Unable to open passwd file");
		return(0);
	}
	cgc_bzero(OutputBuf, MAX_FILE_SIZE);

	while (cgc_fgets(buf, 128, PasswdFile)) {
		if (buf[0] == '\0') {
			// empty line
			continue;
		}
		if ((passwd = cgc_strtok(buf, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			cgc_fclose(PasswdFile);
			return(0);
		}
		if ((user = cgc_strtok(NULL, ":")) == NULL) {
			cgc_fclose(PasswdFile);
			cgc_puts("Passwd file is corrupted");
			cgc_fclose(PasswdFile);
			return(0);
		}
		if (cgc_strcmp(user, pCmd->argv[1])) {
			// not the target user, just add this user to the outputbuf
			passwd[cgc_strlen(passwd)] = ':';
			user[cgc_strlen(user)] = ':';
			cgc_strcat(OutputBuf, buf);
			cgc_strcat(OutputBuf, "\n");
		} else {
			Found = 1;
		}
		
	}
	cgc_fclose(PasswdFile);

	if (Found) {
		if (cgc_strlen(OutputBuf) > 0) {
			if ((PasswdFile = cgc_fopen("passwd", "w", 1)) == NULL) {
				cgc_puts("Unable to open passwd file");
			return(0);
			}
			// cgc_write the new password buf
			if (cgc_fwrite(OutputBuf, cgc_strlen(OutputBuf)+1, 1, PasswdFile) != cgc_strlen(OutputBuf)+1) {
				cgc_puts("Password file update failed\n\r");
				cgc_fclose(PasswdFile);
				return(0);
			}
	
			cgc_fclose(PasswdFile);
		}
		cgc_printf("User '$s' deleted\n\r", pCmd->argv[1]);
		return(1);
	}

	cgc_printf("User '$s' not found\n\r", pCmd->argv[1]);
	return(0);

}
