#!/usr/bin/env python

from generator.actions import Actions
import random, string, struct

def random_string_n(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(size)])
def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])
def random_bytes_n(size=20):
    return ''.join([chr(random.randint(0,255)) for x in xrange(size)])
def strlen(s):
    return s.index('\x00')

class BIO(object):

    def __init__(self, data):
        self.data = data
        self.didx = 0
        self.bidx = 0

    def read(self, n):
        b = ord(self.data[self.didx])
        r = 0
        for i in xrange(n):
            if self.bidx == 8:
                self.didx += 1
                b = ord(self.data[self.didx])
                self.bidx = 0
            c = (b & (1 << (8 - self.bidx - 1))) >> (8 - self.bidx - 1)
            r |= (c << (n - i - 1))
            self.bidx += 1
        return r & 0xFF

    def write(self, data, n):
        b = ord(self.data[self.didx])
        for i in xrange(n):
            if self.bidx == 8:
                self.data = self.data[:self.didx] + chr(b) + self.data[self.didx+1:]
                self.didx += 1
                b = ord(self.data[self.didx])
                self.bidx = 0
            c = (ord(data) & (1 << (8 - i - 1))) >> (8 - i - 1)
            b |= (c << (8 - self.bidx - 1))
            self.bidx += 1
        self.data = self.data[:self.didx] + chr(b) + self.data[self.didx+1:]

key = None
def _cmp(s1, s2):
    global key
    for i in xrange(len(s1)):
        if s1[i] != s2[i]:
            i1 = key.find(s1[i])
            i2 = key.find(s2[i])
            if i1 == -1 or i2 == -1:
                return s1[i] - s2[i]
            return i1 - i2
    return 0


class SC(object):

    def __init__(self, key):
        self.key = key

    def _bwt(self, comp, d):
        if comp:
            out = ''
            size = 0
            while True:
                if size >= len(d):
                    break
                data = d[size:size+512]
                table = [data[i:] + data[:i] for i in xrange(len(data))]
                global key
                key = self.key
                table.sort(cmp=_cmp)
                last = ''.join([r[-1] for r in table])
                oidx = table.index(data)
                out += struct.pack('<H', oidx)
                out += last
                size += len(data)
                #print 'original oidx: %d' % oidx
                #import sys
                #for c in out:
                #    sys.stdout.write('%02X ' % ord(c))
                #print ''
            return out, len(out)
        else:
            out = ''
            size = 0
            #import sys
            #for c in d:
            #    sys.stdout.write('%02X ' % ord(c))
            #print ''
            while True:
                if size >= len(d):
                    break
                oidx = struct.unpack('<H', d[size:size+2])[0]
                size += 2
                data = d[size:size+512]
                table = [''] * len(data)
                for i in xrange(len(data)):
                    table = [data[j] + table[j] for j in xrange(len(data))]
                    table.sort(cmp=_cmp)
                #print 'later oidx: %d' % oidx
                out += table[oidx]
                size += len(data)
            return out, len(out)

    def _mtf(self, comp, data):
        if comp:
            l = [chr(x) for x in xrange(32)]
            l += list(self.key)
            l += [chr(x) for x in xrange(127, 256)]
            code = list()
            for i in xrange(len(data)):
                c = l.index(data[i])
                code.append(chr(c))
                l.pop(c)
                l.insert(0, data[i])
            out = ''.join(code)
            out_c = '\0' * len(data) * 2
            bio = BIO(out_c)
            for i in xrange(len(data)):
                if ord(out[i]) > 0x0F:
                    bio.write('\x00', 1)
                    bio.write(out[i], 8)
                else:
                    bio.write('\x80', 1)
                    bio.write(chr(ord(out[i]) << 4), 4)
            outlen = bio.didx + 4 + (1 if bio.bidx > 0 else 0)
            out_c = struct.pack('<I', len(data)) + bio.data[:outlen-4]
            #import sys
            #for c in out_c:
            #    sys.stdout.write('%02X ' % ord(c))
            #print ''
            return out_c, outlen
        else:
            sz = struct.unpack('<I', data[0:4])[0]
            if sz > 4096:
                return None, 0
            out = ''
            bio = BIO(data[4:])
            for i in xrange(sz):
                if bio.read(1) == 0:
                    out += chr(bio.read(8))
                else:
                    out += chr(bio.read(4))
            l = [chr(x) for x in xrange(32)]
            l += list(self.key)
            l += [chr(x) for x in xrange(127, 256)]
            out_d = list()
            for c in out:
                n = l[ord(c)]
                out_d.append(n)
                l.pop(ord(c))
                l.insert(0, n)
            out_d = ''.join(out_d)
            return out_d, sz

    def compress(self, data):
        #print 'Before Length: %d, data: %s' % (len(data), data)
        bout, boutlen = self._bwt(True, data)
        #print 'BWT Length: %d, data: %s' % (boutlen, bout)
        mout, moutlen = self._mtf(True, bout)
        #print 'MTF Length: %d, data: %s' % (moutlen, mout)
        return mout, moutlen

    def decompress(self, data):
        #print 'Before Length: %d, data: %s' % (len(data), data)
        mout, moutlen = self._mtf(False, data)
        #print 'iMTF Length: %d, data: %s' % (moutlen, mout)
        bout, boutlen = self._bwt(False, mout)
        #print 'iBWT Length: %d, data: %s' % (boutlen, bout)
        return bout, boutlen

class ASECOMP(Actions):

    def _shuffle_key(self):
        self.key = [chr(x) for x in xrange(32, 127)]
        random.shuffle(self.key)
        self.key = ''.join(self.key)

    def _generate_data(self):
        alph = [chr(x) for x in xrange(32, 127)]
        n = random.randint(1, 100)
        return ''.join([random.choice(alph) * 3 for x in xrange(n/3 + 1)])

    def start(self):
        #self.delay(100)
        #print '---START'
        self.key = None
        self.data = None
        self.original = None
        s = ''
        for i in xrange(0, 8, 2):
            s += '%02X' % ord(self.magic_page[i])
        s += '\n'
        self.read(length=len(s), expect=s)

    def menu(self):
        #print ' >>> MENU'
        s = '1. Compress\n2. Decompress\n3. Quit\n'
        self.read(length=len(s), expect=s)

    def compress(self):
        #print '   +++ compress'
        self.write('1\n')
        s = 'Key?\n'
        self.read(length=len(s), expect=s)
        self._shuffle_key()
        #print 'Compress key (%d): %s' % (len(self.key), self.key)
        self.write(self.key)
        s = 'Data?\n'
        self.read(length=len(s), expect=s)
        self.data = self._generate_data()
        #print 'Compress data (%d): %s' % (len(self.data), self.data)
        self.write(self.data + '\0')
        sc = SC(self.key)
        out, outlen = sc.compress(self.data)
        if out is None:
            s = 'error.\n'
            self.read(length=len(s), expect=s)
            return
        s = 'Original Size: %d\n' % len(self.data)
        s += 'Compressed Size: %d (%d%%)\n' % (outlen, int((1.0 * outlen / len(self.data) * 100)))
        s += 'Compressed Data: '
        for i in xrange(outlen):
            if i >= 32:
                break
            s += '%02X' % ord(out[i])
        s += '\n'
        self.read(length=len(s), expect=s)
        self.original = self.data
        self.data = out

    def decompress(self):
        #print '   +++ decompress'
        if self.data is None:
            self.compress()
            self.menu()
        self.write('2\n')
        s = 'Key?\n'
        self.read(length=len(s), expect=s)
        if self.key is None:
            self._shuffle_key()
        #print 'Decompress key: %s' % self.key
        self.write(self.key)
        s = 'Length?\n'
        self.read(length=len(s), expect=s)
        n = random.randint(1, 512)
        data = self.data
        if self.data is None:
            data = random_bytes_n(n)
        s = '%d\n' % len(data)
        self.write(s)
        s = 'Data?\n'
        self.read(length=len(s), expect=s)
        self.write(data)
        sc = SC(self.key)
        out, outlen = self.original, len(self.original)
        #out, outlen = sc.decompress(data)
        if out is None:
            s = 'error.\n'
            self.read(length=len(s), expect=s)
            return
        s = 'Compressed Size: %d\n' % len(data)
        s += 'Original Size: %d\n' % outlen
        s += 'Original Data: %s\n' % out[:outlen]
        self.read(length=len(s), expect=s)

    def invalid(self):
        while True:
            r = random_string()
            if r[0] not in '123':
                break
        self.write(r[:6] + '\n')
        s = 'Invalid menu.\n'
        self.read(length=len(s), expect=s)

    def quit(self):
        #print '---END'
        self.write('3\n')
        self.read(length=len('Bye.\n'), expect='Bye.\n')
