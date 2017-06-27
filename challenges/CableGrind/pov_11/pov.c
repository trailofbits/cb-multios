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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x67\xb5\x97\x63"
         "\x90\xb1\x8d\x4f\x2a\xe5\xfb\x62\x2c\x8c\x8a\x5b\xe1\xb3\x8c\x7d"
         "\x31\x00\x00\x00\x0b\x97\x01\x6a\xa9\x28\x7c\xbb\x2e\xeb\x26\xb9"
         "\x4d\xc7\x55\xf0\x6e\x21\xb1\xbe\x6a\x06\xd6\xf4\xd1\xfb\x52\x73"
         "\xaa\x1d\xf2\xb3\xbd\xaa\x5d\xae\x90\xa2\x00\x21\x7f\xcb\xc8\x0d"
         "\xc9\x27\x3b\xfb\x1a\x45\x1b\xd8\x47\xac\x01\x00\x50\x9c\x2d\xfc"
         "\x39\xfa\xe5\x33\x9c\x0e\x66\xb4\xcc\x76\xa0\xf3\xc3\x92\x69\x1a"
         "\x32\x27\xcc\xf6\xc9\xc6\x29\x94\xbc\xa4\x39\x86\x35\x36\x98\xa7"
         "\x30\xb4\x7e\x78\x39\x87\x80\x1c\x6e\x7b\xf9\x83\xd8\x7b\xe9\x49"
         "\x42\x5c\x7e\xc8\x90\x1a\x43\xfe\x29\xe5\x2f\xef\xf6\x0f\xaa\x71"
         "\xb4\xf3\xfa\x42\x85\x76\xc6\x50\xa4\xc2\x5d\xd2\x9b\x5d\x4e\x3a"
         "\x73\x0f\xc6\x1e\x9a\xa1\xc9\xe4\x09\x73\xed\xb6\xf1\xfb\x39\xb1"
         "\xff\xdd\xe7\xd9\x74\x57\xd5\x56\xcd\xe6\xf2\x7e\xf1\x79\x6b\xee"
         "\xfc\x72\x0f\xcc\x11\xf2\x99\xfa\xb0\x76\xb6\x77\x3c\x7f\xda\x85"
         "\xbc\x9f\x1b\x3f\xed\xce\x76\x6b\x04\xbc\x1d\x3b\x28\xaf\x50\xe1"
         "\x4f\xa2\x98\x96\xb3\x34\xf6\xa4\x3a\xb8\xe2\xcc\x46\x0b\x31\xc2"
         "\x8c\x39\xbd\x9e\xd7\x01\xa4\x79\xae\x7d\xbe\x21\x0c\xdf\xe7\x23"
         "\x01\x23\x1b\x87\xc2\x7a\xb3\xf5\x4c\x13\xee\x01\x00\x7a\x89\xe4"
         "\xf1\x5c\x51\xc3\x9b\xc1\x7d\xae\x05\xb5\xbe\xfa\x23\xa9\x22\x04"
         "\x6a\xfb\x83\x2f\x4c\xcd\x05\x6d\x0e\xf4\xd5\x0f\xe4\x99\xde\x6d"
         "\x10\xd1\x92\x20\x99\xfb\x05\xac\x82\x4d\x6e\x08\x86\x4a\xfa\xaf"
         "\xca\x98\x58\x9b\xe2\xac\xe5\x34\x08\x87\xbf\x18\x5a\x3d\x0d\x9d"
         "\xdc\xcb\x4b\x89\x43\xf7\x7d\x13\xea\x69\x14\x4a\x16\x1c\x04\xdc"
         "\x3e\xd4\xa6\x65\xae\xf1\x5c\xcc\x4a\x35\x4c\x46\x1b\x09\x1c\x84"
         "\xa3\x8a\x68\x3a\x80\xee\x6c\xb1\x9d\x54\x55\xb2\xdf\xa5\x5f\x24"
         "\xbf\x50\xcc\x7e\x48\x3f\x93\x14\x57\x10\x9b\x37\xe0\x6b\xaf\x51"
         "\xb3\x8f\x2c\xd0\xd8\x57\x67\x88\xce\x7d\xd3\x13\xe4\xbb\x3b\x8c"
         "\xd0\x68\x2c\x0c\x6d\x17\x6c\xee\xef\x77\x0d\xf5\xec\xa1\xcb\xe7"
         "\x3b\x94\x08\x68\x6e\x5c\xc2\xaf\x57\xc7\x13\x8e\x25\x52\xa7\xd4"
         "\x8f\xf3\xdc\x5c\xea\x5f\x4c\xfa\x27\x29\x43\x50\xc1\x6c\xc9\x8c"
         "\xdf\x1d\xb1\x1f\xa8\xef\x71\x1c\x1f\x44\x3b\x95\xb2\x1a\xd4\x3f"
         "\x02\x50\x7a\x4b\xb9\x1d\x81\x97\xed\xf3\xf8\xda\x2d\x03\x30\xc8"
         "\x0f\xec\x7a\x46\x96\x65\xc6\x5d\xa0\x97\xa9\x61\xe5\x69\x28\x85"
         "\x5c\x76\x76\xc8\xdb\xb2\x1a\x2a\x83\x3a\x81\x80\xa0\x03\xab\x86"
         "\xa1\x75\xe0\x1b\x33\xfd\x28\x2e\x50\x81\xb6\xa2\x02\x9c\x7b\x46"
         "\x4c\x70\xe4\x94\x89\xe1\xb3\x7f\xa5\x09\xe1\x5c\x28\x39\x6a\x5b"
         "\x97\x15\x54\x9d\xaf\x4e\x8e\x34\xdd\x29\x7b\x3a\xc1\x29\x14\x20"
         "\x00\xaf\x45\x05\x2d\x28\xe8\x07\x6f\xb7\x33\xe1\xc0\x8c\xc9\xad"
         "\x77\xb7\xf8\x37\x68\x55\x41\x3f\x6c\x22\x87\xa5\x1a\x44\x4f\x8b"
         "\xad\x0d\x76\x31\xab\xc7\xfd\x31\xa5\x54\xee\x27\xc4\x21\x16\x8c"
         "\x05\xca\xd6\x72\xcf\x5c\xee\x4d\xfa\x23\x65\xa0\x8b\xdf\xb9\xd2"
         "\xc7\x00\xfe\xcc\x4d\x5d\x5d\x8d\xe9\x65\x05\x77\x10\x71\x4a\x1c"
         "\xd0\x68\x4f\x76\x52\x12\x96\xdf\x0c\xf6\xd0\x5d\x3f\x00\xc5\x80"
         "\xc0\x22\x15\xeb\xe3\x0a\x80\x4a\x6f\x5c\xed\xf4\x9d\x5e\xfc\xb6"
         "\x78\xe5\xe8\xc7\x88\xf6\x5b\xc5\xba\x40\x77\xfd\x0a\x51\x3e\x34"
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
.*===inquilinecopse
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x71\x75\x69\x6c\x69\x6e\x65\x63\x6f"
         "\x70\x73\x65";
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
.*===preformisticexemplifiable
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x72\x65\x66\x6f\x72\x6d\x69\x73\x74\x69"
         "\x63\x65\x78\x65\x6d\x70\x6c\x69\x66\x69\x61\x62\x6c\x65";
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
