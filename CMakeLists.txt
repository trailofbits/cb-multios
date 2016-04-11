project (cb_porting)
include_directories ("include") 											#nessecary libraries shared by all challenge binaries

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
	set(CMAKE_C_COMPILER clang-3.6)
endif()
if(APPLE)
	set(APPLE TRUE)  ##accurate on my mac
endif()
if(WIN32)
	set(WIN TRUE)
endif()

set( main_dir cqe-challenges )												#directory which contains all cb subdirs 

file(GLOB challenge_binaries ${main_dir}/*) 								#list of all files(+paths) in maindir - all dirs should be cbs
add_subdirectory(include)

function(buildCB flags)
	MESSAGE("building ${cb_id}")
	aux_source_directory(${cb_path}/src cb_src) 								#get all source files
	aux_source_directory(${cb_path}/lib cb_lib)  
	aux_source_directory(${cb_path}/include cb_inc)  
	set(cb_all_src ${cb_lib} ${cb_src} ${cb_inc}  )

	include_directories(${cb_path}/lib)
	include_directories(${cb_path}/src)
	include_directories(${cb_path}/include)

	set(CFLAGS "${flags} -g3 ${CFLAGS}")
	set(CFLAGS "-Derrno=__cgc_errno ${CFLAGS}")
	set(CFLAGS "-isystem include ${CFLAGS}")

	if(LINUX)
		set(LINUX TRUE)
		set(CFLAGS "-m32 ${CFLAGS}")
	endif()

	add_executable(${cb_id} ${cb_all_src}   ) 
	add_executable(${cb_id}_patched ${cb_all_src}   ) 

	set_target_properties(${cb_id} PROPERTIES COMPILE_FLAGS "${CFLAGS}")
	set_target_properties(${cb_id}_patched  PROPERTIES COMPILE_FLAGS "${CFLAGS} -DPATCHED")	

	target_link_libraries (${cb_id} LINK_PUBLIC libcgc)
	target_link_libraries (${cb_id}_patched LINK_PUBLIC libcgc)
	
endfunction(buildCB)

function(buildCB_LD flags ldflags)
	MESSAGE("building ${cb_id}")
	aux_source_directory(${cb_path}/src cb_src) 								#get all source files
	aux_source_directory(${cb_path}/lib cb_lib)  
	aux_source_directory(${cb_path}/include cb_inc)  
	set(cb_all_src ${cb_lib} ${cb_src} ${cb_inc}  )

	include_directories(${cb_path}/lib)
	include_directories(${cb_path}/src)
	include_directories(${cb_path}/include)

	set(CFLAGS "${flags} -g3 ${CFLAGS}")
	if(LINUX)
		set(LINUX TRUE)
		set(CFLAGS "-m32 ${CFLAGS}")
	endif()

	add_executable(${cb_id} ${cb_all_src}   ) 
	add_executable(${cb_id}_patched ${cb_all_src}  ) 

	set_target_properties(${cb_id}  PROPERTIES COMPILE_FLAGS "${CFLAGS}")
	set_target_properties(${cb_id}  PROPERTIES LINK_FLAGS "${ldflags}")
	set_target_properties(${cb_id}_patched  PROPERTIES COMPILE_FLAGS "${CFLAGS} -DPATCHED")	
	set_target_properties(${cb_id}_patched  PROPERTIES LINK_FLAGS "${ldflags} -DPATCHED")

	target_link_libraries (${cb_id} LINK_PUBLIC libcgc)
	target_link_libraries (${cb_id}_patched LINK_PUBLIC libcgc)

endfunction(buildCB_LD)


FOREACH(cb_path ${challenge_binaries})										#iterate through cbs
#	if (LINUX)		- test os														
		if (IS_DIRECTORY ${cb_path})
			MESSAGE("${cb_path}")
			get_filename_component(cb_id ${cb_path}  NAME )			#get filename
								
			add_subdirectory(${cb_path} ${cb_path}/bin)

		endif()
#	endif()
ENDFOREACH()
