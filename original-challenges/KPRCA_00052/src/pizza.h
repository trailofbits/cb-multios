#ifndef PIZZA_H_
#define PIZZA_H_

extern "C"
{
#include <libcgc.h>
};

#include "list.h"
#include "topping.h"
#include "sauce.h"

enum { SMALL=1, MED=2, LG=3, SIXINCH=1, TWELVEINCH=2 };
enum { WHITE=1, WHEAT=2 };

class Pizza {
private:
    List<Topping *> toppings;
    List<Sauce *> sauce_ots; //ots = On the side
public:
    Pizza();
    virtual ~Pizza();
    bool add_topping(Topping *topping);
    bool remove_topping(size_t idx);
    bool add_sauce(Sauce *sauce);
    bool remove_sauce(size_t idx);
    void print_toppings();
    void print_sauces();
    size_t get_num_toppings();
    size_t get_num_sauces();
    virtual void print_pizza();

    virtual int get_calories() = 0;
    virtual int get_carbs() = 0;
    virtual int get_prep_time() = 0;
};

#endif
