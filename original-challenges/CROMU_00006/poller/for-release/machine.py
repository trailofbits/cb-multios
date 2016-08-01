#!/usr/bin/env python

from generator.actions import Actions
from random import randint
from struct import pack
import ctypes

class CharterMath():
    def __init__(self):
        self.dll = ctypes.CDLL('build/patched/so/CROMU_00006.so')

        self.scale_factor = self.dll.bar_scale_factor
        self.scale_factor.argtypes = [ctypes.c_uint, ctypes.c_uint]
        self.scale_factor.restype = ctypes.c_double

        self.use_columns = self.dll.bar_use_columns
        self.use_columns.argtypes = [ctypes.c_uint, ctypes.c_double, ctypes.c_uint]
        self.use_columns.restype = ctypes.c_uint

        self.divisor = self.dll.spark_divisor
        self.divisor.argtypes = [ctypes.c_uint, ctypes.c_uint, ctypes.c_uint]
        self.divisor.restype = ctypes.c_double

        self.pick_index = self.dll.spark_pick_index
        self.pick_index.argtypes = [ctypes.c_uint, ctypes.c_uint, ctypes.c_double]
        self.pick_index.restype = ctypes.c_uint

class Grapher(Actions):
    def w(self, *data):
        dl = len(data)
        self.write(pack('<' + dl * 'L', *data))

    def start(self):
        # try to not send too much data over the wire
        self.state['max_value'] = max_value = randint(10, 2**8)
        # generate data
        self.state['data'] = [randint(0, max_value) for x in xrange(randint(1, 32))]
        self.m = CharterMath()

    def send_data(self):
        self.w(len(self.state['data']))
        self.w(*self.state['data'])

    def menu(self):
        self.read(length=4, expect="CHRT")
        self.read(length=4, expect=pack('<L', len(self.state['data'])))

    def sparks(self):
        self.w(1)
        sparks = xrange(0x2581, 0x2588)
        self.w(len(sparks))
        packed_sparks = pack('<' + len(sparks) * 'L', *sparks)
        self.write(packed_sparks)
        
        data = self.state['data']
          
        d_min = min(data)
        d_max = max(data)
        expectation = ''

        if (d_min == d_max):
            expectation = pack('<L', sparks[-1]) * len(data)
        else:
            div = self.m.divisor(d_max, d_min, len(sparks))
            for datum in data:
                  idx = self.m.pick_index(datum, d_min, div)
                  if idx >= len(sparks):
                      idx = len(sparks) - 1
                  expectation += pack('<L', sparks[idx])
                  
        self.read(length=4*len(data))

    def bars(self):
        self.w(3)
        data = self.state['data']
        max = self.state['max_value'] * 2
        cols = randint(0, 64)
        sym_b = randint(33, 126)
        sym = pack('<B', sym_b)
        
        self.w(max)
        self.w(cols)
        self.w(sym_b)
        
        scale = self.m.scale_factor(cols, max)
        for datum in data:
            use = self.m.use_columns(datum, scale, cols)
            self.read(length=(int(use) + 1), expect=((sym * int(use)) + "\n"))

    def echo(self):
        self.w(4)
        count = randint(1, 64)
        self.w(count)
        expectation = ''
        for _n in xrange(count):
            expectation += pack('<L', randint(0, (2**32)-1))
        self.write(expectation)
        self.read(length=(count*4), expect=expectation)

    def seed(self):
        self.w(5)
        self.state['seed'] = randint(0, 2**32)
        self.w(self.state['seed'])
        self.read(length=4)

    def noise(self):
        self.w(6)
        q = randint(8, 64)
        self.w(q)
        self.read(length=(q - (q % 4)))

    def tainted_menu(self):
        self.menu()

    def tainted_sparks(self):
        self.sparks()

    def tainted_bars(self):
        self.w(3)
        max = self.state['max_value']
        cols = randint(0, 128)
        sym = pack('<L', randint(33, 126))
        
        self.w(max)
        self.w(cols)
        self.write(sym)
        
        for _datum in self.state['data']:
            self.read(delim="\n")

    def tainted_echo(self):
        self.echo()
        
    def tainted_noise(self):
        self.noise()

    def tainted_replacer(self):
        self.w(7)

    def terminate(self):
        self.w(randint(8, 2**31))
