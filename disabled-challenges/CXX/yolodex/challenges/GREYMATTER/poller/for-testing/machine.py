#!/usr/bin/env python
#
# Copyright (C) 2014 
#   Brian Caswell <bmc@lungetech.com>
#   Narf Industries <info@narfindustries.com>
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

from generator.actions import Actions, Variable
from random import choice, randint
import string
import struct


def random_string(a, b):
    """
    'Safe' is qualified as strings that don't contain:
    1) "()" - Avoid potentially-SEGFAULTing canonicalization.
    2) "\x06" - Avoid STRING_TERMINATOR
    3) "$SRC$" & "$!SRC$" - Avoid accidentially introducing links.

    "(" and ")" are only problems if it appears adjacent to each other, 
    triggering buggy canonicalization.  Therefore, we allow "(" and ")" in the 
    general case, but make a pass to eliminate any "()" instances.
    """
    safe_printable = string.printable.replace("\x06", "")
    return ''.join(choice(safe_printable) for _ in \
        range(randint(a, b))).replace("()", ")_").replace("$SRC$", "$CRS$").replace("$!SRC$", "$!CRS$")

def canonicalize_path(path):
    """
    Provided a non-canonicalized path, returns a canonicalized one.  Used to 
    verify CB canonicalization behavior.

    Canonicalization rules:
    1) "()" are stripped.
    """
    cp = path.replace("()", "")
    return cp


class GreyMatter(Actions):

    DEBUG = 0
    SZ_MAX_DOC = 0x2000
    SZ_MAX_PATH = 0x100
    STRING_TERMINATOR = "\x06"

    def _respond(self, doc_path):
        """
        Provided a path, produce a file that possibly contains links to other 
        files and send that file to the CB.  Keep track of the outstanding 
        referenced files.

        The CB will recurse depth-first through links.  We need to mirror this 
        behavior here if we want an opportunity to verify canonicalization.

        As such, it is easiest if this function recurses as well, following 
        sequential, depth-first order.
        """
        doc = ""
        sz_doc = 0
        parens_path = False

        if self.DEBUG:
            if type(doc_path) == Variable:
                str_doc_path = "<INDEX VARIABLE>"
            else:
                str_doc_path = doc_path
            print "Currently serving '%s'" % str_doc_path

        # If we're not in the index document special case, we need to do a 
        # read() and verify the requested document against the correctly 
        # canonicalized path.
        if type(doc_path) != Variable:
            self.read(
                delim=self.STRING_TERMINATOR, 
                expect=doc_path,
            )


        # We choose a random number of paths to include in our document.
        if self.chance(0.25): # Keep path explosion (relatively) under control.
            num_links = randint(1, 4)
            if self.chance(0.25):
                # In some small percentage of paths, we generate a path that 
                # contains "()", triggering faulty canonicalization.
                parens_path = True
        else:
            num_links = 0

        if self.DEBUG:
            print "\t%d links in this doc" % num_links

        # We generate our paths, keeping track of the amount of space consumed.
        # Do this before the fluff loop below because we need to guarantee that 
        # the links make it into the document.
        paths = [] # These are links without the bookends.
        links = [] 
        for _ in range(num_links):
            # Why do we sometimes go slightly over on patch length?  
            # Subtracting 10 is empirically suffcient.
            new_path = random_string(1, self.SZ_MAX_PATH-10)
            sz_new_path = len(new_path)

            # If we've decided that we're including "()"s ...
            if parens_path:
                num_parens = randint(1, 8)
                for _ in range(num_parens):
                    idx_bisect = randint(0, sz_new_path)
                    new_path = new_path[:idx_bisect] + "()" + new_path[idx_bisect:]

                # We truncate the path so that we don't accidentally overflow 
                # the vulnerable buffer.

                # While we might assume that we could code this to allow paths 
                # longer than the vulnerable buffer length (because parens 
                # shouldn't count against the total), this is actually 
                # substantially more work because the CB will immediately 
                # reject any path thats overly long (its first length check 
                # is correct), resulting in desynchronization between CB and 
                # poller.
                new_path = new_path[:self.SZ_MAX_PATH-10]

            paths.append(new_path)
            link = "$SRC$" + new_path + "$!SRC$"
            if self.DEBUG:
                print "Responding to '%s'; generated a link: '%s'" % (str_doc_path, link)
            links.append(link)
            sz_doc += len(link)

        # We populate the document with a random amount of random characters 
        # separating our paths.  We make sure to not exceed MAX_USHORT.
        for i in range(num_links):
            fluff = random_string(0, self.SZ_MAX_DOC-sz_doc)
            doc += fluff
            sz_doc += len(fluff)

            doc += links[i] # We're already counting the length of links.

            fluff = random_string(0, self.SZ_MAX_DOC-sz_doc)
            doc += fluff
            sz_doc += len(fluff)

        # This will happen if the document has no links.
        if 0 == sz_doc:
            fluff = random_string(1, self.SZ_MAX_DOC-sz_doc)
            doc += fluff
            sz_doc += len(fluff)

        # 2B: size of document (sz_doc)
        # XB: path + STRING_TERMINATOR
        # (sz_doc)B: the document
        self.write(
            struct.pack("<H", sz_doc),
            doc_path, 
            self.STRING_TERMINATOR, 
            doc
        )

        # OK, we've sent a document to the CB that contains anywhere between 0 
        # and 4 links to further documents.  We must recurse and handle each 
        # link in order.
        # We need this to be in sequential order, so we can't iterate over 
        # paths directly (as this is backed by a hash table).
        for i in range(len(paths)):
            path = paths[i]
            cp = canonicalize_path(path)
            if self.DEBUG:
                print "Recursing to serve '%s', canon'ed to '%s'" % (path, cp)
            self._respond(cp)

    def start(self):
        """
        Intialize state.
        """
        # The CB will first request a randomly-named index file.  This is a 
        # unique case because this filename will be a Variable and its value, 
        # therefore, is inacccessible during poll generation.
        idx_path = Variable("idxpath")
        idx_path.set_slice(begin=0, end=-1)
        self.read(
            delim=self.STRING_TERMINATOR, 
            assign=idx_path)
        self.state['idx_path'] = idx_path

    def respond(self):
        """
        If there are any outstanding requests, we randomly choose one and 
        respond to it.

        If there are no remaining requests, we must have responded to all the 
        requests and we're done.
        """
        idx_path = self.state['idx_path']
        self._respond(idx_path)




