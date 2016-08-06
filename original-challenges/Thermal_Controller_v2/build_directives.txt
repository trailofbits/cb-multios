AUTHOR_ID  = CROMU
SERVICE_ID = 00064
VULN_COUNT = 1


CFLAGS     = -O0 -g -Werror -Wno-overlength-strings -Wno-packed
CXXFLAGS = -fno-exceptions -fno-rtti

include /usr/share/cb-testing/cgc-cb.mk
