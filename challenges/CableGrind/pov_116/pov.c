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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xe7\x87\x0d\x73"
         "\xe7\x9b\x28\x8a\x9c\x6e\xd7\xdb\x8c\x00\x00\x00\xd6\x07\x0f\x4b"
         "\xea\xd6\x5b\x10\x79\x11\x07\xe2\x80\xcb\x36\x76\xae\x9a\xb9\x31"
         "\x84\x02\xd5\xd1\x81\x1f\xdd\xe7\x82\x44\x17\x8d\x19\x43\xf0\xd1"
         "\x1b\x23\xc1\xec\x38\x02\xcf\xf2\x24\xe1\x8e\x67\xbf\x19\xe3\xd1"
         "\x1b\xb4\x5e\x84\xa3\x99\x76\xe4\x3c\x7e\x26\x72\x7d\x85\x17\xcd"
         "\xe8\x54\xb1\x54\x8c\x13\xca\xf5\xa6\x21\x29\xf2\x1d\x4f\x6d\x6f"
         "\xc5\xc9\x4b\xd2\xf1\x0c\x8c\xb5\x2f\xb7\x42\xcb\x76\x44\x24\x00"
         "\x90\x76\x79\xb4\x30\x85\x8d\x23\x03\x24\x94\xdb\x4f\xe1\x42\xfe"
         "\xf0\x6a\x78\x4a\xc1\x14\x24\x00\x60\x92\x9b\xcb\x13\x9d\x1e\xf0"
         "\x79\xef\xaf\xb7\xb2\xdc\xc1\x87\x34\x2b\x87\xd6\x60\xf4\x57\xbb"
         "\xab\xdb\x9c\x7f\x00\x6b\x46\x98\x44\xe5\xc2\x5d\xda\x50\x52\x45"
         "\xdc\x0e\x23\xbd\x53\xa1\xc3\xf1\xcd\x9f\x1e\x20\x84\x34\xa3\x8c"
         "\x4b\xe6\xcc\xee\x89\xeb\x1d\x85\xfe\x5a\x78\x1b\x8e\x67\x5a\xb9"
         "\xe3\x4c\x1c\x56\xba\x47\x57\x63\x96\xb7\xf0\xc9\x05\xb6\x1e\x29"
         "\xd5\x30\xc2\x12\xf3\x7d\xd5\x5e\x23\xda\x5c\x21\xe6\x36\x6e\x39"
         "\x34\x3d\x84\x6a\x45\x07\xd7\x95\x98\x49\x88\xa0\xd7\x1f\x67\x32"
         "\xa5\xf6\xde\x64\xb5\x34\xb8\x24\xca\xc3\xe9\x4c\x5a\x64\x8c\x3e"
         "\xe8\x19\xa8\x34\xd7\xd7\xbe\x43\x54\xf9\x97\xc2\x74\xf4\x16\x57"
         "\x68\xb6\x7b\xe1\x55\x15\x7c\x83\xee\xf3\x55\x57\x03\xb5\x4b\x7b"
         "\xdc\x64\xf0\xc1\x60\x90\xc8\x88\xc3\xc3\x12\x1b\xf1\xb2\xfa\xea"
         "\x5e\x99\x1c\x5e\x3c\x38\x84\xb1\x32\x6f\x5f\x30\xfc\xef\x96\x13"
         "\xe8\x91\x9c\x7b\x63\x32\xe1\xab\x85\x24\x00\xb0\xa6\x8f\x7d\x7d"
         "\x78\x73\xe7\x34\x41\x97\x24\x77\x55\x34\xdc\xdb\xc4\x89\x7b\xb7"
         "\x18\x38\xf1\x41\xb1\x62\x67\xb1\xe2\x05\x56\x89\x59\x41\x88\xaa"
         "\x34\x8b\x9d\xbe\x6b\x08\xaa\x94\xc4\xb2\x8a\xaf\x1d\xdb\xe2\xe4"
         "\x1c\x07\x89\x05\x5d\x98\xf5\xb8\xfa\x2c\x88\x1f\x1d\x6a\x65\x75"
         "\xf6\xee\x90\x4a\xb1\x13\x40\x24\x6a\x7b\x36\xc8\x52\x3c\xef\x33"
         "\xb2\xc2\x8a\x85\x9c\xf8\x6c\x88\x71\x29\x90\x4a\xe1\x11\xd3\xb0"
         "\x99\x43\x52\x3d\x2a\x8c\x00\x9e\xa1\x1d\x71\x27\x9f\xeb\x03\x19"
         "\xb9\x1c\x23\x05\x26\x5c\x13\xe9\x1b\xcf\x6b\xb6\x3c\x3d\x6a\x4a"
         "\xf1\xfa\xf9\x61\x4b\xe3\x5d\x61\x98\xc6\x5f\xd4\x2a\xf1\xf4\xb8"
         "\xad\x8f\x60\x16\x08\x8f\x28\xb4\x2f\x3b\x79\xaa\x80\x27\x31\xb1"
         "\xdd\x0b\x35\xc0\x2f\xe9\x70\xbc\xf5\x5b\x25\x40\x78\x55\xa0\xa8"
         "\xe4\xa8\x69\xe6\x41\xdd\x70\x9f\xca\x26\x24\x4e\x36\x8d\xb0\x49"
         "\x55\xe0\x3c\xfa\x58\xe9\xab\x2d\x9e\x42\x0b\x9f\xe6\x66\x3d\x01"
         "\xa6\x38\x86\x80\x6e\xfa\xf4\x3c\xf2\x1d\x3a\x64\xb7\x3d\xed\xf4"
         "\xd3\x69\xe0\xc3\xd1\x32\xb3\x75\xa6\x5e\xca\x6d\x35\xfe\x81\x79"
         "\x31\xc9\x74\x9c\x1e\x56\xe6\x72\x88\x90\x24\x00\x2b\xd5\xe1\x3c"
         "\xb2\x1d\x40\x51\x78\x24\xc7\x29\x4e\x7e\x5e\xb6\x03\xc7\x4a\xea"
         "\x7e\x6a\x24\x00\x18\x37\x0e\xfe\x77\x23\x00\xf3\x0b\xc7\xd0\x16"
         "\x4e\xb2\xba\x6e\xe5\x7b\x9c\x0f\x51\x7a\x9d\x36\x3a\x1a\xa2\x4d"
         "\x47\xc1\x25\x0e\x85\x11\x81\xf5\x87\x99\x2b\x0b\xde\x03\x48\x75"
         "\x68\x25\xe3\xaf\xca\x3b\x49\x28\x87\xed\xdc\xf7\xba\xfa\xf0\x21"
         "\x6c\xd9\xc5\x79\x0e\xb7\x39\x03\xb3\x11\x8c\xa0\x57\x4c\x43\x31"
         "\x36\x12\x4d\xfb\xc7\x9d\xdb\x35\x81\x87\x08\x79\x38\x9f\xdf\x23"
         "\x33\xd6\xd9\x84\xfa\xcb\x16\xe5\xd1\xbe\x67\x3f\x93\xa0\xa1\xea"
         "\x71\x76\x39\x22\x19\x6a\xb1\xa2\xdb\xe1\x55\x10\x83\x19\x21\x1d"
         "\x4d\xf0\x60\x92\xf2\x53\x1f\xde\x2c\x5e\xe9\xa0\x89\x5f\xf2\x8a"
         "\x02\x39\x11\x73\xf8\x68\x5f\xcd\x8b\xc7\x32\xb6\xe1\x91\x01\xb9"
         "\xd3\x3c\xd4\x68\x80\xd3\xa4\xf7\xe7\x3f\xf1\x81\x21\x38\xe8\x15"
         "\xca\xc5\xb6\xbf\xc8\x68\xab\xe9\x66\x7e\x1f\xd8\xe0\x00\xc7\xe6"
         "\xe3\x47\xe2\x4b\x45\x90\xd8\xd9\x81\xd0\x2f\x2a\xb7\x15\xb4\x90"
         "\xdb\xfa\x97\x2b\xb4\xd7\xeb\xfb\x33\xb4\xf7\x59\x6c\xb6\x58\xa6"
         "\x7d\xa4\x12\xf6\x16\xf9\x5c\xfb\x65\x53\x49\x7d\xd3\xb2\xac\x14"
         "\x36\x97\x2e\xaa\x09\xa7\xda\x39\x65\x85\x34\x2d\x56\x9d\x5b\x0d"
         "\x24\x00\x8f\x34\xf1\x58\x20\x87\xf3\x5d\xfd\x47\xce\x24\xbf\xb2"
         "\xea\x94\x3b\x7c\x0a\xcf\x12\x50\x12\x7b\x35\x7f\x22\xc3\x65\x79"
         "\x34\xe9\x80\x8f\xd0\x0a\x08\x2b\x2c\x69\x65\xf9\x23\x6e\x43\xfa"
         "\x41\x22\xe2\x93\x0d\x0b\x58\xd5\x32\x90\x15\x83\x69\x15\x76\x01"
         "\xb7\xd6\x86\xf1\xc8\x60\x1f\xac\xaa\x4a\xcc\x1f\x14\x39\x24\x67"
         "\x86\x6d\x6c\x51\x3d\xe6\xd6\x9a\x59\x2a\xf6\x2a\xc7\x48\x13\xf7"
         "\xc0\xfa\x7c\x84\x54\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===superestablishmentsuccor
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x75\x70\x65\x72\x65\x73\x74\x61\x62\x6c"
         "\x69\x73\x68\x6d\x65\x6e\x74\x73\x75\x63\x63\x6f\x72";
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
.*===superestablishmentsuccor
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x75\x70\x65\x72\x65\x73\x74\x61\x62\x6c"
         "\x69\x73\x68\x6d\x65\x6e\x74\x73\x75\x63\x63\x6f\x72";
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
