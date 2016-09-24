add_library(cgc libcgc.c maths.S ansi_x931_aes128.c)
target_include_directories(cgc PUBLIC tiny-AES128-C)
target_link_libraries(cgc LINK_PUBLIC tiny-AES128-C)

# Build tiny-AES128-C
add_subdirectory(tiny-AES128-C)
