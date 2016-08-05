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

typedef char __attribute__((regparm(2))) (*f_inspect)(void *, unsigned int);

typedef struct {
	unsigned int id;
	Appetizer a;
	Meal m;
	Dessert d;
	f_inspect fi;
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
 * Search list of customers to find the one having c_id
 *
 * @param c_list 	List of Customers
 * @param c_id 		Customer ID
 * @return Pointer to Customer if found, else NULL
 */
Customer *get_customer_by_id(Customer *c_list, unsigned int c_id);

/**
 * Remove all customers from customer list
 * 
 * @param c_list 	Customer List
 */
void clear_customer_list(Customer **c_list);

/**
 * Select an appetizer from the menu
 *
 * @param m 	Menu
 * @param c 	Customer
 * @return Pointer to appetizer
 */
Appetizer *select_appetizer(Appetizer *a_list, Customer *c);

/**
 * Select an meal from the menu
 *
 * @param m 	Menu
 * @param c 	Customer
 * @return Pointer to meal
 */
Meal *select_meal(Meal *m_list, Customer *c);

/**
 * Select an dessert from the menu
 *
 * @param m 	Menu
 * @param c 	Customer
 * @return Pointer to dessert
 */
Dessert *select_dessert(Dessert *d_list, Customer *c);

/**
 * Accept a plate of food
 *
 * @param food 		Food for Customer
 * @param buf 		Customer buffer to store food
 * @param bufsz 	Size of buf
 */
void accept_food(void *food, void *buf, unsigned int bufsz);

/**
 * The customer will inspect the Appetizer when it is delivered.
 *
 * @param a 	Appetizer
 * @return SUCCESS on success, else -1
 */
char __attribute__((regparm(2))) inspect_appetizer(void *a, unsigned int cid);

/**
 * The customer will inspect the Meal when it is delivered.
 *
 * @param m 	Meal
 * @return SUCCESS on success, else -1
 */
char __attribute__((regparm(2))) inspect_meal(void *m, unsigned int cid);

/**
 * The customer will inspect the Dessert when it is delivered.
 *
 * @param d 	Dessert
 * @return SUCCESS on success, else -1
 */
char __attribute__((regparm(2))) inspect_dessert(void *d, unsigned int cid);

/**
 * Print the contents of a customer for debugging
 *
 * @param c 	Customer
 */
void print_customer(Customer *c);

#endif