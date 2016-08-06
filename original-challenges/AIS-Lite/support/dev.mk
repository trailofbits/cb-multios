
# unit tests
ALLSRCS = $(wildcard lib/*.c test/*.c test/lib/*.c src/*.c)
UTSRCS = $(filter-out src/service.c,$(ALLSRCS))
UTOBJS = $(UTSRCS:.c=.o)
UTOBJDIR = tbuild/
UT_DIR = test/
BINDIR = bin/
UTPATH = $(BINDIR)$(UT_DIR)

TEST_SRCS = $(wildcard $(UT_DIR)/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_BINS = $(notdir $(TEST_OBJS:.o=))

UTOBJS_NO_TESTS = $(addprefix $(UTOBJDIR), $(filter-out test/test_%,$(UTOBJS)))
UTOBJS_ONLY_TESTS = $(addprefix $(UTOBJDIR), $(filter test/test_%,$(UTOBJS)))

UTCC = /usr/i386-linux-cgc/bin/clang
UTCFLAGS = -nostdlib -fno-builtin -nostdinc -Iinclude -Ilib -Isrc -Itest/lib -I/usr/include -O0 -g -Werror -Wno-overlength-strings -Wno-packed 

UTLD = /usr/i386-linux-cgc/bin/ld
UTLDIFLAGS = -I/usr/include -Itbuild/lib -Itbuild/test/lib
UTLDLFLAGS = -Ltbuild/test -L/usr/lib -lcgc

#TEST_PATCHED_CFLAGS = -DPATCHED

.PHONY: unit_test unit_clean unit_prep gen_pov1 clean_pov1

# have to define a newline so that the test commands can execute; it puts the commands on separate lines
define \n


endef

unit_test: unit_prep $(UTOBJS) $(TEST_BINS)
	$(foreach bin,$(TEST_BINS), ./$(addprefix $(UTPATH),$(bin))${\n})

$(UTOBJS): %.o: %.c
	$(UTCC) -c $(UTCFLAGS) $(TEST_PATCHED_CFLAGS) -o $(addprefix $(UTOBJDIR), $@) $<

$(TEST_BINS):
	$(UTLD) -nostdlib -static -o $(addprefix $(UTPATH), $@) $(UTLDIFLAGS) $(filter %$@.o,$(UTOBJS_ONLY_TESTS)) $(UTOBJS_NO_TESTS) $(UTLDLFLAGS)

unit_clean:
	rm -rf $(UTOBJDIR) $(BINDIR)

unit_prep:
	@mkdir $(BINDIR) $(UTPATH) $(UTOBJDIR) $(UTOBJDIR)/lib $(UTOBJDIR)/src $(UTOBJDIR)/test $(UTOBJDIR)/test/lib



GEN_POV_DIR = support/gen_povs
pov_gen:
	generate-polls --count 1 $(GEN_POV_DIR)/machine.py $(GEN_POV_DIR)/state-graph.yaml $(GEN_POV_DIR)
	cp $(GEN_POV_DIR)/*.xml pov/POV_00099.xml

pov_clean:
	rm -f $(GEN_POV_DIR)/*.xml $(GEN_POV_DIR)/*.png $(GEN_POV_DIR)/*.dot


# include Makefile
# # clang security tests
# include sectest.mk
