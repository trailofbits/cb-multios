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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x2d\x6b\x1d\xab"
         "\x9d\x52\x79\x6e\x44\x5e\x6e\xc9\x9b\x01\x00\x00\x7e\xa9\x17\x6e"
         "\x48\x57\x1b\x43\xef\x88\x40\x4f\x38\x76\xda\x8b\x3f\x50\xba\x98"
         "\x10\x29\xd0\x18\x6f\x4f\x97\x47\xb1\x87\x8c\x5f\x7e\xcc\xf4\x9a"
         "\x08\x3f\xfa\xc3\xd2\xa0\x1a\x63\xaf\x06\xfb\x28\x97\xcf\xb3\xfd"
         "\x86\xec\x00\xc0\x06\x2f\x83\x61\x23\x5e\x95\x1b\xdd\x03\x9e\x98"
         "\xec\x18\x1c\x3f\x70\xdd\xae\xf0\x2d\xc8\x94\x3b\x0f\xa2\x49\x81"
         "\x64\x37\x19\x4a\xdf\x97\x05\xb5\xc8\x39\x6e\x41\xef\xc5\xd8\xfc"
         "\x90\x7a\xc4\xb8\x12\x23\x66\x99\xa2\x8b\xe9\x5a\x51\x0e\x1a\x7e"
         "\xcd\x5a\x48\xc9\xba\x90\xe3\xa9\xe1\xa6\x56\x89\xdd\xdb\x83\xd4"
         "\xf1\x8f\x0f\x05\x1d\x0a\x55\x3e\x38\x0d\x62\x69\xcd\x76\x82\x34"
         "\x17\xa5\x30\x04\x46\x28\x93\x24\x87\xa3\x78\xbc\xf6\xbc\x90\x34"
         "\x5f\xb0\x05\x6f\xdb\xa2\x63\x18\x17\xa8\xb5\x1d\xff\x0a\x28\x5a"
         "\xbd\xfe\x8f\x50\x37\x2c\xdc\xb4\xcf\xd8\xe9\xd8\xd9\x81\x16\x29"
         "\x10\x9d\xd7\x95\xb8\x68\x9b\xf3\xb7\xfa\x33\x70\x0b\xdc\x57\x5b"
         "\x90\xb3\x94\xd5\x78\x43\x38\xb2\x23\x55\x74\xe2\xb5\x0d\xc5\xe3"
         "\x30\xa2\x96\xfd\xa2\xe3\xfa\x60\x58\x0e\x38\xc0\xdc\x98\x84\x2b"
         "\xcb\x21\x37\x8d\xb1\x55\xc9\x00\x47\xe1\x64\x65\xe1\xe7\x5d\x79"
         "\x4b\x71\x52\xcd\x43\xed\x49\x5e\x43\x8c\x3f\x7c\x21\xb9\x30\xad"
         "\x1b\xbd\x80\x50\x2b\xc0\x72\x55\x26\x88\x4f\xa9\x00\x2f\x36\x25"
         "\xf1\x6c\x39\x04\x6b\x1a\x06\x48\xfc\x83\xfb\x03\x74\x11\xe1\xae"
         "\x5f\xf7\x92\x53\xe1\x62\x24\x25\xfc\x9a\xa3\x71\x31\x01\x56\xf9"
         "\x80\xa6\x6b\x8e\xf1\x11\x47\x7e\xfa\x72\xf3\x28\x98\xd1\xda\x5e"
         "\xc1\xaf\x1c\x48\x88\x36\x71\xd7\x69\xd1\x22\xd7\xf7\xee\xae\xdc"
         "\x99\x33\xbb\xf4\x25\x72\x19\xa1\xce\x76\x33\xd6\x28\xa0\x71\x35"
         "\x02\x3c\x05\xcb\xa7\x64\x70\x97\x6d\x75\xf3\x11\xcb\xdb\x66\xe8"
         "\xc5\x17\x71\x81\x9d\x5f\xef\x23\xea\x94\xf3\xc6\xec\x96\xcf\x9e"
         "\x2c\x9c\x16\xcb\x94\x38\x00\x38\x00\x38\x00\x8f\xce\x64\xc7\x7e"
         "\x0d\x12\xc8\xdc\xf9\x1a\x39\x64\xef\xbb\xd5\xa6\x36\xc9\x1e\x15"
         "\x79\xaa\xc8\x1a\x2f\x69\x10\x05\xa3\xa8\x89\x6e\x51\x49\xdf\x1f"
         "\x63\x79\xad\xe1\xbc\xb9\x23\x98\x78\xc2\x36\xcf\x43\x97\x86\xc8"
         "\x99\x15\xf7\xd0\xc1\xf3\x75\xe4\x39\xe6\xd8\x7b\x1a\x06\x48\xff"
         "\xa8\x26\x6d\xc2\x22\xd1\x3c\xcd\x62\x96\xa4\x26\xc1\x6d\x2e\x09"
         "\x50\x7c\xc2\xa0\xb7\xca\xfc\x93\xef\x5f\xf1\x9f\xd0\xdf\xed\x52"
         "\x9b\x4d\x81\x30\x55\xc7\x95\xa1\xa0\x17\x8e\xcc\x3d\xc2\xa3\x32"
         "\xe9\xe3\x1f\x45\xd4\x49\xd1\x13\xa1\x8f\xe0\xf0\xbe\xf5\x3d\x60"
         "\x8f\x10\x8c\x34\x87\x08\xc0\x2f\xb9\xa9\xda\xa4\x93\x3e\xdb\x67"
         "\x73\xcd\x5f\xd6\x6c\xa1\x98\x94\x48\x06\xbc\xda\xfd\x8c\x6b\x74"
         "\xcf\xca\x5f\x81\xd4\x14\x76\xa1\xa5\xb0\x38\x24\xcd\x79\x0b\xf8"
         "\x3c\xdf\xbf\xfe\x8d\xe5\x96\x2c\x16\xd8\x2f\x2e\x46\x39\xf6\xbc"
         "\xac\x6b\x82\x3b\x03\x1b\x26\x52\x31\xde\xa2\x4f\x83\xd5\xed\xc6"
         "\x73\x2b\x81\x82\xeb\x02\xbf\x7b\x8e\x9c\x6c\x21\x7c\x92\x4c\x07"
         "\xdb\x1f\x49\xd4\xa3\xe1\x4a\xb8\xb4\x02\x60\xb9\x13\xc7\xed\x1c"
         "\x33\x6b\x75\x0e\x6a\x33\x48\x21\xf2\x99\x55\x0a\x4b\x7d\xaf\xf3"
         "\x34\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===hyperduliaferrateen
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x68\x79\x70\x65\x72\x64\x75\x6c\x69\x61\x66"
         "\x65\x72\x72\x61\x74\x65\x65\x6e";
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
.*===malthouseenteralgia
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6d\x61\x6c\x74\x68\x6f\x75\x73\x65\x65\x6e"
         "\x74\x65\x72\x61\x6c\x67\x69\x61";
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
