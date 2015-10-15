
CC = clang
CFLAGS     = -O0 -g -Werror -Wno-overlength-strings -Wno-packed
INCLUDES = -Ilib -Iinclude

all:
	-mkdir bin
	$(CC) $(CFLAGS) $(INCLUDES) src/*.c lib/*.c  -o bin/CROMU_00007

