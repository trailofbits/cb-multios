#ifndef VEGGIE_H_
#define VEGGIE_H_
#include "topping.h"

class Veggie : public Topping
{
private:
    Veggie(const char *_name, int _calories, int _carbs);
public:
    virtual ~Veggie();
    static Veggie *pick_veggie(const char *veggie_name);
    static void list_options();
    virtual bool is_vegetarian() { return true; }
    virtual bool contains_pork() { return false; }
};

#endif
