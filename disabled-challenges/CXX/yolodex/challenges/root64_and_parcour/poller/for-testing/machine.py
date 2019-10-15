#!/usr/bin/env python
from generator.actions import Actions, Variable
import random
import string
import math

def random_string(length, population=string.letters+string.digits):
    s = ''
    for x in xrange(length):
        s += random.choice(population)
    return s

def root64len(mode, s):
    if mode == 'decode':
        return int(math.floor( (len(s)) * 3.0 / 4))
    else:
        return int(math.ceil(len(s) / 3.0) * 4)

class Pttp(Actions):
    def start(self):
        self.state['has_token'] = False

    def hello(self):
        self.write('HELLO\n')
        token = Variable('token')
        token.set_re('OK ([0-9A-F]*)\n', group=1)
        self.read(delim='\n', assign=token)
        self.state['has_token'] = token

    def auth(self):
        if 'has_token' in self.state:
            self.write('AUTH ', self.state['has_token'], '\n')
            self.read(delim='\n', expect='OK\n')
        else:
            self.write('AUTH ' + random_string(random.randint(1, 10)) + '\n')
            self.read(delim='\n')

    def init_data(self):
        self.set_data()

    def init_mode(self):
        self.set_mode()

    def init_key(self):
        self.set_key()

    def initialized(self):
        pass

    def call_random(self):
        s = random_string(random.randint(5, 20))
        self.write('CALL ' + s + '\n')
        self.read(delim='\n', expect='ERROR 404\n')

    def call_home(self):
        self.write('CALL /\n')
        self.read(delim='\n', expect_format='pcre', expect="OK \d+\n")
        self.read(delim='\n', expect="Directory listing\n")
        self.read(delim='\n', expect_format='pcre',
                  expect="\t/ \(called \d+ times\)\t\tHome page\n")
        self.read(delim='\n', expect_format='pcre',
                  expect="\t/root64 \(called \d+ times\)\t\tRoot64 conversion tool\n")
        self.read(delim='\n', expect_format='pcre',
                  expect="\t/parcour \(called \d+ times\)\t\tParcour obfuscator\n")
        self.read(delim='\n', expect="\n")
    def call_root64(self):
        size = root64len(self.state['mode'], self.state['data'])
        self.write('CALL /root64\n')
        self.read(delim='\n', expect="OK %d\n" % size)
        if size > 0:
            self.read(length=size)

    def call_parcour(self):
        size = len(self.state['data'])
        self.write('CALL /parcour\n')
        self.read(delim='\n', expect_format='pcre', expect="OK \d+\n")
        if size > 0:
            self.read(length=size)

    def set_random(self):
        arg = random_string(random.randint(1, 32))
        val = random_string(random.randint(1, 32))
        self.write('SET {0} {1}\n'.format(arg, val))
        self.read(delim='\n', expect="OK\n")

    def set_mode(self):
        if random.randint(0,1):
            self.write('SET mode encode\n')
            self.state['mode'] = 'encode'
        else:
            self.write('SET mode decode\n')
            self.state['mode'] = 'decode'
        self.read(delim='\n', expect="OK\n")

    def set_data(self):
        data = random_string(random.randint(1, 127))
        self.write('SET data {0}\n'.format(data))
        self.read(delim='\n', expect="OK\n")
        self.state['data'] = data

    def set_key(self):
        key = random_string(random.randint(1, 127))
        self.write('SET key {0}\n'.format(key))
        self.read(delim='\n', expect="OK\n")
        self.state['key'] = key

    def bye(self):
        self.write('BYE\n')
        self.read(delim='\n', expect='BYE\n')
