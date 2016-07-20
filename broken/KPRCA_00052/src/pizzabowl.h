#ifndef PIZZABOWL_H_
#define PIZZABOWL_H_
#include "pizza.h"

class PizzaBowl: public Pizza {
private:
    bool side_of_bread;

public:
    PizzaBowl(bool _side_of_bread = false);
    virtual ~PizzaBowl();

    void add_side_of_bread();
    void remove_side_of_bread();

    virtual int get_calories();
    virtual int get_carbs();
    virtual int get_prep_time();
    virtual void print_pizza();
};

#endif
