#include <libpov.h>
int main(void) {
   negotiate_type1(0x0, 0x0, 0);
   do {
      //*** variable declaration for busy_weekend
      static unsigned char dvar_00000000[] = 
         "\x73\x61\x74\x75\x72\x64\x61\x79\x2d\x32\x34\x68\x35\x39\x6d\x60"
         "\x73\x75\x6e\x64\x61\x79\x2d\x32\x34\x68\x35\x39\x6d\x60";
      static unsigned int dvar_00000000_len = 30;
      unsigned char *var_00000 = NULL;
      unsigned int var_00000_len = 0;
      var_00000 = append_buf(var_00000, &var_00000_len, dvar_00000000, dvar_00000000_len);
      putenv("busy_weekend", var_00000, var_00000_len);
      free(var_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x65\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x69\x64\x2d\x34\x39\x60\x65"
         "\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x6e\x61\x6d\x65\x2d\x4f\x76\x65"
         "\x72\x77\x6f\x72\x6b\x65\x64\x20\x45\x6d\x70\x6c\x6f\x79\x65\x65"
         "\x60\x77\x61\x67\x65\x2d\x34\x32\x2e\x34\x32\x60\x65\x78\x65\x6d"
         "\x70\x74\x2d\x79\x65\x73\x60\x0a";
      static unsigned int write_00000_00000_len = 72;
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
      static unsigned char write_00001_00000[] = 
         "\x65\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x69\x64\x2d\x34\x39\x60\x77"
         "\x65\x65\x6b\x2d\x32\x33\x60";
      static unsigned int write_00001_00000_len = 23;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         transmit_all(1, write_00001, write_00001_len);
      }
      free(write_00001);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = append_var("busy_weekend", write_00002, &write_00002_len);
      if (write_00002_len > 0) {
         transmit_all(1, write_00002, write_00002_len);
      }
      free(write_00002);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00003 = NULL;
      unsigned int write_00003_len = 0;
      write_00003 = append_var("busy_weekend", write_00003, &write_00003_len);
      if (write_00003_len > 0) {
         transmit_all(1, write_00003, write_00003_len);
      }
      free(write_00003);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00004 = NULL;
      unsigned int write_00004_len = 0;
      write_00004 = append_var("busy_weekend", write_00004, &write_00004_len);
      if (write_00004_len > 0) {
         transmit_all(1, write_00004, write_00004_len);
      }
      free(write_00004);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00005 = NULL;
      unsigned int write_00005_len = 0;
      write_00005 = append_var("busy_weekend", write_00005, &write_00005_len);
      if (write_00005_len > 0) {
         transmit_all(1, write_00005, write_00005_len);
      }
      free(write_00005);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00006 = NULL;
      unsigned int write_00006_len = 0;
      write_00006 = append_var("busy_weekend", write_00006, &write_00006_len);
      if (write_00006_len > 0) {
         transmit_all(1, write_00006, write_00006_len);
      }
      free(write_00006);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00007 = NULL;
      unsigned int write_00007_len = 0;
      write_00007 = append_var("busy_weekend", write_00007, &write_00007_len);
      if (write_00007_len > 0) {
         transmit_all(1, write_00007, write_00007_len);
      }
      free(write_00007);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00008 = NULL;
      unsigned int write_00008_len = 0;
      write_00008 = append_var("busy_weekend", write_00008, &write_00008_len);
      if (write_00008_len > 0) {
         transmit_all(1, write_00008, write_00008_len);
      }
      free(write_00008);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00009 = NULL;
      unsigned int write_00009_len = 0;
      write_00009 = append_var("busy_weekend", write_00009, &write_00009_len);
      if (write_00009_len > 0) {
         transmit_all(1, write_00009, write_00009_len);
      }
      free(write_00009);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00010 = NULL;
      unsigned int write_00010_len = 0;
      write_00010 = append_var("busy_weekend", write_00010, &write_00010_len);
      if (write_00010_len > 0) {
         transmit_all(1, write_00010, write_00010_len);
      }
      free(write_00010);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00011 = NULL;
      unsigned int write_00011_len = 0;
      write_00011 = append_var("busy_weekend", write_00011, &write_00011_len);
      if (write_00011_len > 0) {
         transmit_all(1, write_00011, write_00011_len);
      }
      free(write_00011);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00012 = NULL;
      unsigned int write_00012_len = 0;
      write_00012 = append_var("busy_weekend", write_00012, &write_00012_len);
      if (write_00012_len > 0) {
         transmit_all(1, write_00012, write_00012_len);
      }
      free(write_00012);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00013 = NULL;
      unsigned int write_00013_len = 0;
      write_00013 = append_var("busy_weekend", write_00013, &write_00013_len);
      if (write_00013_len > 0) {
         transmit_all(1, write_00013, write_00013_len);
      }
      free(write_00013);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00014 = NULL;
      unsigned int write_00014_len = 0;
      write_00014 = append_var("busy_weekend", write_00014, &write_00014_len);
      if (write_00014_len > 0) {
         transmit_all(1, write_00014, write_00014_len);
      }
      free(write_00014);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00015 = NULL;
      unsigned int write_00015_len = 0;
      write_00015 = append_var("busy_weekend", write_00015, &write_00015_len);
      if (write_00015_len > 0) {
         transmit_all(1, write_00015, write_00015_len);
      }
      free(write_00015);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00016 = NULL;
      unsigned int write_00016_len = 0;
      write_00016 = append_var("busy_weekend", write_00016, &write_00016_len);
      if (write_00016_len > 0) {
         transmit_all(1, write_00016, write_00016_len);
      }
      free(write_00016);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00017 = NULL;
      unsigned int write_00017_len = 0;
      write_00017 = append_var("busy_weekend", write_00017, &write_00017_len);
      if (write_00017_len > 0) {
         transmit_all(1, write_00017, write_00017_len);
      }
      free(write_00017);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00018 = NULL;
      unsigned int write_00018_len = 0;
      write_00018 = append_var("busy_weekend", write_00018, &write_00018_len);
      if (write_00018_len > 0) {
         transmit_all(1, write_00018, write_00018_len);
      }
      free(write_00018);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00019 = NULL;
      unsigned int write_00019_len = 0;
      write_00019 = append_var("busy_weekend", write_00019, &write_00019_len);
      if (write_00019_len > 0) {
         transmit_all(1, write_00019, write_00019_len);
      }
      free(write_00019);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00020 = NULL;
      unsigned int write_00020_len = 0;
      write_00020 = append_var("busy_weekend", write_00020, &write_00020_len);
      if (write_00020_len > 0) {
         transmit_all(1, write_00020, write_00020_len);
      }
      free(write_00020);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00021 = NULL;
      unsigned int write_00021_len = 0;
      write_00021 = append_var("busy_weekend", write_00021, &write_00021_len);
      if (write_00021_len > 0) {
         transmit_all(1, write_00021, write_00021_len);
      }
      free(write_00021);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00022 = NULL;
      unsigned int write_00022_len = 0;
      write_00022 = append_var("busy_weekend", write_00022, &write_00022_len);
      if (write_00022_len > 0) {
         transmit_all(1, write_00022, write_00022_len);
      }
      free(write_00022);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00023 = NULL;
      unsigned int write_00023_len = 0;
      write_00023 = append_var("busy_weekend", write_00023, &write_00023_len);
      if (write_00023_len > 0) {
         transmit_all(1, write_00023, write_00023_len);
      }
      free(write_00023);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00024 = NULL;
      unsigned int write_00024_len = 0;
      write_00024 = append_var("busy_weekend", write_00024, &write_00024_len);
      if (write_00024_len > 0) {
         transmit_all(1, write_00024, write_00024_len);
      }
      free(write_00024);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00025 = NULL;
      unsigned int write_00025_len = 0;
      write_00025 = append_var("busy_weekend", write_00025, &write_00025_len);
      if (write_00025_len > 0) {
         transmit_all(1, write_00025, write_00025_len);
      }
      free(write_00025);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00026 = NULL;
      unsigned int write_00026_len = 0;
      write_00026 = append_var("busy_weekend", write_00026, &write_00026_len);
      if (write_00026_len > 0) {
         transmit_all(1, write_00026, write_00026_len);
      }
      free(write_00026);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00027 = NULL;
      unsigned int write_00027_len = 0;
      write_00027 = append_var("busy_weekend", write_00027, &write_00027_len);
      if (write_00027_len > 0) {
         transmit_all(1, write_00027, write_00027_len);
      }
      free(write_00027);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00028 = NULL;
      unsigned int write_00028_len = 0;
      write_00028 = append_var("busy_weekend", write_00028, &write_00028_len);
      if (write_00028_len > 0) {
         transmit_all(1, write_00028, write_00028_len);
      }
      free(write_00028);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00029 = NULL;
      unsigned int write_00029_len = 0;
      write_00029 = append_var("busy_weekend", write_00029, &write_00029_len);
      if (write_00029_len > 0) {
         transmit_all(1, write_00029, write_00029_len);
      }
      free(write_00029);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00030 = NULL;
      unsigned int write_00030_len = 0;
      write_00030 = append_var("busy_weekend", write_00030, &write_00030_len);
      if (write_00030_len > 0) {
         transmit_all(1, write_00030, write_00030_len);
      }
      free(write_00030);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00031 = NULL;
      unsigned int write_00031_len = 0;
      write_00031 = append_var("busy_weekend", write_00031, &write_00031_len);
      if (write_00031_len > 0) {
         transmit_all(1, write_00031, write_00031_len);
      }
      free(write_00031);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00032 = NULL;
      unsigned int write_00032_len = 0;
      write_00032 = append_var("busy_weekend", write_00032, &write_00032_len);
      if (write_00032_len > 0) {
         transmit_all(1, write_00032, write_00032_len);
      }
      free(write_00032);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00033 = NULL;
      unsigned int write_00033_len = 0;
      write_00033 = append_var("busy_weekend", write_00033, &write_00033_len);
      if (write_00033_len > 0) {
         transmit_all(1, write_00033, write_00033_len);
      }
      free(write_00033);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00034 = NULL;
      unsigned int write_00034_len = 0;
      write_00034 = append_var("busy_weekend", write_00034, &write_00034_len);
      if (write_00034_len > 0) {
         transmit_all(1, write_00034, write_00034_len);
      }
      free(write_00034);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = append_var("busy_weekend", write_00035, &write_00035_len);
      if (write_00035_len > 0) {
         transmit_all(1, write_00035, write_00035_len);
      }
      free(write_00035);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00036 = NULL;
      unsigned int write_00036_len = 0;
      write_00036 = append_var("busy_weekend", write_00036, &write_00036_len);
      if (write_00036_len > 0) {
         transmit_all(1, write_00036, write_00036_len);
      }
      free(write_00036);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = append_var("busy_weekend", write_00037, &write_00037_len);
      if (write_00037_len > 0) {
         transmit_all(1, write_00037, write_00037_len);
      }
      free(write_00037);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = append_var("busy_weekend", write_00038, &write_00038_len);
      if (write_00038_len > 0) {
         transmit_all(1, write_00038, write_00038_len);
      }
      free(write_00038);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00039 = NULL;
      unsigned int write_00039_len = 0;
      write_00039 = append_var("busy_weekend", write_00039, &write_00039_len);
      if (write_00039_len > 0) {
         transmit_all(1, write_00039, write_00039_len);
      }
      free(write_00039);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00040 = NULL;
      unsigned int write_00040_len = 0;
      write_00040 = append_var("busy_weekend", write_00040, &write_00040_len);
      if (write_00040_len > 0) {
         transmit_all(1, write_00040, write_00040_len);
      }
      free(write_00040);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00041 = NULL;
      unsigned int write_00041_len = 0;
      write_00041 = append_var("busy_weekend", write_00041, &write_00041_len);
      if (write_00041_len > 0) {
         transmit_all(1, write_00041, write_00041_len);
      }
      free(write_00041);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00042 = NULL;
      unsigned int write_00042_len = 0;
      write_00042 = append_var("busy_weekend", write_00042, &write_00042_len);
      if (write_00042_len > 0) {
         transmit_all(1, write_00042, write_00042_len);
      }
      free(write_00042);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00043 = NULL;
      unsigned int write_00043_len = 0;
      write_00043 = append_var("busy_weekend", write_00043, &write_00043_len);
      if (write_00043_len > 0) {
         transmit_all(1, write_00043, write_00043_len);
      }
      free(write_00043);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00044 = NULL;
      unsigned int write_00044_len = 0;
      write_00044 = append_var("busy_weekend", write_00044, &write_00044_len);
      if (write_00044_len > 0) {
         transmit_all(1, write_00044, write_00044_len);
      }
      free(write_00044);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00045 = NULL;
      unsigned int write_00045_len = 0;
      write_00045 = append_var("busy_weekend", write_00045, &write_00045_len);
      if (write_00045_len > 0) {
         transmit_all(1, write_00045, write_00045_len);
      }
      free(write_00045);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00046 = NULL;
      unsigned int write_00046_len = 0;
      write_00046 = append_var("busy_weekend", write_00046, &write_00046_len);
      if (write_00046_len > 0) {
         transmit_all(1, write_00046, write_00046_len);
      }
      free(write_00046);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00047 = NULL;
      unsigned int write_00047_len = 0;
      write_00047 = append_var("busy_weekend", write_00047, &write_00047_len);
      if (write_00047_len > 0) {
         transmit_all(1, write_00047, write_00047_len);
      }
      free(write_00047);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00048 = NULL;
      unsigned int write_00048_len = 0;
      write_00048 = append_var("busy_weekend", write_00048, &write_00048_len);
      if (write_00048_len > 0) {
         transmit_all(1, write_00048, write_00048_len);
      }
      free(write_00048);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00049 = NULL;
      unsigned int write_00049_len = 0;
      write_00049 = append_var("busy_weekend", write_00049, &write_00049_len);
      if (write_00049_len > 0) {
         transmit_all(1, write_00049, write_00049_len);
      }
      free(write_00049);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00050 = NULL;
      unsigned int write_00050_len = 0;
      write_00050 = append_var("busy_weekend", write_00050, &write_00050_len);
      if (write_00050_len > 0) {
         transmit_all(1, write_00050, write_00050_len);
      }
      free(write_00050);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00051 = NULL;
      unsigned int write_00051_len = 0;
      write_00051 = append_var("busy_weekend", write_00051, &write_00051_len);
      if (write_00051_len > 0) {
         transmit_all(1, write_00051, write_00051_len);
      }
      free(write_00051);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00052 = NULL;
      unsigned int write_00052_len = 0;
      write_00052 = append_var("busy_weekend", write_00052, &write_00052_len);
      if (write_00052_len > 0) {
         transmit_all(1, write_00052, write_00052_len);
      }
      free(write_00052);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00053 = NULL;
      unsigned int write_00053_len = 0;
      write_00053 = append_var("busy_weekend", write_00053, &write_00053_len);
      if (write_00053_len > 0) {
         transmit_all(1, write_00053, write_00053_len);
      }
      free(write_00053);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00054 = NULL;
      unsigned int write_00054_len = 0;
      write_00054 = append_var("busy_weekend", write_00054, &write_00054_len);
      if (write_00054_len > 0) {
         transmit_all(1, write_00054, write_00054_len);
      }
      free(write_00054);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00055 = NULL;
      unsigned int write_00055_len = 0;
      write_00055 = append_var("busy_weekend", write_00055, &write_00055_len);
      if (write_00055_len > 0) {
         transmit_all(1, write_00055, write_00055_len);
      }
      free(write_00055);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00056 = NULL;
      unsigned int write_00056_len = 0;
      write_00056 = append_var("busy_weekend", write_00056, &write_00056_len);
      if (write_00056_len > 0) {
         transmit_all(1, write_00056, write_00056_len);
      }
      free(write_00056);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00057 = NULL;
      unsigned int write_00057_len = 0;
      write_00057 = append_var("busy_weekend", write_00057, &write_00057_len);
      if (write_00057_len > 0) {
         transmit_all(1, write_00057, write_00057_len);
      }
      free(write_00057);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00058 = NULL;
      unsigned int write_00058_len = 0;
      write_00058 = append_var("busy_weekend", write_00058, &write_00058_len);
      if (write_00058_len > 0) {
         transmit_all(1, write_00058, write_00058_len);
      }
      free(write_00058);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00059 = NULL;
      unsigned int write_00059_len = 0;
      write_00059 = append_var("busy_weekend", write_00059, &write_00059_len);
      if (write_00059_len > 0) {
         transmit_all(1, write_00059, write_00059_len);
      }
      free(write_00059);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00060 = NULL;
      unsigned int write_00060_len = 0;
      write_00060 = append_var("busy_weekend", write_00060, &write_00060_len);
      if (write_00060_len > 0) {
         transmit_all(1, write_00060, write_00060_len);
      }
      free(write_00060);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00061 = NULL;
      unsigned int write_00061_len = 0;
      write_00061 = append_var("busy_weekend", write_00061, &write_00061_len);
      if (write_00061_len > 0) {
         transmit_all(1, write_00061, write_00061_len);
      }
      free(write_00061);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00062 = NULL;
      unsigned int write_00062_len = 0;
      write_00062 = append_var("busy_weekend", write_00062, &write_00062_len);
      if (write_00062_len > 0) {
         transmit_all(1, write_00062, write_00062_len);
      }
      free(write_00062);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00063 = NULL;
      unsigned int write_00063_len = 0;
      write_00063 = append_var("busy_weekend", write_00063, &write_00063_len);
      if (write_00063_len > 0) {
         transmit_all(1, write_00063, write_00063_len);
      }
      free(write_00063);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00064 = NULL;
      unsigned int write_00064_len = 0;
      write_00064 = append_var("busy_weekend", write_00064, &write_00064_len);
      if (write_00064_len > 0) {
         transmit_all(1, write_00064, write_00064_len);
      }
      free(write_00064);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00065 = NULL;
      unsigned int write_00065_len = 0;
      write_00065 = append_var("busy_weekend", write_00065, &write_00065_len);
      if (write_00065_len > 0) {
         transmit_all(1, write_00065, write_00065_len);
      }
      free(write_00065);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00066 = NULL;
      unsigned int write_00066_len = 0;
      write_00066 = append_var("busy_weekend", write_00066, &write_00066_len);
      if (write_00066_len > 0) {
         transmit_all(1, write_00066, write_00066_len);
      }
      free(write_00066);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00067 = NULL;
      unsigned int write_00067_len = 0;
      write_00067 = append_var("busy_weekend", write_00067, &write_00067_len);
      if (write_00067_len > 0) {
         transmit_all(1, write_00067, write_00067_len);
      }
      free(write_00067);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00068 = NULL;
      unsigned int write_00068_len = 0;
      write_00068 = append_var("busy_weekend", write_00068, &write_00068_len);
      if (write_00068_len > 0) {
         transmit_all(1, write_00068, write_00068_len);
      }
      free(write_00068);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00069 = NULL;
      unsigned int write_00069_len = 0;
      write_00069 = append_var("busy_weekend", write_00069, &write_00069_len);
      if (write_00069_len > 0) {
         transmit_all(1, write_00069, write_00069_len);
      }
      free(write_00069);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00070 = NULL;
      unsigned int write_00070_len = 0;
      write_00070 = append_var("busy_weekend", write_00070, &write_00070_len);
      if (write_00070_len > 0) {
         transmit_all(1, write_00070, write_00070_len);
      }
      free(write_00070);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00071 = NULL;
      unsigned int write_00071_len = 0;
      write_00071 = append_var("busy_weekend", write_00071, &write_00071_len);
      if (write_00071_len > 0) {
         transmit_all(1, write_00071, write_00071_len);
      }
      free(write_00071);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00072 = NULL;
      unsigned int write_00072_len = 0;
      write_00072 = append_var("busy_weekend", write_00072, &write_00072_len);
      if (write_00072_len > 0) {
         transmit_all(1, write_00072, write_00072_len);
      }
      free(write_00072);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00073 = NULL;
      unsigned int write_00073_len = 0;
      write_00073 = append_var("busy_weekend", write_00073, &write_00073_len);
      if (write_00073_len > 0) {
         transmit_all(1, write_00073, write_00073_len);
      }
      free(write_00073);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00074 = NULL;
      unsigned int write_00074_len = 0;
      write_00074 = append_var("busy_weekend", write_00074, &write_00074_len);
      if (write_00074_len > 0) {
         transmit_all(1, write_00074, write_00074_len);
      }
      free(write_00074);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00075 = NULL;
      unsigned int write_00075_len = 0;
      write_00075 = append_var("busy_weekend", write_00075, &write_00075_len);
      if (write_00075_len > 0) {
         transmit_all(1, write_00075, write_00075_len);
      }
      free(write_00075);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00076 = NULL;
      unsigned int write_00076_len = 0;
      write_00076 = append_var("busy_weekend", write_00076, &write_00076_len);
      if (write_00076_len > 0) {
         transmit_all(1, write_00076, write_00076_len);
      }
      free(write_00076);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00077 = NULL;
      unsigned int write_00077_len = 0;
      write_00077 = append_var("busy_weekend", write_00077, &write_00077_len);
      if (write_00077_len > 0) {
         transmit_all(1, write_00077, write_00077_len);
      }
      free(write_00077);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00078 = NULL;
      unsigned int write_00078_len = 0;
      write_00078 = append_var("busy_weekend", write_00078, &write_00078_len);
      if (write_00078_len > 0) {
         transmit_all(1, write_00078, write_00078_len);
      }
      free(write_00078);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00079 = NULL;
      unsigned int write_00079_len = 0;
      write_00079 = append_var("busy_weekend", write_00079, &write_00079_len);
      if (write_00079_len > 0) {
         transmit_all(1, write_00079, write_00079_len);
      }
      free(write_00079);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00080 = NULL;
      unsigned int write_00080_len = 0;
      write_00080 = append_var("busy_weekend", write_00080, &write_00080_len);
      if (write_00080_len > 0) {
         transmit_all(1, write_00080, write_00080_len);
      }
      free(write_00080);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00081 = NULL;
      unsigned int write_00081_len = 0;
      write_00081 = append_var("busy_weekend", write_00081, &write_00081_len);
      if (write_00081_len > 0) {
         transmit_all(1, write_00081, write_00081_len);
      }
      free(write_00081);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00082 = NULL;
      unsigned int write_00082_len = 0;
      write_00082 = append_var("busy_weekend", write_00082, &write_00082_len);
      if (write_00082_len > 0) {
         transmit_all(1, write_00082, write_00082_len);
      }
      free(write_00082);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00083 = NULL;
      unsigned int write_00083_len = 0;
      write_00083 = append_var("busy_weekend", write_00083, &write_00083_len);
      if (write_00083_len > 0) {
         transmit_all(1, write_00083, write_00083_len);
      }
      free(write_00083);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00084 = NULL;
      unsigned int write_00084_len = 0;
      write_00084 = append_var("busy_weekend", write_00084, &write_00084_len);
      if (write_00084_len > 0) {
         transmit_all(1, write_00084, write_00084_len);
      }
      free(write_00084);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00085 = NULL;
      unsigned int write_00085_len = 0;
      write_00085 = append_var("busy_weekend", write_00085, &write_00085_len);
      if (write_00085_len > 0) {
         transmit_all(1, write_00085, write_00085_len);
      }
      free(write_00085);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00086 = NULL;
      unsigned int write_00086_len = 0;
      write_00086 = append_var("busy_weekend", write_00086, &write_00086_len);
      if (write_00086_len > 0) {
         transmit_all(1, write_00086, write_00086_len);
      }
      free(write_00086);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00087 = NULL;
      unsigned int write_00087_len = 0;
      write_00087 = append_var("busy_weekend", write_00087, &write_00087_len);
      if (write_00087_len > 0) {
         transmit_all(1, write_00087, write_00087_len);
      }
      free(write_00087);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00088 = NULL;
      unsigned int write_00088_len = 0;
      write_00088 = append_var("busy_weekend", write_00088, &write_00088_len);
      if (write_00088_len > 0) {
         transmit_all(1, write_00088, write_00088_len);
      }
      free(write_00088);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00089 = NULL;
      unsigned int write_00089_len = 0;
      write_00089 = append_var("busy_weekend", write_00089, &write_00089_len);
      if (write_00089_len > 0) {
         transmit_all(1, write_00089, write_00089_len);
      }
      free(write_00089);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00090 = NULL;
      unsigned int write_00090_len = 0;
      write_00090 = append_var("busy_weekend", write_00090, &write_00090_len);
      if (write_00090_len > 0) {
         transmit_all(1, write_00090, write_00090_len);
      }
      free(write_00090);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00091 = NULL;
      unsigned int write_00091_len = 0;
      write_00091 = append_var("busy_weekend", write_00091, &write_00091_len);
      if (write_00091_len > 0) {
         transmit_all(1, write_00091, write_00091_len);
      }
      free(write_00091);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00092 = NULL;
      unsigned int write_00092_len = 0;
      write_00092 = append_var("busy_weekend", write_00092, &write_00092_len);
      if (write_00092_len > 0) {
         transmit_all(1, write_00092, write_00092_len);
      }
      free(write_00092);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00093 = NULL;
      unsigned int write_00093_len = 0;
      write_00093 = append_var("busy_weekend", write_00093, &write_00093_len);
      if (write_00093_len > 0) {
         transmit_all(1, write_00093, write_00093_len);
      }
      free(write_00093);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00094 = NULL;
      unsigned int write_00094_len = 0;
      write_00094 = append_var("busy_weekend", write_00094, &write_00094_len);
      if (write_00094_len > 0) {
         transmit_all(1, write_00094, write_00094_len);
      }
      free(write_00094);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00095 = NULL;
      unsigned int write_00095_len = 0;
      write_00095 = append_var("busy_weekend", write_00095, &write_00095_len);
      if (write_00095_len > 0) {
         transmit_all(1, write_00095, write_00095_len);
      }
      free(write_00095);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00096 = NULL;
      unsigned int write_00096_len = 0;
      write_00096 = append_var("busy_weekend", write_00096, &write_00096_len);
      if (write_00096_len > 0) {
         transmit_all(1, write_00096, write_00096_len);
      }
      free(write_00096);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00097 = NULL;
      unsigned int write_00097_len = 0;
      write_00097 = append_var("busy_weekend", write_00097, &write_00097_len);
      if (write_00097_len > 0) {
         transmit_all(1, write_00097, write_00097_len);
      }
      free(write_00097);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00098 = NULL;
      unsigned int write_00098_len = 0;
      write_00098 = append_var("busy_weekend", write_00098, &write_00098_len);
      if (write_00098_len > 0) {
         transmit_all(1, write_00098, write_00098_len);
      }
      free(write_00098);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00099 = NULL;
      unsigned int write_00099_len = 0;
      write_00099 = append_var("busy_weekend", write_00099, &write_00099_len);
      if (write_00099_len > 0) {
         transmit_all(1, write_00099, write_00099_len);
      }
      free(write_00099);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00100 = NULL;
      unsigned int write_00100_len = 0;
      write_00100 = append_var("busy_weekend", write_00100, &write_00100_len);
      if (write_00100_len > 0) {
         transmit_all(1, write_00100, write_00100_len);
      }
      free(write_00100);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00101 = NULL;
      unsigned int write_00101_len = 0;
      write_00101 = append_var("busy_weekend", write_00101, &write_00101_len);
      if (write_00101_len > 0) {
         transmit_all(1, write_00101, write_00101_len);
      }
      free(write_00101);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00102 = NULL;
      unsigned int write_00102_len = 0;
      write_00102 = append_var("busy_weekend", write_00102, &write_00102_len);
      if (write_00102_len > 0) {
         transmit_all(1, write_00102, write_00102_len);
      }
      free(write_00102);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00103 = NULL;
      unsigned int write_00103_len = 0;
      write_00103 = append_var("busy_weekend", write_00103, &write_00103_len);
      if (write_00103_len > 0) {
         transmit_all(1, write_00103, write_00103_len);
      }
      free(write_00103);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00104 = NULL;
      unsigned int write_00104_len = 0;
      write_00104 = append_var("busy_weekend", write_00104, &write_00104_len);
      if (write_00104_len > 0) {
         transmit_all(1, write_00104, write_00104_len);
      }
      free(write_00104);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00105 = NULL;
      unsigned int write_00105_len = 0;
      write_00105 = append_var("busy_weekend", write_00105, &write_00105_len);
      if (write_00105_len > 0) {
         transmit_all(1, write_00105, write_00105_len);
      }
      free(write_00105);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00106 = NULL;
      unsigned int write_00106_len = 0;
      write_00106 = append_var("busy_weekend", write_00106, &write_00106_len);
      if (write_00106_len > 0) {
         transmit_all(1, write_00106, write_00106_len);
      }
      free(write_00106);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00107 = NULL;
      unsigned int write_00107_len = 0;
      write_00107 = append_var("busy_weekend", write_00107, &write_00107_len);
      if (write_00107_len > 0) {
         transmit_all(1, write_00107, write_00107_len);
      }
      free(write_00107);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00108 = NULL;
      unsigned int write_00108_len = 0;
      write_00108 = append_var("busy_weekend", write_00108, &write_00108_len);
      if (write_00108_len > 0) {
         transmit_all(1, write_00108, write_00108_len);
      }
      free(write_00108);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00109 = NULL;
      unsigned int write_00109_len = 0;
      write_00109 = append_var("busy_weekend", write_00109, &write_00109_len);
      if (write_00109_len > 0) {
         transmit_all(1, write_00109, write_00109_len);
      }
      free(write_00109);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00110 = NULL;
      unsigned int write_00110_len = 0;
      write_00110 = append_var("busy_weekend", write_00110, &write_00110_len);
      if (write_00110_len > 0) {
         transmit_all(1, write_00110, write_00110_len);
      }
      free(write_00110);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00111 = NULL;
      unsigned int write_00111_len = 0;
      write_00111 = append_var("busy_weekend", write_00111, &write_00111_len);
      if (write_00111_len > 0) {
         transmit_all(1, write_00111, write_00111_len);
      }
      free(write_00111);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00112 = NULL;
      unsigned int write_00112_len = 0;
      write_00112 = append_var("busy_weekend", write_00112, &write_00112_len);
      if (write_00112_len > 0) {
         transmit_all(1, write_00112, write_00112_len);
      }
      free(write_00112);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00113 = NULL;
      unsigned int write_00113_len = 0;
      write_00113 = append_var("busy_weekend", write_00113, &write_00113_len);
      if (write_00113_len > 0) {
         transmit_all(1, write_00113, write_00113_len);
      }
      free(write_00113);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00114 = NULL;
      unsigned int write_00114_len = 0;
      write_00114 = append_var("busy_weekend", write_00114, &write_00114_len);
      if (write_00114_len > 0) {
         transmit_all(1, write_00114, write_00114_len);
      }
      free(write_00114);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00115 = NULL;
      unsigned int write_00115_len = 0;
      write_00115 = append_var("busy_weekend", write_00115, &write_00115_len);
      if (write_00115_len > 0) {
         transmit_all(1, write_00115, write_00115_len);
      }
      free(write_00115);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00116 = NULL;
      unsigned int write_00116_len = 0;
      write_00116 = append_var("busy_weekend", write_00116, &write_00116_len);
      if (write_00116_len > 0) {
         transmit_all(1, write_00116, write_00116_len);
      }
      free(write_00116);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00117 = NULL;
      unsigned int write_00117_len = 0;
      write_00117 = append_var("busy_weekend", write_00117, &write_00117_len);
      if (write_00117_len > 0) {
         transmit_all(1, write_00117, write_00117_len);
      }
      free(write_00117);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00118 = NULL;
      unsigned int write_00118_len = 0;
      write_00118 = append_var("busy_weekend", write_00118, &write_00118_len);
      if (write_00118_len > 0) {
         transmit_all(1, write_00118, write_00118_len);
      }
      free(write_00118);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00119 = NULL;
      unsigned int write_00119_len = 0;
      write_00119 = append_var("busy_weekend", write_00119, &write_00119_len);
      if (write_00119_len > 0) {
         transmit_all(1, write_00119, write_00119_len);
      }
      free(write_00119);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00120 = NULL;
      unsigned int write_00120_len = 0;
      write_00120 = append_var("busy_weekend", write_00120, &write_00120_len);
      if (write_00120_len > 0) {
         transmit_all(1, write_00120, write_00120_len);
      }
      free(write_00120);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00121 = NULL;
      unsigned int write_00121_len = 0;
      write_00121 = append_var("busy_weekend", write_00121, &write_00121_len);
      if (write_00121_len > 0) {
         transmit_all(1, write_00121, write_00121_len);
      }
      free(write_00121);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00122 = NULL;
      unsigned int write_00122_len = 0;
      write_00122 = append_var("busy_weekend", write_00122, &write_00122_len);
      if (write_00122_len > 0) {
         transmit_all(1, write_00122, write_00122_len);
      }
      free(write_00122);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00123 = NULL;
      unsigned int write_00123_len = 0;
      write_00123 = append_var("busy_weekend", write_00123, &write_00123_len);
      if (write_00123_len > 0) {
         transmit_all(1, write_00123, write_00123_len);
      }
      free(write_00123);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00124 = NULL;
      unsigned int write_00124_len = 0;
      write_00124 = append_var("busy_weekend", write_00124, &write_00124_len);
      if (write_00124_len > 0) {
         transmit_all(1, write_00124, write_00124_len);
      }
      free(write_00124);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00125 = NULL;
      unsigned int write_00125_len = 0;
      write_00125 = append_var("busy_weekend", write_00125, &write_00125_len);
      if (write_00125_len > 0) {
         transmit_all(1, write_00125, write_00125_len);
      }
      free(write_00125);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00126 = NULL;
      unsigned int write_00126_len = 0;
      write_00126 = append_var("busy_weekend", write_00126, &write_00126_len);
      if (write_00126_len > 0) {
         transmit_all(1, write_00126, write_00126_len);
      }
      free(write_00126);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00127 = NULL;
      unsigned int write_00127_len = 0;
      write_00127 = append_var("busy_weekend", write_00127, &write_00127_len);
      if (write_00127_len > 0) {
         transmit_all(1, write_00127, write_00127_len);
      }
      free(write_00127);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00128 = NULL;
      unsigned int write_00128_len = 0;
      write_00128 = append_var("busy_weekend", write_00128, &write_00128_len);
      if (write_00128_len > 0) {
         transmit_all(1, write_00128, write_00128_len);
      }
      free(write_00128);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00129 = NULL;
      unsigned int write_00129_len = 0;
      write_00129 = append_var("busy_weekend", write_00129, &write_00129_len);
      if (write_00129_len > 0) {
         transmit_all(1, write_00129, write_00129_len);
      }
      free(write_00129);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00130 = NULL;
      unsigned int write_00130_len = 0;
      write_00130 = append_var("busy_weekend", write_00130, &write_00130_len);
      if (write_00130_len > 0) {
         transmit_all(1, write_00130, write_00130_len);
      }
      free(write_00130);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00131 = NULL;
      unsigned int write_00131_len = 0;
      write_00131 = append_var("busy_weekend", write_00131, &write_00131_len);
      if (write_00131_len > 0) {
         transmit_all(1, write_00131, write_00131_len);
      }
      free(write_00131);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00132 = NULL;
      unsigned int write_00132_len = 0;
      write_00132 = append_var("busy_weekend", write_00132, &write_00132_len);
      if (write_00132_len > 0) {
         transmit_all(1, write_00132, write_00132_len);
      }
      free(write_00132);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00133 = NULL;
      unsigned int write_00133_len = 0;
      write_00133 = append_var("busy_weekend", write_00133, &write_00133_len);
      if (write_00133_len > 0) {
         transmit_all(1, write_00133, write_00133_len);
      }
      free(write_00133);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00134 = NULL;
      unsigned int write_00134_len = 0;
      write_00134 = append_var("busy_weekend", write_00134, &write_00134_len);
      if (write_00134_len > 0) {
         transmit_all(1, write_00134, write_00134_len);
      }
      free(write_00134);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00135 = NULL;
      unsigned int write_00135_len = 0;
      write_00135 = append_var("busy_weekend", write_00135, &write_00135_len);
      if (write_00135_len > 0) {
         transmit_all(1, write_00135, write_00135_len);
      }
      free(write_00135);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00136 = NULL;
      unsigned int write_00136_len = 0;
      write_00136 = append_var("busy_weekend", write_00136, &write_00136_len);
      if (write_00136_len > 0) {
         transmit_all(1, write_00136, write_00136_len);
      }
      free(write_00136);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00137 = NULL;
      unsigned int write_00137_len = 0;
      write_00137 = append_var("busy_weekend", write_00137, &write_00137_len);
      if (write_00137_len > 0) {
         transmit_all(1, write_00137, write_00137_len);
      }
      free(write_00137);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00138 = NULL;
      unsigned int write_00138_len = 0;
      write_00138 = append_var("busy_weekend", write_00138, &write_00138_len);
      if (write_00138_len > 0) {
         transmit_all(1, write_00138, write_00138_len);
      }
      free(write_00138);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00139 = NULL;
      unsigned int write_00139_len = 0;
      write_00139 = append_var("busy_weekend", write_00139, &write_00139_len);
      if (write_00139_len > 0) {
         transmit_all(1, write_00139, write_00139_len);
      }
      free(write_00139);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00140 = NULL;
      unsigned int write_00140_len = 0;
      write_00140 = append_var("busy_weekend", write_00140, &write_00140_len);
      if (write_00140_len > 0) {
         transmit_all(1, write_00140, write_00140_len);
      }
      free(write_00140);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00141 = NULL;
      unsigned int write_00141_len = 0;
      write_00141 = append_var("busy_weekend", write_00141, &write_00141_len);
      if (write_00141_len > 0) {
         transmit_all(1, write_00141, write_00141_len);
      }
      free(write_00141);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00142 = NULL;
      unsigned int write_00142_len = 0;
      write_00142 = append_var("busy_weekend", write_00142, &write_00142_len);
      if (write_00142_len > 0) {
         transmit_all(1, write_00142, write_00142_len);
      }
      free(write_00142);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00143 = NULL;
      unsigned int write_00143_len = 0;
      write_00143 = append_var("busy_weekend", write_00143, &write_00143_len);
      if (write_00143_len > 0) {
         transmit_all(1, write_00143, write_00143_len);
      }
      free(write_00143);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00144 = NULL;
      unsigned int write_00144_len = 0;
      write_00144 = append_var("busy_weekend", write_00144, &write_00144_len);
      if (write_00144_len > 0) {
         transmit_all(1, write_00144, write_00144_len);
      }
      free(write_00144);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00145 = NULL;
      unsigned int write_00145_len = 0;
      write_00145 = append_var("busy_weekend", write_00145, &write_00145_len);
      if (write_00145_len > 0) {
         transmit_all(1, write_00145, write_00145_len);
      }
      free(write_00145);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00146 = NULL;
      unsigned int write_00146_len = 0;
      write_00146 = append_var("busy_weekend", write_00146, &write_00146_len);
      if (write_00146_len > 0) {
         transmit_all(1, write_00146, write_00146_len);
      }
      free(write_00146);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00147 = NULL;
      unsigned int write_00147_len = 0;
      write_00147 = append_var("busy_weekend", write_00147, &write_00147_len);
      if (write_00147_len > 0) {
         transmit_all(1, write_00147, write_00147_len);
      }
      free(write_00147);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00148 = NULL;
      unsigned int write_00148_len = 0;
      write_00148 = append_var("busy_weekend", write_00148, &write_00148_len);
      if (write_00148_len > 0) {
         transmit_all(1, write_00148, write_00148_len);
      }
      free(write_00148);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00149 = NULL;
      unsigned int write_00149_len = 0;
      write_00149 = append_var("busy_weekend", write_00149, &write_00149_len);
      if (write_00149_len > 0) {
         transmit_all(1, write_00149, write_00149_len);
      }
      free(write_00149);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00150 = NULL;
      unsigned int write_00150_len = 0;
      write_00150 = append_var("busy_weekend", write_00150, &write_00150_len);
      if (write_00150_len > 0) {
         transmit_all(1, write_00150, write_00150_len);
      }
      free(write_00150);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00151 = NULL;
      unsigned int write_00151_len = 0;
      write_00151 = append_var("busy_weekend", write_00151, &write_00151_len);
      if (write_00151_len > 0) {
         transmit_all(1, write_00151, write_00151_len);
      }
      free(write_00151);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00152 = NULL;
      unsigned int write_00152_len = 0;
      write_00152 = append_var("busy_weekend", write_00152, &write_00152_len);
      if (write_00152_len > 0) {
         transmit_all(1, write_00152, write_00152_len);
      }
      free(write_00152);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00153 = NULL;
      unsigned int write_00153_len = 0;
      write_00153 = append_var("busy_weekend", write_00153, &write_00153_len);
      if (write_00153_len > 0) {
         transmit_all(1, write_00153, write_00153_len);
      }
      free(write_00153);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00154 = NULL;
      unsigned int write_00154_len = 0;
      write_00154 = append_var("busy_weekend", write_00154, &write_00154_len);
      if (write_00154_len > 0) {
         transmit_all(1, write_00154, write_00154_len);
      }
      free(write_00154);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00155 = NULL;
      unsigned int write_00155_len = 0;
      write_00155 = append_var("busy_weekend", write_00155, &write_00155_len);
      if (write_00155_len > 0) {
         transmit_all(1, write_00155, write_00155_len);
      }
      free(write_00155);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00156 = NULL;
      unsigned int write_00156_len = 0;
      write_00156 = append_var("busy_weekend", write_00156, &write_00156_len);
      if (write_00156_len > 0) {
         transmit_all(1, write_00156, write_00156_len);
      }
      free(write_00156);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00157 = NULL;
      unsigned int write_00157_len = 0;
      write_00157 = append_var("busy_weekend", write_00157, &write_00157_len);
      if (write_00157_len > 0) {
         transmit_all(1, write_00157, write_00157_len);
      }
      free(write_00157);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00158 = NULL;
      unsigned int write_00158_len = 0;
      write_00158 = append_var("busy_weekend", write_00158, &write_00158_len);
      if (write_00158_len > 0) {
         transmit_all(1, write_00158, write_00158_len);
      }
      free(write_00158);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00159 = NULL;
      unsigned int write_00159_len = 0;
      write_00159 = append_var("busy_weekend", write_00159, &write_00159_len);
      if (write_00159_len > 0) {
         transmit_all(1, write_00159, write_00159_len);
      }
      free(write_00159);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00160 = NULL;
      unsigned int write_00160_len = 0;
      write_00160 = append_var("busy_weekend", write_00160, &write_00160_len);
      if (write_00160_len > 0) {
         transmit_all(1, write_00160, write_00160_len);
      }
      free(write_00160);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00161 = NULL;
      unsigned int write_00161_len = 0;
      write_00161 = append_var("busy_weekend", write_00161, &write_00161_len);
      if (write_00161_len > 0) {
         transmit_all(1, write_00161, write_00161_len);
      }
      free(write_00161);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00162 = NULL;
      unsigned int write_00162_len = 0;
      write_00162 = append_var("busy_weekend", write_00162, &write_00162_len);
      if (write_00162_len > 0) {
         transmit_all(1, write_00162, write_00162_len);
      }
      free(write_00162);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00163 = NULL;
      unsigned int write_00163_len = 0;
      write_00163 = append_var("busy_weekend", write_00163, &write_00163_len);
      if (write_00163_len > 0) {
         transmit_all(1, write_00163, write_00163_len);
      }
      free(write_00163);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00164 = NULL;
      unsigned int write_00164_len = 0;
      write_00164 = append_var("busy_weekend", write_00164, &write_00164_len);
      if (write_00164_len > 0) {
         transmit_all(1, write_00164, write_00164_len);
      }
      free(write_00164);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00165 = NULL;
      unsigned int write_00165_len = 0;
      write_00165 = append_var("busy_weekend", write_00165, &write_00165_len);
      if (write_00165_len > 0) {
         transmit_all(1, write_00165, write_00165_len);
      }
      free(write_00165);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00166 = NULL;
      unsigned int write_00166_len = 0;
      write_00166 = append_var("busy_weekend", write_00166, &write_00166_len);
      if (write_00166_len > 0) {
         transmit_all(1, write_00166, write_00166_len);
      }
      free(write_00166);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00167 = NULL;
      unsigned int write_00167_len = 0;
      write_00167 = append_var("busy_weekend", write_00167, &write_00167_len);
      if (write_00167_len > 0) {
         transmit_all(1, write_00167, write_00167_len);
      }
      free(write_00167);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00168 = NULL;
      unsigned int write_00168_len = 0;
      write_00168 = append_var("busy_weekend", write_00168, &write_00168_len);
      if (write_00168_len > 0) {
         transmit_all(1, write_00168, write_00168_len);
      }
      free(write_00168);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00169 = NULL;
      unsigned int write_00169_len = 0;
      write_00169 = append_var("busy_weekend", write_00169, &write_00169_len);
      if (write_00169_len > 0) {
         transmit_all(1, write_00169, write_00169_len);
      }
      free(write_00169);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00170 = NULL;
      unsigned int write_00170_len = 0;
      write_00170 = append_var("busy_weekend", write_00170, &write_00170_len);
      if (write_00170_len > 0) {
         transmit_all(1, write_00170, write_00170_len);
      }
      free(write_00170);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00171 = NULL;
      unsigned int write_00171_len = 0;
      write_00171 = append_var("busy_weekend", write_00171, &write_00171_len);
      if (write_00171_len > 0) {
         transmit_all(1, write_00171, write_00171_len);
      }
      free(write_00171);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00172 = NULL;
      unsigned int write_00172_len = 0;
      write_00172 = append_var("busy_weekend", write_00172, &write_00172_len);
      if (write_00172_len > 0) {
         transmit_all(1, write_00172, write_00172_len);
      }
      free(write_00172);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00173 = NULL;
      unsigned int write_00173_len = 0;
      write_00173 = append_var("busy_weekend", write_00173, &write_00173_len);
      if (write_00173_len > 0) {
         transmit_all(1, write_00173, write_00173_len);
      }
      free(write_00173);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00174 = NULL;
      unsigned int write_00174_len = 0;
      write_00174 = append_var("busy_weekend", write_00174, &write_00174_len);
      if (write_00174_len > 0) {
         transmit_all(1, write_00174, write_00174_len);
      }
      free(write_00174);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00175 = NULL;
      unsigned int write_00175_len = 0;
      write_00175 = append_var("busy_weekend", write_00175, &write_00175_len);
      if (write_00175_len > 0) {
         transmit_all(1, write_00175, write_00175_len);
      }
      free(write_00175);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00176 = NULL;
      unsigned int write_00176_len = 0;
      write_00176 = append_var("busy_weekend", write_00176, &write_00176_len);
      if (write_00176_len > 0) {
         transmit_all(1, write_00176, write_00176_len);
      }
      free(write_00176);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00177 = NULL;
      unsigned int write_00177_len = 0;
      write_00177 = append_var("busy_weekend", write_00177, &write_00177_len);
      if (write_00177_len > 0) {
         transmit_all(1, write_00177, write_00177_len);
      }
      free(write_00177);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00178 = NULL;
      unsigned int write_00178_len = 0;
      write_00178 = append_var("busy_weekend", write_00178, &write_00178_len);
      if (write_00178_len > 0) {
         transmit_all(1, write_00178, write_00178_len);
      }
      free(write_00178);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00179 = NULL;
      unsigned int write_00179_len = 0;
      write_00179 = append_var("busy_weekend", write_00179, &write_00179_len);
      if (write_00179_len > 0) {
         transmit_all(1, write_00179, write_00179_len);
      }
      free(write_00179);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00180 = NULL;
      unsigned int write_00180_len = 0;
      write_00180 = append_var("busy_weekend", write_00180, &write_00180_len);
      if (write_00180_len > 0) {
         transmit_all(1, write_00180, write_00180_len);
      }
      free(write_00180);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00181 = NULL;
      unsigned int write_00181_len = 0;
      write_00181 = append_var("busy_weekend", write_00181, &write_00181_len);
      if (write_00181_len > 0) {
         transmit_all(1, write_00181, write_00181_len);
      }
      free(write_00181);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00182 = NULL;
      unsigned int write_00182_len = 0;
      write_00182 = append_var("busy_weekend", write_00182, &write_00182_len);
      if (write_00182_len > 0) {
         transmit_all(1, write_00182, write_00182_len);
      }
      free(write_00182);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00183 = NULL;
      unsigned int write_00183_len = 0;
      write_00183 = append_var("busy_weekend", write_00183, &write_00183_len);
      if (write_00183_len > 0) {
         transmit_all(1, write_00183, write_00183_len);
      }
      free(write_00183);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00184 = NULL;
      unsigned int write_00184_len = 0;
      write_00184 = append_var("busy_weekend", write_00184, &write_00184_len);
      if (write_00184_len > 0) {
         transmit_all(1, write_00184, write_00184_len);
      }
      free(write_00184);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00185 = NULL;
      unsigned int write_00185_len = 0;
      write_00185 = append_var("busy_weekend", write_00185, &write_00185_len);
      if (write_00185_len > 0) {
         transmit_all(1, write_00185, write_00185_len);
      }
      free(write_00185);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00186 = NULL;
      unsigned int write_00186_len = 0;
      write_00186 = append_var("busy_weekend", write_00186, &write_00186_len);
      if (write_00186_len > 0) {
         transmit_all(1, write_00186, write_00186_len);
      }
      free(write_00186);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00187 = NULL;
      unsigned int write_00187_len = 0;
      write_00187 = append_var("busy_weekend", write_00187, &write_00187_len);
      if (write_00187_len > 0) {
         transmit_all(1, write_00187, write_00187_len);
      }
      free(write_00187);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00188 = NULL;
      unsigned int write_00188_len = 0;
      write_00188 = append_var("busy_weekend", write_00188, &write_00188_len);
      if (write_00188_len > 0) {
         transmit_all(1, write_00188, write_00188_len);
      }
      free(write_00188);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00189 = NULL;
      unsigned int write_00189_len = 0;
      write_00189 = append_var("busy_weekend", write_00189, &write_00189_len);
      if (write_00189_len > 0) {
         transmit_all(1, write_00189, write_00189_len);
      }
      free(write_00189);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00190 = NULL;
      unsigned int write_00190_len = 0;
      write_00190 = append_var("busy_weekend", write_00190, &write_00190_len);
      if (write_00190_len > 0) {
         transmit_all(1, write_00190, write_00190_len);
      }
      free(write_00190);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00191 = NULL;
      unsigned int write_00191_len = 0;
      write_00191 = append_var("busy_weekend", write_00191, &write_00191_len);
      if (write_00191_len > 0) {
         transmit_all(1, write_00191, write_00191_len);
      }
      free(write_00191);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00192 = NULL;
      unsigned int write_00192_len = 0;
      write_00192 = append_var("busy_weekend", write_00192, &write_00192_len);
      if (write_00192_len > 0) {
         transmit_all(1, write_00192, write_00192_len);
      }
      free(write_00192);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00193 = NULL;
      unsigned int write_00193_len = 0;
      write_00193 = append_var("busy_weekend", write_00193, &write_00193_len);
      if (write_00193_len > 0) {
         transmit_all(1, write_00193, write_00193_len);
      }
      free(write_00193);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00194 = NULL;
      unsigned int write_00194_len = 0;
      write_00194 = append_var("busy_weekend", write_00194, &write_00194_len);
      if (write_00194_len > 0) {
         transmit_all(1, write_00194, write_00194_len);
      }
      free(write_00194);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00195 = NULL;
      unsigned int write_00195_len = 0;
      write_00195 = append_var("busy_weekend", write_00195, &write_00195_len);
      if (write_00195_len > 0) {
         transmit_all(1, write_00195, write_00195_len);
      }
      free(write_00195);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00196 = NULL;
      unsigned int write_00196_len = 0;
      write_00196 = append_var("busy_weekend", write_00196, &write_00196_len);
      if (write_00196_len > 0) {
         transmit_all(1, write_00196, write_00196_len);
      }
      free(write_00196);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00197 = NULL;
      unsigned int write_00197_len = 0;
      write_00197 = append_var("busy_weekend", write_00197, &write_00197_len);
      if (write_00197_len > 0) {
         transmit_all(1, write_00197, write_00197_len);
      }
      free(write_00197);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00198 = NULL;
      unsigned int write_00198_len = 0;
      write_00198 = append_var("busy_weekend", write_00198, &write_00198_len);
      if (write_00198_len > 0) {
         transmit_all(1, write_00198, write_00198_len);
      }
      free(write_00198);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00199 = NULL;
      unsigned int write_00199_len = 0;
      write_00199 = append_var("busy_weekend", write_00199, &write_00199_len);
      if (write_00199_len > 0) {
         transmit_all(1, write_00199, write_00199_len);
      }
      free(write_00199);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00200 = NULL;
      unsigned int write_00200_len = 0;
      write_00200 = append_var("busy_weekend", write_00200, &write_00200_len);
      if (write_00200_len > 0) {
         transmit_all(1, write_00200, write_00200_len);
      }
      free(write_00200);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00201 = NULL;
      unsigned int write_00201_len = 0;
      write_00201 = append_var("busy_weekend", write_00201, &write_00201_len);
      if (write_00201_len > 0) {
         transmit_all(1, write_00201, write_00201_len);
      }
      free(write_00201);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00202 = NULL;
      unsigned int write_00202_len = 0;
      write_00202 = append_var("busy_weekend", write_00202, &write_00202_len);
      if (write_00202_len > 0) {
         transmit_all(1, write_00202, write_00202_len);
      }
      free(write_00202);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00203 = NULL;
      unsigned int write_00203_len = 0;
      write_00203 = append_var("busy_weekend", write_00203, &write_00203_len);
      if (write_00203_len > 0) {
         transmit_all(1, write_00203, write_00203_len);
      }
      free(write_00203);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00204 = NULL;
      unsigned int write_00204_len = 0;
      write_00204 = append_var("busy_weekend", write_00204, &write_00204_len);
      if (write_00204_len > 0) {
         transmit_all(1, write_00204, write_00204_len);
      }
      free(write_00204);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00205 = NULL;
      unsigned int write_00205_len = 0;
      write_00205 = append_var("busy_weekend", write_00205, &write_00205_len);
      if (write_00205_len > 0) {
         transmit_all(1, write_00205, write_00205_len);
      }
      free(write_00205);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00206 = NULL;
      unsigned int write_00206_len = 0;
      write_00206 = append_var("busy_weekend", write_00206, &write_00206_len);
      if (write_00206_len > 0) {
         transmit_all(1, write_00206, write_00206_len);
      }
      free(write_00206);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00207 = NULL;
      unsigned int write_00207_len = 0;
      write_00207 = append_var("busy_weekend", write_00207, &write_00207_len);
      if (write_00207_len > 0) {
         transmit_all(1, write_00207, write_00207_len);
      }
      free(write_00207);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00208 = NULL;
      unsigned int write_00208_len = 0;
      write_00208 = append_var("busy_weekend", write_00208, &write_00208_len);
      if (write_00208_len > 0) {
         transmit_all(1, write_00208, write_00208_len);
      }
      free(write_00208);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00209 = NULL;
      unsigned int write_00209_len = 0;
      write_00209 = append_var("busy_weekend", write_00209, &write_00209_len);
      if (write_00209_len > 0) {
         transmit_all(1, write_00209, write_00209_len);
      }
      free(write_00209);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00210 = NULL;
      unsigned int write_00210_len = 0;
      write_00210 = append_var("busy_weekend", write_00210, &write_00210_len);
      if (write_00210_len > 0) {
         transmit_all(1, write_00210, write_00210_len);
      }
      free(write_00210);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00211 = NULL;
      unsigned int write_00211_len = 0;
      write_00211 = append_var("busy_weekend", write_00211, &write_00211_len);
      if (write_00211_len > 0) {
         transmit_all(1, write_00211, write_00211_len);
      }
      free(write_00211);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00212 = NULL;
      unsigned int write_00212_len = 0;
      write_00212 = append_var("busy_weekend", write_00212, &write_00212_len);
      if (write_00212_len > 0) {
         transmit_all(1, write_00212, write_00212_len);
      }
      free(write_00212);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00213 = NULL;
      unsigned int write_00213_len = 0;
      write_00213 = append_var("busy_weekend", write_00213, &write_00213_len);
      if (write_00213_len > 0) {
         transmit_all(1, write_00213, write_00213_len);
      }
      free(write_00213);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00214 = NULL;
      unsigned int write_00214_len = 0;
      write_00214 = append_var("busy_weekend", write_00214, &write_00214_len);
      if (write_00214_len > 0) {
         transmit_all(1, write_00214, write_00214_len);
      }
      free(write_00214);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00215 = NULL;
      unsigned int write_00215_len = 0;
      write_00215 = append_var("busy_weekend", write_00215, &write_00215_len);
      if (write_00215_len > 0) {
         transmit_all(1, write_00215, write_00215_len);
      }
      free(write_00215);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00216 = NULL;
      unsigned int write_00216_len = 0;
      write_00216 = append_var("busy_weekend", write_00216, &write_00216_len);
      if (write_00216_len > 0) {
         transmit_all(1, write_00216, write_00216_len);
      }
      free(write_00216);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00217 = NULL;
      unsigned int write_00217_len = 0;
      write_00217 = append_var("busy_weekend", write_00217, &write_00217_len);
      if (write_00217_len > 0) {
         transmit_all(1, write_00217, write_00217_len);
      }
      free(write_00217);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00218 = NULL;
      unsigned int write_00218_len = 0;
      write_00218 = append_var("busy_weekend", write_00218, &write_00218_len);
      if (write_00218_len > 0) {
         transmit_all(1, write_00218, write_00218_len);
      }
      free(write_00218);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00219 = NULL;
      unsigned int write_00219_len = 0;
      write_00219 = append_var("busy_weekend", write_00219, &write_00219_len);
      if (write_00219_len > 0) {
         transmit_all(1, write_00219, write_00219_len);
      }
      free(write_00219);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00220 = NULL;
      unsigned int write_00220_len = 0;
      write_00220 = append_var("busy_weekend", write_00220, &write_00220_len);
      if (write_00220_len > 0) {
         transmit_all(1, write_00220, write_00220_len);
      }
      free(write_00220);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00221 = NULL;
      unsigned int write_00221_len = 0;
      write_00221 = append_var("busy_weekend", write_00221, &write_00221_len);
      if (write_00221_len > 0) {
         transmit_all(1, write_00221, write_00221_len);
      }
      free(write_00221);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00222 = NULL;
      unsigned int write_00222_len = 0;
      write_00222 = append_var("busy_weekend", write_00222, &write_00222_len);
      if (write_00222_len > 0) {
         transmit_all(1, write_00222, write_00222_len);
      }
      free(write_00222);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00223 = NULL;
      unsigned int write_00223_len = 0;
      write_00223 = append_var("busy_weekend", write_00223, &write_00223_len);
      if (write_00223_len > 0) {
         transmit_all(1, write_00223, write_00223_len);
      }
      free(write_00223);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00224 = NULL;
      unsigned int write_00224_len = 0;
      write_00224 = append_var("busy_weekend", write_00224, &write_00224_len);
      if (write_00224_len > 0) {
         transmit_all(1, write_00224, write_00224_len);
      }
      free(write_00224);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00225 = NULL;
      unsigned int write_00225_len = 0;
      write_00225 = append_var("busy_weekend", write_00225, &write_00225_len);
      if (write_00225_len > 0) {
         transmit_all(1, write_00225, write_00225_len);
      }
      free(write_00225);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00226 = NULL;
      unsigned int write_00226_len = 0;
      write_00226 = append_var("busy_weekend", write_00226, &write_00226_len);
      if (write_00226_len > 0) {
         transmit_all(1, write_00226, write_00226_len);
      }
      free(write_00226);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00227 = NULL;
      unsigned int write_00227_len = 0;
      write_00227 = append_var("busy_weekend", write_00227, &write_00227_len);
      if (write_00227_len > 0) {
         transmit_all(1, write_00227, write_00227_len);
      }
      free(write_00227);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00228 = NULL;
      unsigned int write_00228_len = 0;
      write_00228 = append_var("busy_weekend", write_00228, &write_00228_len);
      if (write_00228_len > 0) {
         transmit_all(1, write_00228, write_00228_len);
      }
      free(write_00228);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00229 = NULL;
      unsigned int write_00229_len = 0;
      write_00229 = append_var("busy_weekend", write_00229, &write_00229_len);
      if (write_00229_len > 0) {
         transmit_all(1, write_00229, write_00229_len);
      }
      free(write_00229);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00230 = NULL;
      unsigned int write_00230_len = 0;
      write_00230 = append_var("busy_weekend", write_00230, &write_00230_len);
      if (write_00230_len > 0) {
         transmit_all(1, write_00230, write_00230_len);
      }
      free(write_00230);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00231 = NULL;
      unsigned int write_00231_len = 0;
      write_00231 = append_var("busy_weekend", write_00231, &write_00231_len);
      if (write_00231_len > 0) {
         transmit_all(1, write_00231, write_00231_len);
      }
      free(write_00231);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00232 = NULL;
      unsigned int write_00232_len = 0;
      write_00232 = append_var("busy_weekend", write_00232, &write_00232_len);
      if (write_00232_len > 0) {
         transmit_all(1, write_00232, write_00232_len);
      }
      free(write_00232);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00233 = NULL;
      unsigned int write_00233_len = 0;
      write_00233 = append_var("busy_weekend", write_00233, &write_00233_len);
      if (write_00233_len > 0) {
         transmit_all(1, write_00233, write_00233_len);
      }
      free(write_00233);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00234 = NULL;
      unsigned int write_00234_len = 0;
      write_00234 = append_var("busy_weekend", write_00234, &write_00234_len);
      if (write_00234_len > 0) {
         transmit_all(1, write_00234, write_00234_len);
      }
      free(write_00234);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00235 = NULL;
      unsigned int write_00235_len = 0;
      write_00235 = append_var("busy_weekend", write_00235, &write_00235_len);
      if (write_00235_len > 0) {
         transmit_all(1, write_00235, write_00235_len);
      }
      free(write_00235);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00236 = NULL;
      unsigned int write_00236_len = 0;
      write_00236 = append_var("busy_weekend", write_00236, &write_00236_len);
      if (write_00236_len > 0) {
         transmit_all(1, write_00236, write_00236_len);
      }
      free(write_00236);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00237 = NULL;
      unsigned int write_00237_len = 0;
      write_00237 = append_var("busy_weekend", write_00237, &write_00237_len);
      if (write_00237_len > 0) {
         transmit_all(1, write_00237, write_00237_len);
      }
      free(write_00237);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00238 = NULL;
      unsigned int write_00238_len = 0;
      write_00238 = append_var("busy_weekend", write_00238, &write_00238_len);
      if (write_00238_len > 0) {
         transmit_all(1, write_00238, write_00238_len);
      }
      free(write_00238);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00239 = NULL;
      unsigned int write_00239_len = 0;
      write_00239 = append_var("busy_weekend", write_00239, &write_00239_len);
      if (write_00239_len > 0) {
         transmit_all(1, write_00239, write_00239_len);
      }
      free(write_00239);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00240 = NULL;
      unsigned int write_00240_len = 0;
      write_00240 = append_var("busy_weekend", write_00240, &write_00240_len);
      if (write_00240_len > 0) {
         transmit_all(1, write_00240, write_00240_len);
      }
      free(write_00240);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00241 = NULL;
      unsigned int write_00241_len = 0;
      write_00241 = append_var("busy_weekend", write_00241, &write_00241_len);
      if (write_00241_len > 0) {
         transmit_all(1, write_00241, write_00241_len);
      }
      free(write_00241);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00242 = NULL;
      unsigned int write_00242_len = 0;
      write_00242 = append_var("busy_weekend", write_00242, &write_00242_len);
      if (write_00242_len > 0) {
         transmit_all(1, write_00242, write_00242_len);
      }
      free(write_00242);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00243 = NULL;
      unsigned int write_00243_len = 0;
      write_00243 = append_var("busy_weekend", write_00243, &write_00243_len);
      if (write_00243_len > 0) {
         transmit_all(1, write_00243, write_00243_len);
      }
      free(write_00243);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00244 = NULL;
      unsigned int write_00244_len = 0;
      write_00244 = append_var("busy_weekend", write_00244, &write_00244_len);
      if (write_00244_len > 0) {
         transmit_all(1, write_00244, write_00244_len);
      }
      free(write_00244);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00245 = NULL;
      unsigned int write_00245_len = 0;
      write_00245 = append_var("busy_weekend", write_00245, &write_00245_len);
      if (write_00245_len > 0) {
         transmit_all(1, write_00245, write_00245_len);
      }
      free(write_00245);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00246 = NULL;
      unsigned int write_00246_len = 0;
      write_00246 = append_var("busy_weekend", write_00246, &write_00246_len);
      if (write_00246_len > 0) {
         transmit_all(1, write_00246, write_00246_len);
      }
      free(write_00246);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00247 = NULL;
      unsigned int write_00247_len = 0;
      write_00247 = append_var("busy_weekend", write_00247, &write_00247_len);
      if (write_00247_len > 0) {
         transmit_all(1, write_00247, write_00247_len);
      }
      free(write_00247);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00248 = NULL;
      unsigned int write_00248_len = 0;
      write_00248 = append_var("busy_weekend", write_00248, &write_00248_len);
      if (write_00248_len > 0) {
         transmit_all(1, write_00248, write_00248_len);
      }
      free(write_00248);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00249 = NULL;
      unsigned int write_00249_len = 0;
      write_00249 = append_var("busy_weekend", write_00249, &write_00249_len);
      if (write_00249_len > 0) {
         transmit_all(1, write_00249, write_00249_len);
      }
      free(write_00249);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00250 = NULL;
      unsigned int write_00250_len = 0;
      write_00250 = append_var("busy_weekend", write_00250, &write_00250_len);
      if (write_00250_len > 0) {
         transmit_all(1, write_00250, write_00250_len);
      }
      free(write_00250);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00251 = NULL;
      unsigned int write_00251_len = 0;
      write_00251 = append_var("busy_weekend", write_00251, &write_00251_len);
      if (write_00251_len > 0) {
         transmit_all(1, write_00251, write_00251_len);
      }
      free(write_00251);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00252 = NULL;
      unsigned int write_00252_len = 0;
      write_00252 = append_var("busy_weekend", write_00252, &write_00252_len);
      if (write_00252_len > 0) {
         transmit_all(1, write_00252, write_00252_len);
      }
      free(write_00252);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00253 = NULL;
      unsigned int write_00253_len = 0;
      write_00253 = append_var("busy_weekend", write_00253, &write_00253_len);
      if (write_00253_len > 0) {
         transmit_all(1, write_00253, write_00253_len);
      }
      free(write_00253);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00254 = NULL;
      unsigned int write_00254_len = 0;
      write_00254 = append_var("busy_weekend", write_00254, &write_00254_len);
      if (write_00254_len > 0) {
         transmit_all(1, write_00254, write_00254_len);
      }
      free(write_00254);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00255 = NULL;
      unsigned int write_00255_len = 0;
      write_00255 = append_var("busy_weekend", write_00255, &write_00255_len);
      if (write_00255_len > 0) {
         transmit_all(1, write_00255, write_00255_len);
      }
      free(write_00255);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00256 = NULL;
      unsigned int write_00256_len = 0;
      write_00256 = append_var("busy_weekend", write_00256, &write_00256_len);
      if (write_00256_len > 0) {
         transmit_all(1, write_00256, write_00256_len);
      }
      free(write_00256);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00257 = NULL;
      unsigned int write_00257_len = 0;
      write_00257 = append_var("busy_weekend", write_00257, &write_00257_len);
      if (write_00257_len > 0) {
         transmit_all(1, write_00257, write_00257_len);
      }
      free(write_00257);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00258 = NULL;
      unsigned int write_00258_len = 0;
      write_00258 = append_var("busy_weekend", write_00258, &write_00258_len);
      if (write_00258_len > 0) {
         transmit_all(1, write_00258, write_00258_len);
      }
      free(write_00258);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00259 = NULL;
      unsigned int write_00259_len = 0;
      write_00259 = append_var("busy_weekend", write_00259, &write_00259_len);
      if (write_00259_len > 0) {
         transmit_all(1, write_00259, write_00259_len);
      }
      free(write_00259);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00260 = NULL;
      unsigned int write_00260_len = 0;
      write_00260 = append_var("busy_weekend", write_00260, &write_00260_len);
      if (write_00260_len > 0) {
         transmit_all(1, write_00260, write_00260_len);
      }
      free(write_00260);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00261 = NULL;
      unsigned int write_00261_len = 0;
      write_00261 = append_var("busy_weekend", write_00261, &write_00261_len);
      if (write_00261_len > 0) {
         transmit_all(1, write_00261, write_00261_len);
      }
      free(write_00261);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00262 = NULL;
      unsigned int write_00262_len = 0;
      write_00262 = append_var("busy_weekend", write_00262, &write_00262_len);
      if (write_00262_len > 0) {
         transmit_all(1, write_00262, write_00262_len);
      }
      free(write_00262);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00263 = NULL;
      unsigned int write_00263_len = 0;
      write_00263 = append_var("busy_weekend", write_00263, &write_00263_len);
      if (write_00263_len > 0) {
         transmit_all(1, write_00263, write_00263_len);
      }
      free(write_00263);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00264 = NULL;
      unsigned int write_00264_len = 0;
      write_00264 = append_var("busy_weekend", write_00264, &write_00264_len);
      if (write_00264_len > 0) {
         transmit_all(1, write_00264, write_00264_len);
      }
      free(write_00264);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00265 = NULL;
      unsigned int write_00265_len = 0;
      write_00265 = append_var("busy_weekend", write_00265, &write_00265_len);
      if (write_00265_len > 0) {
         transmit_all(1, write_00265, write_00265_len);
      }
      free(write_00265);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00266 = NULL;
      unsigned int write_00266_len = 0;
      write_00266 = append_var("busy_weekend", write_00266, &write_00266_len);
      if (write_00266_len > 0) {
         transmit_all(1, write_00266, write_00266_len);
      }
      free(write_00266);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00267 = NULL;
      unsigned int write_00267_len = 0;
      write_00267 = append_var("busy_weekend", write_00267, &write_00267_len);
      if (write_00267_len > 0) {
         transmit_all(1, write_00267, write_00267_len);
      }
      free(write_00267);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00268 = NULL;
      unsigned int write_00268_len = 0;
      write_00268 = append_var("busy_weekend", write_00268, &write_00268_len);
      if (write_00268_len > 0) {
         transmit_all(1, write_00268, write_00268_len);
      }
      free(write_00268);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00269 = NULL;
      unsigned int write_00269_len = 0;
      write_00269 = append_var("busy_weekend", write_00269, &write_00269_len);
      if (write_00269_len > 0) {
         transmit_all(1, write_00269, write_00269_len);
      }
      free(write_00269);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00270 = NULL;
      unsigned int write_00270_len = 0;
      write_00270 = append_var("busy_weekend", write_00270, &write_00270_len);
      if (write_00270_len > 0) {
         transmit_all(1, write_00270, write_00270_len);
      }
      free(write_00270);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00271 = NULL;
      unsigned int write_00271_len = 0;
      write_00271 = append_var("busy_weekend", write_00271, &write_00271_len);
      if (write_00271_len > 0) {
         transmit_all(1, write_00271, write_00271_len);
      }
      free(write_00271);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00272 = NULL;
      unsigned int write_00272_len = 0;
      write_00272 = append_var("busy_weekend", write_00272, &write_00272_len);
      if (write_00272_len > 0) {
         transmit_all(1, write_00272, write_00272_len);
      }
      free(write_00272);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00273 = NULL;
      unsigned int write_00273_len = 0;
      write_00273 = append_var("busy_weekend", write_00273, &write_00273_len);
      if (write_00273_len > 0) {
         transmit_all(1, write_00273, write_00273_len);
      }
      free(write_00273);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00274 = NULL;
      unsigned int write_00274_len = 0;
      write_00274 = append_var("busy_weekend", write_00274, &write_00274_len);
      if (write_00274_len > 0) {
         transmit_all(1, write_00274, write_00274_len);
      }
      free(write_00274);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00275 = NULL;
      unsigned int write_00275_len = 0;
      write_00275 = append_var("busy_weekend", write_00275, &write_00275_len);
      if (write_00275_len > 0) {
         transmit_all(1, write_00275, write_00275_len);
      }
      free(write_00275);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00276 = NULL;
      unsigned int write_00276_len = 0;
      write_00276 = append_var("busy_weekend", write_00276, &write_00276_len);
      if (write_00276_len > 0) {
         transmit_all(1, write_00276, write_00276_len);
      }
      free(write_00276);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00277 = NULL;
      unsigned int write_00277_len = 0;
      write_00277 = append_var("busy_weekend", write_00277, &write_00277_len);
      if (write_00277_len > 0) {
         transmit_all(1, write_00277, write_00277_len);
      }
      free(write_00277);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00278 = NULL;
      unsigned int write_00278_len = 0;
      write_00278 = append_var("busy_weekend", write_00278, &write_00278_len);
      if (write_00278_len > 0) {
         transmit_all(1, write_00278, write_00278_len);
      }
      free(write_00278);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00279 = NULL;
      unsigned int write_00279_len = 0;
      write_00279 = append_var("busy_weekend", write_00279, &write_00279_len);
      if (write_00279_len > 0) {
         transmit_all(1, write_00279, write_00279_len);
      }
      free(write_00279);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00280 = NULL;
      unsigned int write_00280_len = 0;
      write_00280 = append_var("busy_weekend", write_00280, &write_00280_len);
      if (write_00280_len > 0) {
         transmit_all(1, write_00280, write_00280_len);
      }
      free(write_00280);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00281 = NULL;
      unsigned int write_00281_len = 0;
      write_00281 = append_var("busy_weekend", write_00281, &write_00281_len);
      if (write_00281_len > 0) {
         transmit_all(1, write_00281, write_00281_len);
      }
      free(write_00281);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00282 = NULL;
      unsigned int write_00282_len = 0;
      write_00282 = append_var("busy_weekend", write_00282, &write_00282_len);
      if (write_00282_len > 0) {
         transmit_all(1, write_00282, write_00282_len);
      }
      free(write_00282);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00283 = NULL;
      unsigned int write_00283_len = 0;
      write_00283 = append_var("busy_weekend", write_00283, &write_00283_len);
      if (write_00283_len > 0) {
         transmit_all(1, write_00283, write_00283_len);
      }
      free(write_00283);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00284 = NULL;
      unsigned int write_00284_len = 0;
      write_00284 = append_var("busy_weekend", write_00284, &write_00284_len);
      if (write_00284_len > 0) {
         transmit_all(1, write_00284, write_00284_len);
      }
      free(write_00284);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00285 = NULL;
      unsigned int write_00285_len = 0;
      write_00285 = append_var("busy_weekend", write_00285, &write_00285_len);
      if (write_00285_len > 0) {
         transmit_all(1, write_00285, write_00285_len);
      }
      free(write_00285);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00286 = NULL;
      unsigned int write_00286_len = 0;
      write_00286 = append_var("busy_weekend", write_00286, &write_00286_len);
      if (write_00286_len > 0) {
         transmit_all(1, write_00286, write_00286_len);
      }
      free(write_00286);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00287 = NULL;
      unsigned int write_00287_len = 0;
      write_00287 = append_var("busy_weekend", write_00287, &write_00287_len);
      if (write_00287_len > 0) {
         transmit_all(1, write_00287, write_00287_len);
      }
      free(write_00287);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00288 = NULL;
      unsigned int write_00288_len = 0;
      write_00288 = append_var("busy_weekend", write_00288, &write_00288_len);
      if (write_00288_len > 0) {
         transmit_all(1, write_00288, write_00288_len);
      }
      free(write_00288);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00289 = NULL;
      unsigned int write_00289_len = 0;
      write_00289 = append_var("busy_weekend", write_00289, &write_00289_len);
      if (write_00289_len > 0) {
         transmit_all(1, write_00289, write_00289_len);
      }
      free(write_00289);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00290 = NULL;
      unsigned int write_00290_len = 0;
      write_00290 = append_var("busy_weekend", write_00290, &write_00290_len);
      if (write_00290_len > 0) {
         transmit_all(1, write_00290, write_00290_len);
      }
      free(write_00290);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00291 = NULL;
      unsigned int write_00291_len = 0;
      write_00291 = append_var("busy_weekend", write_00291, &write_00291_len);
      if (write_00291_len > 0) {
         transmit_all(1, write_00291, write_00291_len);
      }
      free(write_00291);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00292 = NULL;
      unsigned int write_00292_len = 0;
      write_00292 = append_var("busy_weekend", write_00292, &write_00292_len);
      if (write_00292_len > 0) {
         transmit_all(1, write_00292, write_00292_len);
      }
      free(write_00292);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00293 = NULL;
      unsigned int write_00293_len = 0;
      write_00293 = append_var("busy_weekend", write_00293, &write_00293_len);
      if (write_00293_len > 0) {
         transmit_all(1, write_00293, write_00293_len);
      }
      free(write_00293);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00294 = NULL;
      unsigned int write_00294_len = 0;
      write_00294 = append_var("busy_weekend", write_00294, &write_00294_len);
      if (write_00294_len > 0) {
         transmit_all(1, write_00294, write_00294_len);
      }
      free(write_00294);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00295 = NULL;
      unsigned int write_00295_len = 0;
      write_00295 = append_var("busy_weekend", write_00295, &write_00295_len);
      if (write_00295_len > 0) {
         transmit_all(1, write_00295, write_00295_len);
      }
      free(write_00295);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00296 = NULL;
      unsigned int write_00296_len = 0;
      write_00296 = append_var("busy_weekend", write_00296, &write_00296_len);
      if (write_00296_len > 0) {
         transmit_all(1, write_00296, write_00296_len);
      }
      free(write_00296);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00297 = NULL;
      unsigned int write_00297_len = 0;
      write_00297 = append_var("busy_weekend", write_00297, &write_00297_len);
      if (write_00297_len > 0) {
         transmit_all(1, write_00297, write_00297_len);
      }
      free(write_00297);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00298 = NULL;
      unsigned int write_00298_len = 0;
      write_00298 = append_var("busy_weekend", write_00298, &write_00298_len);
      if (write_00298_len > 0) {
         transmit_all(1, write_00298, write_00298_len);
      }
      free(write_00298);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00299 = NULL;
      unsigned int write_00299_len = 0;
      write_00299 = append_var("busy_weekend", write_00299, &write_00299_len);
      if (write_00299_len > 0) {
         transmit_all(1, write_00299, write_00299_len);
      }
      free(write_00299);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00300 = NULL;
      unsigned int write_00300_len = 0;
      write_00300 = append_var("busy_weekend", write_00300, &write_00300_len);
      if (write_00300_len > 0) {
         transmit_all(1, write_00300, write_00300_len);
      }
      free(write_00300);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00301 = NULL;
      unsigned int write_00301_len = 0;
      write_00301 = append_var("busy_weekend", write_00301, &write_00301_len);
      if (write_00301_len > 0) {
         transmit_all(1, write_00301, write_00301_len);
      }
      free(write_00301);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00302 = NULL;
      unsigned int write_00302_len = 0;
      write_00302 = append_var("busy_weekend", write_00302, &write_00302_len);
      if (write_00302_len > 0) {
         transmit_all(1, write_00302, write_00302_len);
      }
      free(write_00302);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00303 = NULL;
      unsigned int write_00303_len = 0;
      write_00303 = append_var("busy_weekend", write_00303, &write_00303_len);
      if (write_00303_len > 0) {
         transmit_all(1, write_00303, write_00303_len);
      }
      free(write_00303);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00304 = NULL;
      unsigned int write_00304_len = 0;
      write_00304 = append_var("busy_weekend", write_00304, &write_00304_len);
      if (write_00304_len > 0) {
         transmit_all(1, write_00304, write_00304_len);
      }
      free(write_00304);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00305 = NULL;
      unsigned int write_00305_len = 0;
      write_00305 = append_var("busy_weekend", write_00305, &write_00305_len);
      if (write_00305_len > 0) {
         transmit_all(1, write_00305, write_00305_len);
      }
      free(write_00305);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00306 = NULL;
      unsigned int write_00306_len = 0;
      write_00306 = append_var("busy_weekend", write_00306, &write_00306_len);
      if (write_00306_len > 0) {
         transmit_all(1, write_00306, write_00306_len);
      }
      free(write_00306);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00307 = NULL;
      unsigned int write_00307_len = 0;
      write_00307 = append_var("busy_weekend", write_00307, &write_00307_len);
      if (write_00307_len > 0) {
         transmit_all(1, write_00307, write_00307_len);
      }
      free(write_00307);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00308 = NULL;
      unsigned int write_00308_len = 0;
      write_00308 = append_var("busy_weekend", write_00308, &write_00308_len);
      if (write_00308_len > 0) {
         transmit_all(1, write_00308, write_00308_len);
      }
      free(write_00308);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00309 = NULL;
      unsigned int write_00309_len = 0;
      write_00309 = append_var("busy_weekend", write_00309, &write_00309_len);
      if (write_00309_len > 0) {
         transmit_all(1, write_00309, write_00309_len);
      }
      free(write_00309);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00310 = NULL;
      unsigned int write_00310_len = 0;
      write_00310 = append_var("busy_weekend", write_00310, &write_00310_len);
      if (write_00310_len > 0) {
         transmit_all(1, write_00310, write_00310_len);
      }
      free(write_00310);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00311 = NULL;
      unsigned int write_00311_len = 0;
      write_00311 = append_var("busy_weekend", write_00311, &write_00311_len);
      if (write_00311_len > 0) {
         transmit_all(1, write_00311, write_00311_len);
      }
      free(write_00311);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00312 = NULL;
      unsigned int write_00312_len = 0;
      write_00312 = append_var("busy_weekend", write_00312, &write_00312_len);
      if (write_00312_len > 0) {
         transmit_all(1, write_00312, write_00312_len);
      }
      free(write_00312);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00313 = NULL;
      unsigned int write_00313_len = 0;
      write_00313 = append_var("busy_weekend", write_00313, &write_00313_len);
      if (write_00313_len > 0) {
         transmit_all(1, write_00313, write_00313_len);
      }
      free(write_00313);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00314 = NULL;
      unsigned int write_00314_len = 0;
      write_00314 = append_var("busy_weekend", write_00314, &write_00314_len);
      if (write_00314_len > 0) {
         transmit_all(1, write_00314, write_00314_len);
      }
      free(write_00314);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00315 = NULL;
      unsigned int write_00315_len = 0;
      write_00315 = append_var("busy_weekend", write_00315, &write_00315_len);
      if (write_00315_len > 0) {
         transmit_all(1, write_00315, write_00315_len);
      }
      free(write_00315);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00316 = NULL;
      unsigned int write_00316_len = 0;
      write_00316 = append_var("busy_weekend", write_00316, &write_00316_len);
      if (write_00316_len > 0) {
         transmit_all(1, write_00316, write_00316_len);
      }
      free(write_00316);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00317 = NULL;
      unsigned int write_00317_len = 0;
      write_00317 = append_var("busy_weekend", write_00317, &write_00317_len);
      if (write_00317_len > 0) {
         transmit_all(1, write_00317, write_00317_len);
      }
      free(write_00317);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00318 = NULL;
      unsigned int write_00318_len = 0;
      write_00318 = append_var("busy_weekend", write_00318, &write_00318_len);
      if (write_00318_len > 0) {
         transmit_all(1, write_00318, write_00318_len);
      }
      free(write_00318);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00319 = NULL;
      unsigned int write_00319_len = 0;
      write_00319 = append_var("busy_weekend", write_00319, &write_00319_len);
      if (write_00319_len > 0) {
         transmit_all(1, write_00319, write_00319_len);
      }
      free(write_00319);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00320 = NULL;
      unsigned int write_00320_len = 0;
      write_00320 = append_var("busy_weekend", write_00320, &write_00320_len);
      if (write_00320_len > 0) {
         transmit_all(1, write_00320, write_00320_len);
      }
      free(write_00320);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00321 = NULL;
      unsigned int write_00321_len = 0;
      write_00321 = append_var("busy_weekend", write_00321, &write_00321_len);
      if (write_00321_len > 0) {
         transmit_all(1, write_00321, write_00321_len);
      }
      free(write_00321);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00322 = NULL;
      unsigned int write_00322_len = 0;
      write_00322 = append_var("busy_weekend", write_00322, &write_00322_len);
      if (write_00322_len > 0) {
         transmit_all(1, write_00322, write_00322_len);
      }
      free(write_00322);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00323 = NULL;
      unsigned int write_00323_len = 0;
      write_00323 = append_var("busy_weekend", write_00323, &write_00323_len);
      if (write_00323_len > 0) {
         transmit_all(1, write_00323, write_00323_len);
      }
      free(write_00323);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00324 = NULL;
      unsigned int write_00324_len = 0;
      write_00324 = append_var("busy_weekend", write_00324, &write_00324_len);
      if (write_00324_len > 0) {
         transmit_all(1, write_00324, write_00324_len);
      }
      free(write_00324);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00325 = NULL;
      unsigned int write_00325_len = 0;
      write_00325 = append_var("busy_weekend", write_00325, &write_00325_len);
      if (write_00325_len > 0) {
         transmit_all(1, write_00325, write_00325_len);
      }
      free(write_00325);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00326 = NULL;
      unsigned int write_00326_len = 0;
      write_00326 = append_var("busy_weekend", write_00326, &write_00326_len);
      if (write_00326_len > 0) {
         transmit_all(1, write_00326, write_00326_len);
      }
      free(write_00326);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00327 = NULL;
      unsigned int write_00327_len = 0;
      write_00327 = append_var("busy_weekend", write_00327, &write_00327_len);
      if (write_00327_len > 0) {
         transmit_all(1, write_00327, write_00327_len);
      }
      free(write_00327);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00328 = NULL;
      unsigned int write_00328_len = 0;
      write_00328 = append_var("busy_weekend", write_00328, &write_00328_len);
      if (write_00328_len > 0) {
         transmit_all(1, write_00328, write_00328_len);
      }
      free(write_00328);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00329 = NULL;
      unsigned int write_00329_len = 0;
      write_00329 = append_var("busy_weekend", write_00329, &write_00329_len);
      if (write_00329_len > 0) {
         transmit_all(1, write_00329, write_00329_len);
      }
      free(write_00329);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00330 = NULL;
      unsigned int write_00330_len = 0;
      write_00330 = append_var("busy_weekend", write_00330, &write_00330_len);
      if (write_00330_len > 0) {
         transmit_all(1, write_00330, write_00330_len);
      }
      free(write_00330);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00331 = NULL;
      unsigned int write_00331_len = 0;
      write_00331 = append_var("busy_weekend", write_00331, &write_00331_len);
      if (write_00331_len > 0) {
         transmit_all(1, write_00331, write_00331_len);
      }
      free(write_00331);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00332 = NULL;
      unsigned int write_00332_len = 0;
      write_00332 = append_var("busy_weekend", write_00332, &write_00332_len);
      if (write_00332_len > 0) {
         transmit_all(1, write_00332, write_00332_len);
      }
      free(write_00332);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00333 = NULL;
      unsigned int write_00333_len = 0;
      write_00333 = append_var("busy_weekend", write_00333, &write_00333_len);
      if (write_00333_len > 0) {
         transmit_all(1, write_00333, write_00333_len);
      }
      free(write_00333);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00334 = NULL;
      unsigned int write_00334_len = 0;
      write_00334 = append_var("busy_weekend", write_00334, &write_00334_len);
      if (write_00334_len > 0) {
         transmit_all(1, write_00334, write_00334_len);
      }
      free(write_00334);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00335 = NULL;
      unsigned int write_00335_len = 0;
      write_00335 = append_var("busy_weekend", write_00335, &write_00335_len);
      if (write_00335_len > 0) {
         transmit_all(1, write_00335, write_00335_len);
      }
      free(write_00335);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00336 = NULL;
      unsigned int write_00336_len = 0;
      write_00336 = append_var("busy_weekend", write_00336, &write_00336_len);
      if (write_00336_len > 0) {
         transmit_all(1, write_00336, write_00336_len);
      }
      free(write_00336);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00337 = NULL;
      unsigned int write_00337_len = 0;
      write_00337 = append_var("busy_weekend", write_00337, &write_00337_len);
      if (write_00337_len > 0) {
         transmit_all(1, write_00337, write_00337_len);
      }
      free(write_00337);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00338 = NULL;
      unsigned int write_00338_len = 0;
      write_00338 = append_var("busy_weekend", write_00338, &write_00338_len);
      if (write_00338_len > 0) {
         transmit_all(1, write_00338, write_00338_len);
      }
      free(write_00338);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00339 = NULL;
      unsigned int write_00339_len = 0;
      write_00339 = append_var("busy_weekend", write_00339, &write_00339_len);
      if (write_00339_len > 0) {
         transmit_all(1, write_00339, write_00339_len);
      }
      free(write_00339);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00340 = NULL;
      unsigned int write_00340_len = 0;
      write_00340 = append_var("busy_weekend", write_00340, &write_00340_len);
      if (write_00340_len > 0) {
         transmit_all(1, write_00340, write_00340_len);
      }
      free(write_00340);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00341 = NULL;
      unsigned int write_00341_len = 0;
      write_00341 = append_var("busy_weekend", write_00341, &write_00341_len);
      if (write_00341_len > 0) {
         transmit_all(1, write_00341, write_00341_len);
      }
      free(write_00341);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00342 = NULL;
      unsigned int write_00342_len = 0;
      write_00342 = append_var("busy_weekend", write_00342, &write_00342_len);
      if (write_00342_len > 0) {
         transmit_all(1, write_00342, write_00342_len);
      }
      free(write_00342);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00343 = NULL;
      unsigned int write_00343_len = 0;
      write_00343 = append_var("busy_weekend", write_00343, &write_00343_len);
      if (write_00343_len > 0) {
         transmit_all(1, write_00343, write_00343_len);
      }
      free(write_00343);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00344 = NULL;
      unsigned int write_00344_len = 0;
      write_00344 = append_var("busy_weekend", write_00344, &write_00344_len);
      if (write_00344_len > 0) {
         transmit_all(1, write_00344, write_00344_len);
      }
      free(write_00344);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00345 = NULL;
      unsigned int write_00345_len = 0;
      write_00345 = append_var("busy_weekend", write_00345, &write_00345_len);
      if (write_00345_len > 0) {
         transmit_all(1, write_00345, write_00345_len);
      }
      free(write_00345);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00346 = NULL;
      unsigned int write_00346_len = 0;
      write_00346 = append_var("busy_weekend", write_00346, &write_00346_len);
      if (write_00346_len > 0) {
         transmit_all(1, write_00346, write_00346_len);
      }
      free(write_00346);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00347 = NULL;
      unsigned int write_00347_len = 0;
      write_00347 = append_var("busy_weekend", write_00347, &write_00347_len);
      if (write_00347_len > 0) {
         transmit_all(1, write_00347, write_00347_len);
      }
      free(write_00347);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00348 = NULL;
      unsigned int write_00348_len = 0;
      write_00348 = append_var("busy_weekend", write_00348, &write_00348_len);
      if (write_00348_len > 0) {
         transmit_all(1, write_00348, write_00348_len);
      }
      free(write_00348);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00349 = NULL;
      unsigned int write_00349_len = 0;
      write_00349 = append_var("busy_weekend", write_00349, &write_00349_len);
      if (write_00349_len > 0) {
         transmit_all(1, write_00349, write_00349_len);
      }
      free(write_00349);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00350 = NULL;
      unsigned int write_00350_len = 0;
      write_00350 = append_var("busy_weekend", write_00350, &write_00350_len);
      if (write_00350_len > 0) {
         transmit_all(1, write_00350, write_00350_len);
      }
      free(write_00350);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00351 = NULL;
      unsigned int write_00351_len = 0;
      write_00351 = append_var("busy_weekend", write_00351, &write_00351_len);
      if (write_00351_len > 0) {
         transmit_all(1, write_00351, write_00351_len);
      }
      free(write_00351);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00352 = NULL;
      unsigned int write_00352_len = 0;
      write_00352 = append_var("busy_weekend", write_00352, &write_00352_len);
      if (write_00352_len > 0) {
         transmit_all(1, write_00352, write_00352_len);
      }
      free(write_00352);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00353 = NULL;
      unsigned int write_00353_len = 0;
      write_00353 = append_var("busy_weekend", write_00353, &write_00353_len);
      if (write_00353_len > 0) {
         transmit_all(1, write_00353, write_00353_len);
      }
      free(write_00353);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00354 = NULL;
      unsigned int write_00354_len = 0;
      write_00354 = append_var("busy_weekend", write_00354, &write_00354_len);
      if (write_00354_len > 0) {
         transmit_all(1, write_00354, write_00354_len);
      }
      free(write_00354);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00355 = NULL;
      unsigned int write_00355_len = 0;
      write_00355 = append_var("busy_weekend", write_00355, &write_00355_len);
      if (write_00355_len > 0) {
         transmit_all(1, write_00355, write_00355_len);
      }
      free(write_00355);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00356 = NULL;
      unsigned int write_00356_len = 0;
      write_00356 = append_var("busy_weekend", write_00356, &write_00356_len);
      if (write_00356_len > 0) {
         transmit_all(1, write_00356, write_00356_len);
      }
      free(write_00356);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00357 = NULL;
      unsigned int write_00357_len = 0;
      write_00357 = append_var("busy_weekend", write_00357, &write_00357_len);
      if (write_00357_len > 0) {
         transmit_all(1, write_00357, write_00357_len);
      }
      free(write_00357);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00358 = NULL;
      unsigned int write_00358_len = 0;
      write_00358 = append_var("busy_weekend", write_00358, &write_00358_len);
      if (write_00358_len > 0) {
         transmit_all(1, write_00358, write_00358_len);
      }
      free(write_00358);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00359 = NULL;
      unsigned int write_00359_len = 0;
      write_00359 = append_var("busy_weekend", write_00359, &write_00359_len);
      if (write_00359_len > 0) {
         transmit_all(1, write_00359, write_00359_len);
      }
      free(write_00359);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00360 = NULL;
      unsigned int write_00360_len = 0;
      write_00360 = append_var("busy_weekend", write_00360, &write_00360_len);
      if (write_00360_len > 0) {
         transmit_all(1, write_00360, write_00360_len);
      }
      free(write_00360);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00361 = NULL;
      unsigned int write_00361_len = 0;
      write_00361 = append_var("busy_weekend", write_00361, &write_00361_len);
      if (write_00361_len > 0) {
         transmit_all(1, write_00361, write_00361_len);
      }
      free(write_00361);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00362 = NULL;
      unsigned int write_00362_len = 0;
      write_00362 = append_var("busy_weekend", write_00362, &write_00362_len);
      if (write_00362_len > 0) {
         transmit_all(1, write_00362, write_00362_len);
      }
      free(write_00362);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00363 = NULL;
      unsigned int write_00363_len = 0;
      write_00363 = append_var("busy_weekend", write_00363, &write_00363_len);
      if (write_00363_len > 0) {
         transmit_all(1, write_00363, write_00363_len);
      }
      free(write_00363);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00364 = NULL;
      unsigned int write_00364_len = 0;
      write_00364 = append_var("busy_weekend", write_00364, &write_00364_len);
      if (write_00364_len > 0) {
         transmit_all(1, write_00364, write_00364_len);
      }
      free(write_00364);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00365 = NULL;
      unsigned int write_00365_len = 0;
      write_00365 = append_var("busy_weekend", write_00365, &write_00365_len);
      if (write_00365_len > 0) {
         transmit_all(1, write_00365, write_00365_len);
      }
      free(write_00365);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00366 = NULL;
      unsigned int write_00366_len = 0;
      write_00366 = append_var("busy_weekend", write_00366, &write_00366_len);
      if (write_00366_len > 0) {
         transmit_all(1, write_00366, write_00366_len);
      }
      free(write_00366);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00367 = NULL;
      unsigned int write_00367_len = 0;
      write_00367 = append_var("busy_weekend", write_00367, &write_00367_len);
      if (write_00367_len > 0) {
         transmit_all(1, write_00367, write_00367_len);
      }
      free(write_00367);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00368 = NULL;
      unsigned int write_00368_len = 0;
      write_00368 = append_var("busy_weekend", write_00368, &write_00368_len);
      if (write_00368_len > 0) {
         transmit_all(1, write_00368, write_00368_len);
      }
      free(write_00368);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00369 = NULL;
      unsigned int write_00369_len = 0;
      write_00369 = append_var("busy_weekend", write_00369, &write_00369_len);
      if (write_00369_len > 0) {
         transmit_all(1, write_00369, write_00369_len);
      }
      free(write_00369);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00370 = NULL;
      unsigned int write_00370_len = 0;
      write_00370 = append_var("busy_weekend", write_00370, &write_00370_len);
      if (write_00370_len > 0) {
         transmit_all(1, write_00370, write_00370_len);
      }
      free(write_00370);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00371 = NULL;
      unsigned int write_00371_len = 0;
      write_00371 = append_var("busy_weekend", write_00371, &write_00371_len);
      if (write_00371_len > 0) {
         transmit_all(1, write_00371, write_00371_len);
      }
      free(write_00371);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00372 = NULL;
      unsigned int write_00372_len = 0;
      write_00372 = append_var("busy_weekend", write_00372, &write_00372_len);
      if (write_00372_len > 0) {
         transmit_all(1, write_00372, write_00372_len);
      }
      free(write_00372);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00373 = NULL;
      unsigned int write_00373_len = 0;
      write_00373 = append_var("busy_weekend", write_00373, &write_00373_len);
      if (write_00373_len > 0) {
         transmit_all(1, write_00373, write_00373_len);
      }
      free(write_00373);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00374 = NULL;
      unsigned int write_00374_len = 0;
      write_00374 = append_var("busy_weekend", write_00374, &write_00374_len);
      if (write_00374_len > 0) {
         transmit_all(1, write_00374, write_00374_len);
      }
      free(write_00374);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00375 = NULL;
      unsigned int write_00375_len = 0;
      write_00375 = append_var("busy_weekend", write_00375, &write_00375_len);
      if (write_00375_len > 0) {
         transmit_all(1, write_00375, write_00375_len);
      }
      free(write_00375);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00376 = NULL;
      unsigned int write_00376_len = 0;
      write_00376 = append_var("busy_weekend", write_00376, &write_00376_len);
      if (write_00376_len > 0) {
         transmit_all(1, write_00376, write_00376_len);
      }
      free(write_00376);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00377 = NULL;
      unsigned int write_00377_len = 0;
      write_00377 = append_var("busy_weekend", write_00377, &write_00377_len);
      if (write_00377_len > 0) {
         transmit_all(1, write_00377, write_00377_len);
      }
      free(write_00377);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00378 = NULL;
      unsigned int write_00378_len = 0;
      write_00378 = append_var("busy_weekend", write_00378, &write_00378_len);
      if (write_00378_len > 0) {
         transmit_all(1, write_00378, write_00378_len);
      }
      free(write_00378);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00379 = NULL;
      unsigned int write_00379_len = 0;
      write_00379 = append_var("busy_weekend", write_00379, &write_00379_len);
      if (write_00379_len > 0) {
         transmit_all(1, write_00379, write_00379_len);
      }
      free(write_00379);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00380 = NULL;
      unsigned int write_00380_len = 0;
      write_00380 = append_var("busy_weekend", write_00380, &write_00380_len);
      if (write_00380_len > 0) {
         transmit_all(1, write_00380, write_00380_len);
      }
      free(write_00380);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00381 = NULL;
      unsigned int write_00381_len = 0;
      write_00381 = append_var("busy_weekend", write_00381, &write_00381_len);
      if (write_00381_len > 0) {
         transmit_all(1, write_00381, write_00381_len);
      }
      free(write_00381);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00382 = NULL;
      unsigned int write_00382_len = 0;
      write_00382 = append_var("busy_weekend", write_00382, &write_00382_len);
      if (write_00382_len > 0) {
         transmit_all(1, write_00382, write_00382_len);
      }
      free(write_00382);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00383 = NULL;
      unsigned int write_00383_len = 0;
      write_00383 = append_var("busy_weekend", write_00383, &write_00383_len);
      if (write_00383_len > 0) {
         transmit_all(1, write_00383, write_00383_len);
      }
      free(write_00383);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00384 = NULL;
      unsigned int write_00384_len = 0;
      write_00384 = append_var("busy_weekend", write_00384, &write_00384_len);
      if (write_00384_len > 0) {
         transmit_all(1, write_00384, write_00384_len);
      }
      free(write_00384);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00385 = NULL;
      unsigned int write_00385_len = 0;
      write_00385 = append_var("busy_weekend", write_00385, &write_00385_len);
      if (write_00385_len > 0) {
         transmit_all(1, write_00385, write_00385_len);
      }
      free(write_00385);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00386 = NULL;
      unsigned int write_00386_len = 0;
      write_00386 = append_var("busy_weekend", write_00386, &write_00386_len);
      if (write_00386_len > 0) {
         transmit_all(1, write_00386, write_00386_len);
      }
      free(write_00386);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00387 = NULL;
      unsigned int write_00387_len = 0;
      write_00387 = append_var("busy_weekend", write_00387, &write_00387_len);
      if (write_00387_len > 0) {
         transmit_all(1, write_00387, write_00387_len);
      }
      free(write_00387);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00388 = NULL;
      unsigned int write_00388_len = 0;
      write_00388 = append_var("busy_weekend", write_00388, &write_00388_len);
      if (write_00388_len > 0) {
         transmit_all(1, write_00388, write_00388_len);
      }
      free(write_00388);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00389 = NULL;
      unsigned int write_00389_len = 0;
      write_00389 = append_var("busy_weekend", write_00389, &write_00389_len);
      if (write_00389_len > 0) {
         transmit_all(1, write_00389, write_00389_len);
      }
      free(write_00389);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00390 = NULL;
      unsigned int write_00390_len = 0;
      write_00390 = append_var("busy_weekend", write_00390, &write_00390_len);
      if (write_00390_len > 0) {
         transmit_all(1, write_00390, write_00390_len);
      }
      free(write_00390);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00391 = NULL;
      unsigned int write_00391_len = 0;
      write_00391 = append_var("busy_weekend", write_00391, &write_00391_len);
      if (write_00391_len > 0) {
         transmit_all(1, write_00391, write_00391_len);
      }
      free(write_00391);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00392 = NULL;
      unsigned int write_00392_len = 0;
      write_00392 = append_var("busy_weekend", write_00392, &write_00392_len);
      if (write_00392_len > 0) {
         transmit_all(1, write_00392, write_00392_len);
      }
      free(write_00392);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00393 = NULL;
      unsigned int write_00393_len = 0;
      write_00393 = append_var("busy_weekend", write_00393, &write_00393_len);
      if (write_00393_len > 0) {
         transmit_all(1, write_00393, write_00393_len);
      }
      free(write_00393);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00394 = NULL;
      unsigned int write_00394_len = 0;
      write_00394 = append_var("busy_weekend", write_00394, &write_00394_len);
      if (write_00394_len > 0) {
         transmit_all(1, write_00394, write_00394_len);
      }
      free(write_00394);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00395 = NULL;
      unsigned int write_00395_len = 0;
      write_00395 = append_var("busy_weekend", write_00395, &write_00395_len);
      if (write_00395_len > 0) {
         transmit_all(1, write_00395, write_00395_len);
      }
      free(write_00395);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00396 = NULL;
      unsigned int write_00396_len = 0;
      write_00396 = append_var("busy_weekend", write_00396, &write_00396_len);
      if (write_00396_len > 0) {
         transmit_all(1, write_00396, write_00396_len);
      }
      free(write_00396);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00397 = NULL;
      unsigned int write_00397_len = 0;
      write_00397 = append_var("busy_weekend", write_00397, &write_00397_len);
      if (write_00397_len > 0) {
         transmit_all(1, write_00397, write_00397_len);
      }
      free(write_00397);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00398 = NULL;
      unsigned int write_00398_len = 0;
      write_00398 = append_var("busy_weekend", write_00398, &write_00398_len);
      if (write_00398_len > 0) {
         transmit_all(1, write_00398, write_00398_len);
      }
      free(write_00398);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00399 = NULL;
      unsigned int write_00399_len = 0;
      write_00399 = append_var("busy_weekend", write_00399, &write_00399_len);
      if (write_00399_len > 0) {
         transmit_all(1, write_00399, write_00399_len);
      }
      free(write_00399);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00400 = NULL;
      unsigned int write_00400_len = 0;
      write_00400 = append_var("busy_weekend", write_00400, &write_00400_len);
      if (write_00400_len > 0) {
         transmit_all(1, write_00400, write_00400_len);
      }
      free(write_00400);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00401 = NULL;
      unsigned int write_00401_len = 0;
      write_00401 = append_var("busy_weekend", write_00401, &write_00401_len);
      if (write_00401_len > 0) {
         transmit_all(1, write_00401, write_00401_len);
      }
      free(write_00401);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00402 = NULL;
      unsigned int write_00402_len = 0;
      write_00402 = append_var("busy_weekend", write_00402, &write_00402_len);
      if (write_00402_len > 0) {
         transmit_all(1, write_00402, write_00402_len);
      }
      free(write_00402);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00403 = NULL;
      unsigned int write_00403_len = 0;
      write_00403 = append_var("busy_weekend", write_00403, &write_00403_len);
      if (write_00403_len > 0) {
         transmit_all(1, write_00403, write_00403_len);
      }
      free(write_00403);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00404 = NULL;
      unsigned int write_00404_len = 0;
      write_00404 = append_var("busy_weekend", write_00404, &write_00404_len);
      if (write_00404_len > 0) {
         transmit_all(1, write_00404, write_00404_len);
      }
      free(write_00404);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00405 = NULL;
      unsigned int write_00405_len = 0;
      write_00405 = append_var("busy_weekend", write_00405, &write_00405_len);
      if (write_00405_len > 0) {
         transmit_all(1, write_00405, write_00405_len);
      }
      free(write_00405);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00406 = NULL;
      unsigned int write_00406_len = 0;
      write_00406 = append_var("busy_weekend", write_00406, &write_00406_len);
      if (write_00406_len > 0) {
         transmit_all(1, write_00406, write_00406_len);
      }
      free(write_00406);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00407 = NULL;
      unsigned int write_00407_len = 0;
      write_00407 = append_var("busy_weekend", write_00407, &write_00407_len);
      if (write_00407_len > 0) {
         transmit_all(1, write_00407, write_00407_len);
      }
      free(write_00407);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00408 = NULL;
      unsigned int write_00408_len = 0;
      write_00408 = append_var("busy_weekend", write_00408, &write_00408_len);
      if (write_00408_len > 0) {
         transmit_all(1, write_00408, write_00408_len);
      }
      free(write_00408);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00409 = NULL;
      unsigned int write_00409_len = 0;
      write_00409 = append_var("busy_weekend", write_00409, &write_00409_len);
      if (write_00409_len > 0) {
         transmit_all(1, write_00409, write_00409_len);
      }
      free(write_00409);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00410 = NULL;
      unsigned int write_00410_len = 0;
      write_00410 = append_var("busy_weekend", write_00410, &write_00410_len);
      if (write_00410_len > 0) {
         transmit_all(1, write_00410, write_00410_len);
      }
      free(write_00410);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00411 = NULL;
      unsigned int write_00411_len = 0;
      write_00411 = append_var("busy_weekend", write_00411, &write_00411_len);
      if (write_00411_len > 0) {
         transmit_all(1, write_00411, write_00411_len);
      }
      free(write_00411);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00412 = NULL;
      unsigned int write_00412_len = 0;
      write_00412 = append_var("busy_weekend", write_00412, &write_00412_len);
      if (write_00412_len > 0) {
         transmit_all(1, write_00412, write_00412_len);
      }
      free(write_00412);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00413 = NULL;
      unsigned int write_00413_len = 0;
      write_00413 = append_var("busy_weekend", write_00413, &write_00413_len);
      if (write_00413_len > 0) {
         transmit_all(1, write_00413, write_00413_len);
      }
      free(write_00413);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00414 = NULL;
      unsigned int write_00414_len = 0;
      write_00414 = append_var("busy_weekend", write_00414, &write_00414_len);
      if (write_00414_len > 0) {
         transmit_all(1, write_00414, write_00414_len);
      }
      free(write_00414);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00415 = NULL;
      unsigned int write_00415_len = 0;
      write_00415 = append_var("busy_weekend", write_00415, &write_00415_len);
      if (write_00415_len > 0) {
         transmit_all(1, write_00415, write_00415_len);
      }
      free(write_00415);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00416 = NULL;
      unsigned int write_00416_len = 0;
      write_00416 = append_var("busy_weekend", write_00416, &write_00416_len);
      if (write_00416_len > 0) {
         transmit_all(1, write_00416, write_00416_len);
      }
      free(write_00416);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00417 = NULL;
      unsigned int write_00417_len = 0;
      write_00417 = append_var("busy_weekend", write_00417, &write_00417_len);
      if (write_00417_len > 0) {
         transmit_all(1, write_00417, write_00417_len);
      }
      free(write_00417);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00418 = NULL;
      unsigned int write_00418_len = 0;
      write_00418 = append_var("busy_weekend", write_00418, &write_00418_len);
      if (write_00418_len > 0) {
         transmit_all(1, write_00418, write_00418_len);
      }
      free(write_00418);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00419 = NULL;
      unsigned int write_00419_len = 0;
      write_00419 = append_var("busy_weekend", write_00419, &write_00419_len);
      if (write_00419_len > 0) {
         transmit_all(1, write_00419, write_00419_len);
      }
      free(write_00419);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00420 = NULL;
      unsigned int write_00420_len = 0;
      write_00420 = append_var("busy_weekend", write_00420, &write_00420_len);
      if (write_00420_len > 0) {
         transmit_all(1, write_00420, write_00420_len);
      }
      free(write_00420);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00421 = NULL;
      unsigned int write_00421_len = 0;
      write_00421 = append_var("busy_weekend", write_00421, &write_00421_len);
      if (write_00421_len > 0) {
         transmit_all(1, write_00421, write_00421_len);
      }
      free(write_00421);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00422 = NULL;
      unsigned int write_00422_len = 0;
      write_00422 = append_var("busy_weekend", write_00422, &write_00422_len);
      if (write_00422_len > 0) {
         transmit_all(1, write_00422, write_00422_len);
      }
      free(write_00422);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00423 = NULL;
      unsigned int write_00423_len = 0;
      write_00423 = append_var("busy_weekend", write_00423, &write_00423_len);
      if (write_00423_len > 0) {
         transmit_all(1, write_00423, write_00423_len);
      }
      free(write_00423);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00424 = NULL;
      unsigned int write_00424_len = 0;
      write_00424 = append_var("busy_weekend", write_00424, &write_00424_len);
      if (write_00424_len > 0) {
         transmit_all(1, write_00424, write_00424_len);
      }
      free(write_00424);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00425 = NULL;
      unsigned int write_00425_len = 0;
      write_00425 = append_var("busy_weekend", write_00425, &write_00425_len);
      if (write_00425_len > 0) {
         transmit_all(1, write_00425, write_00425_len);
      }
      free(write_00425);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00426 = NULL;
      unsigned int write_00426_len = 0;
      write_00426 = append_var("busy_weekend", write_00426, &write_00426_len);
      if (write_00426_len > 0) {
         transmit_all(1, write_00426, write_00426_len);
      }
      free(write_00426);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00427 = NULL;
      unsigned int write_00427_len = 0;
      write_00427 = append_var("busy_weekend", write_00427, &write_00427_len);
      if (write_00427_len > 0) {
         transmit_all(1, write_00427, write_00427_len);
      }
      free(write_00427);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00428 = NULL;
      unsigned int write_00428_len = 0;
      write_00428 = append_var("busy_weekend", write_00428, &write_00428_len);
      if (write_00428_len > 0) {
         transmit_all(1, write_00428, write_00428_len);
      }
      free(write_00428);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00429 = NULL;
      unsigned int write_00429_len = 0;
      write_00429 = append_var("busy_weekend", write_00429, &write_00429_len);
      if (write_00429_len > 0) {
         transmit_all(1, write_00429, write_00429_len);
      }
      free(write_00429);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00430 = NULL;
      unsigned int write_00430_len = 0;
      write_00430 = append_var("busy_weekend", write_00430, &write_00430_len);
      if (write_00430_len > 0) {
         transmit_all(1, write_00430, write_00430_len);
      }
      free(write_00430);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00431 = NULL;
      unsigned int write_00431_len = 0;
      write_00431 = append_var("busy_weekend", write_00431, &write_00431_len);
      if (write_00431_len > 0) {
         transmit_all(1, write_00431, write_00431_len);
      }
      free(write_00431);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00432 = NULL;
      unsigned int write_00432_len = 0;
      write_00432 = append_var("busy_weekend", write_00432, &write_00432_len);
      if (write_00432_len > 0) {
         transmit_all(1, write_00432, write_00432_len);
      }
      free(write_00432);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00433 = NULL;
      unsigned int write_00433_len = 0;
      write_00433 = append_var("busy_weekend", write_00433, &write_00433_len);
      if (write_00433_len > 0) {
         transmit_all(1, write_00433, write_00433_len);
      }
      free(write_00433);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00434 = NULL;
      unsigned int write_00434_len = 0;
      write_00434 = append_var("busy_weekend", write_00434, &write_00434_len);
      if (write_00434_len > 0) {
         transmit_all(1, write_00434, write_00434_len);
      }
      free(write_00434);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00435 = NULL;
      unsigned int write_00435_len = 0;
      write_00435 = append_var("busy_weekend", write_00435, &write_00435_len);
      if (write_00435_len > 0) {
         transmit_all(1, write_00435, write_00435_len);
      }
      free(write_00435);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00436 = NULL;
      unsigned int write_00436_len = 0;
      write_00436 = append_var("busy_weekend", write_00436, &write_00436_len);
      if (write_00436_len > 0) {
         transmit_all(1, write_00436, write_00436_len);
      }
      free(write_00436);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00437 = NULL;
      unsigned int write_00437_len = 0;
      write_00437 = append_var("busy_weekend", write_00437, &write_00437_len);
      if (write_00437_len > 0) {
         transmit_all(1, write_00437, write_00437_len);
      }
      free(write_00437);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00438 = NULL;
      unsigned int write_00438_len = 0;
      write_00438 = append_var("busy_weekend", write_00438, &write_00438_len);
      if (write_00438_len > 0) {
         transmit_all(1, write_00438, write_00438_len);
      }
      free(write_00438);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00439 = NULL;
      unsigned int write_00439_len = 0;
      write_00439 = append_var("busy_weekend", write_00439, &write_00439_len);
      if (write_00439_len > 0) {
         transmit_all(1, write_00439, write_00439_len);
      }
      free(write_00439);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00440 = NULL;
      unsigned int write_00440_len = 0;
      write_00440 = append_var("busy_weekend", write_00440, &write_00440_len);
      if (write_00440_len > 0) {
         transmit_all(1, write_00440, write_00440_len);
      }
      free(write_00440);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00441 = NULL;
      unsigned int write_00441_len = 0;
      write_00441 = append_var("busy_weekend", write_00441, &write_00441_len);
      if (write_00441_len > 0) {
         transmit_all(1, write_00441, write_00441_len);
      }
      free(write_00441);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00442 = NULL;
      unsigned int write_00442_len = 0;
      write_00442 = append_var("busy_weekend", write_00442, &write_00442_len);
      if (write_00442_len > 0) {
         transmit_all(1, write_00442, write_00442_len);
      }
      free(write_00442);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00443 = NULL;
      unsigned int write_00443_len = 0;
      write_00443 = append_var("busy_weekend", write_00443, &write_00443_len);
      if (write_00443_len > 0) {
         transmit_all(1, write_00443, write_00443_len);
      }
      free(write_00443);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00444 = NULL;
      unsigned int write_00444_len = 0;
      write_00444 = append_var("busy_weekend", write_00444, &write_00444_len);
      if (write_00444_len > 0) {
         transmit_all(1, write_00444, write_00444_len);
      }
      free(write_00444);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00445 = NULL;
      unsigned int write_00445_len = 0;
      write_00445 = append_var("busy_weekend", write_00445, &write_00445_len);
      if (write_00445_len > 0) {
         transmit_all(1, write_00445, write_00445_len);
      }
      free(write_00445);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00446 = NULL;
      unsigned int write_00446_len = 0;
      write_00446 = append_var("busy_weekend", write_00446, &write_00446_len);
      if (write_00446_len > 0) {
         transmit_all(1, write_00446, write_00446_len);
      }
      free(write_00446);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00447 = NULL;
      unsigned int write_00447_len = 0;
      write_00447 = append_var("busy_weekend", write_00447, &write_00447_len);
      if (write_00447_len > 0) {
         transmit_all(1, write_00447, write_00447_len);
      }
      free(write_00447);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00448 = NULL;
      unsigned int write_00448_len = 0;
      write_00448 = append_var("busy_weekend", write_00448, &write_00448_len);
      if (write_00448_len > 0) {
         transmit_all(1, write_00448, write_00448_len);
      }
      free(write_00448);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00449 = NULL;
      unsigned int write_00449_len = 0;
      write_00449 = append_var("busy_weekend", write_00449, &write_00449_len);
      if (write_00449_len > 0) {
         transmit_all(1, write_00449, write_00449_len);
      }
      free(write_00449);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00450 = NULL;
      unsigned int write_00450_len = 0;
      write_00450 = append_var("busy_weekend", write_00450, &write_00450_len);
      if (write_00450_len > 0) {
         transmit_all(1, write_00450, write_00450_len);
      }
      free(write_00450);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00451 = NULL;
      unsigned int write_00451_len = 0;
      write_00451 = append_var("busy_weekend", write_00451, &write_00451_len);
      if (write_00451_len > 0) {
         transmit_all(1, write_00451, write_00451_len);
      }
      free(write_00451);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00452 = NULL;
      unsigned int write_00452_len = 0;
      write_00452 = append_var("busy_weekend", write_00452, &write_00452_len);
      if (write_00452_len > 0) {
         transmit_all(1, write_00452, write_00452_len);
      }
      free(write_00452);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00453 = NULL;
      unsigned int write_00453_len = 0;
      write_00453 = append_var("busy_weekend", write_00453, &write_00453_len);
      if (write_00453_len > 0) {
         transmit_all(1, write_00453, write_00453_len);
      }
      free(write_00453);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00454 = NULL;
      unsigned int write_00454_len = 0;
      write_00454 = append_var("busy_weekend", write_00454, &write_00454_len);
      if (write_00454_len > 0) {
         transmit_all(1, write_00454, write_00454_len);
      }
      free(write_00454);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00455 = NULL;
      unsigned int write_00455_len = 0;
      write_00455 = append_var("busy_weekend", write_00455, &write_00455_len);
      if (write_00455_len > 0) {
         transmit_all(1, write_00455, write_00455_len);
      }
      free(write_00455);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00456 = NULL;
      unsigned int write_00456_len = 0;
      write_00456 = append_var("busy_weekend", write_00456, &write_00456_len);
      if (write_00456_len > 0) {
         transmit_all(1, write_00456, write_00456_len);
      }
      free(write_00456);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00457 = NULL;
      unsigned int write_00457_len = 0;
      write_00457 = append_var("busy_weekend", write_00457, &write_00457_len);
      if (write_00457_len > 0) {
         transmit_all(1, write_00457, write_00457_len);
      }
      free(write_00457);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00458 = NULL;
      unsigned int write_00458_len = 0;
      write_00458 = append_var("busy_weekend", write_00458, &write_00458_len);
      if (write_00458_len > 0) {
         transmit_all(1, write_00458, write_00458_len);
      }
      free(write_00458);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00459 = NULL;
      unsigned int write_00459_len = 0;
      write_00459 = append_var("busy_weekend", write_00459, &write_00459_len);
      if (write_00459_len > 0) {
         transmit_all(1, write_00459, write_00459_len);
      }
      free(write_00459);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00460 = NULL;
      unsigned int write_00460_len = 0;
      write_00460 = append_var("busy_weekend", write_00460, &write_00460_len);
      if (write_00460_len > 0) {
         transmit_all(1, write_00460, write_00460_len);
      }
      free(write_00460);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00461 = NULL;
      unsigned int write_00461_len = 0;
      write_00461 = append_var("busy_weekend", write_00461, &write_00461_len);
      if (write_00461_len > 0) {
         transmit_all(1, write_00461, write_00461_len);
      }
      free(write_00461);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00462 = NULL;
      unsigned int write_00462_len = 0;
      write_00462 = append_var("busy_weekend", write_00462, &write_00462_len);
      if (write_00462_len > 0) {
         transmit_all(1, write_00462, write_00462_len);
      }
      free(write_00462);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00463 = NULL;
      unsigned int write_00463_len = 0;
      write_00463 = append_var("busy_weekend", write_00463, &write_00463_len);
      if (write_00463_len > 0) {
         transmit_all(1, write_00463, write_00463_len);
      }
      free(write_00463);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00464 = NULL;
      unsigned int write_00464_len = 0;
      write_00464 = append_var("busy_weekend", write_00464, &write_00464_len);
      if (write_00464_len > 0) {
         transmit_all(1, write_00464, write_00464_len);
      }
      free(write_00464);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00465 = NULL;
      unsigned int write_00465_len = 0;
      write_00465 = append_var("busy_weekend", write_00465, &write_00465_len);
      if (write_00465_len > 0) {
         transmit_all(1, write_00465, write_00465_len);
      }
      free(write_00465);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00466 = NULL;
      unsigned int write_00466_len = 0;
      write_00466 = append_var("busy_weekend", write_00466, &write_00466_len);
      if (write_00466_len > 0) {
         transmit_all(1, write_00466, write_00466_len);
      }
      free(write_00466);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00467 = NULL;
      unsigned int write_00467_len = 0;
      write_00467 = append_var("busy_weekend", write_00467, &write_00467_len);
      if (write_00467_len > 0) {
         transmit_all(1, write_00467, write_00467_len);
      }
      free(write_00467);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00468 = NULL;
      unsigned int write_00468_len = 0;
      write_00468 = append_var("busy_weekend", write_00468, &write_00468_len);
      if (write_00468_len > 0) {
         transmit_all(1, write_00468, write_00468_len);
      }
      free(write_00468);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00469 = NULL;
      unsigned int write_00469_len = 0;
      write_00469 = append_var("busy_weekend", write_00469, &write_00469_len);
      if (write_00469_len > 0) {
         transmit_all(1, write_00469, write_00469_len);
      }
      free(write_00469);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00470 = NULL;
      unsigned int write_00470_len = 0;
      write_00470 = append_var("busy_weekend", write_00470, &write_00470_len);
      if (write_00470_len > 0) {
         transmit_all(1, write_00470, write_00470_len);
      }
      free(write_00470);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00471 = NULL;
      unsigned int write_00471_len = 0;
      write_00471 = append_var("busy_weekend", write_00471, &write_00471_len);
      if (write_00471_len > 0) {
         transmit_all(1, write_00471, write_00471_len);
      }
      free(write_00471);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00472 = NULL;
      unsigned int write_00472_len = 0;
      write_00472 = append_var("busy_weekend", write_00472, &write_00472_len);
      if (write_00472_len > 0) {
         transmit_all(1, write_00472, write_00472_len);
      }
      free(write_00472);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00473 = NULL;
      unsigned int write_00473_len = 0;
      write_00473 = append_var("busy_weekend", write_00473, &write_00473_len);
      if (write_00473_len > 0) {
         transmit_all(1, write_00473, write_00473_len);
      }
      free(write_00473);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00474 = NULL;
      unsigned int write_00474_len = 0;
      write_00474 = append_var("busy_weekend", write_00474, &write_00474_len);
      if (write_00474_len > 0) {
         transmit_all(1, write_00474, write_00474_len);
      }
      free(write_00474);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00475 = NULL;
      unsigned int write_00475_len = 0;
      write_00475 = append_var("busy_weekend", write_00475, &write_00475_len);
      if (write_00475_len > 0) {
         transmit_all(1, write_00475, write_00475_len);
      }
      free(write_00475);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00476 = NULL;
      unsigned int write_00476_len = 0;
      write_00476 = append_var("busy_weekend", write_00476, &write_00476_len);
      if (write_00476_len > 0) {
         transmit_all(1, write_00476, write_00476_len);
      }
      free(write_00476);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00477 = NULL;
      unsigned int write_00477_len = 0;
      write_00477 = append_var("busy_weekend", write_00477, &write_00477_len);
      if (write_00477_len > 0) {
         transmit_all(1, write_00477, write_00477_len);
      }
      free(write_00477);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00478 = NULL;
      unsigned int write_00478_len = 0;
      write_00478 = append_var("busy_weekend", write_00478, &write_00478_len);
      if (write_00478_len > 0) {
         transmit_all(1, write_00478, write_00478_len);
      }
      free(write_00478);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00479 = NULL;
      unsigned int write_00479_len = 0;
      write_00479 = append_var("busy_weekend", write_00479, &write_00479_len);
      if (write_00479_len > 0) {
         transmit_all(1, write_00479, write_00479_len);
      }
      free(write_00479);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00480 = NULL;
      unsigned int write_00480_len = 0;
      write_00480 = append_var("busy_weekend", write_00480, &write_00480_len);
      if (write_00480_len > 0) {
         transmit_all(1, write_00480, write_00480_len);
      }
      free(write_00480);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00481 = NULL;
      unsigned int write_00481_len = 0;
      write_00481 = append_var("busy_weekend", write_00481, &write_00481_len);
      if (write_00481_len > 0) {
         transmit_all(1, write_00481, write_00481_len);
      }
      free(write_00481);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00482 = NULL;
      unsigned int write_00482_len = 0;
      write_00482 = append_var("busy_weekend", write_00482, &write_00482_len);
      if (write_00482_len > 0) {
         transmit_all(1, write_00482, write_00482_len);
      }
      free(write_00482);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00483 = NULL;
      unsigned int write_00483_len = 0;
      write_00483 = append_var("busy_weekend", write_00483, &write_00483_len);
      if (write_00483_len > 0) {
         transmit_all(1, write_00483, write_00483_len);
      }
      free(write_00483);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00484 = NULL;
      unsigned int write_00484_len = 0;
      write_00484 = append_var("busy_weekend", write_00484, &write_00484_len);
      if (write_00484_len > 0) {
         transmit_all(1, write_00484, write_00484_len);
      }
      free(write_00484);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00485 = NULL;
      unsigned int write_00485_len = 0;
      write_00485 = append_var("busy_weekend", write_00485, &write_00485_len);
      if (write_00485_len > 0) {
         transmit_all(1, write_00485, write_00485_len);
      }
      free(write_00485);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00486 = NULL;
      unsigned int write_00486_len = 0;
      write_00486 = append_var("busy_weekend", write_00486, &write_00486_len);
      if (write_00486_len > 0) {
         transmit_all(1, write_00486, write_00486_len);
      }
      free(write_00486);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00487 = NULL;
      unsigned int write_00487_len = 0;
      write_00487 = append_var("busy_weekend", write_00487, &write_00487_len);
      if (write_00487_len > 0) {
         transmit_all(1, write_00487, write_00487_len);
      }
      free(write_00487);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00488 = NULL;
      unsigned int write_00488_len = 0;
      write_00488 = append_var("busy_weekend", write_00488, &write_00488_len);
      if (write_00488_len > 0) {
         transmit_all(1, write_00488, write_00488_len);
      }
      free(write_00488);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00489 = NULL;
      unsigned int write_00489_len = 0;
      write_00489 = append_var("busy_weekend", write_00489, &write_00489_len);
      if (write_00489_len > 0) {
         transmit_all(1, write_00489, write_00489_len);
      }
      free(write_00489);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00490 = NULL;
      unsigned int write_00490_len = 0;
      write_00490 = append_var("busy_weekend", write_00490, &write_00490_len);
      if (write_00490_len > 0) {
         transmit_all(1, write_00490, write_00490_len);
      }
      free(write_00490);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00491 = NULL;
      unsigned int write_00491_len = 0;
      write_00491 = append_var("busy_weekend", write_00491, &write_00491_len);
      if (write_00491_len > 0) {
         transmit_all(1, write_00491, write_00491_len);
      }
      free(write_00491);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00492 = NULL;
      unsigned int write_00492_len = 0;
      write_00492 = append_var("busy_weekend", write_00492, &write_00492_len);
      if (write_00492_len > 0) {
         transmit_all(1, write_00492, write_00492_len);
      }
      free(write_00492);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00493 = NULL;
      unsigned int write_00493_len = 0;
      write_00493 = append_var("busy_weekend", write_00493, &write_00493_len);
      if (write_00493_len > 0) {
         transmit_all(1, write_00493, write_00493_len);
      }
      free(write_00493);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00494 = NULL;
      unsigned int write_00494_len = 0;
      write_00494 = append_var("busy_weekend", write_00494, &write_00494_len);
      if (write_00494_len > 0) {
         transmit_all(1, write_00494, write_00494_len);
      }
      free(write_00494);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00495 = NULL;
      unsigned int write_00495_len = 0;
      write_00495 = append_var("busy_weekend", write_00495, &write_00495_len);
      if (write_00495_len > 0) {
         transmit_all(1, write_00495, write_00495_len);
      }
      free(write_00495);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00496 = NULL;
      unsigned int write_00496_len = 0;
      write_00496 = append_var("busy_weekend", write_00496, &write_00496_len);
      if (write_00496_len > 0) {
         transmit_all(1, write_00496, write_00496_len);
      }
      free(write_00496);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00497 = NULL;
      unsigned int write_00497_len = 0;
      write_00497 = append_var("busy_weekend", write_00497, &write_00497_len);
      if (write_00497_len > 0) {
         transmit_all(1, write_00497, write_00497_len);
      }
      free(write_00497);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00498 = NULL;
      unsigned int write_00498_len = 0;
      write_00498 = append_var("busy_weekend", write_00498, &write_00498_len);
      if (write_00498_len > 0) {
         transmit_all(1, write_00498, write_00498_len);
      }
      free(write_00498);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00499 = NULL;
      unsigned int write_00499_len = 0;
      write_00499 = append_var("busy_weekend", write_00499, &write_00499_len);
      if (write_00499_len > 0) {
         transmit_all(1, write_00499, write_00499_len);
      }
      free(write_00499);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00500 = NULL;
      unsigned int write_00500_len = 0;
      write_00500 = append_var("busy_weekend", write_00500, &write_00500_len);
      if (write_00500_len > 0) {
         transmit_all(1, write_00500, write_00500_len);
      }
      free(write_00500);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00501 = NULL;
      unsigned int write_00501_len = 0;
      write_00501 = append_var("busy_weekend", write_00501, &write_00501_len);
      if (write_00501_len > 0) {
         transmit_all(1, write_00501, write_00501_len);
      }
      free(write_00501);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00502 = NULL;
      unsigned int write_00502_len = 0;
      write_00502 = append_var("busy_weekend", write_00502, &write_00502_len);
      if (write_00502_len > 0) {
         transmit_all(1, write_00502, write_00502_len);
      }
      free(write_00502);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00503 = NULL;
      unsigned int write_00503_len = 0;
      write_00503 = append_var("busy_weekend", write_00503, &write_00503_len);
      if (write_00503_len > 0) {
         transmit_all(1, write_00503, write_00503_len);
      }
      free(write_00503);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00504 = NULL;
      unsigned int write_00504_len = 0;
      write_00504 = append_var("busy_weekend", write_00504, &write_00504_len);
      if (write_00504_len > 0) {
         transmit_all(1, write_00504, write_00504_len);
      }
      free(write_00504);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00505 = NULL;
      unsigned int write_00505_len = 0;
      write_00505 = append_var("busy_weekend", write_00505, &write_00505_len);
      if (write_00505_len > 0) {
         transmit_all(1, write_00505, write_00505_len);
      }
      free(write_00505);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00506 = NULL;
      unsigned int write_00506_len = 0;
      write_00506 = append_var("busy_weekend", write_00506, &write_00506_len);
      if (write_00506_len > 0) {
         transmit_all(1, write_00506, write_00506_len);
      }
      free(write_00506);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00507 = NULL;
      unsigned int write_00507_len = 0;
      write_00507 = append_var("busy_weekend", write_00507, &write_00507_len);
      if (write_00507_len > 0) {
         transmit_all(1, write_00507, write_00507_len);
      }
      free(write_00507);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00508 = NULL;
      unsigned int write_00508_len = 0;
      write_00508 = append_var("busy_weekend", write_00508, &write_00508_len);
      if (write_00508_len > 0) {
         transmit_all(1, write_00508, write_00508_len);
      }
      free(write_00508);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00509 = NULL;
      unsigned int write_00509_len = 0;
      write_00509 = append_var("busy_weekend", write_00509, &write_00509_len);
      if (write_00509_len > 0) {
         transmit_all(1, write_00509, write_00509_len);
      }
      free(write_00509);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00510 = NULL;
      unsigned int write_00510_len = 0;
      write_00510 = append_var("busy_weekend", write_00510, &write_00510_len);
      if (write_00510_len > 0) {
         transmit_all(1, write_00510, write_00510_len);
      }
      free(write_00510);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00511 = NULL;
      unsigned int write_00511_len = 0;
      write_00511 = append_var("busy_weekend", write_00511, &write_00511_len);
      if (write_00511_len > 0) {
         transmit_all(1, write_00511, write_00511_len);
      }
      free(write_00511);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00512 = NULL;
      unsigned int write_00512_len = 0;
      write_00512 = append_var("busy_weekend", write_00512, &write_00512_len);
      if (write_00512_len > 0) {
         transmit_all(1, write_00512, write_00512_len);
      }
      free(write_00512);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00513 = NULL;
      unsigned int write_00513_len = 0;
      write_00513 = append_var("busy_weekend", write_00513, &write_00513_len);
      if (write_00513_len > 0) {
         transmit_all(1, write_00513, write_00513_len);
      }
      free(write_00513);
   } while (0);
   do {
      //*** writing data
      unsigned char *write_00514 = NULL;
      unsigned int write_00514_len = 0;
      write_00514 = append_var("busy_weekend", write_00514, &write_00514_len);
      if (write_00514_len > 0) {
         transmit_all(1, write_00514, write_00514_len);
      }
      free(write_00514);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00515_00000[] = 
         "\x0a";
      static unsigned int write_00515_00000_len = 1;
      unsigned char *write_00515 = NULL;
      unsigned int write_00515_len = 0;
      write_00515 = append_buf(write_00515, &write_00515_len, write_00515_00000, write_00515_00000_len);
      if (write_00515_len > 0) {
         transmit_all(1, write_00515, write_00515_len);
      }
      free(write_00515);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00516_00000[] = 
         "\x71\x75\x65\x72\x79\x2d\x77\x65\x65\x6b\x60\x65\x6d\x70\x6c\x6f"
         "\x79\x65\x65\x5f\x69\x64\x2d\x34\x39\x60\x77\x65\x65\x6b\x2d\x32"
         "\x33\x60\x0a";
      static unsigned int write_00516_00000_len = 35;
      unsigned char *write_00516 = NULL;
      unsigned int write_00516_len = 0;
      write_00516 = append_buf(write_00516, &write_00516_len, write_00516_00000, write_00516_00000_len);
      if (write_00516_len > 0) {
         transmit_all(1, write_00516, write_00516_len);
      }
      free(write_00516);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00517_00000[] = 
         "\x65\x6d\x70\x6c\x6f\x79\x65\x65\x5f\x69\x64\x2d\x34\x39\x60\x77"
         "\x65\x65\x6b\x2d\x32\x33\x60\x66\x72\x69\x64\x61\x79\x2d\x32\x68"
         "\x30\x6d\x60\x0a";
      static unsigned int write_00517_00000_len = 36;
      unsigned char *write_00517 = NULL;
      unsigned int write_00517_len = 0;
      write_00517 = append_buf(write_00517, &write_00517_len, write_00517_00000, write_00517_00000_len);
      if (write_00517_len > 0) {
         transmit_all(1, write_00517, write_00517_len);
      }
      free(write_00517);
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
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
}
