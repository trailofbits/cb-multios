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

#ifndef ORDER_H
#define ORDER_H 1

#include "menu.h"

typedef struct {
	unsigned int t_id;
	unsigned int c_id;
	FoodTypes ftype;
	void *item;
	void *next;
} Order;


/**
 * Get the first order from the list
 *
 * @param o_list 	Pointer to list of Order's 
 * @return Pointer to first order or NULL if list is empty
 */
Order *pop_order_from_list(Order **o_list);

/**
 * Add a new order to the end of the list
 *
 * @param o_list 	List of Order's
 * @param o 		New Order
 */
void append_order_to_list(Order **o_list, Order *o);

/**
 * Count the number of order on the list
 *
 * @param o_list 	List of Order's
 * @return Number of Order
 */
unsigned char get_order_list_size(Order *o_list);

#endif