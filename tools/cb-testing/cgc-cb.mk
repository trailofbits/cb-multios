ifndef POLLS_RELEASE_COUNT
POLLS_RELEASE_COUNT=1000
endif

ifndef POLLS_RELEASE_SEED
POLLS_RELEASE_SEED=$(shell od -An -i -N 4 /dev/urandom)
endif

ifndef POLLS_RELEASE_MAX_DEPTH
POLLS_RELEASE_MAX_DEPTH=1048575
endif

ifndef POLLS_TESTING_COUNT
POLLS_TESTING_COUNT=1000
endif

ifndef POLLS_TESTING_SEED
POLLS_TESTING_SEED=$(shell od -An -i -N 4 /dev/urandom)
endif

ifndef POLLS_TESTING_MAX_DEPTH
POLLS_TESTING_MAX_DEPTH=1048575
endif

ifndef BIN_COUNT
BIN_COUNT=0
endif

ifndef POLL_REUSE_COUNT
POLL_REUSE_COUNT=0
endif

ifndef VULN_COUNT
VULN_COUNT=0
endif

LIBS       = -L/usr/lib -lcgc
LDFLAGS    = -nostdlib -static
POV_LIBS   = -lpov

CC			= /usr/i386-linux-cgc/bin/clang
LD			= /usr/i386-linux-cgc/bin/ld
CXX			= /usr/i386-linux-cgc/bin/clang++
OBJCOPY			= /usr/i386-linux-cgc/bin/objcopy
LD_ELF                  = /usr/bin/ld

SHELL		:= $(SHELL) -e
BIN_DIR		= bin
POV_DIR		= pov
BUILD_DIR	= build
ifeq ("/usr/i386-linux-cgc/bin/clang", "$(CC)")
CGC_CFLAGS	= -nostdlib -fno-builtin -nostdinc -Iinclude -Ilib -I/usr/include $(CFLAGS) -DCGC_BIN_COUNT=$(BIN_COUNT)
else
CGC_CFLAGS	= -nostdlib -fno-builtin -nostdinc -nostartfiles -nodefaultlibs -Iinclude -Ilib -I/usr/include $(CFLAGS) -DCGC_BIN_COUNT=$(BIN_COUNT)
endif

POV_CFLAGS	= -nostdlib -fno-builtin -nostdinc -Iinclude -Ilib -I/usr/include $(CFLAGS)

EXE		= $(AUTHOR_ID)_$(SERVICE_ID)
CB_INSTALL_DIR	= $(DESTDIR)/usr/share/cgc-challenges/$(EXE)
PATH		:= /usr/i386-linux-cgc/bin:$(PATH)
BINS		= $(wildcard cb_*)
POV_BINS	= $(wildcard pov_*)
POV_SRCS    = $(wildcard pov_*/*.c)
SRCS		= $(wildcard src/*.c src/*.cc lib/*.c lib/*.cc)
CXX_SRCS 	= $(filter %.cc, $(SRCS))
EXTENDED_APP	= /usr/share/cb-testing/CGC_Extended_Application.pdf
EXTENDED_APP_SZ	= $(shell du -b $(EXTENDED_APP) | awk '{print $$1}')

POLLS_RELEASE = $(wildcard poller/for-release/*.xml)
POLLS_TESTING = $(wildcard poller/for-testing/*.xml)
POVS = $(wildcard $(POV_DIR)/*.xml)
POVXML = $(wildcard $(POV_DIR)/*.povxml)

CB_ADDITIONS	=
ifndef NO_CB_DPKG
CB_ADDITIONS	+=dpkg.o
endif
ifndef NO_CB_EXTENDED_APP
CB_ADDITIONS	+=cgc-extended-application.o
endif

has_ids_rules		= $(sort $(wildcard ids/*.rules))
has_cfe_pov   		= $(sort $(wildcard pov_*) $(wildcard pov/*.povxml))
get_poll_args 		= $(if $(call has_cfe_pov),--store_seed --repeat $(POLL_REUSE_COUNT),)
get_pcap_args 		= $(if $(call has_cfe_pov),,--pcap $(PCAP_FILE_PATH))
get_test_args 		= $(if $(call has_cfe_pov),--negotiate,)
get_ids_args 		= $(if $(call has_ids_rules),--ids_rules $(call has_ids_rules,))
get_cb_bins   		= $(sort $(filter-out %_partial, $(filter-out %_patched, $(notdir $(wildcard $(BIN_DIR)/$(EXE)*)))))
get_cb_patched_bins = $(sort $(filter-out %_partial, $(filter %_patched, $(notdir $(wildcard $(BIN_DIR)/$(EXE)*)))))

OBJS_		= $(SRCS:.c=.o)
OBJS		= $(OBJS_:.cc=.o) $(CB_ADDITIONS)
ELF_OBJS	= $(OBJS:.o=.elf)

POV_OBJS	= $(POV_SRCS:.c=.o)
BUILD_POV_OBJS = $(addprefix $(BUILD_DIR)/, $(POV_OBJS))
BUILD_POV_DIRS = $(addprefix $(BUILD_DIR)/, $(POV_BINS))

POV_XML_BINS = $(POVXML:.povxml=.pov)

POLL_RELEASE_LOGS  = $(POLLS_RELEASE:.povxml=.log)
POLL_TESTING_LOGS  = $(POLLS_TESTING:.povxml=.log)
POV_LOGS	= $(POVS:.xml=.log)

BUILD_POLL_TESTING_LOG  = $(addprefix $(BUILD_DIR)/, $(POLL_RELEASE_LOGS))
BUILD_POLL_RELEASE_LOG  = $(addprefix $(BUILD_DIR)/, $(POLL_TESTING_LOGS))
BUILD_POV_LOG   = $(addprefix $(BUILD_DIR)/, $(POV_LOGS))

ifeq ($(VULN_COUNT), 0)
PATCHED_CFLAGS = $(CGC_CFLAGS) -DPATCHED
else
PATCHED_CFLAGS = $(CGC_CFLAGS) $(shell seq -f '-DPATCHED_%g ' -s '' $(VULN_COUNT))
endif 

PATCHED_DIR     = patched
PATCHED_EXE     = $(EXE)_patched
PATCHED_PATH    = $(BIN_DIR)/$(PATCHED_EXE)
PATCHED_OBJS    = $(addprefix $(BUILD_DIR)/$(PATCHED_DIR)/, $(OBJS))
PATCHED_DEBUG_PATH = $(BUILD_DIR)/$(PATCHED_DIR)/$(BIN_DIR)/$(EXE)

PATCHED_ELF_OBJS = $(addprefix $(BUILD_DIR)/$(PATCHED_DIR)/, $(ELF_OBJS))
PATCHED_ELF_STUB = $(BUILD_DIR)/$(PATCHED_DIR)/syscall-stub.elf
PATCHED_SO      = $(BUILD_DIR)/$(PATCHED_DIR)/so/$(EXE).so

RELEASE_CFLAGS  = $(CGC_CFLAGS)
RELEASE_DIR     = release
RELEASE_EXE	= $(EXE)
RELEASE_PATH    = $(BIN_DIR)/$(RELEASE_EXE)
RELEASE_OBJS    = $(addprefix $(BUILD_DIR)/$(RELEASE_DIR)/, $(OBJS))
RELEASE_DEBUG_PATH = $(BUILD_DIR)/$(RELEASE_DIR)/$(BIN_DIR)/$(EXE)

PARTIAL_CFLAGS  = $(CGC_CFLAGS) -DPATCHED_$(PARTIAL_ID)
PARTIAL_DIR     = partial_$(PARTIAL_ID)
PARTIAL_EXE		= $(EXE)_patched_$(PARTIAL_ID)_partial
PARTIAL_PATH    = $(BIN_DIR)/$(PARTIAL_EXE)
PARTIAL_OBJS    = $(addprefix $(BUILD_DIR)/$(PARTIAL_DIR)/, $(OBJS))
PARTIAL_DEBUG_PATH = $(BUILD_DIR)/$(PARTIAL_DIR)/$(BIN_DIR)/$(EXE)

PCAP_DIR        = pcap
PCAP_FILE_PATH	= $(PCAP_DIR)/$(RELEASE_EXE)_poll.pcap
PARTIAL_ID =

all: build test

testit:
	@echo $(call get_cb_bins)
	@echo $(call get_cb_patched_bins)
	@echo $(BINS)

prep:
	@mkdir -p $(BUILD_DIR)/$(PATCHED_DIR)/lib $(BUILD_DIR)/$(PATCHED_DIR)/src $(BUILD_DIR)/$(PATCHED_DIR)/$(BIN_DIR)
	@mkdir -p $(BUILD_DIR)/$(RELEASE_DIR)/lib $(BUILD_DIR)/$(RELEASE_DIR)/src $(BUILD_DIR)/$(RELEASE_DIR)/$(BIN_DIR)
	@mkdir -p $(BUILD_DIR)/$(POV_DIR)
	@mkdir -p $(PCAP_DIR) $(BIN_DIR) $(POV_DIR)
	@mkdir -p $(BUILD_DIR)/poller/for-testing $(BUILD_DIR)/poller/for-release
	@mkdir -p $(BUILD_DIR)/$(PATCHED_DIR)/so $(BUILD_POV_DIRS)
ifneq ($(strip $(PARTIAL_ID)), )
	@mkdir -p $(BUILD_DIR)/$(PARTIAL_DIR)/lib $(BUILD_DIR)/$(PARTIAL_DIR)/src $(BUILD_DIR)/$(PARTIAL_DIR)/$(BIN_DIR)
endif


%.pov: %.povxml
	pov-xml2c -x $< -o $(BUILD_DIR)/$@.c
	$(CC) -c $(POV_CFLAGS) -o $(BUILD_DIR)/$@.o $(BUILD_DIR)/$@.c
	$(LD) $(LDFLAGS) -o $@ $(BUILD_DIR)/$@.o $(LIBS) $(POV_LIBS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(POV_CFLAGS) -o $@ $^

build_pov_objs: prep $(BUILD_POV_OBJS)

$(POV_BINS): build_pov_objs
	$(LD) $(LDFLAGS) -o $(POV_DIR)/$@.pov $(BUILD_DIR)/$@/*.o $(LIBS) $(POV_LIBS)

pov: prep $(POV_XML_BINS) $(POV_BINS)

$(BINS): cb_%:
	( cd $@; make -f ../Makefile build build-partial SERVICE_ID=$(SERVICE_ID)_$* BIN_COUNT=$(words $(BINS)) VULN_COUNT=$(VULN_COUNT))
	cp $@/$(BIN_DIR)/* $(BIN_DIR)

build-binaries: $(BINS)

clean-binaries: ; $(foreach dir, $(BINS), (cd $(dir) && make -f ../Makefile clean) &&) : 

$(BUILD_DIR)/$(RELEASE_DIR)/dpkg.o $(BUILD_DIR)/$(PATCHED_DIR)/dpkg.o $(BUILD_DIR)/$(PARTIAL_DIR)/dpkg.o: /etc/decree_version
	echo "The DECREE packages used in the creation of this challenge binary were:" > $@.txt
	dpkg --list | grep -i cgc >> $@.txt
	$(OBJCOPY) --input binary --output cgc32-i386 --binary-architecture i386 $@.txt $@

$(BUILD_DIR)/$(RELEASE_DIR)/cgc-extended-application.o $(BUILD_DIR)/$(PATCHED_DIR)/cgc-extended-application.o $(BUILD_DIR)/$(PARTIAL_DIR)/cgc-extended-application.o: $(EXTENDED_APP)
	echo "The $(EXTENDED_APP_SZ) byte CGC Extended Application follows. Each team participating in CGC must have submitted this completed agreement including the Team Information, the Liability Waiver, the Site Visit Information Sheet and the Event Participation agreement." > $@.tmp
	cat $(EXTENDED_APP) >> $@.tmp
	$(OBJCOPY) --input binary --output cgc32-i386 --binary-architecture i386 $@.tmp $@

%.elf: %.o
	cp $< $@
	cgc2elf $@

$(PATCHED_ELF_STUB):
	$(CC) -c -nostdlib -fno-builtin -nostdinc -o $(BUILD_DIR)/$(PATCHED_DIR)/syscall-stub.elf /usr/share/cb-testing/syscall-stub.c
	cgc2elf $(BUILD_DIR)/$(PATCHED_DIR)/syscall-stub.elf

build-partial:
ifneq ($(VULN_COUNT), 0)
ifeq ($(BIN_COUNT), 0)
	( for i in $(shell seq $(VULN_COUNT)); do \
		echo $(VULN_COUNT) ; \
		make PARTIAL_ID=$$i partial; \
	  done )
else
	( for i in $(shell seq $(VULN_COUNT)); do \
		echo $(VULN_COUNT) ; \
		make -f ../Makefile PARTIAL_ID=$$i partial; \
	  done )
endif
endif

# Release rules
release: prep $(RELEASE_PATH)

$(RELEASE_PATH): $(RELEASE_OBJS)
	$(LD) $(LDFLAGS) -s -o $(RELEASE_PATH) -I$(BUILD_DIR)/$(RELEASE_DIR)/lib $^ $(LIBS)
	$(LD) $(LDFLAGS) -o $(RELEASE_DEBUG_PATH) -I$(BUILD_DIR)/$(RELEASE_DIR)/lib $^ $(LIBS)

$(BUILD_DIR)/$(RELEASE_DIR)/%.o: %.c
	$(CC) -c $(RELEASE_CFLAGS) -o $@ $<

$(BUILD_DIR)/$(RELEASE_DIR)/%.o: %.cc
	$(CXX) -c $(RELEASE_CFLAGS) $(CXXFLAGS) -o $@ $<

# Partially patched binary rules
partial: prep $(PARTIAL_PATH)

$(PARTIAL_PATH): $(PARTIAL_OBJS)
	$(LD) $(LDFLAGS) -s -o $(PARTIAL_PATH) -I$(BUILD_DIR)/$(PARTIAL_DIR)/lib $^ $(LIBS)
	$(LD) $(LDFLAGS) -o $(PARTIAL_DEBUG_PATH) -I$(BUILD_DIR)/$(PARTIAL_DIR)/lib $^ $(LIBS)

$(BUILD_DIR)/$(PARTIAL_DIR)/%.o: %.c
	$(CC) -c $(PARTIAL_CFLAGS) -o $@ $<

$(BUILD_DIR)/$(PARTIAL_DIR)/%.o: %.cc
	$(CXX) -c $(PARTIAL_CFLAGS) $(CXXFLAGS) -o $@ $<

# Patched rules
patched: prep $(PATCHED_PATH) $(PATCHED_SO)

patched-so: prep $(PATCHED_SO)

$(PATCHED_PATH): $(PATCHED_OBJS)
	$(LD) $(LDFLAGS) -s -o $(PATCHED_PATH) $^ $(LIBS)
	$(LD) $(LDFLAGS) -o $(PATCHED_DEBUG_PATH) -I$(BUILD_DIR)/$(RELEASE_DIR)/lib $^ $(LIBS)

$(BUILD_DIR)/$(PATCHED_DIR)/%.o: %.c
	$(CC) -c $(PATCHED_CFLAGS) -o $@ $<

$(BUILD_DIR)/$(PATCHED_DIR)/%.o: %.cc
	$(CXX) -c $(PATCHED_CFLAGS) $(CXXFLAGS) -o $@ $<

ifneq ("$(CXX_SRCS)", "")
$(PATCHED_SO):
	@echo "SO build artifact not currently supported for C++ services"
else
$(PATCHED_SO): $(PATCHED_ELF_OBJS) $(PATCHED_ELF_STUB)
	$(LD_ELF) -shared -o $@ $^ 
endif

generate-polls:
	if [ -f poller/for-release/machine.py ] && [ -f poller/for-release/state-graph.yaml ]; then generate-polls $(call get_poll_args) --count $(POLLS_RELEASE_COUNT) --seed $(POLLS_RELEASE_SEED) --depth $(POLLS_RELEASE_MAX_DEPTH) poller/for-release/machine.py poller/for-release/state-graph.yaml poller/for-release; fi
	if [ -f poller/for-testing/machine.py ] && [ -f poller/for-testing/state-graph.yaml ]; then generate-polls $(call get_poll_args) --count $(POLLS_TESTING_COUNT) --seed $(POLLS_TESTING_SEED) --depth $(POLLS_TESTING_MAX_DEPTH) poller/for-testing/machine.py poller/for-testing/state-graph.yaml poller/for-testing; fi

check: generate-polls
# Polls that the CB author intends to release the resulting network traffic during CQE
	if [ -d poller/for-release ]; then cb-test $(call get_test_args) --xml_dir poller/for-release/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).for-release.txt --cb $(call get_cb_bins) $(call get_pcap_args); fi
	if [ -d poller/for-release ]; then cb-test $(call get_test_args) --xml_dir poller/for-release/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).for-release.txt --cb $(call get_cb_patched_bins); fi

# Polls that the CB author intends to NOT release the resulting network traffic during CQE
	if [ -d poller/for-testing ]; then cb-test $(call get_test_args) --xml_dir poller/for-testing/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).for-testing.txt --cb $(call get_cb_bins); fi
	if [ -d poller/for-testing ]; then cb-test $(call get_test_args) --xml_dir poller/for-testing/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).for-testing.txt --cb $(call get_cb_patched_bins); fi

# POVs that should generate an identified crash for CQE when sent to the release CB but not the patched CB
	cb-test $(call get_test_args) --xml_dir $(POV_DIR) --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).pov.txt --failure_ok --should_core --cb $(call get_cb_bins)
	cb-test $(call get_test_args) --xml_dir $(POV_DIR) --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).pov.txt --failure_ok --cb $(call get_cb_patched_bins)

check-ids:
	if [ -d poller/for-release ]; then cb-test $(call get_ids_args) $(call get_test_args) --enable_remote --xml_dir poller/for-release/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).for-release-ids.txt    --cb $(call get_cb_bins); fi
	if [ -d poller/for-release ]; then cb-test $(call get_ids_args) $(call get_test_args) --enable_remote --xml_dir poller/for-release/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).for-release-ids.txt    --cb $(call get_cb_patched_bins); fi
	if [ -d poller/for-testing ]; then cb-test $(call get_ids_args) $(call get_test_args) --enable_remote --xml_dir poller/for-testing/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).for-testing-ids.txt    --cb $(call get_cb_bins); fi
	if [ -d poller/for-testing ]; then cb-test $(call get_ids_args) $(call get_test_args) --enable_remote --xml_dir poller/for-testing/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).for-testing-ids.txt    --cb $(call get_cb_patched_bins); fi
	cb-test $(call get_ids_args) $(call get_test_args) --enable_remote --xml_dir $(POV_DIR) --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).pov-ids.txt --failure_ok --cb $(call get_cb_bins)
	cb-test $(call get_ids_args) $(call get_test_args) --enable_remote --xml_dir $(POV_DIR) --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).pov-ids.txt --failure_ok --cb $(call get_cb_patched_bins)

check-remote:
	if [ -d poller/for-release ]; then cb-test                      $(call get_test_args) --enable_remote --xml_dir poller/for-release/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).for-release-remote.txt --cb $(call get_cb_bins); fi
	if [ -d poller/for-release ]; then cb-test                      $(call get_test_args) --enable_remote --xml_dir poller/for-release/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).for-release-remote.txt --cb $(call get_cb_patched_bins); fi
	if [ -d poller/for-testing ]; then cb-test                      $(call get_test_args) --enable_remote --xml_dir poller/for-testing/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).for-testing-remote.txt --cb $(call get_cb_bins); fi
	if [ -d poller/for-testing ]; then cb-test                      $(call get_test_args) --enable_remote --xml_dir poller/for-testing/ --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).for-testing-remote.txt --cb $(call get_cb_patched_bins); fi
	cb-test $(call get_test_args)                      --enable_remote --xml_dir $(POV_DIR) --directory $(BIN_DIR) --log $(BUILD_DIR)/$(RELEASE_EXE).pov-remote.txt --failure_ok --should_core --cb $(call get_cb_bins)
	cb-test $(call get_test_args)                      --enable_remote --xml_dir $(POV_DIR) --directory $(BIN_DIR) --log $(BUILD_DIR)/$(PATCHED_EXE).pov-remote.txt --failure_ok --cb $(call get_cb_patched_bins)

clean-test:
	@-rm -f $(BUILD_POV_LOG) $(BUILD_POLL_LOG)

clean: clean-test clean-binaries
	-rm -rf $(BUILD_DIR) $(BIN_DIR) $(PCAP_DIR)
	-rm -f test.log 
	-rm -f poller/for-release/edges.png poller/for-release/nodes.png poller/for-release/counts.png
	-rm -f poller/for-release/gen_*.xml 
	-rm -f poller/for-release/GEN_*.xml 
	-rm -f poller/for-release/graph.dot
	-rm -f poller/for-testing/edges.png poller/for-testing/nodes.png poller/for-testing/counts.png
	-rm -f poller/for-testing/gen_*.xml 
	-rm -f poller/for-testing/GEN_*.xml 
	-rm -f poller/for-testing/graph.dot
	-rm -f poller/for-release/machine.pyc
	-rm -f poller/for-testing/machine.pyc
	-rm -f $(POV_DIR)/*.pov
	-if [ -d $(POV_DIR) ]; then rmdir --ignore-fail-on-non-empty $(POV_DIR); fi

ifeq ($(strip $(BINS)),)
build: prep release patched pov build-partial
else
build: prep build-binaries pov
endif

install: 
	install -d $(CB_INSTALL_DIR)/$(BIN_DIR)
	install -d $(CB_INSTALL_DIR)/$(POV_DIR)
	if [ ! -z "$(POVS)" ]; then install -m 444 $(wildcard $(POV_DIR)/*.xml) $(CB_INSTALL_DIR)/$(POV_DIR) ; fi
	if [ ! -z "$(POV_BINS)" ] || [ ! -z "$(POVXML)" ]; then install -m 555 $(wildcard $(POV_DIR)/*.pov) $(CB_INSTALL_DIR)/$(POV_DIR) ; fi
	if [ -d ids ]; then install -d $(CB_INSTALL_DIR)/ids ; fi
	if [ -d ids ]; then install -m 444 $(wildcard ids/*.rules) $(CB_INSTALL_DIR)/ids  ; fi
	if [ -d poller/for-release ]; then install -d $(CB_INSTALL_DIR)/poller/for-release ; fi
	if [ -d poller/for-release ]; then install -m 444 $(wildcard poller/for-release/*.xml) $(CB_INSTALL_DIR)/poller/for-release ; fi
	if [ -d poller/for-testing ]; then install -d $(CB_INSTALL_DIR)/poller/for-testing ; fi
	if [ -d poller/for-testing ]; then install -m 444 $(wildcard poller/for-testing/*.xml) $(CB_INSTALL_DIR)/poller/for-testing ; fi
	if [ -f $(PCAP_FILE_PATH) ]; then install -d $(CB_INSTALL_DIR)/$(PCAP_DIR) ; fi
	if [ -f $(PCAP_FILE_PATH) ]; then install -m 444 $(PCAP_FILE_PATH) $(CB_INSTALL_DIR)/$(PCAP_DIR) ; fi
	install -m 555 $(wildcard $(BIN_DIR)/$(EXE)*) $(CB_INSTALL_DIR)/$(BIN_DIR)

test: build check

.PHONY: install all clean clean-test patched prep release remake test build-partial $(BINS) $(POV_BINS) 
