cmake_minimum_required(VERSION 3.14)
project(tolk)

set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LINKER_LANGUAGE CXX)
set(COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

add_compile_definitions(UNICODE)

set(HEADER_FILES
    src/ScreenReaderDriver.h
    src/ScreenReaderDriverJAWS.h
    src/ScreenReaderDriverNVDA.h
    src/ScreenReaderDriverSA.h
    src/ScreenReaderDriverSAPI.h
    src/ScreenReaderDriverSNova.h
    src/ScreenReaderDriverWE.h
    src/ScreenReaderDriverZT.h
    src/Tolk.h
    src/TolkVersion.h
    src/fsapi.h
    src/wineyes.h
    src/zt.h
)

set(SOURCE_FILES
    src/ScreenReaderDriverJAWS.cpp
    src/ScreenReaderDriverNVDA.cpp
    src/ScreenReaderDriverSA.cpp
    src/ScreenReaderDriverSAPI.cpp
    src/ScreenReaderDriverSNova.cpp
    src/ScreenReaderDriverWE.cpp
    src/ScreenReaderDriverZT.cpp
    src/Tolk.cpp
    src/TolkJNI.cpp
    src/fsapi.c
    src/wineyes.c
    src/zt.c
)

# To do: Build examples.

add_library(volk SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(volk User32.Lib Ole32.Lib OleAut32.Lib)