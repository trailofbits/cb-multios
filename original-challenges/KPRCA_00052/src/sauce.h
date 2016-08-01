#ifndef SAUCE_H_
#define SAUCE_H_
#include "topping.h"

class Sauce : public Topping {
private:
    Sauce(const char *_name, int _calories, int _carbs);
public:
    virtual ~Sauce();
    static Sauce *pour_sauce(const char *sauce_name);
    static void list_options();
    virtual bool is_vegetarian() { return true; }
    virtual bool contains_pork() { return false; }
};

#endif
