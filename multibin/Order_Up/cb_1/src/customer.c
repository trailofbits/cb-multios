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
#include <stdint.h>
#include "libc.h"

#include "menu.h"
#include "customer.h"

Customer *pop_customer_from_list(Customer **c_list) {
	if (NULL == *c_list) return NULL;

	Customer *c = *c_list;
	*c_list = (Customer *)c->next;
	DBG("Pop customer %U from customer list\n", c->id);
#ifdef DEBUG
		print_customer_list(*c_list);
#endif
	c->next = NULL;
	return c;
}

void append_customer_to_list(Customer **c_list, Customer *c) {
	Customer *cur = *c_list;
	c->next = NULL;
	if (NULL == cur) {
		*c_list = c;
	} else {
		for (; NULL != cur->next; cur=(Customer *)cur->next);

		cur->next = c;
		DBG("Append customer %U to customer list\n", c->id);
	}
#ifdef DEBUG
		print_customer_list(*c_list);
#endif
}

unsigned char get_customer_list_size(Customer *c_list) {
	Customer *cur = c_list;
	unsigned char count = 0;

	while (NULL != cur) {
		cur=(Customer *)cur->next;
		count++;
	}
	return count;
}

void print_customer_list(Customer *c_list) {
	Customer *cur = c_list;
	unsigned char count = 0;
	DBG("Printing Customer list of size %U\n", get_customer_list_size(c_list));
	while (NULL != cur) {
		DBG("Customer: %U\n", cur->id);
		cur=(Customer *)cur->next;
	}
}

void print_customer(Customer *c) {
	DBG("Customer id: %U, next: %H\n", c->id, c->next);
	print_appetizer(&c->a);
	print_meal(&c->m);
	print_dessert(&c->d);
}
