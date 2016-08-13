from generator.actions import Actions
import random
import string
import struct

class Hangman(Actions):
    with open('examples/hangman/words.txt') as word_fh:
        words = [x.strip() for x in word_fh.readlines()]

    def _match(self, data):
        self.read(length=len(data), expect=data)

    def start(self):
        self._match('Password: ')

    def good_password(self):
        self.write("HANGEMHIGH!\n")
        self._match("Welcome to Hangman Blondie!\n")

    def bad_password(self):
        sequence = ''.join([chr(x) for x in range(256)]).replace('\x00','').replace('\n','')
        data = self.random_buffer(random.randint(1, 254), sequence) + "\n"
        self.write(data)
        return -1

    def _high_score(self):
        self._match("Congratulations blondie, add yourself to the high score list\n")
        self._match("What is your name? ")
        
        # send a random name
        banned = '\x25\x00\x0a\x5c'
        sequence = ''.join([chr(x) for x in range(256)])
        for i in banned:
            sequence = sequence.replace(i, '')
        name = self.random_buffer(random.randint(1, 30), sequence) + "\n"
        self.write(name)

        self._match("New member of the HOF: %s" % name)

    def _bad_choice(self):
        # any character, and then anything but 'newline' causes a failure
        sequence = ''.join([chr(x) for x in range(256)])
        response = random.choice(sequence)

        sequence = sequence.replace('\n', '')
        response += random.choice(sequence)
        
        self.write(response)
        self._match("Invalid guess, game over.\n")

    def _repeat_choice(self, used):
        # pick a character from an existing stream
        self._send_from(used)

    def _get_word(self):
        value = random.randint(0, 0xFFFFFFFF)
   
        offset = value % 4093

        magic_value = struct.unpack('<L', self.magic_page[offset:offset+4])[0]
        word = Hangman.words[magic_value % len(Hangman.words)]

        return word, struct.pack('<L', value)

    def _send_from(self, sequence):
        char = random.choice(sequence)
        self.write('%s\n' % char)
        return char

    def _replace_offset(self, sequence, offset, value):
        result = sequence[:offset] + value + sequence[offset+1:]
        return result

    def play_game(self):
        self._match("Choose your word seed. Please send 4 bytes\n")

        word, location = self._get_word()
        self.write(location)
        self.comment('word should be: %s' % word)

        used = ''
        current = '_' * len(word)
        available = string.lowercase
        correct = [x for x in string.lowercase if x in word]
        incorrect = [x for x in string.lowercase if x not in word]

        # bleck
        gallows = "   ---\n   | |\n     |\n     |\n     |\n     |\n -----\n |   |\n"
        indexes = [17, 24, 23, 25, 31, 37, 39]
        parts = ['O', '|', '/', '\\', '|', '/', '\\']

        bad_guesses = 0

        while True:
            self._match("\n" + gallows + "\n")
            self._match('used:      "%s"\n' % used)
            self._match('available: "%s"\n' % available)
            self._match('\ncurrent: %s\n' % current)
            self._match("\nYour guess: ")

            # Very rarely, send invalid input which causes a failure
            if self.chance(.00001):
                self._bad_choice()
                return

            # Very rarely, repeat a choice.
            if len(used) and self.chance(.00001):
                self._send_from(used)
                self._match("Invalid guess, game over.\n")
                return

            # Do we choose correctly?
            if self.chance(.50):
                # print "GOT", repr(correct)
                sent = self._send_from(correct)
                correct.remove(sent)
                available = available.replace(sent, '')
                locations = [i for i, x in enumerate(word) if x == sent]
                for i in locations:
                    current = self._replace_offset(current, i, sent)

                used += sent

                if '_' in current:
                    self._match("\nMiraculously, you have manage to prolong Tuco's life.\n")
                else:
                    self._match("\nNice shot Blondie, you freed Tuco.\n")
                    self._match("The correct word is: %s.\n" % word)
                    self._high_score()
                    return
            else:
                # choose & send an incorrect letter
                sent = self._send_from(incorrect)
                incorrect.remove(sent)
                available = available.replace(sent, '')
                used += sent

                gallows = self._replace_offset(gallows, indexes[bad_guesses], parts[bad_guesses])
                # gallows = gallows[:indexes[bad_guesses]] + parts[bad_guesses] + gallows[indexes[bad_guesses]+1:]

                bad_guesses += 1 
                # handle adding a part
                if bad_guesses == len(parts):
                    self._match("\n" + gallows + "\n")
                    self._match("\nBlondie, you missed, Tuco has been hanged.\n")
                    self._match("The correct word is: %s.\n" % word)
                    return
                else:
                    self._match("\nHaha, Tuco is feeling that rope a little more!\n")

    def play_again(self):
        self._match("Play again (y/n)? ")

    def play_again_yes(self):
        self.write('%s\n' % random.choice('yY'))
    
    def play_again_no(self):
        self.write('%s\n' % random.choice('nN'))

    def play_again_bad_answer(self):
        self.comment('play again bad answer')
        sequence = ''.join([chr(x) for x in range(256)])
        for x in 'yYnN':
            sequence = sequence.replace(x, '')

        data = random.choice(sequence)
        sequence = sequence.replace('\n', '')
        data += random.choice(sequence)

        self.write(data)
