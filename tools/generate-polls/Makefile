BIN_DIR     = $(DESTDIR)/usr/bin
MANDIR      = $(DESTDIR)/usr/share/man/man1
PY_DIR      = $(DESTDIR)/usr/lib/pymodules/python2.7
SHARE_DIR   = $(DESTDIR)/usr/share/generator/examples
MAN         = generate-polls.1.gz

all: man

%.1.gz: %.md
	pandoc -s -t man $< -o $<.tmp
	gzip -9 < $<.tmp > $@

man: $(MAN)

install:
	install -d $(BIN_DIR)
	install -d $(MANDIR)
	install -d $(PY_DIR)/generator
	install -d $(SHARE_DIR)
	install -d $(SHARE_DIR)/bookworm
	install -d $(SHARE_DIR)/dfars
	install -d $(SHARE_DIR)/ftplite
	install generate-polls $(BIN_DIR)
	install $(MAN) $(MANDIR)
	install -m 444 examples/bookworm/* $(SHARE_DIR)/bookworm
	install -m 444 examples/dfars/* $(SHARE_DIR)/dfars
	install -m 444 examples/ftplite/* $(SHARE_DIR)/ftplite
	install -m 444 lib/*.py $(PY_DIR)
	install -m 444 generator/*.py $(PY_DIR)/generator

clean:
	-rm -f *.tmp $(MAN)
