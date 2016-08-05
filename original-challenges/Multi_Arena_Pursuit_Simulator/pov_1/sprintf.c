/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "cbstring.h"
#include "cbstdio.h"

static char* digits = "0123456789ABCDEF";
/*F*************************/

int
b16_2w(buf, num)

char *buf;				/* buffer to hold the hex string */
unsigned int num;		/* the 1-byte value to convert */
/*
* PURPOSE : Convert a 1-byte value into a 4 character string and store it in a buffer
*
* RETURN : The length of the number string
*
*F*/
{
	char tmp[2];
	bzero(tmp, 0);

	if (num > 0xff) {
		buf[0] = '|';
		buf[1] = 'B';
		buf[2] = 'A';
		buf[3] = 'D';
		buf[4] = '|';

		return 5;
	}

	buf[0] = '0';
	buf[1] = 'x';

	if (num == 0) {
		buf[2] = '0';
		buf[3] = '0';
		return 4;
	} else {
		buf[3] = digits[num % 16];
		num = num / 16;
		buf[2] = digits[num % 16];

		return 4;

	}
	return 0;
}

/*F*************************/

int
b10_int(buf, num)

char *buf;				/* buffer to hold the number string */
int num;		/* the number to convert */
/*
* PURPOSE : Convert an integer into a string and store it in a buffer
*
* RETURN : The length of the number string
*
*F*/
{
	char tmp[13];
	bzero(tmp, 13);

	if (num == 0) {
		buf[0] = '0';
		return 1;
	} else {
		int i=0, j=0;
		int size=0;

		if(num < 0) {
			buf[0] = '-';
			num = num * -1;
			j = j+1;
		}

		for(i=0; i<11 && num!=0; i++) {
			tmp[i] = digits[num % 10];
			num = num / 10;
		}
		size = i;

		for(i=size; i > 0; i--) {
			buf[j+i-1] = tmp[size-i];
		}

		return size + j;

	}
	return 0;
}

/*F*************************/

int
b10_uint(buf, num)

char *buf;				/* buffer to hold the number string */
unsigned int num;		/* the number to convert */
/*
* PURPOSE : Convert a number into a string and store it in a buffer
*
* RETURN : The length of the number string
*
*F*/
{
	char tmp[12];
	bzero(tmp, 12);

	if (num == 0) {
		buf[0] = '0';
		return 1;
	} else {
		int i, size;
		for(i=0; i<10 && num!=0; i++) {
			tmp[i] = digits[num % 10];
			num = num / 10;
		}
		size = i;

		for(i=size; i > 0; i--) {
			buf[i-1] = tmp[size-i];
		}

		return size;

	}
	return 0;
}

/*F*************************/

int
db_4p(buf, num)

char *buf;				/* buffer to hold the number string */
double num;		/* the number to convert */
/*
* PURPOSE : Convert a positive floating point number into a string and store it in a buffer
*
* RETURN : The length of the number string
*
*F*/
{
	char tmp[40];
	bzero(tmp, 40);

	if (num == 0) {
		buf[0] = '0';
		buf[0] = '.';
		buf[0] = '0';
		return 3;
	} else {
		int i, size;
		for(i=0; i<10 && num>=1; i++) {
			tmp[i] = digits[(unsigned int) num % 10];
			num = num / 10;
		}
		size = i;

		for(i=size; i > 0; i--) {
			buf[i-1] = tmp[size-i];
			num = (num * 10) - ((unsigned int)(num * 10));			
		}
		buf[size] = '.';
		size++;

		for(i=0; i<4; i++) {
			buf[size] = digits[(unsigned int)(num * 10)];
			num = (num * 10) - ((unsigned int)(num * 10));
			size++;
		}

		return size;

	}
	return 0;
}

/*F*************************/

int
vsprintf(buf, fmt, args)

char *buf;				/* buffer to hold formatted string */
const char *fmt;        /* format of string */
va_list args;			/* list of arguments */

/*
* PURPOSE : Store a formatted string into a buffer
*
* RETURN : The number of characters stored in the buffer, or
*          a negative value if there was an error
*
*F*/
{
	char *x;
	int in;
	unsigned int u;
	unsigned char h;
	unsigned char ch;
	double db;
	int len;
	char *str;
	str = buf;
	int c, d, i;
	for(c = 0, d=0; fmt[c]; c++) {
		if(fmt[c] != '!') {
			str[d++] = fmt[c];
			continue;
		}

		c++;

		// Type
		switch(fmt[c]) {
			case 'X': 			// null-terminated string
				x = va_arg(args, char *);
				if (!x) x = "|BAD|";
				len = strlen(x);
				for(i = len; i > 0; i--) 
					str[d++] = x[len-i];
				continue; 
			
			case 'U':			// unsigned int
				u = va_arg(args, unsigned int);
				len = b10_uint(&str[d], u);
				d+=len;
				continue;

			case 'H': 			// unsigned char to 0x00
				h = va_arg(args, unsigned int);
				len = b16_2w(&str[d], h);
				d+=len;
				continue;

			case 'C':          // unsigned char 
				ch = va_arg(args, unsigned int);
				str[d]=ch;
				d+=sizeof(unsigned char);
				continue;

			case 'D':          // double
			 	db = va_arg(args, double);
			 	len = db_4p(&str[d], db);
			 	d+=len;
			 	continue;	

			case 'I':			// unsigned int
				in = va_arg(args, int);
				len = b10_int(&str[d], in);
				d+=len;
				continue;


		}
	}

	return d;
}

int
sprintf(char *buf, const char* fmt, ...)
{
	int n;
	va_list ap;

	va_start(ap, fmt);
	n = vsprintf (buf, fmt, ap);
	va_end(ap);
	return (n);
}
