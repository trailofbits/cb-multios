#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

from generator.actions import Actions, Variable
from random import choice, randint
from os.path import dirname, abspath, join
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from common import DEBUG, CONFIG
from breakfast import Liquids, Cereals, Toppings, \
                        GenericString, PrinterString, CommandRunner

class TemplatePoller(Actions):

    PLACE_BOWL_MSG      = '\x11\xd1\xe0\xa4'
    ADD_CEREAL_MSG      = '\xec\xdf\x01\xbb'
    ADD_LIQUID_MSG      = '\xba\xfd\xff\x03'
    ADD_TOPPING_MSG     = '\xca\x0d\xcc\xf1'
    BREAKFAST_READY_MSG = '\x3a\xcc\x00\xe8'

    INITIAL_ORDER_ID        = 4242
    INPUT_TYPE_PLAIN        = '\xdd\x11\x44\xaa'
    INPUT_TYPE_SERIALIZED   = '\x00\xaa\xdd\x11'

    OK      = ''
    ERR     = ''


    def _gen_status_msgs(self):
        ok = [0,0,0,0]
        err = [0,0,0,0]
        for idx in [c for c in range(len(self.magic_page)) if c % 2 == 0]:
            ok[idx % 4] ^= ord(self.magic_page[idx])
            err[(idx+1) % 4] ^= ord(self.magic_page[idx+1])
        self.OK  = ''.join([chr(c) for c in ok])
        self.ERR = ''.join([chr(c) for c in err])

    def _create_stream(self, content_buf, type_buf):
        b = type_buf
        b += sp.pack_single_uint16(len(content_buf))
        b += content_buf
        return b

    def create_random_breakfast(self, item_count):
        b = []
        for idx in range(item_count):
            item_type = choice([Liquids, Cereals, Toppings])
            item = item_type()
            item.rand_content()
            b.append(item)
        return b

    def create_random_pov(self, types):
        p = []
        for t in types:
            item = t()
            item.rand_content()
            p.append(item)
        return p

    def make_plain_content(self, breakfast):
        content = ''
        for item in breakfast:
            content += item.get_plain_content()
        return content

    def make_serialized_content(self, breakfast):
        content = ''
        for item in breakfast:
            content += item.get_serialized_content()
        return content


    def start(self):
        if DEBUG:
            print "------- start -----------"
        self._gen_status_msgs()
        self.order_id = self.INITIAL_ORDER_ID

    def plain(self):
        '''
        Communicate using plain data (not serialized).
        '''
        if DEBUG:
            print "cmd: plain -----------"

        breakfast = self.create_random_breakfast(randint(3,16))
        breakfast = list(set(breakfast)) # rm dups
        content = self.make_plain_content(breakfast)
        stream = self._create_stream(content, self.INPUT_TYPE_PLAIN)
        self.write(stream)

        read_buf = sp.pack_single_int32(self.order_id)
        read_buf += self.PLACE_BOWL_MSG
        if any( isinstance(item, Cereals) for item in breakfast ):
            read_buf += self.ADD_CEREAL_MSG
        if any( isinstance(item, Liquids) for item in breakfast ):
            read_buf += self.ADD_LIQUID_MSG
        if any( isinstance(item, Toppings) for item in breakfast ):
            read_buf += self.ADD_TOPPING_MSG

        read_buf += self.BREAKFAST_READY_MSG
        read_buf += self.OK
        self.read(length=len(read_buf), expect=read_buf)

        self.order_id += 1

        return 0

    def serialized(self):
        '''
        Communicate using serialized data.
        '''
        if DEBUG:
            print "cmd: serialized -----------"

        breakfast = self.create_random_breakfast(randint(3,16))
        breakfast = list(set(breakfast)) # rm dups
        content = self.make_serialized_content(breakfast)
        stream = self._create_stream(content, self.INPUT_TYPE_SERIALIZED)
        self.write(stream)

        read_buf = sp.pack_single_int32(self.order_id)
        read_buf += self.PLACE_BOWL_MSG
        if any( isinstance(item, Cereals) for item in breakfast ):
            read_buf += self.ADD_CEREAL_MSG
        if any( isinstance(item, Liquids) for item in breakfast ):
            read_buf += self.ADD_LIQUID_MSG
        if any( isinstance(item, Toppings) for item in breakfast ):
            read_buf += self.ADD_TOPPING_MSG

        read_buf += self.BREAKFAST_READY_MSG
        self.read(length=len(read_buf), expect=read_buf)
        # read_buf += self.OK
        self.read(length=4)

        self.order_id += 1

        return 0

    def serialized_pov(self):
        '''
        Communicate using serialized data containing POV.
        '''
        if DEBUG:
            print "cmd: serialized pov -----------"

        breakfast = self.create_random_breakfast(randint(3,8))
        breakfast = list(set(breakfast)) # rm dups
        # breakfast += self.create_random_pov([GenericString, PrinterString, CommandRunner])
        breakfast += self.create_random_pov([CommandRunner])
        content = self.make_serialized_content(breakfast)
        stream = self._create_stream(content, self.INPUT_TYPE_SERIALIZED)
        self.write(stream)

        read_buf = sp.pack_single_int32(self.order_id)
        read_buf += self.PLACE_BOWL_MSG
        if any( isinstance(item, Cereals) for item in breakfast ):
            read_buf += self.ADD_CEREAL_MSG
        if any( isinstance(item, Liquids) for item in breakfast ):
            read_buf += self.ADD_LIQUID_MSG
        if any( isinstance(item, Toppings) for item in breakfast ):
            read_buf += self.ADD_TOPPING_MSG

        read_buf += self.BREAKFAST_READY_MSG
        self.read(length=len(read_buf), expect=read_buf)
        # read_buf += self.OK
        self.read(length=4)

        self.order_id += 1

        return 0


    def quit(self):
        '''
        Quit cleanly
        '''
        if DEBUG:
            print "cmd: quit -----------"

        return -1

    def bogus(self):
        '''
        Send a bogus command
        '''
        if DEBUG:
            print "cmd: bogus -----------"

        # self.write(self.state['e'].make_trigger_buf('BOGUS'))

        # self.read(length=len(self.state['e'].ok), expect=self.state['e'].ok)

        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0
