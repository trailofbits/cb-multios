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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb4\x48\xc4\x57"
         "\x91\x63\xb6\x2d\x8c\xf2\xcb\x2b\xb9\x01\x00\x00\x95\x0c\x5c\x6a"
         "\x7e\x86\x0d\x00\x74\x42\xaa\x06\x68\x8d\x47\x96\x78\xce\x0b\x67"
         "\x3a\xe9\x5b\x78\x1c\x50\xc9\xf7\x57\xc6\x2e\x5e\x20\x5d\x3c\xad"
         "\x9e\xfe\xc4\xe7\xf3\xab\x93\x57\xf8\xe0\x10\x4b\x2a\x45\xfd\x9f"
         "\x15\x45\x57\xaa\xee\x5c\x83\x45\xbf\xc9\xda\xdf\x3d\xfc\x4e\x06"
         "\xaf\x68\x3e\x80\x19\x6d\xc9\xf2\xca\x9e\xd9\x99\x2b\x10\x4e\xff"
         "\x35\xdd\x38\x99\x89\x11\xf6\x65\xc8\xd1\x86\xc6\x7d\xb9\x15\xcc"
         "\x53\x84\x9c\x67\x8e\xb0\x1d\xd9\xac\x81\xfb\x17\x31\x60\xe5\x5f"
         "\x2e\x0b\x10\xa7\xff\x5a\x32\x00\x60\x6f\xb9\x18\x96\x5f\xfb\x38"
         "\xd0\xab\x42\x42\x9e\x85\x94\xcc\x16\xd5\xc1\xce\x99\x03\x9b\x72"
         "\x2a\x49\xc5\xeb\x36\xbe\x6f\xc2\x2b\x6a\xb4\x50\xbe\x1d\x49\xd6"
         "\x01\x81\x4b\x81\x50\x54\x12\x91\xf1\x5b\x69\x94\xc5\x04\xf3\xf0"
         "\xe0\x2d\x85\x1c\x29\x4a\xb4\x5c\xf9\xa7\xdd\x5f\x85\xee\xc9\x90"
         "\xe2\x15\xc1\xed\x71\xae\xaf\x6d\x2f\xcf\x08\x8b\x65\x72\x0d\xaa"
         "\x40\xbb\x93\x3b\x9a\x73\x99\x04\x13\xc3\x42\x9c\xe2\xe4\x5f\xef"
         "\x8b\xcd\x47\x90\x66\xb6\xda\x36\xa4\x96\xee\x49\x30\xf0\x92\xa5"
         "\x4d\xbe\x51\xca\xc0\x03\xd5\x8f\xb5\xfd\x65\x27\xf5\x32\x45\xfe"
         "\xc0\xf3\x71\x29\x8e\xd4\x0c\xa6\xcb\x50\xd1\x57\xee\x59\x9c\x84"
         "\x5a\x1f\x0f\x70\xbd\xe8\xa4\x20\x10\x96\xa7\x1e\xf4\xd8\x9d\xb0"
         "\x82\xdf\x0d\x0b\xcb\xf0\xcc\xb2\x90\x7b\x6a\xb1\xbc\x64\xc1\xf4"
         "\x66\x32\x58\xc9\x29\x6f\xdd\x0a\x3a\xd6\x7f\xda\x65\x0c\x85\x1e"
         "\x62\xe6\xe2\x7f\x7f\xdf\xcc\xae\x8d\x19\xd4\x0f\x47\xfd\xdd\x62"
         "\xb2\x82\x98\x35\xe1\x6c\x7d\xc0\xc1\xd7\xf5\xfe\x74\xf2\x0b\xdf"
         "\xec\xcc\x58\xe8\xa2\xd3\xfd\x92\xdf\x63\x3f\x72\xb0\x0c\x30\xca"
         "\x21\xdc\x7f\x40\x44\x86\xbd\x81\x76\xf9\xd9\xd7\x44\x6f\x70\x7e"
         "\x4b\x8b\xaa\x21\x93\xf2\x7b\xdc\x7a\xdc\x95\x82\x50\x5b\x3c\xbc"
         "\xe3\x7b\x30\xa1\x6e\xd2\xcb\xf7\x83\x6b\xdb\x8a\x69\x07\x97\xef"
         "\xfb\xa4\x4a\x14\x0f\xa4\xa2\xd8\xa5\x80\x47\x50\x89\xfd\x5a\x1f"
         "\x26\xa8\xb7\x3f\x4c\xe7\xed\x2e\x22\x1a\x0d\x00\x0d\x80\x7c\x59"
         "\x24\x7b\x70\x3b\xf2\x75\x25\x0b\xb8\x0f\x47\xb7\xd2\x70\xaf\x6d"
         "\x24\xce\x37\x5b\xa0\x99\xa0\x13\xeb\x48\x1f\x35\x7b\xa1\x82\x87"
         "\xbb\x1c\x35\xf5\x01\xff\x77\xf4\xbc\x4b\x91\x54\x13\xfd\x8a\xaa"
         "\x2d\x27\x10\x0f\xce\x60\x27\x12\xae\x19\x27\x01\x1a\x62\x32\x08"
         "\xcb\x14\x7c\x37\x1b\x37\x90\x40\x83\x4d\xeb\x5f\x28\x54\x1d\x1e"
         "\xa9\x12\x29\xa8\x12\x18\x66\xf4\x73\x24\x2b\x87\xef\xda\x96\x7f"
         "\xf5\x6f\xc4\x06\xed\x6e\x3d\xc7\x90\x21\xd7\xe5\x7c\x29\x97\xba"
         "\x10\x58\x69\x70\x09\xaf\x80\x61\xbb\x76\x64\xab\xe5\x80\x22\xc5"
         "\xe7\x87\xcf\xc4\xc2\x1d\x02\x90\x08\x21\x9e\x07\xfd\x13\xef\x53"
         "\xc7\x0d\xd6\x06\x34\xa8\x3b\x9b\x33\xa2\x35\xa1\x87\x55\x36\xf4"
         "\x54\x00\x00\xa5\x86\xdf\x66\xfa\x69\xe0\x0d\xd1\xd0\x81\x60\xbc"
         "\x11\x21\xb4\xf5\x1f\xa6\xbf\xdb\x13\x65\xd2\xde\xac\x17\x93\x95"
         "\xc3\x44\x03\xc3\x7c\x39\xe2\x5d\x35\x17\xf4\x2d\x34\x95\x0d\x68"
         "\xb8\x2c\x67\xb3\xca\x6f\x50\xb0\x48\xd6\x8c\xd9\x60\x00\x8c\xc4"
         "\x75\x68\x00\x26\x34\x82\xab\x70\xdc\xe2\x04\x97\xbf\x81\xc8\x51"
         "\x3e\x50\xbc\xd4\x96\x85\x00\x00\xff\x21\x86\x79\x9a\x5a\xcf\x51"
         "\x3f\x29\x88\x26\x53\x87\xb5\x32\x44\xcf\xfa\xcc\x79\x9e\x9f\xf8"
         "\x9b\x3f\xa2\x23\x3c\xbf\xd0\x0e\xd4\x8c\xd3\x1e\x24\x09\x18\x7a"
         "\xf4\xa5\x85\x63\x6d\xad\xf5\x82\xb1\xf7\xbb\x2f\xa9\x9a\x80\x01"
         "\xcc\x4b\x50\xca\x31\xee\xb0\x75\x2b\xef\x77\x7c\x4f\xa4\xf6\xc0"
         "\x3e\x0f\xf7\x19\xae\x7f\x9a\x44\x41\x3a\x0c\x05\xc5\x8f\x72\x45"
         "\x78\x00\x36\x4a\x01\x3c\x56\x9b\x5a\xd3\x10\xdc\xba\x30\xc2\x1e"
         "\x7f\xfe\xc4\xd1\xe1\xfe\xaf\x97\x25\xe1\x52\xee\xc1\xe6\x9a\x17"
         "\x9c\xa7\x76\x64\x2d\x4b\x37\x6e\xb8\x59\xf1\x9f\xdf\x6c\x18\x2c"
         "\xbb\x3a\x8d\xc6\xc8\x70\x99\xcf\x8c\xb2\xf3\x6c\xf8\x99\x77\x02"
         "\xae\x8d\x0e\xe2\x34\xcb\x3b\xea\x33\x3b\xe1\x9d\xad\xad\x49\x2a"
         "\xed\x77\x71\x3c\x3b\xd0\xc3\x6a\x4f\x63\xec\x2c\xeb\x03\x39\xd0"
         "\xe0\x57\x00\x35\xb2\x00\x00\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===lindengamy
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x69\x6e\x64\x65\x6e\x67\x61\x6d\x79";
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
.*===misproduceunthrilled
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6d\x69\x73\x70\x72\x6f\x64\x75\x63\x65\x75"
         "\x6e\x74\x68\x72\x69\x6c\x6c\x65\x64";
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
