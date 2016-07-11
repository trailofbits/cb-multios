#!/usr/bin/env python

from generator.actions import Actions
import random
import string
from struct import pack


class StringSearch(Actions):


    def start(self):


        self.tag_db = [ (0x100, 'ImageWidth'), (0x101, 'ImageLength'), (0x102, 'BitsPerSample'), (0x103, 'Compression'),
                    (0x106, 'PhotometricInterpretation'), (0x112, 'Orientation'), (0x115, 'SamplesPerPixel'), 
                    (0x11c, 'PlanarConfiguration'), (0x212, 'YCbCrSubSampling'), (0x213, 'YCbCrPositioning'),
                    (0x11a, 'XResolution'), (0x11b, 'YResolution'), (0x128, 'ResolutionUnit'), (0x111, 'StripOffsets'),
                    (0x116, 'RowsPerStrip'), (0x117, 'StripByteCounts'), (0x201, 'InterchangeFormat'),
                    (0x202, 'InterchangeFormatLength'), (0x12d, 'TransferFunction'), (0x13e, 'WhitePoint'), 
                    (0x13f, 'PrimaryChromaticities'), (0x211, 'YCbCrCoefficients'), (0x214, 'ReferenceBlackWhite'),
                    (0x132, 'DateTime'), (0x10e, 'ImageDescription'), (0x10f, 'Make'), (0x110, 'Model'),
                    (0x131, 'Software'), (0x13b, 'Artist'), (0x8298, 'Copyright') ]


        self.ifd_tag_db = [ (0x9000, 'ExifVersion'), (0xa000, 'FlashpixVersion'), (0xa001, 'ColorSpace'), (0x9101, 'ComponentsConfiguration'),
                    (0x9102, 'CompressedBitsPerPixel'), (0xa002, 'PixelXDimension'), (0xa003, 'PixelYDimension'), 
                    (0x927c, 'MakeNote'), (0x9286, 'UserComment'), (0xa004, 'RelatedSoundFile'), (0x9003, 'DateTimeOriginal'),
                    (0x9004, 'DateTimeDigitized'), (0x9290, 'SubSecTime'), (0x9291, 'SubSecTimeOriginal'), (0x9292, 'SubSecTimeDigitized'),
                    (0xa420, 'ImageUniqueID') ]

        self.gps_tag_db = [ "GPSVersionID", "GPSLatyitudeRef", "GPSLatitude", "GPSLongitudeRef", "GPSLongitude", "GPSAltitudeRef", 
                "GPSAltitude", "GPSTimeStamp", "GPSSatellites", "GPSStatus", "GPSMeasureMode", "GPSDOP", "GPSSpeedRef", "GPSSpeed", 
                "GPSTrackRef", "GPSTrack", "GPSImgDirectionRef", "GPSImgDirection", "GPSMapDatum", "GPSDestLatitudeRef", "GPSDestLatitude", 
                "GPSDestLongitudeRef", "GPSDestLongitude", "GPSDestBearingRef", "GPSDestBearing", "GPSDestDistanceRef", "GPSDestDistance", 
                "GPSProcessingMethod", "GPSAreaInformation", "GPSDateStamp", "GPSDifferential" ]


        self.tag_types_db = [(1, 'BYTE'), (2, 'ASCII'), (3, 'SHORT'), (4, 'LONG'), (5, 'RATIONAL'), (7,'UNDEFINED'), (9, 'SLONG'), (10, 'SRATIONAL')]
        self.tag_types = [1, 2, 3, 4, 5, 7, 9, 10]

    def SOM(self):

        som=pack('H',0xffF8)
        self.write(som)

        self.read(delim='\n', expect = 'SOM marker found\n')

    def exit(self):

        pass

    def random1(self):

        data = pack('H', random.randint(400, 1000))
        self.write(data)

        self.read(delim='\n', expect = 'Did not find SOM marker\n')


    def random2(self):

        data = pack('H', random.randint(400, 1000))
        self.write(data)

    def SAP0(self):

        data = pack('H', 0xfff0)
        self.write(data)

        self.read(delim='\n', expect = 'SAP0 marker found\n')

        self.write(pack('H', 0x10))
        self.write('SAP0')
        self.write(pack('5H', 0,0,0,0,0))

    def build_SAP1(self):

        length = 0
        sap_values = pack('0c')
        sap_values_len = 0
        value = 0

        sap_hdr = pack('4sH', 'SAP1', 0)
        sap1_hdr_len = len(sap_hdr)

        num_ifds = random.randint(3,10)

        ifd_length = 2 + (12 * num_ifds)
        tff0_length = 8

        length = sap1_hdr_len + tff0_length + ifd_length

        sap1 = sap_hdr

        sap1 = sap1 + pack('2HL', 0x4949, 0x2a, 8)

        sap1 = sap1 + pack('H', num_ifds)

        # values_offset will be used to index to data pointed to from IFDs
        values_offset = tff0_length + ifd_length

        # build a list of expect strings to parse once this SAP1 is transmitted
        expect_strings = []

        expect_strings.append('Intel formatted integers\n')
        expect_strings.append('TagMark = 2A\n')
        expect_strings.append('Offset = 8\n')
        expect_strings.append('# of compatility arrays: {}\n'.format(num_ifds))

        for x in range (0, num_ifds-2):

            value = 0
            num_tags = len(self.tag_db)
            rand_tag = random.randint(0, num_tags-1)
            tag = self.tag_db[rand_tag][0]
            count  = x
            num_tag_types = len(self.tag_types_db)
            rand_tag_type = random.randint(0, num_tag_types-1)


            tag_type = self.tag_types_db[rand_tag_type][0]

            if tag_type == 2:

                temp_str = pack('20s', ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(random.randint(5,19))))

                count = len(temp_str)

                sap_values = sap_values + temp_str
                value = values_offset
                values_offset = values_offset + 20
                sap_values_len = sap_values_len + 20

            sap1 = sap1 + pack('2H2L', tag, tag_type, count, value)

            expect_strings.append('Tag: {:X} ({})\n'.format(tag, self.tag_db[rand_tag][1]))
            expect_strings.append('Type: {:X} ({})\n'.format(tag_type, self.tag_types_db[rand_tag_type][1]))
            expect_strings.append('Count: {}\n'.format(count))
          
            if tag_type == 2:

                expect_string = 'Value: ' + temp_str.split('\0')[0] + '\n'
                expect_strings.append(expect_string)

            else:
                expect_strings.append('Value: {}\n'.format(value))

        tag = 0x8769
        tag_type = 7
        value = values_offset

        sap1 = sap1 + pack('2H2L', tag, tag_type, num_ifds-2, value)

        expect_strings.append('Tag: {:X} ({})\n'.format(tag, 'EXIF IFD Pointer'))
        expect_strings.append('Type: {:X} ({})\n'.format(tag_type, self.tag_types_db[5][1]))
        expect_strings.append('Count: {}\n'.format(num_ifds-2))
        expect_strings.append('Value: {}\n'.format(value))

        ifd_data, ifd_expect_list = self.build_IFD()

        sap_values_len = sap_values_len + len(ifd_data)

        sap_values = sap_values + ifd_data

        expect_strings = expect_strings + ifd_expect_list

        values_offset = values_offset + len(ifd_data)

        # now add a GPS IFD 
        tag = 0x8825
        tag_type = 7
        value = values_offset

        sap1 = sap1 + pack('2H2L', tag, tag_type, num_ifds-1, value)

        expect_strings.append('Tag: {:X} ({})\n'.format(tag, 'GPS Info'))
        expect_strings.append('Type: {:X} ({})\n'.format(tag_type, self.tag_types_db[5][1]))
        expect_strings.append('Count: {}\n'.format(num_ifds-1))
        expect_strings.append('Value: {}\n'.format(value))


        gps_data, gps_expect_list = self.build_GPS()

        sap_values_len = sap_values_len + len(gps_data)

        sap_values = sap_values + gps_data

        expect_strings = expect_strings + gps_expect_list

        expect_strings.append('Finished processing\n')

        length = length + sap_values_len
        sap1 = sap1 + sap_values

        # this is the first expect string, but since we didn't know the final length until the end...
        # so insert it at the beginning
        expect_strings.insert(0,'sizeof section is {}\n'.format(length))
        sap1 = pack('H', length) + sap1

        return sap1, expect_strings

    def build_GPS(self):

        length = 0
        sap_values = pack('0c')
        sap_values_len = 0
        value = 0

        num_ifds = random.randint(1,10)

        ifd_length = 2 + (12 * num_ifds)

        length =  ifd_length

        sap1 = pack('H', num_ifds)

        # values_offset will be used to index to data pointed to from IFDs
        values_offset = ifd_length

        # build a list of expect strings to parse once this SAP1 is transmitted
        expect_strings = []

        expect_strings.append('# of arrays: {}\n'.format(num_ifds))

        for x in range (0, num_ifds):

            value = 0
            num_tags = len(self.gps_tag_db) 
            rand_tag = random.randint(0, num_tags-1)
            tag = rand_tag

            num_tag_types = len(self.tag_types_db)
            rand_tag_type = random.randint(0, num_tag_types-1)


            tag_type = self.tag_types_db[rand_tag_type][0]

            value = x*2

            sap1 = sap1 + pack('2H2L', tag, tag_type, x, value)

            expect_strings.append('Tag: {:X} ({})\n'.format(tag, self.gps_tag_db[rand_tag]))
            expect_strings.append('Type: {:X} ({})\n'.format(tag_type, self.tag_types_db[rand_tag_type][1]))
            expect_strings.append('Count: {}\n'.format(x))
            expect_strings.append('Value: {}\n'.format(value))


        return sap1, expect_strings

    def build_IFD(self):

        length = 0
        sap_values = pack('0c')
        sap_values_len = 0
        value = 0

        num_ifds = random.randint(1,10)

        ifd_length = 2 + (12 * num_ifds)

        length =  ifd_length

        sap1 = pack('H', num_ifds)

        # values_offset will be used to index to data pointed to from IFDs
        values_offset = ifd_length

        # build a list of expect strings to parse once this SAP1 is transmitted
        expect_strings = []

        expect_strings.append('# of arrays: {}\n'.format(num_ifds))

        for x in range (0, num_ifds):

            value = 0
            num_tags = len(self.ifd_tag_db) 
            rand_tag = random.randint(0, num_tags-1)
            tag = self.ifd_tag_db[rand_tag][0]

            num_tag_types = len(self.tag_types_db)
            rand_tag_type = random.randint(0, num_tag_types-1)


            tag_type = self.tag_types_db[rand_tag_type][0]

            value = x*2

            if tag_type == 2:

                temp_str = pack('20s', ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(random.randint(5,19))))

                sap_values = sap_values + temp_str
                value = values_offset
                values_offset = values_offset + 20
                sap_values_len = sap_values_len + 20
                length = length + 20

            sap1 = sap1 + pack('2H2L', tag, tag_type, x, value)

            expect_strings.append('Tag: {:X} ({})\n'.format(tag, self.ifd_tag_db[rand_tag][1]))
            expect_strings.append('Type: {:X} ({})\n'.format(tag_type, self.tag_types_db[rand_tag_type][1]))
            expect_strings.append('Count: {}\n'.format(x))
          
            if tag_type == 2:

                expect_string = 'Value: ' + temp_str.split('\0')[0] + '\n'
                expect_strings.append(expect_string)

            else:
                expect_strings.append('Value: {}\n'.format(value))


        sap1 = sap1 + sap_values
        
        return sap1, expect_strings

    def SAP1(self):

        data = pack('H', 0xfff1)
        self.write(data)

        self.read(delim='\n', expect='SAP1 marker found\n')

        sap1_data, expect_list = self.build_SAP1()

        self.write(sap1_data)

        for expect_string in expect_list:

            self.read(length=len(expect_string), expect=expect_string)


    def TFF1(self):

        pass







