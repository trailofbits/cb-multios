#ifndef PIZZASUB_H_
#define PIZZASUB_H_
#include "pizza.h"

class PizzaSub: public Pizza {
private:
    unsigned char sub_size;
    unsigned char bread_type;

    size_t sub_calories;
    size_t sub_carbs;
public:
    PizzaSub(unsigned char _sub_size, unsigned char _bread_type);
    virtual ~PizzaSub();

    void choose_white_bread();
    void choose_wheat_bread();
    unsigned char get_sub_size();
    void set_sub_size(unsigned char _sub_size);

    virtual int get_calories();
    virtual int get_carbs();
    virtual int get_prep_time();
    virtual void print_pizza();
};

#endif
