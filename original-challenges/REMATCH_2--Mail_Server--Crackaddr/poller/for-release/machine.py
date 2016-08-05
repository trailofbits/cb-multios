#!/usr/bin/env python

from generator.actions import Actions,Variable
import random
import string
import struct
import pdb 
import ctypes

class PollGenerator(Actions):

  def start(self):
    self.delay(50)
    self.count = 0

  def gen_random_str(self, min, max):
        length = self.random_in_range(min, max)
        s = ''.join(chr(self.random_in_range(0x2E, 0x7e)) for _ in range(length-2))
        return s
  def init_prng(self):
        #setup prng
        self.prng = ctypes.CDLL('build/patched/so/CROMU_00098.so')
        self.seed_prng = self.prng.seed_prng
        self.seed_prng.argtypes = [ctypes.c_uint]
        self.seed_prng.restype = None
        self.random_in_range = self.prng.random_in_range
        self.random_in_range.argtypes = [ctypes.c_uint, ctypes.c_uint]
        self.random_in_range.restype = ctypes.c_uint
        self.call_prng = self.prng.prng
        self.call_prng.argtypes = []
        self.call_prng.restype = ctypes.c_uint
        self.seed_prng(ctypes.c_uint(struct.unpack('<L', self.magic_page[0:4])[0]))

  def send_addr(self):
      self.write(self.addr + '\n')
      self.read(delim='\n', expect=self.output + '\n')

  def pick_address(self):
      count = len(self.address_book)
      return self.address_book[self.random_in_range(0, count - 1)]

  def gen_random_msg(self):
      msg = {}
      msg['sender'] = self.pick_address()
      msg['recipient'] = self.pick_address()
      msg['subject'] = self.gen_random_str(5, 32)
      msg['data'] = self.gen_random_str(5, 256)
      msg['data_length'] = len(msg['data'])
      return msg


  def sendmail(self):
      self.read(delim=':', expect="sendmail:")
      self.address_book = []
      self.init_prng()
      for i in range(20):
          address = {}
          address['index'] = i + 1
          address['name'] = self.gen_random_str(5,32)
          address['home_server'] = self.gen_random_str(5,32)
          address['mode'] = self.random_in_range(0,1)
          self.address_book.append(address)
      self.mail_queues = []
      for i in range(33):
          mq = {}
          sender = self.pick_address()
          mq['name'] = sender['name']
          mq['messages'] = []
          mq['messages'].append(self.gen_random_msg())
          self.mail_queues.append(mq)

  def sendmail_read_queue(self, mq):
      i = 0
      for msg in mq['messages']:
          self.read(delim='\n', expect='%d) From:%s To: %s SUBJECT:%s' % (i, msg['sender']['name'], msg['recipient']['name'], msg['subject']))
          i += 1

  def find_queue(self, name):
      for mq in self.mail_queues:
          if mq['name'] == name:
              return mq
      return None

  def sendmail_loop(self):
      self.count += 1
      if self.count > 5:
          self.sendmail_quit()
          return -1
  
  def sendmail_ADDRESSBOOK(self):
      self.write("ADDRESSBOOK\n")
      self.read(delim='\n', expect="Address Book:")
      for each in self.address_book:
          self.read(delim='\n', expect="%d) %s@%s [%d]" % (each['index'], each['name'], each['home_server'], each['mode']))

  def sendmail_LIST(self):
      mq = random.choice(self.mail_queues)
      self.write("LIST %s\n" % mq['name'])
      self.sendmail_read_queue(self.find_queue(mq['name']))

  def sendmail_LISTALL(self):
      self.write("LISTALL\n")
      for mq in self.mail_queues:
          self.read(delim='\n', expect='QUEUE: %s\n' % mq['name'])
          self.sendmail_read_queue(mq)
          self.read(delim='\n')

  def sendmail_POST(self):
      msg = self.gen_random_msg()
      if (self.chance() < 0.2):
        output = "A"*1000
        while (len(output) >= 1000):
          length = random.randint(10, 2000)
          recipient = ''.join(random.choice(string.ascii_letters) for _ in range(length))
          # Don't allow Cc's in large strings
          if len(recipient) > 750:
            recipient = recipient.replace('C', '4')
          output = self.make_output(recipient)

        command = "POST sender:%s!recipient:+%s!body:%s!subject:%s!\n" % (msg['sender']['name'], recipient, msg['data'], msg['subject'])
        self.write(command);
        self.read(delim='\n', expect="addr:%s" % output)
      else:
        command = "POST sender:%s!recipient:%s!body:%s!subject:%s!\n" % (msg['sender']['name'], msg['recipient']['name'], msg['data'], msg['subject'])
        mq = self.find_queue(msg['sender']['name'])
        if mq == None:
            mq = {}
            mq['name'] = msg['sender']['name']
            mq['messages'] = []
            mq['messages'].append(msg)
            self.mail_queues.append(mq)
        else:
            mq['messages'].append(msg)
        self.write(command)
        self.read(delim='\n', expect='Message Received')

  def sendmail_READ(self):
      mq = random.choice(self.mail_queues)
      mq = self.find_queue(mq['name'])
      msg_num = random.randint(0, len(mq['messages'])-1)
      self.write("READ %s %d\n" % (mq['name'], msg_num))
      self.read(delim='\n', expect="%d) Subject:%s Body:%s\n" % (msg_num, mq['messages'][msg_num]['subject'], mq['messages'][msg_num]['data']))

  def sendmail_quit(self):
      self.write("QUIT\n")
      self.read(delim='\n', expect="Goodbye.")


  def make_output(self, addr):
    addrp = 0
    output = ""
    outp = 0
    endp = 1024 - 5

    while (addr[addrp] == ' '):
        addrp+=1
    
    inA = False
    inC = False
    Blevel = 0
    Blevelout = 0
    full = False
    Dmode = False
    outputLevel = 0

    while (addrp < len(addr)):

      c = addr[addrp]
      addrp+=1
      full = (outp >= endp)
      if (not full and outputLevel > 0):
        output += c
        outp+=1

      if (c == 'A'):
        outputLevel = 0;
        if (not inA):
          inA = True
          endp-=1
      if (c == 'a'):
        outputLevel += 1
        if outputLevel <= 1:
          output += c
          outp+=1
        if (inA):
          inA = False
          endp+=1
      
      if (c == 'B'):
        Blevel+=1
        if (not full):
          Blevelout+=1
          endp-=1
          outputLevel += 1

      if ((c == 'b') and (Blevel > 0)):
        Blevel-=1
        outputLevel -= 1
        if (not full):
          Blevelout-=1
          endp+=1
        continue
      elif (c == 'b'):
        if (not full and outputLevel > 0):
          output = output[0:len(output)-1]
          outp-=1

      if ((c == 'C') and (not inC)):
        inC = True
        
      if ((c == 'c') and (inC)):
        inC = False
        endp+=1

      if (c == 'D'):
        Dmode = not Dmode


      if (( c == 'F') and (not full)):
        if addrp < len(addr):
          output += addr[addrp]
          outp+=1
          addrp+=1
        continue

      if (c == 'G'):
        addrp+=1
        continue

    if (inA):
      output+= 'a'
      outp += 1
    while ((Blevelout > 0) and (outp < endp - 2)):
      Blevelout-=1
      output += 'b'
      outp += 1
    if (inC):
      output+= 'c'
      outp += 1
    if (Dmode):
      output+='D'
      outp += 1

    return output


