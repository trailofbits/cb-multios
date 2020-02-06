#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
from random import randint

import support as sp
from common import CONFIG

FOOD_TYPE = {
    'APP_TYPE': 0,
    'MEAL_TYPE': 1,
    'DES_TYPE': 2,
}

class Appetizer:
    def __init__(self, ftype='APP_TYPE', name=''):
        self.ftype = FOOD_TYPE[ftype]
        self.name = name

        if '' == self.name:
            self.name = sp.random_string(randint(1, CONFIG['APP_NAME_SZ'] - 1))

    def __str__(self):
        return "(name: {0})".format(self.name)

    def __repr__(self):
        return self.__str__()

class Meal:
    def __init__(self, ftype='MEAL_TYPE', name='', main='', veggie='', side=''):
        self.ftype = FOOD_TYPE[ftype]
        self.name = name
        self.main = main
        self.veggie = veggie
        self.side = side

        if '' == self.name:
            self.name = sp.random_string(randint(1, CONFIG['MEAL_NAME_SZ'] - 1))
        if '' == self.main:
            self.main = sp.random_string(randint(1, CONFIG['MEAL_MAIN_SZ'] - 1))
        if '' == self.veggie:
            self.veggie = sp.random_string(randint(1, CONFIG['MEAL_VEG_SZ'] - 1))
        if '' == self.side:
            self.side = sp.random_string(randint(1, CONFIG['MEAL_SIDE_SZ'] - 1))

    def __str__(self):
        return "(name: {0}, main: {1}, veggie: {2} side: {3})".format(self.name,
                                                                    self.main,
                                                                    self.veggie,
                                                                    self.side)

    def __repr__(self):
        return self.__str__()

class Dessert:
    def __init__(self, ftype='DES_TYPE', name=''):
        self.ftype = FOOD_TYPE[ftype]
        self.name = name

        if '' == self.name:
            self.name = sp.random_string(randint(1, CONFIG['DES_NAME_SZ'] - 1))

    def __str__(self):
        return "(name: {0})".format(self.name)

    def __repr__(self):
        return self.__str__()

class Menu:
    def __init__(self, appetizers=[], meals=[], desserts=[]):
        self.appetizers = appetizers
        self.meals = meals
        self.desserts = desserts

    def add_appetizer(self, appetizer):
        self.appetizers.append(item)

    def add_meal(self, meal):
        self.meals.append(item)

    def add_dessert(self, dessert):
        self.desserts.append(item)


    def __str__(self):
        return "barcode: {0}, model_num: {1}, cost: {2}\ndescription: {3}".format(self.barcode,
                                                                                self.model_num,
                                                                                self.cost,
                                                                                self.description)

    def __repr__(self):
        return self.__str__()
