#!/usr/bin/env python
#
# Copyright (c) 2014 Jason L. Wright (jason@thought.net)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

from generator.actions import Actions
import random
import string
import re
import sys

def random_string(size):
    chars = string.letters + string.digits
    return ''.join(random.choice(chars) for _ in range(size))

class PetPoller(Actions):
    pettypes = { 'cat' : { 'rollover' : 'will not roll over',
                           'flush' : 'purrs takes a nap',
                           'speak' : 'meows' },
                 'dog' : { 'rollover' : 'rolls over',
                           'speak' : 'barks',
                           'flush' : 'goes to sleep... permanently' },
                 'hotdog' : { 'rollover' : 'rolls over on the grill',
                              'speak' : 'can\'t speak',
                              'flush' : 'tastes great with ketchup and mustard'}}

    def start(self):
        self.pets = []
        self.go_read(expect='ctors called...\n')
        self.go_read(expect='list init...\n')
        self.seq = random.randint(-sys.maxint - 1, sys.maxint)

    def main(self):
        pass

    def create_and_name(self):
        d = {}
        d['type'] = random.choice(self.pettypes.keys())
        d['name'] = random_string(random.randint(1, 150))
        self.go_write('%d create %s\n' % (self.seq, d['type']))
        self.seq += 1
        self.go_read(expect='init..\n')
        self.go_write('%d name %d %s\n' % (self.seq, len(self.pets), d['name']))
        self.seq += 1
        self.pets.append(d)

    def debug(self):
        self.go_write('%d debug\n' % (self.seq))
        self.seq += 1
        if len(self.pets) == 0:
            pass
        else:
            for p in self.pets:
                self.read(delim='\n', expect=r'^[a-f0-9]{8} [a-f0-9]{8}\n$',
                          expect_format='pcre')

    def delete(self):
        if len(self.pets) == 0:
            self.go_write('%d delete %d\n' % (self.seq, 0))
            self.seq += 1
            self.go_read(expect="you don't have any pets\n")
        else:
            if len(self.pets) == 1:
                n = 0
            else:
                n = random.randrange(0, len(self.pets)-1)

            self.go_write('%d delete %d\n' % (self.seq, n))
            self.seq += 1
            p = self.pets.pop(n)
            m = p['name'] + ' ' + self.pettypes[p['type']]['flush'] + "\n"
            self.go_read(expect=m)

    def rollover(self):
        self.go_write('%d rollover\n' % (self.seq))
        self.seq += 1
        for p in self.pets:
            m = p['name'] + ' ' + self.pettypes[p['type']]['rollover'] + "\n"
            self.go_read(expect=m)

    def speak(self):
        self.go_write('%d speak\n' % (self.seq))
        self.seq += 1
        for p in self.pets:
            m = p['name'] + ' ' + self.pettypes[p['type']]['speak'] + "\n"
            self.go_read(expect=m)
    
    def done(self):
        pass

    def go_write(self, s):
        self.write(s)

    def go_read(self, expect):
        self.read(expect=expect, length=len(expect))
