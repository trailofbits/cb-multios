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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xdb\x70\xdb\xb0"
         "\xcf\x04\x3c\x70\x85\x4a\xda\x92\x90\x00\x00\x00\xb8\x8b\x7c\xbc"
         "\x13\x00\xf7\xff\x1f\x36\x4b\xef\x6c\xde\x13\x00\xc6\x72\x9d\x1a"
         "\x49\x21\x02\xc9\x0b\xe9\x3b\x43\xb0\x0b\x91\xd5\x5d\xfd\xee\x0d"
         "\x6a\xa8\x7d\xd9\x64\xed\x23\xe5\x64\x35\x41\xf7\xb7\xf1\x84\x12"
         "\x9d\xec\xd2\x44\xbb\x63\x46\x31\x47\x89\x6b\x50\x57\x02\xd4\x47"
         "\x36\xe3\x13\x60\x96\x18\xcd\x06\x0c\xcb\x67\xe4\xac\x95\xa5\x27"
         "\xd0\xb4\xde\xe6\x3d\x6a\x01\x6f\xb6\xfb\x6b\x9e\x74\x00\xe8\xad"
         "\xc6\xcc\x18\xf2\xa1\x8e\xfb\x6b\x87\xa0\xdd\x49\x7e\x8a\x43\x15"
         "\xe5\xd0\x9a\x4d\x8b\x52\x40\x9f\x93\xcf\xf0\xdf\x29\x5d\x9c\x80"
         "\x83\xce\x28\x74\x34\xe4\x59\x57\x90\x65\x06\x77\xef\x6e\x99\xb0"
         "\xca\xcd\x39\x1a\xc4\x52\x36\xca\xc5\x19\xea\xb7\xfd\xd9\x3e\xb4"
         "\xf1\x62\xff\x9f\x4f\xe0\xe8\x1a\x6e\xed\xb8\xae\x50\xa8\xd0\xe6"
         "\x1c\x4b\x75\x0f\x18\x6d\xf8\x36\x0a\x24\x9a\x38\x0b\xf9\x6a\xf4"
         "\x64\xc4\x50\x47\x9f\xe2\x8f\x26\x2f\x5a\xf4\xfe\xc6\x6d\xf7\x24"
         "\xc9\x81\xbc\x3a\x3f\x62\xe6\xad\xde\x9a\xf3\x80\x11\x9e\x7b\x80"
         "\x53\x2b\x3a\x88\x5b\x4b\x45\x4f\x0d\xc7\x10\xb8\xc6\x9b\x9f\x27"
         "\x87\x7e\x3e\x5e\xab\xbc\x23\x01\x9c\x08\x0f\xc0\x28\x48\x79\x92"
         "\x12\x57\x9a\x5a\x33\x5c\x68\x49\xe5\x62\x07\x43\x62\x7d\x46\x8c"
         "\xc9\xd8\x7e\x75\x4c\x1f\x71\xda\x68\x78\x21\x2d\x86\x8d\x92\x54"
         "\x98\x8f\xcc\x1d\x8f\x15\xde\xda\x9d\xe7\x4d\x22\xa3\x5d\xca\xd6"
         "\xa1\x0b\x0e\x13\xbb\xc1\xba\xab\xef\xe0\xf8\xdd\xce\x1b\x82\xe9"
         "\x57\xb5\xef\x0f\x21\xad\x67\x72\x31\xc3\xd9\x1c\xbd\x77\x29\xf0"
         "\x7c\xa9\x72\x9c\x9e\x16\xa2\x12\xbf\x7d\x99\x35\xb7\x4a\xd1\xfb"
         "\xcd\xaf\x16\x07\xde\x64\xe9\x22\xa6\x08\x9d\x60\xb2\xf8\x89\x64"
         "\x11\x29\xa2\x5a\x27\xd1\x0c\x5c\xf8\x8c\x0f\x70\x2d\x2e\x7f\x5b"
         "\xa9\xf4\x7c\xcb\x4d\x48\x33\xf0\x14\xce\xad\x96\xf5\xbe\xf5\xdd"
         "\xb8\xa2\x2a\x56\x4a\x09\xd1\xad\x07\xec\x42\x07\xc1\x61\xba\xfe"
         "\x41\x90\x03\x1f\x3d\xd7\x0d\xdc\x2a\xac\x8f\x59\x6a\x6b\x58\xaa"
         "\xf8\xa8\xf8\x6e\x78\xf2\xeb\x72\xae\xd6\x56\x6c\xdf\x10\xe2\xb9"
         "\x99\x67\x14\x1a\x61\xb4\x1f\x6f\x07\x6e\x5b\xcd\xb3\x39\xd8\xe2"
         "\x04\x99\xca\x5a\x22\xb0\xf6\xe8\x5d\xcd\x52\xaf\x7a\x00\xf9\x2b"
         "\x89\xf5\xdc\x88\xef\xc0\xad\xc9\x65\x4f\xe1\xaf\x2f\x27\xd6\xf4"
         "\x4c\x5b\x8c\xd8\x93\xc7\xe6\x9f\x45\xa8\x4f\xc8\x21\x13\xfc\x0e"
         "\xde\xdf\xb9\x4f\xf2\x49\xe8\x48\xb5\x19\xcc\xe8\x1b\x49\xd8\x48"
         "\x43\xae\x0d\x4b\x7e\x0d\x90\x78\xe5\xed\xe5\xbd\x11\x5e\x95\xa0"
         "\xcc\xf1\xfa\x93\xae\x34\xe1\xe1\x41\xdb\x3e\x82\xc8\x8f\x2a\xbe"
         "\x27\xb7\xac\xd7\xbd\x43\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===undercropArenga
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x64\x65\x72\x63\x72\x6f\x70\x41\x72"
         "\x65\x6e\x67\x61";
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
.*===menialitypreintelligent
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6d\x65\x6e\x69\x61\x6c\x69\x74\x79\x70\x72"
         "\x65\x69\x6e\x74\x65\x6c\x6c\x69\x67\x65\x6e\x74";
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
