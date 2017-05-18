#!/usr/bin/env python
from generator.actions import Actions
import math
import random
import string
import struct

VAULT_SIZE = 100
handlers = [0x080482d0, 0x080484a0, 0x08048590]

def random_string(size=20):
    return ''.join([chr(random.randint(0,255)) for x in xrange(random.randint(1,size))])

class TVS(Actions):
    def start(self):
        self.state['ikey'] = 0xAA
        self.state['okey'] = 0x55
        self.state['time'] = 2208988800.0 + 1418382816.0
        self.state['items'] = {}
        self.state['k'] = 0xb7fc0024
        k = self.next_k()
        self.state['items'][k] = reduce(lambda x,y: x+y, [struct.pack('<I', x) for x in handlers], '')

    def write_bytes(self, s):
        out = ''
        for c in s:
            out += chr(self.state['ikey'] ^ ord(c))
            self.state['ikey'] += ord(c)
            self.state['ikey'] &= 0xff
        self.write(out)

    def read_bytes(self, s):
        out = ''
        for c in s:
            out += chr(self.state['okey'] ^ ord(c))
            self.state['okey'] += ord(c)
            self.state['okey'] &= 0xff
        self.read(length=len(out), expect=out)

    def phase1(self):
        pass

    def phase2(self):
        pass

    def _send_time(self):
        fractional, secs = math.modf(self.state['time'])
        fractional = int(fractional * (1 << 32))
        secs = int(secs)
        self.write_bytes(struct.pack('>HHII', 1, 8, fractional, secs))

    def send_time(self):
        self.state['time'] += random.uniform(0, 4)
        self._send_time()

    def list_things(self):
        s = struct.pack('>HHB', 2, len(self.state['items'].keys()) * 8 + 1, 1)
        for k in sorted(self.state['items'].keys()):
            s += struct.pack('>II', k, 0 if self.state['items'][k] is None else len(self.state['items'][k]))
        self.write_bytes(struct.pack('>HHB', 2, 1, 1))
        self.read_bytes(s)

    def list_things_2(self):
        return self.list_things()

    def next_k(self):
        k = self.state['k']
        self.state['k'] += 8
        return k

    def store_things(self):
        if len(self.state['items'].keys()) == VAULT_SIZE:
            return
        k = self.next_k()
        v = random_string(random.randint(20, 100))
        self.write_bytes(struct.pack('>HHB', 2, len(v) + 1, 2) + v)
        self.read_bytes(struct.pack('>HHBI', 2, 5, 2, k))
        self.state['items'][k] = v

    def store_things_2(self):
        return self.store_things()

    def open_it_up(self):
        while self.state['time'] < 2208988800 + 1419462000 + random.randint(0, 100):
            self.state['time'] += 150
            self._send_time()

    def get_things(self):
        try:
            k, v = random.choice(filter(lambda x: x[1] is not None, self.state['items'].items()))
            self.state['items'][k] = None
            self.write_bytes(struct.pack('>HHBI', 2, 5, 4, k))
            self.read_bytes(struct.pack('>HHB', 2, len(v) + 1, 4) + v)
        except IndexError:
            pass

    def update_things(self):
        if len(self.state['items']) == 0:
            return
        k = random.choice(self.state['items'].keys())
        v = random_string(random.randint(20, 500))
        self.write_bytes(struct.pack('>HHBI', 2, len(v) + 5, 3, k) + v)
        self.read_bytes(struct.pack('>HHBI', 2, 5, 3, k))
        self.state['items'][k] = v

    def ping(self):
        r = random_string()
        self.write_bytes(struct.pack('>HH', 0, len(r)) + r)
        self.read_bytes(struct.pack('>HH', 0, len(r)) + r)

    def ping_2(self):
        return self.ping()

    def quit(self):
        pass
