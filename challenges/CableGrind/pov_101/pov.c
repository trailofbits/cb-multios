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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xf1\xd7\x97\x49"
         "\x6f\xa9\x4c\x45\x41\x59\xb6\x8a\x3f\x00\x00\x00\x70\x12\xbe\xff"
         "\x39\x24\x0d\xf7\x37\x33\x78\x28\x95\x17\xf5\xb3\x25\x37\x37\x00"
         "\x3d\x08\x2b\x27\x01\x42\x15\x5b\x1d\x70\xbe\x90\x89\x95\x7e\x32"
         "\xfd\x68\x9e\x70\x07\x6b\xb4\x93\xce\x8c\xee\x65\xfc\xd0\x41\x0a"
         "\x42\xd5\x0e\x85\x1c\x0e\xcf\x54\x2f\x9d\x3a\x9a\xf4\xf2\x56\xb4"
         "\x7d\xd8\x0d\xe5\x9b\x18\x21\xaf\xb9\x8b\x8b\x27\xc8\x6a\xbf\x2e"
         "\x22\xfa\x84\x97\x0c\x20\x7b\x03\x49\x95\xf2\x05\x65\x47\xd6\x19"
         "\xbb\xfa\xe7\xca\xc6\x71\x78\xe3\x80\x59\xa2\x01\x36\xab\xc7\x86"
         "\xee\x55\x97\x2e\x16\xef\xd4\x38\xab\x93\x1e\x81\xe9\x43\xdf\xb1"
         "\x0d\x79\xcc\xe5\x70\xf2\x74\xcd\x9f\x88\xac\x26\x7c\x46\x50\xbd"
         "\x2d\x79\x29\xe7\x57\x23\x55\x73\x01\xc9\xc5\x32\x97\x19\xd4\x7c"
         "\x8a\x4f\x28\x96\x31\x4f\x68\x63\x00\x89\x20\x92\x2d\x5a\x18\x7f"
         "\x2f\x69\x6b\x60\x63\xb4\x97\xae\x63\x31\xa6\x0f\x55\x15\xe4\xcb"
         "\x52\xa6\x40\xe4\x61\x52\x4d\x33\xa7\x03\x97\x95\x84\x5f\xfa\x82"
         "\xdd\xd5\xca\x36\x01\x59\x48\x7d\x9f\x45\xcf\xa1\x89\x62\xcd\xf5"
         "\xd7\xcb\x71\x1f\x11\x2b\x29\x92\xd2\xf9\x3a\x0d\x2e\x33\x12\xf9"
         "\x02\x12\x08\x9e\x8b\xb5\xd1\x86\xc3\x48\xb2\xbb\x0a\x09\x3f\xae"
         "\xe9\xab\xfa\xa5\x8e\x3e\x5c\xb6\x4a\x55\xce\x78\xb9\x63\x4d\x3c"
         "\x0c\xf6\xeb\xaa\x09\xf4\xb2\xeb\xb7\x39\x44\x2b\xae\xcb\x12\xd9"
         "\xc5\xc6\xf0\x6a\x4b\xc6\xa5\xac\x30\xe1\x60\xcf\x86\x8d\x08\x7c"
         "\x0c\xda\xee\x7d\x66\x16\x1a\xce\x5d\x9f\x5c\xe1\x1e\xf8\xbf\xcc"
         "\x3f\x85\xbd\x6d\xf7\xb0\x0d\xdb\x53\x42\x2a\x15\x4d\xcf\x22\x5b"
         "\x24\x68\x0e\xb9\x93\x46\x74\xdd\xf7\x83\xe2\xe4\x26\x14\x25\x63"
         "\x77\x2c\x58\x8a\x31\xc9\xad\xed\xda\x87\x5b\x0c\x88\xdf\xc8\x8f"
         "\xbf\x8d\x90\x53\x1f\xfb\xb3\x07\x8e\xca\x50\x7a\xda\x17\xd1\xa3"
         "\x9b\xe2\x1e\x41\xb8\xf1\xa9\xcf\xdc\x81\xf6\x0b\x35\xee\xe9\x33"
         "\xb2\x12\x04\x71\xa9\x83\x3f\x34\xca\xb6\x66\x8c\x33\xd1\x62\x2f"
         "\x62\xe7\x9f\x2e\x46\x4e\xdc\xa7\xbf\x2f\x19\xf9\x3d\x98\x28\x90"
         "\xb3\x9d\xdf\xd5\x78\xa9\xb4\x9a\x3a\xd4\x08\x47\x56\x58\x81\x74"
         "\xa3\x47\x29\x6e\xda\x58\xfe\x2a\x58\x5b\xe7\xc9\xaf\xcb\x81\x57"
         "\xf5\xea\xd3\xf8\xb9\x3c\x7b\x8a\x2a\x61\x7c\x32\x3b\x71\xeb\x14"
         "\x85\x9e\x70\xc5\x40\xd0\x8f\x41\x55\x6b\x10\x50\x80\x2f\x8a\x11"
         "\xf7\x56\x36\x89\xd6\xf9\xe6\xfd\xe3\x7b\x5a\xe2\xb2\x5d\x1e\x4d"
         "\xd7\x5b\xbb\xd0\xd6\x5e\x28\x6d\x59\x44\xa1\xbd\xd8\x4a\xe9\x0e"
         "\xd7\x6e\x15\xb7\x03\x1b\x50\x7a\x2a\x92\xb6\xbe\x56\xf1\xba\x21"
         "\x0e\x5e\xe4\xc2\xe8\xe7\xaf\x97\x06\x69\xcf\x6d\x02\x5b\x05\x33"
         "\x3c\x22\xa9\x34\xa7\x88\x13\x21\x83\x36\xae\x43\xdb\x98\x30\x3f"
         "\xdf\x08\x6e\x43\x18\x7c\xcc\xf1\x8f\xae\x76\xf5\x13\xc7\x11\xe1"
         "\xd0\x80\x97\x8e\x3b\x29\xdd\xb8\x09\xa1\x27\x0a\x80\xb7\x03\x69"
         "\x44\x86\x11\x21\xfc\xea\xf2\x64\x80\x47\x5f\x21\x33\x7e\xfc\xba"
         "\x78\x67\xb7\xd0\x75\xb1\x05\x9c\xab\x88\xa8\x89\x4c\xe9\x46\x46"
         "\x9b\x22\xa4\x70\x23\xc6\x17\x8e\xb5\x13\x66\xf1\x37\x78\x44\xb6"
         "\x9c\x71\x00\x96\x6c\x59\xe4\x7b\x9f\x41\xf6\x42\x90\xe2\x20\x20"
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
.*===radiopaqueunrecruitable
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x61\x64\x69\x6f\x70\x61\x71\x75\x65\x75"
         "\x6e\x72\x65\x63\x72\x75\x69\x74\x61\x62\x6c\x65";
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
.*===mattapharyngological
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6d\x61\x74\x74\x61\x70\x68\x61\x72\x79\x6e"
         "\x67\x6f\x6c\x6f\x67\x69\x63\x61\x6c";
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
