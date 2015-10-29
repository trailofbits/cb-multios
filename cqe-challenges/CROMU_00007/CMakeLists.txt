set( CC "clang")
set( CFLAGS "-O0 -g -Werror -Wno-overlength-strings -Wno-packed -fno-builtin ")
set( INCLUDES "-Ilib -Iinclude")
buildCB(${CFLAGS})