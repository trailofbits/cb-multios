AUTHOR_ID  = KPRCA
SERVICE_ID = 00111
CFLAGS     = -O1 -g -Werror -Wno-overlength-strings -Wno-packed -Wall
CXXFLAGS   = --std=c++11 -fno-exceptions -fno-rtti -DCPLUSPLUS -Dmain=_main
VULN_COUNT = 1

include /usr/share/cb-testing/cgc-cb.mk
