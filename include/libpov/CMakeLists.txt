file(GLOB srcs *.c)
add_library(pov ${srcs})

target_compile_definitions(pov PUBLIC -DNPATCHED)
target_compile_options(pov PUBLIC
    -Wextra
    -pedantic
    -nostdlib
    -fno-builtin
    -nostdinc
    -O0
    -Wno-overlength-strings
    -Wno-packed
    -Wno-unused-function
)

target_include_directories(pov PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pov LINK_PUBLIC cgc)
