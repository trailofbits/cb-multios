#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
from collections import OrderedDict

MAX_MEMO_SUBJECT = 32
MAX_MEMO_BODY = 4096
MAX_MEMO_ID = 500
MAX_AC_LEN = 32
MAX_AC_LIST = 100

def random_string_n(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(size)])

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

def random_body_string(words):
  s = ''
  while (len(s) < MAX_MEMO_BODY):
    if len(s) != 0 and random.randint(1, 100) <= 10:
      break
    if random.randint(1, 100) <= 20:
      s += random.choice(words)[0]
    else:
      s += random_string()
    s += ' '
  return s if len(s) < MAX_MEMO_BODY else s[:MAX_MEMO_BODY]

def random_digits(size=20):
  return ''.join([random.choice(string.digits) for x in xrange(random.randint(1,size))])

class AMMM(Actions):
  def ac_init(self):
    self.state['ac_word_list'] = [
        ("acceptible", "acceptable"), ("amature", "amateur"),
        ("arguement", "argument"), ("beleive", "believe"),
        ("calender", "calendar"), ("cemetary", "cemetery"),
        ("collectable", "collectible"), ("concensus", "consensus"),
        ("equiptment", "equipment"), ("existance", "existence"),
        ("firey", "fiery"), ("foriegn", "foreign"),
        ("guage", "gauge"), ("greatful", "grateful"),
        ("harrass", "harass"), ("ignorence", "ignorance"),
        ("lisense", "license"), ("maintenence", "maintenance"),
        ("relevent", "relevant"), ("wierd", "weird"),
        ]

  def start(self):
    self.state['g_memo_ids'] = list(0 for i in xrange(MAX_MEMO_ID))
    self.state['ac_word_list'] = []
    self.state['memos'] = []

    self.ac_init()

    banner_str = "====== 3M v0.2 ======\n"
    self.read(length=len(banner_str), expect=banner_str)
    menu_str = "======================\n" + \
        " 1. New memo\n" + " 2. View memo\n" + \
        " 3. Update memo\n" + " 4. Delete memo\n" + \
        " 5. Add custom AC word\n" + " 6. Quit\n" + \
        "======================\n"
    self.read(length=len(menu_str), expect=menu_str)

  def commands(self):
    pass

  def cmd_new(self):
    self.write('1\n')
    self.read(length=len('subject? '), expect='subject? ')
    subject = random_string(MAX_MEMO_SUBJECT - 1)
    self.write(subject + '\n')
    self.read(length=len('year? '), expect='year? ')
    year = random.randint(1970, 2500)
    self.write('%d\n' % year)
    self.read(length=len('month? '), expect='month? ')
    month = random.randint(1, 12)
    self.write('%d\n' % month)
    self.read(length=len('date? '), expect='date? ')
    date = random.randint(1, 31)
    self.write('%d\n' % date)
    self.read(length=len('priority? '), expect='priority? ')
    priority = random.randint(0, 2)
    self.write('%d\n' % priority)
    self.read(length=len('body? '), expect='body? ')
    body = random_body_string(self.state['ac_word_list'])
    self.write(body + '\n')

    words = body.split(' ')
    body = ''
    for w in words:
      for (t,c) in self.state['ac_word_list']:
        if w == t:
          w = c
          break
      body += w + ' '
    body = body[:-1]
    memo_id = -1
    for i in xrange(MAX_MEMO_ID):
      if self.state['g_memo_ids'][i] == 0:
        memo_id = i
        break
    if memo_id == -1:
      return
    memo = (memo_id, subject, year, month, date, priority, body)
    self.state['g_memo_ids'][memo_id] = 1
    self.state['memos'].append(memo)
    s = 'id: %d created.\n' % memo_id
    self.read(length=len(s), expect=s)

  def cmd_view(self):
    self.write('2\n')
    self.read(length=len('id? '), expect='id? ')
    if len(self.state['memos']) == 0:
      self.write('%d\n' % random.randint(0, MAX_MEMO_ID))
      return
    memo = random.choice(self.state['memos'])
    self.write('%d\n' % memo[0])
    s = '[%d] %s\n' % (memo[0], memo[1])
    self.read(length=len(s), expect=s)
    s = 'Date: %04d-%02d-%02d\n' % (memo[2], memo[3], memo[4])
    self.read(length=len(s), expect=s)
    s = 'Priority: '
    if memo[5] == 0:
      s += '*__ (Low)\n'
    elif memo[5] == 1:
      s += '**_ (Normal)\n'
    elif memo[5] == 2:
      s += '*** (High)\n'
    self.read(length=len(s), expect=s)
    s = '------------------------------\n'
    self.read(length=len(s), expect=s)
    s = ''
    for i in xrange(len(memo[6])):
      if i % 29 == 0:
        s += '\n'
      s += memo[6][i]
    s += '\n'
    self.read(length=len(s), expect=s)

  def cmd_update(self):
    self.write('3\n')
    self.read(length=len('id? '), expect='id? ')
    if len(self.state['memos']) == 0:
      self.write('%d\n' % random.randint(0, MAX_MEMO_ID))
      return
    memo = random.choice(self.state['memos'])
    self.write('%d\n' % memo[0])
    self.state['memos'].remove(memo)

    self.read(length=len('subject? '), expect='subject? ')
    if random.randint(1, 100) <= 70:
      subject = random_string(MAX_MEMO_SUBJECT - 1)
      self.write(subject + '\n')
    else:
      subject = memo[1]
      self.write('\n')
    self.read(length=len('year? '), expect='year? ')
    if random.randint(1, 100) <= 70:
      year = random.randint(1970, 2500)
      self.write('%d\n' % year)
    else:
      year = memo[2]
      self.write('\n')
    self.read(length=len('month? '), expect='month? ')
    if random.randint(1, 100) <= 70:
      month = random.randint(1, 12)
      self.write('%d\n' % month)
    else:
      month = memo[3]
      self.write('\n')
    self.read(length=len('date? '), expect='date? ')
    if random.randint(1, 100) <= 70:
      date = random.randint(1, 31)
      self.write('%d\n' % date)
    else:
      date = memo[4]
      self.write('\n')
    self.read(length=len('priority? '), expect='priority? ')
    if random.randint(1, 100) <= 70:
      priority = random.randint(0, 2)
      self.write('%d\n' % priority)
    else:
      priority = memo[5]
      self.write('\n')
    self.read(length=len('body? '), expect='body? ')
    if random.randint(1, 100) <= 70:
      body = random_body_string(self.state['ac_word_list'])
      self.write(body + '\n')

      #for (t,c) in self.state['ac_word_list']:
      #  body = body.replace(t, c)
    else:
      body = memo[6]
      self.write('\n')

    memo = (memo[0], subject, year, month, date, priority, body)
    self.state['memos'].append(memo)

  def cmd_delete(self):
    self.write('4\n')
    self.read(length=len('id? '), expect='id? ')
    if len(self.state['memos']) == 0:
      self.write('%d\n' % random.randint(0, MAX_MEMO_ID))
      return
    memo = random.choice(self.state['memos'])
    self.write('%d\n' % memo[0])
    self.state['memos'].remove(memo)
    self.state['g_memo_ids'][memo[0]] = 0

  def cmd_add_ac(self):
    self.write('5\n')
    self.read(length=len('typo? '), expect='typo? ')
    typo = random_string(MAX_AC_LEN - 1)
    self.write(typo + '\n')
    self.read(length=len('correct? '), expect='correct? ')
    correct = random_string(len(typo))
    self.write(correct + '\n')

    if len(self.state['ac_word_list']) >= MAX_AC_LIST:
      return

    typos = [x for (x,y) in self.state['ac_word_list']]
    if typo in typos:
      return
    self.state['ac_word_list'].append((typo, correct))

  def quit(self):
    self.write('6\n')
    self.read(length=len('bye!\n'), expect='bye!\n')
