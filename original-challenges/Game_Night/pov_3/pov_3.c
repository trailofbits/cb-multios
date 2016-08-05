/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "conv.h"
#include <libpov.h>
int main(void) {
    negotiate_type1(0x00ffffff, 0x00ffffff, 0);
    //*** delay
    delay(100);
    do {
        unsigned char *read_00000;
        unsigned int read_00000_len;
        unsigned int read_00000_ptr = 0;
        //**** delimited read
        static unsigned char read_00000_delim[] = 
            "\x0a";
        read_00000 = NULL;
        read_00000_len = 0;
        int read_00000_res = delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
        if (read_00000_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00000_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00000_ptr += data_match(read_00000 + read_00000_ptr, read_00000_len - read_00000_ptr, match_00000_00000, 22);
        free(read_00000);
        if (read_00000_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00001;
        unsigned int read_00001_len;
        unsigned int read_00001_ptr = 0;
        //**** delimited read
        static unsigned char read_00001_delim[] = 
            "\x0a";
        read_00001 = NULL;
        read_00001_len = 0;
        int read_00001_res = delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
        if (read_00001_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00001_00000[] = 
            "\x0a";
        read_00001_ptr += data_match(read_00001 + read_00001_ptr, read_00001_len - read_00001_ptr, match_00001_00000, 1);
        free(read_00001);
        if (read_00001_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00002;
        unsigned int read_00002_len;
        unsigned int read_00002_ptr = 0;
        //**** delimited read
        static unsigned char read_00002_delim[] = 
            "\x0a";
        read_00002 = NULL;
        read_00002_len = 0;
        int read_00002_res = delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 1);
        if (read_00002_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00002_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00002_ptr += data_match(read_00002 + read_00002_ptr, read_00002_len - read_00002_ptr, match_00002_00000, 11);
        free(read_00002);
        if (read_00002_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00003;
        unsigned int read_00003_len;
        unsigned int read_00003_ptr = 0;
        //**** delimited read
        static unsigned char read_00003_delim[] = 
            "\x0a";
        read_00003 = NULL;
        read_00003_len = 0;
        int read_00003_res = delimited_read(0, &read_00003, &read_00003_len, read_00003_delim, 1);
        if (read_00003_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00003_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00003_ptr += data_match(read_00003 + read_00003_ptr, read_00003_len - read_00003_ptr, match_00003_00000, 9);
        free(read_00003);
        if (read_00003_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00004;
        unsigned int read_00004_len;
        unsigned int read_00004_ptr = 0;
        //**** delimited read
        static unsigned char read_00004_delim[] = 
            "\x0a";
        read_00004 = NULL;
        read_00004_len = 0;
        int read_00004_res = delimited_read(0, &read_00004, &read_00004_len, read_00004_delim, 1);
        if (read_00004_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00004_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00004_ptr += data_match(read_00004 + read_00004_ptr, read_00004_len - read_00004_ptr, match_00004_00000, 10);
        free(read_00004);
        if (read_00004_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00005;
        unsigned int read_00005_len;
        unsigned int read_00005_ptr = 0;
        //**** delimited read
        static unsigned char read_00005_delim[] = 
            "\x0a";
        read_00005 = NULL;
        read_00005_len = 0;
        int read_00005_res = delimited_read(0, &read_00005, &read_00005_len, read_00005_delim, 1);
        if (read_00005_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00005_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00005_ptr += data_match(read_00005 + read_00005_ptr, read_00005_len - read_00005_ptr, match_00005_00000, 20);
        free(read_00005);
        if (read_00005_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00006;
        unsigned int read_00006_len;
        unsigned int read_00006_ptr = 0;
        //**** delimited read
        static unsigned char read_00006_delim[] = 
            "\x0a";
        read_00006 = NULL;
        read_00006_len = 0;
        int read_00006_res = delimited_read(0, &read_00006, &read_00006_len, read_00006_delim, 1);
        if (read_00006_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00006_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00006_ptr += data_match(read_00006 + read_00006_ptr, read_00006_len - read_00006_ptr, match_00006_00000, 15);
        free(read_00006);
        if (read_00006_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00007;
        unsigned int read_00007_len;
        unsigned int read_00007_ptr = 0;
        //**** delimited read
        static unsigned char read_00007_delim[] = 
            "\x0a";
        read_00007 = NULL;
        read_00007_len = 0;
        int read_00007_res = delimited_read(0, &read_00007, &read_00007_len, read_00007_delim, 1);
        if (read_00007_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00007_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00007_ptr += data_match(read_00007 + read_00007_ptr, read_00007_len - read_00007_ptr, match_00007_00000, 20);
        free(read_00007);
        if (read_00007_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00008;
        unsigned int read_00008_len;
        unsigned int read_00008_ptr = 0;
        //**** delimited read
        static unsigned char read_00008_delim[] = 
            "\x0a";
        read_00008 = NULL;
        read_00008_len = 0;
        int read_00008_res = delimited_read(0, &read_00008, &read_00008_len, read_00008_delim, 1);
        if (read_00008_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00008_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00008_ptr += data_match(read_00008 + read_00008_ptr, read_00008_len - read_00008_ptr, match_00008_00000, 28);
        free(read_00008);
        if (read_00008_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00009;
        unsigned int read_00009_len;
        unsigned int read_00009_ptr = 0;
        //**** delimited read
        static unsigned char read_00009_delim[] = 
            "\x0a";
        read_00009 = NULL;
        read_00009_len = 0;
        int read_00009_res = delimited_read(0, &read_00009, &read_00009_len, read_00009_delim, 1);
        if (read_00009_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00009_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00009_ptr += data_match(read_00009 + read_00009_ptr, read_00009_len - read_00009_ptr, match_00009_00000, 8);
        free(read_00009);
        if (read_00009_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00010;
        unsigned int read_00010_len;
        unsigned int read_00010_ptr = 0;
        //**** delimited read
        static unsigned char read_00010_delim[] = 
            "\x0a";
        read_00010 = NULL;
        read_00010_len = 0;
        int read_00010_res = delimited_read(0, &read_00010, &read_00010_len, read_00010_delim, 1);
        if (read_00010_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00010_00000[] = 
            "\x0a";
        read_00010_ptr += data_match(read_00010 + read_00010_ptr, read_00010_len - read_00010_ptr, match_00010_00000, 1);
        free(read_00010);
        if (read_00010_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00000_00000[] = 
            "\x32\x0a";
        static unsigned int write_00000_00000_len = 2;
        unsigned char *write_00000 = NULL;
        unsigned int write_00000_len = 0;
        write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
        if (write_00000_len > 0) {
            transmit_all(1, write_00000, write_00000_len);
        }
        free(write_00000);
    } while (0);
    do {
        unsigned char *read_00011;
        unsigned int read_00011_len;
        unsigned int read_00011_ptr = 0;
        //**** delimited read
        static unsigned char read_00011_delim[] = 
            "\x0a";
        read_00011 = NULL;
        read_00011_len = 0;
        int read_00011_res = delimited_read(0, &read_00011, &read_00011_len, read_00011_delim, 1);
        if (read_00011_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00011_00000[] = 
            "\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x63\x68\x65\x73\x73"
            "\x6d\x61\x73\x74\x65\x72\x20\x30\x78\x38\x30\x30\x30\x2c\x20\x65"
            "\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x62\x6f\x61\x72\x64\x3a"
            "\x0a";
        read_00011_ptr += data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 49);
        free(read_00011);
        if (read_00011_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00001_00000[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x70"
            "\x20\x20\x20\x20\x20\x20\x20\x0a";
        static unsigned int write_00001_00000_len = 72;
        unsigned char *write_00001 = NULL;
        unsigned int write_00001_len = 0;
        write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
        if (write_00001_len > 0) {
            transmit_all(1, write_00001, write_00001_len);
        }
        free(write_00001);
    } while (0);
    do {
        unsigned char *read_00012;
        unsigned int read_00012_len;
        unsigned int read_00012_ptr = 0;
        //**** length read
        read_00012_len = 20;
        read_00012 = (unsigned char*)malloc(read_00012_len);
        int read_00012_res = length_read(0, read_00012, read_00012_len);
        if (read_00012_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00012_00000[] = 
            "\x4d\x75\x61\x68\x68\x61\x68\x61\x2c\x20\x49\x20\x6d\x6f\x76\x65"
            "\x20\x74\x6f\x20";
        read_00012_ptr += data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 20);
        free(read_00012);
        if (read_00012_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00013;
        unsigned int read_00013_len;
        unsigned int read_00013_ptr = 0;
        //**** length read
        read_00013_len = 4;
        read_00013 = (unsigned char*)malloc(read_00013_len);
        int read_00013_res = length_read(0, read_00013, read_00013_len);
        if (read_00013_res) {} //silence unused variable warning
        //**** read assign to var "cookie" from slice
        assign_from_slice("cookie", read_00013, read_00013_len - read_00013_ptr, 0, 0, 1);
        free(read_00013);
        if (read_00013_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00014;
        unsigned int read_00014_len;
        unsigned int read_00014_ptr = 0;
        //**** delimited read
        static unsigned char read_00014_delim[] = 
            "\x0a";
        read_00014 = NULL;
        read_00014_len = 0;
        int read_00014_res = delimited_read(0, &read_00014, &read_00014_len, read_00014_delim, 1);
        if (read_00014_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00014_00000[] = 
            "\x0a";
        read_00014_ptr += data_match(read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, match_00014_00000, 1);
        free(read_00014);
        if (read_00014_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00015;
        unsigned int read_00015_len;
        unsigned int read_00015_ptr = 0;
        //**** delimited read
        static unsigned char read_00015_delim[] = 
            "\x0a";
        read_00015 = NULL;
        read_00015_len = 0;
        int read_00015_res = delimited_read(0, &read_00015, &read_00015_len, read_00015_delim, 1);
        if (read_00015_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00015_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00015_ptr += data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 22);
        free(read_00015);
        if (read_00015_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00016;
        unsigned int read_00016_len;
        unsigned int read_00016_ptr = 0;
        //**** delimited read
        static unsigned char read_00016_delim[] = 
            "\x0a";
        read_00016 = NULL;
        read_00016_len = 0;
        int read_00016_res = delimited_read(0, &read_00016, &read_00016_len, read_00016_delim, 1);
        if (read_00016_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00016_00000[] = 
            "\x0a";
        read_00016_ptr += data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 1);
        free(read_00016);
        if (read_00016_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00017;
        unsigned int read_00017_len;
        unsigned int read_00017_ptr = 0;
        //**** delimited read
        static unsigned char read_00017_delim[] = 
            "\x0a";
        read_00017 = NULL;
        read_00017_len = 0;
        int read_00017_res = delimited_read(0, &read_00017, &read_00017_len, read_00017_delim, 1);
        if (read_00017_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00017_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00017_ptr += data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 11);
        free(read_00017);
        if (read_00017_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00018;
        unsigned int read_00018_len;
        unsigned int read_00018_ptr = 0;
        //**** delimited read
        static unsigned char read_00018_delim[] = 
            "\x0a";
        read_00018 = NULL;
        read_00018_len = 0;
        int read_00018_res = delimited_read(0, &read_00018, &read_00018_len, read_00018_delim, 1);
        if (read_00018_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00018_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00018_ptr += data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 9);
        free(read_00018);
        if (read_00018_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00019;
        unsigned int read_00019_len;
        unsigned int read_00019_ptr = 0;
        //**** delimited read
        static unsigned char read_00019_delim[] = 
            "\x0a";
        read_00019 = NULL;
        read_00019_len = 0;
        int read_00019_res = delimited_read(0, &read_00019, &read_00019_len, read_00019_delim, 1);
        if (read_00019_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00019_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00019_ptr += data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 10);
        free(read_00019);
        if (read_00019_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00020;
        unsigned int read_00020_len;
        unsigned int read_00020_ptr = 0;
        //**** delimited read
        static unsigned char read_00020_delim[] = 
            "\x0a";
        read_00020 = NULL;
        read_00020_len = 0;
        int read_00020_res = delimited_read(0, &read_00020, &read_00020_len, read_00020_delim, 1);
        if (read_00020_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00020_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00020_ptr += data_match(read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, match_00020_00000, 20);
        free(read_00020);
        if (read_00020_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00021;
        unsigned int read_00021_len;
        unsigned int read_00021_ptr = 0;
        //**** delimited read
        static unsigned char read_00021_delim[] = 
            "\x0a";
        read_00021 = NULL;
        read_00021_len = 0;
        int read_00021_res = delimited_read(0, &read_00021, &read_00021_len, read_00021_delim, 1);
        if (read_00021_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00021_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00021_ptr += data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 15);
        free(read_00021);
        if (read_00021_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00022;
        unsigned int read_00022_len;
        unsigned int read_00022_ptr = 0;
        //**** delimited read
        static unsigned char read_00022_delim[] = 
            "\x0a";
        read_00022 = NULL;
        read_00022_len = 0;
        int read_00022_res = delimited_read(0, &read_00022, &read_00022_len, read_00022_delim, 1);
        if (read_00022_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00022_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00022_ptr += data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 20);
        free(read_00022);
        if (read_00022_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00023;
        unsigned int read_00023_len;
        unsigned int read_00023_ptr = 0;
        //**** delimited read
        static unsigned char read_00023_delim[] = 
            "\x0a";
        read_00023 = NULL;
        read_00023_len = 0;
        int read_00023_res = delimited_read(0, &read_00023, &read_00023_len, read_00023_delim, 1);
        if (read_00023_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00023_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00023_ptr += data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 28);
        free(read_00023);
        if (read_00023_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00024;
        unsigned int read_00024_len;
        unsigned int read_00024_ptr = 0;
        //**** delimited read
        static unsigned char read_00024_delim[] = 
            "\x0a";
        read_00024 = NULL;
        read_00024_len = 0;
        int read_00024_res = delimited_read(0, &read_00024, &read_00024_len, read_00024_delim, 1);
        if (read_00024_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00024_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00024_ptr += data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 8);
        free(read_00024);
        if (read_00024_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00025;
        unsigned int read_00025_len;
        unsigned int read_00025_ptr = 0;
        //**** delimited read
        static unsigned char read_00025_delim[] = 
            "\x0a";
        read_00025 = NULL;
        read_00025_len = 0;
        int read_00025_res = delimited_read(0, &read_00025, &read_00025_len, read_00025_delim, 1);
        if (read_00025_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00025_00000[] = 
            "\x0a";
        read_00025_ptr += data_match(read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, match_00025_00000, 1);
        free(read_00025);
        if (read_00025_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00002_00000[] = 
            "\x33\x0a";
        static unsigned int write_00002_00000_len = 2;
        unsigned char *write_00002 = NULL;
        unsigned int write_00002_len = 0;
        write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
        if (write_00002_len > 0) {
            transmit_all(1, write_00002, write_00002_len);
        }
        free(write_00002);
    } while (0);
    do {
        unsigned char *read_00026;
        unsigned int read_00026_len;
        unsigned int read_00026_ptr = 0;
        //**** delimited read
        static unsigned char read_00026_delim[] = 
            "\x0a";
        read_00026 = NULL;
        read_00026_len = 0;
        int read_00026_res = delimited_read(0, &read_00026, &read_00026_len, read_00026_delim, 1);
        if (read_00026_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00026_00000[] = 
            "\x4c\x65\x74\x20\x6d\x65\x20\x68\x65\x6c\x70\x20\x79\x6f\x75\x20"
            "\x63\x68\x65\x61\x74\x20\x61\x74\x20\x73\x75\x64\x6f\x6b\x75\x2c"
            "\x20\x65\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x62\x6f\x61\x72"
            "\x64\x20\x6e\x30\x30\x62\x3a\x0a";
        read_00026_ptr += data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 56);
        free(read_00026);
        if (read_00026_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00003_00000[] = 
            "\x31\x31\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static unsigned int write_00003_00000_len = 90;
        unsigned char *write_00003 = NULL;
        unsigned int write_00003_len = 0;
        write_00003 = append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
        if (write_00003_len > 0) {
            transmit_all(1, write_00003, write_00003_len);
        }
        free(write_00003);
    } while (0);
    do {
        unsigned char *read_00027;
        unsigned int read_00027_len;
        unsigned int read_00027_ptr = 0;
        //**** delimited read
        static unsigned char read_00027_delim[] = 
            "\x0a";
        read_00027 = NULL;
        read_00027_len = 0;
        int read_00027_res = delimited_read(0, &read_00027, &read_00027_len, read_00027_delim, 1);
        if (read_00027_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00027_00000[] = 
            "\x4e\x69\x63\x65\x20\x74\x72\x79\x0a";
        read_00027_ptr += data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 9);
        free(read_00027);
        if (read_00027_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00028;
        unsigned int read_00028_len;
        unsigned int read_00028_ptr = 0;
        //**** delimited read
        static unsigned char read_00028_delim[] = 
            "\x0a";
        read_00028 = NULL;
        read_00028_len = 0;
        int read_00028_res = delimited_read(0, &read_00028, &read_00028_len, read_00028_delim, 1);
        if (read_00028_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00028_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00028_ptr += data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 22);
        free(read_00028);
        if (read_00028_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00029;
        unsigned int read_00029_len;
        unsigned int read_00029_ptr = 0;
        //**** delimited read
        static unsigned char read_00029_delim[] = 
            "\x0a";
        read_00029 = NULL;
        read_00029_len = 0;
        int read_00029_res = delimited_read(0, &read_00029, &read_00029_len, read_00029_delim, 1);
        if (read_00029_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00029_00000[] = 
            "\x0a";
        read_00029_ptr += data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 1);
        free(read_00029);
        if (read_00029_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00030;
        unsigned int read_00030_len;
        unsigned int read_00030_ptr = 0;
        //**** delimited read
        static unsigned char read_00030_delim[] = 
            "\x0a";
        read_00030 = NULL;
        read_00030_len = 0;
        int read_00030_res = delimited_read(0, &read_00030, &read_00030_len, read_00030_delim, 1);
        if (read_00030_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00030_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00030_ptr += data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 11);
        free(read_00030);
        if (read_00030_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00031;
        unsigned int read_00031_len;
        unsigned int read_00031_ptr = 0;
        //**** delimited read
        static unsigned char read_00031_delim[] = 
            "\x0a";
        read_00031 = NULL;
        read_00031_len = 0;
        int read_00031_res = delimited_read(0, &read_00031, &read_00031_len, read_00031_delim, 1);
        if (read_00031_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00031_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00031_ptr += data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 9);
        free(read_00031);
        if (read_00031_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00032;
        unsigned int read_00032_len;
        unsigned int read_00032_ptr = 0;
        //**** delimited read
        static unsigned char read_00032_delim[] = 
            "\x0a";
        read_00032 = NULL;
        read_00032_len = 0;
        int read_00032_res = delimited_read(0, &read_00032, &read_00032_len, read_00032_delim, 1);
        if (read_00032_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00032_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00032_ptr += data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 10);
        free(read_00032);
        if (read_00032_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00033;
        unsigned int read_00033_len;
        unsigned int read_00033_ptr = 0;
        //**** delimited read
        static unsigned char read_00033_delim[] = 
            "\x0a";
        read_00033 = NULL;
        read_00033_len = 0;
        int read_00033_res = delimited_read(0, &read_00033, &read_00033_len, read_00033_delim, 1);
        if (read_00033_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00033_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00033_ptr += data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 20);
        free(read_00033);
        if (read_00033_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00034;
        unsigned int read_00034_len;
        unsigned int read_00034_ptr = 0;
        //**** delimited read
        static unsigned char read_00034_delim[] = 
            "\x0a";
        read_00034 = NULL;
        read_00034_len = 0;
        int read_00034_res = delimited_read(0, &read_00034, &read_00034_len, read_00034_delim, 1);
        if (read_00034_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00034_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00034_ptr += data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 15);
        free(read_00034);
        if (read_00034_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00035;
        unsigned int read_00035_len;
        unsigned int read_00035_ptr = 0;
        //**** delimited read
        static unsigned char read_00035_delim[] = 
            "\x0a";
        read_00035 = NULL;
        read_00035_len = 0;
        int read_00035_res = delimited_read(0, &read_00035, &read_00035_len, read_00035_delim, 1);
        if (read_00035_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00035_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00035_ptr += data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 20);
        free(read_00035);
        if (read_00035_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00036;
        unsigned int read_00036_len;
        unsigned int read_00036_ptr = 0;
        //**** delimited read
        static unsigned char read_00036_delim[] = 
            "\x0a";
        read_00036 = NULL;
        read_00036_len = 0;
        int read_00036_res = delimited_read(0, &read_00036, &read_00036_len, read_00036_delim, 1);
        if (read_00036_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00036_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00036_ptr += data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 28);
        free(read_00036);
        if (read_00036_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00037;
        unsigned int read_00037_len;
        unsigned int read_00037_ptr = 0;
        //**** delimited read
        static unsigned char read_00037_delim[] = 
            "\x0a";
        read_00037 = NULL;
        read_00037_len = 0;
        int read_00037_res = delimited_read(0, &read_00037, &read_00037_len, read_00037_delim, 1);
        if (read_00037_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00037_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00037_ptr += data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 8);
        free(read_00037);
        if (read_00037_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00038;
        unsigned int read_00038_len;
        unsigned int read_00038_ptr = 0;
        //**** delimited read
        static unsigned char read_00038_delim[] = 
            "\x0a";
        read_00038 = NULL;
        read_00038_len = 0;
        int read_00038_res = delimited_read(0, &read_00038, &read_00038_len, read_00038_delim, 1);
        if (read_00038_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00038_00000[] = 
            "\x0a";
        read_00038_ptr += data_match(read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, match_00038_00000, 1);
        free(read_00038);
        if (read_00038_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00004_00000[] = 
            "\x34\x0a";
        static unsigned int write_00004_00000_len = 2;
        unsigned char *write_00004 = NULL;
        unsigned int write_00004_len = 0;
        write_00004 = append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
        if (write_00004_len > 0) {
            transmit_all(1, write_00004, write_00004_len);
        }
        free(write_00004);
    } while (0);
    do {
        unsigned char *read_00039;
        unsigned int read_00039_len;
        unsigned int read_00039_ptr = 0;
        //**** delimited read
        static unsigned char read_00039_delim[] = 
            "\x0a";
        read_00039 = NULL;
        read_00039_len = 0;
        int read_00039_res = delimited_read(0, &read_00039, &read_00039_len, read_00039_delim, 1);
        if (read_00039_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00039_00000[] = 
            "\x47\x69\x76\x65\x20\x6d\x65\x20\x61\x20\x63\x6f\x75\x6e\x74\x64"
            "\x6f\x77\x6e\x21\x0a";
        read_00039_ptr += data_match(read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, match_00039_00000, 21);
        free(read_00039);
        if (read_00039_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00005_00000[] = 
            "\x66\x66\x66\x66\x66\x66\x66\x66\x0a";
        static unsigned int write_00005_00000_len = 9;
        unsigned char *write_00005 = NULL;
        unsigned int write_00005_len = 0;
        write_00005 = append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
        if (write_00005_len > 0) {
            transmit_all(1, write_00005, write_00005_len);
        }
        free(write_00005);
    } while (0);
    do {
        unsigned char *read_00040;
        unsigned int read_00040_len;
        unsigned int read_00040_ptr = 0;
        //**** delimited read
        static unsigned char read_00040_delim[] = 
            "\x0a";
        read_00040 = NULL;
        read_00040_len = 0;
        int read_00040_res = delimited_read(0, &read_00040, &read_00040_len, read_00040_delim, 1);
        if (read_00040_res) {} //silence unused variable warning
        free(read_00040);
        if (read_00040_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00041;
        unsigned int read_00041_len;
        unsigned int read_00041_ptr = 0;
        //**** delimited read
        static unsigned char read_00041_delim[] = 
            "\x0a";
        read_00041 = NULL;
        read_00041_len = 0;
        int read_00041_res = delimited_read(0, &read_00041, &read_00041_len, read_00041_delim, 1);
        if (read_00041_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00041_00000[] = 
            "\x57\x6f\x61\x68\x2e\x2e\x2e\x20\x62\x6c\x65\x68\x0a";
        read_00041_ptr += data_match(read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, match_00041_00000, 13);
        free(read_00041);
        if (read_00041_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00042;
        unsigned int read_00042_len;
        unsigned int read_00042_ptr = 0;
        //**** delimited read
        static unsigned char read_00042_delim[] = 
            "\x0a";
        read_00042 = NULL;
        read_00042_len = 0;
        int read_00042_res = delimited_read(0, &read_00042, &read_00042_len, read_00042_delim, 1);
        if (read_00042_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00042_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00042_ptr += data_match(read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, match_00042_00000, 22);
        free(read_00042);
        if (read_00042_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00043;
        unsigned int read_00043_len;
        unsigned int read_00043_ptr = 0;
        //**** delimited read
        static unsigned char read_00043_delim[] = 
            "\x0a";
        read_00043 = NULL;
        read_00043_len = 0;
        int read_00043_res = delimited_read(0, &read_00043, &read_00043_len, read_00043_delim, 1);
        if (read_00043_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00043_00000[] = 
            "\x0a";
        read_00043_ptr += data_match(read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, match_00043_00000, 1);
        free(read_00043);
        if (read_00043_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00044;
        unsigned int read_00044_len;
        unsigned int read_00044_ptr = 0;
        //**** delimited read
        static unsigned char read_00044_delim[] = 
            "\x0a";
        read_00044 = NULL;
        read_00044_len = 0;
        int read_00044_res = delimited_read(0, &read_00044, &read_00044_len, read_00044_delim, 1);
        if (read_00044_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00044_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00044_ptr += data_match(read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, match_00044_00000, 11);
        free(read_00044);
        if (read_00044_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00045;
        unsigned int read_00045_len;
        unsigned int read_00045_ptr = 0;
        //**** delimited read
        static unsigned char read_00045_delim[] = 
            "\x0a";
        read_00045 = NULL;
        read_00045_len = 0;
        int read_00045_res = delimited_read(0, &read_00045, &read_00045_len, read_00045_delim, 1);
        if (read_00045_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00045_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00045_ptr += data_match(read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, match_00045_00000, 9);
        free(read_00045);
        if (read_00045_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00046;
        unsigned int read_00046_len;
        unsigned int read_00046_ptr = 0;
        //**** delimited read
        static unsigned char read_00046_delim[] = 
            "\x0a";
        read_00046 = NULL;
        read_00046_len = 0;
        int read_00046_res = delimited_read(0, &read_00046, &read_00046_len, read_00046_delim, 1);
        if (read_00046_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00046_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00046_ptr += data_match(read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, match_00046_00000, 10);
        free(read_00046);
        if (read_00046_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00047;
        unsigned int read_00047_len;
        unsigned int read_00047_ptr = 0;
        //**** delimited read
        static unsigned char read_00047_delim[] = 
            "\x0a";
        read_00047 = NULL;
        read_00047_len = 0;
        int read_00047_res = delimited_read(0, &read_00047, &read_00047_len, read_00047_delim, 1);
        if (read_00047_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00047_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00047_ptr += data_match(read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, match_00047_00000, 20);
        free(read_00047);
        if (read_00047_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00048;
        unsigned int read_00048_len;
        unsigned int read_00048_ptr = 0;
        //**** delimited read
        static unsigned char read_00048_delim[] = 
            "\x0a";
        read_00048 = NULL;
        read_00048_len = 0;
        int read_00048_res = delimited_read(0, &read_00048, &read_00048_len, read_00048_delim, 1);
        if (read_00048_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00048_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00048_ptr += data_match(read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, match_00048_00000, 15);
        free(read_00048);
        if (read_00048_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00049;
        unsigned int read_00049_len;
        unsigned int read_00049_ptr = 0;
        //**** delimited read
        static unsigned char read_00049_delim[] = 
            "\x0a";
        read_00049 = NULL;
        read_00049_len = 0;
        int read_00049_res = delimited_read(0, &read_00049, &read_00049_len, read_00049_delim, 1);
        if (read_00049_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00049_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00049_ptr += data_match(read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, match_00049_00000, 20);
        free(read_00049);
        if (read_00049_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00050;
        unsigned int read_00050_len;
        unsigned int read_00050_ptr = 0;
        //**** delimited read
        static unsigned char read_00050_delim[] = 
            "\x0a";
        read_00050 = NULL;
        read_00050_len = 0;
        int read_00050_res = delimited_read(0, &read_00050, &read_00050_len, read_00050_delim, 1);
        if (read_00050_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00050_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00050_ptr += data_match(read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, match_00050_00000, 28);
        free(read_00050);
        if (read_00050_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00051;
        unsigned int read_00051_len;
        unsigned int read_00051_ptr = 0;
        //**** delimited read
        static unsigned char read_00051_delim[] = 
            "\x0a";
        read_00051 = NULL;
        read_00051_len = 0;
        int read_00051_res = delimited_read(0, &read_00051, &read_00051_len, read_00051_delim, 1);
        if (read_00051_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00051_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00051_ptr += data_match(read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, match_00051_00000, 8);
        free(read_00051);
        if (read_00051_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00052;
        unsigned int read_00052_len;
        unsigned int read_00052_ptr = 0;
        //**** delimited read
        static unsigned char read_00052_delim[] = 
            "\x0a";
        read_00052 = NULL;
        read_00052_len = 0;
        int read_00052_res = delimited_read(0, &read_00052, &read_00052_len, read_00052_delim, 1);
        if (read_00052_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00052_00000[] = 
            "\x0a";
        read_00052_ptr += data_match(read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, match_00052_00000, 1);
        free(read_00052);
        if (read_00052_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00006_00000[] = 
            "\x33\x0a";
        static unsigned int write_00006_00000_len = 2;
        unsigned char *write_00006 = NULL;
        unsigned int write_00006_len = 0;
        write_00006 = append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
        if (write_00006_len > 0) {
            transmit_all(1, write_00006, write_00006_len);
        }
        free(write_00006);
    } while (0);
    do {
        unsigned char *read_00053;
        unsigned int read_00053_len;
        unsigned int read_00053_ptr = 0;
        //**** delimited read
        static unsigned char read_00053_delim[] = 
            "\x0a";
        read_00053 = NULL;
        read_00053_len = 0;
        int read_00053_res = delimited_read(0, &read_00053, &read_00053_len, read_00053_delim, 1);
        if (read_00053_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00053_00000[] = 
            "\x4c\x65\x74\x20\x6d\x65\x20\x68\x65\x6c\x70\x20\x79\x6f\x75\x20"
            "\x63\x68\x65\x61\x74\x20\x61\x74\x20\x73\x75\x64\x6f\x6b\x75\x2c"
            "\x20\x65\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x62\x6f\x61\x72"
            "\x64\x20\x6e\x30\x30\x62\x3a\x0a";
        read_00053_ptr += data_match(read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, match_00053_00000, 56);
        free(read_00053);
        if (read_00053_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00007_00000[] = 
            "\x31\x31\x31\x31\x31\x31\x31\x31\x20\x0a\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static unsigned int write_00007_00000_len = 90;
        unsigned char *write_00007 = NULL;
        unsigned int write_00007_len = 0;
        write_00007 = append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
        if (write_00007_len > 0) {
            transmit_all(1, write_00007, write_00007_len);
        }
        free(write_00007);
    } while (0);
    do {
        unsigned char *read_00054;
        unsigned int read_00054_len;
        unsigned int read_00054_ptr = 0;
        //**** delimited read
        static unsigned char read_00054_delim[] = 
            "\x0a";
        read_00054 = NULL;
        read_00054_len = 0;
        int read_00054_res = delimited_read(0, &read_00054, &read_00054_len, read_00054_delim, 1);
        if (read_00054_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00054_00000[] = 
            "\x4e\x69\x63\x65\x20\x74\x72\x79\x0a";
        read_00054_ptr += data_match(read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, match_00054_00000, 9);
        free(read_00054);
        if (read_00054_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00055;
        unsigned int read_00055_len;
        unsigned int read_00055_ptr = 0;
        //**** delimited read
        static unsigned char read_00055_delim[] = 
            "\x0a";
        read_00055 = NULL;
        read_00055_len = 0;
        int read_00055_res = delimited_read(0, &read_00055, &read_00055_len, read_00055_delim, 1);
        if (read_00055_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00055_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00055_ptr += data_match(read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, match_00055_00000, 22);
        free(read_00055);
        if (read_00055_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00056;
        unsigned int read_00056_len;
        unsigned int read_00056_ptr = 0;
        //**** delimited read
        static unsigned char read_00056_delim[] = 
            "\x0a";
        read_00056 = NULL;
        read_00056_len = 0;
        int read_00056_res = delimited_read(0, &read_00056, &read_00056_len, read_00056_delim, 1);
        if (read_00056_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00056_00000[] = 
            "\x0a";
        read_00056_ptr += data_match(read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, match_00056_00000, 1);
        free(read_00056);
        if (read_00056_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00057;
        unsigned int read_00057_len;
        unsigned int read_00057_ptr = 0;
        //**** delimited read
        static unsigned char read_00057_delim[] = 
            "\x0a";
        read_00057 = NULL;
        read_00057_len = 0;
        int read_00057_res = delimited_read(0, &read_00057, &read_00057_len, read_00057_delim, 1);
        if (read_00057_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00057_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00057_ptr += data_match(read_00057 + read_00057_ptr, read_00057_len - read_00057_ptr, match_00057_00000, 11);
        free(read_00057);
        if (read_00057_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00058;
        unsigned int read_00058_len;
        unsigned int read_00058_ptr = 0;
        //**** delimited read
        static unsigned char read_00058_delim[] = 
            "\x0a";
        read_00058 = NULL;
        read_00058_len = 0;
        int read_00058_res = delimited_read(0, &read_00058, &read_00058_len, read_00058_delim, 1);
        if (read_00058_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00058_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00058_ptr += data_match(read_00058 + read_00058_ptr, read_00058_len - read_00058_ptr, match_00058_00000, 9);
        free(read_00058);
        if (read_00058_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00059;
        unsigned int read_00059_len;
        unsigned int read_00059_ptr = 0;
        //**** delimited read
        static unsigned char read_00059_delim[] = 
            "\x0a";
        read_00059 = NULL;
        read_00059_len = 0;
        int read_00059_res = delimited_read(0, &read_00059, &read_00059_len, read_00059_delim, 1);
        if (read_00059_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00059_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00059_ptr += data_match(read_00059 + read_00059_ptr, read_00059_len - read_00059_ptr, match_00059_00000, 10);
        free(read_00059);
        if (read_00059_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00060;
        unsigned int read_00060_len;
        unsigned int read_00060_ptr = 0;
        //**** delimited read
        static unsigned char read_00060_delim[] = 
            "\x0a";
        read_00060 = NULL;
        read_00060_len = 0;
        int read_00060_res = delimited_read(0, &read_00060, &read_00060_len, read_00060_delim, 1);
        if (read_00060_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00060_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00060_ptr += data_match(read_00060 + read_00060_ptr, read_00060_len - read_00060_ptr, match_00060_00000, 20);
        free(read_00060);
        if (read_00060_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00061;
        unsigned int read_00061_len;
        unsigned int read_00061_ptr = 0;
        //**** delimited read
        static unsigned char read_00061_delim[] = 
            "\x0a";
        read_00061 = NULL;
        read_00061_len = 0;
        int read_00061_res = delimited_read(0, &read_00061, &read_00061_len, read_00061_delim, 1);
        if (read_00061_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00061_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00061_ptr += data_match(read_00061 + read_00061_ptr, read_00061_len - read_00061_ptr, match_00061_00000, 15);
        free(read_00061);
        if (read_00061_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00062;
        unsigned int read_00062_len;
        unsigned int read_00062_ptr = 0;
        //**** delimited read
        static unsigned char read_00062_delim[] = 
            "\x0a";
        read_00062 = NULL;
        read_00062_len = 0;
        int read_00062_res = delimited_read(0, &read_00062, &read_00062_len, read_00062_delim, 1);
        if (read_00062_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00062_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00062_ptr += data_match(read_00062 + read_00062_ptr, read_00062_len - read_00062_ptr, match_00062_00000, 20);
        free(read_00062);
        if (read_00062_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00063;
        unsigned int read_00063_len;
        unsigned int read_00063_ptr = 0;
        //**** delimited read
        static unsigned char read_00063_delim[] = 
            "\x0a";
        read_00063 = NULL;
        read_00063_len = 0;
        int read_00063_res = delimited_read(0, &read_00063, &read_00063_len, read_00063_delim, 1);
        if (read_00063_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00063_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00063_ptr += data_match(read_00063 + read_00063_ptr, read_00063_len - read_00063_ptr, match_00063_00000, 28);
        free(read_00063);
        if (read_00063_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00064;
        unsigned int read_00064_len;
        unsigned int read_00064_ptr = 0;
        //**** delimited read
        static unsigned char read_00064_delim[] = 
            "\x0a";
        read_00064 = NULL;
        read_00064_len = 0;
        int read_00064_res = delimited_read(0, &read_00064, &read_00064_len, read_00064_delim, 1);
        if (read_00064_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00064_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00064_ptr += data_match(read_00064 + read_00064_ptr, read_00064_len - read_00064_ptr, match_00064_00000, 8);
        free(read_00064);
        if (read_00064_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00065;
        unsigned int read_00065_len;
        unsigned int read_00065_ptr = 0;
        //**** delimited read
        static unsigned char read_00065_delim[] = 
            "\x0a";
        read_00065 = NULL;
        read_00065_len = 0;
        int read_00065_res = delimited_read(0, &read_00065, &read_00065_len, read_00065_delim, 1);
        if (read_00065_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00065_00000[] = 
            "\x0a";
        read_00065_ptr += data_match(read_00065 + read_00065_ptr, read_00065_len - read_00065_ptr, match_00065_00000, 1);
        free(read_00065);
        if (read_00065_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00008_00000[] = 
            "\x34\x0a";
        static unsigned int write_00008_00000_len = 2;
        unsigned char *write_00008 = NULL;
        unsigned int write_00008_len = 0;
        write_00008 = append_buf(write_00008, &write_00008_len, write_00008_00000, write_00008_00000_len);
        if (write_00008_len > 0) {
            transmit_all(1, write_00008, write_00008_len);
        }
        free(write_00008);
    } while (0);
    do {
        unsigned char *read_00066;
        unsigned int read_00066_len;
        unsigned int read_00066_ptr = 0;
        //**** delimited read
        static unsigned char read_00066_delim[] = 
            "\x0a";
        read_00066 = NULL;
        read_00066_len = 0;
        int read_00066_res = delimited_read(0, &read_00066, &read_00066_len, read_00066_delim, 1);
        if (read_00066_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00066_00000[] = 
            "\x47\x69\x76\x65\x20\x6d\x65\x20\x61\x20\x63\x6f\x75\x6e\x74\x64"
            "\x6f\x77\x6e\x21\x0a";
        read_00066_ptr += data_match(read_00066 + read_00066_ptr, read_00066_len - read_00066_ptr, match_00066_00000, 21);
        free(read_00066);
        if (read_00066_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned int cookie;
        char cookie_str[40] = { 0 };
        unsigned char *varbuf;
        size_t varlen;

        varbuf = getenv("cookie", &varlen);
        if (varbuf == NULL)
            return -1;

        cookie = (cookie & 0xff) << 24 |
            (cookie & 0xff00) << 16 | 
            (cookie & 0xff0000) << 8 |
            (cookie & 0xff000000);

        if (utostr(*(unsigned int *)varbuf, 16, 0, cookie_str, sizeof(cookie_str)) != 0)
            return -1;

        transmit_all(1, cookie_str, strlen(cookie_str));
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00010_00000[] = 
            "\x0a";
        static unsigned int write_00010_00000_len = 1;
        unsigned char *write_00010 = NULL;
        unsigned int write_00010_len = 0;
        write_00010 = append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
        if (write_00010_len > 0) {
            transmit_all(1, write_00010, write_00010_len);
        }
        free(write_00010);
    } while (0);
    do {
        unsigned char *read_00067;
        unsigned int read_00067_len;
        unsigned int read_00067_ptr = 0;
        //**** delimited read
        static unsigned char read_00067_delim[] = 
            "\x0a";
        read_00067 = NULL;
        read_00067_len = 0;
        int read_00067_res = delimited_read(0, &read_00067, &read_00067_len, read_00067_delim, 1);
        if (read_00067_res) {} //silence unused variable warning
        free(read_00067);
        if (read_00067_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00068;
        unsigned int read_00068_len;
        unsigned int read_00068_ptr = 0;
        //**** delimited read
        static unsigned char read_00068_delim[] = 
            "\x0a";
        read_00068 = NULL;
        read_00068_len = 0;
        int read_00068_res = delimited_read(0, &read_00068, &read_00068_len, read_00068_delim, 1);
        if (read_00068_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00068_00000[] = 
            "\x49\x20\x73\x61\x79\x20\x68\x75\x72\x6c\x2c\x20\x69\x66\x20\x79"
            "\x6f\x75\x20\x62\x6c\x6f\x77\x20\x63\x68\x75\x6e\x6b\x73\x20\x61"
            "\x6e\x64\x20\x73\x68\x65\x20\x63\x6f\x6d\x65\x73\x20\x62\x61\x63"
            "\x6b\x2c\x20\x73\x68\x65\x27\x73\x20\x79\x6f\x75\x72\x73\x2e\x0a";
        read_00068_ptr += data_match(read_00068 + read_00068_ptr, read_00068_len - read_00068_ptr, match_00068_00000, 64);
        free(read_00068);
        if (read_00068_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00069;
        unsigned int read_00069_len;
        unsigned int read_00069_ptr = 0;
        //**** delimited read
        static unsigned char read_00069_delim[] = 
            "\x0a";
        read_00069 = NULL;
        read_00069_len = 0;
        int read_00069_res = delimited_read(0, &read_00069, &read_00069_len, read_00069_delim, 1);
        if (read_00069_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00069_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00069_ptr += data_match(read_00069 + read_00069_ptr, read_00069_len - read_00069_ptr, match_00069_00000, 22);
        free(read_00069);
        if (read_00069_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00070;
        unsigned int read_00070_len;
        unsigned int read_00070_ptr = 0;
        //**** delimited read
        static unsigned char read_00070_delim[] = 
            "\x0a";
        read_00070 = NULL;
        read_00070_len = 0;
        int read_00070_res = delimited_read(0, &read_00070, &read_00070_len, read_00070_delim, 1);
        if (read_00070_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00070_00000[] = 
            "\x0a";
        read_00070_ptr += data_match(read_00070 + read_00070_ptr, read_00070_len - read_00070_ptr, match_00070_00000, 1);
        free(read_00070);
        if (read_00070_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00071;
        unsigned int read_00071_len;
        unsigned int read_00071_ptr = 0;
        //**** delimited read
        static unsigned char read_00071_delim[] = 
            "\x0a";
        read_00071 = NULL;
        read_00071_len = 0;
        int read_00071_res = delimited_read(0, &read_00071, &read_00071_len, read_00071_delim, 1);
        if (read_00071_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00071_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00071_ptr += data_match(read_00071 + read_00071_ptr, read_00071_len - read_00071_ptr, match_00071_00000, 11);
        free(read_00071);
        if (read_00071_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00072;
        unsigned int read_00072_len;
        unsigned int read_00072_ptr = 0;
        //**** delimited read
        static unsigned char read_00072_delim[] = 
            "\x0a";
        read_00072 = NULL;
        read_00072_len = 0;
        int read_00072_res = delimited_read(0, &read_00072, &read_00072_len, read_00072_delim, 1);
        if (read_00072_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00072_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00072_ptr += data_match(read_00072 + read_00072_ptr, read_00072_len - read_00072_ptr, match_00072_00000, 9);
        free(read_00072);
        if (read_00072_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00073;
        unsigned int read_00073_len;
        unsigned int read_00073_ptr = 0;
        //**** delimited read
        static unsigned char read_00073_delim[] = 
            "\x0a";
        read_00073 = NULL;
        read_00073_len = 0;
        int read_00073_res = delimited_read(0, &read_00073, &read_00073_len, read_00073_delim, 1);
        if (read_00073_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00073_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00073_ptr += data_match(read_00073 + read_00073_ptr, read_00073_len - read_00073_ptr, match_00073_00000, 10);
        free(read_00073);
        if (read_00073_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00074;
        unsigned int read_00074_len;
        unsigned int read_00074_ptr = 0;
        //**** delimited read
        static unsigned char read_00074_delim[] = 
            "\x0a";
        read_00074 = NULL;
        read_00074_len = 0;
        int read_00074_res = delimited_read(0, &read_00074, &read_00074_len, read_00074_delim, 1);
        if (read_00074_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00074_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00074_ptr += data_match(read_00074 + read_00074_ptr, read_00074_len - read_00074_ptr, match_00074_00000, 20);
        free(read_00074);
        if (read_00074_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00075;
        unsigned int read_00075_len;
        unsigned int read_00075_ptr = 0;
        //**** delimited read
        static unsigned char read_00075_delim[] = 
            "\x0a";
        read_00075 = NULL;
        read_00075_len = 0;
        int read_00075_res = delimited_read(0, &read_00075, &read_00075_len, read_00075_delim, 1);
        if (read_00075_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00075_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00075_ptr += data_match(read_00075 + read_00075_ptr, read_00075_len - read_00075_ptr, match_00075_00000, 15);
        free(read_00075);
        if (read_00075_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00076;
        unsigned int read_00076_len;
        unsigned int read_00076_ptr = 0;
        //**** delimited read
        static unsigned char read_00076_delim[] = 
            "\x0a";
        read_00076 = NULL;
        read_00076_len = 0;
        int read_00076_res = delimited_read(0, &read_00076, &read_00076_len, read_00076_delim, 1);
        if (read_00076_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00076_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00076_ptr += data_match(read_00076 + read_00076_ptr, read_00076_len - read_00076_ptr, match_00076_00000, 20);
        free(read_00076);
        if (read_00076_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00077;
        unsigned int read_00077_len;
        unsigned int read_00077_ptr = 0;
        //**** delimited read
        static unsigned char read_00077_delim[] = 
            "\x0a";
        read_00077 = NULL;
        read_00077_len = 0;
        int read_00077_res = delimited_read(0, &read_00077, &read_00077_len, read_00077_delim, 1);
        if (read_00077_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00077_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00077_ptr += data_match(read_00077 + read_00077_ptr, read_00077_len - read_00077_ptr, match_00077_00000, 28);
        free(read_00077);
        if (read_00077_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00078;
        unsigned int read_00078_len;
        unsigned int read_00078_ptr = 0;
        //**** delimited read
        static unsigned char read_00078_delim[] = 
            "\x0a";
        read_00078 = NULL;
        read_00078_len = 0;
        int read_00078_res = delimited_read(0, &read_00078, &read_00078_len, read_00078_delim, 1);
        if (read_00078_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00078_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00078_ptr += data_match(read_00078 + read_00078_ptr, read_00078_len - read_00078_ptr, match_00078_00000, 8);
        free(read_00078);
        if (read_00078_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00079;
        unsigned int read_00079_len;
        unsigned int read_00079_ptr = 0;
        //**** delimited read
        static unsigned char read_00079_delim[] = 
            "\x0a";
        read_00079 = NULL;
        read_00079_len = 0;
        int read_00079_res = delimited_read(0, &read_00079, &read_00079_len, read_00079_delim, 1);
        if (read_00079_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00079_00000[] = 
            "\x0a";
        read_00079_ptr += data_match(read_00079 + read_00079_ptr, read_00079_len - read_00079_ptr, match_00079_00000, 1);
        free(read_00079);
        if (read_00079_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00011_00000[] = 
            "\x35\x0a";
        static unsigned int write_00011_00000_len = 2;
        unsigned char *write_00011 = NULL;
        unsigned int write_00011_len = 0;
        write_00011 = append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
        if (write_00011_len > 0) {
            transmit_all(1, write_00011, write_00011_len);
        }
        free(write_00011);
    } while (0);
    do {
        unsigned char *read_00080;
        unsigned int read_00080_len;
        unsigned int read_00080_ptr = 0;
        //**** delimited read
        static unsigned char read_00080_delim[] = 
            "\x0a";
        read_00080 = NULL;
        read_00080_len = 0;
        int read_00080_res = delimited_read(0, &read_00080, &read_00080_len, read_00080_delim, 1);
        if (read_00080_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00080_00000[] = 
            "\x57\x65\x6c\x63\x6f\x6d\x65\x20\x74\x6f\x20\x74\x68\x65\x20\x53"
            "\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x21\x0a";
        read_00080_ptr += data_match(read_00080 + read_00080_ptr, read_00080_len - read_00080_ptr, match_00080_00000, 28);
        free(read_00080);
        if (read_00080_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00081;
        unsigned int read_00081_len;
        unsigned int read_00081_ptr = 0;
        //**** delimited read
        static unsigned char read_00081_delim[] = 
            "\x0a";
        read_00081 = NULL;
        read_00081_len = 0;
        int read_00081_res = delimited_read(0, &read_00081, &read_00081_len, read_00081_delim, 1);
        if (read_00081_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00081_00000[] = 
            "\x41\x20\x77\x69\x6c\x64\x20\x4d\x69\x73\x73\x69\x6e\x67\x6e\x6f"
            "\x20\x68\x61\x73\x20\x61\x70\x70\x65\x61\x72\x65\x64\x21\x0a";
        read_00081_ptr += data_match(read_00081 + read_00081_ptr, read_00081_len - read_00081_ptr, match_00081_00000, 31);
        free(read_00081);
        if (read_00081_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00082;
        unsigned int read_00082_len;
        unsigned int read_00082_ptr = 0;
        //**** delimited read
        static unsigned char read_00082_delim[] = 
            "\x0a";
        read_00082 = NULL;
        read_00082_len = 0;
        int read_00082_res = delimited_read(0, &read_00082, &read_00082_len, read_00082_delim, 1);
        if (read_00082_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00082_00000[] = 
            "\x57\x68\x61\x74\x20\x74\x6f\x20\x64\x6f\x3f\x0a";
        read_00082_ptr += data_match(read_00082 + read_00082_ptr, read_00082_len - read_00082_ptr, match_00082_00000, 12);
        free(read_00082);
        if (read_00082_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00083;
        unsigned int read_00083_len;
        unsigned int read_00083_ptr = 0;
        //**** delimited read
        static unsigned char read_00083_delim[] = 
            "\x0a";
        read_00083 = NULL;
        read_00083_len = 0;
        int read_00083_res = delimited_read(0, &read_00083, &read_00083_len, read_00083_delim, 1);
        if (read_00083_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00083_00000[] = 
            "\x31\x2e\x20\x42\x61\x6c\x6c\x0a";
        read_00083_ptr += data_match(read_00083 + read_00083_ptr, read_00083_len - read_00083_ptr, match_00083_00000, 8);
        free(read_00083);
        if (read_00083_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00084;
        unsigned int read_00084_len;
        unsigned int read_00084_ptr = 0;
        //**** delimited read
        static unsigned char read_00084_delim[] = 
            "\x0a";
        read_00084 = NULL;
        read_00084_len = 0;
        int read_00084_res = delimited_read(0, &read_00084, &read_00084_len, read_00084_delim, 1);
        if (read_00084_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00084_00000[] = 
            "\x32\x2e\x20\x52\x6f\x63\x6b\x0a";
        read_00084_ptr += data_match(read_00084 + read_00084_ptr, read_00084_len - read_00084_ptr, match_00084_00000, 8);
        free(read_00084);
        if (read_00084_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00085;
        unsigned int read_00085_len;
        unsigned int read_00085_ptr = 0;
        //**** delimited read
        static unsigned char read_00085_delim[] = 
            "\x0a";
        read_00085 = NULL;
        read_00085_len = 0;
        int read_00085_res = delimited_read(0, &read_00085, &read_00085_len, read_00085_delim, 1);
        if (read_00085_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00085_00000[] = 
            "\x33\x2e\x20\x42\x61\x69\x74\x0a";
        read_00085_ptr += data_match(read_00085 + read_00085_ptr, read_00085_len - read_00085_ptr, match_00085_00000, 8);
        free(read_00085);
        if (read_00085_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00086;
        unsigned int read_00086_len;
        unsigned int read_00086_ptr = 0;
        //**** delimited read
        static unsigned char read_00086_delim[] = 
            "\x0a";
        read_00086 = NULL;
        read_00086_len = 0;
        int read_00086_res = delimited_read(0, &read_00086, &read_00086_len, read_00086_delim, 1);
        if (read_00086_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00086_00000[] = 
            "\x34\x2e\x20\x52\x75\x6e\x0a";
        read_00086_ptr += data_match(read_00086 + read_00086_ptr, read_00086_len - read_00086_ptr, match_00086_00000, 7);
        free(read_00086);
        if (read_00086_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00087;
        unsigned int read_00087_len;
        unsigned int read_00087_ptr = 0;
        //**** delimited read
        static unsigned char read_00087_delim[] = 
            "\x0a";
        read_00087 = NULL;
        read_00087_len = 0;
        int read_00087_res = delimited_read(0, &read_00087, &read_00087_len, read_00087_delim, 1);
        if (read_00087_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00087_00000[] = 
            "\x0a";
        read_00087_ptr += data_match(read_00087 + read_00087_ptr, read_00087_len - read_00087_ptr, match_00087_00000, 1);
        free(read_00087);
        if (read_00087_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00012_00000[] = 
            "\x31\x0a";
        static unsigned int write_00012_00000_len = 2;
        unsigned char *write_00012 = NULL;
        unsigned int write_00012_len = 0;
        write_00012 = append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
        if (write_00012_len > 0) {
            transmit_all(1, write_00012, write_00012_len);
        }
        free(write_00012);
    } while (0);
    do {
        unsigned char *read_00088;
        unsigned int read_00088_len;
        unsigned int read_00088_ptr = 0;
        //**** delimited read
        static unsigned char read_00088_delim[] = 
            "\x0a";
        read_00088 = NULL;
        read_00088_len = 0;
        int read_00088_res = delimited_read(0, &read_00088, &read_00088_len, read_00088_delim, 1);
        if (read_00088_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00088_00000[] = 
            "\x43\x6f\x6e\x67\x72\x61\x74\x75\x6c\x61\x74\x69\x6f\x6e\x73\x2c"
            "\x20\x79\x6f\x75\x27\x76\x65\x20\x63\x61\x75\x67\x68\x74\x20\x4d"
            "\x69\x73\x73\x69\x6e\x67\x6e\x6f\x21\x0a";
        read_00088_ptr += data_match(read_00088 + read_00088_ptr, read_00088_len - read_00088_ptr, match_00088_00000, 42);
        free(read_00088);
        if (read_00088_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00089;
        unsigned int read_00089_len;
        unsigned int read_00089_ptr = 0;
        //**** delimited read
        static unsigned char read_00089_delim[] = 
            "\x0a";
        read_00089 = NULL;
        read_00089_len = 0;
        int read_00089_res = delimited_read(0, &read_00089, &read_00089_len, read_00089_delim, 1);
        if (read_00089_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00089_00000[] = 
            "\x50\x6c\x65\x61\x73\x65\x20\x65\x6e\x74\x65\x72\x20\x61\x20\x6e"
            "\x69\x63\x6b\x6e\x61\x6d\x65\x3a\x0a";
        read_00089_ptr += data_match(read_00089 + read_00089_ptr, read_00089_len - read_00089_ptr, match_00089_00000, 25);
        free(read_00089);
        if (read_00089_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned int type1_ip;
        char type1_ip_str[40] = { 0 };
        unsigned char *varbuf;
        size_t varlen;

        varbuf = getenv("TYPE1_IP", &varlen);
        if (varbuf == NULL)
            return -1;

        if (utostr(*(unsigned int *)varbuf, 16, 0, type1_ip_str, sizeof(type1_ip_str)) != 0)
            return -1;

        transmit_all(1, type1_ip_str, strlen(type1_ip_str));
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00014_00000[] = 
            "\x0a";
        static unsigned int write_00014_00000_len = 1;
        unsigned char *write_00014 = NULL;
        unsigned int write_00014_len = 0;
        write_00014 = append_buf(write_00014, &write_00014_len, write_00014_00000, write_00014_00000_len);
        if (write_00014_len > 0) {
            transmit_all(1, write_00014, write_00014_len);
        }
        free(write_00014);
    } while (0);
    do {
        unsigned char *read_00090;
        unsigned int read_00090_len;
        unsigned int read_00090_ptr = 0;
        //**** delimited read
        static unsigned char read_00090_delim[] = 
            "\x0a";
        read_00090 = NULL;
        read_00090_len = 0;
        int read_00090_res = delimited_read(0, &read_00090, &read_00090_len, read_00090_delim, 1);
        if (read_00090_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00090_00000[] = 
            "\x42\x5a\x5a\x5a\x54\x21\x0a";
        read_00090_ptr += data_match(read_00090 + read_00090_ptr, read_00090_len - read_00090_ptr, match_00090_00000, 7);
        free(read_00090);
        if (read_00090_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned int type1_reg;
        char type1_reg_str[40] = { 0 };
        unsigned char *varbuf;
        size_t varlen;

        varbuf = getenv("TYPE1_REG", &varlen);
        if (varbuf == NULL)
            return -1;

        if (utostr(*(unsigned int *)varbuf, 16, 0, type1_reg_str, sizeof(type1_reg_str)) != 0)
            return -1;

        transmit_all(1, type1_reg_str, strlen(type1_reg_str));
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00016_00000[] = 
            "\x0a";
        static unsigned int write_00016_00000_len = 1;
        unsigned char *write_00016 = NULL;
        unsigned int write_00016_len = 0;
        write_00016 = append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
        if (write_00016_len > 0) {
            transmit_all(1, write_00016, write_00016_len);
        }
        free(write_00016);
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00017_00000[] = 
            "\x38\x0a";
        static unsigned int write_00017_00000_len = 2;
        unsigned char *write_00017 = NULL;
        unsigned int write_00017_len = 0;
        write_00017 = append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
        if (write_00017_len > 0) {
            transmit_all(1, write_00017, write_00017_len);
        }
        free(write_00017);
    } while (0);
}
