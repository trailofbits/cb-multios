#!/usr/bin/env python

from generator.actions import Actions
import random
import string
import struct


def kaprica_mixin(self):
    if hasattr(self, 'xlat_seed'):
        return

    def xlat_seed(seed):
        def hash_string(seed):
            H = 0x314abc86
            for c in seed:
                H = (H * 37) & 0xffffffff
                H ^= ord(c)
                H = ((H << 13) ^ (H >> 19)) & 0xffffffff
            return H

        def hash_iterate(H):
            H = (H * 3) & 0xffffffff
            H = ((H << 13) ^ (H >> 19) ^ (H >> 21)) & 0xffffffff
            return H
        xmap = list(xrange(256))
        xmap_inv = list(xrange(256))
        state = hash_string(seed)
        for i in xrange(255, 0, -1):
            j = state % i
            state = hash_iterate(state)
            xmap[i], xmap[j] = xmap[j], xmap[i]
        for i in xrange(256):
            xmap_inv[xmap[i]] = i
        self.xlat_map = xmap
        self.xlat_map_inv = xmap_inv
    self.xlat_seed = xlat_seed
    self.xlat_map = None
    self.xlat_map_inv = None

    def xlat_string(s, inverse=False):
        if inverse:
            return ''.join([chr(self.xlat_map_inv[ord(c)]) for c in s])
        return ''.join([chr(self.xlat_map[ord(c)]) for c in s])
    self.xlat_string = xlat_string

    def read(delim=None, length=None, expect=None):
        if self.xlat_map:
            if delim:
                delim = self.xlat_string(delim)
            if expect:
                expect = self.xlat_string(expect)
        return self._original_read(delim=delim, length=length, expect=expect)
    self._original_read = self.read
    self.read = read

    def write(s):
        if self.xlat_map:
            if s:
                s = self.xlat_string(s)
        return self._original_write(s)
    self._original_write = self.write
    self.write = write


class File(object):
    def __init__(self, path):
        self.name = pcs(path)[-1]
        self.path = path
        self.data = ''
        self.ref_cnt = 0

RDONLY = 1 << 0
RDWR = 1 << 1
TRUNC = 1 << 2
APPEND = 1 << 3
MAX_FDS = 1024

STATUS_OK = 1
STATUS_ERR = 2


class FileHandle(object):
    def __init__(self, f, flags):
        self.f = f
        self.flags = flags

        if flags & APPEND:
            self.offset = len(self.f.data)
        else:
            self.offset = 0

        f.ref_cnt += 1

    def write(self, s):
        after = self.f.data[self.offset + len(s):]
        self.f.data = self.f.data[:self.offset] + s + after


class Request(object):
    TYPES = {
        'OPEN_F_NUM': 1,
        'READ_F_NUM': 2,
        'WRITE_F_NUM': 3,
        'LSEEK_F_NUM': 4,
        'CLOSE_F_NUM': 5,
        'CREAT_F_NUM': 6,
        'UNLINK_F_NUM': 7,
    }

    def __init__(self, _type):
        self._type = _type
        self._pl = ''

    def append(self, data):
        if isinstance(data, int):
            self._pl += struct.pack('<I', data)
        elif isinstance(data, str):
            self._pl += struct.pack('<I', len(data))
            self._pl += data

    def serialize(self):
        s = struct.pack('<I', self._type)
        s += struct.pack('<I', len(self._pl))
        s += self._pl
        return s


dirs = [''.join(random.sample(string.lowercase, random.randint(1, 8))) for _ in range(32)]


def rp():
    x = '/'.join(random.sample(dirs, random.randint(1, 5)))
    return '/' + x


def rs(_max=8 * 1024):
    return ''.join(random.choice(string.lowercase) for _ in range(random.randint(0, _max)))


def pcs(p, include_last=True):
    if include_last:
        return filter(None, p.split('/'))
    else:
        return filter(None, p.split('/'))[:-1]


class TemplateGenerator(Actions):
    def readln(self, s):
        self.read(expect=s, delim='\n')

    def start(self):
        #self.delay(100)
        # kaprica_mixin(self)
        # self.xlat_seed('HASHTAGYOLOSWAG')

        self.readln('FSAAS')
        sig = 0
        for i in xrange(0, 0x1000, 4):
            sig ^= struct.unpack('<I', self.magic_page[i: i + 4])[0]
        self.readln(hex(sig)[2:-1])

        self.tree = {}
        self.files = []
        self.fhs = [None] * MAX_FDS

    def req_loop(self):
        pass

    def read_req_fin(self):
        self.read(delim=struct.pack('<Q', 0x8442e492f255bf31))

    def read_error(self):
        self.read(length=4, expect=struct.pack('<I', STATUS_ERR))
        self.read_req_fin()

    def read_ok(self):
        self.read(length=4, expect=struct.pack('<I', STATUS_OK))
        self.read_req_fin()

    def read_fd(self, n):
        self.read(length=4, expect=struct.pack('<I', STATUS_OK))
        self.read(length=4)
        self.read(length=4, expect=struct.pack('<I', n))
        self.read_req_fin()

    def do_open(self):
        r = Request(Request.TYPES['OPEN_F_NUM'])

        if not self.files:
            return

        if random.random() < 0.80:
            pathname = random.choice(self.files).path
        else:
            pathname = rp()

        flags = 0
        if random.random() < 0.5:
            flags |= RDONLY
        else:
            flags |= RDWR

        if random.random() < 0.5:
            flags |= TRUNC
        else:
            flags |= APPEND

        mode = 0xdead

        if flags & RDONLY:
            flags = RDONLY | TRUNC

        if not (flags & TRUNC or flags & APPEND):
            flags |= APPEND

        if not (flags & RDONLY or flags & RDWR):
            flags |= RDONLY

        r.append(pathname)
        r.append(flags)
        r.append(mode)

        self.readln('QQQ')
        self.write(r.serialize())

        node = self.tree
        for pc in pcs(pathname, False):
            if isinstance(node, dict) and pc in node and isinstance(node[pc], dict):
                node = node[pc]
            else:
                self.read_error()
                return

        name = pcs(pathname)[-1]
        if not (name in node and isinstance(node[name], File)):
            self.read_error()
            return
        else:
            node = node[name]

        fd = None
        for i, x in enumerate(self.fhs):
            if not x:
                fd = i
                break

        if fd is None:
            self.read_error()
            return

        self.fhs[fd] = FileHandle(node, flags)
        self.read_fd(fd)

    def do_read(self):
        r = Request(Request.TYPES['READ_F_NUM'])

        f = random.choice(filter(None, self.fhs) + [None])

        if f:
            fd = self.fhs.index(f)
        else:
            fd = 9999

        if random.random() < 0.15:
            fd = len(self.fhs) + 1

        if f and len(f.f.data) > 0:
            count = random.randint(0, max(0, len(f.f.data) - f.offset))
        else:
            count = 9999

        r.append(fd)
        r.append(count)

        self.readln('QQQ')
        self.write(r.serialize())

        if not f or fd >= len(self.fhs) or count > len(f.f.data) - f.offset:
            self.read_error()
            return

        f.offset += count
        self.read(length=4, expect=struct.pack('<I', STATUS_OK))
        self.read(length=4)
        self.read(length=4, expect=struct.pack('<I', count))
        self.read_req_fin()

    def do_write(self):
        r = Request(Request.TYPES['WRITE_F_NUM'])

        f = random.choice(filter(None, self.fhs) + [None])
        if f:
            fd = self.fhs.index(f)
        else:
            fd = 9999

        if random.random() < 0.15:
            fd = len(self.fhs) + 1

        data = rs()

        r.append(fd)
        r.append(data)

        self.readln('QQQ')
        self.write(r.serialize())

        if not f or fd >= len(self.fhs) or f.flags & RDONLY:
            self.read_error()
            return

        if f:
            f.write(data)

        f.offset += len(data)
        self.read(length=4, expect=struct.pack('<I', STATUS_OK))
        self.read(length=4)
        self.read(length=4, expect=struct.pack('<I', len(data)))
        self.read_req_fin()

    def do_lseek(self):
        SEEK_SET = 0
        SEEK_CUR = 1

        r = Request(Request.TYPES['LSEEK_F_NUM'])

        f = random.choice(filter(None, self.fhs) + [None])

        if f:
            fd = self.fhs.index(f)
        else:
            fd = 9999

        whence = random.choice([SEEK_SET, SEEK_CUR])

        if f:
            if whence == SEEK_SET:
                offset = random.randint(0, len(f.f.data))
            else:
                offset = random.randint(0, max(0, len(f.f.data) - f.offset))
        else:
            offset = 9999

        r.append(fd)
        r.append(offset)
        r.append(whence)

        self.readln('QQQ')
        self.write(r.serialize())

        if not f or fd >= len(self.fhs):
            self.read_error()
            return

        if whence == SEEK_SET and offset >= len(f.f.data):
            self.read_error()
            return

        if whence == SEEK_CUR and offset + f.offset >= len(f.f.data):
            self.read_error()
            return

        if whence == SEEK_SET:
            f.offset = offset
        else:
            f.offset += offset

        self.read(length=4, expect=struct.pack('<I', STATUS_OK))
        self.read(length=4, expect=struct.pack('<I', 4))
        self.read(length=4, expect=struct.pack('<I', f.offset))
        self.read_req_fin()

    def do_close(self):
        r = Request(Request.TYPES['CLOSE_F_NUM'])

        if self.fhs:
            possible = list(enumerate(self.fhs))
            try:
                fd, x = random.choice(filter(all, possible))
            except IndexError:
                fd, x = 9999, None
        else:
            fd, x = 9999, None

        if not x:
            r.append(fd)
            self.readln('QQQ')
            self.write(r.serialize())
            self.read_error()

    def do_creat(self):
        MAKE_PARENTS = 1 << 1
        r = Request(Request.TYPES['CREAT_F_NUM'])

        pathname = rp()
        mode = 0

        if random.random() < 0.65:
            mode |= MAKE_PARENTS

        r.append(pathname)
        r.append(mode)

        self.readln('QQQ')
        self.write(r.serialize())

        node = self.tree
        for pc in pcs(pathname, False):
            if isinstance(node, dict) and pc in node and isinstance(node[pc], dict):
                node = node[pc]
            elif isinstance(node, dict) and pc not in node and mode & MAKE_PARENTS:
                node[pc] = {}
                node = node[pc]
            else:
                self.read_error()
                return

        if not isinstance(node, dict):
            self.read_error()
            return

        lpc = pcs(pathname)[-1]

        if lpc in node:
            self.read_error()
            return

        node[lpc] = File(pathname)
        self.files.append(node[lpc])
        self.read_ok()

    def do_unlink(self):
        r = Request(Request.TYPES['UNLINK_F_NUM'])

        if not self.files:
            return

        if random.random() < 0.80:
            pathname = random.choice(self.files).path
        else:
            pathname = rp()

        r.append(pathname)

        parent = None
        node = self.tree
        try:
            for pc in pcs(pathname):
                parent = node
                node = node[pc]
        except (TypeError, KeyError):
            self.readln('QQQ')
            self.write(r.serialize())
            self.read_error()
            return

        if not isinstance(node, File):
            self.readln('QQQ')
            self.write(r.serialize())
            self.read_error()
            return

        if node.ref_cnt == 1:
            return

        self.readln('QQQ')
        self.write(r.serialize())

        if node.ref_cnt != 0:
            self.read_error()
            return

        del parent[node.name]
        self.files.remove(node)
        self.read_ok()

    def done(self):
        self.write(struct.pack('<I', 0xb7eb7e))
