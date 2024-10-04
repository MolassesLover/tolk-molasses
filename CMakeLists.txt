cmake_minimum_required(VERSION 3.14)
project(tolk)

set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(COMPILE_WARNING_AS_ERROR ON)
set(LINKER_LANGUAGE CXX)

option(BUILD_EXAMPLES OFF)

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

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

add_library(tolk SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(tolk PUBLIC /usr/include/w32api/)

target_link_libraries(tolk User32 Ole32 OleAut32)