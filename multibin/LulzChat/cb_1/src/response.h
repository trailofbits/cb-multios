/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RESPONSE_H
#define RESPONSE_H

#include "message.h"
#include "user.h"
#include "msg_queue.h"
#include "packet.h"

#define MAX_USERNAME_LEN 64
#define MAX_PASSWORD_LEN 64

#define STATUS_OK     0
#define STATUS_BAD    400
#define STATUS_DENIED 403
#define STATUS_FAIL   404
#define STATUS_EXISTS 409

typedef struct response {
  int status_code;
  unsigned int data_len;
  char *data;
} response_t;

/* Server-side */
void send_response(response_t *, enum cmd_t);
void send_register_res(int, user_t *);
void send_login_res(int, user_t *);
void send_list_res(int, msg_queue, int);
void send_view_res(int, message_t *);
void send_send_res(int);
void send_delete_res(int, int);

/* Client-side */
int handle_response(enum cmd_t, response_t *);

#endif
