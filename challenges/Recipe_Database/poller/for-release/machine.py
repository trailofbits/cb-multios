#!/usr/bin/env python

from generator.actions import Actions
import random


class ProposalGenerator(Actions):


    def start(self):

        self.recipe_book = []

        self.read_main_menu_text()

    def read_main_menu_text(self):

        self.read(delim='\n', expect='\n')
        self.read(delim='\n', expect='1 - Enter a Recipe\n')
        self.read(delim='\n', expect='2 - Find a Recipe\n')
        self.read(delim='\n', expect='3 - Print Tagged Recipes\n')
        self.read(delim='\n', expect='4 - Print Shopping List\n')
        self.read(delim='\n', expect='5 - Exit\n')


    def menu(self):

        pass
        

    def find_recipe(self):

        num_of_recipes = len(self.recipe_book)

        

        if num_of_recipes == 0:
            recipe_to_find = 'alpha'
        else:

         #   recipe_to_find = random.choice([item[0] for item in self.recipe_book])
            num_to_find = random.randint(0, num_of_recipes-1)
            recipe_to_find = self.recipe_book[num_to_find][0]

        self.write('2\n')

        expect_string= 'Enter search term: '
        self.read(length = len(expect_string), expect=expect_string)

        self.write(recipe_to_find + '\n')

        self.read(delim='\n', expect='\n')

        if num_of_recipes > 0:

            self.read(delim='\n', expect='\n')

            expect_string = '\t\t' + recipe_to_find + '\n\n'

            self.read(length = len(expect_string), expect=expect_string)

            expect_string = 'Ingredients\n'
            self.read(length = len(expect_string), expect=expect_string)

            expect_string = "-----------\n"
            self.read(length = len(expect_string), expect=expect_string)

            for item in self.recipe_book[num_to_find][1]:

                expect_string = item + '\n'
                self.read(length = len(expect_string), expect=expect_string)


            self.read(delim='\n', expect='\n')

            expect_string = 'Instructions\n'
            self.read(length = len(expect_string), expect=expect_string)

            expect_string = "------------\n"
            self.read(length = len(expect_string), expect=expect_string)
            
            for item in self.recipe_book[num_to_find][3]:

                expect_string = item + '\n'
                self.read(length = len(expect_string), expect=expect_string)

            self.read(delim='\n', expect='\n')
            self.read(delim='\n', expect='\n')

            expect_string= 'Would you like to tag this recipe? '
            self.read(length = len(expect_string), expect=expect_string)

            self.write('y\n')

            self.recipe_book[num_to_find][4] = 'Y'

        self.read_main_menu_text()


    def print_tagged(self):

        # pass
        self.write('3\n')

        self.read(delim='\n', expect='\n')

        for entry in self.recipe_book:

            if entry[4] == 'N':
                continue

            expect_string = '\t\t' + entry[0] + '\n\n'

            self.read(length = len(expect_string), expect=expect_string)

            expect_string = 'Ingredients\n'
            self.read(length = len(expect_string), expect=expect_string)

            expect_string = "-----------\n"
            self.read(length = len(expect_string), expect=expect_string)

            for item in entry[1]:

                expect_string = item + '\n'
                self.read(length = len(expect_string), expect=expect_string)


            self.read(delim='\n', expect='\n')

            expect_string = 'Instructions\n'
            self.read(length = len(expect_string), expect=expect_string)

            expect_string = "------------\n"
            self.read(length = len(expect_string), expect=expect_string)
            
            for item in entry[3]:

                expect_string = item + '\n'
                self.read(length = len(expect_string), expect=expect_string)

            self.read(delim='\n', expect='\n')
            self.read(delim='\n', expect='\n')


        self.read_main_menu_text()

    def exit(self):

        self.write('5\n')


    def enter_recipe(self):


        ingredients = []
        measures = []
        steps = []

        self.write('1\n')


        expect_string = 'Enter Title: '

        self.read(length=len(expect_string), expect=expect_string)

        # actual input expected to be 100 bytes or less, do 105 to test bounds checking
        title=''.join(random.choice('abcdefghijklmnop') for _ in range(65))

        if len(title) > 100:
            self.prop_name=title[:100]
        else:
            self.prop_name=title

        self.write(title + '\n')


        # enter the ingredients for the recipe
        expect_string = 'Enter the measurement and ingredients, one per line.  A blank line ends.\n\n'

        self.read(length=len(expect_string), expect=expect_string)

        num_ingredients = random.randint(3, 20)

        for x in range(0, num_ingredients):

            amount = random.choice('123456789')
            unit = random.choice(['tsp', 'tbsp', 'cup', 'oz', ''])

            if unit != '':
                measure= '{} {}'.format(amount, unit)
            else:
                measure= amount

            ingredient=''.join(random.choice('abcdefghijklmnop ') for _ in range(25))

            temp_str = measure + ' ' + ingredient

            ingredients.append(ingredient)
            measures.append(temp_str)

            self.write(temp_str + '\n')

        self.write('\n')


        # enter the instructions for the recipe
        expect_string = "Enter the step by step instructions.  A blank line to end.\n\n"

        self.read(length=len(expect_string), expect=expect_string)

        num_steps = random.randint(3, 20)

        for x in range(0, num_steps):

            expect_string = 'Step {}: '.format(x+1)

            self.read(length=len(expect_string), expect=expect_string)

            temp_str=''.join(random.choice('abcdefghijklmnop ') for _ in range(190))

            steps.append(temp_str)

            self.write(temp_str + '\n')

        expect_string = 'Step {}: '.format(x+2)

        self.read(length=len(expect_string), expect=expect_string)

        self.write('\n')

        self.recipe_book.append([title, measures, ingredients, steps, 'N'])

        self.read_main_menu_text()


    def print_shopping_list(self):

        pass

        my_list = []

        self.write('4\n')

        self.read(delim='\n', expect='\n')

        expect_string = "Shopping List\n"
        self.read(length=len(expect_string), expect=expect_string)

        expect_string = "-------------\n"
        self.read(length=len(expect_string), expect=expect_string)


        for entry in self.recipe_book:

            if entry[4] == 'N':
                continue


            my_list = my_list + entry[2]


        if len(my_list) > 0:

            my_list.sort()

            for entry in my_list:
                self.read(delim='\n', expect=entry)


        self.read(delim='\n', expect='\n')

        self.read_main_menu_text()


    def create_measurement(self):


        pass

        
