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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xd7\xdb\x3d\xe8"
         "\x92\xf4\xd9\x64\xb5\x50\xf5\xef\xe1\x00\x00\x00\x3e\x21\xf7\x0c"
         "\x0e\xa6\x75\xc0\x9f\xb4\xc0\x59\xd6\x4d\x07\x17\x50\x64\xbf\xd8"
         "\x7e\x60\x63\xb5\xe4\xd6\x54\x77\x10\x35\x46\x00\xcd\x9a\xd4\x82"
         "\x3b\xad\x17\x4f\xaf\x19\x78\xc0\x42\xb5\x7f\x4b\x16\x90\xab\x76"
         "\xd8\xf6\x3d\xe0\x75\x3c\x67\xdd\x44\xad\xca\xf8\x97\xee\x88\xa1"
         "\x2a\xa6\xce\x33\x94\xa9\x33\x63\x7c\xe6\x14\xb6\x5f\x61\xcd\x6d"
         "\x5d\x59\xae\xa8\x44\xec\x3c\xe3\x12\xf2\xd6\x7d\x3d\x4d\xf2\xc2"
         "\x24\x3a\xea\x54\x6c\x73\xaf\xc1\xd7\x51\x29\xd9\xb4\x99\xda\x98"
         "\x6a\x57\x5b\x38\x8e\x42\x12\x78\x93\xbc\x19\x54\x88\x0b\x33\x7f"
         "\xf5\x6d\xb3\xc7\xd8\xca\x97\x86\xde\x0d\x0a\xfd\x18\xe2\xd2\x66"
         "\x45\xd8\x57\x33\xac\xe8\xca\xc9\xf1\x36\xab\xb8\x20\x79\x2b\x4a"
         "\x9d\x5b\xee\x3b\x90\x9a\x4f\x3b\xc1\xaf\x00\x8e\xf2\x8c\x62\x1d"
         "\x40\xf6\x34\xbf\x2a\xfb\x5c\xb7\x2e\x8a\xc3\x84\xef\x9f\x1c\x43"
         "\xe8\x63\xda\x9d\x46\x66\x84\x6b\x41\x9e\xcb\x2d\x2e\x14\x67\x2f"
         "\x72\xee\xbe\xbb\x77\xad\x2d\x50\x84\xe0\xb7\x2c\xa9\x16\x7b\xbf"
         "\x13\x8f\xfe\xb3\x3b\x7d\xec\xb7\xee\x1a\xe6\x29\x4c\xe3\xc0\xbc"
         "\x9b\x0a\x79\xbb\x4e\x3e\xb4\x0e\xaa\x26\xc2\x8c\x2d\x7e\x6e\xd1"
         "\x1b\xa9\x11\x5e\x8b\x26\x9f\xc2\x1d\x1f\x9d\x6e\x0f\x11\x00\xc5"
         "\x06\x75\x55\x58\x52\x97\x36\xb5\x6b\x82\x00\xf5\xe8\xcb\x10\x17"
         "\x00\x17\x18\x74\xfa\xdf\x96\x2f\x68\x98\xa8\x87\x03\x07\x70\x90"
         "\x13\x81\x0f\x0d\xfb\x9b\x17\xe6\x4c\x59\x95\x49\x49\x47\x5c\x96"
         "\x96\xda\xf0\x6f\x58\x4c\x0d\x46\x80\x6a\xf3\xe5\xc6\x38\x63\x5f"
         "\x03\x20\x0a\xb5\x6e\xb3\x3e\x69\x18\x8f\xa7\xde\x6f\x78\xae\xa6"
         "\x6f\x7b\xd1\xdf\x8b\x4e\x6e\x92\xd6\x8a\x67\x35\x09\x92\x8d\x9b"
         "\x9c\xb9\x9c\x1a\x96\x39\xcb\x0d\x84\x32\x3d\x70\xb6\x22\x3a\x4b"
         "\xb6\xcf\x36\x59\x4f\x7c\xd8\x91\xcc\x41\x77\xfd\x3d\x91\x32\xd2"
         "\xd2\xbb\xb6\x6c\x3c\x8c\xbb\x72\xa4\x81\xe6\x4e\x65\x02\x96\x49"
         "\xc0\xb2\xc1\xb8\xbe\xd1\x86\x5d\x22\x29\x51\x01\xf6\x6c\xa6\xc2"
         "\xf7\x08\x89\x09\x7a\x26\x17\xad\x3e\x7f\x12\xef\xfb\xe4\x72\x23"
         "\xf2\xf6\xa0\x7c\x03\xf3\x64\xbd\xed\x28\x05\x08\x69\xad\x1a\x88"
         "\x66\xe4\x23\x17\xcb\xca\x8c\x03\xf6\x74\xae\xb2\xc9\x63\xfb\x94"
         "\x27\xf8\xba\xab\x35\x59\x16\xbb\x1e\xe0\xaf\x6f\x22\xab\x1a\x4c"
         "\x43\x9c\xa4\x6c\x17\x35\x71\x71\xef\xa8\x2c\xf3\x69\x86\xa3\x53"
         "\xac\xd6\x5f\xb6\xeb\x75\x48\x3f\x25\xfe\x65\xb4\x57\xac\x03\xa4"
         "\x03\x0f\xf8\xa6\xd2\xff\x1c\x78\xa0\x32\xb1\xd8\xa5\xa1\xc0\xb1"
         "\x75\x7c\x85\x01\x88\x13\x9a\xb8\x1e\xf2\x39\x1f\x26\x52\x11\x6f"
         "\xc1\x74\xe2\xc0\x61\x1e\xba\x93\xbe\x22\xcf\x4f\x5f\x21\xe3\x7c"
         "\x74\xa5\xd1\x2e\x10\x8d\xdd\xff\xb4\x23\x43\xd3\x1e\x8c\xa2\x07"
         "\x3d\x89\x7d\xc9\x2a\xe6\x6e\xe5\x18\x07\xe9\xcd\x92\x57\x87\x02"
         "\xab\x86\x48\xe0\xbe\x1c\x94\x4e\xbd\xf4\x4d\x94\xbd\xa3\x3a\xbf"
         "\x6e\x44\x11\xb2\xdf\x59\xb9\x1d\x39\xc4\x6c\xea\x4f\xa2\x9b\x5d"
         "\x90\x61\xb0\x75\x5f\xcd\xf0\x2a\xfe\xe3\x66\xcc\x3c\x81\x35\x1f"
         "\x85\xdc\x36\xe8\x21\xba\x92\xc2\x80\xf2\xef\xfb\x81\x17\xbc\x7c"
         "\x0c\x2e\x2c\x7d\x2e\x39\x08\x9a\x81\x8b\x10\xe3\x6b\x3b\x28\x81"
         "\x92\xb6\x3b\x54\x24\x16\x60\xb5\x5c\x0e\xe4\x8b\x1f\xd4\xea\xa1"
         "\x05\xe0\x17\x17\x00\x4d\xbb\xf3\xe3\xee\x2c\x93\x83\x54\x4a\xcd"
         "\xe4\x17\x17\x00\x80\x90\xe9\xc7\x4b\x32\x4c\x11\xfc\xe4\xd4\x96"
         "\xf9\x20\x7a\x52\x5a\x43\xb7\x5c\xee\x71\xfd\x2e\xe1\x72\xf2\xa4"
         "\x1a\x5a\x6d\x1b\x8c\xee\x90\xb7\xac\x68\x07\xa1\xfb\xe9\x08\xd2"
         "\xba\x7a\x18\xf1\x42\xd6\x7e\x26\x9e\x03\x65\xfe\x5a\x1f\x84\x16"
         "\xe1\xee\x57\x11\x04\x83\x38\x12\x5c\xf7\x66\x2d\xb1\xdb\x2f\xdb"
         "\x44\x76\xec\xa5\x19\x4c\xb2\x54\x26\x2e\x80\x35\x2c\x6f\x32\xde"
         "\x21\xef\x89\xec\x7a\xdc\x7d\x43\x95\x7c\xf0\x5c\x54\xe1\x6c\xe2"
         "\x93\x61\x03\xb6\xa2\x27\x68\xcc\xae\x6c\x7e\xdf\x9f\x69\x5e\xb7"
         "\x45\x4d\x82\x72\x22\x75\x08\x0c\xed\x92\xea\xf0\x53\xe2\x51\x7f"
         "\x2b\x32\x27\x4d\xb2\x21\x80\xcb\x33\x52\x3d\x03\x4d\xaa\xb7\x78"
         "\x01\x64\x2b\x77\x7c\x22\x46\xbf\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Zantedeschiacladocarpous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x5a\x61\x6e\x74\x65\x64\x65\x73\x63\x68\x69"
         "\x61\x63\x6c\x61\x64\x6f\x63\x61\x72\x70\x6f\x75\x73";
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
.*===loungyimpolite
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6f\x75\x6e\x67\x79\x69\x6d\x70\x6f\x6c"
         "\x69\x74\x65";
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
