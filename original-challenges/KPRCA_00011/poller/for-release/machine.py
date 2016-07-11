#!/usr/bin/env python

from generator.actions import Actions
import random
import string

MOVIES = [
  ("The Shawshank Redemption", "Two imprisoned men bond over a number of years, finding solace and eventual\n     redemption through acts of common decency.", 1994, 93, "Other", "R"),
  ("The Godfather", "The aging patriarch of an organized crime dynasty transfers control of his clandestine\n     empire to his reluctant son.", 1972, 92, "Other", "R"),
  ("The Dark Knight", "When Batman, Gordon have Harvey Dent launch an assault on the mob, they let the clown\n     out of the box, the Joker, bent on turning Gotham on itself and bringing any heroes\n     down to his level.", 2008, 90, "Action", "PG13"),
  ("Inception", "A thief who steals corporate secrets through use of dream-sharing technology is given the\n     inverse task of planting an idea into the mind of a CEO.", 2010, 88, "Action", "PG13"),
  ("The Matrix", "A computer hacker learns from mysterious rebels about the true nature of his reality and\n     his role in the war against its controllers.", 1999, 87, "Action", "R"),
  ("Modern Times", "The Tramp struggles to live in modern industrial society with the help of a young\n     homeless woman.", 1936, 86, "Comedy", "G"),
  ("About Time", "At the age of 21, Tim discovers he can travel in time and change what happens and has\n     happened in his own life. His decision to make his world a better place by getting\n     a girlfriend turns out not to be as easy as you might think.", 2013, 78, "Romance", "R"),
  ("Yes Man", "A guy challenges himself to say \"yes\" to everything for an entire year.", 2008, 69, "Comedy", "PG13"),
  ("The Conjuring", "Paranormal investigators Ed and Lorraine Warren work to help a family terrorized\n     by a dark presence in their farmhouse.", 2013, 75, "Horror", "R"),
  ("The Lion King", "Lion cub and future king Simba searches for his identity. His eagerness to please others\n     and penchant for testing his boundaries sometimes gets him into trouble.", 1994, 85, "Other", "G")
]

def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

class ARentMovie(Actions):
    def start(self):
        self.state['rented'] = []

        self.read(delim='\n', expect='========= Movie Rental Service v0.1 =========\n')
        self.read(delim='\n', expect='   . . . Initializing the inventory . . .\n')
        self.read(delim='\n', expect='         (movie info from IMDb.com)\n')
        self.read_string('=============================================')

    def read_string(self, s):
        self.read(length=len(s), expect=s)

    def read_movie(self, movies, idx):
        title, desc, year, score, genre, rating = movies[idx]
        self.read_string('[%d] %s (%d, %s) - %s [%d/100]\n  => %s\n'
            % (idx+1, title, year, rating, genre, score, desc))

    def read_movies(self):
        self.read_string('\nMovies (Full)\n--------------\n')
        for x in xrange(len(MOVIES)):
            self.read_movie(MOVIES, x)
        self.read_string('--------------\n%d movie(s)\n' % len(MOVIES))

    def menu(self):
        self.read_string('\n1. List movies\n2. Rent movie\n3. Return movie\n4. Admin mode\n5. Exit\n\nChoice: ')

    def list_movie(self):
        self.write('1 list\n')
        self.read_movies()
        self.read_string('\nMovies (Rented)\n--------------\n')
        for x in xrange(len(self.state['rented'])):
            self.read_movie(map(lambda x: MOVIES[x], self.state['rented']), x)
        self.read_string('--------------\n%d movie(s)\n' % len(self.state['rented']))

    def rent_movie(self):
        self.write('2 rent\n')
        self.read_movies()
        
        self.read_string('Enter movie id: ')
        if random.randint(1, 100) <= 15:
            self.write('%d\n' % random.randint(11, 200))
            self.read_string('[ERROR] Invalid movie id. Try again.\n')
            self.read_string('Enter movie id: ')

        idx = random.randint(0, 9)
        if random.randint(1, 100) <= 75:
            for i in xrange(0, 10):
                if i not in self.state['rented']:
                    idx = i
                    break

        self.write('%d\n' % (idx+1))
        if idx in self.state['rented']:
            self.read(delim='\n', expect='Sorry, [%s] is already rented at this time. Please try again later.\n' % MOVIES[idx][0])
        else:
            self.read(delim='\n', expect='Successfully rented [%s]! Enjoy!\n' % MOVIES[idx][0])
            self.state['rented'].append(idx)

    def return_movie(self):
        self.write('3 return\n')
        self.read_string('\nMovies (Rented)\n--------------\n')
        for x in xrange(len(self.state['rented'])):
            self.read_movie(map(lambda x: MOVIES[x], self.state['rented']), x)
        self.read_string('--------------\n%d movie(s)\n' % len(self.state['rented']))
        if len(self.state['rented']) == 0:
            self.read(delim='\n', expect='[ERROR] All the movies are in our inventory.\n')
            return
        while True:
            self.read_string('Enter movie id: ')
            if random.randint(1, 100) <= 15:
                idx = random.randint(11, 200)
            elif random.randint(1, 100) <= 80:
                idx = random.randint(1, len(self.state['rented']))
            else:
                idx = random.randint(1, 10)
            self.write('%d\n' % idx)
            if idx <= len(self.state['rented']):
                break
            self.read(delim='\n', expect='[ERROR] Invalid movie id. Try again.\n')
        idx = self.state['rented'].pop(idx - 1)
        self.read(delim='\n', expect='Successfully returned [%s]! Thank you!\n' % MOVIES[idx][0])

    def try_login(self):
        self.write('4 login\n')
        self.read_string('username: ')
        if random.randint(1, 100) <= 80:
            self.write('admin\n')
            self.read_string('password: ')
            self.write('%s\n' % random_string(20))
        else:
            self.write('%s\n' % random_string(15))
        self.read(delim='\n', expect='[ERROR] Permission Denied: Wrong credentials\n')

    def invalid_menu(self):
        if random.randint(0, 1) == 0:
            self.write('%d invalid\n' % random.randint(6, 9))
        else:
            self.write('%s invalid\n' % random_string(10))
        self.read(delim='\n', expect='[ERROR] Invalid menu. Please select again.\n')

    def quit(self):
        self.write('5 quit\n')
        self.read(delim='\n', expect='Bye!\n')
