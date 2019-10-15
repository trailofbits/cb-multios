from generator.actions import Actions
import random
import string
import struct
import StringIO

def random_name(max_size=8, min_size=3):
    characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    fname = "".join(random.choice(characters) for c in range(max_size))
    lname = "".join(random.choice(characters) for c in range(max_size))
    fname = fname[0].upper() + fname[1:]
    lname = lname[0].upper() + lname[1:]
    return ''.join(fname) + ' ' + ''.join(lname)

class Topping():
    def __init__(self, name, calories, carbs, is_meat, has_pork):
        self.name = name
        self.calories = calories
        self.carbs = carbs
        self.is_meat = is_meat
        self.has_pork = has_pork

    def read_topping(self, _read, asterisk=True):
        _read(self.name)
        if (asterisk):
            if self.has_pork:
                _read("**")
            elif self.is_meat:
                _read("*")
        _read("\n");

cheeses = [
    Topping("Mozzarella", 460, 26, False, False),
    Topping("Cheddar", 330, 19, False, False),
    Topping("Parmesan", 280, 16, False, False),
    Topping("Monterey", 380, 21, False, False),
    Topping("Provolone", 350, 22, False, False),
    Topping("Romano", 250, 18, False, False)
    ]

meats = [
    Topping("Pepperoni", 222, 22, True, True),
    Topping("All beef pepperoni", 270, 12, True, False),
    Topping("Sausage", 350, 15, True, True),
    Topping("Chicken", 367, 29, True, False),
    Topping("Jerk Pork", 450, 45, True, True),
    Topping("Ground Beef", 150, 11, True, False)
    ]

veggies = [
    Topping("Mushrooms", 40, 6, False, False),
    Topping("Onions", 22, 7, False, False),
    Topping("Olives", 70, 11, False, False),
    Topping("Tomatoes", 30, 5, False, False),
    Topping("Green Peppers", 24, 3, False, False),
    Topping("Red Peppers", 28, 5, False, False),
    Topping("Spinach", 33, 4, False, False),
    Topping("Arugula", 37, 6, False, False)
    ]

sauces_ots = [
    Topping("Tomato", 222, 22, False, False),
    Topping("Balsamic", 270, 12, False, False),
    Topping("Italian", 350, 15, False, False),
    Topping("Ceasar", 367, 29, False, False),
    Topping("Ranch", 450, 45, False, False),
    Topping("Lite Italian", 150, 11, False, False),
    Topping("Lite Ceasar", 250, 20, False, False),
    Topping("Lite Ranch", 300, 30, False, False)
    ]

class Pizza():
    def __init__(self):
        self.toppings = []
        self.sauces = []
        self.calories = 0
        self.carbs = 0
        self.pizza_size = ""

    def set_pizzapie(self, size):
        self.prep_time = (18 *60)
        if (size == 1):
            self.calories = 1000
            self.carbs = 222
            self.pizza_size = "SMALL"
        elif (size == 2):
            self.calories = 1500
            self.carbs = 284
            self.pizza_size = "MEDIUM"
        elif (size == 3):
            self.calories = 2300
            self.carbs = 356
            self.pizza_size = "LARGE"
        self.pizza_text = ("Classic Pizza Pie, Size: %s\n" %  self.pizza_size)

    def set_pizzasub(self, size, bread_type):
        self.prep_time = (240)
        if (size == 1):
            self.calories = 900
            self.carbs = 222
            self.pizza_size = "6 Inch"
        elif (size == 2):
            self.calories = 1800
            self.carbs = 356
            self.pizza_size = "12 Inch"
        self.bread_text = "White" if bread_type == 1 else "Wheat"
        self.pizza_text = ("Pizza Sub, Size: %s %s\n" % (self.pizza_size, self.bread_text))

    def set_pizzabowl(self, side_of_bread):
        self.prep_time = (120)
        if (side_of_bread == 1):
            self.calories = 180
            self.carbs = 26
            self.bread_text = "Yep"
        else:
            self.bread_text = "Nah"
        self.pizza_text = ("The Famous Pizza Bowl. Bread on the side? - %s\n" % self.bread_text);

    def add_topping(self, topping, _read):
        if topping not in self.toppings:
            self.toppings.append(topping)
        _read("Added topping\n")

    def add_sauce(self, sauce, _read):
        self.sauces.append(sauce)
        _read("Added sauce\n")

    def read_toppings(self, _read):
        if not self.toppings:
            _read("\tNone\n")
            return
        for x in xrange(len(self.toppings)):
            _read("\t%d. " % (x+1))
            self.toppings[x].read_topping(_read, True)

    def read_sauces(self, _read):
        if not self.sauces:
            _read("\tNone\n")
            return

        for x in xrange(len(self.sauces)):
            _read("\t%d. " % (x+1))
            self.sauces[x].read_topping(_read, True)

    def read_pizza(self, _read):
        _read(self.pizza_text)
        _read("    Selected Toppings\n")
        self.read_toppings(_read);
        _read("    Sauce on the side\n")
        self.read_sauces(_read);

    def get_calories(self):
        calories = 0
        for topping in self.toppings:
            calories += topping.calories

        for sauce in self.sauces:
            calories += sauce.calories
        return calories + self.calories

    def get_carbs(self):
        carbs = 0
        for topping in self.toppings:
            carbs += topping.carbs

        for sauce in self.sauces:
            carbs += sauce.carbs
        return carbs + self.carbs

    def get_prep_time(self):
        return self.prep_time + len(self.toppings) * 30 + len(self.sauces) * 15

class Order():
    def __init__(self, pickup_name):
        self.pickup_name = pickup_name
        self.pizzas = []

    def add_pizza(self, pizza):
        self.pizzas.append(pizza)

    def wait_time(self, _read):
        i = 0
        wait_time = 0
        wait_time_modifier = 1
        prep_time = 0
        max_wait_time = self.pizzas[0].get_prep_time()
        for pizza in self.pizzas:
            prep_time = pizza.get_prep_time()
            wait_time += prep_time

            if (max_wait_time < prep_time):
                max_wait_time = prep_time

        wait_time_modifier += len(self.pizzas) / 5;
        _read("Pizza length... = %d\n" % len(self.pizzas))
        return (wait_time + ((max_wait_time * wait_time_modifier) / len(self.pizzas)))

    def read_order(self, _read):
        calories = 0
        carbs = 0
        _read("==================================================\n")
        for x in xrange(len(self.pizzas)):
            _read("  Item #%d. " % int(x+1))
            self.pizzas[x].read_pizza(_read)
            calories += self.pizzas[x].get_calories()
            carbs += self.pizzas[x].get_carbs()

        _read("--------------------------------------\n")
        _read("\t\tCalories: %d\n" % calories)
        _read("\t\tCarbs   : %d\n\n" % carbs)
        _read("\t\tEstimated wait time: %d minute(s)\n" % (self.wait_time(_read)/60))
        _read("==================================================\n")

class PizzaOrders(Actions):
    def _read(self, string):
        self.read(length=len(string), expect=string)

    def _read_toppings(self, toppings, tabs=False, has_asterisk=False):
        for x in xrange(len(toppings)):
            if tabs:
                self._read("\t")
            self._read("%d. " % (x+1))
            toppings[x].read_topping(self._read, has_asterisk)
            #%s\n" % (x+1, toppings[x].name))

    def _read_order_empty(self):
        if not self.orders or not len(self.orders):
            self._read("No orders have been inputted\n")
            return True
        return False

    def _read_single_order(self, x):
        self._read("%d - %s: Ordered %d pizza(s)\n" % (x+1, self.orders[x].pickup_name,
                                                        len(self.orders[x].pizzas)))
        self.orders[x].read_order(self._read)

    def _read_list_orders(self, full=False):
        if not full:
            self._read("0. Cancel\n")
        if not self.orders or not len(self.orders):
            return

        for x in xrange(len(self.orders)):
            self._read("%d - %s: Ordered %d pizza(s)\n" % (x+1, self.orders[x].pickup_name,
                                                            len(self.orders[x].pizzas)))
            if full:
                self.orders[x].read_order(self._read)

    def _add_pizza(self, order):
        pizza = Pizza()
        pizza_type = random.randint(1,3)

        self._read("Choose what the kind of pizza\n")
        self._read("1. Pizza Pie - The classic!\n")
        self._read("2. Pizza Sub - All the fun, on a bun\n")
        self._read("3. Pizza Bowl - Our own twist\n")
        self._read("Choice: ")
        if (pizza_type == 1):
            self.write("1\n")
            self._read("Select Size\n")
            self._read("1. Small\n")
            self._read("2. Medium\n")
            self._read("3. Large\n")
            self._read("Choice: ")

            size = random.randint(1,3)
            self.write("%d\n" % size)
            pizza.set_pizzapie(size)
            self._read("Successfully added a new Pizza Pie!\n")
        elif (pizza_type == 2):
            self.write("2\n")
            self._read("Select Size\n")
            self._read("1. 6 inch\n")
            self._read("2. 12 inch\n")
            self._read("Choice: ")
            size = random.randint(1,2)
            self.write("%d\n" % size)
            self._read("Select Bread Type\n")
            self._read("1. White\n")
            self._read("2. Wheat\n")
            self._read("Choice: ")
            bread_type = random.randint(1,2)
            self.write("%d\n" % bread_type)
            pizza.set_pizzasub(size, bread_type)
            self._read("Successfully added a new Pizza Sub!\n")
        elif (pizza_type == 3):
            self.write("3\n")
            self._read("Side of bread?\n")
            self._read("1. Yes\n")
            self._read("2. No\n")
            self._read("Choice: ")
            side_of_bread = random.randint(1,2)
            self.write("%d\n" % side_of_bread)
            pizza.set_pizzabowl(side_of_bread)
            self._read("Successfully added a new Pizza Bowl!\n")
        order.add_pizza(pizza)
        return pizza

    def start(self):
        self.orders = []
        self._read("Enter system password: ")
        self.write("pizzapass\n");
        self._read("\n")
        self._read("Welcome to the CGC Pizzeria order management system.\n")

    def main_menu(self):
        self._read("1. Input Order\n");
        self._read("2. Update Order\n");
        self._read("3. View One Orders\n");
        self._read("4. View All Orders\n");
        self._read("5. Delete Order\n");
        self._read("6. Clear All Orders\n");
        self._read("7. Logout\n");
        self._read("Choice: ");

    def input_order(self):
        self.write('1\n')
        order = Order(random_name())
        self.orders.append(order)
        self._read('Enter Pickup Name: ')
        self.write(order.pickup_name + '\n')
        self.state['pizza'] = self._add_pizza(order)
        self.state['order'] = order
        self.state['update'] = False

    def order_option_menu(self):
        self._read("Select an option:\n");
        self._read("1. Add Toppings\n");
        self._read("2. Remove Toppings\n");
        self._read("3. Add Sauce\n");
        self._read("4. Remove Sauce\n");
        self._read("5. Finished With Pizza\n");
        self._read("Choice: ");

    def add_topping(self):
        self.write('1\n')
        topping_type = 0
        topping = ''

        while topping_type != 4:
            self._read("Select topping type:\n")
            self._read("1. Cheese\n")
            self._read("2. Meat\n")
            self._read("3. Veggies\n")
            self._read("4. No More Toppings\n")
            self._read("Choice: ");

            topping_type = random.randint(1,4)
            self.write('%d\n' % (topping_type))
            if topping_type == 1:
                self._read_toppings(cheeses)
                self._read("Enter topping name: ")
                topping = cheeses[random.randint(0, len(cheeses) - 1)]
                self.write("%s\n" % topping.name)
            elif topping_type == 2:
                self._read_toppings(meats)
                self._read("Enter topping name: ")
                topping = meats[random.randint(0, len(meats) - 1)]
                self.write("%s\n" % topping.name)
            elif topping_type == 3:
                self._read_toppings(veggies)
                self._read("Enter topping name: ")
                topping = veggies[random.randint(0, len(veggies) - 1)]
                self.write("%s\n" % topping.name)
            else:
                continue
            self.state['pizza'].add_topping(topping, self._read)

    def remove_topping(self):
        self.write('2\n')
        toppings = self.state['pizza'].toppings
        while len(toppings):
            self._read("Toppings Added\n")
            self._read("\t0. Cancel\n")
            self._read_toppings(toppings, True, True)
            self._read("Choice: ")

            choice = random.randint(0, len(toppings))
            if (choice == 0):
                self.write('0\n')
                self._read('Finished removing toppings\n')
                break
            else:
                self.write('%d\n' % (choice))
                del self.state['pizza'].toppings[choice - 1]
                self._read("Removed Topping\n")

        if not len(toppings):
            self._read("No Toppings to remove\n")

    def add_sauce(self):
        self.write('3\n')
        sauce_type = 0

        while sauce_type != 2:
            self._read("Select an option:\n")
            self._read("1. Add Sauce\n")
            self._read("2. No More Sauces\n")
            self._read("Choice: ");
            sauce = ''

            sauce_type = random.randint(1,2)
            if sauce_type == 1:
                self.write('1\n')
                self._read_toppings(sauces_ots)
                self._read("Enter sauce name: ")
                sauce = sauces_ots[random.randint(0, len(sauces_ots) - 1)]
                self.write("%s\n" % sauce.name)
            else:
                self.write('2\n')
                continue
            self.state['pizza'].add_sauce(sauce, self._read)

    def remove_sauce(self):
        self.write('4\n')
        sauces = self.state['pizza'].sauces
        while len(sauces):
            self._read("Sauces on the side\n")
            self._read("\t0. Cancel\n")
            self._read_toppings(sauces, True, True)
            self._read("Choice: ")

            choice = random.randint(0, len(sauces))
            if (choice == 0):
                self.write('0\n')
                self._read('Finished removing sauces\n')
                break
            else:
                self.write('%d\n' % (choice))
                #del self.state['pizza'].sauces[choice - 1]
                del sauces[choice -1]
                self._read("Removed sauce\n")

        if not len(sauces):
            self._read("No sauces to remove\n")

    def finished_adding_pizza(self):
        self.write('5\n')
        self._read("Successfully added pizza!\n")
        self._read("1. Add another Pizza\n")
        self._read("2. Quit\n")
        if len(self.state['order'].pizzas) > 1:
            self._read("3. Remove Pizza from order\n")
        self._read("Choice: ");

    def add_another_pizza(self):
        self.write('1\n')
        self.state['pizza'] = self._add_pizza(self.state['order'])

    def quit_to_main_menu(self):
        self.write('2\n')
        if self.state['update']:
            self._read('Order successfully updated!\n')
        else:
            self._read('Order successfully added!\n')

    def update_order(self):
        return
        self._read_order_empty()
        _read_list_orders(self)
        self._read("Choice: ");
        orderlen = len(self.orders) if self.orders else 0
        choice = 0
        while choice != 2:
            choice = random.randint(0, orderlen)
            self.write('%d\n' % (topping_type))
            if (choice == 0):
                self._read('Canceled\n')
                break
            else:
                del self.state['pizza'].toppings[choice - 1]
                self._read("Removed Topping\n")

    def view_one_order(self):
        self.write('3\n')
        if self._read_order_empty():
            return
        self._read("View single Order\n")
        self._read_list_orders()
        self._read("Choice: ");
        choice = random.randint(0, len(self.orders) - 1)
        self.write("%d\n" % (choice))
        if (choice == 0):
            self._read('Canceled\n')
        else:
            self._read_single_order(choice - 1)
            self._read("*  = Contains Meat\n")
            self._read("** = Contains Pork\n")

    def view_all_orders(self):
        self.write('4\n')
        if self._read_order_empty():
            return

        self._read_list_orders(True)
        self._read("*  = Contains Meat\n")
        self._read("** = Contains Pork\n")

    def delete_order(self):
        self.write('5\n')
        if self._read_order_empty():
            return

        _read_list_orders(self)
        self._read("Choice: ");
        choice = random.randint(0, len(self.orders) - 1)
        if (choice == 0):
            self._read('Canceled\n')
        else:
            del self.orders[choice-1]


    def clear_all_orders(self):
        self.write('6\n')
        if self._read_order_empty():
            return

        self._read("Delete ALL Orders\n")
        self._read("0. Cancel\n")
        self._read("1. Confirm\n")
        self._read("Choice: ");
        choice = random.randint(0, len(self.orders) - 1)
        if (choice == 0):
            self._read('Canceled\n')
        else:
            self._read("Removing all orders\n")
            self.orders = []
            self._read("Cleared all previous orders\n")

    def logout(self):
        self.write('7\n')
        self.orders = []
        self._read("Logging out\n")

    def quit(self):
        self._read("Enter system password: ")
        self.write('quit\n')
        self._read("Received termination string\n")

