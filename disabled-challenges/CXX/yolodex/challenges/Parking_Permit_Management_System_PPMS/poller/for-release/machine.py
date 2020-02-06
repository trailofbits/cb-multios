#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
from collections import OrderedDict

CMD_AUTH = 0
CMD_NEW_PERMIT = 1
CMD_NEW_PERMIT_RING = 2
CMD_REFACTOR_RING = 3
CMD_TEST_PERMIT = 4
CMD_TEST_PERMIT_RING = 5
CMD_INVALID = 6

MAX_SPOT_NUMBER = 200

def random_string_n(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(size)])

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

def random_digits(size=20):
  return ''.join([random.choice(string.digits) for x in xrange(random.randint(1,size))])

class APPMS(Actions):
  def start(self):
    self.state['g_mkey'] = 'I_AM_YOUR_FATHER'
    self.state['g_session_key'] = None
    self.state['g_auth'] = 0

  def commands(self):
    pass

  def get_error(self):
    self.read(length=1, expect='\x10')

  def license_number(self):
    s = random_string(8)
    n = random_digits(4)
    r = s + n + random_string_n()
    return (s+n)[:9]

  def permit_token(self):
    token = random_string_n(4) + chr(0x55) + random_string_n(2)
    cs = 0;
    for c in token:
      cs += ord(c)
    cs %= 0xAB
    token = token + chr(cs)
    return token

  def cmd_auth(self):
    cmd = struct.pack('<b16s', CMD_AUTH, self.state['g_mkey'])
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd)
    skey = Variable('skey')
    skey.set_re('(.*)')
    self.read(length=1, expect='\x00')
    self.read(length=4, expect=struct.pack('<I', 16))
    self.read(length=16, assign=skey)
    self.state['g_session_key'] = skey
    self.state['g_auth'] = 3

  def cmd_new_permit(self):
    if self.state['g_session_key'] == None:
      return
    lic = self.license_number()
    n_e = random.randint(0, 1000)
    spot = random.randint(1, MAX_SPOT_NUMBER)
    cmd = struct.pack('<b16s10sII', CMD_NEW_PERMIT, '_SESSION_KEY_', lic, n_e, spot)
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd[:5], self.state['g_session_key'], cmd[21:])

    if self.state['g_auth'] > 0:
      self.read(length=(1 + 4), expect='\x00' + struct.pack('<I', 26))
      self.read(length=(8 + 10 + 2 * 4))
      self.state['g_auth'] -= 1
    else:
      self.get_error()

  def cmd_new_permit_ring(self):
    if self.state['g_session_key'] == None:
      return
    lics = []
    n_es = []
    spots = []
    tokens = []
    valid = True
    n = random.randint(0, 5)

    for i in xrange(n):
      while True:
        lic = self.license_number()
        if lic not in lics:
          lics.append(lic)
          break
      while True:
        spot = random.randint(1, MAX_SPOT_NUMBER)
        if spot not in spots:
          spots.append(spot)
          break
      if random.randint(1,100) <= 20:
        n_e = 0
        valid = False
      else:
        n_e = random.randint(1, 1000)
      n_es.append(n_e)
      token = self.permit_token()
      tokens.append(token)

    cmd = struct.pack('<b16sI', CMD_NEW_PERMIT_RING, '_SESSION_KEY_', n)
    for i in xrange(n):
      cmd += struct.pack('<8s10sII', tokens[i], lics[i], n_es[i], spots[i])
    ns = (5 - n) * 26
    if ns > 0:
      cmd += '\x00' * ns
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd[:5], self.state['g_session_key'], cmd[21:])

    if self.state['g_auth'] > 0 and valid:
      self.read(length=(1 + 4), expect='\x00' + struct.pack('<I', 4 + 5 * 26))
      self.read(length=4, expect=struct.pack('<I', n))
      for i in xrange(n):
        self.read(length=(8 + 10 + 2 * 4))
      n = (5 - n) * 26
      if n > 0:
        self.read(length=n, expect='\x00'*n)
      self.state['g_auth'] -= 1
    else:
      self.get_error()

  def cmd_refactor_ring(self):
    if self.state['g_session_key'] == None:
      return
    lics = []
    n_es = []
    spots = []
    tokens = []
    n = random.randint(0, 5)

    for i in xrange(n):
      while True:
        lic = self.license_number()
        if lic not in lics:
          lics.append(lic)
          break
      while True:
        spot = random.randint(1, MAX_SPOT_NUMBER)
        if spot not in spots:
          spots.append(spot)
          break
      if random.randint(1, 100) <= 20:
        n_e = 0
      else:
        n_e = random.randint(1, 1000)
      n_es.append(n_e)
      token = self.permit_token()
      tokens.append(token)

    cmd = struct.pack('<b16sI', CMD_REFACTOR_RING, '_SESSION_KEY_', n)
    for i in xrange(n):
      cmd += struct.pack('<8s10sII', tokens[i], lics[i], n_es[i], spots[i])
    ns = (5 - n) * 26
    if ns > 0:
      cmd += '\x00' * ns
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd[:5], self.state['g_session_key'], cmd[21:])

    il = []
    for i in xrange(n):
      if n_es[i] > 0:
        il.append(i)

    if self.state['g_auth'] > 0:
      self.read(length=(1 + 4), expect='\x00' + struct.pack('<I', 4 + 5 * 26))
      self.read(length=4, expect=struct.pack('<I', len(il)))
      for i in il:
        self.read(length=(8 + 10 + 2 * 4))
      n = (5 - len(il)) * 26
      if n > 0:
        self.read(length=n, expect='\x00'*n)
      self.state['g_auth'] -= 1
    else:
      self.get_error()

  def cmd_test_permit(self):
    if self.state['g_session_key'] == None:
      return
    valid = True
    token = self.permit_token()
    lic = self.license_number()
    n_e = random.randint(0, 1000)
    if n_e == 0:
      valid = False
    spot = random.randint(1, MAX_SPOT_NUMBER)
    cmd = struct.pack('<b16s8s10sIII10s', CMD_TEST_PERMIT, '_SESSION_KEY_', token, lic, n_e, spot, spot, lic)
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd[:5], self.state['g_session_key'], cmd[21:])

    if self.state['g_auth'] > 0 and valid:
      self.read(length=1, expect='\x00')
      self.state['g_auth'] -= 1
    else:
      self.get_error()

  def cmd_test_permit_ring(self):
    if self.state['g_session_key'] == None:
      return
    valid = True
    lics = []
    n_es = []
    spots = []
    tokens = []
    n = random.randint(0, 5)

    for i in xrange(n):
      while True:
        lic = self.license_number()
        if lic not in lics:
          lics.append(lic)
          break
      while True:
        spot = random.randint(1, MAX_SPOT_NUMBER)
        if spot not in spots:
          spots.append(spot)
          break
      if random.randint(1,100) <= 20:
        n_e = 0
        valid = False
      else:
        n_e = random.randint(1, 1000)
      n_es.append(n_e)
      token = self.permit_token()
      tokens.append(token)

    cmd = struct.pack('<b16sI', CMD_TEST_PERMIT_RING, '_SESSION_KEY_', n)
    for i in xrange(n):
      cmd += struct.pack('<8s10sII', tokens[i], lics[i], n_es[i], spots[i])
    ns = (5 - n) * 26
    if ns > 0:
      cmd += '\x00' * ns
    for i in xrange(n):
      cmd += struct.pack('<I', spots[i])
    ns = (5 - n) * 4
    if ns > 0:
      cmd += '\x00' * ns
    for i in xrange(n):
      cmd += struct.pack('10s', lics[i])
    ns = (5 - n) * 10
    if ns > 0:
      cmd += '\x00' * ns
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd[:5], self.state['g_session_key'], cmd[21:])

    if self.state['g_auth'] > 0 and valid:
      self.read(length=1, expect='\x00')
      self.state['g_auth'] -= 1
    else:
      self.get_error()

  def quit(self):
    cmd = struct.pack('<b', CMD_INVALID)
    cmd = struct.pack('<I', len(cmd)) + cmd
    self.write(cmd)
