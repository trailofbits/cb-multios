#!/usr/bin/env python
from generator.actions import Actions

import itertools
import operator
import random
import re
import string
import struct
import sys

def rs(n=16):
    return ''.join([random.choice(string.letters) for _ in xrange(1, n + 1)])

def rls(_min=32, _max=256):
    return rs(random.choice(xrange(_min, _max + 1)))

def strtol(s):
    s = s.strip()
    if s[0] == '+':
        sign = 1
        s = s[1:]
    elif s[0] == '-':
        sign = -1
        s = s[1:]
    else:
        sign = 1

    numpart = ""
    for x in s:
        if x in string.digits:
            numpart = numpart + x
        else:
            break

    return sign * int(numpart)

class Machine(Actions):
    def start(self):
        self.state['store'] = {}

    def read_prompt(self):
        self.read(expect="hackdis> ", delim=' ')

    def choose_command(self):
        pass

    def auth(self):
        self.read_prompt()
        self.write("auth password\n")
        self.read(expect="auth ok\n", delim="\n")

    def append(self):
        try:
            key = random.choice(self.state['store'].keys())
        except IndexError:
            return
        app_val = rls(_max=32)

        self.read_prompt()
        self.write("append {} {}\n".format(key, app_val))
        try:
            self.state['store'][key] += app_val
        except TypeError:
            self.state['store'][key] = str(self.state['store'][key]) + app_val

        self.read(expect="{}\n".format(len(self.state['store'][key])), delim="\n")

        self.read_prompt()
        self.write("get {}\n".format(key))
        self.read(expect="val is \"{}\"\n".format(self.state['store'][key]), delim="\n")

    def bitcount(self):
        try:
            key = random.choice(self.state['store'].keys())
        except IndexError:
            return

        count = reduce(lambda acc, x: acc + x.count("1"),
                       map(bin, map(ord, str(self.state['store'][key]))), 0)

        self.read_prompt()
        self.write("bitcount {}\n".format(key))
        self.read(expect="{}\n".format(count), delim="\n")

    def bitop(self):
        try:
            k1 = random.choice(self.state['store'].keys())
            for _ in xrange(3):
                k2 = random.choice(self.state['store'].keys())
                if k1 != k2:
                    break
            else:
                return
        except IndexError:
            return

        act = random.choice(['and', 'or', 'xor', 'not'])
        opt = {
            'and': operator.and_,
            'xor': operator.xor,
            'or': operator.or_,
            'not': operator.invert,
        }
        op = opt[act]

        v1 = str(self.state['store'][k1])
        v2 = str(self.state['store'][k2])

        z = itertools.izip_longest(v1, v2, fillvalue='\x00')

        res = ""
        for a, b, in z:
            a, b = ord(a), ord(b)
            if op is operator.invert:
                res = res + chr(op(b) & 0xff)
            else:
                res = res + chr(op(a, b))

        self.read_prompt()
        self.write("bitop {} {} {}\n".format(act, k1, k2))
        self.read(delim='\n', expect='.*\n', expect_format='pcre')

    def decr(self):
        try:
            key = random.choice(self.state['store'].keys())
            if isinstance(self.state['store'][key], int):
                val = self.state['store'][key]
            else:
                val = strtol(self.state['store'][key])
        except ValueError:
            val = 0
        except IndexError:
            return

        val -= 1
        self.state['store'][key] = val

        self.read_prompt()
        self.write("decr {}\n".format(key))
        self.read(expect="num is {}\n".format(val), delim="\n")

        self.read_prompt()
        self.write("get {}\n".format(key))
        self.read(expect="val is \"{}\"\n".format(val), delim="\n")

    def dele(self):
        self.read_prompt()
        if self.chance(0.03) or not self.state['store']:
            key = rls()
            self.write("del {}\n".format(key))
            self.read(expect="0\n", delim="\n")
        else:
            key = random.choice(self.state['store'].keys())
            self.write("del {}\n".format(key))
            self.read(expect="1\n", delim="\n")
            self.state['store'].pop(key)
        self.read_prompt()
        self.write("get {}\n".format(key))
        self.read(expect="nil\n", delim="\n")


    def exists(self):
        self.read_prompt()
        key = rls()
        self.write("exists {}\n".format(key))
        if key in self.state['store']:
            self.read(expect="1\n", delim="\n")
        else:
            self.read(expect="0\n", delim="\n")

    def get(self):
        try:
            key = random.choice(self.state['store'].keys())
        except IndexError:
            return
        self.read_prompt()
        self.write("get {}\n".format(key))
        self.read(expect="val is \"{}\"\n".format(self.state['store'][key]), delim="\n")

    def incr(self):

        try:
            key = random.choice(self.state['store'].keys())
            if isinstance(self.state['store'][key], int):
                val = self.state['store'][key]
            else:
                val = strtol(self.state['store'][key])
        except ValueError:
            val = 0
        except IndexError:
            return

        val += 1
        self.state['store'][key] = val

        self.read_prompt()
        self.write("incr {}\n".format(key))
        self.read(expect="num is {}\n".format(val), delim="\n")

        self.read_prompt()
        self.write("get {}\n".format(key))
        self.read(expect="val is \"{}\"\n".format(val), delim="\n")

    def keys(self):
        if len(self.state['store']) == 0:
            self.read_prompt()
            self.write("keys\n")
            self.read(expect='empty\n', delim='\n')

    def rename(self):
        try:
            old_key = random.choice(self.state['store'].keys())
        except IndexError:
            return

        new_key = rls()

        if new_key == old_key:
            return

        self.state['store'][new_key] = self.state['store'].pop(old_key)

        self.read_prompt()
        self.write("rename {} {}\n".format(old_key, new_key))
        self.read(expect="1\n", delim="\n")

    def set(self):
        key = rls()
        val = rls(_max=64)

        self.read_prompt()
        self.write("set {} {}\n".format(key, val))
        if key in self.state['store']:
            self.read(expect="0\n", delim="\n")
            return
        else:
            self.state['store'][key] = val
            self.read(expect="1\n", delim="\n")

        self.read_prompt()
        self.write("get {}\n".format(key))
        self.read(expect="val is \"{}\"\n".format(self.state['store'][key]), delim="\n")

    def quit(self):
        self.read_prompt()
        self.write("quit\n")
        self.read(expect="bye\n", delim="\n")
