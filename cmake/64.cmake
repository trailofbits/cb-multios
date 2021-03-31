set(CMAKE_SYSTEM_PROCESSOR amd64)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

if(WIN32)
    set(CMAKE_ASM_MASM_COMPILER clang)
else(WIN32)    
    set(CMAKE_ASM_COMPILER clang)
endif(WIN32)