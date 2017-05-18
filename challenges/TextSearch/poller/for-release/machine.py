from generator.actions import Actions
import math
import random
import string
import struct
import re

def random_printable(max_size, is_text=True, min_size=1):
    if is_text:
        printable = "".join(set(string.printable) - set(' \x0b\x0c\r\n'))
    else:
        printable = "".join(set(string.printable) - set(' \\()*+?&|[]^.${}#<=\t\n\r\x0b\x0c'))
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(printable) for c in range(max_size))

def random_operator():
    operator = '0*+?|'
    op = random.choice(operator)

    if op == '0':
        return ''
    if random.randint(0,10) == 0:
        return '\\' + op

    return op

def random_text():
    it = random.randint(1, 50)
    text = ""
    for i in xrange(it):
        text += random_printable(10) + ' '
        if i % 3:
            text += '\n'

    while(text[-1] == '\n'):
        text = text[:-1]

    return text

def random_search_str():
    it = random.randint(1, 5)
    sstr = ''
    for i in xrange(it):
        sstr = random_printable(1, False)
        if random.randint(0,7) == 0:
            sstr = '(' + sstr + ')'
        elif random.randint(0,15) == 0:
            sstr = '[' + sstr + ']'
        elif random.randint(0,20) == 0:
            sstr += ' '
        sstr += random_operator()

    while(sstr[-1] == '|' or sstr[-1] == '\\'):
        sstr = sstr[:-1]

    return sstr

class TextSearch(Actions):
    menu_str = (
        "Text Searcher: Main Menu\n" +
        "1. Enter Text\n" +
        "2. Enter Search String\n" +
        "3. Line Search - Partial Matches\n" +
        "4. Line Search - Exact Matches\n" +
        "5. Print Text\n" +
        "6. Print Search String\n" +
        "7. Search Text\n" +
        "8. Quit\n\n"
    )
    select_str = "Select: "

    enter_text_str = "Enter text to search\n"
    enter_search_str= "Enter search string\n"

    no_text_str = "Input text has not been received\n"
    no_search_str = "Search text has not been received\n"

    bad_selection = "Bad Selection\n"
    exit_str = "Exiting..."

    def _read(self, string):
        self.read(length=len(string), expect=string)

    def _read_status_bar(self):
        if self.text:
            if len(self.text) > 15:
                self._read("[Text={0}...]\n".format(self.text[:15]))
            else:
                self._read("[Text={0}]\n".format(self.text))


        if self.search_str:
            if len(self.search_str) > 15:
                self._read("[SearchString={0}...]\n".format(self.search_str[:15]))
            else:
                self._read("[SearchString={0}]\n".format(self.search_str))

        if self.match == 'PARTIAL':
            self._read("[LineMatching=Partial]\n")
        else:
            self._read("[LineMatching=Exact]\n")

    def _read_text(self):
        if self.text:
            self._read("--Text--\n{0}\n".format(self.text))
        else:
            self._read("--Text--\n\n")

    def _read_search_str(self):
        if self.search_str:
            self._read("--Search String--\n{0}\n".format(self.search_str))
        else:
            self._read("--Search String--\n\n")

    def start(self):
        self.text = ''
        self.search_str = ''
        self.match = 'PARTIAL'

    def menu(self):
        self._read('\n')
        self._read(self.menu_str)
        self._read_status_bar()
        self._read(self.select_str)

    def enter_text(self):
        self.write('1\n')
        self._read(self.enter_text_str)
        self.text = random_text()
        self.write(self.text)
        self.write('\n')
        self.write('\n')
        self.write('\n')

    def enter_search(self):
        self.write('2\n')
        self._read(self.enter_search_str)
        self.search_str = random_search_str()
        self.write(self.search_str)
        self.write('\n')

    def line_set_partial_match(self):
        self.write('3\n')
        self.match = 'PARTIAL'

    def line_set_exact_match(self):
        self.write('4\n')
        self.match = 'ALL'

    def print_text(self):
        self.write('5\n')
        self._read_text()

    def print_search(self):
        self.write('6\n')
        self._read_search_str()

    def search_text(self):
        self.write('7\n')
        if not self.text:
            self._read(self.no_text_str)
        elif not self.search_str:
            self._read(self.no_search_str)

        for line in self.text.split('\n'):
            if not line:
                continue
            if self.match == 'ALL':
                match = re.findall(self.search_str, line)
                if "".join(match) == line:
                    self._read(line)
                    self._read('\n')
            elif self.match == 'PARTIAL':
                match = re.findall(self.search_str, line)
                if ''.join(match):
                    self._read(line)
                    self._read('\n')

    def quit(self):
        self.write('8\n')
        self._read(self.exit_str)


