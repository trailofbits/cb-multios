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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x1b\x52\x20\x96"
         "\xb0\x7f\x74\x89\xc3\x79\x79\x9a\x62\x01\x00\x00\x31\xd6\xc0\x07"
         "\xfe\x68\x8a\x71\xdc\x75\xae\x89\xe7\x69\x84\xdd\x50\x4c\x19\x57"
         "\x0b\x90\x6b\x77\x29\x30\x4e\xb0\x54\xd2\x5c\xc9\x41\xe8\x4a\xc1"
         "\x33\x0f\x90\x51\x5f\xd7\x40\x36\xed\xa9\x46\x4f\x08\x18\xe4\xec"
         "\x4f\xab\xab\x0a\x8e\x10\x84\x15\x54\x1c\xe8\xe8\xc7\x6e\xfa\xae"
         "\x44\xb0\x71\xc5\x7a\x90\xd9\xe6\x3c\x61\x23\x67\x2d\x06\x01\xf8"
         "\x8d\x44\x8b\x34\x35\x6f\xbb\x57\xf0\xd6\xb3\xa6\x6b\xb1\x34\x22"
         "\x7b\xe7\x89\xe3\xc8\x95\x3e\x96\x86\xc6\xe5\x45\x9a\xae\x90\x94"
         "\x33\x35\xbb\x45\x06\x00\xbe\x71\xfd\x30\x35\x02\x2d\x46\x70\x1e"
         "\x68\x57\xa2\x37\xdc\x19\x6b\xfa\xdc\x0d\xe6\xcc\x2a\xe6\x1d\xb7"
         "\xa5\x65\xba\x16\xcf\x82\x69\x79\x6b\xd9\xa7\x46\xdb\x4b\x67\xee"
         "\x45\x52\xdf\xcb\x46\x00\x84\x28\xe6\x92\x99\xe3\xb6\x62\xfe\x7c"
         "\x2c\x5e\xa0\xc6\x03\x27\x52\xf0\xee\xb6\x07\x6c\x75\xa7\x74\x86"
         "\x10\x1e\x0d\x55\x53\xaf\x82\xc6\x32\x56\xf5\xe8\xe3\x2a\x5a\x12"
         "\x9e\x8b\x5f\xc5\xf5\xb1\x6e\x2c\xf3\xb9\x03\xfd\xda\x8e\x34\x2f"
         "\x23\x1c\xfd\xe5\x73\x61\xa6\x48\x92\xf1\x82\xde\x92\x8c\xe6\x4d"
         "\x5b\xad\x37\x75\x1c\x00\x50\xa4\xd4\x44\xdb\xff\x3e\x16\x29\xce"
         "\x5a\x38\xef\x36\xd2\xf7\x84\x3c\x58\x3d\xba\xf6\x87\x39\x8d\xa2"
         "\x05\x8a\x30\xf6\x59\xec\xbe\x4f\x94\x16\x61\xcb\xee\xef\xcc\xc7"
         "\xfc\xac\x80\xb1\x8f\xcf\xa3\x99\x75\x19\x4b\x8f\xc6\x9c\xa1\x27"
         "\xd0\xc7\x4b\x3e\x77\x50\xa8\x60\x1d\xbc\x30\x79\xc8\xf7\x50\x3b"
         "\x8d\x86\xd1\xab\xe0\xcf\xd6\x87\x6e\x19\x23\x1a\x9d\x1e\x01\x20"
         "\xf0\xd3\x35\x06\xb8\x88\xff\x15\x8f\xfd\x06\xf7\x2a\x3e\x34\x91"
         "\x29\xac\x7d\x11\x8b\xf9\x6b\xaa\x14\x3e\x18\x08\xe5\x73\x8d\x92"
         "\xe1\x26\x5e\x38\x93\xee\x98\x0e\x03\xc7\x71\xdc\xa7\xeb\x08\x35"
         "\x15\x63\x4e\x82\x8d\x7b\xb4\x88\x6c\xe8\xcc\x52\xce\x4d\x90\xe5"
         "\x52\x01\x55\x93\xb1\x0c\x51\xa7\xd6\x86\x3a\xe6\x5f\xab\xf0\x45"
         "\x7a\xa9\x38\xab\x70\xbb\x94\x47\xcb\x68\xa9\x52\x3d\x90\x27\xd8"
         "\xf7\xbd\x32\x53\x37\xc5\x89\xae\x1d\x90\x06\x6d\xfe\xcf\xb7\x96"
         "\x04\x47\x10\x71\xac\x54\x00\xd3\x4c\xb2\x70\x63\x0a\xb9\x84\xad"
         "\xdf\xab\xf9\x7c\x49\x62\x86\x16\x3d\x94\x47\xec\xe3\x99\xa4\xc3"
         "\x77\x31\x37\xbf\x46\x1f\x9f\xf2\x65\xd4\x0e\xd7\x38\xd9\x1c\xc5"
         "\x46\x86\x0f\xc1\x71\x80\x78\x27\xf0\x6f\x50\xc3\x33\x1c\x91\x65"
         "\xf0\x11\x47\xec\xf6\x6d\x81\x8f\x2c\xb6\x20\xf0\x35\x70\x92\x65"
         "\xe4\xc0\x1f\xf2\x7d\xf4\xaf\xb6\xc7\x40\x72\x9f\x76\x27\xb5\x16"
         "\xdd\xc0\x9b\x70\x7c\x2f\xc7\x74\x26\xaa\x0a\xf6\xbb\x24\xac\x0b"
         "\x8c\x6f\x0b\xaa\xe7\xf2\xf2\xd0\x1e\xfc\x91\xbf\x2d\xc3\x59\x3d"
         "\x98\x76\x89\x24\x66\x86\x08\xef\x99\xb9\x80\xe9\xf8\x3d\xc9\x52"
         "\x95\xc0\x55\xf6\x65\xf8\x27\xb7\xc1\x5e\x04\x0f\xce\x98\x83\xfd"
         "\xde\xe1\x65\xd0\x5c\x23\xb3\x72\x57\x1d\x7a\x90\x0d\x02\xa9\x9f"
         "\x37\x8c\x3f\x1c\xde\xd8\x76\x05\x63\xf9\x9b\x08\x41\x26\xbf\x10"
         "\x8c\x8b\xd4\x4e\x51\x2a\x74\x13\x32\x7f\x5b\x16\x97\xd7\x83\x3e"
         "\xeb\xaf\x83\xca\x9a\x55\x21\x8c\x7f\x1a\x88\x18\xad\xf1\xc3\x6a"
         "\x35\xdd\xa0\x54\x00\xc9\xd1\x1d\xa7\x55\xca\x26\xad\x12\x35\x43"
         "\x97\xab\x4f\x21\x8e\x85\xcf\x60\xc7\x0f\x8f\xba\x6d\x54\x00\xe9"
         "\xb0\x5c\x65\xf0\xe4\xa9\xec\x8c\xed\xee\x67\xe5\x3d\xd1\x03\xc2"
         "\xd6\x45\xa8\x54\x99\x7f\x81\xed\x6f\x4e\x0f\x92\xa6\xbd\xa0\xd1"
         "\x2d\x13\x21\x82\x66\x02\x3d\xdf\x18\x90\xc8\x55\xa8\x33\xb0\x8d"
         "\x5b\xeb\x60\xf5\x07\xfe\xff\x39\x1d\xe7\x6b\xbc\x84\xfb\xec\xc6"
         "\x0c\x92\xee\xeb\xec\xd9\x4f\x2e\xdc\xe9\x5e\xf4\xa1\x03\x48\x7d"
         "\x90\x48\x94\xb6\xf8\xe1\x57\x6b\x9a\x38\x79\xb8\x88\xa0\xd0\xde"
         "\xae\x60\x04\xf7\x71\xee\x42\x72\x3c\x5a\xdd\xd9\x40\x75\xa9\x5a"
         "\x6d\x17\xce\x12\x94\xbd\xe2\xcc\x0a\xba\x1a\x69\xbb\x1e\x4e\x45"
         "\x58\x48\xe8\x8e\xfe\xd8\x88\xf6\xd3\x11\xee\xc2\x9d\x8a\x16\xb0"
         "\x05\x76\x56\xb5\x56\xc5\x50\xf6\x3e\xac\xf5\x9b\x15\x03\x95\xf6"
         "\x96\xe7\x70\x92\x92\xfc\x8d\x01\xfb\x24\x4b\x23\x7c\x22\xf9\x99"
         "\x15\x63\xf2\xd1\xe7\x00\x84\x0c\x88\x61\xf8\x3a\x10\xe7\xf2\x38"
         "\x03\x9a\x6b\x7a\xb1\x9d\xe4\xc0\x7e\x12\x40\x5c\xc4\x42\x3d\xa0"
         "\xd6\x9a\x6f\x97\x97\x62\x9f\x7a\x74\x0e\xe7\xd0\xb6\x17\xa9\xe1"
         "\x43\x88\x82\x58\x18\x2e\xde\x16\x1c\xad\xde\x98\xb7\x7d\x83\xfe"
         "\x8d\xb2\xe2\xd1\x49\xc5\x58\x13\xd4\x75\x51\xdd\x86\x29\xf8\x5d"
         "\xdc\xa8\xa2\x90\xda\xab\xd5\x89\xbf\x1b\x39\x5f\xc6\x64\x42\x86"
         "\x1a\x63\x22\xc8";
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
.*===shortishscob
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x68\x6f\x72\x74\x69\x73\x68\x73\x63\x6f"
         "\x62";
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
.*===trichitepersonship
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x74\x72\x69\x63\x68\x69\x74\x65\x70\x65\x72"
         "\x73\x6f\x6e\x73\x68\x69\x70";
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
