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
#include "memcpy.h"
#include "list.h"
#include "malloc.h"
#include "string.h"
#include "recv_until_delim_n.h"

#include "restaurant.h"
#include "customer.h"
#include "menu.h"
#include "table.h"
#include "table_comms.h"
#include "comms.h"

// CMD values for this cb
static const char CMD_ADD_CUST[4] 		= {'\xEE','\x01','\xEE','\x01'};
static const char CMD_GET_ORDERS[4] 	= {'\x01','\xEE','\x01','\xEE'};
static const char CMD_ORDER_UP[4] 		= {'\x0E','\x0E','\x0E','\x0E'};
static const char CMD_TABLE_STATUS[4] 	= {'\xBE','\xBE','\xBE','\xBE'};
static const char CMD_BUS_TABLES[4]		= {'\xBB','\x11','\x11','\xBB'};
static const char CMD_QUIT[4] 			= {'\xB0','\x01','\xB0','\x01'};


Customer *waiting_list = NULL;

/**
 * Determine if the waiting list is empty.
 *
 * @return TRUE if empty, else FALSE
 */
static unsigned char is_waiting_list_empty(void) {
	return (NULL == waiting_list);
}

/**
 * Get the next customer in line on the waiting list
 *
 * @return Pointer to next customer or NULL if list is empty
 */
static Customer *pop_customer_from_waiting_list(void) {
	if (TRUE == is_waiting_list_empty()) return NULL;
	return pop_customer_from_list(&waiting_list);
}

/**
 * Add a new customer to the end of the waiting list
 *
 * @param c 	New Customer
 */
static void append_customer_to_waiting_list(Customer *c) {
	append_customer_to_list(&waiting_list, c);
}

/**
 * Count the number of customers on the waiting list
 *
 * @return Number of Customers
 */
static unsigned char get_waiting_list_size(void) {
	return get_customer_list_size(waiting_list);
}

/**
 * When new customers arrive, add them to the waiting list and then seat them.
 *
 * @return SUCCESS on success, else -1
 */
static char do_add_customers(void) {
	unsigned char party_sz[2] = {0};
	unsigned int table_id = 0;
	unsigned char seats = 0;
	unsigned char to_seat = 0;
	Customer *c = NULL;
	Customer *c_to_seat = NULL;

	// recv # of customers in party
	RECV(STDIN, (char *)party_sz, sizeof(unsigned char));
    DBG("%U customers in party.\n", party_sz[0]);

	// recv customers
	while (0 < party_sz[0]) {
		c = malloc(sizeof(Customer));
		MALLOC_OK(c);

		// recv customer ID
		RECV(STDIN, (char *)&c->id, sizeof(unsigned int));
	    DBG("Recvd c->id: %U.\n", c->id);
		c->next = NULL;

		append_customer_to_waiting_list(c);
		DBG("Added customer %U to waiting list\n", c->id);
		party_sz[0]--;
	}
	DBG("New waiting_list count %U\n", get_waiting_list_size());
// #ifdef DEBUG
// 		print_customer_list(*c_list);
// #endif

	// search for vacant tables and seat customers
	while (FALSE == is_waiting_list_empty()) {

		// check for vacant table
		table_id = get_next_vacant_table();
		if (-1 == table_id) {
		    DBG("No vacant tables.\n");
			break;
		}
	    DBG("Next vacant table id: %U.\n", table_id);

		seats = get_seat_count_at_table(table_id);
	    DBG("Seats at table: %U.\n", seats);

	    // seat up to "seats" customers, so determine # of customers that 
	    // can be seated.
	    to_seat = get_waiting_list_size();
	    if (0 == to_seat) break;
	    if (seats < to_seat) {
	    	to_seat = seats;
	    }
	    DBG("%U customers will be seated.\n", to_seat);

		// make list having to_seat number of customers
		for (int idx = 0; idx < to_seat; idx++) {
			c = pop_customer_from_waiting_list();
			append_customer_to_list(&c_to_seat, c);
			DBG("Added customer %U to c_to_seat list\n", c->id);
		}

		// seat those customers
		if (SUCCESS != seat_customers_at_table(table_id, to_seat, &c_to_seat)) {
		    DBG("Failed to seat %U customers.\n", to_seat);
			return -1;
		}
		party_sz[0] += to_seat;
	}

	// send # customers seated
	SEND(STDOUT, (char *)party_sz, sizeof(unsigned char));
    DBG("%U customers seated.\n", party_sz[0]);

	return SUCCESS;
}

/**
 * Collect orders from all tables having Customers ready to order
 *
 * @return SUCCESS on success, else -1
 */
static char do_get_orders(void) {
	Order *o_array[TABLE_CNT + 1] = {0};
	Order *o = NULL;
	unsigned char order_count = 0;
	unsigned int ids[2] = {0};

	// loop through tables
	DBG("getting table orders\n");
	for (unsigned int table_id = 1; table_id <= TABLE_CNT; table_id++) {
		DBG("get orders for table %U\n", table_id);
		order_count += get_orders_from_table(table_id, &o_array[table_id]);
	}

	// send order count
	SEND(STDOUT, (char *)&order_count, sizeof(unsigned char));
	DBG("sending %U orders\n", order_count);

	// send orders
	for (unsigned int table_id = 1; table_id <= TABLE_CNT; table_id++) {
		o = pop_order_from_list(&o_array[table_id]);
		while (NULL != o) {
			ids[0] = o->t_id;
			ids[1] = o->c_id;
			DBG("sending order for customer %U from table %U\n", o->c_id, o->t_id);
			SEND(STDOUT, (char *)ids, sizeof(ids));

			// send ftype
			// send food item
			switch (o->ftype) {
				case APP_TYPE:
					DBG("sending appetizer...");
					SEND(STDOUT, (char *)o->item, sizeof(Appetizer) - sizeof(void *));
					DBG("done\n")
					break;
				case MEAL_TYPE:
					DBG("sending meal\n");
					SEND(STDOUT, (char *)o->item, sizeof(Meal) - sizeof(void *));
					DBG("done\n")
					break;
				case DES_TYPE:
					DBG("sending dessert\n");
					SEND(STDOUT, (char *)o->item, sizeof(Dessert) - sizeof(void *));
					DBG("done\n")
					break;
				default:
					DBG("invalid Order ftype\n");
					free(o);
					return -1;
			}
			free(o->item);
			free(o);
			o = pop_order_from_list(&o_array[table_id]);
		}
	}
	DBG("done sending orders\n");
	return SUCCESS;
}

/**
 * Collect prepared orders
 *
 * @return SUCCESS on success, else -1
 */
static char do_order_up(void) {
	Order *o_array[TABLE_CNT + 1] = {0};
	Order *o = NULL;
	Appetizer *a = NULL;
	Meal *m = NULL;
	Dessert *d = NULL;
	unsigned char order_count = 0;
	unsigned int ids[2] = {0};
	FoodTypes ft = 0;
	char ret = SUCCESS;
	char res = 0;

	// recv order count
	RECV(STDIN, (char *)&order_count, sizeof(unsigned char));
	DBG("receiving %U orders\n", order_count);

	// recv orders
	for (unsigned char idx = 0; idx < order_count; idx++) {
		o = malloc(sizeof(Order));
		MALLOC_OK(o);
		memset(o, '\x00', sizeof(Order));

		// recv t_id and c_id
		RECV(STDIN, (char *)ids, sizeof(ids));
		o->t_id = ids[0];
		o->c_id = ids[1];
		DBG("recv'd order for customer %U at table %U\n", o->c_id, o->t_id);

		// if t_id is not a valid t_id, then return -1
		if ((0 == o->t_id) || (TABLE_CNT < o->t_id)) {
			DBG("invalid Table ID %U\n", o->t_id);
			free(o);
			return -1;
		}

		// recv ftype
		ft = 0;
		RECV(STDIN, (char *)&ft, sizeof(FoodTypes));
		o->ftype = ft;

		// recv food item
		switch (o->ftype) {
			case APP_TYPE:
				DBG("receiving appetizer...\n");
				a = malloc(sizeof(Appetizer));
				MALLOC_OK(a);
				memset(a, '\x00', sizeof(Appetizer));
				a->ftype = APP_TYPE;
				RECV(STDIN, (char *)a->name, APP_NAME_SZ);
				DBG("received appetizer\n");
				print_appetizer(a);
				o->item = a;
				break;
			case MEAL_TYPE:
				DBG("receiving meal...\n");
				m = malloc(sizeof(Meal));
				MALLOC_OK(m);
				memset(m, '\x00', sizeof(Meal));
				m->ftype = MEAL_TYPE;
				RECV(STDIN, (char *)m->name, MEAL_NAME_SZ + MEAL_MAIN_SZ + MEAL_VEG_SZ + MEAL_SIDE_SZ);
				DBG("received meal\n");
				print_meal(m);
				o->item = m;
				break;
			case DES_TYPE:
				DBG("receiving dessert...\n");
				d = malloc(sizeof(Dessert));
				MALLOC_OK(d);
				memset(d, '\x00', sizeof(Dessert));
				d->ftype = DES_TYPE;
				RECV(STDIN, (char *)d->name, DES_NAME_SZ);
				DBG("received dessert\n");
				print_dessert(d);
				o->item = d;
				break;
			default:
				DBG("invalid Order ftype %U\n", o->ftype);
				free(o);
				return -1;
		}
		// Note: if forget to check if table_id is valid, can write Order pointers throughout the stack
		append_order_to_list(&o_array[o->t_id], o);
	}
	DBG("done recving orders\n");


	// loop through tables
	DBG("delivering orders to tables\n");
	for (unsigned int table_id = 1; table_id <= TABLE_CNT; table_id++) {
		DBG("delivering orders for table %U\n", table_id);
		res = deliver_orders_to_table(table_id, &o_array[table_id]);
		if (SUCCESS != res) {
			DBG("order delivery failed at table %U\n", table_id);
			ret++;
		} else {
			DBG("order delivery succeeded at table %U\n", table_id);			
		}
	}

	if (SUCCESS != ret) {
		return -1;
	} else {
		return ret;
	}
}

/**
 * Get the status of each table.
 *
 * Status of a table is one of the phases in TableStatus enum
 *
 * @return SUCCESS on success, else -1
 */
static char do_table_status(void) {
	unsigned int table_id;
	TableStatus all_ts[TABLE_CNT + 1] = {0};
	for (table_id = 1; table_id <= TABLE_CNT; table_id++) {
		all_ts[table_id] = get_status_of_table(table_id);
		DBG("got status of %U for table %U\n", all_ts[table_id], table_id);
	}

	for (table_id = 1; table_id <= TABLE_CNT; table_id++) {
		SEND(STDOUT, (char *)&all_ts[table_id], sizeof(TableStatus));
		DBG("reported status of %U for table %U\n", all_ts[table_id], table_id);
	}

	return SUCCESS;
}

/**
 * Clear and reset all tables where customers have finished eating.
 *
 * @return SUCCESS on success, else -1
 */
static char do_bus_tables(void) {
	unsigned char bus_cnt = 0;
	unsigned int table_id;
	// serach for tables with status FINISHED
	// have table clean and reset
	for (table_id = 1; table_id <= TABLE_CNT; table_id++) {
		if (FINISHED == get_status_of_table(table_id)) {
			clean_and_set_table(table_id);
			bus_cnt++;
		}
	}

	SEND(STDOUT, (char *)&bus_cnt, sizeof(unsigned char));

	return SUCCESS;
}

/**
 * Tell all tables to quit.
 *
 * @return -2 on success, else -1
 */
static char do_table_quit(void) {
	unsigned int table_id;
	int ret = SUCCESS;
	for (table_id = 1; table_id <= TABLE_CNT; table_id++) {
		ret = close_table(table_id);
		if (SUCCESS != ret) {
			return -1;
		}
	}
	return -2;
}

short process_cmd(void) {
    char cmd[5] = {0};
    short ret = 0;

    RECV(STDIN, cmd, sizeof(cmd)-1);
    DBG("recv'd cmd: %S.\n", cmd);
    if (0 == memcmp((void *)CMD_ADD_CUST, cmd, sizeof(CMD_ADD_CUST))) {
    	ret = do_add_customers();
    } else if (0 == memcmp((void *)CMD_GET_ORDERS, cmd, sizeof(CMD_GET_ORDERS))) {
    	ret = do_get_orders();
    } else if (0 == memcmp((void *)CMD_ORDER_UP, cmd, sizeof(CMD_ORDER_UP))) {
    	ret = do_order_up();
    } else if (0 == memcmp((void *)CMD_TABLE_STATUS, cmd, sizeof(CMD_TABLE_STATUS))) {
    	ret = do_table_status();
    } else if (0 == memcmp((void *)CMD_BUS_TABLES, cmd, sizeof(CMD_BUS_TABLES))) {
    	ret = do_bus_tables();
    } else if (0 == memcmp((void *)CMD_QUIT, cmd, sizeof(CMD_QUIT))) {
    	ret = do_table_quit();
    } else {
    	ret = -1;
    }

	return ret;
}
