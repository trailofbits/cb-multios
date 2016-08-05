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


int savePost(unsigned int postID, unsigned int sessionToken, char *post) {

char filename[25];
char postText[MAXPOST_LEN];
fileHandleType fh;
int retcode;
unsigned int count;
int postSize;

	sprintf(filename, "$x.post", postID);

	retcode = createFile(filename, REGULAR, ROOT_ID);

    if ( retcode != 0 ) {

        printf("1Error making post file.\n");
        _terminate(-1);
    }

    fh = openFile(filename, ROOT_ID);

    if ( fh < 0 ) {

    	printf("2error opening post file\n");
        	_terminate(-1);

    }

    retcode = writeFile(fh, (void *)&sessionToken, sizeof(sessionToken), ROOT_ID);

    if (retcode != 0) {

    	printf("3Error writing post's ID\n");
    	_terminate(-1);
    }

    strncpy(postText, post, MAXPOST_LEN);

    // make sure its null terminated
    postText[MAXPOST_LEN-1] = 0;

    postSize = strlen(postText);

    retcode = writeFile(fh, (void *)&postSize, sizeof(postSize), ROOT_ID );

    retcode = writeFile(fh, postText, postSize, ROOT_ID);

    if (retcode != 0) {

    	printf("4Error writing post's text\n");
    	_terminate(-1);
    }

    closeFile(fh);

    // update the log of all postings
    fh = openFile("posts.log", ROOT_ID);

    if (fh < 0 ) {

        printf("5unable to open posts.log\n");
        _terminate(-1);
    }
    
    retcode = writeFile(fh, (void *)&postID, sizeof(postID), ROOT_ID );
    closeFile(fh);

return 0;

}

int saveComment(unsigned int postID, unsigned int commenterID, char *comment) {

char filename[25];
char commentText[COMMENT_LEN];
fileHandleType fh;
int retcode;
unsigned int count;
int postSize;

    sprintf(filename, "$x.post", postID);

    fh = openFile(filename, ROOT_ID);

    if ( fh < 0 ) {

        printf("error opening post file\n");
        printf("fh = $d\n", fh);
        return -1;

    }

    // writeFile automatically begins writing at the end of the file and so appends to it
    retcode = writeFile(fh, (void *)&commenterID, sizeof(commenterID), ROOT_ID);

    if (retcode != 0) {

        printf("Error writing commenter's ID\n");
        return(-1);
    }

    strncpy(commentText, comment, COMMENT_LEN);
    commentText[COMMENT_LEN-1] = 0;

    postSize = strlen(commentText);

    retcode = writeFile(fh, (void *)&postSize, sizeof(postSize), ROOT_ID );

    if (retcode != 0) {

        printf("Error writing comment's size\n");
        _terminate(-1);
    }

    retcode = writeFile(fh, commentText, postSize, ROOT_ID);

    if (retcode != 0) {

        printf("Error writing comment's text\n");
        _terminate(-1);
    }

    closeFile(fh);

    return 0;
}

// this function will lookup the next post this user hasn't seen yet and call retrievePost to display it.
int newFeedPost(unsigned int sessionToken, char **postMessage, int *messageSize ) {

char filename[25];
fileHandleType fh;
fileHandleType fh2;
int retcode;
unsigned int lastPostRead;
unsigned int nextPost;
unsigned int count;

        sprintf(filename, "$x.user", sessionToken);

        fh = openFile(filename, ROOT_ID);

        if ( fh < 0 ) {

            printf("error opening users file\n");
            printf("fh = $d\n", fh);
            return -1;

        }

        // the first word in the file is the user's last seen postID
        retcode = readFile(fh, (void *)&lastPostRead, sizeof(int), 0, &count, ROOT_ID);

        if ( retcode != 0 ) {

            printf("error reading users file\n");
            return -1;

        }

        closeFile(fh);

        // now open the post log file and find the next post after the postID 
        fh2 = openFile("posts.log", ROOT_ID);

        nextPost = 0;

        while ( nextPost <= lastPostRead ) {

            retcode = readFile(fh2, (void *)&nextPost, sizeof(int), 0, &count, ROOT_ID);

            if (retcode == ERROR_EOF ) {

                break;
            }

        } // while (nextPost <= lastPostRead)

        closeFile( fh2 );

        if ( nextPost > lastPostRead ) {

            // postText = 0;
            retcode = retrievePost( nextPost, 0, postMessage , messageSize);

            if ( retcode == 0 ) {


                // update the users state file
                fh = openFile(filename, ROOT_ID);

                if ( fh < 0 ) {

                    printf("error opening users file\n");
                    printf("fh = $d\n", fh);
                    return -1;

                }

                fileWritePosition( fh, 0 );

                writeFile( fh, (void *)&nextPost, sizeof (int), ROOT_ID);

                closeFile(fh);
            }
            else {

                return -1;

            }

        }
        else {

            return -1;
        }

    return 0;
}

int retrievePost( unsigned int postID, int includeComments, char **postMessage, int *messageSize ) {

char filename[25];
char buffer[1000];
char fullname[REALNAME_LEN];
unsigned int count;
unsigned int postersID;
unsigned int commentCount;
unsigned int commenterNameLen;
unsigned int commentSize;
int postSize;
char postText[MAXPOST_LEN];
fileHandleType fh;
fileHandleType fh2;
int retcode;
char comment[COMMENT_LEN];
char commenter[REALNAME_LEN];
unsigned int commenterID;
unsigned int messageOffset;

	sprintf(filename, "$x.post", postID);

    fh = openFile(filename, ROOT_ID);

    // if the file can't be opened, it must be a bad postID so respond with an error
    if ( fh < 0 ) {

 		return -1;

    }

    retcode = readFile(fh, (void *)&postersID, sizeof(postersID), 0, 0, ROOT_ID);

    if (retcode != 0 ) {

	   printf("Error reading post's ID\n");
	   _terminate(-1);

    }

    retcode = readFile(fh, (void *)&postSize, sizeof(postSize), 0, &count, ROOT_ID);

    if (retcode != 0) {

    	printf("Error reading post's size\n");
    	_terminate(-1);

    }


    retcode = readFile(fh, postText, postSize, 0, &count, ROOT_ID);

    if (retcode != 0 && retcode != ERROR_EOF) {

    	printf("Error reading post's text\n");
    	_terminate(-1);

    }

    sprintf(filename, "$x.user", postersID);

    fh2 = openFile(filename, ROOT_ID);

    if ( fh2 < 0 ) {

    	printf("Error opening users file\n");
    	_terminate(-1);

    }

    retcode = readFile(fh2, fullname, REALNAME_LEN, 12, &count, ROOT_ID);

    if (retcode < 0 && retcode != ERROR_EOF ) {

        printf("Error reading name\n");
        _terminate(-1);

    }

    closeFile(fh2);

    fullname[count] = 0;

    retcode = allocate(4096, 0, (void **)postMessage);

    if (retcode != 0) {

        printf("unable to allocate() memory\n");
        _terminate(-1);
    }

    messageOffset = 0;

    memcpy(*postMessage+messageOffset, &count, sizeof(count));
    messageOffset+=sizeof(count);
    memcpy( *postMessage+messageOffset,fullname, count );
    messageOffset+=count;
    memcpy( *postMessage+messageOffset, &postSize, sizeof(postSize) );
    messageOffset+=sizeof(postSize);
    memcpy( *postMessage+messageOffset, postText, postSize );
    messageOffset+=postSize;

   // read any comments stored with the post and then send also (if requested)

    commentCount = 0;

    while (1) {

         // if comments aren't wanted (for a feed post) then just exist the loop
        if (!includeComments) {

            break;
        }

        retcode = readFile(fh, (void *)&commenterID, sizeof(commenterID), 0, 0, ROOT_ID);

        // if nothing was read, it must not have any comments so just leave the loop
        if (retcode != 0 ) {

            break;
        }

        retcode = readFile(fh, (void *)&commentSize, sizeof(commentSize), 0, &count, ROOT_ID);
        if (retcode != 0) {

            printf("Error reading comment's size\n");
            _terminate(-1);
        }

        retcode = readFile(fh, comment, commentSize, 0, &count, ROOT_ID);

        if (retcode != 0 && retcode != ERROR_EOF) {

            printf("Error reading post's text\n");
            _terminate(-1);
        }

        commentSize = count;

        sprintf(filename, "$x.user", commenterID);

        fh2 = openFile(filename, ROOT_ID);

        if ( fh2 >= 0 ) {

            retcode = readFile(fh2, (void *)&commenterNameLen, sizeof(commenterNameLen), 8, &count, ROOT_ID);

            if ( retcode < 0  ) {

                printf("Error reading commenter name length\n");
                _terminate(-1);

            }

            retcode = readFile(fh2, commenter, commenterNameLen, 0, &count, ROOT_ID);

            if (retcode < 0 && retcode != ERROR_EOF ) {

                printf("Error reading commenter name\n");
                _terminate(-1);

            }

            closeFile(fh2);

        }
        else {

            strcpy(commenter, "anonymous");
            commenterNameLen = strlen(commenter);

        }

        commentCount++;

        memcpy(*postMessage+messageOffset, &commentCount, sizeof(commentCount));
        messageOffset+=sizeof(commentCount);

        memcpy(*postMessage+messageOffset, &commenterNameLen, sizeof(count));
        messageOffset+=sizeof(count);

        memcpy( *postMessage+messageOffset,commenter, commenterNameLen );
        messageOffset+=commenterNameLen;

        memcpy( *postMessage+messageOffset, &commentSize, sizeof(commentSize) );
        messageOffset+=sizeof(commentSize);

        memcpy( *postMessage+messageOffset, comment, commentSize );
        messageOffset+=commentSize;        

    } // while (1)

    *messageSize = messageOffset;

    closeFile(fh);
    return 0;
}




