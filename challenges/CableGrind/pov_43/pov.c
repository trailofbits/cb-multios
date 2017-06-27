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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x24\x9e\xa6\x28"
         "\x49\x03\x0e\x5f\x8a\xde\x9e\x08\x61\x94\x34\x30\x38\xb5\x7f\x8e"
         "\xf5\x00\x00\x00\x61\x4f\x3b\x20\x37\x69\x5c\xb6\x0e\x70\x9d\x15"
         "\x31\x32\x76\x18\x28\x10\xa6\x1e\x53\xdb\x56\x6d\xd4\xab\x95\xf7"
         "\x0e\x67\x4a\x60\xfb\x3b\x88\x54\x4d\xca\x90\xfa\x4c\x9e\xe5\xc2"
         "\xa9\xdb\x1c\x2e\x6d\xd0\xa5\x00\x7e\x58\x9d\x5a\xe7\xcf\xbd\x4c"
         "\x30\xa5\x37\xf7\x49\xbe\x30\x0b\x3b\xcf\x12\x3f\xd9\x3f\xd3\xe6"
         "\x7f\x23\xbe\xf7\x00\x77\x58\x53\x9c\x03\x5d\x5b\xf7\x28\xc2\xe8"
         "\x94\xab\x9f\xb4\x10\x86\x59\xd4\xa1\xd8\xea\xd5\x67\xf8\x79\xf3"
         "\xcc\x00\x25\x5e\x83\xde\x90\xa7\xf5\x25\x97\x59\xb6\x96\x0d\x7e"
         "\xe9\xc8\x63\xe1\x47\x42\xec\xb9\xc7\xc2\x91\x01\xac\x5a\x65\x6e"
         "\x65\x0b\x42\xd8\x64\xda\xf6\x69\xbf\xba\x63\xd8\x80\xcc\x43\x8f"
         "\x83\xf9\x24\x12\x2f\x5d\xec\xbb\xf2\x51\x7c\x7a\x7b\x77\x4a\xac"
         "\x32\x88\x28\x2c\xfb\x61\x80\x55\x65\xcf\x49\x31\x2b\xa2\x0a\x4b"
         "\x7a\x0a\xe6\x1d\x43\x2c\x4a\x3e\x80\xd7\x61\x4c\x4a\x3b\xd2\x7f"
         "\xb6\x60\xf9\x05\xac\x15\xa6\xb8\xcb\x7b\x02\x41\x8f\xdc\x66\x9a"
         "\x37\xee\xb2\x75\xe5\x56\xb0\x75\x05\x37\x28\x31\x4a\xc5\x43\x44"
         "\x78\x82\xe9\x46\x6e\x6f\xca\x94\x08\x35\xe8\xa1\x70\x05\xba\x6a"
         "\xe5\xd3\x25\x91\x9b\x32\xb9\xa2\xc5\x28\xe5\x2d\xc5\xda\xc8\xd5"
         "\x78\x5a\xc8\x44\x58\xf8\x32\x98\x5a\xd5\xfb\xb3\x63\xf8\xb1\xd2"
         "\xc3\x9d\x0e\x6c\x64\x78\x31\xf7\x53\xbf\x09\xf9\xe9\x42\x11\xe1"
         "\xdf\x1a\xdb\x9f\xc2\x68\xe2\x5e\x6c\x83\xd0\xff\x65\x8f\xcc\xbe"
         "\xcf\xd8\xc5\x80\xc9\xb0\x78\x1b\xcf\xcd\xd4\xd4\x90\x70\xf2\x4c"
         "\xf7\x5e\xf5\x12\x2f\x2d\x48\x5e\xc7\x62\xdd\xb3\x1c\x6d\x86\x8f"
         "\x63\x5d\xff\x35\x6c\xd5\xf8\xdb\xfb\x59\x0b\x7f\xe5\x3d\xab\x5e"
         "\x7a\xe9\x39\xff\x3c\xf8\xcf\x01\x28\x34\x5b\x7e\x51\x15\x85\xd1"
         "\x69\x68\xa0\x5d\xc7\x8c\x17\x5b\x18\x00\x91\xfd\x9c\xcd\xbb\x4f"
         "\x10\xa6\x52\x1b\x20\xac\xae\x6c\x37\x01\x87\xc2\x57\x4e\xec\xd7"
         "\x0d\xb6\x08\x42\xcf\xeb\xfd\x00\x82\x8a\x67\x50\x45\x7b\x10\xa4"
         "\x55\x59\xd8\x67\x72\x34\xf3\x3c\xb4\x81\xdb\x14\x4e\xf6\xe9\x17"
         "\xf3\x54\x87\xff\xe2\x66\xa0\xf2\xca\x60\x1b\x57\xa7\x5a\xf8\x6d"
         "\x0f\xa5\x55\x71\x07\xad\xbb\x12\x75\x96\x7a\x51\x14\x59\x46\x11"
         "\xf8\xfe\xb0\xab\x74\x14\x5a\xf7\x41\x0d\x0b\xb6\xd0\x44\x9e\x87"
         "\x12\xd7\xcb\x79\x9a\x77\x56\x3c\x8e\x23\xde\x98\xc7\xa4\xf9\xe3"
         "\x5f\x15\x15\xeb\x65\x9f\x08\x0b\xd2\x52\xf0\x20\xc9\x1a\x33\x47"
         "\x33\xc5\x7e\xa3\xcb\xe0\xd5\xf6\xa4\x45\xd7\x43\x0b\x09\xfe\xdb"
         "\x8a\x4c\x9f\xf5\x13\x6b\x56\xa5\x32\x96\x8b\x8f\x0c\x45\x08\xcf"
         "\xde\x59\x49\x81\x1e\x65\xcb\xf7\x07\x85\x57\xda\x39\x06\x77\xc0"
         "\x92\x4e\x0c\x36\xc9\xde\x6c\x64\x0b\x77\x2f\x43\xea\x9f\x00\x1f"
         "\x2b\xe3\x39\xc3\xc5\x68\x6f\xa2\x59\xb0\x50\xa5\xc7\xcc\x11\xc9"
         "\x42\x6f\xdf\x08\x18\xf8\x5b\x3d\xb2\x36\xf1\x8f\xb9\x3e\xc6\xa4"
         "\x4d\x17\xb7\x49\x82\x5e\xa3\x20\x7f\x94\x33\x6d\xad\x39\x22\x19"
         "\x28\xc4\xd7\x6c\xed\x9c\xd9\xfc\xee\xe3\xf3\x74\xd4\x98\x01\xa3"
         "\x93\xa3\xc1\x03\x84\xe0\x2c\x40\x85\xbf\x33\x4b\x06\x0f\xe3\xdf"
         "\x4c\x74\xe2\x55\x86\xbc\x91\x63\xb7\x60\x51\x65\x39\x46\x28\x03"
         "\x6c\xc2\xe8\xf9\x61\x56\xef\xb0\xef\xa1\x5e\x70\x8f\xbf\x96\xc7"
         "\x40\x96\xb8\xe9\xbc\x62\x00\xd6\x79\x87\xfb\x55\xc0\x7f\x68\xa3"
         "\xad\x5a\x45\x80\x68\xf5\x88\x52\x6e\xf3\xde\x99\xa6\x4d\xad\xa6"
         "\x4d\x23\x15\x5c\xab\xbb\x0e\xb6\x1c\xb4\xfd\x99\x62\x68\x91\x6d"
         "\x12\x01\xe3\xc2\xcb\x65\x49\xa3\xb7\xb6\x3b\x86\xa3\x7d\x04\x42"
         "\x7a\x4d\x5f\x02\x83\x91\x98\x8d\xfd\xfe\x2e\x52\x04\xc8\xc3\x2b"
         "\xc0\x08\xf8\x62\x91\x91\x56\x5c\xed\x16\x37\x8b\xc2\x2f\x23\x9c"
         "\xf9\xa7\x8d\xd7\xdf\x79\xd3\x13\x07\x44\x45\xee\x2e\xe6\x07\xcb"
         "\x4d\xde\xc7\x45\x16\x7f\x59\xda\x1c\xd7\xd4\x69\x5a\xe9\x67\xd4"
         "\x59\xf6\xb3\xc7\x54\x10\x18\xec\xd3\x6c\x18\x1c\xe2\x74\xc8\x62"
         "\xbc\x13\x1f\x0a\x01\xfd\xb6\x67\xa2\x14\xe6\x75\x73\xf1\x8d\xbe"
         "\xa4\xfa\xef\x69\xbd\xd6\x10\x9b\xe2\x54\x1b\x03\x43\x29\x72\x4d"
         "\x6d\x7c\x1e\xb5\xec\xcf\xe6\xb4\x66\x62\x03\x75\xd7\x61\x6f\xf3"
         "\x01\x44\x19\x7f\x3e\xc4\x86\xca\x68\x61\x2a\x84\x2b\x6e\xdf\x87"
         "\x9f\x8d\x3a\xef\x71\x20\xef\xf9\x4f\xc7\x3a\x10\xaf\xe7\x33\x52"
         "\xd1\xde\xc2\x27\xd5\x7b\x6f\xfa\x89\xb8\x68\xa2\xae\xd1\xf1\x45"
         "\xf5\xcd\x45\x05\x30\x23\xff\xaa\x93\xaa\xbe\x4b\x60\x9c\x85\xfd"
         "\x66\x43\xbb\x58\x0d\x4d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===wickedlyinflatedness
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x77\x69\x63\x6b\x65\x64\x6c\x79\x69\x6e\x66"
         "\x6c\x61\x74\x65\x64\x6e\x65\x73\x73";
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
.*===Bitulithicscrin
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x42\x69\x74\x75\x6c\x69\x74\x68\x69\x63\x73"
         "\x63\x72\x69\x6e";
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
