#include <libpov.h>

unsigned int SendBytes(int fd, char *buf, unsigned int len) {
        size_t tx_bytes;
        unsigned int total_bytes = 0;

        while (total_bytes < len) {
                if (transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
                        return(0);
                }
                if (tx_bytes != 1) {
                        return(0);
                }
                total_bytes++;
        }

        return(total_bytes);
}

int main(void) {
   int final_submit;
   negotiate_type2();
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x09\x00\x00\x00\x11\x22\x00\x00\xa0\x08\x00\x00\x11\x27\x00\x08"
         "\x48\x08\x00\x00\xa0\x08\x00\x00\x11\x58\x00\x08\x48\x08\x00\x00"
         "\xa0\x08\x00\x00\x21\x10\x00\x1e";
      static unsigned int write_00000_00000_len = 40;
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
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x0a";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
      if (read_00000_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d"
         "\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d"
         "\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d";
      read_00000_ptr += data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 44);
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x52\x30\x3a\x09\x30\x78\x32\x32\x32\x37\x35\x38\x30\x30\x09\x52"
         "\x31\x3a\x09\x30\x78\x30\x30\x30\x30\x30\x30\x35\x38";
      read_00001_ptr += data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 29);
      free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** length read
      read_00002_len = 21;
      read_00002 = (unsigned char*)malloc(read_00002_len);
      int read_00002_res = length_read(0, read_00002, read_00002_len);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x52\x32\x3a\x09\x30\x78\x30\x30\x30\x30\x30\x30\x30\x30\x09\x52"
         "\x33\x3a\x09\x30\x78";
      read_00002_ptr += data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 21);
      free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      char gimme[10];
      int read_00003_res;

      //**** length read
/*      read_00003_len = 8;
      read_00003 = (unsigned char*)malloc(read_00003_len);
      int read_00003_res = length_read(0, read_00003, read_00003_len);
      if (read_00003_res) {} //silence unused variable warning
*/
      //**** read assign to var "ASCII_TYPE2_VALUE" from slice
      read_00003_res = length_read(0, (unsigned char *)gimme, 8);
      gimme[8] = 0;
      if (read_00003_res) {}
      final_submit = strtoul(gimme, NULL, 16);
      
      free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** submitting type 2 POV results
   SendBytes(3, (char*)&final_submit, 4);
}
