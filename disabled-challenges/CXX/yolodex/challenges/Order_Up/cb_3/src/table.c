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
#include "cgc_memset.h"
#include "cgc_malloc.h"

#include "cgc_menu.h"
#include "cgc_table.h"

Table table;

/**
 * Calculate how many seats this table will have.
 *
 * @return Number of seats.
 */
static unsigned char cgc_calculate_seats_count(void) {
	unsigned char seats = 1;
	unsigned char *flag_bytes = (unsigned char *)FLAG_PAGE;
    // for testing
    // seats = 5;
    // for release
    seats = flag_bytes[table.id] % MAX_TABLE_SIZE;
    if (MIN_TABLE_SIZE > seats) {
       seats += MIN_TABLE_SIZE;
    }

	return seats;
}

/**
 * Count the number of occupied seats
 *
 * @return Number of occupied seats
 */
static unsigned char cgc_get_occupied_seats_count(void) {
	unsigned char occupied_seats = 0;
	Customer *cur = table.customers;
	while (NULL != cur) {
		cur = (Customer *)cur->next;
		occupied_seats++;
	}
	DBG("%U occupied seats\n", occupied_seats);
	return occupied_seats;
}

/**
 * Count the number of empty seats
 *
 * @return Number of empty seats.
 */
static unsigned char cgc_get_empty_seats_count(void) {
	unsigned char empty_seats = cgc_get_seats_count() - cgc_get_occupied_seats_count();
	DBG("%U empty seats\n", empty_seats);
	return empty_seats;
}

/**
 * Update the table status
 *
 * @param ts 	New table status
 */
static void cgc_set_table_status(TableStatus ts) {
	table.status = ts;
}

/**
 * Seat one customer
 *
 * @param c 	Customer to seat
 * @return SUCCESS on success, else -1 if seats are full
 */
static int cgc_seat_customer(Customer *c) {
	DBG("seating a customer\n");
	Customer *cur = table.customers;

	if (0 == cgc_get_empty_seats_count()) {
		DBG("Customer %U not seated. 0 empty seats\n", c->id);
		return -1;
	}

	c->next = NULL;
	if (NULL == cur) {
		table.customers = c;
	} else {
		for (; NULL != cur->next; cur=(Customer *)cur->next);

		cur->next = c;
	}

	DBG("Customer %U seated\n", c->id);
	return SUCCESS;
}

/**
 * Take the order of one customer
 *
 * @param c 	Customer
 * @return Pointer to a new Order or NULL if no order
 */
static Order *cgc_take_customer_order(Customer *c) {
	Order *o = cgc_malloc(sizeof(Order));
	MALLOC_OK(o);
	cgc_memset(o, '\0', sizeof(Order));

	o->t_id = table.id;
	o->c_id = c->id;
	DBG("Table status: %U\n", table.status);
	switch(table.status) {
		case APP_RTO:	// RTO => ready to order
			o->ftype = APP_TYPE;
			o->item = cgc_select_appetizer(cgc_get_appetizer_list(), c);
			DBG("Customer %U ordering appetizer\n", c->id);
			break;
		case MEAL_RTO:
			o->ftype = MEAL_TYPE;
			o->item = cgc_select_meal(cgc_get_meal_list(), c);
			DBG("Customer %U ordering meal\n", c->id);
			break;
		case DES_RTO:
			o->ftype = DES_TYPE;
			o->item = cgc_select_dessert(cgc_get_dessert_list(), c);
			DBG("Customer %U ordering dessert\n", c->id);
			break;
		default:		// WAIT => already ordered, VACANT, FINISHED
			DBG("Customer %U NOT ordering\n", c->id);
			cgc_free(o);
			return NULL;
	}
	return o;
}

void cgc_table_setup(void) {
	cgc_memset(&table, '\0', sizeof(Table));
	table.id = TABLE_ID;
	table.status = VACANT;
	table.seats = cgc_calculate_seats_count();
	table.customers = NULL;
}

void cgc_table_clean_and_set(void) {
	Customer *c_list = table.customers;
	Customer *c = NULL;
	unsigned char cnt = cgc_get_customer_list_size(c_list);
	DBG("%U Customers to remove from table\n", cnt);

	c = cgc_pop_customer_from_list(&c_list);
	while (NULL != c) {
		DBG("Customer %U left the table\n", c->id);
		cgc_free(c);
		c = cgc_pop_customer_from_list(&c_list);
	}

	cgc_table_setup();
}

unsigned char cgc_get_seats_count(void) {
	DBG("%U total seats\n", table.seats);
	return table.seats;
}

TableStatus cgc_get_table_status(void) {
	return table.status;
}

int cgc_seat_customers(unsigned char qty, Customer *c_list) {
	int ret = SUCCESS;
	Customer *c = NULL;

	if (VACANT != cgc_get_table_status()) {
		DBG("table is not vacant");
		cgc_clear_customer_list(&c_list);
		return -1;
	}

    DBG("seating %U customers\n", qty);

	for (unsigned char cnt = 0; cnt < qty; cnt++) {
		c = cgc_pop_customer_from_list(&c_list);
		if (NULL == c) return -1;
		ret = cgc_seat_customer(c);
		if (SUCCESS != ret) return ret;
	}

	if (0 < qty) {
		cgc_set_table_status(table.status + 1);
		DBG("table status updated: %U\n", table.status);
	} else {
		DBG("table status NOT updated: %U\n", table.status);
	}
	return SUCCESS;
}

unsigned char cgc_take_customer_orders(Order **o_list) {
	unsigned char o_count = 0;
	Customer *cur = table.customers;
	Order *o = NULL;

	while (NULL != cur) {
		o = cgc_take_customer_order(cur);
		if (NULL != o) {
			cgc_append_order_to_list(o_list, o);
			o_count++;
		}

		cur = (Customer *)cur->next;		
	}
	if (0 < o_count) {
		cgc_set_table_status(table.status + 1);
		DBG("table status updated: %U\n", table.status);
	} else {
		DBG("table status NOT updated: %U\n", table.status);
	}
	return o_count;
}

/**
 * When food is to be delivered, determine the type of food based on the TableStatus.
 *
 * @param ts 	TableStatus
 * @return Type of food if this table is ready for food delivery, else FOOD_TYPES
 */
static FoodTypes cgc_get_delivery_foodtype_from_tablestatus(TableStatus ts) {
	FoodTypes ftype = 0;

	switch(table.status) {
		case APP_WAIT:
			ftype = APP_TYPE;
			break;
		case MEAL_WAIT:
			ftype = MEAL_TYPE;
			break;
		case DES_WAIT:
			ftype = DES_TYPE;
			break;
		default:		// RTO => ready to order, VACANT, FINISHED
			ftype = FOOD_TYPES;
	}
	return ftype;
}

/**
 * Give a food item to a customer
 *
 * @param c 		Customer
 * @param ftype 	Type of food
 * @param food 		Food item
 * @return SUCCESS on success, else -1 if invalid ftype
 */
static char cgc_give_food_to_customer(Customer *c, FoodTypes ftype, void *food) {

	char ret = SUCCESS;
	unsigned int bufsz = 0;
	void *buf = NULL;

	// get size of food using provided ftype
	switch (ftype) {
		case APP_TYPE:
			DBG("food size as appetizer\n");
			bufsz = sizeof(Appetizer);
			break;
		case MEAL_TYPE:
			DBG("food size as Meal\n");
			bufsz = sizeof(Meal);
			break;
		case DES_TYPE:
			DBG("food size as Dessert\n");
			bufsz = sizeof(Dessert);
			break;
		default:
			DBG("invalid ftype\n");
			ret = -1;
	}

#ifndef PATCHED_2
	// VULN: table.status can be mismatched with ftype provided by user.
	// Use table.status to get location to cgc_write food into Customer and the proper food inspection function
	ftype = cgc_get_delivery_foodtype_from_tablestatus(table.status);
#endif
	switch (ftype) {
		case APP_TYPE:
			DBG("buf as appetizer\n");
			buf = &c->a;
			c->fi = cgc_inspect_appetizer;
			break;
		case MEAL_TYPE:
			DBG("buf as Meal\n");
			buf = &c->m;
			c->fi = cgc_inspect_meal;
			break;
		case DES_TYPE:
			DBG("buf as Dessert\n");
			buf = &c->d;
			c->fi = cgc_inspect_dessert;
			break;
		default:
			DBG("invalid ftype\n");
			ret = -1;
	}

	if (SUCCESS == ret) {
		cgc_accept_food(food, buf, bufsz);
		ret = c->fi(buf, c->id);
	}

#ifdef DEBUG
	switch (ftype) {
		case APP_TYPE:
			DBG("wrote appetizer\n");
			print_appetizer(&c->a);
			break;
		case MEAL_TYPE:
			DBG("wrote meal\n");
			print_meal(&c->m);
			break;
		case DES_TYPE:
			DBG("wrote dessert\n");
			print_dessert(&c->d);
			break;
		default:
			DBG("invalid ftype\n");
			ret = -1;
	}
	print_customer(c);
#endif

	return ret;
}

unsigned char cgc_deliver_customer_orders(Order **o_list) {
	unsigned char o_count = cgc_get_order_list_size(*o_list);
	unsigned char d_count = 0;
	Order *o = NULL;
	Customer *c = NULL;
	FoodTypes ft = 0;

	// loop through orders
	o = cgc_pop_order_from_list(o_list);
	while (NULL != o) {

		// get customer having c_id from order
		c = cgc_get_customer_by_id(table.customers, o->c_id);
		if (NULL != c) {
			// cgc_write food to customer
			if (SUCCESS == cgc_give_food_to_customer(c, o->ftype, o->item)) {
				d_count++;
			}
		}
		cgc_free(o->item);
		cgc_free(o);
		o = cgc_pop_order_from_list(o_list);
	}

	if (0 < d_count) {
		cgc_set_table_status(table.status + 1);
		DBG("table status updated: %U\n", table.status);
	} else {
		DBG("table status NOT updated: %U\n", table.status);
	}

	return (o_count - d_count);
}


