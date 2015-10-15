add_library (libcgc libcgc.c)
if (APPLE)
	set(flags "-DAPPLE")
endif()

if (LINUX)
	set(flags "-DLINUX")
endif()

if (WIN)
	set(flags "-DWIN")
endif()

set_target_properties(libcgc  PROPERTIES COMPILE_FLAGS "${flags}")

target_include_directories (libcgc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})