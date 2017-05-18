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

extern securityIdType securityID;

int cgc_makeFile(int argcount, char **args) {

int retcode;

    if (argcount < 2) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    retcode = cgc_createFile(args[1], REGULAR, securityID);

    if ( retcode != 0 ) {

        cgc_printf("error\n");
        return retcode;
    }

    return 0;

}


int cgc_makeMemFile(int argcount, char **args) {

int retcode;
int memsize;
void *memptr;

    if (argcount < 3) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    memsize = cgc_atoi(args[2]);

    if (memsize < 0 || memsize > 8192*10) {

        return -1;

    }

    memptr = cgc_malloc(memsize);

    if ( memptr < 0 ) {

        return -1;

    }

    cgc_bzero(memptr, memsize);

    retcode = cgc_makeMemoryFile(args[1], (unsigned int)memptr, memsize,  0,  securityID );
    if ( retcode != 0 ) {

        cgc_printf("error\n");
        return retcode;
    }

    return 0;

}

int cgc_eraseFile(int argcount, char **args) {

int retcode;
fileHandleType fh;

    if (argcount < 2) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    fh = cgc_openFile(args[1], securityID);

    switch (fh) {

        case ERROR_NO_PERMISSION:

            cgc_printf("permission denied\n");
            break;

        case ERROR_NOT_FOUND:

            cgc_printf("file $s not found\n", args[1]);
            break;

        case ERROR_BAD_TYPE:

            cgc_printf("bad type for erase\n");
            break;

    }

    if ( fh < 0 ) {

        return (fh);

    }

    retcode = cgc_deleteFile(fh, securityID);

    if ( retcode < 0 ) {

        cgc_printf("error erasing $s\n", args[1]);

        cgc_closeFile(fh);
        return (retcode);

    }

    return 0;

}

int cgc_listFiles(int argcount, char **args) {

int retcode;
findFileHandleType *fileInfoHandle;
char *otherperms [] = { "--", "-W", "R-", "RW" };
char *filetype [] = { "", "DIR", "REG", "MEM", "ROM" };
char ownerName[10];

    fileInfoHandle = 0;

    if ( argcount > 1 ) {

        retcode = cgc_findFiles(args[1], &fileInfoHandle);
    
    }
    else {

        retcode = cgc_findFiles("", &fileInfoHandle);

    }


    cgc_printf("FILENAME                   SIZE        OWNER     O-PERMS    TYPE\n");
    cgc_printf("----------------------------------------------------------------\n");
    while ( retcode == 0 ) {

        if (cgc_lookupName(ownerName, fileInfoHandle->currentFile->securityID) == -1)
            cgc_strcpy(ownerName, "       ");

        cgc_printf("$-25s  $10d  $-8s  $2s    $3s\n", fileInfoHandle->currentFile->name, 
                                    fileInfoHandle->currentFile->fileSize,
                                    ownerName, 
                                    otherperms[fileInfoHandle->currentFile->othersPermissions], 
                                    filetype[fileInfoHandle->currentFile->fileType]);

        retcode = cgc_findNextFile(fileInfoHandle);

    }
    cgc_printf("\n");

    return 0;

}

int cgc_overwriteFile( int argcount, char **args) {

int retcode;
fileHandleType fh;
char text[1024];

    if (argcount < 2) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    fh = cgc_openFile(args[1], securityID);

    if ( fh <  0 ) {

        switch (fh) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied\n");
                break;

            case ERROR_NOT_FOUND:

                cgc_printf("file $s not found\n", args[1]);
                break;

            case ERROR_BAD_TYPE:

                cgc_printf("unable to write files of this type\n");
                break;

            default:
        
                cgc_printf("Error opening $s\n", args[1]);
        
        }
        
        return (fh);
    }

    retcode = cgc_truncateFile(fh, securityID);

    if ( retcode <  0 ) {

        switch (retcode) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied for write\n");
                break;

            default:
        
                cgc_printf("Error writing to $s\n", args[1]);
        
        }

        cgc_closeFile(fh);
        return (retcode);
    }

    while (1) {

        cgc_receive_until(text, '\n', sizeof(text));

        if ( cgc_strlen(text) == 0 ) {

            break;
        }

        retcode = cgc_writeFile(fh, text, cgc_strlen(text), securityID);

        if ( retcode < 0 ) {

            cgc_printf("Error writing to $s\n", args[1]);
            cgc_closeFile(fh);
            return (retcode);

        }

    }

    cgc_closeFile(fh);

    return 0;

}


int cgc_dumpFile(int argcount, char **args) {

int retcode;
fileHandleType fh;
char buffer[1024];
unsigned int readcount;

    if (argcount < 2) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    fh = cgc_openFile(args[1], securityID);

    if ( fh <  0 ) {

        switch (fh) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied\n");
                break;

            case ERROR_NOT_FOUND:

                cgc_printf("file $s not found\n", args[1]);
                break;
                
            case ERROR_BAD_TYPE:

                cgc_printf("unable to display files of this type\n");
                break;

            default:
        
                cgc_printf("Error opening $s\n", args[1]);
        
        }
        
        return (fh);
    }

    cgc_bzero(buffer, sizeof(buffer));

    retcode = cgc_readFile(fh, buffer, sizeof(buffer), 0, &readcount, securityID);

    if ( retcode <  0 && retcode != ERROR_EOF ) {

        switch (retcode) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied for read\n");
                break;

            default:
        
                cgc_printf("Error reading from $s\n", args[1]);
        
        }

        cgc_closeFile(fh);
        return (retcode);
    }

    retcode = 0;

    while ( retcode == 0 ) {

        cgc_write(STDOUT, buffer, readcount);
        cgc_bzero(buffer, sizeof(buffer));
        retcode = cgc_readFile(fh, buffer, sizeof(buffer), 0, &readcount, securityID);
    
    }

    cgc_closeFile(fh);

    cgc_printf("\n");

    if (retcode == ERROR_EOF ) {

        return 0;

    }
    else {

        cgc_printf("Error reading file\n");
        return -1;

    }


}

int cgc_readFromEnd(int argcount, char **args) {

int retcode;
fileHandleType fh;
char buffer[1024];
unsigned int readcount;
fileInfoType fileinfo;

    if (argcount < 3) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    if ( cgc_statusFile( args[1],  &fileinfo) != 0 ) {

        cgc_printf("unable to stat file $s\n", args[1]);
        return -1;

    }

    fh = cgc_openFile(args[1], securityID);

    if ( fh <  0 ) {

        switch (fh) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied\n");
                break;

            case ERROR_NOT_FOUND:

                cgc_printf("file $s not found\n", args[1]);
                break;
                
            default:
        
                cgc_printf("Error opening $s\n", args[1]);
        
        }
        
        return (fh);
    }

    cgc_fileReadPosition(fh, fileinfo.size - cgc_atoi(args[2]));

    cgc_bzero(buffer, sizeof(buffer));

    retcode = cgc_readFile(fh, buffer, sizeof(buffer), 0, &readcount, securityID);

    if ( retcode <  0 && retcode != ERROR_EOF ) {

        switch (retcode) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied for read\n");
                break;

            default:
        
                cgc_printf("Error reading from $s\n", args[1]);
                cgc_printf("errno is $d\n", retcode);
        
        }

        cgc_closeFile(fh);
        return (retcode);
    }

    retcode = 0;

    if (readcount > 0 ) {

        cgc_write(STDOUT, buffer, readcount);
    }

    while ( retcode == 0 ) {

        cgc_bzero(buffer, sizeof(buffer));
        retcode = cgc_readFile(fh, buffer, sizeof(buffer), 0, &readcount, securityID);
        cgc_write(STDOUT, buffer, readcount);
    
    }

    cgc_closeFile(fh);

    cgc_printf("\n");

    if (retcode == ERROR_EOF ) {

        return 0;

    }
    else {

        cgc_printf("Error reading file\n");
        return -1;

    }


}


int cgc_readFirstN(int argcount, char **args) {

int retcode;
fileHandleType fh;
char buffer[1024];
unsigned int readCount;
unsigned int readTermCount;
unsigned int totalRead;

    if (argcount < 3) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    fh = cgc_openFile(args[1], securityID);

    if ( fh <  0 ) {

        switch (fh) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied\n");
                break;

            case ERROR_NOT_FOUND:

                cgc_printf("file $s not found\n", args[1]);
                break;
                
            default:
        
                cgc_printf("Error opening $s\n", args[1]);
        
        }
        
        return (fh);
    }

    readTermCount = cgc_atoi(args[2]);

    if ( readTermCount == 0 ) {

        return 0;
    }

    totalRead = 0;
    cgc_bzero(buffer, sizeof(buffer));

    retcode = cgc_readFile(fh, buffer, cgc_minimum(sizeof(buffer), readTermCount - totalRead), 0, &readCount, securityID);

    if ( retcode <  0 && retcode != ERROR_EOF ) {

        switch (retcode) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied for read\n");
                break;

            default:
        
                cgc_printf("Error reading from $s\n", args[1]);
                cgc_printf("errno is $d\n", retcode);
        
        }

        cgc_closeFile(fh);
        return (retcode);
    }

    retcode = 0;

    if (readCount > 0 ) {

        totalRead += readCount;
        cgc_write(STDOUT, buffer, readCount);
    }

    while ( retcode == 0 && totalRead < readTermCount ) {

        cgc_bzero(buffer, sizeof(buffer));
        retcode = cgc_readFile(fh, buffer, cgc_minimum(sizeof(buffer), readTermCount - totalRead), 0, &readCount, securityID);
        cgc_write(STDOUT, buffer, readCount);
        totalRead += readCount;
    
    }

    cgc_closeFile(fh);

    cgc_printf("\n");

    if (retcode == ERROR_EOF || retcode == NO_ERROR ) {

        return 0;

    }
    else {

        cgc_printf("Error reading file\n");
        return -1;

    }

}


int cgc_copyFile(int argcount, char **args) {

int retcode;
fileHandleType fh;
fileHandleType fh2;
char buffer[1024];
unsigned int readcount;
fileInfoType fileinfo;

    if (argcount < 3) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    fh = cgc_openFile(args[1], securityID);

    if ( fh <  0 ) {

        switch (fh) {

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied\n");
                break;

            case ERROR_NOT_FOUND:

                cgc_printf("file $s not found\n", args[1]);
                break;
                
            default:
        
                cgc_printf("error opening $s\n", args[1]);
        
        }
        
        return (fh);
    }

    if ( cgc_statusFile( args[2],  &fileinfo) != 0 ) {

        retcode = cgc_createFile(args[2], REGULAR, securityID);

        if ( retcode != 0 ) {

            cgc_printf("error creating $s\n", args[2]);
            return -1;
        }

    }
    else {

        cgc_printf("file $s already exists\n", args[2]);
        cgc_closeFile(fh);
        return -1;

    }

    fh2 = cgc_openFile(args[2], securityID);

    if ( fh2 < 0 ) {

        cgc_printf("unable to open $s for writing\n", args[2]);

        cgc_closeFile(fh);

        return -1;

    }

    retcode = 0;

    while ( retcode == 0 ) {

        cgc_bzero(buffer, sizeof(buffer));

        retcode = cgc_readFile(fh, buffer, sizeof(buffer), 0, &readcount, securityID);

        if (readcount > 0 ) {

            cgc_writeFile( fh2, buffer, readcount, securityID);
        }

    }

    cgc_closeFile(fh);

    if (retcode == ERROR_EOF ) {


        cgc_closeFile(fh2);
        return 0;

    }
    else if (retcode == ERROR_NO_PERMISSION) {

        cgc_printf("permission denied for read\n");
        retcode = cgc_deleteFile(fh2, securityID);
        cgc_closeFile(fh2);
        return -1;
    }
    else {

        retcode = cgc_deleteFile(fh2, securityID);
        cgc_printf("error reading file\n");
        cgc_closeFile(fh2);
        return -1;

    }


}

int cgc_setPermissions(int argcount, char **args) {

int retcode;
otherPermsType operms;
fileHandleType fh;

    if (argcount < 3) {

        cgc_printf("invalid usage\n");
        return -1;
    }

    operms = cgc_atoi(args[2]);

    if ( operms > 3 ) {

        cgc_printf("invalid usage\n");
        return -1;

    }

    fh = cgc_openFile(args[1], securityID);

    if ( fh < 0 ) {

        switch (fh) {

            case ERROR_NOT_FOUND:

                cgc_printf("file $s not found\n", args[1]);
                return -1;
                break;

            case ERROR_NO_PERMISSION:

                cgc_printf("permission denied\n");
                return fh;
                break;

        } // switch

    } // if ( fh < 0 )

    retcode = cgc_setPerms(fh, operms, securityID);

    if ( retcode != 0 ) {

        cgc_closeFile(fh);
        cgc_printf("permission denied\n");
        return -1;

    }

    cgc_closeFile(fh);

    return 0;

}


