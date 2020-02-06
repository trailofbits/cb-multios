/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "cgc_orderiomanager.h"
#include "cgc_pizzaiomanager.h"

OrderIoManager::OrderIoManager()
{
}

OrderIoManager::~OrderIoManager()
{
}

void OrderIoManager::list_orders()
{
    int i = 0;
    for (i = 0; i < orders.length(); i++) {
        cgc_printf("%d - %s: Ordered %d pizza(s)\n", i+1, orders[i].get_name(), orders[i].get_num_pizzas());
    }
}

bool OrderIoManager::input_order(cgc_size_t idx)
{
    if (orders.is_full()) {
        cgc_printf("Maxed out orders\n");
        return false;
    }

    Order order;
    PizzaIoManager pim;
    Pizza *pizza;
    int choice;
    bool done_adding_pizzas = false;
    bool is_new_order = true;

    if (idx == -1) {
        cgc_printf("Enter Pickup Name: ");
        while (!readline(Order::NAME_SIZE)) {
            cgc_printf("Bad Pickup Name\n");
            cgc_printf("Enter Pickup Name: ");
        }

        if (!order.set_name(get_last_input()))
            return false;

        pim.new_pizza();
        pizza = pim.get_pizza();
        if (pizza)
            order.add_pizza(pizza);
    } else {
        is_new_order = false;
        order = orders[idx];
        cgc_printf("Editing order for %s\n", order.get_name());
    }

    while (!done_adding_pizzas) {
        cgc_printf("1. Add another Pizza\n");
        cgc_printf("2. Quit\n");
        if (order.get_num_pizzas() > 1)
            cgc_printf("3. Remove Pizza from order\n");

        while (true) {
            cgc_printf("Choice: ");
            choice = readnum();
            if (choice == 1) {
                pim.new_pizza();
                pizza = pim.get_pizza();
                if (pizza)
                    order.add_pizza(pizza);
                break;
            } else if (choice == 2) {
                done_adding_pizzas = true;
                break;
#ifdef PATCHED
            } else if (choice == 3 && order.get_num_pizzas() > 1) {
#else
            } else if (choice == 3) {
#endif
                cgc_printf("0. Cancel\n");
                order.print_order();
                cgc_printf("Choice: ");
                choice = readnum();
                if (choice == 0) {
                    cgc_printf("Canceled\n");
                    break;
                } else if (choice > order.get_num_pizzas()) {
                    cgc_printf("Bad Selection\n");
                } else {
                    order.remove_pizza(--choice);
                    cgc_printf("Removed Item #%d\n", choice+1);
                }
                break;
            } else {
                cgc_printf("Bad Selection\n");
            }
        }
    }

    if (is_new_order) {
        orders.add(order);
        cgc_printf("Order successfully added!\n");
    } else {
        orders[idx] = order;
        cgc_printf("Order successfully updated!\n");
    }
    return true;
}

bool OrderIoManager::update_order()
{
    Order my_order;
    int choice;

    if (orders.is_empty()) {
        cgc_printf("No orders have been inputted\n");
        return false;
    }

    cgc_printf("Update an Order\n");
    cgc_printf("0. Cancel\n");
    list_orders();
    cgc_printf("Choice: ");
    choice = readnum();
    if (choice == 0) {
        cgc_printf("Canceled\n");
        return false;
    } else if (choice > orders.length()) {
        cgc_printf("Bad Selection\n");
        return false;
    }

    return input_order(--choice);
}

bool OrderIoManager::delete_order()
{
    Order my_order;
    int choice;

    if (orders.is_empty()) {
        cgc_printf("No orders have been inputted\n");
        return false;
    }

    cgc_printf("Delete an Order\n");
    cgc_printf("0. Cancel\n");
    list_orders();
    cgc_printf("Choice: ");
    choice = readnum();
    if (choice == 0) {
        cgc_printf("Canceled\n");
        return false;
    } else if (choice < 1 || choice > orders.length()) {
        cgc_printf("Bad Selection\n");
        return false;
    }

    orders[--choice].remove_all_pizzas();
    return orders.remove(choice);
}

void OrderIoManager::clear_all_orders(bool force)
{
    Order order;
    int choice;

    if (!force) {
        cgc_printf("Delete ALL Orders\n");
        cgc_printf("0. Cancel\n");
        cgc_printf("1. Confirm\n");
        cgc_printf("Choice: ");
        choice = readnum();
        if (choice == 0) {
            cgc_printf("Canceled\n");
            return;
        } else if (choice > 1) {
            cgc_printf("Bad Selection\n");
        }

        cgc_printf("Removing all orders\n");
    }

    while(orders.pop(order)) {
        order.remove_all_pizzas();
    }
}


bool OrderIoManager::view_single_order()
{
    Order my_order;
    int choice, i;

    if (orders.is_empty()) {
        cgc_printf("No orders have been inputted\n");
        return false;
    }

    cgc_printf("View single Order\n");
    cgc_printf("0. Cancel\n");
    list_orders();
    cgc_printf("Choice: ");
    choice = readnum();
    if (choice == 0) {
        cgc_printf("Canceled\n");
        return false;
    } else if (choice > orders.length()) {
        cgc_printf("Bad Selection\n");
        return false;
    }

    i = --choice;
    cgc_printf("%d - %s: Ordered %d pizza(s)\n", i+1, orders[i].get_name(), orders[i].get_num_pizzas());
    orders[i].print_order();
    cgc_printf("*  = Contains Meat\n");
    cgc_printf("** = Contains Pork\n");
    return true;
}

void OrderIoManager::print_orders()
{
    int i = 0;

    if (orders.is_empty()) {
        cgc_printf("No orders have been inputted\n");
        return;
    }

    for (i = 0; i < orders.length(); i++) {
        cgc_printf("%d - %s: Ordered %d pizza(s)\n", i+1, orders[i].get_name(), orders[i].get_num_pizzas());
        orders[i].print_order();
    }
    cgc_printf("*  = Contains Meat\n");
    cgc_printf("** = Contains Pork\n");
}
