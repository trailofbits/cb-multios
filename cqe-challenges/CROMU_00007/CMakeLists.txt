set( CC "clang")
set( CFLAGS "-O0 -g -Werror -Wno-overlength-strings -Wno-packed -fno-builtin -Wno-int-to-pointer-cast ")
set( INCLUDES "-Ilib -Iinclude")
buildCB(${CFLAGS})