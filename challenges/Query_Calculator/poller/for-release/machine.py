#!/usr/bin/env python

from generator.actions import Actions
import random
from struct import pack, unpack
import ctypes

class Cqltor(Actions):
    def start(self):
       #self.delay(100)
       magic_prefix = self.magic_page[0:4]
       chk = sum(map(lambda c: ord(c), magic_prefix))
       self.expect_str("cqltor ready " + str(chk))

    def menu(self):
        self.comment("menu")

    def intmath(self):
        self.comment("intmath")

        pairs = map(lambda _x:
                  str(random.randint(1,64)) +
                    " " +
                    random.sample(["+", "-", "/", "*"], 1)[0],
                    xrange(random.randint(2,4)))

        math = " ".join(pairs)[0:-2]
        goal = eval(math)
        
        # print math, "=", goal
        
        self.send("FIND " + math + " FROM dual")
        self.expect_str(str(goal))

    def strfuns(self):
        self.comment("strfuns")

        in_strlen = random.randint(4, 32)

        start_spaces = ' ' * random.randint(0, 5)
        end_spaces   = ' ' * random.randint(0, 5)
        
        in_text = (
            start_spaces +
            ''.join(map(lambda _x:
                        chr(random.randint(0x41, 0x7a)),
                        xrange(in_strlen))) +
            end_spaces)

        case_fun = 'upcase'
        cased_text = in_text.upper()
        if random.choice([True, False]):
            case_fun = 'downcase'
            cased_text = in_text.lower()

        chomped_text = cased_text.strip()

        resolver = random.randint(1, 3)
        # if 1 == resolver:
        pos = random.randint(0, len(chomped_text) - 1)
        expect = ord(chomped_text[pos])
        qry = (
            'ord(chomp(' +
            case_fun +
            '(\'' +
            in_text +
            '\')), ' +
            str(pos + 1) +
            ')')
        if 2 == resolver:
            needle = chomped_text[pos]
            found = chomped_text.find(needle)
            expect = found + 1
            qry = (
                'idx(chomp(' +
                case_fun +
                '(\'' +
                in_text +
                '\')), \'' +
                needle +
                '\')')
        if 3 == resolver:
            needle = chomped_text[pos]
            found = chomped_text.rfind(needle)
            expect = found + 1
            qry = (
                'ridx(chomp(' +
                case_fun +
                '(\'' +
                in_text +
                '\')), \'' +
                needle +
                '\')')

        # print qry, '=', expect
        self.send('FIND ' +
                  qry +
                  'FROM asdf')
        self.expect_str(str(expect))
        
    def disconnect(self):
        self.comment("disconnect")
        self.send("exit")
    
    def wrap(self, message):
        return pack('<H', len(message)) + message
    def send(self, message):
        self.comment('sent %d bytes', len(message) + 2)
        self.write(self.wrap(message))
    def expect_str(self, message):
        msg = self.wrap(message)
        self.read(length=len(msg), expect=msg)
