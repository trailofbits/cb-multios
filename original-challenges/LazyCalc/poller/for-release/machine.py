#!/usr/bin/env python

from generator.actions import Actions
import struct
import random
import string
import numpy as np

g_secret = None

CMD_ADD = 0x903C5CE4
CMD_SUB = 0xC66AC07F
CMD_MUL = 0x3FD26000
CMD_DIV = 0xC5554A87
CMD_MOD = 0x5EAC467D
CMD_EXP = 0xAE22983D
CMD_IMP = 0xB635A8AD
CMD_CMP = 0x285C3CB4
CMD_QUT = 0x7DA7BAE3

def g_prng():
  global g_state
  g_state = g_state * 1103515247 + 13579
  return (g_state / 65536) % 32768

def init_g_state(secret):
  global g_state
  g_state = secret * 1103515247 + 13579

def pack(x):
  return struct.pack('<I', x)

def spack(x):
  return struct.pack('<i', x)

def random_bytes(n=20):
  return ''.join(chr(random.randint(0,255)) for _ in range(n))

def random_string(n=20):
  s = string.ascii_letters + string.digits
  return ''.join(random.choice(s) for _ in range(n))

class Op(object):

  OP_ADD = 0x45FD1D19
  OP_SUB = 0x9B6A4495
  OP_MUL = 0xA2F78B10
  OP_DIV = 0xE8BBACD2
  OP_MOD = 0x2BAE191D
  OP_IMP = 0xA9A367A0
  OP_EXP = 0xEC810F07
  OP_CMP = 0x76FC2ED2

  def __init__(self, typ, arg1, arg2):
    self.typ = typ
    self.arg1 = arg1
    self.arg2 = arg2
    self.result = 0

  def compute(self):
    if self.typ == self.OP_ADD:
      self.result = self.arg1 + self.arg2
    elif self.typ == self.OP_SUB:
      self.result = self.arg1 - self.arg2
    elif self.typ == self.OP_MUL:
      self.result = self.arg1 * self.arg2
    elif self.typ == self.OP_DIV:
      if self.arg2 == 0:
        return
      self.result = self.arg1 / self.arg2
    elif self.typ == self.OP_MOD:
      if self.arg2 == 0:
        return
      self.result = self.arg1 % self.arg2

class Calc(Actions):

  def start(self):
    #self.delay(100)
    global g_secret
    g_secret = self.magic_page

    sm = 0
    for i in xrange(4096/4):
      sm += struct.unpack('<I', self.magic_page[i*4:i*4 +4])[0]
    sm %= 128
    if ord(self.magic_page[0]) & 1:
      sm = -sm
    self.rslr = sm
    s = struct.pack('<h', self.rslr)
    self.read(length=len(s), expect=s)
    if random.randint(1, 1000) <= 5:
      n = random.randint(0, 2)
    else:
      n = random.randint(3, 30)
    self.write(pack(n))
    self.n = n
    if n < 3:
      s = '\xFF\xFF\xFF\xF0'
      self.read(length=len(s), expect=s)
    self.calcs = []

  def do_calc(self, cmd):
    if cmd == CMD_ADD:
      typ = Op.OP_ADD
    elif cmd == CMD_SUB:
      typ = Op.OP_SUB
    elif cmd == CMD_MUL:
      typ = Op.OP_MUL
    elif cmd == CMD_DIV:
      typ = Op.OP_DIV
    elif cmd == CMD_MOD:
      typ = Op.OP_MOD

    while True:
      arg1 = np.int32(random.randint(-2147483648, 2147483647))
      if arg1 != 0:
        break
    while True:
      arg2 = np.int32(random.randint(-2147483648, 2147483647))
      if arg2 != 0:
        break
    self.write(spack(arg1) + spack(arg2))
    self.calcs.append(Op(typ, arg1, arg2))

  @staticmethod
  def gen_random_op():
    typ = random.choice([Op.OP_ADD, Op.OP_SUB, Op.OP_MUL])
    while True:
      arg1 = np.int32(random.randint(-2147483648, 2147483647))
      if arg1 != 0:
        break
    while True:
      arg2 = np.int32(random.randint(-2147483648, 2147483647))
      if arg2 != 0:
        break
    op = Op(typ, arg1, arg2)
    return op

  def do_imp(self):
    self.n = random.randint(3, 30)
    self.write(pack(self.n))
    self.calcs = []
    s = ''
    for i in xrange(self.n):
      op = self.gen_random_op()
      self.calcs.append(op)
      s += pack(op.typ) + spack(op.arg1) + spack(op.arg2) + spack(0)
    self.write(s)

  @staticmethod
  def print_cmp(op):
    o_s = '?'
    if op.typ == Op.OP_ADD:
      o_s = '+'
    elif op.typ == Op.OP_SUB:
      o_s = '-'
    elif op.typ == Op.OP_MUL:
      o_s = '*'
    elif op.typ == Op.OP_DIV:
      o_s = '/'
    elif op.typ == Op.OP_MOD:
      o_s = '%'
    s = 'A: %d, B: %d\n' % (op.arg1, op.arg2)
    s += 'Result of A %s B: %d\n' % (o_s, op.result)
    return s

  def do_cmp(self):
    s = '\n'
    for i, op in enumerate(self.calcs):
      op.compute()
      op.result += self.rslr
      s += 'Slot #%02d\n' % (i + 1)
      s += self.print_cmp(op)
    self.read(length=len(s), expect=s)

  def do_commands(self):
    if self.n < 3:
      return

    cmds = []
    for i in xrange(random.randint(15, 40)):
      cmds.append(random.choice([CMD_ADD, CMD_SUB, CMD_MUL, CMD_EXP, CMD_IMP, CMD_CMP]))

    for cmd in cmds:
      self.write(pack(cmd))
      if cmd in [CMD_ADD, CMD_SUB, CMD_MUL]:
        if self.n == len(self.calcs):
          s = '\xFF\xFF\xFF\xAB'
          self.read(length=len(s), expect=s)
        else:
          self.do_calc(cmd)
      elif cmd == CMD_EXP:
        results = []
        for c in self.calcs:
          c.compute()
          c.result += self.rslr
          results.append(spack(c.result))
        s = ''.join(results)
        if s != '':
          self.read(length=len(s), expect=s)
      elif cmd == CMD_IMP:
        self.do_imp()
      elif cmd == CMD_CMP:
        self.do_cmp()

    if random.randint(1, 100) <= 2:
      cmd = random.randint(0, 0xFFFFFFFF)
      while cmd in [CMD_ADD, CMD_SUB, CMD_MUL, CMD_EXP, CMD_IMP, CMD_CMP, CMD_QUT]:
        cmd = random.randint(0, 0xFFFFFFFF)
      self.write(pack(cmd))
      s = '\xFF\xFF\xFF\xFF'
      self.read(length=len(s), expect=s)

    cmd = CMD_QUT
    self.write(pack(cmd))
    s = '\x00\x00\x00\x00'
    self.read(length=len(s), expect=s)

