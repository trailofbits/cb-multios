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

import ctypes

import os
import random
import sys
import math

# this is lame, I cant free out zoombuf
import datetime


sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'narfpylib.zip'))
__author__ = 'scsi'

CURDIR = os.path.dirname(__file__)
BASEPATH = os.path.abspath(os.path.join(CURDIR, '../../'))
BUILD_DIR = os.path.join(BASEPATH, 'build')
LIBDIR = os.path.join(BASEPATH, 'lib')


DATADIR = os.path.join(BASEPATH, "support", 'data')
from jinja2 import Template

H_TMPL = """
/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef MIX_CHEM
#define MIX_CHEM

const static int N_FORMULAS = {{ n_chem_forms }};
typedef struct chem_formula {
	char *compound_name;
	double mole;
} chem_formula_t;

static chem_formula_t chem_formulas[N_FORMULAS] = {
	{% for cfn, mole in chem_forms %}{ "{{ cfn }}", {{ mole }} },
	{% endfor %}

};

#endif

"""



def get_compounds(sample_size, over_percentage):
	f = open(os.path.join(DATADIR, 'comps_strip'))
	lines = [x.replace('\\', '').replace(',', '') for x in map(str.strip, f.readlines())]
	f.close()
	compound_list = list(set(lines))

	random.seed(0x3209baaa)
	sample = random.sample(compound_list, sample_size)

	l = [(s, random.uniform(0.1, 2.3)) for s in sample]
	assert(int(sample_size*over_percentage) > 20)
	l = [(s, random.uniform(2.3, 2.4)) for s, i in l[:int(sample_size*over_percentage)]] + l[int(sample_size * over_percentage):]

	# disperse this thing so a hash function can actually find these values
	random.shuffle(l)
	return l



class MixologyCodeGen(object):

	sample_size = 3000
	pg_size = 25
	code_fn = 'libcompound'
	over_percentage = 0.05
	prep_sample_sz = 1000
	mix_sample_sz = 25


	compounds_and_weights = get_compounds(sample_size, over_percentage)
	compound_list = [c for c, w in compounds_and_weights]

	mix = ctypes.cdll.LoadLibrary(os.path.join(BUILD_DIR, "patched", "so",  "NRFIN_00007.so"))


	class compounds_sample_t(ctypes.Structure):
		_fields_=[("sample", ctypes.POINTER(ctypes.c_uint)),
		           ("sample_sz", ctypes.c_uint )]

	sample_compounds = mix.sample_compounds
	sample_compounds.restype = ctypes.POINTER(compounds_sample_t)

	zoom_buf = mix.zoom_buf
	zoom_buf.restype = ctypes.c_char_p
	zoom_buf.argtypes = [ctypes.POINTER(compounds_sample_t)]


	@property
	def max_pg(self):
		return math.ceil(self.sample_size / self.pg_size)-2

	@property
	def massive_compounds(self):
		return [c for c, w in filter(lambda x: x[1] > 2.3, self.compounds_and_weights)]


	@property
	def h_file_path(self):
		return os.path.join(LIBDIR, self.code_fn + '.h')

	@property
	def num_entries(self):
		return len(self.compounds_and_weights)


	def _arb_sample_zoom(self, sample_seed, sample_sz):



		x = self.sample_compounds(sample_seed, sample_sz)
		b = self.zoom_buf(x)
		assert(b is not None)
		self.mix.free_sample_st(x)

		del x

		return b

	def _mix_sample_idxs(self, idxs, light_idxs):
		# ll = reduce(lambda x, y: x*y, [self.compounds_and_weights[i][1] for i in idxs])
		ll = 1
		final_idx = []
		for i in idxs:
			if(ll < 2**24):
				ll *= self.compounds_and_weights[i][1]
				final_idx.append(i)

		assert(ll > 2**24)
		assert(ll < 2**32)

		alloc_sample_st = self.mix.alloc_sample_st
		alloc_sample_st.restype = ctypes.POINTER(self.compounds_sample_t)

		samp = alloc_sample_st(self.mix_sample_sz)
		set_sample_at_idx = self.mix.set_sample_at_idx
		set_sample_at_idx.argtypes = [ctypes.POINTER(self.compounds_sample_t), ctypes.c_uint, ctypes.c_uint]


		ii = 0

		for i in range(0, self.mix_sample_sz):
			try:
				ii = final_idx.pop()
			except IndexError:
				pass
			# we just fill the sample up with the last index so that multiple is only done once
			set_sample_at_idx(samp, i, ii)


		b = self.zoom_buf(samp)
		self.mix.free_sample_st(samp)

		assert(b is not None)
		# need 20 idxs at
		return b

	def _get_sample_heavy_idxs(self, sample_seed):
		z = ctypes.c_char_p(sample_seed)
		x = mix.sample_compounds(z, self.prep_sample_sz)

		idxs = []
		light_idxs = []
		for i in range(0, len(self.compound_list)):
			r =mix.check_compound_idx_in_sample(x, i)
			if r == 1 and self.compounds_and_weights[i][1] > 2.3:
				idxs.append(i)
			elif r == 1 and self.compounds_and_weights[i][1] < 2.3:
				light_idxs.append(i)
		assert(len(idxs) >= 20)
		return idxs, light_idxs



	def get_prep_sample_zoom(self, sample_seed):
		return self._arb_sample_zoom(sample_seed, self.prep_sample_sz)


	def get_mix_sample_zoom(self, sample_seed):
		return self._arb_sample_zoom(sample_seed, self.mix_sample_sz)




	def generate_code(self):
		t = Template(H_TMPL)

		s = t.render(chem_forms=self.compounds_and_weights, n_chem_forms=len(self.compounds_and_weights))
		with open(self.h_file_path, 'w') as f:
			f.write(s)


if __name__ == '__main__':
	m = MixologyCodeGen()
	m.generate_code()
