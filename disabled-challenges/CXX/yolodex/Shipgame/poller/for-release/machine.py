#!/usr/bin/env python

from generator.actions import Actions, Variable
import copy
import random
import string
import numpy
import struct

users = [ "Alice", "Bob", "Carol", "Dave", "Eve" ]
servers = [ "walkthrough", "newsletter" ]
pages = { servers[0]: [ "building-a-cb.md", "cgc-qualifier-event-api.md", "cgc-repository.md", "debugging-a-cb.md", "running-the-vm.md", "scoring-cbs.md", "submitting-a-cb.md", "testing-a-cb.md", "understanding-poll-generators.md" ], servers[1] : [ "cpp.md", "ipc.md", "template.md" ] }
termDelim = "\n\t\n\t\n"

class Router(Actions):

    def start(self):
        self.username = random.choice(users)
        self.uid = Variable('uid')
        self.uid.set_re("HELLO " + self.username + " YOUR UID IS ([a-f0-9]+) HOW CAN I HELP YOU\\n", group=1)

    def say_hi_good(self):
        self.write("HELLO I AM " + self.username + "\n")
        self.read(delim='\n', assign=self.uid)
        
    def say_hi_bad(self):
        self.write("HI I AM " + self.username + "\n")
        self.read(delim='\n', expect="BAD CMD\n")
  
    def get_page(self):
        pass

    def get_page_good(self):
        s = random.choice(servers)
        url = s + "/" + random.choice(pages[s])
        self.write(self.uid)
        self.write(" SAYS GET " + url + " PLEASE\n" )

        self.read(delim=termDelim)

    def get_page_bad(self):
        bServer = random.randint(0,1)
        s = random.choice(servers)
        p = random.choice(pages[s])
        if bServer :
          s += ".test"
        
        url = s + "/" + p + ".test"

        self.write(self.uid)
        self.write(" SAYS GET " + url + " PLEASE\n" )
        
        if bServer :
          self.read(delim='\n', expect="SERVER [" + s + "] NOT FOUND\n")
        else :
          self.read(delim=termDelim, expect=p + ".test : PAGE NOT FOUND\n" + termDelim)

    def say_bye(self):
        self.write("GOODBYE\n")
        self.read(delim='\n', expect="GOODBYE\n")

    def end(self):
        pass



