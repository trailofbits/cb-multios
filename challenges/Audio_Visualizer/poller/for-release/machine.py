from generator.actions import Actions
import random
import string
import struct

#define MAX_MSGS 5
#define MAX_RCPT 16
#define MAX_ADDR_LEN 32
#define MAX_DATA 512
#define MAX_USER_LEN 64
#define MAX_PASS_LEN 64
#define MAX_LINE 64

def random_bad_input(max_size=10, min_size=2):
    characters = string.letters + string.digits + ' .\t;:\'"?!@#$&()'
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(characters) for c in range(max_size)) + '\n'

def random_bad_choice(is_file_loaded):
    characters = '34567890'
    if(is_file_loaded):
        return '0\n'
    else:
        return ''.join(random.choice(characters) + '\n')

def random_num(is_file_loaded):
    characters = string.digits
    return ''.join(random.choice(characters) + '\n')

def random_uwfc_file(well_formed):
    MAX_NUM_SAMPLES = 2
    #sample_rates = [8000, 11025, 16000, 22050, 32000, 44100, 48000]
    # cb-test timeout is too low, so only allowing 2
    # sample_rates = [8000, 11025]
    sample_rates = [4000, 8000] # BMC - modified to use smaller sample rates, for faster testing

    chunk_id_p = struct.pack('4s', "FFIR")
    format_p = struct.pack('4s', "UWFC")
    sub_chunk1_id_p = struct.pack('4s', "cgc ")
    sub_chunk1_size = 16
    sub_chunk1_size_p = struct.pack('i', sub_chunk1_size)
    audio_format_p = struct.pack('h', 1)
    num_channels = 1 if random.randint(0,1) else 2
    num_channels_p = struct.pack('h', num_channels)
    sample_rate = sample_rates[random.randint(0, len(sample_rates) - 1)]
    sample_rate_p = struct.pack('i', sample_rate)
    bits_per_sample = 8 if random.randint(0,1) else 16
    bits_per_sample_p = struct.pack('h', bits_per_sample)
    sub_chunk2_id_p = struct.pack('4s', "data")

    byte_rate_p = struct.pack('i', sample_rate * num_channels * bits_per_sample/8)
    block_align = num_channels * bits_per_sample/8
    block_align_p = struct.pack('h', block_align)
    sub_chunk2_size = random.randrange(0, sample_rate * MAX_NUM_SAMPLES, block_align)
    sub_chunk2_size_p = struct.pack('i', sub_chunk2_size)
    chunk_size_p = struct.pack('i', 4 + (8 + sub_chunk1_size) + (8 + sub_chunk2_size))

    data_p = ''
    for x in xrange(0, sub_chunk2_size, block_align):
        for y in xrange(num_channels):
            if(bits_per_sample == 8):
                data_p += struct.pack('B', random.randint(0, 255))
            elif(bits_per_sample == 16):
                data_p += struct.pack('h', random.randint(-32768, 32767))

    if not well_formed:
        chunk_id_p = struct.pack('4s', "ffir")

    uwfc_file = (chunk_id_p + chunk_size_p + format_p +
                sub_chunk1_id_p + sub_chunk1_size_p + audio_format_p +
                num_channels_p + sample_rate_p + byte_rate_p +
                block_align_p + bits_per_sample_p + sub_chunk2_id_p +
                sub_chunk2_size_p + data_p)

    return uwfc_file


def random_line(max_size=62, min_size=2):
    characters = string.letters + string.digits + ' .\t;:\'"?!@#$&()'
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(characters) for c in range(max_size)) + '\n'


def random_alphanum(max_size, min_size=2):
    alphanum = string.letters + string.digits
    max_size = max_size if max_size >= min_size else min_size
    return ''.join(random.choice(alphanum) for c in range(max_size))


class Visualizer(Actions):
    num_buckets = 12
    eq_delim = "|-----|" * num_buckets + "\n"
    nf_menu = ( "1. Load File\n"
                "2. Quit\n\n" )
    fl_menu = ( "1. Load New File\n"
                "2. Wave Visualizer\n"
                "3. EQ Visualizer\n"
                "4. Power Visualizer\n"
                "5. Enable Low Pass Filter\n"
                "6. Enable High Pass Filter\n"
                "7. Disable Filters\n"
                "8. Set visualization speed multiplier (0-9)\n"
                "9. Quit" )
    fl_menu_pcre = ( "--Current\ Track:\ Sampled\ @\d{4,5}Hz\ (?:8|16)\ bit,\ (?:Stereo|Mono)\ -\ Data\ Size=\d*\n"
                "::Options:\ Filter\ Type=(?:None|Low\ Pass|High\ Pass)\ \|\ Visualization\ Slowdown\ Multiplier=[0-9]" )
    wav_vis_pcre = "(?:\ *\*\ *\|\ *\*\ *\n|\ *\*\ *\n)*"
    eq_vis_pcre = "(?:\ {3}(?:\|[\ \|=-]{5}\|){12}\n*)*"
    pow_vis_pcre = "(?:=*]\n)*"


    def start(self):
        pass

    def no_file(self):
        self.state['file_loaded'] = False
        self.read(delim='--NO FILE LOADED--\n', expect=self.nf_menu)

    def bad_nf_choice(self):
        self.write(random_bad_choice(self.state['file_loaded']))
        self.read(delim='\n', expect="ERROR: Bad Choice. Select another option")

    def bad_nf_input(self):
        self.write(random_bad_input())
        self.read(delim='\n', expect="ERROR: Bad Input. Valid Options: 1, 2")

    def nf_quit(self):
        self.write('2\n')
        self.read(delim='\n', expect="EXITING...")

    def load_file(self):
        self.state['file_loaded'] = True
        uwfc_file = random_uwfc_file(True)
        self.write('1\n')
        self.write(uwfc_file)

    def file_loaded(self):
        self.state['file_loaded'] = True
        self.read(delim='\n\n', expect=self.fl_menu)
        self.read(delim='::\n\n', expect=self.fl_menu_pcre, expect_format='pcre')

    def bad_fl_choice(self):
        self.write(random_bad_choice(self.state['file_loaded']))
        self.read(delim='\n', expect="ERROR: Bad Choice. Select another option")

    def bad_fl_input(self):
        self.write(random_bad_input())
        self.read(delim='\n', expect="ERROR: Bad Input. Valid Options: 1, 2, 3, 4, 5, 6, 7, 8, 9")

    def wave_vis(self):
        self.write('2\n')
        self.read(delim='++++END VISUALIZATION++++\n\n', expect=self.wav_vis_pcre, expect_format='pcre')

    def eq_vis(self):
        self.write('3\n')
        self.read(delim='++++END VISUALIZATION++++\n\n', expect=self.eq_vis_pcre, expect_format='pcre')

    def pow_vis(self):
        self.write('4\n')
        self.read(delim='++++END VISUALIZATION++++\n\n', expect=self.pow_vis_pcre, expect_format='pcre')

    def low_pass(self):
        self.write('5\n')

    def high_pass(self):
        self.write('6\n')

    def no_filter(self):
        self.write('7\n')

    def vis_speed(self):
        self.write('8\n')
        speed = random.choice('0123456789')
        self.write(speed + '\n')
        self.read(delim='\n', expect="Multiplier set to {0}\n".format(speed))

    def quit(self):
        self.write('9\n')
        self.read(delim='\n', expect="EXITING...\n")

