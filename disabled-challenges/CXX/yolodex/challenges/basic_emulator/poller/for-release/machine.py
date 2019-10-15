from generator.actions import Actions
import random
import string

I_LOOP = 0
I_ADD = 1
I_XOR = 2
I_LD = 3
I_SUB = 4

def random_upper(size):
    alphanum = string.ascii_uppercase
    return ''.join(random.choice(alphanum) for c in range(size))

def random_byte():
    return chr(random.randint(0, 255))

def reg_num(r):
    reg_map = {
        'b': 0,
        'c': 1,
        'd': 2,
        'e': 3,
        'h': 4,
        'l': 5,
        'a': 7
    }
    return reg_map[r]

def insns_to_bytes(insns):
    s = ''
    for i in insns:
        if i[0] == I_LOOP:
            s += '\x18\xFE'
        if i[0] == I_ADD:
            if isinstance(i[1], int):
                s += '\xC6' + chr(i[1])
            else:
                s += chr(0x80 | reg_num(i[1]))
        if i[0] == I_XOR:
            if isinstance(i[1], int):
                s += '\xEE' + chr(i[1])
            else:
                s += chr(0xA8 | reg_num(i[1]))
        if i[0] == I_SUB:
            if isinstance(i[1], int):
                s += '\xD6' + chr(i[1])
            else:
                s += chr(0x90 | reg_num(i[1]))
        if i[0] == I_LD:
            if isinstance(i[2], int):
                s += chr(0x06 | reg_num(i[1]) << 3) + chr(i[2])
            else:
                s += chr(0x40 | (reg_num(i[1]) << 3) | reg_num(i[2]))
    return s

def simulate(insns):
    class r: pass
    r.f = 0xB0
    r.a = 0x01
    r.b = 0x00
    r.c = 0x13
    r.d = 0x00
    r.e = 0xD8
    r.h = 0x01
    r.l = 0x4D
    r.sp = 0xFFFE
    r.pc = 0x0150

    def get_reg(n):
        regmap = {
            'b': r.b,
            'c': r.c,
            'd': r.d,
            'e': r.e,
            'h': r.h,
            'l': r.l,
            'a': r.a
        }
        return regmap[n]

    def set_reg(n, x):
        x = x & 0xff
        if n == 'b':
            r.b = x
        if n == 'c':
            r.c = x
        if n == 'd':
            r.d = x
        if n == 'e':
            r.e = x
        if n == 'h':
            r.h = x
        if n == 'l':
            r.l = x
        if n == 'a':
            r.a = x

    def m(x, y):
        return (x << 8) | y

    for i in insns:
        if i[0] == I_LOOP:
            break
        if i[0] == I_ADD:
            if isinstance(i[1], int):
                r.a = (r.a + i[1]) & 0xff
                r.pc += 2
            else:
                r.a = (r.a + get_reg(i[1])) & 0xff
                r.pc += 1
        if i[0] == I_SUB:
            if isinstance(i[1], int):
                r.a = (r.a - i[1]) & 0xff
                r.pc += 2
            else:
                r.a = (r.a - get_reg(i[1])) & 0xff
                r.pc += 1
        if i[0] == I_XOR:
            if isinstance(i[1], int):
                r.a = (r.a ^ i[1]) & 0xff
                r.pc += 2
            else:
                r.a = (r.a ^ get_reg(i[1])) & 0xff
                r.pc += 1
        if i[0] == I_LD:
            x = 0
            if isinstance(i[2], int):
                x = i[2] & 0xff
                r.pc += 2
            else:
                x = get_reg(i[2])
                r.pc += 1
            set_reg(i[1], x)

    return m(r.a, r.f), m(r.b, r.c), m(r.d, r.e), m(r.h, r.l), r.sp, r.pc

class Game(Actions):
    def start(self):
        self.state['instructions'] = []

    def insn(self):
        pass

    def send_rom(self):
        self.state['instructions'] += [(I_LOOP,)]
        #print len(self.state['instructions'])

        ROM = ''
        # interrupt vectors
        while len(ROM) < 0x100:
            ROM += random_byte()

        ROM += '\x00\xC3\x50\x01' # hdr (code)
        ROM += random_upper(0x30) # hdr (logo)
        ROM += random_upper(0x10) # hdr (title)
        ROM += '\x00\x00\x00' # hdr (new_pub + sgb_flags)
        ROM += '\x00' # hdr (cart_type)
        ROM += '\x00' # hdr (rom_size)
        ROM += '\x00' # hdr (ram_size)
        ROM += random_byte() # hdr (region)
        ROM += random_byte() # hdr (publisher)
        ROM += random_byte() # hdr (version)
        ROM += random_byte() # hdr (hdr_cksum)
        ROM += random_byte() + random_byte() # hdr (cksum)

        ROM += insns_to_bytes(self.state['instructions'])
        # padding
        while len(ROM) < 0x8000:
            ROM += random_byte()

        self.write(ROM)
        self.read(delim='\n', expect='..2JLoading .*\n', expect_format='pcre')
        self._actions.append(self._wrap('delay', '500'))

    def cmd(self):
        pass

    def cmd_help(self):
        self.write('?')
        self.read(delim='HELP:')
        self.read(delim='\n', expect=' (q)uit, (h)elp, (wasd) direction keys, (j) A, (k) B, (u) SELECT, (i) START\n')

    def cmd_quit(self):
        af, bc, de, hl, sp, pc = simulate(self.state['instructions'])

        self.write('q')
        self.read(delim='Good-Bye\n')
        self.read(delim='\n', expect_format='pcre', expect='AF = %02X.., BC = %04X, DE = %04X, HL = %04X\n' %
            (af >> 8, bc, de, hl))
        self.read(delim='\n', expect='SP = %04X, PC = %04X\n' % (sp, pc))

    def add_insn(self):
        opr = random.choice(['a', 'b', 'c', 'd', 'e', 'h', 'l'] + range(0, 255))
        self.state['instructions'] += [(I_ADD, opr)]

    def sub_insn(self):
        opr = random.choice(['a', 'b', 'c', 'd', 'e', 'h', 'l'] + range(0, 255))
        self.state['instructions'] += [(I_SUB, opr)]

    def xor_insn(self):
        opr = random.choice(['a', 'b', 'c', 'd', 'e', 'h', 'l'] + range(0, 255))
        self.state['instructions'] += [(I_XOR, opr)]

    def ld_insn(self):
        dst = random.choice(['a', 'b', 'c', 'd', 'e', 'h', 'l'])
        opr = random.choice(['a', 'b', 'c', 'd', 'e', 'h', 'l'] + range(0, 255))
        self.state['instructions'] += [(I_LD, dst, opr)]
