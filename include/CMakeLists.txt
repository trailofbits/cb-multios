enable_language(ASM)
add_library(libcgc libcgc.c maths.S)

if(APPLE)
    set(flags "-DAPPLE")
endif()

if(LINUX)
    set(flags "-fno-builtin   -DLINUX")
endif()

if(WIN)
    set(flags "-DWIN")
endif()

set_target_properties(libcgc PROPERTIES COMPILE_FLAGS "-m32 ${flags}")

target_include_directories(libcgc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
