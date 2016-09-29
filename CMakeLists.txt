# Using this min version for now
cmake_minimum_required(VERSION 3.1)

project(cb_porting)

# Needed for newer challenges
enable_language(ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Default flags for everything
add_compile_options(
    -fno-builtin
    -Wno-int-to-pointer-cast
    -Wno-writable-strings
    -g3
    -m32
)

# Link everything 32-bit (until we have a 64-bit option)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")

# Linker options
# Dynamic by default
option(BUILD_SHARED_LIBS "" ON)
if(BUILD_STATIC_LIBS AND UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,--allow-multiple-definition")
    SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
    SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
endif()

if(UNIX AND NOT APPLE)
    add_definitions(-DLINUX)
    SET(CMAKE_ASM_COMPILER clang-3.8)
    SET(CMAKE_C_COMPILER clang-3.8)
    SET(CMAKE_CXX_COMPILER clang++-3.8)
endif()
if(APPLE)
    add_definitions(-DAPPLE)
    SET(CMAKE_ASM_COMPILER clang)
    SET(CMAKE_C_COMPILER clang)
    SET(CMAKE_CXX_COMPILER clang++)
endif()
if(WIN32)
    add_definitions(-DWIN)
endif()

# Build all libraries
add_subdirectory(include)
include_directories(include)

function(build path target)
    message("Building ${target}")

    # Gather all sources
    aux_source_directory(${path}/src cb_src)
    aux_source_directory(${path}/lib cb_lib)
    aux_source_directory(${path}/include cb_inc)
    set(cb_all_src ${cb_lib} ${cb_src} ${cb_inc})

    add_executable(${target} ${cb_all_src})
    add_executable(${target}_patched ${cb_all_src})

    target_include_directories(${target} PUBLIC ${path}/lib ${path}/src ${path}/include)
    target_include_directories(${target}_patched PUBLIC ${path}/lib ${path}/src ${path}/include)

    # Add patched defines
    target_compile_definitions(${target}_patched PUBLIC "${patch_defs}")

    target_link_libraries(${target} LINK_PUBLIC libcgc)
    target_link_libraries(${target}_patched LINK_PUBLIC libcgc)
endfunction()

function(buildCB)
    # Generate all the patched #defines for this challenge
    set(patch_defs "-DPATCHED")
    if(VULN_COUNT)
        foreach(i RANGE 1 ${VULN_COUNT})
            set(patch_defs "${patch_defs} -DPATCHED_${i}")
        endforeach()
    endif()

    # Some challenges have multiple binaries that need to be built
    # Check if these directories exist
    file(GLOB cb_parts "${cb_path}/cb_*")
    if(cb_parts)
        # Iterate through the directories and build each
        set(i 1)
        foreach(cb ${cb_parts})
            build(${cb} ${cb_id}_${i})
            MATH(EXPR i "${i} + 1")
        endforeach()
    else()
        # Build normally if there are no extra directories
        build(${cb_path} ${cb_id})
    endif()
endfunction(buildCB)

# More options needed for cbs
add_compile_options(-nostdinc)
add_definitions(-Derrno=__cgc_errno)

file(GLOB challenge_binaries processed-challenges/*)
foreach(cb_path ${challenge_binaries})
    if(IS_DIRECTORY ${cb_path} AND EXISTS ${cb_path}/CMakeLists.txt)
        # Get filename
        get_filename_component(cb_id ${cb_path} NAME)
        add_subdirectory(${cb_path} ${cb_path}/bin)
    endif()
endforeach()
