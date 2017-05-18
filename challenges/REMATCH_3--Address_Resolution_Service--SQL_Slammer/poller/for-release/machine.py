#!/usr/bin/env python

from generator.actions import Actions
import random
import string
import struct
import ctypes 

class PRNG:
  def __init__(self, magic_page, generator):
    self.prng_offset = 0
    self.magic_page = magic_page
    self.random_state = []
    self.x = struct.unpack("<I", magic_page[0:4])[0]
    self.y = struct.unpack("<I", magic_page[4:8])[0]
    self.z = struct.unpack("<I", magic_page[8:12])[0]
    self.w = struct.unpack("<I", magic_page[12:16])[0]

  def prng(self):
    r = self.x
    r = r ^ ((r << 11)&0xffffffff)
    r = r ^ ((r >> 8)&0xffffffff)
    self.x = self.y
    self.y = self.z
    self.z = self.w
    self.w = self.w ^ ((self.w >> 19)&0xffffffff)
    self.w = self.w ^ r
    return self.w

  def random_in_range(self, min, max):
    if (min > max):
      return 0
    if (min == max):
      return min
    delta = max - min
    scale = 0xffffffff / delta
    value = self.prng()
    return min + (value / scale)

  def gen_random_str(self, length):
    if (length <= 0):
      return None
    s = ''.join(chr(self.random_in_range(0x41, 0x7a)) for _ in range(length))
    return s

  def gen_random_number(self, min, max):
    return self.random_in_range(min, max)


class CROMU_000094Generator(Actions):
    def start(self):
        self.delay(50)
        adminPortOffset = 0
        self.count = 0
        #initialize state
        self.prng = PRNG(self.magic_page, self)
        self.serverList = []
        numServers = self.prng.gen_random_number(10,32)
        stringLen = self.prng.gen_random_number(34, 64)
        for i in range(numServers):
          server = {"name":self.prng.gen_random_str(stringLen - i), "instances":[]}
          self.serverList.append(server)
          numInstances = self.prng.gen_random_number(1, 15)
          instanceLen = self.prng.gen_random_number(32, 64)
          for j in range(numInstances):
            adminPortOffset = (adminPortOffset + 4) % 4096
            instance = {"name":self.prng.gen_random_str(instanceLen - j), "port":self.prng.gen_random_number(0, 65535),
              "adminPortOffset":adminPortOffset}
            server["instances"].append(instance)

    def main_loop(self):
      if self.count > 5:
        self.quit()
        return -1
      else:
        self.count += 1

    def query_invalid(self):
      query = struct.pack("<B", random.randint(20, 255)) 
      self.write(query + '\n')
      self.read(delim='\n', expect="Invalid Query")
      return -1

    def query_all(self):
      query = "\x01"
      self.write(query + '\n')
      self.read(delim='\n', expect="Query All")
      response = ""
      for server in self.serverList:
        response += "server:%s:" % server["name"]
      self.read(length=3, expect='\x05' + struct.pack("<H", len(response)))
      self.read(delim='\0', expect=response)

    def query_server(self):
      server = random.choice(self.serverList)
      query = "\x02" + server["name"]
      self.write(query + '\n')
      self.read(delim='\n', expect="Query Server")
      response = ""
      for instance in server["instances"]:
        response += "instance:%s:" % instance["name"]
      self.read(length=3, expect='\x05' + struct.pack("<H", len(response)))
      self.read(delim='\0', expect=response)

    def query_one(self):
      server = random.choice(self.serverList)
      instance = random.choice(server["instances"])
      query = "\x03" + instance["name"]
      self.write(query + '\n')
      self.read(delim='\n', expect="Query One")
      response = "instance:%s:tcp:%d:server:%s:" % (instance["name"], instance["port"], server["name"])
      self.read(length=3, expect='\x05' + struct.pack("<H", len(response)))
      self.read(delim='\0', expect=response)

    def query_admin(self):
      server = random.choice(self.serverList)
      instance = random.choice(server["instances"])
      query = "\x04\x01" + instance["name"]
      self.write(query + '\n')
      adminPort = self.magic_page[instance["adminPortOffset"]:instance["adminPortOffset"]+2]
      response = "admin:%x:" % struct.unpack("<H", adminPort)[0]
      self.read(delim='\n', expect="Query Admin")
      self.read(length=3, expect='\x05' + struct.pack("<H", len(response)))
      self.read(delim='\0', expect=response)

    def quit(self):
      self.write('\xff\n')
      self.read(delim='\n', expect="Invalid Query")
