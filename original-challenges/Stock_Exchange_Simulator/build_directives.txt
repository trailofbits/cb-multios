AUTHOR_ID  = NRFIN
SERVICE_ID = 00045
CFLAGS     = -O0 -g -Werror -Wno-overlength-strings -Wno-packed
VULN_COUNT = 1
POLLS_RELEASE_MAX_DEPTH = 500

include /usr/share/cb-testing/cgc-cb.mk
