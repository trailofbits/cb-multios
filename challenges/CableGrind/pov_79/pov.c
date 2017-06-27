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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x51\x9b\x2f\x98"
         "\xe7\x0e\xf3\xee\x27\xc4\x32\x9d\xc7\x58\x85\xfc\x9c\x5c\xf1\xc4"
         "\xd2\x01\x00\x00\x83\x57\x28\xc8\x3a\xe9\xcb\xe5\x32\x52\x5f\x2e"
         "\xfe\xe0\x4d\xd4\x35\xda\x22\x12\x6c\xb0\xe8\xf2\xb5\x64\xd3\x1e"
         "\x73\x49\x19\x4a\xdd\x46\x68\xbc\x72\xa1\xf7\xac\x81\x76\x18\x9b"
         "\xae\xb5\x7f\x72\x97\x79\x96\x6f\x37\x37\x00\x87\xfe\x98\x97\xbc"
         "\x8e\x3e\xb0\xf2\x58\x3c\xaa\x3d\x02\x58\x01\xd1\xdc\x6c\x7a\xea"
         "\xa7\xf1\x5c\x8e\xf2\xd1\x3a\x8c\xbf\x3a\x9d\xfc\x27\x75\xd2\xe4"
         "\xb6\xb2\x4a\x61\xd8\x89\x4d\xa1\xab\xb9\xf0\x22\xda\x70\xfe\xc2"
         "\x95\x40\x4d\xc0\xd8\xd4\x4a\x2c\xb3\x59\xe6\xfa\xa9\x65\x7e\xfd"
         "\x2e\xde\x21\xb9\xf0\x96\x18\xf3\x98\x5a\x43\xed\x1e\x6a\x2f\x34"
         "\xe1\xd8\x6d\x94\x7b\x81\xdf\x51\xb0\x4b\x94\x89\x1d\x9c\x44\xdd"
         "\x22\xbf\x4c\x78\x37\x29\x74\x41\xf3\x9d\xa3\xf4\x3f\x0d\x54\x18"
         "\xae\xbd\x93\x45\x8e\xaf\x83\x94\x54\x86\x15\x2a\xa4\x76\xd5\xcf"
         "\x5e\xbd\xc8\xdb\x5e\x31\x40\xdd\xf2\x29\xaf\xdb\xe4\x10\xca\x80"
         "\xe4\x23\xb5\x20\xd3\x43\xe7\x13\xe9\x3e\xcd\xe3\xfa\xe3\xc1\x8e"
         "\xba\x1b\x13\xcf\x31\x79\xe4\xfc\xe9\x56\x0d\x21\x71\x9b\xe0\x18"
         "\xe5\x46\xd8\x73\x11\xb6\x19\x07\xfc\x12\xfb\x35\x62\x7f\xfa\x74"
         "\x46\x34\x5e\xf0\x0d\xe8\x5d\xcd\x92\xe5\xed\xc7\x38\x67\xed\xfb"
         "\x48\x96\xa9\xfd\x94\xdb\xdd\x49\xa5\x4f\x5c\x11\xf5\x4a\x7f\xa3"
         "\x0f\x8d\xe4\xf2\xfa\x1c\x70\x47\xf4\x75\x05\xd2\xb7\xee\x1f\xbe"
         "\x5e\xca\x60\xfb\x5b\xcc\xd8\x18\x82\x5d\xba\x12\xfb\xe7\xe8\xf5"
         "\x7e\x69\x48\x5a\x06\xd0\xc6\xc6\x98\x34\xd9\x70\xb4\x09\x0b\xb6"
         "\x2c\xee\x8a\xe9\x60\x8f\xa6\x03\xb7\x80\x1f\xf1\x6d\x1b\x0a\xa0"
         "\xf3\xb9\x9e\x20\xe5\xa9\xe7\xee\x6f\xf0\x2d\xc5\xd9\x59\x06\xab"
         "\x18\x42\x31\x44\x32\x99\x69\xa7\x0b\xe5\x12\xc6\x50\x69\xa3\x33"
         "\x11\x45\x1a\x38\xa8\x18\xd2\xa5\x20\xe3\x03\x7e\xf4\x8b\x14\x03"
         "\x88\x4c\x6d\x12\x6d\xe1\x12\x9b\xd7\x16\xac\xbd\x61\x9f\x24\x37"
         "\x00\x10\xe0\x22\x23\x7e\xbd\x6b\xf7\x37\x00\x37\x00\x8e\xd8\x51"
         "\xca\x5b\x18\x4b\x15\xf2\xb6\xc1\x45\xf1\x5d\xcc\x4b\x53\x0d\x2e"
         "\xc3\x4a\xdd\x39\x60\xd1\x07\xbf\xac\x4a\x85\x3a\x8d\x79\x76\x9c"
         "\x21\x11\xb0\x49\xb3\xec\x3e\x5e\xd7\x35\x8b\x38\xaa\xa0\xb8\x04"
         "\x8b\xd7\x32\x48\xbd\x81\xee\xaa\x9a\xbc\x73\x85\xa8\xf5\x59\xb0"
         "\x26\x3e\xe5\x02\xa2\x7d\x8a\xc8\x71\x36\xfd\x79\xdc\x36\xce\x3f"
         "\x95\x0b\xca\xb9\x37\x51\x0a\xd3\x22\x06\x50\xab\x1b\x68\x3e\x1a"
         "\xc1\x84\xef\x54\x0d\x40\x0f\xfd\x1c\xb6\x44\x02\x2b\x78\x13\xf7"
         "\x67\xa7\x0c\x09\x69\xb3\x84\x1e\x96\xc9\x8f\x3d\x7d\xa9\xd2\xaf"
         "\x6c\xbd\x26\x53\x08\x92\xb2\x50\xfc\x73\x94\x86\xa7\x60\x98\x0f"
         "\xd8\xc6\xe6\xa8\xb3\xeb\xe9\x51\xe3\x69\x69\x8e\x55\x07\x68\x2d"
         "\xc9\x9f\x41\xf5\x04\x3b\xc7\x85\x53\xf4\xa5\xb5\xe5\x15\x92\xe5"
         "\xa4\x0c\xd4\x12\x1b\x12\x57\x02\x8c\x66\x79\x7c\xda\x01\x1e\xd6"
         "\xa7\x5a\x16\x9d\xef\x99\x60\xb1\x4f\x36\x43\xd8\x66\xcd\xda\xa4"
         "\xab\x57\x95\xe8\x00\x51\x78\x76\xef\xd1\x20\x5f\xde\x7c\x45\xb0"
         "\x7b\xfd\x20\xa0\x5c\xd1\xe6\x1b\xc8\x7b\xce\x52\xcb\xc0\x7c\xf8"
         "\xe9\xd4\x33\x6b\xd7\x40\x98\xeb\xe4\x67\x43\xab\xcd\x34\xc5\xe5"
         "\x82\x6a\x82\x5d\xe9\x03\x15\x50\x05\x85\x45\x3b\x99\xbe\xe6\x17"
         "\x75\xff\xd7\x76\xc6\x19\x29\x45\x8d\x38\xf9\x75\x4f\x5f\xe8\x38"
         "\x9b\x29\x29\x4e\x37\xc4\xb9\xb7\x5a\x03\x98\xeb\xa8\xa6\x23\x38"
         "\xf4\x35\x85\x06\x4b\x74\x56\xab\xa2\xf6\xaa\x99\x73\xce\xd1\x84"
         "\x8d\x2c\xab\x01\x21\xd7\x6a\xb4\x37\xfd\x57\x80\x4d\x8a\xd1\xaa"
         "\xb3\xaa\x81\x1e\x56\x7c\x1f\x23\x2d\x6a\x77\xc6\xec\xe8\x58\x9c"
         "\xcc\x5b\xf8\x8b\x2c\x66\xb2\x16\xff\x37\x72\x93\xbd\xc1\xd3\x7a"
         "\x1f\x56\x52\xdb\x5a\x0d\xc3\xfe\x9c\x23\x3a\xf7\xb6\x42\x9f\x26"
         "\x28\xd5\x78\x34\x4a\x3a\x54\x51\x79\x4f\x49\x06\x24\x1a\x65\x14"
         "\x2d\x96\xd4\x53\x04\x7b\xc2\xae\xe4\x08\x07\xae\xf5\xbf\x1d\x5c"
         "\x63\xda\x2e\x0e\x8e\x75\xf2\x09\xf6\x03\x97\x02\x7f\x2a\xc9\xf0"
         "\x37\x59\x53\x39\x59\xc0\xa2\x47\x30\xa9\x78\x5d\x6a\xb8\x83\xcd"
         "\xb7\x1b\x44\xa5\xfa\x05\xac\x2d\x02\x41\x90\xa7\xeb\x64\xd8\x26"
         "\x8b\x0c\xa2\x3f\x50\xe3\x59\xc8\x52\x74\x11\x35\xa4\x96\x57\x00"
         "\x60\xf1\x5e\xcc\x02\xdb\xbd\x15\xbd\x63\xf6\xd8\x62\x49\x0c\xe8"
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
.*===usurperunplannedly
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x73\x75\x72\x70\x65\x72\x75\x6e\x70\x6c"
         "\x61\x6e\x6e\x65\x64\x6c\x79";
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
.*===cacuminalgastrohysterorrhaphy
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x61\x63\x75\x6d\x69\x6e\x61\x6c\x67\x61"
         "\x73\x74\x72\x6f\x68\x79\x73\x74\x65\x72\x6f\x72\x72\x68\x61\x70"
         "\x68\x79";
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
