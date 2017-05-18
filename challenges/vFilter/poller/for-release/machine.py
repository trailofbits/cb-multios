#!/usr/bin/env python
from functools import partial
from generator.actions import Actions
import random
import struct

def random_bytes(minlen, maxlen):
    length = random.randint(minlen, maxlen)
    return ''.join([chr(random.randint(0,255)) for x in xrange(length)])

class Filter(object):
    def __init__(self):
        self.insn = []
        self._insn = []
        self.rfp = 15
        self.ra = random.randint(0, 6)
        self.rb = random.randint(self.ra+1, 9)
        self.rc = random.randint(self.rb+1, 11)
        self.rt = random.randint(self.rc+1, 14)

        # move ctx pointer into Rc
        self.move(self.rc, 0)

        # initialize Ra to zero
        self.alu(11, self.ra, rextra=0)

        self.ld_ctx(0)

    def bytecode(self):
        return struct.pack('<I', len(self.insn)) + ''.join(self.insn)

    def ret(self):
        self.move(0, self.ra)
        self.jmp(5, 0, 0, 0)
        self._insn.append(partial(self._ret))

    def _ret(self):
        self.reg[0] = self.reg[self.ra]
    
    def jmp(self, code, offset, rdst, rsrc=None, rextra=None):
        if rsrc is None:
            source = 1
            rsrc = 0
        else:
            source = 0
            rextra = 0
        x = struct.pack('<BBHI', (code << 4) | (source << 3) | 4, (rsrc << 4) | rdst, offset, rextra)
        self.insn.append(x)
    
    def alu(self, code, rdst, rsrc=None, rextra=None):
        if rsrc is None:
            source = 1
            rsrc = 0
        else:
            source = 0
            rextra = 0
        x = struct.pack('<BBHI', (code << 4) | (source << 3) | 3, (rsrc << 4) | rdst, 0, rextra)
        self.insn.append(x)

    def ld(self, dst, src, offset, size=0):
        x = struct.pack('<BBHI', (0 << 5) | (size << 3) | 0, (src << 4) | dst, offset, 0)
        self.insn.append(x)

    def st(self, dst, src, offset, size=0):
        x = struct.pack('<BBHI', (0 << 5) | (size << 3) | 2, (src << 4) | dst, offset, 0)
        self.insn.append(x)

    def ld_ctx(self, offset):
        # if past header, we have to verify
        if offset > 16:
            # init Rb to 0
            self.alu(11, self.rb, rextra=0)

            # retrieve length from ctx
            self.ld(self.rt, self.rc, 8, size=2)

            # if offset -gte length, jump over ld
            self.jmp(3, 1, self.rt, rextra=offset-16)

        # do the load
        self.ld(self.rb, self.rc, offset)
        self._insn.append(partial(self._ld_ctx, offset))

    def _ld_ctx(self, offset):
        if offset < len(self.ctx):
            self.reg[self.rb] = ord(self.ctx[offset])
        else:
            self.reg[self.rb] = 0

    def ld_fp(self, offset):
        self.ld(self.rb, self.rfp, offset, size=2)
        self._insn.append(partial(self._ld_fp, offset))

    def _ld_fp(self, offset):
        val = self.stack[offset]
        val |= self.stack[offset + 1] << 8
        val |= self.stack[offset + 2] << 16
        val |= self.stack[offset + 3] << 24
        self.reg[self.rb] = val

    def st_fp(self, offset):
        self.st(self.rfp, self.ra, offset, size=2)
        self._insn.append(partial(self._st_fp, offset))

    def _st_fp(self, offset):
        val = self.reg[self.ra]
        self.stack[offset] = val & 0xff
        self.stack[offset + 1] = (val >> 8) & 0xff
        self.stack[offset + 2] = (val >> 16) & 0xff
        self.stack[offset + 3] = (val >> 24) & 0xff

    def move(self, dst, src):
        self.alu(11, dst, rsrc=src)
        self._insn.append(partial(self._binop, lambda a, b: b, dst, src))

    def binop(self, op, alu, dst, rsrc):
        self.alu(alu, dst, rsrc=rsrc)
        self._insn.append(partial(self._binop, op, dst, rsrc))

    def binop_const(self, op, alu, dst, extra):
        self.alu(alu, dst, rextra=extra)
        self._insn.append(partial(self._binop_const, op, dst, extra))

    def _binop(self, op, dst, src):
        self.reg[dst] = op(self.reg[dst], self.reg[src]) & 0xffffffff

    def _binop_const(self, op, dst, extra):
        self.reg[dst] = op(self.reg[dst], extra) & 0xffffffff

    def random(self, count=1):
        INSN = [
            partial(self.move, self.ra, self.rb), # rA -> rB
#            partial(self.move, self.rb, self.ra), # rB -> rA
            lambda: self.ld_ctx(random.randint(0, 1000)), # ctx[rand] -> rB
            partial(self.binop, lambda a, b: a+b, 0, self.ra, self.rb), # rA + rB -> rA
            lambda: self.binop_const(lambda a, b: a+b, 0, self.ra, random.randint(0, 0x7fffffff)), # rA + rand -> rA
            partial(self.binop, lambda a, b: a-b, 1, self.ra, self.rb), # rA - rB -> rA
            lambda: self.binop_const(lambda a, b: a-b, 1, self.ra, random.randint(0, 0x7fffffff)), # rA - rand -> rA
            partial(self.binop, lambda a, b: a*b, 2, self.ra, self.rb), # rA * rB -> rA
            lambda: self.binop_const(lambda a, b: a*b, 2, self.ra, random.randint(0, 0x7fffffff)), # rA * rand -> rA
#            partial(self.binop, lambda a, b: a/b, 3, self.ra, self.rb), # rA / rB -> rA
            lambda: self.binop_const(lambda a, b: a/b, 3, self.ra, random.randint(0x1, 0x7fffffff)), # rA / rand -> rA
#            partial(self.binop, lambda a, b: a%b, 4, self.ra, self.rb), # rA % rB -> rA
            lambda: self.binop_const(lambda a, b: a%b, 4, self.ra, random.randint(0x1, 0x7fffffff)), # rA % rand -> rA
            partial(self.binop, lambda a, b: a|b, 5, self.ra, self.rb), # rA | rB -> rA
            lambda: self.binop_const(lambda a, b: a|b, 5, self.ra, random.randint(0, 0x7fffffff)), # rA | rand -> rA
            partial(self.binop, lambda a, b: a&b, 6, self.ra, self.rb), # rA & rB -> rA
            lambda: self.binop_const(lambda a, b: a&b, 6, self.ra, random.randint(0, 0x7fffffff)), # rA & rand -> rA
            partial(self.binop, lambda a, b: a^b, 7, self.ra, self.rb), # rA ^ rB -> rA
            lambda: self.binop_const(lambda a, b: a^b, 7, self.ra, random.randint(0, 0x7fffffff)), # rA ^ rand -> rA
#            partial(self.binop, lambda a, b: a<<b, 8, self.ra, self.rb), # rA << rB -> rA
            lambda: self.binop_const(lambda a, b: a<<b, 8, self.ra, random.randint(0, 30)), # rA << rand -> rA
#            partial(self.binop, lambda a, b: a>>b, 9, self.ra, self.rb), # rA >> rB -> rA
            lambda: self.binop_const(lambda a, b: a>>b, 9, self.ra, random.randint(0, 30)), # rA >> rand -> rA
            lambda: self.ld_fp(random.randint(0, 32)),
            lambda: self.st_fp(random.randint(0, 32))
        ]

        for x in xrange(count):
            random.choice(INSN)()

    def execute(self, pkt, action):
        ts, ts_usec, orig_length, data = pkt

        # initialize executor state
        self.ctx = struct.pack('<IIII', ts, ts_usec, len(data), orig_length) + data
        self.reg = [0] * 16
        self.stack = [0] * 48

        # run through the bytecode
        for f in self._insn:
            try:
                f()
            except ZeroDivisionError:
                self.reg[0] = 0xFFFFFFFF
                break

        action.read(length=4, expect=struct.pack('<I', self.reg[0]))

class TemplateGenerator(Actions):
    def start(self):
        self.delay(50)
        self.state['filter'] = None
        self.state['pkts'] = []

        self.write(self.magic_page[:4])
        self.read(length=0x1000, expect=self.magic_page)

    def random_pkts(self):
        for x in xrange(int(25 * random.paretovariate(2))):
            self.random_pkt()

    def random_pkt(self):
        if len(self.state['pkts']) > 1000:
            return
        ts = random.randint(1, 0x7FFFFFFF)
        ts_usec = random.randint(0, 1000000)
        pkt = random_bytes(1, 2000)
        orig_length = random.randint(len(pkt), 2000)
        self.state['pkts'].append((ts, ts_usec, orig_length, pkt))

    def random_filter(self):
        self.state['filter'] = Filter()
        self.state['filter'].random(random.randint(10, 100))
        self.state['filter'].ret()

    def send_pkts(self):
        file_hdr = struct.pack('<IHHII', 0x12ab34cd, 3, random.randint(10, 0xFFFF), random.randint(2000, 0xFFFF), 1)
        pkts = ''.join([struct.pack('<IIII', ts, ts_usec, len(data), orig_length) + data for ts, ts_usec, orig_length, data in self.state['pkts']])
        self.write(struct.pack('<I', len(file_hdr) + len(pkts)))
        self.write(file_hdr)
        self.write(pkts)
        self.read(length=1, expect='\x01')

    def send_filter(self):
        bc = self.state['filter'].bytecode()
        self.write(bc)
        self.read(length=1, expect='\x01')

    def execute(self):
        self.send_filter()
        self.send_pkts()
        for pkt in self.state['pkts']:
            self.state['filter'].execute(pkt, self)
