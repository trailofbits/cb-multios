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

#ifndef REQUEST_H
#define REQUEST_H

#include "user.h"
#include "message.h"
#include "packet.h"

typedef struct register_req {
  char username[MAX_USERNAME_LEN];
  char password[MAX_PASSWORD_LEN];
  char password_confirm[MAX_PASSWORD_LEN];
} register_req_t;

typedef struct login_req {
  char username[MAX_USERNAME_LEN];
  char password[MAX_PASSWORD_LEN];
} login_req_t;

typedef struct logout_req {
  unsigned short user_id;
  unsigned int auth_code;
} logout_req_t;

typedef struct list_req {
  unsigned short user_id;
  unsigned int auth_code;
} list_req_t;

typedef struct view_req {
  unsigned short user_id;
  unsigned int auth_code;
  unsigned int message_id;
} view_req_t;

typedef struct send_req {
  unsigned short user_id;
  unsigned int auth_code;
  char username[MAX_USERNAME_LEN];
  message_t *msg;
} send_req_t;

typedef struct delete_req {
  unsigned short user_id;
  unsigned int auth_code;
  unsigned int message_id;
} delete_req_t;

typedef struct quit_req {
  int code;
} quit_req_t;

/* Server-side */

/* Client-side */
void send_request(void *, enum cmd_t);

#endif
