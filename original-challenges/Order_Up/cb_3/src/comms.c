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
#include "malloc.h"
#include "memcmp.h"

#include "table.h"
#include "customer.h"
#include "order.h"
#include "comms.h"

/**
 * Process command to seat a group of customers at this table.
 */
static void cmd_seat_customers_at_table(void) {
	int ret = 0;
	unsigned char to_seat = 0;
	Customer *c_list = NULL;
	Customer *c = NULL;

	// recv group size to_seat
	RECV(T_STDIN, (char *)&to_seat, sizeof(unsigned char));
	DBG("%U customer's to seat.\n", to_seat);

	for (unsigned char cnt = 0; cnt < to_seat; cnt++) {
		DBG("creating Customer\n");
		c = malloc(sizeof(Customer));
		MALLOC_OK(c);
		// recv customer id
		DBG("recv'ing Customer ID\n");
		RECV(T_STDIN, (char *)&c->id, sizeof(unsigned int));		
	    DBG("recv'd customer %U to seat\n", c->id);
	    append_customer_to_list(&c_list, c);
	    DBG("added customer %U to c_list.\n", c->id);
	}

	// seat at table
	ret = seat_customers(to_seat, c_list);

	if (SUCCESS == ret) {
		// send STATUS_OK msg
	    DBG("seated ok\n");
		send_status(STATUS_OK);		
	} else {
	    DBG("seats full\n");
		send_status(STATUS_ERR);
	}
}

/**
 * Process command to take the orders of all customers at this table.
 */
static void cmd_take_orders(void) {
	Order *o_list = NULL;
	Order *cur = NULL;
	unsigned char o_count = 0;

	o_count = take_customer_orders(&o_list);
	DBG("order count: %U\n", o_count);

	SEND(T_STDOUT, (char *)&o_count, sizeof(unsigned char));

	while(0 < o_count) {
		cur = pop_order_from_list(&o_list);
		if (NULL == cur) {
			DBG("missing an order in order list\n");
			break;
		}

		// send t_id
		DBG("send t_id: %U\n", cur->t_id);
		SEND(T_STDOUT, (char *)&cur->t_id, sizeof(unsigned int));

		// send c_id
		DBG("send c_id: %U\n", cur->c_id);
		SEND(T_STDOUT, (char *)&cur->c_id, sizeof(unsigned int));

		// send ftype
		// send food item
		switch (cur->ftype) {
			case APP_TYPE:
				DBG("sending appetizer\n");
				SEND(T_STDOUT, (char *)cur->item, sizeof(Appetizer) - sizeof(void *));
				break;
			case MEAL_TYPE:
				DBG("sending meal\n");
				SEND(T_STDOUT, (char *)cur->item, sizeof(Meal) - sizeof(void *));
				break;
			case DES_TYPE:
				DBG("sending dessert\n");
				SEND(T_STDOUT, (char *)cur->item, sizeof(Dessert) - sizeof(void *));
				break;
			default:
				DBG("invalid Order ftype\n");
		}

		o_count--;
	}
}

/**
 * Process command to deliver orders to all customers at this table.
 */
static void cmd_deliver_orders(void) {
	Order *o_list = NULL;
	Order *o = NULL;
	Appetizer *app = NULL;
	Meal *meal = NULL;
	Dessert *des = NULL;
	unsigned char ret = 0;
	unsigned char o_count = 0;

	// recv order_count
	RECV(T_STDIN, (char *)&o_count, sizeof(unsigned char));
	DBG("order count: %U\n", o_count);

	// recv_orders
	while (0 < o_count) {
		o = malloc(sizeof(Order));
		MALLOC_OK(o);
		memset(o, '\x00', sizeof(Order));

		o->t_id = TABLE_ID;
		// recv c->id
		RECV(T_STDIN, (char *)&o->c_id, sizeof(unsigned int));
		DBG("recv c_id: %U\n", o->c_id);

		// recv ftype
		RECV(T_STDIN, (char *)&o->ftype, sizeof(FoodTypes));
		DBG("recv ftype: %U\n", o->ftype);

		// recv food content
		switch (o->ftype) {
			case APP_TYPE:
				app = malloc(sizeof(Appetizer));
				MALLOC_OK(app);
				memset(app, '\x00', sizeof(Appetizer));
				app->ftype = o->ftype;
				DBG("receiving appetizer\n");
				RECV(T_STDIN, (char *)app->name, APP_NAME_SZ);
				DBG("received appetizer\n");
				print_appetizer(app);
				o->item = (void *)app;
				break;
			case MEAL_TYPE:
				meal = malloc(sizeof(Meal));
				MALLOC_OK(meal);
				memset(meal, '\x00', sizeof(Meal));
				meal->ftype = o->ftype;
				DBG("receiving meal\n");
				RECV(T_STDIN, (char *)meal->name, MEAL_NAME_SZ + MEAL_MAIN_SZ + MEAL_VEG_SZ + MEAL_SIDE_SZ);
				DBG("received meal\n");
				print_meal(meal);
				o->item = (void *)meal;
				break;
			case DES_TYPE:
				des = malloc(sizeof(Dessert));
				MALLOC_OK(des);
				memset(des, '\x00', sizeof(Dessert));
				des->ftype = o->ftype;
				DBG("receiving dessert\n");
				RECV(T_STDIN, (char *)des->name, DES_NAME_SZ);
				DBG("received dessert\n");
				print_dessert(des);
				o->item = (void *)des;
				break;
			default:
				DBG("invalid Order ftype\n");
				free(o);
				ret++;
		}
		append_order_to_list(&o_list, o);
		o_count--;
	}

	ret += deliver_customer_orders(&o_list);

	if (SUCCESS == ret) {
		// send STATUS_OK msg
	    DBG("orders delivered ok\n");
		send_status(STATUS_OK);		
	} else {
	    DBG("%U orders not delivered\n", ret);
		send_status(STATUS_ERR);
	}
}

/**
 * Process command querying this table's available seating
 */
static void cmd_get_seat_count_at_table(void) {
	unsigned char count = get_seats_count();
	// send count
    DBG("seat count: %U\n", count);
	SEND(T_STDOUT, (char *)&count, sizeof(unsigned char));
}

/**
 * Process cmd querying this table's status
 */
static void cmd_get_table_status(void) {
	TableStatus ts = get_table_status();
	// send table status
    DBG("table status is %U\n", ts);
	SEND(T_STDOUT, (char *)&ts, sizeof(TableStatus));
}

/**
 * Process command to clean and set this table
 */
static void cmd_clean_and_set_table(void) {
	// reset table to initial settings
	table_clean_and_set();
	send_status(STATUS_OK);
}

/**
 * Process command to quit.
 */
static void cmd_quit(void) {
	DBG("quitting\n");
	send_status(STATUS_OK);		
}

void send_status(const char *status_code) {
    SEND(T_STDOUT, status_code, 2);
}

short process_cmd(void) {
    char cmd[5] = {0};
    short ret = 0;

    DBG("recving cmd on fd: %U.\n", T_STDIN);
    RECV(T_STDIN, cmd, sizeof(cmd)-1);
    DBG("recv'd cmd: %S\n", cmd);
    if (0 == memcmp((void *)T_CMD_SEAT_CUST, cmd, sizeof(T_CMD_SEAT_CUST))) {
    	cmd_seat_customers_at_table();
    } else if (0 == memcmp((void *)T_CMD_TAKE_ORDER, cmd, sizeof(T_CMD_TAKE_ORDER))) {
    	cmd_take_orders();
    } else if (0 == memcmp((void *)T_CMD_DELIVER_ORDER, cmd, sizeof(T_CMD_DELIVER_ORDER))) {
    	cmd_deliver_orders();
    } else if (0 == memcmp((void *)T_CMD_TABLE_SIZE, cmd, sizeof(T_CMD_TABLE_SIZE))) {
    	cmd_get_seat_count_at_table();
    } else if (0 == memcmp((void *)T_CMD_TABLE_STATUS, cmd, sizeof(T_CMD_TABLE_STATUS))) {
    	cmd_get_table_status();
    } else if (0 == memcmp((void *)T_CMD_TABLE_CLEAN_SET, cmd, sizeof(T_CMD_TABLE_CLEAN_SET))) {
    	cmd_clean_and_set_table();
    } else if (0 == memcmp((void *)T_CMD_QUIT, cmd, sizeof(T_CMD_QUIT))) {
    	cmd_quit();
    	ret = -2;
    }

	return ret;
}



