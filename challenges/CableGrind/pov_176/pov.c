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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xef\x43\x72\x33"
         "\x70\x45\x5c\xdc\x6d\x68\x0a\x2e\xd3\x01\x00\x00\xbb\x80\x6a\x15"
         "\x38\x4f\x59\xe4\xba\x87\x97\x7f\xc8\x6f\x90\x4e\x26\x43\x2a\x0b"
         "\x98\xcd\x7f\x39\xb0\xa1\x1d\x09\x55\x91\x15\xc0\xe3\x1d\x4c\xb7"
         "\xff\x0e\x8d\x83\x06\x6a\xee\x4a\x0f\xc7\xad\xa3\x6c\x93\xb2\x0a"
         "\x88\xf4\x85\x86\xe2\x53\x99\x0c\x62\x7e\x44\x42\xd9\x13\x4a\xde"
         "\x0c\xd3\x69\x29\xda\xeb\x87\x6e\x0c\x14\x35\x6a\x0f\x81\x0e\xb2"
         "\x87\x2b\xf1\xfa\x8e\x91\x19\xe5\xa9\x83\x59\xd6\x1a\xdd\xcb\x7b"
         "\x9a\x61\x86\x4f\x9d\xa0\x0f\x1e\x95\x38\xc6\x03\xb1\x69\xfd\xad"
         "\x57\xe3\x46\xbd\x71\xbb\x7e\x1e\x76\x55\xc2\xd0\x41\x67\xbf\xb1"
         "\x43\x76\xa3\x5e\xcc\xf0\x8c\x1f\x07\x34\x1f\x03\x4e\xff\x63\xaf"
         "\x1b\xf9\x2f\x56\x9f\x04\xfd\x18\x3e\x38\x0d\xa8\xe9\xda\x44\x79"
         "\xa6\x8f\x03\x33\xe5\x6b\xa0\x8a\xfa\x53\x0d\xaa\x70\xe8\xc5\x5e"
         "\xf9\x46\xc6\xec\x81\xb6\x17\xc0\x82\xab\x5d\x41\x2c\x1d\x2d\x45"
         "\xec\x40\x74\xde\x77\x8d\x3a\x4f\xeb\x1c\x86\x25\xaa\x89\x12\xa7"
         "\xcb\xcb\xda\x5b\x37\x25\xc2\xdf\x1b\xf3\x40\xd5\x6a\xf7\xf9\x51"
         "\x99\x78\xc4\xaa\x6e\x9a\xd7\x59\x9a\x65\x14\x9e\x56\x60\x41\x79"
         "\x71\xa4\xa5\x88\xd6\x54\xce\xc8\xc4\x11\x2e\x99\xc2\x54\xc0\xf2"
         "\xc0\x80\x6c\xb3\x7d\xf3\x9c\x2f\x1c\xf5\x63\x62\x40\x66\x16\x74"
         "\x67\x1a\xac\xc5\x05\xf6\x4b\x72\xb1\x6a\x65\x66\x82\xb8\x82\x92"
         "\xff\xbc\xac\x2b\xc8\x55\xc3\x4a\x63\x69\x22\xd1\x6a\xc6\x71\x5e"
         "\xfe\x8b\x6f\x30\x9f\xfd\x3c\xf3\x8e\xa6\x7b\xc9\x46\x2a\x14\x68"
         "\xcb\x06\x01\x08\x25\xae\x05\x33\x48\x08\x65\x95\xe6\x7d\x00\x9d"
         "\x95\x91\xa0\xf1\xc7\x01\x54\xe8\xc9\x40\x38\xc6\xfe\x9b\x26\x87"
         "\x19\x33\xa5\x10\x39\x3b\x6c\x70\x8d\x87\x62\x77\xe8\x4b\x89\x2d"
         "\x29\x26\x09\x0a\x5e\x28\xd0\xe2\xc2\x67\x9a\x9a\xf5\xbd\xb7\x0d"
         "\x87\x69\xd6\xc0\xeb\xf5\xbd\x14\xfc\x4f\x66\x42\x44\xb4\x65\x26"
         "\x2a\x33\xc6\xef\x6b\xbb\x79\x5b\x10\x06\x3e\x98\xdf\x4e\xa4\x72"
         "\x5e\x61\x48\x7e\xac\x11\x18\xb8\x34\xb3\x34\xb4\xe5\x51\x9c\x78"
         "\xf6\x58\xbd\x4f\x4f\x00\x2b\x22\x96\x0d\x7c\x10\x9f\x71\x71\x75"
         "\x17\x56\xf0\x98\x4f\x22\x37\x8f\xd0\x48\x0f\x5c\xd1\x7b\xae\x30"
         "\xa2\x76\x2a\x76\x5f\x15\xb4\x94\xeb\x8a\xbe\x2f\x01\xf0\x87\xb5"
         "\x82\x48\x85\x6a\x4d\x72\x82\x58\x3c\x2d\x4e\xff\x40\xba\xdb\x21"
         "\x76\x04\xf6\x0b\x75\x6a\x1d\x8c\xa7\x29\x2f\x37\x1e\xce\x64\x69"
         "\x53\x72\xfe\xd1\x60\xab\x94\x62\xbc\xc3\x9e\x3b\x82\x7b\xf9\x93"
         "\xfe\xb2\xa0\xa5\xf2\x7a\x20\x78\x4f\xb8\x45\x86\x65\x12\xaf\xe9"
         "\xc9\x90\xfd\xb0\x49\x43\xb5\xd8\xcf\x6d\xf5\x05\x62\x29\x3c\x98"
         "\x66\xf9\xd8\x94\x8a\x56\xe7\xce\x23\x20\x20\x20\x20\x20\x20\x20"
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
.*===galleywormphos
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x67\x61\x6c\x6c\x65\x79\x77\x6f\x72\x6d\x70"
         "\x68\x6f\x73";
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
.*===changeablyzoophilitic
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x68\x61\x6e\x67\x65\x61\x62\x6c\x79\x7a"
         "\x6f\x6f\x70\x68\x69\x6c\x69\x74\x69\x63";
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
