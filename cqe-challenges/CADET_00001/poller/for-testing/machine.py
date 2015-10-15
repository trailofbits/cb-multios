from generator.actions import Actions
import random
import string

class Palindrome(Actions):
    def start(self):
        pass

    def banner(self):
        # Confirm the initial empty line
        self.read(delim='\n', expect='\n')
        # Confirm the actual banner
        self.read(delim='\n', expect='Welcome to Palindrome Finder\n')

    def request(self):
        # Skip the empty line
        self.read(delim='\n', expect='\n')
        # Confirm the request
        self.read(length=37, expect='\tPlease enter a possible palindrome: ')

    def palindrome(self):
	halfword = self.random_string(random.randint(1, 16))
        self.write(halfword + halfword[::-1] + "\n")
        self.read(delim='\n', expect="\t\tYes, that's a palindrome!\n")

    def not_palindrome(self):
	word = self.random_string(random.randint(2, 32))
	while self.is_palindrome(word):
		word = self.random_string(random.randint(2, 32))
        self.write(word + "\n")
        self.read(delim='\n', expect="\t\tNope, that's not a palindrome\n")

    def is_palindrome(self, word):
	for i in range(0, len(word) / 2):
		if word[i] != word[-i - 1]:
			return False
	return True

    def random_string(self, size):
        chars = string.letters + string.digits
        return ''.join(random.choice(chars) for _ in range(size))
