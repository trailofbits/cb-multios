
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

#include "filesystem.h"
#include "auth.h"

#ifndef SERVICE_H
#define SERVICE_H

#define USERNAME_LEN 20
#define PASSWORD_LEN 20
#define REALNAME_LEN 30
#define MAXPOST_LEN 128
#define COMMENT_LEN 100
#define LOGINMESSAGE_LEN 40

typedef struct {

	char name[USERNAME_LEN+1];
	char password[PASSWORD_LEN+1];
	char fullname[REALNAME_LEN+1];

} newUserMessageType;

typedef struct {

	unsigned int responseCode;

} responseMessageType;


typedef struct {

	char name[USERNAME_LEN+1];
	char password[PASSWORD_LEN+1];

} loginMessageType;

typedef struct {

	unsigned int sessionToken;
	char message[LOGINMESSAGE_LEN];

} loginResponseMessageType;

typedef struct {

	unsigned int sessionToken;

}  feedRequestMessageType;

typedef struct {

	unsigned int postID;

}  requestPostMessageType;


typedef struct {

	unsigned int postID;
	char fullname[REALNAME_LEN];
	char post[MAXPOST_LEN];
	char comment[COMMENT_LEN];

} feedMessageType;

typedef struct {

	unsigned int sessionToken;
	char post[MAXPOST_LEN];

}  newPostMessageType;

typedef struct {

	unsigned int postID;
	unsigned int commenterID;
	char comment[COMMENT_LEN];

}  addCommentMessageType;


int receiveMessage( void *message );
int sendResponse( void *message, int length );
int savePost(unsigned int nextPostID, unsigned int sessionToken, char *post);
int saveComment(unsigned int postID, unsigned int commenterID, char *comment);
int newFeedPost(unsigned int sessionToken, char **postMessage, int *messageSize );
int retrievePost( unsigned int postID, int includeComments, char **postMessage, int *messageSize);
int sendStickPost( unsigned int postID );


#endif



