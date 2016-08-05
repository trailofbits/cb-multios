#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack, unpack, unpack_from
from ctypes import *
from math import floor
import numpy as np

NEW_FILE        = '\x01'
CHECK_FILE      = '\x02'
SKEW_IMAGE      = '\x03'
ROTATE_IMAGE    = '\x04'
BRIGHTNESS      = '\x05'
OPACITY         = '\x06'
COMPRESS        = '\x07'
DECOMPRESS      = '\x08'
SHOW_PIXEL      = '\x09'
SCALE_IMAGE     = '\x0a'
EXIT            = '\x0b'

COORDS          = [ ('x',0) , ('y',1) , ('z',2) ]

MAX_PIXELS      = 4096/10

M_PI            = 3.14159265358979323846

class Poller(Actions):

    red_blue   = [ 0x00, 0x20, 0x40, 0x60, 0xA0, 0xC0, 0xE0, 0xFF ]
    green      = [ 0x00, 0x60, 0xB0, 0xFF ]

    def start(self):
        self.delay(50)
        self.read(delim='\n', expect='3D Coordinates (3DC) Image File Format Tools\n')
        self.file_data = []
        self.compressed = ""
        self.compressed_colors = []
        self.last_shown = 0
        self.decompress_flag = 0
        self.count = 0

        # setup ctypes for prng functions
        self.dll = CDLL('build/patched/so/CROMU_00078.so')
        self.seed_prng = self.dll.seed_prng
        self.seed_prng.argtypes = [ c_uint ]
        self.seed_prng.restype = None
        self.random_in_range = self.dll.random_in_range
        self.random_in_range.argtypes = [ c_uint, c_uint ]
        self.random_in_range.restype = c_uint
        self.prng = self.dll.prng
        self.prng.argtypes = [ ]
        self.prng.restype = c_uint

        self.multiply = self.dll.multiply
        self.multiply.argtypes = [ c_double, c_double ]
        self.multiply.restype = c_int

        self.divide = self.dll.divide
        self.divide.argtypes = [ c_double, c_double ]
        self.divide.restype = c_short

        self.degToRad = self.dll.degree_to_radian
        self.degToRad.argtypes = [ c_short ]
        self.degToRad.restype = c_short

        self.cos = self.dll.cosine
        self.cos.argtypes = [ c_short ]
        self.cos.restype = c_double

        self.sin = self.dll.sine
        self.sin.argtypes = [ c_short ]
        self.sin.restype = c_double

    def readFile(self):
        self.seed_prng(c_uint(unpack('<L', self.magic_page[0:4])[0]))

        x = 0
        for _ in xrange(4096/10):
            # z, r, x, a, b, y, g
            t = {}
            t['x'] = c_short(self.prng()).value

            x += 2
            t['y'] = c_short(self.prng()).value

            x += 2
            t['z'] = c_short(self.prng()).value

            x += 2
            t['r'] = c_ubyte(self.prng()).value

            x += 1
            t['g'] = c_ubyte(self.prng()).value

            x += 1
            t['b'] = c_ubyte(self.prng()).value

            x += 1
            t['a'] = c_ubyte(self.prng()).value

            x += 1
            self.file_data.append(t)



    def top(self):
        self.count += 1
        if self.count > 5:
            self.end()
            return -1
        pass

    def checkFile(self):
        self.write(CHECK_FILE)
        self.read(delim='\n', expect='CHECK_FILE selected\n')
        for px in self.file_data:
            self.read(delim='\n', expect='XYZ:  (%d, %d, %d)\n' % (px['x'], px['y'], px['z']) )
            self.read(delim='\n', expect='RGBA: (#%02x%02x%02x%02x)\n' % (px['r'], px['g'], px['b'], px['a']) )
            self.read(delim='\n', expect='\n')

    def newFile(self):
        self.write(NEW_FILE)
        self.read(delim='\n', expect='NEW_FILE selected\n')
        self.read(delim='\n', expect='Please submit your new file data (%d bytes):\n' % (MAX_PIXELS * 10))

        self.file_data = []
        x = 0

        data_to_send = ""

        while (x < 4090):
            t = {}

            new_x = random.randint(-32767,32767)
            new_y = random.randint(-32767,32767)
            new_z = random.randint(-32767,32767)
            new_r = random.randint(0,255)
            new_g = random.randint(0,255)
            new_b = random.randint(0,255)
            new_a = random.randint(0,255)

            data_to_send += pack("<h", new_x)
            data_to_send += pack("<h", new_y)
            data_to_send += pack("<h", new_z)
            data_to_send += pack("<B", new_r)
            data_to_send += pack("<B", new_g)
            data_to_send += pack("<B", new_b)
            data_to_send += pack("<B", new_a)

            t['x'] = new_x
            t['y'] = new_y
            t['z'] = new_z
            t['r'] = new_r
            t['g'] = new_g
            t['b'] = new_b
            t['a'] = new_a

            x += 10
            self.file_data.append(t)

        self.write(data_to_send)

        self.read(delim='\n', expect='New file loaded\n')

        return


    def skewImage(self):
        self.write(SKEW_IMAGE)
        self.read(delim='\n', expect='SKEW_IMAGE selected\n')

        coord = random.choice(COORDS)
        self.write(pack("<B",coord[1]))

        skew_val = c_short(random.randint(-32767,32767))
        self.write(pack("<h",skew_val.value))   # Skew amount

        for px in self.file_data:
            tmp = c_short(px[coord[0]])
            px[coord[0]] = c_short(tmp.value + skew_val.value).value

        return


    def rotateImage(self):
        multiply = self.multiply
        sin = self.sin
        cos = self.cos
        self.write(ROTATE_IMAGE)
        self.read(delim='\n', expect='ROTATE_IMAGE selected\n')

        coord = random.choice(COORDS)
        self.write(pack("<B",coord[1]))

        degree = random.randint(-32767,32767)
        self.write(pack("<h",degree))   # Skew amount

        a = self.degToRad(degree)

        for px in self.file_data:
            if coord[0] is 'x':
                px['y'] = c_short(multiply(px['y'], cos(a)) - multiply(px['z'], sin(a))).value
                px['z'] = c_short(multiply(px['y'], sin(a)) + multiply(px['z'], cos(a))).value

            elif coord[0] is 'y':
                px['x'] = c_short(multiply(px['z'], sin(a)) + multiply(px['x'], cos(a))).value
                px['z'] = c_short(multiply(px['z'], cos(a)) - multiply(px['x'], sin(a))).value

            elif coord[0] is 'z':
                px['x'] = c_short(multiply(px['x'], cos(a)) - multiply(px['y'], sin(a))).value
                px['y'] = c_short(multiply(px['x'], sin(a)) + multiply(px['y'], cos(a))).value

            else:
                continue

        return

    def scaleImage(self):
        divide = self.divide
        multiply = self.multiply
        self.write(SCALE_IMAGE)
        self.read(delim='\n', expect='SCALE_IMAGE selected\n')
        scale_val = random.randint(1,200)

        self.write(pack("<h", scale_val))

        percent = divide(scale_val, 100)

        for px in self.file_data:
            tmp_x = multiply(px['x'], percent)
            tmp_y = multiply(px['y'], percent)
            tmp_z = multiply(px['z'], percent)

            if tmp_x > 0xffff:
                if px['x'] < 0:
                    px['x'] = -32768
                else:
                    px['x'] = 32767
            else:
                px['x'] = c_short(tmp_x).value

            if tmp_y > 0xffff:
                if px['y'] < 0:
                    px['y'] = -32768
                else:
                    px['y'] = 32767
            else:
                px['y'] = c_short(tmp_y).value

            if tmp_z > 0xffff:
                if px['z'] < 0:
                    px['z'] = -32768
                else:
                    px['z'] = 32767
            else:
                px['z'] = c_short(tmp_z).value

        return

    def brightness(self):
        self.write(BRIGHTNESS)
        bright_val = random.randint(-255,255)
        self.read(delim='\n', expect='BRIGHTNESS selected\n')
        self.write(pack("<h", bright_val))

        for px in self.file_data:
            tmp_r = px['r'] + bright_val
            tmp_g = px['g'] + bright_val
            tmp_b = px['b'] + bright_val

            if tmp_r > 0xff:
                px['r'] = 0xff
            elif tmp_r < 0:
                px['r'] = 0
            else:
                px['r'] = tmp_r

            if tmp_g > 0xff:
                px['g'] = 0xff
            elif tmp_g < 0:
                px['g'] = 0
            else:
                px['g'] = tmp_g

            if tmp_b > 0xff:
                px['b'] = 0xff
            elif tmp_b < 0:
                px['b'] = 0
            else:
                px['b'] = tmp_b

        return



    def opacity(self):
        self.write(OPACITY)
        self.read(delim='\n', expect='OPACITY selected\n')
        opacity = random.randint(0x00, 0xff)
        self.write(pack("<B", opacity))

        for px in self.file_data:
            px['a'] = opacity


    def closestMatch(self, type, val):
        #self.read(delim='\n', expect='color: %02x\n' % val)
        close_diff = 0xff
        temp_diff = 0
        max_idx = 8 if (type == 0 or type == 2) else 4
        close_idx = max_idx

        for x in xrange(max_idx):
            if (type == 0 or type == 2):
                temp_diff = abs(val - self.red_blue[x])
            else:
                temp_diff = abs(val - self.green[x])

            if (temp_diff < close_diff):
                close_diff = temp_diff
                close_idx = x

        return close_idx


    def compress(self):
        self.write(COMPRESS)
        self.read(delim='\n', expect='COMPRESS selected\n')

        for px in self.file_data:
            color = 0

            color += (self.closestMatch(0, px['r']) << 5)
            color += (self.closestMatch(1, px['g']) << 3)
            color += (self.closestMatch(2, px['b']) << 0)

            data =  pack("<h", px['x'])
            data += pack("<h", px['y'])
            data += pack("<h", px['z'])
            data += pack("<B", color)

            self.compressed += data

        self.decompress_flag = 0
        return

    def decompress(self):
        self.write(DECOMPRESS)
        self.read(delim='\n', expect='DECOMPRESS selected\n')

        if len(self.compressed) is 0:
            self.read(delim='\n', expect='No compressed data.\n')
            return

        if self.decompress_flag is 1:
            self.read(delim='\n', expect='You have already decompressed the latest data.\n')
            return

        x = 0
        idx = 0

        for t in self.file_data:
            x += 6

            new_color = unpack("<B", self.compressed[x])[0]
            new_red = self.red_blue[(int('11100000',2) & new_color) >> 5] #& 0xff
            new_green = self.green[(int('00011000', 2) & new_color) >> 3] #& 0xff
            new_blue = self.red_blue[(int('00000111', 2) & new_color) >> 0] #& 0xff
            x += 1

            t['r'] = new_red
            t['g'] = new_green
            t['b'] = new_blue
            t['a'] = 0xff

        self.decompress_flag = 1
        return

    def showPixel(self):
        self.write(SHOW_PIXEL)
        self.read(delim='\n', expect='SHOW_PIXEL selected\n')
        self.read(delim='\n', expect='Select the pixel to view:\n')
        px_idx = random.randint(0,MAX_PIXELS-1)
        px_idx = 0
        self.write(pack("<h", px_idx))

        px = self.file_data[px_idx]
        self.last_shown = px_idx

        self.read(delim='\n', expect='XYZ:  (%d, %d, %d)\n' % (px['x'], px['y'], px['z']) )
        self.read(delim='\n', expect='RGBA: (#%02x%02x%02x%02x)\n' % (px['r'], px['g'], px['b'], px['a']) )
        self.read(delim='\n', expect='\n')

        return

    def end(self):
        # tell it to exit normally
        self.write(EXIT)
