#!/usr/bin/env python
from generator.actions import Actions
import random
import struct

def random_bytes(cnt):
    return ''.join([chr(random.randint(0,255)) for x in xrange(cnt)])

def generate_bmp(data):
    width = random.randint(1, 30)
    height = (len(data) / 3 / width) + 1
    nbytes = width * height * 3
    padding = random_bytes(nbytes - len(data))
    comment = random_bytes(32)
    hdr = struct.pack('<HHHH', 0xA9C0, 0, width, height)
    return hdr + comment + data + padding

def generate_exe(data):
    xork = random.randint(1, 255)
    xor = lambda s, n: ''.join([chr(ord(x) ^ n) for x in s])
    exe = Executable()
    exe.rw_data = xor(data, xork)

    exe.pusha()
    reg = Register(random.randint(0, 3))
    exe.move_abs(reg, 0)
    for x in xrange(random.randint(0, 10)):
        exe.nop()
    exe.loop_op(('xor', xork), reg, len(data))
    for x in xrange(random.randint(0, 10)):
        exe.nop()
    exe.popa()

    return exe.as_string()

class Register(object):
    def __init__(self, num):
        self.num = num
        self.value = None

class Executable(object):
    def __init__(self):
        self.base_addr = random.randint(0x10000, 0x38000000)
        self.ep = self.base_addr
        self.ro_data = ''
        self.rw_data = ''
        self.zero_size = random.randint(0x1000, 0x100000)
        self.rw_fixups = []

    @property
    def ro_addr(self):
        return self.base_addr

    @property
    def rw_addr(self):
        return self.ro_addr + len(self.ro_data)

    @property
    def zero_addr(self):
        return self.rw_addr + len(self.rw_data)

    @property
    def ip(self):
        return self.ro_addr + len(self.ro_data)

    @property
    def header(self):
        return struct.pack('<IIIIIIII', 0x4E269472, self.ep, self.ro_addr, len(self.ro_data),
            self.rw_addr, len(self.rw_data), self.zero_addr, self.zero_size)

    def as_string(self):
        for addr, func in self.rw_fixups:
            addr -= self.ro_addr
            x = struct.unpack('<I', self.ro_data[addr:addr+4])[0]
            x = func(x, self.rw_addr)
            self.ro_data = self.ro_data[:addr] + struct.pack('<I', x & 0xffffffff) + self.ro_data[addr+4:]
        return self.header + self.ro_data + self.rw_data

    def nop(self):
        self.ro_data += random.choice([
            '\x90',
            '\x40\x48',
            '\x41\x49',
            '\x42\x4a',
            '\x43\x4b',
            '\x44\x4c',
            '\x45\x4d',
            '\x46\x4e',
            '\x47\x4f',
        ])
    def pusha(self):
        self.ro_data += '\x60'

    def popa(self):
        self.ro_data += '\x61'

    def pop(self, reg):
        self.ro_data += chr(0x58 | reg.num)

    def move_ip(self, reg):
        if random.choice([True, False]):
            # use CALL instruction
            padding = random_bytes(random.randint(0, 6))
            result = self.ip + 5
            self.ro_data += struct.pack('<BI', 0xE8, len(padding)) + padding
            self.pop(reg)
            return result
        else:
            # use absolute address
            result = self.ip
            self.ro_data += struct.pack('<BBI', 0xC7, 0xC0 | reg.num, self.ip)
            return result

    def move_abs(self, reg, value):
        rval = self.move_ip(reg)
        if random.choice([True, False]):
            self.do_op(('sub', -(value - rval)), ('reg', reg))
            self.rw_fixups += [(self.ip - 4, lambda a, x: a - x)]
        else:
            self.do_op(('add', +(value - rval)), ('reg', reg))
            self.rw_fixups += [(self.ip - 4, lambda a, x: a + x)]

    def loop_op(self, op, reg, count):
        # choose to inc reg, inc counter, or unroll 
        R = random.randint(0, 2)
        if R <= 1:
            cmpreg = random.choice(list(set(range(4)) - {reg.num}))
            cmpreg = Register(cmpreg)
            tmpreg = random.choice(list(set(range(4)) - {cmpreg.num,reg.num}))
            tmpreg = Register(tmpreg)
            if R == 0:
                self.do_op(('mov', reg), ('reg', cmpreg))
                self.do_op(('add', count), ('reg', cmpreg))
                self.do_op(('mov', reg), ('reg', tmpreg))
                top = len(self.ro_data)
                self.do_op(('cmp', cmpreg), ('reg', tmpreg))
                self.ro_data += chr(0x74) + chr(13)
                self.do_op(op, ('mem_disp', tmpreg, 0))
                self.ro_data += chr(0x40 | tmpreg.num)
                self.ro_data += chr(0xEB) + chr((top - (len(self.ro_data) + 2)) & 0xff)
            else:
                self.do_op(('mov', count), ('reg', cmpreg))
                self.do_op(('mov', 0), ('reg', tmpreg))
                top = len(self.ro_data)
                self.do_op(('cmp', cmpreg), ('reg', tmpreg))
                self.ro_data += chr(0x74) + chr(10)
                self.do_op(op, ('mem_rr', reg, tmpreg))
                self.ro_data += chr(0x40 | tmpreg.num)
                self.ro_data += chr(0xEB) + chr((top - (len(self.ro_data) + 2)) & 0xff)
        else:
            # unroll the loop
            for x in xrange(count):
                self.do_op(op, ('mem_disp', reg, x))

    def modrm(self, r1, r2):
        if not isinstance(r2, int):
            raise Exception('bad r2')
        mtype = r1[0]
        if mtype == 'mem_disp':
            reg, disp = r1[1], r1[2]
            self.ro_data += chr(0x80 | reg.num | (r2 << 3)) + struct.pack('<I', disp & 0xffffffff)
        elif mtype == 'reg':
            reg = r1[1]
            self.ro_data += chr(0xC0 | reg.num | (r2 << 3))
        elif mtype == 'mem_rr':
            base, index = r1[1], r1[2]
            self.ro_data += chr(0x00 | 4 | (r2 << 3))
            self.ro_data += chr(base.num | (index.num << 3))
        else:
            raise Exception('unknown mtype: ' + mtype)

    def do_op(self, op, target):
        opcodes = {
            'add': 0x01,
            'sub': 0x29,
            'cmp': 0x39,
            'mov': 0x89
        }
        subopcodes = {
            'add': 0,
            'or': 1,
            'adc': 2,
            'sbb': 3,
            'and': 4,
            'sub': 5,
            'xor': 6,
            'cmp': 7
        }
        op, src = op

        if isinstance(src, int):
            # imm32
            if op == 'mov':
                self.ro_data += '\xc7'
                self.modrm(target, 0)
            else:
                self.ro_data += '\x81'
                self.modrm(target, subopcodes[op])
            self.ro_data += struct.pack('<I', src & 0xffffffff)
        elif isinstance(src, Register):
            self.ro_data += chr(opcodes[op])
            self.modrm(target, src.num)
        else:
            raise Exception('bad src argument')

class TemplateGenerator(Actions):
    QUIT = 0x7160f126
    UPDATE = 0x30a7db1a
    CHECK = 0x367bae4d
    WHITELIST = 0xfa5059f
    OK = 0x6fc5499a
    ERROR = 0x42083b85

    def start(self):
        #self.delay(100)
        self.state['rules'] = [self.magic_page[:128]]
        self.state['whitelist'] = []

    def cmd(self, c, d=''):
        self.write(struct.pack('<II', 4 + len(d), c) + d)

    def response(self, r):
        self.read(length=4, expect=struct.pack('<I', r))

    def update_str(self, rules):
        s = ''
        for r in rules:
            s += struct.pack('<BI', int(r[0]), len(r[1])) + r[1]
        cksum = sum([ord(x) for x in s]) + 0x12345678
        return struct.pack('<I', -cksum & 0xffffffff) + s

    def menu(self):
        pass

    def query(self):
        result = self.OK
        r = random.randint(0, 10)
        if r < 5:
            self.comment('CHECK match rule')
            result = self.ERROR
            rule = random.choice(self.state['rules'])
            s = random_bytes(random.randint(0, 10)) + rule + random_bytes(random.randint(0, 10))
        else:
            rule = None
            s = random_bytes(random.randint(1, 40))

        r = random.randint(0, 10)
        if r < 1:
            # encode as bmp
            bmp = generate_bmp(s)
            if self.chance(0.5):
                # bad bmp
                self.comment('CHECK bad bmp')
                bmp += random_bytes(random.randint(1, 20))
                result = self.ERROR
            s = bmp
        elif r < 3:
            # encode as exe
            self.comment('CHECK exe wrapper')
            exe = generate_exe(s)
            s = exe
        else:
            # don't wrap
            pass

        if result == self.OK:
            self.comment('CHECK ok')
        elif self.chance(0.1) and len(self.state['whitelist']) > 0:
            self.comment('whitelist')
            s += random.choice(self.state['whitelist'])
            result = self.OK
        self.cmd(self.CHECK, s)
        self.response(result)

    def update(self):
        self.comment('UPDATE')
        r = []
        for x in xrange(random.randint(5, 10)):
            if self.chance(0.8) or len(self.state['rules']) <= 1:
                # add some rules
                self.comment('update add')
                s = random_bytes(random.randint(5, 30))
                self.state['rules'].append(s)
                r.append((0, s))
            elif len(self.state['rules']) > 1:
                # remove some rules
                self.comment('update remove')
                s = random.choice(self.state['rules'])
                self.state['rules'].remove(s)
                r.append((1, s))
        self.cmd(self.UPDATE, self.update_str(r))
        self.response(self.OK)

    def whitelist(self):
        self.comment('WHITELIST')
        s = random_bytes(random.randint(10, 30))
        self.state['whitelist'].append(s)

        self.cmd(self.WHITELIST, s)
        self.response(self.OK)

    def quit(self):
        self.cmd(self.QUIT)
        self.response(self.OK)
