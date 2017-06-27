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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xaa\xb4\x6b\x06"
         "\x26\x86\x8e\x7f\xbb\x59\xf6\x7b\x31\x01\x00\x00\x20\x07\x52\x99"
         "\x9c\xd8\x06\x1c\x9e\x99\x16\xd1\x5b\xd3\x83\xf9\xad\x2a\xea\xc0"
         "\xcf\x07\x78\x0b\xb7\x67\x96\x7e\x63\xb5\xd6\xc7\xbb\x55\xf0\x09"
         "\xa2\x55\xd6\xe9\x27\xfe\x3a\xf5\x20\x05\xdd\xdf\x98\xf8\x46\xac"
         "\xc9\xb3\x2b\x6b\x8a\xe5\x9c\xf6\x07\x72\x40\xf8\x68\xe7\x08\x9a"
         "\x67\x19\xa4\xdd\x07\x9d\xc0\x19\xeb\x2d\x2a\x8e\x32\x44\xd0\x7f"
         "\xfe\xbe\xa9\x03\x96\x12\x7a\x31\x3c\x46\x79\xaf\x22\xf7\x10\x14"
         "\xcd\x4f\x20\xaa\x16\x7d\x48\x8e\x4c\xbb\xdf\x8b\x8d\x71\xe4\xa5"
         "\xa6\xab\x07\x1b\xe0\x0f\x59\x41\x9c\x80\xcd\xe5\x5a\x7d\x10\xb4"
         "\x9f\xd8\x56\x30\x03\xa5\xc0\x23\xa7\xcb\xc4\x03\xbe\x1d\x43\x8b"
         "\x7d\xc0\x8a\x26\x9f\x85\xe5\x85\xb8\x91\xec\x65\x0b\xad\x7d\x0e"
         "\x27\x91\xde\xf3\x38\xbe\xff\xbc\x16\xca\x5b\xaa\xc1\x4d\xd1\xfd"
         "\x7f\xb2\x92\x81\xdf\x58\xd3\xeb\x7d\xe1\xb2\x09\x08\xbe\x3d\xc5"
         "\xa3\xf7\x36\x6d\x7c\x32\x1c\xa1\x46\x0b\x08\x82\x55\x0b\x1c\xfa"
         "\x23\x84\xd4\x9b\x9a\xa1\xc0\xb0\x5a\xb3\x57\x87\xc5\xa2\x50\xa4"
         "\xbe\x99\x0b\xf9\xff\x90\xb4\x9a\xb2\x07\x0d\x4a\x75\x7c\xd5\xbe"
         "\x09\xce\x9d\xd0\xcd\x74\x70\x6d\x57\xb0\x5d\xb0\x68\xc8\x37\x58"
         "\xd7\x9f\xc6\x90\x80\x28\x25\x83\xf3\x72\xfc\x95\x82\x42\x47\x5c"
         "\xba\x1e\x3e\x87\x2a\xcf\x3c\xaf\xee\xc1\x1b\x40\x83\x95\xeb\xf8"
         "\x5c\x31\x73\x58\xd2\x69\xe6\xa1\xeb\x4f\x72\xda\x23\x0e\x50\x87"
         "\x4b\xb4\x37\x28\xc1\x8e\x29\xb7\x08\xbb\xf6\xc7\xea\x4d\x09\xcf"
         "\x59\xb4\xa6\xa8\xe9\x0d\x4e\x46\xd0\x70\x53\x7a\x5d\x19\x78\xa1"
         "\x29\x3c\x18\x19\x9a\x3d\x44\x89\x8c\x6c\x1c\x3b\x46\xee\x9b\x41"
         "\xfd\x87\x47\x90\x57\x39\xa4\xd5\xb5\x39\xe3\x53\x73\xb5\x16\x31"
         "\x75\x53\x88\x2d\xe9\xe5\x34\xac\xaa\x2e\x08\xd9\x80\x69\x18\x1b"
         "\xff\x19\x8c\xb1\x89\x43\x05\x9f\x67\x00\x59\xa3\x55\xca\x10\xa8"
         "\xcf\x23\x92\x7a\xfd\x80\xb1\x0f\x55\xbe\xeb\xa4\xba\x9a\x74\x1c"
         "\xeb\x76\xbc\x6c\x2b\xf2\x66\x51\x1b\x35\x4f\xf5\x03\x4d\x53\xda"
         "\x76\x9b\xe3\x0f\x09\x4b\xfd\x92\x6c\xb9\x26\xa3\xd5\x5f\x0c\x87"
         "\xa9\xa0\x5d\xa6\x2f\x32\x26\xf8\x58\xcf\x93\x1a\x1f\x6e\xf7\xb2"
         "\xd1\xa7\x85\x86\xce\xf5\xdd\x67\x20\x55\xd0\x35\xaf\x99\xae\x92"
         "\xa6\xd7\x3e\xe1\x6f\x54\xab\xc1\x8f\x63\xe1\xe8\x21\xf3\xe4\x81"
         "\x74\xb4\x36\xbe\x5c\x6b\x02\x96\xeb\x54\x70\xf6\x1e\xf7\x6f\xaa"
         "\xc9\xda\x08\x2e\x50\xae\xc9\xf0\x48\x32\x10\x6a\x29\x1e\x3d\xcf"
         "\x33\x30\x46\x6e\x1e\x19\x1d\x28\x78\x35\x9a\xfd\x90\xfb\x43\xe6"
         "\x7d\xc0\xd3\xb7\x28\xb2\x0f\x96\x68\x29\xd4\x89\xef\x42\x91\x22"
         "\xcd\x3a\x5f\x00\xaa\xd2\xe5\x8f\x91\x05\xab\xfc\x69\x56\x3d\x99"
         "\x8f\x46\x88\xd6\x78\xd1\x51\x50\xf1\x70\xe8\xfa\xb9\x06\x58\xc1"
         "\x89\x46\x32\xab\xd5\x01\x29\xff\xec\x2d\x68\x08\x23\xb2\xcb\x61"
         "\x1a\x64\x5f\xfd\xcf\xba\xb7\x91\xa3\xc2\x48\x13\x87\xdf\xf0\x0a"
         "\xb4\x8e\xfb\x00\x4b\x0d\x42\xa0\xca\x64\x6d\x2c\x8f\x2d\x3d\x76"
         "\x03\x8b\x5d\x94\xd9\xa0\x35\x63\xc4\x7d\xfe\xa0\xf6\x7a\x53\x05"
         "\xdd\xb4\x38\x1e\x88\xca\x63\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===symptosissubcorneous
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x79\x6d\x70\x74\x6f\x73\x69\x73\x73\x75"
         "\x62\x63\x6f\x72\x6e\x65\x6f\x75\x73";
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
.*===cesserreichspfennig
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x65\x73\x73\x65\x72\x72\x65\x69\x63\x68"
         "\x73\x70\x66\x65\x6e\x6e\x69\x67";
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
