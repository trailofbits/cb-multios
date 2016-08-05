/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#ifndef IO_H
#define IO_H

#include <libcgc.h>
#include "stdint.h"

#define CMD_ADD_USER              (0)
#define CMD_DEL_USER              (1)
#define CMD_ADD_DEVICE            (2)
#define CMD_DEL_DEVICE            (3)
#define CMD_POWER_OFF             (4)
#define CMD_GRANT_ACCESS          (5)
#define CMD_UPDATE_DEVICE         (6)
#define CMD_ADD_DEVICE_TO_ALARM   (7)
#define CMD_LIST_ALARM_CODES      (8)

#define RESP_INVALID_CMD                 (0)
#define RESP_MAX_USERS                   (1)
#define RESP_ADD_USER_FAILED             (2)
#define RESP_SUCCESS                     (3)
#define RESP_DEL_USER_FAILED             (4)
#define RESP_ADD_DEVICE_FAILED           (5)
#define RESP_DEL_DEVICE_FAILED           (6)
#define RESP_GRANT_FAILED                (7)
#define RESP_UPDATE_DEVICE_FAILED        (8)
#define RESP_ADD_DEVICE_TO_ALARM_FAILED  (9)
#define RESP_ALARM_ON                   (10)
#define RESP_ALARM_OFF                  (11)
#define RESP_LIST_ALARM_CODES           (12)

size_t ReadBytes(unsigned char *Buf, size_t Max);
size_t SendBytes(unsigned char *Buf, size_t Max);
uint8_t SendResp(uint8_t Code, unsigned char *Data);
uint8_t RecvCommand();

#endif

