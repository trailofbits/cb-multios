/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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
#include "service.h"
#include "filesystem.h"
#include "stdio.h"
#include "string.h"
#include "input.h"
#include "malloc.h"

#define COMMAND_COUNT 10

securityIdType securityID = 0;

int main(void) {
char command[1024];
char buffer[100];
char nameBuffer[10];
int retcode;
int unauth = 1;
unsigned int securityToken;
int i;
int argcount;
char **args;
fileHandleType fh;

    commandsTableType commands[] = {

        {"make", makeFile },
        {"erase", eraseFile }, 
        {"list", listFiles },
        {"write", overwriteFile }, 
        {"show", dumpFile },
        {"last", readFromEnd },
        { "first", readFirstN }, 
        { "copy", copyFile }, 
        { "perms", setPermissions },
        { "makememfile", makeMemFile }

    };

    retcode = initFileSystem(4096, 8192, 8192*300);

    if (retcode != 0) {

        printf("Error making filesystem\n");
        _terminate(-1);
    }


    retcode = createFile("README.txt", REGULAR, ROOT_ID);

    if ( retcode != 0 ) {

        printf("error making README\n");
        _terminate(-1);
    }

    fh = openFile("README.txt", ROOT_ID);

    if ( fh < 0 ) {

        printf("error making README\n");
        _terminate(-1);

    }

    strcpy(buffer, "Welcome to the interactive filesystem shell. ");

    retcode = writeFile(fh, buffer, strlen(buffer), ROOT_ID);

    if (retcode < 0 ) {

        printf("error making README\n");
        _terminate(-1);

    }

    strcpy(buffer, "Valid commands are make, makememfile, erase, list, copy, write, show, first, last, and perms.");

    retcode = writeFile(fh, buffer, strlen(buffer), ROOT_ID);

    if (retcode < 0 ) {

        printf("error making Message of the Day\n");
        _terminate(-1);

    }

    // this should be read-only but needs to be writable so it can be deleted for the exploit
    setPerms(fh, 3, ROOT_ID);

    closeFile(fh);

    makeMemoryFile("authentication.db", 0x4347C000, 4096,  1,  0 );

    while (1) {

        if (unauth) {

            printf("login: ");
        }
        else {

            printf("> ");
        }

        retcode = receive_until(command, '\n', sizeof(command));

        if (strlen(command) == 0) {

            continue;
        }

        argcount = tokenize(command, ' ', &args);
        
        if (unauth) {

            if (argcount != 2) {

                free(args);
                continue;
            }

            securityToken = atoi(args[1]);

            securityID = authenticate(args[0], securityToken);

            if (securityID == 0) {

                printf("Invalid login\n");
                free(args);
                continue;
            }
            else {

                printf("Access allowed\n");
                lookupName(nameBuffer, securityID);

                printf("Welcome $s\n", nameBuffer);

            }

            unauth = 0;

            free(args);
            continue;

        }

        if (strcmp(args[0], "logout") == 0) {

            printf("bye felicia\n");
            unauth = 1;
            continue;

        }
        else if (strcmp(args[0], "exit") == 0 ) {

            break;

        }
        else {

            for ( i= 0; i < COMMAND_COUNT; ++i ) {

                if ( strcmp(args[0], commands[i].command) == 0 ) {

                    retcode = commands[i].handler(argcount, args);
                    break;
                }

            }

            if ( i == COMMAND_COUNT && strlen(args[0]) > 0 ) {

                printf("unknown command $s\n", args[0]);

            }
            
            continue;
        }

    } //while

}  // main  

