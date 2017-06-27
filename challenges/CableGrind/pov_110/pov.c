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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4e\xd4\x14\xd3"
         "\x1e\x8d\xc0\x56\x1d\xa8\x15\xff\x78\x00\x00\x00\x71\xb4\xcd\x8a"
         "\x3f\x03\xdc\xe5\x0e\x9f\x8e\x3a\x5b\xb0\x31\xd9\xbb\x3e\x6e\x4d"
         "\xd8\x76\x94\x7a\xb0\x5c\x18\x95\x06\x20\x34\x6c\x68\x94\x6d\xf9"
         "\xc6\x40\xe1\x9e\x3a\xb5\x56\xea\x07\xf3\x3d\x01\x37\x74\x82\x45"
         "\x3d\x05\x1a\xdd\x3d\x82\xd0\xc5\xd3\x10\xf9\x4a\x2a\x29\xb6\x20"
         "\x76\xcf\x9e\xfc\x92\x21\xb5\x4b\x86\xfb\x4e\xce\x6f\x01\x8a\xa0"
         "\xc9\xc6\x8f\x00\xfb\x24\xfe\xf8\x62\x7c\xca\x0d\x44\xeb\xb2\x48"
         "\xb6\x7a\x29\xab\x2f\x60\xd6\xc3\x91\x38\x6b\x57\xa1\x48\x6e\x27"
         "\xa8\xc5\xe6\x28\xa1\xf1\x84\x9e\xe4\xf8\x53\xc8\x90\x4e\x87\x6e"
         "\x32\x6d\x80\xa6\x80\xad\x87\x30\x15\x67\x4d\x8c\x4d\x14\x0c\x26"
         "\x34\xba\xe8\xda\xbf\xf3\x20\x1a\x7f\x00\x14\xd2\x8d\xa6\x3b\xb0"
         "\x47\x5e\xe0\x84\xd4\x44\x59\x6f\x60\x9e\x7d\x8e\x4e\x5f\x0d\xf8"
         "\x96\x56\x80\xa5\x44\xf1\xaa\x7b\x6c\x52\x1b\x48\xe9\x23\x30\x96"
         "\x08\x15\xfa\x6a\xa9\xa2\xaa\x2b\x01\x7d\x89\x1b\xcc\xda\x39\x5a"
         "\xda\xd4\xd3\x8a\xad\x7e\x65\xfe\x26\xf9\x86\x5a\xd8\xfa\x33\x6c"
         "\xf8\x39\x6c\xed\x2e\xe3\x42\x26\x66\xe1\x67\x09\xd4\x96\x4b\xf1"
         "\x5b\xef\x45\x12\x2b\xd8\x6b\xe9\x0a\x1e\x9b\x05\xbe\xf9\x7d\x1b"
         "\xf6\xf7\x0d\x6c\x42\x94\x0a\xcc\x33\xee\x98\x60\x82\xe4\x69\x8c"
         "\xea\x56\xff\x55\x14\x4b\x36\x2d\xa5\xd1\x2d\xae\x7a\x6b\xf5\x2a"
         "\x3d\x09\x28\x45\x90\x32\x8b\x21\xcd\x92\x6e\xeb\x77\xc2\x40\x63"
         "\xee\x13\x62\x71\x85\xc6\xd2\xb4\xb9\x88\x91\xc0\x1d\xfd\x22\xa1"
         "\x30\x36\xfe\x7c\x7f\x0d\x8d\xcc\xa9\x63\x2c\x9a\x8e\xcb\x67\xc0"
         "\x11\x2f\x84\xdb\x98\xf4\x66\x7b\x40\xc3\x16\x30\xa7\x6f\x08\x79"
         "\xe9\xda\x19\xd9\x03\x66\x71\x2d\xf6\xf0\x11\x92\x0e\x9e\x36\x2d"
         "\x42\x85\x39\xc3\x50\x00\x8f\x0f\x35\x96\xe2\xf2\xc8\xe6\xdb\x63"
         "\x54\xa4\x19\x79\x7c\x73\xa1\x29\x53\x5e\xa2\xc8\x7d\x1c\x69\x96"
         "\x47\x95\x45\x24\xb0\x6e\xe3\xbc\xe6\x5b\x89\x5f\x8e\xb5\x36\x06"
         "\xc0\xad\x11\x9c\x58\x9d\x20\xe2\xbd\x3a\xe2\x35\xf1\xda\xf9\x27"
         "\xad\x37\x3a\x5e\x58\xdc\xfd\xb5\xc8\x32\xa8\xa4\x29\x93\x47\x6b"
         "\x9c\xb5\x12\x03\x41\x92\xfa\x70\x7d\x56\x0c\xc5\xd6\x45\xc9\xff"
         "\xd1\x75\xdb\x04\x28\x02\xf5\x47\x84\x91\x53\x7e\x9a\x54\x95\xaf"
         "\x21\x81\x72\x0c\x8d\x10\x60\xe3\x6a\xa9\xb7\x36\x54\x3d\x0f\xa8"
         "\x41\x3d\x51\x2a\xb1\x8f\x80\x6e\x66\x0f\x7c\xcc\x1b\xea\x14\x22"
         "\x41\x74\x83\x69\x60\x19\x67\x6e\x35\x50\xc4\x68\x1b\x66\x8a\x00"
         "\x25\x2c\x8d\x9d\xc3\x87\xe1\xae\x04\xf7\x25\x26\xe5\x93\xee\xc3"
         "\x5e\xcf\x54\x4f\x9a\xee\xab\xfc\x6b\x3c\xa8\xf8\xf5\x52\xf6\xcb"
         "\x9a\xc2\x7c\x47\x8f\xe4\x19\xb2\xb4\x34\xdf\x02\x88\xb4\x05\xb4"
         "\x82\x84\x4b\x0a\xd4\x6e\x14\xea\xa2\x2e\xa5\x6b\x52\xc9\xc1\x6e"
         "\xfe\x71\x7d\x5c\xa8\xb4\x0a\x8e\xef\x70\x0c\xbb\x8f\x3c\x4b\x03"
         "\xd8\x0e\x02\x8c\xf7\xd4\x78\x08\xe9\xf1\xad\x7e\x81\x4f\xe9\x78"
         "\x6f\xd2\xd1\xa6\x67\x4e\xf9\x0c\x7e\x12\xc3\x0c\x00\xdb\xd3\xd9"
         "\xc6\x0c\x0c\x9c\x31\x91\x64\x56\x21\x3d\x84\x2d\x2c\xe4\x15\xdf"
         "\xee\x68\x9f\x30\x3a\x56\x33\xb0\x18\x48\x04\x2a\x56\x33\x33\x78"
         "\x25\x42\x6c\xe6\xd6\xf9\x10\x1e\x08\x6c\x14\x62\x09\xbc\xee\x8f"
         "\xf5\xe9\x7b\x68\x87\x93\x0a\xfb\xef\xfd\x62\xae\xf8\x8c\xc9\x9c"
         "\xf7\x7b\xf7\x28\xd4\x16\x2f\x7e\xac\xaa\x32\x2f\x41\x83\x17\xcc"
         "\x3c\x7f\x9b\x03\x7f\x25\x49\xac\x7c\x95\xa0\xcb\x78\x0d\x79\xd2"
         "\xf3\x74\xa0\x7c\x05\x8e\x8c\x24\x6a\xd3\x84\x4e\x36\x4f\x5f\x33"
         "\x3e\x23\x64\x36\xf0\xc5\x87\x0e\x7e\x46\x3f\xd9\x22\xb1\x89\x3f"
         "\x43\x53\x50\xc9\x8d\x8e\xe8\xdf\xad\x45\x7f\xe2\x8b\x0c\xa2\xe4"
         "\x7b\x1b\x84\xeb\xbd\x73\x22\xcb\xdb\x71\xc2\x7a\xdd\x9a\xd1\xed"
         "\x83\xa5\xe7\x62\x9b\x68\x58\xce\xc0\xdd\x07\x60\x20\x20\x20\x20"
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
.*===plurifacialmicrographical
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x6c\x75\x72\x69\x66\x61\x63\x69\x61\x6c"
         "\x6d\x69\x63\x72\x6f\x67\x72\x61\x70\x68\x69\x63\x61\x6c";
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
.*===woodrowelshrievalty
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x77\x6f\x6f\x64\x72\x6f\x77\x65\x6c\x73\x68"
         "\x72\x69\x65\x76\x61\x6c\x74\x79";
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
