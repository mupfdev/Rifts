set(CMAKE_SYSTEM_NAME Generic)

set(SDK_ROOT           ${CMAKE_SOURCE_DIR}/Symbian/6.1)
set(EPOC_PLATFORM      ${SDK_ROOT}/Shared/EPOC32)
set(STUB_DIR           ${CMAKE_SOURCE_DIR}/Stubs)

set(CMAKE_C_COMPILER   ${EPOC_PLATFORM}/gcc/bin/gcc.exe)
set(CMAKE_CXX_COMPILER ${EPOC_PLATFORM}/gcc/bin/gcc.exe)
set(CMAKE_ASM_COMPILER ${EPOC_PLATFORM}/gcc/bin/gcc.exe)
set(CMAKE_OBJCOPY      ${EPOC_PLATFORM}/gcc/bin/objcopy.exe)
set(CMAKE_OBJDUMP      ${EPOC_PLATFORM}/gcc/bin/objdump.exe)

set(CMAKE_RANLIB       ${EPOC_PLATFORM}/gcc/bin/ranlib.exe)
set(CMAKE_AR           ${EPOC_PLATFORM}/gcc/bin/ar.exe)

set(CMAKE_CXX_COMPILER_ID_RUN TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_WORKS  TRUE)

include_directories(
    SYSTEM
    ${EPOC_PLATFORM}/include
    ${SDK_ROOT}/Series60/Epoc32/Include
    ${SDK_ROOT}/Series60/Epoc32/Include/libc
    ${STUB_DIR})

set(CORE_FLAGS "-s -fomit-frame-pointer -O -march=armv4t -mthumb-interwork -pipe -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -Wno-switch -mstructure-size-boundary=8")

set(CMAKE_C_FLAGS   ${CORE_FLAGS} CACHE INTERNAL "c compiler flags")
set(CMAKE_CXX_FLAGS ${CORE_FLAGS} CACHE INTERNAL "cxx compiler flags")
set(CMAKE_ASM_FLAGS ${CORE_FLAGS} CACHE INTERNAL "asm compiler flags")
