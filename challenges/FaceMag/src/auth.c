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
#include "cgc_ctype.h"

securityIdType nextSecurityID = 1337;
fileHandleType cgc_securityIDFileHandle;


securityIdType cgc_authenticate(char *name, char *password) {

char username[25];
char pass[25];
char line[200];
char tmpbuff[100];
securityIdType security_ID;
fileHandleType fh;
int retcode;
unsigned int count;


	fh = cgc_openFile("Users.db", ROOT_ID);

	if ( fh < 0 ) {

        cgc_printf("error opening Users.db\n");
        cgc__terminate(-1);

    }

    while ( 1 ) {

	    retcode = cgc_readFileUntil( fh, username, sizeof(username), ':', &count, ROOT_ID);

	    // if no data was cgc_read we must be at the end of the file or its empty
	    if (retcode == 0 ) {

	    	break;
	    }
	    
	    // if the username isn't a match, go to the next entry
	    if (cgc_strcmp(username, name) != 0) {

	    	retcode = cgc_readFileUntil( fh, line, sizeof(line), '\n', &count, ROOT_ID);
	    	continue;
	    }

	    retcode = cgc_readFileUntil( fh, pass, sizeof(pass), ':', &count, ROOT_ID);

	    if ( cgc_strcmp(pass, password) != 0 ) {

	    	cgc_closeFile(fh);
	    	return -1;
	    }

	    // must be a match, so return its assigned accountID
	    retcode = cgc_readFileUntil( fh, tmpbuff, sizeof(tmpbuff), '\n', &count, ROOT_ID);

	    cgc_closeFile(fh);
	    return(cgc_atoi(tmpbuff));

    } // while (retcode >= 0)

    cgc_closeFile(fh);
    return -1;

}


securityIdType cgc_create_user(char *name, char *password, char *real_name) {

char username[25];
char filename[20];
char tmpbuff[25];
unsigned int newID;
unsigned int ID1;
unsigned int ID2;
fileHandleType fh;
fileHandleType fh3;
int retcode;
unsigned int count;
char line[1024];

	fh = cgc_openFile("Users.db", ROOT_ID);

	if ( fh < 0 ) {

        cgc_printf("error opening Users.db\n");
        cgc__terminate(-1);

    }

    if (cgc_securityIDFileHandle == -1 ) {

        cgc_securityIDFileHandle = cgc_openFile("UserIDs.mem", ROOT_ID );

        if (cgc_securityIDFileHandle < 0 ) {

            cgc_printf("error opening security ID file\n");
            cgc__terminate(-1);
        }
    }

    retcode = cgc_readFile( cgc_securityIDFileHandle, (void *)&ID1, sizeof(ID1), 0, 0, ROOT_ID );

    if ( retcode == ERROR_EOF ) {

        cgc_fileReadPosition( cgc_securityIDFileHandle, 1 );

    }

    retcode = cgc_readFile( cgc_securityIDFileHandle, (void *)&ID2, sizeof(ID2), 0, 0, ROOT_ID );

    if ( retcode == ERROR_EOF ) {

        cgc_fileReadPosition( cgc_securityIDFileHandle, 1 );

    }

    newID = ID1 * ID2;
    newID &= 0x7fffffff;

    while ( 1 ) {

	    retcode = cgc_readFileUntil( fh, username, sizeof(username), ':', &count, ROOT_ID);

	    // if no data was cgc_read we must be at the end of the file or its empty
	    if (retcode == 0 )
	    	break;

	    // if the username is a dupe, rewind the securityID by 4 bytes and then return an error
	    if (cgc_strcmp(username, name) == 0) {

            cgc_fileReadPosRelative( cgc_securityIDFileHandle, -4 );
            cgc_closeFile(fh);
	    	return -1;
	    }

        retcode = cgc_readFileUntil( fh, line, sizeof(line), ':', &count, ROOT_ID);
	    retcode = cgc_readFileUntil( fh, line, sizeof(line), '\n', &count, ROOT_ID);

        if ( cgc_atoi(tmpbuff) == newID ) {

            ++newID;
            continue;

        }

    } // while (retcode >= 0)	

    // at the end of the file and didn't find a username collision
    cgc_sprintf(line, "$s:$s:$d\n", name, password, newID);

    retcode = cgc_writeFile(fh, line, cgc_strlen(line), ROOT_ID );

    if (retcode < 0 ) {

    	cgc_printf("error updating Users.db\n");
    	cgc__terminate(-1);

    }

    cgc_closeFile(fh);

    cgc_sprintf(filename, "$x.user", newID );

	retcode = cgc_createFile(filename, REGULAR, ROOT_ID);

    if ( retcode < 0 ) {

        cgc_printf("$d\n", retcode);
        cgc__terminate(-1);
    }

    fh3 = cgc_openFile(filename, ROOT_ID);

    if ( fh3 < 0 ) {

    	cgc_printf("error opening users file\n");
    	cgc__terminate(-1);

    }

#ifdef PATCHED_1
    real_name[REALNAME_LEN] = 0;
#endif

    // initial values for last cgc_read and last written posts
    count = 0;

    cgc_writeFile( fh3, (char *)&count, sizeof(count), ROOT_ID );
    cgc_writeFile( fh3, (char *)&count, sizeof(count), ROOT_ID );

    count = cgc_strlen(real_name);
    cgc_writeFile( fh3, (char *)&count, sizeof(count), ROOT_ID );

    cgc_writeFile( fh3, real_name, count, ROOT_ID );

    cgc_closeFile( fh3 );

    return(newID);

}


