from generator.actions import Actions
import random
import string
import struct
import numpy as np
import math
import datetime as dt
import ctypes

def kaprica_mixin(self):
    if hasattr(self, 'xlat_seed'):
        return

    def xlat_seed(seed):
        def hash_string(seed):
            H = 0x314abc86
            for c in seed:
                H = (H * 37) & 0xffffffff
                H ^= ord(c)
                H = ((H << 13) ^ (H >> 19)) & 0xffffffff
            return H
        def hash_iterate(H):
            H = (H * 3) & 0xffffffff
            H = ((H << 13) ^ (H >> 19) ^ (H >> 21)) & 0xffffffff
            return H
        xmap = list(xrange(256))
        xmap_inv = list(xrange(256))
        state = hash_string(seed)
        for i in xrange(255, 0, -1):
            j = state % i
            state = hash_iterate(state)
            xmap[i], xmap[j] = xmap[j], xmap[i]
        for i in xrange(256):
            xmap_inv[xmap[i]] = i
        self.xlat_map = xmap
        self.xlat_map_inv = xmap_inv
    self.xlat_seed = xlat_seed
    self.xlat_map = None
    self.xlat_map_inv = None

    def xlat_string(s, inverse=False):
        if inverse:
            return ''.join([chr(self.xlat_map_inv[ord(c)]) for c in s])
        return ''.join([chr(self.xlat_map[ord(c)]) for c in s])
    self.xlat_string = xlat_string

    def read(delim=None, length=None, expect=None):
        if self.xlat_map:
            if delim:
                delim = self.xlat_string(delim)
            if expect:
                expect = self.xlat_string(expect)
        return self._original_read(delim=delim, length=length, expect=expect)
    self._original_read = self.read
    self.read = read

    def write(s):
        if self.xlat_map:
            if s:
                s = self.xlat_string(s)
        return self._original_write(s)
    self._original_write = self.write
    self.write = write

def random_word(max_size=10, min_size=2):
    if random.randint(0,4):
        characters = string.letters + string.digits
    else:
        characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ("".join(random.choice(characters) for c in range(max_size))).lower()

def random_text(max_words=10, min_words=3):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
    return text


class Cs10Fun(Actions):
    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _read_array(self, array=None):
        if not array:
            array = self._cur_array
        if not len(array):
            self._read("Empty Array\n")
        else:
            self._read("Array data\n")
            temp_list = []
            for val in array:
                temp_list.append("%d, " % val)
            temp_list[-1] = temp_list[-1][:-2]
            self._read("[" + ''.join(temp_list) + ']\n')

    def start(self):
        #self.delay(100)
        kaprica_mixin(self)
        self.xlat_seed('2e0715f1709c')

        self.write(self.magic_page[:4])
        self.read(length=0x1000, expect=self.magic_page)

        self._cur_array = []
        self._read("Welcome to CS10Fun!\n")
        self._read("Today's lesson is on sorting! We're going to cover 4 types of sorts.\n")
        self._read("Before we begin, create an array of ints\n")

        self.menu()
        self.enter_array()

    def menu(self):
        self._read("Main Menu\n")
        self._read("1. Enter Array\n")
        self._read("2. Multiply Array\n")
        self._read("3. Try Insertion Sort\n")
        self._read("4. Try Selection Sort\n")
        self._read("5. Try Heap Sort\n")
        self._read("6. Try Merge Sort\n")
        self._read("7. Reprint Array\n")
        self._read("0. Exit\n")
        self._read("   -----\n")
        self._read("Current Number of items in array = %d\n" % len(self._cur_array))
        #self._read_array()
        self._read("   -----\n")
        self._read("Make a selection\n")

    def enter_array(self):
        self.write('1\n')
        self._read("Enter a list of numbers to sort. End the list with ';;'\n")
        self._cur_array = []
        for x in xrange(random.randint(1,100)):
            self._cur_array.append(random.randint(-1000000000, 1000000000))
        self.write(','.join([str(x) for x in self._cur_array]) + ',;;\n')
        self._read("New Array\n")
        self._read("Number of items in array = %d\n" % len(self._cur_array))
        self._read_array()

    def multiply_array(self):
        self.write('2\n')

        if len(self._cur_array) > 10000:
            self._read("Array is too long. Can't multiply any more\n")
        elif len(self._cur_array):
            self._read("Quick Grow! Enter a list multiplier. End number with ';'\n")
            multiplier = random.randint(1,3)
            while multiplier * len(self._cur_array) > 1024 and multiplier * len(self._cur_array) <= 1048:
                multiplier = random.randint(1,3)
            self.write("%d;\n" % multiplier)
            self._cur_array *= multiplier
        self._read("Multiplied Array\n")
        self._read("Number of items in array = %d\n" % len(self._cur_array))
        self._read_array()

    def insert_sort(self):
        self.write('3\n')
        self._read_array(sorted(self._cur_array))
        #self.read(expect='Insertion sort takes [\d]+ operations\n', expect_format='pcre', delim='\n')
        self.read(delim='\n')

    def selection_sort(self):
        self.write('4\n')
        self._read_array(sorted(self._cur_array))
        #self.read(expect='Selection sort takes [\d]+ operations\n', expect_format='pcre', delim='\n')
        self.read(delim='\n')

    def heap_sort(self):
        self.write('5\n')
        self._read_array(sorted(self._cur_array))
        #self.read(expect='Heap sort takes [\d]+ operations\n', expect_format='pcre', delim='\n')
        self.read(delim='\n')

    def merge_sort(self):
        self.write('6\n')
        self._read_array(sorted(self._cur_array))
        #self.read(expect='Merge sort takes [\d]+ operations\n', expect_format='pcre', delim='\n')
        self.read(delim='\n')

    def reprint_array(self):
        self.write('7\n')
        self._read("Current Array\n")
        self._read("Number of items in array = %d\n" % len(self._cur_array))
        self._read_array()

    def exit(self):
        self.write('0\n')
        self._read("Thanks for joining us\n")
        self._read("See you next time\n")

