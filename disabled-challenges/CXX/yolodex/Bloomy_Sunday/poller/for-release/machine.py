#!/usr/bin/env python

from generator.actions import Actions, Variable
import random
import string
import struct
import sys
import re

DEP_WORDS = [
  "gloomy", "un-cheerful", "tragic", "depressive", "dejected", "despondent",
  "destroyed", "disconsolate", "dispirited", "down", "downcast", "downhearted",
  "dragged", "pain", "pessimistic", "sad", "unhappy", "weeping", "death",
  "fear", "ruined", "lonely", "miserable", "anxious", "torment", "agony",
  "torture", "distress", "grief", "sorrow", "pathetic", "terrified", "scared"
  ]

def random_string(size=20):
  return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class ABLOOMY(Actions):

  def start(self):
    banner_str = '~=~=~=~= Bloomy Sunday =~=~=~=~\n'
    self.read(length=len(banner_str), expect=banner_str)

    self.state['lyrics'] = ''
    self.state['good'] = False
    self.state['init'] = False

  def menu(self):
    if self.state['init']:
      self.read(length=len('\n'), expect='\n')
    self.state['init'] = True
    menu_str = '1. Submit lyrics\n'
    menu_str += '2. View lyrics\n'
    menu_str += '-3. Quit\n'
    self.read(length=len(menu_str), expect=menu_str)
    self.read(length=len('> '), expect='> ')

  def submit_lyrics(self):
    self.write('1\n')
    dep = False
    lyrics = ''
    num_words = random.randint(1, 6)
    num_lines = random.randint(1, 15)
    for i in xrange(num_lines):
      for j in xrange(num_words):
        if random.randint(1, 100) <= 5:
          lyrics += random.choice(DEP_WORDS)
          dep = True
        else:
          lyrics += random_string()
        lyrics += ' '
      lyrics = lyrics[:-1]
      lyrics += '\n'
      if dep:
        self.write(lyrics)
        s = 'depressing word detected.\n'
        self.read(length=len(s), expect=s)
        self.state['good'] = False
        return
    self.state['lyrics'] = lyrics
    lyrics += 'EOF\n'
    self.write(lyrics)
    self.state['good'] = True

  def view_lyrics(self):
    self.write('002\n')
    if not self.state['good']:
      self.read(length=len('not good.\n'), expect='not good.\n')
    else:
      self.read(length=len(self.state['lyrics']), expect=self.state['lyrics'])

  def quit(self):
    self.write('-3\n')
    bye_msg = "Don't let the sadness grow.\n\n"
    self.read(length=len(bye_msg), expect=bye_msg)

  def invalid(self):
    self.write('%d\n' % random.randint(3, 5000))
    self.read(length=len('Nope!\n'), expect='Nope!\n')
