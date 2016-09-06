add_library(tiny-AES128-C aes.c)
set_target_properties(tiny-AES128-C PROPERTIES COMPILE_FLAGS "-m32")
target_include_directories(tiny-AES128-C PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
