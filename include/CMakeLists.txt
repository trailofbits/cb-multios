add_library(libcgc libcgc.c maths.S ansi_x931_aes128.c)
target_include_directories(libcgc PUBLIC tiny-AES128-C)
target_link_libraries(libcgc LINK_PUBLIC tiny-AES128-C)

# Build tiny-AES128-C
add_subdirectory(tiny-AES128-C)
