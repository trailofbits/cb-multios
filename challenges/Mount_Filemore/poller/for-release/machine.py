#!/usr/bin/env python

from generator.actions import Actions
import random
import struct
import ctypes
import string

MAX_IMG_SIZE=(1024 * 1024 * 128)

GET_BIT = lambda bit_idx: ((1<<(bit_idx)) - 1)
READONLY_FLAG = GET_BIT(1)
HIDDEN_FLAG = GET_BIT(2)
SYSTEM_FLAG = GET_BIT(3)
VOLUME_LBL_FLAG = GET_BIT(4)
SUBDIRECTORY_FLAG = GET_BIT(5)
ARCHIVE_FLAG = GET_BIT(6)

def kaprica_mixin(self):
    if hasattr(self, 'xlat_seed'):
        return

    def xlat_seed(seed):
        def hash_string(seed):
            H = 0x314abc86
            for c in seed:
                H = (H * 37) & 0xffffffff
                H ^= ord(c)
                H = ((H << 13) ^ (H >> 19)) & 0xffffffff
            return H
        def hash_iterate(H):
            H = (H * 3) & 0xffffffff
            H = ((H << 13) ^ (H >> 19) ^ (H >> 21)) & 0xffffffff
            return H
        xmap = list(xrange(256))
        xmap_inv = list(xrange(256))
        state = hash_string(seed)
        for i in xrange(255, 0, -1):
            j = state % i
            state = hash_iterate(state)
            xmap[i], xmap[j] = xmap[j], xmap[i]
        for i in xrange(256):
            xmap_inv[xmap[i]] = i
        self.xlat_map = xmap
        self.xlat_map_inv = xmap_inv
    self.xlat_seed = xlat_seed
    self.xlat_map = None
    self.xlat_map_inv = None

    def xlat_string(s, inverse=False):
        if inverse:
            return ''.join([chr(self.xlat_map_inv[ord(c)]) for c in s])
        return ''.join([chr(self.xlat_map[ord(c)]) for c in s])
    self.xlat_string = xlat_string

    def read(delim=None, length=None, expect=None):
        if self.xlat_map:
            if delim:
                delim = self.xlat_string(delim)
            if expect:
                expect = self.xlat_string(expect)
        return self._original_read(delim=delim, length=length, expect=expect)
    self._original_read = self.read
    self.read = read

    def write(s):
        if self.xlat_map:
            if s:
                s = self.xlat_string(s)
        return self._original_write(s)
    self._original_write = self.write
    self.write = write

pack_bytes = lambda x: struct.pack("{0}B".format(len(x)), *x)
byte_str = lambda x: "\\x%02x" % int(x)

def hfname(name):
    for x in reversed(xrange(len(name))):
        if ord(name[x]) != 0x20:
            return name[:x+1]
    return None

def parent_dir(path):
    if path == '/':
        return None
    path = path if path[-1] != '/' else path[:-1]
    return path.rpartition('/')[0] + '/'

def random_filename(max_size=11, min_size=3):
    if random.randint(0,4):
        characters = string.letters + string.digits
    else:
        characters = string.letters
        max_size = max_size if max_size >= min_size else min_size
        max_size = random.randint(min_size, max_size)
    word = ("".join(random.choice(characters) for c in range(max_size))).upper()
    while (len(word) < 11):
        word += ' '
    return word


def random_text(max_words=10, min_words=3):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
        return text

def random_data(size):
    buf = random_text()
    while len(buf) < size:
        buf += random_text()
    buf = buf[:size]
    return buf

def random_bytes(size):
    return [random.randint(0,255) for x in xrange(size)]

def random_file_name():
    filename = ''
    for x in xrange(random.randint(0,5)):
        filename += '/' + random_filename()

    return filename

class Bhdr(object):
    def __init__(self):
        self.bytes_per_sector = 512
        self.sectors_per_cluster = 1
        self.num_reserved_sectors = 32
        self.num_cgfst = 1
        self.root_cluster_idx = 2
        self.total_sectors_small = 0
        self.total_sectors_large = 0
        self.sectors_per_cgfst = 0

    def serialize(self):
        fs_ser = struct.pack('3s', 3*'\x00')
        fs_ser += struct.pack('8s', 'CGC_CB_FS')
        fs_ser += struct.pack('B', self.sectors_per_cluster)
        fs_ser += struct.pack('H', self.num_reserved_sectors)
        fs_ser += struct.pack('H', self.bytes_per_sector)
        fs_ser += struct.pack('B', self.num_cgfst)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('B', 2)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('I', 0)
        fs_ser += struct.pack('I', self.total_sectors_large)
        fs_ser += struct.pack('I', 2)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('H', 0)
        fs_ser += struct.pack('I', self.sectors_per_cgfst)
        fs_ser += struct.pack('H', 1)
        fs_ser += struct.pack('H', 6)
        fs_ser += struct.pack('12s', 12*'\x00')
        fs_ser += struct.pack('18s', 18*'\x00')
        fs_ser += struct.pack('8s', 'CGFSPOLL')
        fs_ser += struct.pack('419s', 419*'\x00')
        fs_ser += struct.pack('B', 8)
        fs_ser += struct.pack('2s', '\x44\x88')
        return fs_ser

    def size(self):
        return 512

    @classmethod
    def random(cls):
        hdr = cls()
        hdr.sectors_per_cgfst = random.randint(8,16)
        hdr.sectors_per_cgfst = 3
        hdr.total_sectors_large = (hdr.num_reserved_sectors + hdr.sectors_per_cgfst * hdr.num_cgfst +
                                    (hdr.sectors_per_cgfst * hdr.bytes_per_sector / 4) - 2)
        return hdr

class FsFile(object):
    def __init__(self, name=None):
        if name:
            self.name = name[0:11]
            if len(name) < 11:
                self.name += (11 - len(name)) * '\x20'
        self.attrib = 0
        self.reserved = 12 * '\x00'
        self.starting_cluster = 0
        self.size = 0
        self.data = None

    def is_free(self):
        return ord(self.name[0]) == 0x00 or ord(self.name[0]) == 0xE5

    def skip_entry(self):
        return self.attrib == 0x0F or ord(self.name[0]) == 0x00 or ord(self.name[0]) == 0xE5

    def is_directory(self):
        return (self.attrib & SUBDIRECTORY_FLAG)

    def is_file(self):
        return not (self.attrib & SUBDIRECTORY_FLAG)

    def compare_name(self, name):
        if len(name) > 11:
            return False
        return hfname(self.name) == hfname(name)

    def hname(self):
        return hfname(self.name)

    def read_from_file(self, read_fn, offset, num_bytes_to_read):
        if self.skip_entry():
            return
        for x in self.data[offset:offset+num_bytes_to_read]:
            read_fn(byte_str(x))

    def write_to_file(self, offset, bytes_to_write):
        if offset == 0:
            bytes_to_write = bytes_to_write if bytes_to_write <= self.size else self.size
        else:
            size_offset_delta = self.size - offset if self.size / 512 == offset / 512 else 0
            bytes_to_write = 512 - (offset % 512) if size_offset_delta <= 0 else size_offset_delta
            bytes_to_write = 0 if self.size <= offset else bytes_to_write
        write_buf = random_bytes(bytes_to_write)
        self.data = self.data[0:offset] + write_buf + self.data[offset+bytes_to_write:]
        return bytes_to_write, write_buf

    def delete_entry(self):
        self.name = chr(0xE5) + self.name[1:]

    def read_entry(self, read_fn, pwd, recursive=False):
        if self.skip_entry():
            return
        if self.is_file():
            read_fn("File Name: {0}\x0e".format(self.name))
        else:
            read_fn("Directory Name: {0}\x0e".format(pwd + self.name + '/'))

    @classmethod
    def random(cls, is_file=None):
        fs_file = cls(random_filename())
        if is_file == None:
            if (random.randint(0,5) == 0):
                fs_file.attrib |= SUBDIRECTORY_FLAG
                fs_file.size = 0
            else:
                fs_file.size = random.randint(100, 3000)
        elif is_file == True:
            fs_file.size = random.randint(100, 3000)
        else:
            fs_file.attrib |= SUBDIRECTORY_FLAG
            fs_file.size = 0
        return fs_file

class DirectoryTree(object):
    def __init__(self, entry=None):
        self.entry = entry
        self.file_list = []
        self.dir_list = []
        self.print_list = []

    def add_to_print_list(self, fs_entry):
        for i, entry in enumerate(self.print_list):
            if entry.is_free():
                self.print_list[i] = fs_entry
                return
        self.print_list.append(fs_entry)

    def length(self):
        if self.entry.skip_entry():
            return None
        length = 0
        for dir_ in self.dir_list:
            if dir_.entry.skip_entry():
                continue
            length += 1
        for file_ in self.file_list:
            if file_.skip_entry():
                continue
            length += 1
        return length


    def get_random_file(self, pwd, odds=20):
        if self.entry.skip_entry():
            return None

        pwd = pwd + self.entry.hname() + '/' if pwd and self.entry.hname()!= '/' else self.entry.hname()
        for dir_ in self.dir_list:
            if dir_.entry.skip_entry():
                continue
            random_file = dir_.get_random_file(pwd)
            if random_file:
                return random_file
        for file_ in self.file_list:
            if file_.skip_entry():
                continue
            if random.randint(1,odds) == 1:
                return (pwd + file_.hname()), file_
        return None

    def get_random_dir(self, pwd, odds=20):
        if self.entry.skip_entry():
            return None

        pwd = pwd + self.entry.hname() + '/' if pwd and self.entry.hname()!= '/' else self.entry.hname()
        for dir_ in self.dir_list:
            if dir_.entry.skip_entry():
                continue
            random_dir = dir_.get_random_dir(pwd)
            if random_dir:
                return random_dir
        if random.randint(1,odds) == 1:
            return pwd, self
        return None

    def add_entry(self, pwd, parent_dir, fs_entry):
        if self.entry.skip_entry():
            return None
        pwd = pwd + self.entry.hname() + '/' if pwd and self.entry.hname()!= '/' else self.entry.hname()
        parent_dir = parent_dir if parent_dir[-1] == '/' else parent_dir + '/'

        if pwd == parent_dir:
            self.add_to_print_list(fs_entry)
            if fs_entry.is_file():
                for i, file_ in enumerate(self.file_list):
                    if file_.is_free():
                        self.file_list[i] = fs_entry
                        return True
                self.file_list.append(fs_entry)
                return True
            else:
                for i, dir_ in enumerate(self.dir_list):
                    if dir_.entry.is_free():
                        self.dir_list[i] = DirectoryTree(fs_entry)
                        return True
                self.dir_list.append(DirectoryTree(fs_entry))
                return True

        for dir_ in self.dir_list:
            if dir_.entry.skip_entry():
                continue
            if dir_.add_entry(pwd, parent_dir, fs_entry):
                return True

        return False


    def find_entry(self, pwd, path):
        if self.entry.skip_entry():
            return None
        pwd = pwd + self.entry.hname() + '/' if pwd and self.entry.hname()!= '/' else self.entry.hname()
        is_directory = False
        dirpath = path
        if path[-1] == '/':
            is_directory = True
            dirpath = path[:-1]

        for dir_ in self.dir_list:
            if dir_.entry.skip_entry():
                continue
            if dirpath == pwd + self.entry.hname():
                return self.entry
            found_entry = dir_.find_entry(pwd, path)
            if found_entry:
                return found_entry

        if not is_directory:
            for file_ in self.file_list:
                if file_.skip_entry():
                    continue
                if path == pwd + file_.hname():
                    return file_
        return None

    def read_entry(self, read_fn, pwd=None, recursive=False):
        if self.entry.skip_entry():
            return
        pwd = pwd + self.entry.hname() + '/' if pwd and self.entry.hname()!= '/' else self.entry.hname()
        read_fn("Directory Name: {0}\x0e".format(pwd))
        if self.length() == 0:
            read_fn("    --Empty Directory--\x0e\x0e");
        else:
            for entry in self.print_list:
                if not entry.is_free() and entry.is_directory():
                    read_fn("    Subdirectory Name: {0}\x0e".format(entry.name))
            for entry in self.print_list:
                if not entry.is_free() and entry.is_file():
                    read_fn("    File Name: {0}\x0e".format(entry.name))
            read_fn("\x0e")

        if recursive:
            for entry in self.print_list:
                if not entry.is_free() and entry.is_directory():
                    for dir_ in self.dir_list:
                        if dir_.entry == entry:
                            dir_.read_entry(read_fn, pwd, recursive)
                            break


class CgFs(object):
    def __init__(self):
        self.hdr = Bhdr.random()
        self.fs_info_sector = struct.pack('512s', 512 * '\x00')

        total_sectors = self.hdr.total_sectors_small if self.hdr.total_sectors_small else self.hdr.total_sectors_large;

        self.raw_data_size = (total_sectors * self.hdr.bytes_per_sector) - self.hdr.size() - len(self.fs_info_sector)
        self.num_clusters = (self.hdr.sectors_per_cgfst * self.hdr.bytes_per_sector) / 4
        self.raw_data = list(struct.pack('{0}s'.format(self.raw_data_size), self.raw_data_size * '\x00'))

        self.cluster_map_idx_0 = self.hdr.num_reserved_sectors * self.hdr.bytes_per_sector - self.hdr.size() - len(self.fs_info_sector)
        self.cluster_region_idx_0 = (self.cluster_map_idx_0 +
                                        ((self.hdr.sectors_per_cgfst * self.hdr.num_cgfst) * self.hdr.bytes_per_sector))
        self.cluster_size = self.hdr.bytes_per_sector * self.hdr.sectors_per_cluster

        root_fs = FsFile()
        root_fs.name = '/' + 10 * '\x20'
        root_fs.starting_cluster = 2
        self.root_dir = DirectoryTree(root_fs)

        self.all_files = {}
        self.all_dirs = {}

    def serialize(self):
        fs_ser = self.hdr.serialize()
        fs_ser += self.fs_info_sector
        fs_ser += ''.join(self.raw_data)
        return fs_ser


class FileMountTool(Actions):
    def _find_file(self):
        if not self.is_mounted or not self.fs:
            return None

        odds = 10
        entry = self.fs.root_dir.get_random_file('', odds)
        while not entry and odds:
            odds -= 1
            entry = self.fs.root_dir.get_random_file('', odds)
        return entry

    def _find_dir(self):
        if not self.is_mounted or not self.fs:
            return None
        odds = 10
        entry = self.fs.root_dir.get_random_dir(None, odds)
        while not entry and odds:
            odds -= 1
            entry = self.fs.root_dir.get_random_dir(None, odds)
        return entry

    def _get_random_byte(self):
        self.p1 = ctypes.c_uint32(ctypes.c_uint32(47070 * (self.p1 & 65535)).value + ctypes.c_uint32((self.p1 >> 16)).value).value
        self.p2 = ctypes.c_uint32(ctypes.c_uint32(84818 * (self.p2 & 65535)).value + ctypes.c_uint32((self.p2 >> 16)).value).value
        byte_idx =  (ctypes.c_uint32((self.p1 << 16)).value + self.p2) % 4096;
        return struct.unpack('<B', self.magic_page[byte_idx])[0]

    def _read(self, data):
        self.read(length=len(data), expect=data)

    def start(self):
        #self.delay(100)
        self.is_mounted = False
        kaprica_mixin(self)
        self.xlat_seed('2281771')

        self.p1 = ctypes.c_uint32(struct.unpack('<I', self.magic_page[400:404])[0]).value
        self.p2 = ctypes.c_uint32(struct.unpack('<I', self.magic_page[404:408])[0]).value

        self._read("MOUNT FILEMORE v 1.0\x0e");
        self._read("\x0e\x0e");

        self.fs = None
        self.is_mounted = False

    def unmounted(self):
        self._read("Options:\x0e");
        self._read("1. Mount File\x0e");
        self._read("2. Exit\x0e");
        self._read(":> ");

    def mount(self):
        self.write('1\x0e')
        self.fs = CgFs()
        self.is_mounted = True
        self.write(self.fs.serialize())
        self._read("Successfully mounted file system\x0e");

    def mounted(self):
        self._read("Options:\x0e");
        self._read("1. List File/Directory\x0e");
        self._read("2. Recursively List Files/Directories\x0e");
        self._read("3. Preview File\x0e");
        self._read("4. Read From File\x0e");
        self._read("5. Write To File\x0e");
        self._read("6. Update File Size\x0e");
        self._read("7. Add File\x0e");
        self._read("8. Add Directory\x0e");
        self._read("9. Delete File\x0e");
        self._read("10. Delete Directory\x0e");
        self._read("11. View Mounted Filesystem Metadata\x0e");
        self._read("12. Unmount Filesystem\x0e");
        self._read("13. Exit\x0e");
        self._read(":> ");

    def list_files(self):
        self.write('1\x0e')
        self._read("Enter Path\x0e");
        self._read(":> ");

        if random.randint(1,2) == 2:
            entry = self._find_file()
        else:
            entry = self._find_dir()

        if not entry:
            path = random_file_name()
            self.write('\\' + path + '\x0e')
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            fs_entry.read_entry(self._read, parent_dir(path))


    def recursively_list_files(self):
        self.write('2\x0e')
        self._read("Enter Path To Recurse\x0e");
        self._read(":> ");

        entry = self._find_dir()
        path,fs_entry = entry
        self.write(path + '\x0e')
        fs_entry.read_entry(self._read, parent_dir(path), True)

    def preview_file(self):
        self.write('3\x0e')
        self._read("Enter Path Of File To Preview\x0e");
        self._read(":> ");

        entry = self._find_file()
        if not entry:
            path = random_file_name()
            self.write('\\' + path + '\x0e')
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            read_size = fs_entry.size if fs_entry.size < 512 else 512
            fs_entry.read_from_file(self._read, 0, read_size)
            self._read('\x0e')

    def read_file(self):
        self.write('4\x0e')

        self._read("Enter Path Of File To Read From\x0e");
        self._read(":> ");

        entry = self._find_file()
        if not entry:
            path = random_file_name()
            self.write('\\' + path + '\x0e')
            offset = random.randint(1,1000)
            read_size = random.randint(1,1000)
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            if random.randint(1,5) == 1:
                offset = random.randint(0,fs_entry.size / 2)
            else:
                offset = 0
            read_size = random.randint(1, fs_entry.size)

        self._read("Enter Offset\x0e");
        self._read(":> ");
        self.write("{0}\x0e".format(offset))
        self._read("Enter Number Of Bytes To Read\x0e");
        self._read(":> ");
        self.write("{0}\x0e".format(read_size))
        if entry:
            fs_entry.read_from_file(self._read, offset, read_size)
            self._read('\x0e')

    def write_file(self):
        self.write('5\x0e')
        self._read("Enter Path Of File To Write To\x0e");
        self._read(":> ");

        entry = self._find_file()
        write_buf = None
        if not entry:
            path = random_file_name()
            self.write('\\' + path + '\x0e')
            offset = random.randint(20,400)
            write_size = random.randint(20,400)
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            if random.randint(1,5) == 1:
                offset = random.randint(0,fs_entry.size / 2)
            else:
                offset = 0
            write_size = random.randint(1, fs_entry.size)
            write_size, write_buf = fs_entry.write_to_file(offset, write_size)

        self._read("Enter Offset\x0e");
        self._read(":> ");
        self.write("{0}\x0e".format(offset))
        self._read("Enter Number Of Bytes To Write\x0e");
        self._read(":> ");
        self.write("{0}\x0e".format(write_size))

        if write_size:
            self._read("Enter File Data To Be Written: [%d bytes]\x0e" % write_size);
            if write_buf:
                self.write(pack_bytes(write_buf))
                self._read("Successfully wrote: \x0e")
                for x in write_buf:
                    self._read(byte_str(x))
                self._read("\x0e")
            else:
                write_buf = write_size * [0]
                self.write(pack_bytes(write_buf))

    def update_file(self):
        self.write('6\x0e')
        self._read("Enter Path Of File To Update\x0e");
        self._read(":> ");

        entry = self._find_file()
        write_buf = None
        if not entry:
            path = random_file_name()
            self.write('\\' + path + '\x0e')
            new_size = random.randint(1,1000)
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            new_size = random.randint(fs_entry.size /2, fs_entry.size)

        self._read("Enter New Size\x0e");
        self._read(":> ");
        self.write("{0}\x0e".format(new_size))

        if entry:
            self._read("File %s has a new file size of: %d\x0e" % (path, new_size))
            fs_entry.size = new_size
            fs_entry.data= fs_entry.data[:new_size]
        else:
            self._read("Could not update file size\x0e");

    def add_file(self):
        self.write('7\x0e')

        self._read("Enter Parent Directory Of New File\x0e");
        self._read(":> ");
        entry = self._find_dir()
        path,fs_entry = entry
        new_file = FsFile.random(True)
        self.write(path + '\x0e')

        self._read("Enter Name Of New File\x0e");
        self._read(":> ");
        self.write(new_file.name + '\x0e')

        self._read("Enter Size Of New File\x0e");
        self._read(":> ");
        self.write('{0}\x0e'.format(new_file.size))

        self._read("Input File Data?\x0e");
        self._read("1. Yes\x0e");
        self._read("2. No\x0e");
        self._read("3. Fill With Random Data\x0e")
        self._read(":> ");

        choice = random.randint(1,3)
        self.write("{0}\x0e".format(choice))

        if choice == 1:
            self._read("Enter File Data To Be Written: [%d bytes]\x0e" % new_file.size);
            new_file.data = random_bytes(new_file.size)
            self.write(pack_bytes(new_file.data))
        elif choice == 2:
            new_file.data = new_file.size *[0x00]
        elif choice == 3:
            new_file.data = []
            for x in xrange(new_file.size):
                new_file.data.append(self._get_random_byte())


        self._read("Successfully added file\x0e");
        self._read("Parent dir: {0}\x0e".format(path))
        self._read("New file name: {0}\x0e".format(new_file.name))
        self.fs.root_dir.add_entry(None, path, new_file)
        if choice != 2:
            self._read("Data written to disk: \x0e")
            for x in new_file.data:
                self._read(byte_str(x))
            self._read('\x0e')

    def add_directory(self):
        self.write('8\x0e')

        self._read("Enter Parent Directory Of New Directory\x0e");
        self._read(":> ");
        entry = self._find_dir()
        path,fs_entry = entry
        new_file = FsFile.random(False)
        self.write(path + '\x0e')

        self._read("Enter Name Of New Directory\x0e");
        self._read(":> ");
        self.write(new_file.name + '\x0e')

        self._read("Successfully added directory\x0e");
        self._read("Parent dir: {0}\x0e".format(path))
        self._read("New directory name: {0}\x0e".format(new_file.name))

        self.fs.root_dir.add_entry(None, path, new_file)

    def delete_file(self):
        self.write('9\x0e')
        self._read("Enter Path Of File To Delete\x0e");
        self._read(":> ");

        entry = self._find_file()
        if not entry:
            path = random_file_name()
            self.write('\\' + path + '\x0e')
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            fs_entry.delete_entry()
            self._read("Successfully deleted file\x0e");
            self._read("Deleted file: %s\x0e" % path);

    def delete_directory(self):
        entry = self._find_dir()
        if not entry:
            path = random_dir_name()
        else:
            path,fs_entry = entry
            if path == '/':
                self.write("99\x0e")
                return

        self.write('10\x0e')
        self._read("Enter Path Of Directory To Delete\x0e");
        self._read(":> ");
        if not entry:
            path = random_dir_name()
            self.write('\\' + path + '\x0e')
        else:
            path,fs_entry = entry
            self.write(path + '\x0e')
            fs_entry.entry.delete_entry()
            fs_entry.file_list = []
            fs_entry.dir_list = []
            fs_entry.print_list = []
            self._read("Successfully deleted directory\x0e");
            self._read("Deleted directory: %s\x0e" % path);

    def view_metadata(self):
        self.write('11\x0e')

    def unmount(self):
        self.write('12\x0e')
        self._read("Successfully unmounted file system\x0e");
        self._read("Could not unmount file system\x0e");

    def exit(self):
        #self.comment('nothing left to test')
        if not self.is_mounted:
            self.write('2\x0e')
        else:
            self.write('13\x0e')
        self._read("Exiting....\x0e");

