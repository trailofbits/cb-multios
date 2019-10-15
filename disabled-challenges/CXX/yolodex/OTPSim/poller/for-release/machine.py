#!/usr/bin/env python

from generator.actions import Actions
import random, string, struct

def random_string_n(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(size)])
def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])
def random_bytes_n(size=20):
    return ''.join([chr(random.randint(0,255)) for x in xrange(size)])

class OTP(object):

    MAX_OTP_LEN = 128

    def __init__(self, mp, sv, si):
        self.seed_value = struct.unpack('<I', sv)[0]
        self.seed_idx = struct.unpack('<I', si)[0] % 4096
        self.data = ''
        self.num_reqs = 3
        self.magic_page = mp

    def _populate(self):
        sv = struct.pack('<I', self.seed_value)
        idx = self.seed_idx % 4096
        tmp = self.magic_page[idx:]
        if idx != 0:
            tmp += self.magic_page[:idx]
        idx = len(self.data)
        for i in xrange(len(self.data), self.MAX_OTP_LEN):
            self.data += chr(ord(tmp[idx % 4096]) ^ ord(sv[i % 4]))
            idx += 2
        self.seed_idx = idx
        assert len(self.data) == self.MAX_OTP_LEN

    def _consume(self, sz):
        assert len(self.data) >= sz
        self.data = self.data[sz:]

class AOTPSim(Actions):
    def _read_flag(self, success):
        d = '\x00' if success else '\xFF'
        self.read(length=len(d), expect=d)

    def start(self):
        #self.delay(100)
        self.otp = None

    def cmd_loop(self):
        pass

    def handshake(self):
        self.write('SHAK')
        self.read(length=8)
        self.write(self.magic_page[:8])
        sv = random_bytes_n(4)
        self.write(sv)
        si = 0
        for i in xrange(4096 / 4):
            si += struct.unpack('<I', self.magic_page[i * 4:(i + 1) * 4])[0]
            si = si & 0xFFFFFFFF
        si %= 4096
        si = struct.pack('<I', si)
        self.read(length=len(si), expect=si)
        self.otp = OTP(self.magic_page, sv, si)
        self._read_flag(True)

    def generate(self):
        self.write('GENO')
        sz = random.randint(1, OTP.MAX_OTP_LEN)
        sz_s = struct.pack('<I', sz)
        self.write(sz_s)
        if self.otp is None:
            self._read_flag(False)
            return
        if self.otp.num_reqs == 0:
            self._read_flag(False)
            return
        if len(self.otp.data) < sz:
            self.otp._populate()
        data = ''.join(['%02X' % ord(x) for x in self.otp.data[:sz]])
        self.read(length=len(data), expect=data)
        self.otp._consume(sz)
        self.otp.num_reqs -= 1
        self._read_flag(True)

    def extend(self):
        self.write('XTND')
        sz = random.randint(1, 512)
        sz_s = struct.pack('<H', sz)
        self.write(sz_s)
        rdata = random_bytes_n(sz).replace('\x00', '\xFF')
        self.write(rdata + '\x00')
        if self.otp is None:
            self._read_flag(False)
            return
        resp = '\x00'
        resp += rdata
        self.read(length=len(resp), expect=resp)
        self.otp.num_reqs = 3

    def set_seeds(self):
        self.write('SEED')
        sv = random_bytes_n(4)
        si = random_bytes_n(4)
        self.write(sv + si)
        if self.otp is None:
            self._read_flag(False)
            return
        self.otp.seed_value = struct.unpack('<I', sv)[0]
        self.otp.seed_idx = struct.unpack('<I', si)[0]
        self.otp.data = ''
        self.otp._populate()
        self._read_flag(True)

    def verify_otp(self):
        self.write('VERI')
        sv = random_bytes_n(4)
        si = random_bytes_n(4)
        sz = random.randint(12, OTP.MAX_OTP_LEN)
        self.write(si)
        self.write(sv)
        self.write(struct.pack('<I', sz))
        o = OTP(self.magic_page, sv, si)
        o._populate()
        token = o.data[:sz]
        if random.randint(1, 100) <= 10:
            token = random_bytes_n(sz)
        self.write(token)
        self._read_flag(token == o.data[:sz])

    def invalid(self):
        cmd = None
        while cmd is None or cmd in ['SHAK', 'GENO', 'XTND', 'SEED', 'VERI', 'QUIT']:
            cmd = random_string_n(4)
        self.write(cmd)
        self._read_flag(False)

    def quit(self):
        self.write('QUIT')
        self._read_flag(True)
