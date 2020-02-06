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
#ifndef USER_H
#define USER_H 

#include "libcgc.h"
#include "cgc_stdint.h"

#define MAX_USERS (128)

#define PIN_LEN (5)
#define ACCESS_CODE_LEN (31)
typedef struct _user {
	char Username[32];
	char FirstName[32];
	char LastName[32];
	char Pin[PIN_LEN+1];
	char AccessCode[ACCESS_CODE_LEN+1];
} User, *pUser;

uint8_t cgc_FindUsername(char *Username);
int8_t cgc_FindAvailableUser(void);
uint8_t cgc_AddUser(void);
uint8_t cgc_DelUser(void);

#endif
