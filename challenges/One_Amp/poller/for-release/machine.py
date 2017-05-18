#!/usr/bin/env python

from generator.actions import Actions
import random
import struct
import ctypes
import string

MAX_USER_PLAYLISTS = 10

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

def random_word(max_size=8, min_size=3):
    if random.randint(0,4):
        characters = string.letters + string.digits
    else:
        characters = string.letters
        max_size = max_size if max_size >= min_size else min_size
        max_size = random.randint(min_size, max_size)
    word = ("".join(random.choice(characters) for c in range(max_size))).upper()
    return word


def random_text(pad_size=0, max_words=5, min_words=1):
    max_words = max_words if max_words >= min_words else min_words
    text = ''
    for x in xrange(random.randint(min_words, max_words)):
        text += random_word() + ' '
    if not pad_size:
        return text

    text = text[:pad_size] if len(text) >= pad_size else text + '\x00' * (pad_size - len(text))
    return text


def random_file_name():
    filename = ''
    for x in xrange(random.randint(0,5)):
        filename += '/' + random_filename()

    return filename


pack_str = lambda x: struct.pack("{0}s".format(len(x)), x)
pack_bytes = lambda x: struct.pack("{0}B".format(len(x)), *x)
byte_str = lambda x: "\\x%02x" % int(x)

class SongTag(object):
    def __init__(self, song_id, title=None, artist=None, album=None, year=None, comment=None):
        self.header = "CTG"
        self.title = title if title else random_text(pad_size=30)
        self.artist = artist if artist else random_text(pad_size=30)
        self.album = album if album else random_text(pad_size=30)
        self.year = year if year else 1970 + random.randint(0,45)
        self.comment = comment if comment else random_text(pad_size=30)
        self.has_track = '\x00'
        self.track = random.randint(1,20)
        self.unused = '\x00'
        self.song_id = song_id

    def serialize(self):
        tag_ser = pack_str(self.header)
        tag_ser += pack_str(self.title)
        tag_ser += pack_str(self.artist)
        tag_ser += pack_str(self.album)
        tag_ser += struct.pack('H', self.year)
        tag_ser += pack_str(self.comment)
        tag_ser += pack_str(self.has_track)
        tag_ser += struct.pack('b', self.track)
        tag_ser += pack_str(self.unused)
        return tag_ser

    @classmethod
    def random(cls, song_id, all_songs):
        if (len(all_songs) and random.randint(0,4) == 0):
            song = all_songs[random.randint(0, len(all_songs) -1)]
            matched_field_choice = random.randint(0,1)
            if matched_field_choice == 0:
                return cls(song_id, artist=song.tag.artist)
            elif matched_field_choice == 1:
                return cls(song_id, artist=song.tag.artist, album=song.tag.album, year=song.tag.year)
        else:
            return cls(song_id)

bitrates = [0, 320000, 256000, 224000, 192000, 160000, 128000, 112000, 96000, 80000, 64000, 56000, 48000, 40000, 32000]
freqs = [44100, 48000, 32000]
class SongFrame(object):
    def __init__(self, layer, sfreq, num_frames_left):
        self.hdr = [0xFF, 0xF0, 0x00]
        self.hdr[1] |= 0x08
        self.hdr[1] |= layer << 1
        self.hdr[2] |= random.randint(1,14) << 4
        self.hdr[2] |= sfreq << 2
        self.num_frames_left = num_frames_left

        self.data = []
        data_len = (self.samples_per_frame() / 8 * self.bitrate()) / self.freq()
        data_len = data_len if data_len % 4 == 0 else data_len + (4 - (data_len % 4))
        for x in xrange(data_len):
            self.data.append(random.randint(0,255))

    def layer(self):
        return (self.hdr[1] & 0x06) >> 1

    def samples_per_frame(self):
        if (self.layer()) == 1:
            return 384
        if (self.layer()) == 2:
            return 1152
        if (self.layer()) == 3:
            return 1152
        return 0

    def bitrate(self):
        return bitrates[(self.hdr[2] & 0xF0) >> 4]

    def freq(self):
        return freqs[(self.hdr[2] & 0x0C) >> 2]

    def serialize(self):
        frame_ser = pack_bytes(self.hdr)
        frame_ser += struct.pack('H', self.num_frames_left)
        frame_ser += pack_bytes(self.data)
        return frame_ser

    @classmethod
    def random(cls):
        song_frames = []
        num_frames_left = random.randint(1,10)
        layer = random.randint(1,3)
        sfreq = random.randint(0,2)
        for x in reversed(xrange(num_frames_left)):
            song_frames.append(cls(layer, sfreq, x))
        return song_frames


class Song(object):
    def __init__(self, tag, frames):
        self.tag = tag
        self.frames = frames

    def remix_song(self, state, magic_page):
        idx = state['remix_idx']
        for i in xrange(len(self.frames)):
            for j in xrange(len(self.frames[i].data)):
                multiplier = struct.unpack('<B', magic_page[idx])[0]
                data_val = self.frames[i].data[j]
                data_val = (data_val * multiplier) % 256
                self.frames[i].data[j] = data_val
                idx = (idx + 33) % 4096
        state['remix_idx'] = idx

    def serialize(self):
        song_ser = ''
        for frame in self.frames:
            song_ser += frame.serialize()
        song_ser += self.tag.serialize()
        return song_ser

    def read_song(self, read_fn):
        read_fn("Song ID: %d\x02" % self.tag.song_id)
        read_fn("Title: %s\x02" % self.tag.title)
        read_fn("Artist: %s\x02" % self.tag.artist)
        read_fn("Album: %s\x02" % self.tag.album)
        read_fn("Year: %d\x02" % self.tag.year)
        read_fn("Track #: %d\x02" % self.tag.track)
        read_fn("----------\x02")

    def read_frames(self, read_fn):
        read_fn("---Raw Frames---\x02")
        for frame in self.frames:
            for x in frame.data:
                read_fn(byte_str(x))
        read_fn("\x02----------------\x02")

    @classmethod
    def random(cls, song_id, all_songs):
        return cls(SongTag.random(song_id, all_songs), SongFrame.random())

class Playlist(object):
    def __init__(self):
        self.songs = []

    def add_song(self, song):
        self.songs.append(song)

    def remove_song(self, song_id):
        for i in xrange(len(self.songs)):
            if self.songs[i].tag.song_id == song_id:
                self.songs.pop(i)
                return True
        return False

    def find_song(self, song_id):
        for i in xrange(len(self.songs)):
            if self.songs[i].tag.song_id == song_id:
                return self.songs[i]
        return None

    def remix_song(self, song_id, state, magic_page):
        for i in xrange(len(self.songs)):
            if self.songs[i].tag.song_id == song_id:
                self.songs[i].remix_song(state, magic_page)
                return True
        return False

    def read_songs(self, read_fn):
        for song in self.songs:
            song.read_song(read_fn)

    def read_song_frames(self, song_idx, read_fn):
        song = self.find_song(song_idx)
        if song:
            song.read_frames(read_fn)

    def read_playlist(self, read_fn, playlist_id):
        read_fn("Playlist ID: %d\x02" % playlist_id)
        read_fn("Number of songs added to playlist: %d\x02" % len(self.songs))

class OneAmp(Actions):
    def _read(self, data):
        self.read(length=len(data), expect=data)

    def start(self):
        #self.delay(100)
        kaprica_mixin(self)
        self.xlat_seed('393748225')

        self.state['remix_idx'] = ctypes.c_uint32(struct.unpack('<B', self.magic_page[2])[0]).value
        self._playlists = []
        self._master_playlist = Playlist()
        self._cur_playlist = self._master_playlist
        self._song_id_idx = 0

        self._read("--One Amp--\x02")
        self._read("\x02\x02")

    def master_menu(self):
        self._read("Main Menu:\x02")
        self._read("1. Add Song To Library\x02")
        self._read("2. Delete Song From Library\x02")
        self._read("3. Select Playlist\x02")
        self._read("4. List Songs\x02")
        self._read("5. Sort By Song ID (Default Sort)\x02")
        self._read("6. Sort By Song Title\x02")
        self._read("7. Sort By Artist and Album\x02")
        self._read("8. Sort By Artist and Song Title\x02")
        self._read("9. Sort By Album\x02")
        self._read("10. Sort By Album and Song Title\x02")
        self._read("11. Remix Track\x02")
        self._read("12. Create Playlist\x02")
        self._read("13. Delete Playlist\x02")
        self._read("14. List Playlists\x02")
        self._read("15. Exit\x02")
        self._read("[::]  ")

    def playlist_menu(self):
        self._read("Main Menu:\x02")
        self._read("1. Add Song To Playlist\x02")
        self._read("2. Delete Song From Playlist\x02")
        self._read("3. Return to Main Library\x02")
        self._read("4. List Songs\x02")
        self._read("5. Sort By Song ID (Default Sort)\x02")
        self._read("6. Sort By Song Title\x02")
        self._read("7. Sort By Artist and Album\x02")
        self._read("8. Sort By Artist and Song Title\x02")
        self._read("9. Sort By Album\x02")
        self._read("10. Sort By Album and Song Title\x02")
        self._read("11. Remix Track\x02")
        self._read("12. List All Songs In Library\x02")
        self._read("13. Exit\x02")
        self._read("[::]  ")

    def master_add_song(self):
        self.write('1\x02')
        song = Song.random(self._song_id_idx, self._master_playlist.songs)
        self._song_id_idx += 1
        self._master_playlist.add_song(song)
        self.write(song.serialize())
        self._read("Added song to library\x02")

    def master_remove_song(self):
        self.write('2\x02')
        self._read("Enter Song ID to delete from library\x02")
        self._read("[::] ")
        song_idx = random.randint(0, 2*len(self._master_playlist.songs))
        self.write('{0}\x02'.format(song_idx))
        if self._master_playlist.remove_song(song_idx):
            for x in xrange(len(self._playlists)):
                self._playlists[x].remove_song(song_idx)
            self._read("Successfully removed song from library\x02")
        else:
            self._read("Could not remove song from library\x02")

    def master_select_playlist(self):
        self.write('3\x02')
        self._read("Select Playlist ID\x02")
        self._read("[::] ")

        if not len(self._playlists):
            self.write('0\x02')
            self._read("Bad Playlist ID\x02")
            self.master_menu()
            self.master_create_new_playlist()
            self.master_menu()

            self.write('3\x02')
            self._read("Select Playlist ID\x02")
            self._read("[::] ")

        playlist_idx = random.randint(0, len(self._playlists) - 1)
        self.write('{0}\x02'.format(playlist_idx))
        self._cur_playlist = self._playlists[playlist_idx]


    def playlist_add_song(self):
        self.write('1\x02')
        self._read("Enter Song ID to add to playlist\x02")
        self._read("[::] ")

        song_idx = random.randint(0, len(self._master_playlist.songs) + 10)
        self.write('{0}\x02'.format(song_idx))

        song = self._master_playlist.find_song(song_idx)
        already_added = self._cur_playlist.find_song(song_idx)
        if song and not already_added:
            self._cur_playlist.add_song(song)
            self._read("Added song to playlist\x02")
        else:
            self._read("Could not add song to playlist\x02")

    def playlist_delete_song(self):
        self.write('2\x02')
        self._read("Enter Song ID to delete from playlist\x02")
        self._read("[::] ")
        if len(self._cur_playlist.songs) and random.randint(0,3) == 0:
            song_idx = self._cur_playlist.songs[random.randint(0, len(self._cur_playlist.songs)-1)].tag.song_id
        else:
            song_idx = random.randint(0, 2*len(self._master_playlist.songs))
        self.write('{0}\x02'.format(song_idx))
        if self._cur_playlist.remove_song(song_idx):
            self._read("Successfully removed song from playlist\x02")
        else:
            self._read("Could not remove song from playlist\x02")

    def playlist_select_master(self):
        self.write('3\x02')
        self._cur_playlist = self._master_playlist

    def list_all_songs(self):
        self.write('4\x02')
        self._cur_playlist.read_songs(self._read)

    def sort_playlist_by_song_id(self):
        self.write('5\x02')
        self._cur_playlist.songs.sort(key=lambda song: song.tag.song_id)
        self._read("Successfully sorted list by Song ID\x02")

    def sort_playlist_by_song_title(self):
        self.write('6\x02')
        self._cur_playlist.songs.sort(key=lambda song: song.tag.title)
        self._read("Successfully sorted list by Song Title\x02")

    def remix_song(self):
        self.write('11\x02')
        self._read("Enter Song ID to remix\x02")
        self._read("[::] ")
        song_idx = random.randint(0, 2*len(self._master_playlist.songs))
        self.write('{0}\x02'.format(song_idx))

        if self._cur_playlist.find_song(song_idx):
            self._read("Original Track Data:\x02")
            self._master_playlist.read_song_frames(song_idx, self._read)

            self._master_playlist.remix_song(song_idx, self.state, self.magic_page)
            self._read("Successfully remixed song\x02")
            self._read("Printing New Track Data:\x02")
            self._master_playlist.read_song_frames(song_idx, self._read)
        else:
            self._read("Could not remix track\x02")

    def master_create_new_playlist(self):
        self.write('12\x02')
        if len(self._playlists) < MAX_USER_PLAYLISTS:
            self._read("Created a new playlist with ID [%d]\x02" % len(self._playlists))
            self._playlists.append(Playlist())
        else:
            self._read("Maximum number of playlists reached\x02")


    def master_delete_playlist(self):
        self.write('13\x02')
        self._read("Enter Playlist ID to delete")
        self._read("[::] ")

        playlist_idx = random.randint(0, 2*len(self._playlists))
        self.write('{0}\x02'.format(playlist_idx))
        if playlist_idx < len(self._playlists):
            self._playlists.pop(playlist_idx)
            self._read("Deleted Playlist ID: %d\x02" % playlist_idx)
        else:
            self._read("Bad Playlist ID\x02")

    def master_print_all_playlists(self):
        self.write('14\x02')
        for idx, playlist in enumerate(self._playlists):
            playlist.read_playlist(self._read, idx)

    def playlist_all_library_songs(self):
        self.write('12\x02')
        self._master_playlist.read_songs(self._read)

    def exit(self):
        if self._cur_playlist == self._master_playlist:
            self.write('15\x02')
        else:
            self.write('13\x02')
        self._read("--Exited One Amp--\x02")

    def master_list_all_songs(self):
        self.list_all_songs()

    def master_sort_playlist_by_song_id(self):
        self.sort_playlist_by_song_id()

    def master_sort_playlist_by_song_title(self):
        self.sort_playlist_by_song_title()

    def master_remix_song(self):
        self.remix_song()

    def playlist_sort_playlist_by_song_id(self):
        self.sort_playlist_by_song_id()

    def playlist_sort_playlist_by_song_title(self):
        self.sort_playlist_by_song_title()

    def playlist_remix_song(self):
        self.remix_song()

