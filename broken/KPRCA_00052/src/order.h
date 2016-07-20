#ifndef ORDER_H_
#define ORDER_H_

#include "pizza.h"
#include "list.h"

class Order
{
public:
    static const size_t NAME_SIZE = 32;
private:
    char pickup_name[NAME_SIZE];
    List<Pizza *> pizzas;
public:
    Order();
    ~Order();
    int wait_time();
    char *get_name();
    bool set_name(char *name);
    bool add_pizza(Pizza *pizza);
    void remove_pizza(size_t idx);
    void remove_all_pizzas();
    Pizza *get_pizza(size_t idx);
    int get_num_pizzas();
    void print_order();
};

#endif
