#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

set(MAIN ConsoleApp.c)

add_executable(console_app ${MAIN})
target_link_libraries(console_app tolk User32 Ole32 OleAut32)