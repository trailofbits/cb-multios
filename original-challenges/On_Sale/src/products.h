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

#ifndef PRODUCTS_H
#define PRODUCTS_H 1

#define MAX_DESC_LEN	128		// max bytes in Product desc
#define BARCODE_SZ 		8		// # bytes in bar code

typedef float __attribute__((regparm(2))) (*sale_fn)(unsigned int, float);

typedef struct {
	unsigned char barcode[BARCODE_SZ];
	char desc[MAX_DESC_LEN];
	unsigned int model_num;
	float cost;
	sale_fn sfn;
	unsigned int update_serial;
} Product;


/**
 * Initialize the postage and mailboxes.
 */
void setup(void);

/**
 * Process a user's command.
 *
 * @return SUCCESS on success, else -1
 */
short process_cmd(void);

#endif