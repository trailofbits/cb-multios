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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xda\xf1\x62\xf1"
         "\x10\x76\x4a\x3f\xe0\x39\x5c\xbc\x1b\x01\x00\x00\x7f\xe9\xf3\x9a"
         "\x6d\x7e\x4d\x8a\x31\xfc\x0b\x7b\x45\x26\xbc\xfc\x87\x3e\xc7\x15"
         "\x76\xe2\xee\xd3\xe0\xd1\x73\xae\x4c\xe4\xff\xf5\x79\x37\x30\xc2"
         "\xa5\xbf\x46\x5f\x80\x22\xdf\x71\x19\xaa\x19\x03\x8d\x43\x58\xaa"
         "\xdc\x8d\x96\x1c\x7e\x45\x0b\xfb\xfc\x79\xb8\x7c\x32\x39\x18\x67"
         "\x06\xd1\xa6\xd2\xa0\xf9\x8b\x9d\x5a\x73\xae\xb7\x12\xba\x3a\x95"
         "\xbb\x03\xbb\xa0\x74\xf1\x72\x17\xc2\x17\x6c\x42\xde\x62\xcb\x32"
         "\xfb\x93\x4f\x3d\x4a\xac\x4a\xce\x6e\xa6\xc7\xe4\x6b\x3c\x72\x53"
         "\xeb\xef\x30\xd3\x0a\x9d\x0d\xbe\xf4\xec\xcd\x30\x94\x45\x6a\xee"
         "\xae\x50\xc5\xaf\xaa\x49\x4c\x4f\xc6\xbb\x36\x77\x08\x73\x4c\x5e"
         "\xf4\x36\x68\x34\x65\xe6\xee\x36\xb1\x3b\xd5\x0e\x97\x4e\xb0\xd4"
         "\xc4\x8b\xc2\x96\x97\xe6\xb0\x91\x16\xd0\x00\x5d\x04\x70\xfa\xb2"
         "\x35\x1a\x2b\x21\x4d\xaf\x56\x89\x18\x2f\x69\x76\x1a\xac\x07\xdb"
         "\x3a\x73\x89\x03\x60\xd3\x44\x56\xf4\x97\x4f\x1d\x07\x12\x41\xb5"
         "\x00\xfb\x23\x36\x10\xe5\xa1\x77\x65\x4b\xed\x27\xa3\xf1\x75\xc7"
         "\xf9\x69\xc5\x74\xac\xe8\xa9\x5c\x48\x42\x0e\x2d\x1d\xad\xab\x9e"
         "\xcd\xa6\xd1\x9b\xb7\xa4\x33\x6d\xe2\xcb\x2c\x67\x6b\xdd\x0a\x12"
         "\xb9\x23\xc9\x47\x0d\xcb\x53\x20\xb8\x74\x02\xa6\x48\xa5\xab\x62"
         "\x4d\x4f\x32\xa0\x74\xbf\xac\x4e\x50\x30\xbf\xfd\x58\x5d\xbc\x47"
         "\xd3\x38\xfa\x9a\xd3\xe6\xe9\x7e\xae\x03\xca\x50\x18\x05\xd6\xad"
         "\x6b\x7a\x67\x0d\xfb\x43\x21\xb7\xe1\xf7\x79\x94\x26\x52\xff\x96"
         "\xe5\x2c\xbf\x57\x9d\xf5\x54\x57\x91\xd7\x3a\x95\x45\xf9\x0d\x8e"
         "\xb5\xc1\x19\x01\x94\x70\x91\x52\x80\x50\x8c\x63\xec\xbc\x49\x58"
         "\xe6\xed\x3b\x0a\x4d\x5a\x4c\x5c\x46\xb5\xf6\x72\x34\x0a\x06\x5c"
         "\x43\xdb\xc6\xb8\x25\xbf\x64\x88\x8c\x84\xc4\x8b\xc7\x85\x52\x60"
         "\x80\xca\x05\xa8\x7e\x60\xff\xf6\x6a\x23\x2d\xca\x58\x58\x23\x14"
         "\x9c\xac\x1b\x2c\x97\x3f\xa3\x1c\x63\x75\x13\x0e\x7a\x17\x81\xf0"
         "\x1e\x56\x72\x92\x61\xb0\xf4\xb0\x71\xaf\x5f\x53\x40\xc3\xf5\x68"
         "\xfa\x42\xbd\x28\xaf\x0c\xff\x9a\x9e\x79\x45\xb3\x85\xe6\x6b\xed"
         "\x0d\x4f\x19\x46\xca\xa7\x29\x19\x92\x35\xae\xd5\xa0\xe2\x82\x2b"
         "\x15\xf2\x5e\xc3\x02\x4e\xfe\xa4\x8e\xf9\x50\x91\xc3\x52\x4c\xc6"
         "\x28\xb3\x92\x59\x9e\x32\xf1\xcf\x24\xf2\x7e\xf7\x48\x85\xa3\x15"
         "\x5d\xaa\x6c\x9c\x0a\xf8\x2c\x17\x05\x3d\x5d\x38\xe7\x46\xb3\x5f"
         "\x3c\x58\xca\x09\x9f\x74\xbb\x55\xb7\xd2\xac\x34\x6f\x84\xbf\xd4"
         "\x78\x0a\x6c\x25\x83\x9b\xc4\xe0\xcd\x02\x4d\x13\x88\xdb\x36\x69"
         "\x8a\x8b\x92\x21\x01\x5c\x9a\x0e\x79\xc0\xd0\xee\xf0\xe7\x03\x05"
         "\x51\x88\x8a\x69\xe7\xce\xb1\x55\xd0\xc9\x7b\x67\x53\xe5\x6e\xb7"
         "\x68\xda\xe6\x5a\xb9\xad\x3f\xac\x3f\xe5\xba\x87\xc8\x3b\xc1\xd6"
         "\xa0\x4e\x16\xba\xa0\x96\xfd\x67\xdd\xdf\xa7\xae\x30\xb6\x2e\xf2"
         "\xf5\x0d\x7e\x4d\x64\xfe\xb7\x7f\xbb\x7a\x85\xab\xaa\x23\x20\xf1"
         "\x65\x1c\xeb\x88\x82\x90\x0e\x2a\xe8\xd8\x0e\x0c\x3f\x7d\x19\xd6"
         "\x80\x99\x2d\xf3\xe0\xe8\x81\x1b\x64\xe1\x9f\x28\x67\x2c\x0b\x4d"
         "\xb6\xbf\xf0\x1a\x8d\xe1\xbb\x2a\x10\xbe\x20\x20\x20\x20\x20\x20"
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
.*===aerophilethyroidless
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x65\x72\x6f\x70\x68\x69\x6c\x65\x74\x68"
         "\x79\x72\x6f\x69\x64\x6c\x65\x73\x73";
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
.*===avalanchestylopization
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x76\x61\x6c\x61\x6e\x63\x68\x65\x73\x74"
         "\x79\x6c\x6f\x70\x69\x7a\x61\x74\x69\x6f\x6e";
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
