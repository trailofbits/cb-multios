#!/usr/bin/env python

from generator.actions import Actions
import random
import string
import struct
from struct import pack, unpack
import ctypes 


class MorrisGenerator(Actions):
    def start(self):
        #self.delay(100)
        self.count = 0

    def gen_random_str(self, min, max):
        length = self.random_in_range(min, max)
        s = ''.join(chr(self.random_in_range(0x30, 0x7e)) for _ in range(length-2))
        return s

    def gen_random_user(self):
        user = {}
        user['name'] = self.gen_random_str(5, 32)
        user['hostname'] = self.gen_random_str(5,32)
        user['idletime'] = self.call_prng() & 0xffffff
        user['realname'] = self.gen_random_str(5,64)
        user['phone'] = self.gen_random_str(9,9)
        user['online'] = self.random_in_range(0,1)
        return user

    def init_prng(self):
        #setup prng
        self.prng_offset = 0
        self.random_state = []
        for i in range(512):
          self.random_state.append(unpack("<Q", self.magic_page[i*8: i*8 + 8])[0])
        self.a = 12
        self.b = 25 
        self.c = 27
        self.mult = unpack("<Q", self.magic_page[4:12])[0] 
        self.randomIndex = 0
        
        
    def call_prng(self):
        r = self.random_state[self.randomIndex] 
        r = r ^ (r >> self.a) & 0xffffffffffffffff
        r = r ^ (r << self.b) & 0xffffffffffffffff
        r = r ^ (r >> self.c) & 0xffffffffffffffff
        self.random_state[self.randomIndex] = r & 0xffffffffffffffff
        self.randomIndex = (self.randomIndex + 1) % 512
        big = r * self.mult
        return ((big >> 32) & 0xffffffff)

    def random_in_range(self, min, max):
        if (min > max):
          return 0
        if (min == max):
          return min
        delta = max - min
        scale = 0xffffffff / delta
        value = self.call_prng()
        return min + (value / scale)


    def init_lookupd(self):
        self.lookupd_brief = random.choice([True, False])
        self.lookupd_quick = random.choice([True, False])
        self.lookupd_users = []
        self.lookupd_shortlist = []
        self.init_prng()

        self.lookupd_users.append(self.gen_random_user())
        for i in range(10):
            self.lookupd_users.append(self.gen_random_user())


    def lookupd(self):     

        self.init_lookupd()
        self.read(delim=':', expect="frontdoor:")
        command = "lookupd "
        if random.choice([True, False]):
            command += "/W "

        self.write("%s\n" % command)
        command = "lookup "
        if self.lookupd_brief:
            command += '-s '
        else:
            if random.choice([True, False]):
                command += '-l '
        
        
        user = None

        if (self.chance() > 0.2):
            user = random.choice(self.lookupd_users)
            command += user['name']

        self.write(command + '\n')

        if user:
            self.lookupd_read_user(user)
        else:
            # read all users
            for user in self.lookupd_users:
                self.lookupd_read_user(user)


    def lookupd_read_user(self, user):
        if (self.lookupd_brief):
            self.read(delim='\n', expect="Username: %s\n" % user['name'])
            self.read(delim='\n', expect="Real name: %s\n" % user['realname'])
            self.read(delim='\n', expect="Phone #:%s\n" % user['phone'])
            self.read(delim='\n', expect='\n')
        else:
            result = "Username: %s\n" % user['name']
            result += "Real name: %s\n" % user['realname']
            result += "Host name: %s\n" % user['hostname']
            result += "Idle for: %d seconds\n" % user['idletime']
            self.read(length=len(result), expect=result)
            if (user['online'] == 1):
                self.read(delim='\n', expect="User is online\n");
            else:
                self.read(delim='\n', expect="User is offline\n");
            self.read(delim='\n\n', expect="Phone #:%s\n\n" % user['phone'])

    def ish(self):
        self.read(delim=':', expect="frontdoor:")
        self.init_prng()
        command = "ish "
        options = " "
        flags = set(['+n ', '+L ', '+e ', '+9 ', '+8 '])
        pick_flags = random.sample(flags, random.randint(0, len(flags)))
        for each in pick_flags:
            options += each


        #setup internal state
        self.ish_userlist = []
        self.ish_hostlist = []
        for i in range(31):
            newuser = {}
            newuser['username'] = self.gen_random_str(5, 32)
            newuser['password'] = self.gen_random_str(5, 32)
            self.ish_userlist.append(newuser)
        for i in range(31):
            newhost = {}
            newhost['hostname'] = self.gen_random_str(5, 32)
            index = self.random_in_range(1, 31) - 1
            newhost['username'] = self.ish_userlist[index]['username']
            self.ish_hostlist.append(newhost)

        valid = True

        #pick a user + pw
        ish_user = random.choice(self.ish_userlist)

        #pick a hostname
        hostname = None
        for host in self.ish_hostlist:
            if host['username'] == ish_user['username']:
                hostname = host['hostname']
        if not hostname:
            valid = False
            hostname = random.choice(self.ish_hostlist)['hostname']


        command += hostname + options + ' +p ' + ish_user['password'] + ' +l ' + ish_user['username'] + ' '

        #pick a command
        self.ish_command = random.choice(['list', 'pwd', 'dump', 'help', 'info', 'exec'])
        command += self.ish_command 
        if self.ish_command == 'dump':
            self.ish_values = [0]
            #pick an address where we know the contents
            address = 0xb7ffd004 + (random.randint(0, 1023) * 4)
            command += ' %d' % address

        self.write(command + '\n')
        if not valid:
            self.read(delim='\n', expect="Access Denied\n")
        else:
            if self.ish_command == 'list':
                self.read(delim='\n', expect='one two three key')
            elif self.ish_command == 'pwd':
                self.read(delim='\n', expect='.')
            elif self.ish_command == 'dump':
                byte = struct.unpack('<L', self.magic_page[address - 0xb7ffd004:address - 0xb7ffd004+4])[0] & 0xff000000
                self.read(length=4, expect=struct.pack('<L', byte))
            elif self.ish_command == 'help':
                self.read(delim='\n', expect='Here is no help')
            elif self.ish_command == 'info':
                self.read(delim='\n', expect='Here is no info')
            elif self.ish_command == 'exec':
                self.read(delim='\n', expect='Command not supported')

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


    def mailsend(self):
        self.read(delim=':', expect="frontdoor:")
        self.write("mailsend\n")
        self.address_book = []
        self.init_prng()
        for i in range(10):
            address = {}
            address['index'] = i + 1
            address['name'] = self.gen_random_str(5,32)
            address['home_server'] = self.gen_random_str(5,32)
            address['mode'] = self.random_in_range(0,1)
            self.address_book.append(address)
        self.mail_queues = []
        for i in range(15):
            mq = {}
            sender = self.pick_address()
            mq['name'] = sender['name']
            mq['messages'] = []
            mq['messages'].append(self.gen_random_msg())
            self.mail_queues.append(mq)

    def mailsend_read_queue(self, mq):
        i = 0
        for msg in mq['messages'][0:10]:
            self.read(delim='\n', expect='%d) From:%s To: %s SUBJECT:%s' % (i, msg['sender']['name'], msg['recipient']['name'], msg['subject']))
            i += 1

    def find_queue(self, name):
        for mq in self.mail_queues:
            if mq['name'] == name:
                return mq
        return None

    def mailsend_loop(self):
        self.count += 1
        if self.count >= 5:
            self.mailsend_quit()
            self.quit()
            return -1
    
    def mailsend_ADDRESSBOOK(self):
        self.write("ADDRESSBOOK\n")
        self.count += 3
        self.read(delim='\n', expect="Address Book:")
        for each in self.address_book:
            self.read(delim='\n', expect="%d) %s@%s [%d]" % (each['index'], each['name'], each['home_server'], each['mode']))

    def mailsend_LIST(self):
        mq = random.choice(self.mail_queues)
        self.write("LIST %s\n" % mq['name'])
        self.mailsend_read_queue(self.find_queue(mq['name']))

    def mailsend_LISTALL(self):
        self.write("LISTALL\n")
        self.count = 5
        for mq in self.mail_queues[0:10]:
            self.read(delim='\n', expect='QUEUE: %s\n' % mq['name'])
            self.mailsend_read_queue(mq)
            self.read(delim='\n')

    def mailsend_POST(self):
        msg = self.gen_random_msg()
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

    def mailsend_READ(self):
        mq = random.choice(self.mail_queues)
        mq = self.find_queue(mq['name'])
        msg_num = random.randint(0, len(mq['messages'])-1)
        self.write("READ %s %d\n" % (mq['name'], msg_num))
        self.read(delim='\n', expect="%d) Subject:%s Body:%s\n" % (msg_num, mq['messages'][msg_num]['subject'], mq['messages'][msg_num]['data']))

    def mailsend_quit(self):
        self.write("QUIT\n")
        self.read(delim='\n', expect="Goodbye.")

    def quit(self):
        self.write("quit\n")
        self.read(delim='\n', expect="frontdoor:Goodbye\n")
