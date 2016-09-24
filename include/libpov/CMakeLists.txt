
# -c -Wall -Wextra -pedantic -DNPATCHED -nostdlib -fno-builtin -nostdinc -Iinclude -Ilib -I/usr/include -g -O0 -Wno-overlength-strings -Wno-packed -Wno-unused-function
file(GLOB srcs *.c)
add_library(pov ${srcs})
set_target_properties(pov PROPERTIES COMPILE_FLAGS "${CFLAGS} -c -Wall -Wextra -pedantic -DNPATCHED -nostdlib -fno-builtin -nostdinc -g -O0 -Wno-overlength-strings -Wno-packed -Wno-unused-function" LINK_FLAGS "${LDFLAGS} ")
target_include_directories(pov PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
