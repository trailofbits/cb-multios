#!/usr/bin/env python
from generator.actions import Actions
import random
import struct

def hash_string(s, t):
    initials = [
        0,
        0x12345678,
        0x9abcdef,
        0x13579bdf,
        0x02468ace,
        0xdeadbeef,
        0xea7beef,
        0x98765432
    ]
    result = initials[t]
    for x in xrange(0, 0x1000, 4):
        foo = struct.unpack('<I', s[x:x+4])[0]
        result = ((result << 7) ^ (result >> 24)) & 0xffffffff
        result ^= foo
        result = ((result << 13) ^ (result >> 20)) & 0xffffffff
    return result
def escape(s):
    return (s
        .replace('\0', '\\0')
        .replace('\b', '\\b')
        .replace('\r', '\\r')
        .replace('\n', '\\n')
        .replace('\t', '\\t')
    )
def random_string(cnt=None):
    if cnt is None:
        cnt = random.randint(4, 200)
    return escape(''.join([chr(random.randint(0, 255)) for x in xrange(cnt)]))

# tables for multiplication in GF(2^8) using a primitive polynomial of 0x11D
gf_exp = [1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161, 95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226, 217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206, 129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204, 133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84, 168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115, 230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65, 130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166, 81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9, 18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22, 44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142]
gf_log = [0, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75, 4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166, 6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61, 202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175]

def gf_mul(x, y):
    if x == 0 or y == 0:
        return 0
    # g^(log_g(x)+log_g(y)) == x*y
    return gf_exp[(gf_log[x] + gf_log[y]) % 255]
def gf_div(x, y):
    if x == 0:
        return 0
    # g^(log_g(x)-log_g(y)) == x/y
    return gf_exp[(gf_log[x] + 255 - gf_log[y]) % 255]
def gf_inverse(x):
    return gf_exp[(255 - gf_log[x]) % 255]
def gf_poly_eval(poly, x):
    result = poly[0]
    for i in xrange(1, len(poly)):
        result = gf_mul(result, x) ^ poly[i]
    return result
def gf_poly_add(x, y):
    result = [0] * max(len(x), len(y))
    for i in xrange(len(x)):
        result[len(result) - len(x) + i] = x[i]
    for i in xrange(len(y)):
        result[len(result) - len(y) + i] ^= y[i]
    return result
def gf_poly_mul_const(x, c):
    result = [0] * len(x)
    for i in xrange(len(x)):
        result[i] = gf_mul(x[i], c)
    return result
def gf_poly_mul(x, y):
    # long multiplication of polynomials x and y
    result = [0] * (len(x) + len(y) - 1)
    for i in xrange(len(x)):
        for j in xrange(len(y)):
            result[i + j] ^= gf_mul(x[i], y[j])
    return result
def gf_poly_mod(x, y):
    # returns x % y
    result = list(x)
    for i in xrange(len(x) - len(y) + 1):
        c = result[i] # store now since it is modified in the loop
        for j in xrange(len(y)):
            result[i + j] ^= gf_mul(c, y[j])
    return result[-len(y)+1:]
def gen_poly(k, n=0):
    # calculate (x - a^n) * (x - a^(n+1)) ... * (x - a^(n+k-1))
    result = [1]
    for i in xrange(k):
        result = gf_poly_mul(result, [1, gf_exp[n + i]])
    return result
def calc_syn(msg, k, n=0):
    result = [0] * k
    for i in xrange(k):
        result[i] = gf_poly_eval(msg, gf_exp[n + i])
    return result
def calc_lambda(S):
    l = [1]
    L = 0
    T = [1]
    for k in xrange(len(S)):
        T += [0] # T(x) = T(x) * x
        delta = S[k]
        for i in xrange(1, len(l)):
            delta ^= gf_mul(l[len(l) - 1 - i], S[k - i])
        if delta != 0:
            if L <= k:
                L = k
                new_T = gf_poly_mul_const(l, gf_inverse(delta))
            else:
                new_T = T
            l = gf_poly_add(l, gf_poly_mul_const(T, delta))
            T = new_T
    L = 0
    while L < len(l) and l[L] == 0:
        L += 1
    return l[L:]
def calc_locs(l, n=0):
    locs = []
    sigma = [0] * (len(l) - 1)
    for k in xrange(len(sigma)):
        sigma[k] = gf_mul(l[k], gf_exp[len(sigma) - k])

    for i in xrange(255):
        s = 1
        for k in xrange(len(sigma)):
            s ^= sigma[k]
            sigma[k] = gf_mul(sigma[k], gf_exp[len(sigma) - k])
        if s == 0:
            locs += [i]
    return locs
def calc_sigma(locs):
    result = None
    for l in locs:
        tmp = [gf_exp[l]] + [1]
        if result is None:
            result = tmp
        else:
            result = gf_poly_mul(result, tmp)
    return result
def calc_omega(S, sigma):
    return gf_poly_mod(gf_poly_mul(S, sigma), [1] + [0] * len(S)) # S*sigma mod x^2t
def calc_derivative(sigma):
    result = list(sigma)
    for x in xrange(len(result) - 1, 0, -2):
        result[x] = 0
    return result[:-1]
def ecc_encode(msg, k):
    msg = [ord(x) for x in msg]
    p = gen_poly(k)
    return ''.join([chr(x) for x in msg + gf_poly_mod(msg + [0] * k, p)])
def ecc_decode(msg, k):
    msg = [ord(x) for x in msg]
    S = calc_syn(msg, k)
    sigma = calc_lambda(S)
    locs = calc_locs(sigma)
    omega = calc_omega(S[::-1], sigma)
    sigma_prime = calc_derivative(sigma)
    for x in locs:
        x_inv = gf_inverse(gf_exp[(255 - 1 - x) % 255])
        mag = gf_div(gf_poly_eval(omega, x_inv), gf_mul(x_inv, gf_poly_eval(sigma_prime, x_inv)))
        msg[x] ^= mag
    s = ''.join([chr(x) for x in msg])
    return s[:-k], s[-k:]

class Packet(object):
    def __init__(self, hdr, data):
        self.hdr = hdr
        self.data = data

    def encode_data(self):
        # split the data into 255-byte blocks iff FEC is enabled
        n_parity = (self.hdr >> 4) * 4
        n_blocksize = 255 - n_parity
        if n_parity == 0:
            return self.data

        blocks = []
        for x in xrange(0, len(self.data), n_blocksize):
            block_data = self.data[x:x+n_blocksize]
            orig_size = len(block_data)
            block_data = block_data.ljust(n_blocksize, '\x00')
            encoded = ecc_encode(block_data[::-1], n_parity)[::-1]

            # corrupt some symbols
            encoded = [ord(x) for x in encoded]
            for y in xrange(max(0, n_parity / 2 - 2)):
                encoded[random.randint(1,254)] = random.randint(0,255)
            encoded = ''.join([chr(x) for x in encoded])

            # truncate to n_parity + orig_size
            blocks.append(encoded[:n_parity + orig_size])

        return ''.join(blocks)

    def frame(self, data):
        return data.replace('\x7e', '\x7e\x3e').replace('\x7f', '\x7e\x3f') + '\x7f'

    def to_string(self):
        return self.frame(struct.pack('<BB', self.hdr, ~self.hdr & 0xFF) + self.encode_data())

class Metadata(object):
    major = 5
    minor = 12

    def __init__(self):
        self.frames = []
        self.title = None
        self.album = None
        self.artist = None

    def encode_size(self, x):
        result = chr(x % 128)
        x /= 128
        result += chr(x % 128)
        x /= 128
        result += chr(x % 128)
        x /= 128
        result += chr(x % 128)
        x /= 128
        return result[::-1]

    def _add_frame(self, ident, contents):
        self.frames.append(ident + self.encode_size(len(contents)) + contents)

    def set_title(self, title):
        self.title = title
        self._add_frame('TITL', title)

    def set_album(self, album):
        self.album = album
        self._add_frame('ALBM', album)

    def set_artist(self, artist):
        self.artist = artist
        self._add_frame('ARTS', artist)

    def dump(self):
        res = ''
        if self.title:
            res += 'Title: ' + self.title + '\n'
        if self.album:
            res += 'Album: ' + self.album + '\n'
        if self.artist:
            res += 'Artist: ' + self.artist + '\n'
        return res

    def to_string(self):
        frame_data = ''.join(self.frames)
        hdr = 'HDR' + struct.pack('<BB', self.major, self.minor) + self.encode_size(len(frame_data))
        return hdr + frame_data

class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        pass

    def new_packet(self):
        self.state['metadata'] = Metadata()

    def add_frames(self):
        pass

    def add_title(self):
        self.state['metadata'].set_title(random_string())

    def add_album(self):
        self.state['metadata'].set_album(random_string())

    def add_artist(self):
        self.state['metadata'].set_artist(random_string())

    def send_packet(self):
        pkt = Packet(random.randint(0, 7) << 4, self.state['metadata'].to_string())
        #pkt = Packet(0, self.state['metadata'].to_string())
        self.write(pkt.to_string())
        for line in self.state['metadata'].dump().split('\n'):
            if not line: continue
            self.read(delim='\n', expect=line+'\n')

    def do_attestation(self):
        t = random.randint(1, 7)
        pkt = Packet(t, 'HASH')
        self.write(pkt.to_string())
        self.read(length=4, expect=struct.pack('<I', hash_string(self.magic_page, t)))

    def quit(self):
        pass

if __name__ == '__main__':
    m = Metadata()
    p = Packet(0x20, m.to_string())
    print repr(p.to_string())
