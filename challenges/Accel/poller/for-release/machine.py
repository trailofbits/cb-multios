from generator.actions import Actions
import math
import random
import string
import struct

def random_alphanum(max_size, min_size=2):
    alphanum = string.letters + string.digits
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(alphanum) for c in range(max_size))

def random_cell():
    column = random.randint(0, 25)
    row = random.randint(0, 99)
    return '%s%d' % (chr(ord('A') + column), row)

def random_double():
    return random.uniform(-100000, 100000)

def stddev(args):
    # get the mean of the population
    mean = sum(args) / len(args)

    # calculate the variance
    variance = sum(map(lambda x: (x - mean) ** 2, args)) / len(args)

    if any(map(lambda x: math.isnan(x), args)):
        print args, math.sqrt(variance)
    return math.sqrt(variance)

def cell_sortable(cell):
    if cell[0] in string.letters and cell[1] in string.digits:
        row = cell[0:1]
        col = cell[1:]
    elif cell[0] in string.letters and cell[1] in string.letters:
        row = cell[0:2]
        col = cell[2:]
    else:
        raise Exception('Bad row string')

    return '%s%02d' % (row, int(col))

class Spreadsheet(Actions):
    class Value(object):
        def __init__(self):
            pass

    class Double(Value):
        def __init__(self, value):
            self.value = value

        def __str__(self):
            if math.isnan(self.value):
                return '!FORMULA: CIRREF/STR/DIV0'
            if self.value == 0.0:
                return '%.03f' % 0
            return '%.03f' % self.value

        def evaluate(self):
            return round(self.value, 3)

    class Cell(Value):
        def __init__(self, cells, cell):
            self.cell = cell
            self.cells = cells

        def __str__(self):
            return self.cell

        def evaluate(self):
            # prevent circular references
            old_value = self.cells.get(self.cell, None)
            self.cells[self.cell] = float('NaN')

            try:
                if old_value is None:
                    result = 0.0
                elif isinstance(old_value, float):
                    if math.isnan(old_value):
                        raise ValueError()
                    result = old_value
                else:
                    result = round(old_value.evaluate(), 3)
            finally:
                self.cells[self.cell] = old_value

            return result

    class Formula(Value):
        def __init__(self, op, args):
            self.op = op
            self.args = args
            if self.op.numargs is not None:
                assert len(self.args) == self.op.numargs

        def __str__(self):
            if self.op.infix:
                assert self.op.numargs == 2
                return '(%s %s %s)' % (self.args[0], self.op.name, self.args[1])
            else:
                return '%s(%s)' % (self.op.name, ', '.join(map(lambda x: str(x), self.args)))

        def evaluate(self):
            result = round(self.op.evaluate(map(lambda x: x.evaluate(), self.args)), 3)
            if math.isinf(result):
                return float('nan')
            return result

    class String(Value):
        def __init__(self, value):
            self.value = value

        def __str__(self):
            return '"%s"' % (self.value)

        def evaluate(self):
            raise ValueError('Cell is a String')

    class Op(object):
        def __init__(self, name, numargs=None, infix=False, f=None):
            self.name = name
            self.numargs = numargs
            self.infix = infix
            self.f = f

        def evaluate(self, args):
            return self.f(args)

    OPERATORS = [
        Op('AVG', f=lambda args: sum(args)/len(args) if len(args) > 0 else float('NaN')),
        Op('COUNT', f=lambda args: float(len(args))),
        Op('MAX', f=lambda args: max(args)),
        Op('MIN', f=lambda args: min(args)),
        Op('STDDEV', f=stddev),
        Op('ABS', 1, f=lambda args: abs(args[0])),
        Op('+', 2, True, f=lambda args: args[0] + args[1]),
        Op('COS', 1, f=lambda args: math.cos(args[0])),
        Op('LN', 1, f=lambda args: math.log(args[0])),
        Op('LOG10', 1, f=lambda args: math.log10(args[0])),
        Op('POWER', 2, f=lambda args: args[0] ** args[1]),
        Op('*', 2, True, f=lambda args: args[0] * args[1]),
        Op('/', 2, True, f=lambda args: args[0] / args[1]),
        Op('SIN', 1, f=lambda args: math.sin(args[0])),
        Op('SQRT', 1, f=lambda args: math.sqrt(args[0])),
        Op('-', 2, True, f=lambda args: args[0] - args[1]),
        Op('SUM', f=lambda args: sum(args))
    ]

    def cell_text(self, cell):
        value = self.state['cells'].get(cell)
        if value is None:
            valuetext = ''
        elif isinstance(value, self.Formula):
            valuetext = '=' + str(value)
        else:
            valuetext = str(value)
        return valuetext

    def start(self):
        self.state['cells'] = {}

    def menu(self):
        self.read(length=len('Accel:-$ '), expect='Accel:-$ ')

    def random_value(self):
        if self.chance(0.5):
            # double
            return self.Double(random_double())
        elif self.chance(0.5):
            return self.Cell(self.state['cells'], random_cell())
        else:
            return self.random_formula()

    def random_formula(self):
        op = random.choice(self.OPERATORS)
        length = op.numargs or random.randint(1, 10)
        args = map(lambda x: self.random_value(), xrange(length))
        return self.Formula(op, args)

    def _show(self, cell):
        self.write('SHOW %s\n' % cell)
        value = self.state['cells'].get(cell)
        if value is None:
            valuetext = ''
        elif isinstance(value, self.String):
            valuetext = str(value)
        else:
            try:
                value = value.evaluate()
            except OverflowError:
                value = float('NaN')
            except ValueError:
                value = float('NaN')
            except ZeroDivisionError:
                value = float('NaN')
            valuetext = str(self.Double(value))
        if value is not None and isinstance(value, float) and not math.isnan(value):
            # XXX getting the rounding the match is impossible
            length_to_match = min(6, valuetext.index('.') + 2)
            self.read(length=len('Cell Value: ')+length_to_match, expect='Cell Value: %s' % valuetext[:length_to_match])
            self.read(delim='\n')
        else:
            self.read(delim='\n', expect='Cell Value: %s\n' % valuetext)
        self.read(delim='\n', expect='Success.\n')

    def show(self):
        cell = random_cell()
        if self.chance(0.5):
            # repr
            self.write('REPR %s\n' % cell)
            self.read(delim='\n', expect='Cell Repr: %s\n' % self.cell_text(cell))
            self.read(delim='\n', expect='Success.\n')
        else:
            # show
            self._show(cell)

    def show_table(self):
        self.write('SHOW TABLE\n')

        cells = self.state['cells']
        for k in sorted(cells.keys(), key=lambda x: cell_sortable(x)):
            if cells[k] is not None:
                self.read(delim='\n', expect='%s=%s\n' % (k, self.cell_text(k)))
        self.read(delim='\n', expect='Success.\n')

    def clear(self):
        cell = random_cell()
        self.write('CLEAR %s\n' % cell)
        if cell in self.state['cells']:
            del self.state['cells'][cell]
        self.read(delim='\n', expect='Success.\n')

    def assign(self):
        cell = random_cell()

        if self.chance(0.5):
            # double
            value = self.Double(random_double())
            valuetext = str(value)
        elif self.chance(0.5):
            # string
            value = self.String(random_alphanum(100))
            valuetext = str(value)
        else:
            # formula
            valuetext = None
            while valuetext is None:
                value = self.random_formula()
                if len(str(value)) < 500:
                    valuetext = '=' + str(value)

        self.write('%s=%s\n' % (cell, valuetext))
        self.state['cells'][cell] = value
        self.read(delim='\n', expect='Success.\n')

    def quit(self):
        # iterate over all cells to make sure things are right
        cells = self.state['cells']
        for k in cells.keys():
            if cells[k] is not None:
                self._show(k)
                self.read(length=len('Accel:-$ '), expect='Accel:-$ ')

        self.write('EXIT\n')
        self.read(delim='\n', expect='Exiting...\n')
