#include <libpov.h>
int main(void) {
   negotiate_type2();
   unsigned char flag[4] = {0, 0, 0, 0};

   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x03\x03\x03\x03";
      static unsigned int write_00000_00000_len = 4;
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
      read_00000_len = 3;
      read_00000 = (unsigned char*)malloc(read_00000_len);
      int read_00000_res = length_read(0, read_00000, read_00000_len);

      // first 3 byte of flag come from stamp0
      for (int i = 0; i < 3; i++)
         flag[i] = read_00000[i];

      if (read_00000_res) {} //silence unused variable warning
      //**** read assign to var "stamp0" from slice
      assign_from_slice("stamp0", read_00000, read_00000_len - read_00000_ptr, 0, 3, 0);
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** length read
      read_00001_len = 2;
      read_00001 = (unsigned char*)malloc(read_00001_len);
      int read_00001_res = length_read(0, read_00001, read_00001_len);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x04\x04";
      read_00001_ptr += data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 2);
      free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00000[] = 
         "\x03\x03\x03\x03";
      static unsigned int write_00001_00000_len = 4;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 3;
      read_00002 = (unsigned char*)malloc(read_00002_len);
      int read_00002_res = length_read(0, read_00002, read_00002_len);

      // 4th byte of flag comes from stamp1
      flag[3] = read_00002[0];

      if (read_00002_res) {} //silence unused variable warning
      //**** read assign to var "stamp1" from slice
      assign_from_slice("stamp1", read_00002, read_00002_len - read_00002_ptr, 0, 3, 0);
      free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** length read
      read_00003_len = 2;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x04\x04";
      read_00003_ptr += data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 2);
      free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x00\x0f\xf0\xff";
      static unsigned int write_00002_00000_len = 4;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** length read
      read_00004_len = 2;
      read_00004 = (unsigned char*)malloc(read_00004_len);
      int read_00004_res = length_read(0, read_00004, read_00004_len);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x04\x17";
      read_00004_ptr += data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 2);
      free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** submitting type 2 POV results
   // submit_type2("flag");
   type2_submit(flag, 4);
}
