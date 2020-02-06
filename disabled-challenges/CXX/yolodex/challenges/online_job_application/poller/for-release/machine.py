from generator.actions import Actions
import random
import string
import struct
import ctypes
import sys
import pprint

pp = pprint.PrettyPrinter(indent=4)

def random_name(is_required=True):
    if not is_required:
        if random.randint(1,10) == 1:
            return ''

    characters = string.letters + "'"
    max_size = random.randint(1,31)
    return ''.join(random.choice(characters) for c in range(max_size))


def random_suffix():
    if random.randint(1,10) == 1:
        return ''

    valid_suffixes = ["Jr", "Sr", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "Other"]
    choice = random.randint(1, len(valid_suffixes)) - 1
    return valid_suffixes[choice]


def random_month():
    month = random.randint(1,12)
    if month < 10:
        return '0' + str(month)
    else:
        return str(month)


def random_day():
    day = random.randint(1,28)
    if day < 10:
        return '0' + str(day)
    else:
        return str(day)


def random_year():
    return str(random.randint(1900, 2014))


def random_height_feet():
    return str(random.randint(1, 9))


def random_height_inches():
    return str(random.randint(0, 11))


def random_weight():
    return str(random.randint(50, 500))


def random_sex():
    if random.randint(1,2) == 1:
        return 'M'
    else:
        return 'F'


def random_hair():
    valid_hair_color = [ "Bald", "Black", "Blonde or Strawbery", "Brown", "Gray or Partially Gray",
                         "Red or Auburn", "Sandy", "White", "Blue", "Green", "Orange", "Pink", "Purple",
                         "Unspecified or Unknown" ]

    choice = random.randint(1, len(valid_hair_color)) - 1
    return valid_hair_color[choice]


def random_eye():
    valid_eye_color = [ "Black", "Blue", "Brown", "Gray", "Green", "Hazel", "Maroon", "Multicolored",
                        "Pink", "Unknown" ]

    choice = random.randint(1, len(valid_eye_color)) - 1
    return valid_eye_color[choice]


def random_yes_no():
    if random.randint(1,2) == 1:
        return 'Y'
    else:
        return 'N'


def random_text():
    max_size = random.randint(1, 63)
    characters = string.letters + string.digits + ' .?!'
    return ''.join(random.choice(characters) for c in range(max_size))

def random_email():
    characters = string.letters + string.digits

    max_size = random.randint(1, 31)
    front = ''.join(random.choice(characters) for c in range(max_size))
    max_size = random.randint(1, 31)
    back = ''.join(random.choice(characters) for c in range(max_size))

    return front + '@' + back


def random_phone(is_required=True):
    if not is_required:
        if random.randint(1,10) == 1:
            return ''

    characters = string.digits
    max_size = 4
    return '555-555-' + (''.join(random.choice(characters) for c in range(max_size)))


def random_street():
    characters = string.digits
    max_size = random.randint(1, 4)
    street_num = ''.join(random.choice(characters) for c in range(max_size))

    characters = string.letters
    street_name = ''.join(random.choice(characters))
    characters = string.letters + ' '
    max_size = random.randint(3, 15)
    street_name += ''.join(random.choice(characters) for c in range(max_size))

    while (street_name[-1] == ' '):
        street_name = street_name[:-2]

    return street_num + ' ' + street_name + ' St'


def random_city():
    characters = string.letters
    max_size = random.randint(4,31)
    return ''.join(random.choice(characters) for c in range(max_size))


def random_state():
    valid_state = [ "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "DC", "FL", "GA", "HI", "ID", "IL",
                         "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT", "NE",
                         "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD",
                         "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY" ]

    choice = random.randint(1, len(valid_state)) - 1
    return valid_state[choice]

def random_zip_code():
    return str(random.randint(10000, 99999))

def random_gpa():
    gpa_dec = random.randint(0,99)
    gpa_dec_str = str(gpa_dec) if gpa_dec >= 10 else '0' + str(gpa_dec)
    return str(random.randint(0, 4)) + '.' + gpa_dec_str

def random_education():
    valid_education = [ "HS", "COLLEGE", "ADV" ]

    choice = random.randint(1, len(valid_education)) - 1
    return valid_education[choice]

class ApplicationPage():
    def __init__(self):
        self.fields = []

    def check_fields_completed(self):
        for text_field, opt_text_field, is_required, current_val, gen_func in self.fields:
            if current_val is None:
                return False

        return True


    def get_incomplete_field(self):
        for x in xrange(len(self.fields)):
            (text_field, opt_text_field, is_required, current_val, gen_func) = self.fields[x]
            if current_val is None:
                return self.fields[x]

        return None

    def enter_field(self):
        for x in xrange(len(self.fields)):
            (text_field, opt_text_field, is_required, current_val, gen_func) = self.fields[x]
            if current_val is None:
                self.fields[x].current_val = gen_func()
                return True

        return False

    def update_field(self, field_name):
        for x in xrange(len(self.fields)):
            text_field, opt_text_field, is_required, current_val, gen_func = self.fields[x]
            if text_field == field_name:
                current_val = gen_func()
                self.fields[x] = (text_field, opt_text_field, is_required, current_val, gen_func)
                return current_val

        return None

class ApplicantId(ApplicationPage):
    def __init__(self):
        self.fields = [
            ("Last Name", "", True, None, random_name),
            ("First Name", "", True, None, random_name),
            ("Middle Name", " [MI or Middle Name]",  False, None, random_name),
            ("Suffix", " [Jr, Sr, II, etc]", False, None, random_suffix),
            ("DOB Month", " [MM]", True, None, random_month),
            ("DOB Day", " [DD]", True, None, random_day),
            ("DOB Year", " [YYYY]", True, None, random_year),
            ("Height-Feet", " [1-9]", True, None, random_height_feet),
            ("Height-Inches", " [0-11]", True, None, random_height_inches),
            ("Weight", "", True, None, random_weight),
            ("Sex", "", True, None, random_sex),
            ("Hair Color", "", True, None, random_hair),
            ("Eye Color", "", True, None, random_eye)
        ]

class ContactInfo(ApplicationPage):
    def __init__(self):
        self.fields = [
            ("Personal e-mail", "", True, None, random_email),
            ("Work e-mail", "", False, None, random_email),
            ("Home telephone number", " [XXX-XXX-XXXX]", True, None, random_phone),
            ("Work telephone number", " [XXX-XXX-XXXX]", False, None, random_phone)
        ]


class CurrentAddress(ApplicationPage):
    def __init__(self):
        self.fields = [
            ("Move-In Month", " [MM]", True, None, random_month),
            ("Move-In Year", " [YYYY]", True, None, random_year),
            ("Street", "", True, None, random_street),
            ("City", "", True, None, random_city),
            ("State", "", True, None, random_state),
            ("Zip Code", "", True, None, random_zip_code),
            ("Owned by you", "? [Y/N]", True, None, random_yes_no)
        ]


class Education(ApplicationPage):
    def __init__(self):
        self.fields = [
            ("Highest Education", " [HS/COLLEGE/ADV]", True, None, random_education),
            ("Start Month", " [MM]", True, None, random_month),
            ("Start Year", " [YYYY]", True, None, random_year),
            ("End Month", " [MM]", True, None, random_month),
            ("End Year", " [YYYY]", True, None, random_year),
            ("School Name", "", True, None, random_text),
            ("Street", "", True, None, random_street),
            ("City", "", True, None, random_city),
            ("State", "", True, None, random_state),
            ("Zip Code", "", True, None, random_zip_code),
            ("GPA", " [X.XX]", True, None, random_gpa),
            ("Major", " [NA for HS]", True, None, random_text)
        ]


class Employer(ApplicationPage):
    def __init__(self):
        self.fields = [
            ("Most Recent Employer", "", True, None, random_text),
            ("Start Month", " [MM]", True, None, random_month),
            ("Start Year", " [YYYY]", True, None, random_year),
            ("End Month", " [MM]", False, None, random_month),
            ("End Year", " [YYYY]", False, None, random_year),
            ("Street", "", True, None, random_street),
            ("City", "", True, None, random_city),
            ("State", "", True, None, random_state),
            ("Zip Code", "", True, None, random_zip_code),
            ("Supervisor Last Name", "", True, None, random_name),
            ("Supervisor First Name", "", True, None, random_name),
            ("Supervisor Title", "", True, None, random_text),
            ("Supervisor Telephone Number", " [XXX-XXX-XXXX]", True, None, random_phone),
            ("Supervisor e-mail", "", False, None, random_email),
        ]


class Screening(ApplicationPage):
    def __init__(self):
        self.fields = [
            ("Drug Test", "? [Y/N]", True, None, random_yes_no),
            ("Background Investigation", "? [Y/N]", True, None, random_yes_no)
        ]

class Finished(ApplicationPage):
    def __init__(self):
        self.fields = []



class JobApplication(Actions):
    finished_page_text = ("\n\nYou have completed your application with the Sea Eye Association.\n" +
                     "You may review the form. Navigate through the application with **prev and **next.\n" +
                     "Once your are satisfied type **exit to exit and submit the form\n" +
                     "If you wish to discard your application, please use Control-C\n")

    page_text = [ "\nCandidate Info Form\n", "\nContact Info Form\n", "\nAddress Form\n", "\nEducation Form\n",
                    "\nEmployment Form\n", "\nFinal Questions\n", finished_page_text, ""  ]

    finish_text = [ "\n*********Candidate Info:*********\n", "\n*********Contact Info:*********\n",
                    "\n*********Address:*********\n", "\n*********Highest Education:*********\n",
                    "\n*********Most Recent Employer:*********\n", "\n*********Final Screening:*********\n",
                    "" ]

    help_text = ("All commands begin with '**' and may be entered at any time\n" +
                 "**prev <Return to the previous page>\n" +
                 "**next <Move to the next page>\n" +
                 "**update [id] <Update field, ex: \"Update First Name\">\n" +
                 "**help <Print this dialogue>\n" +
                 "**exit <Exit application>\n")

    welcome_text = ("\n\n" +
                    "Thanks for your interest in the Sea Eye Association.\n" +
                    "In order to be considered for the job complete the preliminary online background check\n" +
                    "Due to the secure nature of the position you are applying for you may be asked to\n" +
                    "submit additional paperwork after your preliminary background check has been approved.\n" +
                    "Thank you for your cooperation\n" )

    exit_text = ("Thank you!\n")

    def _read_page_banner(self, page_idx=None):
        page_idx = self.state['page_idx'] if page_idx is None else page_idx
        self.read(length=len(self.page_text[page_idx]), expect=self.page_text[page_idx])

    def _read_completed_form(self):
        page = self.app_pages[self.state['page_idx']]
        if len(self.finish_text[self.state['page_idx']]):
            self.read(length=len(self.finish_text[self.state['page_idx']]),
                        expect=self.finish_text[self.state['page_idx']])
        for text_field, opt_text_field, is_required, current_val, gen_func in page.fields:
            line = text_field + '=' + current_val + '\n'
            self.read(length=len(line), expect=line)

        if self.state['page_idx'] < 6:
            line = "\nType **next to continue\n"
            self.read(length=len(line), expect=line)

    def _read_current_form(self):
        page = self.app_pages[self.state['page_idx']]
        field = page.get_incomplete_field()

        if field is not None:
            (text_field, opt_text_field, is_required, current_val, gen_func) = field
            self.read(length=len(text_field + opt_text_field + ': '), expect=text_field + opt_text_field + ': ')
        else:
            self._read_completed_form()

        return field

    def start(self):
        self.last_page_completed = -1
        self.app_pages = [ ApplicantId(), ContactInfo(), CurrentAddress(), Education(),
                            Employer(), Screening(), Finished() ]

        self.state['page_idx'] = 0

        self.read(length=len(self.welcome_text), expect=self.welcome_text)
        self._read_page_banner()

    def enter_field(self):
        field = self._read_current_form()
        if field is not None:
            page = self.app_pages[self.state['page_idx']]
            (text_field, opt_text_field, is_required, current_val, gen_func) = field
            current_val = page.update_field(text_field) + '\n'
            self.write(current_val)
        else:
            self.write('\n')
            self._read_page_banner()

    def update_field(self):
        if self.state['page_idx'] == 6:
            return

        field = self._read_current_form()
        page = self.app_pages[self.state['page_idx']]
        field_idx = random.randint(0, len(page.fields) - 1)
        text_field, opt_text_field, is_required, current_val, gen_func = page.fields[field_idx]
        self.write("**update " + text_field + "\n")

        if field is None:
            (text_field, opt_text_field, is_required, current_val, gen_func) = page.fields[field_idx]
            self.read(length=len(text_field + opt_text_field + ': '), expect=text_field + opt_text_field + ': ')
            current_val = page.update_field(text_field) + '\n'
            self.write(current_val)
        else:
            line = "Cannot update field until all fields are inputted\n"
            self.read(length=len(line), expect=line)

        self._read_page_banner()

    def next_page(self):
        field = self._read_current_form()
        self.write("**next\n")

        if (self.state['page_idx'] < 6):
            if field is None:
                self.state['page_idx'] += 1
            else:
                self._read_page_banner(page_idx=self.state['page_idx']+1)
                line = "You must complete the previous page before proceeding to this page\n"
                self.read(length=len(line), expect=line)

        self._read_page_banner()

    def prev_page(self):
        field = self._read_current_form()
        self.write("**prev\n")

        if self.state['page_idx'] > 0:
            self.state['page_idx'] -= 1

        self._read_page_banner()

    def help(self):
        field = self._read_current_form()
        self.write("**help\n")
        self.read(length=len(self.help_text), expect=self.help_text)
        self._read_page_banner()

    def exit(self):
        field = self._read_current_form()
        self.write("**exit\n")
        self.read(length=len(self.exit_text), expect=self.exit_text)


