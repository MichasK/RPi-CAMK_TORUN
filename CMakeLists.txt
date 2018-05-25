cmake_minimum_required(VERSION 3.9)
project(SlitGuide)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
set(SOURCE_FILES main.cpp src/Frame.cpp src/Frame.hpp src/AstronomicFrame.cpp src/FrameData.hpp test/AstronomicFram_test.cpp test/AstronomicFram_test.hpp src/SearchingMethods.cpp src/SearchingMethods.hpp src/uart.c src/uart.h)
file(GLOB TEST_SOURCES test/*.cpp)
add_executable(SlitGuide ${SOURCE_FILES} src/AstronomicFrame.hpp ${TEST_SOURCES} src/SearchingMethods.cpp src/SearchingMethods.hpp)
include_directories(${OpenCV_INCLUDE_DIRS})


target_link_libraries( SlitGuide ${OpenCV_LIBS} gtest)