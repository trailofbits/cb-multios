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
#include <libcgc.h>
// #include <stdint.h>
#include "libc.h"

#include "order.h"

Order *pop_order_from_list(Order **o_list) {
	if (NULL == *o_list) return NULL;

	Order *o = *o_list;
	*o_list = (Order *)o->next;

	return o;
}

void append_order_to_list(Order **o_list, Order *o) {
	Order *cur = *o_list;
	o->next = NULL;

	if (NULL == cur) {
		*o_list = o;
	} else {
		for (; NULL != cur->next; cur=(Order *)cur->next);

		cur->next = o;
	}

}

unsigned char get_order_list_size(Order *o_list) {
	Order *cur = o_list;
	unsigned char count = 0;

	while (NULL != cur) {
		cur=(Order *)cur->next;
		count++;
	}
	return count;
}

