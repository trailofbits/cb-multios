POLLS_RELEASE_SEED= -820736521
POLLS_TESTING_SEED= 581115464
AUTHOR_ID  = NRFIN
SERVICE_ID = 00010
POLLS_RELEASE_COUNT = 200
POLLS_TESTING_COUNT = 1000

CFLAGS     = -O0 -g -Werror -Wno-overlength-strings -Wno-packed

include /usr/share/cb-testing/cgc-cb.mk
