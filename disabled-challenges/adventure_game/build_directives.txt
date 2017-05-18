AUTHOR_ID  = KPRCA
SERVICE_ID = 00025
CFLAGS     = -Os -g -Werror -Wno-overlength-strings -Wno-packed -fms-extensions -Wno-microsoft
override LDFLAGS = -nostdlib -static --sort-section=name 
POLLS_TESTING_COUNT = 1000
POLLS_TESTING_SEED = -399189653
POLLS_RELEASE_COUNT = 1
POLLS_RELEASE_SEED = 90

include /usr/share/cb-testing/cgc-cb.mk
