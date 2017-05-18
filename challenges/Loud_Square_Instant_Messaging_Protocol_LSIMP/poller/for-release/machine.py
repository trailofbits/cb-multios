#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
from collections import OrderedDict

CURRENT_VER = 103
MAX_KEY_LEN = 128
MAX_TEXT_LEN = 1024
MAX_DATA_LEN = 512

OP_QUEUE = 0
OP_PROCESS = 1
OP_QUIT = 2

LMT_HELO = 0x4f4c4548
LMT_KEYX = 0x5859454b
LMT_DATA = 0x41544144
LMT_TEXT = 0x54584554

def random_string_n(size=20):
  return ''.join([random.choice(string.printable) for x in xrange(size)])

def random_string(size=20):
  return ''.join([random.choice(string.printable) for x in xrange(random.randint(1,size))])

def random_digits(size=20):
  return ''.join([random.choice(string.digits) for x in xrange(random.randint(1,size))])

def random_bytes(size=20):
  return ''.join([chr(random.randint(0,255)) for x in xrange(size)])

def xor_s(s, key, inv=False):
  i = 0
  x = []
  while i < len(s):
    if inv:
      x.append(chr((ord(s[i]) ^ ~ord(key[i % len(key)])) & 0xFF))
    else:
      x.append(chr(ord(s[i]) ^ ord(key[i % len(key)])))
    i += 1
  return ''.join(x)

def compute_guard(data):
  guard = 0
  for c in data:
    guard = ((guard << 10) ^ (guard + ord(c))) & 0xFFFFFFFF
  return guard

def make_op(op, payload=''):
  s = struct.pack('<I', op) + payload
  s = struct.pack('<I', len(s)) + s
  return s

class AWPLSIMP(Actions):

  def start(self):
    self.state['queue'] = list()
    self.state['dms'] = OrderedDict()
    self.state['helo'] = None
    self.state['keyx'] = None
    self.state['seq'] = 1

  def gen_msg(self, typ):
    if typ == LMT_HELO:
      if self.state['helo'] is None:
        self.state['helo'] = {}
        self.state['helo']['ttl'] = random.randint(1, 200)
        self.state['helo']['secure'] = random.choice([True, False])
        p = struct.pack('<IbbI', LMT_HELO, CURRENT_VER, self.state['helo']['secure'], self.state['helo']['ttl'])
        p += struct.pack('<I', compute_guard(p))
      else:
        p = struct.pack('<IbbI', LMT_HELO, CURRENT_VER, random_bytes(1), random_bytes(4))
        p += struct.pack('<I', compute_guard(p))
      return p
    elif typ == LMT_KEYX:
      if self.state['keyx'] is None:
        self.state['keyx'] = {}
        self.state['keyx']['option'] = random.choice([0x00, 0x30]) | random.choice([0x00, 0x07])
        self.state['keyx']['key'] = random_bytes(random.randint(1, MAX_KEY_LEN))
        p = struct.pack('<IbI', LMT_KEYX, self.state['keyx']['option'], len(self.state['keyx']['key']))
        p += self.state['keyx']['key']
        p += struct.pack('<I', compute_guard(p))
      else:
        key = random_bytes(random.randint(1, MAX_KEY_LEN))
        p = struct.pack('<IbI', LMT_KEYX, random_bytes(1), len(key))
        p += key
        p += struct.pack('<I', compute_guard(p))
      return p
    elif typ == LMT_DATA:
      dummy = random_bytes(4)
      if self.state['keyx']:
        inv = (self.state['keyx']['option'] & 0xF0 == 0x30)
        s = random_string(MAX_DATA_LEN)
        d = xor_s(s, self.state['keyx']['key'], inv=inv)
        self.state['dms'][self.state['seq']] = s
        if self.state['keyx']['option'] & 0x0F == 0x07:
          d = dummy + d
        else:
          d = d + dummy
        p = struct.pack('<III', LMT_DATA, self.state['seq'], len(d))
        p += d
        p += struct.pack('<I', compute_guard(p))
        self.state['seq'] += 1
      else:
        d = random_string(MAX_DATA_LEN)
        p = struct.pack('<III', LMT_DATA, random.randint(0, 200), len(d))
        p += d
        p += struct.pack('<I', compute_guard(p))
      return p
    elif typ == LMT_TEXT:
      d = random_string(MAX_TEXT_LEN)
      p = struct.pack('<II', LMT_TEXT, len(d))
      p += d
      p += struct.pack('<I', compute_guard(p))
      return p

    return None

  def decode_msg(self, es):
    if self.state['keyx']['option'] & 0x0F == 0x07:
      es = es[4:]
    else:
      es = es[:-4]
    inv = (self.state['keyx']['option'] & 0xF0 == 0x30)
    ds = xor_s(es, self.state['keyx']['key'], inv=inv)
    return ds

  def ops(self):
    pass

  def queue_msg(self):
    if self.state['helo'] is None:
      self.state['queue'].append(self.gen_msg(LMT_HELO))
    else:
      if self.state['helo']['secure']:
        if self.state['keyx'] is None:
          self.state['queue'].append(self.gen_msg(LMT_KEYX))
        else:
          self.state['queue'].append(self.gen_msg(LMT_DATA))
      else:
        self.state['queue'].append(self.gen_msg(LMT_TEXT))

  def process_msg(self):
    for m in self.state['queue']:
      self.write(make_op(OP_QUEUE, m))
      self.read(length=len('QUEUED\n'), expect='QUEUED\n')

    self.write(make_op(OP_PROCESS))

    helo, keyx = False, False
    ttl = 0
    seqs = list()
    if len(self.state['queue']) > 0:
      for m in self.state['queue']:
        if helo and ttl > self.state['helo']['ttl']:
          break
        typ = m[:4]
        if typ == 'HELO':
          s = 'HELO [VERSION %d] [SECURE %s] [TTL %d]\n' % \
              (CURRENT_VER, 'on' if self.state['helo']['secure'] else 'off', self.state['helo']['ttl'])
          self.read(length=len(s), expect=s)
          helo = True
          # TODO: Maybe implement wrong version + handler code
        elif typ == 'KEYX':
          if not helo:
            break
          if not keyx:
            if not self.state['helo']['secure']:
              self.read(length=len('KEYX IN NON-SECURE\n'), expect='KEYX IN NON-SECURE\n')
              break
            if len(self.state['keyx']['key']) == 0:
              self.read(length=len('NO KEY\n'), expect='NO KEY\n')    # Impossible case for the poller
            s = 'KEYX [OPTION %s | %s] [LEN %d]\n' % \
                ('prepend' if self.state['keyx']['option'] & 0x0F == 0x07 else 'append', \
                 'inverted' if self.state['keyx']['option'] & 0xF0 == 0x30 else 'as-is', \
                 len(self.state['keyx']['key']))
            self.read(length=len(s), expect=s)
            keyx = True
        elif typ == 'DATA':
          if not helo:
            break
          if not self.state['helo']['secure']:
            self.read(length=len('DATA IN NON-SECURE\n'), expect='DATA IN NON-SECURE\n')
            break
          if not keyx:
            self.read(length=len('DATA BEFORE KEYX\n'), expect='DATA BEFORE KEYX\n')
            break
          seq, l = struct.unpack('<II', m[4:12]) 
          seqs.append(seq)
          s = 'DATA [SEQ %d] [LEN %d]\n' % (seq, l)
          self.read(length=len(s), expect=s)
        elif typ == 'TEXT':
          if not helo:
            break
          if self.state['helo']['secure']:
            self.read(length=len('TEXT IN SECURE\n'), expect='TEXT IN SECURE\n')
            break
          l = struct.unpack('<I', m[4:8])[0]
          if l == 0:
            self.read(length=len('NO TEXT MSG\n'), expect='NO TEXT MSG\n')    # Impossible case for the poller
          msg = m[8:8+l]
          s = 'TEXT [LEN %d] [MSG %s]\n' % (l, msg)
          self.read(length=len(s), expect=s)
        else:
          pass
        ttl += 1

      self.state['dms'] = filter(lambda x: x[0] in seqs, self.state['dms'].items())
      if self.state['helo']['secure'] and len(self.state['dms']) > 0:
        #dc = filter(lambda x: x[:4] == 'DATA', self.state['queue'])
        #dcd = OrderedDict([(struct.unpack('<I', x[4:8])[0], x[12:12+struct.unpack('<I', x[8:12])[0]]) for x in dc])
        #out = ''.join([self.decode_msg(x[1]) for x in dcd.items()])
        exp_out = ''.join(map(lambda x: x[1], self.state['dms']))
        self.read(length=len('SECURE MESSAGE:\n'), expect='SECURE MESSAGE:\n')
        self.read(length=len(exp_out + '\n'), expect=exp_out + '\n')

    if not helo:
      self.read(length=len('HELO MISSING\n'), expect='HELO MISSING\n')

    self.read(length=len('PROCESS DONE\n'), expect='PROCESS DONE\n')
    self.read(length=len('QUEUE CLEARED\n'), expect='QUEUE CLEARED\n')
    self.state['queue'] = list()
    self.state['dms'] = OrderedDict()
    self.state['helo'] = None
    self.state['keyx'] = None
    self.state['seq'] = 1

  def quit(self):
    self.write(make_op(OP_QUIT))
    self.read(length=len('QUIT\n'), expect='QUIT\n')

