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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x86\x39\x63\x0b"
         "\x4e\xce\x88\x69\x95\x6b\xc7\xf1\x9c\x5b\xa6\x0e\xa8\x0b\x11\x8d"
         "\xd5\x00\x00\x00\x99\x1b\x00\x1b\x94\x0c\x15\xf9\xa3\x87\x7b\xf4"
         "\xfa\x58\x98\x09\xe2\x43\x88\x46\x67\x92\x23\xc7\xea\xc8\x08\xb4"
         "\x7b\x38\xc1\xdb\xd0\x11\xb9\x05\x0c\x05\x3a\x67\x4d\x08\x3c\xeb"
         "\x72\x25\xf7\x97\x6b\x8f\xf9\x03\x06\x62\xc5\x4e\x97\x07\x56\xba"
         "\x3f\xdf\xc0\xb0\x84\x0a\xaa\xcf\xe7\x69\x87\x71\x35\xd0\xfc\xe1"
         "\xdc\x57\x57\x65\x63\x55\xe1\x50\x08\x55\x46\x48\xe3\x23\xda\xb5"
         "\x84\x9c\x99\x9e\xce\x61\x76\x17\xcb\xa2\xba\x6d\x47\x41\xe7\x2a"
         "\x74\x1d\xec\xe2\xe7\x79\xc6\x8d\xa2\x4e\x42\xc1\xb2\x42\xa4\x32"
         "\xde\xf1\x5e\xa1\xf7\x68\xe5\x79\x96\x61\x01\xc2\x6c\xf9\x2d\x80"
         "\xd1\xba\xc3\x22\x2b\x57\x83\x87\xdb\x62\x61\x00\xfa\xca\xd6\x31"
         "\x21\x5d\x1f\xfc\x08\x32\x8f\x03\x2b\x62\x38\x72\x1b\xea\xfd\xaf"
         "\x2c\xc0\xc2\x44\x60\xff\xb0\x52\x95\x8f\xde\x68\x27\x80\xd0\xc0"
         "\x30\xa7\x61\xf1\xc6\x53\x45\xb6\xbe\x1a\x0e\x18\x4a\x48\x99\x16"
         "\x56\x6d\xef\x8c\x82\xbc\xe1\xa2\xd7\xc6\xda\xa5\x8c\x70\xac\x29"
         "\xd5\xbc\x72\x8a\x18\xc6\x34\xed\xd1\xa0\xcf\x9a\xa3\x67\x93\x45"
         "\xdb\x66\xb9\xbb\xb8\x48\x8f\x52\x6d\x47\x8c\x73\x20\x8c\xd9\x0b"
         "\xa0\x70\x39\xf6\x71\x00\x87\xf7\x38\xf7\xf1\x6b\x31\xe4\xc6\x8b"
         "\x9b\x7a\x9f\x13\x8a\x88\xeb\x31\xfb\xd0\x20\x29\xa2\x54\xa2\xbb"
         "\x5b\xe7\x05\x5a\xda\x33\x2a\xbf\xd8\xab\x7f\xc4\x61\xbf\x04\xa3"
         "\x18\xfd\x7a\x0a\x8a\x4d\xf7\x20\x07\xe6\x1b\xa1\xea\x92\x86\x02"
         "\xe1\xac\x96\xff\xc3\x4d\x30\x6f\x3e\x21\x16\x85\xd3\xad\x78\x7d"
         "\x17\xa6\xfc\x32\x9c\xf4\xaa\x8f\xbe\xa1\x71\x38\x83\x35\xcf\xbf"
         "\x17\xc7\xed\x8f\x16\xcc\xfe\xb7\x3a\x8f\x4f\x33\x4c\x71\x73\xa2"
         "\xa3\x7a\xb9\xdd\xc2\x6e\xb6\xfd\x53\xee\x54\xcc\x9c\x2e\x42\x9c"
         "\xf2\xd8\xd6\x57\xab\x4c\x93\xd5\xe5\x64\xb6\xba\x79\x8d\xca\x88"
         "\xbb\xf3\x85\x97\x71\x9f\x65\xf8\x6b\x93\x54\xde\x92\x0f\x0b\x39"
         "\xac\xc3\x76\x9a\xe2\x33\xa6\x6a\xc2\x89\x4c\x42\xd8\x72\x05\xee"
         "\x4a\x14\x3f\x38\x6b\x43\x84\x7b\xe8\x0f\x3c\x2e\x44\x26\x52\x9a"
         "\xc5\x7f\xbd\x23\x75\x46\x39\x08\xc2\xaf\x76\x51\xc4\xf8\x4e\x3f"
         "\xe7\x70\x6c\x63\x2d\x9a\x1b\x1b\x85\x34\x43\xc9\xc8\x5d\x1b\xd7"
         "\xdb\xf8\x11\x2b\x78\x65\x5e\x47\xf7\x77\x70\x31\x25\x69\xa4\x8a"
         "\xfb\xd6\x40\xd1\x27\xa8\x00\xeb\xf9\x3f\x20\x0d\xaa\xb2\xf4\x23"
         "\x5b\x74\x98\x16\x18\x1b\x3c\xe1\xac\x05\x87\x89\x77\xe4\x4e\xe2"
         "\xef\xd7\x3d\x4e\x23\x59\xd8\xe6\x29\x5a\x60\x2d\xb8\x9d\x2c\xf3"
         "\x35\xa7\xb9\xe7\xba\xb0\xb5\xbe\x0a\x25\xa3\xe9\x24\xf5\x14\x18"
         "\xc7\x1b\x19\xc3\x25\xae\xe2\x3d\x7b\x8b\x96\x93\xce\x8c\xe7\x12"
         "\xcc\xb1\x62\x5c\xe4\xd8\x13\xd5\x62\xfa\xa2\xb4\x99\x40\x23\x9c"
         "\x72\xc6\x14\x71\x73\xca\x1c\x4b\x4d\xbf\x8b\x70\xf7\xec\xb9\xb0"
         "\xa2\x73\x66\xd0\xb2\x39\x2f\x1a\xfe\x7e\x2d\xfb\x0e\x8b\x79\xd7"
         "\x55\x27\xbc\x5c\x28\xa9\x44\xf2\x24\x8d\x8c\x3d\x45\x5c\x09\x7c"
         "\xef\xdb\x15\x12\x09\xc2\x62\x71\x1d\x27\x66\xf2\xde\xd4\xa1\xca"
         "\xe0\xff\x09\x3c\x12\x66\x06\x25\xfc\x03\xb8\xc5\x1f\x12\xf9\xa7"
         "\x18\xfe\x93\x36\xc1\x5c\x0c\x16\x85\x06\x2d\x20\x0a\x9b\xc5\x81"
         "\xc6\x81\x4c\xd2\x60\x74\xa4\x43\x96\xf5\x05\x5c\x89\x6f\x39\xe0"
         "\x30\x99\xf1\x98\x3a\x13\x0a\xce\xf7\x4f\x59\xb6\x03\x2a\xca\x7e"
         "\xe2\x63\x5d\x2b\x43\x9f\x40\xb5\xdd\xe6\x26\x67\x0a\x1c\x9f\x88"
         "\x45\xcb\x03\x5f\xe1\x03\xbd\xf1\xe9\x38\x61\x53\x10\xa1\x4f\xc8"
         "\x54\xd7\x41\x5c\x88\x5a\x99\x8b\x9d\x60\x8f\x07\xa3\x0d\x00\x9b"
         "\x11\xba\x2f\xe9\x01\xa7\xbd\xd0\x5d\xc8\xdb\xc2\x42\x85\x86\xbb"
         "\x13\xd3\xe2\xe7\x99\x53\x75\x3a\xea\xf6\xd6\xad\xc2\x53\x43\x69"
         "\x84\x85\x58\xb4\xe4\x62\xce\x46\x2f\x40\xc9\x0f\xcd\x16\x69\x9b"
         "\x3a\x9d\x99\xd5\x5d\xa8\x84\x01\x43\xea\xc0\x40\x66\x52\x87\xe5"
         "\x76\x55\xa2\xd0\x55\x18\x10\x97\x8c\x2f\x0e\x00\x9e\x6a\x87\x2b"
         "\x3c\x3b\xb5\x29\xf4\x43\x69\x6f\xe2\xd0\x6b\x79\x40\xf4\xa2\xf5"
         "\xda\x94\x5c\x07\xb9\xb1\xc2\xce\xc3\x27\x53\x9b\x91\x44\x0e\xf2"
         "\xac\x75\xaf\xef\x14\x70\x66\x47\x90\x82\xed\x02\xba\x55\xce\xe9"
         "\x3a\x58\x1e\x5b\x05\x39\x15\x97\x8c\xe3\x66\x6e\xab\xd5\x10\x00"
         "\xb1\x57\x12\x8d\xfc\xb4\xcc\xab\x82\x2d\x5b\x34\x03\x30\x63\x20"
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
.*===outlawrypervertedness
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6f\x75\x74\x6c\x61\x77\x72\x79\x70\x65\x72"
         "\x76\x65\x72\x74\x65\x64\x6e\x65\x73\x73";
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
.*===ineloquentundishonored
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x65\x6c\x6f\x71\x75\x65\x6e\x74\x75"
         "\x6e\x64\x69\x73\x68\x6f\x6e\x6f\x72\x65\x64";
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
.*===goniometerhexameral
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x67\x6f\x6e\x69\x6f\x6d\x65\x74\x65\x72\x68"
         "\x65\x78\x61\x6d\x65\x72\x61\x6c";
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
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 4);
      if (read_00006_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00006_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00006_00000_match;
      pcre *read_00006_00000_pcre = cgc_init_regex(read_00006_00000_regex);
      if (read_00006_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00006_00000_pcre, 0, read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, &read_00006_00000_match);
         if (rc > 0) {
            read_00006_ptr += read_00006_00000_match.match_end - read_00006_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00006_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
}
