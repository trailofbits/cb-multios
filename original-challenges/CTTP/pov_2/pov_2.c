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
   negotiate_type2();
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x50\x54\x54\x43\x33\x1f\x3d\x81\x8f\xc8\xf7\x7f\x04\x00\x00\x00"
         "\x00\x00\x00\x00\xaa\xaa\xaa\xba\x00\x00\x00\x00";
      static unsigned int write_00000_00000_len = 28;
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
      unsigned char key = 0;
      unsigned int to_read = 0;
      unsigned int level = 0;
      unsigned char *challenge;
      //**** length read
      int read_00000_res = length_read(0, &key, sizeof(key));
      read_00000_res = length_read(0, (unsigned char*)&to_read, sizeof(to_read));

      challenge = malloc(to_read+4); //4 bytes for token
      read_00000_res = length_read(0, challenge, to_read+4);
      transmit_all(1, challenge, to_read+4);
      read_00000_res = length_read(0, (unsigned char*)&level, sizeof(level));
      if (read_00000_res) {} //silence unused variable warning

      free(challenge);
      if (read_00000_ptr) {}  //silence unused variable warning if any
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
      //**** read assign to var "TYPE2_VALUE" from slice
      assign_from_slice("TYPE2_VALUE", read_00004, read_00004_len - read_00004_ptr, 0, 0, 1);
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** submitting type 2 POV results
   submit_type2("TYPE2_VALUE");
}
