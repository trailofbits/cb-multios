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
#include "memcmp.h"
#include "memset.h"
#include "memcpy.h"
#include "list.h"
#include "malloc.h"
#include "string.h"

#include "menu.h"
#include "todays_menu.h"

Menu todays_menu;

void menu_setup(void) {
    memset(&todays_menu, '\0', sizeof(Menu));
    load_menu(&todays_menu);
}

Appetizer *get_appetizer_list(void) {
	return todays_menu.appetizer_list;
}

Meal *get_meal_list(void) {
	return todays_menu.meal_list;
}

Dessert *get_dessert_list(void) {
	return todays_menu.dessert_list;
}

unsigned int get_appetizer_count(void) {
	Appetizer *cur = todays_menu.appetizer_list;
	unsigned int count = 0;

	while (NULL != cur) {
		cur=(Appetizer *)cur->next;
		count++;
	}
	return count;
}

unsigned int get_meal_count(void) {
	Meal *cur = todays_menu.meal_list;
	unsigned int count = 0;

	while (NULL != cur) {
		cur=(Meal *)cur->next;
		count++;
	}
	return count;
}

unsigned int get_dessert_count(void) {
	Dessert *cur = todays_menu.dessert_list;
	unsigned int count = 0;

	while (NULL != cur) {
		cur=(Dessert *)cur->next;
		count++;
	}
	return count;
}

void print_appetizer(Appetizer *a) {
	DBG("Appetizer name:%S, next:%H\n", a->name, a->next);
}

void print_meal(Meal *m) {
	DBG("Meal name:%S, main:%S, veggies:%S, side:%S, next:%H\n", m->name, m->main, m->veggies, m->side, m->next);
}

void print_dessert(Dessert *d) {
	DBG("Dessert name:%S, next:%H\n", d->name, d->next);
}
