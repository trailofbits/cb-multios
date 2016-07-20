#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
import re

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class File(object):
  FT_REG = 0
  FT_DIR = 1
  def __init__(self, name, type, size, parent):
    self.name = name
    self.type = type
    self.size = size
    self.parent = parent
    self.opened = False
    self.content = ''
    self.files = []

  def __repr__(self):
    s = ''
    if self.type == self.FT_REG:
      s += '<FILE> %s ' % ('O' if self.opened else 'C')
    else:
      s += '<DIR> D '
    s+= '%d %s\n' % (self.size, self.name)
    return s

  def __str__(self):
    return self.__repr__()

  def open(self):
    if self.opened:
      return 1
    self.opened = True
    return 0

  def close(self):
    if not self.opened:
      return 1
    self.opened = False
    return 0

  def read(self, pos, length):
    if self.type != self.FT_REG:
      return -10, None
    if not self.opened:
      return -30, None
    if self.size == 0:
      return -40, None
    if pos >= self.size:
      return -50, None
    if length == 0:
      length = self.size
    length = (self.size - pos) if length > self.size - pos else length
    return length, self.content[pos:pos + length]

  def write(self, pos, buf, length):
    if self.type != self.FT_REG:
      return -10
    if not self.opened:
      return -30
    if length == 0:
      return 0
    if pos >= self.size or pos + length > self.size:
      self.size = pos + length
    self.content = self.content[:pos] + buf + self.content[pos + length:]
    return length

class AFILES(Actions):

  MAX_NUM_FILES = 512
  MAX_NUM_OPENED_FILES = 20

  def start(self):
    self.commands = ["list", "ls", "create", "new", "open", "close", "close_all", "read", "cat", "modify", "write", "delete", "rm", "mkdir", "rmdir", "chdir", "cd", "help", "?", "quit", "exit"]
    self.usages = [
        "list [file ..]\n - Lists files and directories.\n",
        "create <filename>\n - Creates a file.\n",
        "open <filename>\n - Opens a file.\n",
        "close <fileno>\n - Closes an open file.\n",
        "close_all\n - Closes all open files.\n",
        "read <fileno> [pos] [len]\n - Reads a file.\n",
        "modify <fileno> [pos]\n - Modifies a file.\n",
        "delete <filename>\n - Deletes a file.\n",
        "mkdir <dirname>\n - Creates a directory.\n",
        "rmdir <dirname>\n - Deletes a directory.\n",
        "chdir <dirname>\n - Changes the working directory.\n",
        "quit\n - Quits the program.\n",
        "help [command]\n - Displays the help message.\n",
        ]
    self.root_dir = File('/', File.FT_DIR, 0, None)
    self.root_dir.parent = self.root_dir
    self.cwd = self.root_dir
    self.num_files = 0
    self.num_opened_files = 0
    self.opened_files = [None for i in xrange(self.MAX_NUM_OPENED_FILES)]

  def shell(self):
    self.read(length=len('$ '), expect='$ ')

  def _print_file(self, f):
    out = ''
    if f.type == File.FT_DIR:
      files = f.files
      out += '%d entries\n<DIR> D 0 .\n<DIR> D 0 ..\n' % (len(files) + 2)
      for f in files:
        out += str(f)
    else:
      out += str(f)
    return out

  def list(self):
    cmd = random.choice(['list', 'ls'])
    pool = ['.', '..'] + self.cwd.files
    n = random.randint(0, len(pool))
    files = list()
    for i in xrange(n):
      f = random.choice(pool)
      cmd += ' %s' % (f.name if f != '.' and f != '..' else f)
      files.append(f)
    cmd += '\n'

    out = ''
    if len(files) == 0:
      out += self._print_file(self.cwd)
    elif len(files) == 1:
      f = files[0]
      if f == '.':
        f = self.cwd
      elif f == '..':
        f = self.cwd.parent
      out += self._print_file(f)
    else:
      for f in files:
        if f == '.':
          f = self.cwd
          name = '.'
        elif f == '..':
          f = self.cwd.parent
          name = '..'
        else:
          name = f.name
        out += '%s:\n' % name
        out += self._print_file(f)
        out += '\n'
      out = out[:-1]

    self.write(cmd)
    self.read(length=len(out), expect=out)

  def create(self):
    cmd = random.choice(['create', 'new'])
    name = random_string()
    if random.randint(1, 100) <= 10:
      name = ''
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      out += 'No filename specified\n'
    else:
      if self.num_files == self.MAX_NUM_FILES:
        out += 'Max number of files reached\n'
      elif len(filter(lambda x: x.name == name, self.cwd.files)) > 0:
        out += 'File already exists\n'
      else:
        f = File(name, File.FT_REG, 0, self.cwd)
        self.cwd.files.append(f)
        self.num_files += 1

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def open(self):
    cmd = random.choice(['open'])
    if len(self.cwd.files) == 0:
      f = None
      name = random_string()
    else:
      f = random.choice(self.cwd.files)
      name = f.name
    r = random.randint(1, 100)
    if r <= 10:
      name = random_string()
      f = None
    elif r >= 91:
      name = ''
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      out += 'No filename specified\n'
    else:
      if self.num_opened_files == self.MAX_NUM_OPENED_FILES:
        out += 'Max number of opened files reached\n'
      elif f is None:
        out += 'No such file\n'
      else:
        if f.type == File.FT_DIR:
          out += 'Not a regular file\n'
        elif f.opened:
          out += 'Already opened\n'
        else:
          idx = self.opened_files.index(None)
          f.open()
          self.opened_files[idx] = f
          self.num_opened_files += 1
          out += '[%s] opened (%d)\n' % (name, idx)

    self.write(cmd)
    self.read(length=len(out), expect=out)

  def close(self):
    cmd = random.choice(['close'])
    r = random.randint(1, 100)
    l = []
    if r <= 5:
      idx = ''
    elif r >= 91:
      l = [i for i,x in enumerate(self.opened_files) if x is None]
      idx = random.randint(21, 100)
    else:
      l = [i for i,x in enumerate(self.opened_files) if x is not None]
      idx = random.randint(0, 20)
    if len(l) > 0:
      idx = random.choice(l)
    cmd += ' ' + str(idx) + '\n'

    out = ''
    if idx == '':
      out += 'No fileno specified\n'
    else:
      if idx >= self.MAX_NUM_OPENED_FILES or self.opened_files[idx] is None:
        out += 'Invalid fileno\n'
      else:
        f = self.opened_files[idx]
        if f.type == File.FT_DIR:
          out += 'Not a regular file\n'
        else:
          if not f.opened:
            out += 'Already closed\n'
          f.close()
          self.num_opened_files -= 1
          self.opened_files[idx] = None

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def close_all(self):
    cmd = random.choice(['close_all'])
    cmd += '\n'

    for i,f in enumerate(self.opened_files):
      if f:
        f.close()
        self.num_opened_files -= 1
        self.opened_files[i] = None

    self.write(cmd)

  def readfile(self):
    cmd = random.choice(['read', 'cat'])
    r = random.randint(1, 100)
    l = []
    if r <= 5:
      idx = ''
    elif r >= 91:
      l = [i for i,x in enumerate(self.opened_files) if x is None]
      idx = random.randint(21, 100)
    else:
      l = [i for i,x in enumerate(self.opened_files) if x is not None]
      idx = random.randint(0, 20)
    if len(l) > 0:
      idx = random.choice(l)
    cmd += ' ' + str(idx) + '\n'

    out = ''
    if idx == '':
      out += 'No fileno specified\n'
    else:
      if idx >= self.MAX_NUM_OPENED_FILES or self.opened_files[idx] is None:
        out += 'Invalid fileno\n'
      else:
        f = self.opened_files[idx]
        ret, buf = f.read(0, 0)
        if ret == -10:
          out += 'Not a regular file\n'
        elif ret == -30:
          out += 'File not opened\n'
        elif ret == -40:
          out += 'Empty file\n'
        elif ret == -50:
          out += 'Out of range\n'
        else:
          out += buf

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def modify(self):
    cmd = random.choice(['modify', 'write'])
    r = random.randint(1, 100)
    l = []
    if r <= 5:
      idx = ''
    elif r >= 91:
      l = [i for i,x in enumerate(self.opened_files) if x is None]
      idx = random.randint(21, 100)
    else:
      l = [i for i,x in enumerate(self.opened_files) if x is not None]
      idx = random.randint(0, 20)
    if len(l) > 0:
      idx = random.choice(l)
    cmd += ' ' + str(idx) + '\n'

    self.write(cmd)

    out = ''
    if idx == '':
      out += 'No fileno specified\n'
    else:
      if idx >= self.MAX_NUM_OPENED_FILES or self.opened_files[idx] is None:
        out += 'Invalid fileno\n'
      else:
        f = self.opened_files[idx]
        ret = f.write(0, '', 0)
        if ret == -10:
          out += 'Not a regular file\n'
        elif ret == -30:
          out += 'File not opened\n'
        else:
          tt = '<< Edit Mode - end with EOF >>\n'
          tt += 'pos: %d\n' % 0
          tt += '==============================\n'
          self.read(length=len(tt), expect=tt)
          ss = ''
          for i in xrange(random.randint(1, 20)):
            ss += random_string() + ' '
          ss = ss[:-1] + '\n'
          f.write(0, ss, len(ss))
          self.write(ss + 'EOF\n')
          tt = '==============================\n'
          tt += 'Wrote %d byte(s)\n' % len(ss)
          self.read(length=len(tt), expect=tt)
          return

    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def delete(self):
    cmd = random.choice(['delete', 'rm'])
    r = random.randint(1, 100)
    if r <= 10:
      name = ''
    elif r >= 91:
      name = random_string()
    else:
      if len(self.cwd.files) > 0:
        f = random.choice(self.cwd.files)
        name = f.name
      else:
        name = random_string()
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      out += 'No file specified\n'
    else:
      if len(filter(lambda x: x.name == name, self.cwd.files)) == 0:
        out += 'No such file\n'
      elif f.type != File.FT_REG:
        out += 'Not a regular file\n'
      else:
        if f in self.opened_files:
          idx = self.opened_files.index(f)
          self.write('close %d\n' % idx)
          self.read(length=len('$ '), expect='$ ')
          f.close()
          self.num_opened_files -= 1
          self.opened_files[idx] = None
        self.cwd.files.remove(f)
        self.num_files -= 1

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def mkdir(self):
    cmd = random.choice(['mkdir'])
    name = random_string()
    if random.randint(1, 100) <= 10:
      name = ''
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      out += 'No dirname specified\n'
    else:
      if self.num_files == self.MAX_NUM_FILES:
        out += 'Max number of files reached\n'
      elif len(filter(lambda x: x.name == name, self.cwd.files)) > 0:
        out += 'File already exists\n'
      else:
        f = File(name, File.FT_DIR, 0, self.cwd)
        self.cwd.files.append(f)
        self.num_files += 1

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def _rmdir_helper(self, d):
    files = d.files
    while len(files) > 0:
      f = files[0]
      if f.type == File.FT_REG:
        if f in self.opened_files:
          idx = self.opened_files.index(f)
          f.close()
          self.num_opened_files -= 1
          self.opened_files[idx] = None
      else:
        self._rmdir_helper(f)
      files.remove(f)
      self.num_files -= 1

  def rmdir(self):
    cmd = random.choice(['rmdir'])
    r = random.randint(1, 100)
    if r <= 10:
      name = random_string()
    elif r >= 91:
      name = ''
    else:
      files = filter(lambda x: x.type == File.FT_REG, self.cwd.files)
      dirs = filter(lambda x: x.type == File.FT_DIR, self.cwd.files)
      r = random.randint(1, 100)
      if r <= 50:
        name = random_string()
        if len(files) > 0:
          f = random.choice(files)
          name = f.name
      else:
        name = random_string()
        if len(dirs) > 0:
          f = random.choice(dirs)
          name = f.name
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      out += 'No dirname specified\n'
    elif name not in [x.name for x in self.cwd.files]:
      out += 'No such directory\n'
    elif name in [x.name for x in files]:
      out += 'Not a directory\n'
    else:
      assert(f)
      self._rmdir_helper(f)
      self.cwd.files.remove(f)

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def chdir(self):
    cmd = random.choice(['chdir', 'cd'])
    r = random.randint(1, 100)
    if r <= 10:
      name = random_string()
    elif 11 <= r <= 20:
      name = '.'
    elif 21 <= r <= 30:
      name = '..'
    elif r >= 91:
      name = ''
    else:
      files = filter(lambda x: x.type == File.FT_REG, self.cwd.files)
      dirs = filter(lambda x: x.type == File.FT_DIR, self.cwd.files)
      r = random.randint(1, 100)
      if r <= 50:
        name = ''
        if len(files) > 0:
          f = random.choice(files)
          name = f.name
      else:
        name = ''
        if len(dirs) > 0:
          f = random.choice(dirs)
          name = f.name
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      self.cwd = self.root_dir
    elif name == '.':
      pass
    elif name == '..':
      self.cwd = self.cwd.parent
    elif name not in [x.name for x in self.cwd.files]:
      out += 'No such file or directory\n'
    elif name in [x.name for x in files]:
      out += 'Not a directory\n'
    else:
      assert(f)
      self.cwd = f

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def help(self):
    cmd = random.choice(['help', '?'])
    r = random.randint(1, 100)
    if r <= 90:
      name = random.choice(self.commands)
    elif r >= 95:
      name = ''
    else:
      name = random_string()
    cmd += ' ' + name + '\n'

    out = ''
    if name == '':
      out += ''.join(self.usages)
    else:
      if name == 'list' or name == 'ls':
        out += self.usages[0]
      elif name == 'create' or name == 'new':
        out += self.usages[1]
      elif name == 'open':
        out += self.usages[2]
      elif name == 'close':
        out += self.usages[3]
      elif name == 'close_all':
        out += self.usages[4]
      elif name == 'read' or name == 'cat':
        out += self.usages[5]
      elif name == 'modify' or name == 'write':
        out += self.usages[6]
      elif name == 'delete' or name == 'rm':
        out += self.usages[7]
      elif name == 'mkdir':
        out += self.usages[8]
      elif name == 'rmdir':
        out += self.usages[9]
      elif name == 'chdir' or name == 'cd':
        out += self.usages[10]
      elif name == 'quit' or name == 'exit':
        out += self.usages[11]
      elif name == 'help' or name == '?':
        out += self.usages[12]

    self.write(cmd)
    if len(out) > 0:
      self.read(length=len(out), expect=out)

  def quit(self):
    self.write(random.choice(['quit', 'exit']) + '\n')

  def invalid(self):
    while True:
      s = random_string()
      if s not in self.commands:
        break
    self.write(s + '\n')
    r = 'Unknown command [%s]\n' % s
    self.read(length=len(r), expect=r)
