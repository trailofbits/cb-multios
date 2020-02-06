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

#include "libcgc.h"
#include "cgc_libc.h"

#include "cgc_list.h"
#include "cgc_pool.h"
#include "cgc_stock.h"

// Improper validation of array index
#ifdef PATCHED
static unsigned int
#else
static int
#endif
cgc_strhash(const char *s, cgc_size_t n)
{
    int ret = 0;
    const unsigned char *p = NULL;

    for (p = (const unsigned char *)s; n-- && *p; p++)
        ret = (ret << 8) + *p;

    return ret;
}

static stock_list_t *
cgc_get_bucket(const struct stock_state *state, const char *name)
{
    return (stock_list_t *)&state->stock_hash_table[cgc_strhash(name,
            STOCK_NAME_MAX_LEN) % HASH_TABLE_NUM_BUCKETS];
}

static struct stock *
cgc_lookup_stock(const struct stock_state *state, const char *name)
{
    struct stock *cur = NULL;
    stock_list_t *bucket = cgc_get_bucket(state, name);

    LIST_FOR_EACH(bucket, bucket_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != STOCK)
            return NULL;
#endif

        if (cgc_strncmp(cur->name, name, STOCK_NAME_MAX_LEN) == 0)
            return cur;
    }

    return NULL;
}

static void
cgc_remove_stock(struct stock_state *state, struct stock *stock)
{
    stock_list_t *bucket = NULL;

// Type confusion
#ifdef PATCHED
    if (stock->obj_type != STOCK)
        return;
#endif

    bucket = cgc_get_bucket(state, stock->name);

// Use after free
#ifdef PATCHED
    state->stock_freed = 1;

    LIST_REMOVE(&state->stocks_list, global_list, stock);
#endif
    LIST_REMOVE(bucket, bucket_list, stock);

    cgc_pool_free(&state->stock_pool, stock);
}

static int
cgc_insert_stock(struct stock_state *state, const char *name)
{
    struct stock *new = NULL;
    stock_list_t *bucket = NULL;

    bucket = cgc_get_bucket(state, name);

    if ((new = cgc_pool_alloc(&state->stock_pool)) == NULL)
        return -1;

    LIST_INIT(&new->buy_orders);
    LIST_INIT(&new->sell_orders);
    LIST_ELEMS_INIT(&new->global_list);
    LIST_ELEMS_INIT(&new->bucket_list);

    LIST_PUSH_FRONT(&state->stocks_list, global_list, new);
    LIST_PUSH_FRONT(bucket, bucket_list, new);

// Type confusion
#ifdef PATCHED
    new->obj_type = STOCK;
#endif

// Buffer overflow
#ifdef PATCHED
    cgc_strncpy(new->name, name, STOCK_NAME_MAX_LEN);
#else
    cgc_strcpy(new->name, name);
#endif

    return 0;
}

static struct order *
cgc_lookup_order(const struct stock_state *state, unsigned int id)
{
// Dereference of untrusted pointer
#ifdef PATCHED
    struct order *cur = NULL;

    LIST_FOR_EACH(&state->orders_list, global_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != ORDER)
            return NULL;
#endif

        if (cur->id == id)
            return cur;
    }
    return NULL;
#else
    return (struct order *)id;
#endif
}

static void
cgc_remove_order(struct stock_state *state, struct order *order)
{
    order_list_t *stock_list = NULL;

// Type confusion
#ifdef PATCHED
    if (order->obj_type != ORDER)
        return;
#endif
    
    stock_list = order->type == BUY ?
        &order->stock->buy_orders :
        &order->stock->sell_orders;

    LIST_REMOVE(&state->orders_list, global_list, order);
    LIST_REMOVE(stock_list, stock_list, order);

    order->stock->num_orders--;

    if (order->stock->buy_orders.head == NULL &&
            order->stock->sell_orders.head == NULL) {
        cgc_remove_stock(state, order->stock);
    }

    if (order->quantity == 0)
        order->on_complete(order);
}

static int
cgc_order_cmp(const struct order *a, const struct order *b)
{
    if (a->price != b->price)
        return b->price - a->price;
    else
        return a->type == BUY ? b->id - a->id : a->id - b->id;
}

static void
cgc_on_complete(struct order *order)
{
    // Notify observers, talk to database, etc
#ifdef DEBUG
    fprintf(cgc_stdout, "Order %u complete!\n", order->id);
#endif
}

static int
cgc_match_order(struct stock_state *state, struct stock *stock, struct order *order)
{
    struct order *cur = NULL;
    unsigned int quantity = 0;

// Type confusion
#ifdef PATCHED
    if (order->obj_type != ORDER)
        return -1;
#endif

    if (order->type == BUY) {
        LIST_FOR_EACH_REVERSE(&stock->sell_orders, stock_list, cur) {
// Type confusion
#ifdef PATCHED
            if (cur->obj_type != ORDER)
                return -1;
#endif

            if (order->price >= cur->price) {
                quantity = MIN(order->quantity, cur->quantity);

                order->quantity -= quantity;
                cur->quantity -= quantity;

                if (cur->quantity == 0)
                    cgc_remove_order(state, cur);

                if (order->quantity == 0) {
                    cgc_remove_order(state, order);
                    break;
                }
            }
        }
    } else {
        LIST_FOR_EACH_REVERSE(&stock->buy_orders, stock_list, cur) {
// Type confusion
#ifdef PATCHED
            if (cur->obj_type != ORDER)
                return -1;
#endif

            if (order->price <= cur->price) {
                quantity = MIN(order->quantity, cur->quantity);

                order->quantity -= quantity;
                cur->quantity -= quantity;

                if (cur->quantity == 0)
                    cgc_remove_order(state, cur);

                if (order->quantity == 0) {
                    cgc_remove_order(state, order);
                    break;
                }
            }
        }
    }

    return order->quantity == 0 ? 0 : -1;
}

static unsigned int
cgc_get_next_id(struct stock_state *state, struct order *order)
{
    // Use pointer as value even in patched binary, should be unique once
    // allocated to an order and appears to be needed for the poller to work on
    // the patched binary
    return (unsigned int)order;
}

static int
cgc_insert_order(struct stock_state *state, const char *name, enum order_type type,
        unsigned int quantity, unsigned int price)
{
    struct order *new = NULL;
    struct order *cur = NULL;
    struct stock *stock = NULL;
    order_list_t *stock_list = NULL;

    if (cgc_strnlen(name, STOCK_NAME_MAX_LEN) == 0)
        return -1;

    if ((stock = cgc_lookup_stock(state, name)) == NULL &&
        cgc_insert_stock(state, name) != 0) {
        return -1;
    }

    if (stock == NULL && (stock = cgc_lookup_stock(state, name)) == NULL)
        return -1;

    if ((new = cgc_pool_alloc(&state->stock_pool)) == NULL)
        return -1;

// Type confusion
#ifdef PATCHED
    new->obj_type = ORDER;
#endif

    new->id = cgc_get_next_id(state, new);
    new->type = type;
    new->quantity = quantity;
    new->price = price;
    new->stock = stock;

    // Only one possible action to take for now
    new->on_complete = cgc_on_complete;

    LIST_ELEMS_INIT(&new->global_list);
    LIST_ELEMS_INIT(&new->stock_list);

    stock_list = type == BUY ? &stock->buy_orders : &stock->sell_orders;
    LIST_FOR_EACH(stock_list, stock_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != ORDER)
            return -1;
#endif

        if (cgc_order_cmp(cur, new) >= 0)
            break;
    }

    LIST_INSERT(stock_list, stock_list, cur, new);
    LIST_PUSH_FRONT(&state->orders_list, global_list, new);

    stock->num_orders++;

    if (cgc_match_order(state, stock, new) == 0)
        return 0;
 
    return new->id;
}

static void
cgc_order_to_str(const struct order *order, char *s)
{
    char intbuf[80] = {};
    cgc_strcpy(s, cgc_itoa(order->id, intbuf));

// Type confusion
#ifdef PATCHED
    if (order->obj_type != ORDER)
        return;
#endif

    if (order->type == BUY) {
        cgc_strcat(s, "\tBUY\t");
        cgc_strcat(s, cgc_itoa(order->quantity, intbuf));
        cgc_strcat(s, "\t");
        cgc_strcat(s, cgc_itoa(order->price, intbuf));
        cgc_strcat(s, "\t\t\t\n");
    } else {
        cgc_strcat(s, "\t\t\t");
        cgc_strcat(s, cgc_itoa(order->price, intbuf));
        cgc_strcat(s, "\t");
        cgc_strcat(s, cgc_itoa(order->quantity, intbuf));
        cgc_strcat(s, "\tSELL\n");
    }
}

int 
cgc_cmd_list_stocks(struct stock_state *state)
{
    cgc_size_t len = 0;
    struct stock *cur = NULL;
    struct stock *prev = NULL;
    char buf[5] = {};

// Need to emulate behavior of unpatched bin
#ifdef PATCHED
    if (state->stock_freed)
        return -1;
#endif

    LIST_FOR_EACH(&state->stocks_list, global_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != STOCK)
            return -1;
#endif

        if (cur->buy_orders.head == NULL &&
                cur->sell_orders.head == NULL) {
            cgc_remove_stock(state, cur);
            continue;
        }

        if (cur->global_list.prev != prev)
            return -1;

        prev = cur;
    }

    LIST_FOR_EACH(&state->stocks_list, global_list, cur) {
        len = cgc_strnlen(cur->name, STOCK_NAME_MAX_LEN);

        cgc_strncpy(buf, cur->name, len);
        buf[len++] = '\n';

        if (cgc_write_all(STDOUT, buf, len) != len)
            return -1;
    }

    return 0;
}

int
cgc_cmd_list_orders(const struct stock_state *state, const char *name)
{
    struct order *cur = NULL;
    struct stock *stock = NULL;
    cgc_size_t len = 0;
    char buf[200] = {};

    if ((stock = cgc_lookup_stock(state, name)) == NULL)
        return -1;

    cgc_strcpy(buf, "Order book for ");
    cgc_strncat(buf, stock->name, STOCK_NAME_MAX_LEN);
    cgc_strcat(buf, "\nID\tSIDE\tQTY\tPRICE\tQTY\tSIDE\n"); 

    len = cgc_strlen(buf);
    if (cgc_write_all(STDOUT, buf, len) != len)
        return -1;

    LIST_FOR_EACH(&stock->sell_orders, stock_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != ORDER)
            return -1;
#endif

        cgc_order_to_str(cur, buf);

        len = cgc_strlen(buf);
        if (cgc_write_all(STDOUT, buf, len) != len)
            return -1;
    }

    LIST_FOR_EACH(&stock->buy_orders, stock_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != ORDER)
            return -1;
#endif

        cgc_order_to_str(cur, buf);

        len = cgc_strlen(buf);
        if (cgc_write_all(STDOUT, buf, len) != len)
            return -1;
    }

    return 0;
}

int
cgc_cmd_place_order(struct stock_state *state, const char *name, int type,
        unsigned int quantity, unsigned int price)
{
    return cgc_insert_order(state, name, type == BUY ? BUY : SELL, quantity, price);
}

int
cgc_cmd_check_order(const struct stock_state *state, unsigned int id)
{
    struct order *order = NULL;
    cgc_size_t len = 0;
    char buf[200] = {};

    if ((order = cgc_lookup_order(state, id)) == NULL)
        return -1;

    // Sanity checking for our insane address->id scheme
    if (order->id != (unsigned int)order)
        return -1;

    cgc_order_to_str(order, buf);

    len = cgc_strlen(buf);
    if (cgc_write_all(STDOUT, buf, len) != len)
        return -1;

    return 0;
}

int
cgc_cmd_cancel_order(struct stock_state *state, unsigned int id)
{
    struct order *cur = NULL;

    LIST_FOR_EACH(&state->orders_list, global_list, cur) {
// Type confusion
#ifdef PATCHED
        if (cur->obj_type != ORDER)
            return -1;
#endif
        
        if (cur->id == id)
            break;
    }

    if (!cur)
        return -1;

    cgc_remove_order(state, cur);

    return 0;
}

void
cgc_stock_init(struct stock_state *state)
{
    cgc_size_t i = 0;
    cgc_size_t size = MAX(sizeof(struct order), sizeof(struct stock));

// Use after free
#ifdef PATCHED
    state->stock_freed = 0;
#endif

    cgc_pool_init(&state->stock_pool, size);
    LIST_INIT(&state->stocks_list);
    LIST_INIT(&state->orders_list);
    for (i = 0; i < HASH_TABLE_NUM_BUCKETS; i++)
        LIST_INIT(&state->stock_hash_table[i]);
}

void
cgc_stock_destroy(struct stock_state *state)
{
    struct order *cur = NULL;
    struct order *kill = NULL;

    // Removing all orders will also remove all stocks
    cur = state->orders_list.head;
    while (cur != NULL) {
        kill = cur;
        cur = cur->global_list.next;
        cgc_remove_order(state, kill);
    }

    cgc_pool_destroy(&state->stock_pool);
}

