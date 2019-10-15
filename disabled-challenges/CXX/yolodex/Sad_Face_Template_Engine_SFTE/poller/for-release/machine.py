#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
import re

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class HashDict(object):
  def __init__(self):
    self.dic = dict()
    self.TABLE_SIZE = 256
    self.length = 0
    self.keys = list()

  def _hash(self, s):
    h = 5419
    for c in s:
      h = ((h << 5) + (h << 2) + h) + ord(c)
    return (h % self.TABLE_SIZE)

  def find(self, name):
    cur = self.dic.get(self._hash(name))
    if cur != None and len(cur) > 0:
      for x in cur:
        if x['name'] == name:
          return x['value']
    return None

  def insert(self, name, value):
    x = self.find(name)
    if x == None:
      x = dict()
      x['name'] = name
      x['value'] = value
      h = self._hash(name)
      if self.dic.get(h) == None:
        self.dic[h] = list()
      self.dic[h].insert(0, x)
      self.length += 1
      self.keys.append(name)

  def remove(self, name):
    h = self._hash(name)
    cur = self.dic.get(h)
    if cur != None and len(cur) > 0:
      for x in cur:
        if x['name'] == name:
          cur.remove(x)
          self.keys.remove(name)
          self.length -= 1
          return x

  def get(self, i):
    return self.dic.get(i)


class ASADFACE(Actions):

  def _var2str(self, var):
    var_type = var['type']
    var_value = var['value']
    if var_type == 0:
      return var_value
    elif var_type == 1:
      return '%d' % var_value
    elif var_type == 2:
      return '%.02f' % var_value
    else:
      return 'true' if var_value else 'false'

  def start(self):
    banner_str = '# Sad Face Template Engine - v0.1\n'
    self.read(length=len(banner_str), expect=banner_str)

    self.state['vars'] = HashDict()
    self.state['input'] = ''
    self.state['output'] = ''
    self.state['total_len'] = 0
    self.state['init'] = False

  def menu(self):
    if self.state['init']:
      self.read(length=len('\n'), expect='\n')
    self.state['init'] = True
    menu_str = '1. Define variables\n'
    menu_str += '2. View variables\n'
    menu_str += '3. Submit templated text\n'
    menu_str += '4. Render text\n'
    menu_str += '5. Quit\n'
    menu_str += '\n'
    self.read(length=len(menu_str), expect=menu_str)
    self.read(length=len('> '), expect='> ')

  def define_vars(self):
    self.write('1\n')
    delete_mode = random.choice([True, False])
    num_vars = random.randint(0, 5)

    self.read(length=len('-- Empty variable name will exit this menu\n'), expect='-- Empty variable name will exit this menu\n')
    self.read(length=len('-- Empty value will undefine the variable (if exists)\n'), expect='-- Empty value will undefine the variable (if exists)\n')

    for i in xrange(num_vars):
      self.read(length=len('var name: '), expect='var name: ')
      if delete_mode:
        if self.state['vars'].length == 0:
          self.write('\n')
          return
        var_name = random.choice(self.state['vars'].keys)
      else:
        while True:
          var_name = random_string()
          if var_name not in self.state['vars'].keys:
            break
      self.write('%s\n' % var_name)

      types_str = '-- Available types\n'
      types_str += '    0 - String (default)\n'
      types_str += '    1 - Integer\n'
      types_str += '    2 - Float\n'
      types_str += '    3 - Bool [true/false]\n'
      types_str += 'var type: '
      self.read(length=len(types_str), expect=types_str)
      var_type = random.choice([0, 1, 2, 3])
      self.write('%d\n' % var_type)

      self.read(length=len('var value: '), expect='var value: ')
      if delete_mode:
        self.write('\n')
        self.state['vars'].remove(var_name)
      else:
        if var_type == 0:
          var_value = random_string()
        elif var_type == 1:
          var_value = random.randint(-2147483648, 2147483647)
        elif var_type == 2:
          var_value = ((random.randint(-2147483648, 2147483647) - random.randint(-2147483648, 2147483647)) / 200000.0)
        else:
          var_value = random.choice([True, False])
        self.state['vars'].insert(var_name, { 'type': var_type, 'value': var_value })
        self.write(self._var2str(self.state['vars'].find(var_name)) + '\n')

    self.read(length=len('var name: '), expect='var name: ')
    self.write('\n')

  def view_vars(self):
    self.write('2\n')
    self.read(length=len('-- Current variables:\n'), expect='-- Current variables:\n')

    for i in xrange(self.state['vars'].TABLE_SIZE):
      cur = self.state['vars'].get(i)
      if cur:
        for x in cur:
          s = ' > %s : %s\n' % (x['name'], self._var2str(x['value']))
          self.read(length=len(s), expect=s)
    if self.state['vars'].length > 0:
      s = '-- Total %d variable(s)\n' % self.state['vars'].length
    else:
      s = '-- None\n'
    self.read(length=len(s), expect=s)

  def submit_text(self):
    self.write('3\n')
    self.state['input'] = ''
    self.state['total_len'] = 0
    self.read(length=len('-- Submit a null-terminated string\n'), expect='-- Submit a null-terminated string\n')
    s = ''
    num_things = random.randint(1, 50)
    for i in xrange(num_things):
      thing = random.choice(['normal', 'variable', 'section', 'comment'])
      if thing == 'comment':
        s += ':(#%s):' % random_string()
      elif thing == 'variable' and self.state['vars'].length > 0:
        name = random.choice(self.state['vars'].keys)
        var = self.state['vars'].find(name)
        s += ':(%s):' % name
        self.state['total_len'] += len(self._var2str(var))
      elif thing == 'section' and any((self.state['vars'].find(x))['type'] == 3 for x in self.state['vars'].keys):
        name = random.choice(filter(lambda x: (self.state['vars'].find(x))['type'] == 3, self.state['vars'].keys))
        var = self.state['vars'].find(name)
        rs = random_string()
        s += ':(@%s):' % name
        s += rs
        s += ':(/%s):' % name
        if var['value']:
          self.state['total_len'] += len(rs)
      else:
        rs = random_string()
        s += rs
        self.state['total_len'] += len(rs)

    self.state['input'] = s
    self.write(self.state['input'] + '\0')

  def render_text(self):
    self.write('4\n')
    self.state['output'] = self.state['input']
    for k in self.state['vars'].keys:
      v = self.state['vars'].find(k)
      if v['type'] == 3 and (':(@%s):' % k) in self.state['input']:
        if not v['value']:
          self.state['output'] = re.sub(':\(@%s\):.*?:\(/%s\):' % (k, k), '', self.state['output'])
        else:
          self.state['output'] = self.state['output'].replace(':(@%s):' % k, '')
          self.state['output'] = self.state['output'].replace(':(/%s):' % k, '')
      self.state['output'] = self.state['output'].replace(':(%s):' % k, self._var2str(v))
    self.state['output'] = re.sub(':\(@.*?\):.*?:\(/.*?\):', '', self.state['output'])
    self.state['output'] = re.sub(':\(.*?\):', '', self.state['output'])
    self.state['output'] = re.sub(':\(#.*?\):', '', self.state['output'])
    self.read(length=len('-- Render start.\n'), expect='-- Render start.\n')
    if len(self.state['output']) > 0:
      self.read(length=len(self.state['output']), expect=self.state['output'])
    s = '\n-- Render complete (%d bytes).\n' % len(self.state['output'])
    self.read(length=len(s), expect=s)

  def quit(self):
    self.write('5\n')
    self.read(length=len('# Bye.\n\n'), expect='# Bye.\n\n')

  def invalid(self):
    self.write('%d\n' % random.randint(6, 0xFFFFFFFF))
    self.read(length=len('Invalid menu. Try again.\n'), expect='Invalid menu. Try again.\n')
