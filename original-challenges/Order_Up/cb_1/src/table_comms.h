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
#ifndef TABLE_COMMS_H
#define TABLE_COMMS_H 1

#include "order.h"

#define TABLE_CNT 9
#define MASTER_TID 0
#define T_READ_FD(t_id) 	(((t_id * 2) + 3) + 1)
#define T_WRITE_FD(t_id) 	((t_id * 2) + 3)

// CMD values for table cbs
static const char T_CMD_SEAT_CUST[4] 			= {'\x5E','\xEE','\x5E','\xEE'};
static const char T_CMD_TAKE_ORDER[4] 			= {'\x04','\xDE','\x40','\x01'};
static const char T_CMD_DELIVER_ORDER[4] 		= {'\xDE','\x11','\x4E','\x40'};
static const char T_CMD_TABLE_SIZE[4] 			= {'\x51','\x4E','\x51','\x4E'};
static const char T_CMD_TABLE_STATUS[4] 		= {'\x51','\x3E','\x51','\x3E'};
static const char T_CMD_TABLE_CLEAN_SET[4]		= {'\xC1','\xEA','\x45','\x37'};
static const char T_CMD_QUIT[4] 				= {'\x0F','\xF0','\xFF','\x0F'};

/**
 * Find the next vacant table
 *
 * @return ID of table, else -1 if no vacancies
 */
char get_next_vacant_table(void);

/**
 * Find the number of seats at a table.
 *
 * @param table_id 	ID of table to query.
 * @return Number of seats
 */
char get_seat_count_at_table(unsigned int table_id);

/**
 * Seat a customer at table having id of table_id.
 *
 * @param table_id  ID of table where customer will be seated.
 * @param qty 		Quantity of customers to seat
 * @param c 		Pointer to a linked list of Customer's
 * @return SUCCESS if seated, -1 if all seats are full
 */
char seat_customers_at_table(unsigned int table_id, unsigned char qty, Customer **c);

/**
 * Close out the table and stop servicing it (quit)
 *
 * @param table_id 	ID of table to close out
 * @return SUCCESS if success, else -1
 */
char close_table(unsigned int table_id);

/**
 * Get status of one table
 *
 * @param table_id 	ID of table to query
 * @return Status of table
 */
TableStatus get_status_of_table(unsigned int table_id);

/**
 * Get the orders from one table
 *
 * @param table_id 	ID of table to query
 * @param o_list 	List to store orders
 * @return Number of orders received
 */
unsigned char get_orders_from_table(unsigned int table_id, Order **o_list);

/**
 * Deliver the orders to one table
 *
 * @param table_id 	ID of table to contact
 * @param o_list 	List of orders
 * @return SUCCESS if all customers at table receive orders, else -1
 */
char deliver_orders_to_table(unsigned int table_id, Order **o_list);

/**
 * Clean and set the table
 *
 * @param table_id 	ID of table
 * @return SUCCESS on success, else -1
 */
char clean_and_set_table(unsigned int table_id);

#endif


