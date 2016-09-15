enable_language(ASM)
add_library(libcgc libcgc.c maths.S ansi_x931_aes128.c)

if(APPLE)
    set(flags "-DAPPLE")
endif()

if(LINUX)
    set(flags "-fno-builtin -DLINUX")
endif()

if(WIN)
    set(flags "-DWIN")
endif()

set_target_properties(libcgc PROPERTIES COMPILE_FLAGS "-m32 ${flags}" LINK_FLAGS "${LDFLAGS} ")
target_include_directories(libcgc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/tiny-AES128-C)
target_link_libraries(libcgc LINK_PUBLIC tiny-AES128-C)
