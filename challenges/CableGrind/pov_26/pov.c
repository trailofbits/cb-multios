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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xcc\x25\x0c\xf9"
         "\x83\x46\x19\xc0\x71\x5d\x5d\xc0\x17\x8d\x19\x32\x6f\xff\x4a\x82"
         "\x7a\x00\x00\x00\x67\xd8\xcf\xa8\xff\xb4\x4b\xb3\x39\x15\x27\x50"
         "\xc5\xa4\x6f\x16\x57\x04\x87\xf9\x05\x00\xce\x8a\x81\xcc\x34\x6f"
         "\x94\x28\x6d\x53\xaf\x3f\x1c\x11\xcb\xd1\x6f\xf7\xc6\xeb\x05\x0d"
         "\x5b\x4e\x23\x45\xfd\xef\xee\x05\x74\x0f\x29\x94\x6b\xc9\xe4\xa1"
         "\x00\x7d\x17\x75\xc5\xb5\x0e\x62\xd1\x6e\x37\xce\x83\x0f\x53\xd4"
         "\x20\x29\xf3\x86\xea\x56\x6c\x00\x85\x62\x00\x54\x34\x6f\xbc\x4d"
         "\x19\xb4\xaf\xd7\xbf\x07\x38\x45\xda\xfe\x2d\xc1\xaa\x00\x48\xc2"
         "\xa5\xb1\x2d\x65\xc8\x8a\x64\xd0\x13\xb6\xe4\x96\x97\x23\x95\x0f"
         "\x01\x16\x96\xa7\xe6\xa4\xee\x25\x76\xd5\x19\xb6\xe0\x48\x5c\x5c"
         "\x83\xfc\x64\xe6\x36\xb6\xd6\x70\x05\x2b\xcd\x8b\xef\xf7\x94\xa6"
         "\xec\x3e\x45\x96\x9b\x10\x1c\x36\x70\xbf\x88\xf4\x6c\x73\xac\x8e"
         "\xb9\xfd\x47\x3a\x53\x93\x71\xe1\x59\x59\xea\xb3\xac\x5b\x69\x0d"
         "\xff\x9f\x2a\xd0\x13\x82\xd3\x2c\x13\xb3\xa1\xb3\xd0\xd4\xca\x54"
         "\x45\x27\x87\xc4\x62\xa3\x5d\x27\x3c\x41\x1f\x66\x9f\x5d\x20\x39"
         "\xd6\x69\xc8\xb7\x2c\x3c\x56\xdf\x5b\x7c\x86\x33\xaf\x4f\xec\x6f"
         "\x6c\x63\x64\x1d\x0d\xe9\x98\x79\x46\x91\xf8\x8e\x03\x29\xc4\x30"
         "\x55\x78\x78\xcb\x32\xff\x59\x86\xc8\xf7\x29\x2c\x15\xdb\x83\x71"
         "\x90\xff\x94\x03\x17\x6d\x55\x2a\xc1\xeb\x26\x4f\x68\x4e\x57\x7b"
         "\x9f\xc9\x34\xd7\xa6\x3d\x95\x64\x52\xce\xf1\x0b\x6b\x9a\x57\x4d"
         "\x8b\x8c\x30\xbe\xb8\x29\xfc\xdd\xc4\x9f\x9f\x86\x16\xca\xc6\xe3"
         "\x49\xa9\xa9\x94\xf6\x8d\x19\x89\x47\xe8\x31\x8f\x18\x02\xf1\xe5"
         "\xd7\xaf\xb1\x3f\x16\xa3\x3d\x2c\x53\xd6\xf9\xd2\xe9\xe3\xbb\x67"
         "\x93\xc0\x2a\x0e\x57\xbf\x1c\x83\xa6\x7c\x41\x62\x3a\x85\x4f\x56"
         "\x8d\x52\x1c\x02\x2a\x2d\xc1\x1f\xe3\x99\x3b\xd3\xe2\xc2\x3c\xde"
         "\xd5\x09\x0d\xf8\xfd\x9d\x5e\x24\xd4\x19\x01\xc8\xef\xc2\xb4\xb4"
         "\xa4\x7e\x86\x45\xa0\x2b\x62\xa9\x8b\x98\xb2\x94\x3f\x59\x98\x5d"
         "\xfe\xd3\x75\x4d\x23\xe1\x7a\x1e\x77\x8e\x5a\x5e\x88\x50\x1d\xbf"
         "\xfb\x43\xc7\x6e\x61\xe0\x66\x7b\x32\xb4\xf6\x3a\xdf\xfe\x7e\xa1"
         "\x90\x64\xe6\xde\x04\x9a\x0a\xd3\xcf\xe2\xe5\x44\x12\x71\xdb\xda"
         "\xe9\xad\xf7\xd9\x65\x33\x24\xac\xed\xfb\x2e\x85\x61\x6e\xeb\xab"
         "\xfd\xd9\x05\x91\xe6\x03\x98\x60\x74\x1d\xa9\xdb\xed\x68\x4f\x54"
         "\x7c\x3a\x3b\x2a\xd8\x42\x4e\x8c\x6f\xcd\xe8\x72\x24\xc0\x64\x0e"
         "\x23\xb9\xc5\xa0\x63\x16\xd5\x0f\x0c\x0f\xb1\x2d\x9a\x79\x03\x12"
         "\x8a\x88\x99\xfe\x35\x59\xbd\x46\x1a\x42\x3b\x08\x61\x6d\x3f\x7f"
         "\x82\x3c\x5c\xba\xbf\xd3\x0c\xaf\xab\xe7\x05\xb1\xea\x03\xbd\x94"
         "\xf2\x42\x49\x70\xdb\x88\x44\xfc\x1f\x95\x08\xf0\x05\xf8\x99\x03"
         "\x08\x9b\x29\x33\xfa\x87\x8d\xd3\xee\x5e\xcc\x07\x3c\x65\x72\xbc"
         "\x2d\x36\xa0\xe9\x2a\x7c\xf3\xea\x2f\x64\x30\xcc\xc1\x1c\x9b\xd4"
         "\x41\x1e\x00\xc9\xd8\x5b\xfe\xd2\x0b\x1e\x1e\x1e\x00\x2c\x37\xec"
         "\x43\x83\x5e\x3d\x35\x6b\x35\xe2\x12\x02\x31\xc0\x43\x16\xdb\x6e"
         "\xb2\xae\x9f\x0c\x3a\x1e\x00\x1e\x00\x1e\x76\x08\xa6\x0f\xf0\x47"
         "\x1c\x9b\x75\x95\xcb\x68\x1e\x1e\x00\x68\x91\x15\x9e\x35\xdb\x46"
         "\x54\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===Tantalussubcavity
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x54\x61\x6e\x74\x61\x6c\x75\x73\x73\x75\x62"
         "\x63\x61\x76\x69\x74\x79";
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
.*===unvoiceCamacan
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x76\x6f\x69\x63\x65\x43\x61\x6d\x61"
         "\x63\x61\x6e";
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
