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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x5e\x4d\x3c\x07"
         "\x63\x09\xbe\x22\x53\x12\x6c\x32\x94\x00\x00\x00\xb7\x8a\xc7\xfd"
         "\xed\x4c\x90\xd6\xac\x0a\xbc\xb4\x24\xed\x79\xd9\xc6\xa6\x6d\x9b"
         "\xce\x02\x92\xeb\x2b\x6a\x1e\xce\x2c\x1a\xe0\x20\xb1\x4b\x9c\x50"
         "\xce\x89\x8f\x9d\xdf\x04\xf2\x9e\xdb\x19\xbe\x50\x3b\xc7\x65\x11"
         "\x42\xce\x74\xfb\x17\x83\x67\x99\xb6\x6b\x70\x7c\xe1\x56\x11\x62"
         "\x29\x18\x1e\x3b\x45\x0a\x3d\x9a\xd8\x31\xaa\x32\xa5\xb9\x90\x74"
         "\x7a\x34\x9e\x41\xcc\xfe\xae\x31\xd3\xb8\x2b\x28\x2b\x97\x89\x5e"
         "\xda\xf0\xa4\x5f\x7a\x2e\x7a\x93\xf0\x4f\x15\xbf\x01\xfa\x5f\xde"
         "\xb7\x26\xa0\x77\xf8\x19\x06\xae\x38\x53\x00\xe8\x6f\x4d\xee\xd8"
         "\x80\xd0\xbd\xc8\x9b\x3e\x4c\xf4\x1b\x0e\x8c\xcf\x3f\xfe\x99\x6f"
         "\x38\xfa\x18\xdb\xa1\x92\x6c\x22\x30\x40\xab\x78\x96\x67\xea\x98"
         "\xa0\x40\x5e\xcf\xd0\x91\xbf\x14\x0a\x65\x6b\xb6\x9f\xab\xde\xad"
         "\x86\x0a\xe8\x59\x49\xa4\x05\xbf\xaf\xc6\x35\x02\x5c\x76\x84\x23"
         "\x0a\x43\xf5\x91\x47\x32\x43\x43\x43\x00\xfb\xe6\xb1\xa3\x60\xd7"
         "\xe4\x90\x13\xac\x17\xa3\x09\xbe\x6a\xcf\x8a\x9d\x9d\xa3\x7b\xeb"
         "\x7b\x6a\x74\xd0\x63\xb7\x04\x60\x2f\xf7\x28\xf2\xe2\xb2\x5d\xcf"
         "\x98\xf2\x57\x25\x96\x50\xcb\xa6\x8c\xf3\xf1\xd9\x99\x5b\xec\x1e"
         "\x3c\x39\x8f\x9a\x83\x75\x71\xdd\x68\x0b\xb3\x66\xd1\xea\xb8\x2e"
         "\x15\x1b\x3c\xab\xba\x84\x0f\x15\xcb\x9a\x78\x2c\x64\x3f\x25\x9a"
         "\xdd\x04\xa9\x30\x03\xc0\x8d\x58\xb7\xb4\xa3\x61\xfd\xae\x7d\x54"
         "\x03\x6f\x0d\x95\x75\xf6\x3b\xf3\x5e\x42\xb5\xf5\x1b\x58\x38\x98"
         "\x7e\x66\x41\x0a\xe0\x52\x3f\x1f\xfe\x80\x2a\x43\x00\xf0\x9b\xac"
         "\x9f\xb5\xa4\xc8\xd6\x13\xdb\xbc\x51\x6c\x94\x46\x19\xaf\x63\xe3"
         "\xce\xd7\x38\xdb\x49\x0a\x8b\xc2\x7f\xa1\x52\x45\xcb\x70\xc8\x93"
         "\xbe\x7a\xff\x34\x13\x45\x2f\x7b\x3f\xd8\xdb\x1c\x8d\x4a\x75\xb3"
         "\xeb\xa2\xd9\x8a\x95\x03\x96\x6e\xf7\x4a\xfc\xcc\x45\x95\xff\xb1"
         "\x79\xf7\x4c\x5f\xfd\x5f\xd8\xaa\x13\xe6\xb8\x47\x21\x34\x23\xe6"
         "\xae\x7b\x91\xa1\x80\x31\x79\x0b\xe5\xeb\xeb\xc8\xf7\x44\x8e\x9d"
         "\x08\xe2\x85\x04\x5a\x93\x1c\x26\xe1\xc2\x9b\x39\x35\x4f\xf5\x1d"
         "\x9c\xe4\x7e\xe9\xae\x91\x53\x52\x1e\x9e\xb3\x72\x6e\xed\x8a\x36"
         "\x06\x8e\x6d\x55\x4a\x18\xc8\x07\x2a\x2e\xae\xab\xdb\x7b\x51\xf0"
         "\x6a\x96\xc6\x06\xd5\x61\xb8\x82\x2c\x7b\x13\x56\x43\xed\x34\x92"
         "\xb1\x14\x26\xad\xa5\xa6\xfe\x62\x9b\xed\xec\x7f\x75\x1c\x9f\x8b"
         "\xc9\x6b\xc3\x65\x25\x8f\xf9\xdd\xa1\x20\x28\x4b\xf9\x68\x17\x3d"
         "\x8d\x86\x56\xad\x4f\xac\xc9\xc5\xfa\x19\x3e\xa5\x1e\x03\xca\x83"
         "\x86\x7b\xbb\xd3\xaf\xeb\x0f\x9b\xf1\x8d\xfe\x3d\x90\x2d\x33\x5c"
         "\xc0\x63\xdc\xef\x53\x30\x8a\xe9\x50\x4d\xd8\xe7\x05\x81\x85\xf1"
         "\xd2\x2e\x1c\x2c\x41\xb1\x2e\xf7\x84\x69\x85\xec\x1d\x23\x35\x3a"
         "\x8b\x83\x0b\x1b\x88\x4a\x30\xd4\x30\x50\xc6\x1b\xcb\x4d\x5a\x92"
         "\x05\x1d\x0f\xe2\x47\x44\x7a\xdb\x37\xa6\xde\x6c\xcb\x10\xa4\x83"
         "\x7b\xae\x41\x93\x81\xf2\x46\x01\xf4\x00\xff\x75\xf3\x43\x9b\x5c"
         "\xd2\xc4\x0d\x0f\x6d\xa1\x99\x7a\x5d\x25\x15\xf9\xcd\xd6\xee\xd8"
         "\x15\xae\xd9\x00\xd8\x12\xf7\x3c\xb3\x30\x2b\x20\x2d\x88\xcd\x59"
         "\xe3\x67\x36\x4c\x5c\x22\xbd\x46\x8e\x7f\x71\x3c\xc3\x7e\xc3\x56"
         "\x59\x88\x2f\x36\x5f\xcd\xc5\x6e\x4d\x64\x17\x86\x80\x9a\x76\xcb"
         "\x5d\xf2\xea\xcd\x30\x97\x78\xf4\x24\x64\x1e\xc4\xd1\xb2\xf2\x63"
         "\xd7\x70\x84\xf6\x94\xfa\x4b\xc5\xc4\x35\x0e\x22\x59\x90\xa1\x38"
         "\x9f\x8c\x0b\x07\xf6\x3e\x97\x3a\xd9\x73\x43\xa5\xfa\x42\xc1\x1f"
         "\x64\x0f\x69\xe4\xff\x83\x6e\xf2\xc8\x1e\x1c\x4d\xa7\xee\xad\x58"
         "\xba\x48\xa5\x54\x15\x2f\x78\xb4\xf0\x78\x5d\x18\x84\x38\x1c\x04"
         "\xac\x82\xa2\x12\xa9\x37\xaf\xff\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===sheepkeepingfeedman
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x68\x65\x65\x70\x6b\x65\x65\x70\x69\x6e"
         "\x67\x66\x65\x65\x64\x6d\x61\x6e";
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
.*===amlipyrexic
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x6d\x6c\x69\x70\x79\x72\x65\x78\x69\x63";
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
