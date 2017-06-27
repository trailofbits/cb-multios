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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x82\xcb\xc3\x1c"
         "\x46\x0f\x82\x22\x14\xc8\xda\xc7\xdc\x00\x00\x00\x42\x7d\x69\x01"
         "\x8d\xb9\x81\xc7\x4e\x35\xd4\xa4\x9d\x7e\x9e\xf6\x42\xff\x19\xa2"
         "\x89\xba\x91\x89\xcb\xfe\x9a\x15\xbe\x1b\x37\x87\x89\x85\xae\x02"
         "\xcf\xd5\xe1\x8f\x5a\x3a\x88\xbd\xe2\xcb\x61\x8d\xd5\x79\xad\x98"
         "\xa0\x64\xd3\xfc\xbf\x69\x6b\xdc\x8f\x3b\xf1\xcd\x1f\x5e\xd9\x38"
         "\x97\x59\xa2\x05\x33\x6a\x2d\x2d\x58\x95\x7d\x1c\xc2\x27\x6d\xb9"
         "\x6b\x24\xca\xe2\x89\xc1\xa0\x8c\x28\x1b\x31\x84\xd3\x3b\x8f\x95"
         "\x7c\xde\x36\x48\xe0\x06\x2e\x10\xa3\xff\xa1\x68\xb4\xb2\x9f\x52"
         "\x21\x63\x29\xfd\x3a\x80\x16\x65\x4e\x40\x5b\xa3\x3d\x65\x8f\x1a"
         "\xb4\xed\xf9\xc0\xf1\x8c\xc9\xf7\x79\x52\xe4\x82\x63\x17\x59\xd2"
         "\x09\x65\x74\x36\xb6\x3a\x06\x1f\xb4\x19\x95\xd7\x95\x45\x46\x69"
         "\xa4\xcf\xc2\xe9\x3b\x8c\xf2\x35\x3a\xfb\x7c\xe0\xdc\x12\x98\x2c"
         "\xf8\x0b\x1c\x3a\xb7\x5d\x17\xa6\x0d\x62\x5c\x64\x89\x1d\xa3\xab"
         "\xcc\x42\x11\x04\x85\x74\x98\xa2\x88\xf4\x98\xef\xa5\x10\xd4\x54"
         "\x6c\x05\x54\xf1\x77\x58\xd2\xe0\xfa\x1a\x20\x01\xe4\xa4\xd4\xfb"
         "\x48\x09\x60\x4d\x9f\x12\x09\x1d\x83\xbd\x47\xe2\x73\x33\xbe\x71"
         "\x1e\x85\x7e\xdb\xa6\x52\xa7\xa7\x69\x5e\x77\xc8\x75\xcd\xc7\xb5"
         "\x44\xcc\x2b\x9a\x69\xd5\xdf\x6a\x78\x1f\x56\xc7\x0b\xfe\x5d\x47"
         "\x9f\x59\x58\x5a\x02\xf8\x2d\xbb\x24\x7e\x11\xa6\x5e\x72\x60\x74"
         "\x15\x3b\x37\x7c\x54\xe8\x6e\x46\xd4\x7b\x5a\x4a\x46\x14\x3f\x97"
         "\x07\x51\xb5\x4a\xa9\xfa\xe8\xe5\xb9\x33\x3f\xb7\x48\xf4\x6c\xd1"
         "\x0b\x01\x1e\x02\x25\x68\xfc\x89\xc8\x4d\x0f\xb8\x2c\x91\xfb\xa9"
         "\xe2\x4e\x67\xb0\x53\x22\x55\x0c\x84\xd8\x2c\x26\x25\x62\xeb\xa7"
         "\xe7\xbf\x28\xa4\xa5\x40\xb0\xfc\x26\x20\xe5\x5c\xc9\x66\xd1\x56"
         "\x67\xd1\x2b\x93\xf9\xac\x42\x60\xe9\xb4\x90\x1a\x73\x24\x10\x86"
         "\xd0\xe4\x78\x12\x00\x47\x83\x09\xd6\x5b\x06\x11\xcd\x51\x75\xb0"
         "\x3a\xdb\x0f\x50\x07\x02\x38\x1b\xe9\x67\xdc\x0f\x15\xda\x3f\x76"
         "\x68\x21\x14\xe4\x1e\x0a\x18\x14\xe7\xd6\xce\x8e\xfb\x8e\xe1\x12"
         "\x43\x3a\x66\x10\x86\x72\x2e\xbb\x00\x8b\xf7\xb1\x31\x40\x67\x32"
         "\xcc\xf2\x22\xc7\x7f\xf2\x19\xc5\xbb\x74\x8e\x8a\x63\x80\xb2\x37"
         "\xa0\x8d\x33\x9d\x00\x14\x69\x73\xcb\xfa\x48\x6e\xad\xcb\xf4\xcd"
         "\xac\xc2\x08\x6a\x33\x59\x06\xdd\x0d\x32\x96\x99\x47\x9a\x73\xb4"
         "\x88\x82\xf3\x73\xe8\xed\x5e\x74\x9f\xff\x45\xf4\x28\x28\xe8\x67"
         "\xd6\x05\xd4\xac\xd0\xd9\x21\x5f\x23\x23\x14\x6c\xae\x1d\x25\x89"
         "\xde\x3a\xea\x6a\xb5\xa4\x51\xc8\xf0\x8d\xdf\x33\x59\x41\x5e\x4c"
         "\x1d\x8e\xb3\x9c\x26\x34\x68\x92\x84\x23\xe1\xbf\x2b\x8f\x2a\x6c"
         "\xb5\x4a\x2a\x2e\x5c\x96\x35\x39\x8d\x5b\x81\x81\xe9\xe5\xe8\x02"
         "\x20\xbc\x9f\xbc\x17\x5e\x62\x60\x88\x33\xd4\xf2\x34\x02\x6b\xc4"
         "\xb5\xa7\xcb\x37\x86\xaa\x46\x1b\xa9\x6a\xa8\x42\xf4\x52\xf2\x76"
         "\x1e\x0b\x35\x2c\x4e\x40\x4d\x36\x93\x50\x3c\x6d\x47\x24\xad\xf5"
         "\xa7\x98\x00\x59\xd8\x1d\x15\xff\xe1\x50\x85\x09\x40\x6e\xc5\x57"
         "\x53\x3c\x42\xe3\x87\x44\xa1\x59\x02\x0e\x7a\x14\x17\xf0\x02\xd5"
         "\xf5\x59\x99\x2f\x2d\x84\xe3\x40\xf0\x71\x7d\xc8\xed\x1a\xc4\x4c"
         "\xa5\xd6\x64\x7c\x0e\x96\x04\x38\x16\x2e\xba\x33\x5b\x10\x4f\x1d"
         "\xc1\xe1\x99\xa9\x66\xab\x83\x65\xf4\xb7\x01\xe9\x99\xf7\xe7\x33"
         "\xbd\x57\x11\x32\x97\xe3\xa2\x81\xda\xa9\x49\x3b\xcc\x50\xa1\x9a"
         "\x72\x03\x62\x46\x18\xa7\xaf\xb5\x45\xfc\xac\xda\x63\x47\x81\xe6"
         "\x5e\x26\x1e\x9b\x7b\xa9\x9d\xa7\x9d\x1d\x61\xc5\xf6\x97\xd8\x4f"
         "\x3f\x65\xbd\xa2\xf3\x7f\xbc\x68\xaf\x0f\xfc\x04\xe2\x90\xa1\x37"
         "\x70\x44\xcd\xd8\x75\xd3\x9a\x0d\x25\x8c\x83\x05\x97\x5c\xa4\x45"
         "\x02\x91\x5b\x31\x18\x5e\x5b\x01\x20\x3e\x88\x7b\x35\x27\xd3\x90"
         "\xff\x10\x57\xfe\x3e\x43\xcb\xe1\x55\xd6\xb5\x9b\x78\xf7\x79\xad"
         "\xc3\x4f\x69\x93\x5b\x4a\xb7\x22\xee\x47\x29\xac\x8a\x49\xf8\x90"
         "\x90\xb7\x6e\x3b\x30\x43\xbd\xbf\xb7\xa1\xb8\x4b\x39\x25\xbf\xa0"
         "\x78\xb9\xe6\x91\x35\xb6\x12\x78\xbc\xfc\x24\x9e\x9d\x88\xe5\xf7"
         "\x2f\x42\xde\x03\x89\x04\xe8\x39\x80\xbf\x2f\xd1\x30\xa0\xdc\xd8"
         "\x3d\x6a\x98\x53\x43\x01\x17\xb9\x0a\xb4\x41\xc8\xab\xa9\x85\x34"
         "\xa5\x7d\x2d\xeb\x07\x71\xad\x3f\x3b\x2b\xcf\x32\x77\x6f\xa7\x68"
         "\xca\xcb\x2e\x64\xba\xb6\xa8\x64\xf7\x9e\xff\xbc\x58\xca\x4e\xa0"
         "\xc6\xfe\xa3\x6a\xea\x37\x13\xad\x00\xea\xc9\x69\x14\x7c\xdd\x1c"
         "\x7c\x03\x2d\xe9\x57\x69\x09\x74\xd4\xcb\x59\xb8\x08\xc3\xd5\x2a"
         "\xfa\x52\x89\x6a\xdb\x24\x24\x42\x68\x43\x89\xbb\xf2\x3a\x20\x20"
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
.*===wickedlyinflatedness
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x77\x69\x63\x6b\x65\x64\x6c\x79\x69\x6e\x66"
         "\x6c\x61\x74\x65\x64\x6e\x65\x73\x73";
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
.*===Bitulithicscrin
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x42\x69\x74\x75\x6c\x69\x74\x68\x69\x63\x73"
         "\x63\x72\x69\x6e";
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
