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
#ifndef COMMS_H
#define COMMS_H 1
#include "table.h"

#define MASTER_TID 0
#define T_READ_FD(t_id) 	(((t_id * 2) + 3) + 1)
#define T_WRITE_FD(t_id) 	((t_id * 2) + 3)

#define T_STDIN 	T_READ_FD(TABLE_ID)
#define T_STDOUT	T_WRITE_FD(MASTER_TID)

// CMD values for table cbs
static const char T_CMD_SEAT_CUST[4] 			= {'\x5E','\xEE','\x5E','\xEE'};
static const char T_CMD_TAKE_ORDER[4] 			= {'\x04','\xDE','\x40','\x01'};
static const char T_CMD_DELIVER_ORDER[4] 		= {'\xDE','\x11','\x4E','\x40'};
static const char T_CMD_TABLE_SIZE[4] 			= {'\x51','\x4E','\x51','\x4E'};
static const char T_CMD_TABLE_STATUS[4] 		= {'\x51','\x3E','\x51','\x3E'};
static const char T_CMD_TABLE_CLEAN_SET[4]		= {'\xC1','\xEA','\x45','\x37'};
static const char T_CMD_QUIT[4] 				= {'\x0F','\xF0','\xFF','\x0F'};

static const char STATUS_OK[2] 		= {'\x04','\x04'};
static const char STATUS_ERR[2] 	= {'\x44','\xEE'};
static const char STATUS_QUIT[2]	= {'\x44','\x44'};

static const char STR_TERM[2]			= {'\x01','\0'};

/**
 * Send resulting status of command processing to client
 *
 * @param status_code  The 2 status code bytes to send.
 */
void send_status(const char *status_code);

/**
 * Process a user's command.
 *
 * @return SUCCESS on success, else -1
 */
short process_cmd(void);

#endif