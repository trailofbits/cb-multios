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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x07\x90\xaa\x3e"
         "\x75\x79\x47\x87\xd5\x0a\x16\x8b\x8e\xa6\x95\x43\x44\x75\x4a\xb6"
         "\x57\x01\x00\x00\x31\x00\xc8\xf8\xed\xc6\x31\x51\x14\x0c\xdc\x40"
         "\xde\x1c\x99\x48\x0c\x05\x44\xc9\xce\x84\xdd\xa8\xf1\x29\x17\xa5"
         "\x52\x7a\x5e\x00\x6d\x4f\x07\x9c\x2a\x9e\x07\xa0\x9f\xd3\x61\x07"
         "\xcf\xe4\xf6\xb0\x29\x94\x89\x25\xed\x70\xd0\x96\xb8\x88\xa9\xad"
         "\x7e\xd8\x4c\x7d\x81\xc5\x15\x79\x39\xe4\xf6\x00\x12\x12\x9e\x9a"
         "\xe3\x50\xad\xf6\x26\xeb\xba\x18\x0b\x08\x67\x36\x65\x52\x17\x63"
         "\x80\xee\xd2\xa7\xda\xb4\xa8\x3d\x24\x3e\x1d\x4f\xa0\xcf\x24\xff"
         "\x1d\xa2\xdf\xa7\x08\x09\xf2\xc0\x41\x05\xd1\xec\x19\x97\xe0\x9d"
         "\xf0\x73\x53\xd9\xed\x54\xee\x13\xbd\x78\xe8\x47\xff\xac\xae\x73"
         "\xca\x5e\x82\x5a\xf2\x30\xc5\xdf\x37\x9d\x30\x17\xda\x02\xa7\x79"
         "\x63\x94\x0d\x64\x24\x01\xbb\xc6\xb3\x2b\x5f\xb9\x7d\x3d\xae\xc3"
         "\x7e\xc9\x26\xbd\xa0\xe1\x0a\x16\xdc\xb3\x58\xed\xcd\xd5\x18\x9b"
         "\x73\xaf\x47\xf8\x78\xd6\x41\xeb\x61\x8b\x0d\xfc\x70\x36\x7b\x00"
         "\xb6\x89\xce\xcc\xa1\xf9\xb4\x14\xd7\x81\x8e\x08\x6f\x10\x4b\x04"
         "\x02\x11\x05\x98\xbe\x05\x13\x00\xab\x18\xfd\x31\x8d\xac\xdd\x9a"
         "\xb1\x7c\x54\xf7\x61\x58\x0c\x85\xdd\xd4\x69\x7d\x1e\x38\x3b\x5e"
         "\x1a\x53\x85\x03\x13\x00\x18\x80\x6f\xc9\x3f\x38\x64\xa3\x10\x2f"
         "\x7f\xc1\x07\xb1\x9b\xcd\xe6\xde\x34\x64\x83\x00\x30\x51\xff\x57"
         "\xca\x5e\x4e\xa6\x3e\x8e\x8b\xa2\xd8\xe0\x0f\x67\x02\x59\x7f\xe4"
         "\xc0\x21\xc6\xaa\x57\x6f\x42\xfb\x6c\xcb\xac\xd5\x0e\x2f\x2e\x33"
         "\x8c\x80\x35\x6a\xa0\xa6\xd3\x99\x01\xf4\x49\x6d\x44\x39\xd9\x06"
         "\x90\xea\x6c\x12\x50\x00\x03\x2c\x11\xa8\xfd\x85\xd7\x84\xfc\x32"
         "\x0e\x5c\x6b\x52\x88\xd0\x18\x97\x7d\x9c\x61\x38\x51\x8c\x7d\x95"
         "\x44\x0d\xeb\x0e\xdf\x91\x40\x7f\x90\x4d\xd7\x41\xec\x4b\x98\x53"
         "\x19\x66\x96\xc4\x4e\x3c\x5e\xbb\x58\x8f\x90\xf1\x9b\xf9\x22\x17"
         "\x0f\xf3\xea\x73\xcc\xf3\x1d\xd6\xb9\x6d\x2f\x7e\x45\xb5\x1b\x58"
         "\x94\x83\x95\x2e\xaa\x82\xff\x6f\x9c\x34\x83\x00\x86\x53\x76\xf3"
         "\xc3\xa9\x4e\xe6\xd9\xa4\x26\x91\x8a\xc6\x2f\x56\x53\x54\xa5\x34"
         "\x17\x50\xcb\x4f\x1f\x82\x74\x58\x23\x54\x1a\x2e\x72\x79\x12\x95"
         "\xc2\x71\xb5\x2b\x0a\x72\xff\x34\xf5\x92\x2e\x62\x91\x25\xdc\x39"
         "\x84\xa4\x87\xbe\x7f\x39\xa6\xe2\x6a\x15\x3c\x8e\xc8\xf6\xe1\x36"
         "\x31\xb8\x36\x9e\xc0\xc2\x75\xb1\x63\x52\x17\xc0\xab\xef\xf0\x63"
         "\x8f\xcc\x24\x8a\xe9\x48\x72\x3c\xe0\x25\x75\x65\x68\x46\x38\xad"
         "\x37\x24\xab\x86\x67\xb0\xe5\xbe\x5c\xcd\xf1\xea\x17\x81\xb1\x68"
         "\xce\x88\x06\xa6\x46\xf0\x97\xdf\x86\x7a\x30\xc8\x37\x88\x9d\x75"
         "\x5c\xce\xed\x1b\xd1\x08\xec\xa8\x54\x20\x6b\x44\x30\xff\x78\x65"
         "\x5a\x88\xac\x7a\x20\x83\xb9\x41\x25\xce\x64\x9d\x7c\xa6\xc3\xb1"
         "\x50\xc9\xb7\x84\xcd\x4f\xa8\x73\x44\x18\x2c\xa9\x9c\xb7\xe6\x06"
         "\x76\xec\x63\x8a\xb5\xd1\xad\x7d\x0b\xc0\x43\x2f\x0e\x44\xe7\x34"
         "\x0d\xb6\x2f\xd0\x1e\x47\xbd\x09\x9b\x30\xb4\xfd\x33\x46\x50\xdd"
         "\x8a\x1e\x33\x4e\xe2\xcb\xb4\xc3\xb0\x96\x6a\xf2\xea\x0c\xb0\x7f"
         "\x20\xb6\xee\xb0\xce\x74\x23\x37\xc5\xf6\x40\xf1\x2c\xb8\xad\x6b"
         "\xa2\xd3\x63\x18\x56\x9f\x4a\x43\x3c\x65\x8a\xdc\x30\x8d\x42\x6f"
         "\xfe\xd0\xb0\x6f\x84\x56\x03\xc5\x75\x6c\x43\x12\x1c\x43\x9c\x63"
         "\x8e\xa4\xec\xc6\x9b\xf2\x61\x9b\xdb\x43\xb1\xdd\x2e\x54\xc3\x90"
         "\xe5\x18\xd2\xca\x1e\x4b\x62\x32\xf9\xce\x2b\x74\xc8\x82\x0d\x8d"
         "\xd0\x5e\x46\x71\x32\x56\x22\x14\xb5\xd8\xf2\xbd\x27\xce\x7a\xed"
         "\xbb\x7c\x48\xcd\x19\x0f\x97\x25\xe5\xce\xb6\x43\x8f\xe4\xee\xad"
         "\x43\x6e\x2e\xd0\x63\xed\x73\xa8\x01\xeb\x9d\x80\x53\x97\x8b\x8d"
         "\x14\x6e\x60\x30\x16\x51\xc3\x8b\x2c\xfa\x8d\xb4\x4c\xc3\xe6\x40"
         "\xbd\x69\x85\xa9\x1d\x5f\xf2\xe9\x6b\xfc\x62\x43\x63\xae\x2d\xf7"
         "\xd9\x04\x05\x59\xe6\x85\xcb\xa2\xb1\x54\x43\x3c\x5d\x91\x4d\x67"
         "\x48\xe3\x03\xe6\xab\x37\x48\x3c\x16\x68\x0e\xd6\xa2\x4f\xdc\x2e"
         "\xef\x00\x65\xab\x9b\xce\xff\x2a\x3a\xfb\x41\xcb\xf1\xdc\xb7\xf4"
         "\x69\x72\x05\xe6\xd4\x49\x5a\x2a\x22\x10\xf7\x85\x21\x0c\x69\xc5"
         "\xd6\xc1\xaa\xfc\xae\x71\x11\x51\x65\xa2\x4f\xe4\xa8\x89\xee\xa7"
         "\x77\xa7\xe6\xa1\x47\xf4\x7a\x84\xd7\xa4\x5b\x83\xdb\xdc\x5b\x9d"
         "\x0b\x8a\x9f\x19\x71\x98\x0a\x84\xd3\xfc\xbc\x33\x5a\x8d\x20\x20"
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
.*===disaffectedanchorite
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x64\x69\x73\x61\x66\x66\x65\x63\x74\x65\x64"
         "\x61\x6e\x63\x68\x6f\x72\x69\x74\x65";
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
.*===sulfureasupertramp
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x75\x6c\x66\x75\x72\x65\x61\x73\x75\x70"
         "\x65\x72\x74\x72\x61\x6d\x70";
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
.*===scruplercellulifugal
*/
      static char read_00005_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x63\x72\x75\x70\x6c\x65\x72\x63\x65\x6c"
         "\x6c\x75\x6c\x69\x66\x75\x67\x61\x6c";
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
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x3d\x3d\x3d\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 4);
      if (read_00006_res) {} //silence unused variable warning
      /* read match pcre:
.*Dissection finished
*/
      static char read_00006_00000_regex[] = 
         "\x2e\x2a\x44\x69\x73\x73\x65\x63\x74\x69\x6f\x6e\x20\x66\x69\x6e"
         "\x69\x73\x68\x65\x64";
      static match_result read_00006_00000_match;
      pcre *read_00006_00000_pcre = cgc_init_regex(read_00006_00000_regex);
      if (read_00006_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00006_00000_pcre, 0, read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, &read_00006_00000_match);
         if (rc > 0) {
            read_00006_ptr += read_00006_00000_match.match_end - read_00006_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00006_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
}
