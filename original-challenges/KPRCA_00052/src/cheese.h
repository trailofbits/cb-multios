#ifndef CHEESE_H_
#define CHEESE_H_
#include "topping.h"

class Cheese : public Topping {
private:
    Cheese(const char *_name, int _calories, int _carbs);
public:
    virtual ~Cheese();
    static Cheese *select_cheese(const char *cheese_name);
    static void list_options();
    virtual bool is_vegetarian() { return true; }
    virtual bool contains_pork() { return false; }
};

#endif
