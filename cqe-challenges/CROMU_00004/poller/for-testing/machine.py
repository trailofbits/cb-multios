#!/usr/bin/python

from generator.actions import Actions
import random
import re
import subprocess
import sys
from struct import pack
from math import sin

# length of a dot in ms
dot_len_ms = 5
# num of PCM samples in a dot
samples_per_dot = int(44100*(dot_len_ms/1000.0))
# frequency of tones in Hz
freq = 440
# language definition
lang = {
	'!': '.', '"': '-', '#': '..', '$': '.-', '%': '-.',
	'&': '--', '\'': '...', '(': '..-', ')': '.-.', '*': '.--',
	'+': '-..', ',': '-.-', '-': '--.', '.': '---', '/': '....',
	'0': '...-', '1': '..-.', '2': '..--', '3': '.-..', '4': '.-.-',
	'5': '.--.', '6': '.---', '7': '-...', '8': '-..-', '9': '-.-.',
	':': '-.--', ';': '--..', '<': '--.-', '=': '---.', '>': '----',
	'?': '.....', '@': '....-', 'A': '...-.', 'B': '...--', 'C': '..-..',
	'D': '..-.-', 'E': '..--.', 'F': '..---', 'G': '.-...', 'H': '.-..-',
	'I': '.-.-.', 'J': '.-.--', 'K': '.--..', 'L': '.--.-', 'M': '.---.',
	'N': '.----', 'O': '-....', 'P': '-...-', 'Q': '-..-.', 'R': '-..--',
	'S': '-.-..', 'T': '-.-.-', 'U': '-.--.', 'V': '-.---', 'W': '--...',
	'X': '--..-', 'Y': '--.-.', 'Z': '--.--', '\x1f': '-----'
}

class Wav(Actions):
	def start(self):
		pass

	def random_string(self, min_length, max_length):
		chars = map(chr, range(32, 91))
		str = '  '
		# don't allow consecutive spaces or consecutive chars with no variation
		while re.search('  ', str) or len(str) < min_length or re.search('^[ !#\'/?]+$', str) or re.search('^[ "&\.>\x1f]+$', str):
			str = ''.join(random.choice(chars) for _ in range(random.randint(min_length, max_length))).rstrip()
		return str

	def nondiverse_random_string(self):
		chars = '!#/?"'
		return random.choice(chars)

	def gen_tone(self, intervals):
		tone = ''
		for i in range(0, samples_per_dot*intervals):
			tone += pack('<h', 20000*sin(2*3.14159*freq*i/44100))
		return tone

	def gen_silence(self, intervals):
		silence = ''
		for i in range(0, samples_per_dot*intervals):
			silence += pack('<h', 0)
		return silence

	def gen_header(self, data_len, num_samples):
		header = ''
		header += 'PCM '                  # ID
		header += pack("<L", data_len)    # DataSize
		header += pack("<L", num_samples) # NumSamples
		return header
		
	def gen_pcm(self, str, dot_len_ms):
		global samples_per_dot
		samples_per_dot = int(44100*(dot_len_ms/1000.0))
		pcm_data = ''
		num_samples = 0

		str_len = len(str)
		for i in range(0, str_len):
			c = str[i]
			if c == ' ':
				pcm_data += self.gen_silence(7)
				num_samples += 7*samples_per_dot
				continue

			if not c in lang.keys():
				sys.stderr.write("Invalid char "+c+"\n")
				sys.exit(-1)

			code_len = len(lang[c])
			for j in range(0, code_len):
				s = (lang[c])[j]
				if s == '.':
					pcm_data += self.gen_tone(1)
					num_samples += 1*samples_per_dot
				if s == '-':
					pcm_data += self.gen_tone(3)
					num_samples += 3*samples_per_dot

				# append inter-symbol pause if there are more symbol
				if (j < code_len-1):
					pcm_data += self.gen_silence(1)
					num_samples += 1*samples_per_dot

			# append inter-character pause if there are more characters
			if (i < str_len-1) and (str[i+1] != ' '): 
				pcm_data += self.gen_silence(3)
				num_samples += 3*samples_per_dot

		return self.gen_header(len(pcm_data),num_samples)+pcm_data

	def valid(self):
		rnd_str = self.random_string(3,5)
		self.write(self.gen_pcm(rnd_str,random.randint(2,30)))
		self.read(delim='\n', expect=rnd_str)

	def invalid_char(self):
		rnd_str = "\x1f"+self.random_string(3,5)
		self.write(self.gen_pcm(rnd_str,random.randint(2,30)))
		self.read(delim='\n', expect='unknown character\n')

	def insufficient_symbol_diversity(self):
		rnd_str = self.nondiverse_random_string()
		self.write(self.gen_pcm(rnd_str,random.randint(2,30)))
		self.read(delim='\n', expect='Insufficient symbol diversity\n')

	def invalid_length(self):
		rnd_str = self.random_string(30,40)
		self.write(self.gen_pcm(rnd_str,50))
		self.read(delim='\n', expect='Invalid WAV length\n')

