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

#include <libpov.h>
#include "words.h"
int main(void) {
    negotiate_type2();
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
            "\x31\x0a";
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
        /* read match pcre:
           --------

*/
        static char read_00011_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00011_00000_match;
        pcre *read_00011_00000_pcre = init_regex(read_00011_00000_regex);
        if (read_00011_00000_pcre != NULL) {
            int rc = regex_match(read_00011_00000_pcre, 0, read_00011 + read_00011_ptr, read_00011_len - read_00011_ptr, &read_00011_00000_match);
            if (rc > 0) {
                read_00011_ptr += read_00011_00000_match.match_end - read_00011_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00011_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00011);
        if (read_00011_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           |      |

*/
        static char read_00012_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00012_00000_match;
        pcre *read_00012_00000_pcre = init_regex(read_00012_00000_regex);
        if (read_00012_00000_pcre != NULL) {
            int rc = regex_match(read_00012_00000_pcre, 0, read_00012 + read_00012_ptr, read_00012_len - read_00012_ptr, &read_00012_00000_match);
            if (rc > 0) {
                read_00012_ptr += read_00012_00000_match.match_end - read_00012_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00012_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00013_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00013_00000_match;
        pcre *read_00013_00000_pcre = init_regex(read_00013_00000_regex);
        if (read_00013_00000_pcre != NULL) {
            int rc = regex_match(read_00013_00000_pcre, 0, read_00013 + read_00013_ptr, read_00013_len - read_00013_ptr, &read_00013_00000_match);
            if (rc > 0) {
                read_00013_ptr += read_00013_00000_match.match_end - read_00013_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00013_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00014_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00014_00000_match;
        pcre *read_00014_00000_pcre = init_regex(read_00014_00000_regex);
        if (read_00014_00000_pcre != NULL) {
            int rc = regex_match(read_00014_00000_pcre, 0, read_00014 + read_00014_ptr, read_00014_len - read_00014_ptr, &read_00014_00000_match);
            if (rc > 0) {
                read_00014_ptr += read_00014_00000_match.match_end - read_00014_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00014_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00015_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00015_00000_match;
        pcre *read_00015_00000_pcre = init_regex(read_00015_00000_regex);
        if (read_00015_00000_pcre != NULL) {
            int rc = regex_match(read_00015_00000_pcre, 0, read_00015 + read_00015_ptr, read_00015_len - read_00015_ptr, &read_00015_00000_match);
            if (rc > 0) {
                read_00015_ptr += read_00015_00000_match.match_end - read_00015_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00015_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . .     |

*/
        static char read_00016_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00016_00000_match;
        pcre *read_00016_00000_pcre = init_regex(read_00016_00000_regex);
        if (read_00016_00000_pcre != NULL) {
            int rc = regex_match(read_00016_00000_pcre, 0, read_00016 + read_00016_ptr, read_00016_len - read_00016_ptr, &read_00016_00000_match);
            if (rc > 0) {
                read_00016_ptr += read_00016_00000_match.match_end - read_00016_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00016_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |

*/
        static char read_00017_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00017_00000_match;
        pcre *read_00017_00000_pcre = init_regex(read_00017_00000_regex);
        if (read_00017_00000_pcre != NULL) {
            int rc = regex_match(read_00017_00000_pcre, 0, read_00017 + read_00017_ptr, read_00017_len - read_00017_ptr, &read_00017_00000_match);
            if (rc > 0) {
                read_00017_ptr += read_00017_00000_match.match_end - read_00017_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00017_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           _______|

*/
        static char read_00018_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00018_00000_match;
        pcre *read_00018_00000_pcre = init_regex(read_00018_00000_regex);
        if (read_00018_00000_pcre != NULL) {
            int rc = regex_match(read_00018_00000_pcre, 0, read_00018 + read_00018_ptr, read_00018_len - read_00018_ptr, &read_00018_00000_match);
            if (rc > 0) {
                read_00018_ptr += read_00018_00000_match.match_end - read_00018_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00018_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00019_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00019_00000_match;
        pcre *read_00019_00000_pcre = init_regex(read_00019_00000_regex);
        if (read_00019_00000_pcre != NULL) {
            int rc = regex_match(read_00019_00000_pcre, 0, read_00019 + read_00019_ptr, read_00019_len - read_00019_ptr, &read_00019_00000_match);
            if (rc > 0) {
                read_00019_ptr += read_00019_00000_match.match_end - read_00019_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00019_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00020_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00020_00000_match;
        pcre *read_00020_00000_pcre = init_regex(read_00020_00000_regex);
        if (read_00020_00000_pcre != NULL) {
            int rc = regex_match(read_00020_00000_pcre, 0, read_00020 + read_00020_ptr, read_00020_len - read_00020_ptr, &read_00020_00000_match);
            if (rc > 0) {
                read_00020_ptr += read_00020_00000_match.match_end - read_00020_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00020_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00021_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00021_00000_match;
        pcre *read_00021_00000_pcre = init_regex(read_00021_00000_regex);
        if (read_00021_00000_pcre != NULL) {
            int rc = regex_match(read_00021_00000_pcre, 0, read_00021 + read_00021_ptr, read_00021_len - read_00021_ptr, &read_00021_00000_match);
            if (rc > 0) {
                read_00021_ptr += read_00021_00000_match.match_end - read_00021_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00021_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
Incorrect: .*

*/
        static char read_00022_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00022_00000_match;
        pcre *read_00022_00000_pcre = init_regex(read_00022_00000_regex);
        if (read_00022_00000_pcre != NULL) {
            int rc = regex_match(read_00022_00000_pcre, 0, read_00022 + read_00022_ptr, read_00022_len - read_00022_ptr, &read_00022_00000_match);
            if (rc > 0) {
                read_00022_ptr += read_00022_00000_match.match_end - read_00022_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00022_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00022);
        if (read_00022_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00001_00000[] = 
            "\x3a";
        static unsigned int write_00001_00000_len = 1;
        unsigned char *write_00001 = NULL;
        unsigned int write_00001_len = 0;
        write_00001 = append_buf(write_00001, &write_00001_len, write_00001_00000, write_00001_00000_len);
        if (write_00001_len > 0) {
            transmit_all(1, write_00001, write_00001_len);
        }
        free(write_00001);
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
        /* read match pcre:
           --------

*/
        static char read_00023_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00023_00000_match;
        pcre *read_00023_00000_pcre = init_regex(read_00023_00000_regex);
        if (read_00023_00000_pcre != NULL) {
            int rc = regex_match(read_00023_00000_pcre, 0, read_00023 + read_00023_ptr, read_00023_len - read_00023_ptr, &read_00023_00000_match);
            if (rc > 0) {
                read_00023_ptr += read_00023_00000_match.match_end - read_00023_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00023_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |      |

*/
        static char read_00024_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00024_00000_match;
        pcre *read_00024_00000_pcre = init_regex(read_00024_00000_regex);
        if (read_00024_00000_pcre != NULL) {
            int rc = regex_match(read_00024_00000_pcre, 0, read_00024 + read_00024_ptr, read_00024_len - read_00024_ptr, &read_00024_00000_match);
            if (rc > 0) {
                read_00024_ptr += read_00024_00000_match.match_end - read_00024_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00024_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00025_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00025_00000_match;
        pcre *read_00025_00000_pcre = init_regex(read_00025_00000_regex);
        if (read_00025_00000_pcre != NULL) {
            int rc = regex_match(read_00025_00000_pcre, 0, read_00025 + read_00025_ptr, read_00025_len - read_00025_ptr, &read_00025_00000_match);
            if (rc > 0) {
                read_00025_ptr += read_00025_00000_match.match_end - read_00025_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00025_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00026_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00026_00000_match;
        pcre *read_00026_00000_pcre = init_regex(read_00026_00000_regex);
        if (read_00026_00000_pcre != NULL) {
            int rc = regex_match(read_00026_00000_pcre, 0, read_00026 + read_00026_ptr, read_00026_len - read_00026_ptr, &read_00026_00000_match);
            if (rc > 0) {
                read_00026_ptr += read_00026_00000_match.match_end - read_00026_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00026_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00027_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00027_00000_match;
        pcre *read_00027_00000_pcre = init_regex(read_00027_00000_regex);
        if (read_00027_00000_pcre != NULL) {
            int rc = regex_match(read_00027_00000_pcre, 0, read_00027 + read_00027_ptr, read_00027_len - read_00027_ptr, &read_00027_00000_match);
            if (rc > 0) {
                read_00027_ptr += read_00027_00000_match.match_end - read_00027_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00027_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . .     |

*/
        static char read_00028_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00028_00000_match;
        pcre *read_00028_00000_pcre = init_regex(read_00028_00000_regex);
        if (read_00028_00000_pcre != NULL) {
            int rc = regex_match(read_00028_00000_pcre, 0, read_00028 + read_00028_ptr, read_00028_len - read_00028_ptr, &read_00028_00000_match);
            if (rc > 0) {
                read_00028_ptr += read_00028_00000_match.match_end - read_00028_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00028_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |

*/
        static char read_00029_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00029_00000_match;
        pcre *read_00029_00000_pcre = init_regex(read_00029_00000_regex);
        if (read_00029_00000_pcre != NULL) {
            int rc = regex_match(read_00029_00000_pcre, 0, read_00029 + read_00029_ptr, read_00029_len - read_00029_ptr, &read_00029_00000_match);
            if (rc > 0) {
                read_00029_ptr += read_00029_00000_match.match_end - read_00029_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00029_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           _______|

*/
        static char read_00030_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00030_00000_match;
        pcre *read_00030_00000_pcre = init_regex(read_00030_00000_regex);
        if (read_00030_00000_pcre != NULL) {
            int rc = regex_match(read_00030_00000_pcre, 0, read_00030 + read_00030_ptr, read_00030_len - read_00030_ptr, &read_00030_00000_match);
            if (rc > 0) {
                read_00030_ptr += read_00030_00000_match.match_end - read_00030_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00030_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00031_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00031_00000_match;
        pcre *read_00031_00000_pcre = init_regex(read_00031_00000_regex);
        if (read_00031_00000_pcre != NULL) {
            int rc = regex_match(read_00031_00000_pcre, 0, read_00031 + read_00031_ptr, read_00031_len - read_00031_ptr, &read_00031_00000_match);
            if (rc > 0) {
                read_00031_ptr += read_00031_00000_match.match_end - read_00031_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00031_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00032_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00032_00000_match;
        pcre *read_00032_00000_pcre = init_regex(read_00032_00000_regex);
        if (read_00032_00000_pcre != NULL) {
            int rc = regex_match(read_00032_00000_pcre, 0, read_00032 + read_00032_ptr, read_00032_len - read_00032_ptr, &read_00032_00000_match);
            if (rc > 0) {
                read_00032_ptr += read_00032_00000_match.match_end - read_00032_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00032_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00033_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00033_00000_match;
        pcre *read_00033_00000_pcre = init_regex(read_00033_00000_regex);
        if (read_00033_00000_pcre != NULL) {
            int rc = regex_match(read_00033_00000_pcre, 0, read_00033 + read_00033_ptr, read_00033_len - read_00033_ptr, &read_00033_00000_match);
            if (rc > 0) {
                read_00033_ptr += read_00033_00000_match.match_end - read_00033_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00033_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
Incorrect: .*

*/
        static char read_00034_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00034_00000_match;
        pcre *read_00034_00000_pcre = init_regex(read_00034_00000_regex);
        if (read_00034_00000_pcre != NULL) {
            int rc = regex_match(read_00034_00000_pcre, 0, read_00034 + read_00034_ptr, read_00034_len - read_00034_ptr, &read_00034_00000_match);
            if (rc > 0) {
                read_00034_ptr += read_00034_00000_match.match_end - read_00034_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00034_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00034);
        if (read_00034_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00002_00000[] = 
            "\x3a";
        static unsigned int write_00002_00000_len = 1;
        unsigned char *write_00002 = NULL;
        unsigned int write_00002_len = 0;
        write_00002 = append_buf(write_00002, &write_00002_len, write_00002_00000, write_00002_00000_len);
        if (write_00002_len > 0) {
            transmit_all(1, write_00002, write_00002_len);
        }
        free(write_00002);
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
        /* read match pcre:
           --------

*/
        static char read_00035_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00035_00000_match;
        pcre *read_00035_00000_pcre = init_regex(read_00035_00000_regex);
        if (read_00035_00000_pcre != NULL) {
            int rc = regex_match(read_00035_00000_pcre, 0, read_00035 + read_00035_ptr, read_00035_len - read_00035_ptr, &read_00035_00000_match);
            if (rc > 0) {
                read_00035_ptr += read_00035_00000_match.match_end - read_00035_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00035_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |      |

*/
        static char read_00036_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00036_00000_match;
        pcre *read_00036_00000_pcre = init_regex(read_00036_00000_regex);
        if (read_00036_00000_pcre != NULL) {
            int rc = regex_match(read_00036_00000_pcre, 0, read_00036 + read_00036_ptr, read_00036_len - read_00036_ptr, &read_00036_00000_match);
            if (rc > 0) {
                read_00036_ptr += read_00036_00000_match.match_end - read_00036_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00036_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00037_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00037_00000_match;
        pcre *read_00037_00000_pcre = init_regex(read_00037_00000_regex);
        if (read_00037_00000_pcre != NULL) {
            int rc = regex_match(read_00037_00000_pcre, 0, read_00037 + read_00037_ptr, read_00037_len - read_00037_ptr, &read_00037_00000_match);
            if (rc > 0) {
                read_00037_ptr += read_00037_00000_match.match_end - read_00037_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00037_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00038_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00038_00000_match;
        pcre *read_00038_00000_pcre = init_regex(read_00038_00000_regex);
        if (read_00038_00000_pcre != NULL) {
            int rc = regex_match(read_00038_00000_pcre, 0, read_00038 + read_00038_ptr, read_00038_len - read_00038_ptr, &read_00038_00000_match);
            if (rc > 0) {
                read_00038_ptr += read_00038_00000_match.match_end - read_00038_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00038_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00038);
        if (read_00038_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           .      |

*/
        static char read_00039_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00039_00000_match;
        pcre *read_00039_00000_pcre = init_regex(read_00039_00000_regex);
        if (read_00039_00000_pcre != NULL) {
            int rc = regex_match(read_00039_00000_pcre, 0, read_00039 + read_00039_ptr, read_00039_len - read_00039_ptr, &read_00039_00000_match);
            if (rc > 0) {
                read_00039_ptr += read_00039_00000_match.match_end - read_00039_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00039_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00039);
        if (read_00039_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           . .     |

*/
        static char read_00040_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00040_00000_match;
        pcre *read_00040_00000_pcre = init_regex(read_00040_00000_regex);
        if (read_00040_00000_pcre != NULL) {
            int rc = regex_match(read_00040_00000_pcre, 0, read_00040 + read_00040_ptr, read_00040_len - read_00040_ptr, &read_00040_00000_match);
            if (rc > 0) {
                read_00040_ptr += read_00040_00000_match.match_end - read_00040_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00040_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |

*/
        static char read_00041_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00041_00000_match;
        pcre *read_00041_00000_pcre = init_regex(read_00041_00000_regex);
        if (read_00041_00000_pcre != NULL) {
            int rc = regex_match(read_00041_00000_pcre, 0, read_00041 + read_00041_ptr, read_00041_len - read_00041_ptr, &read_00041_00000_match);
            if (rc > 0) {
                read_00041_ptr += read_00041_00000_match.match_end - read_00041_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00041_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           _______|

*/
        static char read_00042_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00042_00000_match;
        pcre *read_00042_00000_pcre = init_regex(read_00042_00000_regex);
        if (read_00042_00000_pcre != NULL) {
            int rc = regex_match(read_00042_00000_pcre, 0, read_00042 + read_00042_ptr, read_00042_len - read_00042_ptr, &read_00042_00000_match);
            if (rc > 0) {
                read_00042_ptr += read_00042_00000_match.match_end - read_00042_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00042_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00043_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00043_00000_match;
        pcre *read_00043_00000_pcre = init_regex(read_00043_00000_regex);
        if (read_00043_00000_pcre != NULL) {
            int rc = regex_match(read_00043_00000_pcre, 0, read_00043 + read_00043_ptr, read_00043_len - read_00043_ptr, &read_00043_00000_match);
            if (rc > 0) {
                read_00043_ptr += read_00043_00000_match.match_end - read_00043_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00043_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00044_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00044_00000_match;
        pcre *read_00044_00000_pcre = init_regex(read_00044_00000_regex);
        if (read_00044_00000_pcre != NULL) {
            int rc = regex_match(read_00044_00000_pcre, 0, read_00044 + read_00044_ptr, read_00044_len - read_00044_ptr, &read_00044_00000_match);
            if (rc > 0) {
                read_00044_ptr += read_00044_00000_match.match_end - read_00044_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00044_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00045_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00045_00000_match;
        pcre *read_00045_00000_pcre = init_regex(read_00045_00000_regex);
        if (read_00045_00000_pcre != NULL) {
            int rc = regex_match(read_00045_00000_pcre, 0, read_00045 + read_00045_ptr, read_00045_len - read_00045_ptr, &read_00045_00000_match);
            if (rc > 0) {
                read_00045_ptr += read_00045_00000_match.match_end - read_00045_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00045_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
Incorrect: .*

*/
        static char read_00046_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00046_00000_match;
        pcre *read_00046_00000_pcre = init_regex(read_00046_00000_regex);
        if (read_00046_00000_pcre != NULL) {
            int rc = regex_match(read_00046_00000_pcre, 0, read_00046 + read_00046_ptr, read_00046_len - read_00046_ptr, &read_00046_00000_match);
            if (rc > 0) {
                read_00046_ptr += read_00046_00000_match.match_end - read_00046_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00046_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00046);
        if (read_00046_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00003_00000[] = 
            "\x3a";
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
        /* read match pcre:
           --------

*/
        static char read_00047_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00047_00000_match;
        pcre *read_00047_00000_pcre = init_regex(read_00047_00000_regex);
        if (read_00047_00000_pcre != NULL) {
            int rc = regex_match(read_00047_00000_pcre, 0, read_00047 + read_00047_ptr, read_00047_len - read_00047_ptr, &read_00047_00000_match);
            if (rc > 0) {
                read_00047_ptr += read_00047_00000_match.match_end - read_00047_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00047_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |      |

*/
        static char read_00048_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00048_00000_match;
        pcre *read_00048_00000_pcre = init_regex(read_00048_00000_regex);
        if (read_00048_00000_pcre != NULL) {
            int rc = regex_match(read_00048_00000_pcre, 0, read_00048 + read_00048_ptr, read_00048_len - read_00048_ptr, &read_00048_00000_match);
            if (rc > 0) {
                read_00048_ptr += read_00048_00000_match.match_end - read_00048_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00048_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00049_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00049_00000_match;
        pcre *read_00049_00000_pcre = init_regex(read_00049_00000_regex);
        if (read_00049_00000_pcre != NULL) {
            int rc = regex_match(read_00049_00000_pcre, 0, read_00049 + read_00049_ptr, read_00049_len - read_00049_ptr, &read_00049_00000_match);
            if (rc > 0) {
                read_00049_ptr += read_00049_00000_match.match_end - read_00049_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00049_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00050_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00050_00000_match;
        pcre *read_00050_00000_pcre = init_regex(read_00050_00000_regex);
        if (read_00050_00000_pcre != NULL) {
            int rc = regex_match(read_00050_00000_pcre, 0, read_00050 + read_00050_ptr, read_00050_len - read_00050_ptr, &read_00050_00000_match);
            if (rc > 0) {
                read_00050_ptr += read_00050_00000_match.match_end - read_00050_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00050_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00051_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00051_00000_match;
        pcre *read_00051_00000_pcre = init_regex(read_00051_00000_regex);
        if (read_00051_00000_pcre != NULL) {
            int rc = regex_match(read_00051_00000_pcre, 0, read_00051 + read_00051_ptr, read_00051_len - read_00051_ptr, &read_00051_00000_match);
            if (rc > 0) {
                read_00051_ptr += read_00051_00000_match.match_end - read_00051_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00051_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . .     |

*/
        static char read_00052_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00052_00000_match;
        pcre *read_00052_00000_pcre = init_regex(read_00052_00000_regex);
        if (read_00052_00000_pcre != NULL) {
            int rc = regex_match(read_00052_00000_pcre, 0, read_00052 + read_00052_ptr, read_00052_len - read_00052_ptr, &read_00052_00000_match);
            if (rc > 0) {
                read_00052_ptr += read_00052_00000_match.match_end - read_00052_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00052_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00052);
        if (read_00052_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           |

*/
        static char read_00053_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00053_00000_match;
        pcre *read_00053_00000_pcre = init_regex(read_00053_00000_regex);
        if (read_00053_00000_pcre != NULL) {
            int rc = regex_match(read_00053_00000_pcre, 0, read_00053 + read_00053_ptr, read_00053_len - read_00053_ptr, &read_00053_00000_match);
            if (rc > 0) {
                read_00053_ptr += read_00053_00000_match.match_end - read_00053_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00053_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00053);
        if (read_00053_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           _______|

*/
        static char read_00054_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00054_00000_match;
        pcre *read_00054_00000_pcre = init_regex(read_00054_00000_regex);
        if (read_00054_00000_pcre != NULL) {
            int rc = regex_match(read_00054_00000_pcre, 0, read_00054 + read_00054_ptr, read_00054_len - read_00054_ptr, &read_00054_00000_match);
            if (rc > 0) {
                read_00054_ptr += read_00054_00000_match.match_end - read_00054_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00054_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00055_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00055_00000_match;
        pcre *read_00055_00000_pcre = init_regex(read_00055_00000_regex);
        if (read_00055_00000_pcre != NULL) {
            int rc = regex_match(read_00055_00000_pcre, 0, read_00055 + read_00055_ptr, read_00055_len - read_00055_ptr, &read_00055_00000_match);
            if (rc > 0) {
                read_00055_ptr += read_00055_00000_match.match_end - read_00055_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00055_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00056_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00056_00000_match;
        pcre *read_00056_00000_pcre = init_regex(read_00056_00000_regex);
        if (read_00056_00000_pcre != NULL) {
            int rc = regex_match(read_00056_00000_pcre, 0, read_00056 + read_00056_ptr, read_00056_len - read_00056_ptr, &read_00056_00000_match);
            if (rc > 0) {
                read_00056_ptr += read_00056_00000_match.match_end - read_00056_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00056_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00057_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00057_00000_match;
        pcre *read_00057_00000_pcre = init_regex(read_00057_00000_regex);
        if (read_00057_00000_pcre != NULL) {
            int rc = regex_match(read_00057_00000_pcre, 0, read_00057 + read_00057_ptr, read_00057_len - read_00057_ptr, &read_00057_00000_match);
            if (rc > 0) {
                read_00057_ptr += read_00057_00000_match.match_end - read_00057_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00057_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
Incorrect: .*

*/
        static char read_00058_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00058_00000_match;
        pcre *read_00058_00000_pcre = init_regex(read_00058_00000_regex);
        if (read_00058_00000_pcre != NULL) {
            int rc = regex_match(read_00058_00000_pcre, 0, read_00058 + read_00058_ptr, read_00058_len - read_00058_ptr, &read_00058_00000_match);
            if (rc > 0) {
                read_00058_ptr += read_00058_00000_match.match_end - read_00058_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00058_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00058);
        if (read_00058_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00004_00000[] = 
            "\x3a";
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
        /* read match pcre:
           --------

*/
        static char read_00059_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00059_00000_match;
        pcre *read_00059_00000_pcre = init_regex(read_00059_00000_regex);
        if (read_00059_00000_pcre != NULL) {
            int rc = regex_match(read_00059_00000_pcre, 0, read_00059 + read_00059_ptr, read_00059_len - read_00059_ptr, &read_00059_00000_match);
            if (rc > 0) {
                read_00059_ptr += read_00059_00000_match.match_end - read_00059_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00059_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |      |

*/
        static char read_00060_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00060_00000_match;
        pcre *read_00060_00000_pcre = init_regex(read_00060_00000_regex);
        if (read_00060_00000_pcre != NULL) {
            int rc = regex_match(read_00060_00000_pcre, 0, read_00060 + read_00060_ptr, read_00060_len - read_00060_ptr, &read_00060_00000_match);
            if (rc > 0) {
                read_00060_ptr += read_00060_00000_match.match_end - read_00060_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00060_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00061_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00061_00000_match;
        pcre *read_00061_00000_pcre = init_regex(read_00061_00000_regex);
        if (read_00061_00000_pcre != NULL) {
            int rc = regex_match(read_00061_00000_pcre, 0, read_00061 + read_00061_ptr, read_00061_len - read_00061_ptr, &read_00061_00000_match);
            if (rc > 0) {
                read_00061_ptr += read_00061_00000_match.match_end - read_00061_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00061_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00062_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00062_00000_match;
        pcre *read_00062_00000_pcre = init_regex(read_00062_00000_regex);
        if (read_00062_00000_pcre != NULL) {
            int rc = regex_match(read_00062_00000_pcre, 0, read_00062 + read_00062_ptr, read_00062_len - read_00062_ptr, &read_00062_00000_match);
            if (rc > 0) {
                read_00062_ptr += read_00062_00000_match.match_end - read_00062_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00062_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00063_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00063_00000_match;
        pcre *read_00063_00000_pcre = init_regex(read_00063_00000_regex);
        if (read_00063_00000_pcre != NULL) {
            int rc = regex_match(read_00063_00000_pcre, 0, read_00063 + read_00063_ptr, read_00063_len - read_00063_ptr, &read_00063_00000_match);
            if (rc > 0) {
                read_00063_ptr += read_00063_00000_match.match_end - read_00063_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00063_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . .     |

*/
        static char read_00064_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00064_00000_match;
        pcre *read_00064_00000_pcre = init_regex(read_00064_00000_regex);
        if (read_00064_00000_pcre != NULL) {
            int rc = regex_match(read_00064_00000_pcre, 0, read_00064 + read_00064_ptr, read_00064_len - read_00064_ptr, &read_00064_00000_match);
            if (rc > 0) {
                read_00064_ptr += read_00064_00000_match.match_end - read_00064_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00064_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |

*/
        static char read_00065_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00065_00000_match;
        pcre *read_00065_00000_pcre = init_regex(read_00065_00000_regex);
        if (read_00065_00000_pcre != NULL) {
            int rc = regex_match(read_00065_00000_pcre, 0, read_00065 + read_00065_ptr, read_00065_len - read_00065_ptr, &read_00065_00000_match);
            if (rc > 0) {
                read_00065_ptr += read_00065_00000_match.match_end - read_00065_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00065_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00065);
        if (read_00065_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           _______|

*/
        static char read_00066_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00066_00000_match;
        pcre *read_00066_00000_pcre = init_regex(read_00066_00000_regex);
        if (read_00066_00000_pcre != NULL) {
            int rc = regex_match(read_00066_00000_pcre, 0, read_00066 + read_00066_ptr, read_00066_len - read_00066_ptr, &read_00066_00000_match);
            if (rc > 0) {
                read_00066_ptr += read_00066_00000_match.match_end - read_00066_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00066_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00066);
        if (read_00066_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:


*/
        static char read_00067_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00067_00000_match;
        pcre *read_00067_00000_pcre = init_regex(read_00067_00000_regex);
        if (read_00067_00000_pcre != NULL) {
            int rc = regex_match(read_00067_00000_pcre, 0, read_00067 + read_00067_ptr, read_00067_len - read_00067_ptr, &read_00067_00000_match);
            if (rc > 0) {
                read_00067_ptr += read_00067_00000_match.match_end - read_00067_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00067_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00068_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00068_00000_match;
        pcre *read_00068_00000_pcre = init_regex(read_00068_00000_regex);
        if (read_00068_00000_pcre != NULL) {
            int rc = regex_match(read_00068_00000_pcre, 0, read_00068 + read_00068_ptr, read_00068_len - read_00068_ptr, &read_00068_00000_match);
            if (rc > 0) {
                read_00068_ptr += read_00068_00000_match.match_end - read_00068_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00068_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00069_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00069_00000_match;
        pcre *read_00069_00000_pcre = init_regex(read_00069_00000_regex);
        if (read_00069_00000_pcre != NULL) {
            int rc = regex_match(read_00069_00000_pcre, 0, read_00069 + read_00069_ptr, read_00069_len - read_00069_ptr, &read_00069_00000_match);
            if (rc > 0) {
                read_00069_ptr += read_00069_00000_match.match_end - read_00069_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00069_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
Incorrect: .*

*/
        static char read_00070_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00070_00000_match;
        pcre *read_00070_00000_pcre = init_regex(read_00070_00000_regex);
        if (read_00070_00000_pcre != NULL) {
            int rc = regex_match(read_00070_00000_pcre, 0, read_00070 + read_00070_ptr, read_00070_len - read_00070_ptr, &read_00070_00000_match);
            if (rc > 0) {
                read_00070_ptr += read_00070_00000_match.match_end - read_00070_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00070_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00070);
        if (read_00070_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00005_00000[] = 
            "\x3a";
        static unsigned int write_00005_00000_len = 1;
        unsigned char *write_00005 = NULL;
        unsigned int write_00005_len = 0;
        write_00005 = append_buf(write_00005, &write_00005_len, write_00005_00000, write_00005_00000_len);
        if (write_00005_len > 0) {
            transmit_all(1, write_00005, write_00005_len);
        }
        free(write_00005);
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
        /* read match pcre:
           --------

*/
        static char read_00071_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00071_00000_match;
        pcre *read_00071_00000_pcre = init_regex(read_00071_00000_regex);
        if (read_00071_00000_pcre != NULL) {
            int rc = regex_match(read_00071_00000_pcre, 0, read_00071 + read_00071_ptr, read_00071_len - read_00071_ptr, &read_00071_00000_match);
            if (rc > 0) {
                read_00071_ptr += read_00071_00000_match.match_end - read_00071_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00071_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |      |

*/
        static char read_00072_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00072_00000_match;
        pcre *read_00072_00000_pcre = init_regex(read_00072_00000_regex);
        if (read_00072_00000_pcre != NULL) {
            int rc = regex_match(read_00072_00000_pcre, 0, read_00072 + read_00072_ptr, read_00072_len - read_00072_ptr, &read_00072_00000_match);
            if (rc > 0) {
                read_00072_ptr += read_00072_00000_match.match_end - read_00072_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00072_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00073_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00073_00000_match;
        pcre *read_00073_00000_pcre = init_regex(read_00073_00000_regex);
        if (read_00073_00000_pcre != NULL) {
            int rc = regex_match(read_00073_00000_pcre, 0, read_00073 + read_00073_ptr, read_00073_len - read_00073_ptr, &read_00073_00000_match);
            if (rc > 0) {
                read_00073_ptr += read_00073_00000_match.match_end - read_00073_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00073_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00074_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00074_00000_match;
        pcre *read_00074_00000_pcre = init_regex(read_00074_00000_regex);
        if (read_00074_00000_pcre != NULL) {
            int rc = regex_match(read_00074_00000_pcre, 0, read_00074 + read_00074_ptr, read_00074_len - read_00074_ptr, &read_00074_00000_match);
            if (rc > 0) {
                read_00074_ptr += read_00074_00000_match.match_end - read_00074_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00074_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00075_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00075_00000_match;
        pcre *read_00075_00000_pcre = init_regex(read_00075_00000_regex);
        if (read_00075_00000_pcre != NULL) {
            int rc = regex_match(read_00075_00000_pcre, 0, read_00075 + read_00075_ptr, read_00075_len - read_00075_ptr, &read_00075_00000_match);
            if (rc > 0) {
                read_00075_ptr += read_00075_00000_match.match_end - read_00075_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00075_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . .     |

*/
        static char read_00076_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00076_00000_match;
        pcre *read_00076_00000_pcre = init_regex(read_00076_00000_regex);
        if (read_00076_00000_pcre != NULL) {
            int rc = regex_match(read_00076_00000_pcre, 0, read_00076 + read_00076_ptr, read_00076_len - read_00076_ptr, &read_00076_00000_match);
            if (rc > 0) {
                read_00076_ptr += read_00076_00000_match.match_end - read_00076_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00076_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |

*/
        static char read_00077_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00077_00000_match;
        pcre *read_00077_00000_pcre = init_regex(read_00077_00000_regex);
        if (read_00077_00000_pcre != NULL) {
            int rc = regex_match(read_00077_00000_pcre, 0, read_00077 + read_00077_ptr, read_00077_len - read_00077_ptr, &read_00077_00000_match);
            if (rc > 0) {
                read_00077_ptr += read_00077_00000_match.match_end - read_00077_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00077_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           _______|

*/
        static char read_00078_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00078_00000_match;
        pcre *read_00078_00000_pcre = init_regex(read_00078_00000_regex);
        if (read_00078_00000_pcre != NULL) {
            int rc = regex_match(read_00078_00000_pcre, 0, read_00078 + read_00078_ptr, read_00078_len - read_00078_ptr, &read_00078_00000_match);
            if (rc > 0) {
                read_00078_ptr += read_00078_00000_match.match_end - read_00078_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00078_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:


*/
        static char read_00079_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00079_00000_match;
        pcre *read_00079_00000_pcre = init_regex(read_00079_00000_regex);
        if (read_00079_00000_pcre != NULL) {
            int rc = regex_match(read_00079_00000_pcre, 0, read_00079 + read_00079_ptr, read_00079_len - read_00079_ptr, &read_00079_00000_match);
            if (rc > 0) {
                read_00079_ptr += read_00079_00000_match.match_end - read_00079_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00079_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00079);
        if (read_00079_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:


*/
        static char read_00080_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00080_00000_match;
        pcre *read_00080_00000_pcre = init_regex(read_00080_00000_regex);
        if (read_00080_00000_pcre != NULL) {
            int rc = regex_match(read_00080_00000_pcre, 0, read_00080 + read_00080_ptr, read_00080_len - read_00080_ptr, &read_00080_00000_match);
            if (rc > 0) {
                read_00080_ptr += read_00080_00000_match.match_end - read_00080_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00080_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00081_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00081_00000_match;
        pcre *read_00081_00000_pcre = init_regex(read_00081_00000_regex);
        if (read_00081_00000_pcre != NULL) {
            int rc = regex_match(read_00081_00000_pcre, 0, read_00081 + read_00081_ptr, read_00081_len - read_00081_ptr, &read_00081_00000_match);
            if (rc > 0) {
                read_00081_ptr += read_00081_00000_match.match_end - read_00081_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00081_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
Incorrect: .*

*/
        static char read_00082_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00082_00000_match;
        pcre *read_00082_00000_pcre = init_regex(read_00082_00000_regex);
        if (read_00082_00000_pcre != NULL) {
            int rc = regex_match(read_00082_00000_pcre, 0, read_00082 + read_00082_ptr, read_00082_len - read_00082_ptr, &read_00082_00000_match);
            if (rc > 0) {
                read_00082_ptr += read_00082_00000_match.match_end - read_00082_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00082_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00082);
        if (read_00082_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00006_00000[] = 
            "\x3a";
        static unsigned int write_00006_00000_len = 1;
        unsigned char *write_00006 = NULL;
        unsigned int write_00006_len = 0;
        write_00006 = append_buf(write_00006, &write_00006_len, write_00006_00000, write_00006_00000_len);
        if (write_00006_len > 0) {
            transmit_all(1, write_00006, write_00006_len);
        }
        free(write_00006);
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
        /* read match pcre:
           --------

*/
        static char read_00083_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00083_00000_match;
        pcre *read_00083_00000_pcre = init_regex(read_00083_00000_regex);
        if (read_00083_00000_pcre != NULL) {
            int rc = regex_match(read_00083_00000_pcre, 0, read_00083 + read_00083_ptr, read_00083_len - read_00083_ptr, &read_00083_00000_match);
            if (rc > 0) {
                read_00083_ptr += read_00083_00000_match.match_end - read_00083_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00083_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |      |

*/
        static char read_00084_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00084_00000_match;
        pcre *read_00084_00000_pcre = init_regex(read_00084_00000_regex);
        if (read_00084_00000_pcre != NULL) {
            int rc = regex_match(read_00084_00000_pcre, 0, read_00084 + read_00084_ptr, read_00084_len - read_00084_ptr, &read_00084_00000_match);
            if (rc > 0) {
                read_00084_ptr += read_00084_00000_match.match_end - read_00084_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00084_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00085_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00085_00000_match;
        pcre *read_00085_00000_pcre = init_regex(read_00085_00000_regex);
        if (read_00085_00000_pcre != NULL) {
            int rc = regex_match(read_00085_00000_pcre, 0, read_00085 + read_00085_ptr, read_00085_len - read_00085_ptr, &read_00085_00000_match);
            if (rc > 0) {
                read_00085_ptr += read_00085_00000_match.match_end - read_00085_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00085_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           ...     |

*/
        static char read_00086_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00086_00000_match;
        pcre *read_00086_00000_pcre = init_regex(read_00086_00000_regex);
        if (read_00086_00000_pcre != NULL) {
            int rc = regex_match(read_00086_00000_pcre, 0, read_00086 + read_00086_ptr, read_00086_len - read_00086_ptr, &read_00086_00000_match);
            if (rc > 0) {
                read_00086_ptr += read_00086_00000_match.match_end - read_00086_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00086_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           .      |

*/
        static char read_00087_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00087_00000_match;
        pcre *read_00087_00000_pcre = init_regex(read_00087_00000_regex);
        if (read_00087_00000_pcre != NULL) {
            int rc = regex_match(read_00087_00000_pcre, 0, read_00087 + read_00087_ptr, read_00087_len - read_00087_ptr, &read_00087_00000_match);
            if (rc > 0) {
                read_00087_ptr += read_00087_00000_match.match_end - read_00087_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00087_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00087);
        if (read_00087_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           . .     |

*/
        static char read_00088_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00088_00000_match;
        pcre *read_00088_00000_pcre = init_regex(read_00088_00000_regex);
        if (read_00088_00000_pcre != NULL) {
            int rc = regex_match(read_00088_00000_pcre, 0, read_00088 + read_00088_ptr, read_00088_len - read_00088_ptr, &read_00088_00000_match);
            if (rc > 0) {
                read_00088_ptr += read_00088_00000_match.match_end - read_00088_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00088_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
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
        /* read match pcre:
           |

*/
        static char read_00089_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00089_00000_match;
        pcre *read_00089_00000_pcre = init_regex(read_00089_00000_regex);
        if (read_00089_00000_pcre != NULL) {
            int rc = regex_match(read_00089_00000_pcre, 0, read_00089 + read_00089_ptr, read_00089_len - read_00089_ptr, &read_00089_00000_match);
            if (rc > 0) {
                read_00089_ptr += read_00089_00000_match.match_end - read_00089_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00089_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00089);
        if (read_00089_ptr) {}  //silence unused variable warning if any
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
        /* read match pcre:
           _______|

*/
        static char read_00090_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00090_00000_match;
        pcre *read_00090_00000_pcre = init_regex(read_00090_00000_regex);
        if (read_00090_00000_pcre != NULL) {
            int rc = regex_match(read_00090_00000_pcre, 0, read_00090 + read_00090_ptr, read_00090_len - read_00090_ptr, &read_00090_00000_match);
            if (rc > 0) {
                read_00090_ptr += read_00090_00000_match.match_end - read_00090_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00090_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00090);
        if (read_00090_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00091;
        unsigned int read_00091_len;
        unsigned int read_00091_ptr = 0;
        //**** delimited read
        static unsigned char read_00091_delim[] = 
            "\x0a";
        read_00091 = NULL;
        read_00091_len = 0;
        int read_00091_res = delimited_read(0, &read_00091, &read_00091_len, read_00091_delim, 1);
        if (read_00091_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00091_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00091_00000_match;
        pcre *read_00091_00000_pcre = init_regex(read_00091_00000_regex);
        if (read_00091_00000_pcre != NULL) {
            int rc = regex_match(read_00091_00000_pcre, 0, read_00091 + read_00091_ptr, read_00091_len - read_00091_ptr, &read_00091_00000_match);
            if (rc > 0) {
                read_00091_ptr += read_00091_00000_match.match_end - read_00091_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00091_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00091);
        if (read_00091_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00092;
        unsigned int read_00092_len;
        unsigned int read_00092_ptr = 0;
        //**** delimited read
        static unsigned char read_00092_delim[] = 
            "\x0a";
        read_00092 = NULL;
        read_00092_len = 0;
        int read_00092_res = delimited_read(0, &read_00092, &read_00092_len, read_00092_delim, 1);
        if (read_00092_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00092_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00092_00000_match;
        pcre *read_00092_00000_pcre = init_regex(read_00092_00000_regex);
        if (read_00092_00000_pcre != NULL) {
            int rc = regex_match(read_00092_00000_pcre, 0, read_00092 + read_00092_ptr, read_00092_len - read_00092_ptr, &read_00092_00000_match);
            if (rc > 0) {
                read_00092_ptr += read_00092_00000_match.match_end - read_00092_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00092_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00092);
        if (read_00092_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00093;
        unsigned int read_00093_len;
        unsigned int read_00093_ptr = 0;
        //**** delimited read
        static unsigned char read_00093_delim[] = 
            "\x0a";
        read_00093 = NULL;
        read_00093_len = 0;
        int read_00093_res = delimited_read(0, &read_00093, &read_00093_len, read_00093_delim, 1);
        if (read_00093_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00093_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00093_00000_match;
        pcre *read_00093_00000_pcre = init_regex(read_00093_00000_regex);
        if (read_00093_00000_pcre != NULL) {
            int rc = regex_match(read_00093_00000_pcre, 0, read_00093 + read_00093_ptr, read_00093_len - read_00093_ptr, &read_00093_00000_match);
            if (rc > 0) {
                read_00093_ptr += read_00093_00000_match.match_end - read_00093_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00093_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00093);
        if (read_00093_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00094;
        unsigned int read_00094_len;
        unsigned int read_00094_ptr = 0;
        //**** delimited read
        static unsigned char read_00094_delim[] = 
            "\x0a";
        read_00094 = NULL;
        read_00094_len = 0;
        int read_00094_res = delimited_read(0, &read_00094, &read_00094_len, read_00094_delim, 1);
        if (read_00094_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00094_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00094_00000_match;
        pcre *read_00094_00000_pcre = init_regex(read_00094_00000_regex);
        if (read_00094_00000_pcre != NULL) {
            int rc = regex_match(read_00094_00000_pcre, 0, read_00094 + read_00094_ptr, read_00094_len - read_00094_ptr, &read_00094_00000_match);
            if (rc > 0) {
                read_00094_ptr += read_00094_00000_match.match_end - read_00094_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00094_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00094);
        if (read_00094_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00007_00000[] = 
            "\x3a";
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
        unsigned char *read_00095;
        unsigned int read_00095_len;
        unsigned int read_00095_ptr = 0;
        //**** delimited read
        static unsigned char read_00095_delim[] = 
            "\x0a";
        read_00095 = NULL;
        read_00095_len = 0;
        int read_00095_res = delimited_read(0, &read_00095, &read_00095_len, read_00095_delim, 1);
        if (read_00095_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00095_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00095_00000_match;
        pcre *read_00095_00000_pcre = init_regex(read_00095_00000_regex);
        if (read_00095_00000_pcre != NULL) {
            int rc = regex_match(read_00095_00000_pcre, 0, read_00095 + read_00095_ptr, read_00095_len - read_00095_ptr, &read_00095_00000_match);
            if (rc > 0) {
                read_00095_ptr += read_00095_00000_match.match_end - read_00095_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00095_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00095);
        if (read_00095_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00096;
        unsigned int read_00096_len;
        unsigned int read_00096_ptr = 0;
        //**** delimited read
        static unsigned char read_00096_delim[] = 
            "\x0a";
        read_00096 = NULL;
        read_00096_len = 0;
        int read_00096_res = delimited_read(0, &read_00096, &read_00096_len, read_00096_delim, 1);
        if (read_00096_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00096_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00096_00000_match;
        pcre *read_00096_00000_pcre = init_regex(read_00096_00000_regex);
        if (read_00096_00000_pcre != NULL) {
            int rc = regex_match(read_00096_00000_pcre, 0, read_00096 + read_00096_ptr, read_00096_len - read_00096_ptr, &read_00096_00000_match);
            if (rc > 0) {
                read_00096_ptr += read_00096_00000_match.match_end - read_00096_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00096_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00096);
        if (read_00096_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00097;
        unsigned int read_00097_len;
        unsigned int read_00097_ptr = 0;
        //**** delimited read
        static unsigned char read_00097_delim[] = 
            "\x0a";
        read_00097 = NULL;
        read_00097_len = 0;
        int read_00097_res = delimited_read(0, &read_00097, &read_00097_len, read_00097_delim, 1);
        if (read_00097_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00097_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00097_00000_match;
        pcre *read_00097_00000_pcre = init_regex(read_00097_00000_regex);
        if (read_00097_00000_pcre != NULL) {
            int rc = regex_match(read_00097_00000_pcre, 0, read_00097 + read_00097_ptr, read_00097_len - read_00097_ptr, &read_00097_00000_match);
            if (rc > 0) {
                read_00097_ptr += read_00097_00000_match.match_end - read_00097_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00097_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00097);
        if (read_00097_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00098;
        unsigned int read_00098_len;
        unsigned int read_00098_ptr = 0;
        //**** delimited read
        static unsigned char read_00098_delim[] = 
            "\x0a";
        read_00098 = NULL;
        read_00098_len = 0;
        int read_00098_res = delimited_read(0, &read_00098, &read_00098_len, read_00098_delim, 1);
        if (read_00098_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00098_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00098_00000_match;
        pcre *read_00098_00000_pcre = init_regex(read_00098_00000_regex);
        if (read_00098_00000_pcre != NULL) {
            int rc = regex_match(read_00098_00000_pcre, 0, read_00098 + read_00098_ptr, read_00098_len - read_00098_ptr, &read_00098_00000_match);
            if (rc > 0) {
                read_00098_ptr += read_00098_00000_match.match_end - read_00098_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00098_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00098);
        if (read_00098_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00099;
        unsigned int read_00099_len;
        unsigned int read_00099_ptr = 0;
        //**** delimited read
        static unsigned char read_00099_delim[] = 
            "\x0a";
        read_00099 = NULL;
        read_00099_len = 0;
        int read_00099_res = delimited_read(0, &read_00099, &read_00099_len, read_00099_delim, 1);
        if (read_00099_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00099_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00099_00000_match;
        pcre *read_00099_00000_pcre = init_regex(read_00099_00000_regex);
        if (read_00099_00000_pcre != NULL) {
            int rc = regex_match(read_00099_00000_pcre, 0, read_00099 + read_00099_ptr, read_00099_len - read_00099_ptr, &read_00099_00000_match);
            if (rc > 0) {
                read_00099_ptr += read_00099_00000_match.match_end - read_00099_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00099_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00099);
        if (read_00099_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00100;
        unsigned int read_00100_len;
        unsigned int read_00100_ptr = 0;
        //**** delimited read
        static unsigned char read_00100_delim[] = 
            "\x0a";
        read_00100 = NULL;
        read_00100_len = 0;
        int read_00100_res = delimited_read(0, &read_00100, &read_00100_len, read_00100_delim, 1);
        if (read_00100_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00100_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00100_00000_match;
        pcre *read_00100_00000_pcre = init_regex(read_00100_00000_regex);
        if (read_00100_00000_pcre != NULL) {
            int rc = regex_match(read_00100_00000_pcre, 0, read_00100 + read_00100_ptr, read_00100_len - read_00100_ptr, &read_00100_00000_match);
            if (rc > 0) {
                read_00100_ptr += read_00100_00000_match.match_end - read_00100_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00100_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00100);
        if (read_00100_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00101;
        unsigned int read_00101_len;
        unsigned int read_00101_ptr = 0;
        //**** delimited read
        static unsigned char read_00101_delim[] = 
            "\x0a";
        read_00101 = NULL;
        read_00101_len = 0;
        int read_00101_res = delimited_read(0, &read_00101, &read_00101_len, read_00101_delim, 1);
        if (read_00101_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00101_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00101_00000_match;
        pcre *read_00101_00000_pcre = init_regex(read_00101_00000_regex);
        if (read_00101_00000_pcre != NULL) {
            int rc = regex_match(read_00101_00000_pcre, 0, read_00101 + read_00101_ptr, read_00101_len - read_00101_ptr, &read_00101_00000_match);
            if (rc > 0) {
                read_00101_ptr += read_00101_00000_match.match_end - read_00101_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00101_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00101);
        if (read_00101_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00102;
        unsigned int read_00102_len;
        unsigned int read_00102_ptr = 0;
        //**** delimited read
        static unsigned char read_00102_delim[] = 
            "\x0a";
        read_00102 = NULL;
        read_00102_len = 0;
        int read_00102_res = delimited_read(0, &read_00102, &read_00102_len, read_00102_delim, 1);
        if (read_00102_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00102_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00102_00000_match;
        pcre *read_00102_00000_pcre = init_regex(read_00102_00000_regex);
        if (read_00102_00000_pcre != NULL) {
            int rc = regex_match(read_00102_00000_pcre, 0, read_00102 + read_00102_ptr, read_00102_len - read_00102_ptr, &read_00102_00000_match);
            if (rc > 0) {
                read_00102_ptr += read_00102_00000_match.match_end - read_00102_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00102_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00102);
        if (read_00102_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00103;
        unsigned int read_00103_len;
        unsigned int read_00103_ptr = 0;
        //**** delimited read
        static unsigned char read_00103_delim[] = 
            "\x0a";
        read_00103 = NULL;
        read_00103_len = 0;
        int read_00103_res = delimited_read(0, &read_00103, &read_00103_len, read_00103_delim, 1);
        if (read_00103_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00103_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00103_00000_match;
        pcre *read_00103_00000_pcre = init_regex(read_00103_00000_regex);
        if (read_00103_00000_pcre != NULL) {
            int rc = regex_match(read_00103_00000_pcre, 0, read_00103 + read_00103_ptr, read_00103_len - read_00103_ptr, &read_00103_00000_match);
            if (rc > 0) {
                read_00103_ptr += read_00103_00000_match.match_end - read_00103_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00103_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00103);
        if (read_00103_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00104;
        unsigned int read_00104_len;
        unsigned int read_00104_ptr = 0;
        //**** delimited read
        static unsigned char read_00104_delim[] = 
            "\x0a";
        read_00104 = NULL;
        read_00104_len = 0;
        int read_00104_res = delimited_read(0, &read_00104, &read_00104_len, read_00104_delim, 1);
        if (read_00104_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00104_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00104_00000_match;
        pcre *read_00104_00000_pcre = init_regex(read_00104_00000_regex);
        if (read_00104_00000_pcre != NULL) {
            int rc = regex_match(read_00104_00000_pcre, 0, read_00104 + read_00104_ptr, read_00104_len - read_00104_ptr, &read_00104_00000_match);
            if (rc > 0) {
                read_00104_ptr += read_00104_00000_match.match_end - read_00104_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00104_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00104);
        if (read_00104_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00105;
        unsigned int read_00105_len;
        unsigned int read_00105_ptr = 0;
        //**** delimited read
        static unsigned char read_00105_delim[] = 
            "\x0a";
        read_00105 = NULL;
        read_00105_len = 0;
        int read_00105_res = delimited_read(0, &read_00105, &read_00105_len, read_00105_delim, 1);
        if (read_00105_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00105_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00105_00000_match;
        pcre *read_00105_00000_pcre = init_regex(read_00105_00000_regex);
        if (read_00105_00000_pcre != NULL) {
            int rc = regex_match(read_00105_00000_pcre, 0, read_00105 + read_00105_ptr, read_00105_len - read_00105_ptr, &read_00105_00000_match);
            if (rc > 0) {
                read_00105_ptr += read_00105_00000_match.match_end - read_00105_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00105_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00105);
        if (read_00105_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00106;
        unsigned int read_00106_len;
        unsigned int read_00106_ptr = 0;
        //**** length read
        read_00106_len = 20;
        read_00106 = (unsigned char*)malloc(read_00106_len);
        int read_00106_res = length_read(0, read_00106, read_00106_len);
        if (read_00106_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00106_00000[] = 
            "\x53\x6f\x72\x72\x79\x2c\x20\x74\x68\x65\x20\x77\x6f\x72\x64\x20"
            "\x77\x61\x73\x20";
        read_00106_ptr += data_match(read_00106 + read_00106_ptr, read_00106_len - read_00106_ptr, match_00106_00000, 20);
        free(read_00106);
        if (read_00106_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00107;
        unsigned int read_00107_len;
        unsigned int read_00107_ptr = 0;
        //**** length read
        read_00107_len = 8;
        read_00107 = (unsigned char*)malloc(read_00107_len);
        int read_00107_res = length_read(0, read_00107, read_00107_len);
        if (read_00107_res) {} //silence unused variable warning
        //**** read assign to var "word0" from slice
        assign_from_slice("word0", read_00107, read_00107_len - read_00107_ptr, 0, 0, 1);
        free(read_00107);
        if (read_00107_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00108;
        unsigned int read_00108_len;
        unsigned int read_00108_ptr = 0;
        //**** delimited read
        static unsigned char read_00108_delim[] = 
            "\x0a";
        read_00108 = NULL;
        read_00108_len = 0;
        int read_00108_res = delimited_read(0, &read_00108, &read_00108_len, read_00108_delim, 1);
        if (read_00108_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00108_00000[] = 
            "\x21\x0a";
        read_00108_ptr += data_match(read_00108 + read_00108_ptr, read_00108_len - read_00108_ptr, match_00108_00000, 2);
        free(read_00108);
        if (read_00108_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00109;
        unsigned int read_00109_len;
        unsigned int read_00109_ptr = 0;
        //**** delimited read
        static unsigned char read_00109_delim[] = 
            "\x0a";
        read_00109 = NULL;
        read_00109_len = 0;
        int read_00109_res = delimited_read(0, &read_00109, &read_00109_len, read_00109_delim, 1);
        if (read_00109_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00109_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00109_ptr += data_match(read_00109 + read_00109_ptr, read_00109_len - read_00109_ptr, match_00109_00000, 22);
        free(read_00109);
        if (read_00109_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00110;
        unsigned int read_00110_len;
        unsigned int read_00110_ptr = 0;
        //**** delimited read
        static unsigned char read_00110_delim[] = 
            "\x0a";
        read_00110 = NULL;
        read_00110_len = 0;
        int read_00110_res = delimited_read(0, &read_00110, &read_00110_len, read_00110_delim, 1);
        if (read_00110_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00110_00000[] = 
            "\x0a";
        read_00110_ptr += data_match(read_00110 + read_00110_ptr, read_00110_len - read_00110_ptr, match_00110_00000, 1);
        free(read_00110);
        if (read_00110_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00111;
        unsigned int read_00111_len;
        unsigned int read_00111_ptr = 0;
        //**** delimited read
        static unsigned char read_00111_delim[] = 
            "\x0a";
        read_00111 = NULL;
        read_00111_len = 0;
        int read_00111_res = delimited_read(0, &read_00111, &read_00111_len, read_00111_delim, 1);
        if (read_00111_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00111_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00111_ptr += data_match(read_00111 + read_00111_ptr, read_00111_len - read_00111_ptr, match_00111_00000, 11);
        free(read_00111);
        if (read_00111_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00112;
        unsigned int read_00112_len;
        unsigned int read_00112_ptr = 0;
        //**** delimited read
        static unsigned char read_00112_delim[] = 
            "\x0a";
        read_00112 = NULL;
        read_00112_len = 0;
        int read_00112_res = delimited_read(0, &read_00112, &read_00112_len, read_00112_delim, 1);
        if (read_00112_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00112_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00112_ptr += data_match(read_00112 + read_00112_ptr, read_00112_len - read_00112_ptr, match_00112_00000, 9);
        free(read_00112);
        if (read_00112_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00113;
        unsigned int read_00113_len;
        unsigned int read_00113_ptr = 0;
        //**** delimited read
        static unsigned char read_00113_delim[] = 
            "\x0a";
        read_00113 = NULL;
        read_00113_len = 0;
        int read_00113_res = delimited_read(0, &read_00113, &read_00113_len, read_00113_delim, 1);
        if (read_00113_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00113_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00113_ptr += data_match(read_00113 + read_00113_ptr, read_00113_len - read_00113_ptr, match_00113_00000, 10);
        free(read_00113);
        if (read_00113_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00114;
        unsigned int read_00114_len;
        unsigned int read_00114_ptr = 0;
        //**** delimited read
        static unsigned char read_00114_delim[] = 
            "\x0a";
        read_00114 = NULL;
        read_00114_len = 0;
        int read_00114_res = delimited_read(0, &read_00114, &read_00114_len, read_00114_delim, 1);
        if (read_00114_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00114_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00114_ptr += data_match(read_00114 + read_00114_ptr, read_00114_len - read_00114_ptr, match_00114_00000, 20);
        free(read_00114);
        if (read_00114_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00115;
        unsigned int read_00115_len;
        unsigned int read_00115_ptr = 0;
        //**** delimited read
        static unsigned char read_00115_delim[] = 
            "\x0a";
        read_00115 = NULL;
        read_00115_len = 0;
        int read_00115_res = delimited_read(0, &read_00115, &read_00115_len, read_00115_delim, 1);
        if (read_00115_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00115_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00115_ptr += data_match(read_00115 + read_00115_ptr, read_00115_len - read_00115_ptr, match_00115_00000, 15);
        free(read_00115);
        if (read_00115_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00116;
        unsigned int read_00116_len;
        unsigned int read_00116_ptr = 0;
        //**** delimited read
        static unsigned char read_00116_delim[] = 
            "\x0a";
        read_00116 = NULL;
        read_00116_len = 0;
        int read_00116_res = delimited_read(0, &read_00116, &read_00116_len, read_00116_delim, 1);
        if (read_00116_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00116_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00116_ptr += data_match(read_00116 + read_00116_ptr, read_00116_len - read_00116_ptr, match_00116_00000, 20);
        free(read_00116);
        if (read_00116_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00117;
        unsigned int read_00117_len;
        unsigned int read_00117_ptr = 0;
        //**** delimited read
        static unsigned char read_00117_delim[] = 
            "\x0a";
        read_00117 = NULL;
        read_00117_len = 0;
        int read_00117_res = delimited_read(0, &read_00117, &read_00117_len, read_00117_delim, 1);
        if (read_00117_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00117_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00117_ptr += data_match(read_00117 + read_00117_ptr, read_00117_len - read_00117_ptr, match_00117_00000, 28);
        free(read_00117);
        if (read_00117_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00118;
        unsigned int read_00118_len;
        unsigned int read_00118_ptr = 0;
        //**** delimited read
        static unsigned char read_00118_delim[] = 
            "\x0a";
        read_00118 = NULL;
        read_00118_len = 0;
        int read_00118_res = delimited_read(0, &read_00118, &read_00118_len, read_00118_delim, 1);
        if (read_00118_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00118_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00118_ptr += data_match(read_00118 + read_00118_ptr, read_00118_len - read_00118_ptr, match_00118_00000, 8);
        free(read_00118);
        if (read_00118_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00119;
        unsigned int read_00119_len;
        unsigned int read_00119_ptr = 0;
        //**** delimited read
        static unsigned char read_00119_delim[] = 
            "\x0a";
        read_00119 = NULL;
        read_00119_len = 0;
        int read_00119_res = delimited_read(0, &read_00119, &read_00119_len, read_00119_delim, 1);
        if (read_00119_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00119_00000[] = 
            "\x0a";
        read_00119_ptr += data_match(read_00119 + read_00119_ptr, read_00119_len - read_00119_ptr, match_00119_00000, 1);
        free(read_00119);
        if (read_00119_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00008_00000[] = 
            "\x31\x0a";
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
        unsigned char *read_00120;
        unsigned int read_00120_len;
        unsigned int read_00120_ptr = 0;
        //**** delimited read
        static unsigned char read_00120_delim[] = 
            "\x0a";
        read_00120 = NULL;
        read_00120_len = 0;
        int read_00120_res = delimited_read(0, &read_00120, &read_00120_len, read_00120_delim, 1);
        if (read_00120_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00120_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00120_00000_match;
        pcre *read_00120_00000_pcre = init_regex(read_00120_00000_regex);
        if (read_00120_00000_pcre != NULL) {
            int rc = regex_match(read_00120_00000_pcre, 0, read_00120 + read_00120_ptr, read_00120_len - read_00120_ptr, &read_00120_00000_match);
            if (rc > 0) {
                read_00120_ptr += read_00120_00000_match.match_end - read_00120_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00120_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00120);
        if (read_00120_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00121;
        unsigned int read_00121_len;
        unsigned int read_00121_ptr = 0;
        //**** delimited read
        static unsigned char read_00121_delim[] = 
            "\x0a";
        read_00121 = NULL;
        read_00121_len = 0;
        int read_00121_res = delimited_read(0, &read_00121, &read_00121_len, read_00121_delim, 1);
        if (read_00121_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00121_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00121_00000_match;
        pcre *read_00121_00000_pcre = init_regex(read_00121_00000_regex);
        if (read_00121_00000_pcre != NULL) {
            int rc = regex_match(read_00121_00000_pcre, 0, read_00121 + read_00121_ptr, read_00121_len - read_00121_ptr, &read_00121_00000_match);
            if (rc > 0) {
                read_00121_ptr += read_00121_00000_match.match_end - read_00121_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00121_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00121);
        if (read_00121_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00122;
        unsigned int read_00122_len;
        unsigned int read_00122_ptr = 0;
        //**** delimited read
        static unsigned char read_00122_delim[] = 
            "\x0a";
        read_00122 = NULL;
        read_00122_len = 0;
        int read_00122_res = delimited_read(0, &read_00122, &read_00122_len, read_00122_delim, 1);
        if (read_00122_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00122_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00122_00000_match;
        pcre *read_00122_00000_pcre = init_regex(read_00122_00000_regex);
        if (read_00122_00000_pcre != NULL) {
            int rc = regex_match(read_00122_00000_pcre, 0, read_00122 + read_00122_ptr, read_00122_len - read_00122_ptr, &read_00122_00000_match);
            if (rc > 0) {
                read_00122_ptr += read_00122_00000_match.match_end - read_00122_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00122_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00122);
        if (read_00122_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00123;
        unsigned int read_00123_len;
        unsigned int read_00123_ptr = 0;
        //**** delimited read
        static unsigned char read_00123_delim[] = 
            "\x0a";
        read_00123 = NULL;
        read_00123_len = 0;
        int read_00123_res = delimited_read(0, &read_00123, &read_00123_len, read_00123_delim, 1);
        if (read_00123_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00123_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00123_00000_match;
        pcre *read_00123_00000_pcre = init_regex(read_00123_00000_regex);
        if (read_00123_00000_pcre != NULL) {
            int rc = regex_match(read_00123_00000_pcre, 0, read_00123 + read_00123_ptr, read_00123_len - read_00123_ptr, &read_00123_00000_match);
            if (rc > 0) {
                read_00123_ptr += read_00123_00000_match.match_end - read_00123_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00123_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00123);
        if (read_00123_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00124;
        unsigned int read_00124_len;
        unsigned int read_00124_ptr = 0;
        //**** delimited read
        static unsigned char read_00124_delim[] = 
            "\x0a";
        read_00124 = NULL;
        read_00124_len = 0;
        int read_00124_res = delimited_read(0, &read_00124, &read_00124_len, read_00124_delim, 1);
        if (read_00124_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00124_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00124_00000_match;
        pcre *read_00124_00000_pcre = init_regex(read_00124_00000_regex);
        if (read_00124_00000_pcre != NULL) {
            int rc = regex_match(read_00124_00000_pcre, 0, read_00124 + read_00124_ptr, read_00124_len - read_00124_ptr, &read_00124_00000_match);
            if (rc > 0) {
                read_00124_ptr += read_00124_00000_match.match_end - read_00124_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00124_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00124);
        if (read_00124_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00125;
        unsigned int read_00125_len;
        unsigned int read_00125_ptr = 0;
        //**** delimited read
        static unsigned char read_00125_delim[] = 
            "\x0a";
        read_00125 = NULL;
        read_00125_len = 0;
        int read_00125_res = delimited_read(0, &read_00125, &read_00125_len, read_00125_delim, 1);
        if (read_00125_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00125_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00125_00000_match;
        pcre *read_00125_00000_pcre = init_regex(read_00125_00000_regex);
        if (read_00125_00000_pcre != NULL) {
            int rc = regex_match(read_00125_00000_pcre, 0, read_00125 + read_00125_ptr, read_00125_len - read_00125_ptr, &read_00125_00000_match);
            if (rc > 0) {
                read_00125_ptr += read_00125_00000_match.match_end - read_00125_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00125_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00125);
        if (read_00125_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00126;
        unsigned int read_00126_len;
        unsigned int read_00126_ptr = 0;
        //**** delimited read
        static unsigned char read_00126_delim[] = 
            "\x0a";
        read_00126 = NULL;
        read_00126_len = 0;
        int read_00126_res = delimited_read(0, &read_00126, &read_00126_len, read_00126_delim, 1);
        if (read_00126_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00126_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00126_00000_match;
        pcre *read_00126_00000_pcre = init_regex(read_00126_00000_regex);
        if (read_00126_00000_pcre != NULL) {
            int rc = regex_match(read_00126_00000_pcre, 0, read_00126 + read_00126_ptr, read_00126_len - read_00126_ptr, &read_00126_00000_match);
            if (rc > 0) {
                read_00126_ptr += read_00126_00000_match.match_end - read_00126_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00126_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00126);
        if (read_00126_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00127;
        unsigned int read_00127_len;
        unsigned int read_00127_ptr = 0;
        //**** delimited read
        static unsigned char read_00127_delim[] = 
            "\x0a";
        read_00127 = NULL;
        read_00127_len = 0;
        int read_00127_res = delimited_read(0, &read_00127, &read_00127_len, read_00127_delim, 1);
        if (read_00127_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00127_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00127_00000_match;
        pcre *read_00127_00000_pcre = init_regex(read_00127_00000_regex);
        if (read_00127_00000_pcre != NULL) {
            int rc = regex_match(read_00127_00000_pcre, 0, read_00127 + read_00127_ptr, read_00127_len - read_00127_ptr, &read_00127_00000_match);
            if (rc > 0) {
                read_00127_ptr += read_00127_00000_match.match_end - read_00127_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00127_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00127);
        if (read_00127_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00128;
        unsigned int read_00128_len;
        unsigned int read_00128_ptr = 0;
        //**** delimited read
        static unsigned char read_00128_delim[] = 
            "\x0a";
        read_00128 = NULL;
        read_00128_len = 0;
        int read_00128_res = delimited_read(0, &read_00128, &read_00128_len, read_00128_delim, 1);
        if (read_00128_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00128_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00128_00000_match;
        pcre *read_00128_00000_pcre = init_regex(read_00128_00000_regex);
        if (read_00128_00000_pcre != NULL) {
            int rc = regex_match(read_00128_00000_pcre, 0, read_00128 + read_00128_ptr, read_00128_len - read_00128_ptr, &read_00128_00000_match);
            if (rc > 0) {
                read_00128_ptr += read_00128_00000_match.match_end - read_00128_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00128_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00128);
        if (read_00128_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00129;
        unsigned int read_00129_len;
        unsigned int read_00129_ptr = 0;
        //**** delimited read
        static unsigned char read_00129_delim[] = 
            "\x0a";
        read_00129 = NULL;
        read_00129_len = 0;
        int read_00129_res = delimited_read(0, &read_00129, &read_00129_len, read_00129_delim, 1);
        if (read_00129_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00129_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00129_00000_match;
        pcre *read_00129_00000_pcre = init_regex(read_00129_00000_regex);
        if (read_00129_00000_pcre != NULL) {
            int rc = regex_match(read_00129_00000_pcre, 0, read_00129 + read_00129_ptr, read_00129_len - read_00129_ptr, &read_00129_00000_match);
            if (rc > 0) {
                read_00129_ptr += read_00129_00000_match.match_end - read_00129_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00129_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00129);
        if (read_00129_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00130;
        unsigned int read_00130_len;
        unsigned int read_00130_ptr = 0;
        //**** delimited read
        static unsigned char read_00130_delim[] = 
            "\x0a";
        read_00130 = NULL;
        read_00130_len = 0;
        int read_00130_res = delimited_read(0, &read_00130, &read_00130_len, read_00130_delim, 1);
        if (read_00130_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00130_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00130_00000_match;
        pcre *read_00130_00000_pcre = init_regex(read_00130_00000_regex);
        if (read_00130_00000_pcre != NULL) {
            int rc = regex_match(read_00130_00000_pcre, 0, read_00130 + read_00130_ptr, read_00130_len - read_00130_ptr, &read_00130_00000_match);
            if (rc > 0) {
                read_00130_ptr += read_00130_00000_match.match_end - read_00130_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00130_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00130);
        if (read_00130_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00131;
        unsigned int read_00131_len;
        unsigned int read_00131_ptr = 0;
        //**** delimited read
        static unsigned char read_00131_delim[] = 
            "\x0a";
        read_00131 = NULL;
        read_00131_len = 0;
        int read_00131_res = delimited_read(0, &read_00131, &read_00131_len, read_00131_delim, 1);
        if (read_00131_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00131_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00131_00000_match;
        pcre *read_00131_00000_pcre = init_regex(read_00131_00000_regex);
        if (read_00131_00000_pcre != NULL) {
            int rc = regex_match(read_00131_00000_pcre, 0, read_00131 + read_00131_ptr, read_00131_len - read_00131_ptr, &read_00131_00000_match);
            if (rc > 0) {
                read_00131_ptr += read_00131_00000_match.match_end - read_00131_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00131_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00131);
        if (read_00131_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00009_00000[] = 
            "\x3a";
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
        unsigned char *read_00132;
        unsigned int read_00132_len;
        unsigned int read_00132_ptr = 0;
        //**** delimited read
        static unsigned char read_00132_delim[] = 
            "\x0a";
        read_00132 = NULL;
        read_00132_len = 0;
        int read_00132_res = delimited_read(0, &read_00132, &read_00132_len, read_00132_delim, 1);
        if (read_00132_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00132_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00132_00000_match;
        pcre *read_00132_00000_pcre = init_regex(read_00132_00000_regex);
        if (read_00132_00000_pcre != NULL) {
            int rc = regex_match(read_00132_00000_pcre, 0, read_00132 + read_00132_ptr, read_00132_len - read_00132_ptr, &read_00132_00000_match);
            if (rc > 0) {
                read_00132_ptr += read_00132_00000_match.match_end - read_00132_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00132_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00132);
        if (read_00132_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00133;
        unsigned int read_00133_len;
        unsigned int read_00133_ptr = 0;
        //**** delimited read
        static unsigned char read_00133_delim[] = 
            "\x0a";
        read_00133 = NULL;
        read_00133_len = 0;
        int read_00133_res = delimited_read(0, &read_00133, &read_00133_len, read_00133_delim, 1);
        if (read_00133_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00133_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00133_00000_match;
        pcre *read_00133_00000_pcre = init_regex(read_00133_00000_regex);
        if (read_00133_00000_pcre != NULL) {
            int rc = regex_match(read_00133_00000_pcre, 0, read_00133 + read_00133_ptr, read_00133_len - read_00133_ptr, &read_00133_00000_match);
            if (rc > 0) {
                read_00133_ptr += read_00133_00000_match.match_end - read_00133_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00133_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00133);
        if (read_00133_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00134;
        unsigned int read_00134_len;
        unsigned int read_00134_ptr = 0;
        //**** delimited read
        static unsigned char read_00134_delim[] = 
            "\x0a";
        read_00134 = NULL;
        read_00134_len = 0;
        int read_00134_res = delimited_read(0, &read_00134, &read_00134_len, read_00134_delim, 1);
        if (read_00134_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00134_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00134_00000_match;
        pcre *read_00134_00000_pcre = init_regex(read_00134_00000_regex);
        if (read_00134_00000_pcre != NULL) {
            int rc = regex_match(read_00134_00000_pcre, 0, read_00134 + read_00134_ptr, read_00134_len - read_00134_ptr, &read_00134_00000_match);
            if (rc > 0) {
                read_00134_ptr += read_00134_00000_match.match_end - read_00134_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00134_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00134);
        if (read_00134_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00135;
        unsigned int read_00135_len;
        unsigned int read_00135_ptr = 0;
        //**** delimited read
        static unsigned char read_00135_delim[] = 
            "\x0a";
        read_00135 = NULL;
        read_00135_len = 0;
        int read_00135_res = delimited_read(0, &read_00135, &read_00135_len, read_00135_delim, 1);
        if (read_00135_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00135_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00135_00000_match;
        pcre *read_00135_00000_pcre = init_regex(read_00135_00000_regex);
        if (read_00135_00000_pcre != NULL) {
            int rc = regex_match(read_00135_00000_pcre, 0, read_00135 + read_00135_ptr, read_00135_len - read_00135_ptr, &read_00135_00000_match);
            if (rc > 0) {
                read_00135_ptr += read_00135_00000_match.match_end - read_00135_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00135_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00135);
        if (read_00135_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00136;
        unsigned int read_00136_len;
        unsigned int read_00136_ptr = 0;
        //**** delimited read
        static unsigned char read_00136_delim[] = 
            "\x0a";
        read_00136 = NULL;
        read_00136_len = 0;
        int read_00136_res = delimited_read(0, &read_00136, &read_00136_len, read_00136_delim, 1);
        if (read_00136_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00136_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00136_00000_match;
        pcre *read_00136_00000_pcre = init_regex(read_00136_00000_regex);
        if (read_00136_00000_pcre != NULL) {
            int rc = regex_match(read_00136_00000_pcre, 0, read_00136 + read_00136_ptr, read_00136_len - read_00136_ptr, &read_00136_00000_match);
            if (rc > 0) {
                read_00136_ptr += read_00136_00000_match.match_end - read_00136_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00136_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00136);
        if (read_00136_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00137;
        unsigned int read_00137_len;
        unsigned int read_00137_ptr = 0;
        //**** delimited read
        static unsigned char read_00137_delim[] = 
            "\x0a";
        read_00137 = NULL;
        read_00137_len = 0;
        int read_00137_res = delimited_read(0, &read_00137, &read_00137_len, read_00137_delim, 1);
        if (read_00137_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00137_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00137_00000_match;
        pcre *read_00137_00000_pcre = init_regex(read_00137_00000_regex);
        if (read_00137_00000_pcre != NULL) {
            int rc = regex_match(read_00137_00000_pcre, 0, read_00137 + read_00137_ptr, read_00137_len - read_00137_ptr, &read_00137_00000_match);
            if (rc > 0) {
                read_00137_ptr += read_00137_00000_match.match_end - read_00137_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00137_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00137);
        if (read_00137_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00138;
        unsigned int read_00138_len;
        unsigned int read_00138_ptr = 0;
        //**** delimited read
        static unsigned char read_00138_delim[] = 
            "\x0a";
        read_00138 = NULL;
        read_00138_len = 0;
        int read_00138_res = delimited_read(0, &read_00138, &read_00138_len, read_00138_delim, 1);
        if (read_00138_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00138_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00138_00000_match;
        pcre *read_00138_00000_pcre = init_regex(read_00138_00000_regex);
        if (read_00138_00000_pcre != NULL) {
            int rc = regex_match(read_00138_00000_pcre, 0, read_00138 + read_00138_ptr, read_00138_len - read_00138_ptr, &read_00138_00000_match);
            if (rc > 0) {
                read_00138_ptr += read_00138_00000_match.match_end - read_00138_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00138_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00138);
        if (read_00138_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00139;
        unsigned int read_00139_len;
        unsigned int read_00139_ptr = 0;
        //**** delimited read
        static unsigned char read_00139_delim[] = 
            "\x0a";
        read_00139 = NULL;
        read_00139_len = 0;
        int read_00139_res = delimited_read(0, &read_00139, &read_00139_len, read_00139_delim, 1);
        if (read_00139_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00139_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00139_00000_match;
        pcre *read_00139_00000_pcre = init_regex(read_00139_00000_regex);
        if (read_00139_00000_pcre != NULL) {
            int rc = regex_match(read_00139_00000_pcre, 0, read_00139 + read_00139_ptr, read_00139_len - read_00139_ptr, &read_00139_00000_match);
            if (rc > 0) {
                read_00139_ptr += read_00139_00000_match.match_end - read_00139_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00139_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00139);
        if (read_00139_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00140;
        unsigned int read_00140_len;
        unsigned int read_00140_ptr = 0;
        //**** delimited read
        static unsigned char read_00140_delim[] = 
            "\x0a";
        read_00140 = NULL;
        read_00140_len = 0;
        int read_00140_res = delimited_read(0, &read_00140, &read_00140_len, read_00140_delim, 1);
        if (read_00140_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00140_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00140_00000_match;
        pcre *read_00140_00000_pcre = init_regex(read_00140_00000_regex);
        if (read_00140_00000_pcre != NULL) {
            int rc = regex_match(read_00140_00000_pcre, 0, read_00140 + read_00140_ptr, read_00140_len - read_00140_ptr, &read_00140_00000_match);
            if (rc > 0) {
                read_00140_ptr += read_00140_00000_match.match_end - read_00140_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00140_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00140);
        if (read_00140_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00141;
        unsigned int read_00141_len;
        unsigned int read_00141_ptr = 0;
        //**** delimited read
        static unsigned char read_00141_delim[] = 
            "\x0a";
        read_00141 = NULL;
        read_00141_len = 0;
        int read_00141_res = delimited_read(0, &read_00141, &read_00141_len, read_00141_delim, 1);
        if (read_00141_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00141_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00141_00000_match;
        pcre *read_00141_00000_pcre = init_regex(read_00141_00000_regex);
        if (read_00141_00000_pcre != NULL) {
            int rc = regex_match(read_00141_00000_pcre, 0, read_00141 + read_00141_ptr, read_00141_len - read_00141_ptr, &read_00141_00000_match);
            if (rc > 0) {
                read_00141_ptr += read_00141_00000_match.match_end - read_00141_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00141_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00141);
        if (read_00141_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00142;
        unsigned int read_00142_len;
        unsigned int read_00142_ptr = 0;
        //**** delimited read
        static unsigned char read_00142_delim[] = 
            "\x0a";
        read_00142 = NULL;
        read_00142_len = 0;
        int read_00142_res = delimited_read(0, &read_00142, &read_00142_len, read_00142_delim, 1);
        if (read_00142_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00142_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00142_00000_match;
        pcre *read_00142_00000_pcre = init_regex(read_00142_00000_regex);
        if (read_00142_00000_pcre != NULL) {
            int rc = regex_match(read_00142_00000_pcre, 0, read_00142 + read_00142_ptr, read_00142_len - read_00142_ptr, &read_00142_00000_match);
            if (rc > 0) {
                read_00142_ptr += read_00142_00000_match.match_end - read_00142_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00142_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00142);
        if (read_00142_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00143;
        unsigned int read_00143_len;
        unsigned int read_00143_ptr = 0;
        //**** delimited read
        static unsigned char read_00143_delim[] = 
            "\x0a";
        read_00143 = NULL;
        read_00143_len = 0;
        int read_00143_res = delimited_read(0, &read_00143, &read_00143_len, read_00143_delim, 1);
        if (read_00143_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00143_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00143_00000_match;
        pcre *read_00143_00000_pcre = init_regex(read_00143_00000_regex);
        if (read_00143_00000_pcre != NULL) {
            int rc = regex_match(read_00143_00000_pcre, 0, read_00143 + read_00143_ptr, read_00143_len - read_00143_ptr, &read_00143_00000_match);
            if (rc > 0) {
                read_00143_ptr += read_00143_00000_match.match_end - read_00143_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00143_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00143);
        if (read_00143_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00010_00000[] = 
            "\x3a";
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
        unsigned char *read_00144;
        unsigned int read_00144_len;
        unsigned int read_00144_ptr = 0;
        //**** delimited read
        static unsigned char read_00144_delim[] = 
            "\x0a";
        read_00144 = NULL;
        read_00144_len = 0;
        int read_00144_res = delimited_read(0, &read_00144, &read_00144_len, read_00144_delim, 1);
        if (read_00144_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00144_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00144_00000_match;
        pcre *read_00144_00000_pcre = init_regex(read_00144_00000_regex);
        if (read_00144_00000_pcre != NULL) {
            int rc = regex_match(read_00144_00000_pcre, 0, read_00144 + read_00144_ptr, read_00144_len - read_00144_ptr, &read_00144_00000_match);
            if (rc > 0) {
                read_00144_ptr += read_00144_00000_match.match_end - read_00144_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00144_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00144);
        if (read_00144_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00145;
        unsigned int read_00145_len;
        unsigned int read_00145_ptr = 0;
        //**** delimited read
        static unsigned char read_00145_delim[] = 
            "\x0a";
        read_00145 = NULL;
        read_00145_len = 0;
        int read_00145_res = delimited_read(0, &read_00145, &read_00145_len, read_00145_delim, 1);
        if (read_00145_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00145_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00145_00000_match;
        pcre *read_00145_00000_pcre = init_regex(read_00145_00000_regex);
        if (read_00145_00000_pcre != NULL) {
            int rc = regex_match(read_00145_00000_pcre, 0, read_00145 + read_00145_ptr, read_00145_len - read_00145_ptr, &read_00145_00000_match);
            if (rc > 0) {
                read_00145_ptr += read_00145_00000_match.match_end - read_00145_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00145_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00145);
        if (read_00145_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00146;
        unsigned int read_00146_len;
        unsigned int read_00146_ptr = 0;
        //**** delimited read
        static unsigned char read_00146_delim[] = 
            "\x0a";
        read_00146 = NULL;
        read_00146_len = 0;
        int read_00146_res = delimited_read(0, &read_00146, &read_00146_len, read_00146_delim, 1);
        if (read_00146_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00146_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00146_00000_match;
        pcre *read_00146_00000_pcre = init_regex(read_00146_00000_regex);
        if (read_00146_00000_pcre != NULL) {
            int rc = regex_match(read_00146_00000_pcre, 0, read_00146 + read_00146_ptr, read_00146_len - read_00146_ptr, &read_00146_00000_match);
            if (rc > 0) {
                read_00146_ptr += read_00146_00000_match.match_end - read_00146_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00146_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00146);
        if (read_00146_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00147;
        unsigned int read_00147_len;
        unsigned int read_00147_ptr = 0;
        //**** delimited read
        static unsigned char read_00147_delim[] = 
            "\x0a";
        read_00147 = NULL;
        read_00147_len = 0;
        int read_00147_res = delimited_read(0, &read_00147, &read_00147_len, read_00147_delim, 1);
        if (read_00147_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00147_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00147_00000_match;
        pcre *read_00147_00000_pcre = init_regex(read_00147_00000_regex);
        if (read_00147_00000_pcre != NULL) {
            int rc = regex_match(read_00147_00000_pcre, 0, read_00147 + read_00147_ptr, read_00147_len - read_00147_ptr, &read_00147_00000_match);
            if (rc > 0) {
                read_00147_ptr += read_00147_00000_match.match_end - read_00147_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00147_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00147);
        if (read_00147_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00148;
        unsigned int read_00148_len;
        unsigned int read_00148_ptr = 0;
        //**** delimited read
        static unsigned char read_00148_delim[] = 
            "\x0a";
        read_00148 = NULL;
        read_00148_len = 0;
        int read_00148_res = delimited_read(0, &read_00148, &read_00148_len, read_00148_delim, 1);
        if (read_00148_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00148_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00148_00000_match;
        pcre *read_00148_00000_pcre = init_regex(read_00148_00000_regex);
        if (read_00148_00000_pcre != NULL) {
            int rc = regex_match(read_00148_00000_pcre, 0, read_00148 + read_00148_ptr, read_00148_len - read_00148_ptr, &read_00148_00000_match);
            if (rc > 0) {
                read_00148_ptr += read_00148_00000_match.match_end - read_00148_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00148_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00148);
        if (read_00148_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00149;
        unsigned int read_00149_len;
        unsigned int read_00149_ptr = 0;
        //**** delimited read
        static unsigned char read_00149_delim[] = 
            "\x0a";
        read_00149 = NULL;
        read_00149_len = 0;
        int read_00149_res = delimited_read(0, &read_00149, &read_00149_len, read_00149_delim, 1);
        if (read_00149_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00149_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00149_00000_match;
        pcre *read_00149_00000_pcre = init_regex(read_00149_00000_regex);
        if (read_00149_00000_pcre != NULL) {
            int rc = regex_match(read_00149_00000_pcre, 0, read_00149 + read_00149_ptr, read_00149_len - read_00149_ptr, &read_00149_00000_match);
            if (rc > 0) {
                read_00149_ptr += read_00149_00000_match.match_end - read_00149_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00149_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00149);
        if (read_00149_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00150;
        unsigned int read_00150_len;
        unsigned int read_00150_ptr = 0;
        //**** delimited read
        static unsigned char read_00150_delim[] = 
            "\x0a";
        read_00150 = NULL;
        read_00150_len = 0;
        int read_00150_res = delimited_read(0, &read_00150, &read_00150_len, read_00150_delim, 1);
        if (read_00150_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00150_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00150_00000_match;
        pcre *read_00150_00000_pcre = init_regex(read_00150_00000_regex);
        if (read_00150_00000_pcre != NULL) {
            int rc = regex_match(read_00150_00000_pcre, 0, read_00150 + read_00150_ptr, read_00150_len - read_00150_ptr, &read_00150_00000_match);
            if (rc > 0) {
                read_00150_ptr += read_00150_00000_match.match_end - read_00150_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00150_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00150);
        if (read_00150_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00151;
        unsigned int read_00151_len;
        unsigned int read_00151_ptr = 0;
        //**** delimited read
        static unsigned char read_00151_delim[] = 
            "\x0a";
        read_00151 = NULL;
        read_00151_len = 0;
        int read_00151_res = delimited_read(0, &read_00151, &read_00151_len, read_00151_delim, 1);
        if (read_00151_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00151_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00151_00000_match;
        pcre *read_00151_00000_pcre = init_regex(read_00151_00000_regex);
        if (read_00151_00000_pcre != NULL) {
            int rc = regex_match(read_00151_00000_pcre, 0, read_00151 + read_00151_ptr, read_00151_len - read_00151_ptr, &read_00151_00000_match);
            if (rc > 0) {
                read_00151_ptr += read_00151_00000_match.match_end - read_00151_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00151_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00151);
        if (read_00151_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00152;
        unsigned int read_00152_len;
        unsigned int read_00152_ptr = 0;
        //**** delimited read
        static unsigned char read_00152_delim[] = 
            "\x0a";
        read_00152 = NULL;
        read_00152_len = 0;
        int read_00152_res = delimited_read(0, &read_00152, &read_00152_len, read_00152_delim, 1);
        if (read_00152_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00152_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00152_00000_match;
        pcre *read_00152_00000_pcre = init_regex(read_00152_00000_regex);
        if (read_00152_00000_pcre != NULL) {
            int rc = regex_match(read_00152_00000_pcre, 0, read_00152 + read_00152_ptr, read_00152_len - read_00152_ptr, &read_00152_00000_match);
            if (rc > 0) {
                read_00152_ptr += read_00152_00000_match.match_end - read_00152_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00152_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00152);
        if (read_00152_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00153;
        unsigned int read_00153_len;
        unsigned int read_00153_ptr = 0;
        //**** delimited read
        static unsigned char read_00153_delim[] = 
            "\x0a";
        read_00153 = NULL;
        read_00153_len = 0;
        int read_00153_res = delimited_read(0, &read_00153, &read_00153_len, read_00153_delim, 1);
        if (read_00153_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00153_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00153_00000_match;
        pcre *read_00153_00000_pcre = init_regex(read_00153_00000_regex);
        if (read_00153_00000_pcre != NULL) {
            int rc = regex_match(read_00153_00000_pcre, 0, read_00153 + read_00153_ptr, read_00153_len - read_00153_ptr, &read_00153_00000_match);
            if (rc > 0) {
                read_00153_ptr += read_00153_00000_match.match_end - read_00153_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00153_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00153);
        if (read_00153_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00154;
        unsigned int read_00154_len;
        unsigned int read_00154_ptr = 0;
        //**** delimited read
        static unsigned char read_00154_delim[] = 
            "\x0a";
        read_00154 = NULL;
        read_00154_len = 0;
        int read_00154_res = delimited_read(0, &read_00154, &read_00154_len, read_00154_delim, 1);
        if (read_00154_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00154_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00154_00000_match;
        pcre *read_00154_00000_pcre = init_regex(read_00154_00000_regex);
        if (read_00154_00000_pcre != NULL) {
            int rc = regex_match(read_00154_00000_pcre, 0, read_00154 + read_00154_ptr, read_00154_len - read_00154_ptr, &read_00154_00000_match);
            if (rc > 0) {
                read_00154_ptr += read_00154_00000_match.match_end - read_00154_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00154_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00154);
        if (read_00154_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00155;
        unsigned int read_00155_len;
        unsigned int read_00155_ptr = 0;
        //**** delimited read
        static unsigned char read_00155_delim[] = 
            "\x0a";
        read_00155 = NULL;
        read_00155_len = 0;
        int read_00155_res = delimited_read(0, &read_00155, &read_00155_len, read_00155_delim, 1);
        if (read_00155_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00155_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00155_00000_match;
        pcre *read_00155_00000_pcre = init_regex(read_00155_00000_regex);
        if (read_00155_00000_pcre != NULL) {
            int rc = regex_match(read_00155_00000_pcre, 0, read_00155 + read_00155_ptr, read_00155_len - read_00155_ptr, &read_00155_00000_match);
            if (rc > 0) {
                read_00155_ptr += read_00155_00000_match.match_end - read_00155_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00155_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00155);
        if (read_00155_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00011_00000[] = 
            "\x3a";
        static unsigned int write_00011_00000_len = 1;
        unsigned char *write_00011 = NULL;
        unsigned int write_00011_len = 0;
        write_00011 = append_buf(write_00011, &write_00011_len, write_00011_00000, write_00011_00000_len);
        if (write_00011_len > 0) {
            transmit_all(1, write_00011, write_00011_len);
        }
        free(write_00011);
    } while (0);
    do {
        unsigned char *read_00156;
        unsigned int read_00156_len;
        unsigned int read_00156_ptr = 0;
        //**** delimited read
        static unsigned char read_00156_delim[] = 
            "\x0a";
        read_00156 = NULL;
        read_00156_len = 0;
        int read_00156_res = delimited_read(0, &read_00156, &read_00156_len, read_00156_delim, 1);
        if (read_00156_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00156_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00156_00000_match;
        pcre *read_00156_00000_pcre = init_regex(read_00156_00000_regex);
        if (read_00156_00000_pcre != NULL) {
            int rc = regex_match(read_00156_00000_pcre, 0, read_00156 + read_00156_ptr, read_00156_len - read_00156_ptr, &read_00156_00000_match);
            if (rc > 0) {
                read_00156_ptr += read_00156_00000_match.match_end - read_00156_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00156_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00156);
        if (read_00156_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00157;
        unsigned int read_00157_len;
        unsigned int read_00157_ptr = 0;
        //**** delimited read
        static unsigned char read_00157_delim[] = 
            "\x0a";
        read_00157 = NULL;
        read_00157_len = 0;
        int read_00157_res = delimited_read(0, &read_00157, &read_00157_len, read_00157_delim, 1);
        if (read_00157_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00157_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00157_00000_match;
        pcre *read_00157_00000_pcre = init_regex(read_00157_00000_regex);
        if (read_00157_00000_pcre != NULL) {
            int rc = regex_match(read_00157_00000_pcre, 0, read_00157 + read_00157_ptr, read_00157_len - read_00157_ptr, &read_00157_00000_match);
            if (rc > 0) {
                read_00157_ptr += read_00157_00000_match.match_end - read_00157_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00157_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00157);
        if (read_00157_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00158;
        unsigned int read_00158_len;
        unsigned int read_00158_ptr = 0;
        //**** delimited read
        static unsigned char read_00158_delim[] = 
            "\x0a";
        read_00158 = NULL;
        read_00158_len = 0;
        int read_00158_res = delimited_read(0, &read_00158, &read_00158_len, read_00158_delim, 1);
        if (read_00158_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00158_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00158_00000_match;
        pcre *read_00158_00000_pcre = init_regex(read_00158_00000_regex);
        if (read_00158_00000_pcre != NULL) {
            int rc = regex_match(read_00158_00000_pcre, 0, read_00158 + read_00158_ptr, read_00158_len - read_00158_ptr, &read_00158_00000_match);
            if (rc > 0) {
                read_00158_ptr += read_00158_00000_match.match_end - read_00158_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00158_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00158);
        if (read_00158_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00159;
        unsigned int read_00159_len;
        unsigned int read_00159_ptr = 0;
        //**** delimited read
        static unsigned char read_00159_delim[] = 
            "\x0a";
        read_00159 = NULL;
        read_00159_len = 0;
        int read_00159_res = delimited_read(0, &read_00159, &read_00159_len, read_00159_delim, 1);
        if (read_00159_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00159_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00159_00000_match;
        pcre *read_00159_00000_pcre = init_regex(read_00159_00000_regex);
        if (read_00159_00000_pcre != NULL) {
            int rc = regex_match(read_00159_00000_pcre, 0, read_00159 + read_00159_ptr, read_00159_len - read_00159_ptr, &read_00159_00000_match);
            if (rc > 0) {
                read_00159_ptr += read_00159_00000_match.match_end - read_00159_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00159_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00159);
        if (read_00159_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00160;
        unsigned int read_00160_len;
        unsigned int read_00160_ptr = 0;
        //**** delimited read
        static unsigned char read_00160_delim[] = 
            "\x0a";
        read_00160 = NULL;
        read_00160_len = 0;
        int read_00160_res = delimited_read(0, &read_00160, &read_00160_len, read_00160_delim, 1);
        if (read_00160_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00160_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00160_00000_match;
        pcre *read_00160_00000_pcre = init_regex(read_00160_00000_regex);
        if (read_00160_00000_pcre != NULL) {
            int rc = regex_match(read_00160_00000_pcre, 0, read_00160 + read_00160_ptr, read_00160_len - read_00160_ptr, &read_00160_00000_match);
            if (rc > 0) {
                read_00160_ptr += read_00160_00000_match.match_end - read_00160_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00160_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00160);
        if (read_00160_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00161;
        unsigned int read_00161_len;
        unsigned int read_00161_ptr = 0;
        //**** delimited read
        static unsigned char read_00161_delim[] = 
            "\x0a";
        read_00161 = NULL;
        read_00161_len = 0;
        int read_00161_res = delimited_read(0, &read_00161, &read_00161_len, read_00161_delim, 1);
        if (read_00161_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00161_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00161_00000_match;
        pcre *read_00161_00000_pcre = init_regex(read_00161_00000_regex);
        if (read_00161_00000_pcre != NULL) {
            int rc = regex_match(read_00161_00000_pcre, 0, read_00161 + read_00161_ptr, read_00161_len - read_00161_ptr, &read_00161_00000_match);
            if (rc > 0) {
                read_00161_ptr += read_00161_00000_match.match_end - read_00161_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00161_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00161);
        if (read_00161_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00162;
        unsigned int read_00162_len;
        unsigned int read_00162_ptr = 0;
        //**** delimited read
        static unsigned char read_00162_delim[] = 
            "\x0a";
        read_00162 = NULL;
        read_00162_len = 0;
        int read_00162_res = delimited_read(0, &read_00162, &read_00162_len, read_00162_delim, 1);
        if (read_00162_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00162_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00162_00000_match;
        pcre *read_00162_00000_pcre = init_regex(read_00162_00000_regex);
        if (read_00162_00000_pcre != NULL) {
            int rc = regex_match(read_00162_00000_pcre, 0, read_00162 + read_00162_ptr, read_00162_len - read_00162_ptr, &read_00162_00000_match);
            if (rc > 0) {
                read_00162_ptr += read_00162_00000_match.match_end - read_00162_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00162_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00162);
        if (read_00162_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00163;
        unsigned int read_00163_len;
        unsigned int read_00163_ptr = 0;
        //**** delimited read
        static unsigned char read_00163_delim[] = 
            "\x0a";
        read_00163 = NULL;
        read_00163_len = 0;
        int read_00163_res = delimited_read(0, &read_00163, &read_00163_len, read_00163_delim, 1);
        if (read_00163_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00163_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00163_00000_match;
        pcre *read_00163_00000_pcre = init_regex(read_00163_00000_regex);
        if (read_00163_00000_pcre != NULL) {
            int rc = regex_match(read_00163_00000_pcre, 0, read_00163 + read_00163_ptr, read_00163_len - read_00163_ptr, &read_00163_00000_match);
            if (rc > 0) {
                read_00163_ptr += read_00163_00000_match.match_end - read_00163_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00163_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00163);
        if (read_00163_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00164;
        unsigned int read_00164_len;
        unsigned int read_00164_ptr = 0;
        //**** delimited read
        static unsigned char read_00164_delim[] = 
            "\x0a";
        read_00164 = NULL;
        read_00164_len = 0;
        int read_00164_res = delimited_read(0, &read_00164, &read_00164_len, read_00164_delim, 1);
        if (read_00164_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00164_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00164_00000_match;
        pcre *read_00164_00000_pcre = init_regex(read_00164_00000_regex);
        if (read_00164_00000_pcre != NULL) {
            int rc = regex_match(read_00164_00000_pcre, 0, read_00164 + read_00164_ptr, read_00164_len - read_00164_ptr, &read_00164_00000_match);
            if (rc > 0) {
                read_00164_ptr += read_00164_00000_match.match_end - read_00164_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00164_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00164);
        if (read_00164_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00165;
        unsigned int read_00165_len;
        unsigned int read_00165_ptr = 0;
        //**** delimited read
        static unsigned char read_00165_delim[] = 
            "\x0a";
        read_00165 = NULL;
        read_00165_len = 0;
        int read_00165_res = delimited_read(0, &read_00165, &read_00165_len, read_00165_delim, 1);
        if (read_00165_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00165_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00165_00000_match;
        pcre *read_00165_00000_pcre = init_regex(read_00165_00000_regex);
        if (read_00165_00000_pcre != NULL) {
            int rc = regex_match(read_00165_00000_pcre, 0, read_00165 + read_00165_ptr, read_00165_len - read_00165_ptr, &read_00165_00000_match);
            if (rc > 0) {
                read_00165_ptr += read_00165_00000_match.match_end - read_00165_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00165_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00165);
        if (read_00165_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00166;
        unsigned int read_00166_len;
        unsigned int read_00166_ptr = 0;
        //**** delimited read
        static unsigned char read_00166_delim[] = 
            "\x0a";
        read_00166 = NULL;
        read_00166_len = 0;
        int read_00166_res = delimited_read(0, &read_00166, &read_00166_len, read_00166_delim, 1);
        if (read_00166_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00166_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00166_00000_match;
        pcre *read_00166_00000_pcre = init_regex(read_00166_00000_regex);
        if (read_00166_00000_pcre != NULL) {
            int rc = regex_match(read_00166_00000_pcre, 0, read_00166 + read_00166_ptr, read_00166_len - read_00166_ptr, &read_00166_00000_match);
            if (rc > 0) {
                read_00166_ptr += read_00166_00000_match.match_end - read_00166_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00166_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00166);
        if (read_00166_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00167;
        unsigned int read_00167_len;
        unsigned int read_00167_ptr = 0;
        //**** delimited read
        static unsigned char read_00167_delim[] = 
            "\x0a";
        read_00167 = NULL;
        read_00167_len = 0;
        int read_00167_res = delimited_read(0, &read_00167, &read_00167_len, read_00167_delim, 1);
        if (read_00167_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00167_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00167_00000_match;
        pcre *read_00167_00000_pcre = init_regex(read_00167_00000_regex);
        if (read_00167_00000_pcre != NULL) {
            int rc = regex_match(read_00167_00000_pcre, 0, read_00167 + read_00167_ptr, read_00167_len - read_00167_ptr, &read_00167_00000_match);
            if (rc > 0) {
                read_00167_ptr += read_00167_00000_match.match_end - read_00167_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00167_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00167);
        if (read_00167_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00012_00000[] = 
            "\x3a";
        static unsigned int write_00012_00000_len = 1;
        unsigned char *write_00012 = NULL;
        unsigned int write_00012_len = 0;
        write_00012 = append_buf(write_00012, &write_00012_len, write_00012_00000, write_00012_00000_len);
        if (write_00012_len > 0) {
            transmit_all(1, write_00012, write_00012_len);
        }
        free(write_00012);
    } while (0);
    do {
        unsigned char *read_00168;
        unsigned int read_00168_len;
        unsigned int read_00168_ptr = 0;
        //**** delimited read
        static unsigned char read_00168_delim[] = 
            "\x0a";
        read_00168 = NULL;
        read_00168_len = 0;
        int read_00168_res = delimited_read(0, &read_00168, &read_00168_len, read_00168_delim, 1);
        if (read_00168_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00168_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00168_00000_match;
        pcre *read_00168_00000_pcre = init_regex(read_00168_00000_regex);
        if (read_00168_00000_pcre != NULL) {
            int rc = regex_match(read_00168_00000_pcre, 0, read_00168 + read_00168_ptr, read_00168_len - read_00168_ptr, &read_00168_00000_match);
            if (rc > 0) {
                read_00168_ptr += read_00168_00000_match.match_end - read_00168_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00168_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00168);
        if (read_00168_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00169;
        unsigned int read_00169_len;
        unsigned int read_00169_ptr = 0;
        //**** delimited read
        static unsigned char read_00169_delim[] = 
            "\x0a";
        read_00169 = NULL;
        read_00169_len = 0;
        int read_00169_res = delimited_read(0, &read_00169, &read_00169_len, read_00169_delim, 1);
        if (read_00169_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00169_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00169_00000_match;
        pcre *read_00169_00000_pcre = init_regex(read_00169_00000_regex);
        if (read_00169_00000_pcre != NULL) {
            int rc = regex_match(read_00169_00000_pcre, 0, read_00169 + read_00169_ptr, read_00169_len - read_00169_ptr, &read_00169_00000_match);
            if (rc > 0) {
                read_00169_ptr += read_00169_00000_match.match_end - read_00169_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00169_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00169);
        if (read_00169_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00170;
        unsigned int read_00170_len;
        unsigned int read_00170_ptr = 0;
        //**** delimited read
        static unsigned char read_00170_delim[] = 
            "\x0a";
        read_00170 = NULL;
        read_00170_len = 0;
        int read_00170_res = delimited_read(0, &read_00170, &read_00170_len, read_00170_delim, 1);
        if (read_00170_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00170_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00170_00000_match;
        pcre *read_00170_00000_pcre = init_regex(read_00170_00000_regex);
        if (read_00170_00000_pcre != NULL) {
            int rc = regex_match(read_00170_00000_pcre, 0, read_00170 + read_00170_ptr, read_00170_len - read_00170_ptr, &read_00170_00000_match);
            if (rc > 0) {
                read_00170_ptr += read_00170_00000_match.match_end - read_00170_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00170_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00170);
        if (read_00170_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00171;
        unsigned int read_00171_len;
        unsigned int read_00171_ptr = 0;
        //**** delimited read
        static unsigned char read_00171_delim[] = 
            "\x0a";
        read_00171 = NULL;
        read_00171_len = 0;
        int read_00171_res = delimited_read(0, &read_00171, &read_00171_len, read_00171_delim, 1);
        if (read_00171_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00171_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00171_00000_match;
        pcre *read_00171_00000_pcre = init_regex(read_00171_00000_regex);
        if (read_00171_00000_pcre != NULL) {
            int rc = regex_match(read_00171_00000_pcre, 0, read_00171 + read_00171_ptr, read_00171_len - read_00171_ptr, &read_00171_00000_match);
            if (rc > 0) {
                read_00171_ptr += read_00171_00000_match.match_end - read_00171_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00171_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00171);
        if (read_00171_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00172;
        unsigned int read_00172_len;
        unsigned int read_00172_ptr = 0;
        //**** delimited read
        static unsigned char read_00172_delim[] = 
            "\x0a";
        read_00172 = NULL;
        read_00172_len = 0;
        int read_00172_res = delimited_read(0, &read_00172, &read_00172_len, read_00172_delim, 1);
        if (read_00172_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00172_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00172_00000_match;
        pcre *read_00172_00000_pcre = init_regex(read_00172_00000_regex);
        if (read_00172_00000_pcre != NULL) {
            int rc = regex_match(read_00172_00000_pcre, 0, read_00172 + read_00172_ptr, read_00172_len - read_00172_ptr, &read_00172_00000_match);
            if (rc > 0) {
                read_00172_ptr += read_00172_00000_match.match_end - read_00172_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00172_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00172);
        if (read_00172_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00173;
        unsigned int read_00173_len;
        unsigned int read_00173_ptr = 0;
        //**** delimited read
        static unsigned char read_00173_delim[] = 
            "\x0a";
        read_00173 = NULL;
        read_00173_len = 0;
        int read_00173_res = delimited_read(0, &read_00173, &read_00173_len, read_00173_delim, 1);
        if (read_00173_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00173_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00173_00000_match;
        pcre *read_00173_00000_pcre = init_regex(read_00173_00000_regex);
        if (read_00173_00000_pcre != NULL) {
            int rc = regex_match(read_00173_00000_pcre, 0, read_00173 + read_00173_ptr, read_00173_len - read_00173_ptr, &read_00173_00000_match);
            if (rc > 0) {
                read_00173_ptr += read_00173_00000_match.match_end - read_00173_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00173_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00173);
        if (read_00173_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00174;
        unsigned int read_00174_len;
        unsigned int read_00174_ptr = 0;
        //**** delimited read
        static unsigned char read_00174_delim[] = 
            "\x0a";
        read_00174 = NULL;
        read_00174_len = 0;
        int read_00174_res = delimited_read(0, &read_00174, &read_00174_len, read_00174_delim, 1);
        if (read_00174_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00174_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00174_00000_match;
        pcre *read_00174_00000_pcre = init_regex(read_00174_00000_regex);
        if (read_00174_00000_pcre != NULL) {
            int rc = regex_match(read_00174_00000_pcre, 0, read_00174 + read_00174_ptr, read_00174_len - read_00174_ptr, &read_00174_00000_match);
            if (rc > 0) {
                read_00174_ptr += read_00174_00000_match.match_end - read_00174_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00174_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00174);
        if (read_00174_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00175;
        unsigned int read_00175_len;
        unsigned int read_00175_ptr = 0;
        //**** delimited read
        static unsigned char read_00175_delim[] = 
            "\x0a";
        read_00175 = NULL;
        read_00175_len = 0;
        int read_00175_res = delimited_read(0, &read_00175, &read_00175_len, read_00175_delim, 1);
        if (read_00175_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00175_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00175_00000_match;
        pcre *read_00175_00000_pcre = init_regex(read_00175_00000_regex);
        if (read_00175_00000_pcre != NULL) {
            int rc = regex_match(read_00175_00000_pcre, 0, read_00175 + read_00175_ptr, read_00175_len - read_00175_ptr, &read_00175_00000_match);
            if (rc > 0) {
                read_00175_ptr += read_00175_00000_match.match_end - read_00175_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00175_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00175);
        if (read_00175_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00176;
        unsigned int read_00176_len;
        unsigned int read_00176_ptr = 0;
        //**** delimited read
        static unsigned char read_00176_delim[] = 
            "\x0a";
        read_00176 = NULL;
        read_00176_len = 0;
        int read_00176_res = delimited_read(0, &read_00176, &read_00176_len, read_00176_delim, 1);
        if (read_00176_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00176_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00176_00000_match;
        pcre *read_00176_00000_pcre = init_regex(read_00176_00000_regex);
        if (read_00176_00000_pcre != NULL) {
            int rc = regex_match(read_00176_00000_pcre, 0, read_00176 + read_00176_ptr, read_00176_len - read_00176_ptr, &read_00176_00000_match);
            if (rc > 0) {
                read_00176_ptr += read_00176_00000_match.match_end - read_00176_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00176_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00176);
        if (read_00176_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00177;
        unsigned int read_00177_len;
        unsigned int read_00177_ptr = 0;
        //**** delimited read
        static unsigned char read_00177_delim[] = 
            "\x0a";
        read_00177 = NULL;
        read_00177_len = 0;
        int read_00177_res = delimited_read(0, &read_00177, &read_00177_len, read_00177_delim, 1);
        if (read_00177_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00177_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00177_00000_match;
        pcre *read_00177_00000_pcre = init_regex(read_00177_00000_regex);
        if (read_00177_00000_pcre != NULL) {
            int rc = regex_match(read_00177_00000_pcre, 0, read_00177 + read_00177_ptr, read_00177_len - read_00177_ptr, &read_00177_00000_match);
            if (rc > 0) {
                read_00177_ptr += read_00177_00000_match.match_end - read_00177_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00177_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00177);
        if (read_00177_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00178;
        unsigned int read_00178_len;
        unsigned int read_00178_ptr = 0;
        //**** delimited read
        static unsigned char read_00178_delim[] = 
            "\x0a";
        read_00178 = NULL;
        read_00178_len = 0;
        int read_00178_res = delimited_read(0, &read_00178, &read_00178_len, read_00178_delim, 1);
        if (read_00178_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00178_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00178_00000_match;
        pcre *read_00178_00000_pcre = init_regex(read_00178_00000_regex);
        if (read_00178_00000_pcre != NULL) {
            int rc = regex_match(read_00178_00000_pcre, 0, read_00178 + read_00178_ptr, read_00178_len - read_00178_ptr, &read_00178_00000_match);
            if (rc > 0) {
                read_00178_ptr += read_00178_00000_match.match_end - read_00178_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00178_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00178);
        if (read_00178_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00179;
        unsigned int read_00179_len;
        unsigned int read_00179_ptr = 0;
        //**** delimited read
        static unsigned char read_00179_delim[] = 
            "\x0a";
        read_00179 = NULL;
        read_00179_len = 0;
        int read_00179_res = delimited_read(0, &read_00179, &read_00179_len, read_00179_delim, 1);
        if (read_00179_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00179_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00179_00000_match;
        pcre *read_00179_00000_pcre = init_regex(read_00179_00000_regex);
        if (read_00179_00000_pcre != NULL) {
            int rc = regex_match(read_00179_00000_pcre, 0, read_00179 + read_00179_ptr, read_00179_len - read_00179_ptr, &read_00179_00000_match);
            if (rc > 0) {
                read_00179_ptr += read_00179_00000_match.match_end - read_00179_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00179_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00179);
        if (read_00179_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00013_00000[] = 
            "\x3a";
        static unsigned int write_00013_00000_len = 1;
        unsigned char *write_00013 = NULL;
        unsigned int write_00013_len = 0;
        write_00013 = append_buf(write_00013, &write_00013_len, write_00013_00000, write_00013_00000_len);
        if (write_00013_len > 0) {
            transmit_all(1, write_00013, write_00013_len);
        }
        free(write_00013);
    } while (0);
    do {
        unsigned char *read_00180;
        unsigned int read_00180_len;
        unsigned int read_00180_ptr = 0;
        //**** delimited read
        static unsigned char read_00180_delim[] = 
            "\x0a";
        read_00180 = NULL;
        read_00180_len = 0;
        int read_00180_res = delimited_read(0, &read_00180, &read_00180_len, read_00180_delim, 1);
        if (read_00180_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00180_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00180_00000_match;
        pcre *read_00180_00000_pcre = init_regex(read_00180_00000_regex);
        if (read_00180_00000_pcre != NULL) {
            int rc = regex_match(read_00180_00000_pcre, 0, read_00180 + read_00180_ptr, read_00180_len - read_00180_ptr, &read_00180_00000_match);
            if (rc > 0) {
                read_00180_ptr += read_00180_00000_match.match_end - read_00180_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00180_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00180);
        if (read_00180_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00181;
        unsigned int read_00181_len;
        unsigned int read_00181_ptr = 0;
        //**** delimited read
        static unsigned char read_00181_delim[] = 
            "\x0a";
        read_00181 = NULL;
        read_00181_len = 0;
        int read_00181_res = delimited_read(0, &read_00181, &read_00181_len, read_00181_delim, 1);
        if (read_00181_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00181_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00181_00000_match;
        pcre *read_00181_00000_pcre = init_regex(read_00181_00000_regex);
        if (read_00181_00000_pcre != NULL) {
            int rc = regex_match(read_00181_00000_pcre, 0, read_00181 + read_00181_ptr, read_00181_len - read_00181_ptr, &read_00181_00000_match);
            if (rc > 0) {
                read_00181_ptr += read_00181_00000_match.match_end - read_00181_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00181_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00181);
        if (read_00181_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00182;
        unsigned int read_00182_len;
        unsigned int read_00182_ptr = 0;
        //**** delimited read
        static unsigned char read_00182_delim[] = 
            "\x0a";
        read_00182 = NULL;
        read_00182_len = 0;
        int read_00182_res = delimited_read(0, &read_00182, &read_00182_len, read_00182_delim, 1);
        if (read_00182_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00182_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00182_00000_match;
        pcre *read_00182_00000_pcre = init_regex(read_00182_00000_regex);
        if (read_00182_00000_pcre != NULL) {
            int rc = regex_match(read_00182_00000_pcre, 0, read_00182 + read_00182_ptr, read_00182_len - read_00182_ptr, &read_00182_00000_match);
            if (rc > 0) {
                read_00182_ptr += read_00182_00000_match.match_end - read_00182_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00182_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00182);
        if (read_00182_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00183;
        unsigned int read_00183_len;
        unsigned int read_00183_ptr = 0;
        //**** delimited read
        static unsigned char read_00183_delim[] = 
            "\x0a";
        read_00183 = NULL;
        read_00183_len = 0;
        int read_00183_res = delimited_read(0, &read_00183, &read_00183_len, read_00183_delim, 1);
        if (read_00183_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00183_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00183_00000_match;
        pcre *read_00183_00000_pcre = init_regex(read_00183_00000_regex);
        if (read_00183_00000_pcre != NULL) {
            int rc = regex_match(read_00183_00000_pcre, 0, read_00183 + read_00183_ptr, read_00183_len - read_00183_ptr, &read_00183_00000_match);
            if (rc > 0) {
                read_00183_ptr += read_00183_00000_match.match_end - read_00183_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00183_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00183);
        if (read_00183_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00184;
        unsigned int read_00184_len;
        unsigned int read_00184_ptr = 0;
        //**** delimited read
        static unsigned char read_00184_delim[] = 
            "\x0a";
        read_00184 = NULL;
        read_00184_len = 0;
        int read_00184_res = delimited_read(0, &read_00184, &read_00184_len, read_00184_delim, 1);
        if (read_00184_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00184_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00184_00000_match;
        pcre *read_00184_00000_pcre = init_regex(read_00184_00000_regex);
        if (read_00184_00000_pcre != NULL) {
            int rc = regex_match(read_00184_00000_pcre, 0, read_00184 + read_00184_ptr, read_00184_len - read_00184_ptr, &read_00184_00000_match);
            if (rc > 0) {
                read_00184_ptr += read_00184_00000_match.match_end - read_00184_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00184_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00184);
        if (read_00184_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00185;
        unsigned int read_00185_len;
        unsigned int read_00185_ptr = 0;
        //**** delimited read
        static unsigned char read_00185_delim[] = 
            "\x0a";
        read_00185 = NULL;
        read_00185_len = 0;
        int read_00185_res = delimited_read(0, &read_00185, &read_00185_len, read_00185_delim, 1);
        if (read_00185_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00185_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00185_00000_match;
        pcre *read_00185_00000_pcre = init_regex(read_00185_00000_regex);
        if (read_00185_00000_pcre != NULL) {
            int rc = regex_match(read_00185_00000_pcre, 0, read_00185 + read_00185_ptr, read_00185_len - read_00185_ptr, &read_00185_00000_match);
            if (rc > 0) {
                read_00185_ptr += read_00185_00000_match.match_end - read_00185_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00185_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00185);
        if (read_00185_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00186;
        unsigned int read_00186_len;
        unsigned int read_00186_ptr = 0;
        //**** delimited read
        static unsigned char read_00186_delim[] = 
            "\x0a";
        read_00186 = NULL;
        read_00186_len = 0;
        int read_00186_res = delimited_read(0, &read_00186, &read_00186_len, read_00186_delim, 1);
        if (read_00186_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00186_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00186_00000_match;
        pcre *read_00186_00000_pcre = init_regex(read_00186_00000_regex);
        if (read_00186_00000_pcre != NULL) {
            int rc = regex_match(read_00186_00000_pcre, 0, read_00186 + read_00186_ptr, read_00186_len - read_00186_ptr, &read_00186_00000_match);
            if (rc > 0) {
                read_00186_ptr += read_00186_00000_match.match_end - read_00186_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00186_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00186);
        if (read_00186_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00187;
        unsigned int read_00187_len;
        unsigned int read_00187_ptr = 0;
        //**** delimited read
        static unsigned char read_00187_delim[] = 
            "\x0a";
        read_00187 = NULL;
        read_00187_len = 0;
        int read_00187_res = delimited_read(0, &read_00187, &read_00187_len, read_00187_delim, 1);
        if (read_00187_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00187_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00187_00000_match;
        pcre *read_00187_00000_pcre = init_regex(read_00187_00000_regex);
        if (read_00187_00000_pcre != NULL) {
            int rc = regex_match(read_00187_00000_pcre, 0, read_00187 + read_00187_ptr, read_00187_len - read_00187_ptr, &read_00187_00000_match);
            if (rc > 0) {
                read_00187_ptr += read_00187_00000_match.match_end - read_00187_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00187_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00187);
        if (read_00187_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00188;
        unsigned int read_00188_len;
        unsigned int read_00188_ptr = 0;
        //**** delimited read
        static unsigned char read_00188_delim[] = 
            "\x0a";
        read_00188 = NULL;
        read_00188_len = 0;
        int read_00188_res = delimited_read(0, &read_00188, &read_00188_len, read_00188_delim, 1);
        if (read_00188_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00188_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00188_00000_match;
        pcre *read_00188_00000_pcre = init_regex(read_00188_00000_regex);
        if (read_00188_00000_pcre != NULL) {
            int rc = regex_match(read_00188_00000_pcre, 0, read_00188 + read_00188_ptr, read_00188_len - read_00188_ptr, &read_00188_00000_match);
            if (rc > 0) {
                read_00188_ptr += read_00188_00000_match.match_end - read_00188_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00188_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00188);
        if (read_00188_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00189;
        unsigned int read_00189_len;
        unsigned int read_00189_ptr = 0;
        //**** delimited read
        static unsigned char read_00189_delim[] = 
            "\x0a";
        read_00189 = NULL;
        read_00189_len = 0;
        int read_00189_res = delimited_read(0, &read_00189, &read_00189_len, read_00189_delim, 1);
        if (read_00189_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00189_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00189_00000_match;
        pcre *read_00189_00000_pcre = init_regex(read_00189_00000_regex);
        if (read_00189_00000_pcre != NULL) {
            int rc = regex_match(read_00189_00000_pcre, 0, read_00189 + read_00189_ptr, read_00189_len - read_00189_ptr, &read_00189_00000_match);
            if (rc > 0) {
                read_00189_ptr += read_00189_00000_match.match_end - read_00189_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00189_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00189);
        if (read_00189_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00190;
        unsigned int read_00190_len;
        unsigned int read_00190_ptr = 0;
        //**** delimited read
        static unsigned char read_00190_delim[] = 
            "\x0a";
        read_00190 = NULL;
        read_00190_len = 0;
        int read_00190_res = delimited_read(0, &read_00190, &read_00190_len, read_00190_delim, 1);
        if (read_00190_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00190_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00190_00000_match;
        pcre *read_00190_00000_pcre = init_regex(read_00190_00000_regex);
        if (read_00190_00000_pcre != NULL) {
            int rc = regex_match(read_00190_00000_pcre, 0, read_00190 + read_00190_ptr, read_00190_len - read_00190_ptr, &read_00190_00000_match);
            if (rc > 0) {
                read_00190_ptr += read_00190_00000_match.match_end - read_00190_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00190_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00190);
        if (read_00190_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00191;
        unsigned int read_00191_len;
        unsigned int read_00191_ptr = 0;
        //**** delimited read
        static unsigned char read_00191_delim[] = 
            "\x0a";
        read_00191 = NULL;
        read_00191_len = 0;
        int read_00191_res = delimited_read(0, &read_00191, &read_00191_len, read_00191_delim, 1);
        if (read_00191_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00191_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00191_00000_match;
        pcre *read_00191_00000_pcre = init_regex(read_00191_00000_regex);
        if (read_00191_00000_pcre != NULL) {
            int rc = regex_match(read_00191_00000_pcre, 0, read_00191 + read_00191_ptr, read_00191_len - read_00191_ptr, &read_00191_00000_match);
            if (rc > 0) {
                read_00191_ptr += read_00191_00000_match.match_end - read_00191_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00191_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00191);
        if (read_00191_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00014_00000[] = 
            "\x3a";
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
        unsigned char *read_00192;
        unsigned int read_00192_len;
        unsigned int read_00192_ptr = 0;
        //**** delimited read
        static unsigned char read_00192_delim[] = 
            "\x0a";
        read_00192 = NULL;
        read_00192_len = 0;
        int read_00192_res = delimited_read(0, &read_00192, &read_00192_len, read_00192_delim, 1);
        if (read_00192_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00192_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00192_00000_match;
        pcre *read_00192_00000_pcre = init_regex(read_00192_00000_regex);
        if (read_00192_00000_pcre != NULL) {
            int rc = regex_match(read_00192_00000_pcre, 0, read_00192 + read_00192_ptr, read_00192_len - read_00192_ptr, &read_00192_00000_match);
            if (rc > 0) {
                read_00192_ptr += read_00192_00000_match.match_end - read_00192_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00192_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00192);
        if (read_00192_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00193;
        unsigned int read_00193_len;
        unsigned int read_00193_ptr = 0;
        //**** delimited read
        static unsigned char read_00193_delim[] = 
            "\x0a";
        read_00193 = NULL;
        read_00193_len = 0;
        int read_00193_res = delimited_read(0, &read_00193, &read_00193_len, read_00193_delim, 1);
        if (read_00193_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00193_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00193_00000_match;
        pcre *read_00193_00000_pcre = init_regex(read_00193_00000_regex);
        if (read_00193_00000_pcre != NULL) {
            int rc = regex_match(read_00193_00000_pcre, 0, read_00193 + read_00193_ptr, read_00193_len - read_00193_ptr, &read_00193_00000_match);
            if (rc > 0) {
                read_00193_ptr += read_00193_00000_match.match_end - read_00193_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00193_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00193);
        if (read_00193_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00194;
        unsigned int read_00194_len;
        unsigned int read_00194_ptr = 0;
        //**** delimited read
        static unsigned char read_00194_delim[] = 
            "\x0a";
        read_00194 = NULL;
        read_00194_len = 0;
        int read_00194_res = delimited_read(0, &read_00194, &read_00194_len, read_00194_delim, 1);
        if (read_00194_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00194_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00194_00000_match;
        pcre *read_00194_00000_pcre = init_regex(read_00194_00000_regex);
        if (read_00194_00000_pcre != NULL) {
            int rc = regex_match(read_00194_00000_pcre, 0, read_00194 + read_00194_ptr, read_00194_len - read_00194_ptr, &read_00194_00000_match);
            if (rc > 0) {
                read_00194_ptr += read_00194_00000_match.match_end - read_00194_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00194_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00194);
        if (read_00194_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00195;
        unsigned int read_00195_len;
        unsigned int read_00195_ptr = 0;
        //**** delimited read
        static unsigned char read_00195_delim[] = 
            "\x0a";
        read_00195 = NULL;
        read_00195_len = 0;
        int read_00195_res = delimited_read(0, &read_00195, &read_00195_len, read_00195_delim, 1);
        if (read_00195_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00195_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00195_00000_match;
        pcre *read_00195_00000_pcre = init_regex(read_00195_00000_regex);
        if (read_00195_00000_pcre != NULL) {
            int rc = regex_match(read_00195_00000_pcre, 0, read_00195 + read_00195_ptr, read_00195_len - read_00195_ptr, &read_00195_00000_match);
            if (rc > 0) {
                read_00195_ptr += read_00195_00000_match.match_end - read_00195_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00195_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00195);
        if (read_00195_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00196;
        unsigned int read_00196_len;
        unsigned int read_00196_ptr = 0;
        //**** delimited read
        static unsigned char read_00196_delim[] = 
            "\x0a";
        read_00196 = NULL;
        read_00196_len = 0;
        int read_00196_res = delimited_read(0, &read_00196, &read_00196_len, read_00196_delim, 1);
        if (read_00196_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00196_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00196_00000_match;
        pcre *read_00196_00000_pcre = init_regex(read_00196_00000_regex);
        if (read_00196_00000_pcre != NULL) {
            int rc = regex_match(read_00196_00000_pcre, 0, read_00196 + read_00196_ptr, read_00196_len - read_00196_ptr, &read_00196_00000_match);
            if (rc > 0) {
                read_00196_ptr += read_00196_00000_match.match_end - read_00196_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00196_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00196);
        if (read_00196_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00197;
        unsigned int read_00197_len;
        unsigned int read_00197_ptr = 0;
        //**** delimited read
        static unsigned char read_00197_delim[] = 
            "\x0a";
        read_00197 = NULL;
        read_00197_len = 0;
        int read_00197_res = delimited_read(0, &read_00197, &read_00197_len, read_00197_delim, 1);
        if (read_00197_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00197_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00197_00000_match;
        pcre *read_00197_00000_pcre = init_regex(read_00197_00000_regex);
        if (read_00197_00000_pcre != NULL) {
            int rc = regex_match(read_00197_00000_pcre, 0, read_00197 + read_00197_ptr, read_00197_len - read_00197_ptr, &read_00197_00000_match);
            if (rc > 0) {
                read_00197_ptr += read_00197_00000_match.match_end - read_00197_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00197_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00197);
        if (read_00197_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00198;
        unsigned int read_00198_len;
        unsigned int read_00198_ptr = 0;
        //**** delimited read
        static unsigned char read_00198_delim[] = 
            "\x0a";
        read_00198 = NULL;
        read_00198_len = 0;
        int read_00198_res = delimited_read(0, &read_00198, &read_00198_len, read_00198_delim, 1);
        if (read_00198_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00198_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00198_00000_match;
        pcre *read_00198_00000_pcre = init_regex(read_00198_00000_regex);
        if (read_00198_00000_pcre != NULL) {
            int rc = regex_match(read_00198_00000_pcre, 0, read_00198 + read_00198_ptr, read_00198_len - read_00198_ptr, &read_00198_00000_match);
            if (rc > 0) {
                read_00198_ptr += read_00198_00000_match.match_end - read_00198_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00198_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00198);
        if (read_00198_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00199;
        unsigned int read_00199_len;
        unsigned int read_00199_ptr = 0;
        //**** delimited read
        static unsigned char read_00199_delim[] = 
            "\x0a";
        read_00199 = NULL;
        read_00199_len = 0;
        int read_00199_res = delimited_read(0, &read_00199, &read_00199_len, read_00199_delim, 1);
        if (read_00199_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00199_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00199_00000_match;
        pcre *read_00199_00000_pcre = init_regex(read_00199_00000_regex);
        if (read_00199_00000_pcre != NULL) {
            int rc = regex_match(read_00199_00000_pcre, 0, read_00199 + read_00199_ptr, read_00199_len - read_00199_ptr, &read_00199_00000_match);
            if (rc > 0) {
                read_00199_ptr += read_00199_00000_match.match_end - read_00199_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00199_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00199);
        if (read_00199_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00200;
        unsigned int read_00200_len;
        unsigned int read_00200_ptr = 0;
        //**** delimited read
        static unsigned char read_00200_delim[] = 
            "\x0a";
        read_00200 = NULL;
        read_00200_len = 0;
        int read_00200_res = delimited_read(0, &read_00200, &read_00200_len, read_00200_delim, 1);
        if (read_00200_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00200_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00200_00000_match;
        pcre *read_00200_00000_pcre = init_regex(read_00200_00000_regex);
        if (read_00200_00000_pcre != NULL) {
            int rc = regex_match(read_00200_00000_pcre, 0, read_00200 + read_00200_ptr, read_00200_len - read_00200_ptr, &read_00200_00000_match);
            if (rc > 0) {
                read_00200_ptr += read_00200_00000_match.match_end - read_00200_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00200_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00200);
        if (read_00200_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00201;
        unsigned int read_00201_len;
        unsigned int read_00201_ptr = 0;
        //**** delimited read
        static unsigned char read_00201_delim[] = 
            "\x0a";
        read_00201 = NULL;
        read_00201_len = 0;
        int read_00201_res = delimited_read(0, &read_00201, &read_00201_len, read_00201_delim, 1);
        if (read_00201_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00201_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00201_00000_match;
        pcre *read_00201_00000_pcre = init_regex(read_00201_00000_regex);
        if (read_00201_00000_pcre != NULL) {
            int rc = regex_match(read_00201_00000_pcre, 0, read_00201 + read_00201_ptr, read_00201_len - read_00201_ptr, &read_00201_00000_match);
            if (rc > 0) {
                read_00201_ptr += read_00201_00000_match.match_end - read_00201_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00201_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00201);
        if (read_00201_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00202;
        unsigned int read_00202_len;
        unsigned int read_00202_ptr = 0;
        //**** delimited read
        static unsigned char read_00202_delim[] = 
            "\x0a";
        read_00202 = NULL;
        read_00202_len = 0;
        int read_00202_res = delimited_read(0, &read_00202, &read_00202_len, read_00202_delim, 1);
        if (read_00202_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00202_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00202_00000_match;
        pcre *read_00202_00000_pcre = init_regex(read_00202_00000_regex);
        if (read_00202_00000_pcre != NULL) {
            int rc = regex_match(read_00202_00000_pcre, 0, read_00202 + read_00202_ptr, read_00202_len - read_00202_ptr, &read_00202_00000_match);
            if (rc > 0) {
                read_00202_ptr += read_00202_00000_match.match_end - read_00202_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00202_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00202);
        if (read_00202_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00203;
        unsigned int read_00203_len;
        unsigned int read_00203_ptr = 0;
        //**** delimited read
        static unsigned char read_00203_delim[] = 
            "\x0a";
        read_00203 = NULL;
        read_00203_len = 0;
        int read_00203_res = delimited_read(0, &read_00203, &read_00203_len, read_00203_delim, 1);
        if (read_00203_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00203_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00203_00000_match;
        pcre *read_00203_00000_pcre = init_regex(read_00203_00000_regex);
        if (read_00203_00000_pcre != NULL) {
            int rc = regex_match(read_00203_00000_pcre, 0, read_00203 + read_00203_ptr, read_00203_len - read_00203_ptr, &read_00203_00000_match);
            if (rc > 0) {
                read_00203_ptr += read_00203_00000_match.match_end - read_00203_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00203_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00203);
        if (read_00203_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00015_00000[] = 
            "\x3a";
        static unsigned int write_00015_00000_len = 1;
        unsigned char *write_00015 = NULL;
        unsigned int write_00015_len = 0;
        write_00015 = append_buf(write_00015, &write_00015_len, write_00015_00000, write_00015_00000_len);
        if (write_00015_len > 0) {
            transmit_all(1, write_00015, write_00015_len);
        }
        free(write_00015);
    } while (0);
    do {
        unsigned char *read_00204;
        unsigned int read_00204_len;
        unsigned int read_00204_ptr = 0;
        //**** delimited read
        static unsigned char read_00204_delim[] = 
            "\x0a";
        read_00204 = NULL;
        read_00204_len = 0;
        int read_00204_res = delimited_read(0, &read_00204, &read_00204_len, read_00204_delim, 1);
        if (read_00204_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00204_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00204_00000_match;
        pcre *read_00204_00000_pcre = init_regex(read_00204_00000_regex);
        if (read_00204_00000_pcre != NULL) {
            int rc = regex_match(read_00204_00000_pcre, 0, read_00204 + read_00204_ptr, read_00204_len - read_00204_ptr, &read_00204_00000_match);
            if (rc > 0) {
                read_00204_ptr += read_00204_00000_match.match_end - read_00204_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00204_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00204);
        if (read_00204_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00205;
        unsigned int read_00205_len;
        unsigned int read_00205_ptr = 0;
        //**** delimited read
        static unsigned char read_00205_delim[] = 
            "\x0a";
        read_00205 = NULL;
        read_00205_len = 0;
        int read_00205_res = delimited_read(0, &read_00205, &read_00205_len, read_00205_delim, 1);
        if (read_00205_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00205_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00205_00000_match;
        pcre *read_00205_00000_pcre = init_regex(read_00205_00000_regex);
        if (read_00205_00000_pcre != NULL) {
            int rc = regex_match(read_00205_00000_pcre, 0, read_00205 + read_00205_ptr, read_00205_len - read_00205_ptr, &read_00205_00000_match);
            if (rc > 0) {
                read_00205_ptr += read_00205_00000_match.match_end - read_00205_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00205_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00205);
        if (read_00205_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00206;
        unsigned int read_00206_len;
        unsigned int read_00206_ptr = 0;
        //**** delimited read
        static unsigned char read_00206_delim[] = 
            "\x0a";
        read_00206 = NULL;
        read_00206_len = 0;
        int read_00206_res = delimited_read(0, &read_00206, &read_00206_len, read_00206_delim, 1);
        if (read_00206_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00206_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00206_00000_match;
        pcre *read_00206_00000_pcre = init_regex(read_00206_00000_regex);
        if (read_00206_00000_pcre != NULL) {
            int rc = regex_match(read_00206_00000_pcre, 0, read_00206 + read_00206_ptr, read_00206_len - read_00206_ptr, &read_00206_00000_match);
            if (rc > 0) {
                read_00206_ptr += read_00206_00000_match.match_end - read_00206_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00206_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00206);
        if (read_00206_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00207;
        unsigned int read_00207_len;
        unsigned int read_00207_ptr = 0;
        //**** delimited read
        static unsigned char read_00207_delim[] = 
            "\x0a";
        read_00207 = NULL;
        read_00207_len = 0;
        int read_00207_res = delimited_read(0, &read_00207, &read_00207_len, read_00207_delim, 1);
        if (read_00207_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00207_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00207_00000_match;
        pcre *read_00207_00000_pcre = init_regex(read_00207_00000_regex);
        if (read_00207_00000_pcre != NULL) {
            int rc = regex_match(read_00207_00000_pcre, 0, read_00207 + read_00207_ptr, read_00207_len - read_00207_ptr, &read_00207_00000_match);
            if (rc > 0) {
                read_00207_ptr += read_00207_00000_match.match_end - read_00207_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00207_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00207);
        if (read_00207_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00208;
        unsigned int read_00208_len;
        unsigned int read_00208_ptr = 0;
        //**** delimited read
        static unsigned char read_00208_delim[] = 
            "\x0a";
        read_00208 = NULL;
        read_00208_len = 0;
        int read_00208_res = delimited_read(0, &read_00208, &read_00208_len, read_00208_delim, 1);
        if (read_00208_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00208_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00208_00000_match;
        pcre *read_00208_00000_pcre = init_regex(read_00208_00000_regex);
        if (read_00208_00000_pcre != NULL) {
            int rc = regex_match(read_00208_00000_pcre, 0, read_00208 + read_00208_ptr, read_00208_len - read_00208_ptr, &read_00208_00000_match);
            if (rc > 0) {
                read_00208_ptr += read_00208_00000_match.match_end - read_00208_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00208_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00208);
        if (read_00208_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00209;
        unsigned int read_00209_len;
        unsigned int read_00209_ptr = 0;
        //**** delimited read
        static unsigned char read_00209_delim[] = 
            "\x0a";
        read_00209 = NULL;
        read_00209_len = 0;
        int read_00209_res = delimited_read(0, &read_00209, &read_00209_len, read_00209_delim, 1);
        if (read_00209_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00209_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00209_00000_match;
        pcre *read_00209_00000_pcre = init_regex(read_00209_00000_regex);
        if (read_00209_00000_pcre != NULL) {
            int rc = regex_match(read_00209_00000_pcre, 0, read_00209 + read_00209_ptr, read_00209_len - read_00209_ptr, &read_00209_00000_match);
            if (rc > 0) {
                read_00209_ptr += read_00209_00000_match.match_end - read_00209_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00209_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00209);
        if (read_00209_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00210;
        unsigned int read_00210_len;
        unsigned int read_00210_ptr = 0;
        //**** delimited read
        static unsigned char read_00210_delim[] = 
            "\x0a";
        read_00210 = NULL;
        read_00210_len = 0;
        int read_00210_res = delimited_read(0, &read_00210, &read_00210_len, read_00210_delim, 1);
        if (read_00210_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00210_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00210_00000_match;
        pcre *read_00210_00000_pcre = init_regex(read_00210_00000_regex);
        if (read_00210_00000_pcre != NULL) {
            int rc = regex_match(read_00210_00000_pcre, 0, read_00210 + read_00210_ptr, read_00210_len - read_00210_ptr, &read_00210_00000_match);
            if (rc > 0) {
                read_00210_ptr += read_00210_00000_match.match_end - read_00210_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00210_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00210);
        if (read_00210_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00211;
        unsigned int read_00211_len;
        unsigned int read_00211_ptr = 0;
        //**** delimited read
        static unsigned char read_00211_delim[] = 
            "\x0a";
        read_00211 = NULL;
        read_00211_len = 0;
        int read_00211_res = delimited_read(0, &read_00211, &read_00211_len, read_00211_delim, 1);
        if (read_00211_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00211_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00211_00000_match;
        pcre *read_00211_00000_pcre = init_regex(read_00211_00000_regex);
        if (read_00211_00000_pcre != NULL) {
            int rc = regex_match(read_00211_00000_pcre, 0, read_00211 + read_00211_ptr, read_00211_len - read_00211_ptr, &read_00211_00000_match);
            if (rc > 0) {
                read_00211_ptr += read_00211_00000_match.match_end - read_00211_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00211_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00211);
        if (read_00211_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00212;
        unsigned int read_00212_len;
        unsigned int read_00212_ptr = 0;
        //**** delimited read
        static unsigned char read_00212_delim[] = 
            "\x0a";
        read_00212 = NULL;
        read_00212_len = 0;
        int read_00212_res = delimited_read(0, &read_00212, &read_00212_len, read_00212_delim, 1);
        if (read_00212_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00212_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00212_00000_match;
        pcre *read_00212_00000_pcre = init_regex(read_00212_00000_regex);
        if (read_00212_00000_pcre != NULL) {
            int rc = regex_match(read_00212_00000_pcre, 0, read_00212 + read_00212_ptr, read_00212_len - read_00212_ptr, &read_00212_00000_match);
            if (rc > 0) {
                read_00212_ptr += read_00212_00000_match.match_end - read_00212_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00212_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00212);
        if (read_00212_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00213;
        unsigned int read_00213_len;
        unsigned int read_00213_ptr = 0;
        //**** delimited read
        static unsigned char read_00213_delim[] = 
            "\x0a";
        read_00213 = NULL;
        read_00213_len = 0;
        int read_00213_res = delimited_read(0, &read_00213, &read_00213_len, read_00213_delim, 1);
        if (read_00213_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00213_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00213_00000_match;
        pcre *read_00213_00000_pcre = init_regex(read_00213_00000_regex);
        if (read_00213_00000_pcre != NULL) {
            int rc = regex_match(read_00213_00000_pcre, 0, read_00213 + read_00213_ptr, read_00213_len - read_00213_ptr, &read_00213_00000_match);
            if (rc > 0) {
                read_00213_ptr += read_00213_00000_match.match_end - read_00213_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00213_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00213);
        if (read_00213_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00214;
        unsigned int read_00214_len;
        unsigned int read_00214_ptr = 0;
        //**** delimited read
        static unsigned char read_00214_delim[] = 
            "\x0a";
        read_00214 = NULL;
        read_00214_len = 0;
        int read_00214_res = delimited_read(0, &read_00214, &read_00214_len, read_00214_delim, 1);
        if (read_00214_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00214_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00214_00000_match;
        pcre *read_00214_00000_pcre = init_regex(read_00214_00000_regex);
        if (read_00214_00000_pcre != NULL) {
            int rc = regex_match(read_00214_00000_pcre, 0, read_00214 + read_00214_ptr, read_00214_len - read_00214_ptr, &read_00214_00000_match);
            if (rc > 0) {
                read_00214_ptr += read_00214_00000_match.match_end - read_00214_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00214_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00214);
        if (read_00214_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00215;
        unsigned int read_00215_len;
        unsigned int read_00215_ptr = 0;
        //**** length read
        read_00215_len = 20;
        read_00215 = (unsigned char*)malloc(read_00215_len);
        int read_00215_res = length_read(0, read_00215, read_00215_len);
        if (read_00215_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00215_00000[] = 
            "\x53\x6f\x72\x72\x79\x2c\x20\x74\x68\x65\x20\x77\x6f\x72\x64\x20"
            "\x77\x61\x73\x20";
        read_00215_ptr += data_match(read_00215 + read_00215_ptr, read_00215_len - read_00215_ptr, match_00215_00000, 20);
        free(read_00215);
        if (read_00215_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00216;
        unsigned int read_00216_len;
        unsigned int read_00216_ptr = 0;
        //**** length read
        read_00216_len = 8;
        read_00216 = (unsigned char*)malloc(read_00216_len);
        int read_00216_res = length_read(0, read_00216, read_00216_len);
        if (read_00216_res) {} //silence unused variable warning
        //**** read assign to var "word1" from slice
        assign_from_slice("word1", read_00216, read_00216_len - read_00216_ptr, 0, 0, 1);
        free(read_00216);
        if (read_00216_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00217;
        unsigned int read_00217_len;
        unsigned int read_00217_ptr = 0;
        //**** delimited read
        static unsigned char read_00217_delim[] = 
            "\x0a";
        read_00217 = NULL;
        read_00217_len = 0;
        int read_00217_res = delimited_read(0, &read_00217, &read_00217_len, read_00217_delim, 1);
        if (read_00217_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00217_00000[] = 
            "\x21\x0a";
        read_00217_ptr += data_match(read_00217 + read_00217_ptr, read_00217_len - read_00217_ptr, match_00217_00000, 2);
        free(read_00217);
        if (read_00217_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00218;
        unsigned int read_00218_len;
        unsigned int read_00218_ptr = 0;
        //**** delimited read
        static unsigned char read_00218_delim[] = 
            "\x0a";
        read_00218 = NULL;
        read_00218_len = 0;
        int read_00218_res = delimited_read(0, &read_00218, &read_00218_len, read_00218_delim, 1);
        if (read_00218_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00218_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00218_ptr += data_match(read_00218 + read_00218_ptr, read_00218_len - read_00218_ptr, match_00218_00000, 22);
        free(read_00218);
        if (read_00218_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00219;
        unsigned int read_00219_len;
        unsigned int read_00219_ptr = 0;
        //**** delimited read
        static unsigned char read_00219_delim[] = 
            "\x0a";
        read_00219 = NULL;
        read_00219_len = 0;
        int read_00219_res = delimited_read(0, &read_00219, &read_00219_len, read_00219_delim, 1);
        if (read_00219_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00219_00000[] = 
            "\x0a";
        read_00219_ptr += data_match(read_00219 + read_00219_ptr, read_00219_len - read_00219_ptr, match_00219_00000, 1);
        free(read_00219);
        if (read_00219_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00220;
        unsigned int read_00220_len;
        unsigned int read_00220_ptr = 0;
        //**** delimited read
        static unsigned char read_00220_delim[] = 
            "\x0a";
        read_00220 = NULL;
        read_00220_len = 0;
        int read_00220_res = delimited_read(0, &read_00220, &read_00220_len, read_00220_delim, 1);
        if (read_00220_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00220_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00220_ptr += data_match(read_00220 + read_00220_ptr, read_00220_len - read_00220_ptr, match_00220_00000, 11);
        free(read_00220);
        if (read_00220_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00221;
        unsigned int read_00221_len;
        unsigned int read_00221_ptr = 0;
        //**** delimited read
        static unsigned char read_00221_delim[] = 
            "\x0a";
        read_00221 = NULL;
        read_00221_len = 0;
        int read_00221_res = delimited_read(0, &read_00221, &read_00221_len, read_00221_delim, 1);
        if (read_00221_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00221_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00221_ptr += data_match(read_00221 + read_00221_ptr, read_00221_len - read_00221_ptr, match_00221_00000, 9);
        free(read_00221);
        if (read_00221_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00222;
        unsigned int read_00222_len;
        unsigned int read_00222_ptr = 0;
        //**** delimited read
        static unsigned char read_00222_delim[] = 
            "\x0a";
        read_00222 = NULL;
        read_00222_len = 0;
        int read_00222_res = delimited_read(0, &read_00222, &read_00222_len, read_00222_delim, 1);
        if (read_00222_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00222_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00222_ptr += data_match(read_00222 + read_00222_ptr, read_00222_len - read_00222_ptr, match_00222_00000, 10);
        free(read_00222);
        if (read_00222_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00223;
        unsigned int read_00223_len;
        unsigned int read_00223_ptr = 0;
        //**** delimited read
        static unsigned char read_00223_delim[] = 
            "\x0a";
        read_00223 = NULL;
        read_00223_len = 0;
        int read_00223_res = delimited_read(0, &read_00223, &read_00223_len, read_00223_delim, 1);
        if (read_00223_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00223_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00223_ptr += data_match(read_00223 + read_00223_ptr, read_00223_len - read_00223_ptr, match_00223_00000, 20);
        free(read_00223);
        if (read_00223_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00224;
        unsigned int read_00224_len;
        unsigned int read_00224_ptr = 0;
        //**** delimited read
        static unsigned char read_00224_delim[] = 
            "\x0a";
        read_00224 = NULL;
        read_00224_len = 0;
        int read_00224_res = delimited_read(0, &read_00224, &read_00224_len, read_00224_delim, 1);
        if (read_00224_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00224_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00224_ptr += data_match(read_00224 + read_00224_ptr, read_00224_len - read_00224_ptr, match_00224_00000, 15);
        free(read_00224);
        if (read_00224_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00225;
        unsigned int read_00225_len;
        unsigned int read_00225_ptr = 0;
        //**** delimited read
        static unsigned char read_00225_delim[] = 
            "\x0a";
        read_00225 = NULL;
        read_00225_len = 0;
        int read_00225_res = delimited_read(0, &read_00225, &read_00225_len, read_00225_delim, 1);
        if (read_00225_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00225_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00225_ptr += data_match(read_00225 + read_00225_ptr, read_00225_len - read_00225_ptr, match_00225_00000, 20);
        free(read_00225);
        if (read_00225_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00226;
        unsigned int read_00226_len;
        unsigned int read_00226_ptr = 0;
        //**** delimited read
        static unsigned char read_00226_delim[] = 
            "\x0a";
        read_00226 = NULL;
        read_00226_len = 0;
        int read_00226_res = delimited_read(0, &read_00226, &read_00226_len, read_00226_delim, 1);
        if (read_00226_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00226_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00226_ptr += data_match(read_00226 + read_00226_ptr, read_00226_len - read_00226_ptr, match_00226_00000, 28);
        free(read_00226);
        if (read_00226_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00227;
        unsigned int read_00227_len;
        unsigned int read_00227_ptr = 0;
        //**** delimited read
        static unsigned char read_00227_delim[] = 
            "\x0a";
        read_00227 = NULL;
        read_00227_len = 0;
        int read_00227_res = delimited_read(0, &read_00227, &read_00227_len, read_00227_delim, 1);
        if (read_00227_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00227_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00227_ptr += data_match(read_00227 + read_00227_ptr, read_00227_len - read_00227_ptr, match_00227_00000, 8);
        free(read_00227);
        if (read_00227_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00228;
        unsigned int read_00228_len;
        unsigned int read_00228_ptr = 0;
        //**** delimited read
        static unsigned char read_00228_delim[] = 
            "\x0a";
        read_00228 = NULL;
        read_00228_len = 0;
        int read_00228_res = delimited_read(0, &read_00228, &read_00228_len, read_00228_delim, 1);
        if (read_00228_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00228_00000[] = 
            "\x0a";
        read_00228_ptr += data_match(read_00228 + read_00228_ptr, read_00228_len - read_00228_ptr, match_00228_00000, 1);
        free(read_00228);
        if (read_00228_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00016_00000[] = 
            "\x31\x0a";
        static unsigned int write_00016_00000_len = 2;
        unsigned char *write_00016 = NULL;
        unsigned int write_00016_len = 0;
        write_00016 = append_buf(write_00016, &write_00016_len, write_00016_00000, write_00016_00000_len);
        if (write_00016_len > 0) {
            transmit_all(1, write_00016, write_00016_len);
        }
        free(write_00016);
    } while (0);
    do {
        unsigned char *read_00229;
        unsigned int read_00229_len;
        unsigned int read_00229_ptr = 0;
        //**** delimited read
        static unsigned char read_00229_delim[] = 
            "\x0a";
        read_00229 = NULL;
        read_00229_len = 0;
        int read_00229_res = delimited_read(0, &read_00229, &read_00229_len, read_00229_delim, 1);
        if (read_00229_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00229_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00229_00000_match;
        pcre *read_00229_00000_pcre = init_regex(read_00229_00000_regex);
        if (read_00229_00000_pcre != NULL) {
            int rc = regex_match(read_00229_00000_pcre, 0, read_00229 + read_00229_ptr, read_00229_len - read_00229_ptr, &read_00229_00000_match);
            if (rc > 0) {
                read_00229_ptr += read_00229_00000_match.match_end - read_00229_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00229_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00229);
        if (read_00229_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00230;
        unsigned int read_00230_len;
        unsigned int read_00230_ptr = 0;
        //**** delimited read
        static unsigned char read_00230_delim[] = 
            "\x0a";
        read_00230 = NULL;
        read_00230_len = 0;
        int read_00230_res = delimited_read(0, &read_00230, &read_00230_len, read_00230_delim, 1);
        if (read_00230_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00230_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00230_00000_match;
        pcre *read_00230_00000_pcre = init_regex(read_00230_00000_regex);
        if (read_00230_00000_pcre != NULL) {
            int rc = regex_match(read_00230_00000_pcre, 0, read_00230 + read_00230_ptr, read_00230_len - read_00230_ptr, &read_00230_00000_match);
            if (rc > 0) {
                read_00230_ptr += read_00230_00000_match.match_end - read_00230_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00230_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00230);
        if (read_00230_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00231;
        unsigned int read_00231_len;
        unsigned int read_00231_ptr = 0;
        //**** delimited read
        static unsigned char read_00231_delim[] = 
            "\x0a";
        read_00231 = NULL;
        read_00231_len = 0;
        int read_00231_res = delimited_read(0, &read_00231, &read_00231_len, read_00231_delim, 1);
        if (read_00231_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00231_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00231_00000_match;
        pcre *read_00231_00000_pcre = init_regex(read_00231_00000_regex);
        if (read_00231_00000_pcre != NULL) {
            int rc = regex_match(read_00231_00000_pcre, 0, read_00231 + read_00231_ptr, read_00231_len - read_00231_ptr, &read_00231_00000_match);
            if (rc > 0) {
                read_00231_ptr += read_00231_00000_match.match_end - read_00231_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00231_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00231);
        if (read_00231_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00232;
        unsigned int read_00232_len;
        unsigned int read_00232_ptr = 0;
        //**** delimited read
        static unsigned char read_00232_delim[] = 
            "\x0a";
        read_00232 = NULL;
        read_00232_len = 0;
        int read_00232_res = delimited_read(0, &read_00232, &read_00232_len, read_00232_delim, 1);
        if (read_00232_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00232_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00232_00000_match;
        pcre *read_00232_00000_pcre = init_regex(read_00232_00000_regex);
        if (read_00232_00000_pcre != NULL) {
            int rc = regex_match(read_00232_00000_pcre, 0, read_00232 + read_00232_ptr, read_00232_len - read_00232_ptr, &read_00232_00000_match);
            if (rc > 0) {
                read_00232_ptr += read_00232_00000_match.match_end - read_00232_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00232_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00232);
        if (read_00232_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00233;
        unsigned int read_00233_len;
        unsigned int read_00233_ptr = 0;
        //**** delimited read
        static unsigned char read_00233_delim[] = 
            "\x0a";
        read_00233 = NULL;
        read_00233_len = 0;
        int read_00233_res = delimited_read(0, &read_00233, &read_00233_len, read_00233_delim, 1);
        if (read_00233_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00233_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00233_00000_match;
        pcre *read_00233_00000_pcre = init_regex(read_00233_00000_regex);
        if (read_00233_00000_pcre != NULL) {
            int rc = regex_match(read_00233_00000_pcre, 0, read_00233 + read_00233_ptr, read_00233_len - read_00233_ptr, &read_00233_00000_match);
            if (rc > 0) {
                read_00233_ptr += read_00233_00000_match.match_end - read_00233_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00233_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00233);
        if (read_00233_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00234;
        unsigned int read_00234_len;
        unsigned int read_00234_ptr = 0;
        //**** delimited read
        static unsigned char read_00234_delim[] = 
            "\x0a";
        read_00234 = NULL;
        read_00234_len = 0;
        int read_00234_res = delimited_read(0, &read_00234, &read_00234_len, read_00234_delim, 1);
        if (read_00234_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00234_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00234_00000_match;
        pcre *read_00234_00000_pcre = init_regex(read_00234_00000_regex);
        if (read_00234_00000_pcre != NULL) {
            int rc = regex_match(read_00234_00000_pcre, 0, read_00234 + read_00234_ptr, read_00234_len - read_00234_ptr, &read_00234_00000_match);
            if (rc > 0) {
                read_00234_ptr += read_00234_00000_match.match_end - read_00234_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00234_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00234);
        if (read_00234_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00235;
        unsigned int read_00235_len;
        unsigned int read_00235_ptr = 0;
        //**** delimited read
        static unsigned char read_00235_delim[] = 
            "\x0a";
        read_00235 = NULL;
        read_00235_len = 0;
        int read_00235_res = delimited_read(0, &read_00235, &read_00235_len, read_00235_delim, 1);
        if (read_00235_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00235_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00235_00000_match;
        pcre *read_00235_00000_pcre = init_regex(read_00235_00000_regex);
        if (read_00235_00000_pcre != NULL) {
            int rc = regex_match(read_00235_00000_pcre, 0, read_00235 + read_00235_ptr, read_00235_len - read_00235_ptr, &read_00235_00000_match);
            if (rc > 0) {
                read_00235_ptr += read_00235_00000_match.match_end - read_00235_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00235_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00235);
        if (read_00235_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00236;
        unsigned int read_00236_len;
        unsigned int read_00236_ptr = 0;
        //**** delimited read
        static unsigned char read_00236_delim[] = 
            "\x0a";
        read_00236 = NULL;
        read_00236_len = 0;
        int read_00236_res = delimited_read(0, &read_00236, &read_00236_len, read_00236_delim, 1);
        if (read_00236_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00236_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00236_00000_match;
        pcre *read_00236_00000_pcre = init_regex(read_00236_00000_regex);
        if (read_00236_00000_pcre != NULL) {
            int rc = regex_match(read_00236_00000_pcre, 0, read_00236 + read_00236_ptr, read_00236_len - read_00236_ptr, &read_00236_00000_match);
            if (rc > 0) {
                read_00236_ptr += read_00236_00000_match.match_end - read_00236_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00236_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00236);
        if (read_00236_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00237;
        unsigned int read_00237_len;
        unsigned int read_00237_ptr = 0;
        //**** delimited read
        static unsigned char read_00237_delim[] = 
            "\x0a";
        read_00237 = NULL;
        read_00237_len = 0;
        int read_00237_res = delimited_read(0, &read_00237, &read_00237_len, read_00237_delim, 1);
        if (read_00237_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00237_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00237_00000_match;
        pcre *read_00237_00000_pcre = init_regex(read_00237_00000_regex);
        if (read_00237_00000_pcre != NULL) {
            int rc = regex_match(read_00237_00000_pcre, 0, read_00237 + read_00237_ptr, read_00237_len - read_00237_ptr, &read_00237_00000_match);
            if (rc > 0) {
                read_00237_ptr += read_00237_00000_match.match_end - read_00237_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00237_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00237);
        if (read_00237_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00238;
        unsigned int read_00238_len;
        unsigned int read_00238_ptr = 0;
        //**** delimited read
        static unsigned char read_00238_delim[] = 
            "\x0a";
        read_00238 = NULL;
        read_00238_len = 0;
        int read_00238_res = delimited_read(0, &read_00238, &read_00238_len, read_00238_delim, 1);
        if (read_00238_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00238_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00238_00000_match;
        pcre *read_00238_00000_pcre = init_regex(read_00238_00000_regex);
        if (read_00238_00000_pcre != NULL) {
            int rc = regex_match(read_00238_00000_pcre, 0, read_00238 + read_00238_ptr, read_00238_len - read_00238_ptr, &read_00238_00000_match);
            if (rc > 0) {
                read_00238_ptr += read_00238_00000_match.match_end - read_00238_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00238_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00238);
        if (read_00238_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00239;
        unsigned int read_00239_len;
        unsigned int read_00239_ptr = 0;
        //**** delimited read
        static unsigned char read_00239_delim[] = 
            "\x0a";
        read_00239 = NULL;
        read_00239_len = 0;
        int read_00239_res = delimited_read(0, &read_00239, &read_00239_len, read_00239_delim, 1);
        if (read_00239_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00239_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00239_00000_match;
        pcre *read_00239_00000_pcre = init_regex(read_00239_00000_regex);
        if (read_00239_00000_pcre != NULL) {
            int rc = regex_match(read_00239_00000_pcre, 0, read_00239 + read_00239_ptr, read_00239_len - read_00239_ptr, &read_00239_00000_match);
            if (rc > 0) {
                read_00239_ptr += read_00239_00000_match.match_end - read_00239_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00239_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00239);
        if (read_00239_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00240;
        unsigned int read_00240_len;
        unsigned int read_00240_ptr = 0;
        //**** delimited read
        static unsigned char read_00240_delim[] = 
            "\x0a";
        read_00240 = NULL;
        read_00240_len = 0;
        int read_00240_res = delimited_read(0, &read_00240, &read_00240_len, read_00240_delim, 1);
        if (read_00240_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00240_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00240_00000_match;
        pcre *read_00240_00000_pcre = init_regex(read_00240_00000_regex);
        if (read_00240_00000_pcre != NULL) {
            int rc = regex_match(read_00240_00000_pcre, 0, read_00240 + read_00240_ptr, read_00240_len - read_00240_ptr, &read_00240_00000_match);
            if (rc > 0) {
                read_00240_ptr += read_00240_00000_match.match_end - read_00240_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00240_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00240);
        if (read_00240_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00017_00000[] = 
            "\x3a";
        static unsigned int write_00017_00000_len = 1;
        unsigned char *write_00017 = NULL;
        unsigned int write_00017_len = 0;
        write_00017 = append_buf(write_00017, &write_00017_len, write_00017_00000, write_00017_00000_len);
        if (write_00017_len > 0) {
            transmit_all(1, write_00017, write_00017_len);
        }
        free(write_00017);
    } while (0);
    do {
        unsigned char *read_00241;
        unsigned int read_00241_len;
        unsigned int read_00241_ptr = 0;
        //**** delimited read
        static unsigned char read_00241_delim[] = 
            "\x0a";
        read_00241 = NULL;
        read_00241_len = 0;
        int read_00241_res = delimited_read(0, &read_00241, &read_00241_len, read_00241_delim, 1);
        if (read_00241_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00241_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00241_00000_match;
        pcre *read_00241_00000_pcre = init_regex(read_00241_00000_regex);
        if (read_00241_00000_pcre != NULL) {
            int rc = regex_match(read_00241_00000_pcre, 0, read_00241 + read_00241_ptr, read_00241_len - read_00241_ptr, &read_00241_00000_match);
            if (rc > 0) {
                read_00241_ptr += read_00241_00000_match.match_end - read_00241_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00241_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00241);
        if (read_00241_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00242;
        unsigned int read_00242_len;
        unsigned int read_00242_ptr = 0;
        //**** delimited read
        static unsigned char read_00242_delim[] = 
            "\x0a";
        read_00242 = NULL;
        read_00242_len = 0;
        int read_00242_res = delimited_read(0, &read_00242, &read_00242_len, read_00242_delim, 1);
        if (read_00242_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00242_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00242_00000_match;
        pcre *read_00242_00000_pcre = init_regex(read_00242_00000_regex);
        if (read_00242_00000_pcre != NULL) {
            int rc = regex_match(read_00242_00000_pcre, 0, read_00242 + read_00242_ptr, read_00242_len - read_00242_ptr, &read_00242_00000_match);
            if (rc > 0) {
                read_00242_ptr += read_00242_00000_match.match_end - read_00242_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00242_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00242);
        if (read_00242_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00243;
        unsigned int read_00243_len;
        unsigned int read_00243_ptr = 0;
        //**** delimited read
        static unsigned char read_00243_delim[] = 
            "\x0a";
        read_00243 = NULL;
        read_00243_len = 0;
        int read_00243_res = delimited_read(0, &read_00243, &read_00243_len, read_00243_delim, 1);
        if (read_00243_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00243_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00243_00000_match;
        pcre *read_00243_00000_pcre = init_regex(read_00243_00000_regex);
        if (read_00243_00000_pcre != NULL) {
            int rc = regex_match(read_00243_00000_pcre, 0, read_00243 + read_00243_ptr, read_00243_len - read_00243_ptr, &read_00243_00000_match);
            if (rc > 0) {
                read_00243_ptr += read_00243_00000_match.match_end - read_00243_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00243_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00243);
        if (read_00243_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00244;
        unsigned int read_00244_len;
        unsigned int read_00244_ptr = 0;
        //**** delimited read
        static unsigned char read_00244_delim[] = 
            "\x0a";
        read_00244 = NULL;
        read_00244_len = 0;
        int read_00244_res = delimited_read(0, &read_00244, &read_00244_len, read_00244_delim, 1);
        if (read_00244_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00244_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00244_00000_match;
        pcre *read_00244_00000_pcre = init_regex(read_00244_00000_regex);
        if (read_00244_00000_pcre != NULL) {
            int rc = regex_match(read_00244_00000_pcre, 0, read_00244 + read_00244_ptr, read_00244_len - read_00244_ptr, &read_00244_00000_match);
            if (rc > 0) {
                read_00244_ptr += read_00244_00000_match.match_end - read_00244_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00244_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00244);
        if (read_00244_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00245;
        unsigned int read_00245_len;
        unsigned int read_00245_ptr = 0;
        //**** delimited read
        static unsigned char read_00245_delim[] = 
            "\x0a";
        read_00245 = NULL;
        read_00245_len = 0;
        int read_00245_res = delimited_read(0, &read_00245, &read_00245_len, read_00245_delim, 1);
        if (read_00245_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00245_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00245_00000_match;
        pcre *read_00245_00000_pcre = init_regex(read_00245_00000_regex);
        if (read_00245_00000_pcre != NULL) {
            int rc = regex_match(read_00245_00000_pcre, 0, read_00245 + read_00245_ptr, read_00245_len - read_00245_ptr, &read_00245_00000_match);
            if (rc > 0) {
                read_00245_ptr += read_00245_00000_match.match_end - read_00245_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00245_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00245);
        if (read_00245_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00246;
        unsigned int read_00246_len;
        unsigned int read_00246_ptr = 0;
        //**** delimited read
        static unsigned char read_00246_delim[] = 
            "\x0a";
        read_00246 = NULL;
        read_00246_len = 0;
        int read_00246_res = delimited_read(0, &read_00246, &read_00246_len, read_00246_delim, 1);
        if (read_00246_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00246_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00246_00000_match;
        pcre *read_00246_00000_pcre = init_regex(read_00246_00000_regex);
        if (read_00246_00000_pcre != NULL) {
            int rc = regex_match(read_00246_00000_pcre, 0, read_00246 + read_00246_ptr, read_00246_len - read_00246_ptr, &read_00246_00000_match);
            if (rc > 0) {
                read_00246_ptr += read_00246_00000_match.match_end - read_00246_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00246_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00246);
        if (read_00246_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00247;
        unsigned int read_00247_len;
        unsigned int read_00247_ptr = 0;
        //**** delimited read
        static unsigned char read_00247_delim[] = 
            "\x0a";
        read_00247 = NULL;
        read_00247_len = 0;
        int read_00247_res = delimited_read(0, &read_00247, &read_00247_len, read_00247_delim, 1);
        if (read_00247_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00247_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00247_00000_match;
        pcre *read_00247_00000_pcre = init_regex(read_00247_00000_regex);
        if (read_00247_00000_pcre != NULL) {
            int rc = regex_match(read_00247_00000_pcre, 0, read_00247 + read_00247_ptr, read_00247_len - read_00247_ptr, &read_00247_00000_match);
            if (rc > 0) {
                read_00247_ptr += read_00247_00000_match.match_end - read_00247_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00247_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00247);
        if (read_00247_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00248;
        unsigned int read_00248_len;
        unsigned int read_00248_ptr = 0;
        //**** delimited read
        static unsigned char read_00248_delim[] = 
            "\x0a";
        read_00248 = NULL;
        read_00248_len = 0;
        int read_00248_res = delimited_read(0, &read_00248, &read_00248_len, read_00248_delim, 1);
        if (read_00248_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00248_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00248_00000_match;
        pcre *read_00248_00000_pcre = init_regex(read_00248_00000_regex);
        if (read_00248_00000_pcre != NULL) {
            int rc = regex_match(read_00248_00000_pcre, 0, read_00248 + read_00248_ptr, read_00248_len - read_00248_ptr, &read_00248_00000_match);
            if (rc > 0) {
                read_00248_ptr += read_00248_00000_match.match_end - read_00248_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00248_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00248);
        if (read_00248_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00249;
        unsigned int read_00249_len;
        unsigned int read_00249_ptr = 0;
        //**** delimited read
        static unsigned char read_00249_delim[] = 
            "\x0a";
        read_00249 = NULL;
        read_00249_len = 0;
        int read_00249_res = delimited_read(0, &read_00249, &read_00249_len, read_00249_delim, 1);
        if (read_00249_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00249_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00249_00000_match;
        pcre *read_00249_00000_pcre = init_regex(read_00249_00000_regex);
        if (read_00249_00000_pcre != NULL) {
            int rc = regex_match(read_00249_00000_pcre, 0, read_00249 + read_00249_ptr, read_00249_len - read_00249_ptr, &read_00249_00000_match);
            if (rc > 0) {
                read_00249_ptr += read_00249_00000_match.match_end - read_00249_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00249_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00249);
        if (read_00249_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00250;
        unsigned int read_00250_len;
        unsigned int read_00250_ptr = 0;
        //**** delimited read
        static unsigned char read_00250_delim[] = 
            "\x0a";
        read_00250 = NULL;
        read_00250_len = 0;
        int read_00250_res = delimited_read(0, &read_00250, &read_00250_len, read_00250_delim, 1);
        if (read_00250_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00250_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00250_00000_match;
        pcre *read_00250_00000_pcre = init_regex(read_00250_00000_regex);
        if (read_00250_00000_pcre != NULL) {
            int rc = regex_match(read_00250_00000_pcre, 0, read_00250 + read_00250_ptr, read_00250_len - read_00250_ptr, &read_00250_00000_match);
            if (rc > 0) {
                read_00250_ptr += read_00250_00000_match.match_end - read_00250_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00250_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00250);
        if (read_00250_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00251;
        unsigned int read_00251_len;
        unsigned int read_00251_ptr = 0;
        //**** delimited read
        static unsigned char read_00251_delim[] = 
            "\x0a";
        read_00251 = NULL;
        read_00251_len = 0;
        int read_00251_res = delimited_read(0, &read_00251, &read_00251_len, read_00251_delim, 1);
        if (read_00251_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00251_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00251_00000_match;
        pcre *read_00251_00000_pcre = init_regex(read_00251_00000_regex);
        if (read_00251_00000_pcre != NULL) {
            int rc = regex_match(read_00251_00000_pcre, 0, read_00251 + read_00251_ptr, read_00251_len - read_00251_ptr, &read_00251_00000_match);
            if (rc > 0) {
                read_00251_ptr += read_00251_00000_match.match_end - read_00251_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00251_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00251);
        if (read_00251_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00252;
        unsigned int read_00252_len;
        unsigned int read_00252_ptr = 0;
        //**** delimited read
        static unsigned char read_00252_delim[] = 
            "\x0a";
        read_00252 = NULL;
        read_00252_len = 0;
        int read_00252_res = delimited_read(0, &read_00252, &read_00252_len, read_00252_delim, 1);
        if (read_00252_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00252_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00252_00000_match;
        pcre *read_00252_00000_pcre = init_regex(read_00252_00000_regex);
        if (read_00252_00000_pcre != NULL) {
            int rc = regex_match(read_00252_00000_pcre, 0, read_00252 + read_00252_ptr, read_00252_len - read_00252_ptr, &read_00252_00000_match);
            if (rc > 0) {
                read_00252_ptr += read_00252_00000_match.match_end - read_00252_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00252_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00252);
        if (read_00252_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00018_00000[] = 
            "\x3a";
        static unsigned int write_00018_00000_len = 1;
        unsigned char *write_00018 = NULL;
        unsigned int write_00018_len = 0;
        write_00018 = append_buf(write_00018, &write_00018_len, write_00018_00000, write_00018_00000_len);
        if (write_00018_len > 0) {
            transmit_all(1, write_00018, write_00018_len);
        }
        free(write_00018);
    } while (0);
    do {
        unsigned char *read_00253;
        unsigned int read_00253_len;
        unsigned int read_00253_ptr = 0;
        //**** delimited read
        static unsigned char read_00253_delim[] = 
            "\x0a";
        read_00253 = NULL;
        read_00253_len = 0;
        int read_00253_res = delimited_read(0, &read_00253, &read_00253_len, read_00253_delim, 1);
        if (read_00253_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00253_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00253_00000_match;
        pcre *read_00253_00000_pcre = init_regex(read_00253_00000_regex);
        if (read_00253_00000_pcre != NULL) {
            int rc = regex_match(read_00253_00000_pcre, 0, read_00253 + read_00253_ptr, read_00253_len - read_00253_ptr, &read_00253_00000_match);
            if (rc > 0) {
                read_00253_ptr += read_00253_00000_match.match_end - read_00253_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00253_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00253);
        if (read_00253_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00254;
        unsigned int read_00254_len;
        unsigned int read_00254_ptr = 0;
        //**** delimited read
        static unsigned char read_00254_delim[] = 
            "\x0a";
        read_00254 = NULL;
        read_00254_len = 0;
        int read_00254_res = delimited_read(0, &read_00254, &read_00254_len, read_00254_delim, 1);
        if (read_00254_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00254_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00254_00000_match;
        pcre *read_00254_00000_pcre = init_regex(read_00254_00000_regex);
        if (read_00254_00000_pcre != NULL) {
            int rc = regex_match(read_00254_00000_pcre, 0, read_00254 + read_00254_ptr, read_00254_len - read_00254_ptr, &read_00254_00000_match);
            if (rc > 0) {
                read_00254_ptr += read_00254_00000_match.match_end - read_00254_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00254_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00254);
        if (read_00254_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00255;
        unsigned int read_00255_len;
        unsigned int read_00255_ptr = 0;
        //**** delimited read
        static unsigned char read_00255_delim[] = 
            "\x0a";
        read_00255 = NULL;
        read_00255_len = 0;
        int read_00255_res = delimited_read(0, &read_00255, &read_00255_len, read_00255_delim, 1);
        if (read_00255_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00255_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00255_00000_match;
        pcre *read_00255_00000_pcre = init_regex(read_00255_00000_regex);
        if (read_00255_00000_pcre != NULL) {
            int rc = regex_match(read_00255_00000_pcre, 0, read_00255 + read_00255_ptr, read_00255_len - read_00255_ptr, &read_00255_00000_match);
            if (rc > 0) {
                read_00255_ptr += read_00255_00000_match.match_end - read_00255_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00255_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00255);
        if (read_00255_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00256;
        unsigned int read_00256_len;
        unsigned int read_00256_ptr = 0;
        //**** delimited read
        static unsigned char read_00256_delim[] = 
            "\x0a";
        read_00256 = NULL;
        read_00256_len = 0;
        int read_00256_res = delimited_read(0, &read_00256, &read_00256_len, read_00256_delim, 1);
        if (read_00256_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00256_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00256_00000_match;
        pcre *read_00256_00000_pcre = init_regex(read_00256_00000_regex);
        if (read_00256_00000_pcre != NULL) {
            int rc = regex_match(read_00256_00000_pcre, 0, read_00256 + read_00256_ptr, read_00256_len - read_00256_ptr, &read_00256_00000_match);
            if (rc > 0) {
                read_00256_ptr += read_00256_00000_match.match_end - read_00256_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00256_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00256);
        if (read_00256_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00257;
        unsigned int read_00257_len;
        unsigned int read_00257_ptr = 0;
        //**** delimited read
        static unsigned char read_00257_delim[] = 
            "\x0a";
        read_00257 = NULL;
        read_00257_len = 0;
        int read_00257_res = delimited_read(0, &read_00257, &read_00257_len, read_00257_delim, 1);
        if (read_00257_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00257_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00257_00000_match;
        pcre *read_00257_00000_pcre = init_regex(read_00257_00000_regex);
        if (read_00257_00000_pcre != NULL) {
            int rc = regex_match(read_00257_00000_pcre, 0, read_00257 + read_00257_ptr, read_00257_len - read_00257_ptr, &read_00257_00000_match);
            if (rc > 0) {
                read_00257_ptr += read_00257_00000_match.match_end - read_00257_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00257_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00257);
        if (read_00257_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00258;
        unsigned int read_00258_len;
        unsigned int read_00258_ptr = 0;
        //**** delimited read
        static unsigned char read_00258_delim[] = 
            "\x0a";
        read_00258 = NULL;
        read_00258_len = 0;
        int read_00258_res = delimited_read(0, &read_00258, &read_00258_len, read_00258_delim, 1);
        if (read_00258_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00258_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00258_00000_match;
        pcre *read_00258_00000_pcre = init_regex(read_00258_00000_regex);
        if (read_00258_00000_pcre != NULL) {
            int rc = regex_match(read_00258_00000_pcre, 0, read_00258 + read_00258_ptr, read_00258_len - read_00258_ptr, &read_00258_00000_match);
            if (rc > 0) {
                read_00258_ptr += read_00258_00000_match.match_end - read_00258_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00258_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00258);
        if (read_00258_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00259;
        unsigned int read_00259_len;
        unsigned int read_00259_ptr = 0;
        //**** delimited read
        static unsigned char read_00259_delim[] = 
            "\x0a";
        read_00259 = NULL;
        read_00259_len = 0;
        int read_00259_res = delimited_read(0, &read_00259, &read_00259_len, read_00259_delim, 1);
        if (read_00259_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00259_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00259_00000_match;
        pcre *read_00259_00000_pcre = init_regex(read_00259_00000_regex);
        if (read_00259_00000_pcre != NULL) {
            int rc = regex_match(read_00259_00000_pcre, 0, read_00259 + read_00259_ptr, read_00259_len - read_00259_ptr, &read_00259_00000_match);
            if (rc > 0) {
                read_00259_ptr += read_00259_00000_match.match_end - read_00259_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00259_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00259);
        if (read_00259_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00260;
        unsigned int read_00260_len;
        unsigned int read_00260_ptr = 0;
        //**** delimited read
        static unsigned char read_00260_delim[] = 
            "\x0a";
        read_00260 = NULL;
        read_00260_len = 0;
        int read_00260_res = delimited_read(0, &read_00260, &read_00260_len, read_00260_delim, 1);
        if (read_00260_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00260_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00260_00000_match;
        pcre *read_00260_00000_pcre = init_regex(read_00260_00000_regex);
        if (read_00260_00000_pcre != NULL) {
            int rc = regex_match(read_00260_00000_pcre, 0, read_00260 + read_00260_ptr, read_00260_len - read_00260_ptr, &read_00260_00000_match);
            if (rc > 0) {
                read_00260_ptr += read_00260_00000_match.match_end - read_00260_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00260_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00260);
        if (read_00260_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00261;
        unsigned int read_00261_len;
        unsigned int read_00261_ptr = 0;
        //**** delimited read
        static unsigned char read_00261_delim[] = 
            "\x0a";
        read_00261 = NULL;
        read_00261_len = 0;
        int read_00261_res = delimited_read(0, &read_00261, &read_00261_len, read_00261_delim, 1);
        if (read_00261_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00261_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00261_00000_match;
        pcre *read_00261_00000_pcre = init_regex(read_00261_00000_regex);
        if (read_00261_00000_pcre != NULL) {
            int rc = regex_match(read_00261_00000_pcre, 0, read_00261 + read_00261_ptr, read_00261_len - read_00261_ptr, &read_00261_00000_match);
            if (rc > 0) {
                read_00261_ptr += read_00261_00000_match.match_end - read_00261_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00261_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00261);
        if (read_00261_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00262;
        unsigned int read_00262_len;
        unsigned int read_00262_ptr = 0;
        //**** delimited read
        static unsigned char read_00262_delim[] = 
            "\x0a";
        read_00262 = NULL;
        read_00262_len = 0;
        int read_00262_res = delimited_read(0, &read_00262, &read_00262_len, read_00262_delim, 1);
        if (read_00262_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00262_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00262_00000_match;
        pcre *read_00262_00000_pcre = init_regex(read_00262_00000_regex);
        if (read_00262_00000_pcre != NULL) {
            int rc = regex_match(read_00262_00000_pcre, 0, read_00262 + read_00262_ptr, read_00262_len - read_00262_ptr, &read_00262_00000_match);
            if (rc > 0) {
                read_00262_ptr += read_00262_00000_match.match_end - read_00262_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00262_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00262);
        if (read_00262_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00263;
        unsigned int read_00263_len;
        unsigned int read_00263_ptr = 0;
        //**** delimited read
        static unsigned char read_00263_delim[] = 
            "\x0a";
        read_00263 = NULL;
        read_00263_len = 0;
        int read_00263_res = delimited_read(0, &read_00263, &read_00263_len, read_00263_delim, 1);
        if (read_00263_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00263_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00263_00000_match;
        pcre *read_00263_00000_pcre = init_regex(read_00263_00000_regex);
        if (read_00263_00000_pcre != NULL) {
            int rc = regex_match(read_00263_00000_pcre, 0, read_00263 + read_00263_ptr, read_00263_len - read_00263_ptr, &read_00263_00000_match);
            if (rc > 0) {
                read_00263_ptr += read_00263_00000_match.match_end - read_00263_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00263_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00263);
        if (read_00263_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00264;
        unsigned int read_00264_len;
        unsigned int read_00264_ptr = 0;
        //**** delimited read
        static unsigned char read_00264_delim[] = 
            "\x0a";
        read_00264 = NULL;
        read_00264_len = 0;
        int read_00264_res = delimited_read(0, &read_00264, &read_00264_len, read_00264_delim, 1);
        if (read_00264_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00264_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00264_00000_match;
        pcre *read_00264_00000_pcre = init_regex(read_00264_00000_regex);
        if (read_00264_00000_pcre != NULL) {
            int rc = regex_match(read_00264_00000_pcre, 0, read_00264 + read_00264_ptr, read_00264_len - read_00264_ptr, &read_00264_00000_match);
            if (rc > 0) {
                read_00264_ptr += read_00264_00000_match.match_end - read_00264_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00264_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00264);
        if (read_00264_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00019_00000[] = 
            "\x3a";
        static unsigned int write_00019_00000_len = 1;
        unsigned char *write_00019 = NULL;
        unsigned int write_00019_len = 0;
        write_00019 = append_buf(write_00019, &write_00019_len, write_00019_00000, write_00019_00000_len);
        if (write_00019_len > 0) {
            transmit_all(1, write_00019, write_00019_len);
        }
        free(write_00019);
    } while (0);
    do {
        unsigned char *read_00265;
        unsigned int read_00265_len;
        unsigned int read_00265_ptr = 0;
        //**** delimited read
        static unsigned char read_00265_delim[] = 
            "\x0a";
        read_00265 = NULL;
        read_00265_len = 0;
        int read_00265_res = delimited_read(0, &read_00265, &read_00265_len, read_00265_delim, 1);
        if (read_00265_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00265_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00265_00000_match;
        pcre *read_00265_00000_pcre = init_regex(read_00265_00000_regex);
        if (read_00265_00000_pcre != NULL) {
            int rc = regex_match(read_00265_00000_pcre, 0, read_00265 + read_00265_ptr, read_00265_len - read_00265_ptr, &read_00265_00000_match);
            if (rc > 0) {
                read_00265_ptr += read_00265_00000_match.match_end - read_00265_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00265_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00265);
        if (read_00265_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00266;
        unsigned int read_00266_len;
        unsigned int read_00266_ptr = 0;
        //**** delimited read
        static unsigned char read_00266_delim[] = 
            "\x0a";
        read_00266 = NULL;
        read_00266_len = 0;
        int read_00266_res = delimited_read(0, &read_00266, &read_00266_len, read_00266_delim, 1);
        if (read_00266_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00266_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00266_00000_match;
        pcre *read_00266_00000_pcre = init_regex(read_00266_00000_regex);
        if (read_00266_00000_pcre != NULL) {
            int rc = regex_match(read_00266_00000_pcre, 0, read_00266 + read_00266_ptr, read_00266_len - read_00266_ptr, &read_00266_00000_match);
            if (rc > 0) {
                read_00266_ptr += read_00266_00000_match.match_end - read_00266_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00266_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00266);
        if (read_00266_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00267;
        unsigned int read_00267_len;
        unsigned int read_00267_ptr = 0;
        //**** delimited read
        static unsigned char read_00267_delim[] = 
            "\x0a";
        read_00267 = NULL;
        read_00267_len = 0;
        int read_00267_res = delimited_read(0, &read_00267, &read_00267_len, read_00267_delim, 1);
        if (read_00267_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00267_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00267_00000_match;
        pcre *read_00267_00000_pcre = init_regex(read_00267_00000_regex);
        if (read_00267_00000_pcre != NULL) {
            int rc = regex_match(read_00267_00000_pcre, 0, read_00267 + read_00267_ptr, read_00267_len - read_00267_ptr, &read_00267_00000_match);
            if (rc > 0) {
                read_00267_ptr += read_00267_00000_match.match_end - read_00267_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00267_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00267);
        if (read_00267_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00268;
        unsigned int read_00268_len;
        unsigned int read_00268_ptr = 0;
        //**** delimited read
        static unsigned char read_00268_delim[] = 
            "\x0a";
        read_00268 = NULL;
        read_00268_len = 0;
        int read_00268_res = delimited_read(0, &read_00268, &read_00268_len, read_00268_delim, 1);
        if (read_00268_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00268_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00268_00000_match;
        pcre *read_00268_00000_pcre = init_regex(read_00268_00000_regex);
        if (read_00268_00000_pcre != NULL) {
            int rc = regex_match(read_00268_00000_pcre, 0, read_00268 + read_00268_ptr, read_00268_len - read_00268_ptr, &read_00268_00000_match);
            if (rc > 0) {
                read_00268_ptr += read_00268_00000_match.match_end - read_00268_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00268_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00268);
        if (read_00268_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00269;
        unsigned int read_00269_len;
        unsigned int read_00269_ptr = 0;
        //**** delimited read
        static unsigned char read_00269_delim[] = 
            "\x0a";
        read_00269 = NULL;
        read_00269_len = 0;
        int read_00269_res = delimited_read(0, &read_00269, &read_00269_len, read_00269_delim, 1);
        if (read_00269_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00269_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00269_00000_match;
        pcre *read_00269_00000_pcre = init_regex(read_00269_00000_regex);
        if (read_00269_00000_pcre != NULL) {
            int rc = regex_match(read_00269_00000_pcre, 0, read_00269 + read_00269_ptr, read_00269_len - read_00269_ptr, &read_00269_00000_match);
            if (rc > 0) {
                read_00269_ptr += read_00269_00000_match.match_end - read_00269_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00269_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00269);
        if (read_00269_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00270;
        unsigned int read_00270_len;
        unsigned int read_00270_ptr = 0;
        //**** delimited read
        static unsigned char read_00270_delim[] = 
            "\x0a";
        read_00270 = NULL;
        read_00270_len = 0;
        int read_00270_res = delimited_read(0, &read_00270, &read_00270_len, read_00270_delim, 1);
        if (read_00270_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00270_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00270_00000_match;
        pcre *read_00270_00000_pcre = init_regex(read_00270_00000_regex);
        if (read_00270_00000_pcre != NULL) {
            int rc = regex_match(read_00270_00000_pcre, 0, read_00270 + read_00270_ptr, read_00270_len - read_00270_ptr, &read_00270_00000_match);
            if (rc > 0) {
                read_00270_ptr += read_00270_00000_match.match_end - read_00270_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00270_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00270);
        if (read_00270_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00271;
        unsigned int read_00271_len;
        unsigned int read_00271_ptr = 0;
        //**** delimited read
        static unsigned char read_00271_delim[] = 
            "\x0a";
        read_00271 = NULL;
        read_00271_len = 0;
        int read_00271_res = delimited_read(0, &read_00271, &read_00271_len, read_00271_delim, 1);
        if (read_00271_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00271_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00271_00000_match;
        pcre *read_00271_00000_pcre = init_regex(read_00271_00000_regex);
        if (read_00271_00000_pcre != NULL) {
            int rc = regex_match(read_00271_00000_pcre, 0, read_00271 + read_00271_ptr, read_00271_len - read_00271_ptr, &read_00271_00000_match);
            if (rc > 0) {
                read_00271_ptr += read_00271_00000_match.match_end - read_00271_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00271_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00271);
        if (read_00271_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00272;
        unsigned int read_00272_len;
        unsigned int read_00272_ptr = 0;
        //**** delimited read
        static unsigned char read_00272_delim[] = 
            "\x0a";
        read_00272 = NULL;
        read_00272_len = 0;
        int read_00272_res = delimited_read(0, &read_00272, &read_00272_len, read_00272_delim, 1);
        if (read_00272_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00272_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00272_00000_match;
        pcre *read_00272_00000_pcre = init_regex(read_00272_00000_regex);
        if (read_00272_00000_pcre != NULL) {
            int rc = regex_match(read_00272_00000_pcre, 0, read_00272 + read_00272_ptr, read_00272_len - read_00272_ptr, &read_00272_00000_match);
            if (rc > 0) {
                read_00272_ptr += read_00272_00000_match.match_end - read_00272_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00272_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00272);
        if (read_00272_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00273;
        unsigned int read_00273_len;
        unsigned int read_00273_ptr = 0;
        //**** delimited read
        static unsigned char read_00273_delim[] = 
            "\x0a";
        read_00273 = NULL;
        read_00273_len = 0;
        int read_00273_res = delimited_read(0, &read_00273, &read_00273_len, read_00273_delim, 1);
        if (read_00273_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00273_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00273_00000_match;
        pcre *read_00273_00000_pcre = init_regex(read_00273_00000_regex);
        if (read_00273_00000_pcre != NULL) {
            int rc = regex_match(read_00273_00000_pcre, 0, read_00273 + read_00273_ptr, read_00273_len - read_00273_ptr, &read_00273_00000_match);
            if (rc > 0) {
                read_00273_ptr += read_00273_00000_match.match_end - read_00273_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00273_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00273);
        if (read_00273_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00274;
        unsigned int read_00274_len;
        unsigned int read_00274_ptr = 0;
        //**** delimited read
        static unsigned char read_00274_delim[] = 
            "\x0a";
        read_00274 = NULL;
        read_00274_len = 0;
        int read_00274_res = delimited_read(0, &read_00274, &read_00274_len, read_00274_delim, 1);
        if (read_00274_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00274_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00274_00000_match;
        pcre *read_00274_00000_pcre = init_regex(read_00274_00000_regex);
        if (read_00274_00000_pcre != NULL) {
            int rc = regex_match(read_00274_00000_pcre, 0, read_00274 + read_00274_ptr, read_00274_len - read_00274_ptr, &read_00274_00000_match);
            if (rc > 0) {
                read_00274_ptr += read_00274_00000_match.match_end - read_00274_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00274_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00274);
        if (read_00274_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00275;
        unsigned int read_00275_len;
        unsigned int read_00275_ptr = 0;
        //**** delimited read
        static unsigned char read_00275_delim[] = 
            "\x0a";
        read_00275 = NULL;
        read_00275_len = 0;
        int read_00275_res = delimited_read(0, &read_00275, &read_00275_len, read_00275_delim, 1);
        if (read_00275_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00275_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00275_00000_match;
        pcre *read_00275_00000_pcre = init_regex(read_00275_00000_regex);
        if (read_00275_00000_pcre != NULL) {
            int rc = regex_match(read_00275_00000_pcre, 0, read_00275 + read_00275_ptr, read_00275_len - read_00275_ptr, &read_00275_00000_match);
            if (rc > 0) {
                read_00275_ptr += read_00275_00000_match.match_end - read_00275_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00275_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00275);
        if (read_00275_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00276;
        unsigned int read_00276_len;
        unsigned int read_00276_ptr = 0;
        //**** delimited read
        static unsigned char read_00276_delim[] = 
            "\x0a";
        read_00276 = NULL;
        read_00276_len = 0;
        int read_00276_res = delimited_read(0, &read_00276, &read_00276_len, read_00276_delim, 1);
        if (read_00276_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00276_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00276_00000_match;
        pcre *read_00276_00000_pcre = init_regex(read_00276_00000_regex);
        if (read_00276_00000_pcre != NULL) {
            int rc = regex_match(read_00276_00000_pcre, 0, read_00276 + read_00276_ptr, read_00276_len - read_00276_ptr, &read_00276_00000_match);
            if (rc > 0) {
                read_00276_ptr += read_00276_00000_match.match_end - read_00276_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00276_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00276);
        if (read_00276_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00020_00000[] = 
            "\x3a";
        static unsigned int write_00020_00000_len = 1;
        unsigned char *write_00020 = NULL;
        unsigned int write_00020_len = 0;
        write_00020 = append_buf(write_00020, &write_00020_len, write_00020_00000, write_00020_00000_len);
        if (write_00020_len > 0) {
            transmit_all(1, write_00020, write_00020_len);
        }
        free(write_00020);
    } while (0);
    do {
        unsigned char *read_00277;
        unsigned int read_00277_len;
        unsigned int read_00277_ptr = 0;
        //**** delimited read
        static unsigned char read_00277_delim[] = 
            "\x0a";
        read_00277 = NULL;
        read_00277_len = 0;
        int read_00277_res = delimited_read(0, &read_00277, &read_00277_len, read_00277_delim, 1);
        if (read_00277_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00277_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00277_00000_match;
        pcre *read_00277_00000_pcre = init_regex(read_00277_00000_regex);
        if (read_00277_00000_pcre != NULL) {
            int rc = regex_match(read_00277_00000_pcre, 0, read_00277 + read_00277_ptr, read_00277_len - read_00277_ptr, &read_00277_00000_match);
            if (rc > 0) {
                read_00277_ptr += read_00277_00000_match.match_end - read_00277_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00277_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00277);
        if (read_00277_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00278;
        unsigned int read_00278_len;
        unsigned int read_00278_ptr = 0;
        //**** delimited read
        static unsigned char read_00278_delim[] = 
            "\x0a";
        read_00278 = NULL;
        read_00278_len = 0;
        int read_00278_res = delimited_read(0, &read_00278, &read_00278_len, read_00278_delim, 1);
        if (read_00278_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00278_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00278_00000_match;
        pcre *read_00278_00000_pcre = init_regex(read_00278_00000_regex);
        if (read_00278_00000_pcre != NULL) {
            int rc = regex_match(read_00278_00000_pcre, 0, read_00278 + read_00278_ptr, read_00278_len - read_00278_ptr, &read_00278_00000_match);
            if (rc > 0) {
                read_00278_ptr += read_00278_00000_match.match_end - read_00278_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00278_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00278);
        if (read_00278_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00279;
        unsigned int read_00279_len;
        unsigned int read_00279_ptr = 0;
        //**** delimited read
        static unsigned char read_00279_delim[] = 
            "\x0a";
        read_00279 = NULL;
        read_00279_len = 0;
        int read_00279_res = delimited_read(0, &read_00279, &read_00279_len, read_00279_delim, 1);
        if (read_00279_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00279_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00279_00000_match;
        pcre *read_00279_00000_pcre = init_regex(read_00279_00000_regex);
        if (read_00279_00000_pcre != NULL) {
            int rc = regex_match(read_00279_00000_pcre, 0, read_00279 + read_00279_ptr, read_00279_len - read_00279_ptr, &read_00279_00000_match);
            if (rc > 0) {
                read_00279_ptr += read_00279_00000_match.match_end - read_00279_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00279_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00279);
        if (read_00279_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00280;
        unsigned int read_00280_len;
        unsigned int read_00280_ptr = 0;
        //**** delimited read
        static unsigned char read_00280_delim[] = 
            "\x0a";
        read_00280 = NULL;
        read_00280_len = 0;
        int read_00280_res = delimited_read(0, &read_00280, &read_00280_len, read_00280_delim, 1);
        if (read_00280_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00280_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00280_00000_match;
        pcre *read_00280_00000_pcre = init_regex(read_00280_00000_regex);
        if (read_00280_00000_pcre != NULL) {
            int rc = regex_match(read_00280_00000_pcre, 0, read_00280 + read_00280_ptr, read_00280_len - read_00280_ptr, &read_00280_00000_match);
            if (rc > 0) {
                read_00280_ptr += read_00280_00000_match.match_end - read_00280_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00280_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00280);
        if (read_00280_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00281;
        unsigned int read_00281_len;
        unsigned int read_00281_ptr = 0;
        //**** delimited read
        static unsigned char read_00281_delim[] = 
            "\x0a";
        read_00281 = NULL;
        read_00281_len = 0;
        int read_00281_res = delimited_read(0, &read_00281, &read_00281_len, read_00281_delim, 1);
        if (read_00281_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00281_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00281_00000_match;
        pcre *read_00281_00000_pcre = init_regex(read_00281_00000_regex);
        if (read_00281_00000_pcre != NULL) {
            int rc = regex_match(read_00281_00000_pcre, 0, read_00281 + read_00281_ptr, read_00281_len - read_00281_ptr, &read_00281_00000_match);
            if (rc > 0) {
                read_00281_ptr += read_00281_00000_match.match_end - read_00281_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00281_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00281);
        if (read_00281_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00282;
        unsigned int read_00282_len;
        unsigned int read_00282_ptr = 0;
        //**** delimited read
        static unsigned char read_00282_delim[] = 
            "\x0a";
        read_00282 = NULL;
        read_00282_len = 0;
        int read_00282_res = delimited_read(0, &read_00282, &read_00282_len, read_00282_delim, 1);
        if (read_00282_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00282_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00282_00000_match;
        pcre *read_00282_00000_pcre = init_regex(read_00282_00000_regex);
        if (read_00282_00000_pcre != NULL) {
            int rc = regex_match(read_00282_00000_pcre, 0, read_00282 + read_00282_ptr, read_00282_len - read_00282_ptr, &read_00282_00000_match);
            if (rc > 0) {
                read_00282_ptr += read_00282_00000_match.match_end - read_00282_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00282_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00282);
        if (read_00282_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00283;
        unsigned int read_00283_len;
        unsigned int read_00283_ptr = 0;
        //**** delimited read
        static unsigned char read_00283_delim[] = 
            "\x0a";
        read_00283 = NULL;
        read_00283_len = 0;
        int read_00283_res = delimited_read(0, &read_00283, &read_00283_len, read_00283_delim, 1);
        if (read_00283_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00283_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00283_00000_match;
        pcre *read_00283_00000_pcre = init_regex(read_00283_00000_regex);
        if (read_00283_00000_pcre != NULL) {
            int rc = regex_match(read_00283_00000_pcre, 0, read_00283 + read_00283_ptr, read_00283_len - read_00283_ptr, &read_00283_00000_match);
            if (rc > 0) {
                read_00283_ptr += read_00283_00000_match.match_end - read_00283_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00283_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00283);
        if (read_00283_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00284;
        unsigned int read_00284_len;
        unsigned int read_00284_ptr = 0;
        //**** delimited read
        static unsigned char read_00284_delim[] = 
            "\x0a";
        read_00284 = NULL;
        read_00284_len = 0;
        int read_00284_res = delimited_read(0, &read_00284, &read_00284_len, read_00284_delim, 1);
        if (read_00284_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00284_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00284_00000_match;
        pcre *read_00284_00000_pcre = init_regex(read_00284_00000_regex);
        if (read_00284_00000_pcre != NULL) {
            int rc = regex_match(read_00284_00000_pcre, 0, read_00284 + read_00284_ptr, read_00284_len - read_00284_ptr, &read_00284_00000_match);
            if (rc > 0) {
                read_00284_ptr += read_00284_00000_match.match_end - read_00284_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00284_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00284);
        if (read_00284_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00285;
        unsigned int read_00285_len;
        unsigned int read_00285_ptr = 0;
        //**** delimited read
        static unsigned char read_00285_delim[] = 
            "\x0a";
        read_00285 = NULL;
        read_00285_len = 0;
        int read_00285_res = delimited_read(0, &read_00285, &read_00285_len, read_00285_delim, 1);
        if (read_00285_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00285_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00285_00000_match;
        pcre *read_00285_00000_pcre = init_regex(read_00285_00000_regex);
        if (read_00285_00000_pcre != NULL) {
            int rc = regex_match(read_00285_00000_pcre, 0, read_00285 + read_00285_ptr, read_00285_len - read_00285_ptr, &read_00285_00000_match);
            if (rc > 0) {
                read_00285_ptr += read_00285_00000_match.match_end - read_00285_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00285_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00285);
        if (read_00285_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00286;
        unsigned int read_00286_len;
        unsigned int read_00286_ptr = 0;
        //**** delimited read
        static unsigned char read_00286_delim[] = 
            "\x0a";
        read_00286 = NULL;
        read_00286_len = 0;
        int read_00286_res = delimited_read(0, &read_00286, &read_00286_len, read_00286_delim, 1);
        if (read_00286_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00286_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00286_00000_match;
        pcre *read_00286_00000_pcre = init_regex(read_00286_00000_regex);
        if (read_00286_00000_pcre != NULL) {
            int rc = regex_match(read_00286_00000_pcre, 0, read_00286 + read_00286_ptr, read_00286_len - read_00286_ptr, &read_00286_00000_match);
            if (rc > 0) {
                read_00286_ptr += read_00286_00000_match.match_end - read_00286_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00286_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00286);
        if (read_00286_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00287;
        unsigned int read_00287_len;
        unsigned int read_00287_ptr = 0;
        //**** delimited read
        static unsigned char read_00287_delim[] = 
            "\x0a";
        read_00287 = NULL;
        read_00287_len = 0;
        int read_00287_res = delimited_read(0, &read_00287, &read_00287_len, read_00287_delim, 1);
        if (read_00287_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00287_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00287_00000_match;
        pcre *read_00287_00000_pcre = init_regex(read_00287_00000_regex);
        if (read_00287_00000_pcre != NULL) {
            int rc = regex_match(read_00287_00000_pcre, 0, read_00287 + read_00287_ptr, read_00287_len - read_00287_ptr, &read_00287_00000_match);
            if (rc > 0) {
                read_00287_ptr += read_00287_00000_match.match_end - read_00287_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00287_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00287);
        if (read_00287_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00288;
        unsigned int read_00288_len;
        unsigned int read_00288_ptr = 0;
        //**** delimited read
        static unsigned char read_00288_delim[] = 
            "\x0a";
        read_00288 = NULL;
        read_00288_len = 0;
        int read_00288_res = delimited_read(0, &read_00288, &read_00288_len, read_00288_delim, 1);
        if (read_00288_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00288_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00288_00000_match;
        pcre *read_00288_00000_pcre = init_regex(read_00288_00000_regex);
        if (read_00288_00000_pcre != NULL) {
            int rc = regex_match(read_00288_00000_pcre, 0, read_00288 + read_00288_ptr, read_00288_len - read_00288_ptr, &read_00288_00000_match);
            if (rc > 0) {
                read_00288_ptr += read_00288_00000_match.match_end - read_00288_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00288_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00288);
        if (read_00288_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00021_00000[] = 
            "\x3a";
        static unsigned int write_00021_00000_len = 1;
        unsigned char *write_00021 = NULL;
        unsigned int write_00021_len = 0;
        write_00021 = append_buf(write_00021, &write_00021_len, write_00021_00000, write_00021_00000_len);
        if (write_00021_len > 0) {
            transmit_all(1, write_00021, write_00021_len);
        }
        free(write_00021);
    } while (0);
    do {
        unsigned char *read_00289;
        unsigned int read_00289_len;
        unsigned int read_00289_ptr = 0;
        //**** delimited read
        static unsigned char read_00289_delim[] = 
            "\x0a";
        read_00289 = NULL;
        read_00289_len = 0;
        int read_00289_res = delimited_read(0, &read_00289, &read_00289_len, read_00289_delim, 1);
        if (read_00289_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00289_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00289_00000_match;
        pcre *read_00289_00000_pcre = init_regex(read_00289_00000_regex);
        if (read_00289_00000_pcre != NULL) {
            int rc = regex_match(read_00289_00000_pcre, 0, read_00289 + read_00289_ptr, read_00289_len - read_00289_ptr, &read_00289_00000_match);
            if (rc > 0) {
                read_00289_ptr += read_00289_00000_match.match_end - read_00289_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00289_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00289);
        if (read_00289_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00290;
        unsigned int read_00290_len;
        unsigned int read_00290_ptr = 0;
        //**** delimited read
        static unsigned char read_00290_delim[] = 
            "\x0a";
        read_00290 = NULL;
        read_00290_len = 0;
        int read_00290_res = delimited_read(0, &read_00290, &read_00290_len, read_00290_delim, 1);
        if (read_00290_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00290_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00290_00000_match;
        pcre *read_00290_00000_pcre = init_regex(read_00290_00000_regex);
        if (read_00290_00000_pcre != NULL) {
            int rc = regex_match(read_00290_00000_pcre, 0, read_00290 + read_00290_ptr, read_00290_len - read_00290_ptr, &read_00290_00000_match);
            if (rc > 0) {
                read_00290_ptr += read_00290_00000_match.match_end - read_00290_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00290_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00290);
        if (read_00290_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00291;
        unsigned int read_00291_len;
        unsigned int read_00291_ptr = 0;
        //**** delimited read
        static unsigned char read_00291_delim[] = 
            "\x0a";
        read_00291 = NULL;
        read_00291_len = 0;
        int read_00291_res = delimited_read(0, &read_00291, &read_00291_len, read_00291_delim, 1);
        if (read_00291_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00291_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00291_00000_match;
        pcre *read_00291_00000_pcre = init_regex(read_00291_00000_regex);
        if (read_00291_00000_pcre != NULL) {
            int rc = regex_match(read_00291_00000_pcre, 0, read_00291 + read_00291_ptr, read_00291_len - read_00291_ptr, &read_00291_00000_match);
            if (rc > 0) {
                read_00291_ptr += read_00291_00000_match.match_end - read_00291_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00291_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00291);
        if (read_00291_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00292;
        unsigned int read_00292_len;
        unsigned int read_00292_ptr = 0;
        //**** delimited read
        static unsigned char read_00292_delim[] = 
            "\x0a";
        read_00292 = NULL;
        read_00292_len = 0;
        int read_00292_res = delimited_read(0, &read_00292, &read_00292_len, read_00292_delim, 1);
        if (read_00292_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00292_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00292_00000_match;
        pcre *read_00292_00000_pcre = init_regex(read_00292_00000_regex);
        if (read_00292_00000_pcre != NULL) {
            int rc = regex_match(read_00292_00000_pcre, 0, read_00292 + read_00292_ptr, read_00292_len - read_00292_ptr, &read_00292_00000_match);
            if (rc > 0) {
                read_00292_ptr += read_00292_00000_match.match_end - read_00292_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00292_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00292);
        if (read_00292_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00293;
        unsigned int read_00293_len;
        unsigned int read_00293_ptr = 0;
        //**** delimited read
        static unsigned char read_00293_delim[] = 
            "\x0a";
        read_00293 = NULL;
        read_00293_len = 0;
        int read_00293_res = delimited_read(0, &read_00293, &read_00293_len, read_00293_delim, 1);
        if (read_00293_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00293_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00293_00000_match;
        pcre *read_00293_00000_pcre = init_regex(read_00293_00000_regex);
        if (read_00293_00000_pcre != NULL) {
            int rc = regex_match(read_00293_00000_pcre, 0, read_00293 + read_00293_ptr, read_00293_len - read_00293_ptr, &read_00293_00000_match);
            if (rc > 0) {
                read_00293_ptr += read_00293_00000_match.match_end - read_00293_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00293_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00293);
        if (read_00293_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00294;
        unsigned int read_00294_len;
        unsigned int read_00294_ptr = 0;
        //**** delimited read
        static unsigned char read_00294_delim[] = 
            "\x0a";
        read_00294 = NULL;
        read_00294_len = 0;
        int read_00294_res = delimited_read(0, &read_00294, &read_00294_len, read_00294_delim, 1);
        if (read_00294_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00294_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00294_00000_match;
        pcre *read_00294_00000_pcre = init_regex(read_00294_00000_regex);
        if (read_00294_00000_pcre != NULL) {
            int rc = regex_match(read_00294_00000_pcre, 0, read_00294 + read_00294_ptr, read_00294_len - read_00294_ptr, &read_00294_00000_match);
            if (rc > 0) {
                read_00294_ptr += read_00294_00000_match.match_end - read_00294_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00294_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00294);
        if (read_00294_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00295;
        unsigned int read_00295_len;
        unsigned int read_00295_ptr = 0;
        //**** delimited read
        static unsigned char read_00295_delim[] = 
            "\x0a";
        read_00295 = NULL;
        read_00295_len = 0;
        int read_00295_res = delimited_read(0, &read_00295, &read_00295_len, read_00295_delim, 1);
        if (read_00295_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00295_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00295_00000_match;
        pcre *read_00295_00000_pcre = init_regex(read_00295_00000_regex);
        if (read_00295_00000_pcre != NULL) {
            int rc = regex_match(read_00295_00000_pcre, 0, read_00295 + read_00295_ptr, read_00295_len - read_00295_ptr, &read_00295_00000_match);
            if (rc > 0) {
                read_00295_ptr += read_00295_00000_match.match_end - read_00295_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00295_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00295);
        if (read_00295_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00296;
        unsigned int read_00296_len;
        unsigned int read_00296_ptr = 0;
        //**** delimited read
        static unsigned char read_00296_delim[] = 
            "\x0a";
        read_00296 = NULL;
        read_00296_len = 0;
        int read_00296_res = delimited_read(0, &read_00296, &read_00296_len, read_00296_delim, 1);
        if (read_00296_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00296_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00296_00000_match;
        pcre *read_00296_00000_pcre = init_regex(read_00296_00000_regex);
        if (read_00296_00000_pcre != NULL) {
            int rc = regex_match(read_00296_00000_pcre, 0, read_00296 + read_00296_ptr, read_00296_len - read_00296_ptr, &read_00296_00000_match);
            if (rc > 0) {
                read_00296_ptr += read_00296_00000_match.match_end - read_00296_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00296_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00296);
        if (read_00296_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00297;
        unsigned int read_00297_len;
        unsigned int read_00297_ptr = 0;
        //**** delimited read
        static unsigned char read_00297_delim[] = 
            "\x0a";
        read_00297 = NULL;
        read_00297_len = 0;
        int read_00297_res = delimited_read(0, &read_00297, &read_00297_len, read_00297_delim, 1);
        if (read_00297_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00297_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00297_00000_match;
        pcre *read_00297_00000_pcre = init_regex(read_00297_00000_regex);
        if (read_00297_00000_pcre != NULL) {
            int rc = regex_match(read_00297_00000_pcre, 0, read_00297 + read_00297_ptr, read_00297_len - read_00297_ptr, &read_00297_00000_match);
            if (rc > 0) {
                read_00297_ptr += read_00297_00000_match.match_end - read_00297_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00297_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00297);
        if (read_00297_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00298;
        unsigned int read_00298_len;
        unsigned int read_00298_ptr = 0;
        //**** delimited read
        static unsigned char read_00298_delim[] = 
            "\x0a";
        read_00298 = NULL;
        read_00298_len = 0;
        int read_00298_res = delimited_read(0, &read_00298, &read_00298_len, read_00298_delim, 1);
        if (read_00298_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00298_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00298_00000_match;
        pcre *read_00298_00000_pcre = init_regex(read_00298_00000_regex);
        if (read_00298_00000_pcre != NULL) {
            int rc = regex_match(read_00298_00000_pcre, 0, read_00298 + read_00298_ptr, read_00298_len - read_00298_ptr, &read_00298_00000_match);
            if (rc > 0) {
                read_00298_ptr += read_00298_00000_match.match_end - read_00298_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00298_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00298);
        if (read_00298_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00299;
        unsigned int read_00299_len;
        unsigned int read_00299_ptr = 0;
        //**** delimited read
        static unsigned char read_00299_delim[] = 
            "\x0a";
        read_00299 = NULL;
        read_00299_len = 0;
        int read_00299_res = delimited_read(0, &read_00299, &read_00299_len, read_00299_delim, 1);
        if (read_00299_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00299_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00299_00000_match;
        pcre *read_00299_00000_pcre = init_regex(read_00299_00000_regex);
        if (read_00299_00000_pcre != NULL) {
            int rc = regex_match(read_00299_00000_pcre, 0, read_00299 + read_00299_ptr, read_00299_len - read_00299_ptr, &read_00299_00000_match);
            if (rc > 0) {
                read_00299_ptr += read_00299_00000_match.match_end - read_00299_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00299_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00299);
        if (read_00299_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00300;
        unsigned int read_00300_len;
        unsigned int read_00300_ptr = 0;
        //**** delimited read
        static unsigned char read_00300_delim[] = 
            "\x0a";
        read_00300 = NULL;
        read_00300_len = 0;
        int read_00300_res = delimited_read(0, &read_00300, &read_00300_len, read_00300_delim, 1);
        if (read_00300_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00300_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00300_00000_match;
        pcre *read_00300_00000_pcre = init_regex(read_00300_00000_regex);
        if (read_00300_00000_pcre != NULL) {
            int rc = regex_match(read_00300_00000_pcre, 0, read_00300 + read_00300_ptr, read_00300_len - read_00300_ptr, &read_00300_00000_match);
            if (rc > 0) {
                read_00300_ptr += read_00300_00000_match.match_end - read_00300_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00300_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00300);
        if (read_00300_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00022_00000[] = 
            "\x3a";
        static unsigned int write_00022_00000_len = 1;
        unsigned char *write_00022 = NULL;
        unsigned int write_00022_len = 0;
        write_00022 = append_buf(write_00022, &write_00022_len, write_00022_00000, write_00022_00000_len);
        if (write_00022_len > 0) {
            transmit_all(1, write_00022, write_00022_len);
        }
        free(write_00022);
    } while (0);
    do {
        unsigned char *read_00301;
        unsigned int read_00301_len;
        unsigned int read_00301_ptr = 0;
        //**** delimited read
        static unsigned char read_00301_delim[] = 
            "\x0a";
        read_00301 = NULL;
        read_00301_len = 0;
        int read_00301_res = delimited_read(0, &read_00301, &read_00301_len, read_00301_delim, 1);
        if (read_00301_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00301_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00301_00000_match;
        pcre *read_00301_00000_pcre = init_regex(read_00301_00000_regex);
        if (read_00301_00000_pcre != NULL) {
            int rc = regex_match(read_00301_00000_pcre, 0, read_00301 + read_00301_ptr, read_00301_len - read_00301_ptr, &read_00301_00000_match);
            if (rc > 0) {
                read_00301_ptr += read_00301_00000_match.match_end - read_00301_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00301_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00301);
        if (read_00301_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00302;
        unsigned int read_00302_len;
        unsigned int read_00302_ptr = 0;
        //**** delimited read
        static unsigned char read_00302_delim[] = 
            "\x0a";
        read_00302 = NULL;
        read_00302_len = 0;
        int read_00302_res = delimited_read(0, &read_00302, &read_00302_len, read_00302_delim, 1);
        if (read_00302_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00302_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00302_00000_match;
        pcre *read_00302_00000_pcre = init_regex(read_00302_00000_regex);
        if (read_00302_00000_pcre != NULL) {
            int rc = regex_match(read_00302_00000_pcre, 0, read_00302 + read_00302_ptr, read_00302_len - read_00302_ptr, &read_00302_00000_match);
            if (rc > 0) {
                read_00302_ptr += read_00302_00000_match.match_end - read_00302_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00302_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00302);
        if (read_00302_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00303;
        unsigned int read_00303_len;
        unsigned int read_00303_ptr = 0;
        //**** delimited read
        static unsigned char read_00303_delim[] = 
            "\x0a";
        read_00303 = NULL;
        read_00303_len = 0;
        int read_00303_res = delimited_read(0, &read_00303, &read_00303_len, read_00303_delim, 1);
        if (read_00303_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00303_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00303_00000_match;
        pcre *read_00303_00000_pcre = init_regex(read_00303_00000_regex);
        if (read_00303_00000_pcre != NULL) {
            int rc = regex_match(read_00303_00000_pcre, 0, read_00303 + read_00303_ptr, read_00303_len - read_00303_ptr, &read_00303_00000_match);
            if (rc > 0) {
                read_00303_ptr += read_00303_00000_match.match_end - read_00303_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00303_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00303);
        if (read_00303_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00304;
        unsigned int read_00304_len;
        unsigned int read_00304_ptr = 0;
        //**** delimited read
        static unsigned char read_00304_delim[] = 
            "\x0a";
        read_00304 = NULL;
        read_00304_len = 0;
        int read_00304_res = delimited_read(0, &read_00304, &read_00304_len, read_00304_delim, 1);
        if (read_00304_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00304_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00304_00000_match;
        pcre *read_00304_00000_pcre = init_regex(read_00304_00000_regex);
        if (read_00304_00000_pcre != NULL) {
            int rc = regex_match(read_00304_00000_pcre, 0, read_00304 + read_00304_ptr, read_00304_len - read_00304_ptr, &read_00304_00000_match);
            if (rc > 0) {
                read_00304_ptr += read_00304_00000_match.match_end - read_00304_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00304_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00304);
        if (read_00304_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00305;
        unsigned int read_00305_len;
        unsigned int read_00305_ptr = 0;
        //**** delimited read
        static unsigned char read_00305_delim[] = 
            "\x0a";
        read_00305 = NULL;
        read_00305_len = 0;
        int read_00305_res = delimited_read(0, &read_00305, &read_00305_len, read_00305_delim, 1);
        if (read_00305_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00305_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00305_00000_match;
        pcre *read_00305_00000_pcre = init_regex(read_00305_00000_regex);
        if (read_00305_00000_pcre != NULL) {
            int rc = regex_match(read_00305_00000_pcre, 0, read_00305 + read_00305_ptr, read_00305_len - read_00305_ptr, &read_00305_00000_match);
            if (rc > 0) {
                read_00305_ptr += read_00305_00000_match.match_end - read_00305_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00305_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00305);
        if (read_00305_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00306;
        unsigned int read_00306_len;
        unsigned int read_00306_ptr = 0;
        //**** delimited read
        static unsigned char read_00306_delim[] = 
            "\x0a";
        read_00306 = NULL;
        read_00306_len = 0;
        int read_00306_res = delimited_read(0, &read_00306, &read_00306_len, read_00306_delim, 1);
        if (read_00306_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00306_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00306_00000_match;
        pcre *read_00306_00000_pcre = init_regex(read_00306_00000_regex);
        if (read_00306_00000_pcre != NULL) {
            int rc = regex_match(read_00306_00000_pcre, 0, read_00306 + read_00306_ptr, read_00306_len - read_00306_ptr, &read_00306_00000_match);
            if (rc > 0) {
                read_00306_ptr += read_00306_00000_match.match_end - read_00306_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00306_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00306);
        if (read_00306_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00307;
        unsigned int read_00307_len;
        unsigned int read_00307_ptr = 0;
        //**** delimited read
        static unsigned char read_00307_delim[] = 
            "\x0a";
        read_00307 = NULL;
        read_00307_len = 0;
        int read_00307_res = delimited_read(0, &read_00307, &read_00307_len, read_00307_delim, 1);
        if (read_00307_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00307_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00307_00000_match;
        pcre *read_00307_00000_pcre = init_regex(read_00307_00000_regex);
        if (read_00307_00000_pcre != NULL) {
            int rc = regex_match(read_00307_00000_pcre, 0, read_00307 + read_00307_ptr, read_00307_len - read_00307_ptr, &read_00307_00000_match);
            if (rc > 0) {
                read_00307_ptr += read_00307_00000_match.match_end - read_00307_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00307_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00307);
        if (read_00307_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00308;
        unsigned int read_00308_len;
        unsigned int read_00308_ptr = 0;
        //**** delimited read
        static unsigned char read_00308_delim[] = 
            "\x0a";
        read_00308 = NULL;
        read_00308_len = 0;
        int read_00308_res = delimited_read(0, &read_00308, &read_00308_len, read_00308_delim, 1);
        if (read_00308_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00308_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00308_00000_match;
        pcre *read_00308_00000_pcre = init_regex(read_00308_00000_regex);
        if (read_00308_00000_pcre != NULL) {
            int rc = regex_match(read_00308_00000_pcre, 0, read_00308 + read_00308_ptr, read_00308_len - read_00308_ptr, &read_00308_00000_match);
            if (rc > 0) {
                read_00308_ptr += read_00308_00000_match.match_end - read_00308_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00308_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00308);
        if (read_00308_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00309;
        unsigned int read_00309_len;
        unsigned int read_00309_ptr = 0;
        //**** delimited read
        static unsigned char read_00309_delim[] = 
            "\x0a";
        read_00309 = NULL;
        read_00309_len = 0;
        int read_00309_res = delimited_read(0, &read_00309, &read_00309_len, read_00309_delim, 1);
        if (read_00309_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00309_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00309_00000_match;
        pcre *read_00309_00000_pcre = init_regex(read_00309_00000_regex);
        if (read_00309_00000_pcre != NULL) {
            int rc = regex_match(read_00309_00000_pcre, 0, read_00309 + read_00309_ptr, read_00309_len - read_00309_ptr, &read_00309_00000_match);
            if (rc > 0) {
                read_00309_ptr += read_00309_00000_match.match_end - read_00309_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00309_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00309);
        if (read_00309_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00310;
        unsigned int read_00310_len;
        unsigned int read_00310_ptr = 0;
        //**** delimited read
        static unsigned char read_00310_delim[] = 
            "\x0a";
        read_00310 = NULL;
        read_00310_len = 0;
        int read_00310_res = delimited_read(0, &read_00310, &read_00310_len, read_00310_delim, 1);
        if (read_00310_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00310_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00310_00000_match;
        pcre *read_00310_00000_pcre = init_regex(read_00310_00000_regex);
        if (read_00310_00000_pcre != NULL) {
            int rc = regex_match(read_00310_00000_pcre, 0, read_00310 + read_00310_ptr, read_00310_len - read_00310_ptr, &read_00310_00000_match);
            if (rc > 0) {
                read_00310_ptr += read_00310_00000_match.match_end - read_00310_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00310_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00310);
        if (read_00310_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00311;
        unsigned int read_00311_len;
        unsigned int read_00311_ptr = 0;
        //**** delimited read
        static unsigned char read_00311_delim[] = 
            "\x0a";
        read_00311 = NULL;
        read_00311_len = 0;
        int read_00311_res = delimited_read(0, &read_00311, &read_00311_len, read_00311_delim, 1);
        if (read_00311_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00311_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00311_00000_match;
        pcre *read_00311_00000_pcre = init_regex(read_00311_00000_regex);
        if (read_00311_00000_pcre != NULL) {
            int rc = regex_match(read_00311_00000_pcre, 0, read_00311 + read_00311_ptr, read_00311_len - read_00311_ptr, &read_00311_00000_match);
            if (rc > 0) {
                read_00311_ptr += read_00311_00000_match.match_end - read_00311_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00311_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00311);
        if (read_00311_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00312;
        unsigned int read_00312_len;
        unsigned int read_00312_ptr = 0;
        //**** delimited read
        static unsigned char read_00312_delim[] = 
            "\x0a";
        read_00312 = NULL;
        read_00312_len = 0;
        int read_00312_res = delimited_read(0, &read_00312, &read_00312_len, read_00312_delim, 1);
        if (read_00312_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00312_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00312_00000_match;
        pcre *read_00312_00000_pcre = init_regex(read_00312_00000_regex);
        if (read_00312_00000_pcre != NULL) {
            int rc = regex_match(read_00312_00000_pcre, 0, read_00312 + read_00312_ptr, read_00312_len - read_00312_ptr, &read_00312_00000_match);
            if (rc > 0) {
                read_00312_ptr += read_00312_00000_match.match_end - read_00312_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00312_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00312);
        if (read_00312_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00023_00000[] = 
            "\x3a";
        static unsigned int write_00023_00000_len = 1;
        unsigned char *write_00023 = NULL;
        unsigned int write_00023_len = 0;
        write_00023 = append_buf(write_00023, &write_00023_len, write_00023_00000, write_00023_00000_len);
        if (write_00023_len > 0) {
            transmit_all(1, write_00023, write_00023_len);
        }
        free(write_00023);
    } while (0);
    do {
        unsigned char *read_00313;
        unsigned int read_00313_len;
        unsigned int read_00313_ptr = 0;
        //**** delimited read
        static unsigned char read_00313_delim[] = 
            "\x0a";
        read_00313 = NULL;
        read_00313_len = 0;
        int read_00313_res = delimited_read(0, &read_00313, &read_00313_len, read_00313_delim, 1);
        if (read_00313_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00313_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00313_00000_match;
        pcre *read_00313_00000_pcre = init_regex(read_00313_00000_regex);
        if (read_00313_00000_pcre != NULL) {
            int rc = regex_match(read_00313_00000_pcre, 0, read_00313 + read_00313_ptr, read_00313_len - read_00313_ptr, &read_00313_00000_match);
            if (rc > 0) {
                read_00313_ptr += read_00313_00000_match.match_end - read_00313_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00313_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00313);
        if (read_00313_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00314;
        unsigned int read_00314_len;
        unsigned int read_00314_ptr = 0;
        //**** delimited read
        static unsigned char read_00314_delim[] = 
            "\x0a";
        read_00314 = NULL;
        read_00314_len = 0;
        int read_00314_res = delimited_read(0, &read_00314, &read_00314_len, read_00314_delim, 1);
        if (read_00314_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00314_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00314_00000_match;
        pcre *read_00314_00000_pcre = init_regex(read_00314_00000_regex);
        if (read_00314_00000_pcre != NULL) {
            int rc = regex_match(read_00314_00000_pcre, 0, read_00314 + read_00314_ptr, read_00314_len - read_00314_ptr, &read_00314_00000_match);
            if (rc > 0) {
                read_00314_ptr += read_00314_00000_match.match_end - read_00314_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00314_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00314);
        if (read_00314_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00315;
        unsigned int read_00315_len;
        unsigned int read_00315_ptr = 0;
        //**** delimited read
        static unsigned char read_00315_delim[] = 
            "\x0a";
        read_00315 = NULL;
        read_00315_len = 0;
        int read_00315_res = delimited_read(0, &read_00315, &read_00315_len, read_00315_delim, 1);
        if (read_00315_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00315_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00315_00000_match;
        pcre *read_00315_00000_pcre = init_regex(read_00315_00000_regex);
        if (read_00315_00000_pcre != NULL) {
            int rc = regex_match(read_00315_00000_pcre, 0, read_00315 + read_00315_ptr, read_00315_len - read_00315_ptr, &read_00315_00000_match);
            if (rc > 0) {
                read_00315_ptr += read_00315_00000_match.match_end - read_00315_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00315_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00315);
        if (read_00315_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00316;
        unsigned int read_00316_len;
        unsigned int read_00316_ptr = 0;
        //**** delimited read
        static unsigned char read_00316_delim[] = 
            "\x0a";
        read_00316 = NULL;
        read_00316_len = 0;
        int read_00316_res = delimited_read(0, &read_00316, &read_00316_len, read_00316_delim, 1);
        if (read_00316_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00316_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00316_00000_match;
        pcre *read_00316_00000_pcre = init_regex(read_00316_00000_regex);
        if (read_00316_00000_pcre != NULL) {
            int rc = regex_match(read_00316_00000_pcre, 0, read_00316 + read_00316_ptr, read_00316_len - read_00316_ptr, &read_00316_00000_match);
            if (rc > 0) {
                read_00316_ptr += read_00316_00000_match.match_end - read_00316_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00316_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00316);
        if (read_00316_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00317;
        unsigned int read_00317_len;
        unsigned int read_00317_ptr = 0;
        //**** delimited read
        static unsigned char read_00317_delim[] = 
            "\x0a";
        read_00317 = NULL;
        read_00317_len = 0;
        int read_00317_res = delimited_read(0, &read_00317, &read_00317_len, read_00317_delim, 1);
        if (read_00317_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00317_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00317_00000_match;
        pcre *read_00317_00000_pcre = init_regex(read_00317_00000_regex);
        if (read_00317_00000_pcre != NULL) {
            int rc = regex_match(read_00317_00000_pcre, 0, read_00317 + read_00317_ptr, read_00317_len - read_00317_ptr, &read_00317_00000_match);
            if (rc > 0) {
                read_00317_ptr += read_00317_00000_match.match_end - read_00317_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00317_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00317);
        if (read_00317_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00318;
        unsigned int read_00318_len;
        unsigned int read_00318_ptr = 0;
        //**** delimited read
        static unsigned char read_00318_delim[] = 
            "\x0a";
        read_00318 = NULL;
        read_00318_len = 0;
        int read_00318_res = delimited_read(0, &read_00318, &read_00318_len, read_00318_delim, 1);
        if (read_00318_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00318_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00318_00000_match;
        pcre *read_00318_00000_pcre = init_regex(read_00318_00000_regex);
        if (read_00318_00000_pcre != NULL) {
            int rc = regex_match(read_00318_00000_pcre, 0, read_00318 + read_00318_ptr, read_00318_len - read_00318_ptr, &read_00318_00000_match);
            if (rc > 0) {
                read_00318_ptr += read_00318_00000_match.match_end - read_00318_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00318_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00318);
        if (read_00318_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00319;
        unsigned int read_00319_len;
        unsigned int read_00319_ptr = 0;
        //**** delimited read
        static unsigned char read_00319_delim[] = 
            "\x0a";
        read_00319 = NULL;
        read_00319_len = 0;
        int read_00319_res = delimited_read(0, &read_00319, &read_00319_len, read_00319_delim, 1);
        if (read_00319_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00319_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00319_00000_match;
        pcre *read_00319_00000_pcre = init_regex(read_00319_00000_regex);
        if (read_00319_00000_pcre != NULL) {
            int rc = regex_match(read_00319_00000_pcre, 0, read_00319 + read_00319_ptr, read_00319_len - read_00319_ptr, &read_00319_00000_match);
            if (rc > 0) {
                read_00319_ptr += read_00319_00000_match.match_end - read_00319_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00319_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00319);
        if (read_00319_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00320;
        unsigned int read_00320_len;
        unsigned int read_00320_ptr = 0;
        //**** delimited read
        static unsigned char read_00320_delim[] = 
            "\x0a";
        read_00320 = NULL;
        read_00320_len = 0;
        int read_00320_res = delimited_read(0, &read_00320, &read_00320_len, read_00320_delim, 1);
        if (read_00320_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00320_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00320_00000_match;
        pcre *read_00320_00000_pcre = init_regex(read_00320_00000_regex);
        if (read_00320_00000_pcre != NULL) {
            int rc = regex_match(read_00320_00000_pcre, 0, read_00320 + read_00320_ptr, read_00320_len - read_00320_ptr, &read_00320_00000_match);
            if (rc > 0) {
                read_00320_ptr += read_00320_00000_match.match_end - read_00320_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00320_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00320);
        if (read_00320_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00321;
        unsigned int read_00321_len;
        unsigned int read_00321_ptr = 0;
        //**** delimited read
        static unsigned char read_00321_delim[] = 
            "\x0a";
        read_00321 = NULL;
        read_00321_len = 0;
        int read_00321_res = delimited_read(0, &read_00321, &read_00321_len, read_00321_delim, 1);
        if (read_00321_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00321_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00321_00000_match;
        pcre *read_00321_00000_pcre = init_regex(read_00321_00000_regex);
        if (read_00321_00000_pcre != NULL) {
            int rc = regex_match(read_00321_00000_pcre, 0, read_00321 + read_00321_ptr, read_00321_len - read_00321_ptr, &read_00321_00000_match);
            if (rc > 0) {
                read_00321_ptr += read_00321_00000_match.match_end - read_00321_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00321_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00321);
        if (read_00321_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00322;
        unsigned int read_00322_len;
        unsigned int read_00322_ptr = 0;
        //**** delimited read
        static unsigned char read_00322_delim[] = 
            "\x0a";
        read_00322 = NULL;
        read_00322_len = 0;
        int read_00322_res = delimited_read(0, &read_00322, &read_00322_len, read_00322_delim, 1);
        if (read_00322_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00322_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00322_00000_match;
        pcre *read_00322_00000_pcre = init_regex(read_00322_00000_regex);
        if (read_00322_00000_pcre != NULL) {
            int rc = regex_match(read_00322_00000_pcre, 0, read_00322 + read_00322_ptr, read_00322_len - read_00322_ptr, &read_00322_00000_match);
            if (rc > 0) {
                read_00322_ptr += read_00322_00000_match.match_end - read_00322_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00322_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00322);
        if (read_00322_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00323;
        unsigned int read_00323_len;
        unsigned int read_00323_ptr = 0;
        //**** delimited read
        static unsigned char read_00323_delim[] = 
            "\x0a";
        read_00323 = NULL;
        read_00323_len = 0;
        int read_00323_res = delimited_read(0, &read_00323, &read_00323_len, read_00323_delim, 1);
        if (read_00323_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00323_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00323_00000_match;
        pcre *read_00323_00000_pcre = init_regex(read_00323_00000_regex);
        if (read_00323_00000_pcre != NULL) {
            int rc = regex_match(read_00323_00000_pcre, 0, read_00323 + read_00323_ptr, read_00323_len - read_00323_ptr, &read_00323_00000_match);
            if (rc > 0) {
                read_00323_ptr += read_00323_00000_match.match_end - read_00323_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00323_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00323);
        if (read_00323_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00324;
        unsigned int read_00324_len;
        unsigned int read_00324_ptr = 0;
        //**** length read
        read_00324_len = 20;
        read_00324 = (unsigned char*)malloc(read_00324_len);
        int read_00324_res = length_read(0, read_00324, read_00324_len);
        if (read_00324_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00324_00000[] = 
            "\x53\x6f\x72\x72\x79\x2c\x20\x74\x68\x65\x20\x77\x6f\x72\x64\x20"
            "\x77\x61\x73\x20";
        read_00324_ptr += data_match(read_00324 + read_00324_ptr, read_00324_len - read_00324_ptr, match_00324_00000, 20);
        free(read_00324);
        if (read_00324_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00325;
        unsigned int read_00325_len;
        unsigned int read_00325_ptr = 0;
        //**** length read
        read_00325_len = 8;
        read_00325 = (unsigned char*)malloc(read_00325_len);
        int read_00325_res = length_read(0, read_00325, read_00325_len);
        if (read_00325_res) {} //silence unused variable warning
        //**** read assign to var "word2" from slice
        assign_from_slice("word2", read_00325, read_00325_len - read_00325_ptr, 0, 0, 1);
        free(read_00325);
        if (read_00325_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00326;
        unsigned int read_00326_len;
        unsigned int read_00326_ptr = 0;
        //**** delimited read
        static unsigned char read_00326_delim[] = 
            "\x0a";
        read_00326 = NULL;
        read_00326_len = 0;
        int read_00326_res = delimited_read(0, &read_00326, &read_00326_len, read_00326_delim, 1);
        if (read_00326_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00326_00000[] = 
            "\x21\x0a";
        read_00326_ptr += data_match(read_00326 + read_00326_ptr, read_00326_len - read_00326_ptr, match_00326_00000, 2);
        free(read_00326);
        if (read_00326_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00327;
        unsigned int read_00327_len;
        unsigned int read_00327_ptr = 0;
        //**** delimited read
        static unsigned char read_00327_delim[] = 
            "\x0a";
        read_00327 = NULL;
        read_00327_len = 0;
        int read_00327_res = delimited_read(0, &read_00327, &read_00327_len, read_00327_delim, 1);
        if (read_00327_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00327_00000[] = 
            "\x53\x68\x61\x6c\x6c\x20\x77\x65\x20\x70\x6c\x61\x79\x20\x61\x20"
            "\x67\x61\x6d\x65\x3f\x0a";
        read_00327_ptr += data_match(read_00327 + read_00327_ptr, read_00327_len - read_00327_ptr, match_00327_00000, 22);
        free(read_00327);
        if (read_00327_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00328;
        unsigned int read_00328_len;
        unsigned int read_00328_ptr = 0;
        //**** delimited read
        static unsigned char read_00328_delim[] = 
            "\x0a";
        read_00328 = NULL;
        read_00328_len = 0;
        int read_00328_res = delimited_read(0, &read_00328, &read_00328_len, read_00328_delim, 1);
        if (read_00328_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00328_00000[] = 
            "\x0a";
        read_00328_ptr += data_match(read_00328 + read_00328_ptr, read_00328_len - read_00328_ptr, match_00328_00000, 1);
        free(read_00328);
        if (read_00328_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00329;
        unsigned int read_00329_len;
        unsigned int read_00329_ptr = 0;
        //**** delimited read
        static unsigned char read_00329_delim[] = 
            "\x0a";
        read_00329 = NULL;
        read_00329_len = 0;
        int read_00329_res = delimited_read(0, &read_00329, &read_00329_len, read_00329_delim, 1);
        if (read_00329_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00329_00000[] = 
            "\x31\x2e\x20\x48\x61\x6e\x67\x6d\x61\x6e\x0a";
        read_00329_ptr += data_match(read_00329 + read_00329_ptr, read_00329_len - read_00329_ptr, match_00329_00000, 11);
        free(read_00329);
        if (read_00329_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00330;
        unsigned int read_00330_len;
        unsigned int read_00330_ptr = 0;
        //**** delimited read
        static unsigned char read_00330_delim[] = 
            "\x0a";
        read_00330 = NULL;
        read_00330_len = 0;
        int read_00330_res = delimited_read(0, &read_00330, &read_00330_len, read_00330_delim, 1);
        if (read_00330_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00330_00000[] = 
            "\x32\x2e\x20\x43\x68\x65\x73\x73\x0a";
        read_00330_ptr += data_match(read_00330 + read_00330_ptr, read_00330_len - read_00330_ptr, match_00330_00000, 9);
        free(read_00330);
        if (read_00330_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00331;
        unsigned int read_00331_len;
        unsigned int read_00331_ptr = 0;
        //**** delimited read
        static unsigned char read_00331_delim[] = 
            "\x0a";
        read_00331 = NULL;
        read_00331_len = 0;
        int read_00331_res = delimited_read(0, &read_00331, &read_00331_len, read_00331_delim, 1);
        if (read_00331_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00331_00000[] = 
            "\x33\x2e\x20\x53\x75\x64\x6f\x6b\x75\x0a";
        read_00331_ptr += data_match(read_00331 + read_00331_ptr, read_00331_len - read_00331_ptr, match_00331_00000, 10);
        free(read_00331);
        if (read_00331_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00332;
        unsigned int read_00332_len;
        unsigned int read_00332_ptr = 0;
        //**** delimited read
        static unsigned char read_00332_delim[] = 
            "\x0a";
        read_00332 = NULL;
        read_00332_len = 0;
        int read_00332_res = delimited_read(0, &read_00332, &read_00332_len, read_00332_delim, 1);
        if (read_00332_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00332_00000[] = 
            "\x34\x2e\x20\x47\x61\x6c\x6c\x6f\x6e\x20\x43\x68\x61\x6c\x6c\x65"
            "\x6e\x67\x65\x0a";
        read_00332_ptr += data_match(read_00332 + read_00332_ptr, read_00332_len - read_00332_ptr, match_00332_00000, 20);
        free(read_00332);
        if (read_00332_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00333;
        unsigned int read_00333_len;
        unsigned int read_00333_ptr = 0;
        //**** delimited read
        static unsigned char read_00333_delim[] = 
            "\x0a";
        read_00333 = NULL;
        read_00333_len = 0;
        int read_00333_res = delimited_read(0, &read_00333, &read_00333_len, read_00333_delim, 1);
        if (read_00333_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00333_00000[] = 
            "\x35\x2e\x20\x53\x61\x66\x61\x72\x69\x20\x5a\x6f\x6e\x65\x0a";
        read_00333_ptr += data_match(read_00333 + read_00333_ptr, read_00333_len - read_00333_ptr, match_00333_00000, 15);
        free(read_00333);
        if (read_00333_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00334;
        unsigned int read_00334_len;
        unsigned int read_00334_ptr = 0;
        //**** delimited read
        static unsigned char read_00334_delim[] = 
            "\x0a";
        read_00334 = NULL;
        read_00334_len = 0;
        int read_00334_res = delimited_read(0, &read_00334, &read_00334_len, read_00334_delim, 1);
        if (read_00334_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00334_00000[] = 
            "\x36\x2e\x20\x52\x75\x73\x73\x69\x61\x6e\x20\x52\x6f\x75\x6c\x65"
            "\x74\x74\x65\x0a";
        read_00334_ptr += data_match(read_00334 + read_00334_ptr, read_00334_len - read_00334_ptr, match_00334_00000, 20);
        free(read_00334);
        if (read_00334_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00335;
        unsigned int read_00335_len;
        unsigned int read_00335_ptr = 0;
        //**** delimited read
        static unsigned char read_00335_delim[] = 
            "\x0a";
        read_00335 = NULL;
        read_00335_len = 0;
        int read_00335_res = delimited_read(0, &read_00335, &read_00335_len, read_00335_delim, 1);
        if (read_00335_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00335_00000[] = 
            "\x37\x2e\x20\x47\x6c\x6f\x62\x61\x6c\x20\x54\x68\x65\x72\x6d\x6f"
            "\x6e\x75\x63\x6c\x65\x61\x72\x20\x57\x61\x72\x0a";
        read_00335_ptr += data_match(read_00335 + read_00335_ptr, read_00335_len - read_00335_ptr, match_00335_00000, 28);
        free(read_00335);
        if (read_00335_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00336;
        unsigned int read_00336_len;
        unsigned int read_00336_ptr = 0;
        //**** delimited read
        static unsigned char read_00336_delim[] = 
            "\x0a";
        read_00336 = NULL;
        read_00336_len = 0;
        int read_00336_res = delimited_read(0, &read_00336, &read_00336_len, read_00336_delim, 1);
        if (read_00336_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00336_00000[] = 
            "\x38\x2e\x20\x51\x75\x69\x74\x0a";
        read_00336_ptr += data_match(read_00336 + read_00336_ptr, read_00336_len - read_00336_ptr, match_00336_00000, 8);
        free(read_00336);
        if (read_00336_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00337;
        unsigned int read_00337_len;
        unsigned int read_00337_ptr = 0;
        //**** delimited read
        static unsigned char read_00337_delim[] = 
            "\x0a";
        read_00337 = NULL;
        read_00337_len = 0;
        int read_00337_res = delimited_read(0, &read_00337, &read_00337_len, read_00337_delim, 1);
        if (read_00337_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00337_00000[] = 
            "\x0a";
        read_00337_ptr += data_match(read_00337 + read_00337_ptr, read_00337_len - read_00337_ptr, match_00337_00000, 1);
        free(read_00337);
        if (read_00337_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00024_00000[] = 
            "\x31\x0a";
        static unsigned int write_00024_00000_len = 2;
        unsigned char *write_00024 = NULL;
        unsigned int write_00024_len = 0;
        write_00024 = append_buf(write_00024, &write_00024_len, write_00024_00000, write_00024_00000_len);
        if (write_00024_len > 0) {
            transmit_all(1, write_00024, write_00024_len);
        }
        free(write_00024);
    } while (0);
    do {
        unsigned char *read_00338;
        unsigned int read_00338_len;
        unsigned int read_00338_ptr = 0;
        //**** delimited read
        static unsigned char read_00338_delim[] = 
            "\x0a";
        read_00338 = NULL;
        read_00338_len = 0;
        int read_00338_res = delimited_read(0, &read_00338, &read_00338_len, read_00338_delim, 1);
        if (read_00338_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00338_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00338_00000_match;
        pcre *read_00338_00000_pcre = init_regex(read_00338_00000_regex);
        if (read_00338_00000_pcre != NULL) {
            int rc = regex_match(read_00338_00000_pcre, 0, read_00338 + read_00338_ptr, read_00338_len - read_00338_ptr, &read_00338_00000_match);
            if (rc > 0) {
                read_00338_ptr += read_00338_00000_match.match_end - read_00338_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00338_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00338);
        if (read_00338_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00339;
        unsigned int read_00339_len;
        unsigned int read_00339_ptr = 0;
        //**** delimited read
        static unsigned char read_00339_delim[] = 
            "\x0a";
        read_00339 = NULL;
        read_00339_len = 0;
        int read_00339_res = delimited_read(0, &read_00339, &read_00339_len, read_00339_delim, 1);
        if (read_00339_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00339_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00339_00000_match;
        pcre *read_00339_00000_pcre = init_regex(read_00339_00000_regex);
        if (read_00339_00000_pcre != NULL) {
            int rc = regex_match(read_00339_00000_pcre, 0, read_00339 + read_00339_ptr, read_00339_len - read_00339_ptr, &read_00339_00000_match);
            if (rc > 0) {
                read_00339_ptr += read_00339_00000_match.match_end - read_00339_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00339_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00339);
        if (read_00339_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00340;
        unsigned int read_00340_len;
        unsigned int read_00340_ptr = 0;
        //**** delimited read
        static unsigned char read_00340_delim[] = 
            "\x0a";
        read_00340 = NULL;
        read_00340_len = 0;
        int read_00340_res = delimited_read(0, &read_00340, &read_00340_len, read_00340_delim, 1);
        if (read_00340_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00340_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00340_00000_match;
        pcre *read_00340_00000_pcre = init_regex(read_00340_00000_regex);
        if (read_00340_00000_pcre != NULL) {
            int rc = regex_match(read_00340_00000_pcre, 0, read_00340 + read_00340_ptr, read_00340_len - read_00340_ptr, &read_00340_00000_match);
            if (rc > 0) {
                read_00340_ptr += read_00340_00000_match.match_end - read_00340_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00340_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00340);
        if (read_00340_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00341;
        unsigned int read_00341_len;
        unsigned int read_00341_ptr = 0;
        //**** delimited read
        static unsigned char read_00341_delim[] = 
            "\x0a";
        read_00341 = NULL;
        read_00341_len = 0;
        int read_00341_res = delimited_read(0, &read_00341, &read_00341_len, read_00341_delim, 1);
        if (read_00341_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00341_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00341_00000_match;
        pcre *read_00341_00000_pcre = init_regex(read_00341_00000_regex);
        if (read_00341_00000_pcre != NULL) {
            int rc = regex_match(read_00341_00000_pcre, 0, read_00341 + read_00341_ptr, read_00341_len - read_00341_ptr, &read_00341_00000_match);
            if (rc > 0) {
                read_00341_ptr += read_00341_00000_match.match_end - read_00341_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00341_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00341);
        if (read_00341_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00342;
        unsigned int read_00342_len;
        unsigned int read_00342_ptr = 0;
        //**** delimited read
        static unsigned char read_00342_delim[] = 
            "\x0a";
        read_00342 = NULL;
        read_00342_len = 0;
        int read_00342_res = delimited_read(0, &read_00342, &read_00342_len, read_00342_delim, 1);
        if (read_00342_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00342_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00342_00000_match;
        pcre *read_00342_00000_pcre = init_regex(read_00342_00000_regex);
        if (read_00342_00000_pcre != NULL) {
            int rc = regex_match(read_00342_00000_pcre, 0, read_00342 + read_00342_ptr, read_00342_len - read_00342_ptr, &read_00342_00000_match);
            if (rc > 0) {
                read_00342_ptr += read_00342_00000_match.match_end - read_00342_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00342_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00342);
        if (read_00342_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00343;
        unsigned int read_00343_len;
        unsigned int read_00343_ptr = 0;
        //**** delimited read
        static unsigned char read_00343_delim[] = 
            "\x0a";
        read_00343 = NULL;
        read_00343_len = 0;
        int read_00343_res = delimited_read(0, &read_00343, &read_00343_len, read_00343_delim, 1);
        if (read_00343_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00343_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00343_00000_match;
        pcre *read_00343_00000_pcre = init_regex(read_00343_00000_regex);
        if (read_00343_00000_pcre != NULL) {
            int rc = regex_match(read_00343_00000_pcre, 0, read_00343 + read_00343_ptr, read_00343_len - read_00343_ptr, &read_00343_00000_match);
            if (rc > 0) {
                read_00343_ptr += read_00343_00000_match.match_end - read_00343_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00343_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00343);
        if (read_00343_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00344;
        unsigned int read_00344_len;
        unsigned int read_00344_ptr = 0;
        //**** delimited read
        static unsigned char read_00344_delim[] = 
            "\x0a";
        read_00344 = NULL;
        read_00344_len = 0;
        int read_00344_res = delimited_read(0, &read_00344, &read_00344_len, read_00344_delim, 1);
        if (read_00344_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00344_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00344_00000_match;
        pcre *read_00344_00000_pcre = init_regex(read_00344_00000_regex);
        if (read_00344_00000_pcre != NULL) {
            int rc = regex_match(read_00344_00000_pcre, 0, read_00344 + read_00344_ptr, read_00344_len - read_00344_ptr, &read_00344_00000_match);
            if (rc > 0) {
                read_00344_ptr += read_00344_00000_match.match_end - read_00344_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00344_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00344);
        if (read_00344_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00345;
        unsigned int read_00345_len;
        unsigned int read_00345_ptr = 0;
        //**** delimited read
        static unsigned char read_00345_delim[] = 
            "\x0a";
        read_00345 = NULL;
        read_00345_len = 0;
        int read_00345_res = delimited_read(0, &read_00345, &read_00345_len, read_00345_delim, 1);
        if (read_00345_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00345_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00345_00000_match;
        pcre *read_00345_00000_pcre = init_regex(read_00345_00000_regex);
        if (read_00345_00000_pcre != NULL) {
            int rc = regex_match(read_00345_00000_pcre, 0, read_00345 + read_00345_ptr, read_00345_len - read_00345_ptr, &read_00345_00000_match);
            if (rc > 0) {
                read_00345_ptr += read_00345_00000_match.match_end - read_00345_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00345_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00345);
        if (read_00345_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00346;
        unsigned int read_00346_len;
        unsigned int read_00346_ptr = 0;
        //**** delimited read
        static unsigned char read_00346_delim[] = 
            "\x0a";
        read_00346 = NULL;
        read_00346_len = 0;
        int read_00346_res = delimited_read(0, &read_00346, &read_00346_len, read_00346_delim, 1);
        if (read_00346_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00346_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00346_00000_match;
        pcre *read_00346_00000_pcre = init_regex(read_00346_00000_regex);
        if (read_00346_00000_pcre != NULL) {
            int rc = regex_match(read_00346_00000_pcre, 0, read_00346 + read_00346_ptr, read_00346_len - read_00346_ptr, &read_00346_00000_match);
            if (rc > 0) {
                read_00346_ptr += read_00346_00000_match.match_end - read_00346_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00346_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00346);
        if (read_00346_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00347;
        unsigned int read_00347_len;
        unsigned int read_00347_ptr = 0;
        //**** delimited read
        static unsigned char read_00347_delim[] = 
            "\x0a";
        read_00347 = NULL;
        read_00347_len = 0;
        int read_00347_res = delimited_read(0, &read_00347, &read_00347_len, read_00347_delim, 1);
        if (read_00347_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00347_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00347_00000_match;
        pcre *read_00347_00000_pcre = init_regex(read_00347_00000_regex);
        if (read_00347_00000_pcre != NULL) {
            int rc = regex_match(read_00347_00000_pcre, 0, read_00347 + read_00347_ptr, read_00347_len - read_00347_ptr, &read_00347_00000_match);
            if (rc > 0) {
                read_00347_ptr += read_00347_00000_match.match_end - read_00347_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00347_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00347);
        if (read_00347_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00348;
        unsigned int read_00348_len;
        unsigned int read_00348_ptr = 0;
        //**** delimited read
        static unsigned char read_00348_delim[] = 
            "\x0a";
        read_00348 = NULL;
        read_00348_len = 0;
        int read_00348_res = delimited_read(0, &read_00348, &read_00348_len, read_00348_delim, 1);
        if (read_00348_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00348_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00348_00000_match;
        pcre *read_00348_00000_pcre = init_regex(read_00348_00000_regex);
        if (read_00348_00000_pcre != NULL) {
            int rc = regex_match(read_00348_00000_pcre, 0, read_00348 + read_00348_ptr, read_00348_len - read_00348_ptr, &read_00348_00000_match);
            if (rc > 0) {
                read_00348_ptr += read_00348_00000_match.match_end - read_00348_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00348_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00348);
        if (read_00348_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00349;
        unsigned int read_00349_len;
        unsigned int read_00349_ptr = 0;
        //**** delimited read
        static unsigned char read_00349_delim[] = 
            "\x0a";
        read_00349 = NULL;
        read_00349_len = 0;
        int read_00349_res = delimited_read(0, &read_00349, &read_00349_len, read_00349_delim, 1);
        if (read_00349_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00349_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00349_00000_match;
        pcre *read_00349_00000_pcre = init_regex(read_00349_00000_regex);
        if (read_00349_00000_pcre != NULL) {
            int rc = regex_match(read_00349_00000_pcre, 0, read_00349 + read_00349_ptr, read_00349_len - read_00349_ptr, &read_00349_00000_match);
            if (rc > 0) {
                read_00349_ptr += read_00349_00000_match.match_end - read_00349_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00349_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00349);
        if (read_00349_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00025_00000[] = 
            "\x3a";
        static unsigned int write_00025_00000_len = 1;
        unsigned char *write_00025 = NULL;
        unsigned int write_00025_len = 0;
        write_00025 = append_buf(write_00025, &write_00025_len, write_00025_00000, write_00025_00000_len);
        if (write_00025_len > 0) {
            transmit_all(1, write_00025, write_00025_len);
        }
        free(write_00025);
    } while (0);
    do {
        unsigned char *read_00350;
        unsigned int read_00350_len;
        unsigned int read_00350_ptr = 0;
        //**** delimited read
        static unsigned char read_00350_delim[] = 
            "\x0a";
        read_00350 = NULL;
        read_00350_len = 0;
        int read_00350_res = delimited_read(0, &read_00350, &read_00350_len, read_00350_delim, 1);
        if (read_00350_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00350_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00350_00000_match;
        pcre *read_00350_00000_pcre = init_regex(read_00350_00000_regex);
        if (read_00350_00000_pcre != NULL) {
            int rc = regex_match(read_00350_00000_pcre, 0, read_00350 + read_00350_ptr, read_00350_len - read_00350_ptr, &read_00350_00000_match);
            if (rc > 0) {
                read_00350_ptr += read_00350_00000_match.match_end - read_00350_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00350_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00350);
        if (read_00350_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00351;
        unsigned int read_00351_len;
        unsigned int read_00351_ptr = 0;
        //**** delimited read
        static unsigned char read_00351_delim[] = 
            "\x0a";
        read_00351 = NULL;
        read_00351_len = 0;
        int read_00351_res = delimited_read(0, &read_00351, &read_00351_len, read_00351_delim, 1);
        if (read_00351_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00351_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00351_00000_match;
        pcre *read_00351_00000_pcre = init_regex(read_00351_00000_regex);
        if (read_00351_00000_pcre != NULL) {
            int rc = regex_match(read_00351_00000_pcre, 0, read_00351 + read_00351_ptr, read_00351_len - read_00351_ptr, &read_00351_00000_match);
            if (rc > 0) {
                read_00351_ptr += read_00351_00000_match.match_end - read_00351_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00351_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00351);
        if (read_00351_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00352;
        unsigned int read_00352_len;
        unsigned int read_00352_ptr = 0;
        //**** delimited read
        static unsigned char read_00352_delim[] = 
            "\x0a";
        read_00352 = NULL;
        read_00352_len = 0;
        int read_00352_res = delimited_read(0, &read_00352, &read_00352_len, read_00352_delim, 1);
        if (read_00352_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00352_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00352_00000_match;
        pcre *read_00352_00000_pcre = init_regex(read_00352_00000_regex);
        if (read_00352_00000_pcre != NULL) {
            int rc = regex_match(read_00352_00000_pcre, 0, read_00352 + read_00352_ptr, read_00352_len - read_00352_ptr, &read_00352_00000_match);
            if (rc > 0) {
                read_00352_ptr += read_00352_00000_match.match_end - read_00352_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00352_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00352);
        if (read_00352_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00353;
        unsigned int read_00353_len;
        unsigned int read_00353_ptr = 0;
        //**** delimited read
        static unsigned char read_00353_delim[] = 
            "\x0a";
        read_00353 = NULL;
        read_00353_len = 0;
        int read_00353_res = delimited_read(0, &read_00353, &read_00353_len, read_00353_delim, 1);
        if (read_00353_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00353_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00353_00000_match;
        pcre *read_00353_00000_pcre = init_regex(read_00353_00000_regex);
        if (read_00353_00000_pcre != NULL) {
            int rc = regex_match(read_00353_00000_pcre, 0, read_00353 + read_00353_ptr, read_00353_len - read_00353_ptr, &read_00353_00000_match);
            if (rc > 0) {
                read_00353_ptr += read_00353_00000_match.match_end - read_00353_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00353_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00353);
        if (read_00353_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00354;
        unsigned int read_00354_len;
        unsigned int read_00354_ptr = 0;
        //**** delimited read
        static unsigned char read_00354_delim[] = 
            "\x0a";
        read_00354 = NULL;
        read_00354_len = 0;
        int read_00354_res = delimited_read(0, &read_00354, &read_00354_len, read_00354_delim, 1);
        if (read_00354_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00354_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00354_00000_match;
        pcre *read_00354_00000_pcre = init_regex(read_00354_00000_regex);
        if (read_00354_00000_pcre != NULL) {
            int rc = regex_match(read_00354_00000_pcre, 0, read_00354 + read_00354_ptr, read_00354_len - read_00354_ptr, &read_00354_00000_match);
            if (rc > 0) {
                read_00354_ptr += read_00354_00000_match.match_end - read_00354_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00354_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00354);
        if (read_00354_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00355;
        unsigned int read_00355_len;
        unsigned int read_00355_ptr = 0;
        //**** delimited read
        static unsigned char read_00355_delim[] = 
            "\x0a";
        read_00355 = NULL;
        read_00355_len = 0;
        int read_00355_res = delimited_read(0, &read_00355, &read_00355_len, read_00355_delim, 1);
        if (read_00355_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00355_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00355_00000_match;
        pcre *read_00355_00000_pcre = init_regex(read_00355_00000_regex);
        if (read_00355_00000_pcre != NULL) {
            int rc = regex_match(read_00355_00000_pcre, 0, read_00355 + read_00355_ptr, read_00355_len - read_00355_ptr, &read_00355_00000_match);
            if (rc > 0) {
                read_00355_ptr += read_00355_00000_match.match_end - read_00355_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00355_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00355);
        if (read_00355_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00356;
        unsigned int read_00356_len;
        unsigned int read_00356_ptr = 0;
        //**** delimited read
        static unsigned char read_00356_delim[] = 
            "\x0a";
        read_00356 = NULL;
        read_00356_len = 0;
        int read_00356_res = delimited_read(0, &read_00356, &read_00356_len, read_00356_delim, 1);
        if (read_00356_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00356_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00356_00000_match;
        pcre *read_00356_00000_pcre = init_regex(read_00356_00000_regex);
        if (read_00356_00000_pcre != NULL) {
            int rc = regex_match(read_00356_00000_pcre, 0, read_00356 + read_00356_ptr, read_00356_len - read_00356_ptr, &read_00356_00000_match);
            if (rc > 0) {
                read_00356_ptr += read_00356_00000_match.match_end - read_00356_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00356_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00356);
        if (read_00356_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00357;
        unsigned int read_00357_len;
        unsigned int read_00357_ptr = 0;
        //**** delimited read
        static unsigned char read_00357_delim[] = 
            "\x0a";
        read_00357 = NULL;
        read_00357_len = 0;
        int read_00357_res = delimited_read(0, &read_00357, &read_00357_len, read_00357_delim, 1);
        if (read_00357_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00357_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00357_00000_match;
        pcre *read_00357_00000_pcre = init_regex(read_00357_00000_regex);
        if (read_00357_00000_pcre != NULL) {
            int rc = regex_match(read_00357_00000_pcre, 0, read_00357 + read_00357_ptr, read_00357_len - read_00357_ptr, &read_00357_00000_match);
            if (rc > 0) {
                read_00357_ptr += read_00357_00000_match.match_end - read_00357_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00357_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00357);
        if (read_00357_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00358;
        unsigned int read_00358_len;
        unsigned int read_00358_ptr = 0;
        //**** delimited read
        static unsigned char read_00358_delim[] = 
            "\x0a";
        read_00358 = NULL;
        read_00358_len = 0;
        int read_00358_res = delimited_read(0, &read_00358, &read_00358_len, read_00358_delim, 1);
        if (read_00358_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00358_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00358_00000_match;
        pcre *read_00358_00000_pcre = init_regex(read_00358_00000_regex);
        if (read_00358_00000_pcre != NULL) {
            int rc = regex_match(read_00358_00000_pcre, 0, read_00358 + read_00358_ptr, read_00358_len - read_00358_ptr, &read_00358_00000_match);
            if (rc > 0) {
                read_00358_ptr += read_00358_00000_match.match_end - read_00358_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00358_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00358);
        if (read_00358_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00359;
        unsigned int read_00359_len;
        unsigned int read_00359_ptr = 0;
        //**** delimited read
        static unsigned char read_00359_delim[] = 
            "\x0a";
        read_00359 = NULL;
        read_00359_len = 0;
        int read_00359_res = delimited_read(0, &read_00359, &read_00359_len, read_00359_delim, 1);
        if (read_00359_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00359_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00359_00000_match;
        pcre *read_00359_00000_pcre = init_regex(read_00359_00000_regex);
        if (read_00359_00000_pcre != NULL) {
            int rc = regex_match(read_00359_00000_pcre, 0, read_00359 + read_00359_ptr, read_00359_len - read_00359_ptr, &read_00359_00000_match);
            if (rc > 0) {
                read_00359_ptr += read_00359_00000_match.match_end - read_00359_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00359_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00359);
        if (read_00359_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00360;
        unsigned int read_00360_len;
        unsigned int read_00360_ptr = 0;
        //**** delimited read
        static unsigned char read_00360_delim[] = 
            "\x0a";
        read_00360 = NULL;
        read_00360_len = 0;
        int read_00360_res = delimited_read(0, &read_00360, &read_00360_len, read_00360_delim, 1);
        if (read_00360_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00360_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00360_00000_match;
        pcre *read_00360_00000_pcre = init_regex(read_00360_00000_regex);
        if (read_00360_00000_pcre != NULL) {
            int rc = regex_match(read_00360_00000_pcre, 0, read_00360 + read_00360_ptr, read_00360_len - read_00360_ptr, &read_00360_00000_match);
            if (rc > 0) {
                read_00360_ptr += read_00360_00000_match.match_end - read_00360_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00360_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00360);
        if (read_00360_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00361;
        unsigned int read_00361_len;
        unsigned int read_00361_ptr = 0;
        //**** delimited read
        static unsigned char read_00361_delim[] = 
            "\x0a";
        read_00361 = NULL;
        read_00361_len = 0;
        int read_00361_res = delimited_read(0, &read_00361, &read_00361_len, read_00361_delim, 1);
        if (read_00361_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00361_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00361_00000_match;
        pcre *read_00361_00000_pcre = init_regex(read_00361_00000_regex);
        if (read_00361_00000_pcre != NULL) {
            int rc = regex_match(read_00361_00000_pcre, 0, read_00361 + read_00361_ptr, read_00361_len - read_00361_ptr, &read_00361_00000_match);
            if (rc > 0) {
                read_00361_ptr += read_00361_00000_match.match_end - read_00361_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00361_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00361);
        if (read_00361_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00026_00000[] = 
            "\x3a";
        static unsigned int write_00026_00000_len = 1;
        unsigned char *write_00026 = NULL;
        unsigned int write_00026_len = 0;
        write_00026 = append_buf(write_00026, &write_00026_len, write_00026_00000, write_00026_00000_len);
        if (write_00026_len > 0) {
            transmit_all(1, write_00026, write_00026_len);
        }
        free(write_00026);
    } while (0);
    do {
        unsigned char *read_00362;
        unsigned int read_00362_len;
        unsigned int read_00362_ptr = 0;
        //**** delimited read
        static unsigned char read_00362_delim[] = 
            "\x0a";
        read_00362 = NULL;
        read_00362_len = 0;
        int read_00362_res = delimited_read(0, &read_00362, &read_00362_len, read_00362_delim, 1);
        if (read_00362_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00362_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00362_00000_match;
        pcre *read_00362_00000_pcre = init_regex(read_00362_00000_regex);
        if (read_00362_00000_pcre != NULL) {
            int rc = regex_match(read_00362_00000_pcre, 0, read_00362 + read_00362_ptr, read_00362_len - read_00362_ptr, &read_00362_00000_match);
            if (rc > 0) {
                read_00362_ptr += read_00362_00000_match.match_end - read_00362_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00362_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00362);
        if (read_00362_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00363;
        unsigned int read_00363_len;
        unsigned int read_00363_ptr = 0;
        //**** delimited read
        static unsigned char read_00363_delim[] = 
            "\x0a";
        read_00363 = NULL;
        read_00363_len = 0;
        int read_00363_res = delimited_read(0, &read_00363, &read_00363_len, read_00363_delim, 1);
        if (read_00363_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00363_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00363_00000_match;
        pcre *read_00363_00000_pcre = init_regex(read_00363_00000_regex);
        if (read_00363_00000_pcre != NULL) {
            int rc = regex_match(read_00363_00000_pcre, 0, read_00363 + read_00363_ptr, read_00363_len - read_00363_ptr, &read_00363_00000_match);
            if (rc > 0) {
                read_00363_ptr += read_00363_00000_match.match_end - read_00363_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00363_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00363);
        if (read_00363_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00364;
        unsigned int read_00364_len;
        unsigned int read_00364_ptr = 0;
        //**** delimited read
        static unsigned char read_00364_delim[] = 
            "\x0a";
        read_00364 = NULL;
        read_00364_len = 0;
        int read_00364_res = delimited_read(0, &read_00364, &read_00364_len, read_00364_delim, 1);
        if (read_00364_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00364_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00364_00000_match;
        pcre *read_00364_00000_pcre = init_regex(read_00364_00000_regex);
        if (read_00364_00000_pcre != NULL) {
            int rc = regex_match(read_00364_00000_pcre, 0, read_00364 + read_00364_ptr, read_00364_len - read_00364_ptr, &read_00364_00000_match);
            if (rc > 0) {
                read_00364_ptr += read_00364_00000_match.match_end - read_00364_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00364_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00364);
        if (read_00364_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00365;
        unsigned int read_00365_len;
        unsigned int read_00365_ptr = 0;
        //**** delimited read
        static unsigned char read_00365_delim[] = 
            "\x0a";
        read_00365 = NULL;
        read_00365_len = 0;
        int read_00365_res = delimited_read(0, &read_00365, &read_00365_len, read_00365_delim, 1);
        if (read_00365_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00365_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00365_00000_match;
        pcre *read_00365_00000_pcre = init_regex(read_00365_00000_regex);
        if (read_00365_00000_pcre != NULL) {
            int rc = regex_match(read_00365_00000_pcre, 0, read_00365 + read_00365_ptr, read_00365_len - read_00365_ptr, &read_00365_00000_match);
            if (rc > 0) {
                read_00365_ptr += read_00365_00000_match.match_end - read_00365_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00365_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00365);
        if (read_00365_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00366;
        unsigned int read_00366_len;
        unsigned int read_00366_ptr = 0;
        //**** delimited read
        static unsigned char read_00366_delim[] = 
            "\x0a";
        read_00366 = NULL;
        read_00366_len = 0;
        int read_00366_res = delimited_read(0, &read_00366, &read_00366_len, read_00366_delim, 1);
        if (read_00366_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00366_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00366_00000_match;
        pcre *read_00366_00000_pcre = init_regex(read_00366_00000_regex);
        if (read_00366_00000_pcre != NULL) {
            int rc = regex_match(read_00366_00000_pcre, 0, read_00366 + read_00366_ptr, read_00366_len - read_00366_ptr, &read_00366_00000_match);
            if (rc > 0) {
                read_00366_ptr += read_00366_00000_match.match_end - read_00366_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00366_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00366);
        if (read_00366_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00367;
        unsigned int read_00367_len;
        unsigned int read_00367_ptr = 0;
        //**** delimited read
        static unsigned char read_00367_delim[] = 
            "\x0a";
        read_00367 = NULL;
        read_00367_len = 0;
        int read_00367_res = delimited_read(0, &read_00367, &read_00367_len, read_00367_delim, 1);
        if (read_00367_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00367_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00367_00000_match;
        pcre *read_00367_00000_pcre = init_regex(read_00367_00000_regex);
        if (read_00367_00000_pcre != NULL) {
            int rc = regex_match(read_00367_00000_pcre, 0, read_00367 + read_00367_ptr, read_00367_len - read_00367_ptr, &read_00367_00000_match);
            if (rc > 0) {
                read_00367_ptr += read_00367_00000_match.match_end - read_00367_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00367_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00367);
        if (read_00367_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00368;
        unsigned int read_00368_len;
        unsigned int read_00368_ptr = 0;
        //**** delimited read
        static unsigned char read_00368_delim[] = 
            "\x0a";
        read_00368 = NULL;
        read_00368_len = 0;
        int read_00368_res = delimited_read(0, &read_00368, &read_00368_len, read_00368_delim, 1);
        if (read_00368_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00368_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00368_00000_match;
        pcre *read_00368_00000_pcre = init_regex(read_00368_00000_regex);
        if (read_00368_00000_pcre != NULL) {
            int rc = regex_match(read_00368_00000_pcre, 0, read_00368 + read_00368_ptr, read_00368_len - read_00368_ptr, &read_00368_00000_match);
            if (rc > 0) {
                read_00368_ptr += read_00368_00000_match.match_end - read_00368_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00368_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00368);
        if (read_00368_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00369;
        unsigned int read_00369_len;
        unsigned int read_00369_ptr = 0;
        //**** delimited read
        static unsigned char read_00369_delim[] = 
            "\x0a";
        read_00369 = NULL;
        read_00369_len = 0;
        int read_00369_res = delimited_read(0, &read_00369, &read_00369_len, read_00369_delim, 1);
        if (read_00369_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00369_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00369_00000_match;
        pcre *read_00369_00000_pcre = init_regex(read_00369_00000_regex);
        if (read_00369_00000_pcre != NULL) {
            int rc = regex_match(read_00369_00000_pcre, 0, read_00369 + read_00369_ptr, read_00369_len - read_00369_ptr, &read_00369_00000_match);
            if (rc > 0) {
                read_00369_ptr += read_00369_00000_match.match_end - read_00369_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00369_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00369);
        if (read_00369_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00370;
        unsigned int read_00370_len;
        unsigned int read_00370_ptr = 0;
        //**** delimited read
        static unsigned char read_00370_delim[] = 
            "\x0a";
        read_00370 = NULL;
        read_00370_len = 0;
        int read_00370_res = delimited_read(0, &read_00370, &read_00370_len, read_00370_delim, 1);
        if (read_00370_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00370_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00370_00000_match;
        pcre *read_00370_00000_pcre = init_regex(read_00370_00000_regex);
        if (read_00370_00000_pcre != NULL) {
            int rc = regex_match(read_00370_00000_pcre, 0, read_00370 + read_00370_ptr, read_00370_len - read_00370_ptr, &read_00370_00000_match);
            if (rc > 0) {
                read_00370_ptr += read_00370_00000_match.match_end - read_00370_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00370_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00370);
        if (read_00370_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00371;
        unsigned int read_00371_len;
        unsigned int read_00371_ptr = 0;
        //**** delimited read
        static unsigned char read_00371_delim[] = 
            "\x0a";
        read_00371 = NULL;
        read_00371_len = 0;
        int read_00371_res = delimited_read(0, &read_00371, &read_00371_len, read_00371_delim, 1);
        if (read_00371_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00371_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00371_00000_match;
        pcre *read_00371_00000_pcre = init_regex(read_00371_00000_regex);
        if (read_00371_00000_pcre != NULL) {
            int rc = regex_match(read_00371_00000_pcre, 0, read_00371 + read_00371_ptr, read_00371_len - read_00371_ptr, &read_00371_00000_match);
            if (rc > 0) {
                read_00371_ptr += read_00371_00000_match.match_end - read_00371_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00371_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00371);
        if (read_00371_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00372;
        unsigned int read_00372_len;
        unsigned int read_00372_ptr = 0;
        //**** delimited read
        static unsigned char read_00372_delim[] = 
            "\x0a";
        read_00372 = NULL;
        read_00372_len = 0;
        int read_00372_res = delimited_read(0, &read_00372, &read_00372_len, read_00372_delim, 1);
        if (read_00372_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00372_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00372_00000_match;
        pcre *read_00372_00000_pcre = init_regex(read_00372_00000_regex);
        if (read_00372_00000_pcre != NULL) {
            int rc = regex_match(read_00372_00000_pcre, 0, read_00372 + read_00372_ptr, read_00372_len - read_00372_ptr, &read_00372_00000_match);
            if (rc > 0) {
                read_00372_ptr += read_00372_00000_match.match_end - read_00372_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00372_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00372);
        if (read_00372_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00373;
        unsigned int read_00373_len;
        unsigned int read_00373_ptr = 0;
        //**** delimited read
        static unsigned char read_00373_delim[] = 
            "\x0a";
        read_00373 = NULL;
        read_00373_len = 0;
        int read_00373_res = delimited_read(0, &read_00373, &read_00373_len, read_00373_delim, 1);
        if (read_00373_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00373_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00373_00000_match;
        pcre *read_00373_00000_pcre = init_regex(read_00373_00000_regex);
        if (read_00373_00000_pcre != NULL) {
            int rc = regex_match(read_00373_00000_pcre, 0, read_00373 + read_00373_ptr, read_00373_len - read_00373_ptr, &read_00373_00000_match);
            if (rc > 0) {
                read_00373_ptr += read_00373_00000_match.match_end - read_00373_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00373_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00373);
        if (read_00373_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00027_00000[] = 
            "\x3a";
        static unsigned int write_00027_00000_len = 1;
        unsigned char *write_00027 = NULL;
        unsigned int write_00027_len = 0;
        write_00027 = append_buf(write_00027, &write_00027_len, write_00027_00000, write_00027_00000_len);
        if (write_00027_len > 0) {
            transmit_all(1, write_00027, write_00027_len);
        }
        free(write_00027);
    } while (0);
    do {
        unsigned char *read_00374;
        unsigned int read_00374_len;
        unsigned int read_00374_ptr = 0;
        //**** delimited read
        static unsigned char read_00374_delim[] = 
            "\x0a";
        read_00374 = NULL;
        read_00374_len = 0;
        int read_00374_res = delimited_read(0, &read_00374, &read_00374_len, read_00374_delim, 1);
        if (read_00374_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00374_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00374_00000_match;
        pcre *read_00374_00000_pcre = init_regex(read_00374_00000_regex);
        if (read_00374_00000_pcre != NULL) {
            int rc = regex_match(read_00374_00000_pcre, 0, read_00374 + read_00374_ptr, read_00374_len - read_00374_ptr, &read_00374_00000_match);
            if (rc > 0) {
                read_00374_ptr += read_00374_00000_match.match_end - read_00374_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00374_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00374);
        if (read_00374_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00375;
        unsigned int read_00375_len;
        unsigned int read_00375_ptr = 0;
        //**** delimited read
        static unsigned char read_00375_delim[] = 
            "\x0a";
        read_00375 = NULL;
        read_00375_len = 0;
        int read_00375_res = delimited_read(0, &read_00375, &read_00375_len, read_00375_delim, 1);
        if (read_00375_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00375_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00375_00000_match;
        pcre *read_00375_00000_pcre = init_regex(read_00375_00000_regex);
        if (read_00375_00000_pcre != NULL) {
            int rc = regex_match(read_00375_00000_pcre, 0, read_00375 + read_00375_ptr, read_00375_len - read_00375_ptr, &read_00375_00000_match);
            if (rc > 0) {
                read_00375_ptr += read_00375_00000_match.match_end - read_00375_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00375_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00375);
        if (read_00375_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00376;
        unsigned int read_00376_len;
        unsigned int read_00376_ptr = 0;
        //**** delimited read
        static unsigned char read_00376_delim[] = 
            "\x0a";
        read_00376 = NULL;
        read_00376_len = 0;
        int read_00376_res = delimited_read(0, &read_00376, &read_00376_len, read_00376_delim, 1);
        if (read_00376_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00376_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00376_00000_match;
        pcre *read_00376_00000_pcre = init_regex(read_00376_00000_regex);
        if (read_00376_00000_pcre != NULL) {
            int rc = regex_match(read_00376_00000_pcre, 0, read_00376 + read_00376_ptr, read_00376_len - read_00376_ptr, &read_00376_00000_match);
            if (rc > 0) {
                read_00376_ptr += read_00376_00000_match.match_end - read_00376_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00376_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00376);
        if (read_00376_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00377;
        unsigned int read_00377_len;
        unsigned int read_00377_ptr = 0;
        //**** delimited read
        static unsigned char read_00377_delim[] = 
            "\x0a";
        read_00377 = NULL;
        read_00377_len = 0;
        int read_00377_res = delimited_read(0, &read_00377, &read_00377_len, read_00377_delim, 1);
        if (read_00377_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00377_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00377_00000_match;
        pcre *read_00377_00000_pcre = init_regex(read_00377_00000_regex);
        if (read_00377_00000_pcre != NULL) {
            int rc = regex_match(read_00377_00000_pcre, 0, read_00377 + read_00377_ptr, read_00377_len - read_00377_ptr, &read_00377_00000_match);
            if (rc > 0) {
                read_00377_ptr += read_00377_00000_match.match_end - read_00377_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00377_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00377);
        if (read_00377_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00378;
        unsigned int read_00378_len;
        unsigned int read_00378_ptr = 0;
        //**** delimited read
        static unsigned char read_00378_delim[] = 
            "\x0a";
        read_00378 = NULL;
        read_00378_len = 0;
        int read_00378_res = delimited_read(0, &read_00378, &read_00378_len, read_00378_delim, 1);
        if (read_00378_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00378_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00378_00000_match;
        pcre *read_00378_00000_pcre = init_regex(read_00378_00000_regex);
        if (read_00378_00000_pcre != NULL) {
            int rc = regex_match(read_00378_00000_pcre, 0, read_00378 + read_00378_ptr, read_00378_len - read_00378_ptr, &read_00378_00000_match);
            if (rc > 0) {
                read_00378_ptr += read_00378_00000_match.match_end - read_00378_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00378_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00378);
        if (read_00378_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00379;
        unsigned int read_00379_len;
        unsigned int read_00379_ptr = 0;
        //**** delimited read
        static unsigned char read_00379_delim[] = 
            "\x0a";
        read_00379 = NULL;
        read_00379_len = 0;
        int read_00379_res = delimited_read(0, &read_00379, &read_00379_len, read_00379_delim, 1);
        if (read_00379_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00379_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00379_00000_match;
        pcre *read_00379_00000_pcre = init_regex(read_00379_00000_regex);
        if (read_00379_00000_pcre != NULL) {
            int rc = regex_match(read_00379_00000_pcre, 0, read_00379 + read_00379_ptr, read_00379_len - read_00379_ptr, &read_00379_00000_match);
            if (rc > 0) {
                read_00379_ptr += read_00379_00000_match.match_end - read_00379_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00379_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00379);
        if (read_00379_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00380;
        unsigned int read_00380_len;
        unsigned int read_00380_ptr = 0;
        //**** delimited read
        static unsigned char read_00380_delim[] = 
            "\x0a";
        read_00380 = NULL;
        read_00380_len = 0;
        int read_00380_res = delimited_read(0, &read_00380, &read_00380_len, read_00380_delim, 1);
        if (read_00380_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00380_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00380_00000_match;
        pcre *read_00380_00000_pcre = init_regex(read_00380_00000_regex);
        if (read_00380_00000_pcre != NULL) {
            int rc = regex_match(read_00380_00000_pcre, 0, read_00380 + read_00380_ptr, read_00380_len - read_00380_ptr, &read_00380_00000_match);
            if (rc > 0) {
                read_00380_ptr += read_00380_00000_match.match_end - read_00380_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00380_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00380);
        if (read_00380_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00381;
        unsigned int read_00381_len;
        unsigned int read_00381_ptr = 0;
        //**** delimited read
        static unsigned char read_00381_delim[] = 
            "\x0a";
        read_00381 = NULL;
        read_00381_len = 0;
        int read_00381_res = delimited_read(0, &read_00381, &read_00381_len, read_00381_delim, 1);
        if (read_00381_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00381_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00381_00000_match;
        pcre *read_00381_00000_pcre = init_regex(read_00381_00000_regex);
        if (read_00381_00000_pcre != NULL) {
            int rc = regex_match(read_00381_00000_pcre, 0, read_00381 + read_00381_ptr, read_00381_len - read_00381_ptr, &read_00381_00000_match);
            if (rc > 0) {
                read_00381_ptr += read_00381_00000_match.match_end - read_00381_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00381_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00381);
        if (read_00381_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00382;
        unsigned int read_00382_len;
        unsigned int read_00382_ptr = 0;
        //**** delimited read
        static unsigned char read_00382_delim[] = 
            "\x0a";
        read_00382 = NULL;
        read_00382_len = 0;
        int read_00382_res = delimited_read(0, &read_00382, &read_00382_len, read_00382_delim, 1);
        if (read_00382_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00382_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00382_00000_match;
        pcre *read_00382_00000_pcre = init_regex(read_00382_00000_regex);
        if (read_00382_00000_pcre != NULL) {
            int rc = regex_match(read_00382_00000_pcre, 0, read_00382 + read_00382_ptr, read_00382_len - read_00382_ptr, &read_00382_00000_match);
            if (rc > 0) {
                read_00382_ptr += read_00382_00000_match.match_end - read_00382_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00382_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00382);
        if (read_00382_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00383;
        unsigned int read_00383_len;
        unsigned int read_00383_ptr = 0;
        //**** delimited read
        static unsigned char read_00383_delim[] = 
            "\x0a";
        read_00383 = NULL;
        read_00383_len = 0;
        int read_00383_res = delimited_read(0, &read_00383, &read_00383_len, read_00383_delim, 1);
        if (read_00383_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00383_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00383_00000_match;
        pcre *read_00383_00000_pcre = init_regex(read_00383_00000_regex);
        if (read_00383_00000_pcre != NULL) {
            int rc = regex_match(read_00383_00000_pcre, 0, read_00383 + read_00383_ptr, read_00383_len - read_00383_ptr, &read_00383_00000_match);
            if (rc > 0) {
                read_00383_ptr += read_00383_00000_match.match_end - read_00383_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00383_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00383);
        if (read_00383_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00384;
        unsigned int read_00384_len;
        unsigned int read_00384_ptr = 0;
        //**** delimited read
        static unsigned char read_00384_delim[] = 
            "\x0a";
        read_00384 = NULL;
        read_00384_len = 0;
        int read_00384_res = delimited_read(0, &read_00384, &read_00384_len, read_00384_delim, 1);
        if (read_00384_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00384_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00384_00000_match;
        pcre *read_00384_00000_pcre = init_regex(read_00384_00000_regex);
        if (read_00384_00000_pcre != NULL) {
            int rc = regex_match(read_00384_00000_pcre, 0, read_00384 + read_00384_ptr, read_00384_len - read_00384_ptr, &read_00384_00000_match);
            if (rc > 0) {
                read_00384_ptr += read_00384_00000_match.match_end - read_00384_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00384_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00384);
        if (read_00384_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00385;
        unsigned int read_00385_len;
        unsigned int read_00385_ptr = 0;
        //**** delimited read
        static unsigned char read_00385_delim[] = 
            "\x0a";
        read_00385 = NULL;
        read_00385_len = 0;
        int read_00385_res = delimited_read(0, &read_00385, &read_00385_len, read_00385_delim, 1);
        if (read_00385_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00385_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00385_00000_match;
        pcre *read_00385_00000_pcre = init_regex(read_00385_00000_regex);
        if (read_00385_00000_pcre != NULL) {
            int rc = regex_match(read_00385_00000_pcre, 0, read_00385 + read_00385_ptr, read_00385_len - read_00385_ptr, &read_00385_00000_match);
            if (rc > 0) {
                read_00385_ptr += read_00385_00000_match.match_end - read_00385_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00385_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00385);
        if (read_00385_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00028_00000[] = 
            "\x3a";
        static unsigned int write_00028_00000_len = 1;
        unsigned char *write_00028 = NULL;
        unsigned int write_00028_len = 0;
        write_00028 = append_buf(write_00028, &write_00028_len, write_00028_00000, write_00028_00000_len);
        if (write_00028_len > 0) {
            transmit_all(1, write_00028, write_00028_len);
        }
        free(write_00028);
    } while (0);
    do {
        unsigned char *read_00386;
        unsigned int read_00386_len;
        unsigned int read_00386_ptr = 0;
        //**** delimited read
        static unsigned char read_00386_delim[] = 
            "\x0a";
        read_00386 = NULL;
        read_00386_len = 0;
        int read_00386_res = delimited_read(0, &read_00386, &read_00386_len, read_00386_delim, 1);
        if (read_00386_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00386_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00386_00000_match;
        pcre *read_00386_00000_pcre = init_regex(read_00386_00000_regex);
        if (read_00386_00000_pcre != NULL) {
            int rc = regex_match(read_00386_00000_pcre, 0, read_00386 + read_00386_ptr, read_00386_len - read_00386_ptr, &read_00386_00000_match);
            if (rc > 0) {
                read_00386_ptr += read_00386_00000_match.match_end - read_00386_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00386_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00386);
        if (read_00386_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00387;
        unsigned int read_00387_len;
        unsigned int read_00387_ptr = 0;
        //**** delimited read
        static unsigned char read_00387_delim[] = 
            "\x0a";
        read_00387 = NULL;
        read_00387_len = 0;
        int read_00387_res = delimited_read(0, &read_00387, &read_00387_len, read_00387_delim, 1);
        if (read_00387_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00387_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00387_00000_match;
        pcre *read_00387_00000_pcre = init_regex(read_00387_00000_regex);
        if (read_00387_00000_pcre != NULL) {
            int rc = regex_match(read_00387_00000_pcre, 0, read_00387 + read_00387_ptr, read_00387_len - read_00387_ptr, &read_00387_00000_match);
            if (rc > 0) {
                read_00387_ptr += read_00387_00000_match.match_end - read_00387_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00387_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00387);
        if (read_00387_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00388;
        unsigned int read_00388_len;
        unsigned int read_00388_ptr = 0;
        //**** delimited read
        static unsigned char read_00388_delim[] = 
            "\x0a";
        read_00388 = NULL;
        read_00388_len = 0;
        int read_00388_res = delimited_read(0, &read_00388, &read_00388_len, read_00388_delim, 1);
        if (read_00388_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00388_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00388_00000_match;
        pcre *read_00388_00000_pcre = init_regex(read_00388_00000_regex);
        if (read_00388_00000_pcre != NULL) {
            int rc = regex_match(read_00388_00000_pcre, 0, read_00388 + read_00388_ptr, read_00388_len - read_00388_ptr, &read_00388_00000_match);
            if (rc > 0) {
                read_00388_ptr += read_00388_00000_match.match_end - read_00388_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00388_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00388);
        if (read_00388_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00389;
        unsigned int read_00389_len;
        unsigned int read_00389_ptr = 0;
        //**** delimited read
        static unsigned char read_00389_delim[] = 
            "\x0a";
        read_00389 = NULL;
        read_00389_len = 0;
        int read_00389_res = delimited_read(0, &read_00389, &read_00389_len, read_00389_delim, 1);
        if (read_00389_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00389_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00389_00000_match;
        pcre *read_00389_00000_pcre = init_regex(read_00389_00000_regex);
        if (read_00389_00000_pcre != NULL) {
            int rc = regex_match(read_00389_00000_pcre, 0, read_00389 + read_00389_ptr, read_00389_len - read_00389_ptr, &read_00389_00000_match);
            if (rc > 0) {
                read_00389_ptr += read_00389_00000_match.match_end - read_00389_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00389_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00389);
        if (read_00389_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00390;
        unsigned int read_00390_len;
        unsigned int read_00390_ptr = 0;
        //**** delimited read
        static unsigned char read_00390_delim[] = 
            "\x0a";
        read_00390 = NULL;
        read_00390_len = 0;
        int read_00390_res = delimited_read(0, &read_00390, &read_00390_len, read_00390_delim, 1);
        if (read_00390_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00390_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00390_00000_match;
        pcre *read_00390_00000_pcre = init_regex(read_00390_00000_regex);
        if (read_00390_00000_pcre != NULL) {
            int rc = regex_match(read_00390_00000_pcre, 0, read_00390 + read_00390_ptr, read_00390_len - read_00390_ptr, &read_00390_00000_match);
            if (rc > 0) {
                read_00390_ptr += read_00390_00000_match.match_end - read_00390_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00390_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00390);
        if (read_00390_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00391;
        unsigned int read_00391_len;
        unsigned int read_00391_ptr = 0;
        //**** delimited read
        static unsigned char read_00391_delim[] = 
            "\x0a";
        read_00391 = NULL;
        read_00391_len = 0;
        int read_00391_res = delimited_read(0, &read_00391, &read_00391_len, read_00391_delim, 1);
        if (read_00391_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00391_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00391_00000_match;
        pcre *read_00391_00000_pcre = init_regex(read_00391_00000_regex);
        if (read_00391_00000_pcre != NULL) {
            int rc = regex_match(read_00391_00000_pcre, 0, read_00391 + read_00391_ptr, read_00391_len - read_00391_ptr, &read_00391_00000_match);
            if (rc > 0) {
                read_00391_ptr += read_00391_00000_match.match_end - read_00391_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00391_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00391);
        if (read_00391_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00392;
        unsigned int read_00392_len;
        unsigned int read_00392_ptr = 0;
        //**** delimited read
        static unsigned char read_00392_delim[] = 
            "\x0a";
        read_00392 = NULL;
        read_00392_len = 0;
        int read_00392_res = delimited_read(0, &read_00392, &read_00392_len, read_00392_delim, 1);
        if (read_00392_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00392_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00392_00000_match;
        pcre *read_00392_00000_pcre = init_regex(read_00392_00000_regex);
        if (read_00392_00000_pcre != NULL) {
            int rc = regex_match(read_00392_00000_pcre, 0, read_00392 + read_00392_ptr, read_00392_len - read_00392_ptr, &read_00392_00000_match);
            if (rc > 0) {
                read_00392_ptr += read_00392_00000_match.match_end - read_00392_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00392_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00392);
        if (read_00392_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00393;
        unsigned int read_00393_len;
        unsigned int read_00393_ptr = 0;
        //**** delimited read
        static unsigned char read_00393_delim[] = 
            "\x0a";
        read_00393 = NULL;
        read_00393_len = 0;
        int read_00393_res = delimited_read(0, &read_00393, &read_00393_len, read_00393_delim, 1);
        if (read_00393_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00393_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00393_00000_match;
        pcre *read_00393_00000_pcre = init_regex(read_00393_00000_regex);
        if (read_00393_00000_pcre != NULL) {
            int rc = regex_match(read_00393_00000_pcre, 0, read_00393 + read_00393_ptr, read_00393_len - read_00393_ptr, &read_00393_00000_match);
            if (rc > 0) {
                read_00393_ptr += read_00393_00000_match.match_end - read_00393_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00393_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00393);
        if (read_00393_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00394;
        unsigned int read_00394_len;
        unsigned int read_00394_ptr = 0;
        //**** delimited read
        static unsigned char read_00394_delim[] = 
            "\x0a";
        read_00394 = NULL;
        read_00394_len = 0;
        int read_00394_res = delimited_read(0, &read_00394, &read_00394_len, read_00394_delim, 1);
        if (read_00394_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00394_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00394_00000_match;
        pcre *read_00394_00000_pcre = init_regex(read_00394_00000_regex);
        if (read_00394_00000_pcre != NULL) {
            int rc = regex_match(read_00394_00000_pcre, 0, read_00394 + read_00394_ptr, read_00394_len - read_00394_ptr, &read_00394_00000_match);
            if (rc > 0) {
                read_00394_ptr += read_00394_00000_match.match_end - read_00394_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00394_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00394);
        if (read_00394_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00395;
        unsigned int read_00395_len;
        unsigned int read_00395_ptr = 0;
        //**** delimited read
        static unsigned char read_00395_delim[] = 
            "\x0a";
        read_00395 = NULL;
        read_00395_len = 0;
        int read_00395_res = delimited_read(0, &read_00395, &read_00395_len, read_00395_delim, 1);
        if (read_00395_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00395_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00395_00000_match;
        pcre *read_00395_00000_pcre = init_regex(read_00395_00000_regex);
        if (read_00395_00000_pcre != NULL) {
            int rc = regex_match(read_00395_00000_pcre, 0, read_00395 + read_00395_ptr, read_00395_len - read_00395_ptr, &read_00395_00000_match);
            if (rc > 0) {
                read_00395_ptr += read_00395_00000_match.match_end - read_00395_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00395_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00395);
        if (read_00395_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00396;
        unsigned int read_00396_len;
        unsigned int read_00396_ptr = 0;
        //**** delimited read
        static unsigned char read_00396_delim[] = 
            "\x0a";
        read_00396 = NULL;
        read_00396_len = 0;
        int read_00396_res = delimited_read(0, &read_00396, &read_00396_len, read_00396_delim, 1);
        if (read_00396_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00396_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00396_00000_match;
        pcre *read_00396_00000_pcre = init_regex(read_00396_00000_regex);
        if (read_00396_00000_pcre != NULL) {
            int rc = regex_match(read_00396_00000_pcre, 0, read_00396 + read_00396_ptr, read_00396_len - read_00396_ptr, &read_00396_00000_match);
            if (rc > 0) {
                read_00396_ptr += read_00396_00000_match.match_end - read_00396_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00396_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00396);
        if (read_00396_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00397;
        unsigned int read_00397_len;
        unsigned int read_00397_ptr = 0;
        //**** delimited read
        static unsigned char read_00397_delim[] = 
            "\x0a";
        read_00397 = NULL;
        read_00397_len = 0;
        int read_00397_res = delimited_read(0, &read_00397, &read_00397_len, read_00397_delim, 1);
        if (read_00397_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00397_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00397_00000_match;
        pcre *read_00397_00000_pcre = init_regex(read_00397_00000_regex);
        if (read_00397_00000_pcre != NULL) {
            int rc = regex_match(read_00397_00000_pcre, 0, read_00397 + read_00397_ptr, read_00397_len - read_00397_ptr, &read_00397_00000_match);
            if (rc > 0) {
                read_00397_ptr += read_00397_00000_match.match_end - read_00397_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00397_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00397);
        if (read_00397_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00029_00000[] = 
            "\x3a";
        static unsigned int write_00029_00000_len = 1;
        unsigned char *write_00029 = NULL;
        unsigned int write_00029_len = 0;
        write_00029 = append_buf(write_00029, &write_00029_len, write_00029_00000, write_00029_00000_len);
        if (write_00029_len > 0) {
            transmit_all(1, write_00029, write_00029_len);
        }
        free(write_00029);
    } while (0);
    do {
        unsigned char *read_00398;
        unsigned int read_00398_len;
        unsigned int read_00398_ptr = 0;
        //**** delimited read
        static unsigned char read_00398_delim[] = 
            "\x0a";
        read_00398 = NULL;
        read_00398_len = 0;
        int read_00398_res = delimited_read(0, &read_00398, &read_00398_len, read_00398_delim, 1);
        if (read_00398_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00398_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00398_00000_match;
        pcre *read_00398_00000_pcre = init_regex(read_00398_00000_regex);
        if (read_00398_00000_pcre != NULL) {
            int rc = regex_match(read_00398_00000_pcre, 0, read_00398 + read_00398_ptr, read_00398_len - read_00398_ptr, &read_00398_00000_match);
            if (rc > 0) {
                read_00398_ptr += read_00398_00000_match.match_end - read_00398_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00398_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00398);
        if (read_00398_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00399;
        unsigned int read_00399_len;
        unsigned int read_00399_ptr = 0;
        //**** delimited read
        static unsigned char read_00399_delim[] = 
            "\x0a";
        read_00399 = NULL;
        read_00399_len = 0;
        int read_00399_res = delimited_read(0, &read_00399, &read_00399_len, read_00399_delim, 1);
        if (read_00399_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00399_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00399_00000_match;
        pcre *read_00399_00000_pcre = init_regex(read_00399_00000_regex);
        if (read_00399_00000_pcre != NULL) {
            int rc = regex_match(read_00399_00000_pcre, 0, read_00399 + read_00399_ptr, read_00399_len - read_00399_ptr, &read_00399_00000_match);
            if (rc > 0) {
                read_00399_ptr += read_00399_00000_match.match_end - read_00399_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00399_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00399);
        if (read_00399_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00400;
        unsigned int read_00400_len;
        unsigned int read_00400_ptr = 0;
        //**** delimited read
        static unsigned char read_00400_delim[] = 
            "\x0a";
        read_00400 = NULL;
        read_00400_len = 0;
        int read_00400_res = delimited_read(0, &read_00400, &read_00400_len, read_00400_delim, 1);
        if (read_00400_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00400_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00400_00000_match;
        pcre *read_00400_00000_pcre = init_regex(read_00400_00000_regex);
        if (read_00400_00000_pcre != NULL) {
            int rc = regex_match(read_00400_00000_pcre, 0, read_00400 + read_00400_ptr, read_00400_len - read_00400_ptr, &read_00400_00000_match);
            if (rc > 0) {
                read_00400_ptr += read_00400_00000_match.match_end - read_00400_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00400_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00400);
        if (read_00400_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00401;
        unsigned int read_00401_len;
        unsigned int read_00401_ptr = 0;
        //**** delimited read
        static unsigned char read_00401_delim[] = 
            "\x0a";
        read_00401 = NULL;
        read_00401_len = 0;
        int read_00401_res = delimited_read(0, &read_00401, &read_00401_len, read_00401_delim, 1);
        if (read_00401_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00401_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00401_00000_match;
        pcre *read_00401_00000_pcre = init_regex(read_00401_00000_regex);
        if (read_00401_00000_pcre != NULL) {
            int rc = regex_match(read_00401_00000_pcre, 0, read_00401 + read_00401_ptr, read_00401_len - read_00401_ptr, &read_00401_00000_match);
            if (rc > 0) {
                read_00401_ptr += read_00401_00000_match.match_end - read_00401_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00401_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00401);
        if (read_00401_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00402;
        unsigned int read_00402_len;
        unsigned int read_00402_ptr = 0;
        //**** delimited read
        static unsigned char read_00402_delim[] = 
            "\x0a";
        read_00402 = NULL;
        read_00402_len = 0;
        int read_00402_res = delimited_read(0, &read_00402, &read_00402_len, read_00402_delim, 1);
        if (read_00402_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00402_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00402_00000_match;
        pcre *read_00402_00000_pcre = init_regex(read_00402_00000_regex);
        if (read_00402_00000_pcre != NULL) {
            int rc = regex_match(read_00402_00000_pcre, 0, read_00402 + read_00402_ptr, read_00402_len - read_00402_ptr, &read_00402_00000_match);
            if (rc > 0) {
                read_00402_ptr += read_00402_00000_match.match_end - read_00402_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00402_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00402);
        if (read_00402_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00403;
        unsigned int read_00403_len;
        unsigned int read_00403_ptr = 0;
        //**** delimited read
        static unsigned char read_00403_delim[] = 
            "\x0a";
        read_00403 = NULL;
        read_00403_len = 0;
        int read_00403_res = delimited_read(0, &read_00403, &read_00403_len, read_00403_delim, 1);
        if (read_00403_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00403_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00403_00000_match;
        pcre *read_00403_00000_pcre = init_regex(read_00403_00000_regex);
        if (read_00403_00000_pcre != NULL) {
            int rc = regex_match(read_00403_00000_pcre, 0, read_00403 + read_00403_ptr, read_00403_len - read_00403_ptr, &read_00403_00000_match);
            if (rc > 0) {
                read_00403_ptr += read_00403_00000_match.match_end - read_00403_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00403_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00403);
        if (read_00403_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00404;
        unsigned int read_00404_len;
        unsigned int read_00404_ptr = 0;
        //**** delimited read
        static unsigned char read_00404_delim[] = 
            "\x0a";
        read_00404 = NULL;
        read_00404_len = 0;
        int read_00404_res = delimited_read(0, &read_00404, &read_00404_len, read_00404_delim, 1);
        if (read_00404_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00404_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00404_00000_match;
        pcre *read_00404_00000_pcre = init_regex(read_00404_00000_regex);
        if (read_00404_00000_pcre != NULL) {
            int rc = regex_match(read_00404_00000_pcre, 0, read_00404 + read_00404_ptr, read_00404_len - read_00404_ptr, &read_00404_00000_match);
            if (rc > 0) {
                read_00404_ptr += read_00404_00000_match.match_end - read_00404_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00404_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00404);
        if (read_00404_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00405;
        unsigned int read_00405_len;
        unsigned int read_00405_ptr = 0;
        //**** delimited read
        static unsigned char read_00405_delim[] = 
            "\x0a";
        read_00405 = NULL;
        read_00405_len = 0;
        int read_00405_res = delimited_read(0, &read_00405, &read_00405_len, read_00405_delim, 1);
        if (read_00405_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00405_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00405_00000_match;
        pcre *read_00405_00000_pcre = init_regex(read_00405_00000_regex);
        if (read_00405_00000_pcre != NULL) {
            int rc = regex_match(read_00405_00000_pcre, 0, read_00405 + read_00405_ptr, read_00405_len - read_00405_ptr, &read_00405_00000_match);
            if (rc > 0) {
                read_00405_ptr += read_00405_00000_match.match_end - read_00405_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00405_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00405);
        if (read_00405_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00406;
        unsigned int read_00406_len;
        unsigned int read_00406_ptr = 0;
        //**** delimited read
        static unsigned char read_00406_delim[] = 
            "\x0a";
        read_00406 = NULL;
        read_00406_len = 0;
        int read_00406_res = delimited_read(0, &read_00406, &read_00406_len, read_00406_delim, 1);
        if (read_00406_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00406_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00406_00000_match;
        pcre *read_00406_00000_pcre = init_regex(read_00406_00000_regex);
        if (read_00406_00000_pcre != NULL) {
            int rc = regex_match(read_00406_00000_pcre, 0, read_00406 + read_00406_ptr, read_00406_len - read_00406_ptr, &read_00406_00000_match);
            if (rc > 0) {
                read_00406_ptr += read_00406_00000_match.match_end - read_00406_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00406_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00406);
        if (read_00406_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00407;
        unsigned int read_00407_len;
        unsigned int read_00407_ptr = 0;
        //**** delimited read
        static unsigned char read_00407_delim[] = 
            "\x0a";
        read_00407 = NULL;
        read_00407_len = 0;
        int read_00407_res = delimited_read(0, &read_00407, &read_00407_len, read_00407_delim, 1);
        if (read_00407_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00407_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00407_00000_match;
        pcre *read_00407_00000_pcre = init_regex(read_00407_00000_regex);
        if (read_00407_00000_pcre != NULL) {
            int rc = regex_match(read_00407_00000_pcre, 0, read_00407 + read_00407_ptr, read_00407_len - read_00407_ptr, &read_00407_00000_match);
            if (rc > 0) {
                read_00407_ptr += read_00407_00000_match.match_end - read_00407_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00407_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00407);
        if (read_00407_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00408;
        unsigned int read_00408_len;
        unsigned int read_00408_ptr = 0;
        //**** delimited read
        static unsigned char read_00408_delim[] = 
            "\x0a";
        read_00408 = NULL;
        read_00408_len = 0;
        int read_00408_res = delimited_read(0, &read_00408, &read_00408_len, read_00408_delim, 1);
        if (read_00408_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00408_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00408_00000_match;
        pcre *read_00408_00000_pcre = init_regex(read_00408_00000_regex);
        if (read_00408_00000_pcre != NULL) {
            int rc = regex_match(read_00408_00000_pcre, 0, read_00408 + read_00408_ptr, read_00408_len - read_00408_ptr, &read_00408_00000_match);
            if (rc > 0) {
                read_00408_ptr += read_00408_00000_match.match_end - read_00408_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00408_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00408);
        if (read_00408_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00409;
        unsigned int read_00409_len;
        unsigned int read_00409_ptr = 0;
        //**** delimited read
        static unsigned char read_00409_delim[] = 
            "\x0a";
        read_00409 = NULL;
        read_00409_len = 0;
        int read_00409_res = delimited_read(0, &read_00409, &read_00409_len, read_00409_delim, 1);
        if (read_00409_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00409_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00409_00000_match;
        pcre *read_00409_00000_pcre = init_regex(read_00409_00000_regex);
        if (read_00409_00000_pcre != NULL) {
            int rc = regex_match(read_00409_00000_pcre, 0, read_00409 + read_00409_ptr, read_00409_len - read_00409_ptr, &read_00409_00000_match);
            if (rc > 0) {
                read_00409_ptr += read_00409_00000_match.match_end - read_00409_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00409_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00409);
        if (read_00409_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00030_00000[] = 
            "\x3a";
        static unsigned int write_00030_00000_len = 1;
        unsigned char *write_00030 = NULL;
        unsigned int write_00030_len = 0;
        write_00030 = append_buf(write_00030, &write_00030_len, write_00030_00000, write_00030_00000_len);
        if (write_00030_len > 0) {
            transmit_all(1, write_00030, write_00030_len);
        }
        free(write_00030);
    } while (0);
    do {
        unsigned char *read_00410;
        unsigned int read_00410_len;
        unsigned int read_00410_ptr = 0;
        //**** delimited read
        static unsigned char read_00410_delim[] = 
            "\x0a";
        read_00410 = NULL;
        read_00410_len = 0;
        int read_00410_res = delimited_read(0, &read_00410, &read_00410_len, read_00410_delim, 1);
        if (read_00410_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00410_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00410_00000_match;
        pcre *read_00410_00000_pcre = init_regex(read_00410_00000_regex);
        if (read_00410_00000_pcre != NULL) {
            int rc = regex_match(read_00410_00000_pcre, 0, read_00410 + read_00410_ptr, read_00410_len - read_00410_ptr, &read_00410_00000_match);
            if (rc > 0) {
                read_00410_ptr += read_00410_00000_match.match_end - read_00410_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00410_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00410);
        if (read_00410_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00411;
        unsigned int read_00411_len;
        unsigned int read_00411_ptr = 0;
        //**** delimited read
        static unsigned char read_00411_delim[] = 
            "\x0a";
        read_00411 = NULL;
        read_00411_len = 0;
        int read_00411_res = delimited_read(0, &read_00411, &read_00411_len, read_00411_delim, 1);
        if (read_00411_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00411_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00411_00000_match;
        pcre *read_00411_00000_pcre = init_regex(read_00411_00000_regex);
        if (read_00411_00000_pcre != NULL) {
            int rc = regex_match(read_00411_00000_pcre, 0, read_00411 + read_00411_ptr, read_00411_len - read_00411_ptr, &read_00411_00000_match);
            if (rc > 0) {
                read_00411_ptr += read_00411_00000_match.match_end - read_00411_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00411_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00411);
        if (read_00411_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00412;
        unsigned int read_00412_len;
        unsigned int read_00412_ptr = 0;
        //**** delimited read
        static unsigned char read_00412_delim[] = 
            "\x0a";
        read_00412 = NULL;
        read_00412_len = 0;
        int read_00412_res = delimited_read(0, &read_00412, &read_00412_len, read_00412_delim, 1);
        if (read_00412_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00412_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00412_00000_match;
        pcre *read_00412_00000_pcre = init_regex(read_00412_00000_regex);
        if (read_00412_00000_pcre != NULL) {
            int rc = regex_match(read_00412_00000_pcre, 0, read_00412 + read_00412_ptr, read_00412_len - read_00412_ptr, &read_00412_00000_match);
            if (rc > 0) {
                read_00412_ptr += read_00412_00000_match.match_end - read_00412_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00412_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00412);
        if (read_00412_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00413;
        unsigned int read_00413_len;
        unsigned int read_00413_ptr = 0;
        //**** delimited read
        static unsigned char read_00413_delim[] = 
            "\x0a";
        read_00413 = NULL;
        read_00413_len = 0;
        int read_00413_res = delimited_read(0, &read_00413, &read_00413_len, read_00413_delim, 1);
        if (read_00413_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00413_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00413_00000_match;
        pcre *read_00413_00000_pcre = init_regex(read_00413_00000_regex);
        if (read_00413_00000_pcre != NULL) {
            int rc = regex_match(read_00413_00000_pcre, 0, read_00413 + read_00413_ptr, read_00413_len - read_00413_ptr, &read_00413_00000_match);
            if (rc > 0) {
                read_00413_ptr += read_00413_00000_match.match_end - read_00413_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00413_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00413);
        if (read_00413_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00414;
        unsigned int read_00414_len;
        unsigned int read_00414_ptr = 0;
        //**** delimited read
        static unsigned char read_00414_delim[] = 
            "\x0a";
        read_00414 = NULL;
        read_00414_len = 0;
        int read_00414_res = delimited_read(0, &read_00414, &read_00414_len, read_00414_delim, 1);
        if (read_00414_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00414_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00414_00000_match;
        pcre *read_00414_00000_pcre = init_regex(read_00414_00000_regex);
        if (read_00414_00000_pcre != NULL) {
            int rc = regex_match(read_00414_00000_pcre, 0, read_00414 + read_00414_ptr, read_00414_len - read_00414_ptr, &read_00414_00000_match);
            if (rc > 0) {
                read_00414_ptr += read_00414_00000_match.match_end - read_00414_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00414_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00414);
        if (read_00414_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00415;
        unsigned int read_00415_len;
        unsigned int read_00415_ptr = 0;
        //**** delimited read
        static unsigned char read_00415_delim[] = 
            "\x0a";
        read_00415 = NULL;
        read_00415_len = 0;
        int read_00415_res = delimited_read(0, &read_00415, &read_00415_len, read_00415_delim, 1);
        if (read_00415_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00415_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00415_00000_match;
        pcre *read_00415_00000_pcre = init_regex(read_00415_00000_regex);
        if (read_00415_00000_pcre != NULL) {
            int rc = regex_match(read_00415_00000_pcre, 0, read_00415 + read_00415_ptr, read_00415_len - read_00415_ptr, &read_00415_00000_match);
            if (rc > 0) {
                read_00415_ptr += read_00415_00000_match.match_end - read_00415_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00415_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00415);
        if (read_00415_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00416;
        unsigned int read_00416_len;
        unsigned int read_00416_ptr = 0;
        //**** delimited read
        static unsigned char read_00416_delim[] = 
            "\x0a";
        read_00416 = NULL;
        read_00416_len = 0;
        int read_00416_res = delimited_read(0, &read_00416, &read_00416_len, read_00416_delim, 1);
        if (read_00416_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00416_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00416_00000_match;
        pcre *read_00416_00000_pcre = init_regex(read_00416_00000_regex);
        if (read_00416_00000_pcre != NULL) {
            int rc = regex_match(read_00416_00000_pcre, 0, read_00416 + read_00416_ptr, read_00416_len - read_00416_ptr, &read_00416_00000_match);
            if (rc > 0) {
                read_00416_ptr += read_00416_00000_match.match_end - read_00416_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00416_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00416);
        if (read_00416_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00417;
        unsigned int read_00417_len;
        unsigned int read_00417_ptr = 0;
        //**** delimited read
        static unsigned char read_00417_delim[] = 
            "\x0a";
        read_00417 = NULL;
        read_00417_len = 0;
        int read_00417_res = delimited_read(0, &read_00417, &read_00417_len, read_00417_delim, 1);
        if (read_00417_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00417_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00417_00000_match;
        pcre *read_00417_00000_pcre = init_regex(read_00417_00000_regex);
        if (read_00417_00000_pcre != NULL) {
            int rc = regex_match(read_00417_00000_pcre, 0, read_00417 + read_00417_ptr, read_00417_len - read_00417_ptr, &read_00417_00000_match);
            if (rc > 0) {
                read_00417_ptr += read_00417_00000_match.match_end - read_00417_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00417_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00417);
        if (read_00417_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00418;
        unsigned int read_00418_len;
        unsigned int read_00418_ptr = 0;
        //**** delimited read
        static unsigned char read_00418_delim[] = 
            "\x0a";
        read_00418 = NULL;
        read_00418_len = 0;
        int read_00418_res = delimited_read(0, &read_00418, &read_00418_len, read_00418_delim, 1);
        if (read_00418_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00418_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00418_00000_match;
        pcre *read_00418_00000_pcre = init_regex(read_00418_00000_regex);
        if (read_00418_00000_pcre != NULL) {
            int rc = regex_match(read_00418_00000_pcre, 0, read_00418 + read_00418_ptr, read_00418_len - read_00418_ptr, &read_00418_00000_match);
            if (rc > 0) {
                read_00418_ptr += read_00418_00000_match.match_end - read_00418_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00418_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00418);
        if (read_00418_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00419;
        unsigned int read_00419_len;
        unsigned int read_00419_ptr = 0;
        //**** delimited read
        static unsigned char read_00419_delim[] = 
            "\x0a";
        read_00419 = NULL;
        read_00419_len = 0;
        int read_00419_res = delimited_read(0, &read_00419, &read_00419_len, read_00419_delim, 1);
        if (read_00419_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00419_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00419_00000_match;
        pcre *read_00419_00000_pcre = init_regex(read_00419_00000_regex);
        if (read_00419_00000_pcre != NULL) {
            int rc = regex_match(read_00419_00000_pcre, 0, read_00419 + read_00419_ptr, read_00419_len - read_00419_ptr, &read_00419_00000_match);
            if (rc > 0) {
                read_00419_ptr += read_00419_00000_match.match_end - read_00419_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00419_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00419);
        if (read_00419_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00420;
        unsigned int read_00420_len;
        unsigned int read_00420_ptr = 0;
        //**** delimited read
        static unsigned char read_00420_delim[] = 
            "\x0a";
        read_00420 = NULL;
        read_00420_len = 0;
        int read_00420_res = delimited_read(0, &read_00420, &read_00420_len, read_00420_delim, 1);
        if (read_00420_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00420_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00420_00000_match;
        pcre *read_00420_00000_pcre = init_regex(read_00420_00000_regex);
        if (read_00420_00000_pcre != NULL) {
            int rc = regex_match(read_00420_00000_pcre, 0, read_00420 + read_00420_ptr, read_00420_len - read_00420_ptr, &read_00420_00000_match);
            if (rc > 0) {
                read_00420_ptr += read_00420_00000_match.match_end - read_00420_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00420_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00420);
        if (read_00420_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00421;
        unsigned int read_00421_len;
        unsigned int read_00421_ptr = 0;
        //**** delimited read
        static unsigned char read_00421_delim[] = 
            "\x0a";
        read_00421 = NULL;
        read_00421_len = 0;
        int read_00421_res = delimited_read(0, &read_00421, &read_00421_len, read_00421_delim, 1);
        if (read_00421_res) {} //silence unused variable warning
        /* read match pcre:
Incorrect: .*

*/
        static char read_00421_00000_regex[] = 
            "\x49\x6e\x63\x6f\x72\x72\x65\x63\x74\x3a\x20\x2e\x2a\x0a";
        static match_result read_00421_00000_match;
        pcre *read_00421_00000_pcre = init_regex(read_00421_00000_regex);
        if (read_00421_00000_pcre != NULL) {
            int rc = regex_match(read_00421_00000_pcre, 0, read_00421 + read_00421_ptr, read_00421_len - read_00421_ptr, &read_00421_00000_match);
            if (rc > 0) {
                read_00421_ptr += read_00421_00000_match.match_end - read_00421_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00421_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00421);
        if (read_00421_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00031_00000[] = 
            "\x3a";
        static unsigned int write_00031_00000_len = 1;
        unsigned char *write_00031 = NULL;
        unsigned int write_00031_len = 0;
        write_00031 = append_buf(write_00031, &write_00031_len, write_00031_00000, write_00031_00000_len);
        if (write_00031_len > 0) {
            transmit_all(1, write_00031, write_00031_len);
        }
        free(write_00031);
    } while (0);
    do {
        unsigned char *read_00422;
        unsigned int read_00422_len;
        unsigned int read_00422_ptr = 0;
        //**** delimited read
        static unsigned char read_00422_delim[] = 
            "\x0a";
        read_00422 = NULL;
        read_00422_len = 0;
        int read_00422_res = delimited_read(0, &read_00422, &read_00422_len, read_00422_delim, 1);
        if (read_00422_res) {} //silence unused variable warning
        /* read match pcre:
           --------

*/
        static char read_00422_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x0a";
        static match_result read_00422_00000_match;
        pcre *read_00422_00000_pcre = init_regex(read_00422_00000_regex);
        if (read_00422_00000_pcre != NULL) {
            int rc = regex_match(read_00422_00000_pcre, 0, read_00422 + read_00422_ptr, read_00422_len - read_00422_ptr, &read_00422_00000_match);
            if (rc > 0) {
                read_00422_ptr += read_00422_00000_match.match_end - read_00422_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00422_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00422);
        if (read_00422_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00423;
        unsigned int read_00423_len;
        unsigned int read_00423_ptr = 0;
        //**** delimited read
        static unsigned char read_00423_delim[] = 
            "\x0a";
        read_00423 = NULL;
        read_00423_len = 0;
        int read_00423_res = delimited_read(0, &read_00423, &read_00423_len, read_00423_delim, 1);
        if (read_00423_res) {} //silence unused variable warning
        /* read match pcre:
           |      |

*/
        static char read_00423_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x7c\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00423_00000_match;
        pcre *read_00423_00000_pcre = init_regex(read_00423_00000_regex);
        if (read_00423_00000_pcre != NULL) {
            int rc = regex_match(read_00423_00000_pcre, 0, read_00423 + read_00423_ptr, read_00423_len - read_00423_ptr, &read_00423_00000_match);
            if (rc > 0) {
                read_00423_ptr += read_00423_00000_match.match_end - read_00423_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00423_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00423);
        if (read_00423_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00424;
        unsigned int read_00424_len;
        unsigned int read_00424_ptr = 0;
        //**** delimited read
        static unsigned char read_00424_delim[] = 
            "\x0a";
        read_00424 = NULL;
        read_00424_len = 0;
        int read_00424_res = delimited_read(0, &read_00424, &read_00424_len, read_00424_delim, 1);
        if (read_00424_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00424_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00424_00000_match;
        pcre *read_00424_00000_pcre = init_regex(read_00424_00000_regex);
        if (read_00424_00000_pcre != NULL) {
            int rc = regex_match(read_00424_00000_pcre, 0, read_00424 + read_00424_ptr, read_00424_len - read_00424_ptr, &read_00424_00000_match);
            if (rc > 0) {
                read_00424_ptr += read_00424_00000_match.match_end - read_00424_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00424_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00424);
        if (read_00424_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00425;
        unsigned int read_00425_len;
        unsigned int read_00425_ptr = 0;
        //**** delimited read
        static unsigned char read_00425_delim[] = 
            "\x0a";
        read_00425 = NULL;
        read_00425_len = 0;
        int read_00425_res = delimited_read(0, &read_00425, &read_00425_len, read_00425_delim, 1);
        if (read_00425_res) {} //silence unused variable warning
        /* read match pcre:
           ...     |

*/
        static char read_00425_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x2e\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00425_00000_match;
        pcre *read_00425_00000_pcre = init_regex(read_00425_00000_regex);
        if (read_00425_00000_pcre != NULL) {
            int rc = regex_match(read_00425_00000_pcre, 0, read_00425 + read_00425_ptr, read_00425_len - read_00425_ptr, &read_00425_00000_match);
            if (rc > 0) {
                read_00425_ptr += read_00425_00000_match.match_end - read_00425_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00425_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00425);
        if (read_00425_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00426;
        unsigned int read_00426_len;
        unsigned int read_00426_ptr = 0;
        //**** delimited read
        static unsigned char read_00426_delim[] = 
            "\x0a";
        read_00426 = NULL;
        read_00426_len = 0;
        int read_00426_res = delimited_read(0, &read_00426, &read_00426_len, read_00426_delim, 1);
        if (read_00426_res) {} //silence unused variable warning
        /* read match pcre:
           .      |

*/
        static char read_00426_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x2e\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00426_00000_match;
        pcre *read_00426_00000_pcre = init_regex(read_00426_00000_regex);
        if (read_00426_00000_pcre != NULL) {
            int rc = regex_match(read_00426_00000_pcre, 0, read_00426 + read_00426_ptr, read_00426_len - read_00426_ptr, &read_00426_00000_match);
            if (rc > 0) {
                read_00426_ptr += read_00426_00000_match.match_end - read_00426_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00426_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00426);
        if (read_00426_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00427;
        unsigned int read_00427_len;
        unsigned int read_00427_ptr = 0;
        //**** delimited read
        static unsigned char read_00427_delim[] = 
            "\x0a";
        read_00427 = NULL;
        read_00427_len = 0;
        int read_00427_res = delimited_read(0, &read_00427, &read_00427_len, read_00427_delim, 1);
        if (read_00427_res) {} //silence unused variable warning
        /* read match pcre:
           . .     |

*/
        static char read_00427_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00427_00000_match;
        pcre *read_00427_00000_pcre = init_regex(read_00427_00000_regex);
        if (read_00427_00000_pcre != NULL) {
            int rc = regex_match(read_00427_00000_pcre, 0, read_00427 + read_00427_ptr, read_00427_len - read_00427_ptr, &read_00427_00000_match);
            if (rc > 0) {
                read_00427_ptr += read_00427_00000_match.match_end - read_00427_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00427_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00427);
        if (read_00427_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00428;
        unsigned int read_00428_len;
        unsigned int read_00428_ptr = 0;
        //**** delimited read
        static unsigned char read_00428_delim[] = 
            "\x0a";
        read_00428 = NULL;
        read_00428_len = 0;
        int read_00428_res = delimited_read(0, &read_00428, &read_00428_len, read_00428_delim, 1);
        if (read_00428_res) {} //silence unused variable warning
        /* read match pcre:
           |

*/
        static char read_00428_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7c\x0a";
        static match_result read_00428_00000_match;
        pcre *read_00428_00000_pcre = init_regex(read_00428_00000_regex);
        if (read_00428_00000_pcre != NULL) {
            int rc = regex_match(read_00428_00000_pcre, 0, read_00428 + read_00428_ptr, read_00428_len - read_00428_ptr, &read_00428_00000_match);
            if (rc > 0) {
                read_00428_ptr += read_00428_00000_match.match_end - read_00428_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00428_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00428);
        if (read_00428_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00429;
        unsigned int read_00429_len;
        unsigned int read_00429_ptr = 0;
        //**** delimited read
        static unsigned char read_00429_delim[] = 
            "\x0a";
        read_00429 = NULL;
        read_00429_len = 0;
        int read_00429_res = delimited_read(0, &read_00429, &read_00429_len, read_00429_delim, 1);
        if (read_00429_res) {} //silence unused variable warning
        /* read match pcre:
           _______|

*/
        static char read_00429_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x7c\x0a";
        static match_result read_00429_00000_match;
        pcre *read_00429_00000_pcre = init_regex(read_00429_00000_regex);
        if (read_00429_00000_pcre != NULL) {
            int rc = regex_match(read_00429_00000_pcre, 0, read_00429 + read_00429_ptr, read_00429_len - read_00429_ptr, &read_00429_00000_match);
            if (rc > 0) {
                read_00429_ptr += read_00429_00000_match.match_end - read_00429_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00429_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00429);
        if (read_00429_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00430;
        unsigned int read_00430_len;
        unsigned int read_00430_ptr = 0;
        //**** delimited read
        static unsigned char read_00430_delim[] = 
            "\x0a";
        read_00430 = NULL;
        read_00430_len = 0;
        int read_00430_res = delimited_read(0, &read_00430, &read_00430_len, read_00430_delim, 1);
        if (read_00430_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00430_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00430_00000_match;
        pcre *read_00430_00000_pcre = init_regex(read_00430_00000_regex);
        if (read_00430_00000_pcre != NULL) {
            int rc = regex_match(read_00430_00000_pcre, 0, read_00430 + read_00430_ptr, read_00430_len - read_00430_ptr, &read_00430_00000_match);
            if (rc > 0) {
                read_00430_ptr += read_00430_00000_match.match_end - read_00430_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00430_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00430);
        if (read_00430_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00431;
        unsigned int read_00431_len;
        unsigned int read_00431_ptr = 0;
        //**** delimited read
        static unsigned char read_00431_delim[] = 
            "\x0a";
        read_00431 = NULL;
        read_00431_len = 0;
        int read_00431_res = delimited_read(0, &read_00431, &read_00431_len, read_00431_delim, 1);
        if (read_00431_res) {} //silence unused variable warning
        /* read match pcre:


*/
        static char read_00431_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
            "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00431_00000_match;
        pcre *read_00431_00000_pcre = init_regex(read_00431_00000_regex);
        if (read_00431_00000_pcre != NULL) {
            int rc = regex_match(read_00431_00000_pcre, 0, read_00431 + read_00431_ptr, read_00431_len - read_00431_ptr, &read_00431_00000_match);
            if (rc > 0) {
                read_00431_ptr += read_00431_00000_match.match_end - read_00431_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00431_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00431);
        if (read_00431_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00432;
        unsigned int read_00432_len;
        unsigned int read_00432_ptr = 0;
        //**** delimited read
        static unsigned char read_00432_delim[] = 
            "\x0a";
        read_00432 = NULL;
        read_00432_len = 0;
        int read_00432_res = delimited_read(0, &read_00432, &read_00432_len, read_00432_delim, 1);
        if (read_00432_res) {} //silence unused variable warning
        /* read match pcre:
           . . . . . . . .      

*/
        static char read_00432_00000_regex[] = 
            "\x20\x20\x20\x20\x20\x20\x20\x20\x2e\x20\x2e\x20\x2e\x20\x2e\x20"
            "\x2e\x20\x2e\x20\x2e\x20\x2e\x20\x20\x20\x20\x20\x20\x0a";
        static match_result read_00432_00000_match;
        pcre *read_00432_00000_pcre = init_regex(read_00432_00000_regex);
        if (read_00432_00000_pcre != NULL) {
            int rc = regex_match(read_00432_00000_pcre, 0, read_00432 + read_00432_ptr, read_00432_len - read_00432_ptr, &read_00432_00000_match);
            if (rc > 0) {
                read_00432_ptr += read_00432_00000_match.match_end - read_00432_00000_match.match_start;
            }
            else {
                //this is a pov so what does this even mean?
                //why would we quit on failed match, just keep sending stuff.
            }
            pcre_free(read_00432_00000_pcre);
        }
        else {
            //this is a pov so what does this even mean?
            //why would we quit on failed regex compile, just keep sending stuff.
        }
        free(read_00432);
        if (read_00432_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00433;
        unsigned int read_00433_len;
        unsigned int read_00433_ptr = 0;
        //**** length read
        read_00433_len = 20;
        read_00433 = (unsigned char*)malloc(read_00433_len);
        int read_00433_res = length_read(0, read_00433, read_00433_len);
        if (read_00433_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00433_00000[] = 
            "\x53\x6f\x72\x72\x79\x2c\x20\x74\x68\x65\x20\x77\x6f\x72\x64\x20"
            "\x77\x61\x73\x20";
        read_00433_ptr += data_match(read_00433 + read_00433_ptr, read_00433_len - read_00433_ptr, match_00433_00000, 20);
        free(read_00433);
        if (read_00433_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00434;
        unsigned int read_00434_len;
        unsigned int read_00434_ptr = 0;
        //**** length read
        read_00434_len = 8;
        read_00434 = (unsigned char*)malloc(read_00434_len);
        int read_00434_res = length_read(0, read_00434, read_00434_len);
        if (read_00434_res) {} //silence unused variable warning
        //**** read assign to var "word3" from slice
        assign_from_slice("word3", read_00434, read_00434_len - read_00434_ptr, 0, 0, 1);
        free(read_00434);
        if (read_00434_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        unsigned char *read_00435;
        unsigned int read_00435_len;
        unsigned int read_00435_ptr = 0;
        //**** delimited read
        static unsigned char read_00435_delim[] = 
            "\x0a";
        read_00435 = NULL;
        read_00435_len = 0;
        int read_00435_res = delimited_read(0, &read_00435, &read_00435_len, read_00435_delim, 1);
        if (read_00435_res) {} //silence unused variable warning
        //**** read match data
        static unsigned char match_00435_00000[] = 
            "\x21\x0a";
        read_00435_ptr += data_match(read_00435 + read_00435_ptr, read_00435_len - read_00435_ptr, match_00435_00000, 2);
        free(read_00435);
        if (read_00435_ptr) {}  //silence unused variable warning if any
    } while (0);
    do {
        //*** writing data
        static unsigned char write_00032_00000[] = 
            "\x38\x0a";
        static unsigned int write_00032_00000_len = 2;
        unsigned char *write_00032 = NULL;
        unsigned int write_00032_len = 0;
        write_00032 = append_buf(write_00032, &write_00032_len, write_00032_00000, write_00032_00000_len);
        if (write_00032_len > 0) {
            transmit_all(1, write_00032, write_00032_len);
        }
        free(write_00032);
    } while(0);

    do {
        const char *vars[] = { "word0", "word1", "word2", "word3" };
        unsigned char flag[4];
        unsigned char *varbuf;
        size_t varlen;
        int i, j;

        for (i = 0; i < 4; i++) {
            varbuf = getenv(vars[i], &varlen);
            if (varbuf == NULL)
                break;

            for (j = 0; j < 256; j++) {
                if (memcmp(dict[i * 256 + j], varbuf, varlen) == 0) {
                    flag[i] = j;
                    break;
                }
            }
        }

        type2_submit(flag, sizeof(flag));
    } while (0);
}
