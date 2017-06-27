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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x52\x19\x05\xf0"
         "\x0c\x01\xe8\x9d\x7a\xe2\x2a\xd2\x29\x01\x00\x00\x2b\xa8\xe5\x1f"
         "\x03\x2a\xe2\x5b\xe1\xe5\xc8\x59\x5f\x39\x16\x51\x79\x83\x22\xb4"
         "\xec\xbf\xc4\x21\x6a\x41\xd3\x9c\x78\x15\xb8\x46\x2f\x41\x57\xe9"
         "\x48\xc2\xda\xca\x5c\xcb\xf4\x5a\x32\x71\xdd\x25\x7b\xee\x71\x29"
         "\x00\x04\x48\x8a\xfc\xf5\x32\xec\xc6\x77\xdb\x8a\xc4\x18\xfa\x85"
         "\xa3\x05\xa4\x08\xc6\x0f\xb2\xa7\x49\x30\xd9\x2b\x32\x9c\x5f\xfe"
         "\x8b\xaa\xda\xa9\xe6\x03\xe6\x1b\x27\x51\x6c\xf4\x86\xcc\x13\x47"
         "\xf4\x55\xd6\xcf\x69\xdd\x45\x01\x02\x62\x19\x1b\xc0\x0f\x58\x97"
         "\xe2\x75\x32\x08\x61\x61\x72\x87\x20\xf3\xc8\x50\x64\xd9\x52\xfa"
         "\xba\xfb\xc1\xe9\x3a\x43\xc1\x37\x00\x37\x8b\xc3\x41\x64\xbd\x3a"
         "\x88\x93\x5e\x30\x43\xa1\x40\xb3\x89\x2a\x85\x58\x20\x9d\xf0\x73"
         "\xe8\xf2\x6c\x44\xbc\x00\xf0\x36\x6d\xe8\x0a\x47\x9a\xb5\xf9\xd0"
         "\x2d\x26\x37\x00\xbf\xde\x5c\x4d\x5d\x6a\x35\x32\x34\x72\x60\xcd"
         "\x11\x5a\x17\x37\x26\xdb\xec\x45\xb9\x0e\x26\x6f\xbd\xdb\x9f\x69"
         "\x10\xdc\xdf\x7b\xab\xb2\x0b\x33\x6f\x35\x1f\x60\x6a\x69\x85\xe1"
         "\xb0\xba\x19\xae\x0a\x28\x07\x04\xbf\x90\xac\xae\x0a\xfe\x48\xe4"
         "\x2c\x86\x4d\xb7\x0c\x7e\x04\x5b\x8b\x5c\x02\xff\x60\xf8\x03\x45"
         "\xca\x30\xae\x5e\xf5\x33\x60\x33\x8e\xb0\xb8\xb1\x63\xbf\x24\x2f"
         "\x3f\x06\x5d\x61\x48\x7e\x1b\x5f\x92\x08\x72\xc0\x10\xd1\x39\x10"
         "\x92\x0d\x08\xac\x29\xd8\x86\x22\x0f\x60\xac\x54\xbc\xd3\xd3\xe5"
         "\x10\xbf\x0e\xdb\xab\xca\x09\x90\x03\xf0\x46\x21\x35\xb7\xdb\x96"
         "\x0e\x7b\x98\x02\x6b\x88\xc0\x44\x9e\x16\xd6\xb9\x96\x59\xf8\xb2"
         "\x9d\x04\x1b\x88\x95\x78\xea\x41\xda\xb7\x9d\xf3\xea\x06\x78\x16"
         "\x08\xa8\x06\x1a\x73\xa7\x92\xde\xe7\xa6\x30\xb0\x56\x18\x72\xd9"
         "\x86\x8d\x42\xd4\x47\x2d\xdc\x48\x31\xdc\xa2\x5f\x94\x15\xdd\xcd"
         "\xe2\x04\x37\x88\x89\xe1\x7c\x0a\x98\x03\xa8\x2c\xe1\x26\x50\x8b"
         "\xdb\xb9\x66\xfd\x96\xfc\x72\x05\x82\xb5\xc9\x96\x28\xb2\x33\x28"
         "\x53\xc3\x8c\xe3\xfa\x52\x8e\x21\x4e\x86\xee\x26\xa7\x7f\xf4\x23"
         "\x7e\xa5\xf6\xd7\x13\x09\x98\xf1\x27\xc2\x81\xca\x28\xaf\x61\xa8"
         "\x17\x1b\xdf\xc6\x88\x25\x6c\x5b\xde\x55\xfe\x7b\xf9\xeb\x4a\x2a"
         "\x87\x30\x76\xe8\x85\x9f\x13\x02\x67\x23\x7d\x8c\x59\x6e\xa8\xb2"
         "\x2b\x00\xbe\x1a\x6b\xbd\xb3\xa0\x91\x39\x9b\xfe\x21\x28\xcc\x4a"
         "\x9f\x61\x82\x7d\x4a\x49\x9b\x3c\xb8\x10\xcc\x2c\x93\x89\x4c\x47"
         "\x1f\x40\x4f\x2f\x6b\x9a\xaa\x9c\x60\x99\xef\xda\xe5\x2c\xe5\xec"
         "\xa5\x11\xf8\x40\x9f\x19\xc5\x40\x58\x7e\xe0\xc3\xa5\xa8\x1f\x4f"
         "\xab\xc6\xac\xa9\xfd\xc4\xcb\x2c\xdf\x57\xb0\xa4\xfb\x29\x0e\x74"
         "\x53\x16\xe6\x1a\x77\x83\x17\x7b\x90\x63\xed\x62\xe8\x90\x52\x5d"
         "\xc7\x92\x5b\x9f\xc4\x5c\x28\xa0\x0c\x29\x64\x2c\x11\xcf\x23\xf6"
         "\x57\xf2\xa6\x43\xa5\xff\xc6\xac\xe6\x61\xac\xfd\x70\x2b\x20\x9b"
         "\x14\x39\x89\x3d\xfc\x1d\x8c\x16\xe3\x69\x0e\xf7\x91\xc1\x87\x01"
         "\xdf\x79\xad\x45\xd9\x3a\xd9\xcf\xa7\x9c\xf1\xb9\x88\xba\xf7\x11"
         "\x22\x47\xb7\x24\x10\x0e\x49\xd6\x42\xe0\x60\xf5\x43\xab\xb6\x0a"
         "\x22\x1e\x13\x2c\xae\x19\x61\x79\x78\x68\x23\xa5\x0d\xe4\x88\xc3"
         "\x0f\xb7\x54\xa3\x18\x43\xbe\x7b\x8d\xed\x42\x14\x78\x34\x6d\x50"
         "\xae\xff\xb5\x94\x90\xcf\x9f\x71\x92\xb4\xad\xbc\x66\x20\x20\x20"
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
.*===irislikeaphyllose
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x72\x69\x73\x6c\x69\x6b\x65\x61\x70\x68"
         "\x79\x6c\x6c\x6f\x73\x65";
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
.*===perukiershiplexicographer
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x65\x72\x75\x6b\x69\x65\x72\x73\x68\x69"
         "\x70\x6c\x65\x78\x69\x63\x6f\x67\x72\x61\x70\x68\x65\x72";
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
