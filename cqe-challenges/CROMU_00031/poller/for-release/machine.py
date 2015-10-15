#!/usr/bin/env python


# this will make polls

# polls to remember:
# 9 - will display board
# 666 - will exit
# make a valid move
# make an invalid move on the board
# make an invalid move off the board

# keep a table of piece locations
# track moves

from generator.actions import Actions
import random

LOG_ENABLED = False

class location():
	x = 0
	y = 0

	def __init__(self, x=None, y=None):
		self.x = x
		self.y = y

	# returns good random location on board
	def getRandGoodLocation(self):
		# return 0-7, 0-7
		x = random.randrange(0, 7)
		y = random.randrange(0, 7)

		return (x,y)

	# returns location outside of board
	def getRandBadLocation(self):
		c = random.choice("yn")
		x = 0
		if (c == 'y'):
			x = random.randrange(-10, -1)
		else:
			x = random.randrange(8, 20)

		y = 0
		c = random.choice("yn")
		if (c == 'y'):
			y = random.randrange(-10, -1)
		else:
			y = random.randrange(8, 20)

		return (x,y)

# functions with underscore ('_') are internal only
class Chesser(Actions):
	board = []
	current_turn = 'white'

	def _getPieceByLocation(self, loc):
		# return the piece from the board that is located at position x,y
		for a in self.board:
			if (a[2] == loc[0] and a[3] == loc[1]):
				return a

	# for testing only
	def _printBoard(self):
		cnt = 0
		ss = ""
		for a in self.board:
			ss += a[0] + ' '
			cnt += 1
			if (cnt == 8):
				cnt = 0
				ss += "\n"

		print(ss)

	def _genInitialBoard(self):
		self.board = [('rook', 'black', 0, 7),('knight', 'black', 1,7),('bishop', 'black', 2,7),('queen','black',3,7), \
		  ('king', 'black', 4, 7),('bishop', 'black', 5,7),('knight', 'black', 6,7),('rook','black',7,7), \
		  ('pawn', 'black', 0, 6),('pawn', 'black', 1, 6),('pawn', 'black', 2, 6),('pawn', 'black', 3, 6), \
		  ('pawn', 'black', 4, 6),('pawn', 'black', 5, 6),('pawn', 'black', 6, 6),('pawn', 'black', 7, 6), \
		  ('blank', '', 0, 5),('blank', '', 1, 5),('blank', '', 2, 5),('blank', '', 3, 5), \
		  ('blank', '', 4, 5),('blank', '', 5, 5),('blank', '', 6, 5),('blank', '', 7, 5), \
		  ('blank', '', 0, 4),('blank', '', 1, 4),('blank', '', 2, 4),('blank', '', 3, 4), \
		  ('blank', '', 4, 4),('blank', '', 5, 4),('blank', '', 6, 4),('blank', '', 7, 4), \
		  ('blank', '', 0, 3),('blank', '', 1, 3),('blank', '', 2, 3),('blank', '', 3, 3), \
		  ('blank', '', 4, 3),('blank', '', 5, 3),('blank', '', 6, 3),('blank', '', 7, 3), \
		  ('blank', '', 0, 2),('blank', '', 1, 2),('blank', '', 2, 2),('blank', '', 3, 2), \
		  ('blank', '', 4, 2),('blank', '', 5, 2),('blank', '', 6, 2),('blank', '', 7, 2), \
		  ('pawn', 'white', 0, 1),('pawn', 'white', 1, 1),('pawn', 'white', 2, 1),('pawn', 'white', 3, 1), \
		  ('pawn', 'white', 4, 1),('pawn', 'white', 5, 1),('pawn', 'white', 6, 1),('pawn', 'white', 7, 1), \
		  ('rook', 'white', 0, 0),('knight', 'white', 1, 0),('bishop', 'white', 2, 0),('queen', 'white', 3, 0), \
		  ('king', 'white', 4, 0),('bishop', 'white', 5, 0),('knight', 'white', 6, 0),('rook', 'white', 7, 0)]

	def _assignBoardLocation(self, newPiece):
		loc = 0
		for a in self.board:
			if (a[2] == newPiece[2] and a[3] == newPiece[3]):
				found = loc
			loc += 1
		self.board[found] = newPiece

	# swap positions of two pieces
	def _movePieceOnBoard(self, src, dst):
		pce_src = self._getPieceByLocation(src)
		pce_dst = self._getPieceByLocation(dst)
		new_src = (pce_dst[0], pce_dst[1], pce_src[2],pce_src[3])
		new_dst = (pce_src[0], pce_src[1], pce_dst[2],pce_dst[3])
		self._assignBoardLocation(new_src)
		self._assignBoardLocation(new_dst)

	def _selectGoodPiece(self):
		real_pieces = []
		
		for a in self.board:
			if ((a[0] != 'blank') and (a[1] == self.current_turn)):
				# add to the list of possible pieces
				real_pieces.append(a)

		num = len(real_pieces)
		c = random.randrange(0, num - 1)
		return real_pieces[c]

	def displayBoard(self):
		#print('printer')
		self.write("9\n")
		self.read(length =79, expect=r"^\x00?([.abcdefghijkl]{8}\n){8}", expect_format="pcre")

	def leaveTheGame(self):
		#print('exiting')
		self.write("666\n")
		self.read(length=9, expect=r"good game")

	def keepPlaying(self):
		pass

	def start(self):
		self.read(delim ="WHITE: ", expect=r"^\x00?([.abcdefghijkl]{8}\n){8}", expect_format="pcre")
		self._genInitialBoard()
		self.current_turn = 'white'

	def _move_king(self, src):
		# move a king located at 'src'
		# get possible moves
		#  check if on board
		#  check if blank and not not own color
		# pick a move and make it
		# list of possible moves
		# check each one 
		# choose random spot from remaining spots

		x = src[0]
		y = src[1]

		moves = []
		poss_moves = []
		poss_moves.append((x,y+1))
		poss_moves.append((x+1,y+1))
		poss_moves.append((x,y-1))
		poss_moves.append((x-1,y-1))
		poss_moves.append((x+1,y))
		poss_moves.append((x+1,y-1))
		poss_moves.append((x-1,y))
		poss_moves.append((x-1,y+1))

		my_color = self.current_turn
		for a in poss_moves:
			ret = self._isValidMove((a[0], a[1]), my_color)
			if (ret == 2):
				# yes, blank
				moves.append(a)
			elif (ret == 1):
				# yes, take
				moves.append(a)
			elif (ret == 0):
				#no, same color piece
				pass
			elif (ret == 3):
				#no, off board
				pass

		return moves

	def _move_pawn(self, src):
		# move a pawn located at 'src'
		moves = []

		if (self.current_turn == 'white'):
			move = (src[0], src[1] + 1)
		else:
			move = (src[0], src[1] - 1)

		my_color = self.current_turn
		ret = self._isValidMove((move[0], move[1]), my_color)
		if (ret == 2):
			# yes, blank
			moves.append(move)
		elif (ret == 1):
			# yes, take
			moves.append(move)
		elif (ret == 0):
			#no, same color piece
			pass
		elif (ret == 3):
			#no, off board
			pass

		return moves

	def _move_bishop(self, src):
		moves = []

		moves += self._check_dir(src, "duright")
		moves += self._check_dir(src, "duleft")
		moves += self._check_dir(src, "ddright")
		moves += self._check_dir(src, "ddleft")

		return moves

	# given this destination, can I go there?
	# returns 0 if same color
	# returns 1 if opposite color (takes)
	# returns 2 if blank square
	# retunrs 3 if off board
	# returns -1 if error
	def _isValidMove(self, dst, my_color):
		pce = self._getPieceByLocation(dst)
		
		if (pce == None):
			return -1
		target_color = pce[1]
		if (dst[0] not in range(0,8)) or (dst[1] not in range(0,8)):
			# lands off board
			return 3
		if pce[0] == 'blank':
			return 2
		if (pce[1] == my_color):
			return 0 # bad spot, same color piece
		else:
			# piece of the other color
			return 1

	# returns only good values
	def _check_dir(self, src, dir):
		moves = []
		my_color = self._getPieceByLocation(src)[1]
		# src is starting square
		# dst is ending square
		# dir is: right, left, up, down, duright, duleft, ddleft, ddright

		# diagonal up/right
		if (dir == "duright"):
			for a in range(1, 8):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((src[0]+a, src[1]+a), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((src[0]+a, src[1]+a))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((src[0]+a, src[1]+a))
					return moves

		# diagonal up/left
		if (dir == "duleft"):
			for a in range(1, 8):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((src[0]-a, src[1]+a), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((src[0]-a, src[1]+a))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((src[0]-a, src[1]+a))
					return moves

		# diagonal down/right
		if (dir == "ddright"):
			for a in range(1, 8):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((src[0]+a, src[1]-a), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((src[0]+a, src[1]-a))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((src[0]+a, src[1]-a))
					return moves

		# diagonal down/left
		if (dir == "ddleft"):
			for a in range(1, 8):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((src[0]-a, src[1]-a), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((src[0]-a, src[1]-a))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((src[0]-a, src[1]-a))
					return moves

		if (dir == "right"):
			for a in range(src[0]+1, 8):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((a, src[1]), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((a, src[1]))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((a, src[1]))
					return moves

		if (dir == "left"):
			for a in range(src[0] -1 , -1, -1):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((a, src[1]), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((a, src[1]))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((a, src[1]))
					return moves

		if (dir == "up"):
			for a in range(src[1]+1, 8):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((src[0], a), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((src[0], a))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((src[0], a))
					return moves

		if (dir == "down"):
			for a in range(src[1] -1 , -1, -1):
				# check squares in same rank to right
				# run into piece, stop
				ret = self._isValidMove((src[0], a), my_color)
				if (ret == 2):
					# blank
					# add this square and keep going
					moves.append((src[0], a))
				elif (ret == 0):
					# same color
					# we ran into our own piece, stop looking in this direction
					return moves
				elif (ret == 1):
					# we ran into a piece we can take, stop looking in this direction and take it
					moves.append((src[0], a))
					return moves
		
		#for a in moves:
		#	print(a)

		return moves

	# this will return a list of valid spots to move this piece
	def _move_queen(self, src):
		moves = []

		moves += self._check_dir(src, "right")
		moves += self._check_dir(src, "left")
		moves += self._check_dir(src, "up")
		moves += self._check_dir(src, "down")
		moves += self._check_dir(src, "duright")
		moves += self._check_dir(src, "duleft")
		moves += self._check_dir(src, "ddright")
		moves += self._check_dir(src, "ddleft")

		return moves

	def _move_rook(self, src):
		moves = []

		moves += self._check_dir(src, "right")
		moves += self._check_dir(src, "left")
		moves += self._check_dir(src, "up")
		moves += self._check_dir(src, "down")

		return moves

	def _move_knight(self, src):
		x = src[0]
		y = src[1]

		moves = []
		poss_moves = []
		poss_moves.append((x+2,y+1))
		poss_moves.append((x+2,y-1))
		poss_moves.append((x-2,y+1))
		poss_moves.append((x-2,y-1))
		poss_moves.append((x-1,y+2))
		poss_moves.append((x+1,y+2))
		poss_moves.append((x+1,y-2))
		poss_moves.append((x-1,y-2))

		my_color = self.current_turn
		for a in poss_moves:
			ret = self._isValidMove((a[0], a[1]), my_color)
			if (ret == 2):
				# yes, blank
				moves.append(a)
			elif (ret == 1):
				# yes, take
				moves.append(a)
			elif (ret == 0):
				#no, same color piece
				pass
			elif (ret == 3):
				#no, off board
				pass

		return moves

	def _movePiece(self):
		# get random piece
		# make valid move with selected piece
		
		moves = []
		peece = self._selectGoodPiece()
		src = (peece[2], peece[3])

		if (peece[0] == 'pawn'):
			moves = self._move_pawn(src)
		elif (peece[0] == 'knight'):
			moves = self._move_knight(src)
		elif (peece[0] == 'bishop'):
			moves = self._move_bishop(src)
		elif (peece[0] == 'queen'):
			moves = self._move_queen(src)
		elif (peece[0] == 'king'):
			moves = self._move_king(src)
		elif (peece[0] == 'rook'):
			moves = self._move_rook(src)


		if moves == None:
			return False
		# pick out a random valid location to move this piece to
		maxnum = len(moves)
		if (maxnum < 1):
			return False
		elif (maxnum == 1):
			selected_num = 0
		else:
			selected_num = random.randrange(0, maxnum - 1)
		dst = moves[selected_num]

		str = "{},{} {},{}\n".format(src[0], src[1], dst[0], dst[1])
		#print peece[0] + ' : ' + str
		self.write(str)

		# keep track internally of where pieces are
		self._movePieceOnBoard(src,dst)
		return True

	def makeValidMove(self):
		# keep trying to make a valid move until it works
		while (self._movePiece() == False):
			pass
		
		# change turn
		if (self.current_turn == 'white'):
			self.current_turn = 'black'
		else:
			self.current_turn = 'white'

		exp = r"OK\n" + self.current_turn.upper() + ": "
		delimm = self.current_turn.upper() + ": "
		self.read(delim=delimm, expect=exp, expect_format="pcre")

	def badMoveValidPieceOnBoard(self):
		# pick valid piece and move it randomly
		#global LOG_ENABLED
		#LOG_ENABLED = True
		peece = self._selectGoodPiece()
		dst = location().getRandGoodLocation()
		too_good = True
		moves = []
		while (too_good):
			# make sure this isn't a valid move for this piece
			if (peece[0] == 'pawn'):
				moves = self._move_pawn((peece[2], peece[3]))
			if (peece[0] == 'king'):
				moves = self._move_king((peece[2], peece[3]))
			if (peece[0] == 'knight'):
				moves = self._move_knight((peece[2], peece[3]))
			if (peece[0] == 'rook'):
				moves = self._move_rook((peece[2], peece[3]))
			if (peece[0] == 'queen'):
				moves = self._move_queen((peece[2], peece[3]))
			if (peece[0] == 'bishop'):
				moves = self._move_bishop((peece[2], peece[3]))
			if dst not in moves:
				# this is not a valid move, which is good
				too_good = False
				#print "{}, {} not found in {}".format(peece[0], dst, moves)

			if too_good:
				# try a new location		
				dst = location().getRandGoodLocation()

		str = "{},{} {},{}\n".format(peece[2], peece[3], dst[0], dst[1])
		#print "badmovevalidpieceONboard: " + str
		self.write(str) # bad move with valid piece (on board)
		exp = "NO\n" + self.current_turn.upper() + ": "
		delimm = self.current_turn.upper() + ": "
		self.read(delim=delimm, expect=exp)
		#LOG_ENABLED = False

	def badMoveValidPieceOffBoard(self):
		# pick valid piece and move it randomly
		peece = self._selectGoodPiece()
		dst = location().getRandBadLocation()

		exp = "NO\n" + self.current_turn.upper() + ": "

		str = "{},{} {},{}\n".format(peece[2], peece[3], dst[0], dst[1])
		#print "badmovevalidpieceOFFboard: {} ".format(len(str)) + str
		
		# if the randomly generated location is > 10 or < 0, the length
		#   will be impacted. that is an illegal move format
		if (len(str) > 7):
			exp = "incorrect input\nNot a legal move format\n" + self.current_turn.upper() + ": "
		self.write(str) # bad move with valid piece (on board)
		
		self.read(length=len(exp), expect=exp)
