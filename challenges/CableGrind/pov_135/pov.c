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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x90\x3e\x82\x82"
         "\x97\x85\x58\x40\x61\x0d\x2e\xe7\xed\x00\x00\x00\x75\x6a\x74\x05"
         "\xc8\xa5\x13\xba\x08\x66\x44\x90\xe6\xfb\x05\x3a\x2a\x42\xb2\x6f"
         "\x5a\xaf\x3c\x7c\x40\xe2\x9a\x1e\xef\xa6\xc7\xe2\x19\x5f\x65\x44"
         "\x39\xe4\x88\x26\x33\x2e\xd9\x12\x07\xba\x27\xf6\x55\xef\xd0\x49"
         "\x69\x40\x40\x40\x96\x25\x93\xc6\xfc\x32\x38\x64\xc2\x5a\x7e\x9f"
         "\xec\x01\x32\x92\x5c\xca\x2c\x8b\x40\x14\x4e\xec\xca\xab\x3f\x35"
         "\x4a\x9d\x31\x88\x4d\xab\xf0\xcf\x73\xf2\xc2\x9d\x2a\xf8\x93\x41"
         "\xe7\xc4\x6e\x58\xc7\x25\x39\x46\x2f\x09\x9e\x6d\x27\xaa\x6d\x07"
         "\x12\x7a\x37\x0f\xd2\x39\x28\x87\x2a\xd5\x72\xd0\x6f\x42\x51\x82"
         "\x7c\x2c\x7f\xa3\xf9\xc4\x52\xb4\xd3\xc1\xc4\x6e\x3c\xed\xa9\x8e"
         "\x26\x76\xdd\x58\x72\x3d\x39\xbb\x71\x03\x1f\xef\x55\xd1\x0d\x5c"
         "\x35\x8d\x06\x57\xc8\x0e\x15\x27\xe9\xbe\xfb\xe3\xb3\xdf\x94\x10"
         "\xc3\xdb\xc2\x26\x1f\xd3\x45\x91\x46\x11\xae\x1b\x6e\x6a\xb6\xb4"
         "\x6d\xe8\x78\xb5\x34\x75\xe4\x13\xc7\x37\x64\x49\x7c\x67\xe3\x33"
         "\xeb\x98\x8e\x75\x2b\x91\x31\x59\x78\x0c\xd1\xe0\xef\xef\xff\x59"
         "\x38\x0c\xe2\xff\x20\x6d\x2f\x45\xed\xab\x42\xd1\xf2\xb8\xf7\xff"
         "\x7c\x06\x97\xa4\x75\x90\x50\x25\xf1\xba\x21\x3a\x7d\x34\xf5\x45"
         "\x4c\xe2\xc4\x32\xb3\x8f\xa0\x9d\xc2\xb9\x23\x9e\xd7\x73\x4e\x0e"
         "\xcf\x8a\x41\x14\x38\xf4\x14\xf8\xf2\x49\x45\x7e\x2a\x0b\x7c\x19"
         "\xc1\x10\x87\x6d\x3f\x5d\xab\x1f\x8a\x62\xde\xc3\x8e\x11\xe9\x9b"
         "\x5b\xbb\x0f\xca\x2f\xc2\x92\x11\xaa\x75\xd6\xdb\x07\x3c\x32\xa4"
         "\x1d\x97\xde\x33\x29\x29\xf5\xda\x3b\xc6\xb8\xd3\x69\x9b\x9f\x7f"
         "\xbe\xc8\xaa\xa2\x2c\xa2\xe3\xc3\x31\x34\xad\x1a\xe8\x6e\x33\x1b"
         "\x94\x54\x12\x23\x7a\x23\xf2\xf5\x90\x5f\x1a\x19\x10\xb6\x27\x52"
         "\x92\x48\xfd\x4c\xc9\xd6\xd8\xc6\x10\x76\x31\xa0\x8f\xb4\x52\x37"
         "\xfb\xa4\x54\xc5\x98\x70\x63\x7c\xf3\xde\xe0\x4e\x3f\x2e\x18\x99"
         "\x66\xee\xda\x4e\x10\x52\xf8\xa2\xe4\x31\x0e\xe0\xba\xb4\x87\xed"
         "\xe2\x28\xda\xe8\xdf\xdf\x06\x02\xe7\x9f\x1c\xd3\x2c\x86\x32\x6b"
         "\x32\x42\x23\x90\x1c\x18\x79\x4d\xb4\xd9\x41\xd4\x96\xf5\x49\x53"
         "\x20\xa3\x0c\x04\xa4\xb5\x89\x5f\x52\x5f\xab\x51\x94\x0c\xe8\xc9"
         "\xf5\x33\x1d\x37\xda\x3f\xec\x18\xd5\x10\xd6\x9f\xe9\x46\x39\xc9"
         "\x00\x3a\x59\x6c\x95\x4f\xca\x67\xee\x46\x0c\xcf\xc1\x8e\x26\xb1"
         "\x7e\xb5\xd5\x13\x08\x9f\xa1\xca\x83\xc0\x50\xb9\x1a\x25\x56\xb6"
         "\x8a\x86\xfc\x1c\xc3\x8c\x4a\xe4\x5c\x34\x0d\xcd\xaf\x1c\xd3\xbf"
         "\xe3\xbb\xe9\x0a\xf6\xc3\x9b\xaf\xd5\x89\x0d\xb1\xa2\x41\x5d\xdb"
         "\x34\xfe\xaf\x67\x0d\x65\x96\x5c\xf9\xa9\xc1\xdb\x06\x58\x95\x95"
         "\xd4\xb8\x5b\xc9\x3f\x32\xd4\x7e\x6e\x5e\xf7\x3c\xb6\x3a\xe0\x8a"
         "\x1a\x66\x27\x27\x6d\x8a\x2a\x28\x4f\x10\xa4\x1f\xdd\x7a\x6f\x18"
         "\xec\x49\x1d\x7c\xa2\xd5\xfe\x54\xb2\xa7\xe5\x9e\xae\xf4\xc3\x33"
         "\x4e\xf7\x86\x26\x74\x05\x6f\x2c\x46\x37\x5f\x6f\x90\x0b\x95\x44"
         "\x51\xdb\x7b\x75\x96\x5c\x3e\xe8\x87\x24\xa2\xae\x6b\x81\xc3\xb1"
         "\xee\x38\xa0\x88\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===araguatolucinoid
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x72\x61\x67\x75\x61\x74\x6f\x6c\x75\x63"
         "\x69\x6e\x6f\x69\x64";
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
.*===clinandriabryologist
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x6c\x69\x6e\x61\x6e\x64\x72\x69\x61\x62"
         "\x72\x79\x6f\x6c\x6f\x67\x69\x73\x74";
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
