#!/usr/bin/env python
from generator.actions import Actions, Variable
import random
import string
import struct

def random_string(length):
    s = ''
    for x in xrange(length):
        s += random.choice(string.ascii_uppercase)
    return s

def r_uint32():
    return random.randint(0, 0xffffffff)

def r_vendor():
    vid = r_uint32()
    vtype = random.randint(0, 6)
    loc = random_string(200)
    return vid, vtype, loc

class MultiPass(Actions):
    INIT = 0
    AUTH = 1
    OPS = 2
    FIN = 3

    PURCHASE = 0
    RECHARGE = 1
    BALANCE = 2
    HISTORY = 3
    ISSUE = 4
    REFUND = 5

    OK = 0

    def start(self):
        self.state['counter'] = 0
        self.state['cards'] = {}
        self.state['purchases'] = []
        self.state['transactions'] = []

    def packet(self, card_id, auth_code, pkt_type, op_code, status, transaction_id):
        if isinstance(card_id, Variable):
            self.write(card_id)
        else:
            self.write(struct.pack('<I', card_id))
        if isinstance(auth_code, Variable):
            self.write(auth_code)
        else:
            self.write(struct.pack('<I', auth_code))
        self.write(struct.pack('<BBB', pkt_type, op_code, status))
        if isinstance(transaction_id, Variable):
            self.write(transaction_id)
        else:
            self.write(struct.pack('<I', transaction_id))

    def rpacket(self, pkt_type, op_code, status):
        self.read(length=8) # we can't easily check these
        tid = Variable('trans' + str(self.state['counter']))
        tid.set_slice(0)

        self.state['counter'] += 1
        self.read(length=3, expect=struct.pack('<BBB', pkt_type, op_code, status))
        self.read(length=4, assign=tid)
        return tid

    def loop(self):
        pass

    def exit(self):
        self.packet(0, 0, self.AUTH, self.ISSUE, 0, 0)
        self.rpacket(self.AUTH, self.ISSUE, 13)

    def issue(self):
        value = r_uint32()
        self.packet(0, 0, self.INIT, self.ISSUE, 0, 0)
        self.write(struct.pack('<I', value))

        card_id = Variable('card' + str(self.state['counter']))
        card_id.set_slice(0)
        self.state['counter'] += 1
        auth_code = Variable('auth' + str(self.state['counter']))
        auth_code.set_slice(0)
        self.state['counter'] += 1
        tid = Variable('trans' + str(self.state['counter']))
        tid.set_slice(0)
        self.state['counter'] += 1

        self.read(length=4, assign=card_id)
        self.read(length=4, assign=auth_code)
        self.read(length=3, expect=struct.pack('<BBB', self.INIT, self.ISSUE, self.OK))
        self.read(length=4, assign=tid)

        self.packet(card_id, auth_code, self.FIN, self.ISSUE, self.OK, tid)
        self.rpacket(self.FIN, self.ISSUE, self.OK)

        self.state['cards'][(card_id, auth_code)] = value

    def purchase(self):
        (card_id, auth_code), value = random.choice(self.state['cards'].items())
        cost = random.randint(0, value)
        pid = r_uint32()
        vendor = r_vendor()

        self.packet(card_id, auth_code, self.AUTH, self.PURCHASE, 0, 0)
        tid = self.rpacket(self.AUTH, self.PURCHASE, self.OK)

        self.packet(card_id, auth_code, self.OPS, self.PURCHASE, 0, tid)
        self.write(struct.pack('<IIIBp', pid, cost, vendor[0], vendor[1],
            vendor[2]))
        self.rpacket(self.OPS, self.PURCHASE, self.OK)

        self.packet(card_id, auth_code, self.FIN, self.PURCHASE, 0, tid)
        self.rpacket(self.FIN, self.PURCHASE, self.OK)

        self.state['cards'][(card_id, auth_code)] -= cost
        self.state['purchases'].append((card_id, auth_code, tid, pid, cost))

    def balance(self):
        (card_id, auth_code), value = random.choice(self.state['cards'].items())
        self.packet(card_id, auth_code, self.AUTH, self.BALANCE, 0, 0)
        tid = self.rpacket(self.AUTH, self.BALANCE, self.OK)

        self.packet(card_id, auth_code, self.OPS, self.BALANCE, 0, tid)
        self.rpacket(self.OPS, self.BALANCE, self.OK)

        self.read(expect=struct.pack('<I', value), length=4)

        self.packet(card_id, auth_code, self.FIN, self.BALANCE, 0, tid)
        self.rpacket(self.FIN, self.BALANCE, self.OK)

    def history(self):
        pass

    def refund(self):
        if len(self.state['purchases']) == 0:
            return
        
        p = random.choice(self.state['purchases'])
        (card_id, auth_code, ptid, pid, pvalue) = p
        value = self.state['cards'][(card_id, auth_code)]
        if pvalue >= 0xffffffff - value:
            return

        self.state['purchases'].remove(p)
        self.state['cards'][(card_id, auth_code)] += pvalue
        
        self.packet(card_id, auth_code, self.AUTH, self.REFUND, 0, 0)
        tid = self.rpacket(self.AUTH, self.REFUND, self.OK)

        self.packet(card_id, auth_code, self.OPS, self.REFUND, 0, tid)
        self.write(struct.pack('<I', pid))
        self.write(ptid)
        self.rpacket(self.OPS, self.REFUND, self.OK)

        self.packet(card_id, auth_code, self.FIN, self.REFUND, 0, tid)
        self.rpacket(self.FIN, self.REFUND, self.OK)

    def recharge(self):
        (card_id, auth_code), value = random.choice(self.state['cards'].items())
        amount = random.randint(0, 0xffffffff - value)
        vendor = r_vendor()

        self.packet(card_id, auth_code, self.AUTH, self.RECHARGE, 0, 0)
        tid = self.rpacket(self.AUTH, self.RECHARGE, self.OK)

        self.packet(card_id, auth_code, self.OPS, self.RECHARGE, 0, tid)
        self.write(struct.pack('<IIBp', amount, vendor[0], vendor[1], vendor[2]))
        self.rpacket(self.OPS, self.RECHARGE, self.OK)

        self.packet(card_id, auth_code, self.FIN, self.RECHARGE, 0, tid)
        self.rpacket(self.FIN, self.RECHARGE, self.OK)

        self.state['cards'][(card_id, auth_code)] += amount
