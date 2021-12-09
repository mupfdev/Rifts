set(CMAKE_SYSTEM_NAME Generic)

set(RIFTS_DIR          ${CMAKE_SOURCE_DIR}/Rifts)
set(SDK_ROOT           ${CMAKE_SOURCE_DIR}/Symbian/6.1)
set(EPOC_PLATFORM      ${SDK_ROOT}/Shared/EPOC32)
set(EPOC_LIB           ${SDK_ROOT}/Series60/Epoc32/Release/armi/urel)
set(STUB_DIR           ${CMAKE_SOURCE_DIR}/Stubs)

set(CMAKE_CXX_COMPILER ${EPOC_PLATFORM}/gcc/bin/gcc.exe)
set(CMAKE_OBJCOPY      ${EPOC_PLATFORM}/gcc/bin/objcopy.exe)
set(CMAKE_OBJDUMP      ${EPOC_PLATFORM}/gcc/bin/objdump.exe)

set(CMAKE_RANLIB       ${EPOC_PLATFORM}/gcc/bin/ranlib.exe)
set(CMAKE_AR           ${EPOC_PLATFORM}/gcc/bin/ar.exe)

set(CMAKE_CXX_COMPILER_ID_RUN TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_WORKS  TRUE)

set(LIBS_UREL
    ${EPOC_LIB}/edllstub.lib
    ${EPOC_LIB}/egcc.lib
    ${EPOC_LIB}/ws32.lib
    ${RIFTS_DIR}/Prototype/NokiaRasterizer/App32/LIB/UREL/NRENDERER.LIB
    ${EPOC_LIB}/bitgdi.lib
    ${EPOC_LIB}/euser.lib
    ${EPOC_LIB}/apparc.lib
    ${EPOC_LIB}/cone.lib
    ${EPOC_LIB}/eikcore.lib
    ${EPOC_LIB}/eikcoctl.lib
    ${EPOC_LIB}/avkon.lib
    ${EPOC_LIB}/fbscli.lib
    ${EPOC_LIB}/efsrv.lib
    ${EPOC_LIB}/estlib.lib
    ${EPOC_LIB}/mediaclientaudiostream.lib
    ${EPOC_LIB}/hal.lib
#    ${EPOC_LIB}/bluetooth.lib
#    ${EPOC_LIB}/esock.lib
    ${EPOC_LIB}/flogger.lib
    ${EPOC_LIB}/sysagt.lib
    ${EPOC_LIB}/msgs.lib)

include_directories(
    SYSTEM
    ${EPOC_PLATFORM}/include
    ${SDK_ROOT}/Series60/Epoc32/Include
    ${SDK_ROOT}/Series60/Epoc32/Include/libc
    ${STUB_DIR}
    ${RIFTS_DIR}/Prototype/NokiaRasterizer/App32/LIB/INC)

set(CORE_FLAGS "-s -fomit-frame-pointer -O -march=armv4t -mthumb-interwork -pipe -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -Wno-switch -mstructure-size-boundary=8")

set(CMAKE_CXX_FLAGS ${CORE_FLAGS} CACHE INTERNAL "cxx compiler flags")

macro(build_dll source uid1 uid2 uid3)
    # Create new DefFile from in library
    add_custom_target(
        ${source}.def
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m arm_interwork --output-def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a)

    # Create new Export file from generated DefFle
    add_custom_target(
        tmp.exp
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.def
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m arm_interwork --def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def --output-exp ${CMAKE_CURRENT_BINARY_DIR}/tmp.exp --dllname ${source}[${UID3}].app)

    # Create new Base file
    add_custom_target(
        ${source}.bas
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/tmp.exp
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/ld -s -e _E32Dll -u _E32Dll ${CMAKE_CURRENT_BINARY_DIR}/tmp.exp --dll --base-file ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas -o ${CMAKE_CURRENT_BINARY_DIR}/tmp.app ${EPOC_LIB}/edll.lib --whole-archive ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a --no-whole-archive ${LIBS_UREL})

    # Create new EXPORT file with def a
    add_custom_target(
        ${source}.exp
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m arm_interwork --def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def --dllname ${source}[${UID3}].app --base-file ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas --output-exp ${CMAKE_CURRENT_BINARY_DIR}/${source}.exp)

    # Create new interface LIB file with def a
    add_custom_target(
        ${source}.lib
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.exp
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/dlltool -m arm_interwork --def ${CMAKE_CURRENT_BINARY_DIR}/${source}.def --dllname ${source}[${UID3}].app --base-file ${CMAKE_CURRENT_BINARY_DIR}/${source}.bas --output-lib ${CMAKE_CURRENT_BINARY_DIR}/${source}.lib)

    add_custom_target(
        ${source}.map
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.lib
        COMMAND
        ${EPOC_PLATFORM}/gcc/bin/ld -s -e _E32Dll -u _E32Dll --dll ${CMAKE_CURRENT_BINARY_DIR}/${source}.exp -Map ${CMAKE_CURRENT_BINARY_DIR}/${source}.map -o tmp.app ${EPOC_LIB}/edll.lib --whole-archive ${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a --no-whole-archive ${LIBS_UREL})

    add_custom_target(
        ${source}.app
        ALL
        DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/${source}.map
        COMMAND
        ${EPOC_PLATFORM}/Tools/petran ${CMAKE_CURRENT_BINARY_DIR}/tmp.app ${CMAKE_CURRENT_BINARY_DIR}/${source}.app -nocall -uid1 ${UID1} -uid2 ${UID2} -uid3 ${UID3})

endmacro()
