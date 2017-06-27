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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x20\x01\x4a\x9a"
         "\xf3\x45\x5b\xd5\x65\xc4\x42\xee\xd7\xa1\x74\x60\xd6\xad\x8c\xb7"
         "\xbe\x00\x00\x00\xe9\xbe\xb9\xfc\xf9\x80\x6d\xac\x30\x00\x30\x00"
         "\xbe\x07\x30\xb3\x91\x51\x13\x40\x20\x94\x5c\x1b\x7a\x8d\x21\xf8"
         "\x1a\x60\x91\xee\xf4\x7c\x09\x57\xdd\x08\x5a\x44\x04\xf5\x8f\x51"
         "\xa8\xe4\x0e\xd1\xc9\xb2\x6e\x94\xe4\x60\x16\x96\xda\xcb\x01\x55"
         "\xc5\x8f\xd2\x8c\x6e\xd0\x61\x44\x57\x0f\x71\xae\xd1\xf8\xf4\x17"
         "\x02\xd0\x50\x2d\x97\x53\x6f\x2c\xbf\xa7\x2f\x99\x6f\xcc\xda\x9b"
         "\x83\x96\xbe\xd1\x4e\x8d\xb7\x70\x7f\x14\x85\x61\xd4\xb2\x19\xd6"
         "\x0b\x33\xeb\xda\xed\x61\x08\xb6\xe0\x14\xce\x95\x67\xe2\xa7\x7d"
         "\x15\xc3\x20\x80\x64\xc0\xa3\xf4\xf9\xe3\x30\xd2\xce\xa9\x8c\xea"
         "\x88\x91\xd3\x58\x61\xaf\x41\x33\x99\x5e\x14\xa1\x90\x7e\xdf\xef"
         "\x92\xea\x05\x78\x6b\x6a\x53\x85\x14\x5c\xf6\x32\x59\xd1\xf3\x50"
         "\xe1\x0e\x86\x2a\xf5\xd6\x5e\x9f\xb4\xc6\x0b\x01\x23\xf2\x99\xe9"
         "\x49\x46\x30\x4d\x14\x76\xdc\x0e\xd7\x8b\x52\x7e\x2d\x85\x4f\x89"
         "\x01\x09\x38\x6f\xe3\xb5\x99\x4f\xe1\x10\x35\xe2\xad\x12\xe4\x97"
         "\x85\xb7\x9b\x25\x5a\x50\x6b\x52\x9a\xed\x19\x2e\x7f\xd0\xdb\xd9"
         "\x04\x30\xaa\x09\x5a\x89\x65\x5d\x28\x3f\xa4\x01\xaf\x7d\xf6\x60"
         "\xd1\x12\x0a\x9d\x00\x86\xa3\x0b\xc6\x5f\x66\x08\x64\x13\x70\x0e"
         "\x9d\x32\x40\xfe\xd4\x62\xec\xc9\x60\x38\xbd\x04\x30\x9c\x8d\xc7"
         "\x57\xbd\xec\x4c\x3d\x87\xb0\x31\xe3\xd5\x99\xb5\x04\xfa\xce\xdb"
         "\x3e\xdd\x7b\x9c\x68\x57\x95\xb4\x80\x82\x64\x52\xa2\xca\x65\x01"
         "\x55\xe8\x56\xd5\x1e\x8e\x6d\x31\x0c\xab\x3d\xf4\x39\xb8\x61\x95"
         "\xd4\x00\xc3\x6a\xe1\xdd\x8f\x2a\x64\xe8\x8f\x20\x93\xa9\x32\x20"
         "\xb0\x79\x81\xb1\x8b\x37\xbc\xd9\xe9\x98\x93\xa8\xb6\x5e\x63\xaa"
         "\x8c\x5c\xba\x42\xf6\x19\x32\x02\x71\xc0\xec\x18\x1c\x9c\x3f\x2a"
         "\x46\x5d\x7a\x26\xe9\x9b\x08\x21\xbe\xba\xf1\x06\x08\xca\xf6\x20"
         "\xa2\x64\xfd\xcf\x49\xa7\xe2\xe7\x36\xe0\x63\x2d\xf1\x56\x72\xc5"
         "\x09\x98\x24\x15\xab\x98\x43\x29\xfd\x2f\xc0\x42\x84\x46\x1b\x76"
         "\xf6\x88\x25\xd1\x8e\x78\xe9\x20\xd2\x7d\xa3\x90\x52\x52\x4f\x86"
         "\xac\x6b\x4f\x65\xa3\xdb\x03\xef\xa5\x30\x88\x02\x8a\xe5\x2f\x69"
         "\xe7\x65\xc8\x10\x9f\xcc\x19\x11\x8a\xd8\xa8\xaf\x5a\x9e\xa7\x0d"
         "\xc8\x98\x6e\xed\xaa\x4b\x5e\x9b\xea\x94\x33\xf0\xa2\x0a\x05\xd2"
         "\xf4\x02\x00\x6e\xb5\x11\x79\x58\xd9\x7e\xdd\xae\xd6\xd6\x11\xb4"
         "\x0f\xaf\x11\x92\x60\x9d\xda\x45\x87\x83\xbb\x50\xc7\x09\x07\x17"
         "\xf3\x3f\xd1\x56\x02\x21\x0f\x63\x52\xca\xf2\x5b\x95\xa3\x49\x04"
         "\xab\x88\xf6\xd4\x78\x9a\x7d\x2e\x3e\x52\x4e\x8f\x57\xdf\xf6\x8b"
         "\x65\xb3\x6f\x6a\x09\x63\xf4\xd6\x55\xca\xb1\xf8\xb4\x08\x1a\x4e"
         "\x65\x90\x45\x5d\x59\x16\xef\x80\x30\x5f\xd2\x93\x04\xa7\x15\x07"
         "\xe6\xa5\xe0\xd6\x9f\x8d\xf4\x2d\x6a\x67\x1d\x37\xc8\x83\x4b\xa7"
         "\x0c\x9f\x63\x26\x2b\x66\x66\x9b\x2d\x25\x9e\x72\xf5\x01\xce\xed"
         "\xdb\xa5\x85\x5c\xb1\xd8\xcd\x20\xe2\x50\x43\xcb\xc6\x87\x4c\x11"
         "\x85\x7e\x7c\x54\x45\x83\xc0\x98\xe0\x8d\xab\x30\x30\x00\x80\xb1"
         "\x17\x00\x3f\x7e\xa6\x18\xc4\x90\x46\xa2\xc7\xfa\x5f\xa7\x58\x30"
         "\x00\xa9\xbc\x05\xa8\x7f\xf2\x09\x82\xb1\x2c\x93\xa1\x90\xca\x62"
         "\xce\xa7\x5a\x9d\xb2\x70\x30\xe4\x24\x42\xef\x40\x25\x34\x75\xb5"
         "\x28\xd3\x4b\xec\xdb\xa0\x04\x57\x09\xf0\x05\x86\x4c\xa2\xca\x1e"
         "\xa1\x60\xe1\x9e\xfe\x2a\xd4\x4c\x68\xf8\xde\xb4\x58\xd6\x8d\x78"
         "\xfa\x4d\xdd\xe0\x6d\x16\x88\x55\x1f\xc2\x45\x0c\x5b\xdd\xdd\x16"
         "\x59\x6f\x50\x72\x2e\x82\xff\xe5\xe2\x36\x2e\x24\x76\xcb\x0e\x60"
         "\x92\x85\x7f\x0e\xb5\x92\x46\xe9\xbd\xc8\x2c\xdf\x76\xb6\x07\xc1"
         "\xf7\x7c\xec\x3c\x1f\x4a\x71\x26\x5f\xb4\x58\x16\x69\xa8\x97\x75"
         "\x42\x71\x05\xe6\x4f\x9d\x81\xd3\x57\x43\x63\x3b\x7d\x05\x98\x46"
         "\x74\x75\x8f\x21\xfa\x9a\xc9\x52\x66\x08\x45\x04\x22\xae\x34\x06"
         "\xe3\xf9\xf1\xc2\x33\x94\x0d\x8a\x67\xe5\x06\x93\xaf\xba\xde\xcf"
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
.*===SpatangusChayma
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x53\x70\x61\x74\x61\x6e\x67\x75\x73\x43\x68"
         "\x61\x79\x6d\x61";
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
.*===pegologyscavenage
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x65\x67\x6f\x6c\x6f\x67\x79\x73\x63\x61"
         "\x76\x65\x6e\x61\x67\x65";
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
