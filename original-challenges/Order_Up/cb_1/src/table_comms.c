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
#include "malloc.h"

#include "table.h"
#include "table_comms.h"
#include "comms.h"


char get_next_vacant_table(void) {
	unsigned char table_id;
	TableStatus ts = VACANT;
	for (table_id = 1; table_id <= TABLE_CNT; table_id++) {
		DBG("Requesting status of table ID: %U on fd: %U\n", table_id, T_WRITE_FD(table_id));
		SEND(T_WRITE_FD(table_id), T_CMD_TABLE_STATUS, sizeof(T_CMD_TABLE_STATUS));

		DBG("Receiving status of table ID: %U on fd: %U\n", table_id, T_READ_FD(MASTER_TID));
		RECV(T_READ_FD(MASTER_TID), (char *)&ts, sizeof(TableStatus));
		DBG("Table ID: %U status: %U\n", table_id, ts);
		if (VACANT == ts)
			return table_id;
	}
	return -1;
}

char get_seat_count_at_table(unsigned int table_id) {
	unsigned char count = 1;
	DBG("Requesting seat count of table ID: %U on fd: %U\n", table_id, T_WRITE_FD(table_id));
	SEND(T_WRITE_FD(table_id), T_CMD_TABLE_SIZE, sizeof(T_CMD_TABLE_SIZE));
	DBG("Receiving seat count of table ID: %U on fd: %U\n", table_id, T_READ_FD(MASTER_TID));
	RECV(T_READ_FD(MASTER_TID), (char *)&count, sizeof(unsigned char));
	DBG("Table ID: %U seat count: %U\n", table_id, count);
	return count;
}

char seat_customers_at_table(unsigned int table_id, unsigned char qty, Customer **c_list) {
	char status[sizeof(STATUS_OK) + 1] = {0};
	SEND(T_WRITE_FD(table_id), T_CMD_SEAT_CUST, sizeof(T_CMD_SEAT_CUST));

	// send # customers to seat
	SEND(T_WRITE_FD(table_id), (char *)&qty, sizeof(unsigned char));

	// loop through qty customers
	Customer *c = NULL;
	for (unsigned int s = 0; s < qty; s++) {
		c = pop_customer_from_list(c_list);
		// send customer id
		DBG("Seating c->id: %U\n", c->id);
		SEND(T_WRITE_FD(table_id), (char *)&c->id, sizeof(unsigned int));
		free(c);
	}

	// recv status (OK if seated, ERR if seats are full and couldn't seat all customers)
	RECV(T_READ_FD(MASTER_TID), status, sizeof(STATUS_OK));
	DBG("Seating result: %S\n", status);
	if (0 == memcmp((void *)STATUS_OK, status, sizeof(STATUS_OK))) {
		return SUCCESS;
	} else {
		return -1;
	}
}

char close_table(unsigned int table_id) {
	char status[sizeof(STATUS_OK) + 1] = {0};
	SEND(T_WRITE_FD(table_id), T_CMD_QUIT, sizeof(T_CMD_QUIT));
	RECV(T_READ_FD(MASTER_TID), status, sizeof(STATUS_OK));
	if (0 == memcmp((void *)STATUS_OK, status, sizeof(STATUS_OK))) {
		return SUCCESS;
	} else {
		return -1;
	}
}

TableStatus get_status_of_table(unsigned int table_id) {
	TableStatus ts = VACANT;
	DBG("Requesting status of table ID: %U on fd: %U\n", table_id, T_WRITE_FD(table_id));
	SEND(T_WRITE_FD(table_id), T_CMD_TABLE_STATUS, sizeof(T_CMD_TABLE_STATUS));

	DBG("Receiving status of table ID: %U on fd: %U\n", table_id, T_READ_FD(MASTER_TID));
	RECV(T_READ_FD(MASTER_TID), (char *)&ts, sizeof(TableStatus));
	DBG("Table ID: %U status: %U\n", table_id, ts);

	return ts;
}

unsigned char get_orders_from_table(unsigned int table_id, Order **o_list) {
	unsigned char order_count = 0;
	Order *o = NULL;
	Appetizer *app = NULL;
	Meal *meal = NULL;
	Dessert *des = NULL;
	unsigned char ret = 0;

	// send order request
	DBG("Requesting orders from table ID: %U on fd: %U\n", table_id, T_WRITE_FD(table_id));
	SEND(T_WRITE_FD(table_id), T_CMD_TAKE_ORDER, sizeof(T_CMD_TAKE_ORDER));

	// recv order count
	RECV(T_READ_FD(MASTER_TID), (char *)&order_count, sizeof(unsigned char));
	DBG("Received %U orders from table %U\n", order_count, table_id);

	// recv orders
	ret = order_count;
	while (0 < order_count) {
		o = malloc(sizeof(Order));
		MALLOC_OK(o);
		memset(o, '\x00', sizeof(Order));
		RECV(T_READ_FD(MASTER_TID), (char *)&o->t_id, sizeof(unsigned int));
		RECV(T_READ_FD(MASTER_TID), (char *)&o->c_id, sizeof(unsigned int));
		RECV(T_READ_FD(MASTER_TID), (char *)&o->ftype, sizeof(FoodTypes));
		switch (o->ftype) {
			case APP_TYPE:
				app = malloc(sizeof(Appetizer));
				MALLOC_OK(app);
				app->ftype = o->ftype;
				DBG("receiving appetizer\n");
				RECV(T_READ_FD(MASTER_TID), (char *)app->name, sizeof(Appetizer) - sizeof(FoodTypes) - sizeof(void *));
				o->item = (void *)app;
				break;
			case MEAL_TYPE:
				meal = malloc(sizeof(Meal));
				MALLOC_OK(meal);
				meal->ftype = o->ftype;
				DBG("receiving meal\n");
				RECV(T_READ_FD(MASTER_TID), (char *)meal->name, sizeof(Meal) - sizeof(FoodTypes) - sizeof(void *));
				o->item = (void *)meal;
				break;
			case DES_TYPE:
				des = malloc(sizeof(Dessert));
				MALLOC_OK(des);
				des->ftype = o->ftype;
				DBG("receiving dessert\n");
				RECV(T_READ_FD(MASTER_TID), (char *)des->name, sizeof(Dessert) - sizeof(FoodTypes) - sizeof(void *));
				o->item = (void *)des;
				break;
			default:
				DBG("invalid Order ftype\n");
				free(o);
				return 0;
		}
		append_order_to_list(o_list, o);
		order_count--;
	}

	return ret;
}

char deliver_orders_to_table(unsigned int table_id, Order **o_list) {
	unsigned char order_count = 0;
	Order *o = NULL;
	Appetizer *app = NULL;
	Meal *meal = NULL;
	Dessert *des = NULL;
	char status[sizeof(STATUS_OK) + 1] = {0};

	// send delivery notification
	DBG("Delivering orders to table ID: %U on fd: %U\n", table_id, T_WRITE_FD(table_id));
	SEND(T_WRITE_FD(table_id), T_CMD_DELIVER_ORDER, sizeof(T_CMD_DELIVER_ORDER));

	// table expects 1 order per seated customer
	// but still need to send order_count to prevent the recv/send from hanging
	// when the number of orders doesn't match the number of seated customers.
	order_count = get_order_list_size(*o_list);
	SEND(T_WRITE_FD(table_id), (char *)&order_count, sizeof(unsigned char));
	DBG("Sending %U orders to table %U\n", order_count, table_id);

	// send orders
	o = pop_order_from_list(o_list);
	while (NULL != o) {
		// don't need to send t_id to a table with that id. it already knows.
		// SEND(T_WRITE_FD(table_id), (char *)&o->t_id, sizeof(unsigned char));
		SEND(T_WRITE_FD(table_id), (char *)&o->c_id, sizeof(unsigned int));
		SEND(T_WRITE_FD(table_id), (char *)&o->ftype, sizeof(FoodTypes));
		switch (o->ftype) {
			case APP_TYPE:
				app = (Appetizer *)o->item;
				DBG("sending appetizer %S\n", app->name);
				SEND(T_WRITE_FD(table_id), (char *)app->name, sizeof(Appetizer) - sizeof(FoodTypes) - sizeof(void *));
				break;
			case MEAL_TYPE:
				meal = (Meal *)o->item;
				DBG("sending meal %S, %S, %S, %S\n", meal->name, meal->main, meal->veggies, meal->side);
				SEND(T_WRITE_FD(table_id), (char *)meal->name, sizeof(Meal) - sizeof(FoodTypes) - sizeof(void *));
				break;
			case DES_TYPE:
				des = (Dessert *)o->item;
				DBG("sending dessert %S\n", des->name);
				SEND(T_WRITE_FD(table_id), (char *)des->name, sizeof(Dessert) - sizeof(FoodTypes) - sizeof(void *));
				break;
			default:
				DBG("invalid Order ftype %U\n", o->ftype);
				free(o);
				return 0;
		}
		free(o->item);
		free(o);
		o = pop_order_from_list(o_list);
	}

	// recv status (OK if all orders delivered correctly, ERR if one or more orders was undeliverable)
	RECV(T_READ_FD(MASTER_TID), status, sizeof(STATUS_OK));
	DBG("Order delivery result: %S\n", status);
	if (0 == memcmp((void *)STATUS_OK, status, sizeof(STATUS_OK))) {
		return SUCCESS;
	} else {
		return -1;
	}
}

char clean_and_set_table(unsigned int table_id) {
	char status[sizeof(STATUS_OK) + 1] = {0};

	DBG("Directing clean and set table ID: %U on fd: %U\n", table_id, T_WRITE_FD(table_id));
	SEND(T_WRITE_FD(table_id), T_CMD_TABLE_CLEAN_SET, sizeof(T_CMD_TABLE_CLEAN_SET));
	RECV(T_READ_FD(MASTER_TID), status, sizeof(STATUS_OK));
	if (0 == memcmp((void *)STATUS_OK, status, sizeof(STATUS_OK))) {
		return SUCCESS;
	} else {
		return -1;
	}
}

