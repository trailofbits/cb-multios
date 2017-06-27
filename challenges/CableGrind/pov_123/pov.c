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
         "\x01\x00\x00\x00\x01\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xf7\xfe\xf7\xea"
         "\xd5\x77\x29\x86\x94\x66\xfd\x73\xc0\x00\x00\x00\x88\x1d\xde\xf7"
         "\x95\x1b\x00\x1b\x69\xee\xda\x12\xee\xcf\xfb\xa3\x40\xe1\x5b\x0c"
         "\xc6\xa1\xf1\xd0\xf4\xf5\x03\xf7\xd2\x34\x87\x7d\x61\xc1\xd0\x0b"
         "\x36\xca\xb5\x9e\x0c\x71\xa7\xa2\x80\x97\x56\xac\x44\xd3\x81\x3d"
         "\x98\xe0\xd3\x1a\xfb\x87\xfb\x61\x45\x8c\xf2\xf1\x12\x5b\xbe\x23"
         "\x26\x31\x63\xdc\x7c\x7e\xcf\x47\x22\x11\xd4\x5e\x56\x8f\xbe\x9f"
         "\xeb\xea\x48\xe9\xd3\x93\x94\xcb\xf4\x19\x57\x8c\x74\x1c\x37\x4a"
         "\x70\x75\xc9\x82\x54\x50\x60\xd0\xaa\x8e\x99\x41\x3b\x04\xee\xf6"
         "\xcf\xa2\x7a\xe7\x8d\x11\xb0\xc7\x22\xcd\xc4\x1d\xed\xd5\xc2\xc7"
         "\x07\xcc\xe9\x55\x2d\x1a\x80\xa5\x71\xee\xf0\x51\x31\x0a\x1f\x09"
         "\x2f\x5b\x13\x26\x6d\x5d\xd4\x3a\x47\xe9\xcd\xfa\xe6\xfd\x6e\xa3"
         "\x8a\x38\xc6\x9d\x7b\x37\x79\xe8\x79\x49\xc7\x24\x0b\xd7\xf1\x15"
         "\x8e\x4f\xe6\xb2\xdb\x13\x1d\xbb\xa5\x75\x52\xbe\x51\xe9\x9e\x40"
         "\x17\xd4\x6d\x99\xbc\xc3\xbd\x6f\xef\x8c\xf4\xe6\x1f\x5f\x7b\x7e"
         "\x37\xb4\x51\xad\xf9\xef\x8a\xbd\x3e\x3d\x80\xaa\xd3\xc3\x3e\x16"
         "\x0c\x50\x04\x4b\xd8\x73\x03\xca\x93\x1d\xce\x87\xe1\x17\xd4\xbc"
         "\x05\xe9\xdb\x71\x1b\x98\xd4\xc8\x1a\x2b\x75\xf5\xc7\xda\xd4\x07"
         "\xa8\x92\x30\x78\xb8\xfe\x03\x2d\xa9\xbc\x02\x5d\xe1\xe5\xcf\xa6"
         "\x05\x31\xf8\xf5\xae\x5c\x36\x20\x2c\x1d\x22\xb3\xe8\x15\x4c\xab"
         "\x59\x0f\xfb\x3b\x67\xca\x7f\x4b\xad\x0f\x26\x79\xdd\x0d\x4d\x12"
         "\x70\x85\xa3\x88\xf5\xb0\x81\xae\x7a\x56\x2a\x06\x5d\x16\x73\x68"
         "\x6d\x1d\x13\xee\x3b\x31\x88\x1e\xc0\xea\x2b\x2b\x7b\xfa\x9d\x53"
         "\x86\x79\x2f\x62\x15\xe2\x79\x7e\x86\xed\x82\xa3\xb7\x22\x6e\xc4"
         "\x98\x2b\x28\x3d\xc9\xfd\x54\xe4\xb8\xf0\x02\xd0\x09\x01\xeb\x76"
         "\xe9\x18\x92\xa6\x82\x19\xaf\x75\xdd\xa9\xdd\x9e\x42\x55\x4f\xe5"
         "\x3c\x2a\x4c\x56\xfc\xb4\xab\x01\x46\x4f\x4a\x07\x24\xed\x25\xce"
         "\xbd\x7b\xec\x0b\x8c\xde\x44\x1f\x6e\x84\x82\x04\xbb\xce\xea\xb7"
         "\x8f\x9b\x24\x8b\x0d\xe8\x8b\x98\x32\x5d\x8f\x7a\xb2\xfe\x14\x63"
         "\x3c\x94\x50\xe2\x9f\x90\xca\x25\x20\x3d\x2d\x64\x34\x2b\x4b\x79"
         "\xa9\xcb\x8a\x31\x44\x72\x5b\xfb\x73\x77\xb5\x50\x6c\x2d\xa2\x58"
         "\x34\xd5\x8a\xc5\xf3\x99\x54\x3d\x3e\x6c\x90\x5e\xb1\x41\xf4\x95"
         "\x90\xad\x9d\x0f\xaa\x78\x03\x18\xab\x6c\x45\x91\x39\x30\x07\xcc"
         "\x65\x24\x87\x03\xf0\x6f\xa9\x76\x3f\x9d\xa5\xa4\xc3\x79\x2b\x49"
         "\x24\x4a\x10\xa7\x48\x65\x46\x70\xce\xe9\x4d\x77\x2e\xb5\xad\x59"
         "\x5d\x15\xdd\xc1\x26\x9f\x74\x58\x97\x03\x78\x46\xbd\xd5\xce\xdf"
         "\xb7\x1c\xb3\xaf\x12\x3f\x51\x59\xac\xfa\xb7\x14\x9c\x67\x6e\x5c"
         "\xea\xeb\x26\x1d\x39\x37\xca\xdc\x41\x6e\xa5\x98\x92\xd4\xed\x83"
         "\xae\x93\xe6\x5c\xc5\xa4\x1d\x16\x34\xc8\xeb\xaf\xa0\x83\x61\x22"
         "\xcd\xe7\xf0\xca\xc7\x02\x56\x1a\x21\x9d\xc0\x9f\x92\x14\x87\x51"
         "\x6d\xdd\x8d\x65\xfd\x2c\x5d\xe3\x78\x7f\xcd\xe2\x62\xd2\x70\x6d"
         "\xad\xb3\x1c\x38\x60\x09\x22\x2b\xa6\x6a\x8d\x73\x4b\xfc\xf2\x0a"
         "\x88\xe9\xd3\xf0\x7c\xc2\x9f\x10\xf6\x32\x48\x17\xd0\xc2\xc1\xba"
         "\x2e\x2b\x4b\x02\x72\xf7\x1a\x9f\x32\x63\xf7\x02\x4f\x5b\x23\x20"
         "\x8c\xa0\x25\xfc\x24\x9e\x65\x38\x4b\x51\xc4\x03\x08\xd6\xe7\x30"
         "\x73\xa8\xee\x85\xa7\x3f\x60\xe4\x2e\xec\x2f\x88\x44\xa3\x95\xec"
         "\x9f\x94\x42\xa7\xdd\x6b\xfd\x1d\xa3\x5b\x34\x8a\x23\xf1\xac\x33"
         "\x60\x86\x81\x94\x31\x61\xb6\x8a\x37\x46\xd2\xe2\x03\xc6\x73\xd9"
         "\x54\x5b\x0c\xd4\xd1\xc8\xb9\x1e\x1a\xe5\xac\x00\x82\x36\x97\xad"
         "\xd6\xcd\x10\x36\x6c\xf0\xe7\xc1\xfd\x76\x0d\x10\x11\xad\xbe\xde"
         "\x4a\x38\xd6\xb5\x34\x98\x7f\x16\x04\xb5\x7b\x6e\xa4\xb2\xc3\xc8"
         "\xf9\x88\x50\x49\x29\xa0\x84\xec\xd0\xbb\xbf\x07\x3a\xc3\x88\x90"
         "\xba\x9a\xa7\x50\xcd\x3f\x48\xec\x80\x7f\x48\x79\xca\xf3\x81\xb6"
         "\x7d\x11\xc3\xce\xd4\xf6\x44\x03\xe7\xc5\x4e\xc7\x65\xf9\xc0\x3f"
         "\x49\xfd\x1f\x49\x3a\xdc\xd2\x19\x29\x9c\x1f\x86\xe2\x29\x03\x1a"
         "\x01\x08\x74\xce\x96\xb6\x4d\xbe\x4b\x36\xf9\x76\xcb\xd1\x16\x8a"
         "\x10\x87\xbc\x86\xbe\x0b\x6a\x3d\x71\x2d\x0f\xf0\x16\x71\x0d\x0d"
         "\x98\x39\xec\x7f\x78\x88\x0c\x40\x13\x99\x51\x5b\xda\x6a\x3b\xbd"
         "\x50\x0c\xaa\xfb\x4f\x28\x7d\x54\x13\x69\xa3\x79\x50\x76\x0b\x31"
         "\x62\x3a\xd2\xcb\x78\x5b\xcb\x06\x03\x64\x16\x58\x71\xd4\xc6\x76"
         "\xb2\xb3\xd0\x85\xa6\xa4\x7b\xc6\x86\xb4\xa9\x0a\x45\x6e\x8f\xcf"
         "\xfc\xd0\x55\xeb\xb3\x46\x75\xfd\x70\xa6\x6f\x4f\x17\x61\x4e\x3a"
         "\x62\x9c\x96\xa2\x00\x00\x2d\x85\xd3\x5d\x20\x20\x20\x20\x20\x20"
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
.*===lol
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x6c";
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
