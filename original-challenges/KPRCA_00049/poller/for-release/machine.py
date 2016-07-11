#!/usr/bin/env python
from generator.actions import Actions

import random
import string

words = [
    "the", "of", "and", "to", "a", "in", "that", "is", "was", "he", "for", "it",
    "with", "as", "his", "on", "be", "at", "by", "i", "this", "had", "not",
    "are", "but", "from", "or", "have", "an", "they", "which", "one", "you",
    "were", "her", "all", "she", "there", "would", "their", "we", "him", "been",
    "has", "when", "who", "will", "more", "no", "if", "out", "so", "said",
    "what", "up", "its", "about", "into", "than", "them", "can", "only",
    "other", "new", "some", "could", "time", "these", "two", "may", "then",
    "do", "first", "any", "my", "now", "such", "like", "our", "over", "man",
    "me", "even", "most", "made", "after", "also", "did", "many", "before",
    "must", "through", "back", "years", "where", "much", "your", "way", "well",
    "down", "should", "because", "each", "just", "those", "people", "mr", "how",
    "too", "little", "state", "good", "very", "make", "world", "still", "own",
    "see", "men", "work", "long", "get", "here", "between", "both", "life",
    "being", "under", "never", "day", "same", "another", "know", "while",
    "last", "might", "us", "great", "old", "year", "off", "come", "since",
    "against", "go", "came", "right", "used", "take", "three"
]


def rs(n=16, with_ws=False, space=None):
    space = space[:]

    if not space:
        space = string.letters

    if with_ws:
        if isinstance(space, str):
            space += " \t"
        elif isinstance(space, list):
            space += [" ", "\t"]

    return ''.join([random.choice(space) for _ in xrange(1, n + 1)])


def rls(_min=4, _max=12, **kwargs):
    return rs(random.choice(xrange(_min, _max + 1)), **kwargs)


class Machine(Actions):
    def read_to_newline(self, s):
        self.read(expect=s + '\n', delim='\n')

    def read_prompt(self):
        self.read(expect="nk9001> ", delim=' ')

    def start(self):
        self.nmax = 512
        self.state['store'] = {}

    def choose(self):
        pass

    def junk(self):
        self.read_prompt()
        self.write(rls(space=words) + '\n')
        self.read_to_newline(
            "I don't know what you want, but you can't find it here."
        )

    def get(self):
        self.read_prompt()

        if not self.state['store'] or self.chance(0.03):
            title = rls(space=words)
        else:
            title = random.choice(self.state['store'].keys())

        self.write("get-note {}\n".format(title))
        if title in self.state['store']:
            self.read_to_newline(self.state['store'][title])
        else:
            self.read_to_newline("Unknown note.")

    def new(self):
        self.read_prompt()

        if len(self.state['store']) >= self.nmax:
            self.read_to_newline("Your note book is full.")
            return

        if self.chance(0.03) and self.state['store']:
            title = random.choice(self.state['store'].keys())
        else:
            title = rls(space=words)

        content = rls(space=words, with_ws=True)

        self.write("new-note {} {}\n".format(title, content))
        if title in self.state['store']:
            self.read_to_newline("Your note book is full.")
        else:
            self.state['store'][title] = content
            self.read_to_newline("Note successfully created.")

    def append(self):
        self.read_prompt()

        if not self.state['store'] or self.chance(0.03):
            title = rls(space=words)
        else:
            title = random.choice(self.state['store'].keys())

        content = rls(space=words, with_ws=True)

        if title in self.state['store']:
            self.state['store'][title] += content

        self.write("append-note {} {}\n".format(title, content))
        self.read_to_newline("Note successfully appended.")

    def delete(self):
        self.read_prompt()

        if not self.state['store'] or self.chance(0.03):
            title = rls(space=words)
        else:
            title = random.choice(self.state['store'].keys())

        self.state['store'].pop(title, None)

        self.write("delete-note {}\n".format(title))
        self.read_to_newline("Note successfully deleted.")

    def quit(self):
        self.read_prompt()
        self.write("quit\n")
