#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xaa\xaa\xaa\xaa";
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
         "\xc3\xac";
      static unsigned int write_00001_00000_len = 2;
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
         "\xb1";
      static unsigned int write_00002_00000_len = 1;
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
         "\x04";
      static unsigned int write_00003_00000_len = 1;
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
         "\x00\x00";
      static unsigned int write_00004_00000_len = 2;
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
         "\x00\x00";
      static unsigned int write_00005_00000_len = 2;
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
         "\x00\x00";
      static unsigned int write_00006_00000_len = 2;
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
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00007_00000_len = 4;
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
         "\xc3\xac";
      static unsigned int write_00008_00000_len = 2;
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
         "\xb1";
      static unsigned int write_00009_00000_len = 1;
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
         "\x04";
      static unsigned int write_00010_00000_len = 1;
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
         "\x0a\x00";
      static unsigned int write_00011_00000_len = 2;
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
         "\x00\x00";
      static unsigned int write_00012_00000_len = 2;
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
         "\x00\x0a";
      static unsigned int write_00013_00000_len = 2;
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
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00014_00000_len = 4;
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
         "\xc3\xac";
      static unsigned int write_00015_00000_len = 2;
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
         "\xb1";
      static unsigned int write_00016_00000_len = 1;
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
         "\x04";
      static unsigned int write_00017_00000_len = 1;
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
         "\x0b\x00";
      static unsigned int write_00018_00000_len = 2;
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00019_00000[] = 
         "\x00\x00";
      static unsigned int write_00019_00000_len = 2;
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00020_00000[] = 
         "\x00\x0b";
      static unsigned int write_00020_00000_len = 2;
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00021_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00021_00000_len = 4;
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00022_00000[] = 
         "\xc3\xac";
      static unsigned int write_00022_00000_len = 2;
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00023_00000[] = 
         "\xb1";
      static unsigned int write_00023_00000_len = 1;
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00024_00000[] = 
         "\x04";
      static unsigned int write_00024_00000_len = 1;
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_buf(write_00024, &write_00024_len, write_00024_00000, write_00024_00000_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00025_00000[] = 
         "\x0c\x00";
      static unsigned int write_00025_00000_len = 2;
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00026_00000[] = 
         "\x00\x00";
      static unsigned int write_00026_00000_len = 2;
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00027_00000[] = 
         "\x00\x0c";
      static unsigned int write_00027_00000_len = 2;
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00028_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00028_00000_len = 4;
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00029_00000[] = 
         "\xc3\xac";
      static unsigned int write_00029_00000_len = 2;
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = cgc_append_buf(write_00029, &write_00029_len, write_00029_00000, write_00029_00000_len);
      if (write_00029_len > 0) {
         cgc_transmit_all(1, write_00029, write_00029_len);
      }
      cgc_free(write_00029);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00030_00000[] = 
         "\xb1";
      static unsigned int write_00030_00000_len = 1;
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00031_00000[] = 
         "\x04";
      static unsigned int write_00031_00000_len = 1;
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00032_00000[] = 
         "\x0d\x00";
      static unsigned int write_00032_00000_len = 2;
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = cgc_append_buf(write_00032, &write_00032_len, write_00032_00000, write_00032_00000_len);
      if (write_00032_len > 0) {
         cgc_transmit_all(1, write_00032, write_00032_len);
      }
      cgc_free(write_00032);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00033_00000[] = 
         "\x00\x00";
      static unsigned int write_00033_00000_len = 2;
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_buf(write_00033, &write_00033_len, write_00033_00000, write_00033_00000_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00034_00000[] = 
         "\x00\x0d";
      static unsigned int write_00034_00000_len = 2;
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_buf(write_00034, &write_00034_len, write_00034_00000, write_00034_00000_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00035_00000_len = 4;
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00036_00000[] = 
         "\xc3\xac";
      static unsigned int write_00036_00000_len = 2;
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = cgc_append_buf(write_00036, &write_00036_len, write_00036_00000, write_00036_00000_len);
      if (write_00036_len > 0) {
         cgc_transmit_all(1, write_00036, write_00036_len);
      }
      cgc_free(write_00036);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\xb8";
      static unsigned int write_00037_00000_len = 1;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\x0a";
      static unsigned int write_00038_00000_len = 1;
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = cgc_append_buf(write_00038, &write_00038_len, write_00038_00000, write_00038_00000_len);
      if (write_00038_len > 0) {
         cgc_transmit_all(1, write_00038, write_00038_len);
      }
      cgc_free(write_00038);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00039_00000[] = 
         "\x00\x10";
      static unsigned int write_00039_00000_len = 2;
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = cgc_append_buf(write_00039, &write_00039_len, write_00039_00000, write_00039_00000_len);
      if (write_00039_len > 0) {
         cgc_transmit_all(1, write_00039, write_00039_len);
      }
      cgc_free(write_00039);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00040_00000[] = 
         "\x00\x00";
      static unsigned int write_00040_00000_len = 2;
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_buf(write_00040, &write_00040_len, write_00040_00000, write_00040_00000_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00041_00000[] = 
         "\x00\x00";
      static unsigned int write_00041_00000_len = 2;
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_buf(write_00041, &write_00041_len, write_00041_00000, write_00041_00000_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00042_00000[] = 
         "\x00\x00";
      static unsigned int write_00042_00000_len = 2;
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = cgc_append_buf(write_00042, &write_00042_len, write_00042_00000, write_00042_00000_len);
      if (write_00042_len > 0) {
         cgc_transmit_all(1, write_00042, write_00042_len);
      }
      cgc_free(write_00042);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00043_00000[] = 
         "\x00\x00";
      static unsigned int write_00043_00000_len = 2;
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_buf(write_00043, &write_00043_len, write_00043_00000, write_00043_00000_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00044_00000[] = 
         "\x00\x10";
      static unsigned int write_00044_00000_len = 2;
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = cgc_append_buf(write_00044, &write_00044_len, write_00044_00000, write_00044_00000_len);
      if (write_00044_len > 0) {
         cgc_transmit_all(1, write_00044, write_00044_len);
      }
      cgc_free(write_00044);
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
         "\x3c\x48\x54\x4d\x4c\x3e\x0a";
      read_00000_ptr += cgc_data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 7);
      cgc_free(read_00000);
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
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
      if (read_00001_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00001_00000[] = 
         "\x3c\x48\x45\x41\x44\x3e\x4d\x65\x73\x73\x61\x67\x65\x73\x3c\x2f"
         "\x48\x45\x41\x44\x3e\x0a";
      read_00001_ptr += cgc_data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 22);
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00002;
      unsigned int read_00002_len;
      unsigned int read_00002_ptr = 0;
      //**** delimited read
      static unsigned char read_00002_delim[] = 
         "\x0a";
      read_00002 = NULL;
      read_00002_len = 0;
      int read_00002_res = cgc_delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 1);
      if (read_00002_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00002_00000[] = 
         "\x3c\x42\x4f\x44\x59\x3e\x0a";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 7);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00003;
      unsigned int read_00003_len;
      unsigned int read_00003_ptr = 0;
      //**** delimited read
      static unsigned char read_00003_delim[] = 
         "\x0a";
      read_00003 = NULL;
      read_00003_len = 0;
      int read_00003_res = cgc_delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 1);
      if (read_00003_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00003_00000[] = 
         "\x3c\x62\x3e\x4d\x65\x73\x73\x61\x67\x65\x20\x30\x3a\x3c\x2f\x62"
         "\x3e\x3c\x42\x52\x3e\x0a";
      read_00003_ptr += cgc_data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 22);
      cgc_free(read_00003);
      if (read_00003_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00004;
      unsigned int read_00004_len;
      unsigned int read_00004_ptr = 0;
      //**** delimited read
      static unsigned char read_00004_delim[] = 
         "\x0a";
      read_00004 = NULL;
      read_00004_len = 0;
      int read_00004_res = cgc_delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 1);
      if (read_00004_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00004_00000[] = 
         "\x3c\x62\x3e\x46\x72\x6f\x6d\x3a\x3c\x2f\x62\x3e\x20\x30\x3c\x42"
         "\x52\x3e\x0a";
      read_00004_ptr += cgc_data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 19);
      cgc_free(read_00004);
      if (read_00004_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00005;
      unsigned int read_00005_len;
      unsigned int read_00005_ptr = 0;
      //**** delimited read
      static unsigned char read_00005_delim[] = 
         "\x0a";
      read_00005 = NULL;
      read_00005_len = 0;
      int read_00005_res = cgc_delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 1);
      if (read_00005_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00005_00000[] = 
         "\x3c\x62\x3e\x54\x6f\x3a\x3c\x2f\x62\x3e\x20\x31\x36\x3c\x42\x52"
         "\x3e\x0a";
      read_00005_ptr += cgc_data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 18);
      cgc_free(read_00005);
      if (read_00005_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00006;
      unsigned int read_00006_len;
      unsigned int read_00006_ptr = 0;
      //**** delimited read
      static unsigned char read_00006_delim[] = 
         "\x0a";
      read_00006 = NULL;
      read_00006_len = 0;
      int read_00006_res = cgc_delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 1);
      if (read_00006_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00006_00000[] = 
         "\x3c\x62\x3e\x4d\x65\x73\x73\x61\x67\x65\x20\x44\x61\x74\x61\x3a"
         "\x3c\x2f\x62\x3e\x3c\x42\x52\x3e\x0a";
      read_00006_ptr += cgc_data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 25);
      cgc_free(read_00006);
      if (read_00006_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00007;
      unsigned int read_00007_len;
      unsigned int read_00007_ptr = 0;
      //**** length read
      read_00007_len = 8;
      read_00007 = (unsigned char*)cgc_malloc(read_00007_len);
      int read_00007_res = cgc_length_read(0, read_00007, read_00007_len);
      if (read_00007_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00007_00000[] = 
         "\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x5f";
      read_00007_ptr += cgc_data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 8);
      cgc_free(read_00007);
      if (read_00007_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00008;
      unsigned int read_00008_len;
      unsigned int read_00008_ptr = 0;
      //**** delimited read
      static unsigned char read_00008_delim[] = 
         "\x0a";
      read_00008 = NULL;
      read_00008_len = 0;
      int read_00008_res = cgc_delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 1);
      if (read_00008_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00008_00000[] = 
         "\x0a";
      read_00008_ptr += cgc_data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 1);
      cgc_free(read_00008);
      if (read_00008_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00009;
      unsigned int read_00009_len;
      unsigned int read_00009_ptr = 0;
      //**** delimited read
      static unsigned char read_00009_delim[] = 
         "\x0a";
      read_00009 = NULL;
      read_00009_len = 0;
      int read_00009_res = cgc_delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 1);
      if (read_00009_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00009_00000[] = 
         "\x3c\x2f\x42\x4f\x44\x59\x3e\x0a";
      read_00009_ptr += cgc_data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 8);
      cgc_free(read_00009);
      if (read_00009_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00010;
      unsigned int read_00010_len;
      unsigned int read_00010_ptr = 0;
      //**** delimited read
      static unsigned char read_00010_delim[] = 
         "\x0a";
      read_00010 = NULL;
      read_00010_len = 0;
      int read_00010_res = cgc_delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 1);
      if (read_00010_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00010_00000[] = 
         "\x3c\x2f\x48\x54\x4d\x4c\x3e\x0a";
      read_00010_ptr += cgc_data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 8);
      cgc_free(read_00010);
      if (read_00010_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00045_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00045_00000_len = 4;
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = cgc_append_buf(write_00045, &write_00045_len, write_00045_00000, write_00045_00000_len);
      if (write_00045_len > 0) {
         cgc_transmit_all(1, write_00045, write_00045_len);
      }
      cgc_free(write_00045);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00046_00000[] = 
         "\xc3\xac";
      static unsigned int write_00046_00000_len = 2;
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_buf(write_00046, &write_00046_len, write_00046_00000, write_00046_00000_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00047_00000[] = 
         "\xb1";
      static unsigned int write_00047_00000_len = 1;
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = cgc_append_buf(write_00047, &write_00047_len, write_00047_00000, write_00047_00000_len);
      if (write_00047_len > 0) {
         cgc_transmit_all(1, write_00047, write_00047_len);
      }
      cgc_free(write_00047);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00048_00000[] = 
         "\x04";
      static unsigned int write_00048_00000_len = 1;
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_buf(write_00048, &write_00048_len, write_00048_00000, write_00048_00000_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00049_00000[] = 
         "\x0e\x00";
      static unsigned int write_00049_00000_len = 2;
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_buf(write_00049, &write_00049_len, write_00049_00000, write_00049_00000_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00050_00000[] = 
         "\x00\x00";
      static unsigned int write_00050_00000_len = 2;
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = cgc_append_buf(write_00050, &write_00050_len, write_00050_00000, write_00050_00000_len);
      if (write_00050_len > 0) {
         cgc_transmit_all(1, write_00050, write_00050_len);
      }
      cgc_free(write_00050);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00051_00000[] = 
         "\x00\x0e";
      static unsigned int write_00051_00000_len = 2;
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = cgc_append_buf(write_00051, &write_00051_len, write_00051_00000, write_00051_00000_len);
      if (write_00051_len > 0) {
         cgc_transmit_all(1, write_00051, write_00051_len);
      }
      cgc_free(write_00051);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00052_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00052_00000_len = 4;
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_buf(write_00052, &write_00052_len, write_00052_00000, write_00052_00000_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00053_00000[] = 
         "\xc3\xac";
      static unsigned int write_00053_00000_len = 2;
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = cgc_append_buf(write_00053, &write_00053_len, write_00053_00000, write_00053_00000_len);
      if (write_00053_len > 0) {
         cgc_transmit_all(1, write_00053, write_00053_len);
      }
      cgc_free(write_00053);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00054_00000[] = 
         "\xb1";
      static unsigned int write_00054_00000_len = 1;
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = cgc_append_buf(write_00054, &write_00054_len, write_00054_00000, write_00054_00000_len);
      if (write_00054_len > 0) {
         cgc_transmit_all(1, write_00054, write_00054_len);
      }
      cgc_free(write_00054);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00055_00000[] = 
         "\x04";
      static unsigned int write_00055_00000_len = 1;
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_buf(write_00055, &write_00055_len, write_00055_00000, write_00055_00000_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00056_00000[] = 
         "\x0f\x00";
      static unsigned int write_00056_00000_len = 2;
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = cgc_append_buf(write_00056, &write_00056_len, write_00056_00000, write_00056_00000_len);
      if (write_00056_len > 0) {
         cgc_transmit_all(1, write_00056, write_00056_len);
      }
      cgc_free(write_00056);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00057_00000[] = 
         "\x00\x00";
      static unsigned int write_00057_00000_len = 2;
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = cgc_append_buf(write_00057, &write_00057_len, write_00057_00000, write_00057_00000_len);
      if (write_00057_len > 0) {
         cgc_transmit_all(1, write_00057, write_00057_len);
      }
      cgc_free(write_00057);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00058_00000[] = 
         "\x00\x0f";
      static unsigned int write_00058_00000_len = 2;
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_buf(write_00058, &write_00058_len, write_00058_00000, write_00058_00000_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00059_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00059_00000_len = 4;
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = cgc_append_buf(write_00059, &write_00059_len, write_00059_00000, write_00059_00000_len);
      if (write_00059_len > 0) {
         cgc_transmit_all(1, write_00059, write_00059_len);
      }
      cgc_free(write_00059);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00060_00000[] = 
         "\xc3\xac";
      static unsigned int write_00060_00000_len = 2;
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = cgc_append_buf(write_00060, &write_00060_len, write_00060_00000, write_00060_00000_len);
      if (write_00060_len > 0) {
         cgc_transmit_all(1, write_00060, write_00060_len);
      }
      cgc_free(write_00060);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00061_00000[] = 
         "\xbb";
      static unsigned int write_00061_00000_len = 1;
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_buf(write_00061, &write_00061_len, write_00061_00000, write_00061_00000_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00062_00000[] = 
         "\x04";
      static unsigned int write_00062_00000_len = 1;
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = cgc_append_buf(write_00062, &write_00062_len, write_00062_00000, write_00062_00000_len);
      if (write_00062_len > 0) {
         cgc_transmit_all(1, write_00062, write_00062_len);
      }
      cgc_free(write_00062);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00063_00000[] = 
         "\x01\x00";
      static unsigned int write_00063_00000_len = 2;
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = cgc_append_buf(write_00063, &write_00063_len, write_00063_00000, write_00063_00000_len);
      if (write_00063_len > 0) {
         cgc_transmit_all(1, write_00063, write_00063_len);
      }
      cgc_free(write_00063);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00064_00000[] = 
         "\x00\x00";
      static unsigned int write_00064_00000_len = 2;
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_buf(write_00064, &write_00064_len, write_00064_00000, write_00064_00000_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00065_00000[] = 
         "\x00\x01";
      static unsigned int write_00065_00000_len = 2;
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = cgc_append_buf(write_00065, &write_00065_len, write_00065_00000, write_00065_00000_len);
      if (write_00065_len > 0) {
         cgc_transmit_all(1, write_00065, write_00065_len);
      }
      cgc_free(write_00065);
   } while (0);
   do {
      unsigned char *read_00011;
      unsigned int read_00011_len;
      unsigned int read_00011_ptr = 0;
      //**** delimited read
      static unsigned char read_00011_delim[] = 
         "\x0a";
      read_00011 = NULL;
      read_00011_len = 0;
      int read_00011_res = cgc_delimited_read(0, &read_00011, &read_00011_len, read_00011_delim, 1);
      if (read_00011_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00011_00000[] = 
         "\x3c\x48\x54\x4d\x4c\x3e\x0a";
      read_00011_ptr += cgc_data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 7);
      cgc_free(read_00011);
      if (read_00011_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00012;
      unsigned int read_00012_len;
      unsigned int read_00012_ptr = 0;
      //**** delimited read
      static unsigned char read_00012_delim[] = 
         "\x0a";
      read_00012 = NULL;
      read_00012_len = 0;
      int read_00012_res = cgc_delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 1);
      if (read_00012_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00012_00000[] = 
         "\x3c\x48\x45\x41\x44\x3e\x4d\x65\x73\x73\x61\x67\x65\x73\x3c\x2f"
         "\x48\x45\x41\x44\x3e\x0a";
      read_00012_ptr += cgc_data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 22);
      cgc_free(read_00012);
      if (read_00012_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00013;
      unsigned int read_00013_len;
      unsigned int read_00013_ptr = 0;
      //**** delimited read
      static unsigned char read_00013_delim[] = 
         "\x0a";
      read_00013 = NULL;
      read_00013_len = 0;
      int read_00013_res = cgc_delimited_read(0, &read_00013, &read_00013_len, read_00013_delim, 1);
      if (read_00013_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00013_00000[] = 
         "\x3c\x42\x4f\x44\x59\x3e\x0a";
      read_00013_ptr += cgc_data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 7);
      cgc_free(read_00013);
      if (read_00013_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00014;
      unsigned int read_00014_len;
      unsigned int read_00014_ptr = 0;
      //**** delimited read
      static unsigned char read_00014_delim[] = 
         "\x0a";
      read_00014 = NULL;
      read_00014_len = 0;
      int read_00014_res = cgc_delimited_read(0, &read_00014, &read_00014_len, read_00014_delim, 1);
      if (read_00014_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00014_00000[] = 
         "\x3c\x62\x3e\x4d\x65\x73\x73\x61\x67\x65\x20\x31\x3a\x3c\x2f\x62"
         "\x3e\x3c\x42\x52\x3e\x0a";
      read_00014_ptr += cgc_data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 22);
      cgc_free(read_00014);
      if (read_00014_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00015;
      unsigned int read_00015_len;
      unsigned int read_00015_ptr = 0;
      //**** delimited read
      static unsigned char read_00015_delim[] = 
         "\x0a";
      read_00015 = NULL;
      read_00015_len = 0;
      int read_00015_res = cgc_delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 1);
      if (read_00015_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00015_00000[] = 
         "\x3c\x62\x3e\x46\x72\x6f\x6d\x3a\x3c\x2f\x62\x3e\x20\x30\x3c\x42"
         "\x52\x3e\x0a";
      read_00015_ptr += cgc_data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 19);
      cgc_free(read_00015);
      if (read_00015_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00016;
      unsigned int read_00016_len;
      unsigned int read_00016_ptr = 0;
      //**** delimited read
      static unsigned char read_00016_delim[] = 
         "\x0a";
      read_00016 = NULL;
      read_00016_len = 0;
      int read_00016_res = cgc_delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 1);
      if (read_00016_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00016_00000[] = 
         "\x3c\x62\x3e\x54\x6f\x3a\x3c\x2f\x62\x3e\x20\x30\x3c\x42\x52\x3e"
         "\x0a";
      read_00016_ptr += cgc_data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 17);
      cgc_free(read_00016);
      if (read_00016_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00017;
      unsigned int read_00017_len;
      unsigned int read_00017_ptr = 0;
      //**** delimited read
      static unsigned char read_00017_delim[] = 
         "\x0a";
      read_00017 = NULL;
      read_00017_len = 0;
      int read_00017_res = cgc_delimited_read(0, &read_00017, &read_00017_len, read_00017_delim, 1);
      if (read_00017_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00017_00000[] = 
         "\x3c\x62\x3e\x4d\x65\x73\x73\x61\x67\x65\x20\x44\x61\x74\x61\x3a"
         "\x3c\x2f\x62\x3e\x3c\x42\x52\x3e\x0a";
      read_00017_ptr += cgc_data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 25);
      cgc_free(read_00017);
      if (read_00017_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00018;
      unsigned int read_00018_len;
      unsigned int read_00018_ptr = 0;
      //**** length read
      read_00018_len = 2;
      read_00018 = (unsigned char*)cgc_malloc(read_00018_len);
      int read_00018_res = cgc_length_read(0, read_00018, read_00018_len);
      if (read_00018_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00018_00000[] = 
         "\x5f\x5f";
      read_00018_ptr += cgc_data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 2);
      cgc_free(read_00018);
      if (read_00018_ptr) {}  //silence unused variable warning if any
   } while (0);
   //*** delay
   cgc_delay(100);
   do {
      unsigned char *read_00019;
      unsigned int read_00019_len;
      unsigned int read_00019_ptr = 0;
      //**** delimited read
      static unsigned char read_00019_delim[] = 
         "\x0a";
      read_00019 = NULL;
      read_00019_len = 0;
      int read_00019_res = cgc_delimited_read(0, &read_00019, &read_00019_len, read_00019_delim, 1);
      if (read_00019_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00019_00000[] = 
         "\x0a";
      read_00019_ptr += cgc_data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 1);
      cgc_free(read_00019);
      if (read_00019_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00020;
      unsigned int read_00020_len;
      unsigned int read_00020_ptr = 0;
      //**** delimited read
      static unsigned char read_00020_delim[] = 
         "\x0a";
      read_00020 = NULL;
      read_00020_len = 0;
      int read_00020_res = cgc_delimited_read(0, &read_00020, &read_00020_len, read_00020_delim, 1);
      if (read_00020_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00020_00000[] = 
         "\x3c\x2f\x42\x4f\x44\x59\x3e\x0a";
      read_00020_ptr += cgc_data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 8);
      cgc_free(read_00020);
      if (read_00020_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      unsigned char *read_00021;
      unsigned int read_00021_len;
      unsigned int read_00021_ptr = 0;
      //**** delimited read
      static unsigned char read_00021_delim[] = 
         "\x0a";
      read_00021 = NULL;
      read_00021_len = 0;
      int read_00021_res = cgc_delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 1);
      if (read_00021_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00021_00000[] = 
         "\x3c\x2f\x48\x54\x4d\x4c\x3e\x0a";
      read_00021_ptr += cgc_data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 8);
      cgc_free(read_00021);
      if (read_00021_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00066_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00066_00000_len = 4;
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = cgc_append_buf(write_00066, &write_00066_len, write_00066_00000, write_00066_00000_len);
      if (write_00066_len > 0) {
         cgc_transmit_all(1, write_00066, write_00066_len);
      }
      cgc_free(write_00066);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00067_00000[] = 
         "\xc3\xac";
      static unsigned int write_00067_00000_len = 2;
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_buf(write_00067, &write_00067_len, write_00067_00000, write_00067_00000_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00068_00000[] = 
         "\xb1";
      static unsigned int write_00068_00000_len = 1;
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = cgc_append_buf(write_00068, &write_00068_len, write_00068_00000, write_00068_00000_len);
      if (write_00068_len > 0) {
         cgc_transmit_all(1, write_00068, write_00068_len);
      }
      cgc_free(write_00068);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00069_00000[] = 
         "\x04";
      static unsigned int write_00069_00000_len = 1;
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = cgc_append_buf(write_00069, &write_00069_len, write_00069_00000, write_00069_00000_len);
      if (write_00069_len > 0) {
         cgc_transmit_all(1, write_00069, write_00069_len);
      }
      cgc_free(write_00069);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00070_00000[] = 
         "\x00\x01";
      static unsigned int write_00070_00000_len = 2;
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_buf(write_00070, &write_00070_len, write_00070_00000, write_00070_00000_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00071_00000[] = 
         "\x00\x00";
      static unsigned int write_00071_00000_len = 2;
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = cgc_append_buf(write_00071, &write_00071_len, write_00071_00000, write_00071_00000_len);
      if (write_00071_len > 0) {
         cgc_transmit_all(1, write_00071, write_00071_len);
      }
      cgc_free(write_00071);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00072_00000[] = 
         "\x00\x01";
      static unsigned int write_00072_00000_len = 2;
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = cgc_append_buf(write_00072, &write_00072_len, write_00072_00000, write_00072_00000_len);
      if (write_00072_len > 0) {
         cgc_transmit_all(1, write_00072, write_00072_len);
      }
      cgc_free(write_00072);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00073_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00073_00000_len = 4;
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_buf(write_00073, &write_00073_len, write_00073_00000, write_00073_00000_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00074_00000[] = 
         "\xc3\xac";
      static unsigned int write_00074_00000_len = 2;
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = cgc_append_buf(write_00074, &write_00074_len, write_00074_00000, write_00074_00000_len);
      if (write_00074_len > 0) {
         cgc_transmit_all(1, write_00074, write_00074_len);
      }
      cgc_free(write_00074);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00075_00000[] = 
         "\xb1";
      static unsigned int write_00075_00000_len = 1;
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = cgc_append_buf(write_00075, &write_00075_len, write_00075_00000, write_00075_00000_len);
      if (write_00075_len > 0) {
         cgc_transmit_all(1, write_00075, write_00075_len);
      }
      cgc_free(write_00075);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00076_00000[] = 
         "\x04";
      static unsigned int write_00076_00000_len = 1;
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_buf(write_00076, &write_00076_len, write_00076_00000, write_00076_00000_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00077_00000[] = 
         "\x00\x02";
      static unsigned int write_00077_00000_len = 2;
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = cgc_append_buf(write_00077, &write_00077_len, write_00077_00000, write_00077_00000_len);
      if (write_00077_len > 0) {
         cgc_transmit_all(1, write_00077, write_00077_len);
      }
      cgc_free(write_00077);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00078_00000[] = 
         "\x00\x00";
      static unsigned int write_00078_00000_len = 2;
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = cgc_append_buf(write_00078, &write_00078_len, write_00078_00000, write_00078_00000_len);
      if (write_00078_len > 0) {
         cgc_transmit_all(1, write_00078, write_00078_len);
      }
      cgc_free(write_00078);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00079_00000[] = 
         "\x00\x02";
      static unsigned int write_00079_00000_len = 2;
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_buf(write_00079, &write_00079_len, write_00079_00000, write_00079_00000_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00080_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00080_00000_len = 4;
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = cgc_append_buf(write_00080, &write_00080_len, write_00080_00000, write_00080_00000_len);
      if (write_00080_len > 0) {
         cgc_transmit_all(1, write_00080, write_00080_len);
      }
      cgc_free(write_00080);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00081_00000[] = 
         "\xc3\xac";
      static unsigned int write_00081_00000_len = 2;
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = cgc_append_buf(write_00081, &write_00081_len, write_00081_00000, write_00081_00000_len);
      if (write_00081_len > 0) {
         cgc_transmit_all(1, write_00081, write_00081_len);
      }
      cgc_free(write_00081);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00082_00000[] = 
         "\xb1";
      static unsigned int write_00082_00000_len = 1;
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_buf(write_00082, &write_00082_len, write_00082_00000, write_00082_00000_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00083_00000[] = 
         "\x04";
      static unsigned int write_00083_00000_len = 1;
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = cgc_append_buf(write_00083, &write_00083_len, write_00083_00000, write_00083_00000_len);
      if (write_00083_len > 0) {
         cgc_transmit_all(1, write_00083, write_00083_len);
      }
      cgc_free(write_00083);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00084_00000[] = 
         "\x00\x03";
      static unsigned int write_00084_00000_len = 2;
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = cgc_append_buf(write_00084, &write_00084_len, write_00084_00000, write_00084_00000_len);
      if (write_00084_len > 0) {
         cgc_transmit_all(1, write_00084, write_00084_len);
      }
      cgc_free(write_00084);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x00\x00";
      static unsigned int write_00085_00000_len = 2;
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = cgc_append_buf(write_00085, &write_00085_len, write_00085_00000, write_00085_00000_len);
      if (write_00085_len > 0) {
         cgc_transmit_all(1, write_00085, write_00085_len);
      }
      cgc_free(write_00085);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00086_00000[] = 
         "\x00\x03";
      static unsigned int write_00086_00000_len = 2;
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = cgc_append_buf(write_00086, &write_00086_len, write_00086_00000, write_00086_00000_len);
      if (write_00086_len > 0) {
         cgc_transmit_all(1, write_00086, write_00086_len);
      }
      cgc_free(write_00086);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00087_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00087_00000_len = 4;
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = cgc_append_buf(write_00087, &write_00087_len, write_00087_00000, write_00087_00000_len);
      if (write_00087_len > 0) {
         cgc_transmit_all(1, write_00087, write_00087_len);
      }
      cgc_free(write_00087);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00088_00000[] = 
         "\xc3\xac";
      static unsigned int write_00088_00000_len = 2;
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = cgc_append_buf(write_00088, &write_00088_len, write_00088_00000, write_00088_00000_len);
      if (write_00088_len > 0) {
         cgc_transmit_all(1, write_00088, write_00088_len);
      }
      cgc_free(write_00088);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00089_00000[] = 
         "\xb1";
      static unsigned int write_00089_00000_len = 1;
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = cgc_append_buf(write_00089, &write_00089_len, write_00089_00000, write_00089_00000_len);
      if (write_00089_len > 0) {
         cgc_transmit_all(1, write_00089, write_00089_len);
      }
      cgc_free(write_00089);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00090_00000[] = 
         "\x04";
      static unsigned int write_00090_00000_len = 1;
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = cgc_append_buf(write_00090, &write_00090_len, write_00090_00000, write_00090_00000_len);
      if (write_00090_len > 0) {
         cgc_transmit_all(1, write_00090, write_00090_len);
      }
      cgc_free(write_00090);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00091_00000[] = 
         "\x00\x04";
      static unsigned int write_00091_00000_len = 2;
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = cgc_append_buf(write_00091, &write_00091_len, write_00091_00000, write_00091_00000_len);
      if (write_00091_len > 0) {
         cgc_transmit_all(1, write_00091, write_00091_len);
      }
      cgc_free(write_00091);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00092_00000[] = 
         "\x00\x00";
      static unsigned int write_00092_00000_len = 2;
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = cgc_append_buf(write_00092, &write_00092_len, write_00092_00000, write_00092_00000_len);
      if (write_00092_len > 0) {
         cgc_transmit_all(1, write_00092, write_00092_len);
      }
      cgc_free(write_00092);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00093_00000[] = 
         "\x00\x04";
      static unsigned int write_00093_00000_len = 2;
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = cgc_append_buf(write_00093, &write_00093_len, write_00093_00000, write_00093_00000_len);
      if (write_00093_len > 0) {
         cgc_transmit_all(1, write_00093, write_00093_len);
      }
      cgc_free(write_00093);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00094_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00094_00000_len = 4;
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = cgc_append_buf(write_00094, &write_00094_len, write_00094_00000, write_00094_00000_len);
      if (write_00094_len > 0) {
         cgc_transmit_all(1, write_00094, write_00094_len);
      }
      cgc_free(write_00094);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00095_00000[] = 
         "\xc3\xac";
      static unsigned int write_00095_00000_len = 2;
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = cgc_append_buf(write_00095, &write_00095_len, write_00095_00000, write_00095_00000_len);
      if (write_00095_len > 0) {
         cgc_transmit_all(1, write_00095, write_00095_len);
      }
      cgc_free(write_00095);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00096_00000[] = 
         "\xb1";
      static unsigned int write_00096_00000_len = 1;
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = cgc_append_buf(write_00096, &write_00096_len, write_00096_00000, write_00096_00000_len);
      if (write_00096_len > 0) {
         cgc_transmit_all(1, write_00096, write_00096_len);
      }
      cgc_free(write_00096);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00097_00000[] = 
         "\x04";
      static unsigned int write_00097_00000_len = 1;
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = cgc_append_buf(write_00097, &write_00097_len, write_00097_00000, write_00097_00000_len);
      if (write_00097_len > 0) {
         cgc_transmit_all(1, write_00097, write_00097_len);
      }
      cgc_free(write_00097);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00098_00000[] = 
         "\x01\x01";
      static unsigned int write_00098_00000_len = 2;
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = cgc_append_buf(write_00098, &write_00098_len, write_00098_00000, write_00098_00000_len);
      if (write_00098_len > 0) {
         cgc_transmit_all(1, write_00098, write_00098_len);
      }
      cgc_free(write_00098);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00099_00000[] = 
         "\x00\x00";
      static unsigned int write_00099_00000_len = 2;
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = cgc_append_buf(write_00099, &write_00099_len, write_00099_00000, write_00099_00000_len);
      if (write_00099_len > 0) {
         cgc_transmit_all(1, write_00099, write_00099_len);
      }
      cgc_free(write_00099);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00100_00000[] = 
         "\x00\x02";
      static unsigned int write_00100_00000_len = 2;
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = cgc_append_buf(write_00100, &write_00100_len, write_00100_00000, write_00100_00000_len);
      if (write_00100_len > 0) {
         cgc_transmit_all(1, write_00100, write_00100_len);
      }
      cgc_free(write_00100);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00101_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00101_00000_len = 4;
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = cgc_append_buf(write_00101, &write_00101_len, write_00101_00000, write_00101_00000_len);
      if (write_00101_len > 0) {
         cgc_transmit_all(1, write_00101, write_00101_len);
      }
      cgc_free(write_00101);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00102_00000[] = 
         "\xc3\xac";
      static unsigned int write_00102_00000_len = 2;
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = cgc_append_buf(write_00102, &write_00102_len, write_00102_00000, write_00102_00000_len);
      if (write_00102_len > 0) {
         cgc_transmit_all(1, write_00102, write_00102_len);
      }
      cgc_free(write_00102);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00103_00000[] = 
         "\xb1";
      static unsigned int write_00103_00000_len = 1;
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = cgc_append_buf(write_00103, &write_00103_len, write_00103_00000, write_00103_00000_len);
      if (write_00103_len > 0) {
         cgc_transmit_all(1, write_00103, write_00103_len);
      }
      cgc_free(write_00103);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00104_00000[] = 
         "\x04";
      static unsigned int write_00104_00000_len = 1;
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = cgc_append_buf(write_00104, &write_00104_len, write_00104_00000, write_00104_00000_len);
      if (write_00104_len > 0) {
         cgc_transmit_all(1, write_00104, write_00104_len);
      }
      cgc_free(write_00104);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00105_00000[] = 
         "\x01\x04";
      static unsigned int write_00105_00000_len = 2;
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = cgc_append_buf(write_00105, &write_00105_len, write_00105_00000, write_00105_00000_len);
      if (write_00105_len > 0) {
         cgc_transmit_all(1, write_00105, write_00105_len);
      }
      cgc_free(write_00105);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00106_00000[] = 
         "\x00\x00";
      static unsigned int write_00106_00000_len = 2;
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = cgc_append_buf(write_00106, &write_00106_len, write_00106_00000, write_00106_00000_len);
      if (write_00106_len > 0) {
         cgc_transmit_all(1, write_00106, write_00106_len);
      }
      cgc_free(write_00106);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00107_00000[] = 
         "\x00\x05";
      static unsigned int write_00107_00000_len = 2;
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = cgc_append_buf(write_00107, &write_00107_len, write_00107_00000, write_00107_00000_len);
      if (write_00107_len > 0) {
         cgc_transmit_all(1, write_00107, write_00107_len);
      }
      cgc_free(write_00107);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00108_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00108_00000_len = 4;
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = cgc_append_buf(write_00108, &write_00108_len, write_00108_00000, write_00108_00000_len);
      if (write_00108_len > 0) {
         cgc_transmit_all(1, write_00108, write_00108_len);
      }
      cgc_free(write_00108);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00109_00000[] = 
         "\xc3\xac";
      static unsigned int write_00109_00000_len = 2;
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = cgc_append_buf(write_00109, &write_00109_len, write_00109_00000, write_00109_00000_len);
      if (write_00109_len > 0) {
         cgc_transmit_all(1, write_00109, write_00109_len);
      }
      cgc_free(write_00109);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00110_00000[] = 
         "\xb1";
      static unsigned int write_00110_00000_len = 1;
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = cgc_append_buf(write_00110, &write_00110_len, write_00110_00000, write_00110_00000_len);
      if (write_00110_len > 0) {
         cgc_transmit_all(1, write_00110, write_00110_len);
      }
      cgc_free(write_00110);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00111_00000[] = 
         "\x04";
      static unsigned int write_00111_00000_len = 1;
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = cgc_append_buf(write_00111, &write_00111_len, write_00111_00000, write_00111_00000_len);
      if (write_00111_len > 0) {
         cgc_transmit_all(1, write_00111, write_00111_len);
      }
      cgc_free(write_00111);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00112_00000[] = 
         "\x02\x04";
      static unsigned int write_00112_00000_len = 2;
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = cgc_append_buf(write_00112, &write_00112_len, write_00112_00000, write_00112_00000_len);
      if (write_00112_len > 0) {
         cgc_transmit_all(1, write_00112, write_00112_len);
      }
      cgc_free(write_00112);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00113_00000[] = 
         "\x00\x00";
      static unsigned int write_00113_00000_len = 2;
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = cgc_append_buf(write_00113, &write_00113_len, write_00113_00000, write_00113_00000_len);
      if (write_00113_len > 0) {
         cgc_transmit_all(1, write_00113, write_00113_len);
      }
      cgc_free(write_00113);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00114_00000[] = 
         "\x00\x06";
      static unsigned int write_00114_00000_len = 2;
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = cgc_append_buf(write_00114, &write_00114_len, write_00114_00000, write_00114_00000_len);
      if (write_00114_len > 0) {
         cgc_transmit_all(1, write_00114, write_00114_len);
      }
      cgc_free(write_00114);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00115_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00115_00000_len = 4;
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = cgc_append_buf(write_00115, &write_00115_len, write_00115_00000, write_00115_00000_len);
      if (write_00115_len > 0) {
         cgc_transmit_all(1, write_00115, write_00115_len);
      }
      cgc_free(write_00115);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00116_00000[] = 
         "\xc3\xac";
      static unsigned int write_00116_00000_len = 2;
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = cgc_append_buf(write_00116, &write_00116_len, write_00116_00000, write_00116_00000_len);
      if (write_00116_len > 0) {
         cgc_transmit_all(1, write_00116, write_00116_len);
      }
      cgc_free(write_00116);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00117_00000[] = 
         "\xb1";
      static unsigned int write_00117_00000_len = 1;
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = cgc_append_buf(write_00117, &write_00117_len, write_00117_00000, write_00117_00000_len);
      if (write_00117_len > 0) {
         cgc_transmit_all(1, write_00117, write_00117_len);
      }
      cgc_free(write_00117);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00118_00000[] = 
         "\x04";
      static unsigned int write_00118_00000_len = 1;
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = cgc_append_buf(write_00118, &write_00118_len, write_00118_00000, write_00118_00000_len);
      if (write_00118_len > 0) {
         cgc_transmit_all(1, write_00118, write_00118_len);
      }
      cgc_free(write_00118);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00119_00000[] = 
         "\x03\x04";
      static unsigned int write_00119_00000_len = 2;
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = cgc_append_buf(write_00119, &write_00119_len, write_00119_00000, write_00119_00000_len);
      if (write_00119_len > 0) {
         cgc_transmit_all(1, write_00119, write_00119_len);
      }
      cgc_free(write_00119);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00120_00000[] = 
         "\x00\x00";
      static unsigned int write_00120_00000_len = 2;
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = cgc_append_buf(write_00120, &write_00120_len, write_00120_00000, write_00120_00000_len);
      if (write_00120_len > 0) {
         cgc_transmit_all(1, write_00120, write_00120_len);
      }
      cgc_free(write_00120);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00121_00000[] = 
         "\x00\x07";
      static unsigned int write_00121_00000_len = 2;
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = cgc_append_buf(write_00121, &write_00121_len, write_00121_00000, write_00121_00000_len);
      if (write_00121_len > 0) {
         cgc_transmit_all(1, write_00121, write_00121_len);
      }
      cgc_free(write_00121);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00122_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00122_00000_len = 4;
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = cgc_append_buf(write_00122, &write_00122_len, write_00122_00000, write_00122_00000_len);
      if (write_00122_len > 0) {
         cgc_transmit_all(1, write_00122, write_00122_len);
      }
      cgc_free(write_00122);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00123_00000[] = 
         "\xc3\xac";
      static unsigned int write_00123_00000_len = 2;
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = cgc_append_buf(write_00123, &write_00123_len, write_00123_00000, write_00123_00000_len);
      if (write_00123_len > 0) {
         cgc_transmit_all(1, write_00123, write_00123_len);
      }
      cgc_free(write_00123);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00124_00000[] = 
         "\xb1";
      static unsigned int write_00124_00000_len = 1;
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = cgc_append_buf(write_00124, &write_00124_len, write_00124_00000, write_00124_00000_len);
      if (write_00124_len > 0) {
         cgc_transmit_all(1, write_00124, write_00124_len);
      }
      cgc_free(write_00124);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00125_00000[] = 
         "\x04";
      static unsigned int write_00125_00000_len = 1;
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = cgc_append_buf(write_00125, &write_00125_len, write_00125_00000, write_00125_00000_len);
      if (write_00125_len > 0) {
         cgc_transmit_all(1, write_00125, write_00125_len);
      }
      cgc_free(write_00125);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00126_00000[] = 
         "\x04\x04";
      static unsigned int write_00126_00000_len = 2;
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = cgc_append_buf(write_00126, &write_00126_len, write_00126_00000, write_00126_00000_len);
      if (write_00126_len > 0) {
         cgc_transmit_all(1, write_00126, write_00126_len);
      }
      cgc_free(write_00126);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00127_00000[] = 
         "\x00\x00";
      static unsigned int write_00127_00000_len = 2;
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = cgc_append_buf(write_00127, &write_00127_len, write_00127_00000, write_00127_00000_len);
      if (write_00127_len > 0) {
         cgc_transmit_all(1, write_00127, write_00127_len);
      }
      cgc_free(write_00127);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00128_00000[] = 
         "\x00\x08";
      static unsigned int write_00128_00000_len = 2;
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = cgc_append_buf(write_00128, &write_00128_len, write_00128_00000, write_00128_00000_len);
      if (write_00128_len > 0) {
         cgc_transmit_all(1, write_00128, write_00128_len);
      }
      cgc_free(write_00128);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00129_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00129_00000_len = 4;
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = cgc_append_buf(write_00129, &write_00129_len, write_00129_00000, write_00129_00000_len);
      if (write_00129_len > 0) {
         cgc_transmit_all(1, write_00129, write_00129_len);
      }
      cgc_free(write_00129);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00130_00000[] = 
         "\xc3\xac";
      static unsigned int write_00130_00000_len = 2;
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = cgc_append_buf(write_00130, &write_00130_len, write_00130_00000, write_00130_00000_len);
      if (write_00130_len > 0) {
         cgc_transmit_all(1, write_00130, write_00130_len);
      }
      cgc_free(write_00130);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00131_00000[] = 
         "\xb1";
      static unsigned int write_00131_00000_len = 1;
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = cgc_append_buf(write_00131, &write_00131_len, write_00131_00000, write_00131_00000_len);
      if (write_00131_len > 0) {
         cgc_transmit_all(1, write_00131, write_00131_len);
      }
      cgc_free(write_00131);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00132_00000[] = 
         "\x04";
      static unsigned int write_00132_00000_len = 1;
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = cgc_append_buf(write_00132, &write_00132_len, write_00132_00000, write_00132_00000_len);
      if (write_00132_len > 0) {
         cgc_transmit_all(1, write_00132, write_00132_len);
      }
      cgc_free(write_00132);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00133_00000[] = 
         "\x05\x04";
      static unsigned int write_00133_00000_len = 2;
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = cgc_append_buf(write_00133, &write_00133_len, write_00133_00000, write_00133_00000_len);
      if (write_00133_len > 0) {
         cgc_transmit_all(1, write_00133, write_00133_len);
      }
      cgc_free(write_00133);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00134_00000[] = 
         "\x00\x00";
      static unsigned int write_00134_00000_len = 2;
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = cgc_append_buf(write_00134, &write_00134_len, write_00134_00000, write_00134_00000_len);
      if (write_00134_len > 0) {
         cgc_transmit_all(1, write_00134, write_00134_len);
      }
      cgc_free(write_00134);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00135_00000[] = 
         "\x00\x09";
      static unsigned int write_00135_00000_len = 2;
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = cgc_append_buf(write_00135, &write_00135_len, write_00135_00000, write_00135_00000_len);
      if (write_00135_len > 0) {
         cgc_transmit_all(1, write_00135, write_00135_len);
      }
      cgc_free(write_00135);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00136_00000[] = 
         "\xaa\xaa\xaa\xaa";
      static unsigned int write_00136_00000_len = 4;
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = cgc_append_buf(write_00136, &write_00136_len, write_00136_00000, write_00136_00000_len);
      if (write_00136_len > 0) {
         cgc_transmit_all(1, write_00136, write_00136_len);
      }
      cgc_free(write_00136);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00137_00000[] = 
         "\xc3\xac";
      static unsigned int write_00137_00000_len = 2;
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = cgc_append_buf(write_00137, &write_00137_len, write_00137_00000, write_00137_00000_len);
      if (write_00137_len > 0) {
         cgc_transmit_all(1, write_00137, write_00137_len);
      }
      cgc_free(write_00137);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00138_00000[] = 
         "\xb1";
      static unsigned int write_00138_00000_len = 1;
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = cgc_append_buf(write_00138, &write_00138_len, write_00138_00000, write_00138_00000_len);
      if (write_00138_len > 0) {
         cgc_transmit_all(1, write_00138, write_00138_len);
      }
      cgc_free(write_00138);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00139_00000[] = 
         "\x04";
      static unsigned int write_00139_00000_len = 1;
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = cgc_append_buf(write_00139, &write_00139_len, write_00139_00000, write_00139_00000_len);
      if (write_00139_len > 0) {
         cgc_transmit_all(1, write_00139, write_00139_len);
      }
      cgc_free(write_00139);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00140_00000[] = 
         "\x06\x04";
      static unsigned int write_00140_00000_len = 2;
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = cgc_append_buf(write_00140, &write_00140_len, write_00140_00000, write_00140_00000_len);
      if (write_00140_len > 0) {
         cgc_transmit_all(1, write_00140, write_00140_len);
      }
      cgc_free(write_00140);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00141_00000[] = 
         "\x00\x00";
      static unsigned int write_00141_00000_len = 2;
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = cgc_append_buf(write_00141, &write_00141_len, write_00141_00000, write_00141_00000_len);
      if (write_00141_len > 0) {
         cgc_transmit_all(1, write_00141, write_00141_len);
      }
      cgc_free(write_00141);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00142_00000[] = 
         "\x00\x0a";
      static unsigned int write_00142_00000_len = 2;
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = cgc_append_buf(write_00142, &write_00142_len, write_00142_00000, write_00142_00000_len);
      if (write_00142_len > 0) {
         cgc_transmit_all(1, write_00142, write_00142_len);
      }
      cgc_free(write_00142);
   } while (0);
}
