/*

Author: Debbie Nuttall <debbie@cromulence.com>

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
#ifndef MSLS_APPLICATION_H
#define MSLS_APPLICATION_H

#define APPLICATION_TYPE_LIST_BOARD     0xa0
#define APPLICATION_TYPE_POST_MESSAGE   0xa1
#define APPLICATION_TYPE_DELETE_MESSAGE 0xa2
#define APPLICATION_TYPE_CLEAR_BOARD    0xa3
#define APPLICATION_TYPE_READ_MESSAGE   0xa4 
#define APPLICATION_TYPE_RESPONSE       0xaa

#define APPLICATION_MSG_LENGTH 128
#define APPLICATION_MAX_MESSAGES 64

#pragma pack(push, 1)
typedef struct ApplicationDeleteMsg_s {
  uint8_t msg_num;
} APPLICATION_DELETE_MSG;

typedef struct ApplicationReadMsg_s {
  uint8_t msg_num;
} APPLICATION_READ_MSG;

typedef struct ApplicationPostMsg_s {
  uint8_t message[128];
} APPLICATION_POST_MSG;

typedef struct ApplicationResponseMsg_s {
  uint8_t  message[128];
} APPLICATION_RESPONSE_MSG;
#pragma pack(pop)

void msls_handle_application(SERVER_STATE *state, CLIENT_CONTEXT *connection,  SLS_MESSAGE *msg);
int post_new_message(uint8_t *message);
int delete_message(uint8_t msg_num);
void clear_message_board();
#endif
