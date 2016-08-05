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
#include "io.h"

extern environment ENV;

void Login(void) {
	strcpy(ENV.User, "crs");
	strcpy(ENV.Group, "crs");
}

uint8_t ChUser(Command *pCmd) {
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
		puts("Input error");
		puts("Usage: chuser <username>");
		return(0);
	}

	if ((PasswdFile = fopen("passwd", "r", 1)) == NULL) {
		puts("Unable to open passwd file");
		return(0);
	}

	while (fgets(buf, 128, PasswdFile)) {
		if ((password = strtok(buf, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			return(0);
		}
		if ((user = strtok(NULL, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			return(0);
		}
		if (!strcmp(user, pCmd->argv[1])) {
			if ((group = strtok(NULL, ":")) == NULL) {
				fclose(PasswdFile);
				puts("Passwd file is corrupted");
				return(0);
			}
			// root always has su rights
			if (!strcmp(ENV.User, "root")) {
				strcpy(ENV.User, user);
				strcpy(ENV.Group, group);
				printf("Authentication success for user '$s'\n\r",ENV.User);
				fclose(PasswdFile);
				return(1);
			}
				
			printf("Password: ");
			if (ReadUntilNewline(STDIN, password_buf, 32) == 0) {
				fclose(PasswdFile);
				return(0);
			}
			printf("\b\b  \b\b\n\r");
			
			if (!strcmp(password, password_buf)) {
				// passwords match
				strcpy(ENV.User, user);
				strcpy(ENV.Group, group);
				printf("Authentication success for user '$s'\n\r",ENV.User);
				fclose(PasswdFile);
				return(1);
			} else {
				puts("Authentication failure");
				return(0);
			}
		}
	}
	printf("No passwd entry for user '$s'\n\r", pCmd->argv[1]);
	fclose(PasswdFile);
	return(0);
}

uint8_t ChPw(Command *pCmd) {
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
	if (!strcmp(ENV.User, "root")) {
		if (pCmd->argc != 2) {
			puts("Input error");
			puts("Usage: chpw <username>");
			return(0);
		}
		strcpy(TargetUser, pCmd->argv[1]);
	} else {
		if (pCmd->argc != 1) {
			puts("Input error");
			puts("Usage: chpw");
			return(0);
		}
		strcpy(TargetUser, ENV.User);
	}

	if ((PasswdFile = fopen("passwd", "r", 1)) == NULL) {
		puts("Unable to open passwd file");
		return(0);
	}

	bzero(OutputBuf, MAX_FILE_SIZE);

	while (fgets(buf, 128, PasswdFile)) {
		if (buf[0] == '\0') {
			// empty line
			continue;
		}
		if ((password = strtok(buf, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			fclose(PasswdFile);
			return(0);
		}
		if ((user = strtok(NULL, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			fclose(PasswdFile);
			return(0);
		}
		if (!strcmp(user, TargetUser)) {
			// found the target user
			if ((group = strtok(NULL, ":")) == NULL) {
				fclose(PasswdFile);
				puts("Passwd file is corrupted");
				return(0);
			}

			printf("New password: ");
			if (ReadUntilNewline(STDIN, password_buf, 32) == 0) {
				fclose(PasswdFile);
	                	printf("\b\b  \b\b\n\r");
				puts("Password not changed");
				return(0);
			}
	                printf("\b\b  \b\b\n\r");
#ifdef PATCHED_1
			if (strchr(password_buf, ':')) {
				puts("Passwords may not contain ':' characters");
				fclose(PasswdFile);
				return(0);
			}
#endif

			// add the new passwd file line to the buffer we'll 
			// eventually write back to the passwd file
			// output_buffer += "user:group:password_buf"
			sprintf(NewPasswdLine, "$s:$s:$s\n", password_buf, user, group);
			if (strlen(OutputBuf) + strlen(NewPasswdLine) > MAX_FILE_SIZE) {
				puts("Password file is too large");
				fclose(PasswdFile);
				return(0);
			}
			strcat(OutputBuf, NewPasswdLine);
			
		} else {
			// this is not the user you're looking for
			// add it to the buffer we'll eventually
			// write back to the passwd file
			// but first put back the ':' delimiter the strtok removed
			password[strlen(password)] = ':';
			user[strlen(user)] = ':';
			strcat(OutputBuf, buf);
			strcat(OutputBuf, "\n");
		}
	}
	fclose(PasswdFile);

	if (strlen(OutputBuf) > 0) {
		if ((PasswdFile = fopen("passwd", "w", 1)) == NULL) {
			puts("Unable to open passwd file");
			return(0);
		}
		// write the new password buf
		if (fwrite(OutputBuf, strlen(OutputBuf)+1, 1, PasswdFile) != strlen(OutputBuf)+1) {
			puts("Password file update failed\n\r");
			fclose(PasswdFile);
			return(0);
		}

		fclose(PasswdFile);
	}

	return(1);

}

uint8_t ID(Command *pCmd) {

	if (!pCmd) {
		return(0);
	}

	if (pCmd->argc != 1) {
		puts("Input error");
		puts("Usage: id");
		return(0);
	}

	printf("uid=$s gid=$s\n\r", ENV.User, ENV.Group);

	return(1);
}

uint8_t NewUser(Command *pCmd) {
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

	if (strcmp(ENV.User, "root")) {
		puts("Must be root");
		return(0);
	}

	if (pCmd->argc != 3) {
		puts("Input error");
		puts("Usage: newuser <username> <group>");
		return(0);
	}

	// see if the new user already exists
	if ((PasswdFile = fopen("passwd", "r", 1)) == NULL) {
		puts("Unable to open passwd file");
		return(0);
	}
	bzero(OutputBuf, MAX_FILE_SIZE);

	while (fgets(buf, 128, PasswdFile)) {
		if (buf[0] == '\0') {
			// empty line
			continue;
		}
		if ((passwd = strtok(buf, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			fclose(PasswdFile);
			return(0);
		}
		if ((user = strtok(NULL, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			fclose(PasswdFile);
			return(0);
		}
		if (!strcmp(user, pCmd->argv[1])) {
			printf("User '$s' already exists\n\r", pCmd->argv[1]);
			fclose(PasswdFile);
			return(0);
		}

		// add this line to the output buffer
		passwd[strlen(passwd)] = ':';
		user[strlen(user)] = ':';
		strcat(OutputBuf, buf);
		strcat(OutputBuf, "\n");
	}
	fclose(PasswdFile);

	// got to the end of the file and didn't find the user, so
	// get a password for the new user
	printf("New user password: ");
	if (ReadUntilNewline(STDIN, password_buf, 32) == 0) {
		fclose(PasswdFile);
		return(0);
	}
	printf("\b\b  \b\b\n\r");

	// add the new user to the passwd file
	sprintf(NewPasswdLine, "$s:$s:$s\n", password_buf, pCmd->argv[1], pCmd->argv[2]);
	if (strlen(OutputBuf) + strlen(NewPasswdLine) > MAX_FILE_SIZE) {
		puts("Password file is too large");
		fclose(PasswdFile);
		return(0);
	}
	strcat(OutputBuf, NewPasswdLine);

	if (strlen(OutputBuf) > 0) {
		if ((PasswdFile = fopen("passwd", "w", 1)) == NULL) {
			puts("Unable to open passwd file");
			return(0);
		}
		// write the new password buf
		if (fwrite(OutputBuf, strlen(OutputBuf)+1, 1, PasswdFile) != strlen(OutputBuf)+1) {
			puts("Password file update failed\n\r");
			fclose(PasswdFile);
			return(0);
		}

		fclose(PasswdFile);
	}

	printf("User '$s' added\n\r", pCmd->argv[1]);
	return(1);
}

uint8_t DelUser(Command *pCmd) {
	pFILE PasswdFile;
	char buf[128];
	char *user;
	char *passwd;
	char OutputBuf[MAX_FILE_SIZE];
	uint8_t Found = 0;

	if (!pCmd) {
		return(0);
	}

	if (strcmp(ENV.User, "root")) {
		puts("Must be root");
		return(0);
	}

	if (pCmd->argc != 2) {
		puts("Input error");
		puts("Usage: deluser <username>");
		return(0);
	}

	// see if the user exists
	if ((PasswdFile = fopen("passwd", "r", 1)) == NULL) {
		puts("Unable to open passwd file");
		return(0);
	}
	bzero(OutputBuf, MAX_FILE_SIZE);

	while (fgets(buf, 128, PasswdFile)) {
		if (buf[0] == '\0') {
			// empty line
			continue;
		}
		if ((passwd = strtok(buf, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			fclose(PasswdFile);
			return(0);
		}
		if ((user = strtok(NULL, ":")) == NULL) {
			fclose(PasswdFile);
			puts("Passwd file is corrupted");
			fclose(PasswdFile);
			return(0);
		}
		if (strcmp(user, pCmd->argv[1])) {
			// not the target user, just add this user to the outputbuf
			passwd[strlen(passwd)] = ':';
			user[strlen(user)] = ':';
			strcat(OutputBuf, buf);
			strcat(OutputBuf, "\n");
		} else {
			Found = 1;
		}
		
	}
	fclose(PasswdFile);

	if (Found) {
		if (strlen(OutputBuf) > 0) {
			if ((PasswdFile = fopen("passwd", "w", 1)) == NULL) {
				puts("Unable to open passwd file");
			return(0);
			}
			// write the new password buf
			if (fwrite(OutputBuf, strlen(OutputBuf)+1, 1, PasswdFile) != strlen(OutputBuf)+1) {
				puts("Password file update failed\n\r");
				fclose(PasswdFile);
				return(0);
			}
	
			fclose(PasswdFile);
		}
		printf("User '$s' deleted\n\r", pCmd->argv[1]);
		return(1);
	}

	printf("User '$s' not found\n\r", pCmd->argv[1]);
	return(0);

}
