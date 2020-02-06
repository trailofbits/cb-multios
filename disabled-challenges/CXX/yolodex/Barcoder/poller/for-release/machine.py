from generator.actions import Actions
import random
import string
import struct
import numpy as np
import math
import datetime as dt

def random_word(max_size=10, min_size=2):
    if random.randint(0,4):
        characters = string.letters + string.digits
    else:
        max_size *= 2
        characters = string.digits
    max_size = max_size if max_size >= min_size else min_size
    max_size = random.randint(min_size, max_size)
    return ("".join(random.choice(characters) for c in range(max_size))).lower()

def random_text(max_words=32, min_words=3):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
    return text

barcode_lut = [
	[ ' ', "00", "|| ||  ||  " ],
	[ '!', "01", "||  || ||  " ],
	[ '"', "02", "||  ||  || " ],
	[ '#', "03", "|  |  ||   " ],
	[ '$', "04", "|  |   ||  " ],
	[ '%', "05", "|   |  ||  " ],
	[ '&', "06", "|  ||  |   " ],
	[ '\'', "07", "|  ||   |  " ],
	[ '(', "08", "|   ||  |  ", ],
	[ ')', "09", "||  |  |   ", ],
	[ '*', "10", "||  |   |  ", ],
	[ '+', "11", "||   |  |  ", ],
	[ ',', "12", "| ||  |||  ", ],
	[ '-', "13", "|  || |||  ", ],
	[ '.', "14", "|  ||  ||| ", ],
	[ '/', "15", "| |||  ||  ", ],
	[ '0', "16", "|  ||| ||  ", ],
	[ '1', "17", "|  |||  || ", ],
	[ '2', "18", "||  |||  | ", ],
	[ '3', "19", "||  | |||  ", ],
	[ '4', "20", "||  |  ||| ", ],
	[ '5', "21", "|| |||  |  ", ],
	[ '6', "22", "||  ||| |  ", ],
	[ '7', "23", "||| || ||| ", ],
	[ '8', "24", "||| |  ||  ", ],
	[ '9', "25", "|||  | ||  ", ],
	[ ':', "26", "|||  |  || ", ],
	[ ';', "27", "||| ||  |  ", ],
	[ '<', "28", "|||  || |  ", ],
	[ '=', "29", "|||  ||  | ", ],
	[ '>', "30", "|| || ||   ", ],
	[ '?', "31", "|| ||   || ", ],
	[ '@', "32", "||   || || ", ],
	[ 'A', "33", "| |   ||   ", ],
	[ 'B', "34", "|   | ||   ", ],
	[ 'C', "35", "|   |   || ", ],
	[ 'D', "36", "| ||   |   ", ],
	[ 'E', "37", "|   || |   ", ],
	[ 'F', "38", "|   ||   | ", ],
	[ 'G', "39", "|| |   |   ", ],
	[ 'H', "40", "||   | |   ", ],
	[ 'I', "41", "||   |   | ", ],
	[ 'J', "42", "| || |||   ", ],
	[ 'K', "43", "| ||   ||| ", ],
	[ 'L', "44", "|   || ||| ", ],
	[ 'M', "45", "| ||| ||   ", ],
	[ 'N', "46", "| |||   || ", ],
	[ 'O', "47", "|   ||| || ", ],
	[ 'P', "48", "||| ||| || ", ],
	[ 'Q', "49", "|| |   ||| ", ],
	[ 'R', "50", "||   | ||| ", ],
	[ 'S', "51", "|| ||| |   ", ],
	[ 'T', "52", "|| |||   | ", ],
	[ 'U', "53", "|| ||| ||| ", ],
	[ 'V', "54", "||| | ||   ", ],
	[ 'W', "55", "||| |   || ", ],
	[ 'X', "56", "|||   | || ", ],
	[ 'Y', "57", "||| || |   ", ],
	[ 'Z', "58", "||| ||   | ", ],
	[ '[', "59", "|||   || | ", ],
	[ '\\', "60", "||| |||| | ", ],
	[ ']', "61", "||  |    | ", ],
	[ '^', "62", "||||   | | ", ],
	[ '_', "63", "| |  ||    ", ],
	[ '`', "64", "| |    ||  ", ],
	[ 'a', "65", "|  | ||    ", ],
	[ 'b', "66", "|  |    || ", ],
	[ 'c', "67", "|    | ||  ", ],
	[ 'd', "68", "|    |  || ", ],
	[ 'e', "69", "| ||  |    ", ],
	[ 'f', "70", "| ||    |  ", ],
	[ 'g', "71", "|  || |    ", ],
	[ 'h', "72", "|  ||    | ", ],
	[ 'i', "73", "|    || |  ", ],
	[ 'j', "74", "|    ||  | ", ],
	[ 'k', "75", "||    |  | ", ],
	[ 'l', "76", "||  | |    ", ],
	[ 'm', "77", "|||| ||| | ", ],
	[ 'n', "78", "||    | |  ", ],
	[ 'o', "79", "|   |||| | ", ],
	[ 'p', "80", "| |  ||||  ", ],
	[ 'q', "81", "|  | ||||  ", ],
	[ 'r', "82", "|  |  |||| ", ],
	[ 's', "83", "| ||||  |  ", ],
	[ 't', "84", "|  |||| |  ", ],
	[ 'u', "85", "|  ||||  | ", ],
	[ 'v', "86", "|||| |  |  ", ],
	[ 'w', "87", "||||  | |  ", ],
	[ 'x', "88", "||||  |  | ", ],
	[ 'y', "89", "|| || |||| ", ],
	[ 'z', "90", "|| |||| || ", ],
	[ '{', "91", "|||| || || ", ],
	[ '|', "92", "| | ||||   ", ],
	[ '}', "93", "| |   |||| ", ],
	[ '~', "94", "|   | |||| ", ],
	[ 127, "95", "| |||| |   ", ],
	[ 128, "96", "| ||||   | ", ],
	[ 129, "97", "|||| | |   ", ],
	[ 130, "98", "|||| |   | ", ],
	[ 131, "99", "| ||| |||| ", ],
	[ '\x00', "M1", "| |||| ||| ", ],
	[ '\x00', "M2", "||| | |||| ", ],
	[ '\x00', "M3", "|||| | ||| ", ],
	[ '\x00', "SA", "|| |    |  ", ],
	[ '\x00', "SB", "|| |  |    ", ],
	[ '\x00', "SC", "|| |  |||  ", ],
	[ '\x00', "SP", "||   ||| | ||", ],
	[ '\x00', "QT", "           ", ],
]


class BarcodeType():
    type_b = 104
    type_c = 105


class Barcode128:
    STARTB_IDX = 104
    STARTC_IDX = 105
    STOP_IDX = 106
    QUIET_IDX = 107

    def __init__(self):
        self.checksum = 0
        self.encoding_type = None
        self.raw_str = ""
        self.barcode_array = []

    def get_raw_str(self):
        self.read(self.raw_str)

    def get_barcode_ascii(self):
        i = 1
        barcode_ascii = ''
        while i < len(self.barcode_array) - 1:
            barcode_ascii += self.barcode_array[i][2]
            i += 1

        return barcode_ascii


def create_barcode_from_string(raw_str):
    new_barcode = Barcode128()
    new_barcode.raw_str = raw_str
    new_barcode.encoding_type = BarcodeType.type_c
    for s in raw_str:
        if s < '0' or s > '9':
            new_barcode.encoding_type = BarcodeType.type_b
            break
    new_barcode.checksum = new_barcode.encoding_type

    new_barcode.barcode_array.append(barcode_lut[Barcode128.QUIET_IDX])
    if new_barcode.encoding_type == BarcodeType.type_c:
        new_barcode.barcode_array.append(barcode_lut[Barcode128.STARTC_IDX])
        if len(raw_str) % 2:
            raw_str = '0' + raw_str;
            new_barcode.raw_str = raw_str

        i = 0
        while i < len(raw_str):
            idx = int(raw_str[i:i+2])
            new_barcode.checksum += (i+2)/2 * idx
            new_barcode.barcode_array.append(barcode_lut[idx])
            i += 2
    else:
        new_barcode.barcode_array.append(barcode_lut[Barcode128.STARTB_IDX])

        i = 0
        while i < len(raw_str):
            idx = ord(raw_str[i]) - 32
            new_barcode.checksum += (i+1) * idx
            new_barcode.barcode_array.append(barcode_lut[idx])
            i += 1

    new_barcode.checksum %= 103
    new_barcode.barcode_array.append(barcode_lut[new_barcode.checksum])
    new_barcode.barcode_array.append(barcode_lut[Barcode128.STOP_IDX])
    new_barcode.barcode_array.append(barcode_lut[Barcode128.QUIET_IDX])
    return new_barcode


def create_barcode_from_encoded_data(barcode_ascii):
    new_barcode = Barcode128()
    new_barcode.barcode_array.append(barcode_lut[Barcode128.QUIET_IDX])

    barcode_ascii = barcode_ascii.strip(' ')
    checksum_idx = barcode_ascii.find(barcode_lut[Barcode128.STOP_IDX][2]) - 11
    start_code = barcode_ascii[0:11]
    if start_code == barcode_lut[Barcode128.STARTB_IDX][2]:
        new_barcode.encoding_type = BarcodeType.type_b
        new_barcode.barcode_array.append(barcode_lut[Barcode128.STARTB_IDX])
    elif start_code == barcode_lut[Barcode128STARTC_IDX][2]:
        new_barcode.encoding_type = BarcodeType.type_c
        new_barcode.barcode_array.append(barcode_lut[Barcode128.STARTC_IDX])
    else:
        return None
    new_barcode.checksum = new_barcode.encoding_type

    i = 11
    while i < checksum_idx:
        barcode_encoding = barcode_ascii[i:i+11]
        found = False
        for entry in barcode_lut:
            if barcode_encoding == entry[2]:
                new_barcode.append(entry)
                found = True
                break

        if not found:
            return None
        i+=11

    new_barcode.checksum %= 103
    barcode_checksum_encoding = barcode_ascii[i:i+11]
    if barcode_checksum_encoding != barcode_lut[new_barcode.checksum][2]:
        return None

    new_barcode.barcode_array.append(barcode_lut[new_barcode.checksum])
    new_barcode.barcode_array.append(barcode_lut[Barcode128.STOP_IDX])
    new_barcode.barcode_array.append(barcode_lut[Barcode128.QUIET_IDX])
    return new_barcode


class BarcodeBitmap():
    PIXELW = 4
    PIXELH = 120
    def __init__(self):
        #BMP HEADER
        self.magic = struct.pack('<2s','BM')
        self.file_size = 0
        self.reserved = struct.pack('<I', 0)
        self.data_offset = struct.pack('<I', 0x36)

        #DIB INFO
        self.size = struct.pack('<I', 40)
        self.width = 0
        self.height = struct.pack('<i', BarcodeBitmap.PIXELH)

        self.planes = struct.pack('<H', 1)
        self.bits = struct.pack('<H', 24)
        self.compression = struct.pack('<I', 0)
        self.imagesize = 0
        self.hres = struct.pack('<i', 2835)
        self.vres = struct.pack('<i', 2835)
        self.num_colors = struct.pack('<I', 0)
        self.imp_colors = struct.pack('<I', 0)

        self.data = ''

    def get_packed_data(self):
        bitmap = (self.magic + self.file_size + self.reserved + self.data_offset + self.size +
                self.width + self.height + self.planes + self.bits + self.compression +
                self.imagesize + self.hres + self.vres + self.num_colors + self.imp_colors +
                self.data)
        return bitmap


def create_bbitmap_from_barcode(barcode=None):
    if not barcode:
        word = random_word()
        barcode = create_barcode_from_string(word)

    bbitmap = BarcodeBitmap()
    barcode_ascii = barcode.get_barcode_ascii()
    imagesize = ((len(barcode_ascii) + 22) * BarcodeBitmap.PIXELW * BarcodeBitmap.PIXELH * 3)
    file_size = imagesize + 54
    bbitmap.imagesize = struct.pack('<I', imagesize)
    bbitmap.file_size = struct.pack('<I', file_size)
    width = ((len(barcode_ascii) + 22) * BarcodeBitmap.PIXELW)
    bbitmap.width = struct.pack('<I', width)

    black = struct.pack('<3s', "\x00\x00\x00")
    white = struct.pack('<3s', "\xFF\xFF\xFF")
    quiet = 11 * BarcodeBitmap.PIXELW * struct.pack('<3s', "\xFF\xFF\xFF")
    data_one_row = quiet
    for c in barcode_ascii:
        if c == '|':
            data_one_row += BarcodeBitmap.PIXELW * black
        else:
            data_one_row += BarcodeBitmap.PIXELW * white
    data_one_row += quiet

    bbitmap.data = data_one_row * BarcodeBitmap.PIXELH
    return bbitmap


class Barcode(Actions):
    def _add_to_cache(self, barcode):
        if len(self.barcode_cache) == 10:
            self.barcode_cache.pop(0)
            self.barcode_cache.append(barcode)
        else:
            self.barcode_cache.append(barcode)

    def _read(self, data):
        self.read(length=len(data), expect=data)

    def _read_barcode_cache(self):
        i = 0
        while i < len(self.barcode_cache):
            self._read("    %d. Text: %s\n" % (i+1, self.barcode_cache[i].raw_str))
            i += 1

    def _read_input_barcode_menu(self):
        self._read("Input barcode as:\n")
        self._read("    1. String to encode\n")
        self._read("    2. Barcode encoded in ascii (\"|\" and \" \")\n")
        self._read("    3. Barcode bitmap\n")
        self._read("    0. Return to main menu\n")
        self._read(":-$  ")

    def start(self):
        self.delay(50)
        self.write(self.magic_page[:4])
        self.read(length=0x1000, expect=self.magic_page)

        self._read("Welcome to the EZ Barcode Encoder/Decoder Service\n")
        self.barcode_cache = []

    def user_menu(self):
        self._read("--Select an option--\n")
        self._read("1. Input a new barcode\n")
        self._read("2. View barcode ascii\n")
        self._read("3. Generate barcode image\n")
        self._read("4. View cached barcodes\n")
        self._read("5. Clear cached barcodes\n")
        self._read("6. Quit\n")
        self._read(":-$  ")

    def input_barcode(self):
        self.write('1\n')
        self._read_input_barcode_menu()
        choice = random.randint(0,3)
        choice = 2
        if choice == 0:
            self.write('0\n')
        elif choice == 1:
            self.write('1\n')
            word = random_word()
            self.write("%s\n" % word)
            self._read("Successfully added barcode to cache\n")
            self._read("Barcode text: %s\n" % word)
            self._add_to_cache(create_barcode_from_string(word))
        elif choice == 2:
            self.write('2\n')
            word = random_word()
            new_barcode = create_barcode_from_string(word)
            self.write("%s\n" % new_barcode.get_barcode_ascii())
            self._read("Successfully added barcode to cache\n")
            self._read("Barcode text: %s\n" % new_barcode.raw_str)
            self._add_to_cache(new_barcode)
        elif choice == 3:
            self.write('3\n')
            word = random_word()
            new_barcode = create_barcode_from_string(word)
            bbitmap = create_bbitmap_from_barcode(new_barcode)
            self.write(bbitmap.get_packed_data())
            self._read("Successfully added bitmap barcode to cache\n")
            self._read("Barcode text: %s\n" % new_barcode.raw_str)
            self._add_to_cache(new_barcode)

    def view_barcode_ascii(self):
        self.write('2\n')
        self._read("Select Cached Barcode\n")
        self._read_barcode_cache()
        self._read("    0. Return to main menu\n")
        self._read(":-$  ")

        choice = random.randint(0, len(self.barcode_cache))
        self.write('%d\n' % choice)
        if choice:
            self._read("Raw String: %s\n" % self.barcode_cache[choice - 1].raw_str)
            self._read("%s\n" % self.barcode_cache[choice - 1].get_barcode_ascii())

    def generate_barcode_image(self):
        self.write('3\n')
        self._read("Select Cached Barcode\n")
        self._read_barcode_cache()
        self._read("    0. Return to main menu\n")
        self._read(":-$  ")

        choice = random.randint(0, len(self.barcode_cache))
        self.write('%d\n' % choice)
        if choice:
            self._read("    Printable Barcode:\n")
            bbitmap = create_bbitmap_from_barcode(self.barcode_cache[choice - 1])
            self._read("%s" % bbitmap.get_packed_data())
            self._read("\n    Barcode String: %s\n" % self.barcode_cache[choice - 1].raw_str)


    def view_cached_barcodes(self):
        self.write('4\n')
        self._read("Cached Barcodes\n")
        self._read_barcode_cache()

    def clear_cached_barcode(self):
        self.write('5\n')


    def exit(self):
        self.write('6\n')
        self._read("Thanks for using the EZ Barcode Encoder/Decoder Service\n")

