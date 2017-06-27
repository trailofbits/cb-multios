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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x36\x22\x8f\x12"
         "\x35\xa7\xba\x64\x04\x93\xf9\x17\xc6\x00\x00\x00\x81\xf1\x44\xd4"
         "\x49\xdc\x82\xad\xa2\x66\x50\xb1\x65\x12\xf5\xdc\x6c\x41\x3e\xf8"
         "\x5e\xcc\x2d\xc6\x09\x09\x00\x09\x39\xe9\x87\xb3\x83\x39\xdc\x5a"
         "\x4d\x29\x52\xcf\xd0\xc6\xb7\x1d\x6e\x1f\x59\xde\xa4\x31\x9e\x90"
         "\x20\x97\x91\x72\xf2\x4e\xab\x51\x20\x08\x45\xa9\x5e\x8e\xd3\xbe"
         "\x58\xd9\xf0\xa1\xf8\x93\xa3\x9f\x4c\x76\x9d\xfe\x76\x07\x8c\xd5"
         "\x1c\x64\xf4\x77\x32\x91\xdd\xa1\x25\x56\xa6\x05\x2d\x13\x76\x86"
         "\x09\x60\x85\x93\x6e\xca\x8c\xe2\xb5\x1f\x48\xde\xf9\x8b\x23\xd4"
         "\xcc\x4f\x36\xa1\xcc\xed\x98\x0f\xd1\xf1\x11\x60\xae\xbf\x0e\xda"
         "\x26\x94\x53\x55\xc3\x8d\xb9\x54\x1e\x13\x97\xe9\x67\xe6\x05\x47"
         "\xdc\x31\xc9\x61\x6c\x55\xee\x09\x00\xae\xa6\x72\x79\x35\xd3\x87"
         "\xaf\x09\xf9\x5f\xd7\x87\x6a\xf1\xf5\x43\x6a\xba\xcb\x60\xc0\x3b"
         "\x7e\xab\x60\xce\xf5\x80\x95\x50\x7a\x49\xa2\x70\xd6\x3f\x5b\x88"
         "\x3c\x22\xfa\x7b\xa7\x1d\x4f\x52\x04\x78\x23\x7b\x81\xfa\x06\xe1"
         "\xf2\x7a\x71\x47\x4e\x8f\xf7\x75\x89\xaa\x21\x9e\x41\xca\xac\xa7"
         "\xf0\x21\x38\x2a\x70\x88\x68\x0a\x1a\x02\x94\xfa\x0a\x03\xe7\x00"
         "\x7b\x6c\x21\xa4\x08\x74\xe2\x9a\xbc\xef\xda\x00\xac\x6b\x7c\x88"
         "\x28\x60\x88\xb8\x92\x5b\x14\x10\x87\xa0\x41\x95\x63\xba\x76\x5b"
         "\x10\xf1\x2d\x3f\x80\x89\x43\x00\x1b\x7c\xce\x80\xb2\x75\xde\x5d"
         "\x0a\x37\xb7\xb0\x0d\x30\x49\xae\xe5\xb3\x6b\x75\x35\x99\x04\xb0"
         "\xab\x3d\x06\x54\xbf\x22\xd5\x32\x81\x07\x18\xbd\x3e\xe8\x80\x95"
         "\x09\x00\x3e\x47\x9f\x96\x9d\x15\xa3\xa3\x58\x42\x39\xeb\xa2\xf4"
         "\x3d\xe5\x43\xbf\x3d\xe5\xe9\x2c\x96\x22\xfa\x67\x0a\xf9\xb0\x73"
         "\xf1\xc9\x75\x11\xeb\xae\x69\xee\x75\x6a\xdf\x9c\xf4\x3b\x8f\x3d"
         "\xc4\xa9\x99\xb6\x9b\x91\xca\x2e\x23\x67\xb6\xfe\x88\xb8\xca\xcb"
         "\x0e\x8a\x3c\xe9\xa5\xfe\x58\xe7\x85\x46\x2d\xeb\x27\xfb\xf6\xa7"
         "\xd2\x44\x2e\x66\x07\x0d\x4a\xf0\x34\x36\x8e\xa9\xd7\xba\x05\xa8"
         "\xab\x5e\x84\xd5\xfb\xcd\xeb\x85\xb3\xc7\x8a\x4b\xd1\xae\x82\x50"
         "\x39\x3d\x84\x5e\x91\x24\x6c\x1d\x0c\xee\xdf\xfa\x9a\x88\x74\x79"
         "\xd9\xe5\x79\xd1\xd2\x4c\x1a\xa8\x85\x2c\x07\x23\x10\xa8\x15\x69"
         "\x45\x81\xf3\x84\x91\xe9\x99\x23\x87\x2c\x24\x56\x0b\x36\x40\xb1"
         "\x6c\x04\x51\xe5\x75\x23\x51\x90\x1f\xb3\xc1\x62\xf5\x32\x6c\x73"
         "\x93\x05\x37\x8a\xdd\xb2\x0b\x7e\x9d\x1e\x27\x26\x12\x85\xe1\x29"
         "\xd2\x9c\xfd\xe9\x98\xb6\x9f\x55\xb3\x98\xa9\x51\xf3\x3a\xf9\x67"
         "\xd4\xe2\x4a\x4d\x7e\x2e\x71\x23\x56\x68\xcb\xf2\xb8\xd0\x7e\x56"
         "\xb9\x90\xad\xf2\x87\x85\x11\x6e\x9c\xf5\xd9\x1c\x48\x6c\x32\x21"
         "\x18\x64\xe2\x7d\x4e\xc5\xe7\x82\xe6\x50\x9f\x2c\xaf\x9a\x91\x73"
         "\x5a\xf6\x3e\x10\x64\x6d\xcd\xe9\x4c\x5b\x6d\xad\xd1\xae\x54\xf4"
         "\x13\xd0\x26\xa3\x27\xc0\xad\xfe\x91\x97\x3b\x91\xad\xe2\xe8\x72"
         "\xbb\x6c\xdb\x37\xa8\x3b\xe8\x7b\xc2\x1d\xc0\xf7\xdf\x9e\x9e\x7d"
         "\xe6\xf9\xdc\xf9\xc0\x35\x41\x6b\xfe\x34\x6e\xf9\x24\x76\xa5\x3b"
         "\xf5\x92\x49\xe4\x16\x89\xea\xa9\x97\xf2\x4b\xd1\x37\x97\xfc\xee"
         "\x44\x2b\xd2\xd4\xbb\x97\xe1\x34\xeb\x5e\xbb\x86\x4e\x57\xb2\x1a"
         "\xb4\x25\xec\xb0\x3e\x4d\x0a\xe1\x31\x60\x2d\xdd\xfa\x34\x4f\x75"
         "\xbb\x65\x3b\xbb\x84\xad\x8e\x47\x3c\xbc\xb0\xa1\x53\xfd\x68\xfb"
         "\x67\x5e\x76\x93\x1f\x3d\xbe\xbb\x41\x65\x53\xee\x4e\xd5\x26\x4a"
         "\xc2\x00\xa1\xcd\xf4\xff\x28\x01\xa6\xbd\x49\xe7\x1f\xc9\x06\x64"
         "\x10\xbb\x55\x51\xfa\xc0\x7c\x83\xc5\x8a\x99\xc8\x99\x3b\xf8\xa7"
         "\x90\x35\xa3\xa3\x44\x13\x03\x65\xd3\x80\x38\xdb\x51\xf8\xed\xdb"
         "\x9f\xf5\x9a\x39\x5e\x4c\xe4\xb8\x26\x1b\x5e\x45\xf8\x67\x49\x25"
         "\xa7\xb1\x28\x8f\x1e\xff\x71\xc1\x87\xd8\x09\xef\x02\x66\x30\x06"
         "\xc4\x47\x75\x43\x81\x4e\x2c\xcb\x8b\x1d\xaa\x9f\xf8\x2b\x55\x19"
         "\xc7\x2f\x22\x26\x9c\xf1\xef\xba\x96\xb7\x64\x55\xf5\xc1\x9b\xb5"
         "\xe1\x21\x24\xd9\x6a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===limsypersistence
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x69\x6d\x73\x79\x70\x65\x72\x73\x69\x73"
         "\x74\x65\x6e\x63\x65";
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
.*===chinkingcytologic
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x68\x69\x6e\x6b\x69\x6e\x67\x63\x79\x74"
         "\x6f\x6c\x6f\x67\x69\x63";
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
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 4);
      if (read_00005_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00005_00000_match;
      pcre *read_00005_00000_pcre = cgc_init_regex(read_00005_00000_regex);
      if (read_00005_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00005_00000_pcre, 0, read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, &read_00005_00000_match);
         if (rc > 0) {
            read_00005_ptr += read_00005_00000_match.match_end - read_00005_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00005_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
