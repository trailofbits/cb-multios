/*

Author: Dustin Fraze <df@cromulence.co>

Copyright (c) 2015 Cromulence LLC

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

#include "ltypes.h"

#include <libcgc.h>
#include <stdlib.h>

ltype *lint(char *name, char *val) {
	ltype *ret;
	ret = calloc(sizeof(ltype), 1);
	ret->value = (void *)atoi(val);
	ret->type = "Integer";
	ret->name = strdup(name);
	ret->len = strlen(val);
	return ret;
}

ltype *lstring(char *name, char *val) {
	ltype *ret;
	ret = calloc(sizeof(ltype), 1);
	ret->value = strdup(val);
	ret->type = "String";
	ret->name = strdup(name);
	ret->len = strlen(val);
	return ret;
}

ltype *lbool(char *name, char *val) {
	ltype *ret;
	ret = calloc(sizeof(ltype), 1);
	if(strcmp(val, "True") == 0) {
		ret->value = (void *)1;
	} else {
		ret->value = (void *)0;
	}
	ret->len = 1;
	ret->type = "Boolean";
	ret->name = strdup(name);
	return ret;
}

ltype *lfunc(char *name, void (*val)()) {
	ltype *ret;
	ret = calloc(sizeof(ltype), 1);
	ret->name = strdup(name);
	ret->value = val;
	ret->type = "Function";
	ret->len = 0;
	return ret;
}