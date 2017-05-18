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
#include "cgc_memcmp.h"
#include "cgc_memset.h"
#include "cgc_memcpy.h"
#include "cgc_list.h"
#include "cgc_malloc.h"
#include "cgc_string.h"

#include "cgc_menu.h"
#include "cgc_todays_menu.h"

Menu todays_menu;

void cgc_menu_setup(void) {
    cgc_memset(&todays_menu, '\0', sizeof(Menu));
    cgc_load_menu(&todays_menu);
}

Appetizer *cgc_get_appetizer_list(void) {
	return todays_menu.appetizer_list;
}

Meal *cgc_get_meal_list(void) {
	return todays_menu.meal_list;
}

Dessert *cgc_get_dessert_list(void) {
	return todays_menu.dessert_list;
}

unsigned int cgc_get_appetizer_count(void) {
	Appetizer *cur = todays_menu.appetizer_list;
	unsigned int count = 0;

	while (NULL != cur) {
		cur=(Appetizer *)cur->next;
		count++;
	}
	return count;
}

unsigned int cgc_get_meal_count(void) {
	Meal *cur = todays_menu.meal_list;
	unsigned int count = 0;

	while (NULL != cur) {
		cur=(Meal *)cur->next;
		count++;
	}
	return count;
}

unsigned int cgc_get_dessert_count(void) {
	Dessert *cur = todays_menu.dessert_list;
	unsigned int count = 0;

	while (NULL != cur) {
		cur=(Dessert *)cur->next;
		count++;
	}
	return count;
}

void cgc_print_appetizer(Appetizer *a) {
	DBG("Appetizer name:%S, next:%H\n", a->name, a->next);
}

void cgc_print_meal(Meal *m) {
	DBG("Meal name:%S, main:%S, veggies:%S, side:%S, next:%H\n", m->name, m->main, m->veggies, m->side, m->next);
}

void cgc_print_dessert(Dessert *d) {
	DBG("Dessert name:%S, next:%H\n", d->name, d->next);
}
