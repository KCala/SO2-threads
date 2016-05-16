cmake_minimum_required(VERSION 3.5)
project(SoThreads)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/target")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lncurses")

set(SOURCE_FILES src/main.cpp src/resources/Treasury.cpp src/resources/Treasury.h src/resources/Armory.cpp src/resources/Armory.h src/threads/Oil_Field.cpp src/threads/Oil_Field.h src/threads/Army.cpp src/threads/Army.h src/threads/Weapons_Factory.cpp src/threads/Weapons_Factory.h src/threads/Terrorist_Organization.cpp src/threads/Terrorist_Organization.h src/util/utils.h src/util/consts.h src/util/kbhit.h src/display/Displayer.cpp src/display/Displayer.h)
add_executable(SoThreads ${SOURCE_FILES} src/resources/Treasury.cpp src/resources/Treasury.h src/resources/Armory.cpp src/resources/Armory.h src/util/utils.h src/display/Displayer.cpp src/display/Displayer.h)

find_package(Curses REQUIRED)
target_link_libraries(SoThreads ${CURSES_LIBRARIES})

