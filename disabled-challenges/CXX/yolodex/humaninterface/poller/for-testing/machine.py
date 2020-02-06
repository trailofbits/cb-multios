from generator.actions import Actions
import random
import string
import struct

def random_bytes(size):
    return ''.join(chr(random.randint(0, 0xFF)) for c in xrange(size))

class Forkbeard(Actions):
    LINK_PAYLOAD_SIZE = 339

    def send_radio(self, ch, flow, payload):
        hdr = ch | (flow << 2) | (len(payload) << 3)
        pkt = struct.pack('<H', hdr) + payload
        self.write(pkt)

    def send(self, channel, data):
        pkt = struct.pack('<HH', len(data), channel) + data
        
        offset = 0
        while offset < len(pkt):
            radio_pkt_len = len(pkt) - offset
            if radio_pkt_len > self.LINK_PAYLOAD_SIZE:
                radio_pkt_len = self.LINK_PAYLOAD_SIZE
            
            ch = 1
            if offset == 0:
                ch = 2
            flow = 1
            self.send_radio(ch, flow, pkt[offset:offset+radio_pkt_len])
            offset += radio_pkt_len

    def recv_radio(self, ch, flow, payload, to_match):
        hdr = ch | (flow << 2) | (len(payload) << 3)
        pkt = struct.pack('<H', hdr)
        if to_match >= len(payload):
            pkt += payload
            missing = 0
        elif to_match > 0:
            pkt += payload[:to_match]
            missing = len(payload) - to_match
        else:
            missing = len(payload)
        self.read(length=len(pkt), expect=pkt)
        if missing > 0:
            self.read(length=missing)

    def recv(self, channel, data, length=None):
        if length is None:
            length = len(data)
        missing = length - len(data)
        pkt = struct.pack('<HH', length, channel) + data + '\x00'*missing
        remaining = len(pkt) - missing
        
        offset = 0
        while offset < len(pkt):
            radio_pkt_len = len(pkt) - offset
            if radio_pkt_len > self.LINK_PAYLOAD_SIZE:
                radio_pkt_len = self.LINK_PAYLOAD_SIZE
            
            ch = 1
            if offset == 0:
                ch = 2
            flow = 1
            self.recv_radio(ch, flow, pkt[offset:offset+radio_pkt_len], remaining - offset)
            offset += radio_pkt_len

    def command(self, code, data):
        i = self.state['id']
        self.state['id'] += 1
        if self.state['id'] == 0x100:
            self.state['id'] = 0x01

        self.send(0x0001, struct.pack('<BBH', code, i, len(data)) + data)
        return i

    def start(self):
        self.state['chid'] = 0x40
        self.state['id'] = 0x01
        self.state['protocol'] = 0
        self.state['output'] = '\x00' * 600

    def before_ready(self):
        pass

    def open_channel(self, addr):
        chid = self.state['chid']
        self.state['chid'] += 1

        local = random.randint(0x40, 0xFFFF)
        i = self.command(0x02, struct.pack('<HH', addr, local))
        self.recv(0x0001, struct.pack('<BBHHHHH', 0x03, i, 8, chid, local, 0, 0))

        i = self.command(0x04, struct.pack('<HHBBH', chid, 0, 1, 2, 0x8000))
        self.recv(0x0001, struct.pack('<BBHHHHBBH', 0x05, i, 10, local, 0, 0, 1, 2, 0x8000))

        self.recv(0x0001, struct.pack('<BBHHH', 0x04, 1, 4, local, 0))
        self.send(0x0001, struct.pack('<BBHHHH', 0x05, 1, 6, chid, 0, 0))

        return (local, chid)

    def open_control(self):
        self.state['control'] = self.open_channel(0x1011)

    def open_interrupt(self):
        self.state['interrupt'] = self.open_channel(0x1013)

    def disconnect(self):
        local, remote = self.state['control']
        i = self.command(0x06, struct.pack('<HH', remote, local))
        self.recv(0x0001, struct.pack('<BBHHH', 0x07, i, 4, remote, local))

    def echo(self):
        s = random_bytes(random.randint(500, 2000))
        i = self.command(0x08, s)
        self.recv(0x0001, struct.pack('<BBH', 0x09, i, len(s)) + s)

    def ready(self):
        pass

    def get_protocol(self):
        local, remote = self.state['control']
        self.send(remote, chr(0x60 | random.randint(0,0xF)))
        self.recv(local, chr(0xA0) + chr(self.state['protocol']))

    def set_protocol(self):
        local, remote = self.state['control']
        self.state['protocol'] = 1 if self.chance(0.5) else 0
        self.send(remote, chr(0x70 | self.state['protocol']))
        self.recv(local, chr(0x00))

    def set_report(self):
        local, remote = self.state['control']
        self.send(remote, chr(0x52))
        length = random.randint(1, 600)
        data = random_bytes(length)
        self.send(remote, chr(0xA2) + data)
        self.recv(local, chr(0x00))
        self.state['output'] = data + self.state['output'][length:]

    def get_report(self):
        local, remote = self.state['control']
        if self.chance(0.5):
            length = 200 if self.state['protocol'] == 0 else 700
            self.send(remote, chr(0x41))
            self.recv(local, chr(0xA1), length=length+1)
        else:
            self.send(remote, chr(0x42))
            self.recv(local, chr(0xA2) + self.state['output'])

