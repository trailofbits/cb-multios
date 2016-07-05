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
extern "C" {
#include <string.h>
#include <stdlib.h>
};

#include "order.h"

Order::Order()
{
}

Order::~Order()
{
}

int Order::wait_time()
{
    size_t i = 0, wait_time = 0, wait_time_modifier = 1, prep_time = 0;
    size_t max_wait_time = pizzas[0]->get_prep_time();
    for (i = 0; i < pizzas.length(); i++) {
        prep_time = pizzas[i]->get_prep_time();
        wait_time += prep_time;

        if (max_wait_time < prep_time)
            max_wait_time = prep_time;
    }

    //Factor in wait time grows with larger orders, but not linearly
    wait_time_modifier += pizzas.length() / 5;
    printf("Pizza length... = %d\n", pizzas.length());
    return (wait_time + ((max_wait_time * wait_time_modifier) / pizzas.length()));
}

char *Order::get_name()
{
    return pickup_name;
}

bool Order::set_name(char *name)
{
    if (strlen(name) >= NAME_SIZE)
        return false;

    strcpy(pickup_name, name);
    return true;
}

bool Order::add_pizza(Pizza *pizza)
{
    return pizzas.add(pizza);
}

void Order::remove_pizza(size_t idx)
{
    Pizza *pizza = pizzas[idx];
    pizzas.remove(idx);
    delete pizza;
}

void Order::remove_all_pizzas()
{
    Pizza *pizza;

    while (pizzas.pop(pizza)) {
        delete pizza;
    }
}

Pizza *Order::get_pizza(size_t idx)
{
    if (idx >= pizzas.length())
        return NULL;

    return pizzas[idx];
}

int Order::get_num_pizzas()
{
    return pizzas.length();
}

void Order::print_order()
{
    int i, calories = 0, carbs = 0;
    printf("==================================================\n");
    for (i = 0; i < pizzas.length(); i++) {
        printf("  Item #%d. ", i+1);
        pizzas[i]->print_pizza();
        calories += pizzas[i]->get_calories();
        carbs += pizzas[i]->get_carbs();
    }
    printf("--------------------------------------\n");
    printf("\t\tCalories: %d\n", calories);
    printf("\t\tCarbs   : %d\n\n", carbs);
    printf("\t\tEstimated wait time: %d minute(s)\n", wait_time()/60);
    printf("==================================================\n");
}

