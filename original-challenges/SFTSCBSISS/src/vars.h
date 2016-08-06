/*

Author: Joe Rogers <joe@cromulence.co>

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

#define MAX_NAME_LEN (128)
#define MAX_VALUE_LEN (128)

typedef struct _vars {
	char name[MAX_NAME_LEN];
	uint8_t type;
	unsigned char value[MAX_VALUE_LEN];
	struct _vars *prev;
	struct _vars *next;
} vars_t;

#define STRING (1)
#define INT32 (2)

int32_t InitVARS(void);
int32_t DestroyVARS(void);
vars_t *SearchVARS(char *target_name);
vars_t *CreateVARSObject(char *, uint8_t, void *);
int32_t InsertVARSObject(vars_t *);
int32_t DeleteVARSObject(vars_t *);
vars_t *UpdateVARSObject(char *, uint8_t, void *);
