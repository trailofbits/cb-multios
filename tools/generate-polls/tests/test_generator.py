#!/usr/bin/python

import os
import sys
import unittest
import time
import subprocess

from generator.actions import Variable, Actions


class POLL_GENERATOR(unittest.TestCase):
    def test_variable(self):
        with self.assertRaises(TypeError):
            Variable()

        with self.assertRaises(AssertionError):
            Variable('!')

        x = Variable('foo')

        # can't 'set' without defining the value to set
        with self.assertRaises(AssertionError):
            x.get_set()

        # can't 'read' without defining what to read
        with self.assertRaises(AssertionError):
            x.get_read()

        # can't 'write' until value has been set
        with self.assertRaises(AssertionError):
            x.get_write()

        with self.assertRaises(AssertionError):
            x.set_re(None)

        x.set_re('(.*)')

        self.assertEquals(x.get_read(), '<assign> <var>foo</var> '
                          '<pcre>(.*)</pcre> </assign>')

        x.set_value('hi')
        with self.assertRaises(AssertionError):
            x.get_read()

        self.assertEquals(x.get_set(), '<decl> <var>foo</var> '
                          '<value> <data>hi</data> </value> </decl>')

        with self.assertRaises(AssertionError):
            x.set_slice("1")

        with self.assertRaises(AssertionError):
            x.set_slice(0, "1")

        x.set_slice(0)
        self.assertEquals(x.get_read(), '<assign> <var>foo</var> <slice '
                          'begin="0" /> </assign>')

        x.set_slice(1, 2)
        self.assertEquals(x.get_read(), '<assign> <var>foo</var> <slice '
                          'begin="1" end="2" /> </assign>')

        self.assertEquals(x.get_write(), '<var>foo</var>')

    def test_actions(self):
        Variable
        a = Actions()
        a.write('foo')


if __name__ == '__main__':
    unittest.main()
