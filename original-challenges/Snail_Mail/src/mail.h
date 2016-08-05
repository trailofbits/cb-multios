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

#ifndef MAIL_H
#define MAIL_H 1

#define MAX_SUBJ_LEN 128
#define MAX_BODY_LEN 256

// struct for piece of mail
typedef struct __attribute__((packed))  {
	unsigned short sender;
	unsigned short recipient;
	char subject[MAX_SUBJ_LEN];
	char body[MAX_BODY_LEN];
} mail_t;

/**
 * Initialize the postage and mailboxes.
 */
void setup(void);

/**
 * Process a user's command.
 *
 * @return SUCCESS on success, else -1
 */
short process_cmd(void);

/**
 * Send resulting status of command processing to client
 *
 * @param status_code  The 2 status code bytes to send.
 */
void send_status(char *status_code);


#endif
