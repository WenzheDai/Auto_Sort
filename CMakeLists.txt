cmake_minimum_required(VERSION 3.21)
project(Auto_Sort)

add_definitions("-Wall -lpthread -g")

set(CMAKE_CXX_STANDARD 11)
add_executable(Auto_Sort main.cpp)

set(SOURCE_FILES main.cpp)
#
find_package(pigpio REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${pigpio_INCLUDE_DIRS})
target_link_libraries(Auto_Sort ${OpenCV_LIBS})
target_link_libraries(Auto_Sort pigpio)

