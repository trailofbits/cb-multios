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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x90\x20\x7f\x5e"
         "\x57\x30\xc5\x19\xe7\xc1\x7e\x31\x13\x00\x00\x00\x6f\x58\x4f\xc8"
         "\x2b\x00\xd1\xe1\xd3\xec\x19\xa2\xf4\x46\x79\xe7\x21\xc8\x91\xe7"
         "\x92\xe9\x5e\xcf\x5a\x9e\x95\xe6\x96\x76\xb9\x50\x90\xf9\x59\xcc"
         "\xf4\x18\xb9\x3d\x60\x31\xda\x24\xe9\x96\x63\x40\x37\xbf\x5e\x3c"
         "\x0a\xee\xf2\x8b\xbe\x47\x44\x2f\x69\x9d\x2a\xfd\x6d\x62\xb6\xb0"
         "\x4e\xc9\xe3\xcb\x92\xe6\xc2\x5c\x0a\x82\x4b\x0d\xa5\x7c\xd8\x8c"
         "\x52\x3b\x9f\x52\x95\x0f\xed\x6c\xbc\x94\xc4\x62\x44\x82\xb8\xfc"
         "\xf7\xc2\x87\xeb\xc7\x60\x2f\x96\x56\x18\x94\xff\xb0\x5d\x0f\x88"
         "\x0b\xdd\x29\xf2\x23\xb3\x28\xf9\xfc\x21\x8c\x68\x32\xdb\x00\x4b"
         "\x31\xc3\x11\x7c\x45\x30\xb3\xdb\x64\x43\x88\xe9\xf3\xd1\x47\xf8"
         "\x35\x65\x60\xcd\xef\x3c\x6e\x8a\x91\x5e\x9f\xcd\x78\xd9\xd3\x1f"
         "\x7f\xca\x83\xb6\x62\xa4\x8b\x2e\x24\xb9\xa3\xb5\xbb\xe0\xbf\x83"
         "\xe0\x6e\xf2\x89\xe6\xfb\xe5\xac\xbe\xb6\x1f\xda\xc4\xf7\xb2\x8b"
         "\xea\x29\xf4\xc8\x6e\x76\x7a\x5f\x85\x38\x32\xe6\x89\x83\x13\x1c"
         "\xa1\x38\x5a\xc3\x46\x99\x38\xcd\x49\xd9\x7c\xa8\x60\xf5\x9e\xc3"
         "\xde\x8b\x77\xd8\x6c\xf5\x0d\x29\xe8\xea\xb2\x82\xc0\x4d\x43\xe2"
         "\xc8\xa4\xcf\xb5\xe7\x12\x04\x85\x92\x88\x12\xf2\x5d\xd5\xb5\x62"
         "\xd5\x05\x82\xe3\x9d\xfe\x2a\x74\x09\xbc\x31\x0e\x70\x4d\xad\xce"
         "\xdd\x40\xaf\x4e\x35\x5b\xac\xd7\x52\xfa\x3a\x0d\xa6\xec\xa8\xa6"
         "\xad\xfa\x6f\x7e\x20\xcb\xa3\x7d\xb0\xc2\x45\x53\xa5\xd0\x06\xfa"
         "\x19\xf4\xc8\xab\xd8\xa7\xd9\xb7\xbb\x1e\x03\xa8\x2b\x19\x11\xdc"
         "\x87\xd7\xde\x0c\x85\x16\x63\x6f\xda\x12\xd2\xf2\x6c\x65\x08\x77"
         "\x01\xa8\x27\x6b\x0e\x43\x73\x7b\x79\xe8\x90\x51\xf6\x0f\x59\x8d"
         "\x6c\x81\x91\x1b\x5c\x8c\x74\xac\xc5\x1d\x58\x11\xf0\xbf\xa2\xa5"
         "\x30\x5d\x69\x7c\xa8\x2f\x53\x1b\xd7\x1b\x28\x91\x43\x13\x50\x72"
         "\xdb\xae\x09\x7c\x85\x62\x67\x13\x6b\x25\x17\x58\x2b\x2d\x7d\x74"
         "\x6b\xd6\xf3\x23\xec\x2b\xa7\xd5\x77\x23\xf3\xcf\x3c\x2e\x07\xaa"
         "\x11\x8c\x6b\x86\x71\xb3\x71\x75\xc5\x75\x5a\x54\x54\xbd\x29\x23"
         "\xe8\x32\xbd\x12\x09\x34\x63\xf0\xaf\x97\xea\x9e\x40\x2b\x62\xba"
         "\x2d\x71\x4f\x46\x5d\x8b\x1e\x76\xa2\xe0\x6d\x19\xc4\x24\x4d\xa3"
         "\x8a\x0d\xc4\xea\xaa\x06\x5d\xeb\x69\x3e\xc7\x56\x41\xbb\x8b\x21"
         "\x07\x14\xe0\xae\xc0\x54\x9b\xcb\xdf\x76\x84\x74\xb0\x18\x3c\xa9"
         "\x9b\xd6\xa4\x47\x87\x4e\xf0\x96\xef\x15\xc3\xff\x22\xf9\x92\xe0"
         "\x9b\x4e\xc7\xc5\xbf\xfb\xc2\x60\x1e\xa8\x1a\xca\xd2\xc9\x65\x47"
         "\xb5\x3d\xa6\x4b\xb2\x97\xcc\x42\x6a\xe2\x03\x7b\xd7\x05\x74\xa1"
         "\x34\x74\xb5\x2e\xb4\xec\x35\x53\x6b\xa6\x6b\x72\xce\x4c\x13\x5f"
         "\xb5\x27\x58\x31\x9c\x45\x30\xfd\xb7\xcd\xc1\x81\xf6\x73\x66\x19"
         "\x79\xed\x87\x83\x55\x56\xc6\x44\xc3\xc6\x60\x90\xed\xa6\x5d\xf8"
         "\xa2\x25\xc8\xa9\x83\xee\xb0\x1c\x77\xc9\x04\x03\xc2\xe4\x46\x93"
         "\xee\xe6\x0e\x12\x96\x59\xbf\x38\x06\x1f\xdd\x97\xa8\x5e\xb4\xf1"
         "\xa0\x01\xf3\x13\xb8\x86\x01\x88\xe8\x93\xbd\x5b\x8d\xc6\x56\xee"
         "\x8c\x4a\x70\x6d\x6f\xc0\x8f\x02\x48\x36\xe1\xaa\x45\xfc\xc0\xf8"
         "\xf1\x1b\x87\x27\x09\xc5\x98\x23\x6d\xde\x49\x11\x70\x3f\x98\x36"
         "\x88\xdc\x0c\x72\x7a\xc2\x08\x15\x9b\xbc\x7c\x86\x3f\xe0\xa0\x90"
         "\xb8\x20\x9a\x95\x0c\xeb\xd1\xd1\x3f\xff\x2a\x3d\x47\x9c\xe2\x62"
         "\x7c\x07\x5f\xad\xd3\xac\x16\x42\x00\x12\xea\xd0\xb7\x3b\xa6\xf7"
         "\x0b\x93\x76\x55\x56\xda\xf0\x4f\x1a\x7e\x0f\x62\x26\xed\x8f\x2c"
         "\x2f\xf5\x17\x57\xc2\xce\x29\xd6\x4e\x22\x1b\x6b\xce\xb7\xed\xc3"
         "\x29\xe4\xb0\x26\x4f\x47\x7a\x4e\x13\xc6\xc2\x72\x97\x89\x43\xfd"
         "\x78\x05\x19\xa4\xf2\xe7\x85\xa6\x31\x35\xad\xa0\x91\xe8\x18\xf6"
         "\xac\x60\xe7\xb5\x38\xa5\xf4\x67\x0c\x62\x64\x54\xa2\x12\xf8\x9f"
         "\xd2\xfd\x56\x79\x7a\x8b\x45\x6e\xb3\x2f\x89\xeb\xba\xc3\x42\xe0"
         "\x17\x8c\xf5\x58\xb7\x98\x2d\xe7\xaf\x52\x8d\xc4\xc5\xc1\x47\x5a"
         "\x9d\x1f\x79\x3f\x3a\xbd\x21\x7f\x05\xba\xae\xc6\x38\x38\xb3\x20"
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
.*===GemitoresBourignian
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x47\x65\x6d\x69\x74\x6f\x72\x65\x73\x42\x6f"
         "\x75\x72\x69\x67\x6e\x69\x61\x6e";
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
.*===piperitiousreekingly
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x69\x70\x65\x72\x69\x74\x69\x6f\x75\x73"
         "\x72\x65\x65\x6b\x69\x6e\x67\x6c\x79";
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
.*===tautologicpanimmunity
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x74\x61\x75\x74\x6f\x6c\x6f\x67\x69\x63\x70"
         "\x61\x6e\x69\x6d\x6d\x75\x6e\x69\x74\x79";
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
