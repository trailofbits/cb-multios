#!/usr/bin/env python2

import random
import string
import struct
from generator.actions import Actions

if False:
    EOT = '\n'
else:
    EOT = '\x04'

USERNAME_MAX = 32
BLUB_MAX = 140


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

    def xlat_string(s, inverse=False, is_pcre=False):
        if is_pcre:
            return s
        if inverse:
            return ''.join([chr(self.xlat_map_inv[ord(c)]) if (not is_pcre or c not in '.*') else c for c in s])
        else:
            return ''.join([chr(self.xlat_map[ord(c)]) if (not is_pcre or c not in '.*') else c for c in s])
    self.xlat_string = xlat_string

    def read(delim=None, length=None, expect=None, expect_format=None):
        if self.xlat_map:
            if delim:
                delim = self.xlat_string(delim, is_pcre=expect_format)
            if expect:
                expect = self.xlat_string(expect, is_pcre=expect_format)
        return self._original_read(delim=delim, length=length, expect=expect, expect_format=expect_format)
    self._original_read = self.read
    self.read = read

    def write(s):
        if self.xlat_map:
            if s:
                s = self.xlat_string(s)
        return self._original_write(s)
    self._original_write = self.write
    self.write = write


class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        self.blubs = []
        self.username = self.rblub(30)
        kaprica_mixin(self)
        self.xlat_seed('9an538n9av3;5')

        sig = 0
        for i in xrange(0, 0x1000, 4):
            sig ^= struct.unpack('<I', self.magic_page[i: i + 4])[0]
        self.read(length=4, expect=struct.pack('<I', sig))

    def rblub(self, n=120):
        n = random.randint(10, n)
        s = ''
        for _ in xrange(n):
            s += random.choice(string.letters)
        return s

    def reg(self):
        self.write(self.username + EOT)
        self.read(delim=EOT, expect='Welcome to blubber, ' + self.username)

    def sub_self(self):
        self.prompt()
        self.write('s' + EOT + self.username + EOT)

    def branch(self):
        pass

    def blub(self):
        b = self.rblub()
        self.blubs.append(b)
        self.prompt()
        self.write('b' + EOT + b + EOT)
        self.read(length=5, expect='...: ')

    def read_unread(self):
        self.prompt()
        self.write('r' + EOT)
        self.read(length=4, expect=struct.pack('<i', len(self.blubs)))
        while len(self.blubs):
            b = self.blubs.pop(0)
            self.read(length=4, expect='.*', expect_format='pcre')
            self.read(length=len(self.username), expect=self.username)
            self.read(length=USERNAME_MAX - len(self.username), expect='.*', expect_format='pcre')
            self.read(length=len(b), expect=b)
            self.read(length=BLUB_MAX - len(b), expect='.*', expect_format='pcre')

    def nop(self):
        self.prompt()
        self.write('x' + EOT)

    def prompt(self):
        self.read(delim=EOT, expect='(*) ')

    def exit(self):
        self.write('e' + EOT)
