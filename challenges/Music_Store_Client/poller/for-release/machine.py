#!/usr/bin/env python

from generator.actions import Actions, Variable
from collections import deque
import random
import string


class TemplateGenerator(Actions):

	def start(self):
		self.results = 0
		self.result_xml = []
		self.balance = random.randint(1,20)*2
		self.purchase_song_sid = ""
		self.price = 0
		self.term = Variable('term')
		self.attribute = Variable('attribute')
		self.limit = Variable('limit')
		self.songsLeft = self.balance
		self.read(delim="\n",
				  expect=r'ID=[A-z]{32}\n',
				  expect_format='pcre')
		self.write("BALANCE=" + str(self.balance) + "\x07")

	def get_search(self):
		self.results = random.randint(10,100)
		self.result_xml = []
		self.purchase_song_sid = ""
		self.price = 0

		self.term.set_re(r'term=([A-z]*)&amp;')
		self.read(delim="&", assign=self.term)
		
		self.attribute.set_re(r'attribute=([A-z]*)&amp;')
		self.read(delim="&", assign=self.attribute)

		self.limit.set_re(r'limit=([0-9]*)\n')
		self.read(delim="\n", assign=self.limit)

	def create_artist_result(self):
		if(self.results == 0):
			return

		price_val = 2
		price = '&price=' + str(price_val)

		sid = str(random.randint(1,999999999))
		if self.purchase_song_sid == "":
			self.purchase_song_sid = sid + '\n'
			self.price = price_val
		sid = 'sid=' + sid

		album_len = random.randint(1, 50)
		album = ''.join(random.choice(string.ascii_letters) for _ in
                            range(album_len))
		album = ''.join(['&album=',album])

		song_len = random.randint(1, 50)
		song = ''.join(random.choice(string.ascii_letters) for _ in
                            range(song_len))
		song = ''.join(['&song=',song,'\x07'])  	

		self.write(sid, price, '&artist=', self.term, album, song)
		
		self.results-=1



	def create_album_result(self):
		if(self.results == 0):
			return

		price_val = 2
		price = '&price=' + str(price_val)
		
		sid = str(random.randint(1,999999999))
		if self.purchase_song_sid == "":
			self.purchase_song_sid = sid + '\n'
			self.price = price_val
		sid = 'sid=' + sid

		artist_len = random.randint(1, 50)
		artist = ''.join(random.choice(string.ascii_letters) for _ in
                            range(artist_len))
		artist = ''.join(['&artist=',artist])

		song_len = random.randint(1, 50)
		song = ''.join(random.choice(string.ascii_letters) for _ in
                            range(song_len))
		song = ''.join(['&song=',song,'\x07'])  	

		self.write(sid, price, artist, '&album=', self.term, song)

		self.results-=1

	def create_song_result(self):
		if(self.results == 0):
			return
			
		price_val = 2
		price = '&price=' + str(price_val)
		
		sid = str(random.randint(1,999999999))
		if self.purchase_song_sid == "":
			self.purchase_song_sid = sid + '\n'
			self.price = price_val
		sid = 'sid=' + sid

		artist_len = random.randint(1, 50)
		artist = ''.join(random.choice(string.ascii_letters) for _ in
                            range(artist_len))
		artist = ''.join(['&artist=',artist])

		album_len = random.randint(1, 50)
		album = ''.join(random.choice(string.ascii_letters) for _ in
                            range(album_len))
		album = ''.join(['&album=',album])	

		self.write(sid, price, artist, album, '&song=', self.term, '\x07')

		self.results-=1

	def send_results(self):
		while(self.results>0):
			self.create_artist_result()

	def send_number(self):
		self.write("NUMBER="+str(self.results)+"\x07")

	def purchase_song(self):
		if self.songsLeft == 0:
			pass
		self.read(delim="\n", expect=self.purchase_song_sid)
		self.balance-=self.price
		self.songsLeft-=1
		self.write("BALANCE=" + str(self.balance) + "\x07")
		if self.balance == 0:
			self.quit()

	def quit(self):
		while(self.balance > 0 and self.songsLeft > 0):
			self.get_search()
			self.send_number()
			self.create_artist_result()
			self.send_results()
			self.purchase_song()

		return -1

