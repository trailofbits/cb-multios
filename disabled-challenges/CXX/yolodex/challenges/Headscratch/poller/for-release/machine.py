#!/usr/bin/env python

import random
import string
import struct

from generator.actions import Actions


class Machine(Actions):
    progs = {
        'tolower': '+[>,>++++[<++++++++>-]<.<]',
        'calc': '>>+[->,>+<-------------------------------------------[+++++++++++++++++++++++++++++++++++++++++++<]'
        '>>]<->>>>>+[->,>+<-------------------------------------------------------------[+++++++++++++++++++'
        '++++++++++++++++++++++++++++++++++++++++++<]>>]<<<<[<+<]+[<+>-<<[>-]>]<<[<+<]>[>]<[[->+>+[>+<->>[<-'
        ']<]>>[>]<+[<]+[<+>-<<[>-]>]<<-<]+[>+<->>[<-]<]>>[>]<<-<[<]+[<+>-<<[>-]>]<<-<]+[>+<->>[<-]<]>>[-----'
        '------------------------------------------->>]>-<<<[<<]++++++++++++++++++++++++++++++++++++++++++++'
        '++++[>>]<<<<[[>>->[>]>+>>>>>>>+<<<<<<<<<[<]><<]>+[>]>-[-<<[<]>+[>]>]>>>>>+>>>++++++++++++++++++++++'
        '++++++++++++++++++++++++++++++++++++<[->-[>]<<]<[-<<<<<<<[<]+>----------<<+>[>]>>>>>>]<[-<<<<<<<[<]'
        '+[>]>>>>>]>>>[-]>[-]<<<<<<<<<<[<]><<]>>------------------------------------------------[+++++++++++'
        '+++++++++++++++++++++++++++++++++++++.[-]]>>[.>>]++++++++++.'
    }

    def start(self):
        #self.delay(100)
        self.read(expect='Welcome to the headscratch interpreter.', delim='\n')
        self.read(expect='Enter your program to have it executed!', delim='\n')
        x1, x2 = struct.unpack('<II', self.magic_page[4:12])
        self.read(expect='%u' % (x1 ^ x2), delim='\n')

    def stub(self):
        pass

    def do_tolower(self):
        self.write(self.progs['tolower'] + '\n')

        for _ in xrange(10):
            test_string = ''.join(random.sample(string.letters, 8))
            self.write(test_string.upper() + '\x04')
            self.read(length=len(test_string) + 1, expect=test_string.lower() + '$')
        self.write('\x00')

    def do_calc(self):
        self.write(self.progs['calc'] + '\n')

        n1 = 0
        n2 = 0
        for i in xrange(random.randint(1, 7)):
            n1 += (10 ** i) * random.randint(1, 9)
            n2 += (10 ** i) * random.randint(1, 9)

        assert(len(str(n1)) == len(str(n2))), (n1, n2)
        expr = str(n1) + '+' + str(n2) + '='

        self.write(expr + '\n')
        self.read(expect=str(n1 + n2), delim='\n')

    def finish(self):
        self.read(expect='\x43\x47\xc0\x00', length=4)
