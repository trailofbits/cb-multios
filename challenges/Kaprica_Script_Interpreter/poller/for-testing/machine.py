from generator.actions import Actions
import random
import re
import struct

def random_alpha():
    alphabet = list(set([chr(x) for x in xrange(256)]) - set(['\0']))
    length = random.randint(10, 50)
    return ''.join([random.choice(alphabet) for x in xrange(length)])

def random_number():
    return random.randint(10, 100000)

def get_f(v, f, n):
    if n == 0 and f[0] is None:
        s = ''
        last = sorted([int(x) for x in f.keys()])[-1]
        for x in xrange(last+1):
            if x == 0:
                continue
            if x > 1:
                s += v['OFS']
            s += f.get(x, '')
        f[0] = s
    elif not 1 in f:
        x = 1
        for w in f[0].split(' '):
            f[x] = w
            x += 1
    return f.get(n, '')

def truncate_i(v):
    i = v.get('i') & 0xffffffff
    i = struct.unpack('<i', struct.pack('<I', i))[0]
    v['i'] = i

def print_i(v):
    i = v.get('i', '')
    return str(i) + '\n'

def to_bool(s):
    if isinstance(s, int):
        return 1 if s else 0
    if s == '':
        return 0
    return 1

def to_int(s):
    if isinstance(s, int):
        return s
    m = re.match('([+-]?[0-9]+)', s)
    if not m:
        return 0
    i = int(m.group(1))
    i = struct.unpack('<i', struct.pack('<I', i & 0xffffffff))[0]
    return i

def test1(v, f):
    return get_f(v, f, 0) + '\n'

def test2(v, f):
    return get_f(v, f, 1) + get_f(v, f, 2) + '\n'

def test3(v, f):
    return get_f(v, f, 1) + v['OFS'] + get_f(v, f, 2) + '\n'

def test4(v, f):
    v['OFS'] = 'a'
    get_f(v, f, 1)
    f[3] = 'foo'
    f[0] = None
    return get_f(v, f, 0) + '\n'

def test4b(v, f):
    v['OFS'] = ' '
    return ''

def test5(v, f):
    return ''.join (['%d\n' % x for x in xrange(8)])

def test6(v, f):
    v['i'] = 0
    return print_i(v)

def test7(v, f):
    return print_i(v)

def test8(v, f):
    v['i'] = to_int(v.get('i', 0)) + 10
    truncate_i(v)
    return print_i(v)

def test9(v, f):
    v['i'] = to_int(v.get('i', 0)) * 90
    truncate_i(v)
    return print_i(v)

def test10(v, f):
    v['i'] = to_int(v.get('i', 0)) - 2
    truncate_i(v)
    return print_i(v)

def test11(v, f):
    v['i'] = int(float(to_int(v.get('i', 0))) / 8)
    truncate_i(v)
    return print_i(v)

def test12(v, f):
    v['i'] = to_int(v.get('i', 0)) * 3
    truncate_i(v)
    return print_i(v)

def test13(v, f):
    v['i'] = to_int(v.get('i', 0))
    if v['i'] < 0:
        v['i'] = -(v['i'] % 2)
    else:
        v['i'] = v['i'] % 2
    truncate_i(v)
    return print_i(v)

def test14(v, f):
    v['i'] = 0 if to_bool(v.get('i', 0)) != 0 else 1
    return print_i(v)

def test15(v, f):
    v['i'] = -to_int(v.get('i', 0))
    truncate_i(v)
    return print_i(v)

def test16(v, f):
    i = "a" + str(v.get('i', "")) + "b"
    v['i'] = i

    return print_i(v)

def test17(v, f):
    i = "10" + str(v.get('i', ""))
    v['i'] = i

    return print_i(v)

def test18(v, f):
    i = v.get('i', 0)
    j = 4
    if isinstance(i, str):
        j = str(j)
    if i > j:
        i = 1
    else:
        i = -1
    v['i'] = i
    return print_i(v)

def test19(v, f):
    i = to_int(v.get('i', 0))
    if to_bool(v.get('i', 0)) != 0 and (i - 1) != 0:
        i = 1
    else:
        i = 0
    v['i'] = i

    return print_i(v)

def test20(v, f):
    i = to_int(v.get('i', 0))
    if (i * 8) != 0 or (i - 2) != 0:
        i = 1
    else:
        i = 0
    v['i'] = i
    
    return print_i(v)

def test21(v, f):
    return '0\n'

class Fuzzy(Actions):
    TESTS = [
        (test1, 'print;'),
        (test2, 'print $1 $2;'),
        (test3, 'print $1, $2;'),
        (test4, 'OFS = "a"; $3 = "foo"; print;'),
        (test4b, 'OFS = " ";'),
        (test5, 'for (loop = 0; loop < 8; loop += 1) print loop;'),
        (test6, 'for (i = 0; i < 10; --i) break; print i;'),
        (test7, 'print i;'),
        (test8, 'i += 10; print i;'),
        (test9, 'i = i * 90; print i;'),
        (test10, 'i -= 2; print i;'),
        (test11, 'i /= 8; print i;'),
        (test12, 'i *= 3; print i;'),
        (test13, 'i %= 2; print i;'),
        (test14, 'i = !i; print i;'),
        (test15, 'i = -i; print i;'),
        (test16, 'i = "a" i "b"; print i;'),
        (test17, 'i = "10" i; print i;'),
        (test18, 'i = i > 4 ? 1 : -1; print i;'),
        (test19, 'i = i && (i - 1); print i;'),
        (test20, 'i = (i * 8) || (i - 2); print i;'),
        (test21, 'printf "#d#s", foobar, ORS;'),
    ]

    def execute(self, stmt):
        out = ''
        for x in stmt:
            out += x[0](self.state['vars'], self.state['fields'])
        return out

    def generate_stmt(self):
        ntests = random.randint(len(self.TESTS), len(self.TESTS) * 8)
        stmt = [random.choice(self.TESTS) for x in xrange(ntests)]
        s = '\n'.join([x[1] for x in stmt])
        self.state['results'][s] = stmt
        return s

    def start(self):
        self.state['data'] = '''Lorem ipsum dolor sit amet, 
consectetur adipiscing elit, sed do eiusmod tempor
incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation 
ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute
 irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
 Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt
 mollit anim id est laborum.'''
        self.state['results'] = {}
        self.state['programs'] = []
        self.state['vars'] = {
            'OFS': ' '
        }

    def generate(self):
        pass

    def begin(self):
        s = self.generate_stmt()
        self.state['programs'].append(('BEGIN', s))
        self.write('\nBEGIN { %s }' % s)

    def normal(self):
        word = random.choice(self.state['data'].split())
        s = self.generate_stmt()
        self.state['programs'].append((word, s))
        self.write('\n/%s/ { %s }' % (word, s))

    def end(self):
        s = self.generate_stmt()
        self.state['programs'].append(('END', s))
        self.write('\nEND { %s }' % s)

    def send_data(self):
        self.write(self.state['data'] + '\n')
        for line in self.state['data'].split('\n'):
            line = line.strip('\n')
            self.state['fields'] = {
                0: line
            }
            for x in self.state['programs']:
                if x[0] == 'BEGIN':
                    s = self.execute(self.state['results'][x[1]])
                    self.read(length=len(s), expect=s)
            for x in self.state['programs']:
                line = get_f(self.state['vars'], self.state['fields'], 0)
                if x[0] in line and x[0] not in ('BEGIN', 'END'):
                    s = self.execute(self.state['results'][x[1]])
                    self.read(length=len(s), expect=s)
            for x in self.state['programs']:
                if x[0] == 'END':
                    s = self.execute(self.state['results'][x[1]])
                    self.read(length=len(s), expect=s)
