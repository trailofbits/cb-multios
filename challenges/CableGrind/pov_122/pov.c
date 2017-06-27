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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x5b\x5c\x18\xe7"
         "\x59\xa8\x98\xbc\x2a\x1f\xf2\xf9\xae\x00\x00\x00\xa7\xe9\xde\x62"
         "\xf8\x5a\x45\xa4\xe5\x77\xca\x56\x30\x00\x30\x00\x70\x8e\x30\xf5"
         "\x55\x70\xde\x5a\x37\x64\x8b\xe2\xa3\xd3\x92\xc9\x84\x53\x13\x91"
         "\x2e\xa5\xe6\xce\x9a\xa7\xfd\x90\x1b\x00\xac\xaf\x92\x38\x82\x9f"
         "\x7b\x1b\x06\xe7\x86\xe5\x02\x12\x42\x12\x50\x6a\xcd\xd9\x12\xda"
         "\x44\x4a\x7b\x0d\xf4\x4a\xb5\x3b\xf7\x12\xe9\xbd\x47\xe9\x77\xd9"
         "\x1a\x7b\xe3\x75\xc3\x0b\xb7\x03\x3c\xf3\x31\xe6\xdd\x28\xd7\xdd"
         "\x36\x00\x70\xb5\xfd\xc3\xe3\xd1\xbb\x58\xfc\x14\x89\xea\x0e\xa1"
         "\x84\xee\x70\x80\x6a\x3e\x19\xf9\x4a\x30\x59\xdd\xa0\x5e\x16\xee"
         "\x65\x27\x37\x07\x17\x38\xc9\x1a\xbb\xa1\x0b\x79\xfe\xd1\x51\x10"
         "\x5f\x6a\x3c\x4c\x1c\x7e\xff\x99\x3e\x64\x09\x18\x7e\x76\xa0\x26"
         "\xad\x46\xb7\x79\x57\x98\xcd\x91\xd9\x08\xc8\x5b\x2d\x8d\x11\x25"
         "\x32\x85\x23\xcb\xc5\xed\x10\xbe\xc4\x13\xa6\x05\xc5\x33\xd5\x11"
         "\x90\x41\x4d\x6a\xe8\x6b\x84\xe1\x85\x34\x83\xfa\x5f\x5f\x53\x0f"
         "\x2d\x73\x8c\xad\x8a\x7b\xec\x93\x3a\xe5\xf5\x22\x4e\xc2\x8b\x60"
         "\xff\x98\x94\xa9\x3a\x37\x06\xd1\xee\x7a\x52\x3b\x23\xcd\xdd\x97"
         "\xbf\x5b\x45\x2e\xfb\xca\x2a\x2e\x29\x73\x33\x1a\xe6\x5a\x9b\xf8"
         "\x9e\x83\x06\xe9\x00\x9d\xff\x3c\x1a\xc4\x4d\xca\x69\x69\x67\x42"
         "\xfc\x3d\xf4\x8c\xad\xce\x99\xc5\xf2\xa8\xcc\x46\xf1\x7c\x0d\x73"
         "\x7d\x6d\x6f\x31\x7c\x3e\x6c\x35\x1e\x3c\x00\x94\x68\x5e\x1d\x77"
         "\x8e\x80\x82\x78\x35\xcc\x13\x36\xad\x7f\xf0\x7c\x39\x68\xf0\xc3"
         "\xbd\x0a\x42\x19\xbb\xe7\x12\xb2\xc6\x4e\xf0\x46\xdb\xcc\x77\x72"
         "\x4d\x7c\x85\xac\x1d\xcd\x25\xe1\xef\xff\x44\xf1\x68\xba\x59\x02"
         "\x97\xe4\x1c\x10\xa2\xd8\x63\x0f\x75\x36\x09\x1b\x88\x76\xd5\xeb"
         "\x4f\x1c\x19\xaf\x71\x51\xab\x78\xaf\xb2\xc7\x71\x0d\xe9\x2a\xeb"
         "\x6b\x3e\xd7\xca\x86\xd1\x86\x19\xba\xdd\x37\x30\xd8\x1d\x2d\x77"
         "\x56\xd9\xce\x69\xf7\x4d\xdb\x50\xa7\xd3\xe1\xe0\xa2\xc0\x1b\x29"
         "\xe5\x3e\x41\x84\xef\x52\xc5\x37\x21\x49\x59\x00\xaa\x37\x1a\x14"
         "\x0b\x58\xae\x71\xaf\x98\x52\x6f\x5a\x3c\xa3\x8f\x2f\x66\xa9\x86"
         "\x42\xf2\xfb\x9b\xb2\x9e\xf3\x3c\x87\xf8\xe2\xbf\x81\x7a\x74\xd6"
         "\x4c\xc8\xd5\x8d\xd1\x32\x5d\xf4\xe1\x97\x29\x81\x95\x53\x31\x3f"
         "\x1f\x69\x6d\x99\x62\x14\xb4\x54\x62\x1c\xdc\x48\x9e\xda\xf1\x91"
         "\xb5\x2d\xa2\x99\xe6\xcb\xc4\x6e\xf1\xd4\xa9\x80\xa3\x16\x48\x52"
         "\x68\x24\x92\xb3\x4a\x81\xae\xa3\x0d\xf8\x99\x56\x0c\xf3\xda\xcf"
         "\xa1\x7a\x3d\x99\xb4\xe2\x24\x99\x9a\xb3\x4d\x98\x7b\x13\x73\xa3"
         "\x96\x65\xd2\x93\x87\xc4\xcd\xcd\x05\x3b\x89\x2b\xbd\xdb\x02\x0d"
         "\xf0\xf0\xd9\x6a\x89\xc2\xe7\x61\x0f\x3a\xbe\x3c\x30\x30\x00\x7b"
         "\x17\x88\x08\x8d\x83\x13\xef\x9e\x33\x08\xcc\xb9\x8f\x93\x47\xe6"
         "\x30\x00\xa6\x21\x64\x3f\x41\x39\x8a\x6f\x10\x73\x80\x0e\x73\x38"
         "\x9f\xb0\xfc\x9a\xcc\x8b\x6e\xa3\x62\x5d\xe5\xe6\xeb\xae\x4b\x92"
         "\x64\x1d\x3e\x9f\x53\xa7\x19\x0f\xfd\x2c\xcf\x59\x8e\xf7\xe9\x30"
         "\x91\x04\xb6\x0a\x8a\x7d\x85\x47\xb3\x69\xcc\x26\x6d\x2d\x9e\xf5"
         "\x6e\xfd\xb2\x5b\x5f\xc6\x6a\x90\xc5\xa9\x78\xb3\xf7\xdc\xa9\x3b"
         "\x00\x11\x72\x6d\xae\x1b\x2d\x01\x25\xe5\x21\xf0\x23\x39\x5d\x3b"
         "\x0c\xea\x6b\x63\xce\x0a\x98\x82\xe0\x26\x13\x0d\xd7\x5c\xb5\x76"
         "\xaa\xd2\x3e\x25\xac\x27\x4f\x92\x91\xc3\x5c\x5d\x74\x0f\xc2\x85"
         "\xa9\xd8\xb3\x0c\x32\xb5\xf6\xef\x6c\x75\x39\xba\x5d\x5a\xb9\x56"
         "\x10\x05\xe0\x73\x1c\x39\x20\xba\x1f\x34\xdf\x91\x9c\xc2\xb9\xff"
         "\x68\x7c\x5b\x0e\xa8\xad\x21\x3d\x6f\x18\x56\xef\x7e\xbf\xe1\x10"
         "\xc4\x8b\xed\xc8\xe2\xdd\x07\x5c\x43\xde\x7c\x8a\x3a\x2b\x26\x53"
         "\x03\x04\x0a\xc0\x69\x92\x26\x16\x23\x19\x68\x56\x00\xbb\xc9\x08"
         "\x2a\xaf\x9b\xad\x42\xf3\x27\xe0\xa4\x11\x2b\x19\xae\x7b\xb2\x83"
         "\x3c\x55\x37\x94\xea\xee\x85\x0d\x5b\xc4\xf3\x89\xfb\x6d\x5a\x4e"
         "\x0e\x48\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===SpatangusChayma
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x53\x70\x61\x74\x61\x6e\x67\x75\x73\x43\x68"
         "\x61\x79\x6d\x61";
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
.*===pegologyscavenage
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x65\x67\x6f\x6c\x6f\x67\x79\x73\x63\x61"
         "\x76\x65\x6e\x61\x67\x65";
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
