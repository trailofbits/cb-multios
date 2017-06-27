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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xf9\x57\x06\x72"
         "\x9d\xcb\x1f\xb0\x6b\x62\xe4\x10\x9b\x07\x3e\x59\x74\x50\xf2\xdd"
         "\xf1\x01\x00\x00\xf5\x5c\xf9\xe9\x2f\x49\x9d\xc9\x0b\xcf\xc3\x27"
         "\xea\x97\xc9\x46\x88\x1f\x40\x97\xc7\x4d\x32\x0d\x79\xdb\x79\x4d"
         "\x02\xcd\xbf\x0a\xd8\xa0\x0f\x3a\x87\xc3\xfb\x96\x4c\xe7\xab\x05"
         "\x4c\x20\x2a\x16\x77\x3a\x37\x9c\x07\x50\x24\xef\xd4\xed\xe6\x26"
         "\xcc\x19\x4f\x14\x60\xf4\xbf\xf8\xa5\x87\xd8\x75\xa4\x84\xe1\xc5"
         "\x5e\x3e\xdf\x54\x69\xdb\xe9\xa2\xc9\x43\x94\x85\xf6\x23\x2b\x00"
         "\xca\x5b\x44\x66\x29\x9a\x35\xa5\x2d\x6a\x2a\x13\x38\xeb\x63\x8d"
         "\x6c\x62\x15\x93\xbb\x2a\x84\x16\xe8\x86\x24\xc2\xd3\x35\x24\xe5"
         "\xbc\x9a\x4e\xfe\xb5\x6e\x88\xca\x12\xe6\x30\x66\x61\x9a\xb8\x41"
         "\x1b\x65\xff\xdb\x86\x9d\xce\x8b\x98\xb0\x3e\x0b\x29\xe9\x7a\x12"
         "\xb6\xea\xc6\xd3\x66\xb9\x9a\xd8\xa6\x79\x2e\xd9\xb6\x27\x34\x00"
         "\x8a\xc0\x59\x5b\x28\xa7\x2e\x24\x13\xc0\xd5\xb9\xc2\x2d\xc8\x56"
         "\x68\xd2\x15\x24\xda\xe9\xc8\xb9\xbf\xf5\x8f\xd8\x5e\xc4\xf0\x98"
         "\x6f\x24\x4a\xcd\xc7\x74\x84\x6e\x45\x3e\x4f\x3c\xcd\x07\xca\xc0"
         "\x4c\xc6\x31\x91\x6f\x24\xe8\xd0\x35\xcf\x5c\xac\x04\xa2\x4a\xfa"
         "\xc1\x5b\xac\x6d\x51\x3b\xad\x20\x60\xe9\xf4\x74\x5d\x66\x11\xae"
         "\xaa\x80\xa1\xfd\xff\x2e\xac\x81\x8c\xe7\x47\xbd\xcc\x9e\x4e\x1a"
         "\x3a\x89\x37\xf6\x70\x5d\x8e\x8d\x28\x97\x51\xe1\x1a\xa1\x95\xbb"
         "\x03\x18\xee\x30\x8e\x2b\x5c\x8c\xa2\x5c\x8d\x23\xfc\x69\x93\x34"
         "\xae\x6f\xd8\x60\xd4\x20\xfc\xe8\x16\xf3\x13\xe3\xe3\x14\xd2\x08"
         "\x67\xae\x99\x01\xa2\x0c\x76\xac\x2d\x88\x1e\x27\x55\x2e\xa9\x4d"
         "\x1a\xaf\xb4\xb5\x21\xdf\xf0\xe5\x75\xd2\x23\x47\x91\x1c\x6e\x65"
         "\xf4\x4b\xa7\x94\xe6\xcc\x65\x7d\x17\xa5\x19\x9e\xbf\xd1\x33\x50"
         "\xee\xd3\x0f\x22\x3b\x5d\xbe\x1c\xa8\xcd\x25\x17\xbb\x4d\x07\xca"
         "\x48\x84\x12\x60\xae\x9c\x80\xfe\xe7\x6c\xdf\xff\xfa\x7f\xf2\xb3"
         "\x55\xd4\x1d\xa1\xec\x9c\x1f\xb4\xe6\x47\xc6\x92\x85\x67\xee\x3f"
         "\xab\xeb\x11\xaa\xc6\x1b\xa1\xf0\xdc\x26\x3f\xab\xf8\x10\x60\x66"
         "\x16\x48\xe6\xe7\xce\xd3\xc9\x8d\x9a\xa2\x4f\x9e\x12\xa8\x79\xaf"
         "\xda\xf6\x8b\x07\x5b\x1b\xa5\x55\x06\xef\x70\x60\x39\xfb\x33\xe7"
         "\x3a\xef\xdd\xc4\x45\xf6\xed\x36\x42\x5b\x72\x7f\xd3\x92\xc2\xb0"
         "\x69\xa7\x8a\x88\xa3\x65\x5e\x0c\x72\x41\x14\x3d\xf5\x9d\xfe\x6f"
         "\x68\xdb\x84\x31\xac\xc3\xfc\x58\x92\xaf\x8f\xec\x6a\xe1\x2e\x2a"
         "\xc0\x05\xd8\x6b\xf9\x65\x05\x22\x07\x08\xd8\xd0\xae\x02\x83\x03"
         "\xba\x1f\x2b\x6a\x14\x41\xb4\xec\x0f\xe6\x7b\x72\x7a\x24\xfe\xff"
         "\xdb\x01\xf2\xd2\xbc\x94\x68\xd7\x6a\xad\x4d\x91\x82\xc1\x66\x68"
         "\xb0\xb6\xec\xff\x3b\xee\xeb\x56\xdb\xfa\x62\xb1\xac\xf7\xa0\xa3"
         "\x2f\x56\x3c\x1f\x5e\x88\x9c\xc6\x80\x31\xf7\xe1\x4c\x05\x4b\x84"
         "\x34\x6b\x9d\xae\xde\x3c\xe4\xf7\xa3\xa0\xd2\x2b\xbd\xc3\x65\x27"
         "\x43\xc5\x94\x53\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
