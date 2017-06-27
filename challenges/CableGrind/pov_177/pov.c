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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x70\x48\xc0\xd1"
         "\x20\x84\x25\x8b\x42\x39\x03\xc3\xd7\x01\x00\x00\xb5\x88\x30\x45"
         "\x05\x34\xf4\xc2\x06\x9c\xd8\xe8\x54\x93\x15\x7f\xda\x26\xa9\x94"
         "\xf2\xc1\xec\x3b\xed\x62\x43\x99\x10\x5d\x76\xaf\x54\x4d\x95\x58"
         "\x32\x70\x73\x29\x1c\xdd\x66\x8c\xf1\xd1\xa7\x76\x43\x43\xb1\x04"
         "\x3b\x2b\x00\xa8\xeb\xef\x4b\x47\xc8\x37\x15\x04\x68\x77\x2a\x10"
         "\xb5\x22\xba\xb8\x1a\xc8\x5d\xd2\x80\xf7\x00\xfb\x36\x7b\xed\xce"
         "\x1e\x06\xf8\x57\x91\x58\x97\x45\x88\x61\x65\x36\x39\x59\x03\xb4"
         "\x40\xa9\xb1\x88\xfa\x44\x52\x96\x9a\xef\xa7\x1d\xf5\x6d\x51\x55"
         "\x9a\xe4\xcc\x19\x39\x5a\x45\x2e\x7f\x61\x3e\x61\xc3\x9c\xa7\x03"
         "\xd3\x09\x4a\xdf\xfa\x7a\x75\xc5\x8f\xd0\xf5\x2c\xe2\x0b\x39\x9c"
         "\x74\x7c\xf0\xbe\xf4\x5f\x0b\x9c\xf4\xbf\xb2\x47\x7c\x7d\xf1\x32"
         "\x20\x76\x0c\xee\x14\x0d\xd2\x66\xc9\x03\xb7\xeb\x5a\x0b\xe8\x7e"
         "\x19\x5c\xc5\xe3\x27\x31\x9a\xb7\x3a\x9c\x3a\xa1\xdf\x75\x53\x75"
         "\x3a\x49\x45\x37\x3f\x90\x79\xc2\x3a\xf3\x99\x08\x22\xc7\x94\x5e"
         "\x6a\x5f\x07\xa4\x48\x2b\xc0\x90\x34\xb3\x78\x6e\x5b\xa4\xc4\x1b"
         "\x1c\x1e\x7e\x82\x63\xbf\x0b\x6b\x22\x82\xf4\x51\x7b\xf8\xd8\x15"
         "\xcf\xbf\x5b\x13\x1d\xe5\x6f\x1d\x59\xe7\x3f\x09\xed\x19\x19\xde"
         "\xa0\x70\xee\x69\x62\x5f\x37\x4f\x7c\xd5\x7d\x2a\x17\xf0\x9f\x40"
         "\xd5\x46\x10\x77\x18\x60\xed\x4a\x16\x0e\xad\xd3\x4a\xb3\x6d\xa0"
         "\x6d\xe6\xa6\x46\x58\x09\xe4\xe9\x3d\xdd\xbf\x9c\x80\x12\xf3\x57"
         "\x63\x0d\x36\xfb\xf5\xda\x91\x2c\x74\xee\xe6\x97\xe0\x48\x0c\xe3"
         "\xf0\xdd\xee\x5b\x17\xf2\x04\x66\x72\x8c\x52\x6a\x7c\xde\x67\x04"
         "\x4b\xe7\xdd\x32\xc7\x83\x1d\x7f\x22\x81\xfd\x00\xff\xe0\xbd\x62"
         "\xc1\x6d\x2a\xc0\x5f\x12\xf9\x0e\x22\x95\x54\x0b\x3a\xda\xad\x54"
         "\xe2\x4e\x0d\x1c\xea\x1c\x2f\x83\x29\x47\xca\x3f\xd6\x70\x33\xec"
         "\x2b\x82\x4f\x5e\x8b\x99\x2d\x17\x8a\x5e\xaf\x00\x43\xa0\x33\xb3"
         "\xb2\x7b\xff\x9b\x4e\x09\x51\xe3\xb8\x69\x55\xcf\xd9\xbc\x29\xab"
         "\xd2\x20\x81\x7f\x1f\x0c\x4e\x7a\xa5\x2b\x42\xa9\xf5\x61\x63\xcf"
         "\x31\xa7\xbb\xe5\xb2\xbc\xbf\xf2\xb4\x79\x08\x89\x2d\x18\x80\x57"
         "\xb5\x5c\x09\x7e\x06\x51\xb4\x0e\x7d\x85\xe2\xff\xba\xfb\x63\x41"
         "\xc3\xa5\x0a\x58\xd8\xa0\xc0\x91\x4a\x77\x12\x8f\x5e\x09\xf2\xe6"
         "\xfd\xcc\xdf\xea\xc2\x51\xba\x58\x59\x26\x1d\x32\x23\xf4\xb3\xd0"
         "\x5d\xec\xc8\x45\x3e\x1a\xdb\xb1\x67\x61\x55\xbb\x9e\xc2\xe9\x07"
         "\xda\x9e\xd6\x21\x7f\x4a\x46\x22\xdc\x44\x9b\x09\x4a\x6d\xcf\xc4"
         "\xd1\x23\x0c\xe5\xc2\xaa\x49\xec\x73\xe0\xfd\xd8\x7f\x91\x2c\xeb"
         "\x4d\xb9\x2f\x2c\xb8\x4d\xeb\xd8\x76\x17\x5d\x96\x0e\xb9\xaa\xe5"
         "\xfd\xd8\xe3\xa3\x56\x23\x1c\xac\x01\x02\xfd\x45\x13\x7f\x2f\x88"
         "\x9c\x5e\x09\x78\x5a\x70\xb4\xc2\xce\x8d\xb9\x2d\x8a\x6e\x15\x51"
         "\x31\x59\xc8\x88\x42\x1a\x5a\x39\x41\x7a\x70\x4c\x80\x0d\x69\xfa"
         "\x74\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Bitulithicscrin
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x42\x69\x74\x75\x6c\x69\x74\x68\x69\x63\x73"
         "\x63\x72\x69\x6e";
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
.*===GemitoresBourignian
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x47\x65\x6d\x69\x74\x6f\x72\x65\x73\x42\x6f"
         "\x75\x72\x69\x67\x6e\x69\x61\x6e";
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
.*===piperitiousreekingly
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x69\x70\x65\x72\x69\x74\x69\x6f\x75\x73"
         "\x72\x65\x65\x6b\x69\x6e\x67\x6c\x79";
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
.*===tautologicpanimmunity
*/
      static char read_00006_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x74\x61\x75\x74\x6f\x6c\x6f\x67\x69\x63\x70"
         "\x61\x6e\x69\x6d\x6d\x75\x6e\x69\x74\x79";
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
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** delimited read
      static unsigned char read_00007_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00007 = NULL;
      read_00007_len = 0;
      int read_00007_res = cgc_delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 4);
      if (read_00007_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00007_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00007_00000_match;
      pcre *read_00007_00000_pcre = cgc_init_regex(read_00007_00000_regex);
      if (read_00007_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00007_00000_pcre, 0, read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, &read_00007_00000_match);
         if (rc > 0) {
            read_00007_ptr += read_00007_00000_match.match_end - read_00007_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00007_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
}
