#!/usr/bin/env python
from cStringIO import StringIO
from generator.actions import Actions
import random
import struct

SAMPLE_RATE = 8000.0
SAMPLE_MAX = 0x7FFFFFFF
SAMPLE_MIN = -0x80000000

# *$!@ this #%*!
def c_div(num, denom):
    neg = -1 if num < 0 else 1
    if num < 0:
        num = -num
    return neg * (num / denom)

def saturate(value):
    if value > SAMPLE_MAX:
        value = SAMPLE_MAX
    elif value < SAMPLE_MIN:
        value = SAMPLE_MIN
    return value

class Compression4(object):
    index_table = [
        -1, -1, -1, -1, 1, 3, 6, 9
    ]

    step_table = [
        6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 
        19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 
        50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 
        130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
        337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
        876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 
        2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
        5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 
        15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767 
    ]

    def __init__(self, output):
        self.output = output

    def next_samples(self):
        samples = [c.data[self.idx] >> 16 for c in self.track.channels]
        self.idx += 1
        return samples

    def best_index(self, sample1, sample2):
        diff = abs(sample2 - sample1)
        best = None
        for i in xrange(len(self.step_table)):
            step = self.step_table[i]
            if best is None or abs(step - diff) < best[1]:
                best = (i, abs(step - diff))
        return best[0]

    def new_block(self):
        self.pred = []
        self.index = []
        samples = self.next_samples()
        for x in xrange(len(samples)):
            sample = samples[x]
            self.pred.append(sample)
            if self.idx < self.track.samples():
                self.index.append(self.best_index(sample, self.track.channels[x].data[self.idx] >> 16))
            else:
                self.index.append(self.best_index(sample, 0))
            self.output.write(struct.pack('<hBB', sample, self.index[x], 0))

    def decode(self, value, ch):
        step = self.step_table[self.index[ch]]
        self.index[ch] += self.index_table[value & 7]

        if value & 8:
            step = -step
        if value & 4:
            self.pred[ch] += step
        if value & 2:
            self.pred[ch] += step >> 1
        if value & 1:
            self.pred[ch] += step >> 2
        self.index[ch] = min(7, max(self.index[ch], 0))
        self.pred[ch] = min(0x7FFF, max(self.pred[ch], -0x8000))
        return self.pred[ch]

    def encode(self, sample, ch):
        diff = sample - self.pred[ch]
        if diff < 0:
            value = 0x8
            diff = -diff
        else:
            value = 0x0
        step = self.step_table[self.index[ch]]
        value |= min(diff * 4 / step, 7)
        self.decode(value, ch)
        return value

    def compress(self, track):
        self.track = track
        self.idx = 0
        while self.idx < self.track.samples():
            if (self.output.tell() % 512) == 0:
                # output block header
                self.new_block()
            else:
                samples = self.next_samples()
                if len(samples) == 1:
                    samples += self.next_samples()
                    self.output.write(struct.pack('<B', (self.encode(samples[0], 0) << 4) | self.encode(samples[1], 0)))
                else:
                    self.output.write(struct.pack('<B', (self.encode(samples[0], 0) << 4) | self.encode(samples[1], 1)))

class Gain(object):
    def __init__(self, value):
        self.value = saturate(value)

    @classmethod
    def from_double(cls, value):
        if value < 0:
            raise NotImplemented()
        if value >= 1:
            return Gain(int((value - 1) / 10 * SAMPLE_MAX))
        else:
            return Gain(int((1/value - 1) / 10 * -SAMPLE_MAX))

    @classmethod
    def from_rational(cls, num, denom):
        return Gain(int(float(num) / float(denom) / 10 * SAMPLE_MAX))
#        return Gain(c_div(c_div(num * SAMPLE_MAX, denom), 10))

    @classmethod
    def from_pan(cls, pan):
        return Gain(0 if pan <= 0 else -pan), Gain(0 if pan > 0 else pan)

    def __add__(self, other):
        if not isinstance(other, Gain):
            raise NotImplementedError()

        x = self.value + other.value
        return Gain(x)

    def __mul__(self, other):
        if not isinstance(other, Gain):
            raise NotImplementedError()
        return Gain.from_double(self.as_double() * other.as_double())

    def as_double(self):
        x = float(self.value)
        x *= 10
        x /= SAMPLE_MAX
        if x >= 0:
            return x + 1
        else:
            return 1 / (-x + 1)

    def apply(self, sample):
        sample = int(self.as_double() * sample)
        return saturate(sample)

class AudioStream(object):
    def __init__(self, data):
        self.data = data

    @classmethod
    def fromSilence(cls, length):
        return cls([0] * length)

    @classmethod
    def fromSquareWave(cls, length, hz):
        data = []
        rate = 2 * SAMPLE_RATE / hz
        for x in xrange(length):
            if (int(x / rate) % 2) == 0:
                data.append(-(SAMPLE_MAX / 2))
            else:
                data.append(SAMPLE_MAX / 2)
        return cls(data)

    def extend(self, length):
        diff = length - len(self.data)
        if diff <= 0:
            return

        self.data += [0] * diff

    def mix(self, other, gain):
        self.extend(len(other.data))

        for x in xrange(len(other.data)):
            sample = other.data[x]
            self.data[x] = saturate(self.data[x] + gain.apply(sample))

    def apply_gain(self, gain):
        for x in xrange(len(self.data)):
            self.data[x] = saturate(gain.apply(self.data[x]))

    def apply_echo(self, delay):
        buf = [0] * delay
        gain = Gain.from_rational(-50, 100)
        for x in xrange(len(self.data)):
            wet = gain.apply(buf.pop(0))
            # mix wet and dry
            self.data[x] = saturate(self.data[x] + wet)
            # feedback with delay
            buf.append(self.data[x])

class AudioTrack(object):
    def __init__(self, channels):
        self.channels = channels
        self.gain = Gain(0)
        self.pan = 0

    @classmethod
    def fromMono(cls, left):
        return cls([left])

    @classmethod
    def fromStereo(cls, left, right):
        return cls([left, right])

    @classmethod
    def fromCompressed(cls, data):
        magic, offset, length, compid, sample_rate, channels = struct.unpack('<IIIIII', data[:24])
        data = data[24:]

        if channels == 1:
            track = cls([AudioStream.fromSilence(length)])
        else:
            track = cls([AudioStream.fromSilence(length), AudioStream.fromSilence(length)])

        if compid == 0:
            track.decompress32(data)
        elif compid == 1:
            track.decompress4(data)
        else:
            track.decompress8(data)

        return track

    def samples(self):
        return len(self.channels[0].data)

    def fix_length(self):
        if len(self.channels) <= 1:
            return
        self.channels[0].extend(len(self.channels[1].data))
        self.channels[1].extend(len(self.channels[0].data))

    def compress32(self):
        hdr = struct.pack('<IIIIII', 0x2e617564, 24, self.samples(), 0, SAMPLE_RATE, len(self.channels))
        if len(self.channels) == 1:
            data = ''.join([struct.pack('<i', self.channels[0].data[x]) for x in xrange(self.samples())])
        else:
            data = ''.join([struct.pack('<ii', self.channels[0].data[x], self.channels[1].data[x]) for x in xrange(self.samples())])
        return hdr + data

    def decompress32(self, data):
        def decode(f):
            return struct.unpack('<i', f.read(4))[0]
        f = StringIO(data)
        for x in xrange(self.samples()):
            if len(self.channels) == 1:
                self.channels[0].data[x] = decode(f)
            else:
                self.channels[0].data[x] = decode(f)
                self.channels[1].data[x] = decode(f)

    def compress8(self):
        def encode(sample):
            # reduce sample to (-8192..8192)
            sample >>= 18
            if sample >= 0:
                neg = False
            else:
                neg = True
                sample = -sample - 1

            if sample <= 30:
                value = 0x70 + (30 - sample) / 2
            elif sample <= 94:
                value = 0x60 + (94 - sample) / 4
            elif sample <= 222:
                value = 0x50 + (222 - sample) / 8
            elif sample <= 478:
                value = 0x40 + (478 - sample) / 16
            elif sample <= 990:
                value = 0x30 + (990 - sample) / 32
            elif sample <= 2014:
                value = 0x20 + (2014 - sample) / 64
            elif sample <= 4062:
                value = 0x10 + (4062 - sample) / 128
            elif sample <= 8190:
                value = 0x00 + (8190 - sample) / 258
            else:
                value = 0

            return value | (0x00 if neg else 0x80)

        hdr = struct.pack('<IIIIII', 0x2e617564, 24, self.samples(), 2, SAMPLE_RATE, len(self.channels))
        if len(self.channels) == 1:
            data = ''.join([struct.pack('<B', encode(self.channels[0].data[x])) for x in xrange(self.samples())])
        else:
            data = ''.join([struct.pack('<BB', encode(self.channels[0].data[x]), encode(self.channels[1].data[x])) for x in xrange(self.samples())])
        return hdr + data

    def decompress8(self, data):
        def decode(f):
            value = struct.unpack('<B', f.read(1))[0]
            interval = value & 0xf
            if (value & 0x70) == 0x00:
                sample = 8190 - 258 * interval;
            elif (value & 0x70) == 0x10:
                sample = 4062 - 128 * interval;
            elif (value & 0x70) == 0x20:
                sample = 2014 - 64 * interval;
            elif (value & 0x70) == 0x30:
                sample = 990 - 32 * interval;
            elif (value & 0x70) == 0x40:
                sample = 478 - 16 * interval;
            elif (value & 0x70) == 0x50:
                sample = 222 - 8 * interval;
            elif (value & 0x70) == 0x60:
                sample = 94 - 4 * interval;
            elif (value & 0x70) == 0x70:
                sample = 30 - 2 * interval;
            sample = sample if (value & 0x80) else -sample - 1
            # scale to (SAMPLE_MIN..SAMPLE_MAX)
            return sample << 18
        f = StringIO(data)
        for x in xrange(self.samples()):
            if len(self.channels) == 1:
                self.channels[0].data[x] = decode(f)
            else:
                self.channels[0].data[x] = decode(f)
                self.channels[1].data[x] = decode(f)

    def compress4(self):
        data = StringIO()
        hdr = struct.pack('<IIIIII', 0x2e617564, 24, self.samples(), 1, SAMPLE_RATE, len(self.channels))

        comp = Compression4(data)
        comp.compress(self)
        return hdr + data.getvalue()

    def apply_gain(self, gain):
        for c in self.channels:
            c.apply_gain(gain)

    def apply_pan(self, pan):
        if len(self.channels) <= 1:
            return

        leftGain, rightGain = Gain.from_pan(pan)
        self.channels[0].apply_gain(leftGain)
        self.channels[1].apply_gain(rightGain)

    def apply_echo(self, delay):
        for c in self.channels:
            c.apply_echo(delay)

class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        self.state['rng'] = 0xDEADBEEF12345678
        self.state['tracks'] = []

    def export_audio(self):
        mix = AudioTrack.fromStereo(AudioStream.fromSilence(0), AudioStream.fromSilence(0))
        for track in self.state['tracks']:
            if track is None: continue
            leftGain, rightGain = Gain.from_pan(track.pan)
            if len(track.channels) == 1:
                mix.channels[0].mix(track.channels[0], leftGain * track.gain)
                mix.channels[1].mix(track.channels[0], rightGain * track.gain)
            else:
                mix.channels[0].mix(track.channels[0], leftGain * track.gain)
                mix.channels[1].mix(track.channels[1], rightGain * track.gain)
        return mix

    def quit(self):
        self.menu()
        self.write('9\n')
        self.read(delim='\n', expect='Thank you for trying out Grit! Please leave us a nice review on the app store.\n')

    def menu(self):
        prompt = "1) New track...\n2) Import track\n3) Export...\n4) List tracks\n5) Change gain [track] [hundredths]\n6) Change pan [track] [hundredths]\n7) Combine/split [track] [?track]\n8) Effects...\n9) Quit\n"
        self.read(delim="Quit\n", expect=prompt)

    def random_audio(self, length):
        if self.chance(0.1):
            return AudioStream.fromSilence(length)
        return AudioStream.fromSquareWave(length, random.randint(200, 3000))

    def import_audio(self):
        # generate audio track and send it
        self.write('2\n')
        stereo = self.chance(0.5)
        length = random.randint(1000, 4000)
        if stereo:
            track = AudioTrack.fromStereo(self.random_audio(length), self.random_audio(length))
        else:
            track = AudioTrack.fromMono(self.random_audio(length))

        # randomly choose other compression
        comp = random.choice([track.compress32, track.compress8])
        data = comp()
        self.write(struct.pack('<I', len(data)))
        self.write(data)

        self.state['tracks'].append(AudioTrack.fromCompressed(data))

    def change_gain(self):
        # choose a random track and adjust gain
        tracks = list(filter(lambda t: t is not None, self.state['tracks']))
        if len(tracks) == 0:
            self.write('0\n')
            self.read(delim='\n', expect='Invalid choice\n')
            return
        track = random.choice(tracks)
        x = self.state['tracks'].index(track)
        gain = random.randint(-100, 100)
        self.write('5 %d %d\n' % (x, gain))
        track.gain = Gain.from_rational(gain, 100)

    def change_pan(self):
        # choose a random track and adjust pan
        tracks = list(filter(lambda t: t is not None, self.state['tracks']))
        if len(tracks) == 0:
            self.write('0\n')
            self.read(delim='\n', expect='Invalid choice\n')
            return
        track = random.choice(tracks)
        x = self.state['tracks'].index(track)
        pan = random.randint(-100, 100)
        self.write('6 %d %d\n' % (x, pan))
        track.pan = int(float(pan) / 100 * SAMPLE_MAX)

    def list_tracks(self):
        self.comment('List tracks')
        self.write('4\n')
        for x in xrange(len(self.state['tracks'])):
            track = self.state['tracks'][x]
            if track is None: continue
            self.read(delim='\n', expect='%d) %s samples=%d\n'%(x, 'mono' if len(track.channels) == 1 else 'stereo', track.samples()))

    def combine_split(self):
        # choose a random stereo track or choose two random mono tracks
        # XXX what happens if we send the same mono track twice? double-free? UAF?
        stereo_tracks = list(filter(lambda t: t is not None and len(t.channels) == 2, self.state['tracks']))
        mono_tracks = list(filter(lambda t: t is not None and len(t.channels) == 1, self.state['tracks']))
        if len(stereo_tracks) > 0 and (self.chance(0.5) or len(mono_tracks) <= 1):
            self.comment('Split')
            track = random.choice(stereo_tracks)
            x = self.state['tracks'].index(track)
            self.write('7 %d\n' % x)
            track2 = AudioTrack.fromMono(track.channels[1])
            del track.channels[1]
            self.state['tracks'].append(track2)
        elif len(mono_tracks) > 1:
            self.comment('Combine')
            tracks = random.sample(mono_tracks, 2)
            x0 = self.state['tracks'].index(tracks[0])
            x1 = self.state['tracks'].index(tracks[1])
            self.write('7 %d %d\n' % (x0, x1))
            tracks[0].channels.append(tracks[1].channels[0])
            tracks[0].fix_length()
            self.state['tracks'][x1] = None
        else:
            self.write('0\n')
            self.read(delim='\n', expect='Invalid choice\n')

    def new_menu(self):
        self.write('1\n')
        prompt = "1) Silence [number of samples]\n2) Sine Wave [number of samples] [HZ]\n3) Square Wave [number of samples] [HZ]\n4) White Noise [number of samples]\n5) Cancel\n"
        self.read(delim="Cancel\n", expect=prompt)

    def new_silence(self):
        self.comment('New silence')
        # create new mono audio track with random number of samples
        samples = random.randint(1000, 8000)
        self.write('1 %d\n' % samples)
        self.state['tracks'].append(AudioTrack.fromMono(AudioStream.fromSilence(samples)))

    def new_square(self):
        self.comment('New square wave')
        # create new mono audio track with random number of samples and random freq (200 - 3000)
        samples = random.randint(1000, 8000)
        hz = random.randint(200, 3000)
        self.write('3 %d %d\n' % (samples, hz))
        self.state['tracks'].append(AudioTrack.fromMono(AudioStream.fromSquareWave(samples, hz)))

    def add_entropy(self):
        buf = list([ord(x) ^ 0x55 for x in self.magic_page])
        for x in xrange(1, len(buf)):
            buf[x] = buf[x] ^ (buf[x-1] >> 1)
        for x in xrange(0, len(buf), 4):
            value = buf[x+0]
            value |= buf[x+1] << 8
            value |= buf[x+2] << 16
            value |= buf[x+3] << 24
            self.state['rng'] ^= self.state['rng'] >> 7
            self.state['rng'] ^= value & 0x77777777
            self.state['rng'] ^= self.state['rng'] << 17
            self.state['rng'] &= 0xFFFFFFFFFFFFFFFF

    def random_int32(self):
        result = (self.state['rng'] >> 6) & 0xFFFFFFFF
        self.state['rng'] ^= self.state['rng'] >> 7
        self.state['rng'] ^= self.state['rng'] << 17
        self.state['rng'] &= 0xFFFFFFFFFFFFFFFF
        return struct.unpack('<i', struct.pack('<I', result))[0]

    def from_noise(self, samples):
        self.add_entropy()
        data = []
        for x in xrange(samples):
            data.append(self.random_int32() >> 1)
        return AudioStream(data)

    def new_noise(self):
        self.comment('New noise')
        samples = random.randint(1000, 8000)
        self.write('4 %d\n' % samples)
        self.state['tracks'].append(AudioTrack.fromMono(self.from_noise(samples)))

    def export_menu(self):
        self.write('3\n')
        prompt = "1) Uncompressed 32-bit signed\n2) Compressed 4-bit\n3) Compressed 8-bit\n4) Cancel\n"
        self.read(delim="Cancel\n", expect=prompt)

    def export_4(self):
        self.comment('Export 4')
        self.write('2\n')
        data = self.export_audio().compress4()
        self.read(length=4, expect=struct.pack('<I', len(data)))
        self.read(length=len(data), expect=data)

    def export_8(self):
        self.comment('Export 8')
        self.write('3\n')
        data = self.export_audio().compress8()
        self.read(length=4, expect=struct.pack('<I', len(data)))
        self.read(length=len(data), expect=data)

    def export_32(self):
        self.comment('Export 32')
        self.write('1\n')
        data = self.export_audio().compress32()
        self.read(length=4, expect=struct.pack('<I', len(data)))
        self.read(length=len(data), expect=data)

    def effects_menu(self):
        self.write('8\n')
        prompt = "1) Apply gain [track] [hundredths]\n2) Apply pan [track] [hundredths]\n3) Echo [track] [delay in samples]\n4) Add silence [track] [number of samples]\n5) Cancel\n"
        self.read(delim="Cancel\n", expect=prompt)

    def effects_gain(self):
        tracks = list(filter(lambda t: t is not None, self.state['tracks']))
        if len(tracks) == 0:
            self.write('5\n')
            return
        self.comment('Gain FX')
        track = random.choice(tracks)
        x = self.state['tracks'].index(track)
        gain = random.randint(-100, 100)
        self.write('1 %d %d\n' % (x, gain))
        track.apply_gain(Gain.from_rational(gain, 100))

    def effects_pan(self):
        tracks = list(filter(lambda t: t is not None, self.state['tracks']))
        if len(tracks) == 0:
            self.write('5\n')
            return
        self.comment('Pan FX')
        track = random.choice(tracks)
        x = self.state['tracks'].index(track)
        pan = random.randint(-100, 100)
        self.write('2 %d %d\n' % (x, pan))
        track.apply_pan(int(float(pan) / 100 * SAMPLE_MAX))

    def effects_echo(self):
        tracks = list(filter(lambda t: t is not None, self.state['tracks']))
        if len(tracks) == 0:
            self.write('5\n')
            return
        self.comment('Echo FX')
        track = random.choice(tracks)
        x = self.state['tracks'].index(track)
        delay = random.randint(1, 8000)
        self.write('3 %d %d\n' % (x, delay))
        track.apply_echo(delay)
