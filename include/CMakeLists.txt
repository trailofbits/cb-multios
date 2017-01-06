set(cgc_src libcgc.c maths.S)
if(WIN32)
    set(cgc_src libcgc_win.c maths_win.asm)
    set_source_files_properties(maths_win.asm PROPERTIES COMPILE_FLAGS "/safeseh")
endif()

add_library(cgc ${cgc_src} ansi_x931_aes128.c)
target_include_directories(cgc PUBLIC tiny-AES128-C)
target_link_libraries(cgc LINK_PUBLIC tiny-AES128-C)

# Build tiny-AES128-C
add_subdirectory(tiny-AES128-C)

# Build libpov
add_subdirectory(libpov)
