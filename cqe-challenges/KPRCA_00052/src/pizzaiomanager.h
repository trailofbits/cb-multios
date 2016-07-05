#ifndef PIZZAIOMANAGER_H_
#define PIZZAIOMANAGER_H_

#include "pizza.h"
#include "iomanager.h"

class PizzaIoManager : public IoManager
{
private:
    Pizza *pizza;

    bool create_pizza_pie();
    bool create_pizza_sub();
    bool create_pizza_bowl();

    void add_toppings();
    void remove_toppings();
    void add_sauces();
    void remove_sauces();
public:
    PizzaIoManager(Pizza *_pizza=NULL);
    virtual ~PizzaIoManager();

    bool new_pizza();
    bool edit_pizza(Pizza *_pizza=NULL);
    Pizza *get_pizza();
};

#endif
