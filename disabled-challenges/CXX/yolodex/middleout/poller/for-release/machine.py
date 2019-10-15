#!/usr/bin/env python
from generator.actions import Actions, Variable

import random
import string

bs = string.ascii_letters + string.digits + ' '
end_marker = '\xed\xac\xed\xde'

def random_bytes(n=128):
    return ''.join([random.choice(bs) for _ in xrange(n)])

class Machine(Actions):
    def start(self):
        n = random.randint(0, 32 * 1024)
        data = random_bytes(n)

        self.write('compress\n')
        self.write(data + '\n')
        compressed = Variable('compressed')
        compressed.set_slice(0)
        self.read(delim=end_marker, assign=compressed)

        self.write('decompress\n')
        self.write(compressed)
        self.write('\n')
        self.read(expect=data, length=len(data))
        self.write('quit\n')

    def stop(self):
        pass
