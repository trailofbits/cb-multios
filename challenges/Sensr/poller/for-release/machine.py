#!/usr/bin/env python
from generator.actions import Actions
import random
import struct

TYPE_ERROR = 0
TYPE_RESET = 1
TYPE_LOCATION = 2
TYPE_SPEED = 3
TYPE_RPM = 4

EC_ERROR = 0
EC_TIMESTAMP = 1
EC_DROPPED = 2
EC_INVALID = 3

def calc_hash(s):
    result = 0
    mixer = 0x12345678

    for i in xrange(0, 0x1000, 4):
        x = struct.unpack('<I', s[i:i+4])[0]
        result += x ^ mixer

        mixer ^= (mixer >> 13) & 0xFFFFFFFF
        mixer ^= (mixer << 7) & 0xFFFFFFFF
        mixer ^= (mixer >> 17) & 0xFFFFFFFF

    return result & 0xFFFFFFFF

class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        self.state['speed'] = (None, 0.0)
        self.state['rpm'] = (None, 0.0)
        self.state['loc'] = (None, (0.0, 0.0, 0.0))
        self.state['time'] = calc_hash(self.magic_page)

    def menu(self):
        pass

    def quit(self):
        pass

    def loc(self):
        old_time = self.state['loc'][0]
        x, y, z = self.state['loc'][1]
        if old_time == self.state['time']:
            return

        x = max(0, random.uniform(-10, 10) + x)
        y = max(0, random.uniform(-10, 10) + y)
        z = max(0, random.uniform(-10, 10) + z)
        self.state['loc'] = (self.state['time'], (x, y, z))

        x, y, z = self.state['loc'][1]
        pkt = struct.pack('<BIfff', TYPE_LOCATION, self.state['time'], x, y, z)
        pkt = pkt.ljust(17, chr(0))
        self.write(pkt)
        self.read_aggregate()

    def speed(self):
        old_time, speed = self.state['speed']
        speed = min(max(0, random.uniform(-1, 1) + speed), 240)
        self.state['speed'] = (self.state['time'], speed)

        pkt = struct.pack('<BIf', TYPE_SPEED, self.state['time'], self.state['speed'][1])
        pkt = pkt.ljust(17, chr(0))
        self.write(pkt)
        self.read_aggregate()

    def rpm(self):
        old_time, rpm = self.state['rpm']
        rpm = min(max(0, random.uniform(-50, 50) + rpm), 10000)
        self.state['rpm'] = (self.state['time'], rpm)

        pkt = struct.pack('<BIf', TYPE_RPM, self.state['time'], self.state['rpm'][1])
        pkt = pkt.ljust(17, chr(0))
        self.write(pkt)
        self.read_aggregate()

    def doreset(self):
        self.state['speed'] = (None, 0.0)
        self.state['rpm'] = (None, 0.0)
        self.state['loc'] = (None, (0.0, 0.0, 0.0))
        self.state['time'] = random.randint(0, 0xF0000000)

        self.write(struct.pack('<BI', TYPE_RESET, 0).ljust(17, chr(0)))

    def elapse(self):
        self.state['time'] += random.randint(1, 60)

    def read_aggregate(self):
        self.read_speed()
        self.read_rpm()
        self.read_location()

    def read_speed(self):
        if self.state['speed'][0] is None:
            return

        pkt = struct.pack('<BIf', TYPE_SPEED, self.state['time'], self.state['speed'][1])
        pkt = pkt.ljust(17, chr(0))
        self.read(length=len(pkt), expect=pkt)

    def read_rpm(self):
        if self.state['rpm'][0] is None:
            return

        pkt = struct.pack('<BIf', TYPE_RPM, self.state['time'], self.state['rpm'][1])
        pkt = pkt.ljust(17, chr(0))
        self.read(length=len(pkt), expect=pkt)

    def read_location(self):
        if self.state['loc'][0] is None:
            return

        x, y, z = self.state['loc'][1]
        pkt = struct.pack('<BIfff', TYPE_LOCATION, self.state['time'], x, y, z)
        pkt = pkt.ljust(17, chr(0))
        self.read(length=len(pkt), expect=pkt)

    def read_error(self, ec, extra):
        pkt = struct.pack('<BIII', TYPE_ERROR, 0, ec, extra)
        pkt = pkt.ljust(17, chr(0))
        self.read(length=len(pkt), expect=pkt)
