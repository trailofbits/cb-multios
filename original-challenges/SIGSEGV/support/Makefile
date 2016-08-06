CC = /usr/i386-linux-cgc/bin/clang
LD = /usr/i386-linux-cgc/bin/ld
MKDIR = mkdir -p

CFLAGS = -fno-builtin -nostdinc
LDFLAGS = --nostdlib --static --oformat=binary

SRC = src
OUT = out
BIN = $(OUT)/1.bin $(OUT)/2.bin $(OUT)/3.bin $(OUT)/4.bin $(OUT)/5.bin
PROCESS = ./process.py

all: dirs bins process

%.o: $(SRC)/%.c
	$(CC) -c -o $@ $< -I$(SRC)/ $(CFLAGS)

$(OUT)/%.bin: %.o
	$(LD) -o $@ $(LDFLAGS) $<

process:
	$(PROCESS) $(OUT)

bins: $(BIN)

dirs: $(OUT)

$(OUT):
	$(MKDIR) $(OUT)

clean:
	$(RM) -rf $(OUT) payloads.py trusted.h

.PHONY: dirs bins all process
