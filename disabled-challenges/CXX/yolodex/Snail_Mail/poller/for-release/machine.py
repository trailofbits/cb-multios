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
from snailmail import SnailMail

class SnailMailPoller(Actions):

    CMD_BUY_POSTAGE             = '\x03\x03\x03\x03'
    CMD_ADD_ADDRESS             = '\x05\x05\x05\x05'
    CMD_RECEIVE_MAIL            = '\x10\x10\x10\x10'
    CMD_SORT_MAIL               = '\x11\x11\x11\x11'
    CMD_LIST_ADDRESSES          = '\x12\x12\x12\x12'
    CMD_LIST_UNDELIVERABLE_MAIL = '\x13\x13\x13\x13'
    CMD_DELIVER_MAIL            = '\x14\x14\x14\x14'
    CMD_RETURN_TO_SENDER        = '\x15\x15\x15\x15'
    CMD_LIST_LOST_MAIL          = '\x16\x16\x16\x16'
    CMD_DESTROY_LOST_MAIL       = '\x17\x17\x17\x17'
    CMD_QUIT                    = '\x00\x0F\xF0\xFF'

    BAD_STAMP                   = '\xbb\xaa\xdd'

    STATUS_OK                   = '\x04\x04'
    STATUS_ERR                  = '\x1E\x44'
    STATUS_QUIT                 = '\x04\x17'

    def send_cmd(self, cmd):
        self.write(cmd)

    def recv_status(self, status):
        self.read(length=2, expect=sp.pack_single_string(status))

    def recv_uint16(self, uint16_val, match=True):
        if True == match:
            self.read(length=2, expect=sp.pack_single_uint16(uint16_val))
        else:
            self.read(length=2)

    def recv_hash(self, hash_val, match=True):
        if True == match:
            self.read(length=8, expect=hash_val)
        else:
            self.read(length=8)

    def start(self):
        #self.delay(100)
        self.state['e'] = SnailMail()
        if DEBUG:
            print "------- start -----------"

    def add_address(self):
        '''
        Add one new address to the mail system
        '''
        self.send_cmd(self.CMD_ADD_ADDRESS)
        if DEBUG:
            print "cmd: add addresses"

        invalid = False
        if self.chance(.2):
            invalid = True
        addr = self.state['e'].get_new_address(invalid)
        p_addr = sp.pack_single_uint16(addr)
        self.write(p_addr)

        if True == invalid:
            self.recv_status(self.STATUS_ERR)
        else:
            self.recv_status(self.STATUS_OK)
            self.state['e'].add_mailbox(addr)

        return 0

    def list_addresses(self):
        '''
        Get list of all valid addresses.
        '''
        self.send_cmd(self.CMD_LIST_ADDRESSES)
        if DEBUG:
            print "cmd: list addresses"

        addr_list = self.state['e'].get_all_addresses() # sorted list of addrs
        if [] != addr_list:
            for addr in addr_list:
                self.recv_uint16(addr)
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)
        return 0

    def receive_mail(self):
        '''
        Add a piece of mail into the system.
        '''
        self.send_cmd(self.CMD_RECEIVE_MAIL)
        if DEBUG:
            print "cmd: receive mail"

        stamp = self.state['e'].get_stamp()
        if stamp is None:
            self.write(self.BAD_STAMP)
            self.recv_status(self.STATUS_ERR)
        else:
            self.write(stamp)

            if self.chance(.2):
                m = self.state['e'].make_mail_item(s_invalid=True)
            elif self.chance(.2):
                m = self.state['e'].make_mail_item(r_invalid=True)
            else:
                m = self.state['e'].make_mail_item()

            self.write(m.pack())
            self.recv_status(self.STATUS_OK)
            self.state['e'].receive_mail(m)

        return 0

    def sort_mail(self):
        '''
        Sort received mail and filter undeliverable mail.
        '''
        self.send_cmd(self.CMD_SORT_MAIL)
        if DEBUG:
            print "cmd: sort mail"

        if 0 == self.state['e'].sort_mail():
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)

    def list_undeliverable_mail(self):
        '''
        Get a list of all undeliverable mail.
        '''
        self.send_cmd(self.CMD_LIST_UNDELIVERABLE_MAIL)
        if DEBUG:
            print "cmd: list undeliverable mail"

        u_d_mail = self.state['e'].get_undeliverable_mail() # list of mail sorted increasing by recipient
        if [] != u_d_mail:
            for mail in u_d_mail:
                self.recv_uint16(mail.recipient)
                self.recv_uint16(mail.sender)
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)
        return 0

    def deliver_mail(self):
        '''
        Deliver sorted mail to recipients
        '''
        self.send_cmd(self.CMD_DELIVER_MAIL)
        if DEBUG:
            print "cmd: deliver mail"

        if 0 == self.state['e'].deliver_mail():
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)

    def return_to_sender(self):
        '''
        Process undeliverable mail to return to sender or file in lost box.
        '''
        self.send_cmd(self.CMD_RETURN_TO_SENDER)
        if DEBUG:
            print "cmd: return to sender"

        if 0 == self.state['e'].return_to_sender():
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)

    def list_lost_mail(self):
        '''
        Get a list of all lost mail.
        '''
        self.send_cmd(self.CMD_LIST_LOST_MAIL)
        if DEBUG:
            print "cmd: list lost mail"

        l_mail = self.state['e'].get_lost_mail() # list of mail sorted increasing by sb_hash
        if [] != l_mail:
            for mail in l_mail:
                self.recv_hash(mail.sb_hash)
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)
        return 0

    def destroy_lost_mail(self):
        '''
        Destroy all mail in the lost mail box.
        '''
        self.send_cmd(self.CMD_DESTROY_LOST_MAIL)
        if DEBUG:
            print "cmd: destroy lost mail"

        res = self.state['e'].destroy_lost_mail()
        if 0 == res:
            self.recv_status(self.STATUS_OK)
        else:
            self.recv_status(self.STATUS_ERR)
        return 0

    def buy_postage(self):
        '''
        Sell postage to customer.
        '''
        self.send_cmd(self.CMD_BUY_POSTAGE)
        if DEBUG:
            print "cmd: buy postage"

        stamp = Variable('stamp{0}'.format(self.state['e'].stamp_id()))
        stamp.set_slice(0,3)
        self.read(length=3, assign=stamp)
        self.state['e'].add_stamp(stamp)

        self.recv_status(self.STATUS_OK)

        return 0

    def quit(self):
        '''
        Quit cleanly
        '''
        self.send_cmd(self.CMD_QUIT)
        if DEBUG:
            print "cmd: quit -----------"

        self.recv_status(self.STATUS_QUIT)
        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0


