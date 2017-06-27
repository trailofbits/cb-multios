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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x77\x34\x6c\x96"
         "\x39\xd0\x9c\xa7\x3d\xed\x2f\xfc\x58\x00\x00\x00\x49\x1b\x4e\xe5"
         "\x12\x86\x88\x42\x31\xfc\x77\x8d\x64\x33\x85\x88\xc4\x03\x75\xeb"
         "\xaf\xd1\xf7\x32\x36\x04\x00\xb7\x22\x20\x48\xdf\xeb\x20\x09\x3d"
         "\xd5\xd9\x34\x1d\x11\x50\x73\x50\x4a\x1b\x9c\x43\x84\xe9\xb2\x31"
         "\x97\xe7\xf4\x7a\x7e\xcc\xfb\x47\x0d\xc2\xfc\xad\xb4\x00\x9c\xa2"
         "\xcc\x23\xbe\x59\x33\xc6\x22\x74\x0f\x62\x00\xf8\x28\xb0\x4b\x96"
         "\x90\x91\xa6\x94\xdd\x11\x3e\x6d\xcf\x28\x40\x73\x30\x7a\x47\x3c"
         "\xdb\xd3\xec\x91\xed\x58\x68\x2f\x4c\xc6\x82\xfd\x0c\x7a\xbd\x35"
         "\x0a\x04\x00\x28\x59\x41\x18\x8b\x84\x30\xae\xb7\x9b\x78\x2b\xc9"
         "\xe6\x15\x26\x04\x12\x46\x9a\x74\xa8\x56\xfc\xa1\x04\x00\x2a\xa5"
         "\xb4\x48\xc0\x6c\x0d\x47\x05\x1b\x50\xd2\x7a\x9f\x7d\xea\xed\xcc"
         "\xb9\xe8\x45\x7a\x40\x63\x6a\x66\x41\x4f\x78\x5e\x21\x9f\xdd\x49"
         "\x3d\x20\x80\x4d\xf3\x15\x1c\x8f\x89\x78\x75\x50\x55\x64\x86\xba"
         "\xe9\xee\xa8\xfd\xfe\x89\x95\x42\xc1\xa2\xa3\x5e\x80\xac\xe6\x5c"
         "\xaa\x11\x1e\x80\x6b\x97\xf7\x56\x43\xee\xe1\xad\xc5\xd9\x39\x8f"
         "\x43\x99\x58\x98\x91\x5b\x53\x28\x4d\xfb\x8b\x55\x7b\x9c\x57\x03"
         "\x13\xab\x6d\x07\xef\xf1\x15\xcc\x63\x3e\x0a\x7f\x12\x97\xad\x55"
         "\x59\xb4\xaa\xf7\xa3\xb5\x68\xd6\x41\x34\x54\xcf\x0a\xfc\xe6\x4e"
         "\x25\x3e\x54\x1a\x68\x8a\xde\xc9\x42\xa8\xdd\x5d\x81\xb6\x38\x89"
         "\xf0\x65\x70\xaf\xd4\x03\x98\xff\x37\x7c\x02\xf1\x58\x35\x99\xd0"
         "\x81\x09\xca\xcc\x15\x07\x82\x29\x6a\x4a\xd1\x61\xc5\xde\x00\x47"
         "\x85\x29\x1b\x75\x57\x70\x62\xfa\xc7\x9f\x05\x2d\x7e\x55\xbb\xb6"
         "\xbb\xaa\xbe\x06\x58\xec\xb7\x8c\x46\x11\x29\x1c\x74\xac\x58\xc4"
         "\x63\xc3\x75\x5f\xb2\xbd\x39\xb2\x80\x3d\x57\x83\x70\xd5\xf7\x33"
         "\x89\x26\x22\xb3\x71\x60\x9e\x6d\xb8\xa4\xbf\x95\xf9\xf8\x78\xbd"
         "\x3b\x98\xdd\x7b\xf1\xc7\xc4\x7f\xf7\xde\xe1\xc6\xb9\x12\x60\xe5"
         "\xe0\x32\x19\xec\xec\xbf\xaf\x29\xd8\x3d\x85\x9e\x64\x9b\x3f\x5e"
         "\xa4\x44\x78\x7f\x24\x0a\x71\xe6\xea\x7f\x91\xe1\x3c\xf7\xda\x53"
         "\x0c\xfe\xc9\x57\x84\x76\x42\xe1\x79\xca\x66\xcf\x41\x4b\xbb\x50"
         "\xa0\x7d\xa9\xd5\xa5\xd9\x58\x5a\xea\x82\x2c\xb2\x26\x6f\x7f\xc0"
         "\x1f\x22\x2d\xe7\x0e\xf2\xc1\xe7\xc1\x7f\xf1\x15\xd9\x22\x66\x57"
         "\x58\xa7\xc8\x52\xc9\xf1\x4d\x83\x7b\x72\x01\xd2\x0e\x8c\xe1\x5c"
         "\xcf\x0c\x71\xae\xae\x8f\x44\x56\x6c\x1e\xcb\xbf\x72\xaa\x33\x77"
         "\xf1\x58\x2e\x8e\x78\xf4\x58\xe9\x51\xda\xb3\x6d\x54\xad\x06\x3e"
         "\xa1\xef\xcb\x49\x3a\x10\x96\xcc\x0a\x75\xc2\x58\x66\x2f\xae\xef"
         "\x8d\x78\x74\xc0\x15\x74\x6a\xad\xf0\x40\x9d\xd1\xd0\x38\xd1\xe2"
         "\x9d\x96\x84\x8b\x01\x57\x7f\x96\x2b\x11\xbf\x67\xd2\x7b\x34\x8d"
         "\xe7\x67\x5e\x12\xf5\x58\x34\xd6\xe8\xd6\xe4\x8c\xb6\x5d\x2b\x94"
         "\x41\x7d\xe0\xa7\x7c\xce\x0c\x8c\x55\xca\x49\xfc\x96\x95\x58\x1d"
         "\x2f\xeb\x78\x3c\x2d\x3a\x42\xda\xf3\x90\xb4\x5e\xa6\xaf\x9e\x50"
         "\x41\xdc\x1d\x58\x05\xaa\x7c\xea\xdf\x6e\x8b\x98\xf6\x36\xd3\xf3"
         "\x2f\xdf\x37\xb1\x6d\x0f\x3f\xe3\x27\x9b\x83\xbe\x00\x5e\x60\x32"
         "\x44\xc6\xcf\xf8\xd3\x43\xd1\xcb\x7b\x67\x41\x57\x19\x0c\x11\x1f"
         "\x98\x99\xd5\x5e\xec\x93\x5b\x5a\x29\xe2\x2e\xf6\xa8\xe7\x53\x19"
         "\x87\xf5\x62\x3d\x61\xc8\xbe\x91\x42\xbe\xc4\x9e\xa4\xce\xa4\x0d"
         "\xca\x4e\xb2\x33\x4b\x39\x5c\xdd\x0a\x6b\xa0\x34\x4d\x8c\x62\x2e"
         "\x24\x1b\x20\x30\x02\x5a\xa0\xb3\x1b\xa8\x99\xb4\x98\x2c\x0b\x8e"
         "\x43\x5c\xd4\x84\xa9\x52\x1c\x26\x27\x6b\xb3\xaf\xaf\xa5\xab\x73"
         "\x36\x9a\xb0\x99\x58\x65\x27\x27\xd7\x1d\x2b\x55\xe5\x8c\x91\x7a"
         "\xe8\x26\x41\x2f\x65\x82\x89\xef\xc7\x32\xfd\x93\x68\x64\xac\x53"
         "\x6b\x40\x7f\x39\x71\xfd\x8b\x27\xed\x3c\x85\x6e\x6b\x81\x77\x42"
         "\xb3\x62\xc1\xa5\x09\x4a\xf9\x33\xa5\xa0\x8a\x20\x33\x01\x7c\xa3"
         "\x59\x13\x8b\xcd\xcf\xac\xc7\xf3\x10\x51\xe1\x20\xd9\x2f\xa0\x76"
         "\x9a\x9e\x35\xbd\xfd\x49\x97\xc3\x9c\x46\x58\x2b\x77\xec\xf6\x7f"
         "\xd7\xfd\x20\x57\x6f\x4a\x78\xb2\x45\x0c\xfe\xde\x3c\x92\x22\xd1"
         "\x22\x43\xa5\x89\xb0\xd6\x6e\x78\x5b\x7c\xb2\x2f\xbc\xde\x72\x62"
         "\x96\x36\xb7\x6f\x0e\x31\xce\xe9\x3b\xe6\xb7\xd8\x2f\x5c\xb9\x19"
         "\xff\xb0\xd7\xda\xb1\xc6\xca\x73\x70\xdb\xb7\x5b\x4b\xaa\x0f\xdc"
         "\x2e\xb4\x61\x45\x86\x54\x02\x45\x21\x2a\x1e\xfd\x2b\x17\xb0\x40"
         "\x6b\x75\x38\xcb\xb6\xf8\x4e\x09\x3b\x49\x89\xc2\x65\x7c\x12\x57"
         "\x06\x50\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===twinklybingo
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x74\x77\x69\x6e\x6b\x6c\x79\x62\x69\x6e\x67"
         "\x6f";
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
.*===amlipyrexic
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x6d\x6c\x69\x70\x79\x72\x65\x78\x69\x63";
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
