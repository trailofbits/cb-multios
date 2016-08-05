#!/usr/bin/env python
from generator.actions import Actions
import numpy as np
import random
import struct

MAX_ITEMS = 1000

INSERT = 0x2064
RETR = 0xA097
ADD = 0x2C56
SUB = 0x973D
MUL = 0xE925
SUM = 0x71B8
PROD = 0x1510
FLAG = 0x4141
RAND = 0xC4C5
QUIT = 0xA80B

RESERVED = [INSERT, RETR, ADD, SUB, MUL, SUM, PROD, FLAG, RAND, QUIT]

def random_r():
    if random.randint(0, 10) == 0:
        return random.randint(0, MAX_ITEMS-1) 
    return random.randint(0, 20)

class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        self.state['r'] = {}
        self.state['rand'] = (np.uint32(0x4347c000), 0)

        self.read(length=8, expect=struct.pack('>II', 0xdeadbeef, 0x4347c000))

    def menu(self):
        pass

    def insert(self):
        r = random_r()
        value = np.uint32(random.randint(0, 0xFFFFFFFF))
        self.state['r'][r] = value

        self.write(struct.pack('>HII', INSERT, r, value))

    def retr(self):
        r = random.choice(self.state['r'].keys())
        self.write(struct.pack('>HI', RETR, r))
        self.read(length=4, expect=struct.pack('>I', self.state['r'][r]))

    def retr_all(self):
        for r in self.state['r'].keys():
            self.write(struct.pack('>HI', RETR, r))
            self.read(length=4, expect=struct.pack('>I', self.state['r'][r]))

    def add(self):
        dst = random_r()
        a = random.choice(self.state['r'].keys())
        b = random.choice(self.state['r'].keys())
        self.state['r'][dst] = self.state['r'][a] + self.state['r'][b]

        self.write(struct.pack('>HIII', ADD, a, b, dst))

    def sub(self):
        dst = random_r()
        a = random.choice(self.state['r'].keys())
        b = random.choice(self.state['r'].keys())
        self.state['r'][dst] = self.state['r'][a] - self.state['r'][b]

        self.write(struct.pack('>HIII', SUB, a, b, dst))

    def mul(self):
        dst = random_r()
        a = random.choice(self.state['r'].keys())
        b = random.choice(self.state['r'].keys())
        self.state['r'][dst] = self.state['r'][a] * self.state['r'][b]

        self.write(struct.pack('>HIII', MUL, a, b, dst))

    def sum(self):
        start = random.choice(self.state['r'].keys())
        end = start
        x = 0
        while end in self.state['r']:
            x += self.state['r'][end]
            end += 1

        r = random_r()
        self.state['r'][r] = np.uint32(x)
        self.write(struct.pack('>HIII', SUM, start, end, r))

    def prod(self):
        start = random.choice(self.state['r'].keys())
        end = start
        x = 1
        while end in self.state['r']:
            x *= self.state['r'][end]
            end += 1

        r = random_r()
        self.state['r'][r] = np.uint32(x)
        self.write(struct.pack('>HIII', PROD, start, end, r))

    def flag(self):
        pw = struct.unpack('<I', self.magic_page[0:4])[0]
        if self.chance(0.5):
            pw = random.randint(0, 0xffffffff)
            self.write(struct.pack('>HI', FLAG, pw))
            return

        r = random_r()
        i = random.randint(0, 0xffffffff)
        val = struct.unpack('<I', self.magic_page[(i & 0x3ff)*4 : (i &0x3ff)*4 + 4])[0]
        self.state['r'][r] = np.uint32(val)

        self.write(struct.pack('>HIII', FLAG, pw, r, i))

    def rand(self):
        state, idx = self.state['rand']
        state ^= struct.unpack('<H', self.magic_page[idx*2:idx*2+2])[0]
        state ^= struct.unpack('<H', self.magic_page[idx*2+4:idx*2+6])[0]
        idx = (idx + 4) & 0x3ff
        state *= 1234567
        state = np.uint32(state)
        self.state['rand'] = (state, idx)

        r = random_r()
        self.write(struct.pack('>HI', RAND, r))
        self.state['r'][r] = state

    def echo(self):
        value = None
        while value is None:
            value = random.randint(0, 0xFFFF)
            if value in RESERVED:
                value = None
        self.write(struct.pack('>H', value))
        self.read(length=4, expect=struct.pack('>I', value))

    def quit(self):
        self.retr_all()
        self.write(struct.pack('>H', QUIT))
