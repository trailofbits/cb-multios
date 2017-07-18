#!/usr/bin/env python
from __future__ import division

from generator.actions import Actions

from numpy import int32, uint16

import copy
import math
import operator as op
import random
import re


def trace(fn):
    def wrapper(*args, **kwargs):
        fn(*args, **kwargs)
    return wrapper


class TemplateGenerator(Actions):
    line_regex = re.compile(r'(\d+):\s+(\d+)?')
    ERR_TOO_FEW_ARGS = "Error: Too few arguments for '{}' command"
    ERR_INVALID_INPUT = "Error: Invalid input"

    ADD_HISTORY = 1
    NO_HISTORY = 2

    class Stack(object):
        def __init__(self):
            self._storage = []

        def pop(self):
            return self._storage.pop()

        def peek(self,):
            return self._storage[-1]

        def push(self, value):
            return self._storage.append(value)

        def invert(self):
            self._storage.reverse()

        def __len__(self):
            return len(self._storage)

        def copy(self):
            return copy.deepcopy(self)

    class CalcStack(Stack):
        def pformat(self):
            height = max(len(self._storage), 80)
            padding = 80 - len(self._storage) if len(self._storage) < 80 else 0
            return [
                '{:03}:\t{}'.format(height - i - 1, v)
                for i, v in enumerate(
                    ([''] * padding) + self._storage
                )
            ]

    def _readln(self, s):
        return self.read(expect=s + '\n', delim='\n')

    def _writeln(self, s):
        return self.write(s + '\n')

    def _parse_calc(self):
        self.read(expect='\x1b[2J\x1b[H', length=len('\x1b[2J\x1b[H'))
        # s = '\n'.join([line for line in self.state['calc'].pformat()]) + '\n'
        # self.read(expect=s, length=len(s))
        for line in self.state['calc'].pformat():
            self._readln(line)

        if self.state['err']:
            self._readln(self.state['err'])
        else:
            self._readln('-' * 120)

    def start(self):
        #self.delay(100)
        self.state['calc'] = self.CalcStack()
        self.state['hist'] = self.Stack()
        self.state['err'] = ''
        self.state['ret'] = self.ADD_HISTORY
        self.state['prev_stack'] = self.state['calc'].copy()

        self.write(self.magic_page[:4])
        self.read(length=0x1000, expect=self.magic_page)

        for _ in xrange(8):
            self.command()
            self.implicit_push()

    def command(self):
        if not self.state['err'] and self.state['ret'] == self.ADD_HISTORY:
            self.state['hist'].push(self.state['prev_stack'])
        self.state['prev_stack'] = self.state['calc'].copy()

        self._parse_calc()

        self.state['err'] = ''
        self.state['ret'] = self.ADD_HISTORY

    def _ensure_n(self, cmd, n):
        if len(self.state['calc']) < n:
            self.state['err'] = self.ERR_TOO_FEW_ARGS.format(cmd)
            return False
        else:
            return True

    def _unop(self, name, oper):
        cmd = name
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        self.state['calc'].push(int32(oper(self.state['calc'].pop())))

    def _binop(self, name, oper, rev_args=False):
        cmd = name
        self._writeln(cmd)

        if not self._ensure_n(cmd, 2):
            return

        v1, v2 = self.state['calc'].pop(), self.state['calc'].pop()
        if rev_args:
            self.state['calc'].push(int32(oper(v2, v1)))
        else:
            self.state['calc'].push(int32(oper(v1, v2)))

    def implicit_push(self):
        value = int32(random.randint(-(2 ** 31), 2 ** 31 - 1))
        self._writeln(str(value))
        self.state['calc'].push(value)

    def explicit_push(self):
        value = int32(random.randint(-(2 ** 31), 2 ** 31 - 1))
        self._writeln("push {}".format(value))
        self.state['calc'].push(value)

    def add(self):
        self._binop('+', op.add)

    def sub(self):
        self._binop('-', op.sub, True)

    def mul(self):
        self._binop('*', op.mul)

    def div(self):
        cmd = '/'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 2):
            return

        v1, v2 = self.state['calc'].pop(), self.state['calc'].pop()
        if v1 == 0:
            self.state['err'] = self.ERR_INVALID_INPUT
            self.state['calc'].push(v2)
            self.state['calc'].push(v1)
            return

        self.state['calc'].push((int32(v2 / v1)))

    def fact(self):
        cmd = '!'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        v = self.state['calc'].pop()

        if v < 0 or v > 1000:
            self.state['err'] = self.ERR_INVALID_INPUT
            self.state['calc'].push(v)
            return

        r = int32(1)
        while v > 0:
            r = int32(r * int32(v))
            v -= 1
        self.state['calc'].push(r)

    def neg(self):
        self._unop('neg', op.neg)

    def abs(self):
        self._unop('abs', op.abs)

    def mod_(self):
        cmd = 'mod'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 2):
            return

        v1, v2 = self.state['calc'].pop(), self.state['calc'].pop()
        if v1 == 0:
            self.state['err'] = self.ERR_INVALID_INPUT
            self.state['calc'].push(v2)
            self.state['calc'].push(v1)
            return

        self.state['calc'].push((int32(math.fmod(int32(v2), int32(v1)))))

    def xor(self):
        self._binop('^', op.xor)

    def or_(self):
        self._binop('|', op.or_)

    def and_(self):
        self._binop('&', op.and_)

    def not_(self):
        self._unop('~', lambda x: int32(~x))

    def sum_(self):
        cmd = 'sum'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        n = self.state['calc'].pop()

        if len(self.state['calc']) < n or n < 0:
            self.state['err'] = self.ERR_TOO_FEW_ARGS.format(cmd)
            self.state['calc'].push(n)
            return

        s = int32(0)
        for _ in xrange(n):
            v = self.state['calc'].pop()
            s = int32(int32(s) + int32(v))

        self.state['calc'].push(s)

    def avg(self):
        cmd = 'avg'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        n = self.state['calc'].pop()
        if n == 0:
            self.state['err'] = self.ERR_INVALID_INPUT
            self.state['calc'].push(n)
            return

        if len(self.state['calc']) < n or n < 0:
            self.state['err'] = self.ERR_TOO_FEW_ARGS.format(cmd)
            self.state['calc'].push(n)
            return

        s = int32(0)
        for _ in xrange(n):
            v = self.state['calc'].pop()
            s = int32(int32(s) + int32(v))

        self.state['calc'].push(int32(s / n))

    def dup(self):
        cmd = 'dup'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        self.state['calc'].push(self.state['calc'].peek())

    def dupn(self):
        cmd = 'dupn'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        n = self.state['calc'].pop()

        if len(self.state['calc']) < n or n <= 0:
            self.state['err'] = self.ERR_TOO_FEW_ARGS.format(cmd)
            self.state['calc'].push(n)
            return

        if n > 0:
            self.state['calc']._storage.extend(self.state['calc']._storage[-n:])

    def dupr(self):
        cmd = 'dupr'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 2):
            return

        len_ = self.state['calc'].pop()
        pos = self.state['calc'].pop()

        if (
                len(self.state['calc']) < uint16(pos) or
                len(self.state['calc']) < uint16(len_) or
                len(self.state['calc']) < uint16(pos + len_)
        ):
            self.state['err'] = self.ERR_INVALID_INPUT
            self.state['calc'].push(pos)
            self.state['calc'].push(len_)
            return

        self.state['calc']._storage.extend(self.state['calc']._storage[-pos:-pos + len_])

        self.state['ret'] = self.NO_HISTORY

    def drop(self):
        cmd = 'drop'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        self.state['calc'].pop()

    def dropn(self):
        cmd = 'dropn'
        self._writeln(cmd)

        if not self._ensure_n(cmd, 1):
            return

        n = self.state['calc'].pop()

        if len(self.state['calc']) < n or n < 0:
            self.state['err'] = self.ERR_TOO_FEW_ARGS.format(cmd)
            self.state['calc'].push(n)
            return

        for _ in xrange(n):
            self.state['calc'].pop()

    def min(self):
        self._binop('min', min)

    def max(self):
        self._binop('max', max)

    def depth(self):
        cmd = 'depth'
        self._writeln(cmd)

        self.state['calc'].push(int32(len(self.state['calc'])))

    def invert(self):
        cmd = 'ivrt'
        self._writeln(cmd)

        self.state['calc'].invert()

    def undo(self):
        cmd = 'undo'
        self._writeln(cmd)

        if len(self.state['hist']) < 2:
            self.state['err'] = self.ERR_INVALID_INPUT
            return

        self.state['calc'] = self.state['hist'].pop()
        self.state['ret'] = self.NO_HISTORY

    def quit(self):
        self._writeln('quit')
        self._readln('Bye bye')
