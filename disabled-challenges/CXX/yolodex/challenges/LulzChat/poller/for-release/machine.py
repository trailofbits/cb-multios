#!/usr/bin/env python

from generator.actions import Actions
import random
import subprocess
import string
import struct

MAX_NUM_MSG = 100
MAX_NUM_USERS = 999
TYPE_PROTECTED = 1
TYPE_NORMAL = 0

p = lambda f,x: struct.pack(f,x)

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class LulzChat(Actions):
  def start(self):
    self.user_id = 1
    self.state['users'] = list()
    self.state['messages'] = list()
    self.state['current_user'] = None

    welcome_str = "[INFO] LulzChat Client v0.1\n[INFO] Type 'h' for help menu\n"
    self.read(length=len(welcome_str), expect=welcome_str)

  def menu(self):
    self.read(length=2, expect='> ')

  def help(self):
    help_str = "---- Commands --------------------\n" + \
               " 'h'elp - display this help menu\n" +   \
               " 'r'egister - register a user\n" +      \
               " 'l'ogin - login\n" +                   \
               " 'o'ut - logout\n" +                    \
               " 'e'numerate - list messages\n" +       \
               " 'v'iew - view a message\n" +           \
               " 's'end - send a message\n" +           \
               " 'd'elete - delete a message\n" +       \
               " 'q'uit - quit\n" +                     \
               "----------------------------------\n"
    if self.chance(0.25):
      self.write('h\n')
    elif self.chance(0.25):
      self.write('H\n')
    elif self.chance(0.25):
      self.write('help\n')
    else:
      self.write('HELP\n')
    self.read(length=len(help_str), expect=help_str);

  def register(self):
    if self.chance(0.25):
      self.write('r\n')
    elif self.chance(0.25):
      self.write('R\n')
    elif self.chance(0.25):
      self.write('register\n')
    else:
      self.write('REGISTER\n')

    username = random_string(random.randint(1,63))
    password = random_string(random.randint(1,63))

    self.read(length=len('\n[[[ REGISTER ]]]\n'), expect='\n[[[ REGISTER ]]]\n')
    self.read(length=len('- username: '), expect='- username: ')
    self.write(username + '\n')
    self.read(length=len('- password: '), expect='- password: ')
    self.write(password + '\n')
    self.read(length=len('- password confirm: '), expect='- password confirm: ')
    self.write(password + '\n')
    self.read(length=1, expect='\n')

    # server logic
    if any(user['username'] == username for user in self.state['users']):
      self.read(length=len('[ERROR] Username already exists.\n'), expect='[ERROR] Username already exists.\n')
      return
    if len(self.state['users']) == MAX_NUM_USERS:
      self.read(length=len('[ERROR] Registration Failed..\n'), expect='[ERROR] Registration Failed..\n')
      return

    self.read(length=len('[INFO] Registration Successful! (%s)\n' % username), expect='[INFO] Registration Successful! (%s)\n' % username)
    self.state['users'].append({'username': username, 'password': password, 'user_id': self.user_id})
    self.user_id += 1

  def login(self):
    in_db = False
    user = None
    if self.chance(0.25):
      self.write('l\n')
    elif self.chance(0.25):
      self.write('L\n')
    elif self.chance(0.25):
      self.write('login\n')
    else:
      self.write('LOGIN\n')

    if self.chance(0.10) or len(self.state['users']) == 0:
      username = random_string(random.randint(1,63))
      password = random_string(random.randint(1,63))
    else:
      user = random.choice(self.state['users'])
      username = user['username']
      password = user['password']
      in_db = True
    self.read(length=len('\n[[[ LOGIN ]]]\n'), expect='\n[[[ LOGIN ]]]\n')
    self.read(length=len('- username: '), expect='- username: ')
    self.write(username + '\n')
    self.read(length=len('- password: '), expect='- password: ')
    self.write(password + '\n')

    # server logic
    if in_db:
      self.read(length=len('[INFO] Login Successful!\n'), expect='[INFO] Login Successful!\n')
      if self.state['current_user'] != None:
        self.read(length=len('[INFO] Successfully logged out.\n'), expect='[INFO] Successfully logged out.\n')
      self.state['current_user'] = user
    else:
      self.read(length=len('[ERROR] Login Failed.\n'), expect='[ERROR] Login Failed.\n')

  def logout(self):
    if self.chance(0.25):
      self.write('o\n')
    elif self.chance(0.25):
      self.write('O\n')
    elif self.chance(0.25):
      self.write('out\n')
    else:
      self.write('OUT\n')

    if self.state['current_user']:
      self.read(length=len('[INFO] Successfully logged out.\n'), expect='[INFO] Successfully logged out.\n')
      self.state['current_user'] = None
    else:
      self.read(length=len('[ERROR] Not logged in.\n'), expect='[ERROR] Not logged in.\n')

  def list(self):
    if self.chance(0.25):
      self.write('e\n')
    elif self.chance(0.25):
      self.write('E\n')
    elif self.chance(0.25):
      self.write('enumerate\n')
    else:
      self.write('ENUMERATE\n')

    if self.state['current_user'] == None:
      self.read(length=len('[ERROR] Login first, please.\n'), expect='[ERROR] Login first, please.\n')
      return

    self.read(length=len('\n[[[ MESSAGES ]]]\n'), expect='\n[[[ MESSAGES ]]]\n')
    self.read(length=len('idx. <from_id, length, type>\n'), expect='idx. <from_id, length, type>\n')
    self.read(length=len('----------------------------\n'), expect='----------------------------\n')
    tmp_list =  filter(lambda m: m['to_id'] == self.state['current_user']['user_id'], self.state['messages'])

    for i in xrange(min(len(tmp_list), MAX_NUM_MSG)):
      m = tmp_list[i]
      if (m['type'] == TYPE_PROTECTED):
        es = '%d. <%d, N/A, Protected>\n' % (i+1, m['from_id'])
      else:
        es = '%d. <%d, %d bytes, Normal>\n' % (i+1, m['from_id'], m['text_len'])
      self.read(length=len(es), expect=es)
    ts = 'Total %d message(s).\n\n' % len(tmp_list)
    self.read(length=len(ts), expect=ts)

  def view(self):
    if self.chance(0.25):
      self.write('v\n')
    elif self.chance(0.25):
      self.write('V\n')
    elif self.chance(0.25):
      self.write('view\n')
    else:
      self.write('VIEW\n')

    if self.state['current_user'] == None:
      self.read(length=len('[ERROR] Login first, please.\n'), expect='[ERROR] Login first, please.\n')
      return

    self.read(length=len('\n[[[ MESSAGES ]]]\n'), expect='\n[[[ MESSAGES ]]]\n')
    self.read(length=len('idx. <from_id, length, type>\n'), expect='idx. <from_id, length, type>\n')
    self.read(length=len('----------------------------\n'), expect='----------------------------\n')
    tmp_list =  filter(lambda m: m['to_id'] == self.state['current_user']['user_id'], self.state['messages'])

    for i in xrange(min(len(tmp_list), MAX_NUM_MSG)):
      m = tmp_list[i]
      if (m['type'] == TYPE_PROTECTED):
        es = '%d. <%d, N/A, Protected>\n' % (i+1, m['from_id'])
      else:
        es = '%d. <%d, %d bytes, Normal>\n' % (i+1, m['from_id'], m['text_len'])
      self.read(length=len(es), expect=es)
    ts = 'Total %d message(s).\n\n' % len(tmp_list)
    self.read(length=len(ts), expect=ts)

    if len(tmp_list) == 0:
      self.read(length=len('[INFO] You have no message.\n'), expect='[INFO] You have no message.\n')
      return

    self.read(length=len('Select idx > '), expect='Select idx > ')
    select = random.randint(1, len(tmp_list))
    self.write('%d\n' % select)
    self.read(length=1, expect='\n')

    m = tmp_list[select - 1]
    fs = 'From: USER_%d\n' % m['from_id']
    self.read(length=len(fs), expect=fs)
    ts = 'Type: %s\n' % ('Protected' if m['type'] == TYPE_PROTECTED else 'Normal')
    self.read(length=len(ts), expect=ts)
    ls = 'Length: %d byte(s)\n' % len(m['text'])
    self.read(length=len(ls), expect=ls)
    ms = 'Message: %s\n' % m['text']
    self.read(length=len(ms), expect=ms)

  def send(self):
    in_db = False
    if self.chance(0.25):
      self.write('s\n')
    elif self.chance(0.25):
      self.write('S\n')
    elif self.chance(0.25):
      self.write('send\n')
    else:
      self.write('SEND\n')

    if self.state['current_user'] == None:
      self.read(length=len('[ERROR] Login first, please.\n'), expect='[ERROR] Login first, please.\n')
      return

    self.read(length=len('\n[[[ SEND ]]]\n'), expect='\n[[[ SEND ]]]\n')
    self.read(length=len(' - To: '), expect=' - To: ')

    if self.chance(0.10) or len(self.state['users']) == 0:
      target = random_string(random.randint(1, 63))
    else:
      user = random.choice(self.state['users'])
      target = user['username']
      in_db = True
    self.write(target + '\n')

    self.read(length=len(' - Type (0: normal, 1: protected): '), expect=' - Type (0: normal, 1: protected): ')
    if self.chance(0.50):
      t = TYPE_PROTECTED
    else:
      t = TYPE_NORMAL
    self.write('%d\n' % t)

    self.read(length=len(' - Message: '), expect=' - Message: ')
    msg = random_string(random.randint(1, 511))
    self.write(msg + '\n')
    self.read(length=1, expect='\n')

    to_id = 0
    for u in self.state['users']:
      if u['username'] == target:
        to_id = u['user_id']
        break
    from_id = self.state['current_user']['user_id']
    if to_id == 0:
      self.read(length=len('[ERROR] Send Failed.\n'), expect='[ERROR] Send Failed.\n')
      return
    self.state['messages'].append({'type': t, 'to_id': to_id, 'from_id': from_id, 'text_len': len(msg), 'text': msg})

  def delete(self):
    if self.chance(0.25):
      self.write('d\n')
    elif self.chance(0.25):
      self.write('D\n')
    elif self.chance(0.25):
      self.write('delete\n')
    else:
      self.write('DELETE\n')

    if self.state['current_user'] == None:
      self.read(length=len('[ERROR] Login first, please.\n'), expect='[ERROR] Login first, please.\n')
      return

    self.read(length=len('\n[[[ MESSAGES ]]]\n'), expect='\n[[[ MESSAGES ]]]\n')
    self.read(length=len('idx. <from_id, length, type>\n'), expect='idx. <from_id, length, type>\n')
    self.read(length=len('----------------------------\n'), expect='----------------------------\n')
    tmp_list =  filter(lambda m: m['to_id'] == self.state['current_user']['user_id'], self.state['messages'])

    for i in xrange(min(len(tmp_list), MAX_NUM_MSG)):
      m = tmp_list[i]
      if (m['type'] == TYPE_PROTECTED):
        es = '%d. <%d, N/A, Protected>\n' % (i+1, m['from_id'])
      else:
        es = '%d. <%d, %d bytes, Normal>\n' % (i+1, m['from_id'], m['text_len'])
      self.read(length=len(es), expect=es)
    ts = 'Total %d message(s).\n\n' % len(tmp_list)
    self.read(length=len(ts), expect=ts)

    if len(tmp_list) == 0:
      self.read(length=len('[INFO] You have no message.\n'), expect='[INFO] You have no message.\n')
      return

    self.read(length=len('Select idx > '), expect='Select idx > ')
    select = random.randint(1, len(tmp_list))
    self.write('%d\n' % select)
    self.read(length=1, expect='\n')

    to_remove = tmp_list[select-1]
    self.state['messages'].remove(to_remove)
    self.read(length=len('[INFO] Successfully deleted.\n'), expect='[INFO] Successfully deleted.\n')
    ns = '%d message(s) left.\n' % (len(tmp_list) - 1)
    self.read(length=len(ns), expect=ns)

  def quit(self):
    if self.chance(0.25):
      self.write('q\n')
    elif self.chance(0.25):
      self.write('Q\n')
    elif self.chance(0.25):
      self.write('quit\n')
    else:
      self.write('QUIT\n')
    self.read(length=12, expect='[INFO] Bye!\n')

