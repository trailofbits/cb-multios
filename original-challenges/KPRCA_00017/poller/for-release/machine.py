#!/usr/bin/env python

from generator.actions import Actions
import random
import subprocess
import string
import struct

p = lambda f,x: struct.pack(f,x)

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class HackMan(Actions):
  def start(self):
    welcome_str = '\nWelcome to HackMan v13.37\n\n'
    self.read(length=len(welcome_str), expect=welcome_str)
    self.state['win'] = False
    self.state['total'] = 0
    self.state['words'] = [
        'leonite', 'drawdown', 'conuzor', 'franklin', 'married',
        'excircle', 'solidness', 'aneuria', 'constablery', 'infractible',
        'speedingly', 'scantlinged', 'presphenoid', 'diphyozooid', 'twistiways',
        'didrachma', 'fa', 'gyte', 'emblazonry', 'insulize'
    ]
    self.state['word'] = ''
    self.state['progress'] = ''
    self.state['num_tries'] = 0
    self.stop = random.randint(0, 10)
    self.done = False

  def record_winner(self):
    goodwork_str = '###### Good Work! ######\n' + \
                   '# Leave your comment!! #\n' + \
                   '########################\n' + \
                   'Comment: '
    self.read(length=len(goodwork_str), expect=goodwork_str)
    comment = random_string(random.randint(1,500))
    self.write(comment + '\n')
    comment_str = 'You wrote: %s\n' % comment
    self.read(length=len(comment_str), expect=comment_str)
    self.state['total'] += 1
    self.state['win'] = False
    self.new_challenge()

  def banner(self):
    banner_str = '_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n' + \
                 '_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n' + \
                 '     Sh41l w3 p14y a g4m3?\n' + \
                 '_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n' +\
                 '_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n\n'
    self.read(length=len(banner_str), expect=banner_str)
    self.state['word'] = ''
    self.state['progress'] = ''

  def quit_game(self):
    quit_str = '\n * * * * Thank you for playing! You\'ve won %d times! * * * *\n' % self.state['total']
    self.read(length=len(quit_str), expect=quit_str)
    self.done = True

  def new_challenge(self):
    self.read(length=len('\n@ @ @ @ @  New Challenge  @ @ @ @ @\nSeed? '), expect='\n@ @ @ @ @  New Challenge  @ @ @ @ @\nSeed? ')
    seed = random.randint(0, 2147483647)
    self.write('%d\n' % seed)
    lfsr = ((seed & 0x00FF0000) >> 16) | ((seed & 0x000000FF) << 8)
    if lfsr == 0:
      lfsr = 0xACE1;
    num = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1
    num = (lfsr >> 1) | (num << 15)
    self.state['word'] = self.state['words'][num % 20]
    self.state['progress'] = '_' * len(self.state['word'])
    self.state['num_tries'] = 0

  def play_game(self):
    while not self.done and not self.state['win']:
      if self.state['win'] or len(self.state['word']) == 0:
        self.new_challenge()
        self.state['win'] = False
        continue
      else:
        challenge_str = '[[[ Your challenge: %s ]]]\n' % self.state['progress']
        challenge_str += 'Guess a letter: '
        self.read(length=len(challenge_str), expect=challenge_str)

      # NEW_CHALLENGE
      if self.chance(0.10):
        self.write('+\n')
        self.new_challenge()
        self.state['win'] = False
      # RESET
      elif self.chance(0.10):
        self.write('?\n')
        self.state['num_tries'] = 0
        self.state['progress'] = '_' * len(self.state['word'])
        self.read(length=len('\n^^^^^ RESET ^^^^^\n\n'), expect='\n^^^^^ RESET ^^^^^\n\n')
      # GUESS
      else:
        self.state['num_tries'] += 1;
        if self.chance(0.20):
          bad = list()
          for c in string.ascii_lowercase:
            if c not in self.state['word']:
              bad.append(c)
          self.write('%s\n' % random.choice(bad))
        else:
          for c in string.ascii_lowercase:
            if c in self.state['word'] and c not in self.state['progress']:
              self.write('%s\n' % c)
              new_progress = ''
              for i in xrange(len(self.state['word'])):
                if self.state['word'][i] == c:
                  new_progress += c
                else:
                  new_progress += self.state['progress'][i]
              self.state['progress'] = new_progress
              if '_' not in self.state['progress']:
                got_str = '>>> You got it!! \"%s\" (%d tries) <<<\n' % (self.state['word'], self.state['num_tries'])
                self.read(length=len(got_str), expect=got_str)
                self.state['win'] = True
              break
      # QUIT
      if self.state['total'] == self.stop:
        challenge_str = '[[[ Your challenge: %s ]]]\n' % self.state['progress']
        challenge_str += 'Guess a letter: '
        self.read(length=len(challenge_str), expect=challenge_str)
        self.write('/\n')
        self.quit_game()

  def doit(self):
    while not self.done:
      if self.state['win']:
        self.record_winner()
      else:
        self.banner()
      self.play_game()
