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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x83\x84\xad\x82"
         "\x2e\x15\x96\x97\xf6\x08\x72\x33\x27\x00\x00\x00\x74\x0f\x45\x75"
         "\xa2\x08\x01\x40\x55\x36\x47\x9d\x2c\x71\xb2\x65\x50\x6d\xe3\xfb"
         "\xdf\xd2\x81\x97\xb0\xe5\x18\x29\xd0\xae\x8a\x75\xc3\x22\xde\xd3"
         "\xbc\xd1\xe4\xe8\xc5\x84\xf5\x48\x2e\x9e\x05\x71\x55\xc3\x56\x64"
         "\x6b\xfb\x2c\xfa\xd9\xc0\x01\x00\x0a\xbb\xf4\xcb\x91\xf7\xa6\x11"
         "\x0e\x3f\x45\xd4\xe9\xf7\x25\x49\x80\x34\xb7\xd9\x81\xfc\x1b\xb4"
         "\x02\x30\x12\x01\x4b\x8c\x55\xed\xdd\xe9\x90\xce\x24\xd8\x01\x31"
         "\xda\x1e\xeb\x77\x22\xfc\x2d\xf4\x24\x01\x00\x60\xcd\xa4\x44\xc1"
         "\xc5\x7d\xee\xa9\x89\x57\x95\xb5\xf1\x61\xff\x3c\x10\x49\x51\xee"
         "\x6f\xf2\xfb\xf1\x82\x43\x28\xf2\xcc\x31\x71\x5a\x16\x0b\x66\x2b"
         "\x13\xac\xe1\x98\xec\x95\xf6\x08\xca\xf9\x95\x59\x5a\x5b\xc3\xc6"
         "\x00\x13\x59\x43\x7a\x07\xf5\x21\xa8\xb7\x24\x78\x12\xbe\xf7\x7f"
         "\x01\x65\xd3\x55\x30\x47\x2b\x1e\x15\xaa\x50\x13\x6f\x77\x27\x2b"
         "\xbb\x67\xd4\x4c\xde\xb7\xee\x53\xfd\x03\x12\xf4\x42\x14\x21\x25"
         "\xb0\x45\x93\x86\x6e\x0d\x5a\x3d\xf3\x2d\x3a\x63\xea\x37\x11\xff"
         "\x01\x5f\x2e\x1d\x56\x72\x53\xa4\xdf\x2d\x8e\x6a\x9a\x0c\xd3\x90"
         "\x1f\xbe\x88\x36\xfd\x66\x94\x12\xc1\x0d\xe5\x5e\x34\x78\xd8\xca"
         "\x13\x89\x1c\x27\x2c\xa4\x61\x1e\x72\x08\xe4\x92\x21\xc9\xf4\xc1"
         "\xfc\x82\x8e\x5a\x3b\x34\xbe\x44\x6e\x1a\x74\x77\xd4\x2f\xb5\xff"
         "\xaf\xeb\x2c\x37\xe9\x4f\xae\x44\x55\xa6\xa3\xde\x13\xb3\xff\xfc"
         "\x9b\x57\x89\x79\x34\xdf\x0c\x2d\xa3\x28\x0f\x24\x9f\x82\xf4\xdd"
         "\xbc\xbc\x32\xf4\x34\xa8\x3b\xf1\x15\x63\x54\xcd\x6c\x28\x04\x6d"
         "\x21\x11\x10\xbe\x64\x3e\x46\xf0\x78\x84\x9e\x1d\x03\x9c\x97\xdf"
         "\xb2\x06\xe2\xaf\x1d\xdd\xbf\xd8\x71\xa3\xae\xc0\x4b\x18\xd7\x1a"
         "\x9c\x8c\xa6\xe2\x73\x80\xb9\x49\x4b\x99\xe5\x98\x6f\xe9\x7d\xf6"
         "\x47\xb4\xf4\x3e\xf0\x03\xb9\x10\xe1\xa6\x71\x0e\x18\xc3\x8c\x95"
         "\x8f\x74\x1b\x4b\xb6\x15\x2e\x61\xa1\x7c\xd2\x11\x12\x48\x70\x07"
         "\xe4\xde\xa2\xbf\xd2\x9e\x1a\x80\x42\x01\x06\x0c\x7a\xe8\x04\xc9"
         "\xe6\x1e\x05\x11\x1f\x26\x74\xb4\x84\xd0\xcf\x10\x61\x16\x3d\x84"
         "\xe2\x1f\xc6\xfb\x4f\x43\x63\x0d\x9f\x41\x81\x3d\x39\x5f\xe3\x80"
         "\x79\x5c\x04\x54\x4e\xc3\x5c\x8b\x71\x22\x65\xed\xf8\x06\x53\xb1"
         "\xcb\x79\x4b\x88\x62\x5a\xa7\xb5\x34\x9f\xd9\xb1\x18\xca\x18\x7b"
         "\x4d\x55\x13\x8d\xf2\xbf\x85\xe8\x5f\x76\xd0\x42\xb9\xb0\x3f\xff"
         "\x6e\xa7\xa8\x61\x38\xe0\xec\x4e\x5d\x07\x02\x4d\x30\xf5\x0d\x3c"
         "\x8e\x7c\x6d\xa1\x8e\x13\xb6\x8c\x1a\x83\x85\x74\xa8\xf8\xc2\x85"
         "\x3e\x1c\x19\x2f\x26\xc9\xe5\xe5\x8d\xf9\x28\x7e\x88\xac\xd8\xfc"
         "\x77\x2a\x42\x57\xb0\x57\xea\xe0\xaa\x84\x5a\x05\x9f\x4f\x74\x57"
         "\x93\x4a\xa3\x58\xdc\x3e\x3c\xd6\x81\xd8\x0c\x66\x70\x27\xc4\x98"
         "\x94\xfe\x01\x49\x8e\xa9\xfc\x19\x4d\xbf\xbd\x79\x53\x62\x90\x0c"
         "\x68\x55\xdf\x7f\x22\x15\xa2\xc2\x8b\x39\xdb\x33\x14\xb0\xb5\x7b"
         "\x45\x14\x39\x70\xc3\x5b\xbd\x90\xaa\x68\x4d\x2f\x45\x23\xd4\xf4"
         "\x14\x3a\x18\x7e\xbe\x57\x80\x3e\xaa\x6f\x42\x47\x8a\x56\xa0\xf9"
         "\xf0\x4c\x69\xff\x20\xc4\x00\x62\xa8\xdb\xb3\x43\x7e\xc2\x30\x45"
         "\xd9\xfe\x16\xfe\xaa\x66\x85\x3b\xe9\x50\xfb\x6c\x3e\x2c\x86\x0f"
         "\x86\xd5\x2f\xf8\xe9\xf5\x15\xb7\x46\xf8\x2c\xc3\x32\x22\x58\x37"
         "\x83\x10\xee\x63\x37\x4a\x15\xe8\xa2\x14\x67\x2f\xed\x0f\x49\xe7"
         "\xe9\xf3\x88\xb6\x70\x4a\xb8\x69\xef\xd1\x39\x7b\xdb\x55\xf1\x95"
         "\x08\x41\xb0\xa2\xcf\x61\xc4\x0e\xc0\x47\xf8\x34\x58\xaa\xf8\x28"
         "\xa9\xd0\x9b\x8b\xe1\x34\x2a\xd9\xb4\xc5\x2d\xbb\x66\x7d\x73\xe2"
         "\xc2\x2e\x7b\xea\x72\xd1\x14\x70\x98\x98\x19\x11\x48\x89\x8b\x8a"
         "\xfb\x3b\xe9\xaa\xed\xae\xda\x90\x22\x98\xc9\xcc\x93\x86\xc2\x3f"
         "\x00\xd2\xb1\xcd\x23\xbc\xde\xb9\x24\xef\xfc\x5e\x12\x16\x2e\xff"
         "\xa9\xb0\xa5\x08\x33\xaf\x49\x63\xea\xa6\x4f\x9d\xc4\xb0\xd2\xcd"
         "\x80\xb8\xd9\x5f\x7c\x41\x79\x48\x69\x10\x5e\xd7\xe3\x80\xdd\x57"
         "\x50\x76\x63\x03\x1e\x34\xdc\x3b\xe9\x7a\x32\x42\xdd\x09\xcd\x79"
         "\x47\xc6\xf2\x5a\x4a\x98\x4a\xd3\x78\x33\x20\x20\x20\x20\x20\x20"
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
