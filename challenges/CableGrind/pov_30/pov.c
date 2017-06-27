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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xd6\xe5\x5d\xb1"
         "\xc4\x02\x75\xad\x00\xbf\x05\x14\x0e\x2a\xee\x6c\x27\x73\x1b\xb7"
         "\xa4\x00\x00\x00\xd0\x35\x00\x3b\x30\xbf\xcf\x99\x79\x91\x61\x03"
         "\x3d\x24\x3d\xf8\xf7\x75\xa1\x1c\x36\x4f\x43\xb5\xd1\x0a\xd9\x81"
         "\x90\xa4\xe6\xd7\x54\xd4\x5f\x2a\x31\x5c\x92\x16\x14\xc1\xe5\x60"
         "\xbb\xd0\x4e\x38\x09\x1c\x41\x7a\xd6\x0b\x5f\xb1\x1b\x3e\x00\x3e"
         "\x83\x48\xfc\x2a\xa5\xaf\x43\xfa\xcc\x9c\xe1\xa7\xfe\xa0\x52\xd3"
         "\x8a\xb7\x13\x2c\x04\x33\x15\xfe\x60\xd5\x23\x6a\x31\x3e\xd3\x38"
         "\xc7\xff\xd0\x30\x7c\x16\x87\x73\xca\xd9\x3d\xc6\x3f\xb9\xf8\xfc"
         "\xa7\x08\xd4\x36\x34\xc8\xbd\x07\xc7\xfc\x28\x2b\xf4\xe1\x96\x0c"
         "\x05\x1f\x70\xc3\x34\x82\x6b\x56\xa3\xc0\xdc\xd3\xcd\x14\xcd\xe6"
         "\xc5\xde\xaa\x86\x08\xe9\xa5\x03\x36\x4c\x5d\xf1\x67\x16\x67\x98"
         "\x63\x71\xc9\xaf\xa5\x6a\x46\x98\x65\x50\x52\x6f\x6e\xb6\xa5\xeb"
         "\xdb\x64\xde\x2b\x6d\x4b\x83\xb2\xfa\xf4\xa7\xc3\x00\xb0\xef\x5a"
         "\xfb\xe4\x43\x21\x19\xce\x1a\xb0\x30\x05\x4a\x2e\x5a\xf3\x26\x06"
         "\x96\xa7\x6f\xe2\x30\x92\xa9\x85\xf7\x0a\x8e\x51\x5b\xa3\x4c\xc6"
         "\x10\x5c\x34\x07\x59\x6f\x89\x28\x1b\xf0\x00\xf7\xdc\xf2\xd7\x65"
         "\x9f\xfa\xa9\x81\xbd\x7b\xee\x51\x3f\x24\xbb\x39\x77\x30\x5f\xb0"
         "\x29\x60\xbc\xba\x3f\xa5\xc0\x93\xdd\xe4\xf1\x40\x8d\xf6\xc0\xcf"
         "\x7a\x1a\x6a\x31\x28\xbc\x77\xf9\xf9\x70\x0e\xce\x92\x16\x83\xa7"
         "\x8e\xbe\x91\x1a\x42\x08\xfe\xeb\x4f\xbd\x95\x7e\xa7\xf7\x33\x81"
         "\xbe\x91\x50\xdb\x89\x5d\xd3\x78\xca\x9e\x04\x78\x8b\xdd\xfb\xa8"
         "\x60\x72\x89\x80\xe0\xe8\x84\xff\x97\xf7\xef\xf2\xb3\xd7\xe0\x8b"
         "\x25\xe8\xad\xf9\x42\xaf\x47\x30\x46\x51\x05\x56\xe8\xcf\xfb\x55"
         "\x89\x6d\x15\x89\x1a\x5c\x2a\x03\x4f\x54\xe0\x2b\xb2\x1a\xbf\xaf"
         "\x38\xf6\x7a\x66\x18\x2b\x96\x47\xf0\x1f\xda\xc2\x15\xf6\x9e\x50"
         "\x7b\x7a\xb7\x8f\xa1\xef\x5d\x64\x3b\x95\xb3\x48\x2d\x5a\x4e\xb4"
         "\xe0\xa8\x98\x4b\x52\xf1\x22\xf3\xf4\x7d\x8f\x2c\x20\x66\x4a\x9d"
         "\x0a\x50\xe1\xa1\x24\x73\x51\xa1\x3c\xa7\x6e\x44\x99\xe6\x30\x2e"
         "\xef\xd7\x85\x5f\xfa\x95\xc5\x7b\x26\x9e\x51\xb4\xf7\x12\x63\x0b"
         "\xc3\x1f\x3c\x2f\x96\x22\x08\xd6\x84\x49\x0b\x92\x7e\x6b\x06\x49"
         "\xf1\xde\x12\xfa\xab\xd8\xc9\x67\xc8\x4d\x1a\xf3\x72\xeb\x55\x02"
         "\x19\x09\x5a\x39\xb4\x27\xea\x0e\xc5\xfe\xbb\x25\xb2\x81\x7e\xb5"
         "\x5b\x9a\x47\xf7\xee\xdf\x91\x14\x21\xec\x73\xe1\x39\x9c\x16\x5a"
         "\xa9\x9c\x61\xc1\xd9\xb5\x2b\x45\xa8\x0c\xd2\xbe\xdc\x68\xa8\xb0"
         "\xef\x2d\x84\x47\x49\x76\xa5\x6a\xb3\x1d\x72\x83\x7f\x05\x17\x93"
         "\x40\xc8\xe3\x5a\x5c\xa8\x83\x6f\xcd\xc4\x96\x39\xf4\xba\x6a\xf2"
         "\x6f\x46\x86\x39\x55\x59\xdc\x06\xde\x5b\x3b\xd0\x21\xfc\xb9\x48"
         "\xd0\xc1\x29\x62\xf9\x94\x2f\x4e\xaa\x60\x01\xa0\xea\x46\x90\x7c"
         "\x5e\x69\x1d\xc4\xcc\x9a\xc3\xef\xf0\xd9\xbc\x71\x96\x35\xf5\x1a"
         "\x83\x91\x89\xa6\xa5\x93\x34\x54\x16\xab\x3d\x70\x30\x22\xba\xf3"
         "\x3c\x12\x06\xdb\x50\xbf\x77\x89\x04\xc4\xc0\xfc\x28\xea\xc7\x59"
         "\x57\x81\xa5\xaa\x40\x14\x0a\xee\xfe\x79\x0f\xaa\x68\x0c\xc0\x05"
         "\xd1\x8f\x0c\xa2\x6c\x8f\x64\x02\x48\x9e\x62\xbd\xa8\x88\xb6\xc4"
         "\x8f\x36\xc2\x33\x39\x6e\xc1\x91\xbd\xaa\x93\xfa\x52\x5d\x3e\xa7"
         "\x74\xa2\x93\xc2\xe8\x87\xdb\x8c\x6a\x4a\x65\x3c\xf4\x4a\xd0\xc7"
         "\x04\x70\x3d\xa8\x0f\xcb\x58\x9f\xf9\x0a\x95\x3e\x00\x3e\x00\xcb"
         "\x8d\x08\x85\xc0\x83\x6b\x75\x3e\x00\x3e\x00\x54\xa2\x70\x07\x6b"
         "\x87\x2e\x8e\xec\x22\x51\x1d\x37\xe0\x17\x4c\x78\x7f\xa1\x10\xe7"
         "\xe4\x3f\x77\x41\xfd\x5f\x54\x14\xd8\xbf\x17\x59\x92\x51\xb6\x53"
         "\x6f\x60\x3f\xd9\xe6\xd3\x79\x81\xc9\x88\xc2\x35\xc5\x4a\x57\xb3"
         "\x45\x34\x93\xeb\xaf\x30\x11\x82\x1f\xb5\xf5\x55\x1a\xef\x60\x6b"
         "\x26\x8a\x9c\x13\x55\xa8\x04\x27\x65\x17\x99\xe6\xf1\x79\x03\xf0"
         "\x65\x77\x98\x74\x35\xc6\x59\xa4\xc0\xb7\x3b\xec\xa1\x28\x17\xcf"
         "\xb6\xcb\x52\x7b\x8e\x86\xce\x17\x9b\x9a\x65\x6c\x34\x7b\xb7\xc4"
         "\x02\x64\x32\x53\xd6\xa7\x03\x31\x14\x1a\x40\x48\x5d\xf8\xbd\xb1"
         "\x38\xd9\x38\x6d\x3e\x4f\x2b\x0a\x13\x00\xfa\xca\x70\x09\x5e\x61"
         "\x65\x30\x27\x45\xa2\x3c\xf6\x5f\xbe\x93\x92\x8b\x74\x96\xe2\x60"
         "\x44\xbe\x94\xf2\x96\xc9\x68\x5f\x35\x77\x46\x20\x20\x20\x20\x20"
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
.*===cudavaogreish
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x63\x75\x64\x61\x76\x61\x6f\x67\x72\x65\x69"
         "\x73\x68";
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
.*===Dokoelectrochemically
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x44\x6f\x6b\x6f\x65\x6c\x65\x63\x74\x72\x6f"
         "\x63\x68\x65\x6d\x69\x63\x61\x6c\x6c\x79";
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
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 4);
      if (read_00005_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00005_00000_match;
      pcre *read_00005_00000_pcre = cgc_init_regex(read_00005_00000_regex);
      if (read_00005_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00005_00000_pcre, 0, read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, &read_00005_00000_match);
         if (rc > 0) {
            read_00005_ptr += read_00005_00000_match.match_end - read_00005_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00005_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
}
