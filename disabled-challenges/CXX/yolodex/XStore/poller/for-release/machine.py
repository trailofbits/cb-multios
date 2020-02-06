#!/usr/bin/env python

from generator.actions import Actions
import random, string, struct

def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(5,size))])
def random_string_s(size=20):
    return ''.join([random.choice(string.ascii_letters + ' ') for x in xrange(random.randint(1,size))])
def random_bytes(size=20):
    return ''.join([chr(random.randint(1,255)) for x in xrange(random.randint(1,size))])
def random_bytes_n(size=20):
    return ''.join([chr(random.randint(0,255)) for x in xrange(size)])

class XPKObject(object):
    def __init__(self, t=None, d=None):
        self.t = t
        self.d = d

class XPK(object):

    TYPE_POSITIVE_FIXINT = 0x00
    TYPE_NEGATIVE_FIXINT = 0xE0
    TYPE_FIXSTRING       = 0x80
    TYPE_NONE            = 0xA0
    TYPE_FALSE           = 0xA1
    TYPE_TRUE            = 0xA2
    TYPE_BYTES           = 0xA3
    TYPE_ARRAY           = 0xA4
    TYPE_MAP             = 0xA5
    TYPE_NIL             = 0xA6
    TYPE_INT8            = 0xB0
    TYPE_INT16           = 0xB1
    TYPE_INT32           = 0xB2
    TYPE_INT64           = 0xB3
    TYPE_UINT8           = 0xC0
    TYPE_UINT16          = 0xC1
    TYPE_UINT32          = 0xC2
    TYPE_UINT64          = 0xC3
    TYPE_STRING          = 0xD0

    def __init__(self):
        self.reset()

    def reset(self):
        self.buf = ''
        self.idx = 0

    def swap16(self, n, s):
        fmt = 'h' if s else 'H'
        return struct.unpack('<'+fmt, struct.pack('>'+fmt, n))[0]

    def swap32(self, n, s):
        fmt = 'i' if s else 'I'
        return struct.unpack('<'+fmt, struct.pack('>'+fmt, n))[0]

    def swap64(self, n, s):
        fmt = 'q' if s else 'Q'
        return struct.unpack('<'+fmt, struct.pack('>'+fmt, n))[0]

    def write(self, fmt, data, sz):
        self.buf += struct.pack(fmt, data)
        self.idx += sz

    def write_r(self, data):
        self.buf += data
        self.idx += len(data)

    def read(self, fmt, sz):
        d = struct.unpack(fmt, self.buf[self.idx:self.idx+sz])[0]
        self.idx += sz
        return d

    def read_r(self, sz):
        d = self.buf[self.idx:self.idx+sz]
        self.idx += sz
        return d

    def peek(self, fmt, sz):
        return struct.unpack(fmt, self.buf[self.idx:self.idx+sz])[0]

    def write_marker(self, t):
        self.write('>B', t, 1)

    def read_marker(self):
        t = self.read('>B', 1)
        return t

    def read_obj(self):
        marker = self.read_marker()
        o = XPKObject()
        o.t = marker
        if marker == self.TYPE_FALSE:
            o.d = 0
        elif marker == self.TYPE_TRUE:
            o.d = 1
        elif marker == self.TYPE_BYTES or marker == self.TYPE_STRING:
            o.d = self.read('>H', 2)
        elif marker == self.TYPE_ARRAY or marker == self.TYPE_MAP:
            o.d = self.read('>B', 1)
        elif marker == self.TYPE_INT8:
            o.d = self.read('>b', 1)
        elif marker == self.TYPE_INT16:
            o.d = self.read('>h', 2)
        elif marker == self.TYPE_INT32:
            o.d = self.read('>i', 4)
        elif marker == self.TYPE_INT64:
            o.d = self.read('>q', 8)
        elif marker == self.TYPE_UINT8:
            o.d = self.read('>B', 1)
        elif marker == self.TYPE_UINT16:
            o.d = self.read('>H', 2)
        elif marker == self.TYPE_UINT32:
            o.d = self.read('>I', 4)
        elif marker == self.TYPE_UINT64:
            o.d = self.read('>Q', 8)
        elif marker == self.TYPE_NIL:
            pass
        else:
            if marker < 0x80:
                o.t = self.TYPE_POSITIVE_FIXINT
                o.d = marker
            elif marker < 0xA0:
                o.t = self.TYPE_FIXSTRING
                o.d = marker & 0x1F
            elif marker >= 0xE0:
                o.t = self.TYPE_NEGATIVE_FIXINT
                o.d = struct.unpack('<b', struct.pack('<B', marker))[0]
            else:
                o.t = self.TYPE_NONE
                o.d = 0
        return o

    def next_type(self):
        marker = self.peek('<B', 1)
        if marker < 0x80:
            t = self.TYPE_POSITIVE_FIXINT
        elif marker < 0xA0:
            t = self.TYPE_FIXSTRING
        elif marker >= 0xE0:
            t = self.TYPE_NEGATIVE_FIXINT
        else:
            t = marker
        return t

    def pack_fixint(self, b):
        self.write('>B', b, 1)

    def pack_int(self, si):
        if si >= 0:
            self.pack_uint(si)
            return
        if si >= -32:
            self.pack_fixint(si)
        elif si >= -128:
            self.write_marker(self.TYPE_INT8)
            self.write('>b', si, 1)
        elif si >= -32768:
            self.write_marker(self.TYPE_INT16)
            self.write('>h', si, 2)
        elif si >= -2147483648:
            self.write_marker(self.TYPE_INT32)
            self.write('>i', si, 4)
        else:
            self.write_marker(self.TYPE_INT64)
            self.write('>q', si, 8)

    def pack_uint(self, ui):
        if ui < 128:
            self.pack_fixint(ui)
        elif ui < 256:
            self.write_marker(self.TYPE_UINT8)
            self.write('>B', ui, 1)
        elif ui < 65536:
            self.write_marker(self.TYPE_UINT16)
            self.write('>H', ui, 2)
        elif ui <= 0xFFFFFFFF:
            self.write_marker(self.TYPE_UINT32)
            self.write('>I', ui, 4)
        else:
            self.write_marker(self.TYPE_UINT64)
            self.write('>Q', ui, 8)

    def pack_none(self):
        self.write_marker(self.TYPE_NONE)

    def pack_nil(self):
        self.write_marker(self.TYPE_NIL)

    def pack_bool(self, b):
        self.write_marker(self.TYPE_TRUE if b else self.TYPE_FALSE)

    def pack_str(self, s):
        sz = len(s)
        if sz <= 0x1F:
            val = self.TYPE_FIXSTRING | sz
            self.write('>B', val, 1)
            if sz > 0:
                self.write_r(s)
        elif sz < 65536:
            self.write_marker(self.TYPE_STRING)
            self.write('>H', sz, 2)
            self.write_r(s)

    def pack_bytes(self, bs):
        sz = len(bs)
        if sz < 65536:
            self.write_marker(self.TYPE_BYTES)
            self.write('>H', sz, 2)
            if sz > 0:
                self.write_r(bs)

    def pack_array(self, sz):
        if sz < 256:
            self.write_marker(self.TYPE_ARRAY)
            self.write('>B', sz, 1)

    def pack_map(self, sz):
        if sz < 256:
            self.write_marker(self.TYPE_MAP)
            self.write('>B', sz, 1)

    def unpack_int(self):
        o = self.read_obj()
        if o.t == self.TYPE_NEGATIVE_FIXINT or o.t == self.TYPE_INT8 or o.t == self.TYPE_INT16 or o.t == self.TYPE_INT32 or o.t == self.TYPE_INT64:
            return o.d, True
        elif o.t == self.TYPE_POSITIVE_FIXINT or o.t == self.TYPE_UINT8 or o.t == self.TYPE_UINT16 or o.t == self.TYPE_UINT32 or o.t == self.TYPE_UINT64:
            return o.d, False
        else:
            return None, None

    def unpack_nil(self):
        o = self.read_obj()

    def unpack_bool(self):
        o = self.read_obj()
        if o.t != self.TYPE_TRUE and o.t != self.TYPE_FALSE:
            return None
        return o.d

    def unpack_str(self):
        o = self.read_obj()
        if o.t != self.TYPE_FIXSTRING and o.t != self.TYPE_STRING:
            return None
        return o.d

    def unpack_bytes(self):
        o = self.read_obj()
        if o.t != self.TYPE_BYTES:
            return None
        return o.d

    def unpack_array(self):
        o = self.read_obj()
        if o.t != self.TYPE_ARRAY:
            return None
        return o.d

    def unpack_map(self):
        o = self.read_obj()
        if o.t != self.TYPE_MAP:
            return None
        return o.d


class AXSTORE(Actions):

    TYPE_INT = 0
    TYPE_UINT = 1
    TYPE_BOOL = 2
    TYPE_STRING = 3
    TYPE_BYTES = 4
    TYPE_NIL = 5
    TYPE_MAP = 6
    TYPE_ARRAY = 7
    TYPE_NONE = 8

    CMD_STORE   = 0x4414803BA52CB50D
    CMD_LOOKUP  = 0xF0CEC4CA602CCFF8
    CMD_DELETE  = 0x0842ABE098A0D38E
    CMD_DEBUG   = 0x7B7947D03E5DF85D
    CMD_PRINT   = 0xEDB20325B2A3505B
    CMD_QUIT    = 0xB483456220FC57CC
    COMMANDS    = [CMD_STORE, CMD_LOOKUP, CMD_DELETE, CMD_DEBUG, CMD_PRINT, CMD_QUIT]

    RES_OK          = 0x0
    RES_ERR_PARSING = 0x12B3AC854AF56710
    RES_ERR_KEY     = 0xDFF50A123E5949EA
    RES_INVALID     = 0x5C60BEF967440470

    MAX_PRINT_DEPTH = 32

    def send_cmd(self, cmd, payload=''):
        s  = struct.pack('<QI', cmd, len(payload))
        s += payload
        self.write(s)

    def read_resp(self, resp):
        s = struct.pack('<Q', resp)
        self.read(length=len(s), expect=s)

    def start(self):
        #self.delay(100)
        self.state['debug'] = False
        self.state['g_ctx'] = XPK()
        self.state['g_map'] = {}

        self.write(self.magic_page[:4])
        self.read(length=0x1000, expect=self.magic_page)

    def ready(self):
        pass

    def store(self):
        m = {}
        r = random.randint(1, 5)
        for i in xrange(r):
            m[random_string(15)] = self.random_object()
        g_map = self.state['g_map']
        g_ctx = self.state['g_ctx']
        g_ctx.reset()
        g_ctx.pack_map(len(m))
        for k, v in m.iteritems():
            g_map[k] = v
            g_ctx.pack_str(k)
            self.pack_object(g_ctx, v)
        self.send_cmd(self.CMD_STORE, g_ctx.buf)

        g_ctx.reset()
        g_ctx.pack_array(len(m))
        for k in sorted(m.keys()):
            g_ctx.pack_str(k)
        self.read_resp(self.RES_OK)
        self.read(length=len(g_ctx.buf), expect=g_ctx.buf)

    def lookup(self):
        g_map = self.state['g_map']
        a = random.sample(g_map.keys(), min(len(g_map.keys()), random.randint(1, 5)))
        if random.randint(1, 100) <= 10:
            a.append(random_string(15))
        g_ctx = self.state['g_ctx']
        g_ctx.reset()
        g_ctx.pack_array(len(a))
        for e in a:
            g_ctx.pack_str(e)
        self.send_cmd(self.CMD_LOOKUP, g_ctx.buf)

        g_ctx.reset()
        g_ctx.pack_map(len(a))
        for e in sorted(a):
            if e in g_map.keys():
                o = g_map[e]
            else:
                o = XPKObject(self.TYPE_NONE)
            g_ctx.pack_str(e)
            self.pack_object(g_ctx, o)
        self.read_resp(self.RES_OK)
        self.read(length=len(g_ctx.buf), expect=g_ctx.buf)

    def delete(self):
        g_map = self.state['g_map']
        a = random.sample(g_map.keys(), min(len(g_map.keys()), random.randint(1, 3)))
        if random.randint(1, 100) <= 10:
            a.append(random_string(15))
        g_ctx = self.state['g_ctx']
        g_ctx.reset()
        g_ctx.pack_array(len(a))
        for e in a:
            g_ctx.pack_str(e)
        self.send_cmd(self.CMD_DELETE, g_ctx.buf)

        g_ctx.reset()
        g_ctx.pack_map(len(a))
        for e in sorted(a):
            if e in g_map.keys():
                o = g_map.pop(e)
            else:
                o = XPKObject(self.TYPE_NONE)
            g_ctx.pack_str(e)
            self.pack_object(g_ctx, o)
        self.read_resp(self.RES_OK)
        self.read(length=len(g_ctx.buf), expect=g_ctx.buf)

    def debug(self):
        debug_key = "\x13\xbem\x9b\x83s\x9d\x07\xcak\xcc\xee@k\x7f\xe1\xec\x03\xa7\x37"
        a = [random.choice([True, False]), random.choice([debug_key, random_bytes(30)])]
        g_ctx = self.state['g_ctx']
        g_ctx.reset()
        g_ctx.pack_array(len(a))
        g_ctx.pack_bool(a[0])
        g_ctx.pack_bytes(a[1])
        self.send_cmd(self.CMD_DEBUG, g_ctx.buf)

        if a[1] == debug_key:
            g_ctx.reset()
            o = XPKObject(self.TYPE_BOOL, a[0])
            self.pack_object(g_ctx, o)
            self.read_resp(self.RES_OK)
            self.read(length=len(g_ctx.buf), expect=g_ctx.buf)
            self.state['debug'] = a[0]
        else:
            self.read_resp(self.RES_ERR_KEY)

    def print_item(self, s, depth, o, i, n):
        if o.t == self.TYPE_INT:
            s += '%d\x0b' % struct.unpack('<i', struct.pack('<I', (o.d & 0xFFFFFFFF)))[0]
        elif o.t == self.TYPE_UINT:
            s += '%u\x0b' % (o.d & 0xFFFFFFFF)
        elif o.t == self.TYPE_BOOL:
            s += '%s\x0b' % ('true' if o.d else 'false')
        elif o.t == self.TYPE_STRING:
            s += '"%s"\x0b' % o.d
        elif o.t == self.TYPE_BYTES:
            e = ''
            for c in o.d:
                e += c if c.isalnum() else ('\\%02X' % ord(c))
            s += '<%s>\x0b' % e
        elif o.t == self.TYPE_NIL:
            s += 'NIL\x0b'
        elif o.t == self.TYPE_MAP:
            s += '{\x0b'
            s, i = self.print_map(s, depth + 1, o.d, i, n)
            s += '}\x0b'
        elif o.t == self.TYPE_ARRAY:
            s += '[\x0b'
            s, i = self.print_array(s, depth + 1, o.d, i, n)
            s += ']\x0b'
        return s, i

    def print_array(self, s, depth, a, i, n):
        if depth == self.MAX_PRINT_DEPTH:
            return s,i
        indent = '\t'*depth
        for k in xrange(len(a)):
            if i < n or n == 0:
                s += '%s%d  =>  [VALUE]: ' % (indent, k)
                s, i = self.print_item(s, depth, a[k], i, n)
                i += 1
        return s, i

    def print_map(self, s, depth, m, i, n):
        if depth == self.MAX_PRINT_DEPTH:
            return s,i
        indent = '\t'*depth
        for k in sorted(m.keys()):
            if i < n or n == 0:
                s += '%s[KEY]: %s  =>  [VALUE]: ' % (indent, k)
                s, i = self.print_item(s, depth, m[k], i, n)
                i += 1
        return s, i

    def pprint(self):
        g_map = self.state['g_map']
        g_ctx = self.state['g_ctx']
        g_ctx.reset()
        g_ctx.write_marker(XPK.TYPE_UINT64)
        r = random.randint(0, len(g_map))
        g_ctx.write('>Q', r, 8)
        self.send_cmd(self.CMD_PRINT, g_ctx.buf)

        if self.state['debug']:
            self.read_resp(self.RES_OK)
            s = '\x0b'
            s,i = self.print_map(s, 0, g_map, 0, r) 
            s += '\x0b'
            self.read(length=len(s), expect=s)
        else:
            self.read_resp(self.RES_INVALID)

    def invalid(self):
        while True:
            r = random.randint(0, 0xFFFFFFFFFFFFFFFF)
            if r not in self.COMMANDS:
                break
        self.send_cmd(r)
        self.read_resp(self.RES_INVALID)

    def quit(self):
        self.send_cmd(self.CMD_QUIT)
        self.read_resp(self.RES_OK)

    def pack_object(self, ctx, obj):
        if obj.t == self.TYPE_INT:
            ctx.pack_int(obj.d)
        elif obj.t == self.TYPE_UINT:
            ctx.pack_uint(obj.d)
        elif obj.t == self.TYPE_BOOL:
            ctx.pack_bool(obj.d)
        elif obj.t == self.TYPE_STRING:
            ctx.pack_str(obj.d)
        elif obj.t == self.TYPE_BYTES:
            ctx.pack_bytes(obj.d)
        elif obj.t == self.TYPE_NIL:
            ctx.pack_nil()
        elif obj.t == self.TYPE_MAP:
            ctx.pack_map(len(obj.d))
            for k in sorted(obj.d.keys()):
                ctx.pack_str(k)
                self.pack_object(ctx, obj.d[k])
        elif obj.t == self.TYPE_ARRAY:
            ctx.pack_array(len(obj.d))
            for e in obj.d:
                self.pack_object(ctx, e)
        elif obj.t == self.TYPE_NONE:
            ctx.pack_none()

    def random_object(self):
        types = (self.TYPE_INT, self.TYPE_UINT, self.TYPE_BOOL, self.TYPE_STRING, self.TYPE_BYTES, self.TYPE_NIL, self.TYPE_MAP, self.TYPE_ARRAY)
        t = random.choice(types)
        if t == self.TYPE_INT:
            obj = XPKObject(t, random.randint(-0x7FFFFFFF, 0x7FFFFFFF))
        elif t == self.TYPE_UINT:
            obj = XPKObject(t, random.randint(0, 0xFFFFFFFF))
        elif t == self.TYPE_BOOL:
            obj = XPKObject(t, random.choice((True, False)))
        elif t == self.TYPE_STRING:
            obj = XPKObject(t, random_string(30))
        elif t == self.TYPE_BYTES:
            obj = XPKObject(t, random_bytes(30))
        elif t == self.TYPE_NIL:
            obj = XPKObject(t)
        elif t == self.TYPE_MAP:
            obj = XPKObject(t, {})
            length = random.randint(1, 5)
            for x in xrange(length):
                o = self.random_object()
                k = random_string(10)
                obj.d[k] = o
        elif t == self.TYPE_ARRAY:
            obj = XPKObject(t, [])
            length = random.randint(1, 5)
            for x in xrange(length):
                o = self.random_object()
                obj.d.append(o)
        return obj
