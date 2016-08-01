#!/usr/bin/env python

import math
import random
import string
import sys

from generator.actions import Actions
from struct import pack

CS = {
    "UNIVERSAL": 0,
    "APPLICATION": 1,
    "CONTEXT": 2,
    "PRIVATE": 3
}

TS = {
    "UNKNOWN": 0,
    "BOOLEAN": 1,
    "INTEGER": 2,
    "BITSTR": 3,
    "OCTETSTR": 4,
    "NULL": 5,
    "OID": 6,
    "ODSC": 7,
    "EXT": 8,
    "REAL": 9,
    "ENUM": 10,
    "EPDV": 11,
    "UTFSTR": 12,
    "ROID": 13,

    "SEQ": 16,
    "SET": 17,
    "NUMSTR": 18,
    "PRINTSTR": 19,
    "TELESTR": 20,
    "VIDSTR": 21,
    "IA5STR": 22,
    "UTCTIME": 23,
    "GENTIME": 24,
    "GRAPHSTR": 25,
    "VISSTR": 26,
    "GENSTR": 27,
    "UNISTR": 28,
    "CHRSTR": 29,
    "BMPSTR": 30
}

def r_bytes(n):
    return ''.join([
        chr(random.randint(1, 255))
        for _ in xrange(random.randint(0, n))
    ])

def r_str(n):
    return ''.join(
        random.choice(string.printable)
        for _ in xrange(n)
    )

def enc_length(n):
    if n < 0:
        n = -n

    if n <= 127:
        return pack('B', n)

    nbytes = int(math.ceil(len(bin(n)[2:]) / 8.0))
    if nbytes == 127:
        raise Exception

    bs = pack('B', 0x80 | nbytes)
    for i in xrange(nbytes):
        bs = bs[0] + pack('B', (n >> (i * 8)) & 0xFF) + bs[1:]

    return bs

def dbg(s):
    return
    sys.stderr.write('P' + s)
    sys.stderr.write('\n')
    sys.stderr.flush()

class Element(object):
    def __init__(self, depth, cls=None, tag=None):
        if cls is None:
            self.cls = random.choice(CS.values())
        else:
            self.cls = cls

        if tag is None:
            self.tag = random.randint(0, 35)
        else:
            self.tag = tag

        if self.cls == CS['UNIVERSAL'] and (self.tag == TS['SEQ'] or self.tag == TS['SET']):
            self.primitive = False
        else:
            self.primitive = True

        self.depth = depth
        self.subs = []
        self.data = None
        self.length = 0
        self.start = None

    def encode(self):
        out = ""
        c = self.cls << 6
        p = int(not self.primitive) << 5
        t = self.tag
        out += pack('B', c | p | t)
        if mutate:
            t = enc_length(self.length)
            for x in t:
                try:
                    out += chr((ord(x) ^ random.randint(1, 256)) & 0xff)
                except ValueError:
                    print x, ord(x), type(x)
                    raise

        else:
            out += enc_length(self.length)

        if self.primitive and self.data:
            out += self.data
        else:
            for sub in self.subs:
                out += sub.encode()

        return out

    def add_sub(self, element):
        self.length += element.total_length()
        self.subs.append(element)

    def total_length(self):
        return 1 + len(enc_length(self.length)) + self.length

mutate = False # random.random() <= 1.0 / 3
class ASL6(Actions):
    def random_seq(self):
        self.state['cur_depth'] += 1
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['SEQ']))
        self.state['cur_depth'] -= 1

    def random_set(self):
        self.state['cur_depth'] += 1
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['SET']))
        self.state['cur_depth'] -= 1

    def random_bool(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['BOOLEAN']))

    def random_int(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['INTEGER']))

    def random_bitstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['BITSTR']))

    def random_octetstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['OCTETSTR']))

    def random_null(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['NULL']))

    def random_oid(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['OID']))

    def random_odsc(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['ODSC']))

    def random_ext(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['EXT']))

    def random_real(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['REAL']))

    def random_enum(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['ENUM']))

    def random_epdv(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['EPDV']))

    def random_utfstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['UTFSTR']))

    def random_roid(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['ROID']))

    def random_numstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['NUMSTR']))

    def random_printstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['PRINTSTR']))

    def random_telestr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['TELESTR']))

    def random_vidstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['VIDSTR']))

    def random_ia5str(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['IA5STR']))

    def random_utctime(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['UTCTIME']))

    def random_gentime(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['GENTIME']))

    def random_graphstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['GRAPHSTR']))

    def random_visstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['VISSTR']))

    def random_genstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['GENSTR']))

    def random_unistr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['UNISTR']))

    def random_chrstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['CHRSTR']))

    def random_bmpstr(self):
        self.root.add_sub(self.random_element(c=CS['UNIVERSAL'], t=TS['BMPSTR']))

    def random_element(self, c=None, t=None):
        while True:
            if c is None:
                c = random.choice(CS.values())

            if t is None:
                t = random.randint(0, 32)

            if ((c == CS['UNIVERSAL'] and t == TS['SEQ']) or
                (c == CS['UNIVERSAL'] and t == TS['SET'])):
                n = random.randint(0, 16)
                e = Element(self.state['cur_depth'] + 1, c, t)

                if mutate:
                    e.primitive = int(not e.primitive)

                for _ in xrange(n):
                    re = self.random_element(self.state['cur_depth'] + 2)
                    if re:
                        e.add_sub(re)

                if mutate:
                    e.length = random.randint(-2 ** 64, 2 ** 64)

            elif c == CS['UNIVERSAL'] and t == TS['BOOLEAN']:
                e = Element(self.state['cur_depth'] + 1, c, t)
                e.data = chr(random.choice([0x00, 0xFF]))

                if mutate:
                    e.primitive = int(not e.primitive)

                if mutate:
                    e.length = random.randint(-2**64, 2**64)
                else:
                    e.length = 1

            elif c == CS['UNIVERSAL'] and t == TS['NULL']:
                e = Element(self.state['cur_depth'] + 1, c, t)
                e.data = []

                if mutate:
                    e.primitive = int(not e.primitive)

                if mutate:
                    e.length = random.randint(-2**64, 2**64)
                else:
                    e.length = 0

            elif ((c == CS['UNIVERSAL'] and t == TS['INTEGER']) or
                  (c == CS['UNIVERSAL'] and t == TS['BITSTR']) or
                  (c == CS['UNIVERSAL'] and t == TS['OCTETSTR']) or

                  (c == CS['UNIVERSAL'] and t == TS['UTFSTR']) or
                  (c == CS['UNIVERSAL'] and t == TS['NUMSTR']) or
                  (c == CS['UNIVERSAL'] and t == TS['PRINTSTR']) or
                  (c == CS['UNIVERSAL'] and t == TS['TELESTR']) or
                  (c == CS['UNIVERSAL'] and t == TS['VIDSTR']) or
                  (c == CS['UNIVERSAL'] and t == TS['IA5STR']) or
                  (c == CS['UNIVERSAL'] and t == TS['VISSTR'])):

                e = Element(self.state['cur_depth'] + 1, c, t)
                e.data = r_bytes(8)

                if mutate:
                    e.primitive = int(not e.primitive)

                if mutate:
                    e.length = random.randint(-2**64, 2**64)
                else:
                    e.length = len(e.data)

            elif (c == CS['UNIVERSAL'] and t == TS['OID']):
                e = Element(self.state['cur_depth'] + 1, c, t)
                e.data = '\xf8\xf8\xf6'
                e.length = len(e.data)

            elif ((c == CS['UNIVERSAL'] and t == TS['UTCTIME']) or
                 (c == CS['UNIVERSAL'] and t == TS['GENTIME'])):

                e = Element(self.state['cur_depth'] + 1, c, t)
                e.data = r_bytes(8)

                if mutate:
                    e.primitive = int(not e.primitive)

                if mutate:
                    e.length = random.randint(0, 2 ** 34)
                else:
                    e.length = len(e.data)
            else:
                if not mutate:
                    c = None
                    t = None
                    continue
                else:
                    e = Element(self.state['cur_depth'] + 1, c, t)
                    e.data = r_bytes(8)
                    e.primitive = 1

                    if mutate:
                        e.primitive = int(not e.primitive)

                    if mutate:
                        e.length = random.randint(-len(e.data) * 6, len(e.data) * 6)
                    else:
                        e.length = len(e.data)

            return e

    def parse_length(self, i):
        if ord(self.state['stream'][i]) < 128:
            return 1, ord(self.state['stream'][i])

        num_bytes = ord(self.state['stream'][i]) & 0x7F
        if (num_bytes > 4):
            self.read(delim='\n', expect="ERROR: length too large\n");
            dbg('ERROR: length too large')
            return 0, -1

        if (num_bytes == 0):
            self.read(delim='\n', expect="ERROR: infinite length\n");
            dbg('ERROR: infinite length')
            return 0, -1

        l = 0
        i += 1
        for off in xrange(num_bytes):
            l = (l << 8) | ord(self.state['stream'][i + off])

        return num_bytes + 1, l

    def _decode(self, i, depth):
        if i >= len(self.state['stream']):
            self.read(delim='\n', expect="ERROR: bounds exceeded\n");

        e = Element(depth)
        e.depth = depth
        e.cls = (ord(self.state['stream'][i]) & 0xC0) >> 6
        e.tag = ord(self.state['stream'][i]) & 0x1F
        e.primitive = ((ord(self.state['stream'][i]) & 0x20) == 0)
        e.subs = []

        if e.cls < 0 or e.cls > 4:
            self.read(delim='\n', expect="ERROR: unknown class\n");
            dbg('ERROR: unknown class %d')
            return None

        if e.tag > 30 or e.tag < 0:
            self.read(delim='\n', expect="ERROR: unknown tag\n");
            dbg('ERROR: unknown tag')
            return None

        if (not e.primitive) and (TS['SEQ'] != e.tag and TS['SET'] != e.tag):
            self.read(delim='\n', expect="ERROR: bad constructed type\n");
            dbg('ERROR: bad constructed type %d %d %d' % (e.cls, e.tag, e.primitive))
            return None

        if e.primitive and (TS['SEQ'] == e.tag or TS['SET'] == e.tag):
            self.read(delim='\n', expect="ERROR: bad primitive type\n");
            dbg('ERROR: bad primitive type %d %d' % (e.primitive, e.tag))
            return None

        read, ret = self.parse_length(i + 1)
        if ret < 0:
            dbg('ERROR: bad parse length')
            return None
        e.length = ret

        if e.tag == TS['BOOLEAN'] and e.length != 1:
            dbg('bool len %d' % e.length)
            self.read(delim='\n', expect="ERROR: invalid length for bool\n");
            dbg('ERROR: invalid length for bool')
            return None

        if e.tag == TS['NULL'] and e.length != 0:
            self.read(delim='\n', expect="ERROR: invalid length for null\n");
            dbg('ERROR: invalid length for null %d' % e.length)
            return None

        e.start = i + read + 1
        e.data = self.state['stream'][e.start:e.start + e.length]
        if e.start >= len(self.state['stream']):
            self.read(delim='\n', expect="ERROR: bounds exceeded\n");
            dbg('ERROR 1: bounds exceeded')
            dbg("%d >= %d" % (i , len(self.state['stream'])))
            return None

        if not e.primitive:
            cur = e.start
            while True:
                sub = self._decode(cur, depth + 1)
                if sub is None:
                    return None

                e.subs.append(sub)
                cur = sub.start + sub.length

                if cur >= e.start + e.length:
                    break

        return e

    def print_tag(self, e):
        ex = ""
        if e.cls == CS['UNIVERSAL']:
            if e.tag < 0 or e.tag > len(TS):
                ex += "UNIVERSAL %d " % e.tag
            else:
                for k, v in TS.iteritems():
                    if v == e.tag:
                        ex += "UNIVERSAL %s " % k
                        break
        elif e.cls == CS['APPLICATION']:
            ex += "APPLICATION_%d " % e.tag
        elif e.cls == CS['PRIVATE']:
            ex += "PRIVATE_%d " % e.tag
        elif e.cls == CS['CONTEXT']:
            ex += "[%d]" % e.tag
        elif e.cls == CS['UNKNOWN']:
            ex += "UNKNOWN_%d " % e.tag

        if len(ex):
            self.read(expect=ex, length=len(ex))

    def print_string(self, e):
        ex = ""

        for i in xrange(e.length):
            if e.data[i] in string.ascii_letters + string.digits:
                ex += "%c" % e.data[i]
            else:
                ex += '\\x%x' % ord(e.data[i])

        if len(ex):
            self.read(expect=ex, length=len(ex))

    def print_time(self, e, utc):
        ex = ""
        if utc:
            if e.length < 12:
                self.read(expect="INVALID TIME", length=len("INVALID TIME"))
                return

            for i in xrange(12):
                if e.data[i] not in string.digits:
                    self.read(expect="INVALID TIME", length=len("INVALID TIME"))
                    return

            ex += "%c%c/%c%c/" % (
                e.data[4], e.data[5], e.data[2], e.data[3]
            )

            if e.data[6] < '6':
                ex += "20"
            else:
                ex += "19"
            ex += "%c%c" % (e.data[0], e.data[1])
            ex += " %c%c:%c%c:%c%c GMT" % (
                e.data[6], e.data[7], e.data[8],
                e.data[9], e.data[10], e.data[11]
            )
        else:
            if e.length < 14:
                self.read(expect="INVALID TIME", length=len("INVALID TIME"))
                return

            for i in xrange(14):
                if e.data[i] not in string.digits:
                    self.read(expect="INVALID TIME", length=len("INVALID TIME"))
                    return

            ex += "%c%c/%c%c/%c%c%c%c" % (
                e.data[6], e.data[7], e.data[4], e.data[5],
                e.data[0], e.data[1], e.data[2], e.data[3]
            )
            ex += " %c%c:%c%c:%c%c GMT" % (
                e.data[8], e.data[9], e.data[10],
                e.data[11], e.data[12], e.data[13]
            )

        if len(ex):
            self.read(expect=ex, length=len(ex))

    def print_hex(self, e):
        ex = ""
        if e.length > 16:
            ex += "\n"
            ex += '    ' * (e.depth + 1)
            for i in xrange(e.length):
                ex += "%02X" % ord(e.data[i])
                if i % 32 == 31:
                    ex += "\n"
                    ex += '    ' * (e.depth + 1)
                else:
                    ex += ' '
        else:
            for i in xrange(e.length):
                ex += "%02X " % ord(e.data[i])

        if len(ex):
            self.read(expect=ex, length=len(ex))

    def read_octet_int(self, data, l):
        v = 0
        i = 0
        while i < 4 and i < l:
            v <<= 7
            v |= ord(data[i]) & 0x7F
            if ord(data[i]) & 0x80 == 0:
                return i + 1, v & 0xFFFFFFFF

            i += 1

        return -1, v & 0xFFFFFFFF

    def print_oid(self, e):
        self.read(expect='[\d.]*', expect_format='pcre', delim='\n')

    def print_primitive(self, e):
        if e.cls == CS['UNIVERSAL']:
            if e.tag == TS['BOOLEAN']:
                if ord(e.data[0]) == 0:
                    self.read(expect="False", length=5)
                else:
                    self.read(expect="True", length=4)
            elif (e.tag == TS['INTEGER'] or
                  e.tag == TS['BITSTR'] or
                  e.tag == TS['OCTETSTR']):
                self.print_hex(e)
            elif e.tag == TS['OID']:
                self.print_oid(e)
            elif e.tag == TS['UTCTIME']:
                self.print_time(e, 1)
            elif e.tag == TS['GENTIME']:
                self.print_time(e, 0)
            elif (e.tag == TS['UTFSTR'] or
                  e.tag == TS['NUMSTR'] or
                  e.tag == TS['PRINTSTR'] or
                  e.tag == TS['TELESTR'] or
                  e.tag == TS['VIDSTR'] or
                  e.tag == TS['IA5STR'] or
                  e.tag == TS['VISSTR']):
                self.print_string(e)
            else:
                self.read(expect="UNPRINTABLE", length=len("UNPRINTABLE"))
        else:
            self.read(expect="UNPRINTABLE", length=len("UNPRINTABLE"))

    def _pprint(self, e):
        if e.depth > 0:
            self.read(expect='    ' * e.depth, length=(4 * e.depth))
        self.print_tag(e)

        if e.primitive:
            self.print_primitive(e)
            if not (e.cls == CS['UNIVERSAL'] and e.tag == TS['OID']):
                self.read(expect='\n', length=1)
        else:
            self.read(expect='\n', length=1)
            for sub in e.subs:
                self._pprint(sub)

    def pprint(self):
        if len(self.state['stream']) > 32 * 1024:
            self.read(expect='too big', delim='\n')
            return None

        e = self._decode(0, 0)
        if e:
            self._pprint(e)

    def gen_element(self):
        pass

    def encode_and_emit(self):
        self.state['stream'] = self.root.encode()
        self.write(pack('<I', len(self.state['stream'])))
        self.write(self.state['stream'])

    def start(self):
        self.state['cur_depth'] = 0
        self.root = Element(self.state['cur_depth'], cls=CS['UNIVERSAL'], tag=TS['SEQ'])
