AUTHOR_ID  = KPRCA
SERVICE_ID = 00091
CFLAGS     = -Oz -g -Werror -Wno-overlength-strings -Wno-packed -Wall
CXXFLAGS   = --std=c++11 -fno-exceptions -fno-rtti -DCPLUSPLUS -Dmain=_main
override LDFLAGS = -nostdlib -static -Ttext=0x90000000
VULN_COUNT = 1

include /usr/share/cb-testing/cgc-cb.mk
