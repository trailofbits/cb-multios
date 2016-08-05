/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, / of charge, to any person obtaining a copy
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
#include "stdio.h"
#include "string.h"
#include "input.h"
#include "malloc.h"



int receiveMessage( void *message ) {

unsigned int messageType;
unsigned char field_len;
int retcode;
newUserMessageType *newUser;
loginMessageType *loginUser;
feedRequestMessageType *newFeedRequest;
newPostMessageType *newPost;
requestPostMessageType *requestPost;
addCommentMessageType *newComment;

	if (receive_bytes((char *)&messageType, sizeof(messageType)) == -1)  {

		return -1;
	}

	switch (messageType) {

		case 0xa0:  // add user

			newUser = message;

			if ( newUser == 0 ) {

				_terminate(-1);

			}

			receive_bytes((char *)&field_len, 1);
			receive_bytes(newUser->name, field_len);
			newUser->name[field_len] = 0;

			receive_bytes((char *)&field_len, 1);
			receive_bytes(newUser->password, field_len);
			newUser->password[field_len] = 0;

			receive_bytes((char *)&field_len, 1);
			receive_bytes(newUser->fullname, field_len);
			newUser->fullname[field_len] = 0;

			return(messageType);

			break;

		case 0xb0:  // login user

			loginUser = message;

			if ( loginUser == 0 ) {

				_terminate(-1);

			}

			receive_bytes((char *)&field_len, 1);
			receive_bytes(loginUser->name, field_len);
			loginUser->name[field_len] = 0;

			receive_bytes((char *)&field_len, 1);
			receive_bytes(loginUser->password, field_len);
			loginUser->password[field_len] = 0;
			
			return(messageType);

			break;

		case 0xc0:  // get feed item

			newFeedRequest = message;

			if ( newFeedRequest == 0 ) {

				_terminate(-1);

			}

			receive_bytes((char *)&newFeedRequest->sessionToken, sizeof (newFeedRequest->sessionToken));

			return(messageType);

			break;

		case 0xd0:  // add post

			newPost = message;

			if ( newPost == 0 ) {

				_terminate(-1);

			}

			receive_bytes((void *)&newPost->sessionToken, sizeof(newPost->sessionToken));

			receive_bytes((char *)&field_len, 1);

			receive_bytes(newPost->post, field_len);
			newPost->post[field_len] = 0;
			
			return(messageType);

			break;

		case 0xe0: // add a comment to a post

			newComment = message;

			if ( newComment == 0 ) {

				_terminate(-1);

			}

			receive_bytes((void *)&newComment->postID, sizeof(newComment->postID));
			receive_bytes((void *)&newComment->commenterID, sizeof(newComment->commenterID));
			receive_bytes((char *)&field_len, 1);
			receive_bytes(newComment->comment, field_len);

			newComment->comment[field_len] = 0;

			return (messageType);
			break;

		case 0xf0:  // retrieve specific post from its ID

			requestPost = message;
			
			if ( requestPost  == 0 ) {

				_terminate(-1);

			}

			receive_bytes((char *)&requestPost->postID, sizeof (requestPost->postID));

			return(messageType);

	}

	return 0;

}


int sendResponse( void *message, int length ) {


	if (write(STDOUT, message, length) != 0 ) {

		return -1;
	}
	else {

		return 0;
	}

}

