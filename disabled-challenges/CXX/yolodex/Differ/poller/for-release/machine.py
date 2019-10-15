from generator.actions import Actions
import random
import string
import struct
import StringIO

#define MAX_MSGS 5
#define MAX_RCPT 16
#define MAX_ADDR_LEN 32
#define MAX_DATA 512
#define MAX_USER_LEN 64
#define MAX_PASS_LEN 64
#define MAX_LINE 64

def random_word(max_size=10, min_size=2):
    characters = string.letters
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ''.join(random.choice(characters) for c in range(max_size))

def random_line(max_size=8, min_size=1):
    line = random_word()
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    for x in xrange(max_size):
        line += ' ' + random_word()
    return line + '\n'


def vulnerable_sfiles(file_name1, file_name2):
    magic = struct.pack('3s', "SFP")
    file_type = struct.pack('b', 1)
    format_p1 = struct.pack('16s', file_name1)
    format_p2 = struct.pack('16s', file_name2)

    data_p1 = ''
    data_p2 = ''

    y = 1
    for x in xrange(1000):
        if x == 961:
            line = random_line(5000, 5000)
        else:
            line = random_line()

        if x == (y * y):
            data_p1 += line
            data_p2 += random_line()
            y += 1
        else:
            data_p1 += line
            data_p2 += line

    sfilesize1 = struct.pack('i', len(data_p1))
    sfilesize2 = struct.pack('i', len(data_p2))
    sfile1 = (magic + file_type + format_p1 + sfilesize1 + data_p1)
    sfile2 = (magic + file_type + format_p2 + sfilesize2 + data_p2)

    return sfile1, sfile2



class Match():
    def __init__(self):
        self.l_idx = 0
        self.r_idx = 0
        self.length = 0

    def __repr__(self):
        return "{l_idx = %d, r_idx = %d, length = %d}" % (self.l_idx, self.r_idx, self.length)

    def __str__(self):
        return "{l_idx = %d, r_idx = %d, length = %d}" % (self.l_idx, self.r_idx, self.length)

class Sfile():
    def __init__(self, is_binary, file_name):
        self.magic = struct.pack('3s', "SFP")
        self.file_type = struct.pack('b', is_binary)
        self.sfile_name = file_name
        self.data = ''
        self.sfilesize = 0
        self.random_data()

    def copy_sfile(self, sfile):
        self.magic = sfile.magic
        self.file_type = sfile.file_type
        self.sfile_name = sfile.sfile_name + "-MOD"
        self.data = ''
        self.sfilesize = 0
        self.scramble_data(sfile.data)

    def random_data(self):
        self.data = ''
        for x in xrange(150):
            self.data += random_line()
        self.sfilesize = struct.pack('i', len(self.data))

    def scramble_data(self, data):
        for line in StringIO.StringIO(data).readlines():
            if random.randint(0, 1):                #50% chance line is same
                self.data += line
            else:
                if random.randint(0,1):             #25% chance modify lines
                    line = list(line)[random.randint(0, len(line) - 1)] = 'Z'
                    line = "".join(line)
                    self.data += line
                elif random.randint(0,1):        #12.5% chance add lines
                    for x in xrange(random.randint(1,25)):
                        self.data += random_line()
                else:                               #12.5% chance remove line
                    continue
        self.sfilesize = struct.pack('i', len(self.data))

    def raw_sfile(self):
        raw = (self.magic + self.file_type + struct.pack('16s', self.sfile_name) + self.sfilesize + self.data)

        return raw

    def get_no_ws_file_lines(self):
        return [l.replace(" ", "").replace("\t", "") for l in self.data.splitlines()]

    def get_file_lines(self):
        return self.data.splitlines()

class SlowDiff(Actions):
    select_str = "::-> "
    load_success_str = "Successfully Loaded File\n"

    def _get_menu_str(self):
        menu_str = (
            "File Comparer ver 1.0\n" +
            "---------------------\n" +
            "Select an option:\n" +
            "1. Load File 1\n" +
            "2. Load File 2\n"
        )

        if self.ignore_whitespace == "Disabled":
            menu_str += "3. Enable Ignore Whitespace\n"
        else:
            menu_str += "3. Disable Ignore Whitespace\n"

        if self.treat_as_ascii == "Disabled":
            menu_str += "4. Treat Files as Ascii\n"
        else:
            menu_str += "4. Use Native File Type\n"

        menu_str += (
            "5. Compare files\n" +
            "6. Quit\n\n"
        )
        return menu_str

    def _read(self, string):
        self.read(length=len(string), expect=string)

    def _read_menu(self):
        self._read(self._get_menu_str())
        self._read("File 1: {0} <> File 2: {1}\n".format(self.sfile1_name, self.sfile2_name))
        self._read("        Options:\n")
        self._read("Ignore Whitespace={0}\n".format(self.ignore_whitespace))
        self._read("Ignore File Type, Treat as Ascii={0}\n".format(self.treat_as_ascii))
        self._read(self.select_str)

    def _read_diff(self, left_lines, right_lines, matches):
        if not matches:
            self._read("Files don't match at all\n")
            return

        best_match = self._best_match_set(matches)
        llen = len(left_lines)
        rlen = len(right_lines)

        l_idx = 0
        r_idx = 0
        for matching_text in best_match:
            if matching_text.l_idx > matching_text.r_idx:
                self._read("%d,%dr%d,%d\n" % (l_idx, matching_text.l_idx, r_idx, matching_text.r_idx))
                for x in xrange(matching_text.l_idx - l_idx):
                    self._read("< %s\n" % left_lines[l_idx + x])
            elif matching_text.l_idx < matching_text.r_idx:
                self._read("%d,%da%d,%d\n" % (l_idx, matching_text.l_idx, r_idx, matching_text.r_idx))
                for x in xrange(matching_text.r_idx - r_idx):
                    self._read("> %s\n" % right_lines[r_idx + x])
            else:
                if l_idx != matching_text.l_idx or r_idx != matching_text.r_idx:
                    self._read("%d,%dc%d,%d\n" % (l_idx, matching_text.l_idx, r_idx, matching_text.r_idx))
                    for x in xrange(matching_text.l_idx - l_idx):
                        self._read("< %s\n" % left_lines[l_idx + x])
                    self._read("---\n")
                    for x in xrange(matching_text.r_idx - r_idx):
                        self._read("> %s\n" % right_lines[r_idx + x])

            l_idx = matching_text.l_idx + matching_text.length
            r_idx = matching_text.r_idx + matching_text.length

        if l_idx < llen or r_idx < rlen:
            self._read("%d,Ea%d,E\n" % (l_idx, r_idx))

        if l_idx < llen:
            for x in xrange(llen - l_idx):
                self._read("< %s\n" % left_lines[l_idx + x])

        if r_idx < rlen:
            for x in xrange(rlen - r_idx):
                self._read("> %s\n" % right_lines[r_idx + x])

    def _find_match_set(self, matches):
        l_idx = 0
        r_idx = 0
        score = 0

        match_set = []
        new_matches = []

        for match in matches:
            if match.l_idx >= l_idx and match.r_idx >= r_idx:
                score += match.length * (match.length + 1) / 2
                l_idx = match.l_idx + match.length
                r_idx = match.r_idx + match.length

                match_set.append(match)
            else:
                new_matches.append(match)

        matches = new_matches
        return (new_matches, match_set, score)

    def _best_match_set(self, matches):
        score = 0
        best_match = []

        while matches:
            matches, next_match_set, next_score = self._find_match_set(matches)

            if (next_score > score):
                score = next_score
                best_match = next_match_set

        return best_match

    def _diff_lines(self, left_lines, right_lines):
        l_idx = 0
        r_idx = 0
        found_match = 0
        match = Match()
        matches = []
        for lline in left_lines:
            r_idx = 0
            for rline in right_lines:
                found_match = 0
                while lline == rline:
                    if not found_match:
                        found_match = 1
                        match = Match()
                        match.l_idx = l_idx
                        match.r_idx = r_idx
                        match.length = 1;
                    else:
                        match.length += 1

                    try:
                        lline = left_lines[l_idx + match.length]
                        rline = right_lines[r_idx + match.length]
                    except IndexError:
                        break

                if found_match:
                    x = 0
                    add_to_matches = 1
                    for x in xrange(len(matches)):
                        m = matches[x]
                        if m.r_idx < match.r_idx:
                            if m.r_idx + m.length >= match.r_idx + match.length:
                                add_to_matches = 0
                                break
                            x += 1
                        else:
                            break

                    if add_to_matches:
                        matches.insert(x, match)

                r_idx += 1
            l_idx += 1
        return matches

    def _compare_sfiles(self, sfile1, sfile2, treat_as_ascii):
        if sfile1.file_type == sfile1.file_type and sfile1.file_type == 0:
            if sfile1.data == sfile1.data:
                return "Binary files match\n"
            else:
                return "Binary files %s and %s are not identical\n" % (sfile1.file_name, sfile2.file_name)

        if sfile1.file_type != sfile1.file_type and treat_as_ascii != "Enabled":
            return ("File types must be identical in order to compare them.\n" +
                    "Alternatively, enable \"Treat as Ascii\"\n")

        if sfile1.data == sfile2.data:
            return "Files are identical\n"
        else:
            if self.ignore_whitespace == "Disabled":
                matches = self._diff_lines(sfile1.get_file_lines(), sfile2.get_file_lines())
            else:
                matches = self._diff_lines(sfile1.get_no_ws_file_lines(), sfile2.get_no_ws_file_lines())
        self._read_diff(sfile1.get_file_lines(), sfile2.get_file_lines(), matches)

    def start(self):
        self.ignore_whitespace = "Disabled"
        self.treat_as_ascii = "Disabled"
        self.sfile1_name = "No File Loaded"
        self.sfile2_name = "No File Loaded"
        self.sfile1 = Sfile(1, "FILE ONE")
        self.sfile2 = Sfile(1, "FILE TWO")

    def menu(self):
        self._read_menu()

    def load_file1(self):
        self.write('1\n')

        if (random.randint(0,5)):
            self.sfile1 = Sfile(1, "FILE ONE")

        self.write(self.sfile1.raw_sfile())
        self.sfile1_name = self.sfile1.sfile_name
        self._read("Successfully Loaded File\n")
        self._read("\n")

    def load_file2(self):
        self.write('2\n')

        if (random.randint(0,4)):
            self.sfile2 = Sfile(1, "FILE TWO")
        else:
            self.sfile2.copy_sfile(self.sfile1)

        self.write(self.sfile2.raw_sfile())
        self.sfile2_name = self.sfile2.sfile_name
        self._read("Successfully Loaded File\n")
        self._read("\n")

    def toggle_ignore_whitespace(self):
        self.write('3\n')
        if self.ignore_whitespace == "Disabled":
            self.ignore_whitespace = "Enabled"
        else:
            self.ignore_whitespace = "Disabled"
        self._read("\n")

    def toggle_treat_as_ascii(self):
        self.write('4\n')
        if self.treat_as_ascii == "Disabled":
            self.treat_as_ascii = "Enabled"
        else:
            self.treat_as_ascii = "Disabled"
        self._read("\n")

    def compare_files(self):
        self.write('5\n')
        if self.sfile1_name == "No File Loaded" or self.sfile2_name == "No File Loaded":
            self._read("Both files must be loaded before comparing\n")
        else:
            self._compare_sfiles(self.sfile1, self.sfile2, self.treat_as_ascii)
        self._read("\n")

    def quit(self):
        self.write('6\n')
        self._read("\n")
        self._read("Exiting...\n")

