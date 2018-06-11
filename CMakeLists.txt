cmake_minimum_required(VERSION 3.9)
project(SlitGuide)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(include)
set(SOURCE_FILES main.cpp src/Frame.cpp  src/AstronomicFrame.cpp src test/AstronomicFram_test.cpp  src/uart.c src/CenterSearchingMethods.cpp)



set(HEADERS_FILES include/Frame.hpp include/FrameData.hpp include/uart.h include/AstronomicFrame.hpp include/CenterSearchingMethods.hpp)


file(GLOB TEST_SOURCES test/*.cpp)
add_executable(SlitGuide ${SOURCE_FILES} ${TEST_SOURCES} src/SearchingMethods.cpp  ${HEADERS_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})


target_link_libraries( SlitGuide ${OpenCV_LIBS} gtest)