#!/usr/bin/env python

from cStringIO import StringIO
from generator.actions import Actions
import random
import string
import struct

p = lambda f,x: struct.pack(f,x)

STEG_TAG = 0xD86B74D1
PPM_TAG = 0x03259036
MODE_TAG = 0xBB85A71C
TEXT_TAG = 0xBFEFDDE9
END_TAG = 0xAB660AF0

SECRET_TAG = 0xB58333C6
SECRET_END_TAG = 0x0507A018

MODE_EM = 0x1337
MODE_EX = 0x7331

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class APPMSteg(Actions):

  def start(self):
    if random.randint(1,100) <= 50:
      self.state['mode'] = MODE_EM
    else:
      self.state['mode'] = MODE_EX

  def new_ppm(self):
    w = random.randint(1, 400)
    h = random.randint(1, 400)

    pixels = StringIO()
    for i in xrange(w * h * 3):
      pixels.write(chr(random.randint(0, 255)))

    self.state['w'] = w
    self.state['h'] = h
    self.state['pixels'] = pixels
 
  def get_ppm(self):
    ppm = 'PK\n%d %d\n255\n' % (self.state['h'], self.state['w'])
    ppm += self.state['pixels'].getvalue()
    return ppm

  def embed_text(self, text):
    message = p('I', SECRET_TAG)
    message += p('H', len(text))
    message += text
    message += p('I', SECRET_END_TAG)

    if len(message) > self.state['w'] * self.state['h'] * 3 / 8:
      return False

    self.state['pixels'].seek(0)
    for c in message:
      for i in xrange(0, 8):
        pixel = self.state['pixels'].read(1)
        bit = (ord(c) >> (7 - i)) & 1
        if bit:
          pixel = chr(ord(pixel) | 1)
        else:
          pixel = chr(ord(pixel) & ~1)
        self.state['pixels'].seek(-1, 1)
        self.state['pixels'].write(pixel)
    return True

  def generate_ppm(self):
    self.new_ppm()

    if self.state['mode'] == MODE_EX:
      # Generate a temporary random input to be extracted
      text_data = 'Temp random input ___' + random_string(10) + '___'
      if self.embed_text(text_data):
        self.state['text'] = text_data
      else:
        self.state['text'] = None

    if self.state['mode'] == MODE_EM:
      text_data = 'Test string ___' + random_string(10) + '___'
      self.state['text'] = text_data
    else:
      text_data = ''
    text_size = len(text_data)

    ppm_data = self.get_ppm()
    s = ''
    s += p('I', STEG_TAG)
    s += p('I', 0)
    s += p('I', PPM_TAG)
    s += p('I', len(ppm_data))
    s += ppm_data
    s += p('I', MODE_TAG)
    if self.state['mode'] == MODE_EM:
      s += p('H', MODE_EM)
    else:
      s += p('H', MODE_EX)
    s += p('I', TEXT_TAG)
    s += p('H', text_size)
    s += text_data
    s += p('I', END_TAG)

    s = p('I', STEG_TAG) + p('I', len(s)) + s[8:]
    self.state['string'] = s

  def generate_exp(self):
    if self.state['mode'] == MODE_EM:
      if self.embed_text(self.state['text']):
        return self.get_ppm()
      else:
        return '[ERROR] Failed to embed your message.\n'
    else:
      if self.state['text'] == None:
        return '[ERROR] Failed to extract the message.\n'
      else:
        return 'Secret Text: %s\n' % self.state['text']

  def doit(self):
    # DO STUFF
    self.generate_ppm()
    self.write(self.state['string'])

    exp = self.generate_exp()
    self.read(length=len(exp), expect=exp)
