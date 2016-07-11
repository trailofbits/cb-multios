#!/usr/bin/env python

from generator.actions import Actions
import random
import json
from json import encoder
import string
import struct
import sys
from collections import OrderedDict

MAX_DEPTH = 3
num_cats = 0
nyan_says = []
encoder.FLOAT_REPR = lambda o: format(o, '.2f')

p = lambda f,x: struct.pack(f,x)

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class RandomKTY(object):
  def integer(self):
    i = random.randint(0, 0xFFFFFFFF)
    i = 0x7FFFFFFF - i
    return i
  
  def string(self):
    return random_string(random.randint(1, 100))

  def double(self):
    a, b = self.integer(), self.integer()
    while b == 0:
      b = self.integer()
    d = (a * 1.0) / (b * 1.0)
    ds = '%.02f' % d
    return float(ds)

  def array(self, d=0):
    l = random.randint(0, 20)
    if d < MAX_DEPTH:
      return [ self.kty(d + 1) for i in xrange(l) ]
    else:
      return None

  def obj(self, depth=0):
    l = random.randint(0, 20)
    d = OrderedDict([ (self.string(), self.kty(depth + 1)) for i in xrange(l) ])
    if random.randint(1, 100) < 20:
      d['nyan_says'] = self.string()
      global nyan_says
      nyan_says.append(d['nyan_says'])
    return d

  def null(self):
    return None

  def boolean(self):
    return random.randint(0, 1) == 0

  def cat(self):
    global num_cats
    num_cats +=  1
    return '<<__CAT__>>'

  def kty(self, d=0):
    r = random.randint(0, 7)
    if d > MAX_DEPTH:
      r %= 5
    if r == 0:
      return self.integer()
    elif r == 1:
      return self.double()
    elif r == 2:
      return self.string()
    elif r == 3:
      if random.randint(1, 100) < 10:
        return self.cat()
      else:
        return self.kty(d)
    elif r == 4:
      return self.null()
    elif r == 5:
      return self.boolean()
    elif r == 6:
      return self.array(d)
    else:
      return self.obj(d)

class KTY(Actions):
  def start(self):
    welcome_str = 'KTY Pretty Printer v0.1\n'
    self.read(length=len(welcome_str), expect=welcome_str)
    self.num_jsons = random.randint(0, 10)
    self.state['kty'] = None
    self.state['loaded'] = False
    self.kty_gen = RandomKTY()
    menu_str ="""=======================
 1. Import KTY
 2. Print KTY
 3. Quit
=======================
"""
    self.read(length=len(menu_str), expect=menu_str)

  def option(self):
    pass

  def loads(self):
    global num_cats, nyan_says
    self.write('1\n')
    num_cats = 0
    nyan_says = []
    self.state['loaded'] = False
    self.state['kty'] = self.kty_gen.kty()
    kty = json.dumps(self.state['kty']).replace('"<<__CAT__>>"', '=^.^=')
    while len(kty) > 8192:
      num_cats = 0
      nyan_says = []
      self.state['kty'] = self.kty_gen.kty()
      kty = json.dumps(self.state['kty']).replace('"<<__CAT__>>"', '=^.^=')
    self.state['loaded'] = True
    self.write(kty + '\0')

  def dumps(self, nyan=False):
    global num_cats
    if not nyan:
      self.write('2\n')
    if not self.state['loaded']:
      self.read(length=len('Error!\n'), expect='Error!\n')
      return
    s = json.dumps(self.state['kty'], indent=2, separators=(',', ': ')).replace('"<<__CAT__>>"', '=^.^=')
    self.read(length=len(s), expect=s)

  def nyan(self):
    global num_cats
    self.write('777\n')
    self.dumps(True)
    nyan_cat = """

+      o     +              o
    +             o     +       +
o          +
    o  +           +        +
+        o     o       +        o
-_-_-_-_-_-_-_,------,      o
_-_-_-_-_-_-_-|   /\\_/\\
-_-_-_-_-_-_-~|__( ^ .^)  +     +
_-_-_-_-_-_-_-""  ""
+      o         o   +       o
    +         +
o        o         o      o     +
    o           +
+      +     o        o      +

"""
    if not self.state['loaded']:
      return
    if num_cats < 3:
      return
    self.read(length=len(nyan_cat), expect=nyan_cat)
    nyan_says_all = 'NYAN SAYS...\n"\n'
    global nyan_says
    for ns in nyan_says:
      nyan_says_all += ns
    nyan_says_all += '\n"'
    self.read(length=len(nyan_says_all), expect=nyan_says_all)

  def quit(self):
    self.write('3\n')
    self.read(length=len('\n\n=^.^=// Bye!\n\n'), expect='\n\n=^.^=// Bye!\n\n')

  def invalid_menu(self):
    while True:
      n = random.randint(0, 1000)
      if not (n == 1 or n == 2 or n == 3 or n == 777):
        break
    s = '%d\n' % n
    self.write(s)
    self.read(length=len('Invalid menu. Try again.\n'), expect='Invalid menu. Try again.\n')

