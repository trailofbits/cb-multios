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

import os
import random
import string

__author__ = 'scsi'
from generator.actions import Actions
import string
import sys
# add root dir to path so we can use common files for this and POV gen
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../support")))
from mixcodegen.cg import MixologyCodeGen


class Mixology(Actions):

	mix_cg = MixologyCodeGen()
	delim = "\n"
	samp = 1478915022
	mix_cmd_tmpl = "MIX %s %s %s\n"
	s_prep_k = 'sample_prep_limit'
	s_mix_k = 'sample_check_limit'
	maxcmds_for_expensive = 8

	@property
	def _random_prepd_sample(self):
		l = self.state['sample_num']
		if len(l) > 1:
			return random.choice(l)
		return self.state['sample_num'][0]

	def _expect_welcome(self):
		self.read(delim=self.delim, expect="Welcome to the new chemical discovery service!")


	def start(self):
		self.state[self.s_prep_k] = self.maxcmds_for_expensive
        self.state[self.s_mix_k] = self.maxcmds_for_expensive
		
        #x = self._wrap("delay", "100")
		#self._actions.append(x)


		self._expect_welcome()

	def prompt(self):
		pass

	def _list_page(self, pg):
		start = pg*self.mix_cg.pg_size
		end = start + self.mix_cg.pg_size
		i = 0
		for mi in self.mix_cg.compound_list[start:end]:
			self.comment("expect idx %s", str(i+start))
			i +=1

			self.read(delim=self.delim, expect=mi)

	def _check_decrement_sample_limit_write_quit(self, k):
		if self.state[k] != 0:
			self.state[k] = self.state[k] - 1
			return True
		return False


	def prep_sample(self):

		if self._check_decrement_sample_limit_write_quit(self.s_prep_k):
			numeric_sample = random.randint(1, self.samp)
			self.state['sample_num'] = self.state.get('sample_num', []) + [numeric_sample]

			zoom_txt = self.mix_cg.get_prep_sample_zoom(str(numeric_sample))

			self.comment("PREP %s", numeric_sample)
			self.write("PREP %s\n" % numeric_sample)
			self.read(delim=self.delim, expect=zoom_txt+"\n")
		else:
			self.quit()
			return -1


	def _mix_arb_good_sample(self, sample_num, new_name):
		zoom_txt = self.mix_cg.get_mix_sample_zoom(str(sample_num))
		assert(len(zoom_txt) > 0)
		self.comment("MIX %s", sample_num)
		self.write(self.mix_cmd_tmpl % (sample_num, new_name, zoom_txt))
		self.read(delim=self.delim, expect="New compound: %s\n" % new_name)

	def mix_good_sample(self):
		if self._check_decrement_sample_limit_write_quit(self.s_mix_k):
			sample_num = self._random_prepd_sample
			s = string.uppercase + string.lowercase + string.digits
			new_name = "".join([s[random.randrange(0, len(s))] for i in range(0, random.randint(3, 120))])
			self._mix_arb_good_sample(sample_num, new_name)
		else:
			self.quit()
			return -1


	def list_random_good_page(self):
		pg_to_test = random.randint(0, self.mix_cg.max_pg)
		self.comment("LIST page %s", str(pg_to_test))
		self.write("LIST %d\n" % pg_to_test)
		self._list_page(pg_to_test)
		# todo possible terminate here?
		# todo list bad page msg?

	def quit(self):
		self.write("QUIT\n")


if __name__ == "__main__":
	m = Mixology()
	pass


