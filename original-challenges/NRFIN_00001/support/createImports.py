#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

JOKE_FILE = 'chuckNorrisJokes_list_orig.csv'

def print_jokes(joke_list):
  for (length, joke) in joke_list:
    print("insert_joke(jokedb, \"{0}\");".format(joke))

def print_max_joke_length(joke_list):
  max_len = 0;
  for (length, joke) in joke_list:
    if length > max_len:
      max_len = length
  print("The longest joke is {0} chars.\n".format(max_len))

def print_jokes_comma_separated(joke_list):
  for (length, joke) in joke_list:
    print("    {0},".format(joke))


def main():
  jokes = []

  with open(JOKE_FILE, 'r') as f:
    for line in f:
      l = line.replace('\n', '')
      jokes.append( (len(l), l ) )

  # print_max_joke_length(jokes)
  print_jokes(jokes)
  # print_jokes_comma_separated(jokes)

if __name__ == "__main__":
  main()

