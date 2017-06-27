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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xf3\xef\x04\x0a"
         "\xcf\x6c\xf2\x38\x97\x05\x26\x3f\x7c\x19\x37\xe1\x9b\x11\x71\xfe"
         "\xda\x00\x00\x00\x40\x1d\xd9\x39\x93\x4a\xaa\xe4\x70\x71\x01\x3e"
         "\xe7\x94\x83\xd3\xb4\x4c\x35\xc2\x67\xe3\x75\x66\xc2\x7d\xf2\x96"
         "\xa5\xd8\x14\x20\x83\xf9\x4a\xfc\x67\x43\x41\x0c\xc5\x6e\xb6\x0e"
         "\xa8\xf0\x3a\x8a\x38\x05\xe4\xd7\xcd\x46\xa6\x6b\x6c\x19\x73\x5e"
         "\x16\xb6\xc2\x6b\xfb\x6e\x35\xb6\xe9\x1d\xe8\x60\x62\xed\xcf\x7d"
         "\x35\x9e\x53\xcf\xce\x40\x0c\x03\x75\x48\x91\xad\xad\x87\x4d\xc2"
         "\x38\x7a\xc4\x3c\x65\x96\xf2\x05\x97\x3a\x17\x1b\x64\xd3\xbe\x07"
         "\x83\x10\xf4\xcd\xdd\x4e\x95\x43\xfa\xe3\x8c\xfd\xd7\xa8\x44\x56"
         "\x0a\x1a\xdc\x4d\x60\xd9\x78\xe7\x7c\xbf\xa5\x13\xf4\x3d\x20\xc4"
         "\xf0\x84\x5e\x1a\xec\xa4\x91\x54\x44\x60\x40\xb9\xb7\xc4\xae\x2c"
         "\x0e\x4f\x7b\x6e\x4e\x8e\x74\xea\x12\x8b\x8c\x7c\x8b\x09\xb5\xed"
         "\xdd\xb3\x96\x04\x80\x68\x18\x78\x61\xa2\xff\x41\x91\xed\x38\x8e"
         "\x8e\xb2\x3d\x54\x25\x62\xd4\xa9\x5c\x9f\x85\x66\xa1\xee\xdf\x31"
         "\xe8\xee\x5d\xcf\x64\x77\x1d\x4c\xc0\xe9\x54\x51\xa1\x6b\x5d\xa4"
         "\x08\xfb\xc3\x9b\x7b\xbd\x32\xbb\xc9\xfc\x97\x44\xe6\x61\xd2\x55"
         "\xe6\xc6\x44\x2e\x3c\xfc\xeb\x32\x8c\x18\x05\xf5\x2f\x8b\x04\x43"
         "\x39\x57\x02\xf7\x3b\x92\x05\x64\xdc\x56\x47\xbc\x6d\x8b\x14\x88"
         "\x08\x6e\x6d\x6f\xb2\x07\x47\x49\x45\xb9\x5f\x75\x02\x5f\x96\xfe"
         "\x56\xcf\xd4\x42\xd7\x6e\x08\xb5\x8d\x4b\x1d\x2a\x4b\x15\x7b\x51"
         "\xd1\xb3\xa8\x81\x15\xd2\xb7\x50\x50\x28\x9f\xd1\xc0\x1a\x0a\xcc"
         "\x5f\x6d\xec\x5d\x45\x11\x05\x38\x65\x9d\xca\x8d\x84\x6a\x03\xd1"
         "\xff\x10\x5f\xf4\xac\xa4\xc9\xa5\x08\x00\x42\x7f\xeb\xd8\x90\x25"
         "\x23\x07\x93\x9d\x84\xf9\x87\xbf\x08\x00\x57\xb1\x94\xea\x7c\x97"
         "\xcd\xb9\x95\x50\x20\x77\xa7\x15\x24\xbf\xd8\x27\x44\xec\xc4\x81"
         "\x39\xa1\x4c\xfa\x72\xba\x6d\xbc\xba\xe8\x48\x2f\xcd\x8c\xd2\xd5"
         "\x5b\x15\x90\xc5\x4b\x83\xd6\xa7\xe3\x37\xa5\xf9\x01\x27\xdc\x83"
         "\xd2\x83\xc1\x91\xce\x6a\x58\x1a\x2b\x57\xfa\xd8\x6a\x40\xee\xbe"
         "\xb8\x8b\x63\x86\xf0\xfd\x7c\x39\x26\x29\x65\xfa\x25\x5a\xdf\x45"
         "\x51\x4f\xb1\xf9\xad\xe5\x71\x31\x99\x0c\x6d\x3c\xc0\x9d\xba\x16"
         "\xb8\x0a\x09\xd5\x79\x50\x6f\xaa\xfb\xaa\xea\x49\x38\xa2\xda\x4c"
         "\x27\x10\xe3\xf0\x37\x86\x6d\xf8\x98\x38\x15\xbb\x90\xb9\xb8\xb8"
         "\xeb\xb2\x6b\xdf\x0f\x69\x42\x54\x7a\xea\xfe\x57\x2b\x2d\x82\x39"
         "\x04\xd6\x5b\x7e\xe8\x61\x99\xb2\x31\xed\xda\xd7\xd3\x20\x49\x11"
         "\xd7\x49\x41\x75\x95\x91\xe4\x26\x16\x07\xd8\x38\x92\x67\xd0\x6b"
         "\x8e\x1c\x56\x0a\xaf\x81\x07\xdc\x85\x07\xcd\x5e\xf0\x40\xd7\x10"
         "\xb1\x0e\x39\x34\x99\xd1\x41\x4e\xf8\x72\xa2\x19\xc8\xcf\xc6\x29"
         "\x31\xc3\x4e\x56\xc3\x44\xbd\xcb\xac\xcb\xdd\x83\x37\xec\xe1\x87"
         "\xe7\xe3\x1a\x4f\x54\xa1\x51\xfc\xf6\xce\x27\xc3\xbd\x57\xf9\xe6"
         "\x01\x74\x78\xeb\xc7\x50\xa6\x10\xcb\x05\x76\x07\x09\x09\x52\x4a"
         "\x08\x26\xf7\xb8\x6e\xb5\xef\x18\xae\x6e\xae\x9a\xb4\x6e\x4f\x99"
         "\xfc\x1a\x1b\x92\xa2\x2c\x98\xa8\x60\xf0\xbb\xb8\xb6\x26\x4c\x65"
         "\xad\xf0\xc6\x11\x08\x37\x7f\xb8\x62\x30\xe4\x67\x73\xd3\x3d\xeb"
         "\x73\x05\x7a\x01\xb6\x89\x8b\xaf\x6b\x70\x5b\x19\xd7\xef\xe2\x4b"
         "\x3b\xf0\x65\x36\xb2\xb5\x26\x31\x5b\x10\x05\x69\xe4\xb2\x91\x0e"
         "\xc6\x92\xa5\xd2\xd4\x7f\x07\xa9\x9d\x16\xea\x55\xad\x4c\x8e\x47"
         "\x19\x1d\x20\x7c\xa4\xa3\xa2\xf3\x37\xbe\xd7\xe3\xc8\xb3\x85\x94"
         "\x1c\x36\xa0\x76\x61\x61\x6f\x1d\x63\x11\x77\x79\x16\xec\xab\x5f"
         "\x54\xcb\x79\xe1\x01\x6b\x01\x65\xc0\x69\x69\x33\x3f\xef\xeb\xa4"
         "\x71\x4f\xe1\x4b\x82\x2a\x30\x67\x77\x52\xcf\x89\xfc\x66\x5d\xbf"
         "\x44\x96\xf0\x24\x09\x3a\xc3\xdb\x49\xf1\x6a\x3e\x83\x5c\xc7\xa1"
         "\x44\x1f\x62\xd3\x08\x3d\x71\x18\x1e\x1d\x68\xf1\x05\x11\x11\x6d"
         "\x6f\x10\x1f\xc0\xf4\xb5\x32\x96\x9c\xff\x14\xb7\xb2\x30\x10\x0e"
         "\x05\x2c\x21\x36\xa7\x16\xbb\xeb\xbf\x9f\x3c\x6a\x84\x41\x3e\xdb"
         "\xdb\xd2\xe9\x1c\x2b\x56\x03\x96\x5c\x5e\xdc\x20\x20\x20\x20\x20"
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
.*===dyewoodsocii
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x64\x79\x65\x77\x6f\x6f\x64\x73\x6f\x63\x69"
         "\x69";
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
.*===iconismanisostemonous
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x63\x6f\x6e\x69\x73\x6d\x61\x6e\x69\x73"
         "\x6f\x73\x74\x65\x6d\x6f\x6e\x6f\x75\x73";
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
