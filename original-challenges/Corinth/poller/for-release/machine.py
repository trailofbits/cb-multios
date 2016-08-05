#!/usr/bin/env python

from generator.actions import Actions
import random
from struct import pack, unpack
import ctypes
from ctypes import c_double, c_byte, c_uint64
from math import log10, sqrt, sin
from copy import copy
from array import array
from binascii import hexlify

class Monte():
    def __init__(self):
        self.dll = ctypes.CDLL('build/patched/so/CROMU_00073.so')

        self.monte_gen_step = self.dll.monte_gen_step
        self.monte_gen_step.argtypes = [c_double, c_uint64, c_double, c_double]
        self.monte_gen_step.restype = c_double
        
        self.monte_adjust = self.dll.monte_adjust
        self.monte_adjust.argtypes = [c_double, c_double]

        self.monte_happy = self.dll.monte_happy
        self.monte_happy.restype = c_byte

        self.check_random_params = self.dll.check_random_params
        self.check_random_params.argtypes = [c_double, c_uint64, c_double, c_double]
        self.check_random_params.restype = c_byte

        self.kajigger_from_random_int = self.dll.kajigger_from_random_int
        self.kajigger_from_random_int.argtypes = [c_uint64]
        self.kajigger_from_random_int.restype = c_double
        
class Corinth(Actions):
    def start(self):
        #self.delay(100)
        self.PI = 3.14126535

        self.m = Monte()
        self.counter = 0
        self.counter_max = 0x100

        self.splatter = 128.0
        self.scaler = 1.0

        self.monte_initialize()

    def hello(self):
        expectation = self.hello_expectation()
        self.read(length=len(expectation), expect=expectation)

    def monte_check(self):
        self.comment("monte check")

    def monte_okay(self):
        scaler_goal = 0.4

        self.scaler = scaler_goal + (random.random() * 0.0001)
        self.splatter = random.randint(1, 255)

        scaler_del = random.random() * 0.1

        max_result = -1
        # print self.kajigger
        while True:
            result = self.m.check_random_params(self.kajigger,
                                                self.counter,
                                                self.splatter,
                                                self.scaler)

            if result > max_result:
                max_result = result
            
            if result > 20:
                self.doubler_size = result
                # print self.scaler, self.splatter
                self.comment("okay: scaler %.10f splatter %.10f", self.scaler, self.splatter)
                break
            
            if self.scaler > (scaler_goal + 0.2):
                # print self.scaler, scaler_del, max_result
                scaler_del = - abs(scaler_del / 2)
                self.scaler = (scaler_goal + 0.2)
                max_result = -1
            elif self.scaler < scaler_goal:
                # print self.scaler, scaler_del, max_result
                scaler_del = abs(scaler_del / 2)
                self.scaler = scaler_goal
                max_result = -1

            self.scaler = self.scaler + scaler_del
            self.splatter = random.random() * 10000

        in_circle = 0
        
        for i in xrange(0x1000):
            n1 = self.monte_gen()
            n2 = self.monte_gen()
            dist = sqrt((n1 * n1) + (n2 * n2))
            if dist < 1:
                in_circle += 1

        self.comment("in %d tot %d ratio %f want %f",
                     in_circle,
                     0x1000,
                     float(in_circle) / 0x1000,
                     (self.PI / 4))
            
        self.comment("okay: buf %d", self.doubler_size)
        self.write(pack('<BHdd', 10, 16, self.splatter, self.scaler))

        expectation = pack('<BHB', 11, 1, self.doubler_size)
        self.read(length=len(expectation),
                  expect=expectation)
        
    def monte_fail(self):
        self.scaler = random.random()
        self.splatter = random.randint(1, 255)

        # print self.kajigger
        while True:
            result = self.m.check_random_params(self.kajigger,
                                                self.counter,
                                                self.splatter,
                                                self.scaler)
            
            if result < 20:
                self.doubler_size = result
                # print self.scaler, self.splatter
                self.comment("fail: scaler %.10f splatter %.10f", self.scaler, self.splatter)
                break
            
            self.scaler = random.random()
            self.splatter = random.randint(1, 255)

            
        self.write(pack('<BHdd', 10, 16, self.splatter, self.scaler))

        expectation = pack('<BHB', 11, 1, self.doubler_size)
        self.read(length=len(expectation),
                  expect=expectation)

        self.write(pack('<BHs', 20, 1, 'x'))

    def menu(self):
        magic_prefix = self.magic_page[0:4]
        self.comment("menu: counter %d magic %s", 
                     self.counter, 
                     hexlify(magic_prefix))

    def query(self):
        expected_number = self.monte_gen()
        self.comment("query: expect %f", expected_number)
        
        request = pack('<BH', 30, 0)
        self.write(request)
        expected_response = pack('<BHd',
                                 31,
                                 8,
                                 expected_number)
        self.read(length=len(expected_response),
                  expect=expected_response)

    def doubler(self):
        in_circle = 0
        initial_counter = self.counter
        for i in xrange(0x1000):
            n1 = self.monte_gen()
            n2 = self.monte_gen()
            dist = sqrt((n1 * n1) + (n2 * n2))
            if dist < 1:
                in_circle += 1

        ratio = float(in_circle) / 0x1000
        diff = abs((4 * ratio) - self.PI)
        intermediate = int(40 * log10(1.0 / diff))
        my_doubler_size = intermediate - (intermediate % 8)
        
        self.comment("doubler: can double %d", my_doubler_size)

        if (my_doubler_size < 2):
            self.counter = initial_counter
            return
        
        len_to_double = random.randint(1, my_doubler_size)
        
        str_to_double = ''.join(map(lambda _x: chr(random.randint(65, 90)),
                                    xrange(len_to_double)))

        doubled_str = str_to_double * 2
        
        payload = pack('<BH', 20, len_to_double) + str_to_double
        resp = pack('<BH', 21, 2 * len_to_double) + doubled_str

        self.write(payload)
        self.read(length=len(resp), expect=resp)

    def terminate(self):
        self.comment("terminate")
        payload = pack('<BH', 9, 0)
        self.write(payload)

    def menu_error(self):
        id = random.randint(40, 127)
        payload = pack('<BH', id, 0)

        self.comment("menu error: id %d", id)
        self.write(payload)

        resp = pack('<BHB', 1, 1, id)
        self.read(length=len(resp),
                  expect=resp)

    def monte_initialize(self):
        self.splatter = 128.0
        self.scaler = 1.0
        self.m.monte_adjust(self.splatter, self.scaler)

        kajigger_input = self.magic_page[0:8]
        kajigger_int = unpack('=Q', kajigger_input)[0]
        self.kajigger = self.m.kajigger_from_random_int(kajigger_int)
        sine = sin(float(kajigger_int))
        sine_int = unpack('<Q', pack('<d', sine))[0]
        masked_sine_int = sine_int & 0xffffffffffffff00
        masked_sine_float = unpack('<d', pack('<Q', masked_sine_int))[0]
        self.counter = 0
        self.comment("kajigger: %f %s %s",
                     float(self.kajigger),
                     kajigger_input,
                     pack('<dd', self.kajigger, masked_sine_float))

    def monte_initialize_step(self, chunk, idx):     
        chunk_f = self.m.monte_float_cast(unpack('b', chunk)[0])
        return self.m.monte_initialize_step(chunk_f, idx)

    def hello_expectation(self):
        rng = self.monte_gen()

        self.comment("hello: rng %f", rng)
        return pack('<BHd', 0, 8, rng)

    def monte_gen(self):
        result = self.m.monte_gen_step(self.kajigger,
                                       self.counter,
                                       self.splatter,
                                       self.scaler)
        self.counter += 1
        if self.counter >= self.counter_max:
            self.counter = 0

        return result
