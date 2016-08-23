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

#ifndef CUSTOMER_H
#define CUSTOMER_H 1

#include "menu.h"

typedef struct {
	unsigned int id;
	Appetizer a;
	Meal m;
	Dessert d;
	void *next;
} Customer;

/**
 * Get the first customer from the list
 *
 * @param c_list 	Pointer to list of Customer's 
 * @return Pointer to first customer or NULL if list is empty
 */
Customer *pop_customer_from_list(Customer **c_list);

/**
 * Add a new customer to the end of the list
 *
 * @param c_list 	List of Customer's
 * @param c 		New Customer
 */
void append_customer_to_list(Customer **c_list, Customer *c);

/**
 * Count the number of customers on the list
 *
 * @param c_list 	List of Customer's
 * @return Number of Customers
 */
unsigned char get_customer_list_size(Customer *c_list);

/**
 * Print out the customer list for debugging
 *
 * @param c_list 	List of Customer's
 */
void print_customer_list(Customer *c_list);

/**
 * Print the contents of a customer for debugging
 *
 * @param c 	Customer
 */
void print_customer(Customer *c);

#endif

