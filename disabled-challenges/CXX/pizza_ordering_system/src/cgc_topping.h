#ifndef TOPPING_H_
#define TOPPING_H_

class Topping
{
protected:
    const char *name;
    int calories;
    int carbs;

public:
    virtual ~Topping();
    const char *get_topping_name() { return name; }
    int get_calories() { return calories; }
    int get_carbs() { return carbs; }

    bool operator==(const Topping &rhs) const;
    bool operator!=(const Topping &rhs) const;
    virtual bool is_vegetarian() = 0;
    virtual bool contains_pork() = 0;
};

#endif
