file(GLOB srcs *.c)
add_library(pov ${srcs})

target_compile_definitions(pov PUBLIC -DNPATCHED)
if(NOT WIN32)
    target_compile_options(pov PUBLIC
        -pedantic
        -fno-builtin
        -O0
    )
endif()

target_include_directories(pov PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pov LINK_PUBLIC cgc)
