# Using this min version for now
cmake_minimum_required(VERSION 3.1)

project(cb_porting)
include_directories(include)  # necessary libraries shared by all challenge binaries

# Needed for newer challenges
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if(APPLE)
    set(APPLE TRUE)  # accurate on my mac
endif()
if(WIN32)
    set(WIN TRUE)
endif()

set(main_dir processed-challenges) # directory which contains all cb subdirs

file(GLOB challenge_binaries ${main_dir}/*) # list of all files(+paths) in maindir - all dirs should be cbs

# Build libcgc
add_subdirectory(include)

# Build tiny-AES128-C
add_subdirectory(include/tiny-AES128-C)

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

    set_target_properties(${target} PROPERTIES COMPILE_FLAGS "${CFLAGS} " LINK_FLAGS "-m32")
    set_target_properties(${target}_patched PROPERTIES COMPILE_FLAGS "${CFLAGS} ${patch_defs}" LINK_FLAGS "-m32")

    target_link_libraries(${target} LINK_PUBLIC libcgc)
    target_link_libraries(${target}_patched LINK_PUBLIC libcgc)
endfunction()

function(buildCB flags)
    set(CFLAGS "${flags} -g3 -m32 ${CFLAGS}")
    set(CFLAGS "-Derrno=__cgc_errno ${CFLAGS}")

    # Set OS defines
    if(LINUX)
        set(CFLAGS "-DLINUX ${CFLAGS}")
    endif()
    if(APPLE)
        set(CFLAGS "-DAPPLE ${CFLAGS}")
    endif()
    if(WIN)
        set(CFLAGS "-DWIN ${CFLAGS}")
    endif()

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


foreach(cb_path ${challenge_binaries})          #iterate through cbs
    #	if (LINUX)		- test os
    if(IS_DIRECTORY ${cb_path} AND EXISTS ${cb_path}/CMakeLists.txt)
        MESSAGE("${cb_path}")
        get_filename_component(cb_id ${cb_path} NAME)   #get filename

        add_subdirectory(${cb_path} ${cb_path}/bin)

    endif()
    #	endif()
endforeach()
