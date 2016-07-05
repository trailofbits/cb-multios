/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <libcgc.h>
#include "libc.h"

// Receive until 'length' chars read OR 'end' char found OR newline. Up to 'length'
// chars written to 'dest', including 'end' char.  
// Returns 0 on success, otherwise error code. 
// Number of bytes read is returned in 'bytes_read'.
int receive_until(char *dest, size_t length, char end, size_t *bytes_read)
{
	size_t count = 0;
	char c;
	int receive_status;
	size_t receive_bytes;

	do 
	{
		receive_status = receive( STDIN , (void *)&c, 1, &receive_bytes);
		if ((receive_status != 0) || (receive_bytes != 1))
		{
			if (bytes_read != NULL) *bytes_read = count;
			return receive_status;
		}
		dest[count++] = c;
	} while ((c != end) && (c != '\n') && (count < length));
	if (bytes_read != NULL) *bytes_read = count;
	return 0;
}

size_t strlen(char *buf)
{
	size_t length = 0;
	while(buf[length]!='\0') length++;
	return length;
}

void print(char *buf)
{
   size_t len = strlen(buf);
   size_t tx = 0;
   size_t nbytes;
   while (tx < len) {
   	int res = transmit(STDOUT, (void *)buf + tx, len - tx, &nbytes);
   	if (res != 0 || nbytes == 0) {
   	   _terminate(res);
   	}
   	tx += nbytes;
   }
}

// Returns 1 if the strings are equal, otherwise 0
int equals(char *one, char *two)
{
	int i = 0;
	while((one[i]==two[i]) && (one[i]!='\0')) i++;
	return (one[i] == two[i]);
}

// Copy a string from src to dst. Copy ends when null byte reached
// in src string OR when length bytes have been copied to dst.
void strncpy(char *dst, char *src, size_t length)
{
	size_t pos;
	for(pos = 0; pos<length && src[pos]!='\0'; pos++)
	{
		dst[pos] = src[pos];
	}
	if (pos < length)
		dst[pos] = '\0';
}

int isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int atoi(char *str)
{
	size_t i = 0;
	int negative = 0;
	int result = 0;

	if (str == NULL)
		return 0;

	if(str[i] == '-')
	{
		negative = 1;
		i++;
	}
	if (str[i] == '+')
	{
		i++;
	}
	while(isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (negative)
	{
		result = - result;
	}

	return result;

}

// itoa - Does not check output buffer size. 
// Can potentially write up to 12 characters ("-2147483648\0") to str.
void itoa(char *str, int i)
{
	char buffer[11];
	int pos = 0;
	int outpos = 0;
	int neg = 0;
	if (i < 0)
	{
		neg = 1;
		i = -i;
	}
	do
	{
		buffer[pos++] = '0' + i % 10;
		i /= 10;
	} while (i > 0);

	if (neg == 1)
	{
		buffer[pos++] = '-';
	}
	if (str == NULL)
	{
		return;
	}

	while(outpos < pos)
	{
		str[outpos] = buffer[pos - outpos - 1];
		outpos ++;
	}
	str[outpos] = '\0';
}

void memcpy(char *dst, char *src, size_t size)
{
	char *end = dst + size;
	while(dst != end)
	{
		*dst++ = *src++;
	}
}

void memset(char *dst, char c, size_t size)
{
	char *end = dst + size;
	while(dst < end)
	{	
		*dst++ = c;
	}
}
