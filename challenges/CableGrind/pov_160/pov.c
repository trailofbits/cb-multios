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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x66\xc8\xba\x48"
         "\x36\xe4\x5e\x74\xc9\xf5\x2b\x70\x7d\x01\x00\x00\x61\x7f\x52\x50"
         "\x7a\xd5\x1a\xa6\x2b\xde\x58\x54\x9b\x29\xca\xd2\x76\xeb\x5e\x97"
         "\x5e\x00\x5e\x55\x11\xbc\x03\x49\x17\xaa\xac\x99\xf7\x3d\xe0\x6d"
         "\xb7\x22\x3c\xb6\xc2\xe2\x65\x9d\xa0\xc5\x3a\x66\x09\x10\xec\x96"
         "\xca\xca\x91\x0b\x23\xf6\x16\xb6\x0a\x24\x70\x8d\xb6\xa9\xbc\x38"
         "\x44\xf2\x2b\x81\xb1\x0d\xcc\x80\x49\x2b\xd2\xa7\x3e\x07\x1d\x1d"
         "\xcf\xb7\x10\x96\xef\x1e\x93\xec\x8f\x8a\x6f\x98\xe5\xd3\xdf\x37"
         "\x0c\xf0\x1a\x7f\x96\xe8\x2f\x30\x6f\x90\x78\x1c\x56\x5f\x91\x2c"
         "\x1f\x8d\x6c\x4f\x18\x7b\x90\x48\x18\xc6\x6e\x7c\xa0\x70\x21\x3d"
         "\xb6\xcd\x65\x29\x71\x3a\xd3\x75\x6b\x97\x40\x06\x27\x6c\x22\xaf"
         "\x60\x43\x3f\x3a\xac\x0c\x70\x50\x79\xe5\x5a\xde\x78\x55\x35\x82"
         "\xcd\x36\x8c\x5e\x91\xd4\xc4\x66\x76\x0e\x9d\xe5\xd9\xcd\x40\x0a"
         "\x80\x33\xcf\x24\xce\xec\x61\xb1\x06\x4f\x00\xd8\xb9\x03\x68\x06"
         "\xbb\x2e\x9f\xd7\xa5\x08\x3c\xc6\x3b\xac\x43\x77\x6c\xc2\xfd\xf1"
         "\x9b\x07\x87\x17\x17\x59\x1a\xf3\xcf\x71\x50\xc8\x5b\x68\x83\x3f"
         "\x05\x9c\x56\xbf\x18\xd6\xcd\x90\x82\x55\x8c\xca\x66\xf5\x92\xd1"
         "\x2f\x46\xeb\x9e\x9c\x5e\x9a\xf5\x18\xff\x59\x43\x8b\xc2\x11\x70"
         "\xae\xa4\xac\x49\x52\x0b\x61\x5a\x2b\xbf\x6c\x55\x62\xf9\x36\xc5"
         "\x16\xba\xe7\x88\x01\xe2\x70\x3e\x13\x3b\x1a\xb0\x6a\xe1\x6d\x5c"
         "\x49\x37\x92\xcd\xd9\x40\x08\xf7\x2f\x58\x0a\x70\x89\x9c\x07\x25"
         "\x9a\x6a\x8a\xea\x80\x79\xac\xdd\xb0\x30\xa6\x09\xf1\xc2\xdf\xdc"
         "\xa8\x01\x6d\xf9\x0d\xda\x24\x7d\x5e\x6a\xb2\x6b\xa7\xd1\x41\x53"
         "\xfa\x70\x5e\x9f\x05\x20\xde\xe8\x91\xfd\xdf\xfe\x82\x9a\x70\xea"
         "\x00\xe6\x4f\x8e\x1c\x2e\x83\xd5\xe4\x57\x7b\x94\x6f\xd0\x62\xe4"
         "\x9b\xf8\xfc\xb9\x63\x9a\x15\x49\x00\x0e\xf3\x2f\x0a\x17\x72\xc4"
         "\x2a\x4c\xaa\x60\x81\xd9\x11\x78\xd5\xae\xb6\x77\x82\x3e\x9f\xa0"
         "\x8f\x08\xdb\x4f\x97\x5b\xb4\x9a\x7f\x2c\x8c\xd8\x5c\xa2\x16\xc6"
         "\x56\x37\x4c\x0e\xf5\xf9\x2d\x75\xb1\xe0\xa1\x71\x89\xdf\x1f\x64"
         "\xc9\x76\x42\xee\x8d\xc2\xe6\x23\x32\x30\xc2\x2e\xbf\xdf\xc4\xec"
         "\xe6\xd8\x62\xb4\xc9\x28\xed\x41\x7c\x5f\xde\xb3\xa0\xc0\xb0\x99"
         "\x0c\x25\xcb\x80\xdd\x4a\xfb\xa7\x9a\xbb\x0c\x85\x7b\xdc\x17\x41"
         "\xdc\x34\x9c\x22\xbe\x6d\xab\x57\xb4\xd9\x1f\x37\x07\xae\x8c\x1f"
         "\x0b\xa6\x6e\x10\x64\xe7\xb7\xec\x6f\x84\x8f\xe9\x73\x4b\xdf\x07"
         "\xd5\x9c\x1d\xdc\x8d\x2b\x4c\xdc\x4e\xbc\x9e\xc8\xb8\x3d\xdb\x0c"
         "\xa4\xb9\x3b\xaa\xfc\x5e\x77\xdc\xdd\x1f\x55\xbb\x0c\x93\xc9\xa2"
         "\xc9\xc0\x99\x01\x0d\xa6\x62\xb3\x0f\xd0\xe3\x56\x70\x80\xc7\xd8"
         "\x05\xe0\xf8\xbf\x14\xe3\xed\x6a\xab\x46\x80\x2e\x5a\x86\x69\xac"
         "\x0f\xa9\x52\x80\x54\x4f\x16\x0a\xb0\xf6\x1c\xf7\x4a\x46\x09\xcf"
         "\xc2\xe5\x28\x15\x0a\x7b\x25\xb3\x4c\x87\x68\x07\x0c\x6c\x1c\x26"
         "\xe5\x16\x19\xd1\xa2\xe0\x25\x16\xf1\xe0\xf0\x98\xa9\x08\x98\xd1"
         "\x70\x6a\xd3\x1b\x67\x5c\x12\xf0\x08\xa6\xda\x12\x8d\xf6\x7e\xf8"
         "\xd8\x3a\xe9\x06\xf5\x7c\xec\x02\xcd\x20\xec\x95\xd4\x9b\xd7\xdc"
         "\xf2\x7c\xda\xd2\xcc\x8e\xd3\x34\x71\x98\xa4\xb2\x10\x78\xbe\x3a"
         "\x1e\xc3\xa3\xe1\x0e\x8d\x1b\xd6\xc9\x95\x57\x9f\x3b\x52\xb9\x64"
         "\xcb\xe1\x85\x52\x3e\x05\xf1\x6d\xb7\xab\xa0\x6e\xcb\x47\xfc\xe8"
         "\x11\x4b\xe5\xd2\x81\xd6\x45\xf4\x3a\x14\x04\xbb\xb7\x70\x8b\xdd"
         "\xa5\x78\x91\x79\xf9\x23\xda\x4f\xa5\x2b\x69\xf2\xe4\x3f\x32\xf0"
         "\x49\x62\x73\x82\x57\x41\x7b\xb6\x33\x81\x3f\xd5\xf9\x48\x31\xad"
         "\x49\x07\x99\xa1\xea\xc0\xd4\xdf\x4f\x99\xd8\xe6\xb8\xd8\x36\xc3"
         "\xb3\xd2\x88\x67\x08\x34\x22\xdf\xd9\xee\x01\xb9\x6f\x2a\xbc\x46"
         "\x0f\x55\x60\xd9\xd6\x54\x1d\x16\x96\x38\xdc\x4e\x00\x15\xa0\x2f"
         "\x45\xad\x68\x26\x13\xfd\x6e\xc2\x05\x9d\x4a\x4c\xc9\xfe\x02\x29"
         "\x91\x8b\xb4\x1e\x0a\xba\x69\x98\x1c\x8d\x2b\x22\x20\x92\x17\xe3"
         "\x19\x46\x6c\x1a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===archiereusHainan
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x72\x63\x68\x69\x65\x72\x65\x75\x73\x48"
         "\x61\x69\x6e\x61\x6e";
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
.*===laterodeviationNarciss
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x61\x74\x65\x72\x6f\x64\x65\x76\x69\x61"
         "\x74\x69\x6f\x6e\x4e\x61\x72\x63\x69\x73\x73";
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
