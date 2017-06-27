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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x6b\x54\xd0\x25"
         "\x70\xf1\x0a\xee\x0a\x3e\x57\x9f\x0f\x74\x6b\x74\x33\x6b\x58\x92"
         "\x70\x00\x00\x00\x0e\x81\x93\x29\x51\x76\x70\x9b\x4f\x1e\x8a\xb3"
         "\xc5\x0d\xee\xb1\x8c\x40\x00\x39\x9b\x11\x4b\x40\x00\x40\x40\x00"
         "\x66\x70\x90\xd6\x52\x07\xc5\xb4\xba\xe2\x81\xc7\xc7\x63\x16\xa5"
         "\x40\x15\x5c\xfc\xb7\x27\x31\xf9\x27\xf3\xc8\x2e\x00\x7a\x0e\xf6"
         "\xdd\xfc\x8f\x9b\x0d\xb0\x9d\x3a\xb8\xfa\x96\x7c\x48\xad\x03\x7b"
         "\xe5\x52\xf7\x1d\x99\x9c\x8c\x43\x5e\xc9\x39\xee\x11\x58\x13\xf5"
         "\x80\xd7\x63\x7e\xa6\xe1\x80\x05\xa7\x44\xb4\x05\x26\x65\x92\xed"
         "\xb1\x56\x0c\xea\xd0\x86\x2e\xdf\x91\x81\x39\xda\x42\xbb\xdd\xea"
         "\x25\x64\xd9\xcf\x65\x73\xe0\x94\xbc\x86\xad\x88\x13\x9d\x5b\xe8"
         "\xe6\x32\xa2\x60\x93\xcb\xb1\x92\x6c\xaf\xa2\xff\x7b\x5b\x11\x01"
         "\x89\xd2\xd2\xc2\xc5\xd5\x10\x42\x1a\x52\x9a\x44\x3a\x3b\x7c\x5f"
         "\xd4\x75\x50\xa7\x50\x84\x7f\xab\x3b\x37\x27\x02\x76\xb4\x71\x0d"
         "\xf2\x5d\xf3\x42\xb0\x3d\x47\x09\x0a\x18\x3e\xd9\x48\xa5\xd4\x4b"
         "\x0d\xf6\xd9\xb4\xad\x80\xc1\x03\x2f\x13\x84\x89\xc6\x2e\x09\x84"
         "\xe5\xfd\xe8\x56\xc7\x05\xc0\x24\x48\xc8\xff\x32\xc1\xcf\x28\xa1"
         "\xbe\x59\x75\x85\x6f\xe2\x86\xdc\xf1\x56\x7f\xfd\x19\x40\x00\x40"
         "\x40\x00\x43\x18\x9c\x98\x7c\x11\x42\x47\xa0\x02\xa2\x92\x91\x3a"
         "\xdf\x5c\x01\x7b\x7e\x20\x0f\xd7\xb1\x7f\x7b\xd3\xd6\xc7\xd5\xb2"
         "\x2f\x8b\x39\xed\xf0\x10\x87\xae\x60\xe5\x59\xd8\x8d\x2d\xc9\x03"
         "\x1b\x88\x02\x6a\xe4\x3a\x93\x28\x4a\xaa\x69\xf5\xa2\x77\x33\x7b"
         "\x4f\x26\xa2\xac\x33\x9f\x23\xb6\x34\x28\xbe\x28\xe9\xc1\xc1\x71"
         "\x46\x3a\x02\x4c\xae\xc5\xad\xc7\xd5\x61\x38\xd9\x9b\x18\x44\x67"
         "\xdd\xa6\xd2\xd8\xe1\x22\x7f\xee\x41\xcd\x13\x88\xf0\xa7\xeb\x18"
         "\x4f\xc9\x1f\xbd\x0d\x0a\xb1\xc2\x34\x97\xc8\x11\x10\xf8\xb3\xce"
         "\x4a\xda\xde\x70\x99\x5b\x92\x07\x07\xa3\xe6\xbc\x82\xb4\x82\x9f"
         "\x76\x7f\x75\xf8\x58\x7b\x89\xd7\xd1\x53\x7e\x99\x4e\xda\x4e\xcb"
         "\x3b\xd0\xe0\x93\x74\x38\xde\x7c\x77\x41\x37\x8b\xf6\x3a\x23\x64"
         "\x4e\x41\x2d\x77\x39\xae\xde\x28\x7c\x85\xac\x77\x1b\xef\x5e\x51"
         "\xd5\xf6\x65\x88\x96\xd4\xca\x10\x24\xf8\xc4\x7a\x40\x3e\xe9\x6f"
         "\xe1\xae\xf2\x1f\x98\x01\xcb\x5c\x09\xd1\x81\x64\xc6\x6c\x9c\xe9"
         "\x44\xc0\xa6\x48\xc9\xbe\xab\x98\x72\x8a\x13\x5e\x3f\x80\xb5\x37"
         "\x40\x00\xc6\xb5\xa2\xde\x89\xe8\x00\x87\x11\x68\xeb\xac\x40\x89"
         "\x3b\x5b\x72\x02\x26\x5d\xf4\x59\x2b\x26\xde\x84\x92\xcf\x1a\x32"
         "\xae\x83\xcc\x77\x1b\xd8\xcd\xd4\x28\x9a\x60\xda\x09\x2b\x5e\x37"
         "\x9b\xd7\x2d\x03\x38\x3f\x25\x0a\xad\x25\x57\x2e\x1e\x8b\x4c\xbf"
         "\xb6\x73\x2a\xc2\x97\x30\xbf\xdd\xba\x5a\xa0\xbe\x39\x0f\x37\x5b"
         "\xb9\x02\x61\x53\xb9\x87\x18\xc4\x71\x36\x46\x29\xca\xf7\xf0\x59"
         "\xf4\x8b\xd1\x7b\x9f\x20\x65\x47\xf6\xbb\xef\xde\xc6\x64\x3f\xa7"
         "\x41\x05\x23\xe5\xb5\xf7\xe4\x36\x16\x08\x83\xa7\x46\x91\xb6\x1b"
         "\x20\x62\xe4\x3c\x4c\x24\x92\x5e\x7d\xe7\xcf\xaf\x6e\xb7\x24\x21"
         "\xdb\xac\xf8\x03\x08\x82\x60\xb2\x58\xe9\x7e\x10\x8e\x9b\x34\xe7"
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
.*===sharkletcompactedly
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x68\x61\x72\x6b\x6c\x65\x74\x63\x6f\x6d"
         "\x70\x61\x63\x74\x65\x64\x6c\x79";
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
.*===unexchangedsupraventricular
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x75\x6e\x65\x78\x63\x68\x61\x6e\x67\x65\x64"
         "\x73\x75\x70\x72\x61\x76\x65\x6e\x74\x72\x69\x63\x75\x6c\x61\x72";
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
