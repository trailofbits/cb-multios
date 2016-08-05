#include <libpov.h>

void RegisterUser(uint16_t user_id)
{

   //*** writing REGISTER USER
   unsigned char write_00001_00000[] = 
      "\xc3\x3c\x02\x00\x09\x00\x02\xd1\x70\x01\x8f\x96\x02\x75\x48";
   *(uint16_t *)(write_00001_00000 + 7) = user_id;
   static unsigned int write_00001_00000_len = 15;
   unsigned char *write_00001 = NULL;
   unsigned int write_00001_len = 0;
   write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
   if (write_00001_len > 0) {
      transmit_all(1, write_00001, write_00001_len);
   }
   free(write_00001);

   unsigned char *read_00001;
   unsigned int read_00001_len;
   unsigned int read_00001_ptr = 0;
   //**** length read
   read_00001_len = 9;
   read_00001 = (unsigned char*)malloc(read_00001_len);
   int read_00001_res = length_read(0, read_00001, read_00001_len);
   if (read_00001_res) {} //silence unused variable warning
   //**** read match data
   static unsigned char match_00001_00000[] = 
      "\xc3\x3c\x33\x00\x03\x00\x02\x00\x00";
   read_00001_ptr += data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 9);
   free(read_00001);
   if (read_00001_ptr) {}  //silence unused variable warning if any
}

void ChangeUser(uint16_t user_id)
{
   static unsigned char write_00002_00000[] = 
      "\xc3\x3c\x03\x00\x02\x00\xd1\x70";
   *(uint16_t *)&write_00002_00000[6] = user_id;
   static unsigned int write_00002_00000_len = 8;
   unsigned char *write_00002 = NULL;
   unsigned int write_00002_len = 0;
   write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
   if (write_00002_len > 0) {
      transmit_all(1, write_00002, write_00002_len);
   }
   free(write_00002);
  
   unsigned char *read_00002;
   unsigned int read_00002_len;
   unsigned int read_00002_ptr = 0;
   //**** length read
   read_00002_len = 9;
   read_00002 = (unsigned char*)malloc(read_00002_len);
   int read_00002_res = length_read(0, read_00002, read_00002_len);
   if (read_00002_res) {} //silence unused variable warning
   //**** read match data
   static unsigned char match_00002_00000[] = 
      "\xc3\x3c\x33\x00\x03\x00\x03\x00\x00";
   read_00002_ptr += data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 9);
   free(read_00002);
   if (read_00002_ptr) {}  //silence unused variable warning if any

}
void RegisterSensor(uint16_t sensor_id, uint8_t sensor_mac)
{

   static unsigned char write_00003_00000[] = 
      "\xc3\x3c\x01\x00\x06\x00\x2d\x9f\xa2\xea\xda\x2f";
   *(uint16_t *)&write_00003_00000[6] = sensor_id;
   write_00003_00000[11] = sensor_mac;
   static unsigned int write_00003_00000_len = 12;
   unsigned char *write_00003 = NULL;
   unsigned int write_00003_len = 0;
   write_00003 = append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
   if (write_00003_len > 0) {
      transmit_all(1, write_00003, write_00003_len);
   }
   free(write_00003);
  
   unsigned char *read_00003;
   unsigned int read_00003_len;
   unsigned int read_00003_ptr = 0;
   //**** length read
   read_00003_len = 9;
   read_00003 = (unsigned char*)malloc(read_00003_len);
   int read_00003_res = length_read(0, read_00003, read_00003_len);
   if (read_00003_res) {} //silence unused variable warning
   //**** read match data
   static unsigned char match_00003_00000[] = 
      "\xc3\x3c\x33\x00\x03\x00\x01\x00\x00";
   read_00003_ptr += data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 9);
   free(read_00003);
   if (read_00003_ptr) {}  //silence unused variable warning if any
}

int main(void) {
   // negotiate
   type1_vals t1vals;
   type1_negotiate(0xeeeeeeee, 0xeeeeeeee, 7, &t1vals);
  
   char magicBytes[5];
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\xc3\x3c\x33\x00\x01\x00\x00";
      static unsigned int write_00000_00000_len = 7;
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
      read_00000_len = 11;
      read_00000 = (unsigned char*)malloc(read_00000_len);
      int read_00000_res = length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      memcpy(magicBytes, read_00000 + 6, 5);
      //**** read match data
      static unsigned char match_00000_00000[] = 
         "\xc3\x3c\x44\x77\x05\x00";
      free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   int sensor_num = 0;
   for (int i=0; i< 7; i++)
   {
      RegisterUser(i);
      ChangeUser(i);
      for (int j=0; j<3; j++)
      {
         if ((i == 6) && (j == 2)) break;
         RegisterSensor(sensor_num++, magicBytes[j]);
      }
   }
   do {
      //*** writing data
      static unsigned char write_00035_00000[] = 
         "\xc3\x3c\x01\x00\x26\x00\xd3\xde\xbf\xc1\x06\xf2\xff\xff\xff\xf0"
         "\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f\x50\x51\x52\x53\x54"
         "\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f\x60";
      write_00035_00000[11] = magicBytes[4];
      static unsigned int write_00035_00000_len = 44;
      *(uint32_t *)&write_00035_00000[28] = t1vals.regval | 0x11111111;
      *(uint32_t *)&write_00035_00000[40] = t1vals.ipval | 0x11111111;
      
      unsigned char *write_00035 = NULL;
      unsigned int write_00035_len = 0;
      write_00035 = append_buf(write_00035, &write_00035_len, write_00035_00000, write_00035_00000_len);
      if (write_00035_len > 0) {
         transmit_all(1, write_00035, write_00035_len);
      }
      free(write_00035);
   } while (0);
   do {
      unsigned char *read_00035;
      unsigned int read_00035_len;
      unsigned int read_00035_ptr = 0;
      //**** length read
      read_00035_len = 9;
      read_00035 = (unsigned char*)malloc(read_00035_len);
      int read_00035_res = length_read(0, read_00035, read_00035_len);
      if (read_00035_res) {} //silence unused variable warning
      //**** read match data
      static unsigned char match_00035_00000[] = 
         "\xc3\x3c\x33\x00\x03\x00\x01\x00\x00";
      read_00035_ptr += data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 9);
      free(read_00035);
      if (read_00035_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00037_00000[] = 
         "\xc3\x3c\x0b\x00\x01\x00\x00";
      static unsigned int write_00037_00000_len = 7;
      unsigned char *write_00037 = NULL;
      unsigned int write_00037_len = 0;
      write_00037 = append_buf(write_00037, &write_00037_len, write_00037_00000, write_00037_00000_len);
      if (write_00037_len > 0) {
         transmit_all(1, write_00037, write_00037_len);
      }
      free(write_00037);
   } while (0);
   do {
      unsigned char *read_00037;
      unsigned int read_00037_len;
      unsigned int read_00037_ptr = 0;
      //**** length read
      read_00037_len = 1;
      read_00037 = (unsigned char*)malloc(read_00037_len);
      int read_00037_res = length_read(0, read_00037, read_00037_len);
      free(read_00037);
      if (read_00037_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00038_00000[] = 
         "\xc3\x3c\xff\x00\x01\x00\x00";
      static unsigned int write_00038_00000_len = 7;
      unsigned char *write_00038 = NULL;
      unsigned int write_00038_len = 0;
      write_00038 = append_buf(write_00038, &write_00038_len, write_00038_00000, write_00038_00000_len);
      if (write_00038_len > 0) {
         transmit_all(1, write_00038, write_00038_len);
      }
      free(write_00038);
   } while (0);
}
