from generator.actions import Actions
import random
import string
import struct
import numpy as np
import math
import datetime as dt

MAX_NAME = 20
MAX_DESC = 200

def random_word(max_size=7, min_size=3):
    characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ("".join(random.choice(characters) for c in range(max_size))).lower()

def random_text(max_words=32, min_words=3):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
    return text

def random_username(max_size=MAX_NAME, min_size=1):
    return "Player"
#return random_word(MAX_NAME, 1)

class Player:
    def __init__(self, name, flair):
        self.name = name
        self.flair = flair
        self.score = 0
        self.num_rps_wins = 0
        self.num_hi_lo_wins = 0
        self.num_ttt_wins = 0
        self.num_ttt_consecutive_draws = 0
        self.ttt_go_first = True
        self.num_ttt_moves = 0

    def print_stats(self, _read_fn):
        _read_fn("---%s's stats---\n" % (self.name))
        _read_fn("Current Score: %d\n" % (self.score))
        _read_fn("Number of Three in a row draws: %d\n" % (self.num_ttt_consecutive_draws))
        _read_fn("Number of Three in a row wins: %d\n" % (self.num_ttt_wins))
        _read_fn("Number of Hammer, Sheet, Sheers wins: %d\n" % (self.num_rps_wins))
        _read_fn("Number of Guess my number wins: %d\n" % (self.num_hi_lo_wins))
        _read_fn("\n")

class WarGames(Actions):
    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _read_game_menu(self):
        self.player.print_stats(self._read)
        self.read("Choose a game to play:\n")
        self.read("--Easy--\n")
        self.read("1. Hammer, Sheet, Sheers\n")
        self.read("--Medium--\n")
        self.read("2. Guess my number\n")
        self.read("--Impossible--\n")
        self.read("3. Three in a row\n")
        self.read("4. Give up\n\n")
        self.read("Shall we play a game?\n")
        self.read("Game # ")

    def _read_ttt_board(self):
        self.read(expect='|[HC-]|[HC-]|[HC-]|', expect_format='pcre', delim='\n')
        self.read(expect='|[HC-]|[HC-]|[HC-]|', expect_format='pcre', delim='\n')
        self.read(expect='|[HC-]|[HC-]|[HC-]|', expect_format='pcre', delim='\n')

    def _ttt_move(self, y, x, display_twice=True):
        self._read("Enter move [y,x]: ")
        self.write('%d,%d\n' % (y,x))
        self._read('\n')
        self._read_ttt_board()
        if display_twice:
            self._read('\n')
            self._read_ttt_board()

    def start(self):
        #self.delay(100)
        self.player = None
        self.hi_lo_idx = 0
        self.rps_idx = 0
        self.ttt_idx = 0

    def new_user_menu(self):
        self._read("1. Register New Player\n")
        self._read("2. Exit\n")
        self._read("> ")

    def new_user(self):
        self.write('1\n')
        self._read("Flair 1 = Terminator\n")
        self._read("Flair 2 = 2001\n")
        self._read("Flair 3 = Collosus\n")
        self._read("Enter player information: [name,flair]\n")
        self.player = Player(random_username(8), random.randint(1,3))
        self.write("%s, %d\n" % (self.player.name, self.player.flair))
        self._read("\nWelcome to WarGames, %s. It's just you vs. me\n" % (self.player.name))

    def game_menu(self):
        self._read_game_menu()

    def play_rps(self):
        self.write('1\n')
        cchoice_idx = (struct.unpack('<B', self.magic_page[(self.rps_idx):(self.rps_idx + 1)])[0]) % 3
        player_choice = ["HAMMER", "SHEET", "SHEERS"][random.randint(0,2)]
        computer_choice = ["HAMMER", "SHEET", "SHEERS"][cchoice_idx]
        self.rps_idx += 1
        self.rps_idx %= 4096

        self._read("Choose [HAMMER, SHEET, SHEERS]: ")
        self.write("%s\n" % player_choice)

        self._read("%s v %s\n" % (player_choice, computer_choice))
        if player_choice == computer_choice:
            self._read("It's a tie!\n")
            self.player.score += 0
        elif player_choice == "HAMMER" and computer_choice == "SHEET":
            self._read("You Lose.\n")
        elif player_choice == "HAMMER" and computer_choice == "SHEERS":
            self._read("You Win!\n")
            self.player.score += 1000
            self.player.num_rps_wins += 1
        elif player_choice == "SHEET" and computer_choice == "SHEERS":
            self._read("You Lose.\n")
        elif player_choice == "SHEET" and computer_choice == "HAMMER":
            self._read("You Win!\n")
            self.player.score += 1000
            self.player.num_rps_wins += 1
        elif player_choice == "SHEERS" and computer_choice == "HAMMER":
            self._read("You Lose.\n")
        elif player_choice == "SHEERS" and computer_choice == "SHEET":
            self._read("You Win!\n")
            self.player.score += 1000
            self.player.num_rps_wins += 1

    def play_hi_lo(self):
        self.write('2\n')
        winner = struct.unpack('<I', self.magic_page[(self.hi_lo_idx):(self.hi_lo_idx + 4)])[0]
        winner &= 0xFFFF
        self.hi_lo_idx += 4
        self.hi_lo_idx %= 4096
        num_guesses = 16
        self._read("Enter max value (Default=65535): ")
        self.write('\n')
        while num_guesses:
            self._read("Guess the number [%d guesses left]: " % (num_guesses))
            if random.randint(0,99) == 0:
                self.write('%d\n' % winner)
                self._read("You won!\n")
                self.player.score += 1000
                self.player.num_hi_lo_wins += 1
                return
            else:
                guess = random.randint(0, 65534)
                guess = guess +1 if guess == winner else guess
                self.write('%d\n' % guess)
                if guess > winner:
                    self._read("Too High\n")
                elif guess < winner:
                    self._read("Too Low\n")
                num_guesses -= 1
        self._read("Sorry, you lost. Try practicing with a lower max value.\n")
        #self._read("The number was: %d\n" % winner)

    def play_ttt(self):
        self.write('3\n')
        self._read("You're playing 3 in a row. Good luck!\n")
        if self.player.ttt_go_first:
            self._read_ttt_board()
            if random.randint(0,1):
                self._ttt_move(0,0)
                self._ttt_move(1,2)
                self._ttt_move(2,2)
                self._read("You lost.\n")
                self.player.num_ttt_consecutive_draws = 0
            else:
                self._ttt_move(2,0)
                self._ttt_move(2,1)
                self._ttt_move(0,0)
                self._ttt_move(1,2)
                self._ttt_move(0,2, False)
                self._read("It's a tie!\n")
                self.player.num_ttt_consecutive_draws += 1
            self.player.ttt_go_first = False
        else:
            corner = (struct.unpack('<I', self.magic_page[(self.ttt_idx):(self.ttt_idx + 4)])[0]) % 4
            self.ttt_idx += 4
            self.ttt_idx %= 4096
            self._read("\n")
            self._read_ttt_board()
            tie = random.randint(0,1)
            if corner == 0:
                if tie:
                    self._ttt_move(1,1)
                    self._ttt_move(0,2)
                    self._ttt_move(1,0)
                    self._ttt_move(2,2)
                    self.player.num_ttt_consecutive_draws += 1
                    self._read("It's a tie!\n")
                else:
                    self._ttt_move(0,1)
                    self._ttt_move(0,2)
                    self._read("You lost.\n")
                    self.player.num_ttt_consecutive_draws = 0
            elif corner == 1:
                if tie:
                    self._ttt_move(1,1)
                    self._ttt_move(0,1)
                    self._ttt_move(1,0)
                    self._ttt_move(2,2)
                    self.player.num_ttt_consecutive_draws += 1
                    self._read("It's a tie!\n")
                else:
                    self._ttt_move(2,1)
                    self._ttt_move(0,1)
                    self._ttt_move(2,2)
                    self._read("You lost.\n")
                    self.player.num_ttt_consecutive_draws = 0
            elif corner == 2:
                if tie:
                    self._ttt_move(1,1)
                    self._ttt_move(1,0)
                    self._ttt_move(2,2)
                    self._ttt_move(0,2)
                    self.player.num_ttt_consecutive_draws += 1
                    self._read("It's a tie!\n")
                else:
                    self._ttt_move(1,1)
                    self._ttt_move(0,1)
                    self._read("You lost.\n")
                    self.player.num_ttt_consecutive_draws = 0
            elif corner == 3: #
                if tie:
                    self._ttt_move(1,1)
                    self._ttt_move(2,1)
                    self._ttt_move(0,2)
                    self._ttt_move(1,0)
                    self.player.num_ttt_consecutive_draws += 1
                    self._read("It's a tie!\n")
                else:
                    self._ttt_move(0,1)
                    self._ttt_move(1,2)
                    self._ttt_move(2,0)
                    self._read("You lost.\n")
                    self.player.num_ttt_consecutive_draws = 0
            self.player.ttt_go_first = True


    def player_give_up(self):
        self.write('4\n')
        self._read("See you next time, %s\n" % (self.player.name))
        self.player = None

    def exit(self):
        self.write('2\n')
        self._read("Exited\n")

