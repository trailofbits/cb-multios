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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xd8\xad\xea\xad"
         "\xcc\x5a\xef\x8a\xf4\x36\xe7\x82\x85\x70\xcd\x1e\xeb\x94\x1c\xdf"
         "\x48\x01\x00\x00\x5a\xb3\x99\x2a\x4c\x90\x49\x30\x32\xed\x1b\xa4"
         "\xa8\x70\x43\x34\x16\x42\x56\x00\x07\xc7\xd5\xdf\xf2\xad\xe5\x8c"
         "\xb9\xba\xd1\xc1\x14\x2f\x0f\xe2\x95\xc1\x7b\x0c\x0d\x74\xce\xee"
         "\x3f\x82\x20\x82\xa3\xfb\xb9\x52\x23\xc2\x37\xbc\x09\x8b\x7c\x38"
         "\x5c\x32\xa8\x1b\xda\x17\x80\x7d\x35\xb8\x52\xed\x18\xe8\x76\x94"
         "\xc8\xc2\xe2\x9d\xbd\x73\x81\x7c\xf1\x30\x89\x30\x81\x8e\x83\x00"
         "\xa9\x16\xe8\x4f\x0b\x44\x75\x23\x58\x0c\x97\xa6\xd7\x5d\x2e\x4d"
         "\x67\x3d\xdc\x98\xea\x23\x29\x5a\x00\x4a\xaf\xf8\x30\x5d\x0a\x16"
         "\xb4\xb4\x5e\xea\x53\x5a\x00\x02\x34\x2a\x40\x5e\x16\xef\x04\xd6"
         "\xef\x56\xc6\x5a\x58\x6a\x1c\x57\xb9\xfd\x0e\xfd\x6e\x47\xc3\xe9"
         "\x7f\x4a\xc1\xec\xa1\x49\x10\x6e\xb7\x4d\xf6\x37\x4d\x83\x8f\x29"
         "\x5d\xf4\x2f\x05\x87\xd2\x4d\x95\x30\x84\x4d\x2f\xe0\x7a\xda\xb2"
         "\x40\x91\xca\x5e\x26\xe8\xb0\x3a\x5a\x00\x03\x49\xe8\x89\x40\x9a"
         "\x99\xb7\x85\x5f\x32\xec\xcd\xd1\xbb\x9f\x5c\x43\x9b\xae\x9a\xe7"
         "\x1e\xd6\xc5\x57\xdf\xe5\x96\x92\x69\x91\xe7\x40\x13\xed\xd2\x20"
         "\x6d\x51\xb7\x37\x84\xa4\x2b\xea\x30\x18\x36\xea\xea\x72\x7f\x0d"
         "\x63\xc3\xb9\xab\xf3\x81\xc5\x7a\x6a\x99\xd6\x8b\x85\xfc\x82\xa0"
         "\x9b\xe8\x78\x73\x48\xe4\x17\x20\xba\x8f\x62\x74\xa1\x8a\x2f\xbb"
         "\xc3\x30\x47\xe9\xb8\x58\xd5\x3a\x86\x82\x49\x32\x1a\xb9\x28\xe4"
         "\xa7\xcc\xa3\xd9\x71\xa0\x73\x0d\x0c\x29\xd0\x34\x60\xfb\x8a\xe0"
         "\x9f\xc7\x00\x59\x68\x2f\x51\x2a\x49\xaf\x42\x8b\xd8\x27\x8e\xaa"
         "\x1b\x6b\x5d\x6f\x96\x31\xff\xcd\x88\x75\xb3\xfb\xbe\xe2\x7e\x96"
         "\xaf\x96\x94\xfa\x4d\x3e\xbc\x2e\x6f\x61\x07\xc9\x50\x92\x6a\x27"
         "\x41\x13\xf8\xf8\xaa\x75\xda\xc6\xb2\x08\xe1\x69\x4f\x48\x84\xc9"
         "\x78\x84\xe5\x49\x61\x16\xfa\x2e\xa3\x0a\xf3\xaf\x4c\xef\xcf\x73"
         "\x9a\xaa\xd4\x9b\xa4\x58\xd9\xd5\x1f\x41\x16\x9f\xcd\x5a\x76\x27"
         "\x0b\x10\x0f\xba\x82\xcd\x8e\x46\x61\xea\x93\xdd\x48\x4f\x1e\x8a"
         "\x37\xdf\x85\xd6\x91\x8d\xfa\x7e\x19\xb6\x66\x6d\x38\xe5\x4e\xad"
         "\x58\x28\x48\xf2\xc4\xfd\x75\x2c\x24\x0e\x2b\x02\xd0\x97\x9b\xe0"
         "\x5b\x3f\xc0\x50\xa3\x1d\xab\x40\x4d\x25\x87\x28\x06\x2f\x11\x49"
         "\x15\xb8\x06\x19\xe8\xb8\xab\xea\x00\xe5\x31\x67\x25\x0f\xe3\xd3"
         "\x03\x80\x2a\x37\x09\x06\xc0\x7f\x68\x0d\x63\xed\x83\xcb\xee\x7d"
         "\x39\x1d\xd8\xfd\xc1\x2c\x86\x2f\x8b\xb9\x28\x5a\x9c\x4a\xa9\x6a"
         "\xb5\xde\xca\x8b\xc2\xd9\xf0\x5d\xb3\xc4\xb8\xb8\x7f\x14\x0e\xc8"
         "\x6a\xf5\xd9\xa4\x3e\x21\x4b\x11\xd5\x7b\xf3\xc6\x28\x0f\x8a\x7e"
         "\x95\x09\x4f\x6b\x12\xd6\x13\xfe\x7f\x09\x22\x5a\x65\x63\xd3\xf0"
         "\x9e\xd7\x34\xed\xfe\x4a\x05\x16\x77\x79\xc6\x3d\xd2\x3b\x4b\xeb"
         "\x78\x5c\x83\x92\xf3\xb3\x26\x89\x84\x0c\xea\x8b\xa5\xb7\x01\x5d"
         "\x48\xa9\x78\x88\x1c\x08\xda\x20\xcf\x46\x50\xb2\xef\xac\xa5\x2d"
         "\x21\xa2\x20\xb1\x58\x0c\xc4\xd3\x54\x6a\x58\x45\x94\xb7\x07\x02"
         "\xc1\x0f\x03\x85\x29\x14\xd6\x12\x23\x6c\xf8\x00\x80\x01\x9f\xb4"
         "\x12\xf1\x60\x0d\x81\xb6\xed\xf2\x26\x2f\xf7\xde\xea\x17\x14\xfb"
         "\x3d\x45\x2a\xef\x12\x2f\x59\x04\xd9\xbf\x9c\xcb\x31\x4f\x9d\xbb"
         "\x2f\x14\xd7\x4c\xd2\xca\x8f\x30\x8d\xed\x2f\xf2\x8c\x3c\x32\xd2"
         "\x1b\xaa\x82\xca\x9e\x72\xf2\x6b\x36\x01\xb1\xd6\x04\x00\x8e\xf9"
         "\xe8\x10\x46\x25\x3a\xcf\x8a\x72\x9e\xd9\x22\xb8\x8c\x0e\x2c\x37"
         "\x88\x72\x59\x7b\xfc\xf0\xed\xcd\x9e\x69\xb5\x3c\xca\x22\x39\x04"
         "\xfc\x76\xb1\x04\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===wirrshillingless
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x77\x69\x72\x72\x73\x68\x69\x6c\x6c\x69\x6e"
         "\x67\x6c\x65\x73\x73";
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
.*===vibrativeoversail
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x76\x69\x62\x72\x61\x74\x69\x76\x65\x6f\x76"
         "\x65\x72\x73\x61\x69\x6c";
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
