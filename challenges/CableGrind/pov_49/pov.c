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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x6f\x19\x5e\x7f"
         "\xb9\xda\x52\x48\x89\x9d\x4c\x4e\x62\x74\x8f\xd7\xa5\x7e\x42\xb5"
         "\x09\x01\x00\x00\x1c\x8f\xae\x4b\x64\xb2\xf7\x68\x0a\x3a\x8f\x24"
         "\x94\x6e\xb3\x3a\xeb\xe6\x30\x9f\x40\x2c\xce\x66\x1b\x0b\xaf\xbd"
         "\xcb\x33\xeb\x56\x2d\xb1\x9e\x62\x89\xf7\x19\x30\x4a\x15\xe9\x20"
         "\x31\x46\xe6\x75\x6f\x40\x40\x40\xdb\xd8\x11\xc7\x8b\x68\xb8\xa4"
         "\xba\xcb\xfb\x4e\xd2\xa3\xaa\x1e\x31\x1c\x82\xe5\x40\x02\xee\x14"
         "\x8c\x9a\xf6\xd0\xe1\xed\xa7\xaa\x9b\x6e\xd3\x45\xb4\xbb\x86\x32"
         "\x70\xfd\xdc\x3c\x1b\xc8\x06\x8c\x47\x5e\xad\xda\x38\x77\x56\x32"
         "\xdb\xfc\x2e\xab\xb7\x1c\x9b\x7c\x0f\x44\xbf\x4d\xb1\xc9\xaf\x6b"
         "\xcd\x8b\xa5\x1a\x47\xc0\x5a\xfb\x2d\x6b\x92\x40\x4f\xee\xf4\xc2"
         "\x0c\xe0\xfe\xe6\x7c\x06\xd3\x99\xe9\x79\xa4\xfe\x21\x17\xe9\x6f"
         "\x48\x4f\xc8\x14\x54\x8c\xf0\x48\x69\x17\x98\x7f\x41\x23\x1f\x46"
         "\xf8\x7b\xe0\x82\x17\xca\x16\x3d\xe2\x8c\x05\x55\xe4\x0e\x25\xd7"
         "\x67\xa6\xd0\xfc\x0c\x66\x02\xaf\xa5\x1e\x5f\xb9\x73\x0a\x21\xc2"
         "\xc7\xb0\x66\x22\x87\x99\xd5\x6c\x09\xd2\x12\x99\x6f\xb8\xdc\x86"
         "\xf0\x6b\x4a\xa9\x62\xe7\xb8\x8d\x4b\x66\xd6\x5c\x7a\x88\x6a\xab"
         "\xe9\x2c\x04\x64\xdd\x93\x8c\xb6\xee\xf0\x2d\x82\xbe\x2c\x80\x90"
         "\xa6\x3e\x2f\xc1\x97\x21\x87\x17\x73\xb7\xa8\xec\x92\x16\x64\x7b"
         "\xad\x50\xf7\x62\x08\xd0\x82\xe3\xe9\x31\xc9\xe3\x28\x7e\x2a\x10"
         "\xac\x0f\xf6\x26\x01\x26\xab\xe2\xe7\xfb\xa9\xcc\xef\x31\xbd\x24"
         "\xcf\x69\xc2\xb2\x27\x10\x9d\xfd\x53\x48\x14\xae\xe6\x3a\xc4\xd4"
         "\x1b\x69\x7f\xf6\x09\xcb\x7e\x24\xdc\xcc\xb3\xa5\x7a\x8c\xb0\x45"
         "\x36\x7c\x81\xdb\x0e\xb8\x99\xd0\x28\xa1\x0f\x86\x3f\x11\x3e\x9d"
         "\x17\x1e\xd0\xca\x84\x9b\xf1\x36\xf4\xea\x2c\x34\x49\x2c\x81\x7a"
         "\xd8\x4e\xbd\x33\xef\x9b\xb7\x59\x3a\xc1\x2e\x99\x2a\x93\x84\xb2"
         "\x2c\xcd\xbb\x42\xb2\x97\x3f\x0b\x50\x26\x92\xa7\x5d\x08\x38\xf8"
         "\x95\x3a\xc9\x7b\x56\x14\x71\x73\x5b\x69\xb4\x24\x97\xfc\x41\x4d"
         "\xd0\x97\x32\x62\x36\x65\x82\xf3\x20\xc4\xfb\x4b\xfc\xfd\xc5\x78"
         "\xc6\x94\x69\x1b\xfc\xca\xfc\x30\xf2\x9a\xc7\x52\xa8\xd4\x6b\xf4"
         "\x91\x49\x1f\x13\xaf\xcb\x0b\x6b\x12\x6a\x2c\x6c\x07\xeb\x45\x69"
         "\xda\x12\x4f\x4f\x38\x7a\x02\x0b\x11\x48\x12\x1a\x0d\x29\x34\xc5"
         "\x88\x56\x7a\x94\x99\x96\x43\xd8\x95\x09\xde\x11\x34\x56\xfb\xaa"
         "\xa2\xce\x30\x33\x7f\x38\x95\x7d\x10\xbb\x60\xbf\x00\x73\x42\x2d"
         "\x04\xc8\x9d\xbe\x3d\x5a\x16\xfe\xb7\x70\x92\xe3\x31\xec\xd5\x49"
         "\xe4\x7d\x95\xf6\xa5\xc2\xa2\xb6\x67\x72\x61\xeb\x93\xdf\xd9\xc1"
         "\xad\xdb\x2f\x60\xd4\x12\x7d\xe3\x75\xa8\xdf\xf7\x3d\x1b\x12\x75"
         "\x2e\x07\x25\x0f\x20\x55\x2d\xea\xb2\x8e\x4a\x24\xb8\x55\xf2\x27"
         "\x5f\xc2\x63\x0a\x7b\x45\xc1\x8e\x60\xc3\xb0\x80\x6e\x88\x95\xa1"
         "\x3e\xe2\x71\x63\xb8\xef\xbd\xe0\x37\x3c\x9a\x09\x22\x60\x21\xef"
         "\xa2\x38\x89\xaa\x52\x2a\xfc\x29\x4b\xec\xe9\xbc\x75\xe4\x2a\x20"
         "\x1e\x2c\x0b\xb1\x5a\xd4\x85\x5c\xc1\x01\xf5\x18\x54\xf9\x97\x15"
         "\xc7\x01\x72\x45\x85\x8e\x75\x29\x31\xea\x83\xd9\xfb\x27\x64\x29"
         "\x41\xbe\x2c\xb3\x77\x52\x96\xf8\xb9\x42\x3e\x50\xc1\x0c\xc3\xc4"
         "\x1b\x38\x12\xea\xbe\x2d\x63\xc2\xb7\x2a\xe7\x4d\x67\xc6\x4a\x90"
         "\x92\xd0\x54\xdf\x3c\xc8\x07\x7d\xd7\xc0\x6d\x19\xff\x47\x8f\xd2"
         "\x4c\xb9\x43\x54\x4c\x9f\xd8\x15\xb0\x39\x21\x34\xe8\x8b\x4e\x8b"
         "\x3c\xd3\xaf\x97\x90\x2c\x82\xa3\xdc\xe2\x3c\x6b\x37\xc8\x8f\x59"
         "\xbf\x5e\x05\x00\xd5\x78\x28\xd3\x8e\x7e\x54\x84\x6a\x96\xf8\xc3"
         "\x8b\x8e\x5d\x7b\xe0\x16\x6f\xbe\x56\xea\xae\x37\xf5\xdf\xbd\xed"
         "\x77\xd3\x30\xa8\x7b\x95\x39\x57\xdf\xfb\x00\x12\xdd\xe2\x3d\x7b"
         "\x0a\xcf\x9b\xc7\xc8\xe7\x96\x5f\xdb\xf0\xe1\xc0\x76\xde\x07\x4e"
         "\x63\x57\xcc\x97\x6a\xa8\x76\x59\xb4\x01\x74\x6a\xdb\xf0\xec\x9a"
         "\x0b\xac\x34\xf8\xac\x27\xb3\x00\xdd\xb3\x94\x20\x20\x20\x20\x20"
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
.*===araguatolucinoid
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x72\x61\x67\x75\x61\x74\x6f\x6c\x75\x63"
         "\x69\x6e\x6f\x69\x64";
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
.*===clinandriabryologist
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x6c\x69\x6e\x61\x6e\x64\x72\x69\x61\x62"
         "\x72\x79\x6f\x6c\x6f\x67\x69\x73\x74";
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
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 4);
      if (read_00005_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00005_00000_match;
      pcre *read_00005_00000_pcre = cgc_init_regex(read_00005_00000_regex);
      if (read_00005_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00005_00000_pcre, 0, read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, &read_00005_00000_match);
         if (rc > 0) {
            read_00005_ptr += read_00005_00000_match.match_end - read_00005_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00005_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
