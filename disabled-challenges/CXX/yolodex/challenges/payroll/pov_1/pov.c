#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** variable declaration for busy_week
      static unsigned char dvar_00000000[] = 
         "\x65\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x69\x64\x2d\x31\x60\x77\x65"
         "\x65\x6b\x2d\x31\x60\x6d\x6f\x6e\x64\x61\x79\x2d\x32\x34\x68\x35"
         "\x39\x6d\x60\x74\x75\x65\x73\x64\x61\x79\x2d\x32\x34\x68\x35\x39"
         "\x6d\x60\x77\x65\x64\x6e\x65\x73\x64\x61\x79\x2d\x32\x34\x68\x35"
         "\x39\x6d\x60\x74\x68\x75\x72\x73\x64\x61\x79\x2d\x32\x34\x68\x35"
         "\x39\x6d\x60\x66\x72\x69\x64\x61\x79\x2d\x32\x34\x68\x35\x39\x6d"
         "\x60\x73\x61\x74\x75\x72\x64\x61\x79\x2d\x32\x34\x68\x35\x39\x6d"
         "\x60\x73\x75\x6e\x64\x61\x79\x2d\x32\x34\x68\x35\x39\x6d\x60\x0a";
      static unsigned int dvar_00000000_len = 128;
      unsigned char *var_00000 = NULL;
      unsigned int var_00000_len = 0;
      var_00000 = cgc_append_buf(var_00000, &var_00000_len, dvar_00000000, dvar_00000000_len);
      cgc_putenv("busy_week", var_00000, var_00000_len);
      cgc_free(var_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x65\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x69\x64\x2d\x31\x60\x65\x6d"
         "\x70\x6c\x6f\x79\x65\x65\x5f\x6e\x61\x6d\x65\x2d\x4f\x76\x65\x72"
         "\x70\x61\x69\x64\x20\x45\x6d\x70\x6c\x6f\x79\x65\x65\x60\x77\x61"
         "\x67\x65\x2d\x37\x35\x2e\x30\x30\x60\x65\x78\x65\x6d\x70\x74\x2d"
         "\x79\x65\x73\x60\x0a";
      static unsigned int write_00000_00000_len = 69;
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
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_var("busy_week", write_00001, &write_00001_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_var("busy_week", write_00002, &write_00002_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = cgc_append_var("busy_week", write_00003, &write_00003_len);
      if (write_00003_len > 0) {
         cgc_transmit_all(1, write_00003, write_00003_len);
      }
      cgc_free(write_00003);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = cgc_append_var("busy_week", write_00004, &write_00004_len);
      if (write_00004_len > 0) {
         cgc_transmit_all(1, write_00004, write_00004_len);
      }
      cgc_free(write_00004);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = cgc_append_var("busy_week", write_00005, &write_00005_len);
      if (write_00005_len > 0) {
         cgc_transmit_all(1, write_00005, write_00005_len);
      }
      cgc_free(write_00005);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = cgc_append_var("busy_week", write_00006, &write_00006_len);
      if (write_00006_len > 0) {
         cgc_transmit_all(1, write_00006, write_00006_len);
      }
      cgc_free(write_00006);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = cgc_append_var("busy_week", write_00007, &write_00007_len);
      if (write_00007_len > 0) {
         cgc_transmit_all(1, write_00007, write_00007_len);
      }
      cgc_free(write_00007);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = cgc_append_var("busy_week", write_00008, &write_00008_len);
      if (write_00008_len > 0) {
         cgc_transmit_all(1, write_00008, write_00008_len);
      }
      cgc_free(write_00008);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = cgc_append_var("busy_week", write_00009, &write_00009_len);
      if (write_00009_len > 0) {
         cgc_transmit_all(1, write_00009, write_00009_len);
      }
      cgc_free(write_00009);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = cgc_append_var("busy_week", write_00010, &write_00010_len);
      if (write_00010_len > 0) {
         cgc_transmit_all(1, write_00010, write_00010_len);
      }
      cgc_free(write_00010);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = cgc_append_var("busy_week", write_00011, &write_00011_len);
      if (write_00011_len > 0) {
         cgc_transmit_all(1, write_00011, write_00011_len);
      }
      cgc_free(write_00011);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = cgc_append_var("busy_week", write_00012, &write_00012_len);
      if (write_00012_len > 0) {
         cgc_transmit_all(1, write_00012, write_00012_len);
      }
      cgc_free(write_00012);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = cgc_append_var("busy_week", write_00013, &write_00013_len);
      if (write_00013_len > 0) {
         cgc_transmit_all(1, write_00013, write_00013_len);
      }
      cgc_free(write_00013);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = cgc_append_var("busy_week", write_00014, &write_00014_len);
      if (write_00014_len > 0) {
         cgc_transmit_all(1, write_00014, write_00014_len);
      }
      cgc_free(write_00014);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = cgc_append_var("busy_week", write_00015, &write_00015_len);
      if (write_00015_len > 0) {
         cgc_transmit_all(1, write_00015, write_00015_len);
      }
      cgc_free(write_00015);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = cgc_append_var("busy_week", write_00016, &write_00016_len);
      if (write_00016_len > 0) {
         cgc_transmit_all(1, write_00016, write_00016_len);
      }
      cgc_free(write_00016);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = cgc_append_var("busy_week", write_00017, &write_00017_len);
      if (write_00017_len > 0) {
         cgc_transmit_all(1, write_00017, write_00017_len);
      }
      cgc_free(write_00017);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = cgc_append_var("busy_week", write_00018, &write_00018_len);
      if (write_00018_len > 0) {
         cgc_transmit_all(1, write_00018, write_00018_len);
      }
      cgc_free(write_00018);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = cgc_append_var("busy_week", write_00019, &write_00019_len);
      if (write_00019_len > 0) {
         cgc_transmit_all(1, write_00019, write_00019_len);
      }
      cgc_free(write_00019);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = cgc_append_var("busy_week", write_00020, &write_00020_len);
      if (write_00020_len > 0) {
         cgc_transmit_all(1, write_00020, write_00020_len);
      }
      cgc_free(write_00020);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = cgc_append_var("busy_week", write_00021, &write_00021_len);
      if (write_00021_len > 0) {
         cgc_transmit_all(1, write_00021, write_00021_len);
      }
      cgc_free(write_00021);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = cgc_append_var("busy_week", write_00022, &write_00022_len);
      if (write_00022_len > 0) {
         cgc_transmit_all(1, write_00022, write_00022_len);
      }
      cgc_free(write_00022);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = cgc_append_var("busy_week", write_00023, &write_00023_len);
      if (write_00023_len > 0) {
         cgc_transmit_all(1, write_00023, write_00023_len);
      }
      cgc_free(write_00023);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = cgc_append_var("busy_week", write_00024, &write_00024_len);
      if (write_00024_len > 0) {
         cgc_transmit_all(1, write_00024, write_00024_len);
      }
      cgc_free(write_00024);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = cgc_append_var("busy_week", write_00025, &write_00025_len);
      if (write_00025_len > 0) {
         cgc_transmit_all(1, write_00025, write_00025_len);
      }
      cgc_free(write_00025);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = cgc_append_var("busy_week", write_00026, &write_00026_len);
      if (write_00026_len > 0) {
         cgc_transmit_all(1, write_00026, write_00026_len);
      }
      cgc_free(write_00026);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = cgc_append_var("busy_week", write_00027, &write_00027_len);
      if (write_00027_len > 0) {
         cgc_transmit_all(1, write_00027, write_00027_len);
      }
      cgc_free(write_00027);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = cgc_append_var("busy_week", write_00028, &write_00028_len);
      if (write_00028_len > 0) {
         cgc_transmit_all(1, write_00028, write_00028_len);
      }
      cgc_free(write_00028);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = cgc_append_var("busy_week", write_00029, &write_00029_len);
      if (write_00029_len > 0) {
         cgc_transmit_all(1, write_00029, write_00029_len);
      }
      cgc_free(write_00029);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = cgc_append_var("busy_week", write_00030, &write_00030_len);
      if (write_00030_len > 0) {
         cgc_transmit_all(1, write_00030, write_00030_len);
      }
      cgc_free(write_00030);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = cgc_append_var("busy_week", write_00031, &write_00031_len);
      if (write_00031_len > 0) {
         cgc_transmit_all(1, write_00031, write_00031_len);
      }
      cgc_free(write_00031);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = cgc_append_var("busy_week", write_00032, &write_00032_len);
      if (write_00032_len > 0) {
         cgc_transmit_all(1, write_00032, write_00032_len);
      }
      cgc_free(write_00032);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = cgc_append_var("busy_week", write_00033, &write_00033_len);
      if (write_00033_len > 0) {
         cgc_transmit_all(1, write_00033, write_00033_len);
      }
      cgc_free(write_00033);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = cgc_append_var("busy_week", write_00034, &write_00034_len);
      if (write_00034_len > 0) {
         cgc_transmit_all(1, write_00034, write_00034_len);
      }
      cgc_free(write_00034);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = cgc_append_var("busy_week", write_00035, &write_00035_len);
      if (write_00035_len > 0) {
         cgc_transmit_all(1, write_00035, write_00035_len);
      }
      cgc_free(write_00035);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = cgc_append_var("busy_week", write_00036, &write_00036_len);
      if (write_00036_len > 0) {
         cgc_transmit_all(1, write_00036, write_00036_len);
      }
      cgc_free(write_00036);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = cgc_append_var("busy_week", write_00037, &write_00037_len);
      if (write_00037_len > 0) {
         cgc_transmit_all(1, write_00037, write_00037_len);
      }
      cgc_free(write_00037);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = cgc_append_var("busy_week", write_00038, &write_00038_len);
      if (write_00038_len > 0) {
         cgc_transmit_all(1, write_00038, write_00038_len);
      }
      cgc_free(write_00038);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = cgc_append_var("busy_week", write_00039, &write_00039_len);
      if (write_00039_len > 0) {
         cgc_transmit_all(1, write_00039, write_00039_len);
      }
      cgc_free(write_00039);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = cgc_append_var("busy_week", write_00040, &write_00040_len);
      if (write_00040_len > 0) {
         cgc_transmit_all(1, write_00040, write_00040_len);
      }
      cgc_free(write_00040);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = cgc_append_var("busy_week", write_00041, &write_00041_len);
      if (write_00041_len > 0) {
         cgc_transmit_all(1, write_00041, write_00041_len);
      }
      cgc_free(write_00041);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = cgc_append_var("busy_week", write_00042, &write_00042_len);
      if (write_00042_len > 0) {
         cgc_transmit_all(1, write_00042, write_00042_len);
      }
      cgc_free(write_00042);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = cgc_append_var("busy_week", write_00043, &write_00043_len);
      if (write_00043_len > 0) {
         cgc_transmit_all(1, write_00043, write_00043_len);
      }
      cgc_free(write_00043);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = cgc_append_var("busy_week", write_00044, &write_00044_len);
      if (write_00044_len > 0) {
         cgc_transmit_all(1, write_00044, write_00044_len);
      }
      cgc_free(write_00044);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = cgc_append_var("busy_week", write_00045, &write_00045_len);
      if (write_00045_len > 0) {
         cgc_transmit_all(1, write_00045, write_00045_len);
      }
      cgc_free(write_00045);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = cgc_append_var("busy_week", write_00046, &write_00046_len);
      if (write_00046_len > 0) {
         cgc_transmit_all(1, write_00046, write_00046_len);
      }
      cgc_free(write_00046);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = cgc_append_var("busy_week", write_00047, &write_00047_len);
      if (write_00047_len > 0) {
         cgc_transmit_all(1, write_00047, write_00047_len);
      }
      cgc_free(write_00047);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = cgc_append_var("busy_week", write_00048, &write_00048_len);
      if (write_00048_len > 0) {
         cgc_transmit_all(1, write_00048, write_00048_len);
      }
      cgc_free(write_00048);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = cgc_append_var("busy_week", write_00049, &write_00049_len);
      if (write_00049_len > 0) {
         cgc_transmit_all(1, write_00049, write_00049_len);
      }
      cgc_free(write_00049);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = cgc_append_var("busy_week", write_00050, &write_00050_len);
      if (write_00050_len > 0) {
         cgc_transmit_all(1, write_00050, write_00050_len);
      }
      cgc_free(write_00050);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = cgc_append_var("busy_week", write_00051, &write_00051_len);
      if (write_00051_len > 0) {
         cgc_transmit_all(1, write_00051, write_00051_len);
      }
      cgc_free(write_00051);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = cgc_append_var("busy_week", write_00052, &write_00052_len);
      if (write_00052_len > 0) {
         cgc_transmit_all(1, write_00052, write_00052_len);
      }
      cgc_free(write_00052);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = cgc_append_var("busy_week", write_00053, &write_00053_len);
      if (write_00053_len > 0) {
         cgc_transmit_all(1, write_00053, write_00053_len);
      }
      cgc_free(write_00053);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = cgc_append_var("busy_week", write_00054, &write_00054_len);
      if (write_00054_len > 0) {
         cgc_transmit_all(1, write_00054, write_00054_len);
      }
      cgc_free(write_00054);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = cgc_append_var("busy_week", write_00055, &write_00055_len);
      if (write_00055_len > 0) {
         cgc_transmit_all(1, write_00055, write_00055_len);
      }
      cgc_free(write_00055);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = cgc_append_var("busy_week", write_00056, &write_00056_len);
      if (write_00056_len > 0) {
         cgc_transmit_all(1, write_00056, write_00056_len);
      }
      cgc_free(write_00056);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = cgc_append_var("busy_week", write_00057, &write_00057_len);
      if (write_00057_len > 0) {
         cgc_transmit_all(1, write_00057, write_00057_len);
      }
      cgc_free(write_00057);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = cgc_append_var("busy_week", write_00058, &write_00058_len);
      if (write_00058_len > 0) {
         cgc_transmit_all(1, write_00058, write_00058_len);
      }
      cgc_free(write_00058);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = cgc_append_var("busy_week", write_00059, &write_00059_len);
      if (write_00059_len > 0) {
         cgc_transmit_all(1, write_00059, write_00059_len);
      }
      cgc_free(write_00059);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = cgc_append_var("busy_week", write_00060, &write_00060_len);
      if (write_00060_len > 0) {
         cgc_transmit_all(1, write_00060, write_00060_len);
      }
      cgc_free(write_00060);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = cgc_append_var("busy_week", write_00061, &write_00061_len);
      if (write_00061_len > 0) {
         cgc_transmit_all(1, write_00061, write_00061_len);
      }
      cgc_free(write_00061);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = cgc_append_var("busy_week", write_00062, &write_00062_len);
      if (write_00062_len > 0) {
         cgc_transmit_all(1, write_00062, write_00062_len);
      }
      cgc_free(write_00062);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = cgc_append_var("busy_week", write_00063, &write_00063_len);
      if (write_00063_len > 0) {
         cgc_transmit_all(1, write_00063, write_00063_len);
      }
      cgc_free(write_00063);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = cgc_append_var("busy_week", write_00064, &write_00064_len);
      if (write_00064_len > 0) {
         cgc_transmit_all(1, write_00064, write_00064_len);
      }
      cgc_free(write_00064);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = cgc_append_var("busy_week", write_00065, &write_00065_len);
      if (write_00065_len > 0) {
         cgc_transmit_all(1, write_00065, write_00065_len);
      }
      cgc_free(write_00065);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = cgc_append_var("busy_week", write_00066, &write_00066_len);
      if (write_00066_len > 0) {
         cgc_transmit_all(1, write_00066, write_00066_len);
      }
      cgc_free(write_00066);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = cgc_append_var("busy_week", write_00067, &write_00067_len);
      if (write_00067_len > 0) {
         cgc_transmit_all(1, write_00067, write_00067_len);
      }
      cgc_free(write_00067);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = cgc_append_var("busy_week", write_00068, &write_00068_len);
      if (write_00068_len > 0) {
         cgc_transmit_all(1, write_00068, write_00068_len);
      }
      cgc_free(write_00068);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = cgc_append_var("busy_week", write_00069, &write_00069_len);
      if (write_00069_len > 0) {
         cgc_transmit_all(1, write_00069, write_00069_len);
      }
      cgc_free(write_00069);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = cgc_append_var("busy_week", write_00070, &write_00070_len);
      if (write_00070_len > 0) {
         cgc_transmit_all(1, write_00070, write_00070_len);
      }
      cgc_free(write_00070);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = cgc_append_var("busy_week", write_00071, &write_00071_len);
      if (write_00071_len > 0) {
         cgc_transmit_all(1, write_00071, write_00071_len);
      }
      cgc_free(write_00071);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = cgc_append_var("busy_week", write_00072, &write_00072_len);
      if (write_00072_len > 0) {
         cgc_transmit_all(1, write_00072, write_00072_len);
      }
      cgc_free(write_00072);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = cgc_append_var("busy_week", write_00073, &write_00073_len);
      if (write_00073_len > 0) {
         cgc_transmit_all(1, write_00073, write_00073_len);
      }
      cgc_free(write_00073);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = cgc_append_var("busy_week", write_00074, &write_00074_len);
      if (write_00074_len > 0) {
         cgc_transmit_all(1, write_00074, write_00074_len);
      }
      cgc_free(write_00074);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = cgc_append_var("busy_week", write_00075, &write_00075_len);
      if (write_00075_len > 0) {
         cgc_transmit_all(1, write_00075, write_00075_len);
      }
      cgc_free(write_00075);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = cgc_append_var("busy_week", write_00076, &write_00076_len);
      if (write_00076_len > 0) {
         cgc_transmit_all(1, write_00076, write_00076_len);
      }
      cgc_free(write_00076);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = cgc_append_var("busy_week", write_00077, &write_00077_len);
      if (write_00077_len > 0) {
         cgc_transmit_all(1, write_00077, write_00077_len);
      }
      cgc_free(write_00077);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = cgc_append_var("busy_week", write_00078, &write_00078_len);
      if (write_00078_len > 0) {
         cgc_transmit_all(1, write_00078, write_00078_len);
      }
      cgc_free(write_00078);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = cgc_append_var("busy_week", write_00079, &write_00079_len);
      if (write_00079_len > 0) {
         cgc_transmit_all(1, write_00079, write_00079_len);
      }
      cgc_free(write_00079);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = cgc_append_var("busy_week", write_00080, &write_00080_len);
      if (write_00080_len > 0) {
         cgc_transmit_all(1, write_00080, write_00080_len);
      }
      cgc_free(write_00080);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = cgc_append_var("busy_week", write_00081, &write_00081_len);
      if (write_00081_len > 0) {
         cgc_transmit_all(1, write_00081, write_00081_len);
      }
      cgc_free(write_00081);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = cgc_append_var("busy_week", write_00082, &write_00082_len);
      if (write_00082_len > 0) {
         cgc_transmit_all(1, write_00082, write_00082_len);
      }
      cgc_free(write_00082);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = cgc_append_var("busy_week", write_00083, &write_00083_len);
      if (write_00083_len > 0) {
         cgc_transmit_all(1, write_00083, write_00083_len);
      }
      cgc_free(write_00083);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = cgc_append_var("busy_week", write_00084, &write_00084_len);
      if (write_00084_len > 0) {
         cgc_transmit_all(1, write_00084, write_00084_len);
      }
      cgc_free(write_00084);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00085_00000[] = 
         "\x71\x75\x65\x72\x79\x2d\x77\x65\x65\x6b\x60\x65\x6d\x70\x6c\x6f"
         "\x79\x65\x65\x5f\x69\x64\x2d\x31\x60\x77\x65\x65\x6b\x2d\x31\x60"
         "\x0a";
      static unsigned int write_00085_00000_len = 33;
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
         "\x65\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x69\x64\x2d\x31\x60\x77\x65"
         "\x65\x6b\x2d\x31\x60\x6d\x6f\x6e\x64\x61\x79\x2d\x31\x68\x30\x6d"
         "\x60\x0a";
      static unsigned int write_00086_00000_len = 34;
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = cgc_append_buf(write_00086, &write_00086_len, write_00086_00000, write_00086_00000_len);
      if (write_00086_len > 0) {
         cgc_transmit_all(1, write_00086, write_00086_len);
      }
      cgc_free(write_00086);
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
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
