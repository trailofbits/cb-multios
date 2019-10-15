#!/usr/bin/env python
from generator.actions import Actions, encode
import random
import struct

class VM(Actions):
    def start(self):
        self.read(length=4)
        self.state['init_memory'] = random.randint(0, 0xFFFF)
        self.state['init_registers'] = self.chance(0.5)

        self.state['registers'] = []
        while len(self.state['registers']) < 16:
            self.state['registers'].append(random.randint(0,0xFFFFFFFF) if self.state['init_registers'] else 0)

        self.state['memory'] = []
        for x in xrange(0, 0x10000):
            self.state['memory'].append(random.randint(0,0xFF) if x < self.state['init_memory'] else 0)

        flags = self.state['init_memory']
        if self.state['init_registers']:
            flags |= 1 << 31
        self.write('\x00MVi')
        self.write(struct.pack('<I', flags))

        if self.state['init_registers']:
            for x in self.state['registers']:
                self.write(struct.pack('<I', x))

        mem = ''
        for x in xrange(0, self.state['init_memory']):
            mem += chr(self.state['memory'][x])
        if len(mem):
            self.write(mem)

    def opcode(self):
        pass

    def rreg(self):
        return random.randint(0x0, 0xf)

    def rlval(self):
        return random.randint(0,0xffff)

    def signed(self, lval):
        lval = lval & 0xffff
        if lval >= 0x8000:
            return -(0x10000 - lval)
        else:
            return lval

    def add(self, a, b):
        return (a + b) & 0xffffffff

    def inst(self, inst, dst, src, lval):
        self.write(struct.pack('<I', (inst << 24) | (dst << 20) | (src << 16) | lval))

    def opc_load(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()

        addr = lval
        if rsrc != 0:
            addr += r[rsrc]
        addr &= 0xffff

        r[rdst] = self.state['memory'][addr]

        self.inst(1, rdst, rsrc, lval)
        self.register_dump()

    def opc_store(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()

        addr = lval
        if rdst != 0:
            addr += r[rdst]
        addr &= 0xffff

        self.state['memory'][addr] = 0 if rsrc == 0 else (r[rsrc] & 0xff)

        self.inst(2, rdst, rsrc, lval)
        self.register_dump()

    def opc_add(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            r[rdst] += self.add(r[rsrc], self.signed(lval))
            r[rdst] &= 0xffffffff
        else:
            r[rdst] += self.signed(lval)
            r[rdst] &= 0xffffffff
        self.inst(4, rdst, rsrc, lval)
        self.register_dump()

    def opc_sub(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            r[rdst] -= self.add(r[rsrc], self.signed(lval))
            r[rdst] &= 0xffffffff
        else:
            r[rdst] -= self.signed(lval)
            r[rdst] &= 0xffffffff
        self.inst(5, rdst, rsrc, lval)
        self.register_dump()

    def opc_mul(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            r[rdst] *= self.add(r[rsrc], self.signed(lval))
            r[rdst] &= 0xffffffff
        else:
            r[rdst] *= self.signed(lval)
            r[rdst] &= 0xffffffff
        self.inst(6, rdst, rsrc, lval)
        self.register_dump()

    def opc_div(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            if self.add(r[rsrc], self.signed(lval)) == 0:
                lval += 1
            r[rdst] /= self.add(r[rsrc], self.signed(lval))
            r[rdst] &= 0xffffffff
        else:
            if lval == 0:
                lval += 1
            r[rdst] /= self.signed(lval) & 0xffffffff
            r[rdst] &= 0xffffffff
        self.inst(7, rdst, rsrc, lval)
        self.register_dump()

    def opc_and(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            r[rdst] &= r[rsrc] | self.signed(lval)
            r[rdst] &= 0xffffffff
        else:
            r[rdst] &= self.signed(lval)
            r[rdst] &= 0xffffffff
        self.inst(9, rdst, rsrc, lval)
        self.register_dump()

    def opc_xor(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            r[rdst] ^= r[rsrc] | self.signed(lval)
            r[rdst] &= 0xffffffff
        else:
            r[rdst] ^= self.signed(lval)
            r[rdst] &= 0xffffffff
        self.inst(10, rdst, rsrc, lval)
        self.register_dump()

    def opc_or(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrc = self.rreg()
        lval = self.rlval()
        if rsrc != 0:
            r[rdst] |= r[rsrc] | self.signed(lval)
            r[rdst] &= 0xffffffff
        else:
            r[rdst] |= self.signed(lval)
            r[rdst] &= 0xffffffff
        self.inst(8, rdst, rsrc, lval)
        self.register_dump()

    def opc_slt(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrca = self.rreg()
        rsrcb = self.rreg()

        srca = 0 if rsrca == 0 else r[rsrca]
        srcb = 0 if rsrcb == 0 else r[rsrcb]
        if srca < srcb:
            r[rdst] = 1
        else:
            r[rdst] = 0
        self.inst(11, rdst, rsrca, rsrcb)
        self.register_dump()

    def opc_slte(self):
        r = self.state['registers']
        rdst = self.rreg()
        rsrca = self.rreg()
        rsrcb = self.rreg()

        srca = 0 if rsrca == 0 else r[rsrca]
        srcb = 0 if rsrcb == 0 else r[rsrcb]
        if srca <= srcb:
            r[rdst] = 1
        else:
            r[rdst] = 0
        self.inst(12, rdst, rsrca, rsrcb)
        self.register_dump()

    def opc_syscall(self):
        r = self.state['registers']
        start = r[2] & 0xffff
        l = r[3] & 0xffff
        self.inst(3, 0, 0, 0)
        if not ((start + l) > 0x10000 or l == 0):
            if r[1] == 0:
                self.read(expect=''.join(
                    map(chr, self.state['memory'][int(start):int(start)+int(l)])),
                    length=int(l))
            elif r[1] == 1:
                rand_data = [random.randint(0, 0xff) for _ in xrange(int(l))]
                self.state['memory'][start:start + l] = rand_data
                self.write(''.join(map(chr, rand_data)))

        self.register_dump()

    def register_dump(self):
        regs = ''
        for x in self.state['registers']:
            regs += struct.pack('<I', x)
        self.read(length=16*4, expect=regs)

    def end(self):
        self.inst(4, 0, 0, 0) #nop (add r0, r0, 0)
        self.register_dump()

        if self.chance(0.2):
            self.inst(0x00, 0, 0, 0) #invalid opc
        elif self.chance(0.3):
            self.inst(0x07, 0, 0, 0) #div by zero
        else:
            self.inst(0x40, 0, 0, 0) #past end of list
        self.read(length=4, expect="DONE")
