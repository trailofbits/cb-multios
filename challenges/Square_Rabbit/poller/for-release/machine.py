from generator.actions import Actions
import random
import string
import struct
import ctypes
import sys

def random_bad_input(max_size=10, min_size=2):
    characters = string.letters + string.digits + ' .\t;:\'"?!@#$&()'
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(characters) for c in range(max_size)) + '\n'

def random_seed():
    characters = string.digits
    num = random.randint(1, 3333333333)

    return str(num) + '\n'

def random_line(max_size=62, min_size=2):
    characters = string.letters + string.digits + ' .\t;:\'"?!@#$&()'
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(characters) for c in range(max_size)) + '\n'


def random_alphanum(max_size, min_size=2):
    alphanum = string.letters + string.digits
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(alphanum) for c in range(max_size))

class Card():
    def __init__(self, face, suit):
        self.face = face
        self.suit = suit

    def print_card(self):
        if self.face == 1:
            return "D"
        elif self.face <= 10:
            return str(self.face)
        elif self.face == 11:
            return "R"
        elif self.face == 12:
            return "B"
        elif self.face == 13:
            return "L"
        else:
            return "ERROR"

    def get_value(self):
        if self.face > 10:
            return 10
        else:
            return self.face

class Hand():
    def __init__(self):
        self.cards = []
        self.has_stayed = False
        self.has_busted = False
        self.has_doubled = False

    def get_card(self, card):
        self.cards.append(card)
        if self.calc_score() > 21:
            self.has_busted = True

    def stay(self):
        self.has_stayed = True

    def doubled(self):
        self.has_doubled = True

    def can_split(self):
        if len(self.cards) > 2:
            return False
        if self.cards[0].face == self.cards[1].face:
            return True
        if self.cards[0].face >= 10 and self.cards[1].face >= 10:
            return True
        return False

    def is_game_over(self):
        if self.has_stayed or self.has_busted:
            return True
        return False

    def print_hand(self, hide_cards=False):
        hand_str = ""
        if hide_cards:
            hand_str += "|{0}|?|".format(self.cards[0].print_card())
        else:
            for card in self.cards:
                hand_str += "|{0}".format(card.print_card())
            hand_str += "|    Score: {0}".format(self.calc_score())
        return hand_str

    def print_selections(self, num_splits):
        select_str = "Select (H/S"
        if len(self.cards) == 2:
            select_str += "/D"
            if self.can_split() and num_splits < 2:
                select_str += "/X"
        select_str += "): "
        return select_str

    def is_soft(self):
        score = 0
        num_aces = 0
        for card in self.cards:
            score += card.get_value()
            if card.get_value() == 1:
                num_aces += 1
        if num_aces > 0 and score <= 11:
            return True
        return False


    def calc_score(self):
        score = 0
        num_aces = 0
        for card in self.cards:
            score += card.get_value()
            if card.get_value() == 1:
                num_aces += 1
        if num_aces > 0 and score <= 11:
            score += 10
        return score

    def calc_payout(self, dealer):
        if self.calc_score() == 21 and len(self.cards) == 2:
            if dealer.calc_score() == 21 and len(self.cards) == 2:
                return (0, "  Pushed.\n")
            else:
                return (1.5, "  Winner!\n")
        elif self.calc_score() > 21:
            return (-1, "  Busted! Better luck next time\n")
        elif dealer.calc_score() > 21:
            return (1, "  Winner!\n")
        elif self.calc_score() == dealer.calc_score():
            return (0, "  Pushed.\n")
        elif self.calc_score() > dealer.calc_score():
            return (1, "  Winner!\n")
        else:
            return (-1, "  Dealer Wins.\n")

class Deck():
    def __init__(self, seed):
        self.a = ctypes.c_uint32(seed).value
        self.b = ctypes.c_uint32(2345678901).value
        self.c = ctypes.c_uint32(3456789012).value
        self.d = ctypes.c_uint32(4567890123).value
        self.cards = []
        self.top_of_deck = 0

        for i in xrange(52):
            self.cards.append(Card(i%13 + 1, i/13))
        self.shuffle()

    def rng(self):
        temp = self.a ^ ctypes.c_uint32(self.a << 7).value
        self.a = self.b
        self.b = self.c
        self.c = self.d
        self.d = (self.d ^ (self.d >> 22)) ^ (temp ^ (temp >> 16))
        return ctypes.c_uint32(self.d).value

    def shuffle(self):
        for i in xrange(10000):
            pos1 = self.rng() % 52
            pos2 = self.rng() % 52

            temp_card = self.cards[pos1]
            self.cards[pos1] = self.cards[pos2]
            self.cards[pos2] = temp_card
        self.top_of_deck = 0

    def shuffle_if_needed(self):
        if self.top_of_deck > int(.65 * 52):
            self.shuffle()

    def draw_card(self):
        card = self.cards[self.top_of_deck]
        self.top_of_deck += 1
        return card


class Squarerabbit(Actions):
    valid_bets = [100, 200, 500, 1000]
    get_seed = ("Enter a number greater than 0: ")

    welcome_screen = ("\n\n*************************\n"
                      "*Welcome to Game Sultan!*\n"
                      "*************************")

    game_menu = (   "Game Sultan: Main Menu\n"
                    "1. Square Rabbit\n"
                    "2. Quit\n\n"
                    "Select:-@ ")

    srabbit_menu = (  "******************\n"
                    "* Square Rabbit! *\n"
                    "******************\n")

    bet_menu = ("Type QUIT to exit to main menu\n"
                "Place Bet (100, 200, 500, 1000): ")

    quit_game = ("Thanks for playing!\n")

    def start(self):
        seed = random_seed()

        self.state['total_money'] = 100000
        self.state['current_bet'] = 0
        self.state['deck'] = Deck(int(seed))
        self.read(length=len(self.get_seed), expect=self.get_seed)
        self.write(seed);
        self.read(length=len(self.welcome_screen), expect=self.welcome_screen)
        self.read(length=len('\n\n'), expect='\n\n')

    def main_menu(self):
        self.read(length=len(self.game_menu), expect=self.game_menu)

    def squarerabbit(self):
        self.write("1\n")
        self.read(length=len(self.srabbit_menu), expect=self.srabbit_menu)

    def quit(self):
        self.write("2\n")
        self.read(length=len(self.quit_game), expect=self.quit_game)

    def bet(self):
        total_money = ("Total Money: ${0}\n\n".format(int(self.state['total_money'])))
        self.read(length=len(total_money), expect=total_money)
        self.read(length=len(self.bet_menu), expect=self.bet_menu)

        self.state['current_bet'] = random.choice(self.valid_bets)
        self.write("{0}\n".format(self.state['current_bet']))

    def quit_squarerabbit(self):
        total_money = ("Total Money: ${0}\n\n".format(int(self.state['total_money'])))
        self.read(length=len(total_money), expect=total_money)
        self.read(length=len(self.bet_menu), expect=self.bet_menu)
        self.write("QUIT\n")

    def play(self):
        i = 0
        insurance = False
        select_str = ""
        game_in_progress = True
        player_has_squarerabbit = False
        all_hands_busted = True
        deck = self.state['deck']
        deck.shuffle_if_needed()

        self.state['dealer_hand'] = Hand()
        self.state['player_hand'] = [Hand()]
        hand = self.state['player_hand'][0]
        for x in xrange(2):
            self.state['player_hand'][0].get_card(deck.draw_card())
            self.state['dealer_hand'].get_card(deck.draw_card())

        if self.state['dealer_hand'].cards[0].face == 1:
            if (self.state['dealer_hand'].calc_score() == 21 and
               self.state['player_hand'][0].calc_score() == 21):
                player_has_squarerabbit = True
                self.state['player_hand'][0].stay()  #End player's turn
            else:
                insurance_choice = random.choice(['y\n', 'n\n'])
                insurance_req = "Dealer has a Duck... Insurance? (y\\n): "
                self.read(length=len(insurance_req), expect=insurance_req)
                self.write(insurance_choice)
                if(insurance_choice == 'y\n'):
                    insurance = True

                if (self.state['dealer_hand'].cards[1].face >= 10):
                    self.state['player_hand'][0].stay()  #End player's turn
                    if insurance:
                        self.state['current_bet'] = 0

        if (self.state['player_hand'][0].calc_score() == 21):
                player_has_squarerabbit = True
                self.state['player_hand'][0].stay()  #End player's turn

        while (game_in_progress):
            i = 0
            hand = Hand()
            all_hands_busted = True
            for hand in self.state['player_hand']:
                if not hand.has_busted:
                    all_hands_busted = False
                if not hand.is_game_over():
                    break
            if not hand.is_game_over():
                dealer_str = "Dealer: {0}\n".format(self.state['dealer_hand'].print_hand(True))
                divider = '----------------\n'
            else:
                dealer = self.state['dealer_hand']
                if not player_has_squarerabbit and not all_hands_busted:
                    while dealer.calc_score() < 17 or (dealer.calc_score() == 17 and dealer.is_soft()):
                        dealer.get_card(deck.draw_card())

                dealer_str = "Dealer: {0}\n".format(self.state['dealer_hand'].print_hand())
                divider = '-------------------------------\n'
                game_in_progress = False

            self.read(length=len(dealer_str), expect=dealer_str)
            self.read(length=len(divider), expect=divider)
            for hand in self.state['player_hand']:
                select_str = ''
                if i == 0:
                    player_str = "Player: {0}\n".format(hand.print_hand())
                else:
                    player_str = "Split {0}: {1}\n".format(i, hand.print_hand())
                i += 1
                self.read(length=len(player_str), expect=player_str)

                if not game_in_progress:
                    payout, win_str = hand.calc_payout(self.state['dealer_hand'])
                    self.state['total_money'] += payout * self.state['current_bet']
                    if (hand.has_doubled):
                        self.state['total_money'] += payout * self.state['current_bet']

                    self.read(length=len(win_str), expect=win_str)
                    if (player_has_squarerabbit and payout != 0):
                        self.read(length=len("Square Rabbit!\n"), expect="Square Rabbit!\n")
                    continue

                if not hand.is_game_over():
                    select_str = hand.print_selections(len(self.state['player_hand']) - 1)
                    self.read(length=len(select_str), expect=select_str)
                    break


            if not game_in_progress:
                if insurance:
                    self.state['total_money'] -= self.state['current_bet'] / 2
                break;

            if select_str == '':
                continue

            if 'X' in select_str:
                split_rand = random.randint(1,1)
                if split_rand == 1:
                    self.write("X\n")
                    split_hand = Hand()
                    split_hand.get_card(hand.cards.pop())
                    hand.get_card(deck.draw_card())
                    split_hand.get_card(deck.draw_card())
                    self.state['player_hand'].append(split_hand)
                    self.read(length=len("\n"), expect="\n")
                    continue
            elif 'D' in select_str:
                double_rand = random.randint(1,4)
                if double_rand == 1:
                    self.write("D\n")
                    hand.doubled()
                    hand.get_card(deck.draw_card())
                    hand.stay()
                    self.read(length=len("\n"), expect="\n")
                    continue

            if(hand.calc_score() <= 16):
                self.write("H\n")
                hand.get_card(deck.draw_card())
                self.read(length=len("\n"), expect="\n")
                continue

            self.write("S\n")
            self.read(length=len("\n"), expect="\n")
            hand.stay()

