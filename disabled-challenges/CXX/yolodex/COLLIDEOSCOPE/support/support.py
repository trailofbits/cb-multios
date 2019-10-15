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

import functools
import operator
import random
import string


class Variable(object):
    INTEGER = 0
    POINTER = 1

    def __init__(self, kind, value):
        self.kind = kind
        self.value = value

class ASTNode(object):
    def __init__(self):
        pass

    def evaluate(self, ns):
        pass

    def format(self):
        pass

class ASTConstant(ASTNode):
    def __init__(self, value):
        self.value = value

    def evaluate(self, ns):
        return Variable(Variable.INTEGER, self.value)

    def format(self):
        return str(self.value)

class ASTVariable(ASTNode):
    def __init__(self, name):
        self.name = name

    def evaluate(self, ns):
        return ns[self.name]

    def format(self):
        return self.name

class ASTBinaryOperator(ASTNode):
    BIN_ASSIGNMENT = 0
    BIN_ADD = 1
    BIN_SUBTRACT = 2
    BIN_MULTIPLY = 3
    BIN_DIVIDE = 4

    def __init__(self, kind, lhs, rhs):
        self.kind = kind
        self.lhs = lhs
        self.rhs = rhs

    def evaluate(self, ns):
        def signed_int_overflow(i):
            i = i & 0xffffffff
            if (i & (1 << 31)) != 0:
                i = i - (1 << 32)
            return i

        def assign(lhs, rhs):
            # Remove all dereferences
            deref_count = 0
            while isinstance(lhs, ASTUnaryOperator) and lhs.kind == ASTUnaryOperator.UN_DEREFERENCE:
                deref_count += 1
                lhs = lhs.n

            if not isinstance(lhs, ASTVariable):
                return None

            for i in xrange(deref_count):
                v = ns.get(lhs.name, None)
                if v is None:
                    return None

                lhs = ASTVariable(v.value)

            r = rhs.evaluate(ns)
            ns[lhs.name] = r
            return r

        def compat_div(a, b):
            return a // b if a * b > 0 else -(-a // b)

        def math_op(op, lhs, rhs):
            l = lhs.evaluate(ns)
            r = rhs.evaluate(ns)

            if l is None or r is None:
                return None

            if l.kind != Variable.INTEGER or r.kind != Variable.INTEGER:
                return None

            if op == compat_div and r.value == 0:
                return None

            val = signed_int_overflow(op(l.value, r.value))
            return Variable(Variable.INTEGER, val)

        add = functools.partial(math_op, operator.add)
        sub = functools.partial(math_op, operator.sub)
        mul = functools.partial(math_op, operator.mul)
        div = functools.partial(math_op, compat_div)

        ops = [assign, add, sub, mul, div]
        return ops[self.kind](self.lhs, self.rhs)

    def format(self):
        symbols = ['=', '+', '-', '*', '/']
        return '(%s%s%s)' % (self.lhs.format(), symbols[self.kind], self.rhs.format())

class ASTUnaryOperator(ASTNode):
    UN_NEGATE = 0
    UN_ADDRESS_OF = 1
    UN_DEREFERENCE = 2

    def __init__(self, kind, n):
        self.kind = kind
        self.n = n

    def evaluate(self, ns):
        def signed_int_overflow(i):
            i = i & 0xffffffff
            if (i & (1 << 31)) != 0:
                i = i - (1 << 32)
            return i

        def negate(n):
            e = n.evaluate(ns)

            if e is None or e.kind != Variable.INTEGER:
                return None

            val = signed_int_overflow(-e.value)
            return Variable(Variable.INTEGER, val)

        def address_of(n):
            if not isinstance(n, ASTVariable):
                return None

            return Variable(Variable.POINTER, n.name)

        def dereference(n):
            e = n.evaluate(ns)

            if e is None or e.kind != Variable.POINTER:
                return None

            return ns.get(e.value, None)

        ops = [negate, address_of, dereference]
        return ops[self.kind](self.n)

    def format(self):
        symbols = ['~', '&', '$']
        return '%s%s' % (symbols[self.kind], self.n.format())

class Support(object):
    def __init__(self, magic_page):
        self.ns = dict()
        self.dump_tokens = False
        self.dump_ast = False
        self.magic_page = magic_page

    def calculate_csum(self, x):
        ret = 0
        for i in xrange(1024):
            ret = ret ^ ord(self.magic_page[i * 4])
        return (ret ^ x) & 0xffffffff

    def toggle_tokens(self):
        self.dump_tokens = not self.dump_tokens

    def toggle_ast(self):
        self.dump_ast = not self.dump_ast

    @staticmethod
    def hash(s):
        h = 0
        for c in s:
            h = h * 52 + ord(c)

        return h & 0xffffffff

    @staticmethod
    def random_variable_name():
        length = random.randint(1, 4)
        return ''.join(random.choice(string.lowercase) for _ in xrange(length))

    @staticmethod
    def create_variable(ns):
        buckets = { Support.hash(k) for k in ns.iterkeys() }
        name = Support.random_variable_name()
        while Support.hash(name) in buckets:
            name = Support.random_variable_name()

        return name

    @staticmethod
    def get_variable(ns, kind=None):
        if kind is not None:
            d = { k: v for (k, v) in ns.iteritems() if k == kind }
        else:
            d = ns

        if not d:
            return None

        return random.choice(d.keys())

    @staticmethod
    def create_ast_node(ns):
        node = None
        while node is None:
            kind = random.randint(0, 9)
            if kind < 4:
                node = ASTConstant(random.randint(0, 1000))
            elif kind < 5:
                var = Support.get_variable(ns, kind=Variable.INTEGER)
                if var is None:
                    continue

                node = ASTVariable(var)
            elif kind < 8:
                op_kind = random.randint(0, 4)

                if op_kind == ASTBinaryOperator.BIN_ASSIGNMENT:
                    # Create new variable?
                    if bool(random.getrandbits(1)):
                        var = Support.get_variable(ns, kind=Variable.INTEGER)
                        if var is None:
                            continue
                    else:
                        var = Support.create_variable(ns)

                    lhs = ASTVariable(var)
                else:
                    lhs = Support.create_ast_node(ns)

                rhs = Support.create_ast_node(ns)
                node = ASTBinaryOperator(op_kind, lhs, rhs)
            else:
                op_kind = random.randint(0, 2)
                if op_kind == ASTUnaryOperator.UN_NEGATE:
                    n = Support.create_ast_node(ns)
                elif op_kind == ASTUnaryOperator.UN_ADDRESS_OF:
                    var = Support.get_variable(ns)
                    if var is None:
                        continue

                    n = ASTVariable(var)
                else:
                    var = Support.get_variable(ns, kind=Variable.POINTER)
                    if var is None:
                        continue

                    n = ASTVariable(var)

                node = ASTUnaryOperator(op_kind, n)

        return node

    def create_expression(self):
        ns = dict(self.ns)
        a = self.create_ast_node(ns)
        s = a.format() + '\n'
        e = a.evaluate(ns)
        value = 0

        if e is None:
            expected = 'ERROR!\n'
        else:
            self.ns = ns
            expected = '_ = %s\n' % (e.value if e.kind == Variable.INTEGER else '<ptr>')

            if self.dump_tokens:
                expected = s + expected
            if self.dump_ast:
                expected = s + expected

            value = e.value if e.kind == Variable.INTEGER else 0

        return (s, expected, value)

