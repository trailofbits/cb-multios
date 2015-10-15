CC = clang
CFLAGS     = -O0 -g -Werror -Wno-overlength-strings -Wno-packed
INCLUDES = -Ilib

ALL:
	-mkdir bin
	$(CC) $(CFLAGS) $(INCLUDES) src/*.c lib/libc.c lib/libcgc.c  -o bin/CADET_00003
