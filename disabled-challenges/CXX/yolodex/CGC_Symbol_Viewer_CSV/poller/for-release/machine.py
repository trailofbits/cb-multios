#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
from collections import OrderedDict

def random_string_n(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(size)])

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

def random_digits(size=20):
  return ''.join([random.choice(string.digits) for x in xrange(random.randint(1,size))])

def random_bytes(size=20):
  return ''.join([chr(random.randint(0,255)) for x in xrange(size)])


class ACSV(Actions):

  def start(self):
    self.state['cgcf'] = None
    self.state['e_phoff'] = 0
    self.state['e_shoff'] = 0
    self.state['e_shnum'] = 0
    self.state['e_shtrndx'] = 0
    self.state['base_off'] = 0x700
    self.state['num_symbols'] = random.randint(0, 200)
    self.state['symbols'] = list()
    self.state['sections'] = list()
    self.state['has_symtab'] = False
    self.state['cur_off'] = 0

  def _gen_symbol(self):
    symbol = dict()
    symbol['name'] = random_string()
    bind = random.choice([0, 1, 2, 3])
    typ = random.choice([0, 1, 2, 3, 4, 5, 6, 7])
    symbol['info'] = (bind << 4 | typ)
    if typ == 1 or typ == 2:
      symbol['size'] = random.randint(0, 0x7FF)
    else:
      symbol['size'] = 0
    symbol['other'] = random.randint(0, 0xFF)
    symbol['shndx'] = random.randint(0, 0xFFFF)
    symbol['value'] = random.randint(0, 0xFFFFFFFF)
    return symbol

  def _gen_symbols(self):
    for i in xrange(self.state['num_symbols']):
      self.state['symbols'].append(self._gen_symbol())
    symbols = ''
    strtab = '\0'
    for s in self.state['symbols']:
      s['name_off'] = len(strtab)
      strtab += s['name'] + '\0'
      symbols += struct.pack('<IIIBBH', s['name_off'], s['value'], s['size'], s['info'], s['other'], s['shndx'])
    self.state['cgcf'] += symbols
    self.state['strtab'] = strtab

  def _gen_section(self):
    section = dict()
    section['name'] = random_string()
    section['flags'] = random.randint(0, 7)
    section['addr'] = random.randint(0, 0xFFFFFFFF)
    section['offset'] = self.state['cur_off']
    section['size'] = random.randint(0x100, 0x500)
    section['link'] = 0
    section['info'] = random.randint(0, 0xFFFFFFFF)
    section['addralign'] = random.choice([0, 1, 2, 4, 8, 16])
    section['entsize'] = 0
    section['type'] = random.choice([1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 15, 16, 17, 18, 19])
    return section

  def _gen_sections(self):
    self.state['cur_off'] = self.state['base_off']
    self.state['sections'].append({'name': '', 'type': 0, 'flags': 0, 'addr': 0, 'offset': 0, 'size': 0, 'link': 0, 'info': 0, 'addralign': 0, 'entsize': 0})
    for i in xrange(self.state['e_shnum'] - 3):
      if i + 1 == self.state['e_shtrndx']:
        self.state['sections'].append({'name': random_string(), 'type': 3, 'flags': 0, 'addr': 0, 'offset': self.state['cur_off'], 'size': 21 * self.state['e_shnum'], 'link': 0, 'info': 0, 'addralign': 0, 'entsize': 0})
        self.state['cur_off'] += 21 * self.state['e_shnum']
      else:
        s = self._gen_section()
        self.state['sections'].append(s)
        self.state['cur_off'] += s['size']
    self.state['sections'].append({'name': random_string(), 'type': 2, 'flags': 0, 'addr': 0, 'offset': self.state['cur_off'], 'size': self.state['num_symbols'] * 16, 'link': self.state['e_shnum'] - 1, 'info': 0, 'addralign': 0, 'entsize': 0})
    self.state['cur_off'] += self.state['num_symbols'] * 16
    self.state['sections'].append({'name': random_string(), 'type': 3, 'flags': 0, 'addr': 0, 'offset': self.state['cur_off'], 'size': 21 * self.state['num_symbols'], 'link': 0, 'info': 0, 'addralign': 0, 'entsize': 0})
    self.state['cur_off'] += self.state['num_symbols'] + 21

    sections = ''
    shstr = ''
    for s in self.state['sections']:
      s['name_off'] = len(shstr)
      shstr += s['name'] + '\0'
      sections += struct.pack('<IIIIIIIIII', s['name_off'], s['type'], s['flags'], s['addr'], s['offset'], s['size'], s['link'], s['info'], s['addralign'], s['entsize'])
    self.state['cgcf'] += sections
    self.state['shstr'] = shstr

  def _gen_cgcf_header(self):
    if random.randint(1, 100) <= 3:
      header = random_bytes(4)
    else:
      header = '\x7fCGC'
    header += '\x01\x01' + random_bytes(12 - 2)
    header += random_bytes(2 + 2 + 4 + 4)
    self.state['e_phoff'] = random.randint(0x34, 0x34 + 20)
    self.state['e_shoff'] = random.randint(0x400, 0x400 + 100)
    header += struct.pack('<II', self.state['e_phoff'], self.state['e_shoff'])
    header += random_bytes(4)
    header += struct.pack('<H', self.state['e_phoff'])
    header += random_bytes(2 + 2)
    header += struct.pack('<H', 40)
    self.state['e_shnum'] = random.randint(5, 20)
    header += struct.pack('<H', self.state['e_shnum'])
    self.state['e_shtrndx'] = random.randint(1, self.state['e_shnum'] - 3)
    header += struct.pack('<H', self.state['e_shtrndx'])
    header += random_bytes(self.state['e_phoff'] - len(header))
    self.state['cgcf'] = header

  def gen_cgcf(self):
    self._gen_cgcf_header()
    self.state['cgcf'] += random_bytes(self.state['e_shoff'] - len(self.state['cgcf']))
    if self.state['base_off'] - self.state['e_shoff'] < self.state['e_shnum'] * 40:
      self.state['base_off'] = self.state['e_shnum'] * 40 + self.state['e_shoff']
    self._gen_sections()
    self.state['cgcf'] += random_bytes(self.state['base_off'] - len(self.state['cgcf']))

    for i in xrange(len(self.state['sections']) - 2):
      s = self.state['sections'][i]
      if i == self.state['e_shtrndx']:
        self.state['cgcf'] += self.state['shstr'].ljust(s['size'], '\0')
      else:
        self.state['cgcf'] += random_bytes(s['size'])
    self._gen_symbols()
    self.state['cgcf'] += self.state['strtab'].ljust(self.state['sections'][-1]['size'], '\0')
    output = struct.pack('<I', len(self.state['cgcf'])) + self.state['cgcf']
    self.write(output)

  def _max_section_name_len(self):
    return len(max(self.state['sections'], key=lambda x: len(x['name']))['name'])

  def _section_type2str(self, t):
    if t == 0: return "NULL"
    if t == 1: return "PROGBITS"
    if t == 2: return "SYMTAB"
    if t == 3: return "STRTAB"
    if t == 4: return "RELA"
    if t == 5: return "HASH"
    if t == 6: return "DYNAMIC"
    if t == 7: return "NOTE"
    if t == 8: return "NOBITS"
    if t == 9: return "REL"
    if t == 10: return "-reserved-"
    if t == 11: return "DYNSYM"
    if t == 14: return "INIT_ARRAY"
    if t == 15: return "FINI_ARRAY"
    if t == 16: return "PREINIT_ARRAY"
    if t == 17: return "GROUP"
    if t == 18: return "SYMTAB_SHNDX"
    if t == 19: return "NUM"

    return "UNKNOWN"

  def _symbol_type2str(self, t):
    if t == 0: return "NOTYPE"
    if t == 1: return "OBJECT"
    if t == 2: return "FUNC"
    if t == 3: return "SECTION"
    if t == 4: return "FILE"
    if t == 5: return "COMMON"
    if t == 6: return "TLS"
    if t == 7: return "NUM"

    return "UNKNOWN"

  def _symbol_bind2str(self, b):
    if b == 0: return "LOCAL"
    if b == 1: return "GLOBAL"
    if b == 2: return "WEAK"
    if b == 3: return "NUM"

    return "UNKNOWN"

  def parse_cgcf(self):
    if len(self.state['cgcf']) > 2 * 1024 * 1024:
      self.read(length=len('Too big.\n'), expect='Too big.\n')
      return
    if self.state['cgcf'][:4] != '\x7fCGC':
      self.read(length=len('Invalid CGC magic.\n'), expect='Invalid CGC magic.\n')
      return
    s = 'Valid CGC executable format found [%d bytes]\n\n' % len(self.state['cgcf'])
    self.read(length=len(s), expect=s)
    s = '%d section header(s):\n' % len(self.state['sections'])
    self.read(length=len(s), expect=s)
    max_len = self._max_section_name_len()
    s = '  [No.] Name' + ' ' * (max_len - 4) + '  Type           Addr     Off    Size\n'
    self.read(length=len(s), expect=s)
    self.state['sections'] = sorted(self.state['sections'], key=lambda x: x['offset'])
    for i in xrange(len(self.state['sections'])):
      sec = self.state['sections'][i]
      s = '  [%3d] %s' % (i, sec['name'])
      s += ' ' * (max_len - len(sec['name']))
      type_str = self._section_type2str(sec['type'])
      s += '  %s' % type_str
      s += ' ' * (14 - len(type_str))
      s += ' %08x %06x %06x\n' % (sec['addr'], sec['offset'], sec['size'])
      self.read(length=len(s), expect=s)
    self.read(length=len('\n'), expect='\n')

    s = '%d symbol(s):\n' % len(self.state['symbols'])
    self.read(length=len(s), expect=s)
    s = '  [No.] Value       Size Type    Bind    Name\n'
    self.read(length=len(s), expect=s)
    self.state['symbols'] = sorted(self.state['symbols'], key=lambda x: x['name'])
    for i in xrange(len(self.state['symbols'])):
      sym = self.state['symbols'][i]
      typ = self._symbol_type2str(sym['info'] & 0xF)
      bind = self._symbol_bind2str(sym['info'] >> 4)
      s = '  [%3d] 0x%08x %5d %s' % (i, sym['value'], sym['size'], typ)
      s += ' ' * (7 - len(typ))
      s += ' %s' % (bind) + ' ' * (7 - len(bind))
      s += ' %s\n' % sym['name']
      self.read(length=len(s), expect=s)
    self.read(length=len('\n'), expect='\n')

    self.read(length=len('DONE\n'), expect='DONE\n')

