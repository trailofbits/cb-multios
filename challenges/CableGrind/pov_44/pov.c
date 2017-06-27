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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4a\x7d\xfa\xe0"
         "\x8d\x97\x58\x0d\x1f\xe2\x90\x33\x0c\x69\xd9\x96\x4b\xc8\x5b\x39"
         "\xfb\x00\x00\x00\x55\xb3\x82\x84\x64\x34\x4b\xca\x41\x36\x73\xca"
         "\x44\x27\xb5\xcc\xa2\x0f\x97\x9f\xc8\x5c\x23\xac\x8b\xba\x09\x73"
         "\x7d\x1b\x93\x81\xe8\x4c\x17\xc0\x44\x27\x3a\x50\x3a\xf4\x98\xa1"
         "\x2c\x33\x4c\x62\x2d\xdc\xf4\x32\xa7\xb6\xa6\x6c\xbf\x50\xbf\x44"
         "\x51\xc7\xce\xfb\x79\xa7\x5e\xb4\x3c\x00\x4c\xb1\xf1\x91\x12\x60"
         "\xf7\x9a\x7e\x35\xbf\x12\xbe\x6d\xeb\x43\x71\x02\x76\x68\x85\xd9"
         "\x57\x11\x6a\x10\xb1\x10\xe8\x26\xad\x68\x2d\xff\x56\x7c\x2b\x19"
         "\x93\x68\xf4\x50\x80\xf8\x93\x68\x17\x00\x17\x3f\xc9\xea\x75\xff"
         "\xac\xf9\xc5\x2a\x83\x88\xc7\xd3\x9a\xc1\xa1\x7c\xb6\x7c\x5b\x4f"
         "\xeb\x1a\xa4\x77\xbf\x22\x14\xc7\xb7\x68\xe0\xfa\x76\x66\x23\xff"
         "\xc1\x6f\xbd\xbe\xea\x55\xdc\xb2\xb0\x17\xce\x48\x80\xd6\xbd\x03"
         "\xe9\xd5\x9f\x96\x5f\x57\xf6\x34\x0c\xd4\x8f\x1c\x76\xa5\x9b\xad"
         "\x28\xcc\xfe\xfd\xb9\x1c\x9d\xed\x79\x35\x57\x5e\xdd\x48\x80\xdf"
         "\x6e\xd2\xbe\x6d\x14\x33\x2c\xf2\xc0\x5c\x74\x46\xed\xdc\xd9\x03"
         "\x88\xc7\x20\x03\x5c\x72\x64\x60\x0c\xb3\xe8\xb3\x2f\x78\x1c\x83"
         "\xe0\x38\x35\xd0\xf2\xbf\x6a\xaa\xe2\x9e\x6d\x0a\xb0\x43\x17\xef"
         "\x66\x51\x77\x78\x20\x8d\xec\xd8\x14\x32\x5d\x05\x99\xf4\xf5\x5f"
         "\xde\x19\x92\x70\x17\x0d\xb7\x0a\x4e\x66\x08\xee\xc4\x48\x83\x25"
         "\x3a\x7c\x12\xf5\xae\x9b\x2a\xe8\xd6\x83\x7b\xfe\xef\xe5\x3a\x81"
         "\x6b\x60\x52\xed\x00\xf1\xbc\x1f\xf4\xe6\xca\xc3\x8e\x20\x82\xd3"
         "\x92\x80\x11\xd3\x0f\x91\x6f\x0a\xe9\x4e\x52\x57\xce\x8e\xe8\x23"
         "\xfa\x22\x0e\xf1\x11\xd5\xf0\x86\x48\x0a\x4c\xbb\x23\x25\x2b\x03"
         "\x2c\xb9\x72\x46\x0d\x1f\x22\xbe\x35\xd1\x64\xec\x4c\x6f\x18\xfc"
         "\x9f\x62\xbc\xad\x8e\xc9\x6b\xcd\x3e\x23\xd1\xf4\xce\x37\xc1\xcc"
         "\x3a\x1d\xa7\xbb\x3f\x45\x2e\x79\x07\xce\xd6\x51\x22\x3e\xe2\x96"
         "\x1f\x18\x84\x62\x12\x47\xaa\x9b\xd3\x8d\x4d\x80\x0e\xcd\xec\xb5"
         "\x6c\x94\x6e\x2e\x70\x00\x26\x25\x75\xda\xf6\x5d\x62\xcb\x9a\x3d"
         "\x3b\x4a\x77\x0b\x6b\x9f\x05\x1d\xe7\xa3\x6d\x6d\x85\x35\x18\xb8"
         "\x15\x28\x6b\xcc\xfe\x24\x63\xc6\x57\x51\x30\x62\xa8\x00\x6f\xea"
         "\xd5\x23\xcb\x4b\x7e\x1a\x47\x17\x17\x00\xc2\x15\xb8\xfc\x30\x80"
         "\xf5\xb5\xf5\xc8\xf6\x2e\x17\x17\x00\xbb\xc8\xf7\xea\x40\x71\x2f"
         "\x53\x2d\x4c\xcd\x76\x02\xa2\xc8\xec\xa1\xc4\x66\x19\xdb\xe5\x0a"
         "\xd3\xe2\x36\x62\x60\x7d\x73\x92\x21\x8d\x35\x48\x5f\x6e\xcd\xc8"
         "\x7c\xf5\xb8\x5b\x22\x6d\xc7\x0d\xe4\x2c\xa6\x5e\x95\xd3\xb5\x48"
         "\x2f\x6a\x66\xdd\x29\x67\x26\x4a\xce\x3f\xe4\x8b\x49\x47\x01\xdf"
         "\x07\x30\x25\x9d\xaa\xad\xa0\x58\x3b\x16\xe2\xda\x04\x5c\x38\x45"
         "\x44\x26\x27\x93\x16\xb0\xe4\x86\x97\x26\x54\x1b\x34\x5d\xe1\x2d"
         "\x5a\xce\xaf\x59\xd3\x43\x0e\x87\xa0\x14\x89\x80\x5c\x79\xf7\x02"
         "\xdf\xec\xa2\x0f\xc3\xe7\x01\x64\x3a\x54\x6b\xc6\x53\x07\x94\x8f"
         "\x44\x36\x8a\x97\x49\x93\x76\xb2\x70\xf1\x1a\x34\x7b\x9e\xa0\x5b"
         "\x61\xe8\x47\x76\xa3\x30\x3e\xf7\x5e\x04\xd2\x00\xf1\xf3\x3d\xfe"
         "\x38\xc3\x1b\x84\xf9\xbf\x80\x0b\xa3\x7d\x19\x9c\x9c\x06\x29\xb7"
         "\x71\x28\xf0\xbc\x0c\x90\x5c\xe6\xd6\x7b\xa8\xa3\x0d\x74\x79\xe6"
         "\xb5\x71\x0b\x38\xe0\xbd\x05\x1a\xaf\x0c\xcb\x34\x07\xf2\xe6\x29"
         "\x3b\x4c\xd8\xda\xcb\x60\xf1\xfd\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Zantedeschiacladocarpous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x5a\x61\x6e\x74\x65\x64\x65\x73\x63\x68\x69"
         "\x61\x63\x6c\x61\x64\x6f\x63\x61\x72\x70\x6f\x75\x73";
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
.*===loungyimpolite
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x75\x6e\x67\x79\x69\x6d\x70\x6f\x6c"
         "\x69\x74\x65";
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
