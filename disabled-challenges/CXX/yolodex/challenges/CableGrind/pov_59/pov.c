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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb7\xb3\x7c\xc2"
         "\x11\x69\xc7\x4b\x3f\x8a\x5c\xa7\x5c\x90\x4f\x2c\x5a\xb8\xb6\x57"
         "\x47\x01\x00\x00\x04\xbf\xd9\xd0\x1c\xb1\x1d\x81\xef\xd1\xb2\x6a"
         "\x25\x51\xaf\x4d\xc8\x7d\x86\xe7\x15\xd0\xfb\xda\x78\x7a\x81\xbf"
         "\xe7\x21\x97\x07\xa2\x0a\xa2\x2a\x02\x16\x80\x60\x6f\x2c\xbf\x8a"
         "\x9f\xad\x05\x6a\x95\x81\xd5\xba\xfd\x8c\xdf\x38\x87\x84\xa3\x4b"
         "\xc6\xa3\x2e\x3c\xd9\x33\x8f\xe8\xd5\x0c\x5d\x58\x0b\xa8\xc7\xa1"
         "\x62\xdd\x5c\x8e\x3f\xb7\xe0\xf2\xc2\x1b\x58\xaf\x17\x46\x79\x8c"
         "\xc8\x93\xbd\xf7\x19\x4d\x00\x47\xd2\x26\x86\x38\xb9\x3e\x24\xd9"
         "\x79\xae\x9e\xb6\x2a\xdf\xe8\x18\xf1\xff\xe8\xab\xef\x49\x24\xf6"
         "\x80\x68\x23\x0a\xfe\x61\x4f\xc6\x8f\x2f\xc7\xf3\x42\x61\x1a\x86"
         "\xbc\x33\xa1\xac\x41\xa6\xfd\xdd\xed\x86\xee\xa1\x01\x7e\xff\x21"
         "\xb7\x75\x34\x45\x3c\x7f\x17\xbc\xf2\x2d\xf4\x68\xab\x77\x69\xe3"
         "\x0b\x73\xaa\x7d\x54\x10\xc4\xdd\xe6\x21\x7a\xf3\xc2\xe2\xed\xeb"
         "\xbb\xe8\xb9\x96\xd9\x3d\xf2\xb8\xc8\x17\x33\x82\x1d\x75\x6f\x8f"
         "\x5c\x59\x8e\xba\x96\x03\xd3\x08\x3e\xb7\xdc\x20\x5f\xa6\xd5\x51"
         "\xfb\xb3\x4c\x28\xef\xfe\x59\x1f\x7e\xdb\xec\x2e\x3b\x37\x28\x79"
         "\x1b\x95\x91\xab\xba\x5d\x92\xb3\x97\x2c\xe8\x59\x6f\xa4\x27\xf0"
         "\x9f\x42\xa6\x1b\x93\xef\x07\xf8\x37\x05\xcd\x1a\xb9\x53\x5c\x16"
         "\x29\x59\x8b\x0b\xe2\xa3\x1e\x86\xe1\xc1\xb9\x8d\xc7\x2f\x5c\x5d"
         "\x62\xad\x3d\xfd\x03\x3f\x03\x85\x41\xee\x84\x63\xf2\xe7\x3c\xff"
         "\x3d\xcc\x69\x56\xe5\xf0\x17\x0c\x81\x01\x00\x16\x4d\xf2\xbd\xdc"
         "\x00\x63\xde\x81\xb3\x9b\x9b\xf7\x0b\x4f\x30\xed\x92\xb4\x16\x08"
         "\x85\x11\xcd\x04\xce\x60\x5a\x24\xfb\xb1\xa0\x91\x49\x55\x14\x2c"
         "\xd0\x6e\x99\xe9\x92\x2c\xdd\x46\xc2\xd8\x90\xcd\x34\xd8\xfc\xcb"
         "\xd9\x24\x80\xcd\xc0\x96\x8f\x65\x72\x64\x12\x1d\xf4\x4e\x11\x1c"
         "\x22\x5f\xa9\xf1\x31\xa0\xdb\xb5\xb3\x8b\x2a\x2e\x0f\x84\x17\x38"
         "\xa7\x6c\xc4\x71\x10\x8b\xfe\xf0\x89\x8b\xb4\xbe\xf8\xad\x55\x1c"
         "\xee\x00\xc6\x12\x29\x7c\xd6\xa1\x76\x56\x21\xfa\xde\x3b\xfc\x67"
         "\xd6\xd8\xb5\x43\x86\xd6\x2b\xa0\x97\xe0\xa4\x53\x21\x38\xa1\x90"
         "\x41\x58\x53\x14\xf3\x29\x1f\x44\x4b\x96\x41\xf9\xeb\x23\x65\xe3"
         "\xa1\xd6\xa5\xf8\x95\xc4\xf1\x90\xd0\x46\xb3\xaf\x24\xe6\xbd\x55"
         "\x9f\x22\xb8\x94\xea\xb4\xc6\xda\xe8\x6d\xe3\x2b\xe2\x25\x64\x32"
         "\x17\x75\x74\x39\x32\x72\xab\x80\xaf\xf8\x93\x8c\x85\xa1\xaf\xe4"
         "\x78\x5d\x3c\xfa\xfc\xca\x86\x27\xfa\x3a\x5d\x90\xbe\x76\xff\xa5"
         "\x39\xeb\x81\x21\xc4\xba\x13\x4c\xe1\xf1\x78\xe6\xae\x9b\x4c\x7a"
         "\xd8\x58\xb7\x20\xcc\xf2\x7f\x92\x7b\x28\x16\x3c\x6f\xdc\x25\x3c"
         "\x92\x1d\xc1\xe1\xd6\x8a\xfe\x82\xc1\x1b\x8d\xcc\xb1\x26\x4b\x87"
         "\xbf\x60\xfe\x6c\x1c\x0f\xe7\x64\xc5\xa3\x0f\xb4\x9e\xba\x2c\x6e"
         "\x62\xb0\x2a\xb4\xfe\x9b\xe0\xbe\x07\x2e\x57\x7b\x2b\x0b\x90\xd7"
         "\xad\x7f\x1b\x03\xf6\xfe\x26\xb8\x29\x81\x37\xb8\x41\xc9\xb9\xaa"
         "\x17\x37\xfa\x13\xef\x54\xee\x5e\xb1\x72\xde\x4b\xb4\xba\x81\x21"
         "\x8e\x18\x25\xba\xe5\x16\x84\x79\x0d\x17\x62\xe6\xf8\x16\x08\x65"
         "\xf4\xaf\x60\xe1\xfa\xfd\xa7\x2e\x9f\x78\x5b\x8c\x17\xd8\x91\xea"
         "\x19\x4f\x2e\xf3\x23\x87\x3b\x89\x9c\xf9\xe2\xaf\x44\xe1\xa5\x01"
         "\x0a\xc7\x02\x3b\xa6\x3c\x04\x46\x73\x9e\x57\x9b\x42\xf7\x5b\x03"
         "\x62\x42\x3c\x1a\x1b\xec\x49\xe7\xd7\x7b\x91\x4f\x9d\x79\x47\x76"
         "\x93\xf8\x23\xcd\xa2\x73\x92\x6e\x8f\xbf\x20\x20\x20\x20\x20\x20"
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
.*===preservatizeskyphoi
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x72\x65\x73\x65\x72\x76\x61\x74\x69\x7a"
         "\x65\x73\x6b\x79\x70\x68\x6f\x69";
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
.*===xerophagyhematography
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x78\x65\x72\x6f\x70\x68\x61\x67\x79\x68\x65"
         "\x6d\x61\x74\x6f\x67\x72\x61\x70\x68\x79";
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
