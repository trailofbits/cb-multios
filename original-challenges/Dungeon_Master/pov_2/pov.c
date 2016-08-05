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
   negotiate_type1(0xfafafafa, 0xfafafafa, 5);
   //*** delay
   delay(100);
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
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x4d\x65\x6e\x75\x0a";
      read_00000_ptr += data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 5);
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
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
         "\x2d\x2d\x2d\x2d\x2d\x0a";
      read_00001_ptr += data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 6);
      free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 13;
      read_00002 = (unsigned char*)malloc(read_00002_len);
      int read_00002_res = length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read assign to var "play" from pcre: Play game: (.*)

      static char read_00002_regex[] = 
         "\x50\x6c\x61\x79\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("play", read_00002, read_00002_len - read_00002_ptr, read_00002_regex, 1);
      free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 20;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read assign to var "instructions" from pcre: Get instructions: (.*)

      static char read_00003_regex[] = 
         "\x47\x65\x74\x20\x69\x6e\x73\x74\x72\x75\x63\x74\x69\x6f\x6e\x73"
         "\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("instructions", read_00003, read_00003_len - read_00003_ptr, read_00003_regex, 1);
      free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 15;
      read_00004 = (unsigned char*)malloc(read_00004_len);
      int read_00004_res = length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      //**** read assign to var "highScore" from pcre: High Scores: (.*)

      static char read_00004_regex[] = 
         "\x48\x69\x67\x68\x20\x53\x63\x6f\x72\x65\x73\x3a\x20\x28\x2e\x2a"
         "\x29\x0a";
      assign_from_pcre("highScore", read_00004, read_00004_len - read_00004_ptr, read_00004_regex, 1);
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** length read
      read_00005_len = 13;
      read_00005 = (unsigned char*)malloc(read_00005_len);
      int read_00005_res = length_read(0, read_00005, read_00005_len);
      if (read_00005_res) {} //silence unused variable warning
      //**** read assign to var "quit" from pcre: Quit game: (.*)

      static char read_00005_regex[] = 
         "\x51\x75\x69\x74\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("quit", read_00005, read_00005_len - read_00005_ptr, read_00005_regex, 1);
      free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_var("instructions", write_00000, &write_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x0a";
      static unsigned int write_00001_00000_len = 1;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 1);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x47\x61\x6d\x65\x20\x6d\x6f\x76\x65\x73\x0a";
      read_00006_ptr += data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 11);
      free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** delimited read
      static unsigned char read_00007_delim[] = 
         "\x0a";
      read_00007 = NULL;
      read_00007_len = 0;
      int read_00007_res = delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 1);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
      read_00007_ptr += data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 11);
      free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** length read
      read_00008_len = 8;
      read_00008 = (unsigned char*)malloc(read_00008_len);
      int read_00008_res = length_read(0, read_00008, read_00008_len);
      if (read_00008_res) {} //silence unused variable warning
      //**** read assign to var "left" from pcre: Left: (.*)

      static char read_00008_regex[] = 
         "\x4c\x65\x66\x74\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("left", read_00008, read_00008_len - read_00008_ptr, read_00008_regex, 1);
      free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** length read
      read_00009_len = 9;
      read_00009 = (unsigned char*)malloc(read_00009_len);
      int read_00009_res = length_read(0, read_00009, read_00009_len);
      if (read_00009_res) {} //silence unused variable warning
      //**** read assign to var "right" from pcre: Right: (.*)

      static char read_00009_regex[] = 
         "\x52\x69\x67\x68\x74\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("right", read_00009, read_00009_len - read_00009_ptr, read_00009_regex, 1);
      free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** length read
      read_00010_len = 8;
      read_00010 = (unsigned char*)malloc(read_00010_len);
      int read_00010_res = length_read(0, read_00010, read_00010_len);
      if (read_00010_res) {} //silence unused variable warning
      //**** read assign to var "jump" from pcre: Jump: (.*)

      static char read_00010_regex[] = 
         "\x4a\x75\x6d\x70\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("jump", read_00010, read_00010_len - read_00010_ptr, read_00010_regex, 1);
      free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** length read
      read_00011_len = 13;
      read_00011 = (unsigned char*)malloc(read_00011_len);
      int read_00011_res = length_read(0, read_00011, read_00011_len);
      if (read_00011_res) {} //silence unused variable warning
      //**** read assign to var "jumpleft" from pcre: Jump Left: (.*)

      static char read_00011_regex[] = 
         "\x4a\x75\x6d\x70\x20\x4c\x65\x66\x74\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("jumpleft", read_00011, read_00011_len - read_00011_ptr, read_00011_regex, 1);
      free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** length read
      read_00012_len = 14;
      read_00012 = (unsigned char*)malloc(read_00012_len);
      int read_00012_res = length_read(0, read_00012, read_00012_len);
      if (read_00012_res) {} //silence unused variable warning
      //**** read assign to var "jumpright" from pcre: Jump Right: (.*)

      static char read_00012_regex[] = 
         "\x4a\x75\x6d\x70\x20\x52\x69\x67\x68\x74\x3a\x20\x28\x2e\x2a\x29"
         "\x0a";
      assign_from_pcre("jumpright", read_00012, read_00012_len - read_00012_ptr, read_00012_regex, 1);
      free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** length read
      read_00013_len = 8;
      read_00013 = (unsigned char*)malloc(read_00013_len);
      int read_00013_res = length_read(0, read_00013, read_00013_len);
      if (read_00013_res) {} //silence unused variable warning
      //**** read assign to var "wait" from pcre: Wait: (.*)

      static char read_00013_regex[] = 
         "\x57\x61\x69\x74\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("wait", read_00013, read_00013_len - read_00013_ptr, read_00013_regex, 1);
      free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** length read
      read_00014_len = 13;
      read_00014 = (unsigned char*)malloc(read_00014_len);
      int read_00014_res = length_read(0, read_00014, read_00014_len);
      if (read_00014_res) {} //silence unused variable warning
      //**** read assign to var "quit" from pcre: Quit game: (.*)

      static char read_00014_regex[] = 
         "\x51\x75\x69\x74\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("quit", read_00014, read_00014_len - read_00014_ptr, read_00014_regex, 1);
      free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** delimited read
      static unsigned char read_00015_delim[] = 
         "\x0a";
      read_00015 = NULL;
      read_00015_len = 0;
      int read_00015_res = delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 1);
      if (read_00015_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00015_00000[] = 
         "\x4d\x65\x6e\x75\x0a";
      read_00015_ptr += data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 5);
      free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** delimited read
      static unsigned char read_00016_delim[] = 
         "\x0a";
      read_00016 = NULL;
      read_00016_len = 0;
      int read_00016_res = delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 1);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x2d\x2d\x2d\x2d\x2d\x0a";
      read_00016_ptr += data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 6);
      free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** length read
      read_00017_len = 13;
      read_00017 = (unsigned char*)malloc(read_00017_len);
      int read_00017_res = length_read(0, read_00017, read_00017_len);
      if (read_00017_res) {} //silence unused variable warning
      //**** read assign to var "play" from pcre: Play game: (.*)

      static char read_00017_regex[] = 
         "\x50\x6c\x61\x79\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("play", read_00017, read_00017_len - read_00017_ptr, read_00017_regex, 1);
      free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 20;
      read_00018 = (unsigned char*)malloc(read_00018_len);
      int read_00018_res = length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      //**** read assign to var "instructions" from pcre: Get instructions: (.*)

      static char read_00018_regex[] = 
         "\x47\x65\x74\x20\x69\x6e\x73\x74\x72\x75\x63\x74\x69\x6f\x6e\x73"
         "\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("instructions", read_00018, read_00018_len - read_00018_ptr, read_00018_regex, 1);
      free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** length read
      read_00019_len = 15;
      read_00019 = (unsigned char*)malloc(read_00019_len);
      int read_00019_res = length_read(0, read_00019, read_00019_len);
      if (read_00019_res) {} //silence unused variable warning
      //**** read assign to var "highScore" from pcre: High Scores: (.*)

      static char read_00019_regex[] = 
         "\x48\x69\x67\x68\x20\x53\x63\x6f\x72\x65\x73\x3a\x20\x28\x2e\x2a"
         "\x29\x0a";
      assign_from_pcre("highScore", read_00019, read_00019_len - read_00019_ptr, read_00019_regex, 1);
      free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** length read
      read_00020_len = 13;
      read_00020 = (unsigned char*)malloc(read_00020_len);
      int read_00020_res = length_read(0, read_00020, read_00020_len);
      if (read_00020_res) {} //silence unused variable warning
      //**** read assign to var "quit" from pcre: Quit game: (.*)

      static char read_00020_regex[] = 
         "\x51\x75\x69\x74\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("quit", read_00020, read_00020_len - read_00020_ptr, read_00020_regex, 1);
      free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_var("play", write_00002, &write_00002_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x0a";
      static unsigned int write_00003_00000_len = 1;
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
      write_00004 = append_var("right", write_00004, &write_00004_len);
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
      //*** writing data
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = append_var("right", write_00006, &write_00006_len);
      if (write_00006_len > 0) {
         transmit_all(1, write_00006, write_00006_len);
      }
      free(write_00006);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x0a";
      static unsigned int write_00007_00000_len = 1;
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
      write_00008 = append_var("right", write_00008, &write_00008_len);
      if (write_00008_len > 0) {
         transmit_all(1, write_00008, write_00008_len);
      }
      free(write_00008);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x0a";
      static unsigned int write_00009_00000_len = 1;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         transmit_all(1, write_00009, write_00009_len);
      }
      free(write_00009);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = append_var("right", write_00010, &write_00010_len);
      if (write_00010_len > 0) {
         transmit_all(1, write_00010, write_00010_len);
      }
      free(write_00010);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x0a";
      static unsigned int write_00011_00000_len = 1;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         transmit_all(1, write_00011, write_00011_len);
      }
      free(write_00011);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = append_var("right", write_00012, &write_00012_len);
      if (write_00012_len > 0) {
         transmit_all(1, write_00012, write_00012_len);
      }
      free(write_00012);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x0a";
      static unsigned int write_00013_00000_len = 1;
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
      write_00014 = append_var("jumpright", write_00014, &write_00014_len);
      if (write_00014_len > 0) {
         transmit_all(1, write_00014, write_00014_len);
      }
      free(write_00014);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x0a";
      static unsigned int write_00015_00000_len = 1;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         transmit_all(1, write_00015, write_00015_len);
      }
      free(write_00015);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = append_var("jumpright", write_00016, &write_00016_len);
      if (write_00016_len > 0) {
         transmit_all(1, write_00016, write_00016_len);
      }
      free(write_00016);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x0a";
      static unsigned int write_00017_00000_len = 1;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         transmit_all(1, write_00017, write_00017_len);
      }
      free(write_00017);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = append_var("jumpright", write_00018, &write_00018_len);
      if (write_00018_len > 0) {
         transmit_all(1, write_00018, write_00018_len);
      }
      free(write_00018);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x0a";
      static unsigned int write_00019_00000_len = 1;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         transmit_all(1, write_00019, write_00019_len);
      }
      free(write_00019);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = append_var("jumpright", write_00020, &write_00020_len);
      if (write_00020_len > 0) {
         transmit_all(1, write_00020, write_00020_len);
      }
      free(write_00020);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\x0a";
      static unsigned int write_00021_00000_len = 1;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         transmit_all(1, write_00021, write_00021_len);
      }
      free(write_00021);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = append_var("wait", write_00022, &write_00022_len);
      if (write_00022_len > 0) {
         transmit_all(1, write_00022, write_00022_len);
      }
      free(write_00022);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\x0a";
      static unsigned int write_00023_00000_len = 1;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         transmit_all(1, write_00023, write_00023_len);
      }
      free(write_00023);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = append_var("wait", write_00024, &write_00024_len);
      if (write_00024_len > 0) {
         transmit_all(1, write_00024, write_00024_len);
      }
      free(write_00024);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x0a";
      static unsigned int write_00025_00000_len = 1;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         transmit_all(1, write_00025, write_00025_len);
      }
      free(write_00025);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = append_var("wait", write_00026, &write_00026_len);
      if (write_00026_len > 0) {
         transmit_all(1, write_00026, write_00026_len);
      }
      free(write_00026);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x0a";
      static unsigned int write_00027_00000_len = 1;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         transmit_all(1, write_00027, write_00027_len);
      }
      free(write_00027);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = append_var("wait", write_00028, &write_00028_len);
      if (write_00028_len > 0) {
         transmit_all(1, write_00028, write_00028_len);
      }
      free(write_00028);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\x0a";
      static unsigned int write_00029_00000_len = 1;
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = append_buf(write_00029, &write_00029_len, write_00029_00000, write_00029_00000_len);
      if (write_00029_len > 0) {
         transmit_all(1, write_00029, write_00029_len);
      }
      free(write_00029);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = append_var("wait", write_00030, &write_00030_len);
      if (write_00030_len > 0) {
         transmit_all(1, write_00030, write_00030_len);
      }
      free(write_00030);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x0a";
      static unsigned int write_00031_00000_len = 1;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         transmit_all(1, write_00031, write_00031_len);
      }
      free(write_00031);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = append_var("wait", write_00032, &write_00032_len);
      if (write_00032_len > 0) {
         transmit_all(1, write_00032, write_00032_len);
      }
      free(write_00032);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x0a";
      static unsigned int write_00033_00000_len = 1;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         transmit_all(1, write_00033, write_00033_len);
      }
      free(write_00033);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = append_var("wait", write_00034, &write_00034_len);
      if (write_00034_len > 0) {
         transmit_all(1, write_00034, write_00034_len);
      }
      free(write_00034);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\x0a";
      static unsigned int write_00035_00000_len = 1;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         transmit_all(1, write_00035, write_00035_len);
      }
      free(write_00035);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = append_var("wait", write_00036, &write_00036_len);
      if (write_00036_len > 0) {
         transmit_all(1, write_00036, write_00036_len);
      }
      free(write_00036);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\x0a";
      static unsigned int write_00037_00000_len = 1;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         transmit_all(1, write_00037, write_00037_len);
      }
      free(write_00037);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = append_var("wait", write_00038, &write_00038_len);
      if (write_00038_len > 0) {
         transmit_all(1, write_00038, write_00038_len);
      }
      free(write_00038);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x0a";
      static unsigned int write_00039_00000_len = 1;
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = append_buf(write_00039, &write_00039_len, write_00039_00000, write_00039_00000_len);
      if (write_00039_len > 0) {
         transmit_all(1, write_00039, write_00039_len);
      }
      free(write_00039);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = append_var("wait", write_00040, &write_00040_len);
      if (write_00040_len > 0) {
         transmit_all(1, write_00040, write_00040_len);
      }
      free(write_00040);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x0a";
      static unsigned int write_00041_00000_len = 1;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         transmit_all(1, write_00041, write_00041_len);
      }
      free(write_00041);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = append_var("wait", write_00042, &write_00042_len);
      if (write_00042_len > 0) {
         transmit_all(1, write_00042, write_00042_len);
      }
      free(write_00042);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x0a";
      static unsigned int write_00043_00000_len = 1;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         transmit_all(1, write_00043, write_00043_len);
      }
      free(write_00043);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = append_var("wait", write_00044, &write_00044_len);
      if (write_00044_len > 0) {
         transmit_all(1, write_00044, write_00044_len);
      }
      free(write_00044);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\x0a";
      static unsigned int write_00045_00000_len = 1;
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = append_buf(write_00045, &write_00045_len, write_00045_00000, write_00045_00000_len);
      if (write_00045_len > 0) {
         transmit_all(1, write_00045, write_00045_len);
      }
      free(write_00045);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = append_var("wait", write_00046, &write_00046_len);
      if (write_00046_len > 0) {
         transmit_all(1, write_00046, write_00046_len);
      }
      free(write_00046);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\x0a";
      static unsigned int write_00047_00000_len = 1;
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = append_buf(write_00047, &write_00047_len, write_00047_00000, write_00047_00000_len);
      if (write_00047_len > 0) {
         transmit_all(1, write_00047, write_00047_len);
      }
      free(write_00047);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = append_var("wait", write_00048, &write_00048_len);
      if (write_00048_len > 0) {
         transmit_all(1, write_00048, write_00048_len);
      }
      free(write_00048);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x0a";
      static unsigned int write_00049_00000_len = 1;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         transmit_all(1, write_00049, write_00049_len);
      }
      free(write_00049);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = append_var("wait", write_00050, &write_00050_len);
      if (write_00050_len > 0) {
         transmit_all(1, write_00050, write_00050_len);
      }
      free(write_00050);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x0a";
      static unsigned int write_00051_00000_len = 1;
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = append_buf(write_00051, &write_00051_len, write_00051_00000, write_00051_00000_len);
      if (write_00051_len > 0) {
         transmit_all(1, write_00051, write_00051_len);
      }
      free(write_00051);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = append_var("wait", write_00052, &write_00052_len);
      if (write_00052_len > 0) {
         transmit_all(1, write_00052, write_00052_len);
      }
      free(write_00052);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\x0a";
      static unsigned int write_00053_00000_len = 1;
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = append_buf(write_00053, &write_00053_len, write_00053_00000, write_00053_00000_len);
      if (write_00053_len > 0) {
         transmit_all(1, write_00053, write_00053_len);
      }
      free(write_00053);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = append_var("wait", write_00054, &write_00054_len);
      if (write_00054_len > 0) {
         transmit_all(1, write_00054, write_00054_len);
      }
      free(write_00054);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x0a";
      static unsigned int write_00055_00000_len = 1;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         transmit_all(1, write_00055, write_00055_len);
      }
      free(write_00055);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = append_var("wait", write_00056, &write_00056_len);
      if (write_00056_len > 0) {
         transmit_all(1, write_00056, write_00056_len);
      }
      free(write_00056);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x0a";
      static unsigned int write_00057_00000_len = 1;
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = append_buf(write_00057, &write_00057_len, write_00057_00000, write_00057_00000_len);
      if (write_00057_len > 0) {
         transmit_all(1, write_00057, write_00057_len);
      }
      free(write_00057);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = append_var("wait", write_00058, &write_00058_len);
      if (write_00058_len > 0) {
         transmit_all(1, write_00058, write_00058_len);
      }
      free(write_00058);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\x0a";
      static unsigned int write_00059_00000_len = 1;
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = append_buf(write_00059, &write_00059_len, write_00059_00000, write_00059_00000_len);
      if (write_00059_len > 0) {
         transmit_all(1, write_00059, write_00059_len);
      }
      free(write_00059);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = append_var("wait", write_00060, &write_00060_len);
      if (write_00060_len > 0) {
         transmit_all(1, write_00060, write_00060_len);
      }
      free(write_00060);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\x0a";
      static unsigned int write_00061_00000_len = 1;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         transmit_all(1, write_00061, write_00061_len);
      }
      free(write_00061);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = append_var("wait", write_00062, &write_00062_len);
      if (write_00062_len > 0) {
         transmit_all(1, write_00062, write_00062_len);
      }
      free(write_00062);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x0a";
      static unsigned int write_00063_00000_len = 1;
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = append_buf(write_00063, &write_00063_len, write_00063_00000, write_00063_00000_len);
      if (write_00063_len > 0) {
         transmit_all(1, write_00063, write_00063_len);
      }
      free(write_00063);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = append_var("wait", write_00064, &write_00064_len);
      if (write_00064_len > 0) {
         transmit_all(1, write_00064, write_00064_len);
      }
      free(write_00064);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x0a";
      static unsigned int write_00065_00000_len = 1;
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = append_buf(write_00065, &write_00065_len, write_00065_00000, write_00065_00000_len);
      if (write_00065_len > 0) {
         transmit_all(1, write_00065, write_00065_len);
      }
      free(write_00065);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = append_var("wait", write_00066, &write_00066_len);
      if (write_00066_len > 0) {
         transmit_all(1, write_00066, write_00066_len);
      }
      free(write_00066);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\x0a";
      static unsigned int write_00067_00000_len = 1;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         transmit_all(1, write_00067, write_00067_len);
      }
      free(write_00067);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = append_var("wait", write_00068, &write_00068_len);
      if (write_00068_len > 0) {
         transmit_all(1, write_00068, write_00068_len);
      }
      free(write_00068);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x0a";
      static unsigned int write_00069_00000_len = 1;
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = append_buf(write_00069, &write_00069_len, write_00069_00000, write_00069_00000_len);
      if (write_00069_len > 0) {
         transmit_all(1, write_00069, write_00069_len);
      }
      free(write_00069);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = append_var("wait", write_00070, &write_00070_len);
      if (write_00070_len > 0) {
         transmit_all(1, write_00070, write_00070_len);
      }
      free(write_00070);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x0a";
      static unsigned int write_00071_00000_len = 1;
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = append_buf(write_00071, &write_00071_len, write_00071_00000, write_00071_00000_len);
      if (write_00071_len > 0) {
         transmit_all(1, write_00071, write_00071_len);
      }
      free(write_00071);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = append_var("wait", write_00072, &write_00072_len);
      if (write_00072_len > 0) {
         transmit_all(1, write_00072, write_00072_len);
      }
      free(write_00072);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\x0a";
      static unsigned int write_00073_00000_len = 1;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         transmit_all(1, write_00073, write_00073_len);
      }
      free(write_00073);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = append_var("wait", write_00074, &write_00074_len);
      if (write_00074_len > 0) {
         transmit_all(1, write_00074, write_00074_len);
      }
      free(write_00074);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\x0a";
      static unsigned int write_00075_00000_len = 1;
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = append_buf(write_00075, &write_00075_len, write_00075_00000, write_00075_00000_len);
      if (write_00075_len > 0) {
         transmit_all(1, write_00075, write_00075_len);
      }
      free(write_00075);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = append_var("wait", write_00076, &write_00076_len);
      if (write_00076_len > 0) {
         transmit_all(1, write_00076, write_00076_len);
      }
      free(write_00076);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x0a";
      static unsigned int write_00077_00000_len = 1;
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = append_buf(write_00077, &write_00077_len, write_00077_00000, write_00077_00000_len);
      if (write_00077_len > 0) {
         transmit_all(1, write_00077, write_00077_len);
      }
      free(write_00077);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = append_var("wait", write_00078, &write_00078_len);
      if (write_00078_len > 0) {
         transmit_all(1, write_00078, write_00078_len);
      }
      free(write_00078);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x0a";
      static unsigned int write_00079_00000_len = 1;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         transmit_all(1, write_00079, write_00079_len);
      }
      free(write_00079);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = append_var("wait", write_00080, &write_00080_len);
      if (write_00080_len > 0) {
         transmit_all(1, write_00080, write_00080_len);
      }
      free(write_00080);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\x0a";
      static unsigned int write_00081_00000_len = 1;
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = append_buf(write_00081, &write_00081_len, write_00081_00000, write_00081_00000_len);
      if (write_00081_len > 0) {
         transmit_all(1, write_00081, write_00081_len);
      }
      free(write_00081);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = append_var("wait", write_00082, &write_00082_len);
      if (write_00082_len > 0) {
         transmit_all(1, write_00082, write_00082_len);
      }
      free(write_00082);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x0a";
      static unsigned int write_00083_00000_len = 1;
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = append_buf(write_00083, &write_00083_len, write_00083_00000, write_00083_00000_len);
      if (write_00083_len > 0) {
         transmit_all(1, write_00083, write_00083_len);
      }
      free(write_00083);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = append_var("wait", write_00084, &write_00084_len);
      if (write_00084_len > 0) {
         transmit_all(1, write_00084, write_00084_len);
      }
      free(write_00084);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x0a";
      static unsigned int write_00085_00000_len = 1;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         transmit_all(1, write_00085, write_00085_len);
      }
      free(write_00085);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = append_var("wait", write_00086, &write_00086_len);
      if (write_00086_len > 0) {
         transmit_all(1, write_00086, write_00086_len);
      }
      free(write_00086);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\x0a";
      static unsigned int write_00087_00000_len = 1;
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = append_buf(write_00087, &write_00087_len, write_00087_00000, write_00087_00000_len);
      if (write_00087_len > 0) {
         transmit_all(1, write_00087, write_00087_len);
      }
      free(write_00087);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = append_var("wait", write_00088, &write_00088_len);
      if (write_00088_len > 0) {
         transmit_all(1, write_00088, write_00088_len);
      }
      free(write_00088);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\x0a";
      static unsigned int write_00089_00000_len = 1;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         transmit_all(1, write_00089, write_00089_len);
      }
      free(write_00089);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = append_var("wait", write_00090, &write_00090_len);
      if (write_00090_len > 0) {
         transmit_all(1, write_00090, write_00090_len);
      }
      free(write_00090);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x0a";
      static unsigned int write_00091_00000_len = 1;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         transmit_all(1, write_00091, write_00091_len);
      }
      free(write_00091);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = append_var("wait", write_00092, &write_00092_len);
      if (write_00092_len > 0) {
         transmit_all(1, write_00092, write_00092_len);
      }
      free(write_00092);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x0a";
      static unsigned int write_00093_00000_len = 1;
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = append_buf(write_00093, &write_00093_len, write_00093_00000, write_00093_00000_len);
      if (write_00093_len > 0) {
         transmit_all(1, write_00093, write_00093_len);
      }
      free(write_00093);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = append_var("wait", write_00094, &write_00094_len);
      if (write_00094_len > 0) {
         transmit_all(1, write_00094, write_00094_len);
      }
      free(write_00094);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\x0a";
      static unsigned int write_00095_00000_len = 1;
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = append_buf(write_00095, &write_00095_len, write_00095_00000, write_00095_00000_len);
      if (write_00095_len > 0) {
         transmit_all(1, write_00095, write_00095_len);
      }
      free(write_00095);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = append_var("right", write_00096, &write_00096_len);
      if (write_00096_len > 0) {
         transmit_all(1, write_00096, write_00096_len);
      }
      free(write_00096);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x0a";
      static unsigned int write_00097_00000_len = 1;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         transmit_all(1, write_00097, write_00097_len);
      }
      free(write_00097);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = append_var("right", write_00098, &write_00098_len);
      if (write_00098_len > 0) {
         transmit_all(1, write_00098, write_00098_len);
      }
      free(write_00098);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x0a";
      static unsigned int write_00099_00000_len = 1;
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = append_buf(write_00099, &write_00099_len, write_00099_00000, write_00099_00000_len);
      if (write_00099_len > 0) {
         transmit_all(1, write_00099, write_00099_len);
      }
      free(write_00099);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = append_var("right", write_00100, &write_00100_len);
      if (write_00100_len > 0) {
         transmit_all(1, write_00100, write_00100_len);
      }
      free(write_00100);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\x0a";
      static unsigned int write_00101_00000_len = 1;
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = append_buf(write_00101, &write_00101_len, write_00101_00000, write_00101_00000_len);
      if (write_00101_len > 0) {
         transmit_all(1, write_00101, write_00101_len);
      }
      free(write_00101);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = append_var("right", write_00102, &write_00102_len);
      if (write_00102_len > 0) {
         transmit_all(1, write_00102, write_00102_len);
      }
      free(write_00102);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\x0a";
      static unsigned int write_00103_00000_len = 1;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         transmit_all(1, write_00103, write_00103_len);
      }
      free(write_00103);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = append_var("right", write_00104, &write_00104_len);
      if (write_00104_len > 0) {
         transmit_all(1, write_00104, write_00104_len);
      }
      free(write_00104);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x0a";
      static unsigned int write_00105_00000_len = 1;
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = append_buf(write_00105, &write_00105_len, write_00105_00000, write_00105_00000_len);
      if (write_00105_len > 0) {
         transmit_all(1, write_00105, write_00105_len);
      }
      free(write_00105);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = append_var("right", write_00106, &write_00106_len);
      if (write_00106_len > 0) {
         transmit_all(1, write_00106, write_00106_len);
      }
      free(write_00106);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x0a";
      static unsigned int write_00107_00000_len = 1;
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = append_buf(write_00107, &write_00107_len, write_00107_00000, write_00107_00000_len);
      if (write_00107_len > 0) {
         transmit_all(1, write_00107, write_00107_len);
      }
      free(write_00107);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = append_var("right", write_00108, &write_00108_len);
      if (write_00108_len > 0) {
         transmit_all(1, write_00108, write_00108_len);
      }
      free(write_00108);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\x0a";
      static unsigned int write_00109_00000_len = 1;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         transmit_all(1, write_00109, write_00109_len);
      }
      free(write_00109);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = append_var("right", write_00110, &write_00110_len);
      if (write_00110_len > 0) {
         transmit_all(1, write_00110, write_00110_len);
      }
      free(write_00110);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x0a";
      static unsigned int write_00111_00000_len = 1;
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = append_buf(write_00111, &write_00111_len, write_00111_00000, write_00111_00000_len);
      if (write_00111_len > 0) {
         transmit_all(1, write_00111, write_00111_len);
      }
      free(write_00111);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = append_var("right", write_00112, &write_00112_len);
      if (write_00112_len > 0) {
         transmit_all(1, write_00112, write_00112_len);
      }
      free(write_00112);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x0a";
      static unsigned int write_00113_00000_len = 1;
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = append_buf(write_00113, &write_00113_len, write_00113_00000, write_00113_00000_len);
      if (write_00113_len > 0) {
         transmit_all(1, write_00113, write_00113_len);
      }
      free(write_00113);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = append_var("right", write_00114, &write_00114_len);
      if (write_00114_len > 0) {
         transmit_all(1, write_00114, write_00114_len);
      }
      free(write_00114);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\x0a";
      static unsigned int write_00115_00000_len = 1;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         transmit_all(1, write_00115, write_00115_len);
      }
      free(write_00115);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = append_var("right", write_00116, &write_00116_len);
      if (write_00116_len > 0) {
         transmit_all(1, write_00116, write_00116_len);
      }
      free(write_00116);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\x0a";
      static unsigned int write_00117_00000_len = 1;
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = append_buf(write_00117, &write_00117_len, write_00117_00000, write_00117_00000_len);
      if (write_00117_len > 0) {
         transmit_all(1, write_00117, write_00117_len);
      }
      free(write_00117);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = append_var("right", write_00118, &write_00118_len);
      if (write_00118_len > 0) {
         transmit_all(1, write_00118, write_00118_len);
      }
      free(write_00118);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x0a";
      static unsigned int write_00119_00000_len = 1;
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = append_buf(write_00119, &write_00119_len, write_00119_00000, write_00119_00000_len);
      if (write_00119_len > 0) {
         transmit_all(1, write_00119, write_00119_len);
      }
      free(write_00119);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = append_var("right", write_00120, &write_00120_len);
      if (write_00120_len > 0) {
         transmit_all(1, write_00120, write_00120_len);
      }
      free(write_00120);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x0a";
      static unsigned int write_00121_00000_len = 1;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         transmit_all(1, write_00121, write_00121_len);
      }
      free(write_00121);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = append_var("jumpleft", write_00122, &write_00122_len);
      if (write_00122_len > 0) {
         transmit_all(1, write_00122, write_00122_len);
      }
      free(write_00122);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\x0a";
      static unsigned int write_00123_00000_len = 1;
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = append_buf(write_00123, &write_00123_len, write_00123_00000, write_00123_00000_len);
      if (write_00123_len > 0) {
         transmit_all(1, write_00123, write_00123_len);
      }
      free(write_00123);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = append_var("left", write_00124, &write_00124_len);
      if (write_00124_len > 0) {
         transmit_all(1, write_00124, write_00124_len);
      }
      free(write_00124);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x0a";
      static unsigned int write_00125_00000_len = 1;
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = append_buf(write_00125, &write_00125_len, write_00125_00000, write_00125_00000_len);
      if (write_00125_len > 0) {
         transmit_all(1, write_00125, write_00125_len);
      }
      free(write_00125);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = append_var("jumpleft", write_00126, &write_00126_len);
      if (write_00126_len > 0) {
         transmit_all(1, write_00126, write_00126_len);
      }
      free(write_00126);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x0a";
      static unsigned int write_00127_00000_len = 1;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         transmit_all(1, write_00127, write_00127_len);
      }
      free(write_00127);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = append_var("left", write_00128, &write_00128_len);
      if (write_00128_len > 0) {
         transmit_all(1, write_00128, write_00128_len);
      }
      free(write_00128);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\x0a";
      static unsigned int write_00129_00000_len = 1;
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = append_buf(write_00129, &write_00129_len, write_00129_00000, write_00129_00000_len);
      if (write_00129_len > 0) {
         transmit_all(1, write_00129, write_00129_len);
      }
      free(write_00129);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = append_var("jumpleft", write_00130, &write_00130_len);
      if (write_00130_len > 0) {
         transmit_all(1, write_00130, write_00130_len);
      }
      free(write_00130);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\x0a";
      static unsigned int write_00131_00000_len = 1;
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = append_buf(write_00131, &write_00131_len, write_00131_00000, write_00131_00000_len);
      if (write_00131_len > 0) {
         transmit_all(1, write_00131, write_00131_len);
      }
      free(write_00131);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = append_var("wait", write_00132, &write_00132_len);
      if (write_00132_len > 0) {
         transmit_all(1, write_00132, write_00132_len);
      }
      free(write_00132);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x0a";
      static unsigned int write_00133_00000_len = 1;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         transmit_all(1, write_00133, write_00133_len);
      }
      free(write_00133);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = append_var("wait", write_00134, &write_00134_len);
      if (write_00134_len > 0) {
         transmit_all(1, write_00134, write_00134_len);
      }
      free(write_00134);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x0a";
      static unsigned int write_00135_00000_len = 1;
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = append_buf(write_00135, &write_00135_len, write_00135_00000, write_00135_00000_len);
      if (write_00135_len > 0) {
         transmit_all(1, write_00135, write_00135_len);
      }
      free(write_00135);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = append_var("wait", write_00136, &write_00136_len);
      if (write_00136_len > 0) {
         transmit_all(1, write_00136, write_00136_len);
      }
      free(write_00136);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\x0a";
      static unsigned int write_00137_00000_len = 1;
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = append_buf(write_00137, &write_00137_len, write_00137_00000, write_00137_00000_len);
      if (write_00137_len > 0) {
         transmit_all(1, write_00137, write_00137_len);
      }
      free(write_00137);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = append_var("wait", write_00138, &write_00138_len);
      if (write_00138_len > 0) {
         transmit_all(1, write_00138, write_00138_len);
      }
      free(write_00138);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x0a";
      static unsigned int write_00139_00000_len = 1;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         transmit_all(1, write_00139, write_00139_len);
      }
      free(write_00139);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = append_var("wait", write_00140, &write_00140_len);
      if (write_00140_len > 0) {
         transmit_all(1, write_00140, write_00140_len);
      }
      free(write_00140);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x0a";
      static unsigned int write_00141_00000_len = 1;
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = append_buf(write_00141, &write_00141_len, write_00141_00000, write_00141_00000_len);
      if (write_00141_len > 0) {
         transmit_all(1, write_00141, write_00141_len);
      }
      free(write_00141);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = append_var("wait", write_00142, &write_00142_len);
      if (write_00142_len > 0) {
         transmit_all(1, write_00142, write_00142_len);
      }
      free(write_00142);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00143_00000[] = 
         "\x0a";
      static unsigned int write_00143_00000_len = 1;
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = append_buf(write_00143, &write_00143_len, write_00143_00000, write_00143_00000_len);
      if (write_00143_len > 0) {
         transmit_all(1, write_00143, write_00143_len);
      }
      free(write_00143);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = append_var("wait", write_00144, &write_00144_len);
      if (write_00144_len > 0) {
         transmit_all(1, write_00144, write_00144_len);
      }
      free(write_00144);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00145_00000[] = 
         "\x0a";
      static unsigned int write_00145_00000_len = 1;
      unsigned char *write_00145 = NULL;
      unsigned int write_00145_len = 0;
      write_00145 = append_buf(write_00145, &write_00145_len, write_00145_00000, write_00145_00000_len);
      if (write_00145_len > 0) {
         transmit_all(1, write_00145, write_00145_len);
      }
      free(write_00145);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = append_var("wait", write_00146, &write_00146_len);
      if (write_00146_len > 0) {
         transmit_all(1, write_00146, write_00146_len);
      }
      free(write_00146);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00147_00000[] = 
         "\x0a";
      static unsigned int write_00147_00000_len = 1;
      unsigned char *write_00147 = NULL;
      unsigned int write_00147_len = 0;
      write_00147 = append_buf(write_00147, &write_00147_len, write_00147_00000, write_00147_00000_len);
      if (write_00147_len > 0) {
         transmit_all(1, write_00147, write_00147_len);
      }
      free(write_00147);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = append_var("wait", write_00148, &write_00148_len);
      if (write_00148_len > 0) {
         transmit_all(1, write_00148, write_00148_len);
      }
      free(write_00148);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00149_00000[] = 
         "\x0a";
      static unsigned int write_00149_00000_len = 1;
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = append_buf(write_00149, &write_00149_len, write_00149_00000, write_00149_00000_len);
      if (write_00149_len > 0) {
         transmit_all(1, write_00149, write_00149_len);
      }
      free(write_00149);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00150 = NULL;
      unsigned int write_00150_len = 0;
      write_00150 = append_var("wait", write_00150, &write_00150_len);
      if (write_00150_len > 0) {
         transmit_all(1, write_00150, write_00150_len);
      }
      free(write_00150);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00151_00000[] = 
         "\x0a";
      static unsigned int write_00151_00000_len = 1;
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = append_buf(write_00151, &write_00151_len, write_00151_00000, write_00151_00000_len);
      if (write_00151_len > 0) {
         transmit_all(1, write_00151, write_00151_len);
      }
      free(write_00151);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00152 = NULL;
      unsigned int write_00152_len = 0;
      write_00152 = append_var("wait", write_00152, &write_00152_len);
      if (write_00152_len > 0) {
         transmit_all(1, write_00152, write_00152_len);
      }
      free(write_00152);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00153_00000[] = 
         "\x0a";
      static unsigned int write_00153_00000_len = 1;
      unsigned char *write_00153 = NULL;
      unsigned int write_00153_len = 0;
      write_00153 = append_buf(write_00153, &write_00153_len, write_00153_00000, write_00153_00000_len);
      if (write_00153_len > 0) {
         transmit_all(1, write_00153, write_00153_len);
      }
      free(write_00153);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = append_var("jumpright", write_00154, &write_00154_len);
      if (write_00154_len > 0) {
         transmit_all(1, write_00154, write_00154_len);
      }
      free(write_00154);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00155_00000[] = 
         "\x0a";
      static unsigned int write_00155_00000_len = 1;
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = append_buf(write_00155, &write_00155_len, write_00155_00000, write_00155_00000_len);
      if (write_00155_len > 0) {
         transmit_all(1, write_00155, write_00155_len);
      }
      free(write_00155);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00156 = NULL;
      unsigned int write_00156_len = 0;
      write_00156 = append_var("jumpright", write_00156, &write_00156_len);
      if (write_00156_len > 0) {
         transmit_all(1, write_00156, write_00156_len);
      }
      free(write_00156);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00157_00000[] = 
         "\x0a";
      static unsigned int write_00157_00000_len = 1;
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = append_buf(write_00157, &write_00157_len, write_00157_00000, write_00157_00000_len);
      if (write_00157_len > 0) {
         transmit_all(1, write_00157, write_00157_len);
      }
      free(write_00157);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = append_var("right", write_00158, &write_00158_len);
      if (write_00158_len > 0) {
         transmit_all(1, write_00158, write_00158_len);
      }
      free(write_00158);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00159_00000[] = 
         "\x0a";
      static unsigned int write_00159_00000_len = 1;
      unsigned char *write_00159 = NULL;
      unsigned int write_00159_len = 0;
      write_00159 = append_buf(write_00159, &write_00159_len, write_00159_00000, write_00159_00000_len);
      if (write_00159_len > 0) {
         transmit_all(1, write_00159, write_00159_len);
      }
      free(write_00159);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = append_var("wait", write_00160, &write_00160_len);
      if (write_00160_len > 0) {
         transmit_all(1, write_00160, write_00160_len);
      }
      free(write_00160);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00161_00000[] = 
         "\x0a";
      static unsigned int write_00161_00000_len = 1;
      unsigned char *write_00161 = NULL;
      unsigned int write_00161_len = 0;
      write_00161 = append_buf(write_00161, &write_00161_len, write_00161_00000, write_00161_00000_len);
      if (write_00161_len > 0) {
         transmit_all(1, write_00161, write_00161_len);
      }
      free(write_00161);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = append_var("wait", write_00162, &write_00162_len);
      if (write_00162_len > 0) {
         transmit_all(1, write_00162, write_00162_len);
      }
      free(write_00162);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00163_00000[] = 
         "\x0a";
      static unsigned int write_00163_00000_len = 1;
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = append_buf(write_00163, &write_00163_len, write_00163_00000, write_00163_00000_len);
      if (write_00163_len > 0) {
         transmit_all(1, write_00163, write_00163_len);
      }
      free(write_00163);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00164 = NULL;
      unsigned int write_00164_len = 0;
      write_00164 = append_var("wait", write_00164, &write_00164_len);
      if (write_00164_len > 0) {
         transmit_all(1, write_00164, write_00164_len);
      }
      free(write_00164);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00165_00000[] = 
         "\x0a";
      static unsigned int write_00165_00000_len = 1;
      unsigned char *write_00165 = NULL;
      unsigned int write_00165_len = 0;
      write_00165 = append_buf(write_00165, &write_00165_len, write_00165_00000, write_00165_00000_len);
      if (write_00165_len > 0) {
         transmit_all(1, write_00165, write_00165_len);
      }
      free(write_00165);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = append_var("wait", write_00166, &write_00166_len);
      if (write_00166_len > 0) {
         transmit_all(1, write_00166, write_00166_len);
      }
      free(write_00166);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00167_00000[] = 
         "\x0a";
      static unsigned int write_00167_00000_len = 1;
      unsigned char *write_00167 = NULL;
      unsigned int write_00167_len = 0;
      write_00167 = append_buf(write_00167, &write_00167_len, write_00167_00000, write_00167_00000_len);
      if (write_00167_len > 0) {
         transmit_all(1, write_00167, write_00167_len);
      }
      free(write_00167);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = append_var("wait", write_00168, &write_00168_len);
      if (write_00168_len > 0) {
         transmit_all(1, write_00168, write_00168_len);
      }
      free(write_00168);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00169_00000[] = 
         "\x0a";
      static unsigned int write_00169_00000_len = 1;
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = append_buf(write_00169, &write_00169_len, write_00169_00000, write_00169_00000_len);
      if (write_00169_len > 0) {
         transmit_all(1, write_00169, write_00169_len);
      }
      free(write_00169);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00170 = NULL;
      unsigned int write_00170_len = 0;
      write_00170 = append_var("wait", write_00170, &write_00170_len);
      if (write_00170_len > 0) {
         transmit_all(1, write_00170, write_00170_len);
      }
      free(write_00170);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00171_00000[] = 
         "\x0a";
      static unsigned int write_00171_00000_len = 1;
      unsigned char *write_00171 = NULL;
      unsigned int write_00171_len = 0;
      write_00171 = append_buf(write_00171, &write_00171_len, write_00171_00000, write_00171_00000_len);
      if (write_00171_len > 0) {
         transmit_all(1, write_00171, write_00171_len);
      }
      free(write_00171);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = append_var("wait", write_00172, &write_00172_len);
      if (write_00172_len > 0) {
         transmit_all(1, write_00172, write_00172_len);
      }
      free(write_00172);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00173_00000[] = 
         "\x0a";
      static unsigned int write_00173_00000_len = 1;
      unsigned char *write_00173 = NULL;
      unsigned int write_00173_len = 0;
      write_00173 = append_buf(write_00173, &write_00173_len, write_00173_00000, write_00173_00000_len);
      if (write_00173_len > 0) {
         transmit_all(1, write_00173, write_00173_len);
      }
      free(write_00173);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00174 = NULL;
      unsigned int write_00174_len = 0;
      write_00174 = append_var("wait", write_00174, &write_00174_len);
      if (write_00174_len > 0) {
         transmit_all(1, write_00174, write_00174_len);
      }
      free(write_00174);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00175_00000[] = 
         "\x0a";
      static unsigned int write_00175_00000_len = 1;
      unsigned char *write_00175 = NULL;
      unsigned int write_00175_len = 0;
      write_00175 = append_buf(write_00175, &write_00175_len, write_00175_00000, write_00175_00000_len);
      if (write_00175_len > 0) {
         transmit_all(1, write_00175, write_00175_len);
      }
      free(write_00175);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00176 = NULL;
      unsigned int write_00176_len = 0;
      write_00176 = append_var("wait", write_00176, &write_00176_len);
      if (write_00176_len > 0) {
         transmit_all(1, write_00176, write_00176_len);
      }
      free(write_00176);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00177_00000[] = 
         "\x0a";
      static unsigned int write_00177_00000_len = 1;
      unsigned char *write_00177 = NULL;
      unsigned int write_00177_len = 0;
      write_00177 = append_buf(write_00177, &write_00177_len, write_00177_00000, write_00177_00000_len);
      if (write_00177_len > 0) {
         transmit_all(1, write_00177, write_00177_len);
      }
      free(write_00177);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00178 = NULL;
      unsigned int write_00178_len = 0;
      write_00178 = append_var("wait", write_00178, &write_00178_len);
      if (write_00178_len > 0) {
         transmit_all(1, write_00178, write_00178_len);
      }
      free(write_00178);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00179_00000[] = 
         "\x0a";
      static unsigned int write_00179_00000_len = 1;
      unsigned char *write_00179 = NULL;
      unsigned int write_00179_len = 0;
      write_00179 = append_buf(write_00179, &write_00179_len, write_00179_00000, write_00179_00000_len);
      if (write_00179_len > 0) {
         transmit_all(1, write_00179, write_00179_len);
      }
      free(write_00179);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00180 = NULL;
      unsigned int write_00180_len = 0;
      write_00180 = append_var("wait", write_00180, &write_00180_len);
      if (write_00180_len > 0) {
         transmit_all(1, write_00180, write_00180_len);
      }
      free(write_00180);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00181_00000[] = 
         "\x0a";
      static unsigned int write_00181_00000_len = 1;
      unsigned char *write_00181 = NULL;
      unsigned int write_00181_len = 0;
      write_00181 = append_buf(write_00181, &write_00181_len, write_00181_00000, write_00181_00000_len);
      if (write_00181_len > 0) {
         transmit_all(1, write_00181, write_00181_len);
      }
      free(write_00181);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00182 = NULL;
      unsigned int write_00182_len = 0;
      write_00182 = append_var("wait", write_00182, &write_00182_len);
      if (write_00182_len > 0) {
         transmit_all(1, write_00182, write_00182_len);
      }
      free(write_00182);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00183_00000[] = 
         "\x0a";
      static unsigned int write_00183_00000_len = 1;
      unsigned char *write_00183 = NULL;
      unsigned int write_00183_len = 0;
      write_00183 = append_buf(write_00183, &write_00183_len, write_00183_00000, write_00183_00000_len);
      if (write_00183_len > 0) {
         transmit_all(1, write_00183, write_00183_len);
      }
      free(write_00183);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00184 = NULL;
      unsigned int write_00184_len = 0;
      write_00184 = append_var("wait", write_00184, &write_00184_len);
      if (write_00184_len > 0) {
         transmit_all(1, write_00184, write_00184_len);
      }
      free(write_00184);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00185_00000[] = 
         "\x0a";
      static unsigned int write_00185_00000_len = 1;
      unsigned char *write_00185 = NULL;
      unsigned int write_00185_len = 0;
      write_00185 = append_buf(write_00185, &write_00185_len, write_00185_00000, write_00185_00000_len);
      if (write_00185_len > 0) {
         transmit_all(1, write_00185, write_00185_len);
      }
      free(write_00185);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00186 = NULL;
      unsigned int write_00186_len = 0;
      write_00186 = append_var("wait", write_00186, &write_00186_len);
      if (write_00186_len > 0) {
         transmit_all(1, write_00186, write_00186_len);
      }
      free(write_00186);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00187_00000[] = 
         "\x0a";
      static unsigned int write_00187_00000_len = 1;
      unsigned char *write_00187 = NULL;
      unsigned int write_00187_len = 0;
      write_00187 = append_buf(write_00187, &write_00187_len, write_00187_00000, write_00187_00000_len);
      if (write_00187_len > 0) {
         transmit_all(1, write_00187, write_00187_len);
      }
      free(write_00187);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00188 = NULL;
      unsigned int write_00188_len = 0;
      write_00188 = append_var("wait", write_00188, &write_00188_len);
      if (write_00188_len > 0) {
         transmit_all(1, write_00188, write_00188_len);
      }
      free(write_00188);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00189_00000[] = 
         "\x0a";
      static unsigned int write_00189_00000_len = 1;
      unsigned char *write_00189 = NULL;
      unsigned int write_00189_len = 0;
      write_00189 = append_buf(write_00189, &write_00189_len, write_00189_00000, write_00189_00000_len);
      if (write_00189_len > 0) {
         transmit_all(1, write_00189, write_00189_len);
      }
      free(write_00189);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00190 = NULL;
      unsigned int write_00190_len = 0;
      write_00190 = append_var("wait", write_00190, &write_00190_len);
      if (write_00190_len > 0) {
         transmit_all(1, write_00190, write_00190_len);
      }
      free(write_00190);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00191_00000[] = 
         "\x0a";
      static unsigned int write_00191_00000_len = 1;
      unsigned char *write_00191 = NULL;
      unsigned int write_00191_len = 0;
      write_00191 = append_buf(write_00191, &write_00191_len, write_00191_00000, write_00191_00000_len);
      if (write_00191_len > 0) {
         transmit_all(1, write_00191, write_00191_len);
      }
      free(write_00191);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00192 = NULL;
      unsigned int write_00192_len = 0;
      write_00192 = append_var("wait", write_00192, &write_00192_len);
      if (write_00192_len > 0) {
         transmit_all(1, write_00192, write_00192_len);
      }
      free(write_00192);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00193_00000[] = 
         "\x0a";
      static unsigned int write_00193_00000_len = 1;
      unsigned char *write_00193 = NULL;
      unsigned int write_00193_len = 0;
      write_00193 = append_buf(write_00193, &write_00193_len, write_00193_00000, write_00193_00000_len);
      if (write_00193_len > 0) {
         transmit_all(1, write_00193, write_00193_len);
      }
      free(write_00193);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00194 = NULL;
      unsigned int write_00194_len = 0;
      write_00194 = append_var("wait", write_00194, &write_00194_len);
      if (write_00194_len > 0) {
         transmit_all(1, write_00194, write_00194_len);
      }
      free(write_00194);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00195_00000[] = 
         "\x0a";
      static unsigned int write_00195_00000_len = 1;
      unsigned char *write_00195 = NULL;
      unsigned int write_00195_len = 0;
      write_00195 = append_buf(write_00195, &write_00195_len, write_00195_00000, write_00195_00000_len);
      if (write_00195_len > 0) {
         transmit_all(1, write_00195, write_00195_len);
      }
      free(write_00195);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00196 = NULL;
      unsigned int write_00196_len = 0;
      write_00196 = append_var("wait", write_00196, &write_00196_len);
      if (write_00196_len > 0) {
         transmit_all(1, write_00196, write_00196_len);
      }
      free(write_00196);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00197_00000[] = 
         "\x0a";
      static unsigned int write_00197_00000_len = 1;
      unsigned char *write_00197 = NULL;
      unsigned int write_00197_len = 0;
      write_00197 = append_buf(write_00197, &write_00197_len, write_00197_00000, write_00197_00000_len);
      if (write_00197_len > 0) {
         transmit_all(1, write_00197, write_00197_len);
      }
      free(write_00197);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00198 = NULL;
      unsigned int write_00198_len = 0;
      write_00198 = append_var("wait", write_00198, &write_00198_len);
      if (write_00198_len > 0) {
         transmit_all(1, write_00198, write_00198_len);
      }
      free(write_00198);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00199_00000[] = 
         "\x0a";
      static unsigned int write_00199_00000_len = 1;
      unsigned char *write_00199 = NULL;
      unsigned int write_00199_len = 0;
      write_00199 = append_buf(write_00199, &write_00199_len, write_00199_00000, write_00199_00000_len);
      if (write_00199_len > 0) {
         transmit_all(1, write_00199, write_00199_len);
      }
      free(write_00199);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00200 = NULL;
      unsigned int write_00200_len = 0;
      write_00200 = append_var("wait", write_00200, &write_00200_len);
      if (write_00200_len > 0) {
         transmit_all(1, write_00200, write_00200_len);
      }
      free(write_00200);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00201_00000[] = 
         "\x0a";
      static unsigned int write_00201_00000_len = 1;
      unsigned char *write_00201 = NULL;
      unsigned int write_00201_len = 0;
      write_00201 = append_buf(write_00201, &write_00201_len, write_00201_00000, write_00201_00000_len);
      if (write_00201_len > 0) {
         transmit_all(1, write_00201, write_00201_len);
      }
      free(write_00201);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00202 = NULL;
      unsigned int write_00202_len = 0;
      write_00202 = append_var("wait", write_00202, &write_00202_len);
      if (write_00202_len > 0) {
         transmit_all(1, write_00202, write_00202_len);
      }
      free(write_00202);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00203_00000[] = 
         "\x0a";
      static unsigned int write_00203_00000_len = 1;
      unsigned char *write_00203 = NULL;
      unsigned int write_00203_len = 0;
      write_00203 = append_buf(write_00203, &write_00203_len, write_00203_00000, write_00203_00000_len);
      if (write_00203_len > 0) {
         transmit_all(1, write_00203, write_00203_len);
      }
      free(write_00203);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00204 = NULL;
      unsigned int write_00204_len = 0;
      write_00204 = append_var("wait", write_00204, &write_00204_len);
      if (write_00204_len > 0) {
         transmit_all(1, write_00204, write_00204_len);
      }
      free(write_00204);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00205_00000[] = 
         "\x0a";
      static unsigned int write_00205_00000_len = 1;
      unsigned char *write_00205 = NULL;
      unsigned int write_00205_len = 0;
      write_00205 = append_buf(write_00205, &write_00205_len, write_00205_00000, write_00205_00000_len);
      if (write_00205_len > 0) {
         transmit_all(1, write_00205, write_00205_len);
      }
      free(write_00205);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00206 = NULL;
      unsigned int write_00206_len = 0;
      write_00206 = append_var("wait", write_00206, &write_00206_len);
      if (write_00206_len > 0) {
         transmit_all(1, write_00206, write_00206_len);
      }
      free(write_00206);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00207_00000[] = 
         "\x0a";
      static unsigned int write_00207_00000_len = 1;
      unsigned char *write_00207 = NULL;
      unsigned int write_00207_len = 0;
      write_00207 = append_buf(write_00207, &write_00207_len, write_00207_00000, write_00207_00000_len);
      if (write_00207_len > 0) {
         transmit_all(1, write_00207, write_00207_len);
      }
      free(write_00207);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00208 = NULL;
      unsigned int write_00208_len = 0;
      write_00208 = append_var("wait", write_00208, &write_00208_len);
      if (write_00208_len > 0) {
         transmit_all(1, write_00208, write_00208_len);
      }
      free(write_00208);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00209_00000[] = 
         "\x0a";
      static unsigned int write_00209_00000_len = 1;
      unsigned char *write_00209 = NULL;
      unsigned int write_00209_len = 0;
      write_00209 = append_buf(write_00209, &write_00209_len, write_00209_00000, write_00209_00000_len);
      if (write_00209_len > 0) {
         transmit_all(1, write_00209, write_00209_len);
      }
      free(write_00209);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00210 = NULL;
      unsigned int write_00210_len = 0;
      write_00210 = append_var("left", write_00210, &write_00210_len);
      if (write_00210_len > 0) {
         transmit_all(1, write_00210, write_00210_len);
      }
      free(write_00210);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00211_00000[] = 
         "\x0a";
      static unsigned int write_00211_00000_len = 1;
      unsigned char *write_00211 = NULL;
      unsigned int write_00211_len = 0;
      write_00211 = append_buf(write_00211, &write_00211_len, write_00211_00000, write_00211_00000_len);
      if (write_00211_len > 0) {
         transmit_all(1, write_00211, write_00211_len);
      }
      free(write_00211);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00212 = NULL;
      unsigned int write_00212_len = 0;
      write_00212 = append_var("right", write_00212, &write_00212_len);
      if (write_00212_len > 0) {
         transmit_all(1, write_00212, write_00212_len);
      }
      free(write_00212);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00213_00000[] = 
         "\x0a";
      static unsigned int write_00213_00000_len = 1;
      unsigned char *write_00213 = NULL;
      unsigned int write_00213_len = 0;
      write_00213 = append_buf(write_00213, &write_00213_len, write_00213_00000, write_00213_00000_len);
      if (write_00213_len > 0) {
         transmit_all(1, write_00213, write_00213_len);
      }
      free(write_00213);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00214 = NULL;
      unsigned int write_00214_len = 0;
      write_00214 = append_var("right", write_00214, &write_00214_len);
      if (write_00214_len > 0) {
         transmit_all(1, write_00214, write_00214_len);
      }
      free(write_00214);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00215_00000[] = 
         "\x0a";
      static unsigned int write_00215_00000_len = 1;
      unsigned char *write_00215 = NULL;
      unsigned int write_00215_len = 0;
      write_00215 = append_buf(write_00215, &write_00215_len, write_00215_00000, write_00215_00000_len);
      if (write_00215_len > 0) {
         transmit_all(1, write_00215, write_00215_len);
      }
      free(write_00215);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00216 = NULL;
      unsigned int write_00216_len = 0;
      write_00216 = append_var("right", write_00216, &write_00216_len);
      if (write_00216_len > 0) {
         transmit_all(1, write_00216, write_00216_len);
      }
      free(write_00216);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00217_00000[] = 
         "\x0a";
      static unsigned int write_00217_00000_len = 1;
      unsigned char *write_00217 = NULL;
      unsigned int write_00217_len = 0;
      write_00217 = append_buf(write_00217, &write_00217_len, write_00217_00000, write_00217_00000_len);
      if (write_00217_len > 0) {
         transmit_all(1, write_00217, write_00217_len);
      }
      free(write_00217);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00218 = NULL;
      unsigned int write_00218_len = 0;
      write_00218 = append_var("right", write_00218, &write_00218_len);
      if (write_00218_len > 0) {
         transmit_all(1, write_00218, write_00218_len);
      }
      free(write_00218);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00219_00000[] = 
         "\x0a";
      static unsigned int write_00219_00000_len = 1;
      unsigned char *write_00219 = NULL;
      unsigned int write_00219_len = 0;
      write_00219 = append_buf(write_00219, &write_00219_len, write_00219_00000, write_00219_00000_len);
      if (write_00219_len > 0) {
         transmit_all(1, write_00219, write_00219_len);
      }
      free(write_00219);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00220 = NULL;
      unsigned int write_00220_len = 0;
      write_00220 = append_var("right", write_00220, &write_00220_len);
      if (write_00220_len > 0) {
         transmit_all(1, write_00220, write_00220_len);
      }
      free(write_00220);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00221_00000[] = 
         "\x0a";
      static unsigned int write_00221_00000_len = 1;
      unsigned char *write_00221 = NULL;
      unsigned int write_00221_len = 0;
      write_00221 = append_buf(write_00221, &write_00221_len, write_00221_00000, write_00221_00000_len);
      if (write_00221_len > 0) {
         transmit_all(1, write_00221, write_00221_len);
      }
      free(write_00221);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00222 = NULL;
      unsigned int write_00222_len = 0;
      write_00222 = append_var("right", write_00222, &write_00222_len);
      if (write_00222_len > 0) {
         transmit_all(1, write_00222, write_00222_len);
      }
      free(write_00222);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00223_00000[] = 
         "\x0a";
      static unsigned int write_00223_00000_len = 1;
      unsigned char *write_00223 = NULL;
      unsigned int write_00223_len = 0;
      write_00223 = append_buf(write_00223, &write_00223_len, write_00223_00000, write_00223_00000_len);
      if (write_00223_len > 0) {
         transmit_all(1, write_00223, write_00223_len);
      }
      free(write_00223);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00224 = NULL;
      unsigned int write_00224_len = 0;
      write_00224 = append_var("right", write_00224, &write_00224_len);
      if (write_00224_len > 0) {
         transmit_all(1, write_00224, write_00224_len);
      }
      free(write_00224);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00225_00000[] = 
         "\x0a";
      static unsigned int write_00225_00000_len = 1;
      unsigned char *write_00225 = NULL;
      unsigned int write_00225_len = 0;
      write_00225 = append_buf(write_00225, &write_00225_len, write_00225_00000, write_00225_00000_len);
      if (write_00225_len > 0) {
         transmit_all(1, write_00225, write_00225_len);
      }
      free(write_00225);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00226 = NULL;
      unsigned int write_00226_len = 0;
      write_00226 = append_var("jumpright", write_00226, &write_00226_len);
      if (write_00226_len > 0) {
         transmit_all(1, write_00226, write_00226_len);
      }
      free(write_00226);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00227_00000[] = 
         "\x0a";
      static unsigned int write_00227_00000_len = 1;
      unsigned char *write_00227 = NULL;
      unsigned int write_00227_len = 0;
      write_00227 = append_buf(write_00227, &write_00227_len, write_00227_00000, write_00227_00000_len);
      if (write_00227_len > 0) {
         transmit_all(1, write_00227, write_00227_len);
      }
      free(write_00227);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00228 = NULL;
      unsigned int write_00228_len = 0;
      write_00228 = append_var("wait", write_00228, &write_00228_len);
      if (write_00228_len > 0) {
         transmit_all(1, write_00228, write_00228_len);
      }
      free(write_00228);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00229_00000[] = 
         "\x0a";
      static unsigned int write_00229_00000_len = 1;
      unsigned char *write_00229 = NULL;
      unsigned int write_00229_len = 0;
      write_00229 = append_buf(write_00229, &write_00229_len, write_00229_00000, write_00229_00000_len);
      if (write_00229_len > 0) {
         transmit_all(1, write_00229, write_00229_len);
      }
      free(write_00229);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00230 = NULL;
      unsigned int write_00230_len = 0;
      write_00230 = append_var("wait", write_00230, &write_00230_len);
      if (write_00230_len > 0) {
         transmit_all(1, write_00230, write_00230_len);
      }
      free(write_00230);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00231_00000[] = 
         "\x0a";
      static unsigned int write_00231_00000_len = 1;
      unsigned char *write_00231 = NULL;
      unsigned int write_00231_len = 0;
      write_00231 = append_buf(write_00231, &write_00231_len, write_00231_00000, write_00231_00000_len);
      if (write_00231_len > 0) {
         transmit_all(1, write_00231, write_00231_len);
      }
      free(write_00231);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00232 = NULL;
      unsigned int write_00232_len = 0;
      write_00232 = append_var("wait", write_00232, &write_00232_len);
      if (write_00232_len > 0) {
         transmit_all(1, write_00232, write_00232_len);
      }
      free(write_00232);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00233_00000[] = 
         "\x0a";
      static unsigned int write_00233_00000_len = 1;
      unsigned char *write_00233 = NULL;
      unsigned int write_00233_len = 0;
      write_00233 = append_buf(write_00233, &write_00233_len, write_00233_00000, write_00233_00000_len);
      if (write_00233_len > 0) {
         transmit_all(1, write_00233, write_00233_len);
      }
      free(write_00233);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00234 = NULL;
      unsigned int write_00234_len = 0;
      write_00234 = append_var("jumpright", write_00234, &write_00234_len);
      if (write_00234_len > 0) {
         transmit_all(1, write_00234, write_00234_len);
      }
      free(write_00234);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00235_00000[] = 
         "\x0a";
      static unsigned int write_00235_00000_len = 1;
      unsigned char *write_00235 = NULL;
      unsigned int write_00235_len = 0;
      write_00235 = append_buf(write_00235, &write_00235_len, write_00235_00000, write_00235_00000_len);
      if (write_00235_len > 0) {
         transmit_all(1, write_00235, write_00235_len);
      }
      free(write_00235);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00236 = NULL;
      unsigned int write_00236_len = 0;
      write_00236 = append_var("right", write_00236, &write_00236_len);
      if (write_00236_len > 0) {
         transmit_all(1, write_00236, write_00236_len);
      }
      free(write_00236);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00237_00000[] = 
         "\x0a";
      static unsigned int write_00237_00000_len = 1;
      unsigned char *write_00237 = NULL;
      unsigned int write_00237_len = 0;
      write_00237 = append_buf(write_00237, &write_00237_len, write_00237_00000, write_00237_00000_len);
      if (write_00237_len > 0) {
         transmit_all(1, write_00237, write_00237_len);
      }
      free(write_00237);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00238 = NULL;
      unsigned int write_00238_len = 0;
      write_00238 = append_var("right", write_00238, &write_00238_len);
      if (write_00238_len > 0) {
         transmit_all(1, write_00238, write_00238_len);
      }
      free(write_00238);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00239_00000[] = 
         "\x0a";
      static unsigned int write_00239_00000_len = 1;
      unsigned char *write_00239 = NULL;
      unsigned int write_00239_len = 0;
      write_00239 = append_buf(write_00239, &write_00239_len, write_00239_00000, write_00239_00000_len);
      if (write_00239_len > 0) {
         transmit_all(1, write_00239, write_00239_len);
      }
      free(write_00239);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00240 = NULL;
      unsigned int write_00240_len = 0;
      write_00240 = append_var("right", write_00240, &write_00240_len);
      if (write_00240_len > 0) {
         transmit_all(1, write_00240, write_00240_len);
      }
      free(write_00240);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00241_00000[] = 
         "\x0a";
      static unsigned int write_00241_00000_len = 1;
      unsigned char *write_00241 = NULL;
      unsigned int write_00241_len = 0;
      write_00241 = append_buf(write_00241, &write_00241_len, write_00241_00000, write_00241_00000_len);
      if (write_00241_len > 0) {
         transmit_all(1, write_00241, write_00241_len);
      }
      free(write_00241);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00242 = NULL;
      unsigned int write_00242_len = 0;
      write_00242 = append_var("jumpright", write_00242, &write_00242_len);
      if (write_00242_len > 0) {
         transmit_all(1, write_00242, write_00242_len);
      }
      free(write_00242);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00243_00000[] = 
         "\x0a";
      static unsigned int write_00243_00000_len = 1;
      unsigned char *write_00243 = NULL;
      unsigned int write_00243_len = 0;
      write_00243 = append_buf(write_00243, &write_00243_len, write_00243_00000, write_00243_00000_len);
      if (write_00243_len > 0) {
         transmit_all(1, write_00243, write_00243_len);
      }
      free(write_00243);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00244 = NULL;
      unsigned int write_00244_len = 0;
      write_00244 = append_var("jumpright", write_00244, &write_00244_len);
      if (write_00244_len > 0) {
         transmit_all(1, write_00244, write_00244_len);
      }
      free(write_00244);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00245_00000[] = 
         "\x0a";
      static unsigned int write_00245_00000_len = 1;
      unsigned char *write_00245 = NULL;
      unsigned int write_00245_len = 0;
      write_00245 = append_buf(write_00245, &write_00245_len, write_00245_00000, write_00245_00000_len);
      if (write_00245_len > 0) {
         transmit_all(1, write_00245, write_00245_len);
      }
      free(write_00245);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00246 = NULL;
      unsigned int write_00246_len = 0;
      write_00246 = append_var("jumpright", write_00246, &write_00246_len);
      if (write_00246_len > 0) {
         transmit_all(1, write_00246, write_00246_len);
      }
      free(write_00246);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00247_00000[] = 
         "\x0a";
      static unsigned int write_00247_00000_len = 1;
      unsigned char *write_00247 = NULL;
      unsigned int write_00247_len = 0;
      write_00247 = append_buf(write_00247, &write_00247_len, write_00247_00000, write_00247_00000_len);
      if (write_00247_len > 0) {
         transmit_all(1, write_00247, write_00247_len);
      }
      free(write_00247);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00248 = NULL;
      unsigned int write_00248_len = 0;
      write_00248 = append_var("right", write_00248, &write_00248_len);
      if (write_00248_len > 0) {
         transmit_all(1, write_00248, write_00248_len);
      }
      free(write_00248);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00249_00000[] = 
         "\x0a";
      static unsigned int write_00249_00000_len = 1;
      unsigned char *write_00249 = NULL;
      unsigned int write_00249_len = 0;
      write_00249 = append_buf(write_00249, &write_00249_len, write_00249_00000, write_00249_00000_len);
      if (write_00249_len > 0) {
         transmit_all(1, write_00249, write_00249_len);
      }
      free(write_00249);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00250 = NULL;
      unsigned int write_00250_len = 0;
      write_00250 = append_var("jumpright", write_00250, &write_00250_len);
      if (write_00250_len > 0) {
         transmit_all(1, write_00250, write_00250_len);
      }
      free(write_00250);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00251_00000[] = 
         "\x0a";
      static unsigned int write_00251_00000_len = 1;
      unsigned char *write_00251 = NULL;
      unsigned int write_00251_len = 0;
      write_00251 = append_buf(write_00251, &write_00251_len, write_00251_00000, write_00251_00000_len);
      if (write_00251_len > 0) {
         transmit_all(1, write_00251, write_00251_len);
      }
      free(write_00251);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00252 = NULL;
      unsigned int write_00252_len = 0;
      write_00252 = append_var("right", write_00252, &write_00252_len);
      if (write_00252_len > 0) {
         transmit_all(1, write_00252, write_00252_len);
      }
      free(write_00252);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00253_00000[] = 
         "\x0a";
      static unsigned int write_00253_00000_len = 1;
      unsigned char *write_00253 = NULL;
      unsigned int write_00253_len = 0;
      write_00253 = append_buf(write_00253, &write_00253_len, write_00253_00000, write_00253_00000_len);
      if (write_00253_len > 0) {
         transmit_all(1, write_00253, write_00253_len);
      }
      free(write_00253);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00254 = NULL;
      unsigned int write_00254_len = 0;
      write_00254 = append_var("right", write_00254, &write_00254_len);
      if (write_00254_len > 0) {
         transmit_all(1, write_00254, write_00254_len);
      }
      free(write_00254);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00255_00000[] = 
         "\x0a";
      static unsigned int write_00255_00000_len = 1;
      unsigned char *write_00255 = NULL;
      unsigned int write_00255_len = 0;
      write_00255 = append_buf(write_00255, &write_00255_len, write_00255_00000, write_00255_00000_len);
      if (write_00255_len > 0) {
         transmit_all(1, write_00255, write_00255_len);
      }
      free(write_00255);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00256 = NULL;
      unsigned int write_00256_len = 0;
      write_00256 = append_var("wait", write_00256, &write_00256_len);
      if (write_00256_len > 0) {
         transmit_all(1, write_00256, write_00256_len);
      }
      free(write_00256);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00257_00000[] = 
         "\x0a";
      static unsigned int write_00257_00000_len = 1;
      unsigned char *write_00257 = NULL;
      unsigned int write_00257_len = 0;
      write_00257 = append_buf(write_00257, &write_00257_len, write_00257_00000, write_00257_00000_len);
      if (write_00257_len > 0) {
         transmit_all(1, write_00257, write_00257_len);
      }
      free(write_00257);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00258 = NULL;
      unsigned int write_00258_len = 0;
      write_00258 = append_var("wait", write_00258, &write_00258_len);
      if (write_00258_len > 0) {
         transmit_all(1, write_00258, write_00258_len);
      }
      free(write_00258);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00259_00000[] = 
         "\x0a";
      static unsigned int write_00259_00000_len = 1;
      unsigned char *write_00259 = NULL;
      unsigned int write_00259_len = 0;
      write_00259 = append_buf(write_00259, &write_00259_len, write_00259_00000, write_00259_00000_len);
      if (write_00259_len > 0) {
         transmit_all(1, write_00259, write_00259_len);
      }
      free(write_00259);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00260 = NULL;
      unsigned int write_00260_len = 0;
      write_00260 = append_var("wait", write_00260, &write_00260_len);
      if (write_00260_len > 0) {
         transmit_all(1, write_00260, write_00260_len);
      }
      free(write_00260);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00261_00000[] = 
         "\x0a";
      static unsigned int write_00261_00000_len = 1;
      unsigned char *write_00261 = NULL;
      unsigned int write_00261_len = 0;
      write_00261 = append_buf(write_00261, &write_00261_len, write_00261_00000, write_00261_00000_len);
      if (write_00261_len > 0) {
         transmit_all(1, write_00261, write_00261_len);
      }
      free(write_00261);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00262 = NULL;
      unsigned int write_00262_len = 0;
      write_00262 = append_var("wait", write_00262, &write_00262_len);
      if (write_00262_len > 0) {
         transmit_all(1, write_00262, write_00262_len);
      }
      free(write_00262);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00263_00000[] = 
         "\x0a";
      static unsigned int write_00263_00000_len = 1;
      unsigned char *write_00263 = NULL;
      unsigned int write_00263_len = 0;
      write_00263 = append_buf(write_00263, &write_00263_len, write_00263_00000, write_00263_00000_len);
      if (write_00263_len > 0) {
         transmit_all(1, write_00263, write_00263_len);
      }
      free(write_00263);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00264 = NULL;
      unsigned int write_00264_len = 0;
      write_00264 = append_var("wait", write_00264, &write_00264_len);
      if (write_00264_len > 0) {
         transmit_all(1, write_00264, write_00264_len);
      }
      free(write_00264);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00265_00000[] = 
         "\x0a";
      static unsigned int write_00265_00000_len = 1;
      unsigned char *write_00265 = NULL;
      unsigned int write_00265_len = 0;
      write_00265 = append_buf(write_00265, &write_00265_len, write_00265_00000, write_00265_00000_len);
      if (write_00265_len > 0) {
         transmit_all(1, write_00265, write_00265_len);
      }
      free(write_00265);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00266 = NULL;
      unsigned int write_00266_len = 0;
      write_00266 = append_var("wait", write_00266, &write_00266_len);
      if (write_00266_len > 0) {
         transmit_all(1, write_00266, write_00266_len);
      }
      free(write_00266);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00267_00000[] = 
         "\x0a";
      static unsigned int write_00267_00000_len = 1;
      unsigned char *write_00267 = NULL;
      unsigned int write_00267_len = 0;
      write_00267 = append_buf(write_00267, &write_00267_len, write_00267_00000, write_00267_00000_len);
      if (write_00267_len > 0) {
         transmit_all(1, write_00267, write_00267_len);
      }
      free(write_00267);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00268 = NULL;
      unsigned int write_00268_len = 0;
      write_00268 = append_var("wait", write_00268, &write_00268_len);
      if (write_00268_len > 0) {
         transmit_all(1, write_00268, write_00268_len);
      }
      free(write_00268);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00269_00000[] = 
         "\x0a";
      static unsigned int write_00269_00000_len = 1;
      unsigned char *write_00269 = NULL;
      unsigned int write_00269_len = 0;
      write_00269 = append_buf(write_00269, &write_00269_len, write_00269_00000, write_00269_00000_len);
      if (write_00269_len > 0) {
         transmit_all(1, write_00269, write_00269_len);
      }
      free(write_00269);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00270 = NULL;
      unsigned int write_00270_len = 0;
      write_00270 = append_var("wait", write_00270, &write_00270_len);
      if (write_00270_len > 0) {
         transmit_all(1, write_00270, write_00270_len);
      }
      free(write_00270);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00271_00000[] = 
         "\x0a";
      static unsigned int write_00271_00000_len = 1;
      unsigned char *write_00271 = NULL;
      unsigned int write_00271_len = 0;
      write_00271 = append_buf(write_00271, &write_00271_len, write_00271_00000, write_00271_00000_len);
      if (write_00271_len > 0) {
         transmit_all(1, write_00271, write_00271_len);
      }
      free(write_00271);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00272 = NULL;
      unsigned int write_00272_len = 0;
      write_00272 = append_var("wait", write_00272, &write_00272_len);
      if (write_00272_len > 0) {
         transmit_all(1, write_00272, write_00272_len);
      }
      free(write_00272);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00273_00000[] = 
         "\x0a";
      static unsigned int write_00273_00000_len = 1;
      unsigned char *write_00273 = NULL;
      unsigned int write_00273_len = 0;
      write_00273 = append_buf(write_00273, &write_00273_len, write_00273_00000, write_00273_00000_len);
      if (write_00273_len > 0) {
         transmit_all(1, write_00273, write_00273_len);
      }
      free(write_00273);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00274 = NULL;
      unsigned int write_00274_len = 0;
      write_00274 = append_var("wait", write_00274, &write_00274_len);
      if (write_00274_len > 0) {
         transmit_all(1, write_00274, write_00274_len);
      }
      free(write_00274);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00275_00000[] = 
         "\x0a";
      static unsigned int write_00275_00000_len = 1;
      unsigned char *write_00275 = NULL;
      unsigned int write_00275_len = 0;
      write_00275 = append_buf(write_00275, &write_00275_len, write_00275_00000, write_00275_00000_len);
      if (write_00275_len > 0) {
         transmit_all(1, write_00275, write_00275_len);
      }
      free(write_00275);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00276 = NULL;
      unsigned int write_00276_len = 0;
      write_00276 = append_var("wait", write_00276, &write_00276_len);
      if (write_00276_len > 0) {
         transmit_all(1, write_00276, write_00276_len);
      }
      free(write_00276);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00277_00000[] = 
         "\x0a";
      static unsigned int write_00277_00000_len = 1;
      unsigned char *write_00277 = NULL;
      unsigned int write_00277_len = 0;
      write_00277 = append_buf(write_00277, &write_00277_len, write_00277_00000, write_00277_00000_len);
      if (write_00277_len > 0) {
         transmit_all(1, write_00277, write_00277_len);
      }
      free(write_00277);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00278 = NULL;
      unsigned int write_00278_len = 0;
      write_00278 = append_var("wait", write_00278, &write_00278_len);
      if (write_00278_len > 0) {
         transmit_all(1, write_00278, write_00278_len);
      }
      free(write_00278);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00279_00000[] = 
         "\x0a";
      static unsigned int write_00279_00000_len = 1;
      unsigned char *write_00279 = NULL;
      unsigned int write_00279_len = 0;
      write_00279 = append_buf(write_00279, &write_00279_len, write_00279_00000, write_00279_00000_len);
      if (write_00279_len > 0) {
         transmit_all(1, write_00279, write_00279_len);
      }
      free(write_00279);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00280 = NULL;
      unsigned int write_00280_len = 0;
      write_00280 = append_var("wait", write_00280, &write_00280_len);
      if (write_00280_len > 0) {
         transmit_all(1, write_00280, write_00280_len);
      }
      free(write_00280);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00281_00000[] = 
         "\x0a";
      static unsigned int write_00281_00000_len = 1;
      unsigned char *write_00281 = NULL;
      unsigned int write_00281_len = 0;
      write_00281 = append_buf(write_00281, &write_00281_len, write_00281_00000, write_00281_00000_len);
      if (write_00281_len > 0) {
         transmit_all(1, write_00281, write_00281_len);
      }
      free(write_00281);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00282 = NULL;
      unsigned int write_00282_len = 0;
      write_00282 = append_var("wait", write_00282, &write_00282_len);
      if (write_00282_len > 0) {
         transmit_all(1, write_00282, write_00282_len);
      }
      free(write_00282);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00283_00000[] = 
         "\x0a";
      static unsigned int write_00283_00000_len = 1;
      unsigned char *write_00283 = NULL;
      unsigned int write_00283_len = 0;
      write_00283 = append_buf(write_00283, &write_00283_len, write_00283_00000, write_00283_00000_len);
      if (write_00283_len > 0) {
         transmit_all(1, write_00283, write_00283_len);
      }
      free(write_00283);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00284 = NULL;
      unsigned int write_00284_len = 0;
      write_00284 = append_var("wait", write_00284, &write_00284_len);
      if (write_00284_len > 0) {
         transmit_all(1, write_00284, write_00284_len);
      }
      free(write_00284);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00285_00000[] = 
         "\x0a";
      static unsigned int write_00285_00000_len = 1;
      unsigned char *write_00285 = NULL;
      unsigned int write_00285_len = 0;
      write_00285 = append_buf(write_00285, &write_00285_len, write_00285_00000, write_00285_00000_len);
      if (write_00285_len > 0) {
         transmit_all(1, write_00285, write_00285_len);
      }
      free(write_00285);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00286 = NULL;
      unsigned int write_00286_len = 0;
      write_00286 = append_var("wait", write_00286, &write_00286_len);
      if (write_00286_len > 0) {
         transmit_all(1, write_00286, write_00286_len);
      }
      free(write_00286);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00287_00000[] = 
         "\x0a";
      static unsigned int write_00287_00000_len = 1;
      unsigned char *write_00287 = NULL;
      unsigned int write_00287_len = 0;
      write_00287 = append_buf(write_00287, &write_00287_len, write_00287_00000, write_00287_00000_len);
      if (write_00287_len > 0) {
         transmit_all(1, write_00287, write_00287_len);
      }
      free(write_00287);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00288 = NULL;
      unsigned int write_00288_len = 0;
      write_00288 = append_var("wait", write_00288, &write_00288_len);
      if (write_00288_len > 0) {
         transmit_all(1, write_00288, write_00288_len);
      }
      free(write_00288);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00289_00000[] = 
         "\x0a";
      static unsigned int write_00289_00000_len = 1;
      unsigned char *write_00289 = NULL;
      unsigned int write_00289_len = 0;
      write_00289 = append_buf(write_00289, &write_00289_len, write_00289_00000, write_00289_00000_len);
      if (write_00289_len > 0) {
         transmit_all(1, write_00289, write_00289_len);
      }
      free(write_00289);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00290 = NULL;
      unsigned int write_00290_len = 0;
      write_00290 = append_var("wait", write_00290, &write_00290_len);
      if (write_00290_len > 0) {
         transmit_all(1, write_00290, write_00290_len);
      }
      free(write_00290);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00291_00000[] = 
         "\x0a";
      static unsigned int write_00291_00000_len = 1;
      unsigned char *write_00291 = NULL;
      unsigned int write_00291_len = 0;
      write_00291 = append_buf(write_00291, &write_00291_len, write_00291_00000, write_00291_00000_len);
      if (write_00291_len > 0) {
         transmit_all(1, write_00291, write_00291_len);
      }
      free(write_00291);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00292 = NULL;
      unsigned int write_00292_len = 0;
      write_00292 = append_var("wait", write_00292, &write_00292_len);
      if (write_00292_len > 0) {
         transmit_all(1, write_00292, write_00292_len);
      }
      free(write_00292);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00293_00000[] = 
         "\x0a";
      static unsigned int write_00293_00000_len = 1;
      unsigned char *write_00293 = NULL;
      unsigned int write_00293_len = 0;
      write_00293 = append_buf(write_00293, &write_00293_len, write_00293_00000, write_00293_00000_len);
      if (write_00293_len > 0) {
         transmit_all(1, write_00293, write_00293_len);
      }
      free(write_00293);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00294 = NULL;
      unsigned int write_00294_len = 0;
      write_00294 = append_var("wait", write_00294, &write_00294_len);
      if (write_00294_len > 0) {
         transmit_all(1, write_00294, write_00294_len);
      }
      free(write_00294);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00295_00000[] = 
         "\x0a";
      static unsigned int write_00295_00000_len = 1;
      unsigned char *write_00295 = NULL;
      unsigned int write_00295_len = 0;
      write_00295 = append_buf(write_00295, &write_00295_len, write_00295_00000, write_00295_00000_len);
      if (write_00295_len > 0) {
         transmit_all(1, write_00295, write_00295_len);
      }
      free(write_00295);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00296 = NULL;
      unsigned int write_00296_len = 0;
      write_00296 = append_var("wait", write_00296, &write_00296_len);
      if (write_00296_len > 0) {
         transmit_all(1, write_00296, write_00296_len);
      }
      free(write_00296);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00297_00000[] = 
         "\x0a";
      static unsigned int write_00297_00000_len = 1;
      unsigned char *write_00297 = NULL;
      unsigned int write_00297_len = 0;
      write_00297 = append_buf(write_00297, &write_00297_len, write_00297_00000, write_00297_00000_len);
      if (write_00297_len > 0) {
         transmit_all(1, write_00297, write_00297_len);
      }
      free(write_00297);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00298 = NULL;
      unsigned int write_00298_len = 0;
      write_00298 = append_var("wait", write_00298, &write_00298_len);
      if (write_00298_len > 0) {
         transmit_all(1, write_00298, write_00298_len);
      }
      free(write_00298);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00299_00000[] = 
         "\x0a";
      static unsigned int write_00299_00000_len = 1;
      unsigned char *write_00299 = NULL;
      unsigned int write_00299_len = 0;
      write_00299 = append_buf(write_00299, &write_00299_len, write_00299_00000, write_00299_00000_len);
      if (write_00299_len > 0) {
         transmit_all(1, write_00299, write_00299_len);
      }
      free(write_00299);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00300 = NULL;
      unsigned int write_00300_len = 0;
      write_00300 = append_var("wait", write_00300, &write_00300_len);
      if (write_00300_len > 0) {
         transmit_all(1, write_00300, write_00300_len);
      }
      free(write_00300);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00301_00000[] = 
         "\x0a";
      static unsigned int write_00301_00000_len = 1;
      unsigned char *write_00301 = NULL;
      unsigned int write_00301_len = 0;
      write_00301 = append_buf(write_00301, &write_00301_len, write_00301_00000, write_00301_00000_len);
      if (write_00301_len > 0) {
         transmit_all(1, write_00301, write_00301_len);
      }
      free(write_00301);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00302 = NULL;
      unsigned int write_00302_len = 0;
      write_00302 = append_var("wait", write_00302, &write_00302_len);
      if (write_00302_len > 0) {
         transmit_all(1, write_00302, write_00302_len);
      }
      free(write_00302);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00303_00000[] = 
         "\x0a";
      static unsigned int write_00303_00000_len = 1;
      unsigned char *write_00303 = NULL;
      unsigned int write_00303_len = 0;
      write_00303 = append_buf(write_00303, &write_00303_len, write_00303_00000, write_00303_00000_len);
      if (write_00303_len > 0) {
         transmit_all(1, write_00303, write_00303_len);
      }
      free(write_00303);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00304 = NULL;
      unsigned int write_00304_len = 0;
      write_00304 = append_var("wait", write_00304, &write_00304_len);
      if (write_00304_len > 0) {
         transmit_all(1, write_00304, write_00304_len);
      }
      free(write_00304);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00305_00000[] = 
         "\x0a";
      static unsigned int write_00305_00000_len = 1;
      unsigned char *write_00305 = NULL;
      unsigned int write_00305_len = 0;
      write_00305 = append_buf(write_00305, &write_00305_len, write_00305_00000, write_00305_00000_len);
      if (write_00305_len > 0) {
         transmit_all(1, write_00305, write_00305_len);
      }
      free(write_00305);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00306 = NULL;
      unsigned int write_00306_len = 0;
      write_00306 = append_var("left", write_00306, &write_00306_len);
      if (write_00306_len > 0) {
         transmit_all(1, write_00306, write_00306_len);
      }
      free(write_00306);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00307_00000[] = 
         "\x0a";
      static unsigned int write_00307_00000_len = 1;
      unsigned char *write_00307 = NULL;
      unsigned int write_00307_len = 0;
      write_00307 = append_buf(write_00307, &write_00307_len, write_00307_00000, write_00307_00000_len);
      if (write_00307_len > 0) {
         transmit_all(1, write_00307, write_00307_len);
      }
      free(write_00307);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00308 = NULL;
      unsigned int write_00308_len = 0;
      write_00308 = append_var("jumpright", write_00308, &write_00308_len);
      if (write_00308_len > 0) {
         transmit_all(1, write_00308, write_00308_len);
      }
      free(write_00308);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00309_00000[] = 
         "\x0a";
      static unsigned int write_00309_00000_len = 1;
      unsigned char *write_00309 = NULL;
      unsigned int write_00309_len = 0;
      write_00309 = append_buf(write_00309, &write_00309_len, write_00309_00000, write_00309_00000_len);
      if (write_00309_len > 0) {
         transmit_all(1, write_00309, write_00309_len);
      }
      free(write_00309);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00310 = NULL;
      unsigned int write_00310_len = 0;
      write_00310 = append_var("wait", write_00310, &write_00310_len);
      if (write_00310_len > 0) {
         transmit_all(1, write_00310, write_00310_len);
      }
      free(write_00310);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00311_00000[] = 
         "\x0a";
      static unsigned int write_00311_00000_len = 1;
      unsigned char *write_00311 = NULL;
      unsigned int write_00311_len = 0;
      write_00311 = append_buf(write_00311, &write_00311_len, write_00311_00000, write_00311_00000_len);
      if (write_00311_len > 0) {
         transmit_all(1, write_00311, write_00311_len);
      }
      free(write_00311);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00312 = NULL;
      unsigned int write_00312_len = 0;
      write_00312 = append_var("jumpright", write_00312, &write_00312_len);
      if (write_00312_len > 0) {
         transmit_all(1, write_00312, write_00312_len);
      }
      free(write_00312);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00313_00000[] = 
         "\x0a";
      static unsigned int write_00313_00000_len = 1;
      unsigned char *write_00313 = NULL;
      unsigned int write_00313_len = 0;
      write_00313 = append_buf(write_00313, &write_00313_len, write_00313_00000, write_00313_00000_len);
      if (write_00313_len > 0) {
         transmit_all(1, write_00313, write_00313_len);
      }
      free(write_00313);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00314 = NULL;
      unsigned int write_00314_len = 0;
      write_00314 = append_var("right", write_00314, &write_00314_len);
      if (write_00314_len > 0) {
         transmit_all(1, write_00314, write_00314_len);
      }
      free(write_00314);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00315_00000[] = 
         "\x0a";
      static unsigned int write_00315_00000_len = 1;
      unsigned char *write_00315 = NULL;
      unsigned int write_00315_len = 0;
      write_00315 = append_buf(write_00315, &write_00315_len, write_00315_00000, write_00315_00000_len);
      if (write_00315_len > 0) {
         transmit_all(1, write_00315, write_00315_len);
      }
      free(write_00315);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00316 = NULL;
      unsigned int write_00316_len = 0;
      write_00316 = append_var("right", write_00316, &write_00316_len);
      if (write_00316_len > 0) {
         transmit_all(1, write_00316, write_00316_len);
      }
      free(write_00316);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00317_00000[] = 
         "\x0a";
      static unsigned int write_00317_00000_len = 1;
      unsigned char *write_00317 = NULL;
      unsigned int write_00317_len = 0;
      write_00317 = append_buf(write_00317, &write_00317_len, write_00317_00000, write_00317_00000_len);
      if (write_00317_len > 0) {
         transmit_all(1, write_00317, write_00317_len);
      }
      free(write_00317);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00318 = NULL;
      unsigned int write_00318_len = 0;
      write_00318 = append_var("right", write_00318, &write_00318_len);
      if (write_00318_len > 0) {
         transmit_all(1, write_00318, write_00318_len);
      }
      free(write_00318);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00319_00000[] = 
         "\x0a";
      static unsigned int write_00319_00000_len = 1;
      unsigned char *write_00319 = NULL;
      unsigned int write_00319_len = 0;
      write_00319 = append_buf(write_00319, &write_00319_len, write_00319_00000, write_00319_00000_len);
      if (write_00319_len > 0) {
         transmit_all(1, write_00319, write_00319_len);
      }
      free(write_00319);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00320 = NULL;
      unsigned int write_00320_len = 0;
      write_00320 = append_var("right", write_00320, &write_00320_len);
      if (write_00320_len > 0) {
         transmit_all(1, write_00320, write_00320_len);
      }
      free(write_00320);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00321_00000[] = 
         "\x0a";
      static unsigned int write_00321_00000_len = 1;
      unsigned char *write_00321 = NULL;
      unsigned int write_00321_len = 0;
      write_00321 = append_buf(write_00321, &write_00321_len, write_00321_00000, write_00321_00000_len);
      if (write_00321_len > 0) {
         transmit_all(1, write_00321, write_00321_len);
      }
      free(write_00321);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00322 = NULL;
      unsigned int write_00322_len = 0;
      write_00322 = append_var("right", write_00322, &write_00322_len);
      if (write_00322_len > 0) {
         transmit_all(1, write_00322, write_00322_len);
      }
      free(write_00322);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00323_00000[] = 
         "\x0a";
      static unsigned int write_00323_00000_len = 1;
      unsigned char *write_00323 = NULL;
      unsigned int write_00323_len = 0;
      write_00323 = append_buf(write_00323, &write_00323_len, write_00323_00000, write_00323_00000_len);
      if (write_00323_len > 0) {
         transmit_all(1, write_00323, write_00323_len);
      }
      free(write_00323);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00324 = NULL;
      unsigned int write_00324_len = 0;
      write_00324 = append_var("jumpright", write_00324, &write_00324_len);
      if (write_00324_len > 0) {
         transmit_all(1, write_00324, write_00324_len);
      }
      free(write_00324);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00325_00000[] = 
         "\x0a";
      static unsigned int write_00325_00000_len = 1;
      unsigned char *write_00325 = NULL;
      unsigned int write_00325_len = 0;
      write_00325 = append_buf(write_00325, &write_00325_len, write_00325_00000, write_00325_00000_len);
      if (write_00325_len > 0) {
         transmit_all(1, write_00325, write_00325_len);
      }
      free(write_00325);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00326 = NULL;
      unsigned int write_00326_len = 0;
      write_00326 = append_var("jumpright", write_00326, &write_00326_len);
      if (write_00326_len > 0) {
         transmit_all(1, write_00326, write_00326_len);
      }
      free(write_00326);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00327_00000[] = 
         "\x0a";
      static unsigned int write_00327_00000_len = 1;
      unsigned char *write_00327 = NULL;
      unsigned int write_00327_len = 0;
      write_00327 = append_buf(write_00327, &write_00327_len, write_00327_00000, write_00327_00000_len);
      if (write_00327_len > 0) {
         transmit_all(1, write_00327, write_00327_len);
      }
      free(write_00327);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00328 = NULL;
      unsigned int write_00328_len = 0;
      write_00328 = append_var("jumpright", write_00328, &write_00328_len);
      if (write_00328_len > 0) {
         transmit_all(1, write_00328, write_00328_len);
      }
      free(write_00328);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00329_00000[] = 
         "\x0a";
      static unsigned int write_00329_00000_len = 1;
      unsigned char *write_00329 = NULL;
      unsigned int write_00329_len = 0;
      write_00329 = append_buf(write_00329, &write_00329_len, write_00329_00000, write_00329_00000_len);
      if (write_00329_len > 0) {
         transmit_all(1, write_00329, write_00329_len);
      }
      free(write_00329);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00330 = NULL;
      unsigned int write_00330_len = 0;
      write_00330 = append_var("right", write_00330, &write_00330_len);
      if (write_00330_len > 0) {
         transmit_all(1, write_00330, write_00330_len);
      }
      free(write_00330);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00331_00000[] = 
         "\x0a";
      static unsigned int write_00331_00000_len = 1;
      unsigned char *write_00331 = NULL;
      unsigned int write_00331_len = 0;
      write_00331 = append_buf(write_00331, &write_00331_len, write_00331_00000, write_00331_00000_len);
      if (write_00331_len > 0) {
         transmit_all(1, write_00331, write_00331_len);
      }
      free(write_00331);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00332 = NULL;
      unsigned int write_00332_len = 0;
      write_00332 = append_var("jumpright", write_00332, &write_00332_len);
      if (write_00332_len > 0) {
         transmit_all(1, write_00332, write_00332_len);
      }
      free(write_00332);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00333_00000[] = 
         "\x0a";
      static unsigned int write_00333_00000_len = 1;
      unsigned char *write_00333 = NULL;
      unsigned int write_00333_len = 0;
      write_00333 = append_buf(write_00333, &write_00333_len, write_00333_00000, write_00333_00000_len);
      if (write_00333_len > 0) {
         transmit_all(1, write_00333, write_00333_len);
      }
      free(write_00333);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00334 = NULL;
      unsigned int write_00334_len = 0;
      write_00334 = append_var("right", write_00334, &write_00334_len);
      if (write_00334_len > 0) {
         transmit_all(1, write_00334, write_00334_len);
      }
      free(write_00334);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00335_00000[] = 
         "\x0a";
      static unsigned int write_00335_00000_len = 1;
      unsigned char *write_00335 = NULL;
      unsigned int write_00335_len = 0;
      write_00335 = append_buf(write_00335, &write_00335_len, write_00335_00000, write_00335_00000_len);
      if (write_00335_len > 0) {
         transmit_all(1, write_00335, write_00335_len);
      }
      free(write_00335);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00336 = NULL;
      unsigned int write_00336_len = 0;
      write_00336 = append_var("right", write_00336, &write_00336_len);
      if (write_00336_len > 0) {
         transmit_all(1, write_00336, write_00336_len);
      }
      free(write_00336);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00337_00000[] = 
         "\x0a";
      static unsigned int write_00337_00000_len = 1;
      unsigned char *write_00337 = NULL;
      unsigned int write_00337_len = 0;
      write_00337 = append_buf(write_00337, &write_00337_len, write_00337_00000, write_00337_00000_len);
      if (write_00337_len > 0) {
         transmit_all(1, write_00337, write_00337_len);
      }
      free(write_00337);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00338 = NULL;
      unsigned int write_00338_len = 0;
      write_00338 = append_var("wait", write_00338, &write_00338_len);
      if (write_00338_len > 0) {
         transmit_all(1, write_00338, write_00338_len);
      }
      free(write_00338);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00339_00000[] = 
         "\x0a";
      static unsigned int write_00339_00000_len = 1;
      unsigned char *write_00339 = NULL;
      unsigned int write_00339_len = 0;
      write_00339 = append_buf(write_00339, &write_00339_len, write_00339_00000, write_00339_00000_len);
      if (write_00339_len > 0) {
         transmit_all(1, write_00339, write_00339_len);
      }
      free(write_00339);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00340 = NULL;
      unsigned int write_00340_len = 0;
      write_00340 = append_var("wait", write_00340, &write_00340_len);
      if (write_00340_len > 0) {
         transmit_all(1, write_00340, write_00340_len);
      }
      free(write_00340);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00341_00000[] = 
         "\x0a";
      static unsigned int write_00341_00000_len = 1;
      unsigned char *write_00341 = NULL;
      unsigned int write_00341_len = 0;
      write_00341 = append_buf(write_00341, &write_00341_len, write_00341_00000, write_00341_00000_len);
      if (write_00341_len > 0) {
         transmit_all(1, write_00341, write_00341_len);
      }
      free(write_00341);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00342 = NULL;
      unsigned int write_00342_len = 0;
      write_00342 = append_var("wait", write_00342, &write_00342_len);
      if (write_00342_len > 0) {
         transmit_all(1, write_00342, write_00342_len);
      }
      free(write_00342);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00343_00000[] = 
         "\x0a";
      static unsigned int write_00343_00000_len = 1;
      unsigned char *write_00343 = NULL;
      unsigned int write_00343_len = 0;
      write_00343 = append_buf(write_00343, &write_00343_len, write_00343_00000, write_00343_00000_len);
      if (write_00343_len > 0) {
         transmit_all(1, write_00343, write_00343_len);
      }
      free(write_00343);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00344 = NULL;
      unsigned int write_00344_len = 0;
      write_00344 = append_var("wait", write_00344, &write_00344_len);
      if (write_00344_len > 0) {
         transmit_all(1, write_00344, write_00344_len);
      }
      free(write_00344);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00345_00000[] = 
         "\x0a";
      static unsigned int write_00345_00000_len = 1;
      unsigned char *write_00345 = NULL;
      unsigned int write_00345_len = 0;
      write_00345 = append_buf(write_00345, &write_00345_len, write_00345_00000, write_00345_00000_len);
      if (write_00345_len > 0) {
         transmit_all(1, write_00345, write_00345_len);
      }
      free(write_00345);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00346 = NULL;
      unsigned int write_00346_len = 0;
      write_00346 = append_var("wait", write_00346, &write_00346_len);
      if (write_00346_len > 0) {
         transmit_all(1, write_00346, write_00346_len);
      }
      free(write_00346);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00347_00000[] = 
         "\x0a";
      static unsigned int write_00347_00000_len = 1;
      unsigned char *write_00347 = NULL;
      unsigned int write_00347_len = 0;
      write_00347 = append_buf(write_00347, &write_00347_len, write_00347_00000, write_00347_00000_len);
      if (write_00347_len > 0) {
         transmit_all(1, write_00347, write_00347_len);
      }
      free(write_00347);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00348 = NULL;
      unsigned int write_00348_len = 0;
      write_00348 = append_var("wait", write_00348, &write_00348_len);
      if (write_00348_len > 0) {
         transmit_all(1, write_00348, write_00348_len);
      }
      free(write_00348);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00349_00000[] = 
         "\x0a";
      static unsigned int write_00349_00000_len = 1;
      unsigned char *write_00349 = NULL;
      unsigned int write_00349_len = 0;
      write_00349 = append_buf(write_00349, &write_00349_len, write_00349_00000, write_00349_00000_len);
      if (write_00349_len > 0) {
         transmit_all(1, write_00349, write_00349_len);
      }
      free(write_00349);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00350 = NULL;
      unsigned int write_00350_len = 0;
      write_00350 = append_var("wait", write_00350, &write_00350_len);
      if (write_00350_len > 0) {
         transmit_all(1, write_00350, write_00350_len);
      }
      free(write_00350);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00351_00000[] = 
         "\x0a";
      static unsigned int write_00351_00000_len = 1;
      unsigned char *write_00351 = NULL;
      unsigned int write_00351_len = 0;
      write_00351 = append_buf(write_00351, &write_00351_len, write_00351_00000, write_00351_00000_len);
      if (write_00351_len > 0) {
         transmit_all(1, write_00351, write_00351_len);
      }
      free(write_00351);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00352 = NULL;
      unsigned int write_00352_len = 0;
      write_00352 = append_var("wait", write_00352, &write_00352_len);
      if (write_00352_len > 0) {
         transmit_all(1, write_00352, write_00352_len);
      }
      free(write_00352);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00353_00000[] = 
         "\x0a";
      static unsigned int write_00353_00000_len = 1;
      unsigned char *write_00353 = NULL;
      unsigned int write_00353_len = 0;
      write_00353 = append_buf(write_00353, &write_00353_len, write_00353_00000, write_00353_00000_len);
      if (write_00353_len > 0) {
         transmit_all(1, write_00353, write_00353_len);
      }
      free(write_00353);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00354 = NULL;
      unsigned int write_00354_len = 0;
      write_00354 = append_var("wait", write_00354, &write_00354_len);
      if (write_00354_len > 0) {
         transmit_all(1, write_00354, write_00354_len);
      }
      free(write_00354);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00355_00000[] = 
         "\x0a";
      static unsigned int write_00355_00000_len = 1;
      unsigned char *write_00355 = NULL;
      unsigned int write_00355_len = 0;
      write_00355 = append_buf(write_00355, &write_00355_len, write_00355_00000, write_00355_00000_len);
      if (write_00355_len > 0) {
         transmit_all(1, write_00355, write_00355_len);
      }
      free(write_00355);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00356 = NULL;
      unsigned int write_00356_len = 0;
      write_00356 = append_var("wait", write_00356, &write_00356_len);
      if (write_00356_len > 0) {
         transmit_all(1, write_00356, write_00356_len);
      }
      free(write_00356);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00357_00000[] = 
         "\x0a";
      static unsigned int write_00357_00000_len = 1;
      unsigned char *write_00357 = NULL;
      unsigned int write_00357_len = 0;
      write_00357 = append_buf(write_00357, &write_00357_len, write_00357_00000, write_00357_00000_len);
      if (write_00357_len > 0) {
         transmit_all(1, write_00357, write_00357_len);
      }
      free(write_00357);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00358 = NULL;
      unsigned int write_00358_len = 0;
      write_00358 = append_var("wait", write_00358, &write_00358_len);
      if (write_00358_len > 0) {
         transmit_all(1, write_00358, write_00358_len);
      }
      free(write_00358);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00359_00000[] = 
         "\x0a";
      static unsigned int write_00359_00000_len = 1;
      unsigned char *write_00359 = NULL;
      unsigned int write_00359_len = 0;
      write_00359 = append_buf(write_00359, &write_00359_len, write_00359_00000, write_00359_00000_len);
      if (write_00359_len > 0) {
         transmit_all(1, write_00359, write_00359_len);
      }
      free(write_00359);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00360 = NULL;
      unsigned int write_00360_len = 0;
      write_00360 = append_var("wait", write_00360, &write_00360_len);
      if (write_00360_len > 0) {
         transmit_all(1, write_00360, write_00360_len);
      }
      free(write_00360);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00361_00000[] = 
         "\x0a";
      static unsigned int write_00361_00000_len = 1;
      unsigned char *write_00361 = NULL;
      unsigned int write_00361_len = 0;
      write_00361 = append_buf(write_00361, &write_00361_len, write_00361_00000, write_00361_00000_len);
      if (write_00361_len > 0) {
         transmit_all(1, write_00361, write_00361_len);
      }
      free(write_00361);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00362 = NULL;
      unsigned int write_00362_len = 0;
      write_00362 = append_var("wait", write_00362, &write_00362_len);
      if (write_00362_len > 0) {
         transmit_all(1, write_00362, write_00362_len);
      }
      free(write_00362);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00363_00000[] = 
         "\x0a";
      static unsigned int write_00363_00000_len = 1;
      unsigned char *write_00363 = NULL;
      unsigned int write_00363_len = 0;
      write_00363 = append_buf(write_00363, &write_00363_len, write_00363_00000, write_00363_00000_len);
      if (write_00363_len > 0) {
         transmit_all(1, write_00363, write_00363_len);
      }
      free(write_00363);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00364 = NULL;
      unsigned int write_00364_len = 0;
      write_00364 = append_var("wait", write_00364, &write_00364_len);
      if (write_00364_len > 0) {
         transmit_all(1, write_00364, write_00364_len);
      }
      free(write_00364);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00365_00000[] = 
         "\x0a";
      static unsigned int write_00365_00000_len = 1;
      unsigned char *write_00365 = NULL;
      unsigned int write_00365_len = 0;
      write_00365 = append_buf(write_00365, &write_00365_len, write_00365_00000, write_00365_00000_len);
      if (write_00365_len > 0) {
         transmit_all(1, write_00365, write_00365_len);
      }
      free(write_00365);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00366 = NULL;
      unsigned int write_00366_len = 0;
      write_00366 = append_var("wait", write_00366, &write_00366_len);
      if (write_00366_len > 0) {
         transmit_all(1, write_00366, write_00366_len);
      }
      free(write_00366);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00367_00000[] = 
         "\x0a";
      static unsigned int write_00367_00000_len = 1;
      unsigned char *write_00367 = NULL;
      unsigned int write_00367_len = 0;
      write_00367 = append_buf(write_00367, &write_00367_len, write_00367_00000, write_00367_00000_len);
      if (write_00367_len > 0) {
         transmit_all(1, write_00367, write_00367_len);
      }
      free(write_00367);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00368 = NULL;
      unsigned int write_00368_len = 0;
      write_00368 = append_var("wait", write_00368, &write_00368_len);
      if (write_00368_len > 0) {
         transmit_all(1, write_00368, write_00368_len);
      }
      free(write_00368);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00369_00000[] = 
         "\x0a";
      static unsigned int write_00369_00000_len = 1;
      unsigned char *write_00369 = NULL;
      unsigned int write_00369_len = 0;
      write_00369 = append_buf(write_00369, &write_00369_len, write_00369_00000, write_00369_00000_len);
      if (write_00369_len > 0) {
         transmit_all(1, write_00369, write_00369_len);
      }
      free(write_00369);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00370 = NULL;
      unsigned int write_00370_len = 0;
      write_00370 = append_var("wait", write_00370, &write_00370_len);
      if (write_00370_len > 0) {
         transmit_all(1, write_00370, write_00370_len);
      }
      free(write_00370);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00371_00000[] = 
         "\x0a";
      static unsigned int write_00371_00000_len = 1;
      unsigned char *write_00371 = NULL;
      unsigned int write_00371_len = 0;
      write_00371 = append_buf(write_00371, &write_00371_len, write_00371_00000, write_00371_00000_len);
      if (write_00371_len > 0) {
         transmit_all(1, write_00371, write_00371_len);
      }
      free(write_00371);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00372 = NULL;
      unsigned int write_00372_len = 0;
      write_00372 = append_var("wait", write_00372, &write_00372_len);
      if (write_00372_len > 0) {
         transmit_all(1, write_00372, write_00372_len);
      }
      free(write_00372);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00373_00000[] = 
         "\x0a";
      static unsigned int write_00373_00000_len = 1;
      unsigned char *write_00373 = NULL;
      unsigned int write_00373_len = 0;
      write_00373 = append_buf(write_00373, &write_00373_len, write_00373_00000, write_00373_00000_len);
      if (write_00373_len > 0) {
         transmit_all(1, write_00373, write_00373_len);
      }
      free(write_00373);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00374 = NULL;
      unsigned int write_00374_len = 0;
      write_00374 = append_var("wait", write_00374, &write_00374_len);
      if (write_00374_len > 0) {
         transmit_all(1, write_00374, write_00374_len);
      }
      free(write_00374);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00375_00000[] = 
         "\x0a";
      static unsigned int write_00375_00000_len = 1;
      unsigned char *write_00375 = NULL;
      unsigned int write_00375_len = 0;
      write_00375 = append_buf(write_00375, &write_00375_len, write_00375_00000, write_00375_00000_len);
      if (write_00375_len > 0) {
         transmit_all(1, write_00375, write_00375_len);
      }
      free(write_00375);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00376 = NULL;
      unsigned int write_00376_len = 0;
      write_00376 = append_var("wait", write_00376, &write_00376_len);
      if (write_00376_len > 0) {
         transmit_all(1, write_00376, write_00376_len);
      }
      free(write_00376);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00377_00000[] = 
         "\x0a";
      static unsigned int write_00377_00000_len = 1;
      unsigned char *write_00377 = NULL;
      unsigned int write_00377_len = 0;
      write_00377 = append_buf(write_00377, &write_00377_len, write_00377_00000, write_00377_00000_len);
      if (write_00377_len > 0) {
         transmit_all(1, write_00377, write_00377_len);
      }
      free(write_00377);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00378 = NULL;
      unsigned int write_00378_len = 0;
      write_00378 = append_var("wait", write_00378, &write_00378_len);
      if (write_00378_len > 0) {
         transmit_all(1, write_00378, write_00378_len);
      }
      free(write_00378);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00379_00000[] = 
         "\x0a";
      static unsigned int write_00379_00000_len = 1;
      unsigned char *write_00379 = NULL;
      unsigned int write_00379_len = 0;
      write_00379 = append_buf(write_00379, &write_00379_len, write_00379_00000, write_00379_00000_len);
      if (write_00379_len > 0) {
         transmit_all(1, write_00379, write_00379_len);
      }
      free(write_00379);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00380 = NULL;
      unsigned int write_00380_len = 0;
      write_00380 = append_var("wait", write_00380, &write_00380_len);
      if (write_00380_len > 0) {
         transmit_all(1, write_00380, write_00380_len);
      }
      free(write_00380);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00381_00000[] = 
         "\x0a";
      static unsigned int write_00381_00000_len = 1;
      unsigned char *write_00381 = NULL;
      unsigned int write_00381_len = 0;
      write_00381 = append_buf(write_00381, &write_00381_len, write_00381_00000, write_00381_00000_len);
      if (write_00381_len > 0) {
         transmit_all(1, write_00381, write_00381_len);
      }
      free(write_00381);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00382 = NULL;
      unsigned int write_00382_len = 0;
      write_00382 = append_var("wait", write_00382, &write_00382_len);
      if (write_00382_len > 0) {
         transmit_all(1, write_00382, write_00382_len);
      }
      free(write_00382);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00383_00000[] = 
         "\x0a";
      static unsigned int write_00383_00000_len = 1;
      unsigned char *write_00383 = NULL;
      unsigned int write_00383_len = 0;
      write_00383 = append_buf(write_00383, &write_00383_len, write_00383_00000, write_00383_00000_len);
      if (write_00383_len > 0) {
         transmit_all(1, write_00383, write_00383_len);
      }
      free(write_00383);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00384 = NULL;
      unsigned int write_00384_len = 0;
      write_00384 = append_var("wait", write_00384, &write_00384_len);
      if (write_00384_len > 0) {
         transmit_all(1, write_00384, write_00384_len);
      }
      free(write_00384);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00385_00000[] = 
         "\x0a";
      static unsigned int write_00385_00000_len = 1;
      unsigned char *write_00385 = NULL;
      unsigned int write_00385_len = 0;
      write_00385 = append_buf(write_00385, &write_00385_len, write_00385_00000, write_00385_00000_len);
      if (write_00385_len > 0) {
         transmit_all(1, write_00385, write_00385_len);
      }
      free(write_00385);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00386 = NULL;
      unsigned int write_00386_len = 0;
      write_00386 = append_var("wait", write_00386, &write_00386_len);
      if (write_00386_len > 0) {
         transmit_all(1, write_00386, write_00386_len);
      }
      free(write_00386);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00387_00000[] = 
         "\x0a";
      static unsigned int write_00387_00000_len = 1;
      unsigned char *write_00387 = NULL;
      unsigned int write_00387_len = 0;
      write_00387 = append_buf(write_00387, &write_00387_len, write_00387_00000, write_00387_00000_len);
      if (write_00387_len > 0) {
         transmit_all(1, write_00387, write_00387_len);
      }
      free(write_00387);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00388 = NULL;
      unsigned int write_00388_len = 0;
      write_00388 = append_var("wait", write_00388, &write_00388_len);
      if (write_00388_len > 0) {
         transmit_all(1, write_00388, write_00388_len);
      }
      free(write_00388);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00389_00000[] = 
         "\x0a";
      static unsigned int write_00389_00000_len = 1;
      unsigned char *write_00389 = NULL;
      unsigned int write_00389_len = 0;
      write_00389 = append_buf(write_00389, &write_00389_len, write_00389_00000, write_00389_00000_len);
      if (write_00389_len > 0) {
         transmit_all(1, write_00389, write_00389_len);
      }
      free(write_00389);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00390 = NULL;
      unsigned int write_00390_len = 0;
      write_00390 = append_var("wait", write_00390, &write_00390_len);
      if (write_00390_len > 0) {
         transmit_all(1, write_00390, write_00390_len);
      }
      free(write_00390);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00391_00000[] = 
         "\x0a";
      static unsigned int write_00391_00000_len = 1;
      unsigned char *write_00391 = NULL;
      unsigned int write_00391_len = 0;
      write_00391 = append_buf(write_00391, &write_00391_len, write_00391_00000, write_00391_00000_len);
      if (write_00391_len > 0) {
         transmit_all(1, write_00391, write_00391_len);
      }
      free(write_00391);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00392 = NULL;
      unsigned int write_00392_len = 0;
      write_00392 = append_var("wait", write_00392, &write_00392_len);
      if (write_00392_len > 0) {
         transmit_all(1, write_00392, write_00392_len);
      }
      free(write_00392);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00393_00000[] = 
         "\x0a";
      static unsigned int write_00393_00000_len = 1;
      unsigned char *write_00393 = NULL;
      unsigned int write_00393_len = 0;
      write_00393 = append_buf(write_00393, &write_00393_len, write_00393_00000, write_00393_00000_len);
      if (write_00393_len > 0) {
         transmit_all(1, write_00393, write_00393_len);
      }
      free(write_00393);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00394 = NULL;
      unsigned int write_00394_len = 0;
      write_00394 = append_var("wait", write_00394, &write_00394_len);
      if (write_00394_len > 0) {
         transmit_all(1, write_00394, write_00394_len);
      }
      free(write_00394);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00395_00000[] = 
         "\x0a";
      static unsigned int write_00395_00000_len = 1;
      unsigned char *write_00395 = NULL;
      unsigned int write_00395_len = 0;
      write_00395 = append_buf(write_00395, &write_00395_len, write_00395_00000, write_00395_00000_len);
      if (write_00395_len > 0) {
         transmit_all(1, write_00395, write_00395_len);
      }
      free(write_00395);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00396 = NULL;
      unsigned int write_00396_len = 0;
      write_00396 = append_var("wait", write_00396, &write_00396_len);
      if (write_00396_len > 0) {
         transmit_all(1, write_00396, write_00396_len);
      }
      free(write_00396);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00397_00000[] = 
         "\x0a";
      static unsigned int write_00397_00000_len = 1;
      unsigned char *write_00397 = NULL;
      unsigned int write_00397_len = 0;
      write_00397 = append_buf(write_00397, &write_00397_len, write_00397_00000, write_00397_00000_len);
      if (write_00397_len > 0) {
         transmit_all(1, write_00397, write_00397_len);
      }
      free(write_00397);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00398 = NULL;
      unsigned int write_00398_len = 0;
      write_00398 = append_var("wait", write_00398, &write_00398_len);
      if (write_00398_len > 0) {
         transmit_all(1, write_00398, write_00398_len);
      }
      free(write_00398);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00399_00000[] = 
         "\x0a";
      static unsigned int write_00399_00000_len = 1;
      unsigned char *write_00399 = NULL;
      unsigned int write_00399_len = 0;
      write_00399 = append_buf(write_00399, &write_00399_len, write_00399_00000, write_00399_00000_len);
      if (write_00399_len > 0) {
         transmit_all(1, write_00399, write_00399_len);
      }
      free(write_00399);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00400 = NULL;
      unsigned int write_00400_len = 0;
      write_00400 = append_var("wait", write_00400, &write_00400_len);
      if (write_00400_len > 0) {
         transmit_all(1, write_00400, write_00400_len);
      }
      free(write_00400);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00401_00000[] = 
         "\x0a";
      static unsigned int write_00401_00000_len = 1;
      unsigned char *write_00401 = NULL;
      unsigned int write_00401_len = 0;
      write_00401 = append_buf(write_00401, &write_00401_len, write_00401_00000, write_00401_00000_len);
      if (write_00401_len > 0) {
         transmit_all(1, write_00401, write_00401_len);
      }
      free(write_00401);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00402 = NULL;
      unsigned int write_00402_len = 0;
      write_00402 = append_var("wait", write_00402, &write_00402_len);
      if (write_00402_len > 0) {
         transmit_all(1, write_00402, write_00402_len);
      }
      free(write_00402);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00403_00000[] = 
         "\x0a";
      static unsigned int write_00403_00000_len = 1;
      unsigned char *write_00403 = NULL;
      unsigned int write_00403_len = 0;
      write_00403 = append_buf(write_00403, &write_00403_len, write_00403_00000, write_00403_00000_len);
      if (write_00403_len > 0) {
         transmit_all(1, write_00403, write_00403_len);
      }
      free(write_00403);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00404 = NULL;
      unsigned int write_00404_len = 0;
      write_00404 = append_var("right", write_00404, &write_00404_len);
      if (write_00404_len > 0) {
         transmit_all(1, write_00404, write_00404_len);
      }
      free(write_00404);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00405_00000[] = 
         "\x0a";
      static unsigned int write_00405_00000_len = 1;
      unsigned char *write_00405 = NULL;
      unsigned int write_00405_len = 0;
      write_00405 = append_buf(write_00405, &write_00405_len, write_00405_00000, write_00405_00000_len);
      if (write_00405_len > 0) {
         transmit_all(1, write_00405, write_00405_len);
      }
      free(write_00405);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00406 = NULL;
      unsigned int write_00406_len = 0;
      write_00406 = append_var("jumpright", write_00406, &write_00406_len);
      if (write_00406_len > 0) {
         transmit_all(1, write_00406, write_00406_len);
      }
      free(write_00406);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00407_00000[] = 
         "\x0a";
      static unsigned int write_00407_00000_len = 1;
      unsigned char *write_00407 = NULL;
      unsigned int write_00407_len = 0;
      write_00407 = append_buf(write_00407, &write_00407_len, write_00407_00000, write_00407_00000_len);
      if (write_00407_len > 0) {
         transmit_all(1, write_00407, write_00407_len);
      }
      free(write_00407);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00408 = NULL;
      unsigned int write_00408_len = 0;
      write_00408 = append_var("wait", write_00408, &write_00408_len);
      if (write_00408_len > 0) {
         transmit_all(1, write_00408, write_00408_len);
      }
      free(write_00408);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00409_00000[] = 
         "\x0a";
      static unsigned int write_00409_00000_len = 1;
      unsigned char *write_00409 = NULL;
      unsigned int write_00409_len = 0;
      write_00409 = append_buf(write_00409, &write_00409_len, write_00409_00000, write_00409_00000_len);
      if (write_00409_len > 0) {
         transmit_all(1, write_00409, write_00409_len);
      }
      free(write_00409);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00410 = NULL;
      unsigned int write_00410_len = 0;
      write_00410 = append_var("jumpright", write_00410, &write_00410_len);
      if (write_00410_len > 0) {
         transmit_all(1, write_00410, write_00410_len);
      }
      free(write_00410);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00411_00000[] = 
         "\x0a";
      static unsigned int write_00411_00000_len = 1;
      unsigned char *write_00411 = NULL;
      unsigned int write_00411_len = 0;
      write_00411 = append_buf(write_00411, &write_00411_len, write_00411_00000, write_00411_00000_len);
      if (write_00411_len > 0) {
         transmit_all(1, write_00411, write_00411_len);
      }
      free(write_00411);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00412 = NULL;
      unsigned int write_00412_len = 0;
      write_00412 = append_var("right", write_00412, &write_00412_len);
      if (write_00412_len > 0) {
         transmit_all(1, write_00412, write_00412_len);
      }
      free(write_00412);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00413_00000[] = 
         "\x0a";
      static unsigned int write_00413_00000_len = 1;
      unsigned char *write_00413 = NULL;
      unsigned int write_00413_len = 0;
      write_00413 = append_buf(write_00413, &write_00413_len, write_00413_00000, write_00413_00000_len);
      if (write_00413_len > 0) {
         transmit_all(1, write_00413, write_00413_len);
      }
      free(write_00413);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00414 = NULL;
      unsigned int write_00414_len = 0;
      write_00414 = append_var("right", write_00414, &write_00414_len);
      if (write_00414_len > 0) {
         transmit_all(1, write_00414, write_00414_len);
      }
      free(write_00414);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00415_00000[] = 
         "\x0a";
      static unsigned int write_00415_00000_len = 1;
      unsigned char *write_00415 = NULL;
      unsigned int write_00415_len = 0;
      write_00415 = append_buf(write_00415, &write_00415_len, write_00415_00000, write_00415_00000_len);
      if (write_00415_len > 0) {
         transmit_all(1, write_00415, write_00415_len);
      }
      free(write_00415);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00416 = NULL;
      unsigned int write_00416_len = 0;
      write_00416 = append_var("right", write_00416, &write_00416_len);
      if (write_00416_len > 0) {
         transmit_all(1, write_00416, write_00416_len);
      }
      free(write_00416);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00417_00000[] = 
         "\x0a";
      static unsigned int write_00417_00000_len = 1;
      unsigned char *write_00417 = NULL;
      unsigned int write_00417_len = 0;
      write_00417 = append_buf(write_00417, &write_00417_len, write_00417_00000, write_00417_00000_len);
      if (write_00417_len > 0) {
         transmit_all(1, write_00417, write_00417_len);
      }
      free(write_00417);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00418 = NULL;
      unsigned int write_00418_len = 0;
      write_00418 = append_var("right", write_00418, &write_00418_len);
      if (write_00418_len > 0) {
         transmit_all(1, write_00418, write_00418_len);
      }
      free(write_00418);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00419_00000[] = 
         "\x0a";
      static unsigned int write_00419_00000_len = 1;
      unsigned char *write_00419 = NULL;
      unsigned int write_00419_len = 0;
      write_00419 = append_buf(write_00419, &write_00419_len, write_00419_00000, write_00419_00000_len);
      if (write_00419_len > 0) {
         transmit_all(1, write_00419, write_00419_len);
      }
      free(write_00419);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00420 = NULL;
      unsigned int write_00420_len = 0;
      write_00420 = append_var("right", write_00420, &write_00420_len);
      if (write_00420_len > 0) {
         transmit_all(1, write_00420, write_00420_len);
      }
      free(write_00420);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00421_00000[] = 
         "\x0a";
      static unsigned int write_00421_00000_len = 1;
      unsigned char *write_00421 = NULL;
      unsigned int write_00421_len = 0;
      write_00421 = append_buf(write_00421, &write_00421_len, write_00421_00000, write_00421_00000_len);
      if (write_00421_len > 0) {
         transmit_all(1, write_00421, write_00421_len);
      }
      free(write_00421);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00422 = NULL;
      unsigned int write_00422_len = 0;
      write_00422 = append_var("right", write_00422, &write_00422_len);
      if (write_00422_len > 0) {
         transmit_all(1, write_00422, write_00422_len);
      }
      free(write_00422);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00423_00000[] = 
         "\x0a";
      static unsigned int write_00423_00000_len = 1;
      unsigned char *write_00423 = NULL;
      unsigned int write_00423_len = 0;
      write_00423 = append_buf(write_00423, &write_00423_len, write_00423_00000, write_00423_00000_len);
      if (write_00423_len > 0) {
         transmit_all(1, write_00423, write_00423_len);
      }
      free(write_00423);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00424 = NULL;
      unsigned int write_00424_len = 0;
      write_00424 = append_var("right", write_00424, &write_00424_len);
      if (write_00424_len > 0) {
         transmit_all(1, write_00424, write_00424_len);
      }
      free(write_00424);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00425_00000[] = 
         "\x0a";
      static unsigned int write_00425_00000_len = 1;
      unsigned char *write_00425 = NULL;
      unsigned int write_00425_len = 0;
      write_00425 = append_buf(write_00425, &write_00425_len, write_00425_00000, write_00425_00000_len);
      if (write_00425_len > 0) {
         transmit_all(1, write_00425, write_00425_len);
      }
      free(write_00425);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00426 = NULL;
      unsigned int write_00426_len = 0;
      write_00426 = append_var("right", write_00426, &write_00426_len);
      if (write_00426_len > 0) {
         transmit_all(1, write_00426, write_00426_len);
      }
      free(write_00426);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00427_00000[] = 
         "\x0a";
      static unsigned int write_00427_00000_len = 1;
      unsigned char *write_00427 = NULL;
      unsigned int write_00427_len = 0;
      write_00427 = append_buf(write_00427, &write_00427_len, write_00427_00000, write_00427_00000_len);
      if (write_00427_len > 0) {
         transmit_all(1, write_00427, write_00427_len);
      }
      free(write_00427);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00428 = NULL;
      unsigned int write_00428_len = 0;
      write_00428 = append_var("right", write_00428, &write_00428_len);
      if (write_00428_len > 0) {
         transmit_all(1, write_00428, write_00428_len);
      }
      free(write_00428);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00429_00000[] = 
         "\x0a";
      static unsigned int write_00429_00000_len = 1;
      unsigned char *write_00429 = NULL;
      unsigned int write_00429_len = 0;
      write_00429 = append_buf(write_00429, &write_00429_len, write_00429_00000, write_00429_00000_len);
      if (write_00429_len > 0) {
         transmit_all(1, write_00429, write_00429_len);
      }
      free(write_00429);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00430 = NULL;
      unsigned int write_00430_len = 0;
      write_00430 = append_var("right", write_00430, &write_00430_len);
      if (write_00430_len > 0) {
         transmit_all(1, write_00430, write_00430_len);
      }
      free(write_00430);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00431_00000[] = 
         "\x0a";
      static unsigned int write_00431_00000_len = 1;
      unsigned char *write_00431 = NULL;
      unsigned int write_00431_len = 0;
      write_00431 = append_buf(write_00431, &write_00431_len, write_00431_00000, write_00431_00000_len);
      if (write_00431_len > 0) {
         transmit_all(1, write_00431, write_00431_len);
      }
      free(write_00431);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00432 = NULL;
      unsigned int write_00432_len = 0;
      write_00432 = append_var("right", write_00432, &write_00432_len);
      if (write_00432_len > 0) {
         transmit_all(1, write_00432, write_00432_len);
      }
      free(write_00432);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00433_00000[] = 
         "\x0a";
      static unsigned int write_00433_00000_len = 1;
      unsigned char *write_00433 = NULL;
      unsigned int write_00433_len = 0;
      write_00433 = append_buf(write_00433, &write_00433_len, write_00433_00000, write_00433_00000_len);
      if (write_00433_len > 0) {
         transmit_all(1, write_00433, write_00433_len);
      }
      free(write_00433);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00434 = NULL;
      unsigned int write_00434_len = 0;
      write_00434 = append_var("wait", write_00434, &write_00434_len);
      if (write_00434_len > 0) {
         transmit_all(1, write_00434, write_00434_len);
      }
      free(write_00434);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00435_00000[] = 
         "\x0a";
      static unsigned int write_00435_00000_len = 1;
      unsigned char *write_00435 = NULL;
      unsigned int write_00435_len = 0;
      write_00435 = append_buf(write_00435, &write_00435_len, write_00435_00000, write_00435_00000_len);
      if (write_00435_len > 0) {
         transmit_all(1, write_00435, write_00435_len);
      }
      free(write_00435);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00436 = NULL;
      unsigned int write_00436_len = 0;
      write_00436 = append_var("wait", write_00436, &write_00436_len);
      if (write_00436_len > 0) {
         transmit_all(1, write_00436, write_00436_len);
      }
      free(write_00436);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00437_00000[] = 
         "\x0a";
      static unsigned int write_00437_00000_len = 1;
      unsigned char *write_00437 = NULL;
      unsigned int write_00437_len = 0;
      write_00437 = append_buf(write_00437, &write_00437_len, write_00437_00000, write_00437_00000_len);
      if (write_00437_len > 0) {
         transmit_all(1, write_00437, write_00437_len);
      }
      free(write_00437);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00438 = NULL;
      unsigned int write_00438_len = 0;
      write_00438 = append_var("wait", write_00438, &write_00438_len);
      if (write_00438_len > 0) {
         transmit_all(1, write_00438, write_00438_len);
      }
      free(write_00438);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00439_00000[] = 
         "\x0a";
      static unsigned int write_00439_00000_len = 1;
      unsigned char *write_00439 = NULL;
      unsigned int write_00439_len = 0;
      write_00439 = append_buf(write_00439, &write_00439_len, write_00439_00000, write_00439_00000_len);
      if (write_00439_len > 0) {
         transmit_all(1, write_00439, write_00439_len);
      }
      free(write_00439);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00440 = NULL;
      unsigned int write_00440_len = 0;
      write_00440 = append_var("wait", write_00440, &write_00440_len);
      if (write_00440_len > 0) {
         transmit_all(1, write_00440, write_00440_len);
      }
      free(write_00440);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00441_00000[] = 
         "\x0a";
      static unsigned int write_00441_00000_len = 1;
      unsigned char *write_00441 = NULL;
      unsigned int write_00441_len = 0;
      write_00441 = append_buf(write_00441, &write_00441_len, write_00441_00000, write_00441_00000_len);
      if (write_00441_len > 0) {
         transmit_all(1, write_00441, write_00441_len);
      }
      free(write_00441);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00442 = NULL;
      unsigned int write_00442_len = 0;
      write_00442 = append_var("wait", write_00442, &write_00442_len);
      if (write_00442_len > 0) {
         transmit_all(1, write_00442, write_00442_len);
      }
      free(write_00442);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00443_00000[] = 
         "\x0a";
      static unsigned int write_00443_00000_len = 1;
      unsigned char *write_00443 = NULL;
      unsigned int write_00443_len = 0;
      write_00443 = append_buf(write_00443, &write_00443_len, write_00443_00000, write_00443_00000_len);
      if (write_00443_len > 0) {
         transmit_all(1, write_00443, write_00443_len);
      }
      free(write_00443);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00444 = NULL;
      unsigned int write_00444_len = 0;
      write_00444 = append_var("wait", write_00444, &write_00444_len);
      if (write_00444_len > 0) {
         transmit_all(1, write_00444, write_00444_len);
      }
      free(write_00444);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00445_00000[] = 
         "\x0a";
      static unsigned int write_00445_00000_len = 1;
      unsigned char *write_00445 = NULL;
      unsigned int write_00445_len = 0;
      write_00445 = append_buf(write_00445, &write_00445_len, write_00445_00000, write_00445_00000_len);
      if (write_00445_len > 0) {
         transmit_all(1, write_00445, write_00445_len);
      }
      free(write_00445);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00446 = NULL;
      unsigned int write_00446_len = 0;
      write_00446 = append_var("wait", write_00446, &write_00446_len);
      if (write_00446_len > 0) {
         transmit_all(1, write_00446, write_00446_len);
      }
      free(write_00446);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00447_00000[] = 
         "\x0a";
      static unsigned int write_00447_00000_len = 1;
      unsigned char *write_00447 = NULL;
      unsigned int write_00447_len = 0;
      write_00447 = append_buf(write_00447, &write_00447_len, write_00447_00000, write_00447_00000_len);
      if (write_00447_len > 0) {
         transmit_all(1, write_00447, write_00447_len);
      }
      free(write_00447);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00448 = NULL;
      unsigned int write_00448_len = 0;
      write_00448 = append_var("wait", write_00448, &write_00448_len);
      if (write_00448_len > 0) {
         transmit_all(1, write_00448, write_00448_len);
      }
      free(write_00448);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00449_00000[] = 
         "\x0a";
      static unsigned int write_00449_00000_len = 1;
      unsigned char *write_00449 = NULL;
      unsigned int write_00449_len = 0;
      write_00449 = append_buf(write_00449, &write_00449_len, write_00449_00000, write_00449_00000_len);
      if (write_00449_len > 0) {
         transmit_all(1, write_00449, write_00449_len);
      }
      free(write_00449);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00450 = NULL;
      unsigned int write_00450_len = 0;
      write_00450 = append_var("wait", write_00450, &write_00450_len);
      if (write_00450_len > 0) {
         transmit_all(1, write_00450, write_00450_len);
      }
      free(write_00450);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00451_00000[] = 
         "\x0a";
      static unsigned int write_00451_00000_len = 1;
      unsigned char *write_00451 = NULL;
      unsigned int write_00451_len = 0;
      write_00451 = append_buf(write_00451, &write_00451_len, write_00451_00000, write_00451_00000_len);
      if (write_00451_len > 0) {
         transmit_all(1, write_00451, write_00451_len);
      }
      free(write_00451);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00452 = NULL;
      unsigned int write_00452_len = 0;
      write_00452 = append_var("wait", write_00452, &write_00452_len);
      if (write_00452_len > 0) {
         transmit_all(1, write_00452, write_00452_len);
      }
      free(write_00452);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00453_00000[] = 
         "\x0a";
      static unsigned int write_00453_00000_len = 1;
      unsigned char *write_00453 = NULL;
      unsigned int write_00453_len = 0;
      write_00453 = append_buf(write_00453, &write_00453_len, write_00453_00000, write_00453_00000_len);
      if (write_00453_len > 0) {
         transmit_all(1, write_00453, write_00453_len);
      }
      free(write_00453);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00454 = NULL;
      unsigned int write_00454_len = 0;
      write_00454 = append_var("right", write_00454, &write_00454_len);
      if (write_00454_len > 0) {
         transmit_all(1, write_00454, write_00454_len);
      }
      free(write_00454);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00455_00000[] = 
         "\x0a";
      static unsigned int write_00455_00000_len = 1;
      unsigned char *write_00455 = NULL;
      unsigned int write_00455_len = 0;
      write_00455 = append_buf(write_00455, &write_00455_len, write_00455_00000, write_00455_00000_len);
      if (write_00455_len > 0) {
         transmit_all(1, write_00455, write_00455_len);
      }
      free(write_00455);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00456 = NULL;
      unsigned int write_00456_len = 0;
      write_00456 = append_var("jumpleft", write_00456, &write_00456_len);
      if (write_00456_len > 0) {
         transmit_all(1, write_00456, write_00456_len);
      }
      free(write_00456);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00457_00000[] = 
         "\x0a";
      static unsigned int write_00457_00000_len = 1;
      unsigned char *write_00457 = NULL;
      unsigned int write_00457_len = 0;
      write_00457 = append_buf(write_00457, &write_00457_len, write_00457_00000, write_00457_00000_len);
      if (write_00457_len > 0) {
         transmit_all(1, write_00457, write_00457_len);
      }
      free(write_00457);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00458 = NULL;
      unsigned int write_00458_len = 0;
      write_00458 = append_var("left", write_00458, &write_00458_len);
      if (write_00458_len > 0) {
         transmit_all(1, write_00458, write_00458_len);
      }
      free(write_00458);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00459_00000[] = 
         "\x0a";
      static unsigned int write_00459_00000_len = 1;
      unsigned char *write_00459 = NULL;
      unsigned int write_00459_len = 0;
      write_00459 = append_buf(write_00459, &write_00459_len, write_00459_00000, write_00459_00000_len);
      if (write_00459_len > 0) {
         transmit_all(1, write_00459, write_00459_len);
      }
      free(write_00459);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00460 = NULL;
      unsigned int write_00460_len = 0;
      write_00460 = append_var("left", write_00460, &write_00460_len);
      if (write_00460_len > 0) {
         transmit_all(1, write_00460, write_00460_len);
      }
      free(write_00460);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00461_00000[] = 
         "\x0a";
      static unsigned int write_00461_00000_len = 1;
      unsigned char *write_00461 = NULL;
      unsigned int write_00461_len = 0;
      write_00461 = append_buf(write_00461, &write_00461_len, write_00461_00000, write_00461_00000_len);
      if (write_00461_len > 0) {
         transmit_all(1, write_00461, write_00461_len);
      }
      free(write_00461);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00462 = NULL;
      unsigned int write_00462_len = 0;
      write_00462 = append_var("jumpright", write_00462, &write_00462_len);
      if (write_00462_len > 0) {
         transmit_all(1, write_00462, write_00462_len);
      }
      free(write_00462);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00463_00000[] = 
         "\x0a";
      static unsigned int write_00463_00000_len = 1;
      unsigned char *write_00463 = NULL;
      unsigned int write_00463_len = 0;
      write_00463 = append_buf(write_00463, &write_00463_len, write_00463_00000, write_00463_00000_len);
      if (write_00463_len > 0) {
         transmit_all(1, write_00463, write_00463_len);
      }
      free(write_00463);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00464 = NULL;
      unsigned int write_00464_len = 0;
      write_00464 = append_var("right", write_00464, &write_00464_len);
      if (write_00464_len > 0) {
         transmit_all(1, write_00464, write_00464_len);
      }
      free(write_00464);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00465_00000[] = 
         "\x0a";
      static unsigned int write_00465_00000_len = 1;
      unsigned char *write_00465 = NULL;
      unsigned int write_00465_len = 0;
      write_00465 = append_buf(write_00465, &write_00465_len, write_00465_00000, write_00465_00000_len);
      if (write_00465_len > 0) {
         transmit_all(1, write_00465, write_00465_len);
      }
      free(write_00465);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00466 = NULL;
      unsigned int write_00466_len = 0;
      write_00466 = append_var("wait", write_00466, &write_00466_len);
      if (write_00466_len > 0) {
         transmit_all(1, write_00466, write_00466_len);
      }
      free(write_00466);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00467_00000[] = 
         "\x0a";
      static unsigned int write_00467_00000_len = 1;
      unsigned char *write_00467 = NULL;
      unsigned int write_00467_len = 0;
      write_00467 = append_buf(write_00467, &write_00467_len, write_00467_00000, write_00467_00000_len);
      if (write_00467_len > 0) {
         transmit_all(1, write_00467, write_00467_len);
      }
      free(write_00467);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00468 = NULL;
      unsigned int write_00468_len = 0;
      write_00468 = append_var("wait", write_00468, &write_00468_len);
      if (write_00468_len > 0) {
         transmit_all(1, write_00468, write_00468_len);
      }
      free(write_00468);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00469_00000[] = 
         "\x0a";
      static unsigned int write_00469_00000_len = 1;
      unsigned char *write_00469 = NULL;
      unsigned int write_00469_len = 0;
      write_00469 = append_buf(write_00469, &write_00469_len, write_00469_00000, write_00469_00000_len);
      if (write_00469_len > 0) {
         transmit_all(1, write_00469, write_00469_len);
      }
      free(write_00469);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00470 = NULL;
      unsigned int write_00470_len = 0;
      write_00470 = append_var("wait", write_00470, &write_00470_len);
      if (write_00470_len > 0) {
         transmit_all(1, write_00470, write_00470_len);
      }
      free(write_00470);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00471_00000[] = 
         "\x0a";
      static unsigned int write_00471_00000_len = 1;
      unsigned char *write_00471 = NULL;
      unsigned int write_00471_len = 0;
      write_00471 = append_buf(write_00471, &write_00471_len, write_00471_00000, write_00471_00000_len);
      if (write_00471_len > 0) {
         transmit_all(1, write_00471, write_00471_len);
      }
      free(write_00471);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00472 = NULL;
      unsigned int write_00472_len = 0;
      write_00472 = append_var("wait", write_00472, &write_00472_len);
      if (write_00472_len > 0) {
         transmit_all(1, write_00472, write_00472_len);
      }
      free(write_00472);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00473_00000[] = 
         "\x0a";
      static unsigned int write_00473_00000_len = 1;
      unsigned char *write_00473 = NULL;
      unsigned int write_00473_len = 0;
      write_00473 = append_buf(write_00473, &write_00473_len, write_00473_00000, write_00473_00000_len);
      if (write_00473_len > 0) {
         transmit_all(1, write_00473, write_00473_len);
      }
      free(write_00473);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00474 = NULL;
      unsigned int write_00474_len = 0;
      write_00474 = append_var("wait", write_00474, &write_00474_len);
      if (write_00474_len > 0) {
         transmit_all(1, write_00474, write_00474_len);
      }
      free(write_00474);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00475_00000[] = 
         "\x0a";
      static unsigned int write_00475_00000_len = 1;
      unsigned char *write_00475 = NULL;
      unsigned int write_00475_len = 0;
      write_00475 = append_buf(write_00475, &write_00475_len, write_00475_00000, write_00475_00000_len);
      if (write_00475_len > 0) {
         transmit_all(1, write_00475, write_00475_len);
      }
      free(write_00475);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00476 = NULL;
      unsigned int write_00476_len = 0;
      write_00476 = append_var("wait", write_00476, &write_00476_len);
      if (write_00476_len > 0) {
         transmit_all(1, write_00476, write_00476_len);
      }
      free(write_00476);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00477_00000[] = 
         "\x0a";
      static unsigned int write_00477_00000_len = 1;
      unsigned char *write_00477 = NULL;
      unsigned int write_00477_len = 0;
      write_00477 = append_buf(write_00477, &write_00477_len, write_00477_00000, write_00477_00000_len);
      if (write_00477_len > 0) {
         transmit_all(1, write_00477, write_00477_len);
      }
      free(write_00477);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00478 = NULL;
      unsigned int write_00478_len = 0;
      write_00478 = append_var("wait", write_00478, &write_00478_len);
      if (write_00478_len > 0) {
         transmit_all(1, write_00478, write_00478_len);
      }
      free(write_00478);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00479_00000[] = 
         "\x0a";
      static unsigned int write_00479_00000_len = 1;
      unsigned char *write_00479 = NULL;
      unsigned int write_00479_len = 0;
      write_00479 = append_buf(write_00479, &write_00479_len, write_00479_00000, write_00479_00000_len);
      if (write_00479_len > 0) {
         transmit_all(1, write_00479, write_00479_len);
      }
      free(write_00479);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00480 = NULL;
      unsigned int write_00480_len = 0;
      write_00480 = append_var("wait", write_00480, &write_00480_len);
      if (write_00480_len > 0) {
         transmit_all(1, write_00480, write_00480_len);
      }
      free(write_00480);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00481_00000[] = 
         "\x0a";
      static unsigned int write_00481_00000_len = 1;
      unsigned char *write_00481 = NULL;
      unsigned int write_00481_len = 0;
      write_00481 = append_buf(write_00481, &write_00481_len, write_00481_00000, write_00481_00000_len);
      if (write_00481_len > 0) {
         transmit_all(1, write_00481, write_00481_len);
      }
      free(write_00481);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00482 = NULL;
      unsigned int write_00482_len = 0;
      write_00482 = append_var("wait", write_00482, &write_00482_len);
      if (write_00482_len > 0) {
         transmit_all(1, write_00482, write_00482_len);
      }
      free(write_00482);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00483_00000[] = 
         "\x0a";
      static unsigned int write_00483_00000_len = 1;
      unsigned char *write_00483 = NULL;
      unsigned int write_00483_len = 0;
      write_00483 = append_buf(write_00483, &write_00483_len, write_00483_00000, write_00483_00000_len);
      if (write_00483_len > 0) {
         transmit_all(1, write_00483, write_00483_len);
      }
      free(write_00483);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00484 = NULL;
      unsigned int write_00484_len = 0;
      write_00484 = append_var("wait", write_00484, &write_00484_len);
      if (write_00484_len > 0) {
         transmit_all(1, write_00484, write_00484_len);
      }
      free(write_00484);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00485_00000[] = 
         "\x0a";
      static unsigned int write_00485_00000_len = 1;
      unsigned char *write_00485 = NULL;
      unsigned int write_00485_len = 0;
      write_00485 = append_buf(write_00485, &write_00485_len, write_00485_00000, write_00485_00000_len);
      if (write_00485_len > 0) {
         transmit_all(1, write_00485, write_00485_len);
      }
      free(write_00485);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00486 = NULL;
      unsigned int write_00486_len = 0;
      write_00486 = append_var("wait", write_00486, &write_00486_len);
      if (write_00486_len > 0) {
         transmit_all(1, write_00486, write_00486_len);
      }
      free(write_00486);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00487_00000[] = 
         "\x0a";
      static unsigned int write_00487_00000_len = 1;
      unsigned char *write_00487 = NULL;
      unsigned int write_00487_len = 0;
      write_00487 = append_buf(write_00487, &write_00487_len, write_00487_00000, write_00487_00000_len);
      if (write_00487_len > 0) {
         transmit_all(1, write_00487, write_00487_len);
      }
      free(write_00487);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00488 = NULL;
      unsigned int write_00488_len = 0;
      write_00488 = append_var("wait", write_00488, &write_00488_len);
      if (write_00488_len > 0) {
         transmit_all(1, write_00488, write_00488_len);
      }
      free(write_00488);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00489_00000[] = 
         "\x0a";
      static unsigned int write_00489_00000_len = 1;
      unsigned char *write_00489 = NULL;
      unsigned int write_00489_len = 0;
      write_00489 = append_buf(write_00489, &write_00489_len, write_00489_00000, write_00489_00000_len);
      if (write_00489_len > 0) {
         transmit_all(1, write_00489, write_00489_len);
      }
      free(write_00489);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00490 = NULL;
      unsigned int write_00490_len = 0;
      write_00490 = append_var("wait", write_00490, &write_00490_len);
      if (write_00490_len > 0) {
         transmit_all(1, write_00490, write_00490_len);
      }
      free(write_00490);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00491_00000[] = 
         "\x0a";
      static unsigned int write_00491_00000_len = 1;
      unsigned char *write_00491 = NULL;
      unsigned int write_00491_len = 0;
      write_00491 = append_buf(write_00491, &write_00491_len, write_00491_00000, write_00491_00000_len);
      if (write_00491_len > 0) {
         transmit_all(1, write_00491, write_00491_len);
      }
      free(write_00491);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00492 = NULL;
      unsigned int write_00492_len = 0;
      write_00492 = append_var("wait", write_00492, &write_00492_len);
      if (write_00492_len > 0) {
         transmit_all(1, write_00492, write_00492_len);
      }
      free(write_00492);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00493_00000[] = 
         "\x0a";
      static unsigned int write_00493_00000_len = 1;
      unsigned char *write_00493 = NULL;
      unsigned int write_00493_len = 0;
      write_00493 = append_buf(write_00493, &write_00493_len, write_00493_00000, write_00493_00000_len);
      if (write_00493_len > 0) {
         transmit_all(1, write_00493, write_00493_len);
      }
      free(write_00493);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00494 = NULL;
      unsigned int write_00494_len = 0;
      write_00494 = append_var("wait", write_00494, &write_00494_len);
      if (write_00494_len > 0) {
         transmit_all(1, write_00494, write_00494_len);
      }
      free(write_00494);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00495_00000[] = 
         "\x0a";
      static unsigned int write_00495_00000_len = 1;
      unsigned char *write_00495 = NULL;
      unsigned int write_00495_len = 0;
      write_00495 = append_buf(write_00495, &write_00495_len, write_00495_00000, write_00495_00000_len);
      if (write_00495_len > 0) {
         transmit_all(1, write_00495, write_00495_len);
      }
      free(write_00495);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00496 = NULL;
      unsigned int write_00496_len = 0;
      write_00496 = append_var("wait", write_00496, &write_00496_len);
      if (write_00496_len > 0) {
         transmit_all(1, write_00496, write_00496_len);
      }
      free(write_00496);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00497_00000[] = 
         "\x0a";
      static unsigned int write_00497_00000_len = 1;
      unsigned char *write_00497 = NULL;
      unsigned int write_00497_len = 0;
      write_00497 = append_buf(write_00497, &write_00497_len, write_00497_00000, write_00497_00000_len);
      if (write_00497_len > 0) {
         transmit_all(1, write_00497, write_00497_len);
      }
      free(write_00497);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00498 = NULL;
      unsigned int write_00498_len = 0;
      write_00498 = append_var("wait", write_00498, &write_00498_len);
      if (write_00498_len > 0) {
         transmit_all(1, write_00498, write_00498_len);
      }
      free(write_00498);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00499_00000[] = 
         "\x0a";
      static unsigned int write_00499_00000_len = 1;
      unsigned char *write_00499 = NULL;
      unsigned int write_00499_len = 0;
      write_00499 = append_buf(write_00499, &write_00499_len, write_00499_00000, write_00499_00000_len);
      if (write_00499_len > 0) {
         transmit_all(1, write_00499, write_00499_len);
      }
      free(write_00499);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00500 = NULL;
      unsigned int write_00500_len = 0;
      write_00500 = append_var("wait", write_00500, &write_00500_len);
      if (write_00500_len > 0) {
         transmit_all(1, write_00500, write_00500_len);
      }
      free(write_00500);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00501_00000[] = 
         "\x0a";
      static unsigned int write_00501_00000_len = 1;
      unsigned char *write_00501 = NULL;
      unsigned int write_00501_len = 0;
      write_00501 = append_buf(write_00501, &write_00501_len, write_00501_00000, write_00501_00000_len);
      if (write_00501_len > 0) {
         transmit_all(1, write_00501, write_00501_len);
      }
      free(write_00501);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00502 = NULL;
      unsigned int write_00502_len = 0;
      write_00502 = append_var("wait", write_00502, &write_00502_len);
      if (write_00502_len > 0) {
         transmit_all(1, write_00502, write_00502_len);
      }
      free(write_00502);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00503_00000[] = 
         "\x0a";
      static unsigned int write_00503_00000_len = 1;
      unsigned char *write_00503 = NULL;
      unsigned int write_00503_len = 0;
      write_00503 = append_buf(write_00503, &write_00503_len, write_00503_00000, write_00503_00000_len);
      if (write_00503_len > 0) {
         transmit_all(1, write_00503, write_00503_len);
      }
      free(write_00503);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00504 = NULL;
      unsigned int write_00504_len = 0;
      write_00504 = append_var("wait", write_00504, &write_00504_len);
      if (write_00504_len > 0) {
         transmit_all(1, write_00504, write_00504_len);
      }
      free(write_00504);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00505_00000[] = 
         "\x0a";
      static unsigned int write_00505_00000_len = 1;
      unsigned char *write_00505 = NULL;
      unsigned int write_00505_len = 0;
      write_00505 = append_buf(write_00505, &write_00505_len, write_00505_00000, write_00505_00000_len);
      if (write_00505_len > 0) {
         transmit_all(1, write_00505, write_00505_len);
      }
      free(write_00505);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00506 = NULL;
      unsigned int write_00506_len = 0;
      write_00506 = append_var("wait", write_00506, &write_00506_len);
      if (write_00506_len > 0) {
         transmit_all(1, write_00506, write_00506_len);
      }
      free(write_00506);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00507_00000[] = 
         "\x0a";
      static unsigned int write_00507_00000_len = 1;
      unsigned char *write_00507 = NULL;
      unsigned int write_00507_len = 0;
      write_00507 = append_buf(write_00507, &write_00507_len, write_00507_00000, write_00507_00000_len);
      if (write_00507_len > 0) {
         transmit_all(1, write_00507, write_00507_len);
      }
      free(write_00507);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00508 = NULL;
      unsigned int write_00508_len = 0;
      write_00508 = append_var("wait", write_00508, &write_00508_len);
      if (write_00508_len > 0) {
         transmit_all(1, write_00508, write_00508_len);
      }
      free(write_00508);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00509_00000[] = 
         "\x0a";
      static unsigned int write_00509_00000_len = 1;
      unsigned char *write_00509 = NULL;
      unsigned int write_00509_len = 0;
      write_00509 = append_buf(write_00509, &write_00509_len, write_00509_00000, write_00509_00000_len);
      if (write_00509_len > 0) {
         transmit_all(1, write_00509, write_00509_len);
      }
      free(write_00509);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00510 = NULL;
      unsigned int write_00510_len = 0;
      write_00510 = append_var("wait", write_00510, &write_00510_len);
      if (write_00510_len > 0) {
         transmit_all(1, write_00510, write_00510_len);
      }
      free(write_00510);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00511_00000[] = 
         "\x0a";
      static unsigned int write_00511_00000_len = 1;
      unsigned char *write_00511 = NULL;
      unsigned int write_00511_len = 0;
      write_00511 = append_buf(write_00511, &write_00511_len, write_00511_00000, write_00511_00000_len);
      if (write_00511_len > 0) {
         transmit_all(1, write_00511, write_00511_len);
      }
      free(write_00511);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00512 = NULL;
      unsigned int write_00512_len = 0;
      write_00512 = append_var("wait", write_00512, &write_00512_len);
      if (write_00512_len > 0) {
         transmit_all(1, write_00512, write_00512_len);
      }
      free(write_00512);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00513_00000[] = 
         "\x0a";
      static unsigned int write_00513_00000_len = 1;
      unsigned char *write_00513 = NULL;
      unsigned int write_00513_len = 0;
      write_00513 = append_buf(write_00513, &write_00513_len, write_00513_00000, write_00513_00000_len);
      if (write_00513_len > 0) {
         transmit_all(1, write_00513, write_00513_len);
      }
      free(write_00513);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00514 = NULL;
      unsigned int write_00514_len = 0;
      write_00514 = append_var("left", write_00514, &write_00514_len);
      if (write_00514_len > 0) {
         transmit_all(1, write_00514, write_00514_len);
      }
      free(write_00514);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00515_00000[] = 
         "\x0a";
      static unsigned int write_00515_00000_len = 1;
      unsigned char *write_00515 = NULL;
      unsigned int write_00515_len = 0;
      write_00515 = append_buf(write_00515, &write_00515_len, write_00515_00000, write_00515_00000_len);
      if (write_00515_len > 0) {
         transmit_all(1, write_00515, write_00515_len);
      }
      free(write_00515);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00516 = NULL;
      unsigned int write_00516_len = 0;
      write_00516 = append_var("right", write_00516, &write_00516_len);
      if (write_00516_len > 0) {
         transmit_all(1, write_00516, write_00516_len);
      }
      free(write_00516);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00517_00000[] = 
         "\x0a";
      static unsigned int write_00517_00000_len = 1;
      unsigned char *write_00517 = NULL;
      unsigned int write_00517_len = 0;
      write_00517 = append_buf(write_00517, &write_00517_len, write_00517_00000, write_00517_00000_len);
      if (write_00517_len > 0) {
         transmit_all(1, write_00517, write_00517_len);
      }
      free(write_00517);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00518 = NULL;
      unsigned int write_00518_len = 0;
      write_00518 = append_var("right", write_00518, &write_00518_len);
      if (write_00518_len > 0) {
         transmit_all(1, write_00518, write_00518_len);
      }
      free(write_00518);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00519_00000[] = 
         "\x0a";
      static unsigned int write_00519_00000_len = 1;
      unsigned char *write_00519 = NULL;
      unsigned int write_00519_len = 0;
      write_00519 = append_buf(write_00519, &write_00519_len, write_00519_00000, write_00519_00000_len);
      if (write_00519_len > 0) {
         transmit_all(1, write_00519, write_00519_len);
      }
      free(write_00519);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00520 = NULL;
      unsigned int write_00520_len = 0;
      write_00520 = append_var("right", write_00520, &write_00520_len);
      if (write_00520_len > 0) {
         transmit_all(1, write_00520, write_00520_len);
      }
      free(write_00520);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00521_00000[] = 
         "\x0a";
      static unsigned int write_00521_00000_len = 1;
      unsigned char *write_00521 = NULL;
      unsigned int write_00521_len = 0;
      write_00521 = append_buf(write_00521, &write_00521_len, write_00521_00000, write_00521_00000_len);
      if (write_00521_len > 0) {
         transmit_all(1, write_00521, write_00521_len);
      }
      free(write_00521);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00522 = NULL;
      unsigned int write_00522_len = 0;
      write_00522 = append_var("right", write_00522, &write_00522_len);
      if (write_00522_len > 0) {
         transmit_all(1, write_00522, write_00522_len);
      }
      free(write_00522);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00523_00000[] = 
         "\x0a";
      static unsigned int write_00523_00000_len = 1;
      unsigned char *write_00523 = NULL;
      unsigned int write_00523_len = 0;
      write_00523 = append_buf(write_00523, &write_00523_len, write_00523_00000, write_00523_00000_len);
      if (write_00523_len > 0) {
         transmit_all(1, write_00523, write_00523_len);
      }
      free(write_00523);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00524 = NULL;
      unsigned int write_00524_len = 0;
      write_00524 = append_var("right", write_00524, &write_00524_len);
      if (write_00524_len > 0) {
         transmit_all(1, write_00524, write_00524_len);
      }
      free(write_00524);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00525_00000[] = 
         "\x0a";
      static unsigned int write_00525_00000_len = 1;
      unsigned char *write_00525 = NULL;
      unsigned int write_00525_len = 0;
      write_00525 = append_buf(write_00525, &write_00525_len, write_00525_00000, write_00525_00000_len);
      if (write_00525_len > 0) {
         transmit_all(1, write_00525, write_00525_len);
      }
      free(write_00525);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00526 = NULL;
      unsigned int write_00526_len = 0;
      write_00526 = append_var("right", write_00526, &write_00526_len);
      if (write_00526_len > 0) {
         transmit_all(1, write_00526, write_00526_len);
      }
      free(write_00526);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00527_00000[] = 
         "\x0a";
      static unsigned int write_00527_00000_len = 1;
      unsigned char *write_00527 = NULL;
      unsigned int write_00527_len = 0;
      write_00527 = append_buf(write_00527, &write_00527_len, write_00527_00000, write_00527_00000_len);
      if (write_00527_len > 0) {
         transmit_all(1, write_00527, write_00527_len);
      }
      free(write_00527);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00528 = NULL;
      unsigned int write_00528_len = 0;
      write_00528 = append_var("right", write_00528, &write_00528_len);
      if (write_00528_len > 0) {
         transmit_all(1, write_00528, write_00528_len);
      }
      free(write_00528);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00529_00000[] = 
         "\x0a";
      static unsigned int write_00529_00000_len = 1;
      unsigned char *write_00529 = NULL;
      unsigned int write_00529_len = 0;
      write_00529 = append_buf(write_00529, &write_00529_len, write_00529_00000, write_00529_00000_len);
      if (write_00529_len > 0) {
         transmit_all(1, write_00529, write_00529_len);
      }
      free(write_00529);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00530 = NULL;
      unsigned int write_00530_len = 0;
      write_00530 = append_var("jumpright", write_00530, &write_00530_len);
      if (write_00530_len > 0) {
         transmit_all(1, write_00530, write_00530_len);
      }
      free(write_00530);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00531_00000[] = 
         "\x0a";
      static unsigned int write_00531_00000_len = 1;
      unsigned char *write_00531 = NULL;
      unsigned int write_00531_len = 0;
      write_00531 = append_buf(write_00531, &write_00531_len, write_00531_00000, write_00531_00000_len);
      if (write_00531_len > 0) {
         transmit_all(1, write_00531, write_00531_len);
      }
      free(write_00531);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00532 = NULL;
      unsigned int write_00532_len = 0;
      write_00532 = append_var("wait", write_00532, &write_00532_len);
      if (write_00532_len > 0) {
         transmit_all(1, write_00532, write_00532_len);
      }
      free(write_00532);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00533_00000[] = 
         "\x0a";
      static unsigned int write_00533_00000_len = 1;
      unsigned char *write_00533 = NULL;
      unsigned int write_00533_len = 0;
      write_00533 = append_buf(write_00533, &write_00533_len, write_00533_00000, write_00533_00000_len);
      if (write_00533_len > 0) {
         transmit_all(1, write_00533, write_00533_len);
      }
      free(write_00533);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00534 = NULL;
      unsigned int write_00534_len = 0;
      write_00534 = append_var("wait", write_00534, &write_00534_len);
      if (write_00534_len > 0) {
         transmit_all(1, write_00534, write_00534_len);
      }
      free(write_00534);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00535_00000[] = 
         "\x0a";
      static unsigned int write_00535_00000_len = 1;
      unsigned char *write_00535 = NULL;
      unsigned int write_00535_len = 0;
      write_00535 = append_buf(write_00535, &write_00535_len, write_00535_00000, write_00535_00000_len);
      if (write_00535_len > 0) {
         transmit_all(1, write_00535, write_00535_len);
      }
      free(write_00535);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00536 = NULL;
      unsigned int write_00536_len = 0;
      write_00536 = append_var("wait", write_00536, &write_00536_len);
      if (write_00536_len > 0) {
         transmit_all(1, write_00536, write_00536_len);
      }
      free(write_00536);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00537_00000[] = 
         "\x0a";
      static unsigned int write_00537_00000_len = 1;
      unsigned char *write_00537 = NULL;
      unsigned int write_00537_len = 0;
      write_00537 = append_buf(write_00537, &write_00537_len, write_00537_00000, write_00537_00000_len);
      if (write_00537_len > 0) {
         transmit_all(1, write_00537, write_00537_len);
      }
      free(write_00537);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00538 = NULL;
      unsigned int write_00538_len = 0;
      write_00538 = append_var("jumpright", write_00538, &write_00538_len);
      if (write_00538_len > 0) {
         transmit_all(1, write_00538, write_00538_len);
      }
      free(write_00538);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00539_00000[] = 
         "\x0a";
      static unsigned int write_00539_00000_len = 1;
      unsigned char *write_00539 = NULL;
      unsigned int write_00539_len = 0;
      write_00539 = append_buf(write_00539, &write_00539_len, write_00539_00000, write_00539_00000_len);
      if (write_00539_len > 0) {
         transmit_all(1, write_00539, write_00539_len);
      }
      free(write_00539);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00540 = NULL;
      unsigned int write_00540_len = 0;
      write_00540 = append_var("right", write_00540, &write_00540_len);
      if (write_00540_len > 0) {
         transmit_all(1, write_00540, write_00540_len);
      }
      free(write_00540);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00541_00000[] = 
         "\x0a";
      static unsigned int write_00541_00000_len = 1;
      unsigned char *write_00541 = NULL;
      unsigned int write_00541_len = 0;
      write_00541 = append_buf(write_00541, &write_00541_len, write_00541_00000, write_00541_00000_len);
      if (write_00541_len > 0) {
         transmit_all(1, write_00541, write_00541_len);
      }
      free(write_00541);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00542 = NULL;
      unsigned int write_00542_len = 0;
      write_00542 = append_var("right", write_00542, &write_00542_len);
      if (write_00542_len > 0) {
         transmit_all(1, write_00542, write_00542_len);
      }
      free(write_00542);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00543_00000[] = 
         "\x0a";
      static unsigned int write_00543_00000_len = 1;
      unsigned char *write_00543 = NULL;
      unsigned int write_00543_len = 0;
      write_00543 = append_buf(write_00543, &write_00543_len, write_00543_00000, write_00543_00000_len);
      if (write_00543_len > 0) {
         transmit_all(1, write_00543, write_00543_len);
      }
      free(write_00543);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00544 = NULL;
      unsigned int write_00544_len = 0;
      write_00544 = append_var("right", write_00544, &write_00544_len);
      if (write_00544_len > 0) {
         transmit_all(1, write_00544, write_00544_len);
      }
      free(write_00544);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00545_00000[] = 
         "\x0a";
      static unsigned int write_00545_00000_len = 1;
      unsigned char *write_00545 = NULL;
      unsigned int write_00545_len = 0;
      write_00545 = append_buf(write_00545, &write_00545_len, write_00545_00000, write_00545_00000_len);
      if (write_00545_len > 0) {
         transmit_all(1, write_00545, write_00545_len);
      }
      free(write_00545);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00546 = NULL;
      unsigned int write_00546_len = 0;
      write_00546 = append_var("jumpright", write_00546, &write_00546_len);
      if (write_00546_len > 0) {
         transmit_all(1, write_00546, write_00546_len);
      }
      free(write_00546);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00547_00000[] = 
         "\x0a";
      static unsigned int write_00547_00000_len = 1;
      unsigned char *write_00547 = NULL;
      unsigned int write_00547_len = 0;
      write_00547 = append_buf(write_00547, &write_00547_len, write_00547_00000, write_00547_00000_len);
      if (write_00547_len > 0) {
         transmit_all(1, write_00547, write_00547_len);
      }
      free(write_00547);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00548 = NULL;
      unsigned int write_00548_len = 0;
      write_00548 = append_var("jumpright", write_00548, &write_00548_len);
      if (write_00548_len > 0) {
         transmit_all(1, write_00548, write_00548_len);
      }
      free(write_00548);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00549_00000[] = 
         "\x0a";
      static unsigned int write_00549_00000_len = 1;
      unsigned char *write_00549 = NULL;
      unsigned int write_00549_len = 0;
      write_00549 = append_buf(write_00549, &write_00549_len, write_00549_00000, write_00549_00000_len);
      if (write_00549_len > 0) {
         transmit_all(1, write_00549, write_00549_len);
      }
      free(write_00549);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00550 = NULL;
      unsigned int write_00550_len = 0;
      write_00550 = append_var("jumpright", write_00550, &write_00550_len);
      if (write_00550_len > 0) {
         transmit_all(1, write_00550, write_00550_len);
      }
      free(write_00550);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00551_00000[] = 
         "\x0a";
      static unsigned int write_00551_00000_len = 1;
      unsigned char *write_00551 = NULL;
      unsigned int write_00551_len = 0;
      write_00551 = append_buf(write_00551, &write_00551_len, write_00551_00000, write_00551_00000_len);
      if (write_00551_len > 0) {
         transmit_all(1, write_00551, write_00551_len);
      }
      free(write_00551);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00552 = NULL;
      unsigned int write_00552_len = 0;
      write_00552 = append_var("right", write_00552, &write_00552_len);
      if (write_00552_len > 0) {
         transmit_all(1, write_00552, write_00552_len);
      }
      free(write_00552);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00553_00000[] = 
         "\x0a";
      static unsigned int write_00553_00000_len = 1;
      unsigned char *write_00553 = NULL;
      unsigned int write_00553_len = 0;
      write_00553 = append_buf(write_00553, &write_00553_len, write_00553_00000, write_00553_00000_len);
      if (write_00553_len > 0) {
         transmit_all(1, write_00553, write_00553_len);
      }
      free(write_00553);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00554 = NULL;
      unsigned int write_00554_len = 0;
      write_00554 = append_var("jumpright", write_00554, &write_00554_len);
      if (write_00554_len > 0) {
         transmit_all(1, write_00554, write_00554_len);
      }
      free(write_00554);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00555_00000[] = 
         "\x0a";
      static unsigned int write_00555_00000_len = 1;
      unsigned char *write_00555 = NULL;
      unsigned int write_00555_len = 0;
      write_00555 = append_buf(write_00555, &write_00555_len, write_00555_00000, write_00555_00000_len);
      if (write_00555_len > 0) {
         transmit_all(1, write_00555, write_00555_len);
      }
      free(write_00555);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00556 = NULL;
      unsigned int write_00556_len = 0;
      write_00556 = append_var("right", write_00556, &write_00556_len);
      if (write_00556_len > 0) {
         transmit_all(1, write_00556, write_00556_len);
      }
      free(write_00556);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00557_00000[] = 
         "\x0a";
      static unsigned int write_00557_00000_len = 1;
      unsigned char *write_00557 = NULL;
      unsigned int write_00557_len = 0;
      write_00557 = append_buf(write_00557, &write_00557_len, write_00557_00000, write_00557_00000_len);
      if (write_00557_len > 0) {
         transmit_all(1, write_00557, write_00557_len);
      }
      free(write_00557);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00558 = NULL;
      unsigned int write_00558_len = 0;
      write_00558 = append_var("right", write_00558, &write_00558_len);
      if (write_00558_len > 0) {
         transmit_all(1, write_00558, write_00558_len);
      }
      free(write_00558);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00559_00000[] = 
         "\x0a";
      static unsigned int write_00559_00000_len = 1;
      unsigned char *write_00559 = NULL;
      unsigned int write_00559_len = 0;
      write_00559 = append_buf(write_00559, &write_00559_len, write_00559_00000, write_00559_00000_len);
      if (write_00559_len > 0) {
         transmit_all(1, write_00559, write_00559_len);
      }
      free(write_00559);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00560 = NULL;
      unsigned int write_00560_len = 0;
      write_00560 = append_var("wait", write_00560, &write_00560_len);
      if (write_00560_len > 0) {
         transmit_all(1, write_00560, write_00560_len);
      }
      free(write_00560);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00561_00000[] = 
         "\x0a";
      static unsigned int write_00561_00000_len = 1;
      unsigned char *write_00561 = NULL;
      unsigned int write_00561_len = 0;
      write_00561 = append_buf(write_00561, &write_00561_len, write_00561_00000, write_00561_00000_len);
      if (write_00561_len > 0) {
         transmit_all(1, write_00561, write_00561_len);
      }
      free(write_00561);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00562 = NULL;
      unsigned int write_00562_len = 0;
      write_00562 = append_var("wait", write_00562, &write_00562_len);
      if (write_00562_len > 0) {
         transmit_all(1, write_00562, write_00562_len);
      }
      free(write_00562);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00563_00000[] = 
         "\x0a";
      static unsigned int write_00563_00000_len = 1;
      unsigned char *write_00563 = NULL;
      unsigned int write_00563_len = 0;
      write_00563 = append_buf(write_00563, &write_00563_len, write_00563_00000, write_00563_00000_len);
      if (write_00563_len > 0) {
         transmit_all(1, write_00563, write_00563_len);
      }
      free(write_00563);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00564 = NULL;
      unsigned int write_00564_len = 0;
      write_00564 = append_var("wait", write_00564, &write_00564_len);
      if (write_00564_len > 0) {
         transmit_all(1, write_00564, write_00564_len);
      }
      free(write_00564);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00565_00000[] = 
         "\x0a";
      static unsigned int write_00565_00000_len = 1;
      unsigned char *write_00565 = NULL;
      unsigned int write_00565_len = 0;
      write_00565 = append_buf(write_00565, &write_00565_len, write_00565_00000, write_00565_00000_len);
      if (write_00565_len > 0) {
         transmit_all(1, write_00565, write_00565_len);
      }
      free(write_00565);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00566 = NULL;
      unsigned int write_00566_len = 0;
      write_00566 = append_var("wait", write_00566, &write_00566_len);
      if (write_00566_len > 0) {
         transmit_all(1, write_00566, write_00566_len);
      }
      free(write_00566);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00567_00000[] = 
         "\x0a";
      static unsigned int write_00567_00000_len = 1;
      unsigned char *write_00567 = NULL;
      unsigned int write_00567_len = 0;
      write_00567 = append_buf(write_00567, &write_00567_len, write_00567_00000, write_00567_00000_len);
      if (write_00567_len > 0) {
         transmit_all(1, write_00567, write_00567_len);
      }
      free(write_00567);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00568 = NULL;
      unsigned int write_00568_len = 0;
      write_00568 = append_var("wait", write_00568, &write_00568_len);
      if (write_00568_len > 0) {
         transmit_all(1, write_00568, write_00568_len);
      }
      free(write_00568);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00569_00000[] = 
         "\x0a";
      static unsigned int write_00569_00000_len = 1;
      unsigned char *write_00569 = NULL;
      unsigned int write_00569_len = 0;
      write_00569 = append_buf(write_00569, &write_00569_len, write_00569_00000, write_00569_00000_len);
      if (write_00569_len > 0) {
         transmit_all(1, write_00569, write_00569_len);
      }
      free(write_00569);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00570 = NULL;
      unsigned int write_00570_len = 0;
      write_00570 = append_var("wait", write_00570, &write_00570_len);
      if (write_00570_len > 0) {
         transmit_all(1, write_00570, write_00570_len);
      }
      free(write_00570);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00571_00000[] = 
         "\x0a";
      static unsigned int write_00571_00000_len = 1;
      unsigned char *write_00571 = NULL;
      unsigned int write_00571_len = 0;
      write_00571 = append_buf(write_00571, &write_00571_len, write_00571_00000, write_00571_00000_len);
      if (write_00571_len > 0) {
         transmit_all(1, write_00571, write_00571_len);
      }
      free(write_00571);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00572 = NULL;
      unsigned int write_00572_len = 0;
      write_00572 = append_var("wait", write_00572, &write_00572_len);
      if (write_00572_len > 0) {
         transmit_all(1, write_00572, write_00572_len);
      }
      free(write_00572);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00573_00000[] = 
         "\x0a";
      static unsigned int write_00573_00000_len = 1;
      unsigned char *write_00573 = NULL;
      unsigned int write_00573_len = 0;
      write_00573 = append_buf(write_00573, &write_00573_len, write_00573_00000, write_00573_00000_len);
      if (write_00573_len > 0) {
         transmit_all(1, write_00573, write_00573_len);
      }
      free(write_00573);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00574 = NULL;
      unsigned int write_00574_len = 0;
      write_00574 = append_var("wait", write_00574, &write_00574_len);
      if (write_00574_len > 0) {
         transmit_all(1, write_00574, write_00574_len);
      }
      free(write_00574);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00575_00000[] = 
         "\x0a";
      static unsigned int write_00575_00000_len = 1;
      unsigned char *write_00575 = NULL;
      unsigned int write_00575_len = 0;
      write_00575 = append_buf(write_00575, &write_00575_len, write_00575_00000, write_00575_00000_len);
      if (write_00575_len > 0) {
         transmit_all(1, write_00575, write_00575_len);
      }
      free(write_00575);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00576 = NULL;
      unsigned int write_00576_len = 0;
      write_00576 = append_var("wait", write_00576, &write_00576_len);
      if (write_00576_len > 0) {
         transmit_all(1, write_00576, write_00576_len);
      }
      free(write_00576);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00577_00000[] = 
         "\x0a";
      static unsigned int write_00577_00000_len = 1;
      unsigned char *write_00577 = NULL;
      unsigned int write_00577_len = 0;
      write_00577 = append_buf(write_00577, &write_00577_len, write_00577_00000, write_00577_00000_len);
      if (write_00577_len > 0) {
         transmit_all(1, write_00577, write_00577_len);
      }
      free(write_00577);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00578 = NULL;
      unsigned int write_00578_len = 0;
      write_00578 = append_var("wait", write_00578, &write_00578_len);
      if (write_00578_len > 0) {
         transmit_all(1, write_00578, write_00578_len);
      }
      free(write_00578);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00579_00000[] = 
         "\x0a";
      static unsigned int write_00579_00000_len = 1;
      unsigned char *write_00579 = NULL;
      unsigned int write_00579_len = 0;
      write_00579 = append_buf(write_00579, &write_00579_len, write_00579_00000, write_00579_00000_len);
      if (write_00579_len > 0) {
         transmit_all(1, write_00579, write_00579_len);
      }
      free(write_00579);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00580 = NULL;
      unsigned int write_00580_len = 0;
      write_00580 = append_var("wait", write_00580, &write_00580_len);
      if (write_00580_len > 0) {
         transmit_all(1, write_00580, write_00580_len);
      }
      free(write_00580);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00581_00000[] = 
         "\x0a";
      static unsigned int write_00581_00000_len = 1;
      unsigned char *write_00581 = NULL;
      unsigned int write_00581_len = 0;
      write_00581 = append_buf(write_00581, &write_00581_len, write_00581_00000, write_00581_00000_len);
      if (write_00581_len > 0) {
         transmit_all(1, write_00581, write_00581_len);
      }
      free(write_00581);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00582 = NULL;
      unsigned int write_00582_len = 0;
      write_00582 = append_var("wait", write_00582, &write_00582_len);
      if (write_00582_len > 0) {
         transmit_all(1, write_00582, write_00582_len);
      }
      free(write_00582);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00583_00000[] = 
         "\x0a";
      static unsigned int write_00583_00000_len = 1;
      unsigned char *write_00583 = NULL;
      unsigned int write_00583_len = 0;
      write_00583 = append_buf(write_00583, &write_00583_len, write_00583_00000, write_00583_00000_len);
      if (write_00583_len > 0) {
         transmit_all(1, write_00583, write_00583_len);
      }
      free(write_00583);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00584 = NULL;
      unsigned int write_00584_len = 0;
      write_00584 = append_var("wait", write_00584, &write_00584_len);
      if (write_00584_len > 0) {
         transmit_all(1, write_00584, write_00584_len);
      }
      free(write_00584);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00585_00000[] = 
         "\x0a";
      static unsigned int write_00585_00000_len = 1;
      unsigned char *write_00585 = NULL;
      unsigned int write_00585_len = 0;
      write_00585 = append_buf(write_00585, &write_00585_len, write_00585_00000, write_00585_00000_len);
      if (write_00585_len > 0) {
         transmit_all(1, write_00585, write_00585_len);
      }
      free(write_00585);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00586 = NULL;
      unsigned int write_00586_len = 0;
      write_00586 = append_var("wait", write_00586, &write_00586_len);
      if (write_00586_len > 0) {
         transmit_all(1, write_00586, write_00586_len);
      }
      free(write_00586);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00587_00000[] = 
         "\x0a";
      static unsigned int write_00587_00000_len = 1;
      unsigned char *write_00587 = NULL;
      unsigned int write_00587_len = 0;
      write_00587 = append_buf(write_00587, &write_00587_len, write_00587_00000, write_00587_00000_len);
      if (write_00587_len > 0) {
         transmit_all(1, write_00587, write_00587_len);
      }
      free(write_00587);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00588 = NULL;
      unsigned int write_00588_len = 0;
      write_00588 = append_var("wait", write_00588, &write_00588_len);
      if (write_00588_len > 0) {
         transmit_all(1, write_00588, write_00588_len);
      }
      free(write_00588);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00589_00000[] = 
         "\x0a";
      static unsigned int write_00589_00000_len = 1;
      unsigned char *write_00589 = NULL;
      unsigned int write_00589_len = 0;
      write_00589 = append_buf(write_00589, &write_00589_len, write_00589_00000, write_00589_00000_len);
      if (write_00589_len > 0) {
         transmit_all(1, write_00589, write_00589_len);
      }
      free(write_00589);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00590 = NULL;
      unsigned int write_00590_len = 0;
      write_00590 = append_var("wait", write_00590, &write_00590_len);
      if (write_00590_len > 0) {
         transmit_all(1, write_00590, write_00590_len);
      }
      free(write_00590);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00591_00000[] = 
         "\x0a";
      static unsigned int write_00591_00000_len = 1;
      unsigned char *write_00591 = NULL;
      unsigned int write_00591_len = 0;
      write_00591 = append_buf(write_00591, &write_00591_len, write_00591_00000, write_00591_00000_len);
      if (write_00591_len > 0) {
         transmit_all(1, write_00591, write_00591_len);
      }
      free(write_00591);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00592 = NULL;
      unsigned int write_00592_len = 0;
      write_00592 = append_var("wait", write_00592, &write_00592_len);
      if (write_00592_len > 0) {
         transmit_all(1, write_00592, write_00592_len);
      }
      free(write_00592);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00593_00000[] = 
         "\x0a";
      static unsigned int write_00593_00000_len = 1;
      unsigned char *write_00593 = NULL;
      unsigned int write_00593_len = 0;
      write_00593 = append_buf(write_00593, &write_00593_len, write_00593_00000, write_00593_00000_len);
      if (write_00593_len > 0) {
         transmit_all(1, write_00593, write_00593_len);
      }
      free(write_00593);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00594 = NULL;
      unsigned int write_00594_len = 0;
      write_00594 = append_var("wait", write_00594, &write_00594_len);
      if (write_00594_len > 0) {
         transmit_all(1, write_00594, write_00594_len);
      }
      free(write_00594);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00595_00000[] = 
         "\x0a";
      static unsigned int write_00595_00000_len = 1;
      unsigned char *write_00595 = NULL;
      unsigned int write_00595_len = 0;
      write_00595 = append_buf(write_00595, &write_00595_len, write_00595_00000, write_00595_00000_len);
      if (write_00595_len > 0) {
         transmit_all(1, write_00595, write_00595_len);
      }
      free(write_00595);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00596 = NULL;
      unsigned int write_00596_len = 0;
      write_00596 = append_var("wait", write_00596, &write_00596_len);
      if (write_00596_len > 0) {
         transmit_all(1, write_00596, write_00596_len);
      }
      free(write_00596);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00597_00000[] = 
         "\x0a";
      static unsigned int write_00597_00000_len = 1;
      unsigned char *write_00597 = NULL;
      unsigned int write_00597_len = 0;
      write_00597 = append_buf(write_00597, &write_00597_len, write_00597_00000, write_00597_00000_len);
      if (write_00597_len > 0) {
         transmit_all(1, write_00597, write_00597_len);
      }
      free(write_00597);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00598 = NULL;
      unsigned int write_00598_len = 0;
      write_00598 = append_var("wait", write_00598, &write_00598_len);
      if (write_00598_len > 0) {
         transmit_all(1, write_00598, write_00598_len);
      }
      free(write_00598);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00599_00000[] = 
         "\x0a";
      static unsigned int write_00599_00000_len = 1;
      unsigned char *write_00599 = NULL;
      unsigned int write_00599_len = 0;
      write_00599 = append_buf(write_00599, &write_00599_len, write_00599_00000, write_00599_00000_len);
      if (write_00599_len > 0) {
         transmit_all(1, write_00599, write_00599_len);
      }
      free(write_00599);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00600 = NULL;
      unsigned int write_00600_len = 0;
      write_00600 = append_var("wait", write_00600, &write_00600_len);
      if (write_00600_len > 0) {
         transmit_all(1, write_00600, write_00600_len);
      }
      free(write_00600);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00601_00000[] = 
         "\x0a";
      static unsigned int write_00601_00000_len = 1;
      unsigned char *write_00601 = NULL;
      unsigned int write_00601_len = 0;
      write_00601 = append_buf(write_00601, &write_00601_len, write_00601_00000, write_00601_00000_len);
      if (write_00601_len > 0) {
         transmit_all(1, write_00601, write_00601_len);
      }
      free(write_00601);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00602 = NULL;
      unsigned int write_00602_len = 0;
      write_00602 = append_var("wait", write_00602, &write_00602_len);
      if (write_00602_len > 0) {
         transmit_all(1, write_00602, write_00602_len);
      }
      free(write_00602);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00603_00000[] = 
         "\x0a";
      static unsigned int write_00603_00000_len = 1;
      unsigned char *write_00603 = NULL;
      unsigned int write_00603_len = 0;
      write_00603 = append_buf(write_00603, &write_00603_len, write_00603_00000, write_00603_00000_len);
      if (write_00603_len > 0) {
         transmit_all(1, write_00603, write_00603_len);
      }
      free(write_00603);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00604 = NULL;
      unsigned int write_00604_len = 0;
      write_00604 = append_var("wait", write_00604, &write_00604_len);
      if (write_00604_len > 0) {
         transmit_all(1, write_00604, write_00604_len);
      }
      free(write_00604);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00605_00000[] = 
         "\x0a";
      static unsigned int write_00605_00000_len = 1;
      unsigned char *write_00605 = NULL;
      unsigned int write_00605_len = 0;
      write_00605 = append_buf(write_00605, &write_00605_len, write_00605_00000, write_00605_00000_len);
      if (write_00605_len > 0) {
         transmit_all(1, write_00605, write_00605_len);
      }
      free(write_00605);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00606 = NULL;
      unsigned int write_00606_len = 0;
      write_00606 = append_var("wait", write_00606, &write_00606_len);
      if (write_00606_len > 0) {
         transmit_all(1, write_00606, write_00606_len);
      }
      free(write_00606);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00607_00000[] = 
         "\x0a";
      static unsigned int write_00607_00000_len = 1;
      unsigned char *write_00607 = NULL;
      unsigned int write_00607_len = 0;
      write_00607 = append_buf(write_00607, &write_00607_len, write_00607_00000, write_00607_00000_len);
      if (write_00607_len > 0) {
         transmit_all(1, write_00607, write_00607_len);
      }
      free(write_00607);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00608 = NULL;
      unsigned int write_00608_len = 0;
      write_00608 = append_var("wait", write_00608, &write_00608_len);
      if (write_00608_len > 0) {
         transmit_all(1, write_00608, write_00608_len);
      }
      free(write_00608);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00609_00000[] = 
         "\x0a";
      static unsigned int write_00609_00000_len = 1;
      unsigned char *write_00609 = NULL;
      unsigned int write_00609_len = 0;
      write_00609 = append_buf(write_00609, &write_00609_len, write_00609_00000, write_00609_00000_len);
      if (write_00609_len > 0) {
         transmit_all(1, write_00609, write_00609_len);
      }
      free(write_00609);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00610 = NULL;
      unsigned int write_00610_len = 0;
      write_00610 = append_var("right", write_00610, &write_00610_len);
      if (write_00610_len > 0) {
         transmit_all(1, write_00610, write_00610_len);
      }
      free(write_00610);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00611_00000[] = 
         "\x0a";
      static unsigned int write_00611_00000_len = 1;
      unsigned char *write_00611 = NULL;
      unsigned int write_00611_len = 0;
      write_00611 = append_buf(write_00611, &write_00611_len, write_00611_00000, write_00611_00000_len);
      if (write_00611_len > 0) {
         transmit_all(1, write_00611, write_00611_len);
      }
      free(write_00611);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00612 = NULL;
      unsigned int write_00612_len = 0;
      write_00612 = append_var("jumpright", write_00612, &write_00612_len);
      if (write_00612_len > 0) {
         transmit_all(1, write_00612, write_00612_len);
      }
      free(write_00612);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00613_00000[] = 
         "\x0a";
      static unsigned int write_00613_00000_len = 1;
      unsigned char *write_00613 = NULL;
      unsigned int write_00613_len = 0;
      write_00613 = append_buf(write_00613, &write_00613_len, write_00613_00000, write_00613_00000_len);
      if (write_00613_len > 0) {
         transmit_all(1, write_00613, write_00613_len);
      }
      free(write_00613);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00614 = NULL;
      unsigned int write_00614_len = 0;
      write_00614 = append_var("wait", write_00614, &write_00614_len);
      if (write_00614_len > 0) {
         transmit_all(1, write_00614, write_00614_len);
      }
      free(write_00614);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00615_00000[] = 
         "\x0a";
      static unsigned int write_00615_00000_len = 1;
      unsigned char *write_00615 = NULL;
      unsigned int write_00615_len = 0;
      write_00615 = append_buf(write_00615, &write_00615_len, write_00615_00000, write_00615_00000_len);
      if (write_00615_len > 0) {
         transmit_all(1, write_00615, write_00615_len);
      }
      free(write_00615);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00616 = NULL;
      unsigned int write_00616_len = 0;
      write_00616 = append_var("jumpright", write_00616, &write_00616_len);
      if (write_00616_len > 0) {
         transmit_all(1, write_00616, write_00616_len);
      }
      free(write_00616);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00617_00000[] = 
         "\x0a";
      static unsigned int write_00617_00000_len = 1;
      unsigned char *write_00617 = NULL;
      unsigned int write_00617_len = 0;
      write_00617 = append_buf(write_00617, &write_00617_len, write_00617_00000, write_00617_00000_len);
      if (write_00617_len > 0) {
         transmit_all(1, write_00617, write_00617_len);
      }
      free(write_00617);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00618 = NULL;
      unsigned int write_00618_len = 0;
      write_00618 = append_var("right", write_00618, &write_00618_len);
      if (write_00618_len > 0) {
         transmit_all(1, write_00618, write_00618_len);
      }
      free(write_00618);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00619_00000[] = 
         "\x0a";
      static unsigned int write_00619_00000_len = 1;
      unsigned char *write_00619 = NULL;
      unsigned int write_00619_len = 0;
      write_00619 = append_buf(write_00619, &write_00619_len, write_00619_00000, write_00619_00000_len);
      if (write_00619_len > 0) {
         transmit_all(1, write_00619, write_00619_len);
      }
      free(write_00619);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00620 = NULL;
      unsigned int write_00620_len = 0;
      write_00620 = append_var("right", write_00620, &write_00620_len);
      if (write_00620_len > 0) {
         transmit_all(1, write_00620, write_00620_len);
      }
      free(write_00620);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00621_00000[] = 
         "\x0a";
      static unsigned int write_00621_00000_len = 1;
      unsigned char *write_00621 = NULL;
      unsigned int write_00621_len = 0;
      write_00621 = append_buf(write_00621, &write_00621_len, write_00621_00000, write_00621_00000_len);
      if (write_00621_len > 0) {
         transmit_all(1, write_00621, write_00621_len);
      }
      free(write_00621);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00622 = NULL;
      unsigned int write_00622_len = 0;
      write_00622 = append_var("right", write_00622, &write_00622_len);
      if (write_00622_len > 0) {
         transmit_all(1, write_00622, write_00622_len);
      }
      free(write_00622);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00623_00000[] = 
         "\x0a";
      static unsigned int write_00623_00000_len = 1;
      unsigned char *write_00623 = NULL;
      unsigned int write_00623_len = 0;
      write_00623 = append_buf(write_00623, &write_00623_len, write_00623_00000, write_00623_00000_len);
      if (write_00623_len > 0) {
         transmit_all(1, write_00623, write_00623_len);
      }
      free(write_00623);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00624 = NULL;
      unsigned int write_00624_len = 0;
      write_00624 = append_var("right", write_00624, &write_00624_len);
      if (write_00624_len > 0) {
         transmit_all(1, write_00624, write_00624_len);
      }
      free(write_00624);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00625_00000[] = 
         "\x0a";
      static unsigned int write_00625_00000_len = 1;
      unsigned char *write_00625 = NULL;
      unsigned int write_00625_len = 0;
      write_00625 = append_buf(write_00625, &write_00625_len, write_00625_00000, write_00625_00000_len);
      if (write_00625_len > 0) {
         transmit_all(1, write_00625, write_00625_len);
      }
      free(write_00625);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00626 = NULL;
      unsigned int write_00626_len = 0;
      write_00626 = append_var("right", write_00626, &write_00626_len);
      if (write_00626_len > 0) {
         transmit_all(1, write_00626, write_00626_len);
      }
      free(write_00626);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00627_00000[] = 
         "\x0a";
      static unsigned int write_00627_00000_len = 1;
      unsigned char *write_00627 = NULL;
      unsigned int write_00627_len = 0;
      write_00627 = append_buf(write_00627, &write_00627_len, write_00627_00000, write_00627_00000_len);
      if (write_00627_len > 0) {
         transmit_all(1, write_00627, write_00627_len);
      }
      free(write_00627);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00628 = NULL;
      unsigned int write_00628_len = 0;
      write_00628 = append_var("right", write_00628, &write_00628_len);
      if (write_00628_len > 0) {
         transmit_all(1, write_00628, write_00628_len);
      }
      free(write_00628);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00629_00000[] = 
         "\x0a";
      static unsigned int write_00629_00000_len = 1;
      unsigned char *write_00629 = NULL;
      unsigned int write_00629_len = 0;
      write_00629 = append_buf(write_00629, &write_00629_len, write_00629_00000, write_00629_00000_len);
      if (write_00629_len > 0) {
         transmit_all(1, write_00629, write_00629_len);
      }
      free(write_00629);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00630 = NULL;
      unsigned int write_00630_len = 0;
      write_00630 = append_var("right", write_00630, &write_00630_len);
      if (write_00630_len > 0) {
         transmit_all(1, write_00630, write_00630_len);
      }
      free(write_00630);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00631_00000[] = 
         "\x0a";
      static unsigned int write_00631_00000_len = 1;
      unsigned char *write_00631 = NULL;
      unsigned int write_00631_len = 0;
      write_00631 = append_buf(write_00631, &write_00631_len, write_00631_00000, write_00631_00000_len);
      if (write_00631_len > 0) {
         transmit_all(1, write_00631, write_00631_len);
      }
      free(write_00631);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00632 = NULL;
      unsigned int write_00632_len = 0;
      write_00632 = append_var("right", write_00632, &write_00632_len);
      if (write_00632_len > 0) {
         transmit_all(1, write_00632, write_00632_len);
      }
      free(write_00632);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00633_00000[] = 
         "\x0a";
      static unsigned int write_00633_00000_len = 1;
      unsigned char *write_00633 = NULL;
      unsigned int write_00633_len = 0;
      write_00633 = append_buf(write_00633, &write_00633_len, write_00633_00000, write_00633_00000_len);
      if (write_00633_len > 0) {
         transmit_all(1, write_00633, write_00633_len);
      }
      free(write_00633);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00634 = NULL;
      unsigned int write_00634_len = 0;
      write_00634 = append_var("right", write_00634, &write_00634_len);
      if (write_00634_len > 0) {
         transmit_all(1, write_00634, write_00634_len);
      }
      free(write_00634);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00635_00000[] = 
         "\x0a";
      static unsigned int write_00635_00000_len = 1;
      unsigned char *write_00635 = NULL;
      unsigned int write_00635_len = 0;
      write_00635 = append_buf(write_00635, &write_00635_len, write_00635_00000, write_00635_00000_len);
      if (write_00635_len > 0) {
         transmit_all(1, write_00635, write_00635_len);
      }
      free(write_00635);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00636 = NULL;
      unsigned int write_00636_len = 0;
      write_00636 = append_var("right", write_00636, &write_00636_len);
      if (write_00636_len > 0) {
         transmit_all(1, write_00636, write_00636_len);
      }
      free(write_00636);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00637_00000[] = 
         "\x0a";
      static unsigned int write_00637_00000_len = 1;
      unsigned char *write_00637 = NULL;
      unsigned int write_00637_len = 0;
      write_00637 = append_buf(write_00637, &write_00637_len, write_00637_00000, write_00637_00000_len);
      if (write_00637_len > 0) {
         transmit_all(1, write_00637, write_00637_len);
      }
      free(write_00637);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00638 = NULL;
      unsigned int write_00638_len = 0;
      write_00638 = append_var("right", write_00638, &write_00638_len);
      if (write_00638_len > 0) {
         transmit_all(1, write_00638, write_00638_len);
      }
      free(write_00638);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00639_00000[] = 
         "\x0a";
      static unsigned int write_00639_00000_len = 1;
      unsigned char *write_00639 = NULL;
      unsigned int write_00639_len = 0;
      write_00639 = append_buf(write_00639, &write_00639_len, write_00639_00000, write_00639_00000_len);
      if (write_00639_len > 0) {
         transmit_all(1, write_00639, write_00639_len);
      }
      free(write_00639);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00640 = NULL;
      unsigned int write_00640_len = 0;
      write_00640 = append_var("wait", write_00640, &write_00640_len);
      if (write_00640_len > 0) {
         transmit_all(1, write_00640, write_00640_len);
      }
      free(write_00640);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00641_00000[] = 
         "\x0a";
      static unsigned int write_00641_00000_len = 1;
      unsigned char *write_00641 = NULL;
      unsigned int write_00641_len = 0;
      write_00641 = append_buf(write_00641, &write_00641_len, write_00641_00000, write_00641_00000_len);
      if (write_00641_len > 0) {
         transmit_all(1, write_00641, write_00641_len);
      }
      free(write_00641);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00642 = NULL;
      unsigned int write_00642_len = 0;
      write_00642 = append_var("wait", write_00642, &write_00642_len);
      if (write_00642_len > 0) {
         transmit_all(1, write_00642, write_00642_len);
      }
      free(write_00642);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00643_00000[] = 
         "\x0a";
      static unsigned int write_00643_00000_len = 1;
      unsigned char *write_00643 = NULL;
      unsigned int write_00643_len = 0;
      write_00643 = append_buf(write_00643, &write_00643_len, write_00643_00000, write_00643_00000_len);
      if (write_00643_len > 0) {
         transmit_all(1, write_00643, write_00643_len);
      }
      free(write_00643);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00644 = NULL;
      unsigned int write_00644_len = 0;
      write_00644 = append_var("wait", write_00644, &write_00644_len);
      if (write_00644_len > 0) {
         transmit_all(1, write_00644, write_00644_len);
      }
      free(write_00644);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00645_00000[] = 
         "\x0a";
      static unsigned int write_00645_00000_len = 1;
      unsigned char *write_00645 = NULL;
      unsigned int write_00645_len = 0;
      write_00645 = append_buf(write_00645, &write_00645_len, write_00645_00000, write_00645_00000_len);
      if (write_00645_len > 0) {
         transmit_all(1, write_00645, write_00645_len);
      }
      free(write_00645);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00646 = NULL;
      unsigned int write_00646_len = 0;
      write_00646 = append_var("wait", write_00646, &write_00646_len);
      if (write_00646_len > 0) {
         transmit_all(1, write_00646, write_00646_len);
      }
      free(write_00646);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00647_00000[] = 
         "\x0a";
      static unsigned int write_00647_00000_len = 1;
      unsigned char *write_00647 = NULL;
      unsigned int write_00647_len = 0;
      write_00647 = append_buf(write_00647, &write_00647_len, write_00647_00000, write_00647_00000_len);
      if (write_00647_len > 0) {
         transmit_all(1, write_00647, write_00647_len);
      }
      free(write_00647);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00648 = NULL;
      unsigned int write_00648_len = 0;
      write_00648 = append_var("wait", write_00648, &write_00648_len);
      if (write_00648_len > 0) {
         transmit_all(1, write_00648, write_00648_len);
      }
      free(write_00648);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00649_00000[] = 
         "\x0a";
      static unsigned int write_00649_00000_len = 1;
      unsigned char *write_00649 = NULL;
      unsigned int write_00649_len = 0;
      write_00649 = append_buf(write_00649, &write_00649_len, write_00649_00000, write_00649_00000_len);
      if (write_00649_len > 0) {
         transmit_all(1, write_00649, write_00649_len);
      }
      free(write_00649);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00650 = NULL;
      unsigned int write_00650_len = 0;
      write_00650 = append_var("wait", write_00650, &write_00650_len);
      if (write_00650_len > 0) {
         transmit_all(1, write_00650, write_00650_len);
      }
      free(write_00650);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00651_00000[] = 
         "\x0a";
      static unsigned int write_00651_00000_len = 1;
      unsigned char *write_00651 = NULL;
      unsigned int write_00651_len = 0;
      write_00651 = append_buf(write_00651, &write_00651_len, write_00651_00000, write_00651_00000_len);
      if (write_00651_len > 0) {
         transmit_all(1, write_00651, write_00651_len);
      }
      free(write_00651);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00652 = NULL;
      unsigned int write_00652_len = 0;
      write_00652 = append_var("wait", write_00652, &write_00652_len);
      if (write_00652_len > 0) {
         transmit_all(1, write_00652, write_00652_len);
      }
      free(write_00652);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00653_00000[] = 
         "\x0a";
      static unsigned int write_00653_00000_len = 1;
      unsigned char *write_00653 = NULL;
      unsigned int write_00653_len = 0;
      write_00653 = append_buf(write_00653, &write_00653_len, write_00653_00000, write_00653_00000_len);
      if (write_00653_len > 0) {
         transmit_all(1, write_00653, write_00653_len);
      }
      free(write_00653);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00654 = NULL;
      unsigned int write_00654_len = 0;
      write_00654 = append_var("wait", write_00654, &write_00654_len);
      if (write_00654_len > 0) {
         transmit_all(1, write_00654, write_00654_len);
      }
      free(write_00654);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00655_00000[] = 
         "\x0a";
      static unsigned int write_00655_00000_len = 1;
      unsigned char *write_00655 = NULL;
      unsigned int write_00655_len = 0;
      write_00655 = append_buf(write_00655, &write_00655_len, write_00655_00000, write_00655_00000_len);
      if (write_00655_len > 0) {
         transmit_all(1, write_00655, write_00655_len);
      }
      free(write_00655);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00656 = NULL;
      unsigned int write_00656_len = 0;
      write_00656 = append_var("wait", write_00656, &write_00656_len);
      if (write_00656_len > 0) {
         transmit_all(1, write_00656, write_00656_len);
      }
      free(write_00656);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00657_00000[] = 
         "\x0a";
      static unsigned int write_00657_00000_len = 1;
      unsigned char *write_00657 = NULL;
      unsigned int write_00657_len = 0;
      write_00657 = append_buf(write_00657, &write_00657_len, write_00657_00000, write_00657_00000_len);
      if (write_00657_len > 0) {
         transmit_all(1, write_00657, write_00657_len);
      }
      free(write_00657);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00658 = NULL;
      unsigned int write_00658_len = 0;
      write_00658 = append_var("wait", write_00658, &write_00658_len);
      if (write_00658_len > 0) {
         transmit_all(1, write_00658, write_00658_len);
      }
      free(write_00658);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00659_00000[] = 
         "\x0a";
      static unsigned int write_00659_00000_len = 1;
      unsigned char *write_00659 = NULL;
      unsigned int write_00659_len = 0;
      write_00659 = append_buf(write_00659, &write_00659_len, write_00659_00000, write_00659_00000_len);
      if (write_00659_len > 0) {
         transmit_all(1, write_00659, write_00659_len);
      }
      free(write_00659);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00660 = NULL;
      unsigned int write_00660_len = 0;
      write_00660 = append_var("right", write_00660, &write_00660_len);
      if (write_00660_len > 0) {
         transmit_all(1, write_00660, write_00660_len);
      }
      free(write_00660);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00661_00000[] = 
         "\x0a";
      static unsigned int write_00661_00000_len = 1;
      unsigned char *write_00661 = NULL;
      unsigned int write_00661_len = 0;
      write_00661 = append_buf(write_00661, &write_00661_len, write_00661_00000, write_00661_00000_len);
      if (write_00661_len > 0) {
         transmit_all(1, write_00661, write_00661_len);
      }
      free(write_00661);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00662 = NULL;
      unsigned int write_00662_len = 0;
      write_00662 = append_var("jumpleft", write_00662, &write_00662_len);
      if (write_00662_len > 0) {
         transmit_all(1, write_00662, write_00662_len);
      }
      free(write_00662);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00663_00000[] = 
         "\x0a";
      static unsigned int write_00663_00000_len = 1;
      unsigned char *write_00663 = NULL;
      unsigned int write_00663_len = 0;
      write_00663 = append_buf(write_00663, &write_00663_len, write_00663_00000, write_00663_00000_len);
      if (write_00663_len > 0) {
         transmit_all(1, write_00663, write_00663_len);
      }
      free(write_00663);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00664 = NULL;
      unsigned int write_00664_len = 0;
      write_00664 = append_var("left", write_00664, &write_00664_len);
      if (write_00664_len > 0) {
         transmit_all(1, write_00664, write_00664_len);
      }
      free(write_00664);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00665_00000[] = 
         "\x0a";
      static unsigned int write_00665_00000_len = 1;
      unsigned char *write_00665 = NULL;
      unsigned int write_00665_len = 0;
      write_00665 = append_buf(write_00665, &write_00665_len, write_00665_00000, write_00665_00000_len);
      if (write_00665_len > 0) {
         transmit_all(1, write_00665, write_00665_len);
      }
      free(write_00665);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00666 = NULL;
      unsigned int write_00666_len = 0;
      write_00666 = append_var("left", write_00666, &write_00666_len);
      if (write_00666_len > 0) {
         transmit_all(1, write_00666, write_00666_len);
      }
      free(write_00666);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00667_00000[] = 
         "\x0a";
      static unsigned int write_00667_00000_len = 1;
      unsigned char *write_00667 = NULL;
      unsigned int write_00667_len = 0;
      write_00667 = append_buf(write_00667, &write_00667_len, write_00667_00000, write_00667_00000_len);
      if (write_00667_len > 0) {
         transmit_all(1, write_00667, write_00667_len);
      }
      free(write_00667);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00668 = NULL;
      unsigned int write_00668_len = 0;
      write_00668 = append_var("jumpright", write_00668, &write_00668_len);
      if (write_00668_len > 0) {
         transmit_all(1, write_00668, write_00668_len);
      }
      free(write_00668);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00669_00000[] = 
         "\x0a";
      static unsigned int write_00669_00000_len = 1;
      unsigned char *write_00669 = NULL;
      unsigned int write_00669_len = 0;
      write_00669 = append_buf(write_00669, &write_00669_len, write_00669_00000, write_00669_00000_len);
      if (write_00669_len > 0) {
         transmit_all(1, write_00669, write_00669_len);
      }
      free(write_00669);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00670 = NULL;
      unsigned int write_00670_len = 0;
      write_00670 = append_var("right", write_00670, &write_00670_len);
      if (write_00670_len > 0) {
         transmit_all(1, write_00670, write_00670_len);
      }
      free(write_00670);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00671_00000[] = 
         "\x0a";
      static unsigned int write_00671_00000_len = 1;
      unsigned char *write_00671 = NULL;
      unsigned int write_00671_len = 0;
      write_00671 = append_buf(write_00671, &write_00671_len, write_00671_00000, write_00671_00000_len);
      if (write_00671_len > 0) {
         transmit_all(1, write_00671, write_00671_len);
      }
      free(write_00671);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00672 = NULL;
      unsigned int write_00672_len = 0;
      write_00672 = append_var("wait", write_00672, &write_00672_len);
      if (write_00672_len > 0) {
         transmit_all(1, write_00672, write_00672_len);
      }
      free(write_00672);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00673_00000[] = 
         "\x0a";
      static unsigned int write_00673_00000_len = 1;
      unsigned char *write_00673 = NULL;
      unsigned int write_00673_len = 0;
      write_00673 = append_buf(write_00673, &write_00673_len, write_00673_00000, write_00673_00000_len);
      if (write_00673_len > 0) {
         transmit_all(1, write_00673, write_00673_len);
      }
      free(write_00673);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00674 = NULL;
      unsigned int write_00674_len = 0;
      write_00674 = append_var("wait", write_00674, &write_00674_len);
      if (write_00674_len > 0) {
         transmit_all(1, write_00674, write_00674_len);
      }
      free(write_00674);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00675_00000[] = 
         "\x0a";
      static unsigned int write_00675_00000_len = 1;
      unsigned char *write_00675 = NULL;
      unsigned int write_00675_len = 0;
      write_00675 = append_buf(write_00675, &write_00675_len, write_00675_00000, write_00675_00000_len);
      if (write_00675_len > 0) {
         transmit_all(1, write_00675, write_00675_len);
      }
      free(write_00675);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00676 = NULL;
      unsigned int write_00676_len = 0;
      write_00676 = append_var("wait", write_00676, &write_00676_len);
      if (write_00676_len > 0) {
         transmit_all(1, write_00676, write_00676_len);
      }
      free(write_00676);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00677_00000[] = 
         "\x0a";
      static unsigned int write_00677_00000_len = 1;
      unsigned char *write_00677 = NULL;
      unsigned int write_00677_len = 0;
      write_00677 = append_buf(write_00677, &write_00677_len, write_00677_00000, write_00677_00000_len);
      if (write_00677_len > 0) {
         transmit_all(1, write_00677, write_00677_len);
      }
      free(write_00677);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00678 = NULL;
      unsigned int write_00678_len = 0;
      write_00678 = append_var("wait", write_00678, &write_00678_len);
      if (write_00678_len > 0) {
         transmit_all(1, write_00678, write_00678_len);
      }
      free(write_00678);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00679_00000[] = 
         "\x0a";
      static unsigned int write_00679_00000_len = 1;
      unsigned char *write_00679 = NULL;
      unsigned int write_00679_len = 0;
      write_00679 = append_buf(write_00679, &write_00679_len, write_00679_00000, write_00679_00000_len);
      if (write_00679_len > 0) {
         transmit_all(1, write_00679, write_00679_len);
      }
      free(write_00679);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00680 = NULL;
      unsigned int write_00680_len = 0;
      write_00680 = append_var("wait", write_00680, &write_00680_len);
      if (write_00680_len > 0) {
         transmit_all(1, write_00680, write_00680_len);
      }
      free(write_00680);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00681_00000[] = 
         "\x0a";
      static unsigned int write_00681_00000_len = 1;
      unsigned char *write_00681 = NULL;
      unsigned int write_00681_len = 0;
      write_00681 = append_buf(write_00681, &write_00681_len, write_00681_00000, write_00681_00000_len);
      if (write_00681_len > 0) {
         transmit_all(1, write_00681, write_00681_len);
      }
      free(write_00681);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00682 = NULL;
      unsigned int write_00682_len = 0;
      write_00682 = append_var("wait", write_00682, &write_00682_len);
      if (write_00682_len > 0) {
         transmit_all(1, write_00682, write_00682_len);
      }
      free(write_00682);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00683_00000[] = 
         "\x0a";
      static unsigned int write_00683_00000_len = 1;
      unsigned char *write_00683 = NULL;
      unsigned int write_00683_len = 0;
      write_00683 = append_buf(write_00683, &write_00683_len, write_00683_00000, write_00683_00000_len);
      if (write_00683_len > 0) {
         transmit_all(1, write_00683, write_00683_len);
      }
      free(write_00683);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00684 = NULL;
      unsigned int write_00684_len = 0;
      write_00684 = append_var("wait", write_00684, &write_00684_len);
      if (write_00684_len > 0) {
         transmit_all(1, write_00684, write_00684_len);
      }
      free(write_00684);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00685_00000[] = 
         "\x0a";
      static unsigned int write_00685_00000_len = 1;
      unsigned char *write_00685 = NULL;
      unsigned int write_00685_len = 0;
      write_00685 = append_buf(write_00685, &write_00685_len, write_00685_00000, write_00685_00000_len);
      if (write_00685_len > 0) {
         transmit_all(1, write_00685, write_00685_len);
      }
      free(write_00685);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00686 = NULL;
      unsigned int write_00686_len = 0;
      write_00686 = append_var("wait", write_00686, &write_00686_len);
      if (write_00686_len > 0) {
         transmit_all(1, write_00686, write_00686_len);
      }
      free(write_00686);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00687_00000[] = 
         "\x0a";
      static unsigned int write_00687_00000_len = 1;
      unsigned char *write_00687 = NULL;
      unsigned int write_00687_len = 0;
      write_00687 = append_buf(write_00687, &write_00687_len, write_00687_00000, write_00687_00000_len);
      if (write_00687_len > 0) {
         transmit_all(1, write_00687, write_00687_len);
      }
      free(write_00687);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00688 = NULL;
      unsigned int write_00688_len = 0;
      write_00688 = append_var("wait", write_00688, &write_00688_len);
      if (write_00688_len > 0) {
         transmit_all(1, write_00688, write_00688_len);
      }
      free(write_00688);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00689_00000[] = 
         "\x0a";
      static unsigned int write_00689_00000_len = 1;
      unsigned char *write_00689 = NULL;
      unsigned int write_00689_len = 0;
      write_00689 = append_buf(write_00689, &write_00689_len, write_00689_00000, write_00689_00000_len);
      if (write_00689_len > 0) {
         transmit_all(1, write_00689, write_00689_len);
      }
      free(write_00689);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00690 = NULL;
      unsigned int write_00690_len = 0;
      write_00690 = append_var("wait", write_00690, &write_00690_len);
      if (write_00690_len > 0) {
         transmit_all(1, write_00690, write_00690_len);
      }
      free(write_00690);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00691_00000[] = 
         "\x0a";
      static unsigned int write_00691_00000_len = 1;
      unsigned char *write_00691 = NULL;
      unsigned int write_00691_len = 0;
      write_00691 = append_buf(write_00691, &write_00691_len, write_00691_00000, write_00691_00000_len);
      if (write_00691_len > 0) {
         transmit_all(1, write_00691, write_00691_len);
      }
      free(write_00691);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00692 = NULL;
      unsigned int write_00692_len = 0;
      write_00692 = append_var("wait", write_00692, &write_00692_len);
      if (write_00692_len > 0) {
         transmit_all(1, write_00692, write_00692_len);
      }
      free(write_00692);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00693_00000[] = 
         "\x0a";
      static unsigned int write_00693_00000_len = 1;
      unsigned char *write_00693 = NULL;
      unsigned int write_00693_len = 0;
      write_00693 = append_buf(write_00693, &write_00693_len, write_00693_00000, write_00693_00000_len);
      if (write_00693_len > 0) {
         transmit_all(1, write_00693, write_00693_len);
      }
      free(write_00693);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00694 = NULL;
      unsigned int write_00694_len = 0;
      write_00694 = append_var("wait", write_00694, &write_00694_len);
      if (write_00694_len > 0) {
         transmit_all(1, write_00694, write_00694_len);
      }
      free(write_00694);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00695_00000[] = 
         "\x0a";
      static unsigned int write_00695_00000_len = 1;
      unsigned char *write_00695 = NULL;
      unsigned int write_00695_len = 0;
      write_00695 = append_buf(write_00695, &write_00695_len, write_00695_00000, write_00695_00000_len);
      if (write_00695_len > 0) {
         transmit_all(1, write_00695, write_00695_len);
      }
      free(write_00695);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00696 = NULL;
      unsigned int write_00696_len = 0;
      write_00696 = append_var("wait", write_00696, &write_00696_len);
      if (write_00696_len > 0) {
         transmit_all(1, write_00696, write_00696_len);
      }
      free(write_00696);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00697_00000[] = 
         "\x0a";
      static unsigned int write_00697_00000_len = 1;
      unsigned char *write_00697 = NULL;
      unsigned int write_00697_len = 0;
      write_00697 = append_buf(write_00697, &write_00697_len, write_00697_00000, write_00697_00000_len);
      if (write_00697_len > 0) {
         transmit_all(1, write_00697, write_00697_len);
      }
      free(write_00697);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00698 = NULL;
      unsigned int write_00698_len = 0;
      write_00698 = append_var("wait", write_00698, &write_00698_len);
      if (write_00698_len > 0) {
         transmit_all(1, write_00698, write_00698_len);
      }
      free(write_00698);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00699_00000[] = 
         "\x0a";
      static unsigned int write_00699_00000_len = 1;
      unsigned char *write_00699 = NULL;
      unsigned int write_00699_len = 0;
      write_00699 = append_buf(write_00699, &write_00699_len, write_00699_00000, write_00699_00000_len);
      if (write_00699_len > 0) {
         transmit_all(1, write_00699, write_00699_len);
      }
      free(write_00699);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00700 = NULL;
      unsigned int write_00700_len = 0;
      write_00700 = append_var("wait", write_00700, &write_00700_len);
      if (write_00700_len > 0) {
         transmit_all(1, write_00700, write_00700_len);
      }
      free(write_00700);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00701_00000[] = 
         "\x0a";
      static unsigned int write_00701_00000_len = 1;
      unsigned char *write_00701 = NULL;
      unsigned int write_00701_len = 0;
      write_00701 = append_buf(write_00701, &write_00701_len, write_00701_00000, write_00701_00000_len);
      if (write_00701_len > 0) {
         transmit_all(1, write_00701, write_00701_len);
      }
      free(write_00701);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00702 = NULL;
      unsigned int write_00702_len = 0;
      write_00702 = append_var("wait", write_00702, &write_00702_len);
      if (write_00702_len > 0) {
         transmit_all(1, write_00702, write_00702_len);
      }
      free(write_00702);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00703_00000[] = 
         "\x0a";
      static unsigned int write_00703_00000_len = 1;
      unsigned char *write_00703 = NULL;
      unsigned int write_00703_len = 0;
      write_00703 = append_buf(write_00703, &write_00703_len, write_00703_00000, write_00703_00000_len);
      if (write_00703_len > 0) {
         transmit_all(1, write_00703, write_00703_len);
      }
      free(write_00703);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00704 = NULL;
      unsigned int write_00704_len = 0;
      write_00704 = append_var("wait", write_00704, &write_00704_len);
      if (write_00704_len > 0) {
         transmit_all(1, write_00704, write_00704_len);
      }
      free(write_00704);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00705_00000[] = 
         "\x0a";
      static unsigned int write_00705_00000_len = 1;
      unsigned char *write_00705 = NULL;
      unsigned int write_00705_len = 0;
      write_00705 = append_buf(write_00705, &write_00705_len, write_00705_00000, write_00705_00000_len);
      if (write_00705_len > 0) {
         transmit_all(1, write_00705, write_00705_len);
      }
      free(write_00705);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00706 = NULL;
      unsigned int write_00706_len = 0;
      write_00706 = append_var("wait", write_00706, &write_00706_len);
      if (write_00706_len > 0) {
         transmit_all(1, write_00706, write_00706_len);
      }
      free(write_00706);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00707_00000[] = 
         "\x0a";
      static unsigned int write_00707_00000_len = 1;
      unsigned char *write_00707 = NULL;
      unsigned int write_00707_len = 0;
      write_00707 = append_buf(write_00707, &write_00707_len, write_00707_00000, write_00707_00000_len);
      if (write_00707_len > 0) {
         transmit_all(1, write_00707, write_00707_len);
      }
      free(write_00707);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00708 = NULL;
      unsigned int write_00708_len = 0;
      write_00708 = append_var("wait", write_00708, &write_00708_len);
      if (write_00708_len > 0) {
         transmit_all(1, write_00708, write_00708_len);
      }
      free(write_00708);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00709_00000[] = 
         "\x0a";
      static unsigned int write_00709_00000_len = 1;
      unsigned char *write_00709 = NULL;
      unsigned int write_00709_len = 0;
      write_00709 = append_buf(write_00709, &write_00709_len, write_00709_00000, write_00709_00000_len);
      if (write_00709_len > 0) {
         transmit_all(1, write_00709, write_00709_len);
      }
      free(write_00709);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00710 = NULL;
      unsigned int write_00710_len = 0;
      write_00710 = append_var("wait", write_00710, &write_00710_len);
      if (write_00710_len > 0) {
         transmit_all(1, write_00710, write_00710_len);
      }
      free(write_00710);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00711_00000[] = 
         "\x0a";
      static unsigned int write_00711_00000_len = 1;
      unsigned char *write_00711 = NULL;
      unsigned int write_00711_len = 0;
      write_00711 = append_buf(write_00711, &write_00711_len, write_00711_00000, write_00711_00000_len);
      if (write_00711_len > 0) {
         transmit_all(1, write_00711, write_00711_len);
      }
      free(write_00711);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00712 = NULL;
      unsigned int write_00712_len = 0;
      write_00712 = append_var("wait", write_00712, &write_00712_len);
      if (write_00712_len > 0) {
         transmit_all(1, write_00712, write_00712_len);
      }
      free(write_00712);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00713_00000[] = 
         "\x0a";
      static unsigned int write_00713_00000_len = 1;
      unsigned char *write_00713 = NULL;
      unsigned int write_00713_len = 0;
      write_00713 = append_buf(write_00713, &write_00713_len, write_00713_00000, write_00713_00000_len);
      if (write_00713_len > 0) {
         transmit_all(1, write_00713, write_00713_len);
      }
      free(write_00713);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00714 = NULL;
      unsigned int write_00714_len = 0;
      write_00714 = append_var("wait", write_00714, &write_00714_len);
      if (write_00714_len > 0) {
         transmit_all(1, write_00714, write_00714_len);
      }
      free(write_00714);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00715_00000[] = 
         "\x0a";
      static unsigned int write_00715_00000_len = 1;
      unsigned char *write_00715 = NULL;
      unsigned int write_00715_len = 0;
      write_00715 = append_buf(write_00715, &write_00715_len, write_00715_00000, write_00715_00000_len);
      if (write_00715_len > 0) {
         transmit_all(1, write_00715, write_00715_len);
      }
      free(write_00715);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00716 = NULL;
      unsigned int write_00716_len = 0;
      write_00716 = append_var("wait", write_00716, &write_00716_len);
      if (write_00716_len > 0) {
         transmit_all(1, write_00716, write_00716_len);
      }
      free(write_00716);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00717_00000[] = 
         "\x0a";
      static unsigned int write_00717_00000_len = 1;
      unsigned char *write_00717 = NULL;
      unsigned int write_00717_len = 0;
      write_00717 = append_buf(write_00717, &write_00717_len, write_00717_00000, write_00717_00000_len);
      if (write_00717_len > 0) {
         transmit_all(1, write_00717, write_00717_len);
      }
      free(write_00717);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00718 = NULL;
      unsigned int write_00718_len = 0;
      write_00718 = append_var("wait", write_00718, &write_00718_len);
      if (write_00718_len > 0) {
         transmit_all(1, write_00718, write_00718_len);
      }
      free(write_00718);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00719_00000[] = 
         "\x0a";
      static unsigned int write_00719_00000_len = 1;
      unsigned char *write_00719 = NULL;
      unsigned int write_00719_len = 0;
      write_00719 = append_buf(write_00719, &write_00719_len, write_00719_00000, write_00719_00000_len);
      if (write_00719_len > 0) {
         transmit_all(1, write_00719, write_00719_len);
      }
      free(write_00719);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00720 = NULL;
      unsigned int write_00720_len = 0;
      write_00720 = append_var("right", write_00720, &write_00720_len);
      if (write_00720_len > 0) {
         transmit_all(1, write_00720, write_00720_len);
      }
      free(write_00720);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00721_00000[] = 
         "\x0a";
      static unsigned int write_00721_00000_len = 1;
      unsigned char *write_00721 = NULL;
      unsigned int write_00721_len = 0;
      write_00721 = append_buf(write_00721, &write_00721_len, write_00721_00000, write_00721_00000_len);
      if (write_00721_len > 0) {
         transmit_all(1, write_00721, write_00721_len);
      }
      free(write_00721);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00722 = NULL;
      unsigned int write_00722_len = 0;
      write_00722 = append_var("right", write_00722, &write_00722_len);
      if (write_00722_len > 0) {
         transmit_all(1, write_00722, write_00722_len);
      }
      free(write_00722);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00723_00000[] = 
         "\x0a";
      static unsigned int write_00723_00000_len = 1;
      unsigned char *write_00723 = NULL;
      unsigned int write_00723_len = 0;
      write_00723 = append_buf(write_00723, &write_00723_len, write_00723_00000, write_00723_00000_len);
      if (write_00723_len > 0) {
         transmit_all(1, write_00723, write_00723_len);
      }
      free(write_00723);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00724 = NULL;
      unsigned int write_00724_len = 0;
      write_00724 = append_var("right", write_00724, &write_00724_len);
      if (write_00724_len > 0) {
         transmit_all(1, write_00724, write_00724_len);
      }
      free(write_00724);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00725_00000[] = 
         "\x0a";
      static unsigned int write_00725_00000_len = 1;
      unsigned char *write_00725 = NULL;
      unsigned int write_00725_len = 0;
      write_00725 = append_buf(write_00725, &write_00725_len, write_00725_00000, write_00725_00000_len);
      if (write_00725_len > 0) {
         transmit_all(1, write_00725, write_00725_len);
      }
      free(write_00725);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00726 = NULL;
      unsigned int write_00726_len = 0;
      write_00726 = append_var("right", write_00726, &write_00726_len);
      if (write_00726_len > 0) {
         transmit_all(1, write_00726, write_00726_len);
      }
      free(write_00726);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00727_00000[] = 
         "\x0a";
      static unsigned int write_00727_00000_len = 1;
      unsigned char *write_00727 = NULL;
      unsigned int write_00727_len = 0;
      write_00727 = append_buf(write_00727, &write_00727_len, write_00727_00000, write_00727_00000_len);
      if (write_00727_len > 0) {
         transmit_all(1, write_00727, write_00727_len);
      }
      free(write_00727);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00728 = NULL;
      unsigned int write_00728_len = 0;
      write_00728 = append_var("right", write_00728, &write_00728_len);
      if (write_00728_len > 0) {
         transmit_all(1, write_00728, write_00728_len);
      }
      free(write_00728);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00729_00000[] = 
         "\x0a";
      static unsigned int write_00729_00000_len = 1;
      unsigned char *write_00729 = NULL;
      unsigned int write_00729_len = 0;
      write_00729 = append_buf(write_00729, &write_00729_len, write_00729_00000, write_00729_00000_len);
      if (write_00729_len > 0) {
         transmit_all(1, write_00729, write_00729_len);
      }
      free(write_00729);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00730 = NULL;
      unsigned int write_00730_len = 0;
      write_00730 = append_var("right", write_00730, &write_00730_len);
      if (write_00730_len > 0) {
         transmit_all(1, write_00730, write_00730_len);
      }
      free(write_00730);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00731_00000[] = 
         "\x0a";
      static unsigned int write_00731_00000_len = 1;
      unsigned char *write_00731 = NULL;
      unsigned int write_00731_len = 0;
      write_00731 = append_buf(write_00731, &write_00731_len, write_00731_00000, write_00731_00000_len);
      if (write_00731_len > 0) {
         transmit_all(1, write_00731, write_00731_len);
      }
      free(write_00731);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00732 = NULL;
      unsigned int write_00732_len = 0;
      write_00732 = append_var("right", write_00732, &write_00732_len);
      if (write_00732_len > 0) {
         transmit_all(1, write_00732, write_00732_len);
      }
      free(write_00732);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00733_00000[] = 
         "\x0a";
      static unsigned int write_00733_00000_len = 1;
      unsigned char *write_00733 = NULL;
      unsigned int write_00733_len = 0;
      write_00733 = append_buf(write_00733, &write_00733_len, write_00733_00000, write_00733_00000_len);
      if (write_00733_len > 0) {
         transmit_all(1, write_00733, write_00733_len);
      }
      free(write_00733);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00734 = NULL;
      unsigned int write_00734_len = 0;
      write_00734 = append_var("jumpright", write_00734, &write_00734_len);
      if (write_00734_len > 0) {
         transmit_all(1, write_00734, write_00734_len);
      }
      free(write_00734);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00735_00000[] = 
         "\x0a";
      static unsigned int write_00735_00000_len = 1;
      unsigned char *write_00735 = NULL;
      unsigned int write_00735_len = 0;
      write_00735 = append_buf(write_00735, &write_00735_len, write_00735_00000, write_00735_00000_len);
      if (write_00735_len > 0) {
         transmit_all(1, write_00735, write_00735_len);
      }
      free(write_00735);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00736 = NULL;
      unsigned int write_00736_len = 0;
      write_00736 = append_var("wait", write_00736, &write_00736_len);
      if (write_00736_len > 0) {
         transmit_all(1, write_00736, write_00736_len);
      }
      free(write_00736);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00737_00000[] = 
         "\x0a";
      static unsigned int write_00737_00000_len = 1;
      unsigned char *write_00737 = NULL;
      unsigned int write_00737_len = 0;
      write_00737 = append_buf(write_00737, &write_00737_len, write_00737_00000, write_00737_00000_len);
      if (write_00737_len > 0) {
         transmit_all(1, write_00737, write_00737_len);
      }
      free(write_00737);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00738 = NULL;
      unsigned int write_00738_len = 0;
      write_00738 = append_var("wait", write_00738, &write_00738_len);
      if (write_00738_len > 0) {
         transmit_all(1, write_00738, write_00738_len);
      }
      free(write_00738);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00739_00000[] = 
         "\x0a";
      static unsigned int write_00739_00000_len = 1;
      unsigned char *write_00739 = NULL;
      unsigned int write_00739_len = 0;
      write_00739 = append_buf(write_00739, &write_00739_len, write_00739_00000, write_00739_00000_len);
      if (write_00739_len > 0) {
         transmit_all(1, write_00739, write_00739_len);
      }
      free(write_00739);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00740 = NULL;
      unsigned int write_00740_len = 0;
      write_00740 = append_var("wait", write_00740, &write_00740_len);
      if (write_00740_len > 0) {
         transmit_all(1, write_00740, write_00740_len);
      }
      free(write_00740);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00741_00000[] = 
         "\x0a";
      static unsigned int write_00741_00000_len = 1;
      unsigned char *write_00741 = NULL;
      unsigned int write_00741_len = 0;
      write_00741 = append_buf(write_00741, &write_00741_len, write_00741_00000, write_00741_00000_len);
      if (write_00741_len > 0) {
         transmit_all(1, write_00741, write_00741_len);
      }
      free(write_00741);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00742 = NULL;
      unsigned int write_00742_len = 0;
      write_00742 = append_var("wait", write_00742, &write_00742_len);
      if (write_00742_len > 0) {
         transmit_all(1, write_00742, write_00742_len);
      }
      free(write_00742);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00743_00000[] = 
         "\x0a";
      static unsigned int write_00743_00000_len = 1;
      unsigned char *write_00743 = NULL;
      unsigned int write_00743_len = 0;
      write_00743 = append_buf(write_00743, &write_00743_len, write_00743_00000, write_00743_00000_len);
      if (write_00743_len > 0) {
         transmit_all(1, write_00743, write_00743_len);
      }
      free(write_00743);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00744 = NULL;
      unsigned int write_00744_len = 0;
      write_00744 = append_var("wait", write_00744, &write_00744_len);
      if (write_00744_len > 0) {
         transmit_all(1, write_00744, write_00744_len);
      }
      free(write_00744);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00745_00000[] = 
         "\x0a";
      static unsigned int write_00745_00000_len = 1;
      unsigned char *write_00745 = NULL;
      unsigned int write_00745_len = 0;
      write_00745 = append_buf(write_00745, &write_00745_len, write_00745_00000, write_00745_00000_len);
      if (write_00745_len > 0) {
         transmit_all(1, write_00745, write_00745_len);
      }
      free(write_00745);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00746 = NULL;
      unsigned int write_00746_len = 0;
      write_00746 = append_var("jumpright", write_00746, &write_00746_len);
      if (write_00746_len > 0) {
         transmit_all(1, write_00746, write_00746_len);
      }
      free(write_00746);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00747_00000[] = 
         "\x0a";
      static unsigned int write_00747_00000_len = 1;
      unsigned char *write_00747 = NULL;
      unsigned int write_00747_len = 0;
      write_00747 = append_buf(write_00747, &write_00747_len, write_00747_00000, write_00747_00000_len);
      if (write_00747_len > 0) {
         transmit_all(1, write_00747, write_00747_len);
      }
      free(write_00747);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00748 = NULL;
      unsigned int write_00748_len = 0;
      write_00748 = append_var("right", write_00748, &write_00748_len);
      if (write_00748_len > 0) {
         transmit_all(1, write_00748, write_00748_len);
      }
      free(write_00748);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00749_00000[] = 
         "\x0a";
      static unsigned int write_00749_00000_len = 1;
      unsigned char *write_00749 = NULL;
      unsigned int write_00749_len = 0;
      write_00749 = append_buf(write_00749, &write_00749_len, write_00749_00000, write_00749_00000_len);
      if (write_00749_len > 0) {
         transmit_all(1, write_00749, write_00749_len);
      }
      free(write_00749);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00750 = NULL;
      unsigned int write_00750_len = 0;
      write_00750 = append_var("right", write_00750, &write_00750_len);
      if (write_00750_len > 0) {
         transmit_all(1, write_00750, write_00750_len);
      }
      free(write_00750);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00751_00000[] = 
         "\x0a";
      static unsigned int write_00751_00000_len = 1;
      unsigned char *write_00751 = NULL;
      unsigned int write_00751_len = 0;
      write_00751 = append_buf(write_00751, &write_00751_len, write_00751_00000, write_00751_00000_len);
      if (write_00751_len > 0) {
         transmit_all(1, write_00751, write_00751_len);
      }
      free(write_00751);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00752 = NULL;
      unsigned int write_00752_len = 0;
      write_00752 = append_var("right", write_00752, &write_00752_len);
      if (write_00752_len > 0) {
         transmit_all(1, write_00752, write_00752_len);
      }
      free(write_00752);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00753_00000[] = 
         "\x0a";
      static unsigned int write_00753_00000_len = 1;
      unsigned char *write_00753 = NULL;
      unsigned int write_00753_len = 0;
      write_00753 = append_buf(write_00753, &write_00753_len, write_00753_00000, write_00753_00000_len);
      if (write_00753_len > 0) {
         transmit_all(1, write_00753, write_00753_len);
      }
      free(write_00753);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00754 = NULL;
      unsigned int write_00754_len = 0;
      write_00754 = append_var("right", write_00754, &write_00754_len);
      if (write_00754_len > 0) {
         transmit_all(1, write_00754, write_00754_len);
      }
      free(write_00754);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00755_00000[] = 
         "\x0a";
      static unsigned int write_00755_00000_len = 1;
      unsigned char *write_00755 = NULL;
      unsigned int write_00755_len = 0;
      write_00755 = append_buf(write_00755, &write_00755_len, write_00755_00000, write_00755_00000_len);
      if (write_00755_len > 0) {
         transmit_all(1, write_00755, write_00755_len);
      }
      free(write_00755);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00756 = NULL;
      unsigned int write_00756_len = 0;
      write_00756 = append_var("right", write_00756, &write_00756_len);
      if (write_00756_len > 0) {
         transmit_all(1, write_00756, write_00756_len);
      }
      free(write_00756);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00757_00000[] = 
         "\x0a";
      static unsigned int write_00757_00000_len = 1;
      unsigned char *write_00757 = NULL;
      unsigned int write_00757_len = 0;
      write_00757 = append_buf(write_00757, &write_00757_len, write_00757_00000, write_00757_00000_len);
      if (write_00757_len > 0) {
         transmit_all(1, write_00757, write_00757_len);
      }
      free(write_00757);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00758 = NULL;
      unsigned int write_00758_len = 0;
      write_00758 = append_var("right", write_00758, &write_00758_len);
      if (write_00758_len > 0) {
         transmit_all(1, write_00758, write_00758_len);
      }
      free(write_00758);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00759_00000[] = 
         "\x0a";
      static unsigned int write_00759_00000_len = 1;
      unsigned char *write_00759 = NULL;
      unsigned int write_00759_len = 0;
      write_00759 = append_buf(write_00759, &write_00759_len, write_00759_00000, write_00759_00000_len);
      if (write_00759_len > 0) {
         transmit_all(1, write_00759, write_00759_len);
      }
      free(write_00759);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00760 = NULL;
      unsigned int write_00760_len = 0;
      write_00760 = append_var("right", write_00760, &write_00760_len);
      if (write_00760_len > 0) {
         transmit_all(1, write_00760, write_00760_len);
      }
      free(write_00760);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00761_00000[] = 
         "\x0a";
      static unsigned int write_00761_00000_len = 1;
      unsigned char *write_00761 = NULL;
      unsigned int write_00761_len = 0;
      write_00761 = append_buf(write_00761, &write_00761_len, write_00761_00000, write_00761_00000_len);
      if (write_00761_len > 0) {
         transmit_all(1, write_00761, write_00761_len);
      }
      free(write_00761);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00762 = NULL;
      unsigned int write_00762_len = 0;
      write_00762 = append_var("right", write_00762, &write_00762_len);
      if (write_00762_len > 0) {
         transmit_all(1, write_00762, write_00762_len);
      }
      free(write_00762);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00763_00000[] = 
         "\x0a";
      static unsigned int write_00763_00000_len = 1;
      unsigned char *write_00763 = NULL;
      unsigned int write_00763_len = 0;
      write_00763 = append_buf(write_00763, &write_00763_len, write_00763_00000, write_00763_00000_len);
      if (write_00763_len > 0) {
         transmit_all(1, write_00763, write_00763_len);
      }
      free(write_00763);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00764 = NULL;
      unsigned int write_00764_len = 0;
      write_00764 = append_var("right", write_00764, &write_00764_len);
      if (write_00764_len > 0) {
         transmit_all(1, write_00764, write_00764_len);
      }
      free(write_00764);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00765_00000[] = 
         "\x0a";
      static unsigned int write_00765_00000_len = 1;
      unsigned char *write_00765 = NULL;
      unsigned int write_00765_len = 0;
      write_00765 = append_buf(write_00765, &write_00765_len, write_00765_00000, write_00765_00000_len);
      if (write_00765_len > 0) {
         transmit_all(1, write_00765, write_00765_len);
      }
      free(write_00765);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00766 = NULL;
      unsigned int write_00766_len = 0;
      write_00766 = append_var("right", write_00766, &write_00766_len);
      if (write_00766_len > 0) {
         transmit_all(1, write_00766, write_00766_len);
      }
      free(write_00766);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00767_00000[] = 
         "\x0a";
      static unsigned int write_00767_00000_len = 1;
      unsigned char *write_00767 = NULL;
      unsigned int write_00767_len = 0;
      write_00767 = append_buf(write_00767, &write_00767_len, write_00767_00000, write_00767_00000_len);
      if (write_00767_len > 0) {
         transmit_all(1, write_00767, write_00767_len);
      }
      free(write_00767);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00768 = NULL;
      unsigned int write_00768_len = 0;
      write_00768 = append_var("right", write_00768, &write_00768_len);
      if (write_00768_len > 0) {
         transmit_all(1, write_00768, write_00768_len);
      }
      free(write_00768);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00769_00000[] = 
         "\x0a";
      static unsigned int write_00769_00000_len = 1;
      unsigned char *write_00769 = NULL;
      unsigned int write_00769_len = 0;
      write_00769 = append_buf(write_00769, &write_00769_len, write_00769_00000, write_00769_00000_len);
      if (write_00769_len > 0) {
         transmit_all(1, write_00769, write_00769_len);
      }
      free(write_00769);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00770 = NULL;
      unsigned int write_00770_len = 0;
      write_00770 = append_var("jumpleft", write_00770, &write_00770_len);
      if (write_00770_len > 0) {
         transmit_all(1, write_00770, write_00770_len);
      }
      free(write_00770);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00771_00000[] = 
         "\x0a";
      static unsigned int write_00771_00000_len = 1;
      unsigned char *write_00771 = NULL;
      unsigned int write_00771_len = 0;
      write_00771 = append_buf(write_00771, &write_00771_len, write_00771_00000, write_00771_00000_len);
      if (write_00771_len > 0) {
         transmit_all(1, write_00771, write_00771_len);
      }
      free(write_00771);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00772 = NULL;
      unsigned int write_00772_len = 0;
      write_00772 = append_var("left", write_00772, &write_00772_len);
      if (write_00772_len > 0) {
         transmit_all(1, write_00772, write_00772_len);
      }
      free(write_00772);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00773_00000[] = 
         "\x0a";
      static unsigned int write_00773_00000_len = 1;
      unsigned char *write_00773 = NULL;
      unsigned int write_00773_len = 0;
      write_00773 = append_buf(write_00773, &write_00773_len, write_00773_00000, write_00773_00000_len);
      if (write_00773_len > 0) {
         transmit_all(1, write_00773, write_00773_len);
      }
      free(write_00773);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00774 = NULL;
      unsigned int write_00774_len = 0;
      write_00774 = append_var("left", write_00774, &write_00774_len);
      if (write_00774_len > 0) {
         transmit_all(1, write_00774, write_00774_len);
      }
      free(write_00774);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00775_00000[] = 
         "\x0a";
      static unsigned int write_00775_00000_len = 1;
      unsigned char *write_00775 = NULL;
      unsigned int write_00775_len = 0;
      write_00775 = append_buf(write_00775, &write_00775_len, write_00775_00000, write_00775_00000_len);
      if (write_00775_len > 0) {
         transmit_all(1, write_00775, write_00775_len);
      }
      free(write_00775);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00776 = NULL;
      unsigned int write_00776_len = 0;
      write_00776 = append_var("jumpright", write_00776, &write_00776_len);
      if (write_00776_len > 0) {
         transmit_all(1, write_00776, write_00776_len);
      }
      free(write_00776);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00777_00000[] = 
         "\x0a";
      static unsigned int write_00777_00000_len = 1;
      unsigned char *write_00777 = NULL;
      unsigned int write_00777_len = 0;
      write_00777 = append_buf(write_00777, &write_00777_len, write_00777_00000, write_00777_00000_len);
      if (write_00777_len > 0) {
         transmit_all(1, write_00777, write_00777_len);
      }
      free(write_00777);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00778 = NULL;
      unsigned int write_00778_len = 0;
      write_00778 = append_var("right", write_00778, &write_00778_len);
      if (write_00778_len > 0) {
         transmit_all(1, write_00778, write_00778_len);
      }
      free(write_00778);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00779_00000[] = 
         "\x0a";
      static unsigned int write_00779_00000_len = 1;
      unsigned char *write_00779 = NULL;
      unsigned int write_00779_len = 0;
      write_00779 = append_buf(write_00779, &write_00779_len, write_00779_00000, write_00779_00000_len);
      if (write_00779_len > 0) {
         transmit_all(1, write_00779, write_00779_len);
      }
      free(write_00779);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00780 = NULL;
      unsigned int write_00780_len = 0;
      write_00780 = append_var("wait", write_00780, &write_00780_len);
      if (write_00780_len > 0) {
         transmit_all(1, write_00780, write_00780_len);
      }
      free(write_00780);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00781_00000[] = 
         "\x0a";
      static unsigned int write_00781_00000_len = 1;
      unsigned char *write_00781 = NULL;
      unsigned int write_00781_len = 0;
      write_00781 = append_buf(write_00781, &write_00781_len, write_00781_00000, write_00781_00000_len);
      if (write_00781_len > 0) {
         transmit_all(1, write_00781, write_00781_len);
      }
      free(write_00781);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00782 = NULL;
      unsigned int write_00782_len = 0;
      write_00782 = append_var("wait", write_00782, &write_00782_len);
      if (write_00782_len > 0) {
         transmit_all(1, write_00782, write_00782_len);
      }
      free(write_00782);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00783_00000[] = 
         "\x0a";
      static unsigned int write_00783_00000_len = 1;
      unsigned char *write_00783 = NULL;
      unsigned int write_00783_len = 0;
      write_00783 = append_buf(write_00783, &write_00783_len, write_00783_00000, write_00783_00000_len);
      if (write_00783_len > 0) {
         transmit_all(1, write_00783, write_00783_len);
      }
      free(write_00783);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00784 = NULL;
      unsigned int write_00784_len = 0;
      write_00784 = append_var("wait", write_00784, &write_00784_len);
      if (write_00784_len > 0) {
         transmit_all(1, write_00784, write_00784_len);
      }
      free(write_00784);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00785_00000[] = 
         "\x0a";
      static unsigned int write_00785_00000_len = 1;
      unsigned char *write_00785 = NULL;
      unsigned int write_00785_len = 0;
      write_00785 = append_buf(write_00785, &write_00785_len, write_00785_00000, write_00785_00000_len);
      if (write_00785_len > 0) {
         transmit_all(1, write_00785, write_00785_len);
      }
      free(write_00785);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00786 = NULL;
      unsigned int write_00786_len = 0;
      write_00786 = append_var("wait", write_00786, &write_00786_len);
      if (write_00786_len > 0) {
         transmit_all(1, write_00786, write_00786_len);
      }
      free(write_00786);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00787_00000[] = 
         "\x0a";
      static unsigned int write_00787_00000_len = 1;
      unsigned char *write_00787 = NULL;
      unsigned int write_00787_len = 0;
      write_00787 = append_buf(write_00787, &write_00787_len, write_00787_00000, write_00787_00000_len);
      if (write_00787_len > 0) {
         transmit_all(1, write_00787, write_00787_len);
      }
      free(write_00787);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00788 = NULL;
      unsigned int write_00788_len = 0;
      write_00788 = append_var("wait", write_00788, &write_00788_len);
      if (write_00788_len > 0) {
         transmit_all(1, write_00788, write_00788_len);
      }
      free(write_00788);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00789_00000[] = 
         "\x0a";
      static unsigned int write_00789_00000_len = 1;
      unsigned char *write_00789 = NULL;
      unsigned int write_00789_len = 0;
      write_00789 = append_buf(write_00789, &write_00789_len, write_00789_00000, write_00789_00000_len);
      if (write_00789_len > 0) {
         transmit_all(1, write_00789, write_00789_len);
      }
      free(write_00789);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00790 = NULL;
      unsigned int write_00790_len = 0;
      write_00790 = append_var("wait", write_00790, &write_00790_len);
      if (write_00790_len > 0) {
         transmit_all(1, write_00790, write_00790_len);
      }
      free(write_00790);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00791_00000[] = 
         "\x0a";
      static unsigned int write_00791_00000_len = 1;
      unsigned char *write_00791 = NULL;
      unsigned int write_00791_len = 0;
      write_00791 = append_buf(write_00791, &write_00791_len, write_00791_00000, write_00791_00000_len);
      if (write_00791_len > 0) {
         transmit_all(1, write_00791, write_00791_len);
      }
      free(write_00791);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00792 = NULL;
      unsigned int write_00792_len = 0;
      write_00792 = append_var("wait", write_00792, &write_00792_len);
      if (write_00792_len > 0) {
         transmit_all(1, write_00792, write_00792_len);
      }
      free(write_00792);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00793_00000[] = 
         "\x0a";
      static unsigned int write_00793_00000_len = 1;
      unsigned char *write_00793 = NULL;
      unsigned int write_00793_len = 0;
      write_00793 = append_buf(write_00793, &write_00793_len, write_00793_00000, write_00793_00000_len);
      if (write_00793_len > 0) {
         transmit_all(1, write_00793, write_00793_len);
      }
      free(write_00793);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00794 = NULL;
      unsigned int write_00794_len = 0;
      write_00794 = append_var("wait", write_00794, &write_00794_len);
      if (write_00794_len > 0) {
         transmit_all(1, write_00794, write_00794_len);
      }
      free(write_00794);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00795_00000[] = 
         "\x0a";
      static unsigned int write_00795_00000_len = 1;
      unsigned char *write_00795 = NULL;
      unsigned int write_00795_len = 0;
      write_00795 = append_buf(write_00795, &write_00795_len, write_00795_00000, write_00795_00000_len);
      if (write_00795_len > 0) {
         transmit_all(1, write_00795, write_00795_len);
      }
      free(write_00795);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00796 = NULL;
      unsigned int write_00796_len = 0;
      write_00796 = append_var("wait", write_00796, &write_00796_len);
      if (write_00796_len > 0) {
         transmit_all(1, write_00796, write_00796_len);
      }
      free(write_00796);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00797_00000[] = 
         "\x0a";
      static unsigned int write_00797_00000_len = 1;
      unsigned char *write_00797 = NULL;
      unsigned int write_00797_len = 0;
      write_00797 = append_buf(write_00797, &write_00797_len, write_00797_00000, write_00797_00000_len);
      if (write_00797_len > 0) {
         transmit_all(1, write_00797, write_00797_len);
      }
      free(write_00797);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00798 = NULL;
      unsigned int write_00798_len = 0;
      write_00798 = append_var("wait", write_00798, &write_00798_len);
      if (write_00798_len > 0) {
         transmit_all(1, write_00798, write_00798_len);
      }
      free(write_00798);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00799_00000[] = 
         "\x0a";
      static unsigned int write_00799_00000_len = 1;
      unsigned char *write_00799 = NULL;
      unsigned int write_00799_len = 0;
      write_00799 = append_buf(write_00799, &write_00799_len, write_00799_00000, write_00799_00000_len);
      if (write_00799_len > 0) {
         transmit_all(1, write_00799, write_00799_len);
      }
      free(write_00799);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00800 = NULL;
      unsigned int write_00800_len = 0;
      write_00800 = append_var("wait", write_00800, &write_00800_len);
      if (write_00800_len > 0) {
         transmit_all(1, write_00800, write_00800_len);
      }
      free(write_00800);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00801_00000[] = 
         "\x0a";
      static unsigned int write_00801_00000_len = 1;
      unsigned char *write_00801 = NULL;
      unsigned int write_00801_len = 0;
      write_00801 = append_buf(write_00801, &write_00801_len, write_00801_00000, write_00801_00000_len);
      if (write_00801_len > 0) {
         transmit_all(1, write_00801, write_00801_len);
      }
      free(write_00801);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00802 = NULL;
      unsigned int write_00802_len = 0;
      write_00802 = append_var("wait", write_00802, &write_00802_len);
      if (write_00802_len > 0) {
         transmit_all(1, write_00802, write_00802_len);
      }
      free(write_00802);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00803_00000[] = 
         "\x0a";
      static unsigned int write_00803_00000_len = 1;
      unsigned char *write_00803 = NULL;
      unsigned int write_00803_len = 0;
      write_00803 = append_buf(write_00803, &write_00803_len, write_00803_00000, write_00803_00000_len);
      if (write_00803_len > 0) {
         transmit_all(1, write_00803, write_00803_len);
      }
      free(write_00803);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00804 = NULL;
      unsigned int write_00804_len = 0;
      write_00804 = append_var("wait", write_00804, &write_00804_len);
      if (write_00804_len > 0) {
         transmit_all(1, write_00804, write_00804_len);
      }
      free(write_00804);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00805_00000[] = 
         "\x0a";
      static unsigned int write_00805_00000_len = 1;
      unsigned char *write_00805 = NULL;
      unsigned int write_00805_len = 0;
      write_00805 = append_buf(write_00805, &write_00805_len, write_00805_00000, write_00805_00000_len);
      if (write_00805_len > 0) {
         transmit_all(1, write_00805, write_00805_len);
      }
      free(write_00805);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00806 = NULL;
      unsigned int write_00806_len = 0;
      write_00806 = append_var("wait", write_00806, &write_00806_len);
      if (write_00806_len > 0) {
         transmit_all(1, write_00806, write_00806_len);
      }
      free(write_00806);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00807_00000[] = 
         "\x0a";
      static unsigned int write_00807_00000_len = 1;
      unsigned char *write_00807 = NULL;
      unsigned int write_00807_len = 0;
      write_00807 = append_buf(write_00807, &write_00807_len, write_00807_00000, write_00807_00000_len);
      if (write_00807_len > 0) {
         transmit_all(1, write_00807, write_00807_len);
      }
      free(write_00807);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00808 = NULL;
      unsigned int write_00808_len = 0;
      write_00808 = append_var("wait", write_00808, &write_00808_len);
      if (write_00808_len > 0) {
         transmit_all(1, write_00808, write_00808_len);
      }
      free(write_00808);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00809_00000[] = 
         "\x0a";
      static unsigned int write_00809_00000_len = 1;
      unsigned char *write_00809 = NULL;
      unsigned int write_00809_len = 0;
      write_00809 = append_buf(write_00809, &write_00809_len, write_00809_00000, write_00809_00000_len);
      if (write_00809_len > 0) {
         transmit_all(1, write_00809, write_00809_len);
      }
      free(write_00809);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00810 = NULL;
      unsigned int write_00810_len = 0;
      write_00810 = append_var("wait", write_00810, &write_00810_len);
      if (write_00810_len > 0) {
         transmit_all(1, write_00810, write_00810_len);
      }
      free(write_00810);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00811_00000[] = 
         "\x0a";
      static unsigned int write_00811_00000_len = 1;
      unsigned char *write_00811 = NULL;
      unsigned int write_00811_len = 0;
      write_00811 = append_buf(write_00811, &write_00811_len, write_00811_00000, write_00811_00000_len);
      if (write_00811_len > 0) {
         transmit_all(1, write_00811, write_00811_len);
      }
      free(write_00811);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00812 = NULL;
      unsigned int write_00812_len = 0;
      write_00812 = append_var("wait", write_00812, &write_00812_len);
      if (write_00812_len > 0) {
         transmit_all(1, write_00812, write_00812_len);
      }
      free(write_00812);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00813_00000[] = 
         "\x0a";
      static unsigned int write_00813_00000_len = 1;
      unsigned char *write_00813 = NULL;
      unsigned int write_00813_len = 0;
      write_00813 = append_buf(write_00813, &write_00813_len, write_00813_00000, write_00813_00000_len);
      if (write_00813_len > 0) {
         transmit_all(1, write_00813, write_00813_len);
      }
      free(write_00813);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00814 = NULL;
      unsigned int write_00814_len = 0;
      write_00814 = append_var("wait", write_00814, &write_00814_len);
      if (write_00814_len > 0) {
         transmit_all(1, write_00814, write_00814_len);
      }
      free(write_00814);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00815_00000[] = 
         "\x0a";
      static unsigned int write_00815_00000_len = 1;
      unsigned char *write_00815 = NULL;
      unsigned int write_00815_len = 0;
      write_00815 = append_buf(write_00815, &write_00815_len, write_00815_00000, write_00815_00000_len);
      if (write_00815_len > 0) {
         transmit_all(1, write_00815, write_00815_len);
      }
      free(write_00815);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00816 = NULL;
      unsigned int write_00816_len = 0;
      write_00816 = append_var("wait", write_00816, &write_00816_len);
      if (write_00816_len > 0) {
         transmit_all(1, write_00816, write_00816_len);
      }
      free(write_00816);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00817_00000[] = 
         "\x0a";
      static unsigned int write_00817_00000_len = 1;
      unsigned char *write_00817 = NULL;
      unsigned int write_00817_len = 0;
      write_00817 = append_buf(write_00817, &write_00817_len, write_00817_00000, write_00817_00000_len);
      if (write_00817_len > 0) {
         transmit_all(1, write_00817, write_00817_len);
      }
      free(write_00817);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00818 = NULL;
      unsigned int write_00818_len = 0;
      write_00818 = append_var("wait", write_00818, &write_00818_len);
      if (write_00818_len > 0) {
         transmit_all(1, write_00818, write_00818_len);
      }
      free(write_00818);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00819_00000[] = 
         "\x0a";
      static unsigned int write_00819_00000_len = 1;
      unsigned char *write_00819 = NULL;
      unsigned int write_00819_len = 0;
      write_00819 = append_buf(write_00819, &write_00819_len, write_00819_00000, write_00819_00000_len);
      if (write_00819_len > 0) {
         transmit_all(1, write_00819, write_00819_len);
      }
      free(write_00819);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00820 = NULL;
      unsigned int write_00820_len = 0;
      write_00820 = append_var("wait", write_00820, &write_00820_len);
      if (write_00820_len > 0) {
         transmit_all(1, write_00820, write_00820_len);
      }
      free(write_00820);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00821_00000[] = 
         "\x0a";
      static unsigned int write_00821_00000_len = 1;
      unsigned char *write_00821 = NULL;
      unsigned int write_00821_len = 0;
      write_00821 = append_buf(write_00821, &write_00821_len, write_00821_00000, write_00821_00000_len);
      if (write_00821_len > 0) {
         transmit_all(1, write_00821, write_00821_len);
      }
      free(write_00821);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00822 = NULL;
      unsigned int write_00822_len = 0;
      write_00822 = append_var("wait", write_00822, &write_00822_len);
      if (write_00822_len > 0) {
         transmit_all(1, write_00822, write_00822_len);
      }
      free(write_00822);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00823_00000[] = 
         "\x0a";
      static unsigned int write_00823_00000_len = 1;
      unsigned char *write_00823 = NULL;
      unsigned int write_00823_len = 0;
      write_00823 = append_buf(write_00823, &write_00823_len, write_00823_00000, write_00823_00000_len);
      if (write_00823_len > 0) {
         transmit_all(1, write_00823, write_00823_len);
      }
      free(write_00823);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00824 = NULL;
      unsigned int write_00824_len = 0;
      write_00824 = append_var("wait", write_00824, &write_00824_len);
      if (write_00824_len > 0) {
         transmit_all(1, write_00824, write_00824_len);
      }
      free(write_00824);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00825_00000[] = 
         "\x0a";
      static unsigned int write_00825_00000_len = 1;
      unsigned char *write_00825 = NULL;
      unsigned int write_00825_len = 0;
      write_00825 = append_buf(write_00825, &write_00825_len, write_00825_00000, write_00825_00000_len);
      if (write_00825_len > 0) {
         transmit_all(1, write_00825, write_00825_len);
      }
      free(write_00825);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00826 = NULL;
      unsigned int write_00826_len = 0;
      write_00826 = append_var("wait", write_00826, &write_00826_len);
      if (write_00826_len > 0) {
         transmit_all(1, write_00826, write_00826_len);
      }
      free(write_00826);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00827_00000[] = 
         "\x0a";
      static unsigned int write_00827_00000_len = 1;
      unsigned char *write_00827 = NULL;
      unsigned int write_00827_len = 0;
      write_00827 = append_buf(write_00827, &write_00827_len, write_00827_00000, write_00827_00000_len);
      if (write_00827_len > 0) {
         transmit_all(1, write_00827, write_00827_len);
      }
      free(write_00827);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00828 = NULL;
      unsigned int write_00828_len = 0;
      write_00828 = append_var("wait", write_00828, &write_00828_len);
      if (write_00828_len > 0) {
         transmit_all(1, write_00828, write_00828_len);
      }
      free(write_00828);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00829_00000[] = 
         "\x0a";
      static unsigned int write_00829_00000_len = 1;
      unsigned char *write_00829 = NULL;
      unsigned int write_00829_len = 0;
      write_00829 = append_buf(write_00829, &write_00829_len, write_00829_00000, write_00829_00000_len);
      if (write_00829_len > 0) {
         transmit_all(1, write_00829, write_00829_len);
      }
      free(write_00829);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00830 = NULL;
      unsigned int write_00830_len = 0;
      write_00830 = append_var("right", write_00830, &write_00830_len);
      if (write_00830_len > 0) {
         transmit_all(1, write_00830, write_00830_len);
      }
      free(write_00830);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00831_00000[] = 
         "\x0a";
      static unsigned int write_00831_00000_len = 1;
      unsigned char *write_00831 = NULL;
      unsigned int write_00831_len = 0;
      write_00831 = append_buf(write_00831, &write_00831_len, write_00831_00000, write_00831_00000_len);
      if (write_00831_len > 0) {
         transmit_all(1, write_00831, write_00831_len);
      }
      free(write_00831);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00832 = NULL;
      unsigned int write_00832_len = 0;
      write_00832 = append_var("right", write_00832, &write_00832_len);
      if (write_00832_len > 0) {
         transmit_all(1, write_00832, write_00832_len);
      }
      free(write_00832);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00833_00000[] = 
         "\x0a";
      static unsigned int write_00833_00000_len = 1;
      unsigned char *write_00833 = NULL;
      unsigned int write_00833_len = 0;
      write_00833 = append_buf(write_00833, &write_00833_len, write_00833_00000, write_00833_00000_len);
      if (write_00833_len > 0) {
         transmit_all(1, write_00833, write_00833_len);
      }
      free(write_00833);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00834 = NULL;
      unsigned int write_00834_len = 0;
      write_00834 = append_var("right", write_00834, &write_00834_len);
      if (write_00834_len > 0) {
         transmit_all(1, write_00834, write_00834_len);
      }
      free(write_00834);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00835_00000[] = 
         "\x0a";
      static unsigned int write_00835_00000_len = 1;
      unsigned char *write_00835 = NULL;
      unsigned int write_00835_len = 0;
      write_00835 = append_buf(write_00835, &write_00835_len, write_00835_00000, write_00835_00000_len);
      if (write_00835_len > 0) {
         transmit_all(1, write_00835, write_00835_len);
      }
      free(write_00835);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00836 = NULL;
      unsigned int write_00836_len = 0;
      write_00836 = append_var("right", write_00836, &write_00836_len);
      if (write_00836_len > 0) {
         transmit_all(1, write_00836, write_00836_len);
      }
      free(write_00836);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00837_00000[] = 
         "\x0a";
      static unsigned int write_00837_00000_len = 1;
      unsigned char *write_00837 = NULL;
      unsigned int write_00837_len = 0;
      write_00837 = append_buf(write_00837, &write_00837_len, write_00837_00000, write_00837_00000_len);
      if (write_00837_len > 0) {
         transmit_all(1, write_00837, write_00837_len);
      }
      free(write_00837);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00838 = NULL;
      unsigned int write_00838_len = 0;
      write_00838 = append_var("right", write_00838, &write_00838_len);
      if (write_00838_len > 0) {
         transmit_all(1, write_00838, write_00838_len);
      }
      free(write_00838);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00839_00000[] = 
         "\x0a";
      static unsigned int write_00839_00000_len = 1;
      unsigned char *write_00839 = NULL;
      unsigned int write_00839_len = 0;
      write_00839 = append_buf(write_00839, &write_00839_len, write_00839_00000, write_00839_00000_len);
      if (write_00839_len > 0) {
         transmit_all(1, write_00839, write_00839_len);
      }
      free(write_00839);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00840 = NULL;
      unsigned int write_00840_len = 0;
      write_00840 = append_var("right", write_00840, &write_00840_len);
      if (write_00840_len > 0) {
         transmit_all(1, write_00840, write_00840_len);
      }
      free(write_00840);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00841_00000[] = 
         "\x0a";
      static unsigned int write_00841_00000_len = 1;
      unsigned char *write_00841 = NULL;
      unsigned int write_00841_len = 0;
      write_00841 = append_buf(write_00841, &write_00841_len, write_00841_00000, write_00841_00000_len);
      if (write_00841_len > 0) {
         transmit_all(1, write_00841, write_00841_len);
      }
      free(write_00841);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00842 = NULL;
      unsigned int write_00842_len = 0;
      write_00842 = append_var("jumpright", write_00842, &write_00842_len);
      if (write_00842_len > 0) {
         transmit_all(1, write_00842, write_00842_len);
      }
      free(write_00842);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00843_00000[] = 
         "\x0a";
      static unsigned int write_00843_00000_len = 1;
      unsigned char *write_00843 = NULL;
      unsigned int write_00843_len = 0;
      write_00843 = append_buf(write_00843, &write_00843_len, write_00843_00000, write_00843_00000_len);
      if (write_00843_len > 0) {
         transmit_all(1, write_00843, write_00843_len);
      }
      free(write_00843);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00844 = NULL;
      unsigned int write_00844_len = 0;
      write_00844 = append_var("wait", write_00844, &write_00844_len);
      if (write_00844_len > 0) {
         transmit_all(1, write_00844, write_00844_len);
      }
      free(write_00844);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00845_00000[] = 
         "\x0a";
      static unsigned int write_00845_00000_len = 1;
      unsigned char *write_00845 = NULL;
      unsigned int write_00845_len = 0;
      write_00845 = append_buf(write_00845, &write_00845_len, write_00845_00000, write_00845_00000_len);
      if (write_00845_len > 0) {
         transmit_all(1, write_00845, write_00845_len);
      }
      free(write_00845);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00846 = NULL;
      unsigned int write_00846_len = 0;
      write_00846 = append_var("wait", write_00846, &write_00846_len);
      if (write_00846_len > 0) {
         transmit_all(1, write_00846, write_00846_len);
      }
      free(write_00846);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00847_00000[] = 
         "\x0a";
      static unsigned int write_00847_00000_len = 1;
      unsigned char *write_00847 = NULL;
      unsigned int write_00847_len = 0;
      write_00847 = append_buf(write_00847, &write_00847_len, write_00847_00000, write_00847_00000_len);
      if (write_00847_len > 0) {
         transmit_all(1, write_00847, write_00847_len);
      }
      free(write_00847);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00848 = NULL;
      unsigned int write_00848_len = 0;
      write_00848 = append_var("wait", write_00848, &write_00848_len);
      if (write_00848_len > 0) {
         transmit_all(1, write_00848, write_00848_len);
      }
      free(write_00848);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00849_00000[] = 
         "\x0a";
      static unsigned int write_00849_00000_len = 1;
      unsigned char *write_00849 = NULL;
      unsigned int write_00849_len = 0;
      write_00849 = append_buf(write_00849, &write_00849_len, write_00849_00000, write_00849_00000_len);
      if (write_00849_len > 0) {
         transmit_all(1, write_00849, write_00849_len);
      }
      free(write_00849);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00850 = NULL;
      unsigned int write_00850_len = 0;
      write_00850 = append_var("wait", write_00850, &write_00850_len);
      if (write_00850_len > 0) {
         transmit_all(1, write_00850, write_00850_len);
      }
      free(write_00850);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00851_00000[] = 
         "\x0a";
      static unsigned int write_00851_00000_len = 1;
      unsigned char *write_00851 = NULL;
      unsigned int write_00851_len = 0;
      write_00851 = append_buf(write_00851, &write_00851_len, write_00851_00000, write_00851_00000_len);
      if (write_00851_len > 0) {
         transmit_all(1, write_00851, write_00851_len);
      }
      free(write_00851);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00852 = NULL;
      unsigned int write_00852_len = 0;
      write_00852 = append_var("wait", write_00852, &write_00852_len);
      if (write_00852_len > 0) {
         transmit_all(1, write_00852, write_00852_len);
      }
      free(write_00852);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00853_00000[] = 
         "\x0a";
      static unsigned int write_00853_00000_len = 1;
      unsigned char *write_00853 = NULL;
      unsigned int write_00853_len = 0;
      write_00853 = append_buf(write_00853, &write_00853_len, write_00853_00000, write_00853_00000_len);
      if (write_00853_len > 0) {
         transmit_all(1, write_00853, write_00853_len);
      }
      free(write_00853);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00854 = NULL;
      unsigned int write_00854_len = 0;
      write_00854 = append_var("jumpright", write_00854, &write_00854_len);
      if (write_00854_len > 0) {
         transmit_all(1, write_00854, write_00854_len);
      }
      free(write_00854);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00855_00000[] = 
         "\x0a";
      static unsigned int write_00855_00000_len = 1;
      unsigned char *write_00855 = NULL;
      unsigned int write_00855_len = 0;
      write_00855 = append_buf(write_00855, &write_00855_len, write_00855_00000, write_00855_00000_len);
      if (write_00855_len > 0) {
         transmit_all(1, write_00855, write_00855_len);
      }
      free(write_00855);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00856 = NULL;
      unsigned int write_00856_len = 0;
      write_00856 = append_var("right", write_00856, &write_00856_len);
      if (write_00856_len > 0) {
         transmit_all(1, write_00856, write_00856_len);
      }
      free(write_00856);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00857_00000[] = 
         "\x0a";
      static unsigned int write_00857_00000_len = 1;
      unsigned char *write_00857 = NULL;
      unsigned int write_00857_len = 0;
      write_00857 = append_buf(write_00857, &write_00857_len, write_00857_00000, write_00857_00000_len);
      if (write_00857_len > 0) {
         transmit_all(1, write_00857, write_00857_len);
      }
      free(write_00857);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00858 = NULL;
      unsigned int write_00858_len = 0;
      write_00858 = append_var("right", write_00858, &write_00858_len);
      if (write_00858_len > 0) {
         transmit_all(1, write_00858, write_00858_len);
      }
      free(write_00858);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00859_00000[] = 
         "\x0a";
      static unsigned int write_00859_00000_len = 1;
      unsigned char *write_00859 = NULL;
      unsigned int write_00859_len = 0;
      write_00859 = append_buf(write_00859, &write_00859_len, write_00859_00000, write_00859_00000_len);
      if (write_00859_len > 0) {
         transmit_all(1, write_00859, write_00859_len);
      }
      free(write_00859);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00860 = NULL;
      unsigned int write_00860_len = 0;
      write_00860 = append_var("jumpright", write_00860, &write_00860_len);
      if (write_00860_len > 0) {
         transmit_all(1, write_00860, write_00860_len);
      }
      free(write_00860);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00861_00000[] = 
         "\x0a";
      static unsigned int write_00861_00000_len = 1;
      unsigned char *write_00861 = NULL;
      unsigned int write_00861_len = 0;
      write_00861 = append_buf(write_00861, &write_00861_len, write_00861_00000, write_00861_00000_len);
      if (write_00861_len > 0) {
         transmit_all(1, write_00861, write_00861_len);
      }
      free(write_00861);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00862 = NULL;
      unsigned int write_00862_len = 0;
      write_00862 = append_var("jumpright", write_00862, &write_00862_len);
      if (write_00862_len > 0) {
         transmit_all(1, write_00862, write_00862_len);
      }
      free(write_00862);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00863_00000[] = 
         "\x0a";
      static unsigned int write_00863_00000_len = 1;
      unsigned char *write_00863 = NULL;
      unsigned int write_00863_len = 0;
      write_00863 = append_buf(write_00863, &write_00863_len, write_00863_00000, write_00863_00000_len);
      if (write_00863_len > 0) {
         transmit_all(1, write_00863, write_00863_len);
      }
      free(write_00863);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00864 = NULL;
      unsigned int write_00864_len = 0;
      write_00864 = append_var("jumpright", write_00864, &write_00864_len);
      if (write_00864_len > 0) {
         transmit_all(1, write_00864, write_00864_len);
      }
      free(write_00864);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00865_00000[] = 
         "\x0a";
      static unsigned int write_00865_00000_len = 1;
      unsigned char *write_00865 = NULL;
      unsigned int write_00865_len = 0;
      write_00865 = append_buf(write_00865, &write_00865_len, write_00865_00000, write_00865_00000_len);
      if (write_00865_len > 0) {
         transmit_all(1, write_00865, write_00865_len);
      }
      free(write_00865);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00866 = NULL;
      unsigned int write_00866_len = 0;
      write_00866 = append_var("jumpright", write_00866, &write_00866_len);
      if (write_00866_len > 0) {
         transmit_all(1, write_00866, write_00866_len);
      }
      free(write_00866);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00867_00000[] = 
         "\x0a";
      static unsigned int write_00867_00000_len = 1;
      unsigned char *write_00867 = NULL;
      unsigned int write_00867_len = 0;
      write_00867 = append_buf(write_00867, &write_00867_len, write_00867_00000, write_00867_00000_len);
      if (write_00867_len > 0) {
         transmit_all(1, write_00867, write_00867_len);
      }
      free(write_00867);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00868 = NULL;
      unsigned int write_00868_len = 0;
      write_00868 = append_var("wait", write_00868, &write_00868_len);
      if (write_00868_len > 0) {
         transmit_all(1, write_00868, write_00868_len);
      }
      free(write_00868);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00869_00000[] = 
         "\x0a";
      static unsigned int write_00869_00000_len = 1;
      unsigned char *write_00869 = NULL;
      unsigned int write_00869_len = 0;
      write_00869 = append_buf(write_00869, &write_00869_len, write_00869_00000, write_00869_00000_len);
      if (write_00869_len > 0) {
         transmit_all(1, write_00869, write_00869_len);
      }
      free(write_00869);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00870 = NULL;
      unsigned int write_00870_len = 0;
      write_00870 = append_var("jumpright", write_00870, &write_00870_len);
      if (write_00870_len > 0) {
         transmit_all(1, write_00870, write_00870_len);
      }
      free(write_00870);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00871_00000[] = 
         "\x0a";
      static unsigned int write_00871_00000_len = 1;
      unsigned char *write_00871 = NULL;
      unsigned int write_00871_len = 0;
      write_00871 = append_buf(write_00871, &write_00871_len, write_00871_00000, write_00871_00000_len);
      if (write_00871_len > 0) {
         transmit_all(1, write_00871, write_00871_len);
      }
      free(write_00871);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00872 = NULL;
      unsigned int write_00872_len = 0;
      write_00872 = append_var("jumpright", write_00872, &write_00872_len);
      if (write_00872_len > 0) {
         transmit_all(1, write_00872, write_00872_len);
      }
      free(write_00872);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00873_00000[] = 
         "\x0a";
      static unsigned int write_00873_00000_len = 1;
      unsigned char *write_00873 = NULL;
      unsigned int write_00873_len = 0;
      write_00873 = append_buf(write_00873, &write_00873_len, write_00873_00000, write_00873_00000_len);
      if (write_00873_len > 0) {
         transmit_all(1, write_00873, write_00873_len);
      }
      free(write_00873);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00874 = NULL;
      unsigned int write_00874_len = 0;
      write_00874 = append_var("jumpright", write_00874, &write_00874_len);
      if (write_00874_len > 0) {
         transmit_all(1, write_00874, write_00874_len);
      }
      free(write_00874);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00875_00000[] = 
         "\x0a";
      static unsigned int write_00875_00000_len = 1;
      unsigned char *write_00875 = NULL;
      unsigned int write_00875_len = 0;
      write_00875 = append_buf(write_00875, &write_00875_len, write_00875_00000, write_00875_00000_len);
      if (write_00875_len > 0) {
         transmit_all(1, write_00875, write_00875_len);
      }
      free(write_00875);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00876 = NULL;
      unsigned int write_00876_len = 0;
      write_00876 = append_var("jumpright", write_00876, &write_00876_len);
      if (write_00876_len > 0) {
         transmit_all(1, write_00876, write_00876_len);
      }
      free(write_00876);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00877_00000[] = 
         "\x0a";
      static unsigned int write_00877_00000_len = 1;
      unsigned char *write_00877 = NULL;
      unsigned int write_00877_len = 0;
      write_00877 = append_buf(write_00877, &write_00877_len, write_00877_00000, write_00877_00000_len);
      if (write_00877_len > 0) {
         transmit_all(1, write_00877, write_00877_len);
      }
      free(write_00877);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00878 = NULL;
      unsigned int write_00878_len = 0;
      write_00878 = append_var("right", write_00878, &write_00878_len);
      if (write_00878_len > 0) {
         transmit_all(1, write_00878, write_00878_len);
      }
      free(write_00878);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00879_00000[] = 
         "\x0a";
      static unsigned int write_00879_00000_len = 1;
      unsigned char *write_00879 = NULL;
      unsigned int write_00879_len = 0;
      write_00879 = append_buf(write_00879, &write_00879_len, write_00879_00000, write_00879_00000_len);
      if (write_00879_len > 0) {
         transmit_all(1, write_00879, write_00879_len);
      }
      free(write_00879);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00880 = NULL;
      unsigned int write_00880_len = 0;
      write_00880 = append_var("right", write_00880, &write_00880_len);
      if (write_00880_len > 0) {
         transmit_all(1, write_00880, write_00880_len);
      }
      free(write_00880);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00881_00000[] = 
         "\x0a";
      static unsigned int write_00881_00000_len = 1;
      unsigned char *write_00881 = NULL;
      unsigned int write_00881_len = 0;
      write_00881 = append_buf(write_00881, &write_00881_len, write_00881_00000, write_00881_00000_len);
      if (write_00881_len > 0) {
         transmit_all(1, write_00881, write_00881_len);
      }
      free(write_00881);
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** delimited read
      static unsigned char read_00021_delim[] = 
         "\x0a";
      read_00021 = NULL;
      read_00021_len = 0;
      int read_00021_res = delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 1);
      if (read_00021_res) {} //silence unused variable warning
      //**** read assign to var "user1" from pcre: You found the treasure at position x:([0-9]*) y:([0-9]*) after ([0-9]*) moves\n
      static char read_00021_regex[] = 
         "\x59\x6f\x75\x20\x66\x6f\x75\x6e\x64\x20\x74\x68\x65\x20\x74\x72"
         "\x65\x61\x73\x75\x72\x65\x20\x61\x74\x20\x70\x6f\x73\x69\x74\x69"
         "\x6f\x6e\x20\x78\x3a\x28\x5b\x30\x2d\x39\x5d\x2a\x29\x20\x79\x3a"
         "\x28\x5b\x30\x2d\x39\x5d\x2a\x29\x20\x61\x66\x74\x65\x72\x20\x28"
         "\x5b\x30\x2d\x39\x5d\x2a\x29\x20\x6d\x6f\x76\x65\x73\x5c\x6e";
      assign_from_pcre("user1", read_00021, read_00021_len - read_00021_ptr, read_00021_regex, 3);
      free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00022;
      unsigned int read_00022_len;
      unsigned int read_00022_ptr = 0;
      //**** delimited read
      static unsigned char read_00022_delim[] = 
         "\x0a";
      read_00022 = NULL;
      read_00022_len = 0;
      int read_00022_res = delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 1);
      if (read_00022_res) {} //silence unused variable warning
      /* read match pcre:
Move list: (.*)\n
*/
      static char read_00022_00000_regex[] = 
         "\x4d\x6f\x76\x65\x20\x6c\x69\x73\x74\x3a\x20\x28\x2e\x2a\x29\x5c"
         "\x6e";
      static match_result read_00022_00000_match;
      pcre *read_00022_00000_pcre = init_regex(read_00022_00000_regex);
      if (read_00022_00000_pcre != NULL) {
         int rc = regex_match(read_00022_00000_pcre, 0, read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, &read_00022_00000_match);
         if (rc > 0) {
            read_00022_ptr += read_00022_00000_match.match_end - read_00022_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00022_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      free(read_00022);
      if (read_00022_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00023;
      unsigned int read_00023_len;
      unsigned int read_00023_ptr = 0;
      //**** length read
      read_00023_len = 24;
      read_00023 = (unsigned char*)malloc(read_00023_len);
      int read_00023_res = length_read(0, read_00023, read_00023_len);
      if (read_00023_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00023_00000[] = 
         "\x50\x6c\x65\x61\x73\x65\x20\x65\x6e\x74\x65\x72\x20\x79\x6f\x75"
         "\x72\x20\x6e\x61\x6d\x65\x3a\x20";
      read_00023_ptr += data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 24);
      free(read_00023);
      if (read_00023_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00882_00000[] = 
         "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
         "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
         "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30";
      static unsigned int write_00882_00000_len = 42;
      unsigned char *write_00882 = NULL;
      unsigned int write_00882_len = 0;
      write_00882 = append_buf(write_00882, &write_00882_len, write_00882_00000, write_00882_00000_len);
      if (write_00882_len > 0) {
         transmit_all(1, write_00882, write_00882_len);
      }
      free(write_00882);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00883 = NULL;
      unsigned int write_00883_len = 0;
      write_00883 = append_var("TYPE1_REG", write_00883, &write_00883_len);
      for(int j=0; j<4; j++) {
         if(write_00883[j] == 0x00 || write_00883[j] == 0x0a)
            write_00883[j] = write_00883[j] | 0x01;
      }
      if (write_00883_len > 0) {
         transmit_all(1, write_00883, write_00883_len);
      }
      free(write_00883);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00884 = NULL;
      unsigned int write_00884_len = 0;
      write_00884 = append_var("TYPE1_IP", write_00884, &write_00884_len);
      for(int j=0; j<4; j++) {
         if(write_00884[j] == 0x00 || write_00884[j] == 0x0a)
            write_00884[j] = write_00884[j] | 0x01;
      }
      if (write_00884_len > 0) {
         transmit_all(1, write_00884, write_00884_len);
      }
      free(write_00884);
   } while (0);
   do {
      unsigned char *read_00024;
      unsigned int read_00024_len;
      unsigned int read_00024_ptr = 0;
      //**** delimited read
      static unsigned char read_00024_delim[] = 
         "\x0a";
      read_00024 = NULL;
      read_00024_len = 0;
      int read_00024_res = delimited_read(0, &read_00024, &read_00024_len, read_00024_delim, 1);
      if (read_00024_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00024_00000[] = 
         "\x4d\x65\x6e\x75\x0a";
      read_00024_ptr += data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 5);
      free(read_00024);
      if (read_00024_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00025;
      unsigned int read_00025_len;
      unsigned int read_00025_ptr = 0;
      //**** delimited read
      static unsigned char read_00025_delim[] = 
         "\x0a";
      read_00025 = NULL;
      read_00025_len = 0;
      int read_00025_res = delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 1);
      if (read_00025_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00025_00000[] = 
         "\x2d\x2d\x2d\x2d\x2d\x0a";
      read_00025_ptr += data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 6);
      free(read_00025);
      if (read_00025_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00026;
      unsigned int read_00026_len;
      unsigned int read_00026_ptr = 0;
      //**** length read
      read_00026_len = 13;
      read_00026 = (unsigned char*)malloc(read_00026_len);
      int read_00026_res = length_read(0, read_00026, read_00026_len);
      if (read_00026_res) {} //silence unused variable warning
      //**** read assign to var "play" from pcre: Play game: (.*)

      static char read_00026_regex[] = 
         "\x50\x6c\x61\x79\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("play", read_00026, read_00026_len - read_00026_ptr, read_00026_regex, 1);
      free(read_00026);
      if (read_00026_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00027;
      unsigned int read_00027_len;
      unsigned int read_00027_ptr = 0;
      //**** length read
      read_00027_len = 20;
      read_00027 = (unsigned char*)malloc(read_00027_len);
      int read_00027_res = length_read(0, read_00027, read_00027_len);
      if (read_00027_res) {} //silence unused variable warning
      //**** read assign to var "instructions" from pcre: Get instructions: (.*)

      static char read_00027_regex[] = 
         "\x47\x65\x74\x20\x69\x6e\x73\x74\x72\x75\x63\x74\x69\x6f\x6e\x73"
         "\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("instructions", read_00027, read_00027_len - read_00027_ptr, read_00027_regex, 1);
      free(read_00027);
      if (read_00027_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00028;
      unsigned int read_00028_len;
      unsigned int read_00028_ptr = 0;
      //**** length read
      read_00028_len = 15;
      read_00028 = (unsigned char*)malloc(read_00028_len);
      int read_00028_res = length_read(0, read_00028, read_00028_len);
      if (read_00028_res) {} //silence unused variable warning
      //**** read assign to var "highScore" from pcre: High Scores: (.*)

      static char read_00028_regex[] = 
         "\x48\x69\x67\x68\x20\x53\x63\x6f\x72\x65\x73\x3a\x20\x28\x2e\x2a"
         "\x29\x0a";
      assign_from_pcre("highScore", read_00028, read_00028_len - read_00028_ptr, read_00028_regex, 1);
      free(read_00028);
      if (read_00028_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00029;
      unsigned int read_00029_len;
      unsigned int read_00029_ptr = 0;
      //**** length read
      read_00029_len = 13;
      read_00029 = (unsigned char*)malloc(read_00029_len);
      int read_00029_res = length_read(0, read_00029, read_00029_len);
      if (read_00029_res) {} //silence unused variable warning
      //**** read assign to var "quit" from pcre: Quit game: (.*)

      static char read_00029_regex[] = 
         "\x51\x75\x69\x74\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("quit", read_00029, read_00029_len - read_00029_ptr, read_00029_regex, 1);
      free(read_00029);
      if (read_00029_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00885 = NULL;
      unsigned int write_00885_len = 0;
      write_00885 = append_var("highScore", write_00885, &write_00885_len);
      if (write_00885_len > 0) {
         transmit_all(1, write_00885, write_00885_len);
      }
      free(write_00885);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00886_00000[] = 
         "\x0a";
      static unsigned int write_00886_00000_len = 1;
      unsigned char *write_00886 = NULL;
      unsigned int write_00886_len = 0;
      write_00886 = append_buf(write_00886, &write_00886_len, write_00886_00000, write_00886_00000_len);
      if (write_00886_len > 0) {
         transmit_all(1, write_00886, write_00886_len);
      }
      free(write_00886);
   } while (0);
   do {
      unsigned char *read_00030;
      unsigned int read_00030_len;
      unsigned int read_00030_ptr = 0;
      //**** delimited read
      static unsigned char read_00030_delim[] = 
         "\x0a";
      read_00030 = NULL;
      read_00030_len = 0;
      int read_00030_res = delimited_read(0, &read_00030, &read_00030_len, read_00030_delim, 1);
      if (read_00030_res) {} //silence unused variable warning
      /* read match pcre:
Dungeon conquered in ([0-9]*) moves (.*)\n
*/
      static char read_00030_00000_regex[] = 
         "\x44\x75\x6e\x67\x65\x6f\x6e\x20\x63\x6f\x6e\x71\x75\x65\x72\x65"
         "\x64\x20\x69\x6e\x20\x28\x5b\x30\x2d\x39\x5d\x2a\x29\x20\x6d\x6f"
         "\x76\x65\x73\x20\x28\x2e\x2a\x29\x5c\x6e";
      static match_result read_00030_00000_match;
      pcre *read_00030_00000_pcre = init_regex(read_00030_00000_regex);
      if (read_00030_00000_pcre != NULL) {
         int rc = regex_match(read_00030_00000_pcre, 0, read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, &read_00030_00000_match);
         if (rc > 0) {
            read_00030_ptr += read_00030_00000_match.match_end - read_00030_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00030_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      free(read_00030);
      if (read_00030_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00031;
      unsigned int read_00031_len;
      unsigned int read_00031_ptr = 0;
      //**** delimited read
      static unsigned char read_00031_delim[] = 
         "\x0a";
      read_00031 = NULL;
      read_00031_len = 0;
      int read_00031_res = delimited_read(0, &read_00031, &read_00031_len, read_00031_delim, 1);
      if (read_00031_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00031_00000[] = 
         "\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d"
         "\x2d\x2d\x2d\x0a";
      read_00031_ptr += data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 20);
      free(read_00031);
      if (read_00031_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00032;
      unsigned int read_00032_len;
      unsigned int read_00032_ptr = 0;
      //**** delimited read
      static unsigned char read_00032_delim[] = 
         "\x0a";
      read_00032 = NULL;
      read_00032_len = 0;
      int read_00032_res = delimited_read(0, &read_00032, &read_00032_len, read_00032_delim, 1);
      if (read_00032_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00032_00000[] = 
         "\x20\x6d\x6f\x76\x65\x73\x20\x20\x20\x7c\x20\x20\x20\x6e\x61\x6d"
         "\x65\x20\x20\x0a";
      read_00032_ptr += data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 20);
      free(read_00032);
      if (read_00032_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00033;
      unsigned int read_00033_len;
      unsigned int read_00033_ptr = 0;
      //**** delimited read
      static unsigned char read_00033_delim[] = 
         "\x0a";
      read_00033 = NULL;
      read_00033_len = 0;
      int read_00033_res = delimited_read(0, &read_00033, &read_00033_len, read_00033_delim, 1);
      if (read_00033_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00033_00000[] = 
         "\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d"
         "\x2d\x2d\x2d\x0a";
      read_00033_ptr += data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 20);
      free(read_00033);
      if (read_00033_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00034;
      unsigned int read_00034_len;
      unsigned int read_00034_ptr = 0;
      //**** delimited read
      static unsigned char read_00034_delim[] = 
         "\x0a";
      read_00034 = NULL;
      read_00034_len = 0;
      int read_00034_res = delimited_read(0, &read_00034, &read_00034_len, read_00034_delim, 1);
      if (read_00034_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00034_00000[] = 
         "\x4d\x65\x6e\x75\x0a";
      read_00034_ptr += data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 5);
      free(read_00034);
      if (read_00034_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** delimited read
      static unsigned char read_00035_delim[] = 
         "\x0a";
      read_00035 = NULL;
      read_00035_len = 0;
      int read_00035_res = delimited_read(0, &read_00035, &read_00035_len, read_00035_delim, 1);
      if (read_00035_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00035_00000[] = 
         "\x2d\x2d\x2d\x2d\x2d\x0a";
      read_00035_ptr += data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 6);
      free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00036;
      unsigned int read_00036_len;
      unsigned int read_00036_ptr = 0;
      //**** length read
      read_00036_len = 13;
      read_00036 = (unsigned char*)malloc(read_00036_len);
      int read_00036_res = length_read(0, read_00036, read_00036_len);
      if (read_00036_res) {} //silence unused variable warning
      //**** read assign to var "play" from pcre: Play game: (.*)

      static char read_00036_regex[] = 
         "\x50\x6c\x61\x79\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("play", read_00036, read_00036_len - read_00036_ptr, read_00036_regex, 1);
      free(read_00036);
      if (read_00036_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** length read
      read_00037_len = 20;
      read_00037 = (unsigned char*)malloc(read_00037_len);
      int read_00037_res = length_read(0, read_00037, read_00037_len);
      if (read_00037_res) {} //silence unused variable warning
      //**** read assign to var "instructions" from pcre: Get instructions: (.*)

      static char read_00037_regex[] = 
         "\x47\x65\x74\x20\x69\x6e\x73\x74\x72\x75\x63\x74\x69\x6f\x6e\x73"
         "\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("instructions", read_00037, read_00037_len - read_00037_ptr, read_00037_regex, 1);
      free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00038;
      unsigned int read_00038_len;
      unsigned int read_00038_ptr = 0;
      //**** length read
      read_00038_len = 15;
      read_00038 = (unsigned char*)malloc(read_00038_len);
      int read_00038_res = length_read(0, read_00038, read_00038_len);
      if (read_00038_res) {} //silence unused variable warning
      //**** read assign to var "highScore" from pcre: High Scores: (.*)

      static char read_00038_regex[] = 
         "\x48\x69\x67\x68\x20\x53\x63\x6f\x72\x65\x73\x3a\x20\x28\x2e\x2a"
         "\x29\x0a";
      assign_from_pcre("highScore", read_00038, read_00038_len - read_00038_ptr, read_00038_regex, 1);
      free(read_00038);
      if (read_00038_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00039;
      unsigned int read_00039_len;
      unsigned int read_00039_ptr = 0;
      //**** length read
      read_00039_len = 13;
      read_00039 = (unsigned char*)malloc(read_00039_len);
      int read_00039_res = length_read(0, read_00039, read_00039_len);
      if (read_00039_res) {} //silence unused variable warning
      //**** read assign to var "quit" from pcre: Quit game: (.*)

      static char read_00039_regex[] = 
         "\x51\x75\x69\x74\x20\x67\x61\x6d\x65\x3a\x20\x28\x2e\x2a\x29\x0a";
      assign_from_pcre("quit", read_00039, read_00039_len - read_00039_ptr, read_00039_regex, 1);
      free(read_00039);
      if (read_00039_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00887 = NULL;
      unsigned int write_00887_len = 0;
      write_00887 = append_var("quit", write_00887, &write_00887_len);
      if (write_00887_len > 0) {
         transmit_all(1, write_00887, write_00887_len);
      }
      free(write_00887);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00888_00000[] = 
         "\x0a";
      static unsigned int write_00888_00000_len = 1;
      unsigned char *write_00888 = NULL;
      unsigned int write_00888_len = 0;
      write_00888 = append_buf(write_00888, &write_00888_len, write_00888_00000, write_00888_00000_len);
      if (write_00888_len > 0) {
         transmit_all(1, write_00888, write_00888_len);
      }
      free(write_00888);
   } while (0);
}
