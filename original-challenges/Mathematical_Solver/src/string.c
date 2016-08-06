/*

Author: James Nuttall (james@cromulence.co)

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
#include "stdlib.h"
#include "math_lib.h"

// strlen 
// return length of str (defined as '\n', or '\0')
int get_str_end(char *str)
{
	int num = 0;

	while (str[num] != 0)
	{
		if (str[num] == '\n')
		{
			str[num] = '\0';
			break;
		}
		num++;
	}
	return num;
}

// str: pointer to string
// len: length of string
// reverses the order of the string
void reverse(char *str, int len)
{
	int st = 0;
	int end = len - 1;

	while (st < end)
	{
		char c;
		c = str[end];
		str[end] = str[st];
		str[st] = c;

		st++;
		end--;
	}
}

// pass in the num
// returns the str
int itos(int num, char *str)
{
	int is_neg = 0;

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return SUCCESS;
	}

	if (num < 0)
	{
		is_neg = 1;
		num *= -1;
	}

	int i = 0;
	while (num != 0)
	{
		int rem = num % 10;
		str[i++] = (rem > 9) ? (rem - 10) : rem + '0';
		num = num/10; 
	}

	if (is_neg)
	{
		str[i++] = '-';
	}

	
	reverse(str,i);
	str[i] = '\0';

	return SUCCESS;
}

// number string to integer
// str is the incoming string to get the value from
// moved is the number of characters long this number was
// returns the number
int stoi(char *str, int *moved)
{
	int num = 0;
	int i = 0;
	int len = 0;
	while (str[len] <= '9' && str[len] >= '0')
	{
		//printf("char to find len: %c\n", str[len]);
		len++;
	}
	*moved = len;

	for (i = 0; i < len; i++)
	{
		num = num * 10 + (str[i] - '0');
	}
	//printf("stoi: @offset %d: %c to %d\n", len, *str, num);

	return num;
}
