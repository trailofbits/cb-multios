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
from random import randint, choice
import string
from operator import itemgetter, attrgetter
import numpy as np

from common import CONFIG
import support as sp


class SnailMail(object):

    def __init__(self):
        self.mailboxes = {}
        self.add_mailbox(CONFIG['UNDELIVERABLE_MAIL_ADDR'])
        self.add_mailbox(CONFIG['LOST_MAIL_ADDR'])
        self.add_mailbox(CONFIG['RECEIVED_MAIL_ADDR'])
        self.add_mailbox(CONFIG['SORTED_MAIL_ADDR'])
        self.stamps = StampRoll()

    def address_exists(self, addr):
        return addr in self.mailboxes.keys()

    def is_valid_customer_address(self, addr):
        return (True == self.address_exists(addr)) and (CONFIG['MIN_CUSTOMER_ADDR'] <= addr)

    def get_random_existing_address(self):
        return choice(self.mailboxes.keys())

    def get_new_address(self, invalid=False):
        if True == invalid:
            return self.get_random_existing_address()
        else:
            while True:
                i = randint(CONFIG['MIN_CUSTOMER_ADDR'], 2**16-1)
                if False == self.address_exists(i):
                    return i

    def add_mailbox(self, addr):
        if False == self.address_exists(addr):
            self.mailboxes[addr] = Mailbox(addr)

    def get_all_addresses(self):
        return sorted([x for x in self.mailboxes.keys() if x >= CONFIG['MIN_CUSTOMER_ADDR']])

    def make_mail_item(self, s_invalid=False, r_invalid=False):
        addrs= self.get_all_addresses()
        if [] == addrs:
            addrs = [0]
        s = choice(addrs)
        r = choice(addrs)

        if True == s_invalid:
            s = 1
        if True == r_invalid:
            r = 2
        return MailItem(s, r)

    def put_mail_in_box(self, m, box_id):
        self.mailboxes[box_id].add_mail(m)
        if (1 < CONFIG['DEFAULT_DEBUG_LEVEL']):
            print "Put mail into box {0}.".format(box_id)

    def pop_mail_from_box(self, box_id):
        if (1 < CONFIG['DEFAULT_DEBUG_LEVEL']):
            print "Pop mail from box {0}.".format(box_id)
        return self.mailboxes[box_id].pop_mail()

    def get_all_mail_from_box(self, box_id):
        return self.mailboxes[box_id].mail

    def is_mailbox_empty(self, box_id):
        return self.mailboxes[box_id].is_empty()

    def receive_mail(self, m):
        self.put_mail_in_box(m, CONFIG['RECEIVED_MAIL_ADDR'])

    def sort_mail(self):
        if True == self.is_mailbox_empty(CONFIG['RECEIVED_MAIL_ADDR']):
            return -1

        m = self.pop_mail_from_box(CONFIG['RECEIVED_MAIL_ADDR'])
        while (None != m):
            if True == self.is_valid_customer_address(m.recipient):
                self.put_mail_in_box(m, CONFIG['SORTED_MAIL_ADDR'])
            else:
                self.put_mail_in_box(m, CONFIG['UNDELIVERABLE_MAIL_ADDR'])
            m = self.pop_mail_from_box(CONFIG['RECEIVED_MAIL_ADDR'])
        return 0

    def get_undeliverable_mail(self):
        mail = self.get_all_mail_from_box(CONFIG['UNDELIVERABLE_MAIL_ADDR'])
        if [] == mail:
            return mail
        else:
            s = sorted(mail, key=attrgetter('recipient'))
            return sorted(s, key=attrgetter('sender'))

    def deliver_mail(self):
        if True == self.is_mailbox_empty(CONFIG['SORTED_MAIL_ADDR']):
            return -1

        m = self.pop_mail_from_box(CONFIG['SORTED_MAIL_ADDR'])
        while (None != m):
            self.put_mail_in_box(m, m.recipient)
            m = self.pop_mail_from_box(CONFIG['SORTED_MAIL_ADDR'])

        return 0

    def return_to_sender(self):
        if True == self.is_mailbox_empty(CONFIG['UNDELIVERABLE_MAIL_ADDR']):
            return -1

        m = self.pop_mail_from_box(CONFIG['UNDELIVERABLE_MAIL_ADDR'])
        while (None != m):
            if True == self.is_valid_customer_address(m.sender):
                m.recipient = m.sender
                self.put_mail_in_box(m, CONFIG['RECEIVED_MAIL_ADDR'])
            else:
                self.put_mail_in_box(m, CONFIG['LOST_MAIL_ADDR'])
            m = self.pop_mail_from_box(CONFIG['UNDELIVERABLE_MAIL_ADDR'])
        return 0

    def get_lost_mail(self):
        mail = self.get_all_mail_from_box(CONFIG['LOST_MAIL_ADDR'])
        if [] == mail:
            return mail
        else:
            return sorted(mail, key=attrgetter('sb_hash'))

    def destroy_lost_mail(self):
        if True == self.is_mailbox_empty(CONFIG['LOST_MAIL_ADDR']):
            return -1

        while False == self.is_mailbox_empty(CONFIG['LOST_MAIL_ADDR']):
            m = self.pop_mail_from_box(CONFIG['LOST_MAIL_ADDR'])
            if m is not None:
                del(m)

        return 0

    def add_stamp(self, stamp):
        self.stamps.add(stamp)

    def stamp_id(self):
        return self.stamps.num_created

    def get_stamp(self):
        return self.stamps.get()

class Mailbox(object):

    def __init__(self, address):
        self.address = address
        self.mail = []

    def add_mail(self, mail_item):
        self.mail.append(mail_item)

    def pop_mail(self):
        if False == self.is_empty():
            return self.mail.pop()
        else:
            return None

    def is_empty(self):
        return 0 == len(self.mail)


class MailItem(object):

    def __init__(self, sender, recipient):
        self.sender = sender
        self.recipient = recipient
        self.subject = sp.random_string(CONFIG['MAX_SUBJ_LEN'])
        self.body = sp.random_string(CONFIG['MAX_BODY_LEN'])

    def pack(self):
        '''
        pack mail item for transmit

        sender = 2 byte short
        recipient = 2 byte short
        subject = CONFIG['MAX_SUBJ_LEN'] bytes
        body = CONFIG['MAX_BODY_LEN'] bytes
        '''
        p = ''
        p += sp.pack_single_uint16(self.sender)
        p += sp.pack_single_uint16(self.recipient)
        p += sp.pack_single_string(self.subject)
        p += sp.pack_single_string(self.body)
        return p

    @property
    def sb_hash(self):
        '''
        Use silly hash algorithm to compute hash of subj+body.

        Return the 8 byte hash as a string
        '''
        s_hash = np.uint8([0, 0, 0, 0])
        b_hash = np.uint8([0, 0, 0, 0])
        if (1 < CONFIG['DEFAULT_DEBUG_LEVEL']):
            print "Hashing mail..."

        for i in range(CONFIG['MAX_SUBJ_LEN']):
            s_hash[i % 4] += np.uint8(ord(self.subject[i]))

        for j in range(CONFIG['MAX_BODY_LEN']):
            b_hash[j % 4] += np.uint8(ord(self.body[j]))

        hash_res = np.concatenate((s_hash, b_hash), axis=0)

        return hash_res.tostring()

class StampRoll(object):

    def __init__(self):
        self.stamps = []
        self.num_created = 0

    def add(self, stamp):
        self.stamps.append(stamp)
        self.num_created += 1

    def get(self):
        if [] == self.stamps:
            return None
        return self.stamps.pop()
