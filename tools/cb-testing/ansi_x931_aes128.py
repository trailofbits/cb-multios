#!/usr/bin/env python

"""
A Python implementation of ANSI X9.31 using AES 128, following:

http://csrc.nist.gov/groups/STM/cavp/documents/rng/931rngext.pdf

Copyright (C) 2015 - Brian Caswell <bmc@lungetech.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

"""

#import random
#import unittest
from Crypto.Cipher import AES

class PRNG(object):
    """
    A python implementation of ANSI X9.31 using AES 128

    Attributes:
        random_data: Currently available block of generated random data
        V: "seed value which is also kept secret"
        DT: "date/time vector updated upon each iteration"
        I: Intermediate value
        aes_ctx: AES state machine context
    """
    BLOCK_SIZE = 16

    def __init__(self, seed=None):
        """

        Seed is V + Key + DT as a string
        """
        if seed is not None:
            assert len(seed) == 48
        else:
            seed = "zaybxcwdveuftgsh" + "0123456789abcdef" + "\x00" * 16

        self.V, key, self.DT = [seed[i:i+PRNG.BLOCK_SIZE] for i in range(0, len(seed), PRNG.BLOCK_SIZE)]
        self.random_data = ''

        self.I = "\x00" * PRNG.BLOCK_SIZE
        self.aes_ctx = AES.new(key)

    @staticmethod
    def _xor_string(value_1, value_2):
        """
        value_1 ^ value_2

        Exceptions:
            AssertionError if value_1 and value_2 are not the same length
        """
        assert len(value_1) == len(value_2)
        return ''.join(chr(ord(a) ^ ord(b)) for a, b in zip(value_1, value_2))

    def _get_block(self):
        """
        Get the next block from the PRNG, saving it to self.random_data

        Arguments:
            None

        Returns:
            None

        Exceptions:
            None
        """
        # encrypt the counter value, giving intermediate value I
        self.I = self.aes_ctx.encrypt(self.DT)

        # XOR I with secret vector V, encrypt the result to obtain pseudo
        # random data
        tmp = self._xor_string(self.I, self.V)
        self.random_data = self.aes_ctx.encrypt(tmp)

        # XOR random data with I, and encrypt to get new secret vector V
        tmp = self._xor_string(self.random_data, self.I)
        self.V = self.aes_ctx.encrypt(tmp)

        # update DT value
        i = PRNG.BLOCK_SIZE - 1
        while i >= 0:
            out = (ord(self.DT[i]) + 1) % 256
            self.DT = self.DT[:i] + chr(out) + self.DT[i+1:]
            if out != 0:
                break
            i -= 1

    def get(self, size):
        """
        Get 'size' bytes of random data

        Arguments:
            size: Amount of random data to return

        Returns:
            str of length 'size' of random data

        Exceptions:
            AssertionError if size is not a positive integer
        """
        assert isinstance(size, int)
        assert size > 0

        result = ''
        while len(result) < size:
            need = size - len(result)
            if not len(self.random_data):
                self._get_block()

            result += self.random_data[:need]
            self.random_data = self.random_data[need:]

        return result
