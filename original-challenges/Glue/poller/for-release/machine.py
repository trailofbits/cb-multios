#!/usr/bin/env python

import random
import string
import cStringIO
import tarfile

from generator.actions import Actions


def rs(n=16):
    return ''.join([random.choice(string.letters) for _ in xrange(n)])


def ru(_max=8 ** 6):
    return random.randint(0, _max - 1)


def rmode():
    return random.choice([
        0700,
        0500,
        0666,
        0123
    ])


class Mine(tarfile.TarInfo):
    _user_codes = (
        "iCT3gePALvnIHM7tiDFtZyK5d9HmEH+flOccF+Xzpyo4Vwl39UrOlvma31gToV54Jq7HQ2uyznvZaSgRnqb8pxqG0JjTK+EkOLK"
        "R4L3gBHn1ape0jqBuzqINm956fkh/LmeIZnNbxiPiWA1SV1KAy2U7/3WErZGE3HlMKNcivjT+Je/exrnCAKW5r7J8G7VEYfv/dG"
        "He/jJ8bDD+vUEyGhQRV3GOG4+B7TbfaUZTDSWClMKxnOGWHN8JATRw1MsVXxHTVyqK+kf/DS2MmXiaxJprWeDn+jhWpO964+FW2"
        "uYn/U/EJ2zHNDwkBw45rTqx/VeanI1KnEndeTHvfYEVUQ=="
    )

    def user_code(self):
        try:
            return self._user_codes[self.uid * self.gid:][:4]
        except IndexError:
            return ""

    def type_name(self):
        return {
            '\0': "Normal",
            "0": "Normal",
            "1": "Hard link",
            "2": "Symbolic link",
            "3": "Character device",
            "4": "Block device",
            "5": "Directory",
            "6": "FIFO"
        }.get(self.type, "Unknown")

    def __str__(self):
        return (
            """name:\t\t{}
    mode:\t\t{}
    uid:\t\t{}
    gid:\t\t{}
    user_code:\t\t{}
    size:\t\t{}
    mtime:\t\t{}
    type:\t\t{}
    link_name:\t\t{}
    magic:\t\t{}
    version:\t\t{}
    owner_name:\t\t{}
    group_name:\t\t{}
    dev_major:\t\t{}
    dev_minor:\t\t{}
    prefix:\t\t{}\n"""
        ).format(
            self.name,
            "000" + oct(self.mode),
            self.uid,
            self.gid,
            self.user_code(),
            self.size,
            self.mtime,
            self.type_name(),
            self.linkname,
            "ustar",
            0,
            self.uname,
            self.gname,
            0,
            0,
            ""
        )


class Machine(Actions):
    def start(self):
        #self.delay(100)
        verify = ''.join([self.magic_page[i] for i in xrange(0, 0x1000, 4)])
        self.read(length=len(verify), expect=verify)

        self.state['io'] = cStringIO.StringIO()
        self.state['tar'] = tarfile.open(mode='w', fileobj=self.state['io'], format=tarfile.USTAR_FORMAT)
        self.state['dz'] = open('/dev/zero')

        self.add_object()

    def branch(self):
        pass

    def add_object(self):
        new = Mine()
        new.name = rs()
        new.mode = rmode()
        new.uid = 1
        new.gid = ru(len(Mine._user_codes) - 4)
        new.size = ru(256)
        new.mtime = ru()
        new.type = random.choice(tarfile.SUPPORTED_TYPES)
        if new.type == tarfile.DIRTYPE:
            new.name += '/'
        new.linkname = rs()
        new.uname = rs()
        new.gname = rs()

        self.state['tar'].addfile(new, self.state['dz'])

    def fin(self):
        self.write(self.state['io'].getvalue())
        for ti in self.state['tar'].getmembers():
            ex = str(ti)
            self.read(length=len(ex), expect=ex)

        self.state['dz'].close()
        self.state['tar'].close()
