#ifndef PIZZAPIE_H_
#define PIZZAPIE_H_
#include "pizza.h"

class PizzaPie : public Pizza {
private:
    unsigned char pie_size;
    size_t pie_calories;
    size_t pie_carbs;
public:
    PizzaPie(unsigned char _pie_size);
    virtual ~PizzaPie();

    unsigned char get_pie_size();
    void set_pie_size(unsigned char _pie_size);

    virtual int get_calories();
    virtual int get_carbs();
    virtual int get_prep_time();
    virtual void print_pizza();
};

#endif
