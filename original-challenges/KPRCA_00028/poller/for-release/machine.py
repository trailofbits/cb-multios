#!/usr/bin/env python

from __future__ import print_function
from functools import partial
from generator.actions import Actions
import copy
import inspect
import random
import string
import sys

class SLURUser(Actions):
    WELCOME = "Welcome to the SLUR REPL. Type an expression to evaluate it.\n"
    REPL = '> '
    SS = list(set(string.lowercase))

    # Nodes
    def start(self):
        self.state['prog'] = ''
        self.state['elems'] = []

    def emit(self, s):
        self.state['prog'] += s
        self.write(s)

    def read_intro(self):
        self.read(length=len(self.WELCOME), expect=self.WELCOME)

    def read_repl(self):
        self.read(length=len(self.REPL), expect=self.REPL)

    def pick_elements(self):
        pass

    def pick_quote(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_car(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_cdr(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_cons(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_equal(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_atom(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_cond(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def pick_lambda(self):
        self.state['elems'].append(inspect.stack()[0][3].split('_')[1])

    def produce(self):
        self.emit('( ')
        for elem in self.state['elems']:
            f = getattr(self, 'gen_' + elem)
            self.emit(f())
        self.emit(' )\n')
        sm = SLURMachine()
        ex = sm.run(self.state['prog'])
        self.read(length=len(ex), expect=ex)

    # Util
    def rs(self, l=6):
        return ''.join(random.choice(self.SS) for _ in xrange(l))

    def random_list(self):
        s = '('
        for i in xrange(random.randint(1, 3)):
            if self.chance(0.05):
                s += self.random_list()
            s += self.rs() + ' '
        s += ')'

        return s

    # Generators
    def gen_quote(self):
        s = ' (quote '
        if self.chance(0.5):
            s += self.rs()
        else:
            s += self.random_list()
        s += ' ) '
        return s

    def gen_car(self):
        s = ' (car '
        if self.chance(0.05):
            s += self.rs()
        else:
            s += self.random_list()
        s += ' ) '
        return s

    def gen_cdr(self):
        s = ' (cdr '
        if self.chance(0.05):
            s += self.rs()
        else:
            s += self.random_list()
        s += ' ) '
        return s

    def gen_cons(self):
        s = ' (cons '

        if self.chance(0.5):
            s += self.rs()
        else:
            s += self.random_list()

        if self.chance(0.05):
            s += self.rs()
        else:
            s += self.random_list()

        s += ' ) '
        return s

    def gen_random(self):
        x = random.choice([
            self.gen_quote,
            self.gen_car,
            self.gen_cdr,
            self.gen_cons,
            self.gen_equal,
            self.gen_atom,
        ])

        if self.chance(0.02):
            x = self.gen_cond

        return x()

    def gen_equal(self):
        e1 = self.gen_random()
        if self.chance(0.5):
            e2 = e1
        else:
            e2 = self.gen_random()

        if self.chance(0.95):
            s = ' ( equal {} {} ) '.format(e1, e2)
        else:
            s = '(equal '
            for _ in xrange(random.randint(0, 4)):
                s += random.choice([e1, e2])
            s += ' ) '

        return s

    def gen_atom(self):
        s = ' (atom '
        if self.chance(0.75):
            s +=  self.rs()
        else:
            s += self.random_list()
        s += ' ) '
        return s

    def gen_cond(self):
        s = ' (cond '
        for _ in xrange(0, 4):
            p = self.gen_random()
            e = self.gen_random()
            s += ' ( {} {} ) '.format(p, e)
        s += ' ) '

        return s

    def gen_lambda(self):
        kw = ['cons', 'lambda', 'cond', 'quote', 'atom', 'lambda', 'car', 'cdr', 'equal', ')', '(']
        vs = [self.rs(8) for _ in xrange(random.randint(0, 12))]
        e = self.gen_random()
        toks = filter(None,
                      e.replace('(', ' ( ').replace(')', ' ) ').split(' '))

        for i in xrange(len(toks)):
            if toks[i] in kw:
                continue

            if self.chance(0.1):
                if len(vs):
                    toks[i] = random.choice(vs)

        s = ' ((lambda ( ' + ' '.join(vs) + ' ) ' + e + ' ) '
        cnt = len(vs)
        if self.chance(0.01):
            cnt += random.randint(-1, 3)
            if cnt < 0:
                cnt = 0

        for _ in xrange(cnt):
            s += self.gen_atom()

        s += ' ) '
        return s


class Atom(object):
    def __init__(self, n):
        self.name = n

class Cons(object):
    def __init__(self, e=None):
        self.car = e
        self.cdr = None

    def __getitem__(self, i):
        x = self
        try:
            for _ in xrange(i):
                x = x.cdr
            return x.car
        except AttributeError:
            return None

    def conz(self, e1, e2):
        self.car = e1
        self.cdr = e2

    def append(self, e):
        c = self
        while c is not None and c.cdr is not None:
            c = c.cdr

        if c.car is None:
            c.car = e
            c.cdr = None
            return
        else:
            c.cdr = Cons(e)

class Lambda(object):
    def __init__(self, bnd, exp):
        self.bnd = bnd
        self.exp = exp

class SLURMachine(object):
    UB_ERROR = "Expression too long or unbalanced, try again."
    EV_ERROR = "Error evaluating expression."

    def CONSP(self, x):
        return isinstance(x, Cons)

    def ATOMP(self, x):
        return isinstance(x, Atom)

    def __init__(self):
        self.env = {}
        self.env['nil'] = Cons()
        self.env['t'] = Atom('t')
        self.env['car'] = self.car
        self.env['cdr'] = self.cdr
        self.env['cons'] = self.cons
        self.env['equal'] = self.equal
        self.env['atom'] = self.atom
        self.env['cond'] = self.cond
        self.env['quote'] = self.quote

    def tokenize(self, s):
        s = s.replace('(', ' ( ')
        s = s.replace(')', ' ) ')
        ret = filter(None, s.split(' '))
        return ret

    def parse(self, toks):
        if not toks:
            return None, None

        if toks[0] == '(':
            e1, n1 = self.parse(toks[1:])
            e2, n2 = self.parse(n1)
            c = Cons()
            c.conz(e1, e2)
            return c, n2
        elif toks[0] == ')':
            return None, toks[1:]
        else:
            a = Atom(toks[0])
            e2, n = self.parse(toks[1:])
            c = Cons()
            c.conz(a, e2)
            return c, n

    def quote(self, e):
        if e:
            return e.car
        else:
            return None

    def car(self, e):
        if e and e.car and self.CONSP(e.car):
            return e.car.car
        else:
            return None

    def cdr(self, e):
        if e and e.car and self.CONSP(e.car):
            return e.car.cdr
        else:
            return None

    def cons(self, e):
        if e is None:
            return None

        if e.car is None or e.cdr is None:
            return None

        if not self.CONSP(e.cdr):
            return None

        c = Cons()
        c.car = e.car
        i = e.cdr.car
        while i is not None and self.CONSP(i):
            c.append(i.car)
            i = i.cdr

        return c

    def equal(self, e):
        try:
            if e.car.name == e.cdr.car.name:
                return self.env['t']
            else:
                return self.env['nil']
        except AttributeError:
            return None

    def atom(self, e):
        if e is None or e.car is None:
            return None

        if isinstance(e.car, Atom):
            return self.env['t']
        else:
            return self.env['nil']

    def cond(self, e):
        if e is None:
            return None

        res = None

        while True:
            if e is None or e.car is None or not self.CONSP(e.car):
                break

            if e.car.cdr is None:
                break

            cond = e.car.car
            resp = e.car.cdr.car

            ev = self.meval(cond)
            if ev == self.env['t']:
                res = self.meval(resp)
                break

            e = e.cdr

        return res

    def subst(self, z, e):
        if e is None or z is None:
            return None

        if self.ATOMP(e):
            for (k, v) in z.iteritems():
                if e.name == k.name:
                    return v
            else:
                return e

        c = Cons()
        while e is not None and self.CONSP(e):
            c.append(self.subst(z, e.car))
            e = e.cdr

        return c

    def llambda(self, l, e):
        if l is None or e is None or l.bnd is None:
            return None

        z = {}
        x = 0
        while True:
            bnd = l.bnd[x]
            arg = e[x]

            if bnd is None and arg is None:
                break

            if bnd is None or arg is None:
                return None

            z[bnd] = arg
            x += 1

        subd = self.subst(z, l.exp)
        return self.meval(subd)


    def meval(self, e):
        if e is None:
            return None

        if self.ATOMP(e):
            le = self.env.get(e.name)
            if le is None:
                return e
            else:
                return le

        if e.car is None:
            return None

        if self.ATOMP(e.car) and e.car.name == 'lambda':
            try:
                le = Lambda(e.cdr.car, e.cdr.cdr.car)
                return le
            except AttributeError:
                return None

        f = self.meval(e.car)
        if f is None:
            return None

        l = Cons(f)
        a = e.cdr
        while a and self.CONSP(a):
            ev = self.meval(a.car)
            l.append(ev)
            a = a.cdr

        if isinstance(l.car, Lambda):
            return self.llambda(l.car, l.cdr)

        if hasattr(l.car, '__call__'):
            return l.car(l.cdr)

        return l

    def lprint(self, e):
        s = ''
        if e is None:
            return s

        if self.ATOMP(e):
            s += e.name
        else:
            s += '('
            while e:
                s += self.lprint(e.car)
                e = e.cdr
                if e is None or not self.CONSP(e):
                    break
                s += ' '
            s += ')'

        return s

    def run(self, s):
        try:
            if len(s) > 32 * 1024:
                raise SyntaxError

            toks = self.tokenize(s)
            if len(toks) and toks[0] == '(':
                c, _ = self.parse(toks[1:])
                ev = self.meval(c)
                if ev is None:
                    return self.EV_ERROR
                else:
                    return self.lprint(ev)
            else:
                raise SyntaxError
        except SyntaxError:
            return self.UB_ERROR

    def loop(self):
        while True:
            x = raw_input('> ')
            print(self.run(x))

if __name__ == '__main__':
    def info(type, value, tb):
        import traceback, pdb
        traceback.print_exception(type, value, tb)
        print
        pdb.pm()
    #sys.excepthook = info
    sm = SLURMachine();
    sm.loop()
