cmake_minimum_required(VERSION 3.5)
project(SoThreads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES src/main.cpp src/resources/Treasury.cpp src/resources/Treasury.h src/resources/Armory.cpp src/resources/Armory.h src/threads/Oil_Field.cpp src/threads/Oil_Field.h src/threads/Army.cpp src/threads/Army.h src/threads/Weapons_Factory.cpp src/threads/Weapons_Factory.h src/threads/Terrorist_Organization.cpp src/threads/Terrorist_Organization.h src/util/utils.h src/util/consts.h src/observers/ConsoleObserver.cpp src/observers/ConsoleObserver.h src/util/kbhit.h)
add_executable(SoThreads ${SOURCE_FILES} src/resources/Treasury.cpp src/resources/Treasury.h src/resources/Armory.cpp src/resources/Armory.h src/util/utils.h src/observers/ConsoleObserver.cpp src/observers/ConsoleObserver.h)