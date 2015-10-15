/*

Author: Joe Rogers <joe@cromulence.com>

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
struct language lh;
struct language l[] = {
	{ .c = '\x00', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x01', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x02', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x03', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x04', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x05', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x06', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x07', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x08', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x09', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x0a', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x0b', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x0c', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x0d', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x0e', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x0f', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x10', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x11', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x12', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x13', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x14', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x15', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x16', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x17', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x18', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x19', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x1a', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x1b', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x1c', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x1d', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x1e', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '\x1f', .code = "", .dit = NULL, .dah = NULL },
	{ .c = ' ', .code = "", .dit = NULL, .dah = NULL },
	{ .c = '!', .code = ".", .dit = NULL, .dah = NULL },
	{ .c = '"', .code = "-", .dit = NULL, .dah = NULL },
	{ .c = '#', .code = "..", .dit = NULL, .dah = NULL },
	{ .c = '$', .code = ".-", .dit = NULL, .dah = NULL },
	{ .c = '%', .code = "-.", .dit = NULL, .dah = NULL },
	{ .c = '&', .code = "--", .dit = NULL, .dah = NULL },
	{ .c = '\x27', .code = "...", .dit = NULL, .dah = NULL },
	{ .c = '(', .code = "..-", .dit = NULL, .dah = NULL },
	{ .c = ')', .code = ".-.", .dit = NULL, .dah = NULL },
	{ .c = '*', .code = ".--", .dit = NULL, .dah = NULL },
	{ .c = '+', .code = "-..", .dit = NULL, .dah = NULL },
	{ .c = ',', .code = "-.-", .dit = NULL, .dah = NULL },
	{ .c = '-', .code = "--.", .dit = NULL, .dah = NULL },
	{ .c = '.', .code = "---", .dit = NULL, .dah = NULL },
	{ .c = '/', .code = "....", .dit = NULL, .dah = NULL },
	{ .c = '0', .code = "...-", .dit = NULL, .dah = NULL },
	{ .c = '1', .code = "..-.", .dit = NULL, .dah = NULL },
	{ .c = '2', .code = "..--", .dit = NULL, .dah = NULL },
	{ .c = '3', .code = ".-..", .dit = NULL, .dah = NULL },
	{ .c = '4', .code = ".-.-", .dit = NULL, .dah = NULL },
	{ .c = '5', .code = ".--.", .dit = NULL, .dah = NULL },
	{ .c = '6', .code = ".---", .dit = NULL, .dah = NULL },
	{ .c = '7', .code = "-...", .dit = NULL, .dah = NULL },
	{ .c = '8', .code = "-..-", .dit = NULL, .dah = NULL },
	{ .c = '9', .code = "-.-.", .dit = NULL, .dah = NULL },
	{ .c = ':', .code = "-.--", .dit = NULL, .dah = NULL },
	{ .c = ';', .code = "--..", .dit = NULL, .dah = NULL },
	{ .c = '<', .code = "--.-", .dit = NULL, .dah = NULL },
	{ .c = '=', .code = "---.", .dit = NULL, .dah = NULL },
	{ .c = '>', .code = "----", .dit = NULL, .dah = NULL },
	{ .c = '?', .code = ".....", .dit = NULL, .dah = NULL },
	{ .c = '@', .code = "....-", .dit = NULL, .dah = NULL },
	{ .c = 'A', .code = "...-.", .dit = NULL, .dah = NULL },
	{ .c = 'B', .code = "...--", .dit = NULL, .dah = NULL },
	{ .c = 'C', .code = "..-..", .dit = NULL, .dah = NULL },
	{ .c = 'D', .code = "..-.-", .dit = NULL, .dah = NULL },
	{ .c = 'E', .code = "..--.", .dit = NULL, .dah = NULL },
	{ .c = 'F', .code = "..---", .dit = NULL, .dah = NULL },
	{ .c = 'G', .code = ".-...", .dit = NULL, .dah = NULL },
	{ .c = 'H', .code = ".-..-", .dit = NULL, .dah = NULL },
	{ .c = 'I', .code = ".-.-.", .dit = NULL, .dah = NULL },
	{ .c = 'J', .code = ".-.--", .dit = NULL, .dah = NULL },
	{ .c = 'K', .code = ".--..", .dit = NULL, .dah = NULL },
	{ .c = 'L', .code = ".--.-", .dit = NULL, .dah = NULL },
	{ .c = 'M', .code = ".---.", .dit = NULL, .dah = NULL },
	{ .c = 'N', .code = ".----", .dit = NULL, .dah = NULL },
	{ .c = 'O', .code = "-....", .dit = NULL, .dah = NULL },
	{ .c = 'P', .code = "-...-", .dit = NULL, .dah = NULL },
	{ .c = 'Q', .code = "-..-.", .dit = NULL, .dah = NULL },
	{ .c = 'R', .code = "-..--", .dit = NULL, .dah = NULL },
	{ .c = 'S', .code = "-.-..", .dit = NULL, .dah = NULL },
	{ .c = 'T', .code = "-.-.-", .dit = NULL, .dah = NULL },
	{ .c = 'U', .code = "-.--.", .dit = NULL, .dah = NULL },
	{ .c = 'V', .code = "-.---", .dit = NULL, .dah = NULL },
	{ .c = 'W', .code = "--...", .dit = NULL, .dah = NULL },
	{ .c = 'X', .code = "--..-", .dit = NULL, .dah = NULL },
	{ .c = 'Y', .code = "--.-.", .dit = NULL, .dah = NULL },
	{ .c = 'Z', .code = "--.--", .dit = NULL, .dah = NULL },
};
