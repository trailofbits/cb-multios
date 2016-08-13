#!/usr/bin/env python
#
# Copyright (C) 2014 Brian Caswell <bmc@lungetech.com>
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

import sys
import ansi_x931_aes128
import random
import string


def encode(data):
    """ Encodes a string to the 'cstring' encoding supported by the replay DTD.

    Args:
        data: string value to be encoded

    Returns:
        String containing the encoded value

    Raises:
        None
    """
    chars = string.letters + string.digits + " ?!:."
    return ''.join([x if x in chars else "\\x%02x" % ord(x) for x in data])


class Variable(object):
    def __init__(self, name):
        assert name.isalnum()

        self._name = name
        self._method = None
        self._begin = None
        self._end = None
        self._re = None
        self._value = None

    def set_value(self, value):
        """ Sets the 'Variable' value, useful for Actions.set().

        Args:
            value: Specify data that should be set in the 'var' instance,
                as specified by the DTD.

        Returns:
           None

        Raises:
            Exception if value is not a string
        """
        assert isinstance(value, str)
        self._value = value
        self._method = 'value'

    def set_re(self, value, group=None):
        """ Sets the 'Variable' value to be a regular expression

        Args:
            value: Specify the regular expression used in an 'assign' instance,
                as specified by the DTD.

        Returns:
           None

        Raises:
            Exception if value is not a string
            Exception if value is empty
        """
        assert isinstance(value, str)
        assert len(value)
        if group is not None:
            assert isinstance(group, int)
        else:
            group = 0
        self._re = value
        self._re_group = group
        self._method = 're'

    def set_slice(self, begin, end=None):
        """ Sets the 'Variable' value to be a slice

        Args:
            value: Specify the slice used in an 'assign' instance, as specified
            by the DTD.

        Returns:
           None

        Raises:
            Exception if begin is not an integer
            Exception if end is not None or an integer
        """
        assert isinstance(begin, int)
        assert isinstance(end, (type(None), int))
        self._method = 'slice'

        self._begin = begin
        self._end = end

    def get_read(self):
        """ Get the 'assign' XML element

        Args:
            None

        Returns:
            String defining the '<assign>' XML element

        Raises:
            Exception if the method has not been defined as 're' or 'slice'
        """
        # <assign> <var>foo</var> <slice begin="1" end="10" /> </assign>
        # <assign> <var>bar</var> <pcre>(.*)</pcre> </assign>
        assert self._method in ['re', 'slice']

        xml = ''
        if self._method == 'slice':
            if self._end is None:
                xml = '<slice begin="%d" />' % (self._begin)
            else:
                xml = '<slice begin="%d" end="%d" />' % (self._begin, self._end
                                                         )
        elif self._method == 're':
            if self._re_group != 0:
                xml = '<pcre group="%d">%s</pcre>' % (self._re_group, self._re)
            else:
                xml = '<pcre>%s</pcre>' % (self._re)

        return '<assign> <var>%s</var> %s </assign>' % (self._name, xml)

    def get_set(self):
        """ Get the 'decl' XML element

        Args:
            None

        Returns:
            String defining the '<decl>' XML element

        Raises:
            Exception if the method has not been defined as 'value'
        """
        assert self._method == 'value'
        return '<decl> <var>%s</var> <value> <data>%s</data> '\
               '</value> </decl>' % (self._name, encode(self._value))

    def get_write(self):
        """ Get the XML element that defines writing the variable

        Args:
            None

        Returns:
            String defining the '<var>' XML element

        Raises:
            None
        """
        assert self._method is not None
        return '<var>%s</var>' % (self._name)


class Actions(object):
    """Actions - Define the interactions for a CB

    This class implements the basic methods to interact with a CB, in terms of
    XML generation for use with 'cb-replay'.

    Usage:
        a = Actions():
        a.write('foo')
        a.read(delim='\n')
        a.xml()

    Attributes:
        state: Dict of state values, to be reset upon each iteration.
        used_magic_page: Has the magic page been used
    """

    def __init__(self):
        self._actions = []
        self.state = {}

        self._seed = None
        self._magic_page = None
        self.used_magic_page = False
        self._matched = False
        self._sent = False
        self._recv = False

    @property
    def magic_page(self):
        if not self.used_magic_page:
            self.used_magic_page = True
            self._seed = self.random_buffer(48)
            prng = ansi_x931_aes128.PRNG(self._seed)
            self._magic_page = prng.get(0x1000)
        return self._magic_page

    @classmethod
    def chance(cls, value=0.5):
        """ Randomly return True or False, with the likelyhood defined by
        specifying a percentage argument.

        Args:
            value: A float between 0.0 and 1.0

        Returns:
            True or False

        Raises:
            Exception: if 'value' is not a float between 0.0 and 1.0
        """
        assert isinstance(value, float)
        assert value > 0.0 and value < 1.0
        return random.random() < value

    @staticmethod
    def random_buffer(size, chars=None):
        """ Create a buffer of random data of a length specified by the the
        size argument.
        
        Args:
            size: Size of buffer to create
            chars: Optional sequence of characters (If none is provided, all characters are used)

        Raises:
            None
        """

        if chars is None:
            chars = ''.join([chr(x) for x in range(256)])

        return ''.join(random.choice(chars) for _ in range(size))

    def reset(self):
        """ Re-initialize the instance of the class

        Args:
            None

        Returns:
           None

        Raises:
            None
        """
        self.__init__()

    def xml(self, store_seed=None):
        """ Returns the XML of the existing actions following the replay.dtd
        spec

        Args:
            store_xml: Should the seed be stored in the XML

        Returns:
           String containing XML of the existing actions

        Raises:
            None
        """
        lines = [
            '<?xml version="1.0" standalone="no" ?>',
            '<!DOCTYPE pov SYSTEM "/usr/share/cgc-docs/replay.dtd">'
        ]
        out = '\n'
        actions = '\n    ' + '\n    '.join(self._actions) + '\n'
        out += self._wrap('cbid', 'service') + '\n'
        assert self._matched, 'polls must match or assign content from the server'
        assert self._sent, 'polls must send data to the server'
        assert self._recv, 'polls must recv data from the server'
        if store_seed:
            seed = self._seed
            if seed is None:
                seed = self.random_buffer(48)
            out += self._wrap('seed', seed.encode('hex')) + '\n'
        out += self._wrap('replay', actions) + '\n'
        lines.append(self._wrap('pov', out))
        return '\n'.join(lines)

    @classmethod
    def _wrap(cls, tag, value, **options):
        """ Creates an XML eliment

        Args:
            tag: The tag name
            value: The value of the tag
            **options: arbitrary named arguments, used as attributes for the
                tag

        Returns:
           String containing XML element

        Raises:
            None
        """
        opt_string = ''

        if len(options):
            opts = []
            for key in options:
                opts.append('%s="%s"' % (key, options[key]))
            opt_string = ' ' + ' '.join(opts)
        return '<%s%s>%s</%s>' % (tag, opt_string, value, tag)

    def read(self,
             delim=None,
             length=None,
             expect=None,
             expect_format=None,
             timeout=None,
             assign=None):
        """ Create a 'read' interaction for a challenge binary as supported by
        the replay DTD.

        Args:
            delim: Specify data should be read until the string has been
                received from the CB
            length: Specify the amount of data to be read from the CB.
            expect: Specify the expected value that should be returned from the
                CB
            expect_format: Specify the format of the 'expect' value, allowed
                values are 'pcre', 'asciic', or 'variable'.  Unless a value is
                specified, the default format is 'asciic'.
            assign: An optional 'Variable' instance used to specify XML
                'assign' arguments.

        Returns:
           None

        Raises:
            Exception if delim AND length are specified
            Exception if expect_format is specified and expect is not specified
            Exception if expect_format is not 'pcre' or 'asciic'
            Exception if timeout is not an integer
            Exception if length is not an integer
            Exception if the delimiter is not a string
            Exception if the delimiter is an empty string
            Exception if assign is set and is not a 'Variable' instance
        """
        assert length is not None or delim is not None
        if expect_format is not None:
            assert expect is not None
            assert expect_format in ['pcre', 'asciic', 'variable']

        xml = ''

        if timeout is not None:
            assert isinstance(timeout, int)
            xml += self._wrap('timeout', str(timeout))

        if length is not None:
            assert isinstance(length, int)
            assert length > 0
            xml += self._wrap('length', str(length))

        if delim is not None:
            assert isinstance(delim, str)
            assert len(delim) > 0
            delim = encode(delim)
            xml += self._wrap('delim', delim)

        if expect is not None:
            match = None
            if expect_format == 'variable':
                assert isinstance(expect, Variable)
                match = expect.get_write()
            elif expect_format == 'pcre':
                match = self._wrap('pcre', expect)
            else:
                match = self._wrap('data', encode(expect))
            xml += self._wrap('match', match)
            self._matched = True

        if assign is not None:
            assert isinstance(assign, Variable)
            xml += assign.get_read()
            self._matched = True

        self._recv = True
        xml = self._wrap('read', xml)
        self._actions.append(xml)

    def comment(self, msg, *args):
        """ Create an XML comment of 'msg % args'

        Args:
            msg: Message to be logged
            args: Arguments to be interpreted via str formatting

        Returns
            None

        Raises:
            None
        """
        data = '<!-- %s -->' % encode(msg % args)
        self._actions.append(data)

    def delay(self, value):
        """ Create a 'delay' element, to cause a sleep in the interaction with
        the challenge binary, as supported by the replay DTD.

        Args:
            value: An integer to specify how much to sleep

        Returns
            None

        Raises:
            Exception: if value is not a number greater than zero
        """

        assert isinstance(value, int)
        assert value >= 0

        self._actions.append(self._wrap('delay', '%d' % value))

    def set(self, value):
        """ Declare a variable as supported by the replay DTD.

        Args:
            value: A Variable instance

        Returns
            None

        Raises:
            Exception: if value is not an instance of Variable
        """

        assert isinstance(value, Variable)
        self._actions.append(value.get_set())

    def write(self, *values):
        """ Create a 'write' interaction for a challenge binary as supported by
        the replay DTD.

        Args:
            values: Specify the data that should be sent to the CB.

        Returns
            None

        Raises:
            None
        """

        xml = []
        for value in values:
            if isinstance(value, Variable):
                xml.append(value.get_write())
            else:
                xml.append(self._wrap('data', encode(value)))
        self._sent = True
        self._actions.append(self._wrap('write', ''.join(xml)))
