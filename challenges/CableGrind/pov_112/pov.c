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
         "\x00\x00\x00\x00\x00\x00\x00\x00\xe8\x03\x00\x00\x84\x33\xc5\x9c"
         "\x29\xf3\xcc\xfe\x30\xc3\x0a\xc1\x7d\x00\x00\x00\xc0\x0e\xfd\x8d"
         "\x5b\x00\x49\x4e\x9b\x56\x8b\xb5\xad\x12\x0d\x05\x8c\x6d\x31\x9e"
         "\xac\xed\xd7\x81\x01\x06\x53\x23\xba\x8b\xc2\xc9\x5f\x43\x53\x84"
         "\x42\xbe\xb8\xd6\x5b\x00\xe6\x4a\x2b\xe6\xcd\x9d\xdd\xeb\x15\x5e"
         "\xd1\xef\xc6\x6c\x9e\xee\x6c\xb2\x7e\x99\x93\x51\xa0\xde\xf7\xda"
         "\x9b\xa8\x47\x56\xe3\x9f\xf9\xa8\xd5\x82\xfb\x3f\x04\xfb\x1d\x67"
         "\xf8\xd1\xff\x40\x21\x05\x89\x7a\x7e\xaa\x74\xdb\x57\xcd\xa3\x36"
         "\xe9\x35\xf2\x43\x92\xda\x1c\x65\x68\xd3\x7e\x4c\xb0\x40\xa1\xaa"
         "\xa1\xb8\x82\xd7\xc5\x73\x69\x1a\x33\x29\xd4\xc5\x18\x86\x5b\x66"
         "\x32\x6b\xf5\x7d\x08\xc9\x5b\xf3\x74\x94\xe4\x4a\xf0\x93\x5e\x58"
         "\x76\xc0\xd5\x1e\x81\x2f\x75\xa1\x86\x7b\x21\x70\x47\xf4\x3b\x42"
         "\x61\x8b\x3c\x5a\xa8\xb2\x04\x0c\xac\x1c\xa3\xc9\x9a\xdd\xb0\xa8"
         "\xc2\x25\x17\xc4\xce\x59\x25\x2e\xd8\x28\xe3\x13\x1d\x37\xbe\x67"
         "\xa4\x2f\xe0\x75\x61\x7a\xb7\xee\xe3\x11\x27\xc9\x6c\x10\x0f\xc0"
         "\xc7\x65\x2e\x59\x4a\x3c\x18\xe4\x3e\xea\x41\xcb\x48\x0f\x20\x46"
         "\xd4\x3e\x2a\x10\xfb\x04\x57\x5b\x1e\x4a\xa1\xb5\x20\x7c\x1b\x45"
         "\x2c\xfe\x1f\xe9\x90\x33\x07\x39\xc7\x9f\xd5\x7f\xc6\x32\x28\x5c"
         "\x59\xff\x72\xc4\xcc\x3e\xdf\x88\x8c\xa0\x1a\x4e\x90\x5b\x00\x96"
         "\x35\xe1\x58\x5f\xa0\x15\x55\x9a\x6e\xd8\x6f\x40\x23\x73\x1c\xd8"
         "\xfb\x87\x8c\x1c\x95\x54\x4e\x75\x91\x8a\x04\x43\xfa\x3a\xb7\x5b"
         "\x00\x5b\x00\xe8\x79\x30\x16\xf9\x0d\x53\xfb\xa2\x98\xbd\xda\xbf"
         "\x62\x87\xf9\x19\x42\x16\x4c\xea\xee\xbf\x0d\x00\xc6\x49\x4d\x4c"
         "\x59\x94\xf7\xbf\xf5\x92\x2c\x7c\x81\xf4\x92\x2e\xba\x96\x3a\x0e"
         "\x86\xc8\x92\x6a\x2f\x9f\x48\x28\xe0\x0b\xd6\xc0\x1e\xad\xed\xb4"
         "\x05\xf7\x4b\xce\x52\x1b\x44\xc0\xf6\x55\x3a\x5f\x2d\x41\x11\x54"
         "\x06\xcb\xbf\x81\x27\x74\xc7\x44\x5c\xf6\x08\x1d\xfc\x26\x4a\xb5"
         "\xfb\xbd\x23\x16\x23\xf2\x72\x09\x28\x6b\x2b\x9b\x3d\x4f\x9d\x49"
         "\xbe\x4a\x9b\x2e\x88\xbb\xf4\xc2\xa9\xb3\x8d\x77\x30\x9d\x26\x75"
         "\xd6\x8c\x2e\x03\x84\x50\xc6\xe1\x80\xbd\xac\x08\x75\x27\xe5\xd9"
         "\x55\x11\x0d\xbc\x88\x1e\x19\xc6\x6c\x92\x0f\xbf\xb1\xb1\xba\xcd"
         "\x77\xc8\xae\x55\x8e\x1f\x32\x4a\xae\xea\x8b\x34\x04\xe1\xb6\xf8"
         "\xc3\xaa\x01\x4b\xf4\xa3\x1d\xe9\x58\xd6\x15\x37\x4f\x4e\x02\xea"
         "\x99\xe1\xeb\xc5\x57\xf1\xb3\x45\xdf\x14\x40\xba\xd4\x52\x47\x60"
         "\xbe\x6c\x28\x4e\xa5\x6b\xc2\xd7\x29\xb1\xe1\x64\xb7\xbb\x8e\xee"
         "\x6c\x4a\xf0\x2d\x52\x91\x67\xc8\x23\x2f\x4f\x2e\x9c\x2e\x70\xcd"
         "\x39\xbf\x73\xe6\xca\x50\x00\x9c\x00\xc2\x02\x3c\x73\xfe\x61\x6e"
         "\xf7\x6a\x22\x2d\x5a\x4a\x1f\x5c\x20\x7c\xcb\xa3\x09\xda\x3e\xde"
         "\xbe\x2e\x36\xec\x73\x7b\xa4\xe5\xd1\xcf\x15\x2d\x9f\xd2\xb5\xaa"
         "\x84\x03\x09\x97\xfa\xa6\x22\x03\xa1\x77\x82\xf7\x52\x59\xf1\x1b"
         "\x2c\x81\xe3\xe6\x75\x50\x84\x48\x3e\xc9\xfb\xd6\xf9\x57\x31\x30"
         "\x42\xab\x6d\xf7\x36\xbd\x47\x23\x68\x1a\x77\xf3\xbc\x1e\x3f\x4c"
         "\x08\x73\x26\x09\xfb\xe6\x30\x71\xa8\xd3\x2e\x3a\x87\x1b\x20\x20"
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
.*===pluviographicspermatorrhea
*/
      static char read_00003_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x70\x6c\x75\x76\x69\x6f\x67\x72\x61\x70\x68"
         "\x69\x63\x73\x70\x65\x72\x6d\x61\x74\x6f\x72\x72\x68\x65\x61";
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
.*===hetericismswayable
*/
      static char read_00004_00000_regex[] = 
         "\x2e\x2a\x3d\x3d\x3d\x68\x65\x74\x65\x72\x69\x63\x69\x73\x6d\x73"
         "\x77\x61\x79\x61\x62\x6c\x65";
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
