from generator.actions import Actions
from random import randint
from struct import pack
from subprocess import Popen, PIPE

MAX_WIDTH = 256
MAX_HEIGHT = 256

def random_pixel(bpp):
    if bpp == 32:
        return chr(randint(0,255)) + chr(randint(0,255)) + chr(randint(0,255)) + '\x00'
    else:
        return chr(randint(0,255)) + chr(randint(0,255)) + chr(randint(0,255))

class Bitmap(Actions):
    def start(self):
        quality = randint(1, 50)
        self.state['width'] = randint(1, MAX_WIDTH / 8) * 8
        self.state['height'] = randint(1, MAX_HEIGHT / 8) * 8
        self.state['bpp'] = (self.chance(0.5) and 32) or 24

        size = 14 + 40 + self.state['width'] * self.state['height'] * self.state['bpp'] / 8

        bmp_file = pack('<HIHHI',
            0x4743, # magic
            size,
            quality,
            randint(0, 0xFFFF), # reserved2
            14 + 40)
        bmp_info = pack('<IiiHHIIiiII',
            40, #info size
            self.state['width'],
            self.state['height'],
            1, #planes
            self.state['bpp'],
            0, #comp
            self.state['width'] * self.state['height'] * self.state['bpp'] / 8, #data size
            randint(-0x70000000, 0x70000000), #hres
            randint(-0x70000000, 0x70000000), #vres
            randint(0, 0xF0000000), #colors
            randint(0, 0xF0000000)) #important colors
        
        self.write(bmp_file)
        self.write(bmp_info)

        data = ''
        last_color = random_pixel(self.state['bpp'])
        for x in xrange(self.state['width'] * self.state['height']):
            if self.chance(0.7):
                last_color = random_pixel(self.state['bpp'])
            data += last_color
        self.write(data)
        self.state['bitmap'] = bmp_file + bmp_info + data

    def end(self):
        p = Popen(['bin/KPRCA_00003'], stdin=PIPE, stdout=PIPE)
        p.stdin.write(self.state['bitmap'])
        (stdout, stderr) = p.communicate()
        self.read(length=len(stdout), expect=stdout)
