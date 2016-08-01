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
/**
 * @file stock.h
 *
 * Functions for manipulating stock and order structs.
 */

#ifndef STOCK_H_
#define STOCK_H_

#include "list.h"
#include "pool.h"

#define HASH_TABLE_NUM_BUCKETS 251
#define STOCK_NAME_MAX_LEN 4

enum order_type {
    BUY,
    SELL
};

typedef LIST_OF(struct order) order_list_t;
typedef LIST_OF(struct stock) stock_list_t;

struct stock;

// Type confusion
#ifdef PATCHED
enum object_type {
    ORDER,
    STOCK
};
#endif

struct order {
// Type confusion
#ifdef PATCHED
    enum object_type obj_type;
#else
    int dummy;
#endif
    void (*on_complete)(struct order *order);
    unsigned int id, price, quantity;
    LIST_ELEMS(struct order) global_list, stock_list;
    enum order_type type;
    struct stock *stock;
};

struct stock {
// Type confusion
#ifdef PATCHED
    enum object_type obj_type;
#else
    int dummy;
#endif
    char name[STOCK_NAME_MAX_LEN];
    unsigned int num_orders;
    LIST_ELEMS(struct stock) bucket_list, global_list;
    order_list_t buy_orders, sell_orders;
};

struct stock_state {
// Use after free
#ifdef PATCHED
    int stock_freed;
#endif
    struct pool stock_pool;
    stock_list_t stocks_list;
    order_list_t orders_list;
    stock_list_t stock_hash_table[HASH_TABLE_NUM_BUCKETS];
};

/**
 * Initialize a stock state struct.
 *
 * @param state The stock state struct
 */
void stock_init(struct stock_state *state);

/**
 * Destroy a stock state struct.
 *
 * @param state The stock state struct
 */
void stock_destroy(struct stock_state *state);

/**
 * Process a command to list all stocks, printing to stdout.
 *
 * @param state The stock state struct
 * @return 0 on success, -1 on failure
 */
int cmd_list_stocks(struct stock_state *state);

/**
 * Process a command to list all orders for a stock, printing to stdout.
 *
 * @param state The stock state struct
 * @param name The name of the stock to examine
 * @return 0 on success, -1 on failure
 */
int cmd_list_orders(const struct stock_state *state, const char *name);

/**
 * Process a command to place an order
 *
 * @param state The stock state struct
 * @param name The name of the stock to place an order for
 * @param type The type of the order (zero for buy, non-zero for sell)
 * @param quantity The quantity to order
 * @param price The price for each unit of the order
 * @return id of new order on success, -1 on failure
 */
int cmd_place_order(struct stock_state *state, const char *name, int type,
        unsigned int quantity, unsigned int price);

/**
 * Process a command to check the status of an order, printing to stdout.
 *
 * @param state The stock state struct
 * @param id The id of the order
 * @return 0 on success, -1 on failure
 */
int cmd_check_order(const struct stock_state *state, unsigned int id);

/**
 * Process a command to cancel an order.
 *
 * @param state The stock state struct
 * @param id The id of the order
 * @return 0 on success, -1 on failure
 */
int cmd_cancel_order(struct stock_state *state, unsigned int id);

#endif /* STOCK_H_ */
