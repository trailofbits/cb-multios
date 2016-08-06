#!/usr/bin/env python

from generator.actions import Actions
from random import randint, choice
from struct import pack
from io import BytesIO
import ctypes
import sys

class Protocol():
    def empty_frame(self, id):
        return pack('<2L', id, 0)
    def frame(self, id, data):
        return pack('<2L', id, len(data)) + data

class ChurnItem(ctypes.Union):
    _fields_ = [("i", ctypes.c_ulonglong),
                ("f", ctypes.c_double)]

ChurnInitializerArray = ctypes.c_longlong * 4
ChurnInitializer = ctypes.POINTER(ChurnInitializerArray)

class Gyre():
    def __init__(self):
        #self.dll = ctypes.CDLL('build/patched/so/CROMU_90001.so')
        self.dll = ctypes.CDLL('build/patched/so/CROMU_00020.so')

        self.churn_initialize = self.dll.churn_initialize
        self.churn_initialize.argtypes = [ChurnInitializer]

        self.churn_read_uint32 = self.dll.churn_rand_uint32
        self.churn_read_uint32.restype = ctypes.c_uint

        self.churn_read_uint64 = self.dll.churn_rand_uint64
        self.churn_read_uint64.restype = ctypes.c_ulonglong
    def seed(self, churn_items):
        if len(churn_items) != 4:
            raise "nope"
        self.churn_initialize(churn_items)
    def random_seed(self):
        return randint(0, 2**60)

class Estadio(Actions):
    def start(self):
        self.g = Gyre()
        self.p = Protocol()
    def hello(self):
        self.read(length=8, expect=self.p.empty_frame(0))
        self.write(self.p.empty_frame(0))
    def seed(self):
        seeds = ChurnInitializerArray(0,0,0,0)
        seeds[0] = self.g.random_seed()
        seeds[1] = self.g.random_seed()
        seeds[2] = self.g.random_seed()
        seeds[3] = self.g.random_seed()
        self.g.seed(seeds)
        self.write(self.p.frame(1, pack('<4Q', *seeds)))
        self.read(length=8, expect=self.p.empty_frame(2))
    def gauntlet(self):
        for x in xrange(0, 32):
            self.write(self.p.frame(20, pack('<Q', self.g.churn_read_uint64())))
            self.read(length=8, expect=self.p.empty_frame(21))
    def fail_gauntlet(self):
        fail_at = randint(0, 30)
        for x in xrange(0, 32):
            if (x == fail_at):
                self.write(self.p.frame(20, pack('<Q', self.g.churn_read_uint64() + 1)))
                return
            else:
                self.write(self.p.frame(20, pack('<Q', self.g.churn_read_uint64())))
                self.read(length=8, expect=self.p.empty_frame(21))
    def menu(self):
        self.comment("at menu")
    def guess(self):
        self.write(self.p.frame(20, pack('<Q', self.g.churn_read_uint64())))
        self.read(length=8, expect=self.p.empty_frame(21))
    def wrong_guess(self):
        self.write(self.p.frame(20, pack('<Q', self.g.churn_read_uint64() + 1)))
    def echo(self):
        length = randint(1, 78)
        s = BytesIO()

        for x in xrange(0, length):
            s.write(pack('b', randint(32, 126)))
        s.write(pack('b', 0))

        s.seek(0)
        self.write(self.p.frame(30, s.read()))

        expect_length = length + 1 + 8

        s.seek(0)
        self.read(length=expect_length, expect=self.p.frame(31, s.read()))
    def reseed(self):
        seeds = ChurnInitializerArray(0,0,0,0)
        seeds[0] = self.g.random_seed()
        seeds[1] = self.g.random_seed()
        seeds[2] = self.g.random_seed()
        seeds[3] = self.g.random_seed()
        self.g.seed(seeds)
        self.write(self.p.frame(1, pack('<4Q', *seeds)))
        self.read(length=8, expect=self.p.empty_frame(2))
    def terminate(self):
        self.write(self.p.empty_frame(9))
