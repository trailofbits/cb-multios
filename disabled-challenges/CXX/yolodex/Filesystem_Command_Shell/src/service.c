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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"
#include "cgc_filesystem.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_input.h"
#include "cgc_malloc.h"

#define COMMAND_COUNT 10

securityIdType securityID = 0;

int main(int cgc_argc, char *cgc_argv[]) {
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

        {"make", cgc_makeFile },
        {"erase", cgc_eraseFile }, 
        {"list", cgc_listFiles },
        {"write", cgc_overwriteFile }, 
        {"show", cgc_dumpFile },
        {"last", cgc_readFromEnd },
        { "first", cgc_readFirstN }, 
        { "copy", cgc_copyFile }, 
        { "perms", cgc_setPermissions },
        { "makememfile", cgc_makeMemFile }

    };

    retcode = cgc_initFileSystem(4096, 8192, 8192*300);

    if (retcode != 0) {

        cgc_printf("Error making filesystem\n");
        cgc__terminate(-1);
    }


    retcode = cgc_createFile("README.txt", REGULAR, ROOT_ID);

    if ( retcode != 0 ) {

        cgc_printf("error making README\n");
        cgc__terminate(-1);
    }

    fh = cgc_openFile("README.txt", ROOT_ID);

    if ( fh < 0 ) {

        cgc_printf("error making README\n");
        cgc__terminate(-1);

    }

    cgc_strcpy(buffer, "Welcome to the interactive filesystem shell. ");

    retcode = cgc_writeFile(fh, buffer, cgc_strlen(buffer), ROOT_ID);

    if (retcode < 0 ) {

        cgc_printf("error making README\n");
        cgc__terminate(-1);

    }

    cgc_strcpy(buffer, "Valid commands are make, makememfile, erase, list, copy, write, show, first, last, and perms.");

    retcode = cgc_writeFile(fh, buffer, cgc_strlen(buffer), ROOT_ID);

    if (retcode < 0 ) {

        cgc_printf("error making Message of the Day\n");
        cgc__terminate(-1);

    }

    // this should be cgc_read-only but needs to be writable so it can be deleted for the exploit
    cgc_setPerms(fh, 3, ROOT_ID);

    cgc_closeFile(fh);

    cgc_makeMemoryFile("authentication.db", 0x4347C000, 4096,  1,  0 );

    while (1) {

        if (unauth) {

            cgc_printf("login: ");
        }
        else {

            cgc_printf("> ");
        }

        retcode = cgc_receive_until(command, '\n', sizeof(command));

        if (cgc_strlen(command) == 0) {

            continue;
        }

        argcount = cgc_tokenize(command, ' ', &args);
        
        if (unauth) {

            if (argcount != 2) {

                cgc_free(args);
                continue;
            }

            securityToken = cgc_atoi(args[1]);

            securityID = cgc_authenticate(args[0], securityToken);

            if (securityID == 0) {

                cgc_printf("Invalid login\n");
                cgc_free(args);
                continue;
            }
            else {

                cgc_printf("Access allowed\n");
                cgc_lookupName(nameBuffer, securityID);

                cgc_printf("Welcome $s\n", nameBuffer);

            }

            unauth = 0;

            cgc_free(args);
            continue;

        }

        if (cgc_strcmp(args[0], "logout") == 0) {

            cgc_printf("bye felicia\n");
            unauth = 1;
            continue;

        }
        else if (cgc_strcmp(args[0], "exit") == 0 ) {

            break;

        }
        else {

            for ( i= 0; i < COMMAND_COUNT; ++i ) {

                if ( cgc_strcmp(args[0], commands[i].command) == 0 ) {

                    retcode = commands[i].handler(argcount, args);
                    break;
                }

            }

            if ( i == COMMAND_COUNT && cgc_strlen(args[0]) > 0 ) {

                cgc_printf("unknown command $s\n", args[0]);

            }
            
            continue;
        }

    } //while

}  // main  

