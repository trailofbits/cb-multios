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
#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_memcpy.h"
#include "cgc_malloc.h"

#include "cgc_customer.h"

Customer *cgc_pop_customer_from_list(Customer **c_list) {
	if (NULL == *c_list) return NULL;

	Customer *c = *c_list;
	*c_list = (Customer *)c->next;

	return c;
}

void cgc_append_customer_to_list(Customer **c_list, Customer *c) {
	Customer *cur = *c_list;
	c->next = NULL;
	if (NULL == cur) {
		*c_list = c;
	} else {
		for (; NULL != cur->next; cur=(Customer *)cur->next);

		cur->next = c;
	}
}

unsigned char cgc_get_customer_list_size(Customer *c_list) {
	Customer *cur = c_list;
	unsigned char count = 0;

	while (NULL != cur) {
		cur=(Customer *)cur->next;
		count++;
	}
	return count;
}

Customer *cgc_get_customer_by_id(Customer *c_list, unsigned int c_id) {
	Customer *cur = c_list;

	while (NULL != cur) {
		if (c_id == cur->id) {
			return cur;
		}
		cur=(Customer *)cur->next;
	}
	return NULL;
}

void cgc_clear_customer_list(Customer **c_list) {
	Customer *cur = cgc_pop_customer_from_list(c_list);
	Customer *prev = NULL;

	while (NULL != cur) {
		prev = cur;
		cur = cgc_pop_customer_from_list(c_list);
		cgc_free(prev);
	}
}

Appetizer *cgc_select_appetizer(Appetizer *a_list, Customer *c) {
	Appetizer *cur = a_list;
	// idx into FLAG_PAGE
	unsigned int idx = (c->id * c->id) % 4096;
	// idx into appetizers
	idx = (unsigned int)*((unsigned char *)FLAG_PAGE + idx);
	idx %= cgc_get_appetizer_count();

	while ((cur != NULL) && (0 < idx)) {
		cur = (Appetizer *)cur->next;
		idx--;
	}
	return cur;
}

Meal *cgc_select_meal(Meal *m_list, Customer *c) {
	Meal *cur = m_list;
	// idx into FLAG_PAGE
	unsigned int idx = (c->id * c->id) % 4096;
	// idx into appetizers
	idx = (unsigned int)*((unsigned char *)FLAG_PAGE + idx);
	idx %= cgc_get_meal_count();

	while ((cur != NULL) && (0 < idx)) {
		cur = (Meal *)cur->next;
		idx--;
	}
	return cur;
}

Dessert *cgc_select_dessert(Dessert *d_list, Customer *c) {
	Dessert *cur = d_list;
	// idx into FLAG_PAGE
	unsigned int idx = (c->id * c->id) % 4096;
	// idx into appetizers
	idx = (unsigned int)*((unsigned char *)FLAG_PAGE + idx);
	idx %= cgc_get_dessert_count();

	while ((cur != NULL) && (0 < idx)) {
		cur = (Dessert *)cur->next;
		idx--;
	}
	return cur;
}

char __attribute__((regparm(2))) cgc_inspect_appetizer(void *a, unsigned int cid) {
	Appetizer *app = (Appetizer *)a;
	if ('\0' == app->name[0])
		return -1;
	return SUCCESS;
}

char __attribute__((regparm(2))) cgc_inspect_meal(void *m, unsigned int cid) {
	Meal *meal = (Meal *)m;
	if ('\0' == meal->name[0])
		return -1;
	return SUCCESS;
}

char __attribute__((regparm(2))) cgc_inspect_dessert(void *d, unsigned int cid) {
	Dessert *des = (Dessert *)d;
	if ('\0' == des->name[0])
		return -1;
	return SUCCESS;
}

void cgc_accept_food(void *food, void *buf, unsigned int bufsz) {
	cgc_memcpy(buf, (const void *)food, bufsz);
}

void cgc_print_customer(Customer *c) {
	DBG("Customer id: %U, fi: %H, next: %H\n", c->id, c->fi, c->next);
	cgc_print_appetizer(&c->a);
	cgc_print_meal(&c->m);
	cgc_print_dessert(&c->d);
}

