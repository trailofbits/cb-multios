#ifndef MEAT_H_
#define MEAT_H_
#include "topping.h"

class Meat : public Topping {
private:
    bool is_pork;
    Meat(const char *_name, int _calories, int _carbs, bool _is_pork);
public:
    virtual ~Meat();
    static Meat *add_meat(const char *meat_name);
    static void list_options();
    virtual bool is_vegetarian() { return false; }
    virtual bool contains_pork() { return is_pork; }
};

#endif
