#!/usr/bin/env python

import math
import random
import string
import sys

from generator.actions import Actions
from struct import pack

def random_name():
    characters = string.letters + "'"
    max_size = random.randint(1,31)
    return ''.join(random.choice(characters) for c in range(max_size))

class Machine(Actions):
    def start(self):
        self.state['items'] = {
            "Apple": (10, 1.10),
            "Banana": (25, 0.30),
            "Orange": (10, 1.20),
            "Computer": (1, 1000.00)
        }
        self.read(delim='\n', expect='Welcome to eCommerce v0.1\n')
    
    def menu(self):
        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='Please make a selection:\n')
        self.read(delim='\n', expect='\ta) List products\n')
        self.read(delim='\n', expect='\tb) Buy a product\n')
        self.read(delim='\n', expect='\tc) Sell a product\n')

    def buy(self):
        if len(self.state['items']) == 0:
            self.write('f')
            self.read(delim='\n', expect='Invalid selection\n')
            return
        k, v = random.choice(self.state['items'].items())
        count, cost = v
        self.write('b')
        self.write('%s\n' % k)
        if count == 1:
            del self.state['items'][k]
        else:
            self.state['items'][k] = (count-1, cost)

    def list(self):
        self.write('a')
        for k, v in sorted(self.state['items'].items()):
            self.read(delim='\n', expect='%s (Price: %.02f, Count: %d)\n' % (
                k, v[1], v[0]))

    def sell(self):
        if len(self.state['items']) > 20:
            self.write('f')
            self.read(delim='\n', expect='Invalid selection\n')
            return
        self.write('c')
        name = random_name()
        count = random.randint(1,20)
        cost = random.randint(10, 100000)
        self.state['items'][name] = (count, float(cost)/100)
        self.write('%s\n%d\n%d\n' % (name, cost, count))

    def end(self):
        pass
