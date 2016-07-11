#!/usr/bin/env python

from generator.actions import Actions
from random import randint, choice
from struct import pack
import ctypes
import sys

class Protocol():
    def empty_frame(self, id):
        return self.frame(id, '')
    def frame(self, id, data):
        return pack('<2B', id, len(data)) + data

class ScrambleItem(ctypes.Union):
    _fields_ = [("i", ctypes.c_uint32),
                ("f", ctypes.c_float)]

class Scrambler():
    def __init__(self):
        self.dll = ctypes.CDLL('build/patched/so/CROMU_00028.so')

        self.initialize_phases()
    def initialize_phases(self):
        self.phases = list(xrange(8))
        scramble_args = [ScrambleItem, ScrambleItem]
        for i in xrange(8):
            f = self.dll.__getattr__('phase_'+str(i))
            f.argtypes = scramble_args
            f.restype = ScrambleItem
            self.phases[i] = f
    def find_evil(self):
        return [243, 0, 60, 0, 25, 0, 155, 0]
        evils = list(xrange(8))
        desired = 21
        for i in xrange(7, -1, -1):
            # print "phase", i, "desired", desired
            found = False

            for j in xrange(2**16):
                current = j >> 8
                my_state = j & 0xFF
                first = current
                second = my_state

                if (i % 2 != 0):
                    second = current
                    first = my_state

                new_state = self.phases[i](ScrambleItem(i=first),
                                           ScrambleItem(i=second)).i & 0xFF
                
                # print "\r", new_state,
                
                if (new_state == desired) & (my_state == 0) & (i == 0):
                    continue
                if new_state == desired:
                    # print "\r",
                    # print "input", current, "instate", my_state
                    evils[i] = current
                    desired = j & 0xFF
                    found = True
                    break
            if not found:
                raise StandardError("couldn't find an evil thing :(")
        print evils
        return evils

class Carbonate(Actions):
    cell_count = 4096 * 2**3
    
    def start(self):
        self.p = Protocol()
        self.s = Scrambler()
        self.set = set()

    def hello(self):
        self.comment("hello")
        self.read(length=2, expect=self.p.empty_frame(0))
        self.write(self.p.empty_frame(0))

    def scramble(self):
        for i in xrange(8):
            idk = randint(0, 2**8 - 1)
            self.comment("scramble step %d sending %d", i, idk)
            self.write(self.p.frame(1, pack('<H', idk)))
            self.read(length=2, expect=self.p.empty_frame(2))

    def scramble_evil(self):
        evils = self.s.find_evil()
        self.comment("using evils %s", str(evils))
        for i in evils:
            self.write(self.p.frame(1, pack('<H', i)))
            self.read(length=2, expect=self.p.empty_frame(2))

    def menu(self):
        self.comment("at menu")

    def check_find(self):
        if len(self.set) == 0:
            self.comment("check_find on empty set")
            return
        candidate = choice(list(self.set))
        self.comment("check_find for %d", candidate)
        self.write(self.p.frame(16, pack('<H', candidate)))
        self.read(length=2, expect=self.p.empty_frame(17))

    def check_missing(self):
        candidate = randint(0, self.cell_count)
        while candidate in self.set:
            candidate = randint(0, self.cell_count)
        self.comment("check_missing for %d", candidate)
        self.write(self.p.frame(16, pack('<H', candidate)))
        self.read(length=2, expect=self.p.empty_frame(18))

    def add_new(self):
        candidate = randint(0, self.cell_count)
        while candidate in self.set:
            candidate = randint(0, self.cell_count)
        self.comment("add_new for %d", candidate)
        self.set.add(candidate)
        self.write(self.p.frame(32, pack('<H', candidate)))
        self.read(length=2, expect=self.p.empty_frame(33))

    def add_exists(self):
        if len(self.set) == 0:
            self.comment("add_exists on empty set")
            return
        candidate = choice(list(self.set))
        self.comment("add_existing for %d", candidate)
        self.write(self.p.frame(32, pack('<H', candidate)))
        self.read(length=2, expect=self.p.empty_frame(33))

    def subtract_find(self):
        if len(self.set) == 0:
            self.comment("subtract_find on empty set")
            return
        candidate = choice(list(self.set))
        self.comment("subtract_find for %d", candidate)
        self.set.remove(candidate)
        self.write(self.p.frame(48, pack('<H', candidate)))
        self.read(length=2, expect=self.p.empty_frame(49))

    def subtract_missing(self):
        candidate = randint(0, self.cell_count)
        while candidate in self.set:
            candidate = randint(0, self.cell_count)
        self.comment("subtract_missing for %d", candidate)
        self.write(self.p.frame(48, pack('<H', candidate)))
        self.read(length=2, expect=self.p.empty_frame(49))

    def clear(self):
        self.comment("clear")
        self.set = set()
        self.write(self.p.empty_frame(64))
        self.read(length=2, expect=self.p.empty_frame(65))

    def terminate(self):
        self.comment("Terminating")
