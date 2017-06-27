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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\xb1\x48\x34\xa6"
         "\xbe\xd2\x14\x4e\xe4\x64\xfa\xe4\x10\x00\x00\x00\x9a\x20\xa1\x8b"
         "\x6b\xee\x2c\xd0\x18\x00\xae\xe9\x82\x83\x59\x80\x24\x54\x86\x6c"
         "\x45\xfa\x18\xdc\x55\x51\x86\x94\x02\xb8\x47\x2e\xfe\x29\xfe\x0b"
         "\x69\x94\xc3\x65\xf4\x9c\x72\xd9\x5e\x17\xea\xf3\xca\x6f\x64\xcd"
         "\x48\xf6\x41\x8b\xae\x4f\xa8\x3d\xdb\x5a\x71\x3c\x34\x70\x3f\x36"
         "\xdc\xf7\x32\x26\xd1\x19\x47\xb1\x19\x73\x92\xbb\xa9\xd4\x6a\x4d"
         "\x8b\x0b\x46\x68\x84\xab\x00\xe0\xaa\x43\xf7\x7a\x1b\xdb\xfc\x06"
         "\x36\xc3\x20\x1e\xdf\xe6\xca\x38\xd1\xff\x0b\x09\x39\x03\x07\xe0"
         "\x8b\x58\x4b\xaf\x54\x72\x0d\xe7\x06\x1d\x84\xc9\x56\x5c\xa4\x63"
         "\x0e\xc2\x8d\x77\xa5\x1f\xea\xc9\xc1\xf3\x41\x50\xba\x5a\xc4\x3e"
         "\x7f\xb6\x28\x38\x6e\x05\x90\x19\x43\x8b\xa0\x9f\x33\x64\xeb\x2b"
         "\x15\x16\x38\x54\x65\x25\x89\x18\x66\xd8\xea\x29\xae\xd6\x58\x3c"
         "\x2f\xb9\x46\x52\x19\x73\x7e\x71\x4f\x0a\xd2\x1c\x9f\x71\x00\x12"
         "\x76\xef\x64\x14\xd0\x1a\xd5\x3f\x7f\x11\x3d\x6a\xea\x0a\xb2\xd7"
         "\x04\xdd\xb1\xf5\x99\xa8\x1e\x6b\xea\x67\xe4\xab\xac\x15\xfa\xd6"
         "\xc6\xe5\xbe\x48\x99\xae\x38\xc6\xab\x15\xda\xa7\x46\xd3\xb9\x90"
         "\x8b\xc7\x30\xfa\x6e\x93\xc8\x57\x10\x1a\xf1\x5f\x08\x33\xe9\xaa"
         "\x1a\x8a\x39\x1a\x33\x39\x59\x81\x17\x83\x8f\x4d\xc7\x20\x83\x5a"
         "\xcf\xe2\x23\x77\x4b\xe0\xd3\x6e\xd1\xa6\x82\x03\xfe\xce\x73\xc1"
         "\x6b\xcf\x92\xab\xb9\x5d\x82\x7f\x8d\xaa\x9b\xa7\x42\x9b\xd0\xcd"
         "\x82\x39\x65\x8d\x50\x64\xdb\x4d\x62\x91\xe1\x96\xf1\x6d\xd5\x3e"
         "\xe1\x87\x63\x7e\x89\x51\x8b\xc1\x34\xaa\x07\x6f\x63\x31\x45\xca"
         "\x33\xac\x6f\x08\x95\x13\xc3\x1c\x2a\x97\x77\xf7\x3e\x45\x19\x7e"
         "\xfb\x3a\x27\x9f\xde\xfa\xca\x1d\x6f\x16\x2f\x06\x8f\x79\xc0\xae"
         "\x08\x15\x4b\xdf\x96\x5b\x7e\xdb\xf9\xeb\x2b\x17\x51\x3d\x6c\x25"
         "\xf7\x7e\xc1\xb4\xdf\xff\x66\x28\x64\x0b\xda\xb3\xa3\x0f\x08\x86"
         "\x6d\xa3\xe7\xcd\x95\x03\xc3\xcb\x75\x26\x96\xa7\xa7\x2c\x4c\x7a"
         "\xd3\x27\xa9\xde\xb9\x82\x80\x58\x76\xaf\xfd\x04\xb6\xaa\x7c\x40"
         "\x67\x71\x54\xc4\x05\x07\x7d\xbb\xbe\xd6\xd1\x57\xca\x04\x28\x00"
         "\x03\x25\xd8\x0b\x05\xad\x68\x7b\x33\x38\x65\x59\x15\x92\x14\x15"
         "\xf6\x3f\xf1\xcd\x32\xf7\xb6\x9a\x99\x2c\x8f\xe1\xfe\xa9\x60\x32"
         "\x02\x4b\xac\x57\x07\xc6\xb6\xa2\x0a\x55\x4d\x4e\x8e\x60\x8b\xf5"
         "\xf3\x4e\x61\xe7\x99\x80\x2d\xe9\xc8\x3f\x07\x1f\x55\xb1\xce\x53"
         "\x20\x70\xb6\xbd\x51\x2e\xfb\xf6\x3b\xa5\x64\x42\x82\xb6\x84\x68"
         "\x33\xa1\x6f\xc1\x03\x9f\x17\x8e\x3a\xd7\x03\xef\x3b\x68\xac\x78"
         "\xdc\x33\x11\xee\xac\x46\x8a\xd4\x21\xbc\xc3\x26\x9a\x21\x8f\xe4"
         "\xe6\x79\xbd\x1f\x36\x40\x5c\x88\xc5\x4a\x9e\x15\x34\x63\x85\xf2"
         "\x23\x50\x72\x58\x48\x58\x0a\x45\x0d\x17\xe5\x93\x95\xc5\xd4\x06"
         "\x8f\xf1\x83\x37\x89\xe4\xfc\xd2\x68\x85\xef\x25\x08\xe7\x5b\x65"
         "\x55\x33\xc1\xe0\x2a\xeb\x47\x78\x46\x85\x00\x44\xb1\x50\xd2\xe4"
         "\x8b\x58\x2e\xe9\x4b\xf8\x43\xd2\xd5\x2f\x35\xe6\x08\x39\x81\x9a"
         "\x8b\x39\xb6\xec\xed\x3c\xf9\x9b\xb0\xa3\xff\xb6\xb2\x9e\xab\x40"
         "\x87\x56\x5f\x0f\x8e\x09\x3b\x41\x0d\xab\xdb\x74\x61\x76\x39\xa4"
         "\x42\x01\xd9\x3f\xa3\x43\xd8\x44\x1a\x85\x57\x5a\x95\xde\x64\xbe"
         "\x33\xd5\x8b\x8a\x30\xec\x77\x3d\x49\x44\xd9\x50\x68\x70\x53\x73"
         "\x09\xf7\x6c\x07\x44\x02\x3a\x26\x19\x54\x68\xcf\x5f\x17\xff\x66"
         "\xeb\xe8\x6f\x2f\x2d\xd7\xb6\x49\x64\xee\x14\xfa\xdc\x71\x54\x88"
         "\x43\x8c\x8e\x5a\x6f\xdd\x9c\x27\x45\xfa\xac\x44\xcd\xc0\x4b\x32"
         "\x43\xad\xf8\x67\x2b\x76\x8f\xf8\x8e\xef\xf3\x4f\x68\xc9\xd6\xca"
         "\x83\x0b\xa3\xe5\xe8\xc7\x1a\x9e\x04\x43\x8f\x53\x30\x3a\x1c\xfc"
         "\xb8\xf0\x3d\xd4\x08\xd4\xda\x34\x87\x80\xb2\xa0\xf4\xae\xe1\x97"
         "\x99\x2a\x88\x45\x6b\xf4\xa4\x8c\x0c\x79\x65\xd7\x80\x11\xf8\xeb"
         "\x36\xc1\xca\x8e\xca\x66\x79\x0f\x1e\x17\x53\x4c\xed\x1a\xd5\x1f"
         "\xa1\x79\x02\x56\x8d\x70\x16\x8f\xf3\xe0\x19\x14\xad\xf2\x67\x5e"
         "\xdf\x07\x1b\x34\xb6\x3b\x33\x04\xd2\x02\x12\x91\xf4\xe9\x8d\xb0"
         "\x8b\x8e\xa2\xed\xa9\x4e\x1b\x99\x2c\x6e\x13\x9c\x15\xe8\x14\x9b"
         "\xff\x97\xe6\x92\x51\x79\xae\xa6\xa4\xb9\x0c\x04\x5e\x63\x83\x22"
         "\x64\x4d\x11\x67\x6c\xf2\x76\x29\xb5\x60\x91\x0e\xc7\x8f\x5a\xed"
         "\x04\xc9\xa5\xb4\xb9\xaf\xfd\xd3\x2e\xd9\xb9\x33\x68\x63\x7f\x20"
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
.*===solemnlystre
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x73\x6f\x6c\x65\x6d\x6e\x6c\x79\x73\x74\x72"
         "\x65";
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
.*===remisrepresentationlancet
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x72\x65\x6d\x69\x73\x72\x65\x70\x72\x65\x73"
         "\x65\x6e\x74\x61\x74\x69\x6f\x6e\x6c\x61\x6e\x63\x65\x74";
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
