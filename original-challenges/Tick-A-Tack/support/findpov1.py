#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
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

# The goal is to determine where in the PI values array the simulated player
# should start, such that when repeated games are played, both the player 
# and computer win 257 games causing both scores to wrap back to 0.

def is_goal_score(scores):
	# goal condition
	if scores['player'] == 257 and scores['computer'] == 257:
		return True
	else:
		return False

def is_stopping_score(scores):
	# short circut condition
	if scores['player'] >= 258 or scores['computer'] >= 258:
		return True
	else:
		return is_goal_score(scores)

def run_single_game(game):

	# the order of calling have_winner and have_moves_remaining is important
	while not game.have_winner() and game.have_moves_remaining():
		# process one move
		if game.is_players_turn():
			p_move = game.player_valid_random_move()
			bad_update = game.update_board(p_move)
			if bad_update:
				print("Error: player_valid_random_move() produced invalid move.")
				break;
		else:
			c_move = game.computer_valid_random_move()
			bad_update = game.update_board(c_move)
			if bad_update:
				print("Error: computer_valid_random_move() produced invalid move.")
				break;

		game.move_complete()

	# game is done, update scores
	game.update_score()

def run_game_sequence(index, player_char):
	from tickatack import TickATackGame
	t = TickATackGame(index)
	replay = 0

	while(not is_stopping_score(t.get_scores())):
		# init game
		t.init_game(replay, player_char)

		# play one game
		run_single_game(t)

		# set replay to keep score in follow-on games
		replay = 1

	return {'index': index, 'player_char': player_char, 'scores': t.get_scores()}

def main():
	# loop through 800 indices of PI from PI_PRNG
	PI_INDICES = 800
	game_result = {}

	for i in range(0, PI_INDICES):
		# run a series of games where in each sequence the player starts at
		# a different pi index. The computer always starts at the 0 index.

		# The player is always P.
		game_result = run_game_sequence(i, 'P')
		if is_goal_score(game_result['scores']):
			print("SUCCESS: player_char: {0}, pi_index: {1}, scores: p={2}/c={3}".format(
				game_result['player_char'],
				game_result['index'],
				game_result['scores']['player'],
				game_result['scores']['computer']))
			return

		# The player is always Q.
		game_result = run_game_sequence(i, 'Q')
		if is_goal_score(game_result['scores']):
			print("SUCCESS: player_char: {0}, pi_index: {1}, scores: p={2}/c={3}".format(
				game_result['player_char'],
				game_result['index'],
				game_result['scores']['player'],
				game_result['scores']['computer']))
			return


if __name__ == '__main__':
	main()