import re
import bisect
import ctypes

def get_hex(byte_str):
    return re.sub('([0-9A-Fa-f]{2})', '0x\g<0>,', byte_str)

def pretty_bytes(byte_str):
    byte_lines = re.sub('(0x[0-9A-Fa-f]{2}, ?){16}', '\g<0>\n', byte_str);
    return re.sub('(0x[0-9A-Fa-f]{2}.*?\n)', '    \g<0>', byte_lines);

def xor_bytes(byte_str):
    KEY = 'CS10FUN!'
    i = 0
    keylen = len(KEY)
    byte_array = byte_str.split(', ')
    packed_array = ''
    for byte in byte_array:
        if not byte:
            continue
        packed_array += '0x' + hex(int(byte, 16) ^ ord(KEY[i % keylen]))[2:].zfill(2) + ', '
        i += 1
    return packed_array

def get_function_text(function_name, filename=None):
    filename = 'gdb.txt' if not filename else filename
    f = open(filename)
    lines = f.read().splitlines()
    f.close()

    fn_lines = []
    found_fn = False
    for line in lines:
        if not found_fn:
            if line.find(function_name) != -1:
                found_fn = True
        else:
            if line.find('End of assembler dump') != -1:
                break
            else:
                fn_lines.append(line)

    #print '\n'.join(fn_lines)
    return fn_lines

def parse_gdb_function(function_name, filename=None):
    gdb_re = re.compile('.*?<\+(\d+)>: *(([0-9A-Fa-f]{2} )+) *(.*)\r?\n?')
    byte_code_c = 'unsigned char %s[] = {\n' % (function_name + '_bytes')
    byte_code = ''

    lines = get_function_text(function_name, filename)

    for line in lines:
        line = line.replace('\t', '    ')
        matches = gdb_re.match(line)
        if matches:
            #byte_code_c += get_hex(matches.group(2))
            byte_code += get_hex(matches.group(2))

    byte_code = xor_bytes(byte_code)
    byte_code_c += byte_code[:-2] + '\n};\n\n'
    offset_list = []
    return pretty_bytes(byte_code_c)

of = open('../src/packed.h', 'w')
of.write('#ifndef PACKED_H_\n')
of.write('#define PACKED_H_\n\n')
of.write(parse_gdb_function('insertion_sort'))
of.write(parse_gdb_function('selection_sort'))
of.write(parse_gdb_function('heap_propagate'))
of.write(parse_gdb_function('heapify'))
of.write(parse_gdb_function('heap_sort'))
of.write(parse_gdb_function('merge_helper'))
of.write('#ifndef PATCHED_1\n')
of.write(parse_gdb_function('merge_sort'))
of.write('#else\n')
of.write(parse_gdb_function('merge_sort', 'gdb2.txt'))
of.write('#endif\n\n')
of.write('#endif /* PACKED_H_ */\n')
of.close()

