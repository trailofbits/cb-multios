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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x91\x87\xe2\x56"
         "\x9b\x62\x46\x75\x63\xd2\x8e\xc9\xeb\x4e\xd8\x96\x37\xf9\x31\xd1"
         "\xe7\x00\x00\x00\xa7\x08\x33\x12\x1d\x9e\x6f\x76\xc4\x2e\x33\xc2"
         "\xcc\x9d\x01\x64\x64\xfc\x3b\xb2\xb7\x6e\x3c\xae\xa4\xe4\xf9\xb4"
         "\xb8\x01\x83\x6a\xbb\xd2\x28\x72\xd8\xe6\x84\x91\x4e\x6e\x84\x37"
         "\xdc\x42\x47\x24\x4b\xd2\x19\x6d\xe0\x54\x03\x8c\xfd\xac\xf5\xfe"
         "\xb2\xd7\xd2\x06\x33\x02\x81\x7e\x35\xfb\x03\x1a\x98\x47\x62\xc4"
         "\x78\x64\x88\xd6\xe8\x16\x52\xb2\x3c\xe0\xa2\xbc\x09\x33\xce\x45"
         "\xad\x24\x71\x1d\xfb\x52\x31\xee\x29\xe6\x00\x05\xa3\x0b\x2e\xbf"
         "\x97\xa6\xd4\x5f\x84\xe7\x28\x78\xe3\xa9\xa5\x21\x33\xd5\x72\x67"
         "\x21\x16\x91\x21\x2d\xa3\xf2\xc8\xce\xd3\x6c\x2f\x5b\x33\x32\x5c"
         "\xf5\x01\x0e\xdb\x59\x33\xde\x3e\x3a\x40\x86\x65\x02\xd3\x7e\x1a"
         "\xf7\x10\xdc\x8b\xed\xca\x08\x30\xad\x46\xd2\xce\x1c\x60\xce\xf5"
         "\x03\xc6\x36\xb4\x6c\x5e\x58\x81\xf3\xc2\x5f\x70\x8d\x7c\x46\x32"
         "\x7f\x73\x15\xc0\xf8\x43\x70\x66\xb7\x1d\xa4\x03\xb8\x1a\x91\x08"
         "\x1b\xa5\x94\x33\x00\xd0\x37\x5c\x17\x99\xc1\xb2\x82\x0b\x2a\x1b"
         "\x32\x20\xf6\xdf\x90\x64\x67\x17\xe1\x3d\x0e\x25\x5f\x8f\x65\x32"
         "\x38\xec\x0b\x99\xa8\x4b\x2e\xd5\x6a\xdf\xd3\x4b\x85\x6c\xd4\xf1"
         "\xc0\xf9\x1c\x60\x48\x32\xa8\x6e\x9d\x65\xb7\x66\x6a\xa6\xf7\x27"
         "\xba\x4f\xff\x6a\x01\x67\x1e\x9e\xaf\xf9\x9c\xb7\xe5\x40\x73\x2f"
         "\x89\x40\x45\x28\x03\x2e\x8c\xf5\x00\x5a\x34\xd2\x78\xe3\x0e\x84"
         "\x59\x32\xd8\x29\x95\xc1\x1c\x49\xa8\x88\xb4\xd5\x36\x33\x49\xf3"
         "\x06\xcd\x1d\xf3\x46\x68\xd2\x75\x63\x92\x94\x00\xa0\x68\xe8\xc2"
         "\xd4\x2c\x22\x21\x57\xa4\xe5\x30\xcf\x9b\x19\x28\x1e\x4a\x81\xec"
         "\x92\xfd\x72\x63\x79\x32\x1c\xde\xdf\x07\x6c\xcf\x6a\x6a\xa0\x63"
         "\x31\x38\x82\x08\x93\x36\xfa\xc0\x4b\x5e\x29\xeb\x55\xfa\x36\x51"
         "\x63\xbf\xb1\x48\xb0\x87\xa1\xed\xf8\x6f\x2d\x36\xb2\xe5\x0e\x3b"
         "\x6a\x0b\x1b\x61\x91\x2f\x17\xe6\xc8\x91\xf9\x85\xe4\xb6\x08\x45"
         "\x12\x9d\x69\x5c\x4c\x28\x3f\x2a\xb8\x08\xb6\x7d\x8d\x56\x07\x61"
         "\x14\x74\x3c\xae\xb3\x06\xa8\xab\xc9\x94\x09\x44\x78\xdb\x20\xaa"
         "\x02\x1d\xda\x0a\xfe\x46\x5b\x8d\x4d\xa9\xdb\xb9\x70\xcb\x2c\x72"
         "\x45\xec\x6a\x99\xbb\x86\xee\x26\x59\xf9\x18\x30\x7c\xeb\x67\xa9"
         "\x6f\xe9\x30\xaa\xdb\x1b\x12\x24\x71\xbf\x39\x94\x07\x46\xaf\x4a"
         "\xfb\xb5\x80\x56\x20\xfd\xc3\xc1\x1c\xc6\x42\xe7\x10\x5a\xac\xfd"
         "\xe8\x27\xd1\x3a\xc0\xfa\xfe\xfc\x84\xa3\x8d\xdb\x86\x2d\x65\xf0"
         "\xb3\xe7\xe6\x33\x26\x61\x09\x5f\x72\x29\xc6\xc9\x40\x74\x0d\x0e"
         "\x67\x75\x97\x59\xaa\x39\xa2\x42\xcd\x1b\xb3\xd3\x06\x10\xeb\x81"
         "\xf3\x2f\x24\x98\xb7\xf7\x31\x47\xe7\xc3\x3d\xf4\xa9\xb4\x90\x58"
         "\x41\xef\xbd\xf5\xa2\xc6\x79\xef\x7d\xb5\x13\x4d\xe6\x78\xec\x2a"
         "\xf4\xb7\x47\x31\x9f\x38\xe4\x70\x5f\xd5\x10\x8f\x13\x37\xa5\x4e"
         "\x87\xa9\xba\x97\xb3\x29\xc8\x17\x7a\x31\xa1\x26\x55\x6c\xbc\x83"
         "\x47\xd4\xdd\x4f\xab\xf8\xf4\x53\x14\x6a\x22\x9b\x6a\x23\x99\x68"
         "\x2e\xf5\x78\xed\xe5\x7a\x8d\xdc\x74\xfa\xf7\xb8\x6d\x1d\xac\x4c"
         "\x63\x96\x25\xda\x82\x02\x46\x19\x2f\xae\x5c\x70\x23\x33\xcf\x20"
         "\x82\x33\xe4\xeb\x1c\x0e\x94\x4e\xa8\x75\x36\x01\x3a\xe3\xa4\x01"
         "\xaa\x02\x44\x2b\xea\x41\xb9\xb2\x59\x39\xaf\x07\x95\xa2\x70\x47"
         "\xf8\xc3\x2b\x31\xb0\x19\x0d\xf2\x39\xcd\x7c\xbe\xd8\xd4\x30\xd6"
         "\x7c\xb5\x1a\xae\x4c\xe2\x7b\xb2\xdc\xb4\x20\x8e\x68\xfe\x79\x64"
         "\x97\x4b\x44\x95\x88\x42\xe7\x3a\x8b\x15\x6d\x73\xd9\xba\xc0\x07"
         "\xbb\x77\x63\xbd\x8e\xbd\x5c\x28\x62\xd6\x37\xea\x14\xca\x70\x5e"
         "\xe3\x28\x29\xda\x11\xe2\xa1\x76\x04\xd6\x63\x82\xf0\xe2\x59\x74"
         "\xc6\xa4\xb1\x0c\x0c\xea\x98\xc4\x9d\xb5\xa4\x4f\xd9\x21\x20\x20"
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
.*===inkfishpoppycock
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x6b\x66\x69\x73\x68\x70\x6f\x70\x70"
         "\x79\x63\x6f\x63\x6b";
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
.*===predestinarianglia
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x72\x65\x64\x65\x73\x74\x69\x6e\x61\x72"
         "\x69\x61\x6e\x67\x6c\x69\x61";
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
