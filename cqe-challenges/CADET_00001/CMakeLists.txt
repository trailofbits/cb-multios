set( CFLAGS "-O0 -g -Wno-overlength-strings -Wno-packed -DFORTIFY_SOURCE=0 -fno-stack-protector -fno-builtin -Wno-int-to-pointer-cast ")
buildCB(${CFLAGS})