set(CMAKE_SYSTEM_NAME Generic)

set(SRC_DIR            ${CMAKE_SOURCE_DIR}/src)
set(RIFTS_DIR          ${CMAKE_SOURCE_DIR}/Rifts)
set(SDK_ROOT           ${CMAKE_SOURCE_DIR}/Symbian/6.1)
set(EPOC_PLATFORM      ${SDK_ROOT}/Shared/EPOC32)
set(EPOC_LIB           ${SDK_ROOT}/Series60/Epoc32/Release/armi/urel)

set(CMAKE_CXX_COMPILER ${EPOC_PLATFORM}/gcc/bin/gcc.exe)
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
    ${RIFTS_DIR}/Prototype/NokiaRasterizer/App32/LIB/INC
    ${SRC_DIR})

set(CORE_FLAGS "-s -fomit-frame-pointer -O -march=armv4t -mthumb-interwork -pipe -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -Wno-switch -mstructure-size-boundary=8")

set(CMAKE_CXX_FLAGS ${CORE_FLAGS} CACHE INTERNAL "cxx compiler flags")

function(build_dll machine source file_ext uid1 uid2 uid3)
    # Create new DefFile from in library
    add_custom_target(
        ${source}.def
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m ${machine} --output-def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a)

    # Create new Export file from generated DefFle
    add_custom_target(
        ${source}_tmp.exp
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.def
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m ${machine} --def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def --output-exp ${CMAKE_CURRENT_BINARY_DIR}/${source}_tmp.exp --dllname ${source}[${uid3}].${file_ext})

    # Create new Base file
    add_custom_target(
        ${source}.bas
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}_tmp.exp
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/ld -s -e _E32Dll -u _E32Dll ${CMAKE_CURRENT_BINARY_DIR}/${source}_tmp.exp --dll --base-file ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas -o ${CMAKE_CURRENT_BINARY_DIR}/${source}_tmp.${file_ext} ${EPOC_LIB}/edll.lib --whole-archive ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a --no-whole-archive ${ARGN})

    # Create new EXPORT file with def a
    add_custom_target(
        ${source}.exp
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m ${machine} --def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def --dllname ${source}[${uid3}].${file_ext} --base-file ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas --output-exp ${CMAKE_CURRENT_BINARY_DIR}/${source}.exp)

    # Create new interface LIB file with def a
    add_custom_target(
        ${source}.lib
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.exp
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m ${machine} --def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def --dllname ${source}[${uid3}].${file_ext} --base-file ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas --output-lib ${CMAKE_CURRENT_BINARY_DIR}/${source}.lib)

    add_custom_target(
        ${source}.map
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.lib
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/ld -s -e _E32Dll -u _E32Dll --dll ${CMAKE_CURRENT_BINARY_DIR}/${source}.exp -Map ${CMAKE_CURRENT_BINARY_DIR}/${source}.map -o ${source}_tmp.${file_ext} ${EPOC_LIB}/edll.lib --whole-archive ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a --no-whole-archive ${ARGN})

    add_custom_target(
        ${source}.${file_ext}
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.map
        COMMAND
        ${EPOC_PLATFORM}/Tools/petran ${CMAKE_CURRENT_BINARY_DIR}/${source}_tmp.${file_ext} ${CMAKE_CURRENT_BINARY_DIR}/${source}.${file_ext} -nocall -uid1 ${uid1} -uid2 ${uid2} -uid3 ${uid3})
endfunction()

function(install_file project_name source_dir file drive_letter)
    add_custom_target(
        ${file}_install
        ALL
        DEPENDS
        ${source_dir}/${file}
        COMMAND
        ${CMAKE_COMMAND} -E copy
        ${source_dir}/${file}
        ${drive_letter}:/system/apps/${project_name}/${file})
endfunction()
