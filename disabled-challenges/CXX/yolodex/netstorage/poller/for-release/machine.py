from cStringIO import StringIO
from generator.actions import Actions, Variable
import random
import string
import struct

def le32(x):
    return struct.pack('<I', x)

def le16(x):
    return struct.pack('<H', x)

def be32(x):
    return struct.pack('>I', x)

def be16(x):
    return struct.pack('>H', x)

def random_alphanum(max_size, min_size=2):
    alphanum = string.letters + string.digits
    max_size = random.randint(min_size, max_size)
    return ''.join(random.choice(alphanum) for c in range(max_size))

class RemoteStorage(Actions):
    def start(self):
        self.state['attached'] = False
        self.state['memory'] = StringIO()
        self.state['memory'].write('\x00' * 0x10000)

    def before_attach(self):
        pass

    def devlist(self):
        pkt = be16(0x0111)
        pkt += be16(0x8008)
        pkt += be32(0)

        self.write(pkt)

        pkt = be16(0x0111)
        pkt += be16(0x0008)
        pkt += be32(0)
        pkt += be32(1)
        self.read(length=0xC, expect=pkt)

        pkt = "/sys/devices/pci0000:00/0000:00:1d.1/usb1/1-1"
        pkt += '\x00' * (0x100 - len(pkt))
        self.read(length=0x100, expect=pkt)

        self.state['busid'] = Variable('busid')
        self.state['busid'].set_slice(0)
        self.read(length=0x20, assign=self.state['busid'])

        self.read(length=0x08)

        pkt = be32(3) + be16(0x6666) + be16(0xdead) + be16(0x100) + '\x00\x00\x00\x00\x01\x01'
        self.read(length=0x10, expect=pkt)
        self.read(length=4, expect='\x08\x06\x50\x00')

    def import_(self):
        if self.chance(0.9):
            self.devlist()
        busid = self.state.get('busid')
        if not busid:
            busid = random_alphanum(32)
            busid += '\x00' * (0x20 - len(busid))
        pkt = be16(0x0111)
        pkt += be16(0x8009)
        pkt += be32(0)
        self.write(pkt)
        self.write(busid)

        pkt = be16(0x0111)
        pkt += be16(0x0009)
        if 'busid' in self.state:
            pkt += be32(0)
            self.state['attached'] = True
            self.read(length=8, expect=pkt)
            pkt = "/sys/devices/pci0000:00/0000:00:1d.1/usb1/1-1"
            pkt += '\x00' * (0x100 - len(pkt))
            self.read(length=0x100, expect=pkt)
            self.read(length=0x20)
            self.read(length=0x08)
            pkt = be32(3) + be16(0x6666) + be16(0xdead) + be16(0x100) + '\x00\x00\x00\x00\x01\x01'
            self.read(length=0x10, expect=pkt)
        else:
            pkt += be32(1)
            self.read(length=8, expect=pkt)

    def after_attach(self):
        pass

    def submit_req(self, out, data, setup=None):
        seqnum = random.randint(0, 0xFFFFFFFF)
        devid = random.randint(0, 0xFFFFFFFF)
        ep = random.randint(1, 0xFFFFFFFF)
        if setup:
            ep = 0
            setup = (setup + '\x00' * 8)[:8]
        else:
            setup = '\x00' * 8

        pkt = be32(1)
        pkt += be32(seqnum)
        pkt += be32(devid)
        pkt += be32(0 if out else 1)
        pkt += be32(ep)
        pkt += be32(0) # flags
        pkt += be32(len(data))
        pkt += be32(0) # unused 
        pkt += be32(0) # unused 
        pkt += be32(0) # unused 
        pkt += setup
        if out:
            pkt += data
        self.write(pkt)

        pkt = be32(3)
        pkt += be32(seqnum)
        pkt += be32(devid)
        pkt += be32(0 if out else 1)
        pkt += be32(ep)
        pkt += be32(0) # flags
        pkt += be32(len(data))
        pkt += be32(0) # unused 
        pkt += be32(0) # unused 
        pkt += be32(0) # unused 
        pkt += '\x00' * 8
        self.read(length=len(pkt), expect=pkt)
        if not out and len(data) > 0:
            self.read(length=len(data), expect=data)

    def invalid_urb(self):
        pass

    def setup_get_device_desc(self):
        if not self.state['attached']:
            return
        self.submit_req(False, '\x12\x01\x00\x02\x00\x00\x00@ff\xad\xde\x00\x01\x00\x00\x00\x01', '\x80\x06\xFF\x01')

    def setup_get_config_desc(self):
        if not self.state['attached']:
            return
        self.submit_req(False, '\t\x02 \x00\x01\x01\x00\x802\t\x04\x00\x00\x02\x08\x06P\x00\x07\x05\x81\x02\x00\x02\x00\x07\x05\x02\x02\x00\x02\x00', '\x80\x06\xDE\x02')

    def setup_set_config(self):
        if not self.state['attached']:
            return
        self.submit_req(True, '', '\x00\x09\x01')

    def setup_get_max_lun(self):
        if not self.state['attached']:
            return
        self.submit_req(False, '\x01', '\xA1\xFE')

    def setup_reset(self):
        if not self.state['attached']:
            return
        self.submit_req(True, '', '\x21\xFF')

    def command(self, cb, out, data, error=False, residue=0):
        tag = random.randint(0, 0xFFFFFFFF)

        pkt = le32(0x43425355)
        pkt += le32(tag)
        pkt += le32(len(data))
        pkt += chr(0)
        pkt += chr(1)
        pkt += chr(len(cb))
        cb += '\x00' * (16 - len(cb))
        pkt += cb
        self.submit_req(True, pkt)

        if data is not None:
            if out:
                if len(data) > 512:
                    split = random.randint(0, len(data) - 10)
                    if split > 0:
                        self.submit_req(True, data[0:split])
                    self.submit_req(True, data[split:])
                else:
                    self.submit_req(True, data)
            else:
                self.submit_req(False, data)

        pkt = le32(0x53425355)
        pkt += le32(tag)
        pkt += le32(residue)
        pkt += chr(1 if error else 0)
        self.submit_req(False, pkt)

    def cmd_read_capacity(self):
        if not self.state['attached']:
            return
        self.command('\x25', False, '\x00\x00\x00\x7F\x00\x00\x02\x00')

    def cmd_inquiry(self):
        if not self.state['attached']:
            return
        data = '\x0e\x00\x04\x02\x20\x00\x00\x00' + '\x00'*28
        length = random.randint(0, len(data)) 
        data = data[:length]
        self.command('\x12\x00\x00\x00' + chr(length), False, data)

    def cmd_read(self):
        if not self.state['attached']:
            return
        if True: #self.chance(0.9):
            lba = random.randint(0, (0x10000 / 512) - 1)
            length = min(0x10000 - lba * 512, 0x1000)
            length = random.randint(1, length / 512)
            self.state['memory'].seek(lba * 512)
            data = self.state['memory'].read(length * 512)
            self.command('\x28\x00' + be32(lba) + '\x00' + be16(length), False, data)
        elif self.chance(0.5):
            lba = random.randint((0x10000 / 512), 0xFFFFFFFF)
            length = random.randint(0, 0xFFFF)
            self.command('\x28\x00' + be32(lba) + '\x00' + be16(length), False, None, error=True)
        else:
            lba = random.randint(0, (0x10000 / 512) - 1)
            length = (0x10000 - lba * 512) / 512
            self.state['memory'].seek(lba * 512)
            data = self.state['memory'].read(length * 512)

            length += random.randint(1, 1000)
            self.command('\x28\x00' + be32(lba) + '\x00' + be16(length), False, None, error=True)

    def cmd_write(self):
        if not self.state['attached']:
            return
        lba = random.randint(0, (0x10000 / 512) - 1)
        length = min(0x10000 - lba * 512, 0x1000)
        length = random.randint(512, length) / 512
        data = ''.join(chr(random.randint(0,255)) for c in xrange(length * 512))
        self.state['memory'].seek(lba * 512)
        self.state['memory'].write(data)
        self.command('\x2A\x00' + be32(lba) + '\x00' + be16(length), True, data)

    def cmd_mode_sense(self):
        if not self.state['attached']:
            return
        data = '\x00\x10\x00\x00\x00\x00\x00\x00\x86\x08\x01\x02\x00\x00\x00\x00\x00\x80'
        self.command('\x5A\x00\x3F', False, data)

    def invalid_cmd(self):
        pass

    def quit(self):
        pass
