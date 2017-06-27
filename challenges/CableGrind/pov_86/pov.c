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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x27\xcb\xf5\x70"
         "\x1a\x69\xdb\x76\x58\xf2\xe2\x53\xec\x0f\x3b\x81\x89\x3c\xea\xc0"
         "\xed\x01\x00\x00\x13\x00\xca\x2d\xcf\xd1\x4f\xfb\xc2\x70\xef\x6c"
         "\xbd\x53\xcf\xe1\xef\xbd\x72\xe3\x75\x59\x82\xbf\xe2\x72\xa6\x5f"
         "\x72\xa0\xdf\x0b\x19\xd3\x10\xd0\x10\x4c\x61\x3e\xf4\x6e\x1b\x95"
         "\x8c\x80\xe4\xd9\xf2\x72\x5e\x3e\x9e\xc9\xe2\xdf\x66\xed\x77\x1e"
         "\xc3\xdf\x58\xbb\xa3\xd7\x1c\x99\x37\xac\xf9\xcf\x75\xde\x9b\xd0"
         "\x2c\x55\xdd\xa5\x1f\x3c\x7c\x90\x25\x0c\x4f\x2c\x17\xb3\xee\x3b"
         "\xe4\x2e\x80\xe7\x8a\xdb\xe3\x3a\x5f\xb7\x78\x48\x9f\xcc\xb0\xf1"
         "\x77\x1a\xa0\xd8\x5a\xa8\x8b\x5c\xc4\xd4\xb1\xdc\xc1\x26\x77\x9b"
         "\x71\x79\xb7\xf9\x5b\x26\x2b\x6c\x51\xea\xd3\x53\x05\x7f\xb4\xa3"
         "\x54\x5f\x86\x2a\x8d\xa6\xcc\x7c\x01\x58\x41\xf2\xb3\x4c\xd9\xde"
         "\xb8\x41\x75\x53\x9d\x55\x21\x8a\x00\xcc\xf5\x17\x91\x5e\x01\xbf"
         "\x5e\x32\xa2\xb8\x31\x6c\x0e\xf9\x96\x0d\xb1\xd4\xcb\xed\xe9\x56"
         "\xb7\xb1\x06\x36\x29\x1b\x98\x6f\x10\x90\x13\x02\xd7\x7d\x43\x25"
         "\x09\xf2\xcf\x7e\xa8\x84\xf7\xa4\xb3\xfc\x2e\x66\x36\xd7\xec\x0b"
         "\x87\x99\x07\xaf\xe4\x37\xa6\x38\x87\xe7\xc6\x6e\xf5\xb0\x9d\x09"
         "\x34\xb0\xc8\xf4\x04\xb0\x5b\x8a\x11\xae\xdf\x68\x1a\x8c\xb6\xde"
         "\xc3\x25\x58\xf2\x2c\xa7\x43\x02\x6d\xd0\xbd\x6b\x2c\x3f\xc5\xd9"
         "\x3a\xbe\xcd\x7b\xab\xf9\x70\x5d\x76\x57\xa6\x70\xa2\xb8\xcf\x56"
         "\xcf\xee\xa0\x43\xc4\x61\x76\x83\x8c\xc1\x36\x50\xe2\x6a\xa3\x9b"
         "\x07\x8d\x1b\xf3\x03\xdb\x96\xca\xca\xa3\x88\x0c\x32\x97\x32\xdc"
         "\x73\xeb\x71\xb1\xae\xa3\x67\x5f\x23\xb2\x3d\x1f\x43\xf8\xbf\x90"
         "\x90\x4f\xfc\xaa\xe6\x81\x9b\x53\x17\x38\x95\x53\x4d\xb4\x1e\x6e"
         "\xcd\xe8\x1d\x3a\x76\x30\xb3\xd3\xa8\xfa\x69\x57\x24\x82\x21\xd9"
         "\x44\x6f\x2f\xb1\xe2\x0b\xe8\xbf\x51\x84\x3e\x17\x76\x93\x10\x5f"
         "\x3c\xef\xcb\x6b\xcf\xc9\x7f\xfc\x21\xee\x9c\xfa\x7a\xa7\xc0\x72"
         "\x4e\x74\x60\x64\x6b\xc8\x0e\x8a\xf7\xbd\x4a\x76\x01\x56\x59\xc7"
         "\x28\x45\x31\xee\x68\xc9\x76\x2c\xf9\x90\x05\x0b\xee\xe6\xaf\x5b"
         "\x88\x91\x3a\xbe\x33\x71\xfb\xee\x9a\xba\x31\x9c\x28\x6e\xcf\xc7"
         "\xb8\xb0\x63\x16\xdd\x27\xa5\x42\x79\x8a\xd5\x52\x69\x1d\x30\x45"
         "\xa7\xcb\x5d\x49\x9e\xbb\x96\xcb\x75\xab\xce\x10\x34\x9e\xa0\x2c"
         "\xba\x52\x2c\x4c\x9a\xa7\x11\x8b\xee\xe4\x7f\xe4\x48\x99\xa7\xa3"
         "\x6d\xe4\xa2\xa1\x08\x0c\xc4\x90\x6e\xbd\x39\xb0\x34\x91\x26\x40"
         "\xab\x1a\x6b\xa2\xa5\xd2\x26\x0a\xc0\xbb\x25\xb1\x91\xe5\x72\xca"
         "\x96\x79\xb1\xb5\x7b\xe1\xbf\x82\x91\xb3\xd9\xcd\x98\x39\x44\x29"
         "\xe9\x56\x03\x0c\x3e\x9e\x1f\xa7\x6f\xbf\xcb\x13\x71\xc3\x63\x5a"
         "\x3d\x3a\xcf\x7b\xb7\x68\x70\xe4\xbd\xb9\xd9\xd8\x68\x7f\x40\x41"
         "\x3a\xcc\xb4\xcc\x3b\xc5\xd2\x12\x88\xdf\x19\x63\xd6\x50\xb5\x70"
         "\xf1\x04\x06\x87\x20\xa4\x48\xa5\x3c\xbf\xa4\xca\x5c\x81\xf1\x2c"
         "\x55\xfc\xfd\x30\x79\xd8\xfe\xc4\x1e\x51\x20\xfe\x7a\x6e\xf9\x05"
         "\xa4\x26\x42\x42\x6c\xbe\x2b\xa3\x67\x6f\xce\x34\x17\xc5\x0c\x28"
         "\x33\xe1\xca\xff\x4a\xf2\xc4\xcf\x89\x94\x42\xd4\xaa\x8f\x55\x39"
         "\xc7\x9b\x56\x43\xff\x73\x79\x74\xe2\x20\xea\x85\x6c\xcd\x5b\x04"
         "\x46\x66\xfc\x58\x8e\xf5\x03\x32\xfe\x59\xa5\xfe\x9c\x11\xa6\xf5"
         "\x7f\xd8\x64\x2c\xd5\x3d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===polishedlyhematosis
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x6f\x6c\x69\x73\x68\x65\x64\x6c\x79\x68"
         "\x65\x6d\x61\x74\x6f\x73\x69\x73";
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
.*===geriatricundaubed
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x67\x65\x72\x69\x61\x74\x72\x69\x63\x75\x6e"
         "\x64\x61\x75\x62\x65\x64";
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
