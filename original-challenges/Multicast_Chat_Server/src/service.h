/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#define SUBSCRIBE_CMD "/subscribe"
#define OUT_CMD "/out"
#define IN_CMD "/in"
#define AUTH_CMD "/auth"
#define TOKEN_CMD "/token"

#define FLAG_CHANNEL "FLAG"
#define ADMIN_NAME "admin"

#define WRONG_PASSWORD_MESSAGE "Wrong password! Try again.\n"

#define FLAG_PAGE 0x4347C000

#define ALL_MESSAGES "ALL"

#define MAX_NUM_SIZE 12
#define MESSAGE_SIZE 100
#define MAX_MESSAGE_NUM 100

typedef struct {
 		char* type;
 		char* channel;
 		char* token;
 		char* arguments;
 } Request;