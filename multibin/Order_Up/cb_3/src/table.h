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

#ifndef TABLE_H
#define TABLE_H 1

#define TABLE_ID 			 2
#define MIN_TABLE_SIZE 		 2
#define MAX_TABLE_SIZE 		10

#include "menu.h"
#include "customer.h"
#include "order.h"

typedef enum{
	VACANT = 0,
	APP_RTO = 1,	// RTO => ready to order
	APP_WAIT = 2,	// wait => waiting for order to be delivered
	MEAL_RTO = 3,
	MEAL_WAIT = 4,
	DES_RTO = 5,
	DES_WAIT = 6,
	FINISHED = 7,
	PHASES = 8,
} TableStatus;

typedef struct {
	unsigned int id;
	TableStatus status;
	unsigned char seats;
	Customer *customers;
} Table;


/**
 * Perform setup of the table.
 */
void table_setup(void);

/**
 * Remove all customers and set table to VACANT
 */
void table_clean_and_set(void);

/**
 * Get the number of seats at this table.
 *
 * @return Number of seats
 */
unsigned char get_seats_count(void);

/**
 * Get the status of the table.
 *
 * @return Current status
 */
TableStatus get_table_status(void);

/**
 * Seat a customer at this table.
 *
 * @param qty 		Quantity of customers to seat
 * @param c_list 	List of Customer's'
 * @return SUCCESS if seated ok, else -1 if error or all seats are full.
 */
int seat_customers(unsigned char qty, Customer *c_list);

/**
 * Take the order of each customer and append the order to the order list
 *
 * @param o_list 	List of orders (initially empty)
 * @return Number of orders added to the order list
 */
unsigned char take_customer_orders(Order **o_list);

/**
 * Deliver a set of orders to the customers at this table
 *
 * @param o_list 	List of orders
 * @return Number of orders NOT able to be delivered
 */
unsigned char deliver_customer_orders(Order **o_list);

#endif
